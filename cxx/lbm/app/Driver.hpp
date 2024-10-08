#pragma once

//
// ... LBM Bench header files
//
#include <lbm/D2Q9/State.hpp>
#include <lbm/app/Runtime_Config.hpp>
#include <lbm/app/import.hpp>

namespace lbm::app {

  class Driver {
  public:
    Driver() = delete;

    Driver(int argc, char **argv);
    ~Driver();

    operator int() const;

  private:
    class Impl;
    Impl *pimpl;
  };

} // end of namespace lbm::app
