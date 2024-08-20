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
    using Nodes = MD_Array<Node_Type, 2>;
    using Obstacle_List = vector<size_type>;
    using Bounceback_Lists = Fixed_MD_Array<Dynamic_MD_Array<size_type>, Fixed_Lexical<3, 3>>;

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
        : nx_{input.nnodes(0)}
        , ny_{input.nnodes(1)}
        , nxm1_{nx_ - 1}
        , nym1_{ny_ - 1}
        , order_{Shape{nx_, ny_}}
        , lattice_spacing_(input.lattice_spacing())
        , nodes_{{Nodes{order_}, Nodes{order_}}} {

      initialize_nodes(input);
      initialize_bounceback_lists();
      initialize_boundary_functions(input);
    }

    void
    step() override {
      stream();
      collide();
      reset_boundaries();
      ++time_step_;
    }

    friend bool
    operator==(const State &state0, const State &state1) {
      return state0.time_step_ == state1.time_step_ &&
             state0.nodes_[state0.time_step_ % 2] == state1.nodes_[state1.time_step_ % 2];
    }

    friend bool
    operator!=(const State &state0, const State &state1) {
      return !(state0 == state1);
    }

  private:
    void
    initialize_nodes(Input input) {
      auto &nodes = nodes_[current_time_index()];
      for_each(std::begin(nodes),
               std::end(nodes),
               [&, this, index = size_type(0)](Node_Type &node) mutable {
                 const auto coord = node_coord(index);
                 node.init(input.density(coord), input.velocity(coord));
                 if (input.is_obstacle(coord)) {
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
    initialize_boundary_functions(Input input) {
      using enum Boundary_ID;
      boundary_functions_[Left] = make_left_boundary_function(input);
      boundary_functions_[Right] = make_right_boundary_function(input);
      boundary_functions_[Bottom] = make_left_boundary_function(input);
      boundary_functions_[Top] = make_left_boundary_function(input);
    }

    function<void()>
    make_wall_boundary(Boundary_ID boundary) {
      const auto internal_offsets = get_internal_offsets(boundary);
      return [=, this] {
        auto &nodes = get_next_nodes();
        for_each(nodes.begin(boundary), nodes.end(boundary), [=, this](auto &node) {
          const auto [i, j] = node.indices();
          for_each(std::cbegin(internal_offsets), std::cend(internal_offsets), [&](auto offsets) {
            const auto &[ioffset, joffset] = offsets;
            const auto &interior_node = nodes(i + ioffset, j + joffset);
            node(ioffset, joffset) = interior_node(-ioffset, joffset);
          });
        });
      };
    }

    auto
    get_internal_offsets(Boundary_ID boundary) {
      using enum Boundary_ID;
      switch (boundary) {
      case Left:
        return left_internal_offsets;
      case Right:
        return right_internal_offsets;
      case Bottom:
        return bottom_internal_offsets;
      case Top:
        return top_internal_offsets;
      case Back:
        unreachable_code(source_location::current());
      case Front:
        unreachable_code(source_location::current());
      }
      unreachable_code(source_location::current());
    }

    function<void()>
    make_symmetry_boundary(auto /*internal_offsets*/) {
      return [=, this] {};
    }

    function<void()>
    make_periodic_boundary() {}

    function<void()>
    make_inlet_boundary() {}

    function<void()>
    make_outlet_boundary() {}

    function<void()>
    make_pressure_drop_boundary() {}

    function<void()>
    make_left_boundary_function(Input input) {
      Boundary_Condition bc = input.boundary(Boundary_ID::Left);
      if (holds_alternative<Wall>(bc)) {

        // This could be general enough for all wall boundaries if
        // an iterator  and offsets were provided.
        // This does not handle the corners.

        return [this] {
          constexpr size_type i = 0;
          Nodes &nodes = get_next_nodes();
          for (size_type j = 1; j < nym1_; ++j) {
            for (auto ijoffset : left_internal_offsets) {
              const auto [ioffset, joffset] = ijoffset;
              nodes(i, j)(ioffset, joffset) = nodes(i + ioffset, j + joffset)(-ioffset, -joffset);
            }
          }
        };
      } else if (holds_alternative<Symmetry>(bc)) {
        return [] {};
      } else if (holds_alternative<Inlet>(bc)) {
        return [] {};
      } else if (holds_alternative<Outlet>(bc)) {
        return [] {};
      } else if (holds_alternative<Pressure_Drop>(bc)) {
        return [] {};
      } else {
        unreachable_code(source_location::current());
      }
    }

    function<void()>
    make_right_boundary_function(Input input) {
      Boundary_Condition bc = input.boundary(Boundary_ID::Right);
      if (holds_alternative<Wall>(bc)) {
        return [] {};
      } else if (holds_alternative<Symmetry>(bc)) {
        return [] {};
      } else if (holds_alternative<Inlet>(bc)) {
        return [] {};
      } else if (holds_alternative<Outlet>(bc)) {
        return [] {};
      } else if (holds_alternative<Pressure_Drop>(bc)) {
        return [] {};
      } else {
        unreachable_code(source_location::current());
      }
    }

    function<void()>
    make_bottom_boundary_function(Input input) {
      Boundary_Condition bc = input.boundary(Boundary_ID::Bottom);
      if (holds_alternative<Wall>(bc)) {
        return [] {};
      } else if (holds_alternative<Symmetry>(bc)) {
        return [] {};
      } else if (holds_alternative<Inlet>(bc)) {
        return [] {};
      } else if (holds_alternative<Outlet>(bc)) {
        return [] {};
      } else if (holds_alternative<Pressure_Drop>(bc)) {
        return [] {};
      } else {
        unreachable_code(source_location::current());
      }
    }

    function<void()>
    make_top_boundary_function(Input input) {
      Boundary_Condition bc = input.boundary(Boundary_ID::Top);
      if (holds_alternative<Wall>(bc)) {
        return [] {};
      } else if (holds_alternative<Symmetry>(bc)) {
        return [] {};
      } else if (holds_alternative<Inlet>(bc)) {
        return [] {};
      } else if (holds_alternative<Outlet>(bc)) {
        return [] {};
      } else if (holds_alternative<Pressure_Drop>(bc)) {
        return [] {};
      } else {
        unreachable_code(source_location::current());
      }
    }

    void
    reset_boundaries() {
      using enum Boundary_ID;
      boundary_functions_[Left]();
      boundary_functions_[Right]();
      boundary_functions_[Bottom]();
      boundary_functions_[Top]();
    }

    Nodes &
    get_current_nodes() {
      return nodes_[current_time_index()];
    }

    Nodes &
    get_next_nodes() {
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
      const auto &prev_nodes = nodes_[time_step_ % 2];
      auto &nodes = nodes_[(time_step_ + 1) % 2];
      for (size_type i = 1; i < nxm1_; ++i) {
        for (size_type j = 1; j < nym1_; ++i) {
          for_each(
              std::begin(neighbor_offsets), std::end(neighbor_offsets), [&](const auto &offsets) {
                const auto &[ioffset, joffset] = offsets;
                const size_type ineigh = i + ioffset;
                const size_type jneigh = j + joffset;
                nodes(i, j)(-ioffset, -joffset) = prev_nodes(ineigh, jneigh)(-ioffset, -joffset);
              });
        }
      }
    }

    void
    collide() {
      auto &nodes = nodes_[(time_step_ + 1) % 2];
      for_each(std::begin(nodes), std::end(nodes), [&](auto &node) { node.collide(); });
    }

    json
    get_json() const override {
      json j = json::object();
      j["timeStep"] = time_step_;
      j["nodes"] = nodes_[time_step_ % 2];
      return j;
    }

    void
    set_json(const json &j) override {
      time_step_ = j["timeStep"];
      nodes_[time_step_ % 2] = j["nodes"];
      nodes_[(time_step_ + 1) % 2] = j["nodes"];
    }

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
    unordered_map<Boundary_ID, function<void()>> boundary_functions_{};
  };

} // end of namespace lbm::D2Q9
