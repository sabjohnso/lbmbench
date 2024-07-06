//
// ... LBM Bench header files
//
#include <lbm/core/Expression.hpp>

//
// ... Testing header files
//
#include <catch2/catch_test_macros.hpp>

//
// ... Standard header files
//
#include <cmath>
#include <sstream>
#include <vector>

namespace lbm::core::testing {
  TEST_CASE("2 Dimensional") {
    constexpr double x1 = 4.0;
    constexpr double y1 = 5.0;
    const Euclidean coord1 = {x1, y1};

    constexpr double x2 = 6.0;
    constexpr double y2 = 7.0;
    const Euclidean coord2 = {x2, y2};

    SECTION("x-coordinate") {
      const X x{};

      SECTION("evaluation") {
        CHECK(x.eval(coord1) == x1);
        CHECK(x.eval(coord2) == x2);
      }

      SECTION("conversion to and from json") {
        json json_x = x;
        X x_from_json = json_x;
        CHECK(x == x_from_json);
      }

      SECTION("conversion to and from text") {
        std::stringstream ss;
        ss << x;
        X x_from_text{};
        ss >> x_from_text;
        CHECK(x == x_from_text);
      }
    }

    SECTION("y-coordinate") {
      const Y y{};

      SECTION("evaluation") {
        CHECK(y.eval(coord1) == y1);
        CHECK(y.eval(coord2) == y2);
      }

      SECTION("conversion to and from json") {
        json json_y = y;
        Y y_from_json = json_y;
        CHECK(y == y_from_json);
      }

      SECTION("conversion to and from text") {
        std::stringstream ss;
        ss << y;
        Y y_from_text{};
        ss >> y_from_text;
        CHECK(y == y_from_text);
      }
    }

    SECTION("z-coordinate") {
      Z z{};
      SECTION("evaluation") { CHECK_THROWS(z.eval(coord1)); }
    }

    SECTION("constant") {
      constexpr double a = 3.0;
      const Constant c{a};

      SECTION("evaluation") {
        CHECK(c.eval(coord1) == a);
        CHECK(c.eval(coord2) == a);
      }

      SECTION("conversion to and from json") {
        json json_c = c;
        Constant c_from_json = json_c;
        CHECK(c == c_from_json);
      }

      SECTION("conversion to and from text") {
        std::stringstream ss;
        ss << c;
        Constant c_from_text{};
        ss >> c_from_text;
        CHECK(c == c_from_text);
      }
    }

    SECTION("addition") {
      constexpr double a = 3.0;
      const Constant c{a};
      const X x{};
      Add add(c, x);

      SECTION("evalutation") {
        CHECK(add.eval(coord1) == a + x1);
        CHECK(add.eval(coord2) == a + x2);
      }

      SECTION("conversion to and from json") {
        json json_add = add;

        Add add_from_json = json_add;
        CHECK(add == add_from_json);
      }

      SECTION("conversion to and from text") {
        std::stringstream ss;
        ss << add;
        Add add_from_text{};
        ss >> add_from_text;
        CHECK(add == add_from_text);
      }
    }

    SECTION("subtraction") {
      constexpr double a = 3.0;
      const Constant c{a};
      const X x{};
      Subtract subtract(c, x);

      SECTION("evalutation") {
        CHECK(subtract.eval(coord1) == a - x1);
        CHECK(subtract.eval(coord2) == a - x2);
      }

      SECTION("conversion to and from json") {
        json json_subtract = subtract;

        Subtract subtract_from_json = json_subtract;
        CHECK(subtract == subtract_from_json);
      }

      SECTION("conversion to and from text") {
        std::stringstream ss;
        ss << subtract;
        Subtract subtract_from_text{};
        ss >> subtract_from_text;
        CHECK(subtract == subtract_from_text);
      }
    }

    SECTION("multiplication") {
      constexpr double a = 3.0;
      const Constant c{a};
      const X x{};
      Multiply multiply(c, x);

      SECTION("evalutation") {
        CHECK(multiply.eval(coord1) == a * x1);
        CHECK(multiply.eval(coord2) == a * x2);
      }

      SECTION("conversion to and from json") {
        json json_multiply = multiply;

        Multiply multiply_from_json = json_multiply;
        CHECK(multiply == multiply_from_json);
      }

      SECTION("conversion to and from text") {
        std::stringstream ss;
        ss << multiply;
        Multiply multiply_from_text{};
        ss >> multiply_from_text;
        CHECK(multiply == multiply_from_text);
      }
    }

    SECTION("divide") {
      constexpr double a = 3.0;
      const Constant c{a};
      const X x{};
      Divide divide(c, x);

      SECTION("evalutation") {
        CHECK(divide.eval(coord1) == a / x1);
        CHECK(divide.eval(coord2) == a / x2);
      }

      SECTION("conversion to and from json") {
        json json_divide = divide;

        Divide divide_from_json = json_divide;
        CHECK(divide == divide_from_json);
      }

      SECTION("conversion to and from text") {
        std::stringstream ss;
        ss << divide;
        Divide divide_from_text{};
        ss >> divide_from_text;
        CHECK(divide == divide_from_text);
      }
    }

    SECTION("power") {
      constexpr double a = 3.0;
      const Constant c{a};
      const X x{};
      Power power(c, x);

      SECTION("evalutation") {
        CHECK(power.eval(coord1) == std::pow(a, x1));
        CHECK(power.eval(coord2) == std::pow(a, x2));
      }

      SECTION("conversion to and from json") {
        json json_power = power;

        Power power_from_json = json_power;
        CHECK(power == power_from_json);
      }

      SECTION("conversion to and from text") {
        std::stringstream ss;
        ss << power;
        Power power_from_text{};
        ss >> power_from_text;
        CHECK(power == power_from_text);
      }
    }

    SECTION("atan2") {
      constexpr double a = 3.0;
      const Constant c{a};
      const X x{};
      Atan2 atan2(c, x);

      SECTION("evalutation") {
        CHECK(atan2.eval(coord1) == std::atan2(a, x1));
        CHECK(atan2.eval(coord2) == std::atan2(a, x2));
      }

      SECTION("conversion to and from json") {
        json json_atan2 = atan2;

        Atan2 atan2_from_json = json_atan2;
        CHECK(atan2 == atan2_from_json);
      }

      SECTION("conversion to and from text") {
        std::stringstream ss;
        ss << atan2;
        Atan2 atan2_from_text{};
        ss >> atan2_from_text;
        CHECK(atan2 == atan2_from_text);
      }
    }

    SECTION("negate") {
      Negate negate{X{}};
      SECTION("evaluation") {
        CHECK(negate.eval(coord1) == -x1);
        CHECK(negate.eval(coord2) == -x2);
      }
    }

    SECTION("reciprocal") {
      Reciprocal reciprocal{X{}};
      SECTION("evaluation") {
        CHECK(reciprocal.eval(coord1) == 1.0 / x1);
        CHECK(reciprocal.eval(coord2) == 1.0 / x2);
      }
    }

    SECTION("cos") {
      Cos cos{X{}};
      SECTION("evaluation") {
        CHECK(cos.eval(coord1) == std::cos(x1));
        CHECK(cos.eval(coord2) == std::cos(x2));
      }
    }

    SECTION("sin") {
      Sin sin{X{}};
      SECTION("evaluation") {
        CHECK(sin.eval(coord1) == std::sin(x1));
        CHECK(sin.eval(coord2) == std::sin(x2));
      }
    }

    SECTION("tan") {
      Tan tan{X{}};
      SECTION("evaluation") {
        CHECK(tan.eval(coord1) == std::tan(x1));
        CHECK(tan.eval(coord2) == std::tan(x2));
      }
    }

    SECTION("acos") {
      constexpr double a = 0.5;
      Acos acos{Constant{a}};
      SECTION("evaluation") { CHECK(acos.eval(coord1) == std::acos(a)); }
    }

    SECTION("asin") {
      constexpr double a = 0.5;
      Asin asin{Constant{a}};
      SECTION("evaluation") { CHECK(asin.eval(coord1) == std::asin(a)); }
    }

    SECTION("atan") {
      Atan atan{X{}};
      SECTION("evaluation") {
        CHECK(atan.eval(coord1) == std::atan(x1));
        CHECK(atan.eval(coord2) == std::atan(x2));
      }
    }

    SECTION("cosh") {
      Cosh cosh{X{}};
      SECTION("evaluation") {
        CHECK(cosh.eval(coord1) == std::cosh(x1));
        CHECK(cosh.eval(coord2) == std::cosh(x2));
      }
    }

    SECTION("sinh") {
      Sinh sinh{X{}};
      SECTION("evaluation") {
        CHECK(sinh.eval(coord1) == std::sinh(x1));
        CHECK(sinh.eval(coord2) == std::sinh(x2));
      }
    }

    SECTION("tanh") {
      Tanh tanh{X{}};
      SECTION("evaluation") {
        CHECK(tanh.eval(coord1) == std::tanh(x1));
        CHECK(tanh.eval(coord2) == std::tanh(x2));
      }
    }

    SECTION("acosh") {
      Acosh acosh{X{}};
      SECTION("evaluation") {
        CHECK(acosh.eval(coord1) == std::acosh(x1));
        CHECK(acosh.eval(coord2) == std::acosh(x2));
      }
    }

    SECTION("asinh") {
      Asinh asinh{X{}};
      SECTION("evaluation") {
        CHECK(asinh.eval(coord1) == std::asinh(x1));
        CHECK(asinh.eval(coord2) == std::asinh(x2));
      }
    }

    SECTION("atanh") {
      constexpr double a = 0.5;
      Atanh atanh{Constant{a}};
      SECTION("evaluation") { CHECK(atanh.eval(coord1) == std::atanh(a)); }
    }

    SECTION("exp") {
      Exp exp{X{}};
      SECTION("evaluation") {
        CHECK(exp.eval(coord1) == std::exp(x1));
        CHECK(exp.eval(coord2) == std::exp(x2));
      }
    }

    SECTION("log") {
      Log log{X{}};
      SECTION("evaluation") {
        CHECK(log.eval(coord1) == std::log(x1));
        CHECK(log.eval(coord2) == std::log(x2));
      }
    }

    SECTION("log10") {
      Log10 log10{X{}};
      SECTION("evaluation") {
        CHECK(log10.eval(coord1) == std::log10(x1));
        CHECK(log10.eval(coord2) == std::log10(x2));
      }
    }

    SECTION("sqrt") {
      Sqrt sqrt{X{}};

      SECTION("evaluation") {
        CHECK(sqrt.eval(coord1) == std::sqrt(x1));
        CHECK(sqrt.eval(coord2) == std::sqrt(x2));
      }

      SECTION("conversion to and from json") {
        json j = sqrt;
        Sqrt sqrt_from_json = j;
        CHECK(sqrt == sqrt_from_json);
      }
    }

    SECTION("cbrt") {
      Cbrt cbrt{X{}};
      SECTION("evaluation") {
        CHECK(cbrt.eval(coord1) == std::cbrt(x1));
        CHECK(cbrt.eval(coord2) == std::cbrt(x2));
      }
    }

    SECTION("square") {
      Square square{X{}};
      SECTION("evaluation") {
        CHECK(square.eval(coord1) == x1 * x1);
        CHECK(square.eval(coord2) == x2 * x2);
      }
      SECTION("conversion to and from JSON") {
        json j = square;
        Square square_from_json = j;
        CHECK(square == square_from_json);
      }
    }

    SECTION("cube") {
      Cube cube{X{}};
      SECTION("evaluation") {
        CHECK(cube.eval(coord1) == x1 * x1 * x1);
        CHECK(cube.eval(coord2) == x2 * x2 * x2);
      }
    }

    SECTION("heaviside") {
      Heaviside heaviside{X{}};
      SECTION("evaluation") {
        CHECK(heaviside.eval(coord1) == 1.0);
        CHECK(heaviside.eval(coord2) == 1.0);
        CHECK(heaviside.eval(-coord1) == 0.0);
        CHECK(heaviside.eval(-coord2) == 0.0);
      }
    }
  }

  TEST_CASE("3 Dimensional") {
    constexpr double x1 = 4.0;
    constexpr double y1 = 5.0;
    constexpr double z1 = 6.0;
    const Euclidean coord1 = {x1, y1, z1};

    constexpr double x2 = 7.0;
    constexpr double y2 = 8.0;
    constexpr double z2 = 9.0;
    const Euclidean coord2 = {x2, y2, z2};

    SECTION("x-coordinate") {
      const X x{};

      SECTION("evaluation") {
        CHECK(x.eval(coord1) == x1);
        CHECK(x.eval(coord2) == x2);
      }

      SECTION("conversion to and from json") {
        json json_x = x;
        X x_from_json = json_x;
        CHECK(x == x_from_json);
      }

      SECTION("conversion to and from text") {
        std::stringstream ss;
        ss << x;
        X x_from_text{};
        ss >> x_from_text;
        CHECK(x == x_from_text);
      }
    }

    SECTION("y-coordinate") {
      const Y y{};

      SECTION("evaluation") {
        CHECK(y.eval(coord1) == y1);
        CHECK(y.eval(coord2) == y2);
      }

      SECTION("conversion to and from json") {
        json json_y = y;
        Y y_from_json = json_y;
        CHECK(y == y_from_json);
      }

      SECTION("conversion to and from text") {
        std::stringstream ss;
        ss << y;
        Y y_from_text{};
        ss >> y_from_text;
        CHECK(y == y_from_text);
      }
    }

    SECTION("z-coordinate") {
      const Z z{};

      SECTION("evaluation") {
        CHECK(z.eval(coord1) == z1);
        CHECK(z.eval(coord2) == z2);
      }

      SECTION("conversion to and from json") {
        json json_z = z;
        Z z_from_json = json_z;
        CHECK(z == z_from_json);
      }

      SECTION("conversion to and from text") {
        std::stringstream ss;
        ss << z;
        Z z_from_text{};
        ss >> z_from_text;
        CHECK(z == z_from_text);
      }
    }
  }

  TEST_CASE("JSON Expressions") {
    const double a = 3.0;
    const double b = 4.0;

    const json json_expr = {
        {"sqrt",
         {{"add",
           {{{"square", {{"subtract", {"x", a}}}}}, {{"square", {{"subtract", {"y", b}}}}}}}}}};

    auto expr = parse_json_expr(json_expr);

    const Euclidean coord = {0.0, 0.0};
    CHECK(expr.eval(coord) == 5.0);
  }

} // end of namespace lbm::core::testing
