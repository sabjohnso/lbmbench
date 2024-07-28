#pragma once

//
// ... LBM Bench header files
//
#include <lbm/core/import.hpp>

namespace lbm::core {

  enum Kernel { D2Q9 };

  void
  to_json(json &j, const Kernel &);

  void
  from_json(const json &j, Kernel &kernel);

} // end of namespace lbm::core
