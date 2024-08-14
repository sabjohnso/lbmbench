#include <lbm/core/Boundary_ID.hpp>

namespace lbm::core {

  void
  to_json(json &j, Boundary_ID id) {
    using enum Boundary_ID;
    switch (id) {
    case Left:
      j = "Left";
      break;
    case Right:
      j = "Right";
      break;
    case Bottom:
      j = "Bottom";
      break;
    case Top:
      j = "Top";
      break;
    case Front:
      j = "Front";
      break;
    case Back:
      j = "Back";
      break;
    }
  }

  void
  from_json(const json &j, Boundary_ID &id) {
    using enum Boundary_ID;
    if (j == "Left") {
      id = Left;
    } else if (j == "Right") {
      id = Right;
    } else if (j == "Bottom") {
      id = Bottom;
    } else if (j == "Top") {
      id = Top;
    } else if (j == "Front") {
      id = Front;
    } else if (j == "Back") {
      id = Back;
    }
  }

  ostream &
  operator<<(ostream &os, Boundary_ID id) {
    return os << json(id);
  }

  istream &
  operator>>(istream &is, Boundary_ID &id) {
    id = json::parse(is);
    return is;
  }

} // end of namespace lbm::core
