//
// ... LBM Bench header files
//
#include <lbm/app/Driver.hpp>
#include <lbm/app/Exception_Handler.hpp>

int
main(int argc, char **argv) {
  try {
    return lbm::app::Driver(argc, argv);
  } catch (...) {
    return lbm::app::Exception_Handler(argc, argv);
  }
}
