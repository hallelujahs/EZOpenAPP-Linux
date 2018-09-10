// Copyright (c) 2018 winking324
//


#pragma once  // NOLINT(build/header_guard)

#include <string>

namespace ez_open_app {


struct AppConfig {
  int channel = 1;
  std::string platform;
  std::string app_key;
  std::string serial;
  std::string safe_key;
  std::string token;
};


}  // namespace ez_open_app
