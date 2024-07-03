#pragma once

//
// ... LBM Bench header files
//
#include <lbmbench/details/Expression.hpp>
#include <lbmbench/details/import.hpp>

namespace lbm::details {

  class Initial_Conditions : public JSON_Convertible {

  public:
    using Density_Expression = Expression;
    using Velocity_Expression = vector<Expression>;
    using Density = double;
    using Velocity = vector<double>;
    using Coordinates = vector<double>;

    Initial_Conditions() = default;

    Initial_Conditions(Density_Expression density, Velocity_Expression velocity)
        : density_(density), velocity_(velocity) {}

    Density
    density(Coordinates coord) const {
      return density_->eval(coord);
    }

    Velocity
    velocity(Coordinates coord) const {
      return {velocity_[0]->eval(coord), velocity_[1]->eval(coord)};
    }

    friend bool
    operator==(const Initial_Conditions &ic1, const Initial_Conditions &ic2) {
      assert(ic1.density_);
      assert(ic1.velocity_[0]);
      assert(ic1.velocity_[1]);
      assert(ic2.density_);
      assert(ic2.velocity_[0]);
      assert(ic2.velocity_[1]);

      return *ic1.density_ == *ic2.density_ && *ic1.velocity_[0] == *ic2.velocity_[0] &&
             *ic1.velocity_[1] == *ic1.velocity_[1];
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
      j["initialConditions"]["density"] = *density_;
      j["initialConditions"]["velocity"] = json::array();
      transform(std::begin(velocity_),
                std::end(velocity_),
                back_inserter(j["initialConditions"]["velocity"]),
                [](Expression expr) { return json(*expr); });
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

    Expression density_;
    vector<Expression> velocity_;
  };
} // end of namespace lbm::details
