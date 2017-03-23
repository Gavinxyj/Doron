#pragma once
#include "clientplayer.h"
#include "clientsdk.h"
#include "ItemMgr.h"
#include "JsonParse.h"
class CInterfaceImpl
{
private:
	CInterfaceImpl(void);
	~CInterfaceImpl(void);
	static CInterfaceImpl * m_pInterfaceImpl;
public:
	static CInterfaceImpl * getInitance();
	long m_fd;
	int m_nLoginId;
public:
	//ץͼ
	bool Capture(LPCTSTR strPath, int nLoginId);
	//��ʼԤ��
	long StartVideo(CONNECTINFO *connInfo);
	//ֹͣԤ��
	bool StopVideo(int nLoginId);
	//��½�豸
	bool LoginDev(PITEMDATA itemData);
	//��ʼ���豸
	bool InitMsSdk();
	//��̨����
	bool PtzControl(Client_PTZ_Command *cmd, int nLoginId);
	//������Ƶ����
	bool SetVideoParam(int bright, int contrast, int saturation, int hue, int nLoginId);
	//������
	bool OpenSound(int nLoginId);
	//�ر�����
	bool CloseSound(int nLoginId);
	//��������
	bool SetVolumn(int volumn, int nLoginId);
	//�����л�
	bool StartSwitchSingle(LPCTSTR strId);
	//���������л�
	bool StopSwitchSingle(int nLoginId, int nWindowId, int nTiemOut);
	//ֹͣ�����л�
	bool StopSwitchTemplate();
	//��ʼ¼��
	bool StartRecord(int nLoginId);
	//ֹͣ¼��
	bool StopRecord(int nLoginId);
	//��ʼ�Խ�
	bool StartTalk(int nTalkId);
	//ֹͣ�Խ�
	bool StopTalk(int takkId);
	//��ʼ�л�ģʽ
	bool StartSwitchTemplate();
	//������ʾ��ʽ
	bool SetScreenStyle(int x, int y, int z);
	//��ʼ�����ļ�
	bool StartDownload(LPCTSTR strInfo);
	//ֹͣ�����ļ�
	bool StopDownload(int nFd);
	//����¼�����
	bool SetRecordPlan(LPCTSTR strInfo);
	//����ץ��·��
	bool SetCapturePath(LPCTSTR strInfo);
	//ֹͣ������ƵԤ��
	bool StopAllVideo();
	//�л�����һ������
	bool MoveNext();
	//ѡ���ļ���
	bool SelectFolder();
	//��������·��
	bool SetDownloadPath(LPCTSTR strInfo);
	//��ȡ��Ƶ����
	bool GetVideoParam(int nLoginId, VIDEOPARAM *m_videoParam);
	//�ͷ���Դ
	bool ReleaseRes();
	//���������ļ�
	bool PlaySoundFile(LPCTSTR strInfo);
	//��ȡ�����ID
	bool GetCurCameraObjId();
	//���ý���
	bool SetActive(int num);
	//��ȡ��ǰ���
	bool GetMonitorNum();
	//���ñ������
	bool SetAlarmOut(LPCTSTR strDevInfo, int status);
	//��ȡ�����б�
	bool GetDiskList();
	//���ûط��������ļ�
	bool CallHardPlay(LPCTSTR strFileName, int type);
	//���ӷŴ�
	bool ZoomEnlarge(int nLoginId, HWND hWnd, RectZoom* rect_zoom, int count, OUT int* zoom_id);
	//
	bool SetZoom(int nLoginId, int nZoomId, RectZoom &rectZoom);
	//ֹͣ�Ŵ�
	bool RemoveZoom(int nLoginId, int nZoomId);
};
