// Copyright (c) 2018 winking324
//


#pragma once  // NOLINT(build/header_guard)


#include <ESOpenStream.h>
#include "app_config.h"


namespace ez_open_app {


class AppManager {
 public:
  AppManager();

  ~AppManager();

  int Init();

  int SaveRealPlay();

 private:
  HANDLE handler_;
  AppConfig *app_config_;
};


}  // namespace ez_open_app
