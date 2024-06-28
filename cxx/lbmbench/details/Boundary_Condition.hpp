#pragma once

//
// ... LBM Bench header files
//
#include <lbmbench/details/Boundary_ID.hpp>
#include <lbmbench/details/import.hpp>

namespace lbm::details {

  template <size_type N>
  class Wall {
  public:
    constexpr Wall() = default;
    constexpr Wall(Boundary_ID<N> boundary) : boundary_{boundary} {}

    friend void
    to_json(json &j, const Wall &wall) {
      j = json::object();
      j["wall"] = json::object();
      j["wall"].update(wall.boundary_);
    }

    friend void
    from_json(const json &j, Wall &wall) {
      wall.boundary_ = j["wall"];
    }

    friend ostream &
    operator<<(ostream &os, const Wall &wall) {
      return os << json(wall);
    }

    friend istream &
    operator>>(istream &is, Wall &wall) {
      wall = json::parse(is);
      return is;
    }

    friend bool
    operator<=>(const Wall &wall1, const Wall &wall2) = default;

  private:
    Boundary_ID<N> boundary_{};
  };

  template <size_type N>
  Wall(Boundary_ID<N>) -> Wall<N>;

  template <size_type N>
  class Symmetry {
  public:
    constexpr Symmetry() = default;
    constexpr Symmetry(Boundary_ID<N> boundary) : boundary_{boundary} {}

    friend void
    to_json(json &j, const Symmetry &symmetry) {
      j = json::object();
      j["symmetry"] = json::object();
      j["symmetry"].update(symmetry.boundary_);
    }

    friend void
    from_json(const json &j, Symmetry &symmetry) {
      symmetry.boundary_ = j["symmetry"];
    }

    friend ostream &
    operator<<(ostream &os, const Symmetry &symmetry) {
      return os << json(symmetry);
    }

    friend istream &
    operator>>(istream &is, Symmetry &symmetry) {
      symmetry = json::parse(is);
      return is;
    }

    friend bool
    operator<=>(const Symmetry &symmetry1, const Symmetry &symmetry2) = default;

  private:
    Boundary_ID<N> boundary_;
  };

  template <size_type N>
  Symmetry(Boundary_ID<N>) -> Symmetry<N>;

  template <size_type N>
  class Inlet {
  public:
    constexpr Inlet() = default;
    constexpr Inlet(Boundary_ID<N> boundary, double inlet_speed)
        : boundary_{boundary}, inlet_speed_{inlet_speed} {}

    friend void
    to_json(json &j, const Inlet inlet) {
      j = json::object();
      j["inlet"] = json::object();
      j["inlet"].update(inlet.boundary_);
      j["inlet"]["inletSpeed"] = inlet.inlet_speed_;
    }

    friend void
    from_json(const json &j, Inlet &inlet) {
      inlet.boundary_ = j["inlet"];
      inlet.inlet_speed_ = j["inlet"]["inletSpeed"];
    }

    friend ostream &
    operator<<(ostream &os, const Inlet &inlet) {
      return os << json(inlet);
    }

    friend istream &
    operator>>(istream &is, Inlet &inlet) {
      inlet = json::parse(is);
      return is;
    }

    friend bool
    operator<=>(const Inlet &Inlet1, const Inlet &Inlet2) = default;

  private:
    Boundary_ID<N> boundary_{};
    double inlet_speed_{};
  };

  template <size_type N>
  Inlet(Boundary_ID<N>, double) -> Inlet<N>;

  static_assert(is_default_constructible_v<Inlet<2>>);
  static_assert(is_default_constructible_v<Inlet<3>>);

  template <size_type N>
  class Pressure_Drop {
  public:
    constexpr Pressure_Drop() = default;
    constexpr Pressure_Drop(Boundary_ID<N> boundary, double value)
        : boundary_(boundary), value_(value) {}

    friend void
    to_json(json &j, const Pressure_Drop &pressure_drop) {
      j = json::object();
      j["pressureDrop"] = json::object();
      j["pressureDrop"].update(pressure_drop.boundary_);
      j["pressureDrop"]["value"] = pressure_drop.value_;
    }

    friend void
    from_json(const json &j, Pressure_Drop &pressure_drop) {
      pressure_drop.boundary_ = j["pressureDrop"];
      pressure_drop.value_ = j["pressureDrop"]["value"];
    }

    friend ostream &
    operator<<(ostream &os, const Pressure_Drop &pressure_drop) {
      return os << json(pressure_drop);
    }

    friend istream &
    operator<<(istream &is, Pressure_Drop &pressure_drop) {
      pressure_drop = json::parse(is);
      return is;
    }

    friend bool
    operator<=>(const Pressure_Drop &pressure_drop1, const Pressure_Drop &pressure_drop2) = default;

  private:
    Boundary_ID<N> boundary_{};
    double value_{};
  };

  template <size_type N>
  Pressure_Drop(Boundary_ID<N>, double) -> Pressure_Drop<N>;

  template <size_type N>
  class Boundary_Condition : public variant<Wall<N>, Symmetry<N>, Inlet<N>, Pressure_Drop<N>> {
  public:
    using Base = variant<Wall<N>, Symmetry<N>, Inlet<N>, Pressure_Drop<N>>;
    using Base::Base;

    Boundary_Condition() = default;

    friend void
    to_json(json &j, const Boundary_Condition &boundary_condition) {
      visit([&](const auto &boundary_condition) { j = boundary_condition; }, boundary_condition);
    }

    friend void
    from_json(const json &j, Boundary_Condition &boundary_condition) {
      if (j.contains("wall")) {
        boundary_condition = Wall<N>(j);
      } else if (j.contains("symmetry")) {
        boundary_condition = Symmetry<N>(j);
      } else if (j.contains("inlet")) {
        boundary_condition = Inlet<N>(j);
      } else if (j.contains("pressureDrop")) {
        boundary_condition = Pressure_Drop<N>(j);
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

  template <size_type N>
  Boundary_Condition(Wall<N>) -> Boundary_Condition<N>;

  template <size_type N>
  Boundary_Condition(Symmetry<N>) -> Boundary_Condition<N>;

  template <size_type N>
  Boundary_Condition(Inlet<N>) -> Boundary_Condition<N>;

  template <size_type N>
  Boundary_Condition(Pressure_Drop<N>) -> Boundary_Condition<N>;

} // end of namespace lbm::details
