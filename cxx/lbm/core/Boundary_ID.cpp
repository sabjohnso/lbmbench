//
// ... LBM Bench header files
//
#include <lbm/core/Boundary_ID.hpp>

namespace lbm::core {

  void
  to_json(json &j, Boundary_ID id) {
    switch (id) {
    case Boundary_ID::Left:
      j = "left";
      break;
    case Boundary_ID::Right:
      j = "right";
      break;
    case Boundary_ID::Bottom:
      j = "bottom";
      break;
    case Boundary_ID::Top:
      j = "top";
      break;
    case Boundary_ID::Front:
      j = "front";
      break;
    case Boundary_ID::Back:
      j = "back";
      break;
    }
  }

  void
  from_json(const json &j, Boundary_ID &id) {
    if (j == "left") {
      id = Boundary_ID::Left;
    } else if (j == "right") {
      id = Boundary_ID::Right;
    } else if (j == "bottom") {
      id = Boundary_ID::Bottom;
    } else if (j == "top") {
      id = Boundary_ID::Top;
    } else if (j == "front") {
      id = Boundary_ID::Front;
    } else if (j == "back") {
      id = Boundary_ID::Back;
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
