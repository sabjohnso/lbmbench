//
// ... LBM Bench header files
//
#include <lbmbench/utility.hpp>

//
// ... Testing header files
//
#include <catch2/catch_test_macros.hpp>

//
// ... Standard header files
//
#include <array>
#include <cmath>
#include <sstream>

namespace lbm::testing {
  TEST_CASE("Two Dimensional Obstacle") {
    using std::pow;
    constexpr double radius = 4.0;
    const Euclidean center{10.0, 20.0};

    const Obstacle circle = pow(radius, 2.0) - pow(x - center[0], 2.0) - pow(y - center[1], 2.0);

    SECTION("Contains points inside the circle") {
      CHECK(circle.contains(center));
      const Euclidean point1 = center + Euclidean{radius - 1, 0.0};
      const Euclidean point2 = center + Euclidean{-(radius - 1), 0.0};
      const Euclidean point3 = center + Euclidean{0.0, radius - 1};
      const Euclidean point4 = center + Euclidean{0.0, -(radius - 1)};

      CHECK(circle.contains(center));
      CHECK(circle.contains(point1));
      CHECK(circle.contains(point2));
      CHECK(circle.contains(point3));
      CHECK(circle.contains(point4));
    }

    SECTION("Does not contain points outside of circle") {
      const Euclidean point1 = center + Euclidean{radius + 1, 0.0};
      const Euclidean point2 = center + Euclidean{-(radius + 1), 0.0};
      const Euclidean point3 = center + Euclidean{0.0, radius + 1};
      const Euclidean point4 = center + Euclidean{0.0, -(radius + 1)};

      CHECK(!circle.contains(point1));
      CHECK(!circle.contains(point2));
      CHECK(!circle.contains(point3));
      CHECK(!circle.contains(point4));
    }

    SECTION("Conversion to and from JSON") {
      json json_circle = circle;
      Obstacle circle_from_json = json_circle;
      CHECK(circle == circle_from_json);
    }

    SECTION("Conversion to and from text") {
      std::stringstream ss{};
      ss << circle;
      Obstacle circle_from_text{};
      ss >> circle_from_text;
      CHECK(circle == circle_from_text);
    }
  }

  TEST_CASE("Multiple Obstacles") {
    constexpr double radius = 4.0;
    const Euclidean center{10.0, 20.0};
    const Euclidean origin{0.0, 0.0};
    const Obstacle circle = pow(radius, 2.0) - pow(x - center[0], 2.0) - pow(y - center[1], 2.0);
    const Obstacle square = pow(radius, 2.0) - pow(x, 2.0) - pow(y, 2.0);

    const Obstacles obstacles{circle, square};

    SECTION("Contains points in the circle or the square") {
      CHECK(obstacles.contains(center));
      CHECK(obstacles.contains(origin));
    }

    SECTION("Does not contain points outside of both the point and circle") {
      const Euclidean point{1000.0, 1000.0};
      CHECK(!circle.contains(point));
      CHECK(!square.contains(point));
      CHECK(!obstacles.contains(point));
    }

    SECTION("Conversion to and from JSON") {
      json json_obstacles = obstacles;
      Obstacles obstacles_from_json = json_obstacles;
      CHECK(obstacles == obstacles_from_json);
    }

    SECTION("Conversion to and from text") {
      std::stringstream ss{};
      ss << obstacles;
      Obstacles obstacles_from_text{};
      ss >> obstacles_from_text;
      CHECK(obstacles == obstacles_from_text);
    }
  }
} // end of namespace lbm::testing
