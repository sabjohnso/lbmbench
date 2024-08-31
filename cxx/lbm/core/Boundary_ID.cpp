#include <lbm/core/Boundary_ID.hpp>

namespace lbm::core {

  void
  to_json(json &j, Boundary_ID id) {
    using enum Boundary_ID;
    switch (id) {
    case Left:
      j = "left";
      break;
    case Right:
      j = "right";
      break;
    case Bottom:
      j = "bottom";
      break;
    case Top:
      j = "top";
      break;
    case Front:
      j = "front";
      break;
    case Back:
      j = "back";
      break;
    }
  }

  void
  from_json(const json &j, Boundary_ID &id) {
    using enum Boundary_ID;
    if (j == "left") {
      id = Left;
    } else if (j == "right") {
      id = Right;
    } else if (j == "bottom") {
      id = Bottom;
    } else if (j == "top") {
      id = Top;
    } else if (j == "front") {
      id = Front;
    } else if (j == "back") {
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
