//
// ... LBM Bench header files
//
#include <lbmbench/details/Lattice.hpp>

namespace lbm::details {

  Lattice::Lattice(Bounding_Box bounding_box, double lattice_spacing)
      : bounding_box_(bounding_box), lattice_spacing_(lattice_spacing) {}

  size_type
  Lattice::size(size_type idim) const {
    return static_cast<size_type>(std::ceil(bounding_box_.at(idim) / lattice_spacing_));
  }

  size_type
  Lattice::size() const {
    size_type accum = 1;
    for (size_type i = 0; i < static_cast<size_type>(bounding_box_.size()); ++i) {
      accum *= size(i);
    }
    return accum;
  }

  double
  Lattice::extent(size_type idim) const {
    return bounding_box_.at(idim);
  }

  double
  Lattice::lattice_spacing() const {
    return lattice_spacing_;
  }

  bool
  operator==(const Lattice &lattice1, const Lattice &lattice2) {
    return lattice1.bounding_box_ == lattice2.bounding_box_ &&
           lattice1.lattice_spacing_ == lattice2.lattice_spacing_;
  }

  json
  Lattice::get_json() const {
    json j = json::object();
    j["boundingBox"] = bounding_box_;
    j["latticeSpacing"] = lattice_spacing_;
    return j;
  }

  void
  Lattice::set_json(const json &j) {
    bounding_box_ = j["boundingBox"];
    lattice_spacing_ = j["latticeSpacing"];
  }

} // namespace lbm::details
