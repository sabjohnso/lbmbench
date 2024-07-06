#pragma once

//
// ... LBM Bench header files
//
#include <lbmbench/details/JSON_Convertible.hpp>
#include <lbmbench/details/base_types.hpp>
#include <lbmbench/details/import.hpp>

namespace lbm::details {

  /**
   * @brief A type describing Euclidean vectors with a length determined
   * at runtime.
   *
   * @details This type favors safety over performance and is not
   * intended for performance critical code.
   */
  class Euclidean : public vector<double>, public JSON_Convertible {
  public:
    using Base = vector<double>;
    using Base::Base;

    using Base::begin;
    using Base::end;

    double &operator[](std::size_t) = delete;

    /**
     * @brief Array access operator
     *
     * @details This array access operator supports readonly access and
     * always perfoms bounds checking.
     */
    const double &
    operator[](size_type index) const;

    friend Euclidean
    operator-(const Euclidean &u);

    friend Euclidean
    operator+(const Euclidean &u, const Euclidean &v);

    friend Euclidean
    operator-(const Euclidean &u, const Euclidean &v);

    friend Euclidean
    operator*(const Euclidean &u, double s);

    friend Euclidean
    operator*(double s, const Euclidean &u);

    friend double
    dot(const Euclidean &u, const Euclidean &v);

    friend bool
    operator==(const Euclidean &u, const Euclidean &v);

    friend bool
    operator!=(const Euclidean &u, const Euclidean &v);

    size_type
    size() const {
      return Base::size();
    }

  private:
    json
    get_json() const override;

    void
    set_json(const json &j) override;
  };

} // end of namespace lbm::details
