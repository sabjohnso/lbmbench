#pragma once

//
// ... LBM Bench header files
//
#include <lbm/config.hpp>
#include <lbm/core/IState.hpp>
#include <lbm/core/Input.hpp>
#include <lbm/core/base_types.hpp>
#include <lbm/exceptions/Bad_Config_Path.hpp>
#include <lbm/exceptions/Bad_Float_Type.hpp>
#include <lbm/exceptions/Bad_Input.hpp>
#include <lbm/exceptions/Bad_Kernel_Name.hpp>
#include <lbm/exceptions/Bad_Usage.hpp>
#include <lbm/exceptions/Help_Request.hpp>
#include <lbm/exceptions/Version_Request.hpp>

//
// ... Third-party header files
//
#include <boost/program_options.hpp>
#include <nlohmann/json-schema.hpp>
#include <nlohmann/json.hpp>

//
// ... Standard header files
//
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>

namespace lbm::app {
  using namespace std::literals;

  namespace po = boost::program_options;

  using std::ifstream;
  using std::make_unique;
  using std::unique_ptr;

  using std::filesystem::exists;
  using std::filesystem::path;

  using lbm::core::float32_t;
  using lbm::core::float64_t;

  using lbm::config::schema_location;
  using lbm::config::schema_location_testing;
  using lbm::core::Float_Type;
  using lbm::core::Input;
  using lbm::core::IState;
  using lbm::core::Kernel;
  using lbm::core::size_type;
  using lbm::exceptions::Bad_Config_Path;
  using lbm::exceptions::Bad_Float_Type;
  using lbm::exceptions::Bad_Input;
  using lbm::exceptions::Bad_Kernel_Name;
  using lbm::exceptions::Bad_Usage;
  using lbm::exceptions::Help_Request;
  using lbm::exceptions::Version_Request;

  using nlohmann::json;

  using nlohmann::json_schema::json_validator;

} // end of namespace lbm::app
