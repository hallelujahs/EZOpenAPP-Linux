// Copyright (c) 2018 winking324
//


#include "args_parser.h"

#include <getopt.h>
#include <iostream>


namespace ez_open_app {


ArgsParser::ArgsParser() {
  type_name_ = {
    {std::type_index(typeid(int32_t)),      std::string("INTEGER32")},
    {std::type_index(typeid(int64_t)),      std::string("INTEGER64")},
    {std::type_index(typeid(uint32_t)),     std::string("UINTEGER32")},
    {std::type_index(typeid(uint64_t)),     std::string("UINTEGER64")},
    {std::type_index(typeid(double)),       std::string("DOUBLE")},
    {std::type_index(typeid(std::string)),  std::string("STRING")},
  };

  type_parser_ = {
    {std::type_index(typeid(int32_t)), &ArgsParser::ParseInt32},
    {std::type_index(typeid(int64_t)), &ArgsParser::ParseInt64},
    {std::type_index(typeid(uint32_t)), &ArgsParser::ParseUInt32},
    {std::type_index(typeid(uint64_t)), &ArgsParser::ParseUInt64},
    {std::type_index(typeid(double)), &ArgsParser::ParseDouble},
    {std::type_index(typeid(std::string)), &ArgsParser::ParseString},
  };
}

bool ArgsParser::ParseArgs(int argc, char *const argv[]) {
  std::vector<option> long_options;
  for (const auto &arg_option : args_option_) {
    int has_arg = required_argument;
    if (arg_option.second.type == std::type_index(typeid(bool))) {
      has_arg = no_argument;
    }
    option arg = {arg_option.first, has_arg, nullptr, 0};
    long_options.push_back(arg);
  }
  option end_indicator = {nullptr, 0, nullptr, 0};
  long_options.push_back(end_indicator);

  optind = 1;
  optarg = nullptr;

  int index = 0;
  int ret = 0;
  while ((ret = getopt_long_only(argc, argv, "", &long_options[0], &index)) == 0
      || (ret > 0 && ret != '?')) {
    if (ret == 0) {
      const option &arg_option = long_options[index];
      const ArgInfo &arg_info = args_option_[arg_option.name];
      const char *arg = optarg;
      if (!arg && arg_info.type != std::type_index(typeid(bool)) &&
          optind < argc) {
        arg = argv[optind];
        ++optind;
      }

      if (!ParseType(arg_option.name, arg_info, arg)) {
        optind = 0;
        return false;
      }

      args_parsed_.insert(arg_option.name);
    }
  }

  index = optind;
  optind = 0;

  if (index < argc) {
    return false;
  }

  if (ret != -1) {
    return false;
  }

  return true;
}

void ArgsParser::Reset() {
  args_option_.clear();
  args_parsed_.clear();
}

void ArgsParser::PrintUsage(const char *exec_file, std::ostream &sout) const {
  sout << "Usage: \n  " << exec_file << " ";
  for (const auto &arg_option : args_option_) {
    sout << "--" << arg_option.first << " ";

    const ArgInfo &arg_info = arg_option.second;
    if (arg_info.type == std::type_index(typeid(bool))) continue;

    auto iter = type_name_.find(arg_info.type);
    if (iter == type_name_.end()) {
      std::cerr << "Cannot get type name for " << arg_option.first << std::endl;
      continue;
    }
    sout << iter->second << " ";
  }
  sout << std::endl;
}

const std::set<std::string> &ArgsParser::GetParsedArgName() const {
  return args_parsed_;
}

bool ArgsParser::InsertLongOption(const ArgsParser::ArgInfo &arg_info,
                                  const char *arg_name) {
  if (arg_name == nullptr) {
    std::cerr << "A full parameter should be supplied!" << std::endl;
    return false;
  }

  if (args_option_.count(arg_name) > 0) {
    std::cerr << arg_name << " has been occupied yet!" << std::endl;
    return false;
  }

  args_option_[arg_name] = arg_info;
  return true;
}

bool ArgsParser::ParseType(const char *arg_name,
                           const ArgsParser::ArgInfo &arg_info,
                           const char *arg_value) {
  if (arg_info.type == std::type_index(typeid(bool))) {
    return ParseBool(arg_info, arg_value);
  }

  if (arg_value == nullptr) {
    std::cerr << "No argument available for " << arg_name << std::endl;
    return false;
  }

  auto iter = type_parser_.find(arg_info.type);
  if (iter == type_parser_.end()) {
    std::cerr << "Cannot parse type for " << arg_name << std::endl;
    return false;
  }
  return (this->*(iter->second))(arg_info, arg_value);
}

bool ArgsParser::ParseBool(const ArgsParser::ArgInfo &arg_info,
                           const char *arg_value) {
  (void)arg_value;
  *(arg_info.bool_arg) = true;
  return true;
}

bool ArgsParser::ParseInt32(const ArgsParser::ArgInfo &arg_info,
                            const char *arg_value) {
  char *end_ptr = nullptr;
  long n = strtol(arg_value, &end_ptr, 10);
  if (*end_ptr != '\0') {
    std::cerr << "Invalid integer argument: " << arg_value << std::endl;
    return false;
  }
  *(arg_info.int32_arg) = int32_t(n);
  return true;
}

bool ArgsParser::ParseInt64(const ArgsParser::ArgInfo &arg_info,
                            const char *arg_value) {
  char *end_ptr = nullptr;
  long long n = strtoll(arg_value, &end_ptr, 10);
  if (*end_ptr != '\0') {
    std::cerr << "Invalid integer 64 argument: " << arg_value << std::endl;
    return false;
  }
  *(arg_info.int64_arg) = int64_t(n);
  return true;
}

bool ArgsParser::ParseUInt32(const ArgsParser::ArgInfo &arg_info,
                             const char *arg_value) {
  char *end_ptr = nullptr;
  unsigned long n = strtoul(arg_value, &end_ptr, 10);
  if (*end_ptr != '\0') {
    std::cerr << "Invalid unsigned integer argument: " << arg_value
              << std::endl;
    return false;
  }
  *(arg_info.uint32_arg) = uint32_t(n);
  return true;
}

bool ArgsParser::ParseUInt64(const ArgsParser::ArgInfo &arg_info,
                             const char *arg_value) {
  char *end_ptr = nullptr;
  unsigned long long n = strtoull(arg_value, &end_ptr, 10);
  if (*end_ptr != '\0') {
    std::cerr << "Invalid unsigned integer 64 argument: " << arg_value
              << std::endl;
    return false;
  }
  *(arg_info.uint64_arg) = uint64_t(n);
  return true;
}

bool ArgsParser::ParseDouble(const ArgsParser::ArgInfo &arg_info,
                             const char *arg_value) {
  char *end_ptr = nullptr;
  double n = strtod(arg_value, &end_ptr);
  if (*end_ptr != '\0') {
    std::cerr << "Invalid double argument: " << arg_value << std::endl;
    return false;
  }
  *(arg_info.double_arg) = n;
  return true;
}

bool ArgsParser::ParseString(const ArgsParser::ArgInfo &arg_info,
                             const char *arg_value) {
  *(arg_info.string_arg) = arg_value;
  return true;
}


}  // namespace ez_open_app
