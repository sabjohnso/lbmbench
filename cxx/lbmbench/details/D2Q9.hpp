#pragma once

//
// ... LBM Bench header files
//
#include <lbmbench/details/Fixed_Array.hpp>
#include <lbmbench/details/Fixed_Lexical.hpp>
#include <lbmbench/details/Initial_Conditions.hpp>

#include <lbmbench/details/JSON_Convertible.hpp>
#include <lbmbench/details/Vector.hpp>
#include <lbmbench/details/import.hpp>
#include <lbmbench/details/misc.hpp>

#include <lbmbench/details/D2_Lattice.hpp>

namespace lbm::details::D2Q9 {

  template <class T>
  class Velocity_Distribution : public JSON_Convertible {
  public:
    using Value_Type = T;
    using Reference = T &;
    using Const_Reference = const T &;
    using Density = Value_Type;
    using Storage = Fixed_Array<Value_Type, Fixed_Lexical<3, 3>>;
    using Velocity = Vector<Value_Type, 2>;
    using Momentum = Vector<Value_Type, 2>;

    static constexpr T four_9ths = T(4) / T(9);
    static constexpr T one_9th = T(1) / T(9);
    static constexpr T one_36th = T(1) / T(36);
    static constexpr T one = 1;
    static constexpr T three = 3;
    static constexpr T nine_halves = T(9) / T(2);
    static constexpr T three_halves = T(3) / T(2);

    // clang-format off
    static constexpr Fixed_Array<T, Fixed_Lexical<3,3>> weights = {
        one_36th, one_9th,   one_36th,
        one_9th,  four_9ths, one_9th,
        one_36th, one_9th,   one_36th
    };
    // clang-format on

    // clang-format off
    static constexpr  Fixed_Array<Velocity, Fixed_Lexical<3, 3>>
    discrete_velocities =
      {Velocity{-1, -1}, Velocity{0, -1}, Velocity{1, -1},
       Velocity{-1,  0}, Velocity{0,  0}, Velocity{1,  0},
       Velocity{-1,  1}, Velocity{0,  1}, Velocity{1,  1}};
    // clang-format on

    Velocity_Distribution() = default;

    constexpr Velocity_Distribution(T f1, T f2, same_as<T> auto... fs) : storage_{f1, f2, fs...} {}

    constexpr explicit Velocity_Distribution(Density density, Velocity velocity)
        : storage_{compute_equilibrium_distribution(density, velocity)} {}

    constexpr explicit Velocity_Distribution(Storage values) : storage_{std::move(values)} {}

    constexpr Const_Reference
    operator[](integer i, integer j) const {
      return storage_[i + 1, j + 1];
    }

    Reference
    operator[](integer i, integer j) {
      return storage_[i + 1, j + 1];
    }

    friend bool
    operator==(const Velocity_Distribution &vd1, const Velocity_Distribution &vd2) {
      return vd1.storage_ == vd2.storage_;
    }

    friend bool
    operator!=(const Velocity_Distribution &vd1, const Velocity_Distribution &vd2) {
      return !(vd1 == vd2);
    }

    constexpr Density
    density() const {
      return [this]<std::size_t... Index>(index_sequence<Index...>) {
        return (storage_[Index] + ...);
      }(make_index_sequence<Storage::size()>());
    }

    constexpr Momentum
    momentum() const {
      return [this]<std::size_t... Index>(index_sequence<Index...>) {
        return ((storage_[Index] * discrete_velocities[Index]) + ...);
      }(make_index_sequence<Storage::size()>());
    }

    constexpr Velocity
    velocity() const {
      return momentum() / density();
    }

    static constexpr Velocity_Distribution
    equilibrium(Density density, Velocity velocity) {
      return [&]<std::size_t... Index>(index_sequence<Index...>) {
        return Velocity_Distribution{weights[Index] * density *
                                     (one + three * dot(discrete_velocities[Index], velocity) +
                                      nine_halves * sqr(dot(discrete_velocities[Index], velocity)) -
                                      three_halves * dot(velocity, velocity))...};
      }(make_index_sequence<Storage::size()>());
    }

  private:
    json
    get_json() const override {
      json j = json::object();
      j["classDensities"] = storage_;
      return j;
    }

    void
    set_json(const json &j) override {
      storage_ = j["classDensities"];
    }

    Storage storage_{};
  };

  /**
   * @brief A node in the the lattice holding the velocity and density in addition to the
   * velocity distribution.
   */
  template <class T>
  class Node {
    using Value_Type = T;
    using Reference = T &;
    using Const_Reference = const T &;

    using Velocity = array<Value_Type, 2>;
    using Density = Value_Type;

  public:
    Node() = default;
    Node(Velocity_Distribution<T> classes, bool obstacle)
        : velocity_distribution_(classes), obstacle_(obstacle) {}

    friend void
    to_json(json &j, const Node &node) {
      j = json::object();
      j["node"] = json::object();
      j["node"]["classes"] = node.velocity_distribution_;
      j["node"]["velocity"] = node.velocity_;
      j["node"]["density"] = node.density_;
      j["node"]["obstacle"] = node.obstacle_;
    }

    friend void
    from_json(const json &j, Node &node) {
      node.velocity_distribution_ = j["node"]["classes"];
      node.obstacle_ = j["node"]["obstacle"];
    }

    friend bool
    operator==(const Node &node1, const Node &node2) {
      return (node1.velocity_distribution_ == node2.velocity_distribution_) &&
             (node1.velocity_ == node2.velocity_) && //
             (node1.density_ == node2.density_) &&   //
             (node1.obstacle_ == node2.obstacle_);
    }

    friend bool
    operator!=(const Node &node1, const Node &node2) {
      return !(node1 == node2);
    }

  private:
    Velocity_Distribution<T> velocity_distribution_{};
    Velocity velocity_{};
    Density density_{};
    bool obstacle_{};
  };

  class D2Q9_Input final : public JSON_Convertible {
    using Boundary_Conditions = vector<Boundary_Condition>;
    using Initial_Conditions = Initial_Conditions;
    using Obstacles = vector<Expression>;

  public:
    D2Q9_Input() = default;
    D2Q9_Input(Lattice lattice,
               Initial_Conditions initial_conditions,
               Boundary_Conditions boundary_conditions,
               Obstacles obstacles,
               double viscosity)
        : lattice_(lattice), initial_conditions_(initial_conditions),
          boundary_conditions_(boundary_conditions), obstacles_(obstacles), viscosity_(viscosity) {}

    size_type
    nx() const {
      return lattice_.nx();
    }

    size_type
    ny() const {
      return lattice_.ny();
    }

    json
    get_json() const override {
      json j = json::object();
      j["D2Q9Input"] = json::object();
      j["D2Q9Input"]["viscosity"] = viscosity_;
      j["D2Q9Input"]["boundaryConditions"] = boundary_conditions_;
      j["D2Q9Input"]["obstacles"] = json::array();
      transform(std::begin(obstacles_),
                std::end(obstacles_),
                back_inserter(j["D2Q9Input"]["obstacles"]),
                [](Expression expr) -> json { return *expr; });

      j["D2Q9Input"].update(lattice_);
      return j;
    }

    void
    set_json(const json &j) override {
      viscosity_ = j["D2Q9Input"]["viscosity"];
      j["D2Q9Input"]["boundaryConditions"];
      boundary_conditions_.clear();
      std::transform(std::begin(j["D2Q9Input"]["boundaryConditions"]),
                     std::end(j["D2Q9Input"]["boundaryConditions"]),
                     back_inserter(boundary_conditions_),
                     [](const json bc) { return Boundary_Condition{bc}; });
      obstacles_.clear();
      std::transform(std::begin(j["D2Q9Input"]["obstacles"]),
                     std::end(j["D2Q9Input"]["obstacles"]),
                     back_inserter(obstacles_),
                     [](json obstacle) { return parse_json_expr(obstacle); });
      lattice_ = j["D2Q9Input"];
    }

  private:
    Lattice lattice_{};
    Initial_Conditions initial_conditions_{};
    Boundary_Conditions boundary_conditions_{};
    Obstacles obstacles_{};
    double viscosity_{};
  };

  template <class T>
  class D2Q9_State {
    using Input = D2Q9_Input;
    using Nodes = Array<Node<T>, 2>;
    using Order = Nodes::Order;

  public:
    D2Q9_State(Input input) : input_(input), nodes_(Order{Shape{input.nx(), input.ny()}}) {}

  private:
    void
    setup_nodes() {}

    Input input_;
    Nodes nodes_;
  };

} // end of namespace lbm::details::D2Q9
