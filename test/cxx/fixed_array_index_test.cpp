//
// ... LBM Benchmarks header files
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

//
// ... Standard header files
//
#include <string>

namespace lbm::testing {
  using namespace std::literals;

  TEST_CASE("Fixed Array Index") {

    constexpr size_type a{3};
    constexpr size_type b{4};
    constexpr Fixed_Array_Index idx{a, b};

    SECTION("array access") {

      STATIC_REQUIRE(idx[0] == a);
      STATIC_REQUIRE(idx[1] == b);
    }

    SECTION("bounds checking array access") {
      CHECK(idx.at(0) == a);
      CHECK(idx.at(1) == b);
      CHECK_THROWS(idx.at(2));
    }

    SECTION("conversion to and from JSON") {
      nlohmann::json expected{{"FixedArrayIndex", {a, b}}};
      nlohmann::json json_idx = idx;
      Fixed_Array_Index<2> idx_from_json(expected);

      CHECK(json_idx == expected);
      CHECK(idx_from_json == idx);
    }

    SECTION("conversion to and from strings") {
      Fixed_Array_Index<2> idx_from_string{};
      std::stringstream ss;
      ss << idx;
      ss >> idx_from_string;
      CHECK(idx == idx_from_string);
    }
  }

} // end of namespace lbm::testing
