// DRVideoRealCtrl.cpp : CDRVideoRealCtrl ActiveX 控件类的实现。

#include "stdafx.h"
#include "DRVideoReal.h"
#include "DRVideoRealCtrl.h"
#include "DRVideoRealPropPage.h"
#include "afxdialogex.h"
#include "JsonParse.h"
#include "InterfaceImpl.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CDRVideoRealCtrl, COleControl)



// 消息映射

BEGIN_MESSAGE_MAP(CDRVideoRealCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// 调度映射

BEGIN_DISPATCH_MAP(CDRVideoRealCtrl, COleControl)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "Init", dispidInit, Init, VT_I2, VTS_BSTR)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "Capture", dispidCapture, Capture, VT_I2, VTS_BSTR)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "CaptureAll", dispidCaptureAll, CaptureAll, VT_I2, VTS_BSTR)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "PtzControl", dispidPtzControl, PtzControl, VT_I2, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "SetVideoParam", dispidSetVideoParam, SetVideoParam, VT_I2, VTS_I2 VTS_I2 VTS_I2 VTS_I2)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "OpenSound", dispidOpenSound, OpenSound, VT_I2, VTS_NONE)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "CloseSound", dispidCloseSound, CloseSound, VT_I2, VTS_NONE)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "SetVolumn", dispidSetVolumn, SetVolumn, VT_I2, VTS_I2)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "StartVideo", dispidStartVideo, StartVideo, VT_I2, VTS_BSTR)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "StopVideo", dispidStopVideo, StopVideo, VT_I2, VTS_NONE)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "StartSwitchTemplate", dispidStartSwitchTemplate, StartSwitchTemplate, VT_I2, VTS_BSTR)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "StopSwitchSingle", dispidStopSwitchSingle, StopSwitchSingle, VT_I2, VTS_NONE)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "StartRecord", dispidStartRecord, StartRecord, VT_I2, VTS_NONE)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "StopRecord", dispidStopRecord, StopRecord, VT_I2, VTS_NONE)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "StartAllRecord", dispidStartAllRecord, StartAllRecord, VT_I2, VTS_NONE)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "StopAllRecord", dispidStopAllRecord, StopAllRecord, VT_I2, VTS_NONE)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "StartTalk", dispidStartTalk, StartTalk, VT_I2, VTS_BSTR)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "StopTalk", dispidStopTalk, StopTalk, VT_I2, VTS_NONE)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "StartSwitchSingle", dispidStartSwitchSingle, StartSwitchSingle, VT_I2, VTS_BSTR)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "StopSwitchTemplate", dispidStopSwitchTemplate, StopSwitchTemplate, VT_I2, VTS_NONE)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "SetScreenStyle", dispidSetScreenStyle, SetScreenStyle, VT_I2, VTS_I2 VTS_I2 VTS_I2)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "BrowseFolder", dispidBrowseFolder, BrowseFolder, VT_I2, VTS_BSTR)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "GetDownloadList", dispidGetDownloadList, GetDownloadList, VT_I2, VTS_NONE)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "StartDownload", dispidStartDownload, StartDownload, VT_I2, VTS_BSTR)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "StopDownload", dispidStopDownload, StopDownload, VT_I2, VTS_I2)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "SetRecordPlan", dispidSetRecordPlan, SetRecordPlan, VT_I2, VTS_BSTR)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "SetCapturePath", dispidSetCapturePath, SetCapturePath, VT_I2, VTS_BSTR)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "StopAllVideo", dispidStopAllVideo, StopAllVideo, VT_I2, VTS_NONE)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "MoveNext", dispidMoveNext, MoveNext, VT_I2, VTS_NONE)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "SelectFolder", dispidSelectFolder, SelectFolder, VT_I2, VTS_BSTR)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "SetDownloadPath", dispidSetDownloadPath, SetDownloadPath, VT_I2, VTS_BSTR)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "GetVideoParam", dispidGetVideoParam, GetVideoParam, VT_I2, VTS_NONE)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "ReleaseRes", dispidReleaseRes, ReleaseRes, VT_I2, VTS_NONE)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "PlaySoundFile", dispidPlaySoundFile, PlaySoundFile, VT_I2, VTS_BSTR)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "GetCurCameraObjId", dispidGetCurCameraObjId, GetCurCameraObjId, VT_BSTR, VTS_NONE)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "SetActive", dispidSetActive, SetActive, VT_I2, VTS_I2)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "GetMonitorNum", dispidGetMonitorNum, GetMonitorNum, VT_I2, VTS_NONE)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "SetAlarmOut", dispidSetAlarmOut, SetAlarmOut, VT_I2, VTS_BSTR VTS_I2)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "GetDiskList", dispidGetDiskList, GetDiskList, VT_I2, VTS_NONE)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "CallHardPlay", dispidCallHardPlay, CallHardPlay, VT_I2, VTS_BSTR VTS_I2)
	DISP_FUNCTION_ID(CDRVideoRealCtrl, "SplitScreen", dispidSplitScreen, SplitScreen, VT_I2, VTS_I2)
END_DISPATCH_MAP()



// 事件映射

BEGIN_EVENT_MAP(CDRVideoRealCtrl, COleControl)
	
	EVENT_CUSTOM_ID("OnSysInfo", eventidOnSysInfo, OnSysInfo, VTS_I4 VTS_I4)
END_EVENT_MAP()



// 属性页

// TODO: 按需要添加更多属性页。请记住增加计数!
BEGIN_PROPPAGEIDS(CDRVideoRealCtrl, 1)
	PROPPAGEID(CDRVideoRealPropPage::guid)
END_PROPPAGEIDS(CDRVideoRealCtrl)



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CDRVideoRealCtrl, "DRVIDEOREAL.DRVideoRealCtrl.1",
	0xe457fb87, 0x4610, 0x43d1, 0xb9, 0x9f, 0x56, 0xe1, 0x8, 0x61, 0x48, 0x80)



	// 键入库 ID 和版本

	IMPLEMENT_OLETYPELIB(CDRVideoRealCtrl, _tlid, _wVerMajor, _wVerMinor)



	// 接口 ID

	const IID IID_DDRVideoReal = { 0x51131C17, 0xF78B, 0x4BB3, { 0x83, 0xB6, 0xEF, 0xF0, 0xFC, 0xAC, 0x2B, 0x56 } };
const IID IID_DDRVideoRealEvents = { 0x565438E1, 0x65B3, 0x4F8E, { 0x8C, 0x6E, 0xA1, 0x7B, 0xD6, 0xB9, 0x70, 0x26 } };


// 控件类型信息

static const DWORD _dwDRVideoRealOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CDRVideoRealCtrl, IDS_DRVIDEOREAL, _dwDRVideoRealOleMisc)



	// CDRVideoRealCtrl::CDRVideoRealCtrlFactory::UpdateRegistry -
	// 添加或移除 CDRVideoRealCtrl 的系统注册表项

	BOOL CDRVideoRealCtrl::CDRVideoRealCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: 验证您的控件是否符合单元模型线程处理规则。
	// 有关更多信息，请参考 MFC 技术说明 64。
	// 如果您的控件不符合单元模型规则，则
	// 必须修改如下代码，将第六个参数从
	// afxRegApartmentThreading 改为 0。

	if (bRegister)
		return AfxOleRegisterControlClass(
		AfxGetInstanceHandle(),
		m_clsid,
		m_lpszProgID,
		IDS_DRVIDEOREAL,
		IDB_DRVIDEOREAL,
		afxRegApartmentThreading,
		_dwDRVideoRealOleMisc,
		_tlid,
		_wVerMajor,
		_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CDRVideoRealCtrl::CDRVideoRealCtrl - 构造函数

CDRVideoRealCtrl::CDRVideoRealCtrl()
{
	InitializeIIDs(&IID_DDRVideoReal, &IID_DDRVideoRealEvents);
	// TODO: 在此初始化控件的实例数据。
	m_curWndIndex = 0;
	m_preWndIndex = 0;
	m_mapVideoReal.RemoveAll();
	m_mapConnInfo.RemoveAll();
	m_oldRect.clear();
	HMODULE hModule = GetModuleHandle("DRVideoReal.ocx");

	memset(m_curMoudlePath, 0, 256);
	if (hModule != NULL)
	{
		GetModuleFileName(hModule,m_curMoudlePath, sizeof(m_curMoudlePath));
	}
/*
	DWORD dwThreadId = 0;
	HANDLE hThread = CreateThread(NULL, 0, ThreadProc, this, 0, &dwThreadId);
	Sleep(1000);
	CloseHandle(hThread);*/
}



// CDRVideoRealCtrl::~CDRVideoRealCtrl - 析构函数

CDRVideoRealCtrl::~CDRVideoRealCtrl()
{
	// TODO: 在此清理控件的实例数据。

	for (int nLoop = 0; nLoop < MAX_CHILDWND; nLoop ++)
	{
		if (NULL != m_pVideoReal[nLoop])
		{
			delete m_pVideoReal[nLoop];
			m_pVideoReal[nLoop] = NULL;
		}		
	}
	m_mapVideoReal.RemoveAll();

	int nWindowId = 0;
	CONNECTINFO *pConnInfo = NULL;
	POSITION pos = m_mapConnInfo.GetStartPosition(); 
	while(pos) 
	{ 
		m_mapConnInfo.GetNextAssoc(pos,nWindowId,pConnInfo);
		if ( NULL != pConnInfo)
		{
			delete pConnInfo;
			pConnInfo = NULL;
		}
	} 
	m_mapConnInfo.RemoveAll();

	if (NULL != CJsonParse::getInstance())
	{
		delete CJsonParse::getInstance();
	}
}



// CDRVideoRealCtrl::OnDraw - 绘图函数

void CDRVideoRealCtrl::OnDraw(
	CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: 用您自己的绘图代码替换下面的代码。
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	//pdc->Ellipse(rcBounds);
}



// CDRVideoRealCtrl::DoPropExchange - 持久性支持

void CDRVideoRealCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: 为每个持久的自定义属性调用 PX_ 函数。
}



// CDRVideoRealCtrl::OnResetState - 将控件重置为默认状态

void CDRVideoRealCtrl::OnResetState()
{
	COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值

	// TODO: 在此重置任意其他控件状态。
}



// CDRVideoRealCtrl::AboutBox - 向用户显示“关于”框

void CDRVideoRealCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_DRVIDEOREAL);
	dlgAbout.DoModal();
}



// CDRVideoRealCtrl 消息处理程序


SHORT CDRVideoRealCtrl::Init(LPCTSTR strJsonParam)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	
	if (NULL == strJsonParam) return -1;
	
	if (NULL != CJsonParse::getInstance())
	{
	
		CJsonParse::getInstance()->parseJsonStr(strJsonParam);

		if (CJsonParse::getInstance()->m_pItemData->ocxType == 0)
		{
			bool bRet = CInterfaceImpl::getInitance()->InitMsSdk();

			if (!bRet) return -1;

			PITEMDATA pTemp = CJsonParse::getInstance()->m_pItemData;
			
			bRet = CInterfaceImpl::getInitance()->LoginDev(CJsonParse::getInstance()->m_pItemData);

			if (!bRet) return -1;
		}
		else if (CJsonParse::getInstance()->m_pItemData->ocxType == 1)//tvOcx
		{

		}
	}

	return 0;
}


SHORT CDRVideoRealCtrl::Capture(LPCTSTR strPath)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	CVideoReal *pVideoReal = NULL;

	bool bRet = false;
	if (m_mapVideoReal.Lookup(m_curWndIndex, pVideoReal))
	{
		if (NULL != pVideoReal)
		{
			bRet = pVideoReal->Capture(strPath);
		}
	}

	return bRet;
}


SHORT CDRVideoRealCtrl::CaptureAll(LPCTSTR strPath)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	for (int nLoop = 0; nLoop < MAX_CHILDWND; nLoop ++)
	{
		if (NULL != m_pVideoReal[nLoop] && m_pVideoReal[nLoop]->m_played)
		{
			m_pVideoReal[nLoop]->Capture(strPath);
		}		
	}
	return 0;
}


SHORT CDRVideoRealCtrl::PtzControl(LPCTSTR strCmd, LPCTSTR strParam, LPCTSTR strStart)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	Client_PTZ_Command cmd;

	ZeroMemory(&cmd, sizeof(Client_PTZ_Command));
	cmd.cmd	  = atoi(strCmd);
	cmd.param = atoi(strParam);
	cmd.start = atoi(strStart);
	bool bRet = false;

	CVideoReal *pVideoReal = NULL;
	
	if (m_mapVideoReal.Lookup(m_curWndIndex, pVideoReal))
	{
		if (NULL != pVideoReal && pVideoReal->m_played)
		{
			bRet = pVideoReal->PtzControl(&cmd);
		}
	}

	
	return bRet;
}


SHORT CDRVideoRealCtrl::SetVideoParam(SHORT bright, SHORT contrast, SHORT saturation, SHORT hue)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	CVideoReal *pVideoReal = NULL;
	bool bRet = false;
	if (m_mapVideoReal.Lookup(m_curWndIndex, pVideoReal))
	{
		if (NULL != pVideoReal && pVideoReal->m_played)
		{
			bRet = pVideoReal->SetVideoParam(bright, contrast, saturation, hue);
		}
	}
	return bRet;
}


SHORT CDRVideoRealCtrl::OpenSound(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	CVideoReal *pVideoReal = NULL;
	bool bRet = false;
	if (m_mapVideoReal.Lookup(m_curWndIndex, pVideoReal))
	{
		if (NULL != pVideoReal && pVideoReal->m_played)
		{
			bRet = pVideoReal->OpenSound();
		}
	}

	return bRet;
}


SHORT CDRVideoRealCtrl::CloseSound(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	CVideoReal *pVideoReal = NULL;
	bool bRet = false;
	if (m_mapVideoReal.Lookup(m_curWndIndex, pVideoReal))
	{
		if (NULL != pVideoReal && pVideoReal->m_played)
		{
			bRet = pVideoReal->CloseSound();
		}
	}

	return bRet;
}


SHORT CDRVideoRealCtrl::SetVolumn(SHORT volumn)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	CVideoReal *pVideoReal = NULL;

	bool bRet = false;

	if (m_mapVideoReal.Lookup(m_curWndIndex, pVideoReal))
	{
		if (NULL != pVideoReal)
		{
			bRet = pVideoReal->SetVolumn(volumn);
		}
	}


	return bRet;
}


SHORT CDRVideoRealCtrl::StartVideo(LPCTSTR strJsonCamInfo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	CVideoReal *pVideoReal = NULL;

	bool bRet = false;

	if (m_mapVideoReal.Lookup(m_curWndIndex, pVideoReal))
	{
		if (NULL != pVideoReal)
		{
			LOG4CXX_INFO(CJsonParse::getInstance()->logger, "m_curWndIndex = " << m_curWndIndex << "; pVideoReal = " << pVideoReal);
			CJsonParse::getInstance()->parseJsonConnInfo(strJsonCamInfo);
			
			if (NULL != CJsonParse::getInstance())
			{	
				if (pVideoReal->m_played)
				{
					pVideoReal->StopVideo();
				}
				CJsonParse::getInstance()->m_pConnInfo->info.hPlayWnd = pVideoReal->GetSafeHwnd();
				bRet = pVideoReal->StartVideo(CJsonParse::getInstance()->m_pConnInfo);
				PCONNECTINFO connInfo = new CONNECTINFO;
				memcpy(connInfo, CJsonParse::getInstance()->m_pConnInfo, sizeof(CONNECTINFO));
				m_mapConnInfo.SetAt(m_curWndIndex, connInfo);
			}		
		}
	}

	return bRet;
}


SHORT CDRVideoRealCtrl::StopVideo(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	CVideoReal *pVideoReal = NULL;

	bool bRet = false;

	if (m_mapVideoReal.Lookup(m_curWndIndex, pVideoReal))
	{
		if (NULL != pVideoReal && pVideoReal->m_played)
		{
			bRet = pVideoReal->StopVideo();
		}
	}

	return bRet;
}


SHORT CDRVideoRealCtrl::StartSwitchTemplate(LPCTSTR strId)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	bool bRet = CInterfaceImpl::getInitance()->StartSwitchTemplate();

	return bRet;
}


SHORT CDRVideoRealCtrl::StopSwitchSingle(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	CVideoReal *pVideoReal = NULL;

	bool bRet = false;
	if (m_mapVideoReal.Lookup(m_curWndIndex, pVideoReal))
	{
		if (NULL != pVideoReal && pVideoReal->m_played)
		{
			bRet = pVideoReal->StopSwitchSingle();
		}
	}

	return bRet;
}


SHORT CDRVideoRealCtrl::StartRecord(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	CVideoReal *pVideoReal = NULL;

	bool bRet = false;
	if (m_mapVideoReal.Lookup(m_curWndIndex, pVideoReal))
	{
		if (NULL != pVideoReal && pVideoReal->m_played)
		{
			bRet = pVideoReal->StartRecord();
		}
	}

	return bRet;
}


SHORT CDRVideoRealCtrl::StopRecord(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	CVideoReal *pVideoReal = NULL;
	bool bRet = false;
	if (m_mapVideoReal.Lookup(m_curWndIndex, pVideoReal))
	{
		if (NULL != pVideoReal)
		{
			bRet = pVideoReal->StopRecord();
		}
	}

	return bRet;
}


SHORT CDRVideoRealCtrl::StartAllRecord(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	for (int nLoop = 0; nLoop < MAX_CHILDWND; nLoop ++)
	{
		if (NULL != m_pVideoReal[nLoop] && m_pVideoReal[nLoop]->m_played)
		{
			m_pVideoReal[nLoop]->StartRecord();
		}

	}
	return 0;
}


SHORT CDRVideoRealCtrl::StopAllRecord(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	for (int nLoop = 0; nLoop < MAX_CHILDWND; nLoop ++)
	{
		if (NULL != m_pVideoReal[nLoop] && m_pVideoReal[nLoop]->m_played)
		{
			m_pVideoReal[nLoop]->StopRecord();
		}

	}

	return 0;
}


SHORT CDRVideoRealCtrl::StartTalk(LPCTSTR strInfo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	if (NULL == CInterfaceImpl::getInitance() || NULL == CJsonParse::getInstance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance 实例化失败 ");
		return -1;
	}

	bool bRet = CJsonParse::getInstance()->parseJsonTalkInfo(strInfo);

	if (!bRet)
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "JSON字符串解析失败，请检查JSON字符串是否符合格式");
		return -1;
	}

	CVideoReal *pVideoReal = NULL;

	if (m_mapVideoReal.Lookup(m_curWndIndex, pVideoReal))
	{
		if (NULL != pVideoReal && pVideoReal->m_played)
		{
			bRet = pVideoReal->StartTalk();
		}
	}

	return bRet;
}


SHORT CDRVideoRealCtrl::StopTalk(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance 实例化失败 ");
		return -1;
	}

	bool bRet = CInterfaceImpl::getInitance()->StopTalk(m_curWndIndex);

	return bRet;
}


SHORT CDRVideoRealCtrl::StartSwitchSingle(LPCTSTR strId)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance 实例化失败 ");
		return -1;
	}

	bool bRet = CInterfaceImpl::getInitance()->StartSwitchSingle(strId);

	return bRet;
}


SHORT CDRVideoRealCtrl::StopSwitchTemplate(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance 实例化失败 ");
		return -1;
	}

	bool bRet = CInterfaceImpl::getInitance()->StopSwitchTemplate();

	return bRet;
}


SHORT CDRVideoRealCtrl::SetScreenStyle(SHORT x, SHORT y, SHORT z)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance 实例化失败 ");
		return -1;
	}

	bool bRet = CInterfaceImpl::getInitance()->SetScreenStyle(x, y, z);

	return bRet;
}


SHORT CDRVideoRealCtrl::BrowseFolder(LPCTSTR strPath)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	if(strPath == NULL || strcmp(strPath,"") == 0)
	{
		strPath = m_curMoudlePath;
	}
	if (!PathIsDirectory(strPath))
	{
		LOG4CXX_DEBUG(CJsonParse::getInstance()->logger, "路径不存在");
		return -1;
	}
	::WinExec(("explorer.exe /e,/root, \"" + (CString)strPath + "\""), SW_SHOW);

	return 0;
}


SHORT CDRVideoRealCtrl::GetDownloadList(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	return 0;
}


SHORT CDRVideoRealCtrl::StartDownload(LPCTSTR strInfo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance 实例化失败 ");
		return -1;
	}

	bool bRet = CInterfaceImpl::getInitance()->StartDownload(strInfo);

	return bRet;
}


SHORT CDRVideoRealCtrl::StopDownload(SHORT fd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance 实例化失败 ");
		return -1;
	}

	bool bRet = CInterfaceImpl::getInitance()->StopDownload(fd);

	return bRet;
}


SHORT CDRVideoRealCtrl::SetRecordPlan(LPCTSTR strInfo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance 实例化失败 ");
		return -1;
	}

	bool bRet = CInterfaceImpl::getInitance()->SetRecordPlan(strInfo);

	return bRet;
}


SHORT CDRVideoRealCtrl::SetCapturePath(LPCTSTR strInfo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance 实例化失败 ");
		return -1;
	}

	bool bRet = CInterfaceImpl::getInitance()->SetCapturePath(strInfo);

	return bRet;
}


SHORT CDRVideoRealCtrl::StopAllVideo(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	for (int nLoop = 0; nLoop < MAX_CHILDWND; nLoop ++)
	{
		LOG4CXX_DEBUG(CJsonParse::getInstance()->logger, "m_pVideoReal[" << nLoop << "] = " << m_pVideoReal[nLoop]->m_played);
		if (NULL != m_pVideoReal[nLoop] && m_pVideoReal[nLoop]->m_played)
		{
			LOG4CXX_DEBUG(CJsonParse::getInstance()->logger, "m_pVideoReal[" << nLoop << "] = " << m_pVideoReal[nLoop]);
			m_pVideoReal[nLoop]->StopVideo();
		}
	}

	return 0;
}


SHORT CDRVideoRealCtrl::MoveNext(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance 实例化失败 ");
		return -1;
	}
	bool bRet = CInterfaceImpl::getInitance()->MoveNext();

	return bRet;
}


SHORT CDRVideoRealCtrl::SelectFolder(LPCTSTR strPath)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance 实例化失败 ");
		return -1;
	}

	bool bRet = CInterfaceImpl::getInitance()->SelectFolder();

	return bRet;
}


SHORT CDRVideoRealCtrl::SetDownloadPath(LPCTSTR strPath)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance 实例化失败 ");
		return -1;
	}

	bool bRet = CInterfaceImpl::getInitance()->SetDownloadPath(strPath);

	return bRet;
}


SHORT CDRVideoRealCtrl::GetVideoParam(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance 实例化失败 ");
		return -1;
	}

	CVideoReal *pVideoReal = NULL;

	bool bRet = false;
	if (m_mapVideoReal.Lookup(m_curWndIndex, pVideoReal))
	{
		if (NULL != pVideoReal && pVideoReal->m_played)
		{
			bRet = pVideoReal->GetVideoParam();
		}
	}

	return bRet;
}


SHORT CDRVideoRealCtrl::ReleaseRes(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance 实例化失败 ");
		return -1;
	}

	bool bRet = CInterfaceImpl::getInitance()->ReleaseRes();

	return bRet;
}


SHORT CDRVideoRealCtrl::PlaySoundFile(LPCTSTR strPath)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance 实例化失败 ");
		return -1;
	}

	bool bRet = CInterfaceImpl::getInitance()->PlaySoundFile(strPath);

	return bRet;
}


BSTR CDRVideoRealCtrl::GetCurCameraObjId(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	CONNECTINFO *pConnInfo = NULL;
	bool bRet = false;
	if (m_mapConnInfo.Lookup(m_curWndIndex, pConnInfo))
	{
		if (NULL != pConnInfo)
		{
			CString strResult;
			strResult.Format("%s", pConnInfo->objId);
			return strResult.AllocSysString();
		}
	}
	return NULL;
}


SHORT CDRVideoRealCtrl::SetActive(SHORT num)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance 实例化失败 ");
		return -1;
	}

	bool bRet = CInterfaceImpl::getInitance()->SetActive(num);

	return bRet;
}


SHORT CDRVideoRealCtrl::GetMonitorNum(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	short nCount = 0;

	for (int nLoop = 0; nLoop < MAX_CHILDWND; nLoop ++)
	{
		if (m_pVideoReal[nLoop]->m_played)
		{
			nCount++;
		}		
	}
	return nCount;
}


SHORT CDRVideoRealCtrl::SetAlarmOut(LPCTSTR strDevInfo, SHORT status)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance 实例化失败 ");
		return -1;
	}

	bool bRet = CInterfaceImpl::getInitance()->SetAlarmOut(strDevInfo, status);

	return bRet;
}


SHORT CDRVideoRealCtrl::GetDiskList(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance 实例化失败 ");
		return -1;
	}

	bool bRet = CInterfaceImpl::getInitance()->GetDiskList();

	return bRet;
}


SHORT CDRVideoRealCtrl::CallHardPlay(LPCTSTR strFileName, SHORT type)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance 实例化失败 ");
		return -1;
	}

	bool bRet = CInterfaceImpl::getInitance()->CallHardPlay(strFileName,type);

	return bRet;
}


void CDRVideoRealCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	COleControl::OnLButtonDown(nFlags, point);
}


int CDRVideoRealCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	CRect rect;
	GetWindowRect(&rect);

	for (int nLoop = 0; nLoop < MAX_CHILDWND; nLoop ++)
	{
		m_pVideoReal[nLoop] = new CVideoReal(this);
		m_pVideoReal[nLoop]->Create(IDD_DIALOG_VIDEO, this);
		
		m_pVideoReal[nLoop]->m_curIndex = nLoop;
		m_pVideoReal[nLoop]->m_rect     = rect;
		m_pVideoReal[nLoop]->ShowWindow(SW_SHOW);
		m_mapVideoReal.SetAt(nLoop, m_pVideoReal[nLoop]);
	}

	m_pVideoReal[0]->m_nWidth = rect.Width();
	m_pVideoReal[0]->m_nHight = rect.Height();
	m_pVideoReal[0]->MoveWindow(0,0,rect.Width(),rect.Height());
	m_pVideoReal[0]->ShowWindow(SW_SHOW);

	
	return 0;
}

SHORT CDRVideoRealCtrl::SplitScreen(SHORT num)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	int nSqrNum = 0;
	int nWidth  = 0;
	int nHight  = 0;
	
	if (num == 0) return -1;
	if (num % 2 == 0 || num % (int)sqrt((double)num) == 0 )
	{
		nSqrNum = (int)sqrt((double)num);
		for (int nLoop = 0; nLoop < MAX_CHILDWND; nLoop ++)
		{
			m_pVideoReal[nLoop]->ShowWindow(SW_HIDE);
		}

		CRect rect;

		GetWindowRect(&rect);

		nWidth = (rect.Width()- 4*(nSqrNum-1) )/ nSqrNum;
		nHight = (rect.Height()-4*(nSqrNum-1))/nSqrNum;

		for (int nLoop = 0; nLoop < num; nLoop ++)
		{
			m_pVideoReal[nLoop]->m_splitNum = num;
			m_pVideoReal[nLoop]->MoveWindow((nLoop % nSqrNum)*(nWidth + 4),(nLoop / nSqrNum)*(nHight + 4),nWidth,nHight,TRUE);
			m_pVideoReal[nLoop]->m_nWidth = nWidth;
			m_pVideoReal[nLoop]->m_nHight = nHight;
			

			m_pVideoReal[nLoop]->ShowWindow(SW_SHOW);
			m_pVideoReal[nLoop]->DrawBorder();
			
		}
	}
	else
	{
		nSqrNum = (num + 1) / 2;
		for (int nLoop = 0; nLoop < MAX_CHILDWND; nLoop ++)
		{
			m_pVideoReal[nLoop]->ShowWindow(SW_HIDE);
		}

		CRect rect;

		GetWindowRect(&rect);

		nWidth = (rect.Width()- 4*(nSqrNum-1) )/ nSqrNum;
		nHight = (rect.Height()-4*(nSqrNum-1))/nSqrNum;

		for (int nLoop = 0; nLoop < nSqrNum * nSqrNum; nLoop ++)
		{
			m_pVideoReal[nLoop]->m_splitNum = num;
			m_pVideoReal[nLoop]->MoveWindow((nLoop % nSqrNum)*(nWidth + 4),(nLoop / nSqrNum)*(nHight + 4),nWidth,nHight,TRUE);
			m_pVideoReal[nLoop]->m_nWidth = nWidth;
			m_pVideoReal[nLoop]->m_nHight = nHight;
			m_pVideoReal[nLoop]->ShowWindow(SW_SHOW);
			m_pVideoReal[nLoop]->DrawBorder();
		}

		//m_pVideoReal[1]->ShowWindow(SW_HIDE);
	//	m_pVideoReal[3]->ShowWindow(SW_HIDE);
	//	m_pVideoReal[4]->ShowWindow(SW_HIDE);
		for (int nLoop = 0; nLoop < (nSqrNum - 1) * (nSqrNum - 1); nLoop += nSqrNum)
		{
			for (int index = nLoop; index < nSqrNum + nLoop - 1; index ++)
			{
				m_pVideoReal[index]->ShowWindow(SW_HIDE);
			}
			
		}
		m_pVideoReal[0]->MoveWindow(0,0,nWidth * (nSqrNum - 1) + (nSqrNum - 2) * 4, nHight * (nSqrNum - 1) + (nSqrNum - 2) * 4,TRUE);
		m_pVideoReal[0]->ShowWindow(SW_SHOW);
		m_pVideoReal[0]->DrawBorder();
	}
	

	return 0;
}

DWORD WINAPI CDRVideoRealCtrl::ThreadProc(LPVOID lpParameter)
{
	CDRVideoRealCtrl *pRealCtrl = (CDRVideoRealCtrl*)lpParameter;

	HANDLE hEvent;
	BOOL res ;

	FILETIME preidleTime;
	FILETIME prekernelTime;
	FILETIME preuserTime;

	FILETIME idleTime;
	FILETIME kernelTime;
	FILETIME userTime;

	MEMORYSTATUS ms;

	res = GetSystemTimes( &idleTime, &kernelTime, &userTime );

	preidleTime = idleTime;
	prekernelTime = kernelTime;
	preuserTime = userTime ;

	hEvent = CreateEvent (NULL,FALSE,FALSE,NULL); // 初始值为 nonsignaled ，并且每次触发后自动设置为nonsignaled

	while (TRUE)
	{
		WaitForSingleObject( hEvent,1000 ); //等待500毫秒
		res = GetSystemTimes( &idleTime, &kernelTime, &userTime );

		int idle   = pRealCtrl->CompareFileTime( preidleTime,idleTime);
		int kernel = pRealCtrl->CompareFileTime( prekernelTime, kernelTime);
		int user   = pRealCtrl->CompareFileTime(preuserTime, userTime);

		int cpu = (kernel + user - idle) * 100 / (kernel+user);//（总的时间-空闲时间）/总的时间=占用cpu的时间就是使用率
		//int cpuidle = ( idle) *100/(kernel+user);
		
		::GlobalMemoryStatus(&ms); 
		preidleTime   = idleTime;
		prekernelTime = kernelTime;
		preuserTime   = userTime ;

		if (cpu > 0)
		{
			pRealCtrl->OnSysInfo(cpu, ms.dwMemoryLoad);
			LOG4CXX_DEBUG(CJsonParse::getInstance()->logger, "cpu = " << cpu << "memcpy = " << ms.dwMemoryLoad);
		}
		
	}

	return 0;
}

__int64 CDRVideoRealCtrl::CompareFileTime(FILETIME time1, FILETIME time2)
{
	LARGE_INTEGER la, lb;
	la.LowPart = time1.dwLowDateTime;
	la.HighPart = time1.dwHighDateTime;
	lb.LowPart = time2.dwLowDateTime;
	lb.HighPart = time2.dwHighDateTime;

	return la.QuadPart - lb.QuadPart;
}