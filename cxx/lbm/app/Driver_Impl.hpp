#pragma once

//
// ... LBM Bench header files
//
#include <lbm/D2Q9/State.hpp>
#include <lbm/app/Driver.hpp>
#include <lbm/app/Runtime_Config.hpp>
#include <lbm/app/import.hpp>

namespace lbm::app {

  class Driver::Impl {
  public:
    Impl() = delete;

    Impl(int argc, char **argv);

    operator int() const;

  private:
    Runtime_Config runtime_config_;
    Input input_;
    unique_ptr<I_State> pstate_{};
  };

} // end of namespace lbm::app
