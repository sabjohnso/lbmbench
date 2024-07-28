#pragma once

//
// ... LBM Bench header files
//
#include <lbm/app/import.hpp>
#include <lbm/config.hpp>

//
// ... iostream header files
//
#include <iostream>

namespace lbm::app {

  class Runtime_Config {
  public:
    Runtime_Config(int argc, const char *const *argv);

    ~Runtime_Config();

    const json &
    input() const;

  private:
    class Impl;
    Impl *pimpl;
  };

} // end of namespace lbm::app
