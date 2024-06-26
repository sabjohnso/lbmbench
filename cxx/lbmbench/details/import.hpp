#pragma once

//
// ... Third-party header files
//
#include <nlohmann/json.hpp>

//
// ... Standard header files
//
#include <algorithm>
#include <array>
#include <concepts>
#include <functional>
#include <iostream>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <vector>

namespace lbm::details {

  using nlohmann::json;

  using namespace std::literals;

  // from array
  using std::array;

  // from algorithm
  using std::array;

  // from vector
  using std::vector;

  // from concepts
  using std::convertible_to;

  // from iostream
  using std::istream;
  using std::ostream;

  // from sstream
  using std::ostringstream;

  // from stdexcept
  using std::runtime_error;

  // from functional
  using std::multiplies;

  // from numeric
  using std::accumulate;
  using std::inner_product;

  // from concepts
  using std::integral;
  using std::same_as;

  // from utility
  using std::index_sequence;
  using std::make_index_sequence;

} // end of namespace lbm::details
