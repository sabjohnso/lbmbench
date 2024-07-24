#pragma once

//
// ... LBM Bench header files
//
#include <lbm/exceptions/import.hpp>

namespace lbm::exceptions {

  class Help_Request : public runtime_error {
  public:
    using runtime_error::runtime_error;
  };

} // end of namespace lbm::exceptions
