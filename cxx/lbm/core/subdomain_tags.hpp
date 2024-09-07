#pragma once

//
// ... LBM Bench header files
//
#include <lbm/core/import.hpp>

namespace lbm::core {

  //
  // ... Interior
  //
  struct Interior {
  } constexpr interior{};

  //
  // ... Boundaries 2D and 3D
  //
  struct Left {
  } constexpr left{};

  struct Right {
  } constexpr right{};

  struct Bottom {
  } constexpr bottom{};

  struct Top {
  } constexpr top{};

  struct Back {
  } constexpr back{};

  struct Front {
  } constexpr front{};

  template <class T>
  concept Boundary_Tag2 =
      same_as<Left, T> || same_as<Right, T> || same_as<Bottom, T> || same_as<Top, T>;

  template <class T>
  concept Boundary_Tag3 = Boundary_Tag2<T> || same_as<Back, T> || same_as<Front, T>;

  template <Boundary_Tag3 Boundary>
  using Lower_Boundary = std::conditional_t<
      same_as<Boundary, Left> || same_as<Boundary, Right>,
      Left,
      std::conditional_t<same_as<Boundary, Bottom> || same_as<Boundary, Top>, Bottom, Back>>;

  template <Boundary_Tag3 Boundary>
  using Upper_Boundary = std::conditional_t<
      same_as<Boundary, Left> || same_as<Boundary, Right>,
      Right,
      std::conditional_t<same_as<Boundary, Bottom> || same_as<Boundary, Top>, Top, Front>>;

  //
  // ... Corners 2D
  //
  struct Left_Bottom_Corner {
  } constexpr left_bottom_corner{};

  struct Left_Top_Corner {
  } constexpr left_top_corner{};

  struct Right_Bottom_Corner {
  } constexpr right_bottom_corner{};

  struct Right_Top_Corner {
  } constexpr right_top_corner{};

  template <class T>
  concept Corner_Tag_2D = same_as<T, Left_Bottom_Corner> || same_as<T, Left_Top_Corner> ||
      same_as<T, Right_Bottom_Corner> || same_as<T, Right_Top_Corner>;

  //
  // ... Edges on a three-dimensional grid
  //
  struct Left_Bottom_Edge {
  } constexpr left_bottom_edge{};

  struct Left_Top_Edge {
  } constexpr left_top_edge{};

  struct Right_Bottom_Edge {
  } constexpr right_bottom_edge{};

  struct Right_Top_Edge {
  } constexpr right_top_Edge{};

  struct Left_Back_Edge {
  } constexpr left_back_Edge{};

  struct Left_Front_Edge {
  } constexpr left_front_edge{};

  struct Right_Back_Edge {
  } constexpr right_back_edge{};

  struct Right_Front_Edge {
  } constexpr right_front_edge{};

  struct Bottom_Back_Edge {
  } constexpr bottom_back_Edge{};

  struct Bottom_Front_Edge {
  } constexpr bottom_front_edge{};

  struct Top_Back_Edge {
  } constexpr top_back_edge{};

  struct Top_Front_Edge {
  } constexpr top_front_edge{};

  template <class T>
  concept Edge_Tag_3D =
      same_as<T, Left_Bottom_Edge> || same_as<T, Left_Top_Edge> || same_as<T, Right_Bottom_Edge> ||
      same_as<T, Right_Top_Edge> || same_as<T, Left_Back_Edge> || same_as<T, Left_Front_Edge> ||
      same_as<T, Right_Back_Edge> || same_as<T, Right_Front_Edge> || same_as<T, Bottom_Back_Edge> ||
      same_as<T, Bottom_Front_Edge> || same_as<T, Top_Back_Edge> || same_as<T, Top_Front_Edge>;

  //
  // ... Corners on a three-dimensional grid
  //
  struct Left_Bottom_Back_Corner {
  } constexpr left_bottom_back_corner{};

  struct Left_Bottom_Front_Corner {
  } constexpr left_bottom_front_corner{};

  struct Left_Top_Back_Corner {
  } constexpr left_top_back_corner{};

  struct Left_Top_Front_Corner {
  } constexpr left_top_front_corner{};

  struct Right_Bottom_Back_Corner {
  } constexpr right_bottom_back_corner{};

  struct Right_Bottom_Front_Corner {
  } constexpr right_bottom_front_corner{};

  struct Right_Top_Back_Corner {
  } constexpr right_top_back_corner{};

  struct Right_Top_Front_Corner {
  } constexpr right_top_front_corner{};

  template <class T>
  concept Corner_Tag_3D =
      same_as<T, Left_Bottom_Back_Corner> || same_as<T, Left_Bottom_Front_Corner> ||
      same_as<T, Left_Top_Back_Corner> || same_as<T, Left_Top_Front_Corner> ||
      same_as<T, Right_Bottom_Back_Corner> || same_as<T, Right_Bottom_Front_Corner> ||
      same_as<T, Right_Top_Back_Corner> || same_as<T, Right_Top_Front_Corner>;

  ////////////////////////////////////////////////////////////////////////
  //
  //  ... Serialization prototypes
  //
  //
  // ... Interior
  //
  void
  to_json(json &j, const Interior &);

  void
  from_json(const json &j, Interior &);

  //
  // ... Faces 2D and 3D
  //

  void
  to_json(json &j, const Left &);

  void
  from_json(const json &j, Left &);

  void
  to_json(json &j, const Right &);

  void
  from_json(const json &j, Right &);

  void
  to_json(json &j, const Bottom &);

  void
  from_json(const json &j, Bottom &);

  void
  to_json(json &j, const Top &);

  void
  from_json(const json &j, Top &);

  void
  to_json(json &j, const Back &);

  void
  from_json(const json &j, Back &);

  void
  to_json(json &j, const Front &);

  void
  from_json(const json &j, Front &);

  //
  // ... Corners 2D
  //
  void
  to_json(json &j, const Left_Bottom_Corner &);

  void
  from_json(const json &j, Left_Bottom_Corner &);

  void
  to_json(json &j, const Left_Top_Corner &);

  void
  from_json(const json &j, Left_Top_Corner &);

  void
  to_json(json &j, const Right_Bottom_Corner &);

  void
  from_json(const json &j, Right_Bottom_Corner &);

  void
  to_json(json &j, const Right_Top_Corner &);

  void
  from_json(const json &j, Right_Top_Corner &);

  //
  // ... Edges 3D
  //

  void
  to_json(json &j, const Left_Bottom_Edge &);

  void
  from_json(const json &j, Left_Bottom_Edge &);

  void
  to_json(json &j, const Left_Top_Edge &);

  void
  from_json(const json &j, Left_Top_Edge &);

  void
  to_json(json &j, const Right_Bottom_Edge &);

  void
  from_json(const json &j, Right_Bottom_Edge &);

  void
  to_json(json &j, const Right_Top_Edge &);

  void
  from_json(const json &j, Right_Top_Edge &);

  void
  to_json(json &j, const Left_Back_Edge &);

  void
  from_json(const json &j, Left_Back_Edge &);

  void
  to_json(json &j, const Left_Front_Edge &);

  void
  from_json(const json &j, Left_Front_Edge &);

  void
  to_json(json &j, const Right_Back_Edge &);

  void
  from_json(const json &j, Right_Back_Edge &);

  void
  to_json(json &j, const Right_Front_Edge &);

  void
  from_json(const json &j, Right_Front_Edge &);

  void
  to_json(json &j, const Bottom_Back_Edge &);

  void
  from_json(const json &j, Bottom_Back_Edge &);

  void
  to_json(json &j, const Bottom_Front_Edge &);

  void
  from_json(const json &j, Bottom_Front_Edge &);

  void
  to_json(json &j, const Top_Back_Edge &);

  void
  from_json(const json &j, Top_Back_Edge &);

  void
  to_json(json &j, const Top_Front_Edge &);

  void
  from_json(const json &j, Top_Front_Edge &);

  //
  // ... Corners 3D
  //

  void
  to_json(json &j, const Left_Bottom_Back_Corner &);

  void
  from_json(const json &j, Left_Bottom_Back_Corner &);

  void
  to_json(json &j, const Left_Bottom_Front_Corner &);

  void
  from_json(const json &j, Left_Bottom_Front_Corner &);

  void
  to_json(json &j, const Left_Top_Back_Corner &);

  void
  from_json(const json &j, Left_Top_Back_Corner &);

  void
  to_json(json &j, const Left_Top_Front_Corner &);

  void
  from_json(const json &j, Left_Top_Front_Corner &);

  void
  to_json(json &j, const Right_Bottom_Back_Corner &);

  void
  from_json(const json &j, Right_Bottom_Back_Corner &);

  void
  to_json(json &j, const Right_Bottom_Front_Corner &);

  void
  from_json(const json &j, Right_Bottom_Front_Corner &);

  void
  to_json(json &j, const Right_Top_Back_Corner &);

  void
  from_json(const json &j, Right_Top_Back_Corner &);

  void
  to_json(json &j, const Right_Top_Front_Corner &);

  void
  from_json(const json &j, Right_Top_Front_Corner &);

} // end of namespace lbm::core
