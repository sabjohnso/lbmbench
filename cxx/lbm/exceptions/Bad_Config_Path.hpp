#pragma once

//
// ... LBM Bench header files
//
#include <lbm/exceptions/import.hpp>

namespace lbm::exceptions {

  class Bad_Config_Path : public runtime_error {
  public:
    using runtime_error::runtime_error;
  };

} // namespace lbm::exceptions
