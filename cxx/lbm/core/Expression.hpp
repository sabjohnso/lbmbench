#pragma once

//
// ... LBM Bench header files
//
#include <lbm/core/Euclidean.hpp>
#include <lbm/core/JSON_Convertible.hpp>
#include <lbm/core/base_types.hpp>
#include <lbm/core/import.hpp>

namespace lbm::core {

  class Expr : public JSON_Convertible {
  public:
    virtual double
    eval(const Euclidean &) const = 0;
    virtual ~Expr() = default;

    friend bool
    operator==(const Expr &a, const Expr &b);

    friend bool
    operator!=(const Expr &a, const Expr &b);
  };

  class Expression;

  Expression
  parse_json_expr(json j);

  class Expression final : public JSON_Convertible {
  public:
    using Pointer = shared_ptr<Expr>;

    Expression();

    template <derived_from<Expr> T>
    Expression(shared_ptr<T> pexpr)
        : pexpr_(pexpr) {}

    friend bool
    operator==(const Expression &e0, const Expression &e1) {
      return e0.pexpr_ == e1.pexpr_ || *e0.pexpr_ == *e1.pexpr_;
    }

    friend bool
    operator!=(const Expression &e0, const Expression &e1) {
      return !(e0 == e1);
    }

    double
    eval(const Euclidean &coord) const {
      assert(pexpr_);
      return pexpr_->eval(coord);
    }

    friend Expression
    operator+(Expression e0, Expression e1);

    friend Expression
    operator+(double e0, Expression e1);

    friend Expression
    operator+(Expression e0, double e1);

    friend Expression
    operator-(Expression e0, Expression e1);

    friend Expression
    operator-(double e0, Expression e1);

    friend Expression
    operator-(Expression e0, double e1);

    friend Expression
    operator*(Expression e0, Expression e1);

    friend Expression
    operator*(double e0, Expression e1);

    friend Expression
    operator*(Expression e0, double e1);

    friend Expression
    operator/(Expression e0, Expression e1);

    friend Expression
    operator/(double e0, Expression e1);

    friend Expression
    operator/(Expression e0, double e1);

    friend Expression
    pow(Expression e0, Expression e1);

    friend Expression
    pow(double e0, Expression e1);

    friend Expression
    pow(Expression e0, double e1);

    friend Expression
    heavyside(Expression e);

    operator bool() const { return bool{pexpr_}; }

  private:
    json
    get_json() const override {
      assert(pexpr_);
      return *pexpr_;
    }

    void
    set_json(const json &j) override {
      *this = parse_json_expr(j);
    }

    Pointer pexpr_{};
  };

  Expression
  parse_json_expr(json j);

  class Constant final : public Expr {
  public:
    using Base = Expr;
    Constant() = default;
    Constant(double value);

    double
    eval(const Euclidean &) const override;

  private:
    json
    get_json() const override;

    void
    set_json(const json &j) override;

    double value_;
  };

  template <size_type I>
  class Coord : public Expr {
  public:
    double
    eval(const Euclidean &coord) const override {
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
    name() const override;
  };

  class Y final : public Coord<1> {
  public:
    Y() = default;

  private:
    string
    name() const override;
  };

  class Z final : public Coord<2> {
  public:
    Z() = default;

  private:
    string
    name() const override;
  };

  class Binary_Operator : public Expr {
  public:
    Binary_Operator() = default;

    template <derived_from<Expr> T, derived_from<Expr> U>
    Binary_Operator(const T &arg0, const U &arg1)
        : arg0_(make_shared<T>(arg0))
        , arg1_(make_shared<U>(arg1)) {}

    Binary_Operator(Expression arg0, Expression arg1);

    Binary_Operator(const json &arg0, const json &arg1);

    double
    eval(const Euclidean &coord) const override;

  private:
    virtual double
    operate(double arg0, double arg1) const = 0;

    virtual string
    name() const = 0;

    json
    get_json() const override;

    void
    set_json(const json &j) override;

    Expression arg0_{};
    Expression arg1_{};
  };

  class Add final : public Binary_Operator {
  public:
    using Binary_Operator::Binary_Operator;

  private:
    string
    name() const override;

    double
    operate(double arg0, double arg1) const override;
  };

  class Subtract final : public Binary_Operator {
  public:
    using Binary_Operator::Binary_Operator;

  private:
    string
    name() const override;

    double
    operate(double arg0, double arg1) const override;
  };

  class Multiply final : public Binary_Operator {
  public:
    using Binary_Operator::Binary_Operator;

  private:
    string
    name() const override;

    double
    operate(double arg0, double arg1) const override;
  };

  class Divide final : public Binary_Operator {
  public:
    using Binary_Operator::Binary_Operator;

  private:
    string
    name() const override;

    double
    operate(double arg0, double arg1) const override;
  };

  class Power final : public Binary_Operator {
  public:
    using Binary_Operator::Binary_Operator;

  private:
    string
    name() const override;

    double
    operate(double arg0, double arg1) const override;
  };

  class Atan2 final : public Binary_Operator {
  public:
    using Binary_Operator::Binary_Operator;

  private:
    string
    name() const override;

    double
    operate(double arg0, double arg1) const override;
  };

  class Hypot final : public Binary_Operator {
  public:
    using Binary_Operator::Binary_Operator;

  private:
    string
    name() const override;

    double
    operate(double arg0, double arg1) const override;
  };

  class Unary_Operator : public Expr {
  public:
    using Pointer = shared_ptr<Expr>;

    Unary_Operator() = default;

    explicit Unary_Operator(Expression arg)
        : arg_(arg) {}

    template <derived_from<Expr> T>
    explicit Unary_Operator(const T &arg)
        : arg_(make_shared<T>(arg)) {}

    explicit Unary_Operator(Pointer arg);

    double
    eval(const Euclidean &coord) const override {
      return operate(arg_.eval(coord));
    }

  private:
    virtual double
    operate(double arg) const = 0;

    virtual string
    name() const = 0;

    json
    get_json() const override;

    void
    set_json(const json &j) override;

    Expression arg_{};
  };

  class Negate final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override;

    double
    operate(double arg) const override;
  };

  class Reciprocal final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override;

    double
    operate(double arg) const override;
  };

  class Cos final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override;

    double
    operate(double arg) const override;
  };

  class Sin final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override;

    double
    operate(double arg) const override;
  };

  class Tan final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override;

    double
    operate(double arg) const override;
  };

  class Acos final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override;

    double
    operate(double arg) const override;
  };

  class Asin final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override;

    double
    operate(double arg) const override;
  };

  class Atan final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override;

    double
    operate(double arg) const override;
  };

  class Cosh final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override;

    double
    operate(double arg) const override;
  };

  class Sinh final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override;

    double
    operate(double arg) const override;
  };

  class Tanh final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override;

    double
    operate(double arg) const override;
  };

  class Acosh final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override;

    double
    operate(double arg) const override;
  };

  class Asinh final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override;

    double
    operate(double arg) const override;
  };

  class Atanh final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override;

    double
    operate(double arg) const override;
  };

  class Exp final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override;

    double
    operate(double arg) const override;
  };

  class Log final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override;

    double
    operate(double arg) const override;
  };

  class Log10 final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override;

    double
    operate(double arg) const override;
  };

  class Sqrt final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override;

    double
    operate(double arg) const override;
  };

  class Cbrt final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override;

    double
    operate(double arg) const override;
  };

  class Square final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override;

    double
    operate(double arg) const override;
  };

  class Cube final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override;

    double
    operate(double arg) const override;
  };

  class Heaviside final : public Unary_Operator {
  public:
    using Unary_Operator::Unary_Operator;

  private:
    string
    name() const override;

    double
    operate(double arg) const override;
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
      {"heaviside"s, [](const json &j) { return make_shared<Heaviside>(j); }},
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

  const Expression x = json("x");
  const Expression y = json("y");

  Expression
  constant(double c);

  Expression
  square(Expression e);

  double
  square(double c);

  // double
  // heaviside(double arg);

} // end of namespace lbm::core
