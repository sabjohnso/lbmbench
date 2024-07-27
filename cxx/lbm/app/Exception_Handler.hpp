#pragma once

//
// ... LBM Bench header files
//
#include <lbm/app/import.hpp>

namespace lbm::app {

  class Exception_Handler {
    enum class Exit_Code { SUCCESS, BAD_USAGE, BAD_CONFIG_PATH };

  public:
    Exception_Handler() = delete;
    Exception_Handler(const Exception_Handler &) = delete;

    Exception_Handler(int argc, char **argv) {
      try {
        std::rethrow_exception(std::current_exception());

      } catch (const Help_Request &e) {
        std::cout << e.what() << std::endl;
        exit_code_ = int(Exit_Code::SUCCESS);

      } catch (const Version_Request &e) {
        std::cout << e.what() << std::endl;
        exit_code_ = int(Exit_Code::SUCCESS);

      } catch (const Bad_Usage &e) {

        std::cerr << "Invalid usage error:" << std::endl
                  << "\tinvocation:" << std::endl
                  << "\t\t" << invocation(argc, argv) << std::endl
                  << "\terror message:" << std::endl
                  << "\t\t" << e.what();
        exit_code_ = int(Exit_Code::BAD_USAGE);

      } catch (std::exception &e) {
        std::cerr << "lbmbench encountered an unexpected error:" << std::endl
                  << "\tinvocation:" << std::endl
                  << "\t\t" << invocation(argc, argv) << std::endl
                  << "\terror message:" << std::endl
                  << "\t\t" << e.what() << std::endl;
      }
    }

    operator int() const { return exit_code_; }

  private:
    std::string
    invocation(int argc, char **argv) {
      std::ostringstream oss{};
      std::copy(argv, argv + argc, std::ostream_iterator<std::string>{oss, " "});
      return oss.str();
    }

    int exit_code_{-1};
  };

} // end of namespace lbm::app
