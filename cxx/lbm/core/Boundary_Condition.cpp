#include <lbm/core/Boundary_Condition.hpp>

namespace lbm::core {

  //
  // ... Boundary_Conditions
  //
  json
  Boundary_Conditions::get_json() const {
    json j = static_cast<const Base &>(*this);
    return j;
  }

  void
  Boundary_Conditions::set_json(const json &j) {
    Base::clear();
    transform(std::begin(j),
              std::end(j),
              back_inserter(*this),
              [](const json &bc) -> Boundary_Condition { return bc; });
  }

  //
  // ... Boundary_Condition
  Boundary_ID
  Boundary_Condition::boundary() const {
    return std::visit([](const auto &bc) -> Boundary_ID { return bc.boundary(); },
                      static_cast<const Base &>(*this));
  }

  void
  to_json(json &j, const Boundary_Condition &boundary_condition) {
    visit([&](const auto &boundary_condition) { j = boundary_condition; }, boundary_condition);
  }

  void
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

  ostream &
  operator<<(ostream &os, const Boundary_Condition &boundary_condition) {
    return os << json(boundary_condition);
  }

  istream &
  operator>>(istream &is, Boundary_Condition &boundary_condition) {
    boundary_condition = json::parse(is);
    return is;
  }

  bool
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

  //
  // ... Wall
  //
  Wall::Wall(Boundary_ID boundary)
      : boundary_{boundary} {}

  bool
  operator==(const Wall &wall1, const Wall &wall2) {
    return wall1.boundary_ == wall2.boundary_;
  }

  Boundary_ID
  Wall::boundary() const {
    return boundary_;
  }

  json
  Wall::get_json() const {
    json j = json::object();
    j["wall"] = json::object();
    j["wall"]["boundary"] = boundary_;
    return j;
  }

  void
  Wall::set_json(const json &j) {
    boundary_ = j["wall"]["boundary"];
  }

  //
  // ... Symmetry
  //
  Symmetry::Symmetry(Boundary_ID boundary)
      : boundary_{boundary} {}

  bool
  operator==(const Symmetry &symmetry1, const Symmetry &symmetry2) {
    return symmetry1.boundary_ == symmetry2.boundary_;
  }

  bool
  operator!=(const Symmetry &symmetry1, const Symmetry &symmetry2) {
    return !(symmetry1 == symmetry2);
  }

  Boundary_ID
  Symmetry::boundary() const {
    return boundary_;
  }

  json
  Symmetry::get_json() const {
    json j = json::object();
    j["symmetry"] = boundary_;
    return j;
  }

  void
  Symmetry::set_json(const json &j) {
    boundary_ = j["symmetry"];
  }

  //
  // ... Inlet
  //

  Inlet::Inlet(Boundary_ID boundary, double density, double speed)
      : boundary_{boundary}
      , density_{density}
      , speed_{speed} {}

  bool
  operator==(const Inlet &inlet1, const Inlet &inlet2) {
    return inlet1.boundary_ == inlet2.boundary_ && inlet1.density_ == inlet2.density_ &&
           inlet1.speed_ == inlet2.speed_;
  }

  bool
  operator!=(const Inlet &inlet1, const Inlet &inlet2) {
    return !(inlet1 == inlet2);
  }

  double
  Inlet::density() const {
    return density_;
  }

  double
  Inlet::speed() const {
    return speed_;
  }

  Boundary_ID
  Inlet::boundary() const {
    return boundary_;
  }

  json
  Inlet::get_json() const {
    json j = json::object();
    j["inlet"]["boundary"] = boundary_;
    j["inlet"]["inletSpeed"] = speed_;
    return j;
  }

  void
  Inlet::set_json(const json &j) {
    boundary_ = j["inlet"]["boundary"];
    density_ = j["inlet"]["density"];
    speed_ = j["inlet"]["speed"];
  }

  //
  // ... Outlet
  //

  Outlet::Outlet(Boundary_ID boundary, double density, double speed)
      : boundary_{boundary}
      , density_{density}
      , speed_{speed} {}

  bool
  operator==(const Outlet &outlet1, const Outlet &outlet2) {
    return outlet1.boundary_ == outlet2.boundary_ && outlet1.density_ == outlet2.density_ &&
           outlet1.speed_ == outlet2.speed_;
  }

  bool
  operator!=(const Outlet &outlet1, const Outlet &outlet2) {
    return !(outlet1 == outlet2);
  }

  double
  Outlet::density() const {
    return density_;
  }

  double
  Outlet::speed() const {
    return speed_;
  }

  Boundary_ID
  Outlet::boundary() const {
    return boundary_;
  }

  json
  Outlet::get_json() const {
    json j = json::object();
    j["outlet"] = json::object();
    j["outlet"]["boundary"] = boundary_;
    j["outlet"]["density"] = density_;
    j["outlet"]["speed"] = speed_;
    return j;
  }

  void
  Outlet::set_json(const json &j) {
    boundary_ = j["outlet"]["boundary"];
    density_ = j["outlet"]["dentity"];
    speed_ = j["outlet"]["speed"];
  }

  //
  // ... Pressure_Drop

  Pressure_Drop::Pressure_Drop(Boundary_ID boundary, double value)
      : boundary_(boundary)
      , value_(value) {}

  bool
  operator==(const Pressure_Drop &pressure_drop1, const Pressure_Drop &pressure_drop2) {
    return pressure_drop1.boundary_ == pressure_drop2.boundary_ &&
           pressure_drop1.value_ == pressure_drop2.value_;
  }

  bool
  operator!=(const Pressure_Drop &pressure_drop1, const Pressure_Drop &pressure_drop2) {
    return !(pressure_drop1 == pressure_drop2);
  }

  Boundary_ID
  Pressure_Drop::boundary() const {
    return boundary_;
  }

  json
  Pressure_Drop::get_json() const {
    json j = json::object();
    j["pressureDrop"] = json::object();
    j["pressureDrop"]["boundary"] = boundary_;
    j["pressureDrop"]["value"] = value_;
    return j;
  }

  void
  Pressure_Drop::set_json(const json &j) {
    boundary_ = j["pressureDrop"]["boundary"];
    value_ = j["pressureDrop"]["value"];
  }

} // end of namespace lbm::core
