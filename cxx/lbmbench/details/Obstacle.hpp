#pragma once

//
// ... LBM Bench header files
//
#include <lbmbench/details/Expression.hpp>
#include <lbmbench/details/JSON_Convertible.hpp>

namespace lbm::details {

  class Obstacle : public JSON_Convertible {
  public:
    Obstacle(Expression expression) : expression_(expression) {}

  private:
    json
    get_json() const override {
      json j = *expression;
      return j;
    }

    void
    set_json(const json &j) override {
      expression_ = parse_json_expression(j);
    }

    Expression expression_;
  };

  class Obstacles : public vector<Obstacle>, public JSON_Convertible {
  public:
    using Base = vector<Obstacle>;
    using Base::Base;

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
        return parse_json_expression(expr);
      });
    }
  };

} // end of namespace lbm::details
