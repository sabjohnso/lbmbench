#pragma once

#pragma once

//
// ... LBM Bench header files
//
#include <lbm/exceptions/import.hpp>

namespace lbm::exceptions {

  class Bad_Float_Type : public runtime_error {
  public:
    using runtime_error::runtime_error;
  };

} // end of namespace lbm::exceptions
