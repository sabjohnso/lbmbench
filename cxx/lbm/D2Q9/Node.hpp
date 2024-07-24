#pragma once

//
// ... LBM Bench header files
//
#include <lbm/D2Q9/Velocity_Distribution.hpp>
#include <lbm/D2Q9/import.hpp>

namespace lbm::D2Q9 {

  /**
   * @brief A node in the the lattice holding the velocity, density and
   * velocity distribution.
   */
  template <class T>
  class Node final : public JSON_Convertible {
    using Value_Type = T;
    using Reference = T &;
    using Const_Reference = const T &;
    using Velocity = Vector<T, 2>;
    using Density = Value_Type;

    using Inverse_Time_Scale = Velocity_Distribution<T>::Inverse_Time_Scale;

  public:
    Node() = default;
    Node(Velocity_Distribution<T> classes, bool obstacle = false)
        : velocity_distribution_(classes)
        , obstacle_{obstacle} {}

    Density
    density() const {
      return density_;
    }

    Velocity
    velocity() const {
      return velocity_;
    }

    bool
    is_obstacle() const {
      return obstacle_;
    }

    void
    init(Density density, Euclidean velocity) {
      density_ = density;
      copy(std::begin(velocity), std::end(velocity), std::begin(velocity_));
      velocity_distribution_.set_equilibrium(density_, velocity_);
    }

    void
    collide() {
      density_ = velocity_distribution_.density();
      velocity_ = velocity_distribution_.velocity();
      velocity_distribution_.collide(inverse_time_scale_, density_, velocity_);
    }

    friend bool
    operator==(const Node &node1, const Node &node2) {
      return (node1.velocity_distribution_ == node2.velocity_distribution_) &&
             (node1.velocity_ == node2.velocity_) && //
             (node1.density_ == node2.density_);
    }

    friend bool
    operator!=(const Node &node1, const Node &node2) {
      return !(node1 == node2);
    }

  private:
    json
    get_json() const override {
      json j = json::object();
      j = json::object();
      j["classes"] = velocity_distribution_;
      j["velocity"] = velocity_;
      j["density"] = density_;
      return j;
    }

    void
    set_json(const json &j) override {
      velocity_distribution_ = j["classes"];
      velocity_ = j["velocity"];
      density_ = j["density"];
    }

    Velocity_Distribution<T> velocity_distribution_{};
    Velocity velocity_{};
    Density density_{};
    Inverse_Time_Scale inverse_time_scale_{};
    bool obstacle_{};
  };

} // end of namespace lbm::D2Q9
