#pragma once

//
// ... LBM Bench header files
//
#include <lbm/core/base_types.hpp>
#include <lbm/core/import.hpp>

namespace lbm::core {

  template <class Value, integer Length, integer Mass, integer Time>
  class Scalar_Quantity {
  public:
    using Value_Type = Value;
    using Reference = Value_Type &;
    using Const_Reference = const Value_Type &;

    constexpr Scalar_Quantity() = default;

    explicit constexpr Scalar_Quantity(Value_Type value)
        : value_{value} {};

    constexpr Const_Reference
    value() const {
      return value_;
    }

    Reference
    value() {
      return value_;
    }

    constexpr bool
    operator<=>(const Scalar_Quantity &x) const = default;

    constexpr friend Scalar_Quantity
    operator+(const Scalar_Quantity x, const Scalar_Quantity y) {
      return Scalar_Quantity{x.value_ + y.value_};
    }

    constexpr friend Scalar_Quantity
    operator-(const Scalar_Quantity x, const Scalar_Quantity y) {
      return Scalar_Quantity{x.value_ - y.value_};
    }

    constexpr friend Scalar_Quantity
    operator-(const Scalar_Quantity x) {
      return Scalar_Quantity{-x.value_};
    }

    template <class Value2,
              integer Length2,
              integer Mass2,
              integer Time2,
              typename Result = Scalar_Quantity<common_type_t<Value, Value2>,
                                                Length + Length2,
                                                Mass + Mass2,
                                                Time + Time2>>
    constexpr friend Result
    operator*(const Scalar_Quantity x, const Scalar_Quantity<Value2, Length2, Mass2, Time2> y) {
      return Result{x.value() * y.value()};
    }

    template <class Value2,
              integer Length2,
              integer Mass2,
              integer Time2,
              typename Result = Scalar_Quantity<common_type_t<Value, Value2>,
                                                Length - Length2,
                                                Mass - Mass2,
                                                Time - Time2>>
    constexpr friend Result
    operator/(const Scalar_Quantity x, const Scalar_Quantity<Value2, Length2, Mass2, Time2> y) {
      return Result{x.value() / y.value()};
    }

    template <class Value2, integer Length2, integer Mass2, integer Time2>
    friend class Scalar_Quantity;

  private:
    Value_Type value_{};
  };

  template <class Value>
  using Length = Scalar_Quantity<Value, 1, 0, 0>;

  template <class Value>
  using Mass = Scalar_Quantity<Value, 0, 1, 0>;

  template <class Value>
  using Time = Scalar_Quantity<Value, 0, 0, 1>;

  template <class Value>
  using Area = Scalar_Quantity<Value, 2, 0, 0>;

  template <class Value>
  using Volume = Scalar_Quantity<Value, 3, 0, 0>;

  template <class Value>
  using Density = Scalar_Quantity<Value, -3, 1, 0>;

  template <class Value>
  using Speed = Scalar_Quantity<Value, 1, 0, -1>;

  template <class Value>
  using Scalar_Momentum = Scalar_Quantity<Value, 1, 1, -1>;

  template <class Value>
  using Dimensionless = Scalar_Quantity<Value, 0, 0, 0>;

} // end of namespace lbm::core
