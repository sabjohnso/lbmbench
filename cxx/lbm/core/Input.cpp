#include <lbm/core/Input.hpp>

namespace lbm::core {

  Input::Input(Kernel kernel,
               Float_Type float_type,
               double time_scale,
               size_type num_steps,
               Lattice lattice,
               Initial_Conditions initial_conditions,
               Boundary_Conditions boundary_conditions,
               Obstacles obstacles,
               double viscosity)
      : kernel_{kernel}
      , float_type_{float_type}
      , time_scale_{time_scale}
      , num_steps_{num_steps}
      , lattice_{lattice}
      , initial_conditions_{initial_conditions}
      , boundary_conditions_{boundary_conditions}
      , obstacles_{obstacles}
      , viscosity_{viscosity} {}

  Kernel
  Input::kernel() const {
    return kernel_;
  }

  Float_Type
  Input::float_type() const {
    return float_type_;
  }

  double
  Input::time_scale() const {
    return time_scale_;
  }

  size_type
  Input::num_steps() const {
    return num_steps_;
  }

  size_type
  Input::ndims() const {
    return lattice_.ndims();
  }

  size_type
  Input::nnodes() const {
    return lattice_.nnodes();
  }

  size_type
  Input::nnodes(size_type idim) const {
    return lattice_.nnodes(idim);
  }

  double
  Input::density(Euclidean coord) const {
    return initial_conditions_.density(coord);
  }

  Euclidean
  Input::velocity(Euclidean coord) const {
    return initial_conditions_.velocity(coord);
  }

  bool
  Input::is_obstacle(Euclidean coord) const {
    return obstacles_.contains(coord);
  }

  double
  Input::lattice_spacing() const {
    return lattice_.lattice_spacing();
  }

  optional<Boundary_Condition>
  Input::boundary(Boundary_ID id) const {
    optional<Boundary_Condition> bc{};
    for (auto input_bc : boundary_conditions_) {
      if (input_bc.boundary() == id) {
        bc = input_bc;
        break;
      }
    }
    return bc;
  }

  bool
  operator==(const Input &inp0, const Input &inp1) {
    // clang-format off
      return inp0.lattice_        == inp1.lattice_ &&
        inp0.initial_conditions_  == inp1.initial_conditions_ &&
        inp0.boundary_conditions_ == inp1.boundary_conditions_ &&
        inp0.obstacles_           == inp1.obstacles_ &&
        inp0.viscosity_           == inp1.viscosity_;
    // clang-format on
  }

  json
  Input::get_json() const {
    json j = json::object();
    j["kernel"] = kernel_;
    j["floatType"] = float_type_;
    j["timeScale"] = time_scale_;
    j["numSteps"] = num_steps_;
    j["lattice"] = lattice_;
    j["initialConditions"] = initial_conditions_;
    j["boundaryConditions"] = boundary_conditions_;
    j["obstacles"] = obstacles_;
    j["viscosity"] = viscosity_;
    return j;
  }

  void
  Input::set_json(const json &j) {
    kernel_ = j["kernel"];
    float_type_ = j["floatType"];
    time_scale_ = j["timeScale"];
    num_steps_ = j["numSteps"];
    lattice_ = j["lattice"];
    initial_conditions_ = j["initialConditions"];
    boundary_conditions_ = j["boundaryConditions"];
    obstacles_ = j["obstacles"];
    viscosity_ = j["viscosity"];
  }

} // end of namespace lbm::core
