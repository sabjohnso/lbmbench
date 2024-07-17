//
// ... LBM Bench header files
//
#include <lbm/D2Q9/Node.hpp>

//
// ... Testing header files
//
#include <catch2/catch_test_macros.hpp>

//
// ... Standard header files
//
#include <sstream>

namespace lbm::D2Q9::testing {
  TEST_CASE("Node") {
    Node<double> node{};

    SECTION("Conversion to and from JSON") {
      json json_node = node;
      Node<double> node_from_json = json_node;
      CHECK(node == node_from_json);
    }

    SECTION("Conversion to and from text") {
      std::stringstream ss{};
      ss << node;
      Node<double> node_from_text{};
      ss >> node_from_text;
      CHECK(node == node_from_text);
    }
  }

} // end of namespace lbm::D2Q9::testing
