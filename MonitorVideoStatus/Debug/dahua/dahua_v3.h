//
// Copyright (c) 2010, �㽭�󻪼����ɷ����޹�˾
// All rights reserved.
// 
// �� �� ����dhplaysdk.h
// ժ    Ҫ��H3Cƽ̨����ӿڶ���
//
// �޶���¼������
// ������ڣ�2010��10��25��
// ��    �ߣ�
//
// �޶���¼�������µĽӿڶ����ĵ�"DB 33/ T629.5��2010"���нӿڵ������Լ��޸�
// ������ڣ�2011��03��29��
// ��    �ߣ�
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

// ������
enum
{
	DH_ERR_ERROR   = -1,
	DH_ERR_NOERROR =  0
};

// �����ٶ�
typedef enum _PLAY_SPEED
{
	PLAY_STATUS_16_BACKWARD = 0,     /**< 16���ٺ��˲��� */
	PLAY_STATUS_8_BACKWARD = 1,      /**< 8���ٺ��˲��� */
	PLAY_STATUS_4_BACKWARD = 2,      /**< 4���ٺ��˲��� */
	PLAY_STATUS_2_BACKWARD = 3,      /**< 2���ٺ��˲��� */
	PLAY_STATUS_1_BACKWARD = 4,      /**< �����ٶȺ��˲��� */
	PLAY_STATUS_HALF_BACKWARD = 5,   /**< 1/2���ٺ��˲��� */
	PLAY_STATUS_QUARTER_BACKWARD = 6,/**< 1/4���ٺ��˲��� */
	PLAY_STATUS_QUARTER_FORWARD = 7, /**< 1/4���ٲ��� */
	PLAY_STATUS_HALF_FORWARD = 8,    /**< 1/2���ٲ��� */
	PLAY_STATUS_1_FORWARD = 9,       /**< �����ٶ�ǰ������ */
	PLAY_STATUS_2_FORWARD = 10,      /**< 2����ǰ������ */
	PLAY_STATUS_4_FORWARD = 11,      /**< 4����ǰ������ */
	PLAY_STATUS_8_FORWARD = 12,      /**< 8����ǰ������ */
	PLAY_STATUS_16_FORWARD = 13      /**< 16����ǰ������ */
}PLAY_SPEED;

//
// �ù���δʵ��
// ��    ��: ��Ϣ�ص�����ָ��
// �������:
//			 iSessionId��preview_start��playback_start�ɹ��ķ���ֵ
//			 iMsgType����Ϣ�ص����ͣ���Ҫ��ϸ����
//			 iMsgCode����Ϣ�룬��Ҫ��ϸ����
//			 szMsg����Ϣ����
//			 pUsrData���û��Զ������ݣ�preview_start��playback_start�����pUsrData�ֶΡ�
// �������: ��
// �� �� ֵ: 0 ��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ������
//
typedef int (__stdcall *CBF_Msg)(int iSessionId, int iMsgType, int iMsgCode, char* szMsg, void* pUsrData);

//
// �ù���δʵ��
// ��    ��: ���ݻص�����ָ��
// �������:
//			 iSessionId��preview_start��playback_start�ɹ��ķ���ֵ
//			 iSessionId��preview_start��playback_start�ɹ��ķ���ֵ
//			 iStreamType����Ϣ�ص����ͣ�0Ϊͷ���ݣ�1Ϊ��Ƶ���ݣ�2Ϊ��Ƶ���ݡ�
//			 pData������ָ�룬ȥ��RTPͷ����չͷ����
//			 iDataLen�����ݳ���
//			 pUsrData���û��Զ������ݣ�preview_start��playback_start�����pUsrData�ֶ�
// �������: ��
// �� �� ֵ: 0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ������
//
typedef int (__stdcall* CBF_Stream)(int iSessionId, int iStreamType, char* pData, int iDataLen, void* pUsrData);

//
// ��������: ��ʼ������ӿ�
// �������: ��
// �������: ��
// �� �� ֵ: 0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ������
//
DHPLAYSDK_API int __stdcall media_init();

//
// ��������: ���ٲ���ӿ�
// �������: ��
// �������: ��
// �� �� ֵ: 0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ������
//
DHPLAYSDK_API void __stdcall media_terminate();

//
// ��������: ȫ��ֹͣʵʱԤ��
// �������: ��
// �������: ��
// �� �� ֵ: 0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ������
//
DHPLAYSDK_API int __stdcall stop_all();

//
// ��������: ��ʼԤ��
// �������:
//			 wnd�����Ŵ��ھ�������wndΪNULL����ʾ������ֻ�ص�������
//			 port���������ݵĶ˿ں�
//			 pUsrData���û��Զ�������
// �������: ��
// �� �� ֵ: >=0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ������
//
DHPLAYSDK_API int __stdcall preview_start(void* wnd, 
										  unsigned short port, 
										  void* pUsrData);

//
// δʵ��
// ��������: ������Ϣ�ص�
// �������:
//			 pCbf:��Ϣ�ص�����
// �������: ��
// �� �� ֵ: 0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ������
//
DHPLAYSDK_API int __stdcall set_msgcbf(CBF_Msg pCbf);

//
// δʵ��
// ��������: ����ȡ���ص�
// �������: 
//			 pCbf:ȡ���ص�����
// �������: ��
// �� �� ֵ: 0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ������
//
DHPLAYSDK_API int __stdcall set_streamcbf(CBF_Stream pCbf);

//
// ��������: ֹͣʵʱԤ��
// �������:
//			 pConf:�����ͻ���������Ϣ
// �������: ��
// �� �� ֵ: 0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ������
//
DHPLAYSDK_API int __stdcall preview_stop(int sessionid);

//
// ��������: ��ʼ�ط�
// �������:
//			 wnd�����Ŵ��ھ��
//			 port���������ݵĶ˿ں�
//			 sdp��rtsp DESCRIBE��Ӧʱ��������SDP��Ϣ
//			 filename�������¼���ļ���
//			 pUsrData���û��Զ�������
// �������: ��
// �� �� ֵ:0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ������
//
DHPLAYSDK_API int __stdcall playback_start(void* wnd, 
										   unsigned short port, 
										   const char* sdp, 
										   char* filename, 
										   void* pUsrData);

//
// ��������: ֹͣ�ط�
// �������:
//			 sessionid��play_back�ɹ��ķ���ֵ��
// �������: ��
// �� �� ֵ: 0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ������
//
DHPLAYSDK_API int __stdcall playback_stop(int sessionid);

//
// ��������: ץͼ
// �������:
//			 sessionid��preview_start��playback_start�ɹ��ķ���ֵ��
//			 picturename��ץͼ������ļ���
//			 iPicMode��0 ��ʾJPEG��1 ��ʾBMP
// �������: ��
// �� �� ֵ: 0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ������
//
DHPLAYSDK_API int __stdcall picture_capture(int sessoinid, const char* picturename, int iPicMode);

//
// ��������: ����������С
// �������:
//			 sessionid: preview_start��playback_start�ɹ��ķ���ֵ��
//			 volume:0-100��100��ʾ�������0��ʾ������
// �������: ��
// �� �� ֵ: 0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ������
//
//DHPLAYSDK_API int __stdcall set_audio_volume(int sessionid, int volume);

// 
// ��������: ��ȡ�����룬�����붨��Ӧ��PART3��¼Bһ�¡�
// �������	
// �������	
// �� �� ֵ: ���ش����
//
DHPLAYSDK_API int __stdcall get_lasterror();


//
// ���� : playback_control�ط��ٶȿ���
// ���� : �طſ���һ·��ʷ�ط�
// ���� : port       -- rtp�˿�
//        ctrl_cmd  -- �طſ�������, ��������
// 		  enum ctrl_cmd    //-- �طſ�������, ��������
//        {
//              HTVIDEO_CONTROL_START   =  1   ,    // ��ʼ/��������
//              HTVIDEO_CONTROL_PAUSE   =  2   ,    // ��ͣ����
//              HTVIDEO_CONTROL_STOP    =  3  ,     // ֹͣ����
//              HTVIDEO_CONTROL_NORMAL  =  4  ,     // �����ٶ�
//              HTVIDEO_CONTROL_FAST    =  5  ,     // ���
//              HTVIDEO_CONTROL_SLOW    =  6  ,     // ����
//              HTVIDEO_CONTROL_SEEK    =  7        // �϶�, ��ղ��Ż���
//        };
//        *psz_para  -- �طſ��Ʋ���, ����
// ע�� : �°�Э���޴˽ӿڣ����δʵ��
//
DHPLAYSDK_API void  __stdcall playback_control(unsigned short port, long ctrl_cmd, char* psz_para);

// 
// ��������: ���ûط��ٶȱ���ֵ
// �������	speed���ط��ٶȱ���ֵ��1��ʾ�����طţ�2��ʾ2���ٻطţ�4��ʾ4���ٻطţ��Դ�����
// �������	��
// �� �� ֵ: 0��ʾ�ɹ�,-1��ʾʧ�ܣ�get_lasterror()��ȡ������
//
DHPLAYSDK_API void __stdcall set_playbackspeed(int sessoinid, int speed);



















// 
// ��������: ��������¼��
// �������:
//			 sessionid��preview_star����playback_start����playlocal_start�����ķ���ֵ��
//			 filename�� ����¼����ļ����ƣ��磺  "d:\xxx\RecordFile.dahua_v3"��RecordFile �ɵ���������������·������dahua_v3:��Ӧ���ҵ�decodertag��ʶ��
// �������: ��	
// �� �� ֵ: 0��ʾ�ɹ���-1��ʾʧ��
//
DHPLAYSDK_API int __stdcall record_start(int sessionid, char * filename);

// 
// ��������: ֹͣ����¼��
// �������:
//			 sessionid��preview_star����playback_start����playlocal_start�����ķ���ֵ��
// �������: ��	
// �� �� ֵ: ��
//
DHPLAYSDK_API void __stdcall record_stop(int sessionid);

// 
// ��������: ��������¼�񲥷�
// �������:
//			 wnd��		������Ƶ���ھ��
//			 filename�� ���ŵı����ļ�����
//			 pUserData���û��Զ�������
// �������: ��	
// �� �� ֵ: sessionid
//
DHPLAYSDK_API int __stdcall playlocal_start(void * wnd, char * filename, void * pUserData);

// 
// ��������: ֹͣ����¼�񲥷�
// �������:
//			 sessionid��preview_star����playback_start����playlocal_start�����ķ���ֵ��
// �������: ��	
// �� �� ֵ: ��
//
DHPLAYSDK_API void __stdcall playlocal_stop(int sessionid);

// 
// ��������: ��ѯ��ǰ�����ļ��Ĳ�����ʱ�䳤��
// �������:
//			 sessionid��playlocal_start�����ķ���ֵ
// �������: ��	
// �� �� ֵ: ��ǰ�����ļ��Ĳ�����ʱ�䣬���ʱ�䣬����Ϊ��λ
//
DHPLAYSDK_API int __stdcall fileplaytotaltime_get(int sessionid);

// 
// ��������: ��ѯ��ǰ����¼�񲥷Ž���
// �������:
//			 sessionid��playlocal_start�����ķ���ֵ
// �������: ��	
// �� �� ֵ: ��ǰ�����ļ��Ĳ���ʱ��㣬���ʱ�䣬����Ϊ��λ
//
DHPLAYSDK_API int __stdcall fileplaycurtime_get(int sessionid);

// 
// ��������: ���õ�ǰ����¼�񲥷�ʱ���
// �������:
//			 sessionid��playlocal_start�����ķ���ֵ
//			 itime    ����Ҫ���ŵ�ʱ��㣬���ʱ�䣬����Ϊ��λ
// �������: ��	
// �� �� ֵ: 0��ʾ�ɹ���-1��ʾʧ��
//
DHPLAYSDK_API int __stdcall fileplaycurtime_set(int sessionid, int itime);

// 
// ��������: �������ؽӿ�
// �������:
//			 sessionid��playlocal_start�����ķ���ֵ
//			 speed    �����õĲ��ű��٣����ٶ������£�
// 						PLAY_STATUS_16_BACKWARD = 0,     /**< 16���ٺ��˲��� */
// 						PLAY_STATUS_8_BACKWARD = 1,      /**< 8���ٺ��˲��� */
//						PLAY_STATUS_4_BACKWARD = 2,      /**< 4���ٺ��˲��� */
// 						PLAY_STATUS_2_BACKWARD = 3,      /**< 2���ٺ��˲��� */
// 						PLAY_STATUS_1_BACKWARD = 4,      /**< �����ٶȺ��˲��� */
// 						PLAY_STATUS_HALF_BACKWARD = 5,   /**< 1/2���ٺ��˲��� */
// 						PLAY_STATUS_QUARTER_BACKWARD = 6,/**< 1/4���ٺ��˲��� */
// 						PLAY_STATUS_QUARTER_FORWARD = 7, /**< 1/4���ٲ��� */
// 						PLAY_STATUS_HALF_FORWARD = 8,    /**< 1/2���ٲ��� */
// 						PLAY_STATUS_1_FORWARD = 9,       /**< �����ٶ�ǰ������ */
// 						PLAY_STATUS_2_FORWARD = 10,      /**< 2����ǰ������ */
// 						PLAY_STATUS_4_FORWARD = 11,      /**< 4����ǰ������ */
// 						PLAY_STATUS_8_FORWARD = 12,      /**< 8����ǰ������ */
// 						PLAY_STATUS_16_FORWARD = 13      /**< 16����ǰ������ */

// �������: ��	
// �� �� ֵ: 0��ʾ�ɹ���-1��ʾʧ��
//
DHPLAYSDK_API int __stdcall playspeed_set(int sessionid, int speed);

// 
// ��������: ��ͣ��ǰ����¼�񲥷�
// �������:
//			 sessionid��playlocal_start�����ķ���ֵ
// �������: ��	
// �� �� ֵ: 0��ʾ�ɹ���-1��ʾʧ��
//
DHPLAYSDK_API int __stdcall play_pause(int sessionid);

// 
// ��������: �ָ�����¼�񲥷�
// �������:
//			 sessionid��playlocal_start�����ķ���ֵ
// �������: ��	
// �� �� ֵ: 0��ʾ�ɹ���-1��ʾʧ��
//
DHPLAYSDK_API int __stdcall play_resume(int sessionid);

// 
// ��������: ����¼�����ص�����¼��
// �������:
//			 port    �����������˿�
//			 SDP     ��rtsp DESCRIBE��ӦʱЯ����SDP��Ϣ
//			 filename������¼����ļ����ƣ��磺  "d:\xxx\RecordFile.dahua_v3"��RecordFile �ɵ���������������·������dahua_v3:��Ӧ���ҵ�decodertag��ʶ��
//			 pUsrData���ص�ʱ���û��Զ�������

// �������: ��	
// �� �� ֵ: sessionid
//
DHPLAYSDK_API int __stdcall download_start(unsigned short port, char * SDP, char * filename, void * pUsrData);

// 
// ��������: ֹͣ¼�����ر���Ϊ����¼��
// �������:
//			 sessionid��download_start�����ķ���ֵ
// �������: ��	
// �� �� ֵ: ��
//
DHPLAYSDK_API void __stdcall download_stop(int sessionid);

// 
// ��������: ���ò��ž���
// �������:
//			 sessionid��playback_start����playlocal_start�����ķ���ֵ��
// �������: ��	
// �� �� ֵ: 0��ʾ�ɹ���-1��ʾʧ��
//
DHPLAYSDK_API int __stdcall sound_stop(int sessionid);

// 
// ��������: ȡ�����ž���
// �������:
//			 sessionid��playback_start����playlocal_start�����ķ���ֵ��
// �������: ��	
// �� �� ֵ: ��
//
DHPLAYSDK_API void __stdcall sound_play(int sessionid);

// 
// ��������: ���ò���ʱ����
// �������:
//			 sessionid��playback_start����playlocal_start�����ķ���ֵ
//			 volume   ��Ϊ���õ������� 0 -- 100��100Ϊ�������
// �������: ��	
// �� �� ֵ: ��
//
DHPLAYSDK_API int __stdcall volume_set(int sessionid, unsigned short volume);










#ifdef  __cplusplus
}
#endif

#endif