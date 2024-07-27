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
      const std::vector args = {"exec-path", "--help"};
      const int argc = std::size(args);
      CHECK_THROWS_AS(Runtime_Config(argc, std::data(args)), Help_Request);
    }

    SECTION("Version Request") {
      const std::vector args = {"exec-path", "--version"};
      const int argc = std::size(args);
      CHECK_THROWS_AS(Runtime_Config(argc, std::data(args)), Version_Request);
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
      const std::vector args = {"exec-path", "--input", lbm::config::invalid_input_path};
      const int argc = std::size(args);
      CHECK_THROWS_AS(Runtime_Config(argc, std::data(args)), Bad_Input);
    }

    SECTION("Valid Input") {
      const std::vector args = {"exec-path", "--input", lbm::config::valid_input_path};
      const int argc = std::size(args);
      CHECK_NOTHROW(Runtime_Config(argc, std::data(args)));
    }
  }

} // namespace lbm::app::testing
