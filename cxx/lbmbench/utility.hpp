#pragma once

//
// ... LBM Bench header files
//
#include <lbmbench/details/Array.hpp>
#include <lbmbench/details/Boundary_Condition.hpp>
#include <lbmbench/details/Boundary_ID.hpp>
#include <lbmbench/details/Bounding_Box.hpp>
#include <lbmbench/details/D2Q9.hpp>
#include <lbmbench/details/Euclidean.hpp>
#include <lbmbench/details/Expression.hpp>
#include <lbmbench/details/Fixed_Array.hpp>
#include <lbmbench/details/Fixed_Array_Index.hpp>
#include <lbmbench/details/Fixed_Lexical.hpp>
#include <lbmbench/details/Index.hpp>
#include <lbmbench/details/Initial_Conditions.hpp>
#include <lbmbench/details/Input.hpp>
#include <lbmbench/details/JSON_Convertible.hpp>
#include <lbmbench/details/Lattice.hpp>
#include <lbmbench/details/Lexical.hpp>
#include <lbmbench/details/Obstacle.hpp>
#include <lbmbench/details/Shape.hpp>
#include <lbmbench/details/Vector.hpp>

namespace lbm {
  using details::Bounding_Box;
  using details::Euclidean;
  using details::Input;
  using details::Lattice;
  using details::Obstacle;
  using details::Obstacles;
  using details::x;
  using details::y;

  using details::JSON_Convertible;

  using details::Array;
  using details::Fixed_Array;
  using details::Fixed_Array_Index;
  using details::Fixed_Lexical;
  using details::Index;
  using details::integer;
  using details::json;
  using details::Lexical;
  using details::Shape;
  using details::size_type;
  using details::Vector;

  using details::Boundary;
  using details::Boundary_Condition;
  using details::Boundary_ID;

  using details::Initial_Conditions;

  using details::parse_json_expr;

  using details::Expression;

  // Constants and coordinates
  using details::Constant;
  using details::X;
  using details::Y;
  using details::Z;

  // Binary arithmetic functions
  using details::Add;
  using details::Divide;
  using details::Multiply;
  using details::Power;
  using details::Subtract;

  // Binary special functions
  using details::Atan2;
  using details::Hypot;

  // Unary arithmetic functions
  using details::Negate;
  using details::Reciprocal;

  // Trig functions
  using details::Cos;
  using details::Sin;
  using details::Tan;

  // Inverse trig functions
  using details::Acos;
  using details::Asin;
  using details::Atan;

  // Hyperbolic functions
  using details::Cosh;
  using details::Sinh;
  using details::Tanh;

  // Inverse hyperbolic functions
  using details::Acosh;
  using details::Asinh;
  using details::Atanh;

  // Exponential and logarithmic functions
  using details::Cbrt;
  using details::Cube;
  using details::Exp;
  using details::Heaviside;
  using details::Log;
  using details::Log10;
  using details::Sqrt;
  using details::Square;

  namespace D2Q9 = details::D2Q9;

} // end of namespace lbm
