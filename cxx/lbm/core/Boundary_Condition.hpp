#pragma once

//
// ... LBM Bench header files
//
#include <lbm/core/Boundary_ID.hpp>
#include <lbm/core/import.hpp>

namespace lbm::core {

  class Wall final : public JSON_Convertible {
  public:
    Wall() = default;
    Wall(Boundary_ID boundary);

    friend bool
    operator==(const Wall &wall1, const Wall &wall2);

    Boundary_ID
    boundary() const;

  private:
    json
    get_json() const override;

    void
    set_json(const json &j) override;

    Boundary_ID boundary_{};
  };

  class Symmetry final : public JSON_Convertible {
  public:
    Symmetry() = default;
    Symmetry(Boundary_ID boundary);

    friend bool
    operator==(const Symmetry &symmetry1, const Symmetry &symmetry2);

    friend bool
    operator!=(const Symmetry &symmetry1, const Symmetry &symmetry2);

    Boundary_ID
    boundary() const;

  private:
    json
    get_json() const override;

    void
    set_json(const json &j) override;

    Boundary_ID boundary_;
  };

  class Inlet final : public JSON_Convertible {
  public:
    Inlet() = default;
    Inlet(Boundary_ID boundary, double density, double speed);

    friend bool
    operator==(const Inlet &inlet1, const Inlet &inlet2);

    friend bool
    operator!=(const Inlet &inlet1, const Inlet &inlet2);

    Boundary_ID
    boundary() const;

    double
    density() const;

    double
    speed() const;

  private:
    json
    get_json() const override;

    void
    set_json(const json &j) override;

    Boundary_ID boundary_{};
    double density_{};
    double speed_{};
  };

  class Outlet final : public JSON_Convertible {
  public:
    Outlet() = default;
    Outlet(Boundary_ID boundary, double density, double speed);

    friend bool
    operator==(const Outlet &outlet1, const Outlet &outlet2);

    friend bool
    operator!=(const Outlet &outlet1, const Outlet &outlet2);

    Boundary_ID
    boundary() const;

    double
    density() const;

    double
    speed() const;

  private:
    json
    get_json() const override;

    void
    set_json(const json &j) override;

    Boundary_ID boundary_{};
    double density_{};
    double speed_{};
  };

  class Pressure_Drop final : public JSON_Convertible {
  public:
    Pressure_Drop() = default;
    Pressure_Drop(Boundary_ID boundary, double value);

    friend bool
    operator==(const Pressure_Drop &pressure_drop1, const Pressure_Drop &pressure_drop2);

    friend bool
    operator!=(const Pressure_Drop &pressure_drop1, const Pressure_Drop &pressure_drop2);

    Boundary_ID
    boundary() const;

  private:
    json
    get_json() const override;

    void
    set_json(const json &j) override;

    Boundary_ID boundary_{};
    double value_{};
  };

  class Boundary_Condition : public variant<Wall, Symmetry, Inlet, Outlet, Pressure_Drop> {
  public:
    using Base = variant<Wall, Symmetry, Inlet, Outlet, Pressure_Drop>;
    using Base::Base;

    Boundary_Condition() = default;

    Boundary_ID
    boundary() const;

    friend void
    to_json(json &j, const Boundary_Condition &boundary_condition);

    friend void
    from_json(const json &j, Boundary_Condition &boundary_condition);

    friend ostream &
    operator<<(ostream &os, const Boundary_Condition &boundary_condition);

    friend istream &
    operator>>(istream &is, Boundary_Condition &boundary_condition);

    friend bool
    operator==(const Boundary_Condition &bc1, const Boundary_Condition &bc2);
  };

  class Boundary_Conditions
      : public vector<Boundary_Condition>
      , public JSON_Convertible {
  public:
    using Base = vector<Boundary_Condition>;
    using Base::Base;

  private:
    json
    get_json() const override;

    void
    set_json(const json &j) override;
  };

} // end of namespace lbm::core
