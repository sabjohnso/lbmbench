#include <lbm/app/Driver.hpp>
#include <lbm/app/Driver_Impl.hpp>

namespace lbm::app {

  Driver::Driver(int argc, char **argv)
      : pimpl{new Impl(argc, argv)} {}

  Driver::~Driver() { delete pimpl; }

  Driver::operator int() const { return static_cast<int>(*pimpl); }

} // end of namespace lbm::app
