//
// ... LBM Bench header files
//
#include <lbm/app/Runtime_Config.hpp>
#include <lbm/exceptions/Help_Request.hpp>

//
// ... Testing header files
//
#include <catch2/catch_test_macros.hpp>

//
// ... Standard header files
//
#include <vector>

namespace lbm::app::testing {

  TEST_CASE("Runtime_Config") {
    SECTION("Requesting Help") {
      SECTION("With long flags") {
        const std::vector args = {"exec-path", "--help"};
        const int argc = std::size(args);
        CHECK_THROWS_AS(Runtime_Config(argc, std::data(args)), Help_Request);
      }

      SECTION("With long flags") {
        const std::vector args = {"exec-path", "-h"};
        const int argc = std::size(args);
        CHECK_THROWS_AS(Runtime_Config(argc, std::data(args)), Help_Request);
      }
    }

    SECTION("Version Request") {
      SECTION("With long flags") {
        const std::vector args = {"exec-path", "--version"};
        const int argc = std::size(args);

        CHECK_THROWS_AS(Runtime_Config(argc, std::data(args)), Version_Request);
      }

      SECTION("With long flags") {
        const std::vector args = {"exec-path", "-v"};
        const int argc = std::size(args);

        CHECK_THROWS_AS(Runtime_Config(argc, std::data(args)), Version_Request);
      }
    }

    SECTION("Bad Usage") {
      SECTION("Missing input path") {
        const std::vector args = {"exec-path"};
        const int argc = std::size(args);
        CHECK_THROWS_AS(Runtime_Config(argc, std::data(args)), Bad_Usage);
      }

      SECTION("Unkown option") {
        const std::vector args = {
            "exec-path", "--bad-argument", "--input", lbm::config::invalid_input_path};
        const int argc = std::size(args);
        CHECK_THROWS_AS(Runtime_Config(argc, std::data(args)), Bad_Usage);
      }
    }

    SECTION("Bad Input") {
      SECTION("With long flags") {
        const std::vector args = {"exec-path", "--input", lbm::config::invalid_input_path};
        const int argc = std::size(args);
        CHECK_THROWS_AS(Runtime_Config(argc, std::data(args)), Bad_Input);
      }

      SECTION("With short flags") {
        const std::vector args = {"exec-path", "-i", lbm::config::invalid_input_path};
        const int argc = std::size(args);
        CHECK_THROWS_AS(Runtime_Config(argc, std::data(args)), Bad_Input);
      }
    }

    SECTION("Valid Input") {
      SECTION("With long flags") {
        const std::vector args = {"exec-path", "--input", lbm::config::valid_input_path};
        const int argc = std::size(args);
        CHECK_NOTHROW(Runtime_Config(argc, std::data(args)));
      }

      SECTION("With short flags") {
        const std::vector args = {"exec-path", "-i", lbm::config::valid_input_path};
        const int argc = std::size(args);
        CHECK_NOTHROW(Runtime_Config(argc, std::data(args)));
      }
    }

    SECTION("Access to input data") {
      const json expected_input = [] {
        std::ifstream ifs{lbm::config::valid_input_path};
        return json::parse(ifs);
      }();

      const std::vector args = {"exec-path", "-i", lbm::config::valid_input_path};
      const int argc = std::size(args);
      Runtime_Config runtime_config{argc, std::data(args)};
      CHECK(expected_input == runtime_config.input());
    }
  }

} // namespace lbm::app::testing
