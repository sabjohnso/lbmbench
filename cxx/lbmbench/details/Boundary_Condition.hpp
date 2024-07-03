#pragma once

//
// ... LBM Bench header files
//
#include <lbmbench/details/Boundary_ID.hpp>
#include <lbmbench/details/import.hpp>

namespace lbm::details {

  class Wall final : public JSON_Convertible {
  public:
    constexpr Wall() = default;
    constexpr Wall(Boundary_ID boundary) : boundary_{boundary} {}

    friend bool
    operator==(const Wall &wall1, const Wall &wall2) {
      return wall1.boundary_ == wall2.boundary_;
    }

  private:
    json
    get_json() const override {
      json j = json::object();
      j["wall"] = json::object();
      j["wall"]["boundary"] = boundary_;
      return j;
    }

    void
    set_json(const json &j) override {
      boundary_ = j["wall"]["boundary"];
    }

    Boundary_ID boundary_{};
  };

  class Symmetry final : public JSON_Convertible {
  public:
    constexpr Symmetry() = default;
    constexpr Symmetry(Boundary_ID boundary) : boundary_{boundary} {}

    friend bool
    operator==(const Symmetry &symmetry1, const Symmetry &symmetry2) {
      return symmetry1.boundary_ == symmetry2.boundary_;
    }

    friend bool
    operator!=(const Symmetry &symmetry1, const Symmetry &symmetry2) {
      return !(symmetry1 == symmetry2);
    }

  private:
    json
    get_json() const override {
      json j = json::object();
      j["symmetry"] = boundary_;
      return j;
    }

    void
    set_json(const json &j) override {
      boundary_ = j["symmetry"];
    }

    Boundary_ID boundary_;
  };

  class Inlet final : public JSON_Convertible {
  public:
    constexpr Inlet() = default;
    constexpr Inlet(Boundary_ID boundary, double inlet_speed)
        : boundary_{boundary}, inlet_speed_{inlet_speed} {}

    friend bool
    operator==(const Inlet &inlet1, const Inlet &inlet2) {
      return inlet1.boundary_ == inlet2.boundary_ && inlet1.inlet_speed_ == inlet2.inlet_speed_;
    }

    friend bool
    operator!=(const Inlet &inlet1, const Inlet &inlet2) {
      return !(inlet1 == inlet2);
    }

  private:
    json
    get_json() const override {
      json j = json::object();
      j["inlet"]["boundary"] = boundary_;
      j["inlet"]["inletSpeed"] = inlet_speed_;
      return j;
    }

    void
    set_json(const json &j) override {
      boundary_ = j["inlet"]["boundary"];
      inlet_speed_ = j["inlet"]["inletSpeed"];
    }

    Boundary_ID boundary_{};
    double inlet_speed_{};
  };

  class Outlet final : public JSON_Convertible {
  public:
    constexpr Outlet() = default;
    constexpr Outlet(Boundary_ID boundary, double outlet_speed)
        : boundary_{boundary}, outlet_speed_{outlet_speed} {}

    friend bool
    operator==(const Outlet &outlet1, const Outlet &outlet2) {
      return outlet1.boundary_ == outlet2.boundary_ &&
             outlet1.outlet_speed_ == outlet2.outlet_speed_;
    }
    friend bool
    operator!=(const Outlet &outlet1, const Outlet &outlet2) {
      return !(outlet1 == outlet2);
    }

  private:
    json
    get_json() const override {
      json j = json::object();
      j["outlet"] = json::object();
      j["outlet"]["boundary"] = boundary_;
      j["outlet"]["outletSpeed"] = outlet_speed_;
      return j;
    }

    void
    set_json(const json &j) override {
      boundary_ = j["outlet"]["boundary"];
      outlet_speed_ = j["outlet"]["outletSpeed"];
    }

    Boundary_ID boundary_{};
    double outlet_speed_{};
  };

  class Pressure_Drop final : public JSON_Convertible {
  public:
    constexpr Pressure_Drop() = default;
    constexpr Pressure_Drop(Boundary_ID boundary, double value)
        : boundary_(boundary), value_(value) {}

    friend bool
    operator==(const Pressure_Drop &pressure_drop1, const Pressure_Drop &pressure_drop2) {
      return pressure_drop1.boundary_ == pressure_drop2.boundary_ &&
             pressure_drop1.value_ == pressure_drop2.value_;
    }

    friend bool
    operator!=(const Pressure_Drop &pressure_drop1, const Pressure_Drop &pressure_drop2) {
      return !(pressure_drop1 == pressure_drop2);
    }

  private:
    json
    get_json() const override {
      json j = json::object();
      j["pressureDrop"] = json::object();
      j["pressureDrop"]["boundary"] = boundary_;
      j["pressureDrop"]["value"] = value_;
      return j;
    }

    void
    set_json(const json &j) override {
      boundary_ = j["pressureDrop"]["boundary"];
      value_ = j["pressureDrop"]["value"];
    }

    Boundary_ID boundary_{};
    double value_{};
  };

  class Boundary_Condition : public variant<Wall, Symmetry, Inlet, Outlet, Pressure_Drop> {
  public:
    using Base = variant<Wall, Symmetry, Inlet, Outlet, Pressure_Drop>;
    using Base::Base;

    Boundary_Condition() = default;

    friend void
    to_json(json &j, const Boundary_Condition &boundary_condition) {
      visit([&](const auto &boundary_condition) { j = boundary_condition; }, boundary_condition);
    }

    friend void
    from_json(const json &j, Boundary_Condition &boundary_condition) {
      if (j.contains("wall")) {
        boundary_condition = Wall(j);
      } else if (j.contains("symmetry")) {
        boundary_condition = Symmetry(j);
      } else if (j.contains("inlet")) {
        boundary_condition = Inlet(j);
      } else if (j.contains("outlet")) {
        boundary_condition = Outlet(j);
      } else if (j.contains("pressureDrop")) {
        boundary_condition = Pressure_Drop(j);
      }
    }

    friend ostream &
    operator<<(ostream &os, const Boundary_Condition &boundary_condition) {
      return os << json(boundary_condition);
    }

    friend istream &
    operator>>(istream &is, Boundary_Condition &boundary_condition) {
      boundary_condition = json::parse(is);
      return is;
    }

    friend bool
    operator==(const Boundary_Condition &bc1, const Boundary_Condition &bc2) {
      return visit(
          []<class U, class V>(const U &bc1, const V &bc2) {
            if constexpr (same_as<U, V>) {
              return bc1 == bc2;
            } else {
              return false;
            }
          },
          bc1,
          bc2);
    }
  };

} // end of namespace lbm::details
