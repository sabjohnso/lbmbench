//
// ... LBM Bench header files
//
#include <lbm/utility.hpp>

//
// ... Testing header files
//
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

//
// ... Standard header files
//
#include <sstream>

namespace lbm::core::testing {
  using namespace lbm::D2Q9;

  TEST_CASE("D2Q9 Veleocity_Distribution") {
    using VD = Velocity_Distribution<double>;
    using Density = VD::Density;
    using Velocity = VD::Velocity;

    constexpr Velocity velocity{3.0, 4.0};
    constexpr Density density = 1.0;
    constexpr auto dist = VD::equilibrium(density, velocity);

    SECTION("conversion to and from JSON") {
      json json_dist = dist;
      Velocity_Distribution<double> dist_from_json = json_dist;
      CHECK(dist == dist_from_json);
    }

    SECTION("conversion to and from text") {
      std::stringstream ss{};
      ss << dist;
      Velocity_Distribution<double> dist_from_text{};
      ss >> dist_from_text;
      CHECK(dist == dist_from_text);
    }

    SECTION("properties") {
      constexpr auto dist_density = dist.density();
      REQUIRE_THAT(dist_density, Catch::Matchers::WithinAbs(density, 1.0e-12));

      constexpr auto dist_velocity = dist.velocity();
      REQUIRE_THAT(dist_velocity[0], Catch::Matchers::WithinAbs(velocity[0], 1.0E-12));
      REQUIRE_THAT(dist_velocity[1], Catch::Matchers::WithinAbs(velocity[1], 1.0E-12));
    }
  }

  TEST_CASE("D2Q9 Node") {
    Node<double> node{};

    SECTION("conversion to and from JSON") {
      json json_node = node;

      SECTION("conversion to and from JSON") {
        json json_node = node;
        Node<double> node_from_json = json_node;
        CHECK(node == node_from_json);
      }

      SECTION("conversion to and from text") {}
    }
  }

  TEST_CASE("D2Q9 Input") {
    D2Q9_Input input{
        Lattice{Bounding_Box{200.0, 100.0}, 1.0},
        Initial_Conditions{parse_json_expr(1.0), {parse_json_expr(2.0), parse_json_expr(3.0)}},
        {},
        {parse_json_expr({{"subtract",
                           {25,
                            {{"add",
                              {{{"square", {{"subtract", {"x", 50}}}}},
                               {{"square", {{"subtract", {"y", 50}}}}}}}}}}})},
        0.1};
  }

  TEST_CASE("D2Q9 State") {}

} // namespace lbm::core::testing
