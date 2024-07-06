//
// ... LBM Bench header files
//
#include <lbmbench/details/Euclidean.hpp>

namespace lbm::details {

  const double &
  Euclidean::operator[](size_type index) const {
    return Base::at(index);
  }

  Euclidean
  operator-(const Euclidean &u) {
    return -1.0 * u;
  }

  Euclidean
  operator+(const Euclidean &u, const Euclidean &v) {
    if (u.size() == v.size()) {
      Euclidean result{};
      transform(std::begin(u), std::end(u), std::begin(v), back_inserter(result), plus{});
      return result;
    } else {
      throw logic_error("Invalid addition of Euclidean vectors with different sizes");
    }
  }

  Euclidean
  operator-(const Euclidean &u, const Euclidean &v) {
    if (u.size() == v.size()) {
      Euclidean result{};
      transform(std::begin(u), std::end(u), std::begin(v), back_inserter(result), minus{});
      return result;
    } else {
      throw logic_error("Invalid subtraction of Euclidean vectors with different sizes");
    }
  }

  Euclidean
  operator*(const Euclidean &u, double s) {
    Euclidean result{};
    transform(std::begin(u), std::end(u), back_inserter(result), [=](auto ui) { return ui * s; });
    return result;
  }

  Euclidean
  operator*(double s, const Euclidean &u) {
    Euclidean result{};
    transform(std::begin(u), std::end(u), back_inserter(result), [=](auto ui) { return ui * s; });
    return result;
  }

  double
  dot(const Euclidean &u, const Euclidean &v) {
    if (u.size() == v.size()) {
      return transform_reduce(std::begin(u), std::end(u), std::begin(v), double(0));
    } else {
      throw logic_error("Invalid inner product of Euclidean vectors with different sizes");
    }
  }

  bool
  operator==(const Euclidean &u, const Euclidean &v) {
    if (u.size() == v.size()) {
      return transform_reduce(
          std::begin(u), std::end(u), std::begin(v), true, logical_and{}, equal_to{});
    } else {
      throw logic_error("Invalid comparison of Euclidean vectors with different sizes");
    }
  }

  bool
  operator!=(const Euclidean &u, const Euclidean &v) {
    return !(u == v);
  }

  json
  Euclidean::get_json() const {
    json j = static_cast<const Base &>(*this);
    return j;
  }

  void
  Euclidean::set_json(const json &j) {
    Base::clear();
    transform(std::begin(j),
              std::end(j),
              back_inserter(static_cast<Base &>(*this)),
              [](const json &element) -> double { return element; });
  }
} // namespace lbm::details
