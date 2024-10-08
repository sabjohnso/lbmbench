//
// ... LBM Bench header files
//
#include <lbm/core/Array2.hpp>
#include <lbm/core/forall.hpp>

//
// ... Testing header files
//
#include <catch2/catch_test_macros.hpp>

namespace lbm::core::testing {

  TEST_CASE("Cell Array") {
    constexpr size_type nx = 4;
    constexpr size_type ny = 5;
    constexpr size_type nxm1 = nx - 1;
    constexpr size_type nym1 = ny - 1;
    Array2<int> array{Lexical{Shape{nx, ny}}, 0};
    std::fill(std::begin(array), std::end(array), 0);

    SECTION("Left Boundary Iterator") {
      std::fill(array.begin(left), array.end(left), 1);
      for (size_type j = 1; j < nym1; ++j) {
        CHECK(array(0, j) == 1);
      }

      std::for_each(array.cbegin(right), array.cend(right), [&](auto elem) {
        CHECK(static_cast<const int &>(elem) == 0);
      });

      std::for_each(array.cbegin(bottom), array.cend(bottom), [&](auto elem) {
        CHECK(static_cast<const int &>(elem) == 0);
      });

      std::for_each(array.cbegin(top), array.cend(top), [&](auto elem) {
        CHECK(static_cast<const int &>(elem) == 0);
      });

      std::for_each(
          array.cbegin(interior), array.cend(interior), [](auto elem) { CHECK(elem == 0); });
    }

    SECTION("Right Boundary Iterator") {
      std::fill(array.begin(right), array.end(right), 1);
      for (size_type j = 1; j < nym1; ++j) {
        CHECK(array(nxm1, j) == 1);
      }

      std::for_each(array.cbegin(left), array.cend(left), [&](auto elem) {
        CHECK(static_cast<const int &>(elem) == 0);
      });

      std::for_each(array.cbegin(bottom), array.cend(bottom), [&](auto elem) {
        CHECK(static_cast<const int &>(elem) == 0);
      });

      std::for_each(array.cbegin(top), array.cend(top), [&](auto elem) {
        CHECK(static_cast<const int &>(elem) == 0);
      });
      std::for_each(
          array.cbegin(interior), array.cend(interior), [](auto elem) { CHECK(elem == 0); });
    }

    SECTION("Bottom Boundary Iterator") {
      std::fill(array.begin(bottom), array.end(bottom), 1);
      for (size_type i = 1; i < nxm1; ++i) {
        CHECK(array(i, 0) == 1);
      }

      std::for_each(array.cbegin(right), array.cend(right), [&](auto elem) {
        CHECK(static_cast<const int &>(elem) == 0);
      });

      std::for_each(array.cbegin(left), array.cend(left), [&](auto elem) {
        CHECK(static_cast<const int &>(elem) == 0);
      });

      std::for_each(array.cbegin(top), array.cend(top), [&](auto elem) {
        CHECK(static_cast<const int &>(elem) == 0);
      });

      std::for_each(
          array.cbegin(interior), array.cend(interior), [](auto elem) { CHECK(elem == 0); });
    }

    SECTION("Top Boundary Iterator") {
      std::fill(array.begin(top), array.end(top), 1);
      for (size_type i = 1; i < nxm1; ++i) {
        std::cout << "i: " << i << std::endl;
        CHECK(array(i, nym1) == 1);
      }

      std::for_each(array.cbegin(right), array.cend(right), [&](auto elem) {
        CHECK(static_cast<const int &>(elem) == 0);
      });

      std::for_each(array.cbegin(left), array.cend(left), [&](auto elem) {
        CHECK(static_cast<const int &>(elem) == 0);
      });

      std::for_each(array.cbegin(bottom), array.cend(bottom), [&](auto elem) {
        CHECK(static_cast<const int &>(elem) == 0);
      });

      std::for_each(
          array.cbegin(interior), array.cend(interior), [](auto elem) { CHECK(elem == 0); });
    }

    SECTION("Interior Iterator") {
      std::fill(array.begin(interior), array.end(interior), 1);
      for (size_type i = 1; i < nxm1; ++i) {
        for (size_type j = 1; j < nym1; ++j) {
          CHECK(array(i, j) == 1);
        }
      }

      std::for_each(array.cbegin(right), array.cend(right), [&](auto elem) {
        CHECK(static_cast<const int &>(elem) == 0);
      });

      std::for_each(array.cbegin(left), array.cend(left), [&](auto elem) {
        CHECK(static_cast<const int &>(elem) == 0);
      });

      std::for_each(array.cbegin(bottom), array.cend(bottom), [&](auto elem) {
        CHECK(static_cast<const int &>(elem) == 0);
      });

      std::for_each(array.cbegin(top), array.cend(top), [&](auto elem) {
        CHECK(static_cast<const int &>(elem) == 0);
      });
    }

    SECTION("Forall function") {
      forall(array.begin(left), array.end(left), [](auto it) { it(1, 0) = 1; });
      for (size_type j = 1; j < nym1; ++j) {
        CHECK(array(1, j) == 1);
      }
    }
  }

} // namespace lbm::core::testing
