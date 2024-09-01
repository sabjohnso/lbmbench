#pragma once

//
// ... LBM Bench header files
//
#include <lbm/core/Index.hpp>
#include <lbm/core/Shape.hpp>
#include <lbm/core/base_types.hpp>

namespace lbm::core {

  template <size_type N>
  class Lexical {
    using Shape_Type = Shape<N>;
    using Index_Type = Index<N>;
    using Strides = array<size_type, N>;

  public:
    constexpr Lexical() = default;
    constexpr Lexical(Shape_Type shape)
        : shape_{std::move(shape)}
        , strides_{compute_strides(shape_)} {}

    friend constexpr bool
    operator<=>(const Lexical &, const Lexical &) = default;

    size_type
    storage_index(Index_Type idx) const {
      return inner_product(begin(idx), end(idx), begin(strides_), size_type(0u));
    };

    size_type
    storage_index(size_type i1, size_type i2, same_as<size_type> auto... is) const {
      static_assert(sizeof...(is) == N - 2);
      return storage_index(Index_Type{i1, i2, is...});
    }

    constexpr Index_Type
    array_index(const size_type &index) const {
      return [ =, this ]<std::size_t... i>(index_sequence<i...>) {
        return Index{(index / strides_[i]) % shape_[i]...};
      }
      (make_index_sequence<N>());
    }

    size_type
    size(size_type idim) const {
      return shape_[idim];
    }

    size_type
    size() const {
      return shape_.total_size();
    }

    size_type
    total_size() const {
      return shape_.total_size();
    }

    friend void
    to_json(json &j, const Lexical &order) {
      j = json::object();
      j["Lexical"] = json(order.shape_);
    }

    friend void
    from_json(const json &j, Lexical &order) {
      order.shape_ = j["Lexical"];
      order.strides_ = compute_strides(order.shape_);
    }

    friend ostream &
    operator<<(ostream &os, const Lexical &order) {
      return os << json(order);
    }

    friend istream &
    operator>>(istream &is, Lexical &order) {
      order = json::parse(is);
      return is;
    }

  private:
    static constexpr Strides
    compute_strides(Shape_Type shape) {
      const auto recur = [=](auto recur, size_type stride, same_as<size_type> auto... strides) {
        constexpr size_type nstrides = 1 + sizeof...(strides);
        if constexpr (nstrides == N) {
          return Strides{{stride, strides...}};
        } else {
          return recur(recur, stride * shape[N - nstrides], stride, strides...);
        }
      };
      return recur(recur, 1);
    }

    Shape_Type shape_{};
    Strides strides_{};
  };

} // namespace lbm::core
