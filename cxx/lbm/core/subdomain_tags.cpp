//
// ... LBM Bench header files
//
#include <lbm/core/subdomain_tags.hpp>

namespace lbm::core {

  //
  // ... Interior
  //
  void
  to_json(json &j, const Interior &) {
    j = "interior";
  }

  void
  from_json([[maybe_unused]] const json &j, Interior &) {
    assert(j == "interior");
  }

  //
  // ... Faces 2D and 3D
  //

  void
  to_json(json &j, const Left &) {
    j = "left";
  }

  void
  from_json([[maybe_unused]] const json &j, Left &) {
    assert(j == "left");
  }

  void
  to_json(json &j, const Right &) {
    j = "right";
  }

  void
  from_json([[maybe_unused]] const json &j, Right &) {
    assert(j == "right");
  }

  void
  to_json(json &j, const Bottom &) {
    j = "bottom";
  }

  void
  from_json([[maybe_unused]] const json &j, Bottom &) {
    assert(j == "bottom");
  }
  void
  to_json(json &j, const Top &) {
    j = "top";
  }

  void
  from_json([[maybe_unused]] const json &j, Top &) {
    assert(j == "top");
  }
  void
  to_json(json &j, const Back &) {
    j = "back";
  }

  void
  from_json([[maybe_unused]] const json &j, Back &) {
    assert(j == "back");
  }
  void
  to_json(json &j, const Front &) {
    j = "front";
  }

  void
  from_json([[maybe_unused]] const json &j, Front &) {
    assert(j == "front");
  }

  //
  // ... Corners 2D
  //
  void
  to_json(json &j, const Left_Bottom_Corner &) {
    j = "left_bottom_corner";
  }

  void
  from_json([[maybe_unused]] const json &j, Left_Bottom_Corner &) {
    assert(j == "left_bottom_corner");
  }
  void
  to_json(json &j, const Left_Top_Corner &) {
    j = "left_top_corner";
  }

  void
  from_json([[maybe_unused]] const json &j, Left_Top_Corner &) {
    assert(j == "left_top_corner");
  }
  void
  to_json(json &j, const Right_Bottom_Corner &) {
    j = "right_bottom_corner";
  }

  void
  from_json([[maybe_unused]] const json &j, Right_Bottom_Corner &) {
    assert(j == "right_bottom_corner");
  }
  void
  to_json(json &j, const Right_Top_Corner &) {
    j = "right_top_corner";
  }

  void
  from_json([[maybe_unused]] const json &j, Right_Top_Corner &) {
    assert(j == "right_top_corner");
  }

  //
  // ... Edges 3D
  //

  void
  to_json(json &j, const Left_Bottom_Edge &) {
    j = "left_bottom_edge";
  }

  void
  from_json([[maybe_unused]] const json &j, Left_Bottom_Edge &) {
    assert(j == "left_bottom_edge");
  }
  void
  to_json(json &j, const Left_Top_Edge &) {
    j = "left_top_edge";
  }

  void
  from_json([[maybe_unused]] const json &j, Left_Top_Edge &) {
    assert(j == "left_top_edge");
  }
  void
  to_json(json &j, const Right_Bottom_Edge &) {
    j = "right_bottom_edge";
  }

  void
  from_json([[maybe_unused]] const json &j, Right_Bottom_Edge &) {
    assert(j == "right_bottom_edge");
  }
  void
  to_json(json &j, const Right_Top_Edge &) {
    j = "right_top_edge";
  }

  void
  from_json([[maybe_unused]] const json &j, Right_Top_Edge &) {
    assert(j == "right_top_edge");
  }
  void
  to_json(json &j, const Left_Back_Edge &) {
    j = "left_back_edge";
  }

  void
  from_json([[maybe_unused]] const json &j, Left_Back_Edge &) {
    assert(j == "left_back_edge");
  }
  void
  to_json(json &j, const Left_Front_Edge &) {
    j = "left_front_edge";
  }

  void
  from_json([[maybe_unused]] const json &j, Left_Front_Edge &) {
    assert(j == "left_front_edge");
  }
  void
  to_json(json &j, const Right_Back_Edge &) {
    j = "right_back_edge";
  }

  void
  from_json([[maybe_unused]] const json &j, Right_Back_Edge &) {
    assert(j == "right_back_edge");
  }
  void
  to_json(json &j, const Right_Front_Edge &) {
    j = "right_front_edge";
  }

  void
  from_json([[maybe_unused]] const json &j, Right_Front_Edge &) {
    assert(j == "right_front_edge");
  }
  void
  to_json(json &j, const Bottom_Back_Edge &) {
    j = "bottom_back_edge";
  }

  void
  from_json([[maybe_unused]] const json &j, Bottom_Back_Edge &) {
    assert(j == "bottom_back_edge");
  }
  void
  to_json(json &j, const Bottom_Front_Edge &) {
    j = "bottom_front_edge";
  }

  void
  from_json([[maybe_unused]] const json &j, Bottom_Front_Edge &) {
    assert(j == "bottom_front_edge");
  }
  void
  to_json(json &j, const Top_Back_Edge &) {
    j = "top_back_edge";
  }

  void
  from_json([[maybe_unused]] const json &j, Top_Back_Edge &) {
    assert(j == "top_back_edge");
  }
  void
  to_json(json &j, const Top_Front_Edge &) {
    j = "top_front_edge";
  }

  void
  from_json([[maybe_unused]] const json &j, Top_Front_Edge &) {
    assert(j == "top_front_edge");
  }

  //
  // ... Corners 3D
  //

  void
  to_json(json &j, const Left_Bottom_Back_Corner &) {
    j = "left_bottom_back_corner";
  }

  void
  from_json([[maybe_unused]] const json &j, Left_Bottom_Back_Corner &) {
    assert(j == "left_bottom_back_corner");
  }
  void
  to_json(json &j, const Left_Bottom_Front_Corner &) {
    j = "  left_bottom_front_corner";
  }

  void
  from_json([[maybe_unused]] const json &j, Left_Bottom_Front_Corner &) {
    assert(j == "  left_bottom_front_corner");
  }
  void
  to_json(json &j, const Left_Top_Back_Corner &) {
    j = "  left_top_back_corner";
  }

  void
  from_json([[maybe_unused]] const json &j, Left_Top_Back_Corner &) {
    assert(j == "  left_top_back_corner");
  }
  void
  to_json(json &j, const Left_Top_Front_Corner &) {
    j = "  left_top_front_corner";
  }

  void
  from_json([[maybe_unused]] const json &j, Left_Top_Front_Corner &) {
    assert(j == "  left_top_front_corner");
  }
  void
  to_json(json &j, const Right_Bottom_Back_Corner &) {
    j = "  right_bottom_back_corner";
  }

  void
  from_json([[maybe_unused]] const json &j, Right_Bottom_Back_Corner &) {
    assert(j == "  right_bottom_back_corner");
  }
  void
  to_json(json &j, const Right_Bottom_Front_Corner &) {
    j = "  right_bottom_front_corner";
  }

  void
  from_json([[maybe_unused]] const json &j, Right_Bottom_Front_Corner &) {
    assert(j == "  right_bottom_front_corner");
  }
  void
  to_json(json &j, const Right_Top_Back_Corner &) {
    j = "  right_top_back_corner";
  }

  void
  from_json([[maybe_unused]] const json &j, Right_Top_Back_Corner &) {
    assert(j == "  right_top_back_corner");
  }
  void
  to_json(json &j, const Right_Top_Front_Corner &) {
    j = "  right_top_front_corner";
  }

  void
  from_json([[maybe_unused]] const json &j, Right_Top_Front_Corner &) {
    assert(j == "  right_top_front_corner");
  }

} // end of namespace lbm::core
