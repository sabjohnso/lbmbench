//
// ... LBM Bench header files
//
#include <lbmbench/details/D2_Lattice.hpp>

namespace lbm::details::D2Q9 {

  Lattice::Lattice(double width, double height, double spacing)
      : width_(width), height_(height), spacing_(spacing) {}

  size_type
  Lattice::nx() const {
    return static_cast<size_type>(std::ceil(width_ / spacing_));
  }

  size_type
  Lattice::ny() const {
    return static_cast<size_type>(std::ceil(height_ / spacing_));
  }

  double
  Lattice::width() const {
    return width_;
  }

  double
  Lattice::height() const {
    return height_;
  }

  double
  Lattice::spacing() const {
    return spacing_;
  }

  bool
  operator==(const Lattice &l1, const Lattice &l2) {
    return l1.width_ == l2.width_ && l1.height_ == l2.height_ && l1.spacing_ == l2.spacing_;
  }

  json
  Lattice::get_json() const {
    json j = json::object();
    j["width"] = width();
    j["height"] = height();
    j["spacing"] = spacing();
    return j;
  }

  void
  Lattice::set_json(const json &j) {
    width_ = j["width"];
    height_ = j["height"];
    spacing_ = j["spacing"];
  }

} // end of namespace lbm::details::D2Q9
