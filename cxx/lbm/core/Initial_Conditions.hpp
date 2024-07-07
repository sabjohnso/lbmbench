#pragma once

//
// ... LBM Bench header files
//
#include <lbm/core/Expression.hpp>
#include <lbm/core/import.hpp>

namespace lbm::core {

  class Initial_Density final : public JSON_Convertible {
  public:
    Initial_Density() = default;
    Initial_Density(Expression expression)
        : expression_{expression} {}
    explicit Initial_Density(double c)
        : expression_{make_shared<Constant>(c)} {}

    double
    eval(const Euclidean &coord) const {
      return expression_.eval(coord);
    }

    friend bool
    operator==(const Initial_Density den1, const Initial_Density den2) {
      return den1.expression_ == den2.expression_;
    }

    friend bool
    operator!=(const Initial_Density den1, const Initial_Density den2) {
      return !(den1 == den2);
    }

  private:
    json
    get_json() const override {
      json j = expression_;
      return j;
    }

    void
    set_json(const json &j) override {
      expression_ = j;
    }
    Expression expression_;
  };

  class Initial_Velocity final
      : public vector<Expression>
      , public JSON_Convertible {
  public:
    using Base = vector<Expression>;
    using Base::Base;

    Initial_Velocity() = default;
    Initial_Velocity(const vector<double> &velocity) {
      transform(std::begin(velocity), std::end(velocity), back_inserter(*this), constant);
    }

    size_type
    size() const {
      return Base::size();
    }

    friend bool
    operator==(const Initial_Velocity &velocity1, const Initial_Velocity velocity2) {
      return velocity1.size() == velocity2.size() && //
             transform_reduce(std::begin(velocity1),
                              std::end(velocity1),
                              std::begin(velocity2),
                              true,
                              logical_and{},
                              equal_to{});
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
      transform(std::begin(j), std::end(j), back_inserter(*this), [](const json &json_element) {
        return parse_json_expr(json_element);
      });
    }
  };

  class Initial_Conditions final : public JSON_Convertible {

  public:
    using Density = double;
    using Velocity = Euclidean;
    using Coordinates = Euclidean;

    Initial_Conditions() = default;

    Initial_Conditions(Initial_Density density, Initial_Velocity velocity)
        : density_(density)
        , velocity_(velocity) {}

    Density
    density(Coordinates coord) const {
      return density_.eval(coord);
    }

    Velocity
    velocity(Coordinates coord) const {
      Euclidean result{};
      transform(std::begin(velocity_),
                std::end(velocity_),
                back_inserter(result),
                [&](const Expression &component) { return component.eval(coord); });
      return result;
    }

    friend bool
    operator==(const Initial_Conditions &ic1, const Initial_Conditions &ic2) {
      return ic1.density_ == ic2.density_ && //
             ic1.velocity_ == ic2.velocity_;
    }

    friend bool
    operator!=(const Initial_Conditions &ic1, const Initial_Conditions &ic2) {
      return !(ic1 == ic2);
    }

  private:
    json
    get_json() const override {
      json j = json::object();
      j["initialConditions"] = json::object();
      j["initialConditions"]["density"] = density_;
      j["initialConditions"]["velocity"] = json::array();
      transform(std::begin(velocity_),
                std::end(velocity_),
                back_inserter(j["initialConditions"]["velocity"]),
                [](Expression expr) { return json(expr); });
      return j;
    }

    void
    set_json(const json &j) override {
      density_ = parse_json_expr(j["initialConditions"]["density"]);
      velocity_.resize(j["initialConditions"]["velocity"].size());
      transform(std::begin(j["initialConditions"]["velocity"]),
                std::end(j["initialConditions"]["velocity"]),
                std::begin(velocity_),
                parse_json_expr);
    }

    Initial_Density density_;
    Initial_Velocity velocity_;
  };
} // end of namespace lbm::core
