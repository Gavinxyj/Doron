#pragma once
#define MAX_CHILDWND 32
// DriverAdaptorPlatfromCtrl.h : CDriverAdaptorPlatfromCtrl ActiveX 控件类的声明。
#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>
#include "IDriverAdaptorPlatfrom.h"
#include "DlgOutput.h"
#include <ObjSafe.h>
using namespace log4cxx;
typedef struct _PARAMS
{
	char chIp[32];
	char deviceType[8];
	int  nWindowId;
	int  ncameraId;
	IDriverAdaptorPlatfrom *pDriverAdaptorPat;
	int  nChannelId;
	long loginId;
	BOOL bFlag;

	_PARAMS()
	{
		memset(chIp, 0, 32);
		memset(deviceType,0,8);
		nWindowId  = 0;
		nChannelId = 0;
		ncameraId  = 0;
		loginId    = 0;
		bFlag      = FALSE;
		pDriverAdaptorPat = NULL;
	}

	~_PARAMS()
	{
		memset(chIp, 0, 32);
		memset(deviceType,0,8);
		nWindowId  = 0;
		ncameraId  = 0;
		nChannelId = 0;
		loginId    = 0;
		bFlag      = FALSE;
		if (pDriverAdaptorPat != NULL)
		{
			delete pDriverAdaptorPat;
		}
	}
}PARAMS,*PPARAMS;
// CDriverAdaptorPlatfromCtrl : 有关实现的信息，请参阅 DriverAdaptorPlatfromCtrl.cpp。

class CDriverAdaptorPlatfromCtrl : public COleControl
{
	DECLARE_DYNCREATE(CDriverAdaptorPlatfromCtrl)

// 构造函数
public:
	CDriverAdaptorPlatfromCtrl();
	IDriverAdaptorPlatfrom *m_pDriverAdaptorPat;
// 重写
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
public:
	CMap<CString,LPCTSTR,PPARAMS,PPARAMS>m_mapFactory;
	CDlgOutput *m_pDlgOutPut[MAX_CHILDWND];
	CStatic    m_static[MAX_CHILDWND];
	int m_curWndIndex;
    LoggerPtr logger;
	ULONG_PTR m_gdiplusToken;
	SHORT m_windowId;
	CString m_strIpAddr;
// 实现
protected:
	~CDriverAdaptorPlatfromCtrl();

	DECLARE_OLECREATE_EX(CDriverAdaptorPlatfromCtrl)    // 类工厂和 guid
	DECLARE_OLETYPELIB(CDriverAdaptorPlatfromCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CDriverAdaptorPlatfromCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(CDriverAdaptorPlatfromCtrl)		// 类型名称和杂项状态

	DECLARE_INTERFACE_MAP()
	BEGIN_INTERFACE_PART(ObjSafe, IObjectSafety);
		STDMETHOD_(HRESULT, GetInterfaceSafetyOptions) (
		REFIID riid,
		DWORD __RPC_FAR *pdwSupportedOptions,
		DWORD __RPC_FAR *pdwEnabledOptions
		);
		STDMETHOD_(HRESULT, SetInterfaceSafetyOptions) (
			REFIID riid,
			DWORD dwOptionSetMask,
			DWORD dwEnabledOptions
			);
	END_INTERFACE_PART(ObjSafe);

// 消息映射
	DECLARE_MESSAGE_MAP()

// 调度映射
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// 事件映射
	DECLARE_EVENT_MAP()

// 调度和事件 ID
public:
	enum {
		eventidIPADDRESS = 1L,
		dispidIPAddress = 15,
		dispidCallPreset = 14L,
		dispidPreset = 13L,
		dispidsplitScreen = 12L,
		dispidCapturePicture = 11L,
		dispidStopPlayBack = 10L,
		dispidPlayBack = 9L,
		dispidStopRecord = 8L,
		dispidStartRecord = 7L,
		dispidCloudPatControl = 6L,
		dispidCloseConntecion = 5L,
		dispidStopRealPlay = 4L,
		dispidStartRealPlay = 3L,
		dispidOpenConnection = 2L,
		dispidwindowId = 1
	};
public:
	SHORT OpenConnection(LPCTSTR strIp, ULONG dwPort, LPCTSTR userName, LPCTSTR password, LPCTSTR DeviceType, LPCTSTR params);
	SHORT StartRealPlay(LPCTSTR params);
	SHORT StopRealPlay(LPCTSTR params);
	SHORT CloseConnection(LPCTSTR params);
	SHORT CloudPatControl(ULONG dwCommand, SHORT startEndFlag, SHORT speed,LPCTSTR params);
	SHORT StartRecord(LPCTSTR filePath, ULONG dwChannelId, LPCTSTR DeviceType, LPCTSTR params);
	SHORT StopRecord(ULONG dwChannelId, LPCTSTR DeviceType, LPCTSTR params);
	SHORT PlayBack(LPCTSTR fileName, LPCTSTR DeviceType, LPCTSTR params);
	SHORT StopPlayBack(LPCTSTR DeviceType, LPCTSTR params);
	SHORT CapturePicture(LPCTSTR filePath, SHORT imageType, SHORT imageSize, SHORT imageQuality, SHORT dwChannelId, LPCTSTR DeviceType, LPCTSTR params);
	SHORT splitScreen(SHORT dwScreenNum);
	SHORT Preset(SHORT dwPoint, LPCTSTR DeviceType, LPCTSTR params);
	SHORT CallPreset(SHORT dwPoint, LPCTSTR DeviceType, LPCTSTR params);
private:
	bool InitSocket();

	void ftpRecv(SOCKET inSocket, char* buffer, int nLen);

	void ftpSend(SOCKET inSocket, char* command, int nLen);

	void setTimeout(SOCKET inSocket,bool brecv,int timeout);
public:
	SHORT GetwindowId(void);
	void SetwindowId(SHORT newVal);
	BSTR GetIPAddress(void);
	void SetIPAddress(LPCTSTR newVal);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
public:
	void IPADDRESS(LPCTSTR ipAddr)
	{
		FireEvent(eventidIPADDRESS, EVENT_PARAM(VTS_BSTR), ipAddr);
	}
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

