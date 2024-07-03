#pragma once

//
// ... LBM Bench header files
//
#include <lbmbench/details/JSON_Convertible.hpp>
#include <lbmbench/details/import.hpp>

namespace lbm::details {

  class Expr : public JSON_Convertible {
  public:
    virtual double
    eval(const vector<double> &) const = 0;
    virtual ~Expr() = default;

    friend bool
    operator==(const Expr &a, const Expr &b) {
      return json(a) == json(b);
    }

    friend bool
    operator!=(const Expr &a, const Expr &b) {
      return !(a == b);
    }
  };
  using Expression = shared_ptr<Expr>;

  Expression
  parse_json_expr(json j);

  class Constant final : public Expr {
  public:
    using Base = Expr;
    Constant() = default;
    Constant(double value) : value_(value) {}

    double
    eval(const vector<double> &) const override {
      return value_;
    }

  private:
    json
    get_json() const override {
      return value_;
    }

    void
    set_json(const json &j) override {
      value_ = j;
    }

    double value_;
  };

  template <size_type I>
  class Coord : public Expr {
  public:
    double
    eval(const vector<double> &coord) const override {
      if (coord.size() > I) {
        return coord[I];
      } else {
        throw runtime_error("Coordinate "s + name() + " cannot be extracted from "s +
                            json(coord).dump() + "."s);
      }
    }

  private:
    json
    get_json() const override {
      return name();
    }

    void
    set_json(const json &j) override {
      assert(j == name());
    }

    virtual string
    name() const = 0;
  };

  class X final : public Coord<0> {
  public:
    X() = default;

  private:
    string
    name() const override {
      return "x"s;
    }
  };

  class Y final : public Coord<1> {
  public:
    Y() = default;

  private:
    string
    name() const override {
      return "y"s;
    }
  };

  class Z final : public Coord<2> {
  public:
    Z() = default;

  private:
    string
    name() const override {
      return "z"s;
    }
  };

  class Binary_Operator : public Expr {
  public:
    using Pointer = shared_ptr<Expr>;

    Binary_Operator() = default;

    template <derived_from<Expr> T, derived_from<Expr> U>
    Binary_Operator(const T &arg1, const U &arg2)
        : arg1_(make_shared<T>(arg1)), arg2_(make_shared<U>(arg2)) {}

    Binary_Operator(Pointer arg1, Pointer arg2) : arg1_(arg1), arg2_(arg2) {}

    Binary_Operator(const json &arg1, const json &arg2)
        : arg1_(parse_json_expr(arg1)), arg2_(parse_json_expr(arg2)) {}

    double
    eval(const vector<double> &coord) const override {
      return operate(arg1_->eval(coord), arg2_->eval(coord));
    }

  private:
    virtual double
    operate(double arg1, double arg2) const = 0;

    virtual string
    name() const = 0;

    json
    get_json() const override {

      json j = json::object();
      j[name()] = json::array();
      json arg1_json = *arg1_;
      json arg2_json = *arg2_;
      j[name()].push_back(arg1_json);
      j[name()].push_back(arg2_json);
      return j;
    };

    void
    set_json(const json &j) override {
      arg1_ = parse_json_expr(j[name()][0]);
      arg2_ = parse_json_expr(j[name()][1]);
    };

    Pointer arg1_{};
    Pointer arg2_{};
  };

  class Add final : public Binary_Operator {
  public:
    using Binary_Operator::Binary_Operator;

  private:
    string
    name() const override {
      return "add"s;
    }

    double
    operate(double arg1, double arg2) const override {
      return arg1 + arg2;
    }
  };

  class Subtract final : public Binary_Operator {
  public:
    using Binary_Operator::Binary_Operator;

  private:
    string
    name() const override {
      return "subtract"s;
    }

    double
    operate(double arg1, double arg2) const override {
      return arg1 - arg2;
    }
  };

  class Multiply final : public Binary_Operator {
  public:
    using Binary_Operator::Binary_Operator;

  private:
    string
    name() const override {
      return "mutliply"s;
    }

    double
    operate(double arg1, double arg2) const override {
      return arg1 * arg2;
    }
  };

  class Divide final : public Binary_Operator {
  public:
    using Binary_Operator::Binary_Operator;

  private:
    string
    name() const override {
      return "mutliply"s;
    }

    double
    operate(double arg1, double arg2) const override {
      return arg1 / arg2;
    }
  };

  class Power final : public Binary_Operator {
  public:
    using Binary_Operator::Binary_Operator;

  private:
    string
    name() const override {
      return "pow"s;
    }

    double
    operate(double arg1, double arg2) const override {
      return std::pow(arg1, arg2);
    }
  };

  class Atan2 final : public Binary_Operator {
  public:
    using Binary_Operator::Binary_Operator;

  private:
    string
    name() const override {
      return "atan2"s;
    }

    double
    operate(double arg1, double arg2) const override {
      return std::atan2(arg1, arg2);
    }
  };

  class Hypot final : public Binary_Operator {
  public:
    using Binary_Operator::Binary_Operator;

  private:
    string
    name() const override {
      return "hypot"s;
    }

    double
    operate(double arg1, double arg2) const override {
      return std::hypot(arg1, arg2);
    }
  };

  class Unary_Operator : public Expr {
  public:
    using Pointer = shared_ptr<Expr>;

    Unary_Operator() = default;

    template <derived_from<Expr> T>
    explicit Unary_Operator(const T &arg) : arg_(make_shared<T>(arg)) {}

    explicit Unary_Operator(Pointer arg) : arg_(arg) {}

    double
    eval(const vector<double> &coord) const override {
      return operate(arg_->eval(coord));
    }

  private:
    virtual double
    operate(double arg) const = 0;

    virtual string
    name() const = 0;

    json
    get_json() const override {
      json j = json::object();
      j[name()] = json(*arg_);

      return j;
    };

    void
    set_json(const json &j) override {
      arg_ = parse_json_expr(j.at(name()));
    }

    Pointer arg_{};
  };

  class Negate final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override {
      return "negate"s;
    }

    double
    operate(double arg) const override {
      return -arg;
    }
  };

  class Reciprocal final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override {
      return "reciprocal"s;
    }

    double
    operate(double arg) const override {
      return 1.0 / arg;
    }
  };

  class Cos final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override {
      return "cos"s;
    }

    double
    operate(double arg) const override {
      return std::cos(arg);
    }
  };

  class Sin final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override {
      return "sin"s;
    }

    double
    operate(double arg) const override {
      return std::sin(arg);
    }
  };

  class Tan final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override {
      return "tan"s;
    }

    double
    operate(double arg) const override {
      return std::tan(arg);
    }
  };

  class Acos final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override {
      return "acos"s;
    }

    double
    operate(double arg) const override {
      return std::acos(arg);
    }
  };

  class Asin final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override {
      return "asin"s;
    }

    double
    operate(double arg) const override {
      return std::asin(arg);
    }
  };

  class Atan final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override {
      return "atan"s;
    }

    double
    operate(double arg) const override {
      return std::atan(arg);
    }
  };

  class Cosh final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override {
      return "cosh"s;
    }

    double
    operate(double arg) const override {
      return std::cosh(arg);
    }
  };

  class Sinh final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override {
      return "sinh"s;
    }

    double
    operate(double arg) const override {
      return std::sinh(arg);
    }
  };

  class Tanh final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override {
      return "tanh"s;
    }

    double
    operate(double arg) const override {
      return std::tanh(arg);
    }
  };

  class Acosh final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override {
      return "acosh"s;
    }

    double
    operate(double arg) const override {
      return std::acosh(arg);
    }
  };

  class Asinh final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override {
      return "asinh"s;
    }

    double
    operate(double arg) const override {
      return std::asinh(arg);
    }
  };

  class Atanh final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override {
      return "atanh"s;
    }

    double
    operate(double arg) const override {
      return std::atanh(arg);
    }
  };

  class Exp final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override {
      return "exp"s;
    }

    double
    operate(double arg) const override {
      return std::exp(arg);
    }
  };

  class Log final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override {
      return "log"s;
    }

    double
    operate(double arg) const override {
      return std::log(arg);
    }
  };

  class Log10 final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override {
      return "log10"s;
    }

    double
    operate(double arg) const override {
      return std::log10(arg);
    }
  };

  class Sqrt final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override {
      return "sqrt"s;
    }

    double
    operate(double arg) const override {
      return std::sqrt(arg);
    }
  };

  class Cbrt final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override {
      return "cbrt"s;
    }

    double
    operate(double arg) const override {
      return std::cbrt(arg);
    }
  };

  class Square final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override {
      return "square"s;
    }

    double
    operate(double arg) const override {
      return arg * arg;
    }
  };

  class Cube final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override {
      return "cube"s;
    }

    double
    operate(double arg) const override {
      return arg * arg * arg;
    }
  };

  static const std::map<string, function<shared_ptr<Expr>(const json &)>> operator_map = {
      {"add"s, [](const json &j) { return make_shared<Add>(j); }},
      {"subtract"s, [](const json &j) { return make_shared<Subtract>(j); }},
      {"multiply"s, [](const json &j) { return make_shared<Multiply>(j); }},
      {"divide"s, [](const json &j) { return make_shared<Divide>(j); }},
      {"pow"s, [](const json &j) { return make_shared<Power>(j); }},
      {"atan2"s, [](const json &j) { return make_shared<Atan2>(j); }},
      {"hypot"s, [](const json &j) { return make_shared<Hypot>(j); }},
      {"negate"s, [](const json &j) { return make_shared<Negate>(j); }},
      {"reciprocal"s, [](const json &j) { return make_shared<Reciprocal>(j); }},
      {"cos"s, [](const json &j) { return make_shared<Cos>(j); }},
      {"sin"s, [](const json &j) { return make_shared<Sin>(j); }},
      {"tan"s, [](const json &j) { return make_shared<Tan>(j); }},
      {"acos"s, [](const json &j) { return make_shared<Acos>(j); }},
      {"asin"s, [](const json &j) { return make_shared<Asin>(j); }},
      {"atan"s, [](const json &j) { return make_shared<Atan>(j); }},
      {"cosh"s, [](const json &j) { return make_shared<Cosh>(j); }},
      {"sinh"s, [](const json &j) { return make_shared<Sinh>(j); }},
      {"tanh"s, [](const json &j) { return make_shared<Tanh>(j); }},
      {"acosh"s, [](const json &j) { return make_shared<Acosh>(j); }},
      {"asinh"s, [](const json &j) { return make_shared<Asinh>(j); }},
      {"atanh"s, [](const json &j) { return make_shared<Atanh>(j); }},
      {"exp"s, [](const json &j) { return make_shared<Exp>(j); }},
      {"log"s, [](const json &j) { return make_shared<Log>(j); }},
      {"log10"s, [](const json &j) { return make_shared<Log10>(j); }},
      {"sqrt"s, [](const json &j) { return make_shared<Sqrt>(j); }},
      {"cbrt"s, [](const json &j) { return make_shared<Cbrt>(j); }},
      {"square"s, [](const json &j) { return make_shared<Square>(j); }},
      {"cube"s, [](const json &j) { return make_shared<Cube>(j); }},

  };

  inline string
  get_operator_name(json j) {
    assert(j.is_object());
    assert(j.size() == 1);

    vector<string> keys{};
    for (auto it = j.begin(); it != j.end(); ++it) {
      keys.push_back(it.key());
    }

    if (keys.size() == 1) {
      return keys[0];
    } else {
      throw runtime_error("Expected exactly 1 key in expression object but found "s +
                          to_string(keys.size()));
    }
  }

  inline Expression
  parse_json_expr(json j) {
    std::cout << j << std::endl;
    if (j.is_number()) {
      return make_shared<Constant>(Constant{j.get<double>()});

    } else if (j.is_string()) {
      if (j == "x"s) {
        return make_shared<X>();

      } else if (j == "y"s) {
        return make_shared<Y>();

      } else if (j == "z"s) {
        return make_shared<Z>();

      } else {
        throw runtime_error(j.get<string>() + " is not a valid coordinate name."s);
      }
    } else if (j.is_object()) {
      string operator_name = get_operator_name(j);
      if (operator_map.contains(operator_name)) {
        return operator_map.at(operator_name)(j);
      } else {
        throw runtime_error(operator_name + " is not a valid operator name.");
      }
    } else {
      throw runtime_error("Failed to parse JSON expression: "s + j.dump(4));
    }
  }

} // end of namespace lbm::details
