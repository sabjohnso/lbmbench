#pragma once

//
// ... LBM Bench header files
//
#include <lbm/core/Boundary_Condition.hpp>
#include <lbm/core/Boundary_ID.hpp>
#include <lbm/core/Bounding_Box.hpp>
#include <lbm/core/D2Q9.hpp>
#include <lbm/core/Euclidean.hpp>
#include <lbm/core/Expression.hpp>
#include <lbm/core/Fixed_Array.hpp>
#include <lbm/core/Fixed_Array_Index.hpp>
#include <lbm/core/Fixed_Lexical.hpp>
#include <lbm/core/Index.hpp>
#include <lbm/core/Initial_Conditions.hpp>
#include <lbm/core/Input.hpp>
#include <lbm/core/JSON_Convertible.hpp>
#include <lbm/core/Lattice.hpp>
#include <lbm/core/Lexical.hpp>
#include <lbm/core/MD_Array.hpp>
#include <lbm/core/Obstacle.hpp>
#include <lbm/core/Shape.hpp>
#include <lbm/core/Vector.hpp>

namespace lbm {
  using core::Bounding_Box;
  using core::Euclidean;
  using core::Input;
  using core::Lattice;
  using core::Obstacle;
  using core::Obstacles;
  using core::x;
  using core::y;

  using core::JSON_Convertible;

  using core::Array;
  using core::Fixed_Lexical;
  using core::Fixed_MD_Array;
  using core::Fixed_MD_Array_Index;
  using core::Index;
  using core::integer;
  using core::json;
  using core::Lexical;
  using core::Shape;
  using core::size_type;
  using core::Vector;

  using core::Boundary;
  using core::Boundary_Condition;
  using core::Boundary_ID;

  using core::Initial_Conditions;

  using core::parse_json_expr;

  using core::Expression;

  // Constants and coordinates
  using core::Constant;
  using core::X;
  using core::Y;
  using core::Z;

  // Binary arithmetic functions
  using core::Add;
  using core::Divide;
  using core::Multiply;
  using core::Power;
  using core::Subtract;

  // Binary special functions
  using core::Atan2;
  using core::Hypot;

  // Unary arithmetic functions
  using core::Negate;
  using core::Reciprocal;

  // Trig functions
  using core::Cos;
  using core::Sin;
  using core::Tan;

  // Inverse trig functions
  using core::Acos;
  using core::Asin;
  using core::Atan;

  // Hyperbolic functions
  using core::Cosh;
  using core::Sinh;
  using core::Tanh;

  // Inverse hyperbolic functions
  using core::Acosh;
  using core::Asinh;
  using core::Atanh;

  // Exponential and logarithmic functions
  using core::Cbrt;
  using core::Cube;
  using core::Exp;
  using core::Heaviside;
  using core::Log;
  using core::Log10;
  using core::Sqrt;
  using core::Square;

  namespace D2Q9 = core::D2Q9;

} // end of namespace lbm
