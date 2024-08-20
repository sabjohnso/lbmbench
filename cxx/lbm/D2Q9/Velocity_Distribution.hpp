#pragma once

//
// ... LBM Bench header files
//
#include <lbm/D2Q9/import.hpp>

namespace lbm::D2Q9 {

  /**
   * @brief Velocity distribution for D2Q9
   */
  template <class T>
  class Velocity_Distribution : public JSON_Convertible {
  public:
    using Inverse_Time_Scale = T;
    using Value_Type = T;
    using Reference = T &;
    using Const_Reference = const T &;
    using Density = Value_Type;
    using Storage = Fixed_MD_Array<Value_Type, Fixed_Lexical<3, 3>>;
    using Velocity = Fixed_Euclidean<Value_Type, 2>;
    using Momentum = Fixed_Euclidean<Value_Type, 2>;

    static constexpr T four_9ths = T(4) / T(9);
    static constexpr T one_9th = T(1) / T(9);
    static constexpr T one_36th = T(1) / T(36);
    static constexpr T one = 1;
    static constexpr T three = 3;
    static constexpr T nine_halves = T(9) / T(2);
    static constexpr T three_halves = T(3) / T(2);

    // clang-format off
    static constexpr Fixed_MD_Array<T, Fixed_Lexical<3,3>> weights = {
      one_36th, one_9th,   one_36th,
      one_9th,  four_9ths, one_9th,
      one_36th, one_9th,   one_36th
    };
    // clang-format on

    // clang-format off
    static constexpr  Fixed_MD_Array<Velocity, Fixed_Lexical<3, 3>>
    discrete_velocities =
    {Velocity{-1, -1}, Velocity{0, -1}, Velocity{1, -1},
     Velocity{-1,  0}, Velocity{0,  0}, Velocity{1,  0},
     Velocity{-1,  1}, Velocity{0,  1}, Velocity{1,  1}};
    // clang-format on

    Velocity_Distribution() = default;

    constexpr Velocity_Distribution(T f1, T f2, same_as<T> auto... fs)
        : storage_{f1, f2, fs...} {}

    constexpr explicit Velocity_Distribution(Density density, Velocity velocity)
        : storage_{compute_equilibrium_distribution(density, velocity)} {}

    constexpr explicit Velocity_Distribution(Storage values)
        : storage_{std::move(values)} {}

    Reference
    operator()(size_type i, size_type j) {
      return storage_(i + 1, j + 1);
    }

    constexpr Const_Reference
    operator()(size_type i, size_type j) const {
      return storage_(i + 1, j + 1);
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
      }
      (make_index_sequence<Storage::size()>());
    }

    constexpr Momentum
    momentum() const {
      return [this]<std::size_t... Index>(index_sequence<Index...>) {
        return ((storage_[Index] * discrete_velocities[Index]) + ...);
      }
      (make_index_sequence<Storage::size()>());
    }

    constexpr Velocity
    velocity() const {
      return momentum() / density();
    }

    void
    collide(Inverse_Time_Scale inverse_time_scale, Density density, Velocity velocity) {
      collide_single_loop(inverse_time_scale, density, velocity);
    }
    void
    collide_double_loop_ji(Inverse_Time_Scale inverse_time_scale,
                           Density density,
                           Velocity velocity) {
      for (size_type j = 0; j < Storage::size(1); ++j) {
        for (size_type i = 0; i < Storage::size(0); ++i) {
          storage_(i, j) += inverse_time_scale *
                            (weights[i] * density *
                                 (one + three * dot(discrete_velocities(i, j), velocity()) +
                                  nine_halves * sqr(dot(discrete_velocities(i, j), velocity)) -
                                  three_halves * dot(velocity, velocity)) -
                             storage_(i, j));
        }
      }
    }

    void
    collide_double_loop_ij(Inverse_Time_Scale inverse_time_scale,
                           Density density,
                           Velocity velocity) {
      for (size_type i = 0; i < Storage::size(0); ++i) {
        for (size_type j = 0; j < Storage::size(1); ++j) {
          storage_(i, j) += inverse_time_scale *
                            (weights[i] * density *
                                 (one + three * dot(discrete_velocities(i, j), velocity()) +
                                  nine_halves * sqr(dot(discrete_velocities(i, j), velocity)) -
                                  three_halves * dot(velocity, velocity)) -
                             storage_(i, j));
        }
      }
    }

    void
    collide_single_loop(Inverse_Time_Scale inverse_time_scale, Density density, Velocity velocity) {
      for (size_type i = 0; i < Storage::size(); ++i) {
        storage_[i] +=
            inverse_time_scale * (weights[i] * density *
                                      (one + three * dot(discrete_velocities[i], velocity) +
                                       nine_halves * sqr(dot(discrete_velocities[i], velocity)) -
                                       three_halves * dot(velocity, velocity)) -
                                  storage_[i]);
      }
    }

    void
    collide_algorithm(Inverse_Time_Scale inverse_time_scale, Density density, Velocity velocity) {
      for_each(
          std::begin(storage_), std::end(storage_), [&, this, i = size_type(0)](auto &f) mutable {
            f += inverse_time_scale *
                 (weights[i] * density *
                      (one + three * dot(discrete_velocities[i], velocity()) +
                       nine_halves * sqr(dot(discrete_velocities[i], velocity)) -
                       three_halves * dot(velocity, velocity)) -
                  f[i]);
            ++i;
          });
    }

    void
    collide_vertical(Inverse_Time_Scale inverse_time_scale, Density density, Velocity velocity) {
      [&, this ]<std::size_t... I>(index_sequence<I...>) {
        (
            [&, this] {
              storage_[I] += inverse_time_scale *
                             (weights[I] * density *
                                  (one + three * dot(discrete_velocities[I], velocity()) +
                                   nine_halves * sqr(dot(discrete_velocities[I], velocity)) -
                                   three_halves * dot(velocity, velocity)) -
                              storage_[I]);
            }(),
            ...);
      }
      (make_index_sequence<Storage::size()>());
    }

    void
    collide_horizontal(Inverse_Time_Scale inverse_time_scale, Density density, Velocity velocity) {
      [&, this ]<std::size_t... I>(index_sequence<I...>) {
        unroll_horizontally([&, this] {
          return storage_[I] += inverse_time_scale *
                                (weights[I] * density *
                                     (one + three * dot(discrete_velocities[I], velocity()) +
                                      nine_halves * sqr(dot(discrete_velocities[I], velocity)) -
                                      three_halves * dot(velocity, velocity)) -
                                 storage_[I]);
        }()...);
      }
      (make_index_sequence<Storage::size()>());
    }

    void
    set_equilibrium(const Density &density, const Velocity &velocity) {
      [&, this ]<std::size_t... I>(index_sequence<I...>) {
        (
            [&, this] {
              storage_[I] = weights[I] * density *
                            (one + three * dot(discrete_velocities[I], velocity) +
                             nine_halves * sqr(dot(discrete_velocities[I], velocity)) -
                             three_halves * dot(velocity, velocity));
            }(),
            ...);
      }
      (make_index_sequence<Storage::size()>());
    }

    static constexpr Velocity_Distribution
    equilibrium(Density density, Velocity velocity) {
      return [&]<std::size_t... Index>(index_sequence<Index...>) {
        return Velocity_Distribution{weights[Index] * density *
                                     (one + three * dot(discrete_velocities[Index], velocity) +
                                      nine_halves * sqr(dot(discrete_velocities[Index], velocity)) -
                                      three_halves * dot(velocity, velocity))...};
      }
      (make_index_sequence<Storage::size()>());
    }

    friend constexpr Velocity_Distribution
    operator+(const Velocity_Distribution &f0, const Velocity_Distribution &f1) {
      return Velocity_Distribution{f0.storage_ + f1.storage_};
    }

    friend constexpr Velocity_Distribution
    operator-(const Velocity_Distribution &f0, const Velocity_Distribution &f1) {
      return Velocity_Distribution{f0.storage_ - f1.storage_};
    }

    friend constexpr Velocity_Distribution
    operator*(const Velocity_Distribution &f, Value_Type s) {
      return Velocity_Distribution{f.storage_ * s};
    }

    friend constexpr Velocity_Distribution
    operator*(Value_Type s, const Velocity_Distribution &f) {
      return Velocity_Distribution{s * f.storage_};
    }

    friend constexpr Velocity_Distribution
    operator/(const Velocity_Distribution &f, Value_Type s) {
      return Velocity_Distribution{f.storage_ / s};
    }

  private:
    json
    get_json() const override {
      json j = storage_;
      return j;
    }

    void
    set_json(const json &j) override {
      storage_ = j;
    }

    Storage storage_{};
  };

} // end of namespace lbm::D2Q9
