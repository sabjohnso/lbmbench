#pragma once

//
// ... LBM Bench header files
//
#include <lbmbench/details/import.hpp>

namespace lbm::details {

  class JSON_Convertible {
    virtual json
    get_json() const = 0;

    virtual void
    set_json(const json &) = 0;

    friend void
    to_json(json &j, const JSON_Convertible &e) {
      j = e.get_json();
    }

    friend void
    from_json(const json &j, JSON_Convertible &e) {
      e.set_json(j);
    }

    friend ostream &
    operator<<(ostream &os, const JSON_Convertible &e) {
      return os << json(e);
    }

    friend istream &
    operator>>(istream &is, JSON_Convertible &e) {
      e.set_json(json::parse(is));
      return is;
    }
  };

} // end of namespace lbm::details
