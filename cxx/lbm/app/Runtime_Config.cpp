#include <lbm/app/Runtime_Config.hpp>
#include <lbm/app/Runtime_Config_Impl.hpp>

namespace lbm::app {

  Runtime_Config::Runtime_Config(int argc, const char *const *argv)
      : pimpl{new Impl{argc, argv}} {}

  Runtime_Config::~Runtime_Config() { delete pimpl; }

  const json &
  Runtime_Config::input() const {
    assert(pimpl);
    return pimpl->input();
  }

} // end of namespace lbm::app
