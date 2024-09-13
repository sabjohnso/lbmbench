//
// ... LBM Bench header files
//
#include <lbm/core/Scalar_Quantity.hpp>

//
// ... Testing header files
//
#include <catch2/catch_test_macros.hpp>

namespace lbm::core::testing {

  TEST_CASE("Scalar Quantity") {
    constexpr double a = 3.0;
    constexpr double b = 4.0;

    SECTION("Additive Operators") {
      constexpr Speed<double> s1{a};
      constexpr Speed<double> s2{b};

      SECTION("Addition") {
        constexpr auto s3 = s1 + s2;
        STATIC_CHECK(std::same_as<std::remove_cvref_t<decltype(s3)>, Speed<double>>);
        STATIC_CHECK(s3.value() == a + b);
      }

      SECTION("Subtraction") {
        constexpr auto s3 = s1 - s2;
        STATIC_CHECK(std::same_as<std::remove_cvref_t<decltype(s3)>, Speed<double>>);
        STATIC_CHECK(s3.value() == a - b);
      }

      SECTION("Negation") {
        constexpr auto s3 = -s1;
        STATIC_CHECK(std::same_as<std::remove_cvref_t<decltype(s3)>, Speed<double>>);
        STATIC_CHECK(s3.value() == -a);
      }
    }

    SECTION("Multiplicative_Operators") {
      constexpr Length<double> x{a};
      constexpr Time<double> t{b};

      SECTION("Multiplication") {
        constexpr auto result = x * t;
        STATIC_CHECK(
            std::same_as<std::remove_cvref_t<decltype(result)>, Scalar_Quantity<double, 1, 0, 1>>);
        STATIC_CHECK(result.value() == a * b);
      }

      SECTION("Division") {
        constexpr auto result = x / t;
        STATIC_CHECK(std::same_as<std::remove_cvref_t<decltype(result)>, Speed<double>>);
        STATIC_CHECK(result.value() == a / b);
      };
    }

    SECTION("Messures") {
      SECTION("Area") {
        STATIC_CHECK(std::same_as<Area<double>, decltype(Length<double>{} * Length<double>{})>);
      }

      SECTION("Volume") {
        STATIC_CHECK(
            std::same_as<Volume<double>,
                         decltype(Length<double>{} * Length<double>{} * Length<double>{})>);
      }
      SECTION("Speed") {
        STATIC_CHECK(std::same_as<Speed<double>, decltype(Length<double>{} / Time<double>{})>);
      }

      SECTION("Density") {
        STATIC_CHECK(std::same_as<Density<double>, decltype(Mass<double>{} / Volume<double>{})>);
      }

      SECTION("Dimensionless") {
        STATIC_CHECK(
            std::same_as<Dimensionless<double>, decltype(Length<double>{} / Length<double>{})>);
        STATIC_CHECK(
            std::same_as<Dimensionless<double>, decltype(Mass<double>{} / Mass<double>{})>);

        STATIC_CHECK(
            std::same_as<Dimensionless<double>, decltype(Time<double>{} / Time<double>{})>);
      }
    }
  }

} // namespace lbm::core::testing
