#pragma once

//
// ... LBM Bench header files
//
#include <lbm/app/import.hpp>

namespace lbm::app {

  class Runtime_Config {
  public:
    Runtime_Config(int argc, char **argv)
        : visible_{make_visible_options()}
        , hidden_{make_hidden_options()}
        , positional_{make_positional_arguments()} {

      try {
        po::store(
            po::command_line_parser(argc, argv).options(visible_).positional(positional_).run(),
            vm_);
      } catch (const std::exception &e) {
        replace_command_line_parser_error(argv[0], e);
      }

      if (vm_.count("help")) {
        throw Help_Request{usage(argv[0])};
      } else if (vm_.count("config") == 0) {
        throw Bad_Usage{"missing path to config file\n\n"s + usage(argv[0])};
      }
    }

    bool
    is_restart() const {
      return vm_.count("restart");
    }

    path
    checkpoint_path() const {
      assert(is_restart());
      return vm_["restart"].as<path>();
    }

    path
    config_path() const {
      return vm_["config"].as<path>();
    }

  private:
    void
    replace_command_line_parser_error(const path &executable_path, const std::exception &e) {
      std::ostringstream oss{};
      oss << e.what() << std::endl << "\n" << usage(executable_path);
      throw Bad_Usage{oss.str()};
    }

    void
    read_input() {
      ifstream ifs(vm_["config"].as<path>());
      input_ = json::parse(ifs);
    }

    static po::options_description
    make_visible_options() {
      po::options_description description{};
      description.add_options()                        //
          ("help", "Show this help message and exit.") //
          ("restart",
           po::value<path>()->value_name("CHECKPOINT"),
           "Specify an optional checkpoint file for restarting a simulation");
      return description;
    }

    static po::options_description
    make_hidden_options() {
      po::options_description description{};
      description.add_options() //
          ("config", po::value<path>()->required(), "Configuration file");
      return description;
    }

    static po::positional_options_description
    make_positional_arguments() {
      po::positional_options_description description{};
      description.add("config", -1);
      return description;
    }

    std::string
    usage(const path &executable_path) {
      std::ostringstream oss{};
      oss << "Usage: " << std::string{executable_path.filename()} << " [options] <config-file>\n";
      oss << "Options:" << all_options();
      return oss.str();
    }

    po::options_description
    all_options() {
      po::options_description description{};
      description.add(visible_);
      return description;
    }

    po::options_description visible_{};
    po::options_description hidden_{};
    po::positional_options_description positional_{};
    po::variables_map vm_{};
    json input_{};
  };

} // end of namespace lbm::app
