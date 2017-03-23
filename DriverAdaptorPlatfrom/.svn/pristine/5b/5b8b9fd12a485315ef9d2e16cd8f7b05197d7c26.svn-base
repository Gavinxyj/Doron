#pragma once

#include "../DriverAdaptorPlatfrom/IDriverAdaptorPlatfrom.h"
#include "../../include32/dhnetsdk.h"
class CDriverAdaptorPlatfromCtrl;
class CDhInterfaceImpl : public IDriverAdaptorPlatfrom
{
public:
	//CHkInterfaceImpl(CDlgOutput *pDriverCtrl);
	CDhInterfaceImpl(CDriverAdaptorPlatfromCtrl *pDriverCtrl);
	CDhInterfaceImpl();
	//CHkInterfaceImpl();
	virtual ~CDhInterfaceImpl(void);
private:
	CStatic *m_pStaticCtrl;
	CDriverAdaptorPlatfromCtrl *m_pDriverCtrl;
	LONG m_loginId;
	int  m_channelCount;
	long m_realPlayId;
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

	virtual BOOL StartRealPlayFtp();

public:
	friend void CALLBACK DisConnectFunc(LONG lLoginID, char *pchDVRIP, LONG nDVRPort, DWORD dwUser);
};

