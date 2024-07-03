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
#include <cmath>
#include <concepts>
#include <functional>
#include <iostream>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

namespace lbm::details {

  using nlohmann::json;

  using namespace std::literals;

  // from utility
  using std::index_sequence;
  using std::make_index_sequence;

  // from array
  using std::array;

  // from algorithm
  using std::fill;
  using std::reduce;
  using std::transform_reduce;

  // from functional
  using std::equal_to;
  using std::function;
  using std::logical_and;
  using std::multiplies;
  using std::plus;

  // from vector
  using std::vector;

  // from concepts
  using std::convertible_to;
  using std::derived_from;

  // from string
  using std::string;
  using std::to_string;

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

  // from variant
  using std::variant;
  using std::visit;

  // from type_traits
  using std::common_type_t;
  using std::is_default_constructible_v;

  // from memory
  using std::make_shared;
  using std::make_unique;
  using std::shared_ptr;
  using std::unique_ptr;

} // end of namespace lbm::details
