#pragma once

//
// ... LBM Bench header files
//
#include <lbm/core/JSON_Convertible.hpp>
#include <lbm/core/import.hpp>

namespace lbm::core {

  template <class T>
  class Dynamic_Array
      : public vector<T>
      , public JSON_Convertible {
  public:
    using Base = vector<T>;
    using Base::Base;

  private:
    json
    get_json() const override {
      json j = json::array();
      copy(std::cbegin(*this), std::cend(*this), back_inserter(j));
      return j;
    }

    void
    set_json(const json &j) override {
      Base::clear();
      copy(std::cbegin(j), std::cend(j), back_inserter(*this));
    }
  };

} // end of namespace lbm::core
