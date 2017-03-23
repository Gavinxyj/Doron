#pragma once
#include "../DriverAdaptorPlatfrom/IDriverAdaptorPlatfrom.h"
class CDriverAdaptorPlatfromCtrl;
class CHk8600InterfaceImpl : public IDriverAdaptorPlatfrom
{
public:
	CHk8600InterfaceImpl(CDriverAdaptorPlatfromCtrl *pDriverCtrl);
	~CHk8600InterfaceImpl(void);
public:
private:
	CStatic *m_pStaticCtrl;
	CDriverAdaptorPlatfromCtrl *m_pDriverCtrl;
	int m_LoginId;
	int m_playId;

public:
	virtual BOOL OpenConnection(LPCTSTR strIp, DWORD dwPort, LPCTSTR userName, LPCTSTR password);
	//关闭连接
	virtual BOOL CloseConnection();
	//开始实时预览
	virtual BOOL StartRealPlay(CStatic *pStaticCtrl, LPCTSTR params);

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
};

