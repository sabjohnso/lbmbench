#include <lbm/app/Runtime_Config_Impl.hpp>

namespace lbm::app {

  Runtime_Config::Impl::Impl(int argc, const char *const *argv)
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

  const json &
  Runtime_Config::Impl::input() const {
    return input_;
  }

  void
  Runtime_Config::Impl::replace_command_line_parser_error(const path &executable_path,
                                                          const std::exception &e) {
    std::ostringstream oss{};
    oss << e.what() << std::endl << "\n" << usage(executable_path);
    throw Bad_Usage{oss.str()};
  }

  void
  Runtime_Config::Impl::replace_input_error(const path &executable_path, const std::exception &e) {
    std::ostringstream oss{};
    oss << e.what() << std::endl << "\n" << usage(executable_path);
    throw Bad_Input{oss.str()};
  }

  void
  Runtime_Config::Impl::read_input() {
    ifstream ifs(vm_["input"].as<path>());
    input_ = json::parse(ifs);
  }

  void
  Runtime_Config::Impl::validate_input() const {
    json schema = load_schema();
    json_validator validator(schema);
    validator.validate(input_);
  }

  json
  Runtime_Config::Impl::load_schema() const {
    ifstream ifs{lbm::config::testing ? lbm::config::schema_location_testing
                                      : lbm::config::schema_location};
    return json::parse(ifs);
  }

  po::options_description
  Runtime_Config::Impl::make_visible_options() {
    po::options_description description{};
    description.add_options()("help,h", "Show this help message and exit.")(
        "version,v", "Show the version number and exit")(
        "input,i", po::value<path>()->value_name("INPUT"), "Simulation input file");
    return description;
  }

  std::string
  Runtime_Config::Impl::usage(const path &executable_path) {
    std::ostringstream oss{};
    oss << "Usage: " << std::string{executable_path.filename()} << " [options]";
    oss << "Options:" << visible_;
    return oss.str();
  }

} // end of namespace lbm::app
