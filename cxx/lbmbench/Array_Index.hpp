#pragma once

namespace lbm::details {

  template <size_type N, class storage = std::array<size_type, N>>
  class Array_Index {
  public:
    constexpr Array_Index(size_type i0, size_type i1, Sz... is) {}

  private:
    Storage storage
  };

} // end of namespace lbm::details
