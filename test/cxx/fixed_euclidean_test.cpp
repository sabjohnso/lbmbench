//
// ... LBM Bench header files
//
#include <lbm/core/Fixed_Euclidean.hpp>

//
// ... Testing header files
//
#include <catch2/catch_test_macros.hpp>

namespace lbm::core::testing {
  TEST_CASE("Fixed_Euclidean 2D") {
    constexpr double a = 3.0;
    constexpr double b = 4.0;
    constexpr double c = 5.0;
    constexpr double d = 6.0;
    constexpr Fixed_Euclidean u{a, b};
    constexpr Fixed_Euclidean v{c, d};

    SECTION("array access") {
      CHECK(u[0] == a);
      CHECK(u[1] == b);
      CHECK(v[0] == c);
      CHECK(v[1] == d);
    }

    SECTION("addition") {
      constexpr auto w = u + v;
      CHECK(w[0] == a + c);
      CHECK(w[1] == b + d);
    }

    SECTION("left scaling") {
      constexpr auto w = c * u;
      CHECK(w[0] == c * a);
      CHECK(w[1] == c * b);
    }

    SECTION("right scaling") {
      constexpr auto w = u * c;
      CHECK(w[0] == a * c);
      CHECK(w[1] == b * c);
    }

    SECTION("right inverse scaling") {
      constexpr auto w = u / c;
      CHECK(w[0] == a / c);
      CHECK(w[1] == b / c);
    }

    SECTION("inner product") {
      constexpr auto e = dot(u, v);
      CHECK(e == a * c + b * d);
    }

    SECTION("conversion to and from json") {
      json json_u = u;
      Fixed_Euclidean<double, 2> u_from_json = json_u;
      CHECK(u == u_from_json);
    }

    SECTION("conversion to and from text") {
      std::stringstream ss{};
      ss << u;
      Fixed_Euclidean<double, 2> u_from_text{};
      ss >> u_from_text;
      CHECK(u == u_from_text);
    }
  }
} // end of namespace lbm::core::testing
