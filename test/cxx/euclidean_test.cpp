//
// ... LBM Bench header files
//
#include <lbm/core/Euclidean.hpp>

//
// ... Testing header files
//
#include <catch2/catch_test_macros.hpp>

namespace lbm::core::testing {

  TEST_CASE("2 Dimensional Euclidean Vector") {
    constexpr double u0 = 2.0;
    constexpr double u1 = 3.0;
    const Euclidean u{u0, u1};

    constexpr double v0 = 4.0;
    constexpr double v1 = 5.0;
    const Euclidean v{v0, v1};

    constexpr double s = 6.0;

    SECTION("Element Access") {
      CHECK(u[0] == u0);
      CHECK(u[1] == u1);
      CHECK(u.size() == 2);
    }

    SECTION("Addition") {
      const auto w = u + v;
      CHECK(w[0] == u0 + v0);
      CHECK(w[1] == u1 + v1);
    }

    SECTION("Right Scalar Multiplication") {
      const auto w = u * s;
      CHECK(w[0] == u0 * s);
      CHECK(w[1] == u1 * s);
    }

    SECTION("Left Scalar Multiplication") {
      const auto w = s * u;
      CHECK(w[0] == u0 * s);
      CHECK(w[1] == u1 * s);
    }

    SECTION("Inner Product") {
      const auto x = dot(u, v);
      CHECK(x == u0 * v0 + u1 * v1);
    }

    SECTION("Conversion to and from JSON") {
      json json_u = u;
      Euclidean u_from_json = json_u;
      CHECK(u == u_from_json);
    }

    SECTION("Conversion to and from text") {
      std::stringstream ss{};
      ss << u;
      Euclidean u_from_text{};
      ss >> u_from_text;
      CHECK(u == u_from_text);
    }
  }

  TEST_CASE("3 Dimensional Euclidean Vector") {}

} // end of namespace lbm::core::testing
