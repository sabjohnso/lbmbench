#pragma once

//
// ... LBM Bench header files
//
#include <lbm/core/Boundary_Condition.hpp>
#include <lbm/core/Initial_Conditions.hpp>
#include <lbm/core/Lattice.hpp>
#include <lbm/core/Obstacle.hpp>

namespace lbm::core {

  class Input final : public JSON_Convertible {

  public:
    Input() = default;
    Input(Lattice lattice,
          Initial_Conditions initial_conditions,
          Boundary_Conditions boundary_conditions,
          Obstacles obstacles,
          double viscosity)
        : lattice_{lattice}
        , initial_conditions_{initial_conditions}
        , boundary_conditions_{boundary_conditions}
        , obstacles_{obstacles}
        , viscosity_{viscosity} {}

    size_type
    ndims() const {
      return lattice_.ndims();
    }

    size_type
    nnodes() const {
      return lattice_.nnodes();
    }

    size_type
    nnodes(size_type idim) const {
      return lattice_.nnodes(idim);
    }

    double
    density(Euclidean coord) const {
      return initial_conditions_.density(coord);
    }

    Euclidean
    velocity(Euclidean coord) const {
      return initial_conditions_.velocity(coord);
    }

    bool
    is_obstacle(Euclidean coord) const {
      return obstacles_.contains(coord);
    }

    double
    lattice_spacing() {
      return lattice_.lattice_spacing();
    }

    friend bool
    operator==(const Input &inp0, const Input &inp1) {
      // clang-format off
      return inp0.lattice_        == inp1.lattice_ &&
        inp0.initial_conditions_  == inp1.initial_conditions_ &&
        inp0.boundary_conditions_ == inp1.boundary_conditions_ &&
        inp0.obstacles_           == inp1.obstacles_ &&
        inp0.viscosity_           == inp1.viscosity_;
      // clang-format on
    }

  private:
    json
    get_json() const override {
      json j = json::object();
      j["lattice"] = lattice_;
      j["initialConditions"] = initial_conditions_;
      j["boundaryConditions"] = boundary_conditions_;
      j["obstacles"] = obstacles_;
      j["viscosity"] = viscosity_;
      return j;
    }

    void
    set_json(const json &j) override {
      lattice_ = j["lattice"];
      initial_conditions_ = j["initialConditions"];
      boundary_conditions_ = j["boundaryConditions"];
      obstacles_ = j["obstacles"];
      viscosity_ = j["viscosity"];
    }

    Lattice lattice_{};
    Initial_Conditions initial_conditions_{};
    Boundary_Conditions boundary_conditions_{};
    Obstacles obstacles_{};
    double viscosity_{};
  };

  // template <class T>
  // class D2Q9_State {
  //   using Input = D2Q9_Input;
  //   using Nodes = Array<Node<T>, 2>;
  //   using Order = Nodes::Order;

  // public:
  // private:
  //   void
  //   setup_nodes() {}

  //   Input input_;
  //   Nodes nodes_;
  // };

} // end of namespace lbm::core
