#pragma once

//
// ... LBM Bench header files
//
#include <lbm/core/JSON_Convertible.hpp>

namespace lbm::core {

  class I_State : public JSON_Convertible {
  public:
    virtual void
    step() = 0;

    virtual ~I_State() {}
  };

} // end of namespace lbm::core
