// Copyright (c) 2018 winking324
//


#include <string>
#include <sstream>
#include <iostream>

#include "singleton.h"
#include "args_parser.h"
#include "app_config.h"
#include "app_manager.h"


int main(int argc, char **argv) {
  ez_open_app::AppConfig *app_config =
      ez_open_app::Singleton<ez_open_app::AppConfig>::Instance();

  ez_open_app::ArgsParser args_parser;
  args_parser.AddArgOption("channel", &(app_config->channel));
  args_parser.AddArgOption("platform", &(app_config->platform));
  args_parser.AddArgOption("app_key", &(app_config->app_key));
  args_parser.AddArgOption("serial", &(app_config->serial));
  args_parser.AddArgOption("safe_key", &(app_config->safe_key));
  args_parser.AddArgOption("token", &(app_config->token));

  if (argc <= 1 || !args_parser.ParseArgs(argc, argv)) {
    std::ostringstream sout;
    args_parser.PrintUsage(argv[0], sout);
    std::cerr << sout.str() << std::endl;
    return -1;
  }

  ez_open_app::AppManager app_manager;
  if (app_manager.Init() != 0) {
    return -1;
  }

  std::cout << "start save real play" << std::endl;
  app_manager.SaveRealPlay();
  return 0;
}

