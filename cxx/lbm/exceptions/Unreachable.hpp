#pragma once

//
// ... LBM Bench header files
//
#include <lbm/exceptions/import.hpp>

namespace lbm::exceptions {

  class Unreachable_Code : public logic_error {
  public:
    using logic_error::logic_error;
  };

  [[noreturn]] inline void
  unreachable_code(source_location sloc) {
    ostringstream ss{};
    ss << sloc.file_name() << ":" << sloc.line() << ":0 Executing unreachable code";
    throw Unreachable_Code{ss.str()};
  }

} // end of namespace lbm::exceptions
