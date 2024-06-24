#pragma once

//
// ... Third-party header files
//
#include <nlohmann/json.hpp>

//
// ... Standard header files
//
#include <array>
#include <concepts>
#include <iostream>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace lbm::details {

  using nlohmann::json;

  using namespace std::literals;

  using std::array;
  using std::convertible_to;
  using std::inner_product;
  using std::istream;
  using std::ostream;
  using std::ostringstream;
  using std::runtime_error;

  // from concepts
  using std::integral;
  using std::same_as;

  // from utility
  using std::index_sequence;
  using std::make_index_sequence;

} // end of namespace lbm::details
