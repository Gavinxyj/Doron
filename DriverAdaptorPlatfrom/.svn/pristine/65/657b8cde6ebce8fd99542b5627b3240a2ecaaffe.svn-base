
#pragma once


//#include "stdafx.h"

#include "../DriverAdaptorPlatfrom/IDriverAdaptorPlatfrom.h"
#include "GeneralDef.h"

//class CDlgOutput;
class CDriverAdaptorPlatfromCtrl;
class CHkInterfaceImpl : public IDriverAdaptorPlatfrom
{
public:
	//CHkInterfaceImpl(CDlgOutput *pDriverCtrl);
	CHkInterfaceImpl(CDriverAdaptorPlatfromCtrl *pDriverCtrl);

	CHkInterfaceImpl();
	//CHkInterfaceImpl();
	virtual ~CHkInterfaceImpl(void);
public:
	CStatic *m_pStaticCtrl;
	CDriverAdaptorPlatfromCtrl *m_pDriverCtrl;
public:
	virtual BOOL OpenConnection(LPCTSTR strIp, DWORD dwPort, LPCTSTR userName, LPCTSTR password);
	//关闭连接
	virtual BOOL CloseConnection();
	//开始实时预览
	virtual BOOL StartRealPlay(CStatic *pStaticCtrl);

	virtual BOOL StopRealPlay();

	virtual BOOL CloudPatControl(DWORD dwCommand, DWORD dwStartEndFlag, DWORD dwSpeed);

	virtual BOOL PlayBack(LPCTSTR fileName);

	virtual BOOL StopPlayBack();

	virtual BOOL PausePlayBack(DWORD dwFlag);

	virtual BOOL DownLoadFile(LPCTSTR srcFileName, LPCTSTR saveFileName);

	virtual BOOL StartRecord(LPCTSTR filePath, DWORD dwChannelId = 1);

	virtual BOOL StopRecord();

	virtual BOOL CapturePicture(LPCTSTR filePath, DWORD imageType, DWORD imageSize, DWORD imageQuality, DWORD dwChannelId);

	virtual BOOL Preset(DWORD dwPoint);

	virtual BOOL CallPreset(DWORD dwPoint);

	//不解码显示在窗口上
	virtual BOOL StartRealPlayFtp();

private:
	void GetDecoderCfg();
	void GetDeviceChannelInfo();
private:
	DWORD m_TotalFrames;
	DWORD m_TotalTimes;
	LONG m_lPlayHandle;
	BOOL m_bIsRecording;
	BOOL m_bIsPlaying;
	LOCAL_DEVICE_INFO m_struDeviceInfo;
	
};

