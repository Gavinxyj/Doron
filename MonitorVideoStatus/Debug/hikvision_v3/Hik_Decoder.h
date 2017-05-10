

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

#define  HIK_MSG_TYPE_CLOSE			0		//���ӶϿ�
#define  HIK_MSG_TYPE_ERROR			1		//�������ݴ���


enum PLAY_STATUS_SPEED
{
	PLAY_STATUS_16_BACKWARD = 0,	 //< 16���ٺ��˲��� 
	PLAY_STATUS_8_BACKWARD = 1,      //< 8���ٺ��˲��� 
	PLAY_STATUS_4_BACKWARD = 2,      //< 4���ٺ��˲��� 
	PLAY_STATUS_2_BACKWARD = 3,      //< 2���ٺ��˲��� 
	PLAY_STATUS_1_BACKWARD = 4,      //< �����ٶȺ��˲��� 
	PLAY_STATUS_HALF_BACKWARD = 5,   //< 1/2���ٺ��˲��� 
	PLAY_STATUS_QUARTER_BACKWARD = 6,//< 1/4���ٺ��˲��� 
	PLAY_STATUS_QUARTER_FORWARD = 7, //< 1/4���ٲ��� 
	PLAY_STATUS_HALF_FORWARD = 8,    //< 1/2���ٲ��� 
	PLAY_STATUS_1_FORWARD = 9,       //< �����ٶ�ǰ������ 
	PLAY_STATUS_2_FORWARD = 10,      //< 2����ǰ������ 
	PLAY_STATUS_4_FORWARD = 11,      //< 4����ǰ������ 
	PLAY_STATUS_8_FORWARD = 12,      //< 8����ǰ������ 
	PLAY_STATUS_16_FORWARD = 13      //< 16����ǰ������ 
};

/**
* @struct tagPictureData
* @brief ��Ž����ͼ�����ݵ�ָ��ͳ��ȵ���Ϣ�Ľṹ�嶨��
* @attention ��
*/
typedef struct tagPictureData
{
	unsigned char *pucData[4];                          /**< pucData[0]:Y ƽ��ָ��,pucData[1]:U ƽ��ָ��,pucData[2]:V ƽ��ָ��*/
	unsigned long ulLineSize[4];                        /**< ulLineSize[0]:Yƽ��ÿ�п��, ulLineSize[1]:Uƽ��ÿ�п��, ulLineSize[2]:Vƽ��ÿ�п��*/
	unsigned long ulPicHeight;                          /**< ͼƬ�߶�*/
	unsigned long ulPicWidth;                           /**< ͼƬ���*/
	unsigned long ulRenderTime;                         /**< ������Ⱦ��ʱ�����ݣ���λΪ���룩*/
	unsigned long ulReserverParam1;                     /**< ��������*/
	unsigned long ulReserverParam2;                     /**< ��������*/
}PICTURE_DATA_S;

/**	@fn	CBF_Msg
 *	@brief	��Ϣ�ص�����ָ�롣
 *	@param iSessionId: preview_start��playback_start�ɹ��ķ���ֵ��
 *	@param iMsgType: ��Ϣ�ص����ͣ���Ҫ��ϸ���塣
 *	@param iMsgCode: ��Ϣ�룬��Ҫ��ϸ���塣
 *	@param szMsg: ��Ϣ������
 *	@param pUsrData: �û��Զ������ݣ�preview_start��playback_start�����pUsrData�ֶΡ�
 *	@return	0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ�����롣
 */
typedef int (__stdcall *CBF_Msg)(int iSessionId, int iMsgType, int iMsgCode, char* szMsg, void* pUsrData);

/**	@fn	CBF_Stream
 *	@brief	���ݻص�����ָ�롣
 *	@param iSessionId: preview_start��playback_start�ɹ��ķ���ֵ��
 *	@param iStreamType����Ϣ�ص����ͣ�0Ϊͷ���ݣ�1Ϊ��Ƶ���ݣ�2Ϊ��Ƶ���ݡ�
 *	@param pData������ָ�룬ȥ��RTPͷ����չͷ���ݡ�
 *	@param iDataLen�����ݳ��ȡ�
 *	@param pUsrData: �û��Զ������ݣ�preview_start��playback_start�����pUsrData�ֶΡ�
 *	@return	0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ�����롣
 */
typedef int (__stdcall* CBF_Stream)(int iSessionId, int iStreamType, char* pData, int iDataLen, void* pUsrData);


/**
* �������Ƶ��������Ļص��������Ͷ��塣\n
* @param [IN] sessionid                 ͨ��
* @param [IN] pPictureData              �������Ƶ����
* @param [IN] pUsrData                  �û�����
* @return void
* @note SDK�û������������ûص���������ֹӰ��������ڲ���ý��������
*/
typedef void (__stdcall* VideoData_Stream_PF)(int iSessionId, PICTURE_DATA_S *pPictureData, void* pUsrData);


/**	@fn	media_init
 *	@brief	��ʼ������ӿ�
 *	@param 
 *	@return	0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ�����롣
 */
HIK_DECODER_API int __stdcall media_init();

/**	@fn	media_terminate
 *	@brief	���ٲ���ӿڡ�
 *	@param 
 *	@return void
 */
HIK_DECODER_API void __stdcall media_terminate();

/**	@fn	stop_all
 *	@brief	ȫ��ֹͣʵʱԤ����
 *	@param 
 *	@return 0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ�����롣
 */
HIK_DECODER_API int __stdcall stop_all();

/**	@fn	preview_start
 *	@brief	��ʼԤ���ص�����������Чʱ����Ҫ�ص�����Ƶ������Чʱ�����ص�����Ƶ����
 *          Wnd��Чʱ����Ҫ�ڴ����в�����Ƶ���ص��Ͳ��ſ���ͬʱ��Ч��
 *	@param wnd: ���Ŵ��ھ�������wndΪNULL����ʾ������ֻ�ص�������
 *	@param port: �������ݵĶ˿ںš�
 *	@param pUsrData: �û��Զ������ݡ�
 *	@return >0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ�����롣
 */
HIK_DECODER_API int __stdcall preview_start(void* pWnd, unsigned short nPort, void* pUsrData);

/**	@fn	set_msgcbf
 *	@brief	������Ϣ�ص���
 *	@param pCbf: ��Ϣ�ص�������
 *	@return 0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ�����롣
 */
HIK_DECODER_API int __stdcall set_msgcbf(CBF_Msg pCbf);

/**	@fn	set_streamcbf
 *	@brief ����ȡ���ص����������������preview_start��playback_startǰ���ã�������preview_start��playback_startʹ��ʱ��Ч��
 *	@param pCbf: ȡ���ص�������
 *	@return 0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ�����롣
 */
HIK_DECODER_API int __stdcall set_streamcbf(CBF_Stream pCbf);

/**
* ���������������Ƶ��������Ļص�������\n
* @param [IN] sessionid                 preview_star����playback_start����playlocal_start�����ķ���ֵ
* @param [IN] pfnVideoDataOutput        �������Ƶ����Ļص�����ָ��
* @return 0��ʾ�ɹ���-1��ʾʧ��
* @note
*/
HIK_DECODER_API int __stdcall set_videodatacbf(int sessionid, VideoData_Stream_PF pfnVideoDataOutput);

/**	@fn	preview_stop
 *	@brief	ֹͣʵʱԤ����
 *	@param iSessionId: preview_start�ɹ��ķ���ֵ��
 *	@return 0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ�����롣
 */
HIK_DECODER_API int __stdcall preview_stop(int iSessionId);

/**	@fn	playback_start
 *	@brief	��ʼ�طţ�wnd��Чʱ�������ڴ����в�����Ƶ��
			������ù�set_streamcbf����ȡ���ص���Ч�������ڻص������лص���Ƶ���ݡ�
			���źͻص�����ͬʱ֧�֡�
 *	@param wnd�����Ŵ��ھ����
 *	@param port���������ݵĶ˿ںš�
 *	@param sdp��rtsp DESCRIBE��Ӧʱ��������SDP��Ϣ����ʼʱ���ʽ��clock=20120512T090909Z
 *	@param filename�������¼���ļ�����
 *	@param pUsrData���û��Զ������ݡ�
 *	@return 0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ�����롣
 */
HIK_DECODER_API int __stdcall playback_start(void* pWnd, unsigned short nPort, const char* pSdp, char* pFilename, void* pUsrData);

/**	@fn	playback_stop
 *	@brief	ֹͣ�طš�
 *	@param sessionid��play_back�ɹ��ķ���ֵ��
 *	@return 0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ�����롣
 */
HIK_DECODER_API int __stdcall playback_stop(int iSessionId);

/**	@fn	picture_capture
 *	@brief	ץͼ��ץͼ�����ʽΪĬ��Ϊjpg��
 *	@param sessionid��preview_start��playback_start�ɹ��ķ���ֵ��
 *	@param  picturename��ץͼ������ļ�����
 *	@param iPicMode��0��־JPEG��iPIcMode=1��ʾBMP��
 *	@return 0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ�����롣
 */
HIK_DECODER_API int __stdcall picture_capture(int iSessionId, const char* pPictureName, int iPicMode);

/**	@fn	set_audio_volume
 *	@brief	����������С��
 *	@param sessionid��preview_start��playback_start�ɹ��ķ���ֵ��
  *	@param volume:0-100��100��ʾ�������0��ʾ������ 
 *	@return 0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ�����롣
 */
HIK_DECODER_API int __stdcall set_audio_volume(int iSessionId, int iVolume);

/**	@fn	get_lasterror
 *	@brief	ȫ��ֹͣʵʱԤ����
 *	@param ��ȡ�����룬�����붨��Ӧ��PART3��¼Bһ�¡�
 *	@return 0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ�����롣
 */
HIK_DECODER_API int __stdcall get_lasterror();

/**	@fn	set_playbackspeedEx
 *	@brief	set_playbackspeed��չ�ӿ�,����һ·�ط��ٶȡ����ûط��ٶȱ���ֵ�����Զ�ε��ã������һ������ֵΪ׼
 *	@param speed���ط��ٶȱ���ֵ��1��ʾ�����طţ�2��ʾ2���ٻطţ�4��ʾ4���ٻطţ��Դ�����
 *	@return 0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ�����롣
 */
HIK_DECODER_API void __stdcall set_playbackspeed(int iSessionId, int iSpeed);

/**	@fn	set_playbackspeed 
 *	@brief	���ûط��ٶȱ���ֵ�����Զ�ε��ã������һ������ֵΪ׼
 *	@param speed���ط��ٶȱ���ֵ��1��ʾ�����طţ�2��ʾ2���ٻطţ�4��ʾ4���ٻطţ��Դ�����
 *	@return 0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ�����롣
 */
//HIK_DECODER_API void __stdcall set_playbackspeed(int iSpeed);

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

/**	@fn	record_start
 *	@brief	��������¼��
 *	@param sessionid��preview_star����playback_start����playlocal_start�����ķ���ֵ
 *	@param filename������¼����ļ����ƣ��磺  "d:\xxx\RecordFile.HK_v3"��RecordFile �ɵ���������������·������HK_v3:��Ӧ���ҵ�decodertag��ʶ
 *	@return 0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ�����롣
 */
HIK_DECODER_API int __stdcall record_start(int iSessionId, char* pFileName);

/**	@fn	record_stop
 *	@brief	ֹͣ����¼��
 *	@param sessionid��preview_star����playback_start����playlocal_start�����ķ���ֵ
 *	@return void
 */
HIK_DECODER_API void  __stdcall record_stop(int iSessionId);

/**	@fn	playlocal_start
 *	@brief	��������¼�񲥷�
 *	@param wnd��������Ƶ���ھ��
 *	@param filename�����ŵı����ļ�����
 *	@param pUserData���û��Զ�������
 *	@return >=0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ�����롣
 */
HIK_DECODER_API int __stdcall playlocal_start(void * pWnd, char* pFileName, void * pUserData);

/**	@fn	playlocal_stop
 *	@brief	ֹͣ����¼�񲥷�
 *	@param sessionid��preview_star����playback_start����playlocal_start�����ķ���ֵ
 *	@return void
 */
HIK_DECODER_API void __stdcall playlocal_stop(int iSessionId);

/**	@fn	fileplaytotaltime_get
 *	@brief	��ѯ��ǰ�����ļ��Ĳ�����ʱ�䳤��
 *	@param sessionid��playlocal_start�����ķ���ֵ
 *	@return ��ǰ�����ļ��Ĳ�����ʱ�䣬���ʱ�䣬����Ϊ��λ��
 */
HIK_DECODER_API int __stdcall fileplaytotaltime_get(int iSessionId);

/**	@fn	fileplaycurtime_get
 *	@brief	��ѯ��ǰ����¼�񲥷Ž���
 *	@param sessionid��playlocal_start�����ķ���ֵ
 *	@return ��ǰ�����ļ��Ĳ���ʱ��㣬���ʱ�䣬����Ϊ��λ.
 */
HIK_DECODER_API int __stdcall fileplaycurtime_get(int iSessionId);

/**	@fn	fileplaycurtime_set
 *	@brief	���õ�ǰ����¼�񲥷�ʱ���
 *	@param sessionid�����õ�ǰ����¼�񲥷�ʱ���
 *	@param itime�� ��Ҫ���ŵ�ʱ��㣬���ʱ�䣬����Ϊ��λ
 *	@return 0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ�����롣
 */
HIK_DECODER_API int __stdcall fileplaycurtime_set(int iSessionId, int iTime);

/**	@fn	playspeed_set
 *	@brief	�������ؽӿ�
 *	@param sessionid��playlocal_start�����ķ���ֵ
 *	@param speed�����õĲ��ű��٣����ٶ������£�
	PLAY_STATUS_16_BACKWARD = 0,    //< 16���ٺ��˲��� 
	PLAY_STATUS_8_BACKWARD = 1,      //< 8���ٺ��˲��� 
	PLAY_STATUS_4_BACKWARD = 2,      //< 4���ٺ��˲��� 
	PLAY_STATUS_2_BACKWARD = 3,      //< 2���ٺ��˲��� 
	PLAY_STATUS_1_BACKWARD = 4,      //< �����ٶȺ��˲��� 
	PLAY_STATUS_HALF_BACKWARD = 5,   //< 1/2���ٺ��˲��� 
	PLAY_STATUS_QUARTER_BACKWARD = 6,//< 1/4���ٺ��˲��� 
	PLAY_STATUS_QUARTER_FORWARD = 7, //< 1/4���ٲ��� 
	PLAY_STATUS_HALF_FORWARD = 8,    //< 1/2���ٲ��� 
	PLAY_STATUS_1_FORWARD = 9,       //< �����ٶ�ǰ������ 
	PLAY_STATUS_2_FORWARD = 10,      //< 2����ǰ������ 
	PLAY_STATUS_4_FORWARD = 11,      //< 4����ǰ������ 
	PLAY_STATUS_8_FORWARD = 12,      //< 8����ǰ������ 
	PLAY_STATUS_16_FORWARD = 13      //< 16����ǰ������ 
 *	@return 0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ�����롣
 */
HIK_DECODER_API int __stdcall playspeed_set(int iSessionId, int iSpeed);


/**	@fn	play_pause
 *	@brief	��ͣ��ǰ����¼�񲥷�
 *	@param  iSessionId: Ϊplayback_start(ʵʱ�ط���ͣ) ���� playlocal_start(�����ļ�������ͣ)�����ķ���ֵ��
                        �طŹ�������ͣ���øýӿڣ�֪ͨ���������ͣ״̬�����Ա������жϡ�
 *	@return 0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ�����롣
 */
HIK_DECODER_API int __stdcall play_pause(int iSessionId);

/**	@fn	play_resume
 *	@brief	�ָ���ǰ����¼�񲥷�
 *	@param sessionid��playback_start ���� playlocal_start�����ķ���ֵ
 *	@return 0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ�����롣
 */
HIK_DECODER_API int __stdcall play_resume(int iSessionId);

/**	@fn	download_start
 *	@brief	����¼�����ص�����¼�񣨴��¼�ƽ̨������ʷͼ�񵽱��أ�
 *	port:���������˿�
 *	SDP:rtsp DESCRIBE��ӦʱЯ����SDP��Ϣ
 *	filename:����¼����ļ����ƣ��磺  "d:\xxx\RecordFile.HK_v3"��RecordFile �ɵ���������������·������HK_v3:��Ӧ���ҵ�decodertag��ʶ��
 *	pUsrData:�ص�ʱ���û��Զ�������
 *	@return 0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ�����롣
 */
HIK_DECODER_API int __stdcall download_start(unsigned short nPort, char* pSdp, char* pFileName, void * pUsrData);

/**	@fn	download_stop
 *	@brief	ֹͣ¼�����ر���Ϊ����¼��
 *	@param sessionid��download_start�����ķ���ֵ
 *	@return 0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ�����롣
 */
HIK_DECODER_API void __stdcall download_stop(int iSessionId);

/**	@fn	sound_stop
 *	@brief	���ò��ž���
 *	@param sessionid��playback_start����playlocal_start�����ķ���ֵ
 *	@return 0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ�����롣
 */
HIK_DECODER_API int __stdcall sound_stop(int iSessionId);

/**	@fn	sound_play
 *	@brief	ȡ�����ž���
 *	@param sessionid��playback_start����playlocal_start�����ķ���ֵ
 *	@return 0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ�����롣
 */
HIK_DECODER_API int __stdcall sound_play(int iSessionId);

/**	@fn	volume_set
 *	@brief	���ò���ʱ����
 *	@param sessionid��playback_start����playlocal_start�����ķ���ֵ��
 *          volume Ϊ���õ������� 0 -- 100��100Ϊ�������
 *	@return 0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ�����롣
 */
HIK_DECODER_API int __stdcall volume_set(int iSessionId, unsigned short nVolume);

/**	@fn	play_getspecialdata
 *	@brief	��ȡ��ǰ��ʾ֡��ȫ��ʱ��
 *	@param sessionid��playback_start����playlocal_start�����ķ���ֵ��
 *	@return ��ʾʱ�䣬get_lasterror()��ȡ�����롣
 */
HIK_DECODER_API unsigned int __stdcall play_getspecialdata(int iSessionId);

/**	@fn	play_resetsourcebuffer
 *	@brief	������л�������ʣ������
 *	@param sessionid��playback_start����playlocal_start�����ķ���ֵ��
 *	@return 0��ʾ�ɹ���-1��ʾʧ�ܣ�get_lasterror()��ȡ�����롣
 */
HIK_DECODER_API int __stdcall play_resetsourcebuffer(int iSessionId);
#endif
