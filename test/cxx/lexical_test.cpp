//
// ... LBM Bench header files
//
#include <lbm/core/Lexical.hpp>

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
#include <iostream>

namespace lbm::core::testing {
  TEST_CASE("lexical") {
    SECTION("Degree 2") {
      Lexical order{Shape{2, 3}};

      SECTION("storage index") {
        CHECK(order.storage_index(Index(0, 0)) == 0);
        CHECK(order.storage_index(Index(0, 1)) == 1);
        CHECK(order.storage_index(Index(0, 2)) == 2);
        CHECK(order.storage_index(Index(1, 0)) == 3);
        CHECK(order.storage_index(Index(1, 1)) == 4);
        CHECK(order.storage_index(Index(1, 2)) == 5);
      }

      SECTION("array index") {
        CHECK(order.array_index(0) == Index(0, 0));
        CHECK(order.array_index(1) == Index(0, 1));
        CHECK(order.array_index(2) == Index(0, 2));
        CHECK(order.array_index(3) == Index(1, 0));
        CHECK(order.array_index(4) == Index(1, 1));
        CHECK(order.array_index(5) == Index(1, 2));
      }

      SECTION("conversion to and from JSON") {
        nlohmann::json json_order = order;
        Lexical<2> order_from_json = json_order;
        CHECK(order == order_from_json);
      }

      SECTION("conversion to and from text") {
        std::stringstream ss;
        ss << order;
        Lexical<2> order_from_text{};
        ss >> order_from_text;
        CHECK(order == order_from_text);
      }
    }
  }
} // namespace lbm::core::testing
