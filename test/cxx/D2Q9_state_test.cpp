//
// ... LBM Bench
//
#include <lbm/D2Q9/State.hpp>
#include <lbm/core/Input.hpp>

//
// ... Testing header files
//
#include <catch2/catch_test_macros.hpp>

//
// ... Standard header files
//
#include <sstream>

namespace lbm::D2Q9::testing {
  using namespace lbm::core;

  TEST_CASE("State") {
    constexpr double density = 1.0;
    constexpr double viscosity = 0.01;
    constexpr double u0 = 2.0;
    constexpr double v0 = 3.0;
    constexpr double width = 200.0;
    constexpr double height = 100.0;
    constexpr double lattice_spacing = 0.5;
    constexpr double inlet_speed = 4.0;
    constexpr double outlet_speed = 4.0;
    constexpr double radius = 5.0;
    const Euclidean velocity{u0, v0};
    const Euclidean center0{50.0, 60.0};
    const Euclidean center1{50.0, 40.0};
    const Euclidean point{50.0, 50.0};

    Input input{
        Lattice{Bounding_Box{width, height}, lattice_spacing},
        Initial_Conditions{Initial_Density{density}, Initial_Velocity{constant(u0), constant(v0)}},
        Boundary_Conditions{Inlet{Boundary_ID{Boundary::Lower, Boundary::NA}, inlet_speed},
                            Outlet{Boundary_ID{Boundary::Upper, Boundary::NA}, outlet_speed},
                            Wall{Boundary_ID{Boundary::NA, Boundary::Lower}},
                            Wall{Boundary_ID{Boundary::NA, Boundary::Upper}}},
        Obstacles{square(radius) - (square(x - center0[0]) + square(y - center0[1])),
                  square(radius) - (square(x - center1[0]) + square(y - center1[1]))},
        viscosity};
    State<double> state{input};

    SECTION("Conversion to and from JSON") {
      json json_state = state;
      State<double> state_from_json = json_state;
      CHECK(state == state_from_json);
    }

    SECTION("Conversion to and from text") {
      std::stringstream ss{};
      ss << state;
      State<double> state_from_text{};
      ss >> state_from_text;
      CHECK(state == state_from_text);
    }
  }

} // end of namespace lbm::D2Q9::testing
