#pragma once

//
// ... LBM Bench header files
//
#include <lbm/core/Expression.hpp>
#include <lbm/core/JSON_Convertible.hpp>

namespace lbm::core {

  class Obstacle final : public JSON_Convertible {
  public:
    Obstacle() = default;

    Obstacle(Expression expression)
        : expression_(expression) {}

    bool
    contains(const Euclidean &coord) const {
      return expression_.eval(coord) > 0.0;
    }

    friend bool
    operator==(const Obstacle &obs0, const Obstacle &obs1) {
      return obs0.expression_ == obs1.expression_;
    }

    friend bool
    operator!=(const Obstacle &obs0, const Obstacle &obs1) {
      return !(obs0 == obs1);
    }

  private:
    json
    get_json() const override {
      json j = expression_;
      return j;
    }

    void
    set_json(const json &j) override {
      expression_ = parse_json_expr(j);
    }

    Expression expression_;
  };

  class Obstacles
      : public vector<Obstacle>
      , public JSON_Convertible {
  public:
    using Base = vector<Obstacle>;
    using Base::Base;

    bool
    contains(Euclidean point) const {
      bool result = false;
      auto iter = Base::begin();
      auto last = Base::end();
      while (!result && iter != last) {
        result = iter->contains(point);
        ++iter;
      }
      return result;
    }

  private:
    json
    get_json() const override {
      json j = static_cast<const Base &>(*this);
      return j;
    }

    void
    set_json(const json &j) override {
      Base::clear();
      transform(std::begin(j), std::end(j), back_inserter(*this), [](const json &expr) {
        return parse_json_expr(expr);
      });
    }
  };

} // end of namespace lbm::core
