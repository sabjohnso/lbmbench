#pragma once

//
// ... LBM Bench header files
//
#include <lbm/core/Array.hpp>
#include <lbm/core/Dynamic_Array.hpp>
#include <lbm/core/Euclidean.hpp>
#include <lbm/core/Fixed_Array.hpp>
#include <lbm/core/IState.hpp>
#include <lbm/core/Input.hpp>
#include <lbm/core/JSON_Convertible.hpp>
#include <lbm/core/Lexical.hpp>
#include <lbm/core/Shape.hpp>
#include <lbm/core/Vector.hpp>
#include <lbm/core/base_types.hpp>
#include <lbm/core/misc.hpp>

//
// ... Standard header files
//
#include <algorithm>
#include <array>
#include <concepts>
#include <utility>
#include <vector>

namespace lbm::D2Q9 {
  using lbm::core::Array;
  using lbm::core::Dynamic_Array;
  using lbm::core::Euclidean;
  using lbm::core::Fixed_Array;
  using lbm::core::Fixed_Lexical;
  using lbm::core::Input;
  using lbm::core::integer;
  using lbm::core::IState;
  using lbm::core::json;
  using lbm::core::JSON_Convertible;
  using lbm::core::Lexical;
  using lbm::core::Shape;
  using lbm::core::size_type;
  using lbm::core::sqr;
  using lbm::core::unroll_horizontally;
  using lbm::core::Vector;

  using std::array;
  using std::copy;
  using std::for_each;
  using std::index_sequence;
  using std::make_index_sequence;
  using std::same_as;
  using std::vector;

} // end of namespace lbm::D2Q9
