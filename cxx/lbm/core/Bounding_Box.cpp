//
// ... LBM Bench header files
//
#include <lbm/core/Bounding_Box.hpp>

namespace lbm::core {

  json
  Bounding_Box::get_json() const {
    json j = static_cast<const Base &>(*this);
    return j;
  }

  void
  Bounding_Box::set_json(const json &j) {
    static_cast<Base &>(*this) = vector<double>(j);
  }

} // end of namespace lbm::core
