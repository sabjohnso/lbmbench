#pragma once

//
// ... LBM Bench header files
//
#include <lbmbench/details/Boundary_Condition.hpp>
#include <lbmbench/details/Obstacle.hpp>

namespace lbm::details {

  class Input final : public JSON_Convertible {

  public:
    Input() = default;
    Input(Lattice lattice,
          Initial_Conditions initial_conditions,
          Boundary_Conditions boundary_conditions,
          Obstacles obstacles,
          double viscosity)
        : lattice_{lattice}, initial_conditions_{initial_conditions},
          boundary_conditions_{boundary_conditions}, obstacles_{obstacles}, viscosity_{viscosity} {}

    size_type
    size() const {
      return lattice_.size();
    }

    friend bool
    operator==(const Input &, const Input &) {
      return true;
    }

  private:
    json
    get_json() const override {
      json j = json::object();
      j["D2Q9Input"] = json::object();
      j["D2Q9Input"]["viscosity"] = viscosity_;
      j["D2Q9Input"]["boundaryConditions"] = boundary_conditions_;
      j["D2Q9Input"]["obstacles"] = obstacles_;
      j["D2Q9Input"]["lattice"] = lattice_;
      return j;
    }

    void
    set_json(const json &j) override {
      viscosity_ = j["D2Q9Input"]["viscosity"];
      j["D2Q9Input"]["boundaryConditions"];
      boundary_conditions_.clear();
      std::transform(std::begin(j["D2Q9Input"]["boundaryConditions"]),
                     std::end(j["D2Q9Input"]["boundaryConditions"]),
                     back_inserter(boundary_conditions_),
                     [](const json bc) { return Boundary_Condition{bc}; });
      obstacles_.clear();
      std::transform(std::begin(j["D2Q9Input"]["obstacles"]),
                     std::end(j["D2Q9Input"]["obstacles"]),
                     back_inserter(obstacles_),
                     [](json obstacle) { return parse_json_expr(obstacle); });
      lattice_ = j["D2Q9Input"]["lattice"];
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

} // end of namespace lbm::details
