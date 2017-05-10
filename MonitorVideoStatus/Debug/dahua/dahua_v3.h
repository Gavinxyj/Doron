//
// Copyright (c) 2010, 浙江大华技术股份有限公司
// All rights reserved.
// 
// 文 件 名：dhplaysdk.h
// 摘    要：H3C平台接入接口定义
//
// 修订记录：创建
// 完成日期：2010年10月25日
// 作    者：
//
// 修订记录：按照新的接口定义文档"DB 33/ T629.5—2010"进行接口的增加以及修改
// 完成日期：2011年03月29日
// 作    者：
//

#ifndef _DHPLAYSDK_H
#define _DHPLAYSDK_H

#ifdef DHPLAYSDK_EXPORTS
#define DHPLAYSDK_API __declspec(dllexport)
#else
#define DHPLAYSDK_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

// 错误码
enum
{
	DH_ERR_ERROR   = -1,
	DH_ERR_NOERROR =  0
};

// 播放速度
typedef enum _PLAY_SPEED
{
	PLAY_STATUS_16_BACKWARD = 0,     /**< 16倍速后退播放 */
	PLAY_STATUS_8_BACKWARD = 1,      /**< 8倍速后退播放 */
	PLAY_STATUS_4_BACKWARD = 2,      /**< 4倍速后退播放 */
	PLAY_STATUS_2_BACKWARD = 3,      /**< 2倍速后退播放 */
	PLAY_STATUS_1_BACKWARD = 4,      /**< 正常速度后退播放 */
	PLAY_STATUS_HALF_BACKWARD = 5,   /**< 1/2倍速后退播放 */
	PLAY_STATUS_QUARTER_BACKWARD = 6,/**< 1/4倍速后退播放 */
	PLAY_STATUS_QUARTER_FORWARD = 7, /**< 1/4倍速播放 */
	PLAY_STATUS_HALF_FORWARD = 8,    /**< 1/2倍速播放 */
	PLAY_STATUS_1_FORWARD = 9,       /**< 正常速度前进播放 */
	PLAY_STATUS_2_FORWARD = 10,      /**< 2倍速前进播放 */
	PLAY_STATUS_4_FORWARD = 11,      /**< 4倍速前进播放 */
	PLAY_STATUS_8_FORWARD = 12,      /**< 8倍速前进播放 */
	PLAY_STATUS_16_FORWARD = 13      /**< 16倍速前进播放 */
}PLAY_SPEED;

//
// 该功能未实现
// 描    述: 消息回调函数指针
// 输入参数:
//			 iSessionId：preview_start或playback_start成功的返回值
//			 iMsgType：消息回调类型，需要详细定义
//			 iMsgCode：消息码，需要详细定义
//			 szMsg：消息描述
//			 pUsrData：用户自定义数据，preview_start或playback_start传入的pUsrData字段。
// 输出参数: 无
// 返 回 值: 0 表示成功,-1表示失败，get_lasterror()获取错误码
//
typedef int (__stdcall *CBF_Msg)(int iSessionId, int iMsgType, int iMsgCode, char* szMsg, void* pUsrData);

//
// 该功能未实现
// 描    述: 数据回调函数指针
// 输入参数:
//			 iSessionId：preview_start或playback_start成功的返回值
//			 iSessionId：preview_start或playback_start成功的返回值
//			 iStreamType：消息回调类型，0为头数据，1为视频数据，2为音频数据。
//			 pData：数据指针，去掉RTP头及扩展头数据
//			 iDataLen：数据长度
//			 pUsrData：用户自定义数据，preview_start或playback_start传入的pUsrData字段
// 输出参数: 无
// 返 回 值: 0表示成功,-1表示失败，get_lasterror()获取错误码
//
typedef int (__stdcall* CBF_Stream)(int iSessionId, int iStreamType, char* pData, int iDataLen, void* pUsrData);

//
// 函数描述: 初始化插件接口
// 输入参数: 无
// 输出参数: 无
// 返 回 值: 0表示成功,-1表示失败，get_lasterror()获取错误码
//
DHPLAYSDK_API int __stdcall media_init();

//
// 函数描述: 销毁插件接口
// 输入参数: 无
// 输出参数: 无
// 返 回 值: 0表示成功,-1表示失败，get_lasterror()获取错误码
//
DHPLAYSDK_API void __stdcall media_terminate();

//
// 函数描述: 全部停止实时预览
// 输入参数: 无
// 输出参数: 无
// 返 回 值: 0表示成功,-1表示失败，get_lasterror()获取错误码
//
DHPLAYSDK_API int __stdcall stop_all();

//
// 函数描述: 开始预览
// 输入参数:
//			 wnd：播放窗口句柄，如果wnd为NULL，表示不解码只回调码流。
//			 port：接收数据的端口号
//			 pUsrData：用户自定义数据
// 输出参数: 无
// 返 回 值: >=0表示成功,-1表示失败，get_lasterror()获取错误码
//
DHPLAYSDK_API int __stdcall preview_start(void* wnd, 
										  unsigned short port, 
										  void* pUsrData);

//
// 未实现
// 函数描述: 设置消息回调
// 输入参数:
//			 pCbf:消息回调函数
// 输出参数: 无
// 返 回 值: 0表示成功,-1表示失败，get_lasterror()获取错误码
//
DHPLAYSDK_API int __stdcall set_msgcbf(CBF_Msg pCbf);

//
// 未实现
// 函数描述: 设置取流回调
// 输入参数: 
//			 pCbf:取流回调函数
// 输出参数: 无
// 返 回 值: 0表示成功,-1表示失败，get_lasterror()获取错误码
//
DHPLAYSDK_API int __stdcall set_streamcbf(CBF_Stream pCbf);

//
// 函数描述: 停止实时预览
// 输入参数:
//			 pConf:级联客户端配置信息
// 输出参数: 无
// 返 回 值: 0表示成功,-1表示失败，get_lasterror()获取错误码
//
DHPLAYSDK_API int __stdcall preview_stop(int sessionid);

//
// 函数描述: 开始回放
// 输入参数:
//			 wnd：播放窗口句柄
//			 port：接收数据的端口号
//			 sdp：rtsp DESCRIBE响应时带回来的SDP信息
//			 filename：保存的录像文件名
//			 pUsrData：用户自定义数据
// 输出参数: 无
// 返 回 值:0表示成功,-1表示失败，get_lasterror()获取错误码
//
DHPLAYSDK_API int __stdcall playback_start(void* wnd, 
										   unsigned short port, 
										   const char* sdp, 
										   char* filename, 
										   void* pUsrData);

//
// 函数描述: 停止回放
// 输入参数:
//			 sessionid：play_back成功的返回值。
// 输出参数: 无
// 返 回 值: 0表示成功,-1表示失败，get_lasterror()获取错误码
//
DHPLAYSDK_API int __stdcall playback_stop(int sessionid);

//
// 函数描述: 抓图
// 输入参数:
//			 sessionid：preview_start或playback_start成功的返回值。
//			 picturename：抓图保存的文件名
//			 iPicMode：0 表示JPEG，1 表示BMP
// 输出参数: 无
// 返 回 值: 0表示成功,-1表示失败，get_lasterror()获取错误码
//
DHPLAYSDK_API int __stdcall picture_capture(int sessoinid, const char* picturename, int iPicMode);

//
// 函数描述: 设置音量大小
// 输入参数:
//			 sessionid: preview_start或playback_start成功的返回值。
//			 volume:0-100，100表示音量最大，0表示静音。
// 输出参数: 无
// 返 回 值: 0表示成功,-1表示失败，get_lasterror()获取错误码
//
//DHPLAYSDK_API int __stdcall set_audio_volume(int sessionid, int volume);

// 
// 函数描述: 获取错误码，错误码定义应与PART3附录B一致。
// 输入参数	
// 输出参数	
// 返 回 值: 返回错误号
//
DHPLAYSDK_API int __stdcall get_lasterror();


//
// 名称 : playback_control回放速度控制
// 功能 : 回放控制一路历史回放
// 输入 : port       -- rtp端口
//        ctrl_cmd  -- 回放控制命令, 定义如下
// 		  enum ctrl_cmd    //-- 回放控制命令, 定义如下
//        {
//              HTVIDEO_CONTROL_START   =  1   ,    // 开始/继续播放
//              HTVIDEO_CONTROL_PAUSE   =  2   ,    // 暂停播放
//              HTVIDEO_CONTROL_STOP    =  3  ,     // 停止播放
//              HTVIDEO_CONTROL_NORMAL  =  4  ,     // 正常速度
//              HTVIDEO_CONTROL_FAST    =  5  ,     // 快放
//              HTVIDEO_CONTROL_SLOW    =  6  ,     // 慢放
//              HTVIDEO_CONTROL_SEEK    =  7        // 拖动, 清空播放缓冲
//        };
//        *psz_para  -- 回放控制参数, 保留
// 注意 : 新版协议无此接口，因此未实现
//
DHPLAYSDK_API void  __stdcall playback_control(unsigned short port, long ctrl_cmd, char* psz_para);

// 
// 函数描述: 设置回放速度倍速值
// 输入参数	speed：回放速度倍速值，1表示正常回放，2表示2倍速回放，4表示4倍速回放，以此类推
// 输出参数	无
// 返 回 值: 0表示成功,-1表示失败，get_lasterror()获取错误码
//
DHPLAYSDK_API void __stdcall set_playbackspeed(int sessoinid, int speed);



















// 
// 函数描述: 启动本地录像
// 输入参数:
//			 sessionid：preview_star或者playback_start或者playlocal_start函数的返回值；
//			 filename： 本地录像的文件名称，如：  "d:\xxx\RecordFile.dahua_v3"，RecordFile 由调用者命名（包括路径），dahua_v3:对应厂家的decodertag标识；
// 输出参数: 无	
// 返 回 值: 0表示成功，-1表示失败
//
DHPLAYSDK_API int __stdcall record_start(int sessionid, char * filename);

// 
// 函数描述: 停止本地录像
// 输入参数:
//			 sessionid：preview_star或者playback_start或者playlocal_start函数的返回值；
// 输出参数: 无	
// 返 回 值: 无
//
DHPLAYSDK_API void __stdcall record_stop(int sessionid);

// 
// 函数描述: 启动本地录像播放
// 输入参数:
//			 wnd：		播放视频窗口句柄
//			 filename： 播放的本地文件名称
//			 pUserData：用户自定义数据
// 输出参数: 无	
// 返 回 值: sessionid
//
DHPLAYSDK_API int __stdcall playlocal_start(void * wnd, char * filename, void * pUserData);

// 
// 函数描述: 停止本地录像播放
// 输入参数:
//			 sessionid：preview_star或者playback_start或者playlocal_start函数的返回值；
// 输出参数: 无	
// 返 回 值: 无
//
DHPLAYSDK_API void __stdcall playlocal_stop(int sessionid);

// 
// 函数描述: 查询当前本地文件的播放总时间长度
// 输入参数:
//			 sessionid：playlocal_start函数的返回值
// 输出参数: 无	
// 返 回 值: 当前本地文件的播放总时间，相对时间，以秒为单位
//
DHPLAYSDK_API int __stdcall fileplaytotaltime_get(int sessionid);

// 
// 函数描述: 查询当前本地录像播放进度
// 输入参数:
//			 sessionid：playlocal_start函数的返回值
// 输出参数: 无	
// 返 回 值: 当前本地文件的播放时间点，相对时间，以秒为单位
//
DHPLAYSDK_API int __stdcall fileplaycurtime_get(int sessionid);

// 
// 函数描述: 设置当前本地录像播放时间点
// 输入参数:
//			 sessionid：playlocal_start函数的返回值
//			 itime    ：需要播放的时间点，相对时间，以秒为单位
// 输出参数: 无	
// 返 回 值: 0表示成功，-1表示失败
//
DHPLAYSDK_API int __stdcall fileplaycurtime_set(int sessionid, int itime);

// 
// 函数描述: 播放流控接口
// 输入参数:
//			 sessionid：playlocal_start函数的返回值
//			 speed    ：设置的播放倍速，倍速定义如下：
// 						PLAY_STATUS_16_BACKWARD = 0,     /**< 16倍速后退播放 */
// 						PLAY_STATUS_8_BACKWARD = 1,      /**< 8倍速后退播放 */
//						PLAY_STATUS_4_BACKWARD = 2,      /**< 4倍速后退播放 */
// 						PLAY_STATUS_2_BACKWARD = 3,      /**< 2倍速后退播放 */
// 						PLAY_STATUS_1_BACKWARD = 4,      /**< 正常速度后退播放 */
// 						PLAY_STATUS_HALF_BACKWARD = 5,   /**< 1/2倍速后退播放 */
// 						PLAY_STATUS_QUARTER_BACKWARD = 6,/**< 1/4倍速后退播放 */
// 						PLAY_STATUS_QUARTER_FORWARD = 7, /**< 1/4倍速播放 */
// 						PLAY_STATUS_HALF_FORWARD = 8,    /**< 1/2倍速播放 */
// 						PLAY_STATUS_1_FORWARD = 9,       /**< 正常速度前进播放 */
// 						PLAY_STATUS_2_FORWARD = 10,      /**< 2倍速前进播放 */
// 						PLAY_STATUS_4_FORWARD = 11,      /**< 4倍速前进播放 */
// 						PLAY_STATUS_8_FORWARD = 12,      /**< 8倍速前进播放 */
// 						PLAY_STATUS_16_FORWARD = 13      /**< 16倍速前进播放 */

// 输出参数: 无	
// 返 回 值: 0表示成功，-1表示失败
//
DHPLAYSDK_API int __stdcall playspeed_set(int sessionid, int speed);

// 
// 函数描述: 暂停当前本地录像播放
// 输入参数:
//			 sessionid：playlocal_start函数的返回值
// 输出参数: 无	
// 返 回 值: 0表示成功，-1表示失败
//
DHPLAYSDK_API int __stdcall play_pause(int sessionid);

// 
// 函数描述: 恢复本地录像播放
// 输入参数:
//			 sessionid：playlocal_start函数的返回值
// 输出参数: 无	
// 返 回 值: 0表示成功，-1表示失败
//
DHPLAYSDK_API int __stdcall play_resume(int sessionid);

// 
// 函数描述: 启动录像下载到本地录像
// 输入参数:
//			 port    ：本地收流端口
//			 SDP     ：rtsp DESCRIBE响应时携带的SDP信息
//			 filename：本地录像的文件名称，如：  "d:\xxx\RecordFile.dahua_v3"，RecordFile 由调用者命名（包括路径），dahua_v3:对应厂家的decodertag标识；
//			 pUsrData：回调时的用户自定义数据

// 输出参数: 无	
// 返 回 值: sessionid
//
DHPLAYSDK_API int __stdcall download_start(unsigned short port, char * SDP, char * filename, void * pUsrData);

// 
// 函数描述: 停止录像下载保存为本地录像
// 输入参数:
//			 sessionid：download_start函数的返回值
// 输出参数: 无	
// 返 回 值: 无
//
DHPLAYSDK_API void __stdcall download_stop(int sessionid);

// 
// 函数描述: 设置播放静音
// 输入参数:
//			 sessionid：playback_start或者playlocal_start函数的返回值；
// 输出参数: 无	
// 返 回 值: 0表示成功，-1表示失败
//
DHPLAYSDK_API int __stdcall sound_stop(int sessionid);

// 
// 函数描述: 取消播放静音
// 输入参数:
//			 sessionid：playback_start或者playlocal_start函数的返回值；
// 输出参数: 无	
// 返 回 值: 无
//
DHPLAYSDK_API void __stdcall sound_play(int sessionid);

// 
// 函数描述: 设置播放时音量
// 输入参数:
//			 sessionid：playback_start或者playlocal_start函数的返回值
//			 volume   ：为设置的音量， 0 -- 100，100为最高音量
// 输出参数: 无	
// 返 回 值: 无
//
DHPLAYSDK_API int __stdcall volume_set(int sessionid, unsigned short volume);










#ifdef  __cplusplus
}
#endif

#endif