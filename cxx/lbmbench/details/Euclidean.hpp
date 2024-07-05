#pragma once

//
// ... LBM Bench header files
//
#include <lbmbench/details/JSON_Convertible.hpp>
#include <lbmbench/details/import.hpp>

namespace lbm::details {

  /**
   * @brief A type describing Euclidean vectors with a length determined
   * at runtime.
   *
   * @details This type favors safety over performance and is not
   * intended for performance critical code.
   */
  template <class T>
  class Euclidean : public vector<T>, public JSON_Convertible {
  public:
    using Base = vector<T>;
    using Base::Base;

    using Base::begin;
    using Base::end;

    T &operator[](std::size_t) = delete;

    /**
     * @brief Array access operator
     *
     * @details This array access operator supports readonly access and
     * always perfoms bounds checking.
     */
    const T &
    operator[](size_type index) const {
      return Base::at(index);
    }

    friend Euclidean
    operator+(const Euclidean &u, const Euclidean &v) {
      if (u.size() == v.size()) {
        Euclidean result{};
        transform(std::begin(u), std::end(u), std::begin(v), back_inserter(result), plus{});
        return result;
      } else {
        throw logic_error("Invalid addition of Euclidean vectors with different sizes");
      }
    }

    friend Euclidean
    operator-(const Euclidean &u, const Euclidean &v) {
      if (u.size() == v.size()) {
        Euclidean result{};
        transform(std::begin(u), std::end(u), std::begin(v), back_inserter(result), minus{});
        return result;
      } else {
        throw logic_error("Invalid subtraction of Euclidean vectors with different sizes");
      }
    }

    friend Euclidean
    operator*(const Euclidean &u, T s) {
      Euclidean result{};
      transform(std::begin(u), std::end(u), back_inserter(result), [=](auto ui) { return ui * s; });
      return result;
    }

    friend Euclidean
    operator*(T s, const Euclidean &u) {
      Euclidean result{};
      transform(std::begin(u), std::end(u), back_inserter(result), [=](auto ui) { return ui * s; });
      return result;
    }

    friend T
    dot(const Euclidean &u, const Euclidean &v) {
      if (u.size() == v.size()) {
        return transform_reduce(std::begin(u), std::end(u), std::begin(v), T(0));
      } else {
        throw logic_error("Invalid inner product of Euclidean vectors with different sizes");
      }
    }

    friend bool
    operator==(const Euclidean &u, const Euclidean &v) {
      if (u.size() == v.size()) {
        return transform_reduce(
            std::begin(u), std::end(u), std::begin(v), true, logical_and{}, equal_to{});
      } else {
        throw logic_error("Invalid comparison of Euclidean vectors with different sizes");
      }
    }

    friend bool
    operator!=(const Euclidean &u, const Euclidean &v) {
      return !(u == v);
    }

    size_type
    size() const {
      return Base::size();
    }

  private:
    json
    get_json() const override {
      json j = static_cast<const Base &>(*this);
      return j;
    }

    void
    set_json(const json &j) override {
      Base::clear();
      transform(std::begin(j),
                std::end(j),
                back_inserter(static_cast<Base &>(*this)),
                [](const json &element) -> T { return element; });
    }
  };

  template <class T>
  Euclidean(T &&, same_as<T> auto &&, same_as<T> auto &&...) -> Euclidean<remove_cvref_t<T>>;

} // end of namespace lbm::details
