//
// ... LBM Bench header files
//
#include <lbm/core/Float_Type.hpp>

namespace lbm::core {

  void
  to_json(json &j, const Float_Type &float_type) {
    switch (float_type) {
    case Float_Type::FLOAT32:
      j = "Float32";
      break;
    case Float_Type::FLOAT64:
      j = "Float64";
      break;
    }
  }

  void
  from_json(const json &j, Float_Type &float_type) {
    if (j == "Float32") {
      float_type = Float_Type::FLOAT32;
    } else if (j == "Float64") {
      float_type = Float_Type::FLOAT64;
    } else {
      throw Bad_Float_Type{j.dump()};
    }
  }

} // end of namespace lbm::core
