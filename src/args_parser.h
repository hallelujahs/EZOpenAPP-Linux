// Copyright (c) 2018 winking324
//


#pragma once  // NOLINT(build/header_guard)


#include <set>
#include <map>
#include <vector>
#include <string>
#include <ostream>
#include <typeindex>


namespace ez_open_app {


class ArgsParser {
  struct ArgInfo {
    std::type_index type = typeid(bool);
    union {
      void        *data_arg;
      bool        *bool_arg;
      int32_t     *int32_arg;
      int64_t     *int64_arg;
      uint32_t    *uint32_arg;
      uint64_t    *uint64_arg;
      double      *double_arg;
      std::string *string_arg;
    };
  };

  typedef bool (ArgsParser::*TypeParser)(const ArgInfo &arg_info,
                                         const char *arg_value);

 public:
  ArgsParser();

  template<typename ArgType>
  bool AddArgOption(const char *name, ArgType *store);

  bool ParseArgs(int argc, char *const argv[]);

  void Reset();

  void PrintUsage(const char *exec_file, std::ostream &sout) const;

  const std::set<std::string> &GetParsedArgName() const;

 private:
  bool InsertLongOption(const ArgsParser::ArgInfo &arg_info,
                        const char *arg_name);

  bool ParseType(const char *arg_name, const ArgInfo &arg_info,
                 const char *arg_value);

  bool ParseBool(const ArgInfo &arg_info, const char *arg_value);

  bool ParseInt32(const ArgInfo &arg_info, const char *arg_value);

  bool ParseInt64(const ArgInfo &arg_info, const char *arg_value);

  bool ParseUInt32(const ArgInfo &arg_info, const char *arg_value);

  bool ParseUInt64(const ArgInfo &arg_info, const char *arg_value);

  bool ParseDouble(const ArgInfo &arg_info, const char *arg_value);

  bool ParseString(const ArgInfo &arg_info, const char *arg_value);

 private:
  std::map<std::type_index, std::string> type_name_;
  std::map<std::type_index, TypeParser> type_parser_;
  std::map<const char *, ArgInfo> args_option_;
  std::set<std::string> args_parsed_;
};


template<typename ArgType>
bool ArgsParser::AddArgOption(const char *name, ArgType *store) {
  ArgInfo arg_info;
  arg_info.type = std::type_index(typeid(ArgType));
  arg_info.data_arg = store;
  return InsertLongOption(arg_info, name);
}


}  // namespace ez_open_app

