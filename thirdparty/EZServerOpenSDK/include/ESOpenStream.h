/** \file      OpenNetStreamInterFace.h
 *  \copyright HangZhou Hikvision System Technology Co.,Ltd. All Right Reserved.
 *  \brief     开放Server SDK接口定义
 *
 *  \author    Pi.Kongxuan
 *  \date      2017/09/14
 *
 *  \note      history:
 *  \note      V1.0.0 2017/09/14 peter create 
 */

#ifndef _H_EZ_SERVER_OPENSDK_H_
#define _H_EZ_SERVER_OPENSDK_H_

#ifdef __cplusplus
extern "C" {
#endif


typedef void* HANDLE;


/** \enum  ES_STREAM_EVENT  
 *  \brief 定义取流消息号
 */
typedef enum
{
    ES_NET_EVENT_CONNECTED 		= 0,				//连接成功						
    ES_NET_EVENT_DISCONNECTED 	= 1,				//断开连接
    ES_STREAM_FAIL				= 2,				//请求取流失败
    ES_URL_INVALID				= 3,				//无效url
    ES_PACKET_PARSE_FAIL		= 4					//解析报文失败
}ES_STREAM_EVENT;

/** \enum  ES_STREAM_CODE  
 *  \brief 定义取流错误码
 */
typedef enum
{
    ES_STREAM_CLIENT_RET_STATUS_BASE 		= 5000,                      //服务端起始响应码
    ES_STREAM_CLIENT_RET_STATUS_302  		= 5302,                      //重定向请求
    ES_STREAM_CLIENT_RET_STATUS_402  		= 5402,                      //回放在不到录像文件
    ES_STREAM_CLIENT_RET_STATUS_403  		= 5403,                      //操作码或信令密钥与设备不匹配
    ES_STREAM_CLIENT_RET_STATUS_404  		= 5404,                      //设备不在线
    ES_STREAM_CLIENT_RET_STATUS_405  		= 5405,                      //流媒体向设备发送或接受信令超时/cas响应超时
    ES_STREAM_CLIENT_RET_STATUS_406  		= 5406,                      //token失效
    ES_STREAM_CLIENT_RET_STATUS_407  		= 5407,                      //客户端的URL格式错误
    ES_STREAM_CLIENT_RET_STATUS_409  		= 5409,                      //预览开启隐私保护
    ES_STREAM_CLIENT_RET_STATUS_410  		= 5410,                      //设备达到最大连接数
    ES_STREAM_CLIENT_RET_STATUS_411  		= 5411,                      //token无权限
    ES_STREAM_CLIENT_RET_STATUS_412  		= 5412,                      //session不存在
    ES_STREAM_CLIENT_RET_STATUS_413  		= 5413,                      //验证token的他异常（不具体）
    ES_STREAM_CLIENT_RET_STATUS_415  		= 5415,                      //设备通道错
    ES_STREAM_CLIENT_RET_STATUS_451  		= 5451,                      //设备不支持的码流类型
    ES_STREAM_CLIENT_RET_STATUS_452  		= 5452,                      //设备连接预览流媒体服务器失败
    ES_STREAM_CLIENT_RET_STATUS_454  		= 5454,                      //会话不存在
    ES_STREAM_CLIENT_RET_STATUS_491  		= 5491,                      //相同请求正在处理，拒绝本次处理
    ES_STREAM_CLIENT_RET_STATUS_500  		= 5500,                      //流媒体服务器内部处理错误
    ES_STREAM_CLIENT_RET_STATUS_501  		= 5501,                      //vtm构造级联失败
    ES_STREAM_CLIENT_RET_STATUS_503  		= 5503,                      //vtm分配vtdu服务器失败
    ES_STREAM_CLIENT_RET_STATUS_544  		= 5544,                      //设备返回无视频源
    ES_STREAM_CLIENT_RET_STATUS_545  		= 5545,						 //视频分享时间已经结束
    ES_STREAM_CLIENT_RET_STATUS_546  		= 5546,                      //取流并发路数限制
    ES_STREAM_CLIENT_RET_STATUS_556  		= 5556,                      //ticket校验失败
    ES_STREAM_CLIENT_RET_STATUS_560  		= 5600,                      //群组分享取流二次验证失败

    ES_STREAM_CLIENT_RET_EXCEPTION			= 6700,						//异常数据包
    ES_STREAM_CLIENT_RET_OVER				= 6701,						//结束数据包
    
    ES_STREAM_CLIENT_RET_INVALID_PACKET	    = 9000,						//无效包，包过大
    ES_STREAM_CLIENT_RET_INVALID_HOST		= 9001						//地址不合法
}ES_STREAM_CODE;

/** \enum  ES_API_ERROR  
 *  \brief 接口错误码
 */
typedef enum  {
    ES_NOERROR                  = 0,          //接口调用成功
    ES_ERROR_BadParams          = 1,		  //传入参数不符合要求
    ES_ERROR_AllocMemoryFailed  = 2,          //内存分配失败
    ES_ERROR_Session_Invalid    = 3           //会话异常
}ES_API_CODE;

/** \enum  ES_DATA_TYPE 
 *  \brief 音视频流数据类型
 */
typedef enum {
    ES_STREAM_HEAD    = 0,      ///< 流头
    ES_STREAM_DATA    = 1,		///< 流数据
    ES_STREAM_END     = 2       ///< 结束标记
}ES_STREAM_TYPE;

/** \enum  ES_TRANS_TYPE  
 *  \brief 转封装类型
 */
typedef enum
{
    ES_TRANS_NULL           = 0x0,      //NULL
    ES_TRANS_HIK            = 0x1,      //海康文件层，可用于传输和存储
    ES_TRANS_MPEG2_PS       = 0x2,      //PS文件层，主要用于存储，也可用于传输
    ES_TRANS_MPEG2_TS       = 0x3,      //TS文件层，主要用于传输，也可用于存储
    ES_TRANS_RTP            = 0x4,      //RTP文件层，用于传输
    ES_TRANS_MPEG4          = 0x5,      //MPEG4文件层，用于存储（索引后置方式）
    ES_TRANS_AVI            = 0x7,      //AVI文件层，用于存储
    ES_TRANS_GB_PS          = 0x8,      //国标PS，主要用于国标场合
    ES_TRANS_HLS_TS         = 0x9,      //符合HLS的TS封装，区分普通TS封装
    ES_TRANS_FLV            = 0x0a,     //FLV封装
    ES_TRANS_RAW            = 0x10,     //es流前有参数信息的裸码流(源封装)（很老的版本，现在不推荐使用）
    ES_TRANS_MPEG4_FRONT    = 0x0b,     //MPEG4文件层（索引前置方式）
    ES_TRANS_MPEG4_RESERVE  = 0x0e      //MPEG4文件层（前置索引预留刷新）
}ES_TRANS_TYPE;

/** \enum  ES_AUDIO_CODE_TYPE  
 *  \brief 定义语音编码类型
 */
typedef enum
{
    ES_AUDIO_CODE_TYPE_G722_1     = 0,   // G722_1
    ES_AUDIO_CODE_TYPE_G711_MU    = 1,   // G711_MU
    ES_AUDIO_CODE_TYPE_G711_A     = 2,   // G711_A
    ES_AUDIO_CODE_TYPE_G723       = 3,   // G723
    ES_AUDIO_CODE_TYPE_MP1L2      = 4,   // MP1L2
    ES_AUDIO_CODE_TYPE_MP2L2      = 5,   // MP2L2
    ES_AUDIO_CODE_TYPE_G726       = 6,   // G726
    AUDIO_CODE_TYPE_AAC           = 7,   // AAC
    AUDIO_CODE_TYPE_RAW           = 99,  // RAW
}ES_AUDIO_CODE_TYPE;

typedef struct ST_ES_DEVICE_INFO
{
	char          szDevSerial[64];		//设备序列号
	int  	      iDevChannelNo;		//设备通道号
	char	      szSafeKey[16];		//设备验证码
}ES_DEVICE_INFO;

typedef struct ST_ES_RECORD_INFO
{
	char    szStartTime[32];		//录像开始时间
	char    szStopTime[32];			//录像结束时间
	int 	iRecType;			    //录像来源, 0:混合搜索, 1:云存储, 2:本地录像
    char    szDownloadPath[64];     //录像下载地址, 目前只有云存储回放时使用此参数.
}ES_RECORD_INFO;

/** \enum  ESCONFIG_TYPE 
 *  \brief 配置类型, 调用ESOpenSDK_SetConfigInfo接口进行配置
 */
typedef enum
{
    ESCONFIG_ISP,       //配置运营商类型,默认配置为电信, 0:电信; 1:联通; 2:移动; 4:华数; 9:内网
    ESCONFIG_TRANSTYPE  //转封装类型 参考#ES_TRANS_TYPE
}ES_CONFIG_TYPE;

/** 
 *  \brief 信息回调
 *  \param pHandle      取流句柄
 *  \param code         取流错误码 参考#ES_STREAM_CODE
 *	\param eventType    消息号 参考#ES_STREAM_EVENT
 *  \param pUser		用户自定义数据 
 *
 */
typedef int (*ESOpenSDK_MessageHandler)(HANDLE pHandle, int code, int eventType, void *pUser);

/** 
 *  \brief 数据回调格式
 *  \param phandle  取流句柄
 *  \param enType   数据类型 参见 #ES_STREAM_TYPE
                     0：如果是预览、回放代表数据头，如果是对讲, buf代表设备的音频编码类型int
                     1：数据
                     2：结束标志
                     3：服务器收流异常中止
 *  \param buf      数据内容
 *  \param buflen   数据长度
 *  \param pUser    用户自定义数据
 */
typedef int (*ESOpenSDK_DataCallBack)(HANDLE pHandle, unsigned int dataType, unsigned char *buf,  unsigned int buflen, void* pUser);


typedef struct ST_ES_STREAM_CALLBACK
{
	ESOpenSDK_MessageHandler 	on_recvmessage; //消息回调
	ESOpenSDK_DataCallBack 		on_recvdata;	//数据回调
	void*						pUser;			//用户自定义类型
}ES_STREAM_CALLBACK;

/** \defgroup init 开放SDK初始化
 *  @{
 */

/** 
 *  \brief 初始化库
 *  \param[in] tcp_max_threads tcp链接分配的线程个数.
 *  \param[in] ssl_max_threads ssl链接分配的线程个数(云存储回放会使用到).
 *  \return 0表示成功，-1表示失败
 *  \sa ESOpenSDK_Fini()
 *
 *  \note
 *  该接口必须在调用其他接口之前调用
 */
int ESOpenSDK_Init(unsigned int tcp_max_threads = 12,unsigned int ssl_max_threads = 1);

/** 
 *  \brief  反初始化库
 *  \return 0表示成功，-1表示失败
 *  \sa OpenSDK_InitLib()
 */
int ESOpenSDK_Fini();

/** 
 *  \brief 支持配置平台地址
 *  \param[in] szAppKey 向开放平台申请APPKey.
 *  \param[in] szPlatformAddr 平台域名:开放平台后台地址，默认地址为：https://open.ys7.com .
 *  \return 0表示成功，-1表示失败
 *  \sa 
 *  \note
 *  该接口必须在调用取流, 回放, 对讲接口之前调用
 */
void ESOpenSDK_InitWithAppKey(const char* szAppKey, const char* szPlatformAddr);

/** 
*  \brief  全局配置信息, 根据ESCONFIG_TYPE进行配置
*  \param[in] iKey    配置类型
*  \param[in] iValue  配置数值
 *  \sa 
 */
void ESOpenSDK_SetConfigInfo(ES_CONFIG_TYPE iKey, int iValue);

/** @} */ // end of init



/** \defgroup data 数据接口
 *  @{
 */

/** 
 *  \brief 获取设备详细信息, 包括预览能力级, PTZ, 对讲能力级等.
 *  \param[in]  szAccessToken   认证信息
 *  \param[in]  stDevInfo       设备信息
 *  \param[in]  bUpdate         是否重新获取设备详细信息, true:重新从萤石平台拿数据, 否则拿缓存信息. 
                                true的时机为用户重新登录,需要刷新设备信息,设备加密状态更新
 *	\param[out] pOutDevInfo 	设备信息，需要调用ESOpenSDK_FreeData接口释放
 *	\param[out] iOutLen			pOutDevInfo的长度
 *
 *  \note 
 *  报警信息列表JSON格式如下：
 *  \code {.json}
 *  {
 *		"devSerial":"426931084",	        // 设备序列号
 *		"channelNo":1,				        // 通道号
 *		"videoLevel":2,				        // 视频质量 2-高清 1-标清 0-流畅
 *		"type":1,					        // 1 网络录像机 2 模拟录像机
 *		"isEncrypt":0,				        // 是否开启安全模式:1-开启,0-关闭, 即视频图像是否加密
 *      "support_talk":1,                   // 是否支持对讲:1-支持, 0-不支持
 *      "support_ptz":0,                    // 是否支持云台控制:1-支持, 0-不支持
 *      "ptz_top_bottom":1,                 // 是否支持云台上下:1-支持, 0-不支持
 *      "ptz_left_right":1                  // 是否支持云台左右:1-支持, 0-不支持
 *      "ptz_preset":1,                     // 是否支持云台预置点:1-支持, 0-不支持
 *      "videoQualityInfos": [              // 设备支持的预览能力级详情
 *          {
 *              "videoQualityName":"流畅",  // 清晰度名称
 *              "videoLevel":0,             // 清晰度数值
 *              "streamType":2              // 主子码流类型
 *          },
 *          {
 *              "videoQualityName":"均衡",
 *              "videoLevel":1,
 *              "streamType":2
 *          },
 *          {
 *              "videoQualityName":"高清",
 *              "videoLevel":2,
 *              "streamType":1
 *          }
 *      ]
 *	}
 *  \endcode
 *  \return 0表示成功，其他值表示失败
 */
int ESOpenSDK_GetDevInfo(const char* szAccessToken, const ES_DEVICE_INFO& stDevInfo, const bool bUpdate, void** pOutDevInfo, int* iOutLen);

/** 
 *  \brief 录像搜索，包含云存储和设备SD卡录像
 *  \param[in] szAccessToken   认证信息
 *  \param[in] stDevInfo       设备信息 
 *  \param[in] stRecInfo       录像信息
 *	\param[out] pOutRecInfo    录像片段信息，需要调用ESOpenSDK_FreeData接口释放
 *	\param[out] iOutLen		   pOutRecInfo的长度
 *  \return 非NULL 成功:NULL 失败
 *  \note
 *  录像片段信息格式为:
 *  {
 *      "dataSize":2
 *      "data":[
 *          {
 *          "beginTime":"2017-09-25 00:07:13",          //录像片段开始时间
 *          "endTime":"2017-09-25 00:09:35",            //录像片段结束时间
 *          "recType":1                                 //录像片段类型, 1:云存储, 2:本地存储
 *          "downloadPath":"cloud.ys7.com:88823"        //如果是云存储, 此字段为云存储下载地址
 *          "encrypt" : 1,                              //如果是云存储, 此字段为加密标识, 1:标识加密, 0不加密
 *          "fileSize" : 404296                         //如果是云存储, 此字段文件大小,单位为B
 *          },
 *          {
 *          "beginTime":"2017-09-25 00:09:35",
 *          "endTime":"2017-09-25 00:11:49",
 *          "recType":2
 *          }
 *       ]
 *  }
 *
 */
int ESOpenSDK_SearchVideoRecord(const char* szAccessToken, const ES_DEVICE_INFO& stDevInfo, const ES_RECORD_INFO& stRecInfo, void** pOutRecInfo, int* iOutLen);

/** 
 *  \brief 销毁SDK分配的内存
 *  \param[in] pBuf SDK分配的内存
 *  \return 0表示成功，-1表示失败
 */
void ESOpenSDK_FreeData(void* pBuf);

/** @} */ // end of data


/** \defgroup play 预览接口
 *  @{
 */

/** 
 *  \brief 设置或者切换清晰度
 *  \param[in] szAccessToken 认证信息
 *  \param[in] stDevInfo     设备信息
 *  \param[in] iVideoLevel   视频质量，输入范围在0-2之间, 切换前需判断平台是否支持要切换的清晰度
 *  \return 0表示成功，非0表示失败, 返回值是错误码
 */
int ESOpenSDK_SetVideoLevel(const char* szAccessToken, const ES_DEVICE_INFO& stDevInfo, const int iVideoLevel);

/** 
 *  \brief 开始播放, 消息回调判断取流是否成功
 *  \param[in] szAccessToken 认证信息
 *  \param[in] stDevInfo     设备信息
 *  \param[in] stStreamCB    异步回调信息, 包括消息回调和数据回调
 *  \param[out] pHandle      取流句柄, 用于停止取流
 *  \return 0表示成功，非0表示失败, 返回值是错误码
 *  \sa ESOpenSDK_StopRealPlay
 */
int ESOpenSDK_StartRealPlay(const char* szAccessToken, const ES_DEVICE_INFO& stDevInfo, const ES_STREAM_CALLBACK& stStreamCB, HANDLE& pHandle);

/** 
 *  \brief 停止播放播放
 *  \param[in] phandle ESOpenSDK_StartRealPlay产生的handle
 *  \return 0表示成功，非0表示失败
 *  \sa ESOpenSDK_StartRealPlay()
 */
int ESOpenSDK_StopRealPlay(const HANDLE pHandle);

/** @} */ // end of play

/** \defgroup playback 回放接口
 *  @{
 */

/** 
*  \brief 开始回放, 消息回调判断取流是否成功
 *  \param[in] szAccessToken   认证信息
 *  \param[in] stDevInfo       设备信息
 *  \param[in] stVideoInfo     录像信息
 *  \param[in] stStreamCB      异步回调信息, 包括消息回调和数据回调
 *  \param[out] pHandle        取流句柄, 用于停止取流
 *  \return 0表示成功，非0表示失败, 返回值是错误码
 *  \sa ESOpenSDK_StopPlayBack()
 *  \note 
 *  时间格式为：yyyy-MM-dd hh:mm:ss
 */
int ESOpenSDK_StartPlayBack(const char* szAccessToken, const ES_DEVICE_INFO& stDevInfo, const ES_RECORD_INFO& stRecInfo, const ES_STREAM_CALLBACK& stStreamCB, HANDLE& pHandle);

/** 
 *  \brief 停止回放
 *  \param[in] phandle ESOpenSDK_StartPlayBack产生的handle
 *  \return 0表示成功，非0表示失败
 *	\sa ESOpenSDK_StartPlayBack()
 */
int ESOpenSDK_StopPlayBack(const HANDLE pHandle);

/** @} */ // end of playback

/** \defgroup voice_talk 语音对讲
 *  @{
 */

/** 
 *  \brief 开启语音对讲, 消息回调判断取流是否成功
 *  \param[in] szAccessToken   认证信息
 *  \param[in] stDevInfo       设备信息
 *  \param[in] stStreamCB      异步回调信息, 包括消息回调和数据回调
 *  \param[out] pHandle        取流句柄, 用于停止取流
 *  \return 0表示成功，非0表示失败, 返回值是错误码
 *  \sa ESOpenSDK_StopVoiceTalk()
 */
int ESOpenSDK_StartVoiceTalk(const char* szAccessToken, const ES_DEVICE_INFO& stDevInfo, const ES_STREAM_CALLBACK& stStreamCB, HANDLE& pHandle);

/** 
 *  \brief 发送语音数据
 *  \param[in] szSessionId 会话Id
 *  \return 0表示成功，-1表示失败
 *  \sa ESOpenSDK_StartVoiceTalk()
 */
int ESOpenSDK_StopVoiceTalk(const HANDLE pHandle);

/** 
 *  \brief 
 *  \param[in] szSessionId 会话Id
 *  \return 0表示成功，-1表示失败
 */
int ESOpenSDK_SendVoiceTalk(const HANDLE pHandle, const unsigned char* pData, const int iDataLen);

/** @} */ // end of voice_talk

#ifdef __cplusplus
}
#endif

#endif