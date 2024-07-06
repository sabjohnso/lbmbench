#pragma once

//
// ... LBM Bench header files
//
#include <lbm/core/JSON_Convertible.hpp>
#include <lbm/core/import.hpp>

namespace lbm::core {

  class Bounding_Box final
      : public vector<double>
      , public JSON_Convertible {
  public:
    using Base = vector<double>;
    using Base::Base;

  private:
    json
    get_json() const override;

    void
    set_json(const json &j) override;
  };

} // end of namespace lbm::core
