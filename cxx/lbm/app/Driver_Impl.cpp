#include <lbm/app/Driver_Impl.hpp>

namespace lbm::app {

  Driver::Impl::Impl(int argc, char **argv)
      : runtime_config_{argc, argv}
      , input_{runtime_config_.input()} {

    switch (input_.kernel()) {
    case Kernel::D2Q9:
      switch (input_.float_type()) {
      case Float_Type::FLOAT32:
        pstate_ = make_unique<D2Q9::State<float32_t>>(input_);
        break;
      case Float_Type::FLOAT64:
        pstate_ = make_unique<D2Q9::State<float64_t>>(input_);
        break;
      }
      break;
    }

    for (size_type i = 0; i < input_.num_steps(); ++i) {
      pstate_->step();
    }
  }

  Driver::Impl::operator int() const { return 0; }

} // end of namespace lbm::app
