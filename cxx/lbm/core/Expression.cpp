//
// ... LBM Bench header files
//
#include <lbm/core/Expression.hpp>

namespace lbm::core {

  Expression::Expression()
      : pexpr_{make_shared<Constant>(0.0)} {}

  Expression
  operator+(Expression e0, Expression e1) {
    return make_shared<Add>(e0, e1);
  }

  Expression
  operator+(double e0, Expression e1) {
    return make_shared<Add>(Expression(make_shared<Constant>(e0)), e1);
  }

  Expression
  operator+(Expression e0, double e1) {
    return make_shared<Add>(e0, Expression(make_shared<Constant>(e1)));
  }

  Expression
  operator-(Expression e0, Expression e1) {
    return make_shared<Subtract>(e0, e1);
  }

  Expression
  operator-(double e0, Expression e1) {
    return make_shared<Subtract>(Expression(make_shared<Constant>(e0)), e1);
  }

  Expression
  operator-(Expression e0, double e1) {
    return make_shared<Subtract>(e0, Expression(make_shared<Constant>(e1)));
  }

  Expression
  operator*(Expression e0, Expression e1) {
    return make_shared<Multiply>(e0, e1);
  }

  Expression
  operator*(double e0, Expression e1) {
    return make_shared<Multiply>(Expression(make_shared<Constant>(e0)), e1);
  }

  Expression
  operator*(Expression e0, double e1) {
    return make_shared<Multiply>(e0, Expression(make_shared<Constant>(e1)));
  }

  Expression
  operator/(Expression e0, Expression e1) {
    return make_shared<Divide>(e0, e1);
  }

  Expression
  operator/(double e0, Expression e1) {
    return make_shared<Divide>(Expression(make_shared<Constant>(e0)), e1);
  }

  Expression
  operator/(Expression e0, double e1) {
    return make_shared<Divide>(e0, Expression(make_shared<Constant>(e1)));
  }

  Expression
  pow(Expression e0, Expression e1) {
    return make_shared<Power>(e0, e1);
  }

  Expression
  pow(double e0, Expression e1) {
    return make_shared<Power>(Expression(make_shared<Constant>(e0)), e1);
  }

  Expression
  pow(Expression e0, double e1) {
    return make_shared<Power>(e0, Expression(make_shared<Constant>(e1)));
  }

  // Expression
  // heaviside(Expression e) {
  //   return make_shared<Heaviside>(e);
  // }

  // double
  // heaviside(double arg) {
  //   return arg > 0.0 ? 1.0 : 0.0;
  // }

  bool
  operator==(const Expr &a, const Expr &b) {
    return json(a) == json(b);
  }

  bool
  operator!=(const Expr &a, const Expr &b) {
    return !(a == b);
  }

  Constant::Constant(double value)
      : value_(value) {}

  double
  Constant::eval(const Euclidean &) const {
    return value_;
  }

  json
  Constant::get_json() const {
    return value_;
  }

  void
  Constant::set_json(const json &j) {
    value_ = j;
  }

  string
  X::name() const {
    return "x"s;
  }

  string
  Y::name() const {
    return "y"s;
  }

  string
  Z::name() const {
    return "z"s;
  }

  Binary_Operator::Binary_Operator(Expression arg0, Expression arg1)
      : arg0_(arg0)
      , arg1_(arg1) {}

  Binary_Operator::Binary_Operator(const json &arg0, const json &arg1)
      : arg0_(parse_json_expr(arg0))
      , arg1_(parse_json_expr(arg1)) {}

  double
  Binary_Operator::eval(const Euclidean &coord) const {
    return operate(arg0_.eval(coord), arg1_.eval(coord));
  }

  json
  Binary_Operator::get_json() const {
    json j = json::object();
    j[name()] = json::array();
    json arg0_json = arg0_;
    json arg1_json = arg1_;
    j[name()].push_back(arg0_json);
    j[name()].push_back(arg1_json);
    return j;
  }

  void
  Binary_Operator::set_json(const json &j) {
    arg0_ = parse_json_expr(j[name()][0]);
    arg1_ = parse_json_expr(j[name()][1]);
  }

  Unary_Operator::Unary_Operator(Pointer arg)
      : arg_(arg) {}

  json
  Unary_Operator::get_json() const {
    json j = json::object();
    j[name()] = json(arg_);

    return j;
  }

  void
  Unary_Operator::set_json(const json &j) {
    arg_ = parse_json_expr(j.at(name()));
  }

  string
  Add::name() const {
    return "add"s;
  }

  double
  Add::operate(double arg0, double arg1) const {
    return arg0 + arg1;
  }

  string
  Subtract::name() const {
    return "subtract"s;
  }

  double
  Subtract::operate(double arg0, double arg1) const {
    return arg0 - arg1;
  }

  string
  Multiply::name() const {
    return "multiply"s;
  }

  double
  Multiply::operate(double arg0, double arg1) const {
    return arg0 * arg1;
  }

  string
  Divide::name() const {
    return "divide"s;
  }

  double
  Divide::operate(double arg0, double arg1) const {
    return arg0 / arg1;
  }

  string
  Power::name() const {
    return "pow"s;
  }

  double
  Power::operate(double arg0, double arg1) const {
    return std::pow(arg0, arg1);
  }

  string
  Atan2::name() const {
    return "atan2"s;
  }

  double
  Atan2::operate(double arg0, double arg1) const {
    return std::atan2(arg0, arg1);
  }

  string
  Hypot::name() const {
    return "hypot"s;
  }

  double
  Hypot::operate(double arg0, double arg1) const {
    return std::hypot(arg0, arg1);
  }

  string
  Negate::name() const {
    return "negate"s;
  }

  double
  Negate::operate(double arg) const {
    return -arg;
  }

  string
  Reciprocal::name() const {
    return "reciprocal"s;
  }

  double
  Reciprocal::operate(double arg) const {
    return 1.0 / arg;
  }

  string
  Cos::name() const {
    return "cos"s;
  }

  double
  Cos::operate(double arg) const {
    return std::cos(arg);
  }

  string
  Sin::name() const {
    return "sin"s;
  }

  double
  Sin::operate(double arg) const {
    return std::sin(arg);
  }

  string
  Tan::name() const {
    return "tan"s;
  }

  double
  Tan::operate(double arg) const {
    return std::tan(arg);
  }

  string
  Acos::name() const {
    return "acos"s;
  }

  double
  Acos::operate(double arg) const {
    return std::acos(arg);
  }

  string
  Asin::name() const {
    return "asin"s;
  }

  double
  Asin::operate(double arg) const {
    return std::asin(arg);
  }

  string
  Atan::name() const {
    return "atan"s;
  }

  double
  Atan::operate(double arg) const {
    return std::atan(arg);
  }

  string
  Cosh::name() const {
    return "cosh"s;
  }

  double
  Cosh::operate(double arg) const {
    return std::cosh(arg);
  }

  string
  Sinh::name() const {
    return "sinh"s;
  }

  double
  Sinh::operate(double arg) const {
    return std::sinh(arg);
  }

  string
  Tanh::name() const {
    return "tanh"s;
  }

  double
  Tanh::operate(double arg) const {
    return std::tanh(arg);
  }

  string
  Acosh::name() const {
    return "acosh"s;
  }

  double
  Acosh::operate(double arg) const {
    return std::acosh(arg);
  }

  string
  Asinh::name() const {
    return "asinh"s;
  }

  double
  Asinh::operate(double arg) const {
    return std::asinh(arg);
  }

  string
  Atanh::name() const {
    return "atanh"s;
  }

  double
  Atanh::operate(double arg) const {
    return std::atanh(arg);
  }

  string
  Exp::name() const {
    return "exp"s;
  }

  double
  Exp::operate(double arg) const {
    return std::exp(arg);
  }

  string
  Log::name() const {
    return "log"s;
  }

  double
  Log::operate(double arg) const {
    return std::log(arg);
  }

  string
  Log10::name() const {
    return "log10"s;
  }

  double
  Log10::operate(double arg) const {
    return std::log10(arg);
  }

  string
  Sqrt::name() const {
    return "sqrt"s;
  }

  double
  Sqrt::operate(double arg) const {
    return std::sqrt(arg);
  }

  string
  Cbrt::name() const {
    return "cbrt"s;
  }

  double
  Cbrt::operate(double arg) const {
    return std::cbrt(arg);
  }

  string
  Square::name() const {
    return "square"s;
  }

  double
  Square::operate(double arg) const {
    return arg * arg;
  }

  string
  Cube::name() const {
    return "cube"s;
  }

  double
  Cube::operate(double arg) const {
    return arg * arg * arg;
  }

  string
  Heaviside::name() const {
    return "heaviside"s;
  }

  double
  Heaviside::operate(double arg) const {
    return arg > 0.0 ? 1.0 : 0.0;
  }

  Expression
  constant(double c) {
    return make_shared<Constant>(c);
  }

  Expression
  square(Expression e) {
    return make_shared<Square>(Square{e});
  }

  double
  square(double c) {
    return c * c;
  }

} // namespace lbm::core
