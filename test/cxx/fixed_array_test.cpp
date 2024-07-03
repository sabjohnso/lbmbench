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
#include <algorithm>

namespace lbm::testing {

  TEST_CASE("Fixed Array") {
    SECTION("default initialization") {
      Fixed_Array<double, Fixed_Lexical<2, 3, 4>> array{};
      CHECK(std::all_of(std::cbegin(array), std::cend(array), [](double x) { return x == 0.0; }));
    }

    SECTION("array access") {
      Fixed_Array<double, Fixed_Lexical<3, 3>> array{};
      CHECK(array.size() == 9);
      for (size_type i = 0; i < 3; ++i) {
        for (size_type j = 0; j < 3; ++j) {
          array[i, j] = double(i * 3 + j);
        }
      }
      std::for_each(
          std::begin(array), std::end(array), [i = size_type(0)](const double &x) mutable {
            CHECK(x == double(i));
            ++i;
          });
    }
    SECTION("fill") {
      Fixed_Array<double, Fixed_Lexical<3, 3>> array{};
      array.fill(4.0);
      std::for_each(std::begin(array), std::end(array), [](const auto x) { CHECK(x == 4.0); });
    }
  }
} // end of namespace lbm::testing
