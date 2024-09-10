#pragma once

//
// ... LBM Bench header files
//
#include <lbm/D2Q9/Cell.hpp>
#include <lbm/D2Q9/Grid.hpp>
#include <lbm/D2Q9/import.hpp>

namespace lbm::D2Q9 {

  template <class T>
  class State final : public I_State {
  public:
    using Lattice_Spacing = T;
    using Time_Step = size_type;
    using Cell_Type = Cell<T>;
    using Grid_Type = Grid<T>;
    using Obstacle_List = vector<size_type>;
    using Bounceback_Lists = Fixed_MD_Array<Dynamic_MD_Array<size_type>, Fixed_Lexical<3, 3>>;

    static constexpr array<array<size_type, 2>, 9> classes{
        // clang-format off
      {{-1, -1}, {0, -1}, {1, -1},
       {-1,  0}, {0,  0}, {1,  0},
       {-1,  1}, {0,  1}, {1,  1}}
        // clang-format on
    };

    static constexpr array<array<size_type, 2>, 8> neighbor_offsets{
        // clang-format off
      {{-1, -1}, {0, -1}, {1, -1},
       {-1,  0},          {1,  0},
       {-1,  1}, {0,  1}, {1,  1}}
        // clang-format on
    };

    static constexpr array<array<size_type, 2>, 3> left_internal_offsets{
        // clang-format off
      {{1, -1},
       {1,  0},
       {1,  1}}
        // clang-format on
    };

    static constexpr array<array<size_type, 2>, 3> right_internal_offsets{
        // clang-format off
      {{-1, -1},
       {-1,  0},
       {-1,  1}}
        // clang-format on
    };

    static constexpr array<array<size_type, 2>, 3> bottom_internal_offsets{
        // clang-format off
      {{-1, 1}, {0,  1}, {1,  1}}
        // clang-format on
    };

    static constexpr array<array<size_type, 2>, 3> top_internal_offsets{
        // clang-format off
      {{-1, -1}, {0, -1}, {1, -1}}
        // clang-format on
    };

    State() = default;

    State(Input input)
        : input_{input} {
      initialize();
      initialize_cells();
      initialize_bounceback_lists();
      initialize_boundary_functions();
    }

    void
    initialize() {
      nx_ = input_.ncells(0) + 2; // add 2 for ghost cells on the boundary
      ny_ = input_.ncells(1) + 2;
      nxm1_ = nx_ - 1;
      nym1_ = ny_ - 1;
      order_ = Shape{nx_, ny_};
      lattice_spacing_ = input_.lattice_spacing();
      grids_ = {{Grid_Type{order_}, Grid_Type{order_}}};
    }

    void
    step() override {
      stream();
      collide();
      set_bounce_back_cells();
      set_boundary_cells();
      ++time_step_;
    }

    Time_Step
    time_step() const {
      return time_step_;
    }

    friend bool
    operator==(const State &state0, const State &state1) {
      return json(state0) == json(state1);
      return state0.time_step_ == state1.time_step_ &&
             state0.get_current_cells() == state1.get_current_cells();
    }

    friend bool
    operator!=(const State &state0, const State &state1) {
      return !(state0 == state1);
    }

  private:
    void
    initialize_cells() {
      auto &cells = grids_[current_time_index()];
      for_each(std::begin(cells),
               std::end(cells),
               [&, this, index = size_type(0)](Cell_Type &cell) mutable {
                 const auto coord = cell_coord(index);
                 cell.init(input_.density(coord), input_.velocity(coord));
                 if (input_.is_obstacle(coord)) {
                   obstacles_.push_back(index);
                 }
                 ++index;
               });
    }

    Euclidean
    cell_coord(const size_type index) {
      const auto [i, j] = order_.array_index(index);
      return {(i - T{0.5}) * lattice_spacing_, (j - T{0.5}) * lattice_spacing_};
    }

    void
    initialize_bounceback_lists() {
      for_each(std::cbegin(obstacles_), std::cend(obstacles_), [this](size_type index) {
        return initialize_bounceback_list_obstacle(index);
      });
    }

    void
    initialize_bounceback_list_obstacle(size_type index) {
      const auto &cells = grids_[0];
      const auto ijobst = order_.array_index(index);

      // Note: [clang] structured binding encounters errors using
      // structured binding here for clang versions 15 and below,
      // but the bug is fixed in version 18.
      const size_type iobst = std::get<0>(ijobst);
      const size_type jobst = std::get<1>(ijobst);

      for_each(
          std::cbegin(neighbor_offsets),
          std::cend(neighbor_offsets),
          [&, this](const auto &offsets) {
            const auto &[ioffset, joffset] = offsets;
            const size_type i = iobst + ioffset;
            const size_type j = jobst + joffset;
            if (interior_indices(i, j) && !cells(i, j).is_obstacle()) {
              bounceback_lists_(ioffset + 1, joffset + 1).push_back(order_.storage_index(i, j));
            }
          });
    }

    bool
    domain_indices(size_type i, size_type j) {
      return i >= 0 && i < nx_ && j >= 0 && j < ny_;
    }

    bool
    interior_indices(size_type i, size_type j) {
      return i >= 1 && i < nxm1_ && j >= 1 && j < nym1_;
    }

    void
    initialize_boundary_functions() {}

    // The wall boundary cell should have particle densities that correspond
    // to retro-reflection on the boundary.
    template <Boundary_Tag2 Boundary>
    function<void()>
    make_wall_boundary(Boundary) {
      const auto internal_offsets = get_internal_offsets(Boundary{});
      return [=, this] {
        auto &cells = get_next_cells();
        forall(cells.begin(Boundary{}), cells.end(Boundary{}), [=, this](auto cell) {
          for_each(std::cbegin(internal_offsets), std::cend(internal_offsets), [&](auto offsets) {
            const auto &[i, j] = offsets;
            cell(0, 0)(i, j) = cell(i, j)(-i, -j);
          });
        });
      };
    }

    // The symmetry boundary cell should have particle densities that match the
    // interior cell for the mirrored velocity classes. The boundary condition is
    // set one-to-one between the boundary and interior cells.
    //
    // Like specular reflection on the boundary.
    template <Boundary_Tag2 Boundary>
    function<void()>
    make_symmetry_boundary(Boundary) {
      const auto internal_offsets = get_internal_offsets(Boundary{});
      return [=, this] {
        auto cells = get_next_cells();
        forall(cells.begin(Boundary{}), cells.end(Boundary{}), [this](auto cell) {
          if constexpr (same_as<Boundary, Left>) {
            for (size_type i = -1; i < 2; ++i) {
              for (size_type j = -1; j < 2; ++j) {
                cell(0, 0)(i, j) = cell(1, 0)(-i, j);
              }
            }
          } else if constexpr (same_as<Boundary, Right>) {
            for (size_type i = -1; i < 2; ++i) {
              for (size_type j = -1; j < 2; ++j) {
                cell(0, 0)(i, j) = cell(-1, 0)(-i, j);
              }
            }
          } else if constexpr (same_as<Boundary, Bottom>) {
            for (size_type i = -1; i < 2; ++i) {
              for (size_type j = -1; j < 2; ++j) {
                cell(0, 0)(i, j) = cell(-1, 0)(-i, j);
              }
            }
          } else if constexpr (same_as<Boundary, Top>) {
            for (size_type i = -1; i < 2; ++i) {
              for (size_type j = -1; j < 2; ++j) {
                cell(0, 0)(i, j) = cell(-1, 0)(-i, j);
              }
            }
          }
        });
      };
    }

    // For periodic boundaries, the cell values from the other side of the
    // domain must be copied.
    template <Boundary_Tag2 Boundary>
    function<void()>
    make_periodic_boundary(Boundary) {
      return [this] {
        auto &cells = get_next_cells();

        if constexpr (same_as<Boundary, Left> || same_as<Boundary, Right>) {
          forall(
              cells.begin(left), cells.end(left), cells.begin(right), [](auto cell1, auto cell2) {
                cell1(0, 0) = cell2(-1, 0);
                cell2(0, 0) = cell1(1, 0);
              });

        } else if constexpr (same_as<Boundary, Bottom> || same_as<Boundary, Top>) {
          forall(
              cells.begin(bottom), cells.end(bottom), cells.begin(top), [](auto cell1, auto cell2) {
                cell1(0, 0) = cell2(-1, 0);
                cell2(0, 0) = cell1(1, 0);
              });
        }
      };
    }

    // For an inlet boundary, the particle  class densities are computed
    // according to the defined velocity and density with the addition of
    // bounceback for the non-equilibrium parts of the adjacent cells.
    //
    // Notes:
    // ------
    //
    // This will need to compute the equilibrium of the constant velocity and
    // density.  That should be done once at the start of the program.
    //
    // This will need to compute the equilibrium on the cells adjacent to
    // the boundary to enable the bounceback of the nonequilibrium portion to
    // be computed.  Naively implemented, this would compute the equilibrium
    // three times.
    template <Boundary_Tag2 Boundary>
    function<void()>
    make_inlet_boundary(Boundary) {
      return [] {};
    }

    template <Boundary_Tag2 Boundary>
    static constexpr Fixed_Euclidean<T, 2>
    inward_normal(Boundary) {
      if constexpr (same_as<Boundary, Left>) {
        return {1, 0};
      } else if constexpr (same_as<Boundary, Right>) {
        return {-1, 0};
      } else if constexpr (same_as<Boundary, Bottom>) {
        return {0, 1};
      } else if constexpr (same_as<Boundary, Top>) {
        return {0, -1};
      }
    }

    // Outlet boundaries should be nonreflecting
    function<void()>
    make_outlet_boundary() {
      return [] {};
    }

    // Pressure drop boundaries will involve two boundaries, similar to periodic
    function<void()>
    make_pressure_drop_boundary() {
      return [] {};
    }

    template <Boundary_Tag2 Boundary>
    auto
    get_internal_offsets(Boundary) {
      if constexpr (same_as<Boundary, Left>) {
        return left_internal_offsets;

      } else if constexpr (same_as<Boundary, Right>) {
        return right_internal_offsets;

      } else if constexpr (same_as<Boundary, Bottom>) {
        return bottom_internal_offsets;

      } else if constexpr (same_as<Boundary, Top>) {
        return top_internal_offsets;
      }
    }

    void
    set_bounce_back_cells() {}

    void
    set_boundary_cells() {
      for_each(std::begin(boundary_functions_),
               std::end(boundary_functions_),
               [](auto &boundary_function) { boundary_function(); });
    }

    Grid_Type &
    get_current_cells() {
      return grids_[current_time_index()];
    }

    const Grid_Type &
    get_current_cells() const {
      return grids_[current_time_index()];
    }

    Grid_Type &
    get_next_cells() {
      return grids_[next_time_index()];
    }

    const Grid_Type &
    get_next_cells() const {
      return grids_[next_time_index()];
    }

    size_type
    current_time_index() const {
      return time_step_ % 2;
    }

    size_type
    next_time_index() const {
      return (time_step_ + 1) % 2;
    }

    void
    stream() {
      const auto &current_cells = get_current_cells();
      auto &next_cells = get_next_cells();
      forall(current_cells.begin(interior),
             current_cells.end(interior),
             next_cells.begin(interior),
             [](auto current_cell, auto next_cell) {
               for_each(classes.begin(), classes.end(), [&](auto offsets) {
                 const auto &[i, j] = offsets;
                 next_cell(0, 0)(i, j) = current_cell(-i, -j)(i, j);
               });
             });
    }

    void
    collide() {
      auto &cells = grids_[(time_step_ + 1) % 2];
      for_each(std::begin(cells), std::end(cells), [&](auto &cell) { cell.collide(); });
    }

    json
    get_json() const override {
      json j = json::object();
      j["input"] = input_;
      j["timeStep"] = time_step_;
      j["cells"] = get_current_cells();
      return j;
    }

    void
    set_json(const json &j) override {
      assert(j.contains("/input"_json_pointer));
      assert(j.contains("/timeStep"_json_pointer));
      assert(j.contains("/cells"_json_pointer));

      input_ = j["input"];
      initialize();

      time_step_ = j["timeStep"];
      auto &cells = get_current_cells();
      cells = j["cells"];
    }

    void
    validate_boundary_conditions() {}

    Input input_{};
    size_type nx_{};
    size_type ny_{};
    size_type nxm1_{};
    size_type nym1_{};
    Lexical<2> order_{};
    Lattice_Spacing lattice_spacing_{};
    array<Grid_Type, 2> grids_{};
    Time_Step time_step_{};
    Obstacle_List obstacles_{};
    Bounceback_Lists bounceback_lists_{};
    vector<function<void()>> boundary_functions_{};
  };

} // end of namespace lbm::D2Q9
