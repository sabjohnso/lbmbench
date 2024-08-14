//
// ... LBM Bench header files
//
#include <lbm/config.hpp>
#include <lbm/core/Input.hpp>

//
// ... Third-party header files
//
#include <nlohmann/json-schema.hpp>

//
// ... Testing header files
//
#include <catch2/catch_test_macros.hpp>

//
// ... Standard header files
//
#include <fstream>
#include <sstream>

namespace lbm::core::testing {
  using nlohmann::json_schema::json_validator;

  TEST_CASE("2 Dimensional Input") {
    constexpr auto kernel{Kernel::D2Q9};
    constexpr auto float_type{Float_Type::FLOAT32};
    constexpr double time_scale{0.1};
    constexpr size_type num_steps{10};
    constexpr double density{1.0};
    constexpr double viscosity{0.01};
    constexpr double u0{2.0};
    constexpr double v0{3.0};
    constexpr double width{200.0};
    constexpr double height{100.0};
    constexpr double lattice_spacing{0.5};
    constexpr double inlet_speed{4.0};
    constexpr double outlet_speed{4.0};
    constexpr double radius{5.0};
    const Euclidean velocity{u0, v0};
    const Euclidean center0{50.0, 60.0};
    const Euclidean center1{50.0, 40.0};
    const Euclidean point{50.0, 50.0};

    Input input{
        kernel,
        float_type,
        time_scale,
        num_steps,
        Lattice{Bounding_Box{width, height}, lattice_spacing},
        Initial_Conditions{Initial_Density{density}, Initial_Velocity{constant(u0), constant(v0)}},
        Boundary_Conditions{Inlet{Boundary_ID::Left, inlet_speed},
                            Outlet{Boundary_ID::Right, outlet_speed},
                            Wall{Boundary_ID::Bottom},
                            Wall{Boundary_ID::Top}},
        Obstacles{square(radius) - (square(x - center0[0]) + square(y - center0[1])),
                  square(radius) - (square(x - center1[0]) + square(y - center1[1]))},
        viscosity};

    SECTION("Schema Validation") {
      const json schema = [] {
        std::ifstream ifs{lbm::config::schema_location_testing};
        return json::parse(ifs);
      }();
      json_validator validator(schema);
      validator.validate(json(input));
    }

    SECTION("Equality comparision") {
      CHECK(input == input);
      CHECK(input != Input{});
    }

    SECTION("Density") { CHECK(input.density(point) == density); }

    SECTION("Velocity") { CHECK(input.velocity(point) == velocity); }

    SECTION("Velocity") {
      CHECK(input.is_obstacle(center0));
      CHECK(input.is_obstacle(center1));
      CHECK(!input.is_obstacle(point));
    }

    SECTION("Shape") {
      CHECK(input.ndims() == 2);
      CHECK(input.nnodes(0) == std::ceil(width / lattice_spacing));
      CHECK(input.nnodes(1) == std::ceil(height / lattice_spacing));
    }

    SECTION("Conversion to and from JSON") {

      json json_input = input;
      Input input_from_json = json_input;
      CHECK(input == input_from_json);
    }

    SECTION("Conversion to and from text") {
      std::stringstream ss{};
      ss << input;
      Input input_from_text{};
      ss >> input_from_text;
      CHECK(input == input_from_text);
    }
  }

  TEST_CASE("3 Dimensional Input") {}
} // end of namespace lbm::core::testing
