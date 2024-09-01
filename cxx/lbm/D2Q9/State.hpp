#pragma once

//
// ... LBM Bench header files
//
#include <lbm/D2Q9/Node.hpp>
#include <lbm/D2Q9/import.hpp>

namespace lbm::D2Q9 {

  template <class T>
  class State final : public I_State {
  public:
    using Lattice_Spacing = T;
    using Time_Step = size_type;
    using Node_Type = Node<T>;
    using Nodes = Array2<Node_Type>;
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
      initialize_nodes();
      initialize_bounceback_lists();
      initialize_boundary_functions();
    }

    void
    initialize() {
      nx_ = input_.nnodes(0);
      ny_ = input_.nnodes(1);
      nxm1_ = nx_ - 1;
      nym1_ = ny_ - 1;
      order_ = Shape{nx_, ny_};
      lattice_spacing_ = input_.lattice_spacing();
      nodes_ = {{Nodes{order_}, Nodes{order_}}};
    }

    void
    step() override {
      stream();
      collide();
      set_boundaries();
      ++time_step_;
    }

    friend bool
    operator==(const State &state0, const State &state1) {
      return json(state0) == json(state1);
      return state0.time_step_ == state1.time_step_ &&
             state0.get_current_nodes() == state1.get_current_nodes();
    }

    friend bool
    operator!=(const State &state0, const State &state1) {
      return !(state0 == state1);
    }

  private:
    void
    initialize_nodes() {
      auto &nodes = nodes_[current_time_index()];
      for_each(std::begin(nodes),
               std::end(nodes),
               [&, this, index = size_type(0)](Node_Type &node) mutable {
                 const auto coord = node_coord(index);
                 node.init(input_.density(coord), input_.velocity(coord));
                 if (input_.is_obstacle(coord)) {
                   obstacles_.push_back(index);
                 }
                 ++index;
               });
    }

    Euclidean
    node_coord(const size_type index) {
      const auto [i, j] = order_.array_index(index);
      return {i * lattice_spacing_, j * lattice_spacing_};
    }

    void
    initialize_bounceback_lists() {
      for_each(std::cbegin(obstacles_), std::cend(obstacles_), [this](size_type index) {
        return initialize_bounceback_list_obstacle(index);
      });
    }

    void
    initialize_bounceback_list_obstacle(size_type index) {
      const auto &nodes = nodes_[0];
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
            if (interior_indices(i, j) && !nodes(i, j).is_obstacle()) {
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
    initialize_boundary_functions() {
      using enum Boundary_ID;
    }

    // The wall boundary node should have particle densities that correspond
    // to retro-reflection on the boundary.
    template <Boundary_Tag2 Boundary>
    function<void()>
    make_wall_boundary(Boundary) {
      const auto internal_offsets = get_internal_offsets(Boundary{});
      return [=, this] {
        auto &nodes = get_next_nodes();
        forall(nodes.begin(Boundary{}), nodes.end(Boundary{}), [=, this](auto node) {
          for_each(std::cbegin(internal_offsets), std::cend(internal_offsets), [&](auto offsets) {
            const auto &[i, j] = offsets;
            node(0, 0)(i, j) = node(i, j)(-i, -j);
          });
        });
      };
    }

    // The symmetry boundary node should have particle densities that match the
    // interior node for the mirrored velocity classes. The boundary condition is
    // set one-to-one between the boundary and interior nodes.
    //
    // Like specular reflection on the boundary.
    template <Boundary_Tag2 Boundary>
    function<void()>
    make_symmetry_boundary(Boundary) {
      const auto internal_offsets = get_internal_offsets(Boundary{});
      return [=, this] {
        auto nodes = get_next_nodes();
        forall(nodes.begin(Boundary{}), nodes.end(Boundary{}), [this](auto node) {
          if constexpr (same_as<Boundary, Left>) {
            for (size_type i = -1; i < 2; ++i) {
              for (size_type j = -1; j < 2; ++j) {
                node(0, 0)(i, j) = node(1, 0)(-i, j);
              }
            }
          } else if constexpr (same_as<Boundary, Right>) {
            for (size_type i = -1; i < 2; ++i) {
              for (size_type j = -1; j < 2; ++j) {
                node(0, 0)(i, j) = node(-1, 0)(-i, j);
              }
            }
          } else if constexpr (same_as<Boundary, Bottom>) {
            for (size_type i = -1; i < 2; ++i) {
              for (size_type j = -1; j < 2; ++j) {
                node(0, 0)(i, j) = node(-1, 0)(-i, j);
              }
            }
          } else if constexpr (same_as<Boundary, Top>) {
            for (size_type i = -1; i < 2; ++i) {
              for (size_type j = -1; j < 2; ++j) {
                node(0, 0)(i, j) = node(-1, 0)(-i, j);
              }
            }
          }
        });
      };
    }

    // For periodic boundaries, the node values from the other side of the
    // domain must be copied.
    template <Boundary_Tag2 Boundary>
    function<void()>
    make_periodic_boundary(Boundary) {
      return [this] {
        auto &nodes = get_next_nodes();

        if constexpr (same_as<Boundary, Left> || same_as<Boundary, Right>) {
          forall(
              nodes.begin(left), nodes.end(left), nodes.begin(right), [](auto node1, auto node2) {
                node1(0, 0) = node2(-1, 0);
                node2(0, 0) = node1(1, 0);
              });

        } else if constexpr (same_as<Boundary, Bottom> || same_as<Boundary, Top>) {
          forall(
              nodes.begin(bottom), nodes.end(bottom), nodes.begin(top), [](auto node1, auto node2) {
                node1(0, 0) = node2(-1, 0);
                node2(0, 0) = node1(1, 0);
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
    set_boundaries() {
      for_each(std::begin(boundary_functions_),
               std::end(boundary_functions_),
               [](auto &boundary_function) { boundary_function(); });
    }

    Nodes &
    get_current_nodes() {
      return nodes_[current_time_index()];
    }

    const Nodes &
    get_current_nodes() const {
      return nodes_[current_time_index()];
    }

    Nodes &
    get_next_nodes() {
      return nodes_[next_time_index()];
    }

    const Nodes &
    get_next_nodes() const {
      return nodes_[next_time_index()];
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
      const auto &current_nodes = get_current_nodes();
      auto &next_nodes = get_next_nodes();
      forall(current_nodes.begin(interior),
             current_nodes.end(interior),
             next_nodes.begin(interior),
             [](auto current_node, auto next_node) {
               for_each(classes.begin(), classes.end(), [&](auto offsets) {
                 const auto &[i, j] = offsets;
                 next_node(0, 0)(i, j) = current_node(-i, -j)(i, j);
               });
             });
    }

    void
    collide() {
      auto &nodes = nodes_[(time_step_ + 1) % 2];
      for_each(std::begin(nodes), std::end(nodes), [&](auto &node) { node.collide(); });
    }

    json
    get_json() const override {
      json j = json::object();
      j["input"] = input_;
      j["timeStep"] = time_step_;
      j["nodes"] = get_current_nodes();
      return j;
    }

    void
    set_json(const json &j) override {
      assert(j.contains("/input"_json_pointer));
      assert(j.contains("/timeStep"_json_pointer));
      assert(j.contains("/nodes"_json_pointer));

      input_ = j["input"];
      initialize();

      time_step_ = j["timeStep"];
      auto &nodes = get_current_nodes();
      nodes = j["nodes"];
    }
    Input input_{};
    size_type nx_{};
    size_type ny_{};
    size_type nxm1_{};
    size_type nym1_{};
    Lexical<2> order_{};
    Lattice_Spacing lattice_spacing_{};
    array<Nodes, 2> nodes_{};
    Time_Step time_step_{};
    Obstacle_List obstacles_{};
    Bounceback_Lists bounceback_lists_{};
    vector<function<void()>> boundary_functions_{};
  };

} // end of namespace lbm::D2Q9
