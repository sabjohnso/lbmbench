//
// ... LBM Bench header files
//
#include <lbmbench/details/Expression.hpp>

namespace lbm::details {

  bool
  operator==(const Expr &a, const Expr &b) {
    return json(a) == json(b);
  }

  bool
  operator!=(const Expr &a, const Expr &b) {
    return !(a == b);
  }

  Constant::Constant(double value) : value_(value) {}

  double
  Constant::eval(const vector<double> &) const {
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

  Binary_Operator::Binary_Operator(Pointer arg1, Pointer arg2) : arg1_(arg1), arg2_(arg2) {}

  Binary_Operator::Binary_Operator(const json &arg1, const json &arg2)
      : arg1_(parse_json_expr(arg1)), arg2_(parse_json_expr(arg2)) {}

  double
  Binary_Operator::eval(const vector<double> &coord) const {
    return operate(arg1_->eval(coord), arg2_->eval(coord));
  }

  json
  Binary_Operator::get_json() const {

    json j = json::object();
    j[name()] = json::array();
    json arg1_json = *arg1_;
    json arg2_json = *arg2_;
    j[name()].push_back(arg1_json);
    j[name()].push_back(arg2_json);
    return j;
  };

  void
  Binary_Operator::set_json(const json &j) {
    arg1_ = parse_json_expr(j[name()][0]);
    arg2_ = parse_json_expr(j[name()][1]);
  };

  Unary_Operator::Unary_Operator(Pointer arg) : arg_(arg) {}

  json
  Unary_Operator::get_json() const {
    json j = json::object();
    j[name()] = json(*arg_);

    return j;
  };

  void
  Unary_Operator::set_json(const json &j) {
    arg_ = parse_json_expr(j.at(name()));
  }

  string
  Add::name() const {
    return "add"s;
  }

  double
  Add::operate(double arg1, double arg2) const {
    return arg1 + arg2;
  }

  string
  Subtract::name() const {
    return "subtract"s;
  }

  double
  Subtract::operate(double arg1, double arg2) const {
    return arg1 - arg2;
  }

  string
  Multiply::name() const {
    return "mutliply"s;
  }

  double
  Multiply::operate(double arg1, double arg2) const {
    return arg1 * arg2;
  }

  string
  Divide::name() const {
    return "divide"s;
  }

  double
  Divide::operate(double arg1, double arg2) const {
    return arg1 / arg2;
  }

  string
  Power::name() const {
    return "pow"s;
  }

  double
  Power::operate(double arg1, double arg2) const {
    return std::pow(arg1, arg2);
  }

  string
  Atan2::name() const {
    return "atan2"s;
  }

  double
  Atan2::operate(double arg1, double arg2) const {
    return std::atan2(arg1, arg2);
  }

  string
  Hypot::name() const {
    return "hypot"s;
  }

  double
  Hypot::operate(double arg1, double arg2) const {
    return std::hypot(arg1, arg2);
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

} // namespace lbm::details
