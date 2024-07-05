//
// ... LBM Bench header files
//
#include <lbmbench/details/Bounding_Box.hpp>

namespace lbm::details {

  json
  Bounding_Box::get_json() const {
    json j = static_cast<const Base &>(*this);
    return j;
  }

  void
  Bounding_Box::set_json(const json &j) {
    static_cast<Base &>(*this) = vector<double>(j);
  }

} // end of namespace lbm::details
