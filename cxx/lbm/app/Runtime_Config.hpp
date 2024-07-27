#pragma once

//
// ... LBM Bench header files
//
#include <lbm/app/import.hpp>
#include <lbm/config.hpp>

//
// ... iostream header files
//
#include <iostream>

namespace lbm::app {

  class Runtime_Config {
  public:
    Runtime_Config(int argc, const char *const *argv)
        : visible_{make_visible_options()} {

      try {
        po::store(po::command_line_parser(argc, argv).options(visible_).run(), vm_);
        po::notify(vm_);
      } catch (const std::exception &e) {
        replace_command_line_parser_error(argv[0], e);
      }

      if (vm_.count("help")) {
        throw Help_Request{usage(argv[0])};
      } else if (vm_.count("version")) {
        throw Version_Request{lbm::config::version};
      } else if (vm_.count("input") == 0) {
        throw Bad_Usage{"missing path to input file\n\n"s + usage(argv[0])};
      } else {
        try {
          read_input();
          validate_input();
        } catch (const std::exception &e) {
          replace_input_error(argv[0], e);
        }
      }
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
    replace_input_error(const path &executable_path, const std::exception &e) {
      std::ostringstream oss{};
      oss << e.what() << std::endl << "\n" << usage(executable_path);
      throw Bad_Input{oss.str()};
    }

    void
    read_input() {
      ifstream ifs(vm_["input"].as<path>());
      input_ = json::parse(ifs);
    }

    void
    validate_input() const {
      json schema = load_schema();
      json_validator validator(schema);
      validator.validate(input_);
    }

    json
    load_schema() const {
      ifstream ifs{lbm::config::testing ? lbm::config::schema_location_testing
                                        : lbm::config::schema_location};
      return json::parse(ifs);
    }

    static po::options_description
    make_visible_options() {
      po::options_description description{};
      description.add_options()                             //
          ("help,h", "Show this help message and exit.")    //
          ("version,v", "Show the version number and exit") //
          ("input,i", po::value<path>()->value_name("INPUT"), "Simulation input file");
      return description;
    }

    std::string
    usage(const path &executable_path) {
      std::ostringstream oss{};
      oss << "Usage: " << std::string{executable_path.filename()} << " [options] <input-file>\n";
      oss << "Options:" << all_options();
      return oss.str();
    }

    po::options_description
    all_options() {
      po::options_description description{};
      description.add(visible_);
      return description;
    }

    po::options_description visible_;
    po::variables_map vm_{};
    json input_{};
  };

} // end of namespace lbm::app
