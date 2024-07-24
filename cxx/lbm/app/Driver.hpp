#pragma once

//
// ... LBM Bench header files
//
#include <lbm/app/Runtime_Config.hpp>

namespace lbm::app {

  class Driver {
  public:
    Driver() = delete;

    Driver(int argc, char **argv)
        : runtime_config_{argc, argv} {}

    operator int() const { return 0; }

  private:
    Runtime_Config runtime_config_;
  };

} // end of namespace lbm::app
