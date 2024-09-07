#pragma once

//
// ... LBM Bench header files
//
#include <lbm/core/Boundary_Condition.hpp>
#include <lbm/core/Float_Type.hpp>
#include <lbm/core/Initial_Conditions.hpp>
#include <lbm/core/Kernel.hpp>
#include <lbm/core/Lattice.hpp>
#include <lbm/core/Obstacle.hpp>

namespace lbm::core {

  class Input final : public JSON_Convertible {

  public:
    Input() = default;
    Input(Kernel kernel,
          Float_Type float_type,
          double time_scale,
          size_type num_steps,
          Lattice lattice,
          Initial_Conditions initial_conditions,
          Boundary_Conditions boundary_conditions,
          Obstacles obstacles,
          double viscosity);

    Kernel
    kernel() const;

    Float_Type
    float_type() const;

    double
    time_scale() const;

    size_type
    num_steps() const;

    size_type
    ndims() const;

    size_type
    nnodes() const;

    size_type
    nnodes(size_type idim) const;

    double
    density(Euclidean coord) const;

    Euclidean
    velocity(Euclidean coord) const;

    bool
    is_obstacle(Euclidean coord) const;

    double
    lattice_spacing() const;

    optional<Boundary_Condition>
    boundary(Boundary_ID id) const;

    friend bool
    operator==(const Input &inp0, const Input &inp1);

  private:
    json
    get_json() const override;

    void
    set_json(const json &j) override;

    Kernel kernel_{};
    Float_Type float_type_{};
    double time_scale_{};
    size_type num_steps_{};
    Lattice lattice_{};
    Initial_Conditions initial_conditions_{};
    Boundary_Conditions boundary_conditions_{};
    Obstacles obstacles_{};
    double viscosity_{};
  }; // namespace lbm::core

} // end of namespace lbm::core
