// Copyright (c) 2018 winking324
//


#pragma once  // NOLINT(build/header_guard)


#include <ESOpenStream.h>

#include <string>

#include "app_config.h"


namespace ez_open_app {


class AppManager {
 public:
  AppManager();

  ~AppManager();

  int Init();

  int SaveRealPlay();

  void OnMessage(int code, int event_type);

  void OnData(uint32_t data_type, const std::string &buffer);

 private:
  HANDLE handler_;
  AppConfig *app_config_;
};


}  // namespace ez_open_app
