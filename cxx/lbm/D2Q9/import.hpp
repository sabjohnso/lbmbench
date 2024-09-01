#pragma once

//
// ... LBM Bench header files
//
#include <lbm/core/Array2.hpp>
#include <lbm/core/Boundary_Condition.hpp>
#include <lbm/core/Boundary_ID.hpp>
#include <lbm/core/Dynamic_Array.hpp>
#include <lbm/core/Euclidean.hpp>
#include <lbm/core/Fixed_Array.hpp>
#include <lbm/core/Fixed_Euclidean.hpp>
#include <lbm/core/I_State.hpp>
#include <lbm/core/Input.hpp>
#include <lbm/core/JSON_Convertible.hpp>
#include <lbm/core/Lexical.hpp>
#include <lbm/core/MD_Array.hpp>
#include <lbm/core/Shape.hpp>
#include <lbm/core/base_types.hpp>
#include <lbm/core/forall.hpp>
#include <lbm/core/misc.hpp>
#include <lbm/core/subdomain_tags.hpp>

//
// ... Standard header files
//
#include <algorithm>
#include <array>
#include <concepts>
#include <functional>
#include <unordered_map>
#include <utility>
#include <vector>

namespace lbm::D2Q9 {
  using lbm::core::Bottom;
  using lbm::core::bottom;
  using lbm::core::Boundary_Tag2;
  using lbm::core::Interior;
  using lbm::core::interior;
  using lbm::core::Left;
  using lbm::core::left;
  using lbm::core::Right;
  using lbm::core::right;
  using lbm::core::Top;
  using lbm::core::top;

  using lbm::core::Array2;
  using lbm::core::Boundary_Condition;
  using lbm::core::Boundary_ID;
  using lbm::core::Dynamic_MD_Array;
  using lbm::core::Euclidean;
  using lbm::core::Fixed_Euclidean;
  using lbm::core::Fixed_Lexical;
  using lbm::core::Fixed_MD_Array;
  using lbm::core::I_State;
  using lbm::core::Inlet;
  using lbm::core::Input;
  using lbm::core::integer;
  using lbm::core::json;
  using lbm::core::JSON_Convertible;
  using lbm::core::Lexical;
  using lbm::core::MD_Array;
  using lbm::core::Outlet;
  using lbm::core::Pressure_Drop;
  using lbm::core::Shape;
  using lbm::core::size_type;
  using lbm::core::sqr;
  using lbm::core::Symmetry;
  using lbm::core::unroll_horizontally;
  using lbm::core::Wall;

  using std::array;
  using std::copy;
  using std::for_each;
  using std::function;
  using std::holds_alternative;
  using std::index_sequence;
  using std::make_index_sequence;
  using std::same_as;
  using std::unordered_map;
  using std::vector;

} // end of namespace lbm::D2Q9
