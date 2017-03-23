#pragma once
#include <Windows.h>
class IDriverAdaptorPlatfrom
{
public:
	IDriverAdaptorPlatfrom(void);
	~IDriverAdaptorPlatfrom(void);
	//打开设备连接
	virtual BOOL OpenConnection(LPCTSTR strIp, DWORD dwPort, LPCTSTR userName, LPCTSTR password) = 0;
	//关闭连接
	virtual BOOL CloseConnection() = 0;
	//开始实时预览
	virtual BOOL StartRealPlay(CStatic *pStaticCtrl) = 0;

	virtual BOOL StopRealPlay() = 0;
	
	virtual BOOL CloudPatControl(DWORD dwCommand, DWORD dwStartEndFlag, DWORD dwSpeed) = 0;

	virtual BOOL PlayBack(LPCTSTR fileName) = 0;

	virtual BOOL StopPlayBack() = 0;
	
	virtual BOOL PausePlayBack(DWORD dwFlag) = 0;

	virtual BOOL DownLoadFile(LPCTSTR srcFileName, LPCTSTR saveFileName) = 0;

	virtual BOOL StartRecord(LPCTSTR filePath, DWORD dwChannelId) = 0;

	virtual BOOL StopRecord()  = 0;

	virtual BOOL CapturePicture(LPCTSTR filePath, DWORD imageType, DWORD imageSize, DWORD imageQuality, DWORD dwChannelId) = 0;

	virtual BOOL Preset(DWORD dwPoint) = 0;

	virtual BOOL CallPreset(DWORD dwPoint) = 0;
	//不解码显示在窗口上
	virtual BOOL StartRealPlayFtp() = 0;
};

