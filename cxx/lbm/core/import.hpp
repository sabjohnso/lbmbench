#pragma once

//
// ... LBM Bench header files
//
#include <lbm/exceptions/Bad_Float_Type.hpp>
#include <lbm/exceptions/Bad_Kernel_Name.hpp>
#include <lbm/exceptions/Unreachable.hpp>

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
#include <source_location>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

namespace lbm::core {

  using nlohmann::json;

  using namespace std::literals;

  using lbm::exceptions::Bad_Float_Type;
  using lbm::exceptions::Bad_Kernel_Name;
  using lbm::exceptions::unreachable_code;

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
  using std::minus;
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
  using std::logic_error;
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
  using std::add_const_t;
  using std::add_lvalue_reference;
  using std::common_type_t;
  using std::is_default_constructible_v;
  using std::remove_cvref_t;

  // from source_location
  using std::source_location;

  // from memory
  using std::make_shared;
  using std::make_unique;
  using std::shared_ptr;
  using std::unique_ptr;

} // end of namespace lbm::core
