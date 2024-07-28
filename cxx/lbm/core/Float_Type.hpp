#pragma once

//
// ... LBM Bench header files
//
#include <lbm/core/import.hpp>

namespace lbm::core {

  enum Float_Type { FLOAT32, FLOAT64 };

  void
  to_json(json &j, const Float_Type &float_type);

  void
  from_json(const json &j, Float_Type &float_type);

} // end of namespace lbm::core
