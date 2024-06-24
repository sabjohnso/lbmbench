#pragma once

//
// ... LBM Bench header files
//
#include <lbmbench/details/Fixed_Array_Index.hpp>
#include <lbmbench/details/base_types.hpp>
#include <lbmbench/details/import.hpp>

namespace lbm::details {

  template <size_type... Ns>
  struct Fixed_Lexical {

    static constexpr size_type degree = sizeof...(Ns);

    using data_type = array<size_type, degree>;

    static constexpr data_type extents{{Ns...}};

    using Index = Fixed_Array_Index<degree>;

    static constexpr data_type strides = [] {
      const auto recur = [](auto recur, size_type stride, same_as<size_type> auto... strides) {
        constexpr size_type nstrides = 1 + sizeof...(strides);
        if constexpr (nstrides == degree) {
          return data_type{{stride, strides...}};
        } else {
          return recur(recur, stride * extents[degree - nstrides], stride, strides...);
        }
      };
      return recur(recur, 1);
    }();

    static constexpr size_type
    storage_index(const auto &idx) {
      assert(idx.size() == degree);
      assert(strides.size() == degree);
      return inner_product(begin(idx), end(idx), begin(strides), size_type(0u));
    }

    static constexpr Index
    array_index(const size_type &index) {
      return [=]<std::size_t... i>(index_sequence<i...>) {
        return Index{(index / strides[i]) % extents[i]...};
      }(make_index_sequence<degree>());
    }

    friend void
    to_json(json &j, const Fixed_Lexical) {
      j = {{"FixedLexical", extents}};
    }

    friend void
    from_json(const json &j, Fixed_Lexical &order) {
      for (size_type i = 0u; i < degree; ++i) {
        if (j["FixedLexical"][i] != extents[i]) {
          ostringstream ss{};
          ss << "Expected " << order << ", but received" << j
             << " when initializing Fixed_Lexical.";
          throw runtime_error(ss.str());
        }
      }
    }

    friend ostream &
    operator<<(ostream &os, const Fixed_Lexical &order) {
      return os << json(order);
    }

    friend istream &
    operator>>(istream &is, Fixed_Lexical &order) {
      order = json::parse(is);
      return is;
    }

    friend constexpr bool
    operator<=>(const Fixed_Lexical &, const Fixed_Lexical &) = default;
  };

} // end of namespace lbm::details
