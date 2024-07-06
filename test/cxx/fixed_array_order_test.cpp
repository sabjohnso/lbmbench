//
// ... LBM Bench header files
//
#include <lbm/core/Fixed_Array_Index.hpp>
#include <lbm/core/Fixed_Lexical.hpp>

//
// ... Third-party header files
//
#include <nlohmann/json.hpp>

//
// ... Testing header files
//
#include <catch2/catch_test_macros.hpp>

namespace lbm::core::testing {

  TEST_CASE("Lexical") {
    SECTION("Degree 2") {
      using Order = Fixed_Lexical<2, 3>;

      SECTION("storage index") {
        CHECK(Order::storage_index(Fixed_Array_Index(0, 0)) == 0);
        CHECK(Order::storage_index(Fixed_Array_Index(0, 1)) == 1);
        CHECK(Order::storage_index(Fixed_Array_Index(0, 2)) == 2);
        CHECK(Order::storage_index(Fixed_Array_Index(1, 0)) == 3);
        CHECK(Order::storage_index(Fixed_Array_Index(1, 1)) == 4);
        CHECK(Order::storage_index(Fixed_Array_Index(1, 2)) == 5);
      }

      SECTION("array index") {
        CHECK(Order::array_index(0) == Fixed_Array_Index(0, 0));
        CHECK(Order::array_index(1) == Fixed_Array_Index(0, 1));
        CHECK(Order::array_index(2) == Fixed_Array_Index(0, 2));
        CHECK(Order::array_index(3) == Fixed_Array_Index(1, 0));
        CHECK(Order::array_index(4) == Fixed_Array_Index(1, 1));
        CHECK(Order::array_index(5) == Fixed_Array_Index(1, 2));
      }

      SECTION("conversion to and from JSON") {
        Order order{};
        nlohmann::json json_order = order;
        Order order_from_json = json_order;
        CHECK(order == order_from_json);
      }

      SECTION("conversion to and from text") {
        Order order{};
        std::stringstream ss;
        ss << order;
        Order order_from_stream{};
        ss >> order_from_stream;
        CHECK(order == order_from_stream);
      }
    }

    SECTION("Degree 3") {
      using Order = Fixed_Lexical<2, 3, 4>;
      SECTION("storage index") {
        CHECK(Order::storage_index(Fixed_Array_Index(0, 0, 0)) == 0);
        CHECK(Order::storage_index(Fixed_Array_Index(0, 0, 1)) == 1);
        CHECK(Order::storage_index(Fixed_Array_Index(0, 0, 2)) == 2);
        CHECK(Order::storage_index(Fixed_Array_Index(0, 0, 3)) == 3);
        CHECK(Order::storage_index(Fixed_Array_Index(0, 0, 1)) == 1);
        CHECK(Order::storage_index(Fixed_Array_Index(0, 1, 0)) == 4);
        CHECK(Order::storage_index(Fixed_Array_Index(1, 0, 0)) == 12);
        CHECK(Order::storage_index(Fixed_Array_Index(1, 2, 3)) == 23);
      }

      SECTION("array index") {
        CHECK(Order::array_index(0) == Fixed_Array_Index(0, 0, 0));
        CHECK(Order::array_index(1) == Fixed_Array_Index(0, 0, 1));
        CHECK(Order::array_index(2) == Fixed_Array_Index(0, 0, 2));
        CHECK(Order::array_index(3) == Fixed_Array_Index(0, 0, 3));
        CHECK(Order::array_index(1) == Fixed_Array_Index(0, 0, 1));
        CHECK(Order::array_index(4) == Fixed_Array_Index(0, 1, 0));
        CHECK(Order::array_index(12) == Fixed_Array_Index(1, 0, 0));
        CHECK(Order::array_index(23) == Fixed_Array_Index(1, 2, 3));
      }
    }
  }

} // end of namespace lbm::core::testing
