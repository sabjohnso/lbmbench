#pragma once

//
// ... LBM Benchmarks header files
//
#include <lbmbenchmarks/details/base_types.hpp>

namespace lbm::details {

  template <class T, class Index_Type>
  concept Order_Type = requires(const T &x const Index_Type &idx, const size_type &i) {
    { x.storage_index(idx) } -> std::same_as<size_type>;
    { x.array_index(i) } -> std::same_as<Index_Type>;
  };

} // namespace lbm::details
