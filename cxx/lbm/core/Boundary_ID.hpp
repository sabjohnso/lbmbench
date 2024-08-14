#pragma once

//
// ... LBM Bench header files
//
#include <lbm/core/JSON_Convertible.hpp>
#include <lbm/core/import.hpp>

namespace lbm::core {

  enum class Boundary_ID { Left, Right, Bottom, Top, Front, Back };

  void
  to_json(json &j, Boundary_ID id);

  void
  from_json(const json &j, Boundary_ID &id);

  ostream &
  operator<<(ostream &os, Boundary_ID id);

  istream &
  operator>>(istream &is, Boundary_ID &id);

} // end of namespace lbm::core
