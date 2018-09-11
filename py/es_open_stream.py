# !/usr/bin/python3
# -- coding: utf-8 --
# Author: winking324
import os
import ctypes
import logging
import platform

logging.basicConfig(level=logging.INFO)

LOGGER = logging.getLogger('EZApp')
PLATFORM = str(platform.system()).lower()

BASE_PATH = os.path.split(os.path.realpath(__file__))[0]
SDK_PATH = '/../thirdparty/EZServerOpenSDK/libs/'
SHARED_OBJECT = 'libezserveropensdk.so'


"""
ES_STREAM_EVENT
"""
ES_STREAM_EVENT_NET_CONNECTED = 0
ES_STREAM_EVENT_NET_DISCONNECTED = 1
ES_STREAM_EVENT_STREAM_FAIL = 2
ES_STREAM_EVENT_URL_INVALID = 3
ES_STREAM_EVENT_PACKET_PARSE_FAIL = 4


"""
ES_STREAM_CODE
"""
ES_STREAM_CLIENT_RET_STATUS_BASE = 5000
ES_STREAM_CLIENT_RET_STATUS_302 = 5302
ES_STREAM_CLIENT_RET_STATUS_402 = 5402
ES_STREAM_CLIENT_RET_STATUS_403 = 5403
ES_STREAM_CLIENT_RET_STATUS_404 = 5404
ES_STREAM_CLIENT_RET_STATUS_405 = 5405
ES_STREAM_CLIENT_RET_STATUS_406 = 5406
ES_STREAM_CLIENT_RET_STATUS_407 = 5407
ES_STREAM_CLIENT_RET_STATUS_409 = 5409
ES_STREAM_CLIENT_RET_STATUS_410 = 5410
ES_STREAM_CLIENT_RET_STATUS_411 = 5411
ES_STREAM_CLIENT_RET_STATUS_412 = 5412
ES_STREAM_CLIENT_RET_STATUS_413 = 5413
ES_STREAM_CLIENT_RET_STATUS_415 = 5415
ES_STREAM_CLIENT_RET_STATUS_451 = 5451
ES_STREAM_CLIENT_RET_STATUS_452 = 5452
ES_STREAM_CLIENT_RET_STATUS_454 = 5454
ES_STREAM_CLIENT_RET_STATUS_491 = 5491
ES_STREAM_CLIENT_RET_STATUS_500 = 5500
ES_STREAM_CLIENT_RET_STATUS_501 = 5501
ES_STREAM_CLIENT_RET_STATUS_503 = 5503
ES_STREAM_CLIENT_RET_STATUS_544 = 5544
ES_STREAM_CLIENT_RET_STATUS_545 = 5545
ES_STREAM_CLIENT_RET_STATUS_546 = 5546
ES_STREAM_CLIENT_RET_STATUS_556 = 5556
ES_STREAM_CLIENT_RET_STATUS_560 = 5600
ES_STREAM_CLIENT_RET_EXCEPTION = 6700
ES_STREAM_CLIENT_RET_OVER = 6701
ES_STREAM_CLIENT_RET_INVALID_PACKET = 9000
ES_STREAM_CLIENT_RET_INVALID_HOST = 9001


"""
ES_API_CODE
"""
ES_API_CODE_NOERROR = 0
ES_API_CODE_ERROR_BADPARAMS = 1
ES_API_CODE_ERROR_ALLOCMEMORYFAILED = 2
ES_API_CODE_ERROR_SESSION_INVALID = 3


"""
ES_STREAM_TYPE
"""
ES_STREAM_HEAD = 0
ES_STREAM_DATA = 1
ES_STREAM_END = 2


"""
ES_TRANS_TYPE
"""
ES_TRANS_NULL = 0x0
ES_TRANS_HIK = 0x1
ES_TRANS_MPEG2_PS = 0x2
ES_TRANS_MPEG2_TS = 0x3
ES_TRANS_RTP = 0x4
ES_TRANS_MPEG4 = 0x5
ES_TRANS_AVI = 0x7
ES_TRANS_GB_PS = 0x8
ES_TRANS_HLS_TS = 0x9
ES_TRANS_FLV = 0x0a
ES_TRANS_RAW = 0x10
ES_TRANS_MPEG4_FRONT = 0x0b
ES_TRANS_MPEG4_RESERVE = 0x0e


"""
ES_AUDIO_CODE_TYPE
"""
ES_AUDIO_CODE_TYPE_G722_1 = 0
ES_AUDIO_CODE_TYPE_G711_MU = 1
ES_AUDIO_CODE_TYPE_G711_A = 2
ES_AUDIO_CODE_TYPE_G723 = 3
ES_AUDIO_CODE_TYPE_MP1L2 = 4
ES_AUDIO_CODE_TYPE_MP2L2 = 5
ES_AUDIO_CODE_TYPE_G726 = 6
ES_AUDIO_CODE_TYPE_AAC = 7
ES_AUDIO_CODE_TYPE_RAW = 99


"""
ES_CONFIG_TYPE
"""
ES_CONFIG_ISP = 0
ES_CONFIG_TRANSTYPE = 1


"""
typedef int (*ESOpenSDK_MessageHandler)(HANDLE pHandle, 
                                        int code, 
                                        int eventType, 
                                        void *pUser);
"""
ES_OPENSDK_MESSAGE_CALLBACK = ctypes.CFUNCTYPE(ctypes.c_int, ctypes.c_void_p, ctypes.c_int, ctypes.c_int,
                                               ctypes.c_void_p)


"""
typedef int (*ESOpenSDK_DataCallBack)(HANDLE pHandle, 
                                      unsigned int dataType, 
                                      unsigned char *buf, 
                                      unsigned int buflen, 
                                      void* pUser);
"""
ES_OPENSDK_DATA_CALLBACK = ctypes.CFUNCTYPE(ctypes.c_int, ctypes.c_void_p, ctypes.c_uint,
                                            ctypes.POINTER(ctypes.c_uint8), ctypes.c_uint, ctypes.c_void_p)


class DeviceInfo(ctypes.Structure):
    """
    ES_DEVICE_INFO
    """
    _fields_ = [
        (dev_serial, ctypes.c_char * 64),
        (dev_channel_no, ctypes.c_int),
        (safe_key, ctypes.c_char * 16)
    ]


class RecordInfo(ctypes.Structure):
    """
    ES_RECORD_INFO
    """
    _fields_ = [
        (start_time, ctypes.c_char * 32),
        (stop_time, ctypes.c_char * 32),
        (rec_type, ctypes.c_int),
        (download_path, ctypes.c_char * 64)
    ]


class StreamCallback(ctypes.Structure):
    """
    ES_STREAM_CALLBACK
    """
    _fields_ = [
        (on_recvmessage, ES_OPENSDK_MESSAGE_CALLBACK),
        (on_recvdata, ES_OPENSDK_DATA_CALLBACK),
        (user, ctypes.c_void_p)
    ]


class IESOpenStream:
    def __init__(self):
        self.__lib = None

    def load_dll(self):
        if self.__lib is not None:
            return
        self.__lib = ctypes.CDLL(BASE_PATH + SDK_PATH + SHARED_OBJECT)

    def es_open_sdk_init(self, tcp_max_threads=12, ssl_max_threads=1):
        """
        int ESOpenSDK_Init(unsigned int tcp_max_threads = 12,
                           unsigned int ssl_max_threads = 1);
        """
        self.__lib.ESOpenSDK_Init.argtypes = (ctypes.c_uint, ctypes.c_uint)
        self.__lib.ESOpenSDK_Init.restype = ctypes.c_int
        return self.__lib.ESOpenSDK_Init(tcp_max_threads, ssl_max_threads)

    def es_open_sdk_fini(self):
        """
        int ESOpenSDK_Fini();
        """
        self.__lib.ESOpenSDK_Fini.restype = ctypes.c_int
        return self.__lib.ESOpenSDK_Fini()

    def es_open_sdk_init_with_app_key(self, app_key, platform_addr):
        """
        void ESOpenSDK_InitWithAppKey(const char* szAppKey,
                                      const char* szPlatformAddr);
        """
        self.__lib.ESOpenSDK_InitWithAppKey.argtypes = (ctypes.c_char_p, ctypes.c_char_p)
        self.__lib.ESOpenSDK_InitWithAppKey(app_key, platform_addr)

    def es_open_sdk_set_config_info(self, key, value):
        """
        void ESOpenSDK_SetConfigInfo(ES_CONFIG_TYPE iKey,
                                     int iValue);
        """
        self.__lib.ESOpenSDK_SetConfigInfo.argtypes = (ctypes.c_int, ctypes.c_int)
        self.__lib.ESOpenSDK_SetConfigInfo(key, value)

    def es_open_sdk_get_dev_info(self, token, dev_info, update, out_dev_info, out_len):
        """
        int ESOpenSDK_GetDevInfo(const char* szAccessToken,
                                 const ES_DEVICE_INFO& stDevInfo,
                                 const bool bUpdate,
                                 void** pOutDevInfo,
                                 int* iOutLen);
        """
        self.__lib.ESOpenSDK_GetDevInfo.argtypes = (ctypes.c_char_p, DeviceInfo, ctypes.c_bool,
                                                    ctypes.POINTER(ctypes.c_void_p), ctypes.POINTER(ctypes.c_int))
        self.__lib.ESOpenSDK_GetDevInfo.restype = ctypes.c_int
        self.__lib.ESOpenSDK_GetDevInfo(token, dev_info, update, out_dev_info, out_len)

    def es_open_sdk_search_video_record(self, token, dev_info, rec_info, out_rec_info, out_len):
        """
        int ESOpenSDK_SearchVideoRecord(const char* szAccessToken,
                                        const ES_DEVICE_INFO& stDevInfo,
                                        const ES_RECORD_INFO& stRecInfo,
                                        void** pOutRecInfo,
                                        int* iOutLen);
        """
        self.__lib.ESOpenSDK_SearchVideoRecord.argtypes = (ctypes.c_char_p, DeviceInfo, RecordInfo,
                                                           ctypes.POINTER(ctypes.c_void_p),
                                                           ctypes.POINTER(ctypes.c_int))
        self.__lib.ESOpenSDK_SearchVideoRecord.restype = ctypes.c_int
        self.__lib.ESOpenSDK_SearchVideoRecord(token, dev_info, rec_info, out_rec_info, out_len)

    def es_open_sdk_free_data(self, buf):
        """
        void ESOpenSDK_FreeData(void* pBuf);
        """
        self.__lib.ESOpenSDK_FreeData.argtypes = ctypes.c_void_p
        self.__lib.ESOpenSDK_FreeData(buf)

    def es_open_sdk_set_video_level(self, token, dev_info, video_level):
        """
        int ESOpenSDK_SetVideoLevel(const char* szAccessToken,
                                    const ES_DEVICE_INFO& stDevInfo,
                                    const int iVideoLevel);
        """
        self.__lib.ESOpenSDK_SetVideoLevel.argtypes = (ctypes.c_char_p, DeviceInfo, ctypes.c_int)
        self.__lib.ESOpenSDK_SetVideoLevel.restype = ctypes.c_int
        self.__lib.ESOpenSDK_SetVideoLevel(token, dev_info, video_level)

    def es_open_sdk_start_real_play(self, token, dev_info, callback, handler):
        """
        int ESOpenSDK_StartRealPlay(const char* szAccessToken,
                                    const ES_DEVICE_INFO& stDevInfo,
                                    const ES_STREAM_CALLBACK& stStreamCB,
                                    HANDLE& pHandle);
        """
        self.__lib.ESOpenSDK_StartRealPlay.argtypes = (ctypes.c_char_p, DeviceInfo, StreamCallback,
                                                       ctypes.POINTER(ctypes.c_void_p))
        self.__lib.ESOpenSDK_StartRealPlay.restype = ctypes.c_int
        self.__lib.ESOpenSDK_StartRealPlay(token, dev_info, callback, handler)

    def es_open_sdk_stop_real_play(self, handler):
        """
        int ESOpenSDK_StopRealPlay(const HANDLE pHandle);
        """
        self.__lib.ESOpenSDK_StopRealPlay.argtypes = ctypes.c_void_p
        self.__lib.ESOpenSDK_StopRealPlay.restype = ctypes.c_int
        self.__lib.ESOpenSDK_StopRealPlay(handler)

    def es_open_sdk_start_play_back(self, token, dev_info, rec_info, callback, handler):
        """
        int ESOpenSDK_StartPlayBack(const char* szAccessToken,
                                    const ES_DEVICE_INFO& stDevInfo,
                                    const ES_RECORD_INFO& stRecInfo,
                                    const ES_STREAM_CALLBACK& stStreamCB,
                                    HANDLE& pHandle);
        """
        self.__lib.ESOpenSDK_StartPlayBack.argtypes = (ctypes.c_char_p, DeviceInfo, RecordInfo,
                                                       StreamCallback, ctypes.POINTER(ctypes.c_void_p))
        self.__lib.ESOpenSDK_StartPlayBack.restype = ctypes.c_int
        self.__lib.ESOpenSDK_StartPlayBack(token, dev_info, rec_info, callback, handler)

    def es_open_sdk_stop_play_back(self, handler):
        """
        int ESOpenSDK_StopPlayBack(const HANDLE pHandle);
        """
        self.__lib.ESOpenSDK_StopPlayBack.argtypes = ctypes.c_void_p
        self.__lib.ESOpenSDK_StopPlayBack.restype = ctypes.c_int
        self.__lib.ESOpenSDK_StopPlayBack(handler)

    def es_open_sdk_start_voice_talk(self, token, dev_info, callback, handler):
        """
        int ESOpenSDK_StartVoiceTalk(const char* szAccessToken,
                                     const ES_DEVICE_INFO& stDevInfo,
                                     const ES_STREAM_CALLBACK& stStreamCB,
                                     HANDLE& pHandle);
        """
        self.__lib.ESOpenSDK_StartVoiceTalk.argtypes = (ctypes.c_char_p, DeviceInfo, StreamCallback,
                                                        ctypes.POINTER(ctypes.c_void_p))
        self.__lib.ESOpenSDK_StartVoiceTalk.restype = ctypes.c_int
        self.__lib.ESOpenSDK_StartVoiceTalk(token, dev_info, callback, handler)

    def es_open_sdk_stop_voice_talk(self, handler):
        """
        int ESOpenSDK_StopVoiceTalk(const HANDLE pHandle);
        """
        self.__lib.ESOpenSDK_StopVoiceTalk.argtypes = ctypes.c_void_p
        self.__lib.ESOpenSDK_StopVoiceTalk.restype = ctypes.c_int
        self.__lib.ESOpenSDK_StopVoiceTalk(handler)

    def es_open_sdk_send_voice_talk(self, handler, data, data_length):
        """
        int ESOpenSDK_SendVoiceTalk(const HANDLE pHandle, const unsigned char* pData, const int iDataLen);
        """
        self.__lib.ESOpenSDK_SendVoiceTalk.argtypes = (ctypes.c_void_p, ctypes.POINTER(ctypes.c_uint8), ctypes.c_int)
        self.__lib.ESOpenSDK_SendVoiceTalk.restype = ctypes.c_int
        self.__lib.ESOpenSDK_SendVoiceTalk(handler, data, data_length)


def main():
    if 'linux' not in PLATFORM:
        print('not supported system:', PLATFORM)
        return

    interface = IESOpenStream()
    interface.load_dll()
    interface.es_open_sdk_init()
    interface.es_open_sdk_fini()


if __name__ == '__main__':
    main()
