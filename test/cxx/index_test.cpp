//
// ... LBM Bench header files
//
#include <lbmbench/utility.hpp>

//
// ... Third-party header files
//
#include <nlohmann/json.hpp>

//
// ... Testing header files
//
#include <catch2/catch_test_macros.hpp>

namespace lbm::testing {

  TEST_CASE("Index") {
    Index index{2, 3, 4};

    SECTION("element access") {
      CHECK(index[0] == 2);
      CHECK(index[1] == 3);
      CHECK(index[2] == 4);
    }

    SECTION("element access with bounds checking") {
      CHECK(index.at(0) == 2);
      CHECK(index.at(1) == 3);
      CHECK(index.at(2) == 4);
      CHECK_THROWS(index.at(4));
    }

    SECTION("conversion to and from JSON") {
      nlohmann::json json_index = index;
      Index<3> index_from_json = json_index;
      CHECK(index == index_from_json);
    }

    SECTION("conversion to and from text") {
      std::stringstream ss;
      ss << index;
      Index<3> index_from_text{};
      ss >> index_from_text;
    }
  }

} // namespace lbm::testing
