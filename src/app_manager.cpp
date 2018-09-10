// Copyright (c) 2018 winking324
//


#include "app_manager.h"

#include <unistd.h>
#include <string.h>
#include <iostream>

#include "singleton.h"


namespace ez_open_app {


int MessageCallback(HANDLE handler, int code, int event_type, void *user_data) {
  (void)user_data;
  std::cout << "phandle: " << handler << ", code: " << code
            << ", event type: " << event_type << std::endl;
  return 0;
}

FILE *kSaved = nullptr;

int DataCallBack(HANDLE handler, uint32_t data_type, uint8_t *buf,
                 uint32_t length, void* user_data) {
  (void)user_data;
  std::cout << "handler: " << handler << ", data type: " << data_type
            << ", buffer size: " << length << std::endl;
  if (kSaved == nullptr) {
    kSaved = ::fopen("./test.mp4", "wb");
  }

  ::fwrite(buf, sizeof(uint8_t), length, kSaved);
  return 0;
}


AppManager::AppManager() {
  handler_ = nullptr;
  app_config_ = Singleton<AppConfig>::Instance();
}

AppManager::~AppManager() {
  ESOpenSDK_StopRealPlay(handler_);
  ESOpenSDK_Fini();

  if (kSaved != nullptr) {
    ::fclose(kSaved);
  }
}

int AppManager::Init() {
  if (ESOpenSDK_Init() < 0) {
    std::cerr << "ESOpenSDK init failed" << std::endl;
    return -1;
  }

  ESOpenSDK_InitWithAppKey(app_config_->app_key.c_str(),
                           app_config_->platform.c_str());
  return 0;
}

int AppManager::SaveRealPlay() {
  ES_DEVICE_INFO device_info = {0};
  strcpy(device_info.szDevSerial, app_config_->serial.c_str());
  strcpy(device_info.szSafeKey, app_config_->safe_key.c_str());
  device_info.iDevChannelNo = app_config_->channel;

  ES_STREAM_CALLBACK callback_info;
  callback_info.on_recvmessage = MessageCallback;
  callback_info.on_recvdata = DataCallBack;
  callback_info.pUser = nullptr;

  std::cout << "call start real play" << std::endl;
  int res = ESOpenSDK_StartRealPlay(app_config_->token.c_str(), device_info,
                                    callback_info, handler_);
  if (res == ES_NOERROR) {
    sleep(10);
  }

  return res;
}


}  // namespace ez_open_app
