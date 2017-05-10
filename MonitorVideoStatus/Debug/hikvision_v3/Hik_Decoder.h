

#ifndef _HIK_DECODER_H_
#define _HIK_DECODER_H_

#if defined(WIN32)
    #if defined(HIKVISION_DECODER_EXPORTS)
        #define HIK_DECODER_API extern "C" __declspec( dllexport )
    #else
        #define HIK_DECODER_API extern "C" __declspec( dllimport )
    #endif
#else
    #define HIK_DECODER_API extern "C"
#endif

#define  HIK_STREAM_TYPE_HEAD		0
#define  HIK_STREAM_TYPE_VIDEO		1
#define  HIK_STREAM_TYPE_AUDIO		2
#define  HIK_STREAM_TYPE_END		100

#define  HIK_MSG_TYPE_CLOSE			0		//连接断开
#define  HIK_MSG_TYPE_ERROR			1		//接收数据错误


enum PLAY_STATUS_SPEED
{
	PLAY_STATUS_16_BACKWARD = 0,	 //< 16倍速后退播放 
	PLAY_STATUS_8_BACKWARD = 1,      //< 8倍速后退播放 
	PLAY_STATUS_4_BACKWARD = 2,      //< 4倍速后退播放 
	PLAY_STATUS_2_BACKWARD = 3,      //< 2倍速后退播放 
	PLAY_STATUS_1_BACKWARD = 4,      //< 正常速度后退播放 
	PLAY_STATUS_HALF_BACKWARD = 5,   //< 1/2倍速后退播放 
	PLAY_STATUS_QUARTER_BACKWARD = 6,//< 1/4倍速后退播放 
	PLAY_STATUS_QUARTER_FORWARD = 7, //< 1/4倍速播放 
	PLAY_STATUS_HALF_FORWARD = 8,    //< 1/2倍速播放 
	PLAY_STATUS_1_FORWARD = 9,       //< 正常速度前进播放 
	PLAY_STATUS_2_FORWARD = 10,      //< 2倍速前进播放 
	PLAY_STATUS_4_FORWARD = 11,      //< 4倍速前进播放 
	PLAY_STATUS_8_FORWARD = 12,      //< 8倍速前进播放 
	PLAY_STATUS_16_FORWARD = 13      //< 16倍速前进播放 
};

/**
* @struct tagPictureData
* @brief 存放解码后图像数据的指针和长度等信息的结构体定义
* @attention 无
*/
typedef struct tagPictureData
{
	unsigned char *pucData[4];                          /**< pucData[0]:Y 平面指针,pucData[1]:U 平面指针,pucData[2]:V 平面指针*/
	unsigned long ulLineSize[4];                        /**< ulLineSize[0]:Y平面每行跨距, ulLineSize[1]:U平面每行跨距, ulLineSize[2]:V平面每行跨距*/
	unsigned long ulPicHeight;                          /**< 图片高度*/
	unsigned long ulPicWidth;                           /**< 图片宽度*/
	unsigned long ulRenderTime;                         /**< 用于渲染的时间数据（单位为毫秒）*/
	unsigned long ulReserverParam1;                     /**< 保留参数*/
	unsigned long ulReserverParam2;                     /**< 保留参数*/
}PICTURE_DATA_S;

/**	@fn	CBF_Msg
 *	@brief	消息回调函数指针。
 *	@param iSessionId: preview_start或playback_start成功的返回值。
 *	@param iMsgType: 消息回调类型，需要详细定义。
 *	@param iMsgCode: 消息码，需要详细定义。
 *	@param szMsg: 消息描述。
 *	@param pUsrData: 用户自定义数据，preview_start或playback_start传入的pUsrData字段。
 *	@return	0表示成功,-1表示失败，get_lasterror()获取错误码。
 */
typedef int (__stdcall *CBF_Msg)(int iSessionId, int iMsgType, int iMsgCode, char* szMsg, void* pUsrData);

/**	@fn	CBF_Stream
 *	@brief	数据回调函数指针。
 *	@param iSessionId: preview_start或playback_start成功的返回值。
 *	@param iStreamType：消息回调类型，0为头数据，1为视频数据，2为音频数据。
 *	@param pData：数据指针，去掉RTP头及扩展头数据。
 *	@param iDataLen：数据长度。
 *	@param pUsrData: 用户自定义数据，preview_start或playback_start传入的pUsrData字段。
 *	@return	0表示成功,-1表示失败，get_lasterror()获取错误码。
 */
typedef int (__stdcall* CBF_Stream)(int iSessionId, int iStreamType, char* pData, int iDataLen, void* pUsrData);


/**
* 解码后视频数据输出的回调函数类型定义。\n
* @param [IN] sessionid                 通道
* @param [IN] pPictureData              解码后视频数据
* @param [IN] pUsrData                  用户数据
* @return void
* @note SDK用户不允许阻塞该回调函数，防止影响解码插件内部的媒体流处理。
*/
typedef void (__stdcall* VideoData_Stream_PF)(int iSessionId, PICTURE_DATA_S *pPictureData, void* pUsrData);


/**	@fn	media_init
 *	@brief	初始化插件接口
 *	@param 
 *	@return	0表示成功,-1表示失败，get_lasterror()获取错误码。
 */
HIK_DECODER_API int __stdcall media_init();

/**	@fn	media_terminate
 *	@brief	销毁插件接口。
 *	@param 
 *	@return void
 */
HIK_DECODER_API void __stdcall media_terminate();

/**	@fn	stop_all
 *	@brief	全部停止实时预览。
 *	@param 
 *	@return 0表示成功,-1表示失败，get_lasterror()获取错误码。
 */
HIK_DECODER_API int __stdcall stop_all();

/**	@fn	preview_start
 *	@brief	开始预览回调函数设置有效时，需要回调视音频流，无效时，不回调视音频流。
 *          Wnd有效时，需要在窗口中播放视频。回调和播放可以同时有效。
 *	@param wnd: 播放窗口句柄，如果wnd为NULL，表示不解码只回调码流。
 *	@param port: 接收数据的端口号。
 *	@param pUsrData: 用户自定义数据。
 *	@return >0表示成功,-1表示失败，get_lasterror()获取错误码。
 */
HIK_DECODER_API int __stdcall preview_start(void* pWnd, unsigned short nPort, void* pUsrData);

/**	@fn	set_msgcbf
 *	@brief	设置消息回调。
 *	@param pCbf: 消息回调函数。
 *	@return 0表示成功,-1表示失败，get_lasterror()获取错误码。
 */
HIK_DECODER_API int __stdcall set_msgcbf(CBF_Msg pCbf);

/**	@fn	set_streamcbf
 *	@brief 设置取流回调，这个函数必须在preview_start和playback_start前调用，否则在preview_start和playback_start使用时无效。
 *	@param pCbf: 取流回调函数。
 *	@return 0表示成功,-1表示失败，get_lasterror()获取错误码。
 */
HIK_DECODER_API int __stdcall set_streamcbf(CBF_Stream pCbf);

/**
* 设置启动解码后视频数据输出的回调函数。\n
* @param [IN] sessionid                 preview_star或者playback_start或者playlocal_start函数的返回值
* @param [IN] pfnVideoDataOutput        解码后视频输出的回调函数指针
* @return 0表示成功，-1表示失败
* @note
*/
HIK_DECODER_API int __stdcall set_videodatacbf(int sessionid, VideoData_Stream_PF pfnVideoDataOutput);

/**	@fn	preview_stop
 *	@brief	停止实时预览。
 *	@param iSessionId: preview_start成功的返回值。
 *	@return 0表示成功,-1表示失败，get_lasterror()获取错误码。
 */
HIK_DECODER_API int __stdcall preview_stop(int iSessionId);

/**	@fn	playback_start
 *	@brief	开始回放，wnd有效时，必须在窗口中播放视频。
			如果调用过set_streamcbf设置取流回调有效，必须在回调函数中回调视频数据。
			播放和回调可以同时支持。
 *	@param wnd：播放窗口句柄。
 *	@param port：接收数据的端口号。
 *	@param sdp：rtsp DESCRIBE响应时带回来的SDP信息。开始时间格式：clock=20120512T090909Z
 *	@param filename：保存的录像文件名。
 *	@param pUsrData：用户自定义数据。
 *	@return 0表示成功,-1表示失败，get_lasterror()获取错误码。
 */
HIK_DECODER_API int __stdcall playback_start(void* pWnd, unsigned short nPort, const char* pSdp, char* pFilename, void* pUsrData);

/**	@fn	playback_stop
 *	@brief	停止回放。
 *	@param sessionid：play_back成功的返回值。
 *	@return 0表示成功,-1表示失败，get_lasterror()获取错误码。
 */
HIK_DECODER_API int __stdcall playback_stop(int iSessionId);

/**	@fn	picture_capture
 *	@brief	抓图，抓图保存格式为默认为jpg。
 *	@param sessionid：preview_start或playback_start成功的返回值。
 *	@param  picturename：抓图保存的文件名。
 *	@param iPicMode：0标志JPEG，iPIcMode=1表示BMP。
 *	@return 0表示成功,-1表示失败，get_lasterror()获取错误码。
 */
HIK_DECODER_API int __stdcall picture_capture(int iSessionId, const char* pPictureName, int iPicMode);

/**	@fn	set_audio_volume
 *	@brief	设置音量大小。
 *	@param sessionid：preview_start或playback_start成功的返回值。
  *	@param volume:0-100，100表示音量最大，0表示静音。 
 *	@return 0表示成功,-1表示失败，get_lasterror()获取错误码。
 */
HIK_DECODER_API int __stdcall set_audio_volume(int iSessionId, int iVolume);

/**	@fn	get_lasterror
 *	@brief	全部停止实时预览。
 *	@param 获取错误码，错误码定义应与PART3附录B一致。
 *	@return 0表示成功,-1表示失败，get_lasterror()获取错误码。
 */
HIK_DECODER_API int __stdcall get_lasterror();

/**	@fn	set_playbackspeedEx
 *	@brief	set_playbackspeed扩展接口,设置一路回放速度。设置回放速度倍速值。可以多次调用，以最后一次设置值为准
 *	@param speed：回放速度倍速值，1表示正常回放，2表示2倍速回放，4表示4倍速回放，以此类推
 *	@return 0表示成功,-1表示失败，get_lasterror()获取错误码。
 */
HIK_DECODER_API void __stdcall set_playbackspeed(int iSessionId, int iSpeed);

/**	@fn	set_playbackspeed 
 *	@brief	设置回放速度倍速值。可以多次调用，以最后一次设置值为准
 *	@param speed：回放速度倍速值，1表示正常回放，2表示2倍速回放，4表示4倍速回放，以此类推
 *	@return 0表示成功,-1表示失败，get_lasterror()获取错误码。
 */
//HIK_DECODER_API void __stdcall set_playbackspeed(int iSpeed);

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

/**	@fn	record_start
 *	@brief	启动本地录像
 *	@param sessionid：preview_star或者playback_start或者playlocal_start函数的返回值
 *	@param filename：本地录像的文件名称，如：  "d:\xxx\RecordFile.HK_v3"，RecordFile 由调用者命名（包括路径），HK_v3:对应厂家的decodertag标识
 *	@return 0表示成功,-1表示失败，get_lasterror()获取错误码。
 */
HIK_DECODER_API int __stdcall record_start(int iSessionId, char* pFileName);

/**	@fn	record_stop
 *	@brief	停止本地录像
 *	@param sessionid：preview_star或者playback_start或者playlocal_start函数的返回值
 *	@return void
 */
HIK_DECODER_API void  __stdcall record_stop(int iSessionId);

/**	@fn	playlocal_start
 *	@brief	启动本地录像播放
 *	@param wnd：播放视频窗口句柄
 *	@param filename：播放的本地文件名称
 *	@param pUserData：用户自定义数据
 *	@return >=0表示成功,-1表示失败，get_lasterror()获取错误码。
 */
HIK_DECODER_API int __stdcall playlocal_start(void * pWnd, char* pFileName, void * pUserData);

/**	@fn	playlocal_stop
 *	@brief	停止本地录像播放
 *	@param sessionid：preview_star或者playback_start或者playlocal_start函数的返回值
 *	@return void
 */
HIK_DECODER_API void __stdcall playlocal_stop(int iSessionId);

/**	@fn	fileplaytotaltime_get
 *	@brief	查询当前本地文件的播放总时间长度
 *	@param sessionid：playlocal_start函数的返回值
 *	@return 当前本地文件的播放总时间，相对时间，以秒为单位。
 */
HIK_DECODER_API int __stdcall fileplaytotaltime_get(int iSessionId);

/**	@fn	fileplaycurtime_get
 *	@brief	查询当前本地录像播放进度
 *	@param sessionid：playlocal_start函数的返回值
 *	@return 当前本地文件的播放时间点，相对时间，以秒为单位.
 */
HIK_DECODER_API int __stdcall fileplaycurtime_get(int iSessionId);

/**	@fn	fileplaycurtime_set
 *	@brief	设置当前本地录像播放时间点
 *	@param sessionid：设置当前本地录像播放时间点
 *	@param itime： 需要播放的时间点，相对时间，以秒为单位
 *	@return 0表示成功,-1表示失败，get_lasterror()获取错误码。
 */
HIK_DECODER_API int __stdcall fileplaycurtime_set(int iSessionId, int iTime);

/**	@fn	playspeed_set
 *	@brief	播放流控接口
 *	@param sessionid：playlocal_start函数的返回值
 *	@param speed：设置的播放倍速，倍速定义如下：
	PLAY_STATUS_16_BACKWARD = 0,    //< 16倍速后退播放 
	PLAY_STATUS_8_BACKWARD = 1,      //< 8倍速后退播放 
	PLAY_STATUS_4_BACKWARD = 2,      //< 4倍速后退播放 
	PLAY_STATUS_2_BACKWARD = 3,      //< 2倍速后退播放 
	PLAY_STATUS_1_BACKWARD = 4,      //< 正常速度后退播放 
	PLAY_STATUS_HALF_BACKWARD = 5,   //< 1/2倍速后退播放 
	PLAY_STATUS_QUARTER_BACKWARD = 6,//< 1/4倍速后退播放 
	PLAY_STATUS_QUARTER_FORWARD = 7, //< 1/4倍速播放 
	PLAY_STATUS_HALF_FORWARD = 8,    //< 1/2倍速播放 
	PLAY_STATUS_1_FORWARD = 9,       //< 正常速度前进播放 
	PLAY_STATUS_2_FORWARD = 10,      //< 2倍速前进播放 
	PLAY_STATUS_4_FORWARD = 11,      //< 4倍速前进播放 
	PLAY_STATUS_8_FORWARD = 12,      //< 8倍速前进播放 
	PLAY_STATUS_16_FORWARD = 13      //< 16倍速前进播放 
 *	@return 0表示成功,-1表示失败，get_lasterror()获取错误码。
 */
HIK_DECODER_API int __stdcall playspeed_set(int iSessionId, int iSpeed);


/**	@fn	play_pause
 *	@brief	暂停当前本地录像播放
 *	@param  iSessionId: 为playback_start(实时回放暂停) 或者 playlocal_start(本地文件播放暂停)函数的返回值。
                        回放过程中暂停调用该接口，通知插件处于暂停状态，不对保活做判断。
 *	@return 0表示成功,-1表示失败，get_lasterror()获取错误码。
 */
HIK_DECODER_API int __stdcall play_pause(int iSessionId);

/**	@fn	play_resume
 *	@brief	恢复当前本地录像播放
 *	@param sessionid：playback_start 或者 playlocal_start函数的返回值
 *	@return 0表示成功,-1表示失败，get_lasterror()获取错误码。
 */
HIK_DECODER_API int __stdcall play_resume(int iSessionId);

/**	@fn	download_start
 *	@brief	启动录像下载到本地录像（从下级平台下载历史图像到本地）
 *	port:本地收流端口
 *	SDP:rtsp DESCRIBE响应时携带的SDP信息
 *	filename:本地录像的文件名称，如：  "d:\xxx\RecordFile.HK_v3"，RecordFile 由调用者命名（包括路径），HK_v3:对应厂家的decodertag标识；
 *	pUsrData:回调时的用户自定义数据
 *	@return 0表示成功,-1表示失败，get_lasterror()获取错误码。
 */
HIK_DECODER_API int __stdcall download_start(unsigned short nPort, char* pSdp, char* pFileName, void * pUsrData);

/**	@fn	download_stop
 *	@brief	停止录像下载保存为本地录像
 *	@param sessionid：download_start函数的返回值
 *	@return 0表示成功,-1表示失败，get_lasterror()获取错误码。
 */
HIK_DECODER_API void __stdcall download_stop(int iSessionId);

/**	@fn	sound_stop
 *	@brief	设置播放静音
 *	@param sessionid：playback_start或者playlocal_start函数的返回值
 *	@return 0表示成功,-1表示失败，get_lasterror()获取错误码。
 */
HIK_DECODER_API int __stdcall sound_stop(int iSessionId);

/**	@fn	sound_play
 *	@brief	取消播放静音
 *	@param sessionid：playback_start或者playlocal_start函数的返回值
 *	@return 0表示成功,-1表示失败，get_lasterror()获取错误码。
 */
HIK_DECODER_API int __stdcall sound_play(int iSessionId);

/**	@fn	volume_set
 *	@brief	设置播放时音量
 *	@param sessionid：playback_start或者playlocal_start函数的返回值；
 *          volume 为设置的音量， 0 -- 100，100为最高音量
 *	@return 0表示成功,-1表示失败，get_lasterror()获取错误码。
 */
HIK_DECODER_API int __stdcall volume_set(int iSessionId, unsigned short nVolume);

/**	@fn	play_getspecialdata
 *	@brief	获取当前显示帧的全局时间
 *	@param sessionid：playback_start或者playlocal_start函数的返回值；
 *	@return 表示时间，get_lasterror()获取错误码。
 */
HIK_DECODER_API unsigned int __stdcall play_getspecialdata(int iSessionId);

/**	@fn	play_resetsourcebuffer
 *	@brief	清空所有缓冲区的剩余数据
 *	@param sessionid：playback_start或者playlocal_start函数的返回值；
 *	@return 0表示成功，-1表示失败，get_lasterror()获取错误码。
 */
HIK_DECODER_API int __stdcall play_resetsourcebuffer(int iSessionId);
#endif
