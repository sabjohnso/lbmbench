#include <lbm/core/Kernel.hpp>

namespace lbm::core {

  void
  to_json(json &j, const Kernel &) {
    j = "D2Q9";
  }

  void
  from_json(const json &j, Kernel &kernel) {
    if (j == "D2Q9") {
      kernel = Kernel::D2Q9;
    } else {
      throw Bad_Kernel_Name{j.dump()};
    }
  }

} // end of namespace lbm::core
