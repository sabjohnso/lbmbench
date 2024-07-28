#pragma once

//
// ... LBM Bench header files
//
#include <lbm/core/JSON_Convertible.hpp>

namespace lbm::core {

  class IState : public JSON_Convertible {
  public:
    virtual void
    step() = 0;

    virtual ~IState() {}
  };

} // end of namespace lbm::core
