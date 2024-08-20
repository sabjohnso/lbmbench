#pragma once

namespace lbm::core {

  struct Interior {
  } constexpr interior{};

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

} // end of namespace lbm::core
