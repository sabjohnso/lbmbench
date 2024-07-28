#pragma once

//
// ... LBM Bench header files
//
#include <lbm/app/Runtime_Config.hpp>
#include <lbm/app/import.hpp>
#include <lbm/config.hpp>

//
// ... iostream header files
//
#include <iostream>

namespace lbm::app {

  class Runtime_Config::Impl {
  public:
    Impl(int argc, const char *const *argv);

    const json &
    input() const;

  private:
    void
    replace_command_line_parser_error(const path &executable_path, const std::exception &e);

    void
    replace_input_error(const path &executable_path, const std::exception &e);

    void
    read_input();

    void
    validate_input() const;

    json
    load_schema() const;

    static po::options_description
    make_visible_options();

    std::string
    usage(const path &executable_path);

    po::options_description visible_;
    po::variables_map vm_{};
    json input_{};
  };

} // end of namespace lbm::app
