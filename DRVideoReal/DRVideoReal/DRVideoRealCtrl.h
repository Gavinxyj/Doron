#pragma once
#define MAX_CHILDWND 36
// DRVideoRealCtrl.h : CDRVideoRealCtrl ActiveX 控件类的声明。
#include "VideoReal.h"
// CDRVideoRealCtrl : 有关实现的信息，请参阅 DRVideoRealCtrl.cpp。
#define  WM_RECVDATA	(WM_USER + 1)

class CDRVideoRealCtrl : public COleControl
{
	DECLARE_DYNCREATE(CDRVideoRealCtrl)

// 构造函数
public:
	CDRVideoRealCtrl();

// 重写
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// 实现
protected:
	~CDRVideoRealCtrl();

	DECLARE_OLECREATE_EX(CDRVideoRealCtrl)    // 类工厂和 guid
	DECLARE_OLETYPELIB(CDRVideoRealCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CDRVideoRealCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(CDRVideoRealCtrl)		// 类型名称和杂项状态

// 消息映射
	DECLARE_MESSAGE_MAP()

// 调度映射
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// 事件映射
	DECLARE_EVENT_MAP()

public:
	CMap<int, int, CVideoReal*, CVideoReal*>m_mapVideoReal;
	CMap<int, int, PCONNECTINFO, PCONNECTINFO>m_mapConnInfo;
	CVideoReal *m_pVideoReal[MAX_CHILDWND];
	int m_curWndIndex;
	char m_curMoudlePath[256];
	CRect m_rect;
	int m_preWndIndex;
	CPoint m_prePoint;
	std::vector<WINSTYLE>m_oldRect;
	CMap<int, int, PWINSTYLE, PWINSTYLE>m_mapRect;
public:
	SHORT Init(LPCTSTR strJsonParam);
	SHORT Capture(LPCTSTR strPath);
	SHORT CaptureAll(LPCTSTR strPath);
	SHORT PtzControl(LPCTSTR strCmd, LPCTSTR strParam, LPCTSTR strStart);
	SHORT SetVideoParam(SHORT bright, SHORT contrast, SHORT saturation, SHORT hue);
	SHORT OpenSound(void);
	SHORT CloseSound(void);
	SHORT SetVolumn(SHORT volumn);
	SHORT StartVideo(LPCTSTR strJsonCamInfo);
	SHORT StopVideo(void);
	SHORT StartSwitchTemplate(LPCTSTR strId);
	SHORT StopSwitchSingle(void);
	SHORT StartRecord(void);
	SHORT StopRecord(void);
	SHORT StartAllRecord(void);
	SHORT StopAllRecord(void);
	SHORT StartTalk(LPCTSTR strInfo);
	SHORT StopTalk(void);
	SHORT StartSwitchSingle(LPCTSTR strId);
	SHORT StopSwitchTemplate(void);
	SHORT SetScreenStyle(SHORT x, SHORT y, SHORT z);
	SHORT BrowseFolder(LPCTSTR strPath);
	SHORT GetDownloadList(void);
	SHORT StartDownload(LPCTSTR strInfo);
	SHORT StopDownload(SHORT fd);
	SHORT SetRecordPlan(LPCTSTR strInfo);
	SHORT SetCapturePath(LPCTSTR strInfo);
	SHORT StopAllVideo(void);
	SHORT MoveNext(void);
	SHORT SelectFolder(LPCTSTR strPath);
	SHORT SetDownloadPath(LPCTSTR strPath);
	SHORT GetVideoParam(void);
	SHORT ReleaseRes(void);
	SHORT PlaySoundFile(LPCTSTR strPath);
	BSTR GetCurCameraObjId(void);
	SHORT SetActive(SHORT num);
	SHORT GetMonitorNum(void);
	SHORT SetAlarmOut(LPCTSTR strDevInfo, SHORT status);
	SHORT GetDiskList(void);
	SHORT CallHardPlay(LPCTSTR strFileName, SHORT type);
	SHORT SplitScreen(SHORT num);
	SHORT CaptureEx(SHORT type);
	BSTR PictureToBase64(LPCTSTR fileName);
public:
	static DWORD WINAPI ThreadProc(LPVOID lpParameter);
	__int64 CompareFileTime(FILETIME time1, FILETIME time2);
// 调度和事件 ID
public:
	enum {
		dispidPictureToBase64 = 43L,
		dispidCaptureEx = 42L,
		eventidOnSysInfo = 1L,
		dispidSplitScreen = 41L,
		dispidCallHardPlay = 40L,
		dispidGetDiskList = 39L,
		dispidSetAlarmOut = 38L,
		dispidGetMonitorNum = 37L,
		dispidSetActive = 36L,
		dispidGetCurCameraObjId = 35L,
		dispidPlaySoundFile = 34L,
		dispidReleaseRes = 33L,
		dispidGetVideoParam = 32L,
		dispidSetDownloadPath = 31L,
		dispidSelectFolder = 30L,
		dispidMoveNext = 29L,
		dispidStopAllVideo = 28L,
		dispidSetCapturePath = 27L,
		dispidSetRecordPlan = 26L,
		dispidStopDownload = 25L,
		dispidStartDownload = 24L,
		dispidGetDownloadList = 23L,
		dispidBrowseFolder = 22L,
		dispidSetScreenStyle = 21L,
		dispidStopSwitchTemplate = 20L,
		dispidStartSwitchSingle = 19L,
		dispidStopTalk = 18L,
		dispidStartTalk = 17L,
		dispidStopAllRecord = 16L,
		dispidStartAllRecord = 15L,
		dispidStopRecord = 14L,
		dispidStartRecord = 13L,
		dispidStopSwitchSingle = 12L,
		dispidStartSwitchTemplate = 11L,
		dispidStopVideo = 10L,
		dispidStartVideo = 9L,
		dispidSetVolumn = 8L,
		dispidCloseSound = 7L,
		dispidOpenSound = 6L,
		dispidSetVideoParam = 5L,
		dispidPtzControl = 4L,
		dispidCaptureAll = 3L,
		dispidCapture = 2L,
		dispidInit = 1L
	};
protected:
	
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnRecvMsg(WPARAM wparam, LPARAM lparam);
protected:	
	void OnSysInfo(LONG cpu, LONG mem)
	{
		FireEvent(eventidOnSysInfo, EVENT_PARAM(VTS_I4 VTS_I4), cpu, mem);
	}
	
};

