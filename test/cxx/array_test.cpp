//
// ... LBM Bench header files
//
#include <lbm/core/Array.hpp>

//
// ... Testing header files
//
#include <catch2/catch_test_macros.hpp>

//
// ... Standard header files
//
#include <sstream>

namespace lbm::core::testing {
  TEST_CASE("Array") {
    constexpr size_type nx = 2;
    constexpr size_type ny = 3;
    Array<double, 2> array{Lexical{Shape{nx, ny}}};

    SECTION("element access") {
      for (size_type i = 0; i < nx; ++i) {
        for (size_type j = 0; j < ny; ++j) {
          CHECK(array(i, j) == 0.0);
          CHECK(&array(i, j) == &array(Index{i, j}));
          array(i, j) = i * ny + j;
        }
      }
      std::for_each(
          std::begin(array), std::end(array), [&, i = size_type(0)](const auto &x) mutable {
            CHECK(&x == &array((i / ny) % nx, i % ny));
            CHECK(x == array((i / ny) % nx, i % ny));
            ++i;
          });
    }

    SECTION("conversion to and from JSON") {
      nlohmann::json json_array = array;
      Array<double, 2> array_from_json = json_array;
      CHECK(array == array_from_json);
    }

    SECTION("conversion to and from text") {
      std::stringstream ss;
      ss << array;
      Array<double, 2> array_from_text{};
      ss >> array_from_text;
    }
  }

} // namespace lbm::core::testing
