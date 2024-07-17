#pragma once

//
// ... LBM Bench header files
//
#include <lbm/D2Q9/Node.hpp>
#include <lbm/D2Q9/import.hpp>

namespace lbm::D2Q9 {

  template <class T>
  class State : public JSON_Convertible {
  public:
    using Lattice_Spacing = T;
    using Time_Step = size_type;
    using Nodes = Array<Node<T>, 2>;
    using Obstacle_List = vector<array<size_type, 2>>;
    using Bounceback_Lists = Fixed_Array<vector<array<size_type, 2>>, Fixed_Lexical<3, 3>>;
    State() = default;

    State(Input input)
        : nx_{input.nnodes(0)}
        , ny_{input.nnodes(1)} // , order_{Shape{nx_, ny_}}
                               // , lattice_spacing_{input.lattice_spacing()}
                               // , nodes_{{Nodes{order_}, Nodes{order_}}}
    {

      // initialize_nodes(input);
      // locate_obstacles();
      // initialize_bounceback_lists();
    }

    void
    step() {
      // stream();
      // bounceback();
      // collide();
      // ++time_step_;
    }

    friend bool
    operator==(const State &state0, const State &state1) {
      return state0.time_step_ == state1.time_step_;
      //&&
      //        state0.nodes_[state0.time_step_ % 2] == state1.nodes_[state1.time_step_ % 2];
    }

    friend bool
    operator!=(const State &state0, const State &state1) {
      return !(state0 == state1);
    }

  private:
    void
    initialize_nodes(Input /* input */) {
      // T lattice_spacing = input.lattice_spacing();
      // Nodes &nodes = nodes_[current_time_index()];
      // Nodes &next_nodes = nodes_[next_time_index()];
      // for_each(
      //     std::begin(nodes), std::end(nodes), [&, this, index = size_type(0)](auto &node) mutable
      //     {
      //       const auto [i, j] = order_.array_index(index);
      //     });
      // for (size_type i = 0; i < nx_; ++i) {
      //   for (size_type j = 0; j < ny_; ++j) {
      //     Euclidean coord{lattice_spacing * i, lattice_spacing * j};
      //     bool obstacle = input.is_obstacle(coord);
      //     nodes[i, j].init(input.density(coord), input.velocity(coord),
      //     input.is_obstacle(coord)); if (obstacle) {
      //       obstacles_.push_back(array{i, j});
      //     }
      //   }
      // }
    }

    // Euclidean
    // get_coord(size_type storage_index) {
    //   const auto [i, j] = order_.array_index(storage_index);
    //   return {lattice_spacing_ * i, lattice_spacing_ * j};
    // }

    void
    reset_boundaries() {}

    void
    bounceback() {};

    size_type
    current_time_index() const {
      return time_step_ % 2;
    }

    size_type
    next_time_index() const {
      return (time_step_ + 1) % 2;
    }

    void
    locate_obstacles() {
      // const Nodes &nodes = nodes_[0];
      // for (size_type i = 0; i < nx_; ++i) {
      //   for (size_type j = 0; j < ny_; ++j) {
      //     if (nodes[i, j].is_obstacle()) {
      //       obstacles_.push_back(array{i, j});
      //     }
      //   }
      // }
    }

    void
    initialize_bounceback_lists() {
      // Nodes &nodes = nodes_[0];
      // size_type nx = nodes.size(0);
      // size_type ny = nodes.size(1);
      // for_each(std::begin(obstacles_), std::end(obstacles_), [&, this](const auto &indices) {
      //   const auto &[i, j] = indices;
      //   for_each(std::begin(neigbors), std::end(neighbors), [&, this](const auto &offset) {
      //     const auto &[di, dj] = offset;
      //     size_type ineighbor = i + di;
      //     size_type jneighbor = j + dj;

      //     if (!nodes[ineighbor, jneighbor].is_obstacle()) {
      //       bounceback_list[di + 1, dj + 1].push_back(array{ineigh, jneigh})
      //     }
      //   });
      // });
    }

    // bool
    // in_interior(size_type i, size_type j) const {

    // }

    void
    stream() {}

    void
    collide() {
      // Nodes &nodes = nodes_[(time_step_ + 1) % 2];
      // size_type nx = nodes.size(0);
      // size_type ny = nodes.size(1);
      // for (size_type i = 0; i < nx; ++i) {
      //   for (size_type j = 0; j < ny; ++j) {
      //     nodes[i, j].collide();
      //   }
      // }
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

    size_type nx_;
    size_type ny_;
    Lexical<2> order_;
    Lattice_Spacing lattice_spacing_{};
    array<Nodes, 2> nodes_{};
    Time_Step time_step_{};
    // Obstacle_List obstacles_{};
    // // Bounceback_Lists bounceback_lists{};
  };

} // end of namespace lbm::D2Q9
