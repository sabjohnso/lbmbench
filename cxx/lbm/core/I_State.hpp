#pragma once

//
// ... LBM Bench header files
//
#include <lbm/core/JSON_Convertible.hpp>
#include <lbm/core/base_types.hpp>

namespace lbm::core {

  class I_State : public JSON_Convertible {
  public:
    virtual void
    step() = 0;

    void
    step_n_times(size_type n) {
      for (size_type i = 0; i < n; ++i) {
        step();
      }
    }

    virtual ~I_State() {}
  };

} // end of namespace lbm::core
