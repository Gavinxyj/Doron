// DriverAdaptorPlatfromCtrl.cpp : CDriverAdaptorPlatfromCtrl ActiveX 控件类的实现。

#include "stdafx.h"
#include "DriverAdaptorPlatfrom.h"
#include "DriverAdaptorPlatfromCtrl.h"
#include "DriverAdaptorPlatfromPropPage.h"
#include "afxdialogex.h"
#include "../8600VISION/Hk8600InterfaceImpl.h"
#include "JavaScriptStringParam.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CDriverAdaptorPlatfromCtrl, COleControl)



// 消息映射

BEGIN_MESSAGE_MAP(CDriverAdaptorPlatfromCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_CREATE()
END_MESSAGE_MAP()


BEGIN_INTERFACE_MAP(  CDriverAdaptorPlatfromCtrl, COleControl )
	INTERFACE_PART( CDriverAdaptorPlatfromCtrl, IID_IObjectSafety, ObjSafe)
END_INTERFACE_MAP()
// 调度映射

BEGIN_DISPATCH_MAP(CDriverAdaptorPlatfromCtrl, COleControl)
	DISP_FUNCTION_ID(CDriverAdaptorPlatfromCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_PROPERTY_EX_ID(CDriverAdaptorPlatfromCtrl, "windowId", dispidwindowId, GetwindowId, SetwindowId, VT_I2)
	DISP_FUNCTION_ID(CDriverAdaptorPlatfromCtrl, "OpenConnection", dispidOpenConnection, OpenConnection, VT_I2, VTS_BSTR VTS_UI4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CDriverAdaptorPlatfromCtrl, "StartRealPlay", dispidStartRealPlay, StartRealPlay, VT_I2, VTS_BSTR)
	DISP_FUNCTION_ID(CDriverAdaptorPlatfromCtrl, "StopRealPlay", dispidStopRealPlay, StopRealPlay, VT_I2, VTS_BSTR)
	DISP_FUNCTION_ID(CDriverAdaptorPlatfromCtrl, "CloseConnection", dispidCloseConntecion, CloseConnection, VT_I2, VTS_BSTR)
	DISP_FUNCTION_ID(CDriverAdaptorPlatfromCtrl, "CloudPatControl", dispidCloudPatControl, CloudPatControl, VT_I2, VTS_UI4 VTS_I2 VTS_I2 VTS_BSTR)
	DISP_FUNCTION_ID(CDriverAdaptorPlatfromCtrl, "StartRecord", dispidStartRecord, StartRecord, VT_I2, VTS_BSTR VTS_UI4 VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CDriverAdaptorPlatfromCtrl, "StopRecord", dispidStopRecord, StopRecord, VT_I2, VTS_UI4 VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CDriverAdaptorPlatfromCtrl, "PlayBack", dispidPlayBack, PlayBack, VT_I2, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CDriverAdaptorPlatfromCtrl, "StopPlayBack", dispidStopPlayBack, StopPlayBack, VT_I2, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CDriverAdaptorPlatfromCtrl, "CapturePicture", dispidCapturePicture, CapturePicture, VT_I2, VTS_BSTR VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CDriverAdaptorPlatfromCtrl, "splitScreen", dispidsplitScreen, splitScreen, VT_I2, VTS_I2)
	DISP_FUNCTION_ID(CDriverAdaptorPlatfromCtrl, "Preset", dispidPreset, Preset, VT_I2, VTS_I2 VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CDriverAdaptorPlatfromCtrl, "CallPreset", dispidCallPreset, CallPreset, VT_I2, VTS_I2 VTS_BSTR VTS_BSTR)
	DISP_PROPERTY_EX_ID(CDriverAdaptorPlatfromCtrl, "IPAddress", dispidIPAddress, GetIPAddress, SetIPAddress, VT_BSTR)
END_DISPATCH_MAP()



// 事件映射

BEGIN_EVENT_MAP(CDriverAdaptorPlatfromCtrl, COleControl)
	EVENT_CUSTOM_ID("IPADDRESS", eventidIPADDRESS, IPADDRESS, VTS_BSTR)
END_EVENT_MAP()



// 属性页

// TODO: 按需要添加更多属性页。请记住增加计数!
BEGIN_PROPPAGEIDS(CDriverAdaptorPlatfromCtrl, 1)
	PROPPAGEID(CDriverAdaptorPlatfromPropPage::guid)
END_PROPPAGEIDS(CDriverAdaptorPlatfromCtrl)



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CDriverAdaptorPlatfromCtrl, "DRIVERADAPTORPLA.DriverAdaptorPlaCtrl.1",
	0x3a6b1f54, 0xbfb, 0x4ed1, 0x95, 0x4, 0xb6, 0x19, 0x10, 0x33, 0x8b, 0xae)



// 键入库 ID 和版本

IMPLEMENT_OLETYPELIB(CDriverAdaptorPlatfromCtrl, _tlid, _wVerMajor, _wVerMinor)



// 接口 ID

const IID IID_DDriverAdaptorPlatfrom = { 0x9BC3145A, 0x8744, 0x4ADC, { 0xBB, 0x2F, 0x2, 0x89, 0x1, 0x70, 0x6D, 0xAC } };
const IID IID_DDriverAdaptorPlatfromEvents = { 0x48EF2238, 0x1E11, 0x4157, { 0x81, 0x28, 0x1E, 0x26, 0xB3, 0x3B, 0xD1, 0xB4 } };


// 控件类型信息

static const DWORD _dwDriverAdaptorPlatfromOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CDriverAdaptorPlatfromCtrl, IDS_DRIVERADAPTORPLATFROM, _dwDriverAdaptorPlatfromOleMisc)


	ULONG FAR EXPORT  CDriverAdaptorPlatfromCtrl::XObjSafe::AddRef()
{
	METHOD_PROLOGUE( CDriverAdaptorPlatfromCtrl, ObjSafe);
	return pThis->ExternalAddRef();
}


ULONG FAR EXPORT  CDriverAdaptorPlatfromCtrl::XObjSafe::Release()
{
	METHOD_PROLOGUE( CDriverAdaptorPlatfromCtrl, ObjSafe);
	return pThis->ExternalRelease();
}


HRESULT FAR EXPORT  CDriverAdaptorPlatfromCtrl::XObjSafe::QueryInterface(
	REFIID iid, void FAR* FAR* ppvObj)
{
	METHOD_PROLOGUE( CDriverAdaptorPlatfromCtrl, ObjSafe);
	return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);
}


const DWORD dwSupportedBits = INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA;

const DWORD dwNotSupportedBits = ~dwSupportedBits;


//.............................................................................

// CStopLiteCtrl::XObjSafe::GetInterfaceSafetyOptions

// Allows Container to query what interfaces are safe for what. We're

// optimizing significantly by ignoring which interface the caller is

// asking for.


HRESULT STDMETHODCALLTYPE

	CDriverAdaptorPlatfromCtrl::XObjSafe::GetInterfaceSafetyOptions(

	REFIID riid,

	DWORD __RPC_FAR *pdwSupportedOptions,

	DWORD __RPC_FAR *pdwEnabledOptions)

{

	METHOD_PROLOGUE( CDriverAdaptorPlatfromCtrl, ObjSafe);

	HRESULT retval = ResultFromScode(S_OK);

	// does interface exist?

	IUnknown FAR* punkInterface;

	retval = pThis->ExternalQueryInterface(&riid,

		(void * *)&punkInterface);

	if (retval != E_NOINTERFACE) { // interface exists

		punkInterface->Release(); // release it--just checking!

	}


	// we support both kinds of safety and have always both set,

	// regardless of interface

	*pdwSupportedOptions = *pdwEnabledOptions = dwSupportedBits;

	return retval; // E_NOINTERFACE if QI failed

}


/////////////////////////////////////////////////////////////////////////////

// CStopLiteCtrl::XObjSafe::SetInterfaceSafetyOptions

// Since we're always safe, this is a no-brainer--but we do check to make

// sure the interface requested exists and that the options we're asked to

// set exist and are set on (we don't support unsafe mode).


HRESULT STDMETHODCALLTYPE

	CDriverAdaptorPlatfromCtrl::XObjSafe::SetInterfaceSafetyOptions(

	REFIID riid,

	DWORD dwOptionSetMask,

	DWORD dwEnabledOptions)

{

	METHOD_PROLOGUE( CDriverAdaptorPlatfromCtrl, ObjSafe);

	// does interface exist?

	IUnknown FAR* punkInterface;

	pThis->ExternalQueryInterface(&riid, (void * *)&punkInterface);

	if (punkInterface) { // interface exists
		punkInterface->Release(); // release it--just checking!
	}


	else { // interface doesn't exist
		return ResultFromScode(E_NOINTERFACE);
	}


	// can't set bits we don't support
	if (dwOptionSetMask & dwNotSupportedBits) {
		return ResultFromScode(E_FAIL);
	}


	// can't set bits we do support to zero
	dwEnabledOptions &= dwSupportedBits;


	// (we already know there are no extra bits in mask )
	if ((dwOptionSetMask & dwEnabledOptions) !=    dwOptionSetMask) {
		return ResultFromScode(E_FAIL);
	}       


	// don't need to change anything since we're always safe
	return ResultFromScode(S_OK);
}

// CDriverAdaptorPlatfromCtrl::CDriverAdaptorPlatfromCtrlFactory::UpdateRegistry -
// 添加或移除 CDriverAdaptorPlatfromCtrl 的系统注册表项

BOOL CDriverAdaptorPlatfromCtrl::CDriverAdaptorPlatfromCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_DRIVERADAPTORPLATFROM,
			IDB_DRIVERADAPTORPLATFROM,
			afxRegApartmentThreading,
			_dwDriverAdaptorPlatfromOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CDriverAdaptorPlatfromCtrl::CDriverAdaptorPlatfromCtrl - 构造函数

CDriverAdaptorPlatfromCtrl::CDriverAdaptorPlatfromCtrl()
{
	InitializeIIDs(&IID_DDriverAdaptorPlatfrom, &IID_DDriverAdaptorPlatfromEvents);
	// TODO: 在此初始化控件的实例数据。
	m_mapFactory.RemoveAll();

	m_curWndIndex = 0;
	m_windowId = 0;

	char szPath[256] = {0};

	DWORD dwCode = GetCurrentDirectory(sizeof(szPath), szPath);
	
	HMODULE hModule = GetModuleHandle("DriverAdaptorPlatfrom.ocx");


	
	if (hModule != NULL)
	{
		GetModuleFileName(hModule,szPath, sizeof(szPath));
	}
	CString strTemp;
	strTemp.Format("%s",szPath);

	CString strPath;
	strPath.Format("%s\\config\\config.properties", strTemp.Left(strTemp.ReverseFind('\\')));

	//MessageBox(strPath);
	PropertyConfigurator::configure("C:\\DriverAdaptor\\config.properties");

	logger = Logger::getLogger("debugLogger");

	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);
}



// CDriverAdaptorPlatfromCtrl::~CDriverAdaptorPlatfromCtrl - 析构函数

CDriverAdaptorPlatfromCtrl::~CDriverAdaptorPlatfromCtrl()
{
	// TODO: 在此清理控件的实例数据。
	LOG4CXX_INFO(logger,"~CDriverAdaptorPlatfromCtrl start");
	CString strKey = _T("");
	PARAMS *pDriverAdaptorPat = NULL;
	LOG4CXX_INFO(logger,"mapCount = " << m_mapFactory.GetCount());
	POSITION pos = m_mapFactory.GetStartPosition(); 
	while(pos) 
	{ 
		m_mapFactory.GetNextAssoc(pos,strKey,pDriverAdaptorPat);
		LOG4CXX_INFO(logger,"pDriverAdaptorPat = " << pDriverAdaptorPat);
		if ( NULL != pDriverAdaptorPat)
		{
			pDriverAdaptorPat->pDriverAdaptorPat->StopRealPlay();
			delete pDriverAdaptorPat;
			pDriverAdaptorPat = NULL;
		}
	} 
	m_mapFactory.RemoveAll();

	for (int nLoop = 0; nLoop < MAX_CHILDWND; nLoop ++)
	{
		if (NULL != m_pDlgOutPut[nLoop])
		{
			delete m_pDlgOutPut[nLoop];
			m_pDlgOutPut[nLoop] = NULL;
		}		
	}
	Gdiplus::GdiplusShutdown(m_gdiplusToken);
	LOG4CXX_INFO(logger,"~CDriverAdaptorPlatfromCtrl end");
}



// CDriverAdaptorPlatfromCtrl::OnDraw - 绘图函数

void CDriverAdaptorPlatfromCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: 用您自己的绘图代码替换下面的代码。
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Rectangle(rcBounds);
}



// CDriverAdaptorPlatfromCtrl::DoPropExchange - 持久性支持

void CDriverAdaptorPlatfromCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: 为每个持久的自定义属性调用 PX_ 函数。
}



// CDriverAdaptorPlatfromCtrl::OnResetState - 将控件重置为默认状态

void CDriverAdaptorPlatfromCtrl::OnResetState()
{
	COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值

	// TODO: 在此重置任意其他控件状态。
}



// CDriverAdaptorPlatfromCtrl::AboutBox - 向用户显示“关于”框

void CDriverAdaptorPlatfromCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_DRIVERADAPTORPLATFROM);
	dlgAbout.DoModal();
}



// CDriverAdaptorPlatfromCtrl 消息处理程序


SHORT CDriverAdaptorPlatfromCtrl::GetwindowId(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	return m_windowId;
}


void CDriverAdaptorPlatfromCtrl::SetwindowId(SHORT newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	m_windowId = newVal;
	SetModifiedFlag();
}

SHORT CDriverAdaptorPlatfromCtrl::OpenConnection(LPCTSTR strIp, ULONG dwPort, LPCTSTR userName, LPCTSTR password, LPCTSTR DeviceType, LPCTSTR params)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	
	
	if ( NULL == params ) return FALSE;
	
	CStringArray strarrParams;	
	CJavaScriptStringParam::GetStringParams(params,"|",strarrParams);
	
	CString windowId = "0";
	CJavaScriptStringParam::GetStringParam(strarrParams,"windowId", windowId);

	CString cameraId = "0";
	CJavaScriptStringParam::GetStringParam(strarrParams,"cameraId", cameraId);

	LOG4CXX_INFO(logger,"windowId = " << windowId << "cameraId = " << cameraId);
	BOOL bRet = FALSE;
	PARAMS *pParams = NULL;
	IDriverAdaptorPlatfrom *pDriverAdaptorPat = NULL;
	
	if (strcmp(DeviceType,(const char*)"DH") == 0)
	{
		LOG4CXX_INFO(logger,"DH")
	//	pDriverAdaptorPat = new CDhInterfaceImpl();
		
	}
	else if (strcmp(DeviceType,(const char*)"HK") == 0)
	{
	//	pDriverAdaptorPat = new CHkInterfaceImpl();
		LOG4CXX_INFO(logger,"HK")
	}
	else if (strcmp(DeviceType,(const char*)"HK8600") == 0)
	{
		pDriverAdaptorPat = new CHk8600InterfaceImpl(this);
		LOG4CXX_INFO(logger,"HK8600")
	}

	if ( NULL != pDriverAdaptorPat)
	{
		if (!m_mapFactory.Lookup(windowId,pParams))
		{
			//m_pDriverAdaptorPat = new CHkInterfaceImpl(&m_pDlgOutPut[0]->m_static,this);	
			pParams = new PARAMS;
			strcpy(pParams->chIp,(char*)strIp);
			strcpy(pParams->deviceType, DeviceType);
			pParams->nWindowId = atoi(windowId);
			pParams->ncameraId = atoi(cameraId);
			pParams->pDriverAdaptorPat = pDriverAdaptorPat;
			
			for (int nLoop = 0; nLoop < 3; nLoop ++)
			{
				bRet = pDriverAdaptorPat->OpenConnection(strIp,dwPort,userName,password);

				if (bRet) break;
				
			}
			
			if (!bRet)
			{
				delete pParams;
				pParams = NULL;
			}
			else
			{
				m_mapFactory.SetAt(windowId,pParams);
			}

			LOG4CXX_INFO(logger,"连接"<<DeviceType<<"视频;"<<"IP地址:"<<pParams->chIp<<";端口号:"<<dwPort<<"mapCount = "<<m_mapFactory.GetCount());
			
		}
		else
		{
			/************************************************************************/
			/* 这里的考虑是因为当窗口ID作为key，前端多次调用OpenConnection方法在同一窗口ID上播放，
			   但是链接的设备不同，所以要做下面的判断，若设备不同选释放是上一次的资源，在重新实例化一次*/
			/************************************************************************/
			if (strcmp(pParams->chIp, strIp) != 0)
			{
				LOG4CXX_INFO(logger,"pParams->chIp"<< pParams->chIp << "strIp = " << strIp);
				if ( NULL != pParams)
				{
					delete pParams;
					pParams = NULL;
				}
				
				pParams = new PARAMS;
				strcpy(pParams->chIp,(char*)strIp);
				strcpy(pParams->deviceType, DeviceType);
				pParams->nWindowId = atoi(windowId);
				pParams->pDriverAdaptorPat = pDriverAdaptorPat;


				for (int nLoop = 0; nLoop < 3; nLoop ++)
				{
					bRet = pDriverAdaptorPat->OpenConnection(strIp,dwPort,userName,password);

					if (bRet) break;

				}

				if (!bRet)
				{
					delete pParams;
					pParams = NULL;
				}
				else
				{
					m_mapFactory.SetAt(windowId,pParams);
					LOG4CXX_INFO(logger,"连接"<<DeviceType<<"视频;"<<"IP地址:"<<strIp<<";端口号:"<<dwPort<<"mapCount = "<<m_mapFactory.GetCount());
				}
			}
			else
			{
				this->StartRealPlay(params);
			}
			
		}
		
	}
	return bRet;
}

/************************************************************************/
/* 函数名：  StartRealPlay 
/* 函数描述：开始实时预览
/* 输入参数：params:key = value字符串类型的参数数，如"windowId = 1"
   返回值：  TRUE-成功 FALSE-失败
/************************************************************************/
SHORT CDriverAdaptorPlatfromCtrl::StartRealPlay(LPCTSTR params)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	CStringArray strarrParams;
	CJavaScriptStringParam::GetStringParams(params,"|",strarrParams);

	CString windowId = "0";
	CJavaScriptStringParam::GetStringParam(strarrParams,"windowId", windowId);

	CString cameraId = "0";
	CJavaScriptStringParam::GetStringParam(strarrParams,"cameraId", cameraId);
	BOOL bRet = FALSE;
	PARAMS *pParams = NULL;
	
	if (m_mapFactory.Lookup(windowId,pParams))
	{
		
		bRet = pParams->pDriverAdaptorPat->StartRealPlay(&m_pDlgOutPut[atoi(windowId)]->m_static, cameraId);
		
		/*if (bRet)
		{
			m_pDlgOutPut[atoi(windowId)]->m_captureImage.ShowWindow(SW_SHOW);
			m_pDlgOutPut[atoi(windowId)]->m_recodeBtn.ShowWindow(SW_SHOW);
			m_pDlgOutPut[atoi(windowId)]->m_cloudBtn.ShowWindow(SW_SHOW);
			m_pDlgOutPut[atoi(windowId)]->m_voiceSound.ShowWindow(SW_SHOW);
			m_pDlgOutPut[atoi(windowId)]->m_digitalZoom.ShowWindow(SW_SHOW);
			m_pDlgOutPut[atoi(windowId)]->m_playBackBtn.ShowWindow(SW_SHOW);
			m_pDlgOutPut[atoi(windowId)]->m_closeBtn.ShowWindow(SW_SHOW);
		}*/
	}
	return bRet;
}


SHORT CDriverAdaptorPlatfromCtrl::StopRealPlay(LPCTSTR params)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	if ( NULL == params) return -1;
	
	CStringArray strarrParams;
	CJavaScriptStringParam::GetStringParams(params,";",strarrParams);

	CString windowId = "0";
	CJavaScriptStringParam::GetStringParam(strarrParams,"windowId", windowId);
	
	BOOL bRet = FALSE;
	PARAMS *pParams = NULL;
	if (m_mapFactory.Lookup(windowId,pParams))
	{
		bRet = pParams->pDriverAdaptorPat->StopRealPlay();
		/*if(bRet)
		{
			m_pDlgOutPut[atoi(windowId)]->m_captureImage.ShowWindow(SW_HIDE);
			m_pDlgOutPut[atoi(windowId)]->m_recodeBtn.ShowWindow(SW_HIDE);
			m_pDlgOutPut[atoi(windowId)]->m_cloudBtn.ShowWindow(SW_HIDE);
			m_pDlgOutPut[atoi(windowId)]->m_voiceSound.ShowWindow(SW_HIDE);
			m_pDlgOutPut[atoi(windowId)]->m_digitalZoom.ShowWindow(SW_HIDE);
			m_pDlgOutPut[atoi(windowId)]->m_playBackBtn.ShowWindow(SW_HIDE);
			m_pDlgOutPut[atoi(windowId)]->m_closeBtn.ShowWindow(SW_HIDE);
		}*/
	}
	return bRet;
}


SHORT CDriverAdaptorPlatfromCtrl::CloseConnection(LPCTSTR params)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	if ( NULL == params) return -1;

	CStringArray strarrParams;
	CJavaScriptStringParam::GetStringParams(params,"|",strarrParams);

	CString windowId = "0";
	CJavaScriptStringParam::GetStringParam(strarrParams,"windowId", windowId);

	BOOL bRet = FALSE;
	PARAMS *pParams = NULL;
	if (m_mapFactory.Lookup(windowId,pParams))
	{
		bRet = pParams->pDriverAdaptorPat->CloseConnection();
		
		if (bRet)
		{
			m_mapFactory.RemoveKey(windowId);
		}
		/*if (bRet)
		{
			m_pDlgOutPut[atoi(windowId)]->m_captureImage.ShowWindow(SW_HIDE);
			m_pDlgOutPut[atoi(windowId)]->m_recodeBtn.ShowWindow(SW_HIDE);
			m_pDlgOutPut[atoi(windowId)]->m_cloudBtn.ShowWindow(SW_HIDE);
			m_pDlgOutPut[atoi(windowId)]->m_voiceSound.ShowWindow(SW_HIDE);
			m_pDlgOutPut[atoi(windowId)]->m_digitalZoom.ShowWindow(SW_HIDE);
			m_pDlgOutPut[atoi(windowId)]->m_playBackBtn.ShowWindow(SW_HIDE);
			m_pDlgOutPut[atoi(windowId)]->m_closeBtn.ShowWindow(SW_HIDE);
			
		}*/
	}
	return bRet;
}


SHORT CDriverAdaptorPlatfromCtrl::CloudPatControl(ULONG dwCommand, SHORT startEndFlag, SHORT speed, LPCTSTR params)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	if ( NULL == params) return -1;

	CStringArray strarrParams;
	CJavaScriptStringParam::GetStringParams(params,";",strarrParams);

	CString windowId = "0";
	CJavaScriptStringParam::GetStringParam(strarrParams,"windowId", windowId);
	BOOL bRet = FALSE;
	PARAMS *pParams = NULL;

	if (m_mapFactory.Lookup(windowId,pParams))
	{
		bRet = pParams->pDriverAdaptorPat->CloudPatControl(dwCommand,startEndFlag,speed);
	}
	return bRet;
}


SHORT CDriverAdaptorPlatfromCtrl::StartRecord(LPCTSTR filePath, ULONG dwChannelId, LPCTSTR DeviceType, LPCTSTR params)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	BOOL bRet = FALSE;
	PARAMS *pParams = NULL;

	if (m_mapFactory.Lookup((CString)DeviceType,pParams))
	{
		bRet = pParams->pDriverAdaptorPat->StartRecord(filePath,dwChannelId);
	}
	return bRet;
}


SHORT CDriverAdaptorPlatfromCtrl::StopRecord(ULONG dwChannelId, LPCTSTR DeviceType, LPCTSTR params)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	BOOL bRet = FALSE;
	PARAMS *pParams = NULL;
	if (m_mapFactory.Lookup((CString)DeviceType,pParams))
	{
		bRet = pParams->pDriverAdaptorPat->StopRecord();
	}
	return bRet;
}


SHORT CDriverAdaptorPlatfromCtrl::PlayBack(LPCTSTR fileName, LPCTSTR DeviceType, LPCTSTR params)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	BOOL bRet = FALSE;
	PARAMS *pParams = NULL;

	if (m_mapFactory.Lookup((CString)DeviceType,pParams))
	{
		bRet = pParams->pDriverAdaptorPat->PlayBack(fileName);
	}
	return bRet;
}


SHORT CDriverAdaptorPlatfromCtrl::StopPlayBack(LPCTSTR DeviceType, LPCTSTR params)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	BOOL bRet = FALSE;
	PARAMS *pParams = NULL;

	if (m_mapFactory.Lookup((CString)DeviceType,pParams))
	{
		bRet = pParams->pDriverAdaptorPat->StopPlayBack();
	}
	return bRet;
}



SHORT CDriverAdaptorPlatfromCtrl::CapturePicture(LPCTSTR filePath, SHORT imageType, SHORT imageSize, SHORT imageQuality, SHORT dwChannelId, LPCTSTR DeviceType, LPCTSTR params)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	BOOL bRet = FALSE;
	PARAMS *pParams = NULL;

	if (m_mapFactory.Lookup((CString)DeviceType,pParams))
	{
		bRet = pParams->pDriverAdaptorPat->CapturePicture(filePath,imageType,imageSize,imageQuality,dwChannelId);
	}
	return bRet;
}


SHORT CDriverAdaptorPlatfromCtrl::splitScreen(SHORT dwScreenNum)
{
	int nSqrNum = 0;
	int nWidth  = 0;
	int nHight  = 0;

	nSqrNum = (int)sqrt((double)dwScreenNum);

	for (int nLoop = 0; nLoop < MAX_CHILDWND; nLoop ++)
	{
		m_pDlgOutPut[nLoop]->ShowWindow(SW_HIDE);
	}

	CRect rect;

	GetWindowRect(&rect);

	nWidth = (rect.Width()- 4*(nSqrNum-1) )/ nSqrNum;
	nHight = (rect.Height()-4*(nSqrNum-1))/nSqrNum;

	for (int nLoop = 0; nLoop < dwScreenNum; nLoop ++)
	{
		m_pDlgOutPut[nLoop]->m_splitNum = dwScreenNum;
		m_pDlgOutPut[nLoop]->MoveWindow((nLoop % nSqrNum)*(nWidth + 4),(nLoop / nSqrNum)*(nHight + 4),nWidth,nHight,TRUE);
		m_pDlgOutPut[nLoop]->m_nWidth = nWidth;
		m_pDlgOutPut[nLoop]->m_nHight = nHight;
		m_pDlgOutPut[nLoop]->m_static.MoveWindow(0,0,nWidth,nHight);
		/*if (nWidth < 200)
		{
			m_pDlgOutPut[nLoop]->m_recodeBtn.MoveWindow(0,5,20,20);
			m_pDlgOutPut[nLoop]->m_captureImage.MoveWindow((nWidth/ 7) * 1,5,20,20);
			m_pDlgOutPut[nLoop]->m_cloudBtn.MoveWindow((nWidth/ 7) * 2,5,20,20);
			m_pDlgOutPut[nLoop]->m_voiceSound.MoveWindow((nWidth/ 7) * 3,5, 20,20);
			m_pDlgOutPut[nLoop]->m_digitalZoom.MoveWindow((nWidth/ 7) * 4,5, 20,20);
			m_pDlgOutPut[nLoop]->m_playBackBtn.MoveWindow((nWidth/ 7) * 5,5, 20,20);
			m_pDlgOutPut[nLoop]->m_closeBtn.MoveWindow((nWidth/ 7) * 6,5, 20,20);
		}
		else
		{
			m_pDlgOutPut[nLoop]->m_recodeBtn.MoveWindow(nWidth/2,5,20,20);
			m_pDlgOutPut[nLoop]->m_captureImage.MoveWindow(nWidth/2 + (nWidth/ 14) * 1,5,20,20);
			m_pDlgOutPut[nLoop]->m_cloudBtn.MoveWindow(nWidth/2 + (nWidth/ 14) * 2,5,20,20);
			m_pDlgOutPut[nLoop]->m_voiceSound.MoveWindow(nWidth / 2 + (nWidth/ 14) * 3,5, 20,20);
			m_pDlgOutPut[nLoop]->m_digitalZoom.MoveWindow(nWidth / 2 + (nWidth/ 14) * 4,5, 20,20);
			m_pDlgOutPut[nLoop]->m_playBackBtn.MoveWindow(nWidth / 2 + (nWidth/ 14) * 5,5, 20,20);
			m_pDlgOutPut[nLoop]->m_closeBtn.MoveWindow(nWidth / 2 + (nWidth/ 14) * 6,5, 20,20);
		}
		m_pDlgOutPut[nLoop]->m_cloudLeftUp.MoveWindow(0,0,32,32);
		m_pDlgOutPut[nLoop]->m_cloudRightUp.MoveWindow(nWidth - 32,0,nWidth,32);
		m_pDlgOutPut[nLoop]->m_cloudLeftDown.MoveWindow(0,nHight - 32 - 25, 32,nHight);
		m_pDlgOutPut[nLoop]->m_cloudRightDown.MoveWindow(nWidth - 32,nHight - 32 - 25, nWidth,nHight);
		m_pDlgOutPut[nLoop]->m_cloudUp.MoveWindow(nWidth / 2 - 16,0,32,32);
		m_pDlgOutPut[nLoop]->m_cloudDown.MoveWindow(nWidth / 2 - 16,nHight - 32 - 25,32,nHight);
		m_pDlgOutPut[nLoop]->m_cloudLeft.MoveWindow(0,(nHight - 25) / 2 - 16, 32,32);
		m_pDlgOutPut[nLoop]->m_cloudRight.MoveWindow(nWidth - 32, (nHight - 25) / 2 - 16,nWidth, 32);*/
		m_pDlgOutPut[nLoop]->ShowWindow(SW_SHOW);
		m_pDlgOutPut[nLoop]->DrawBorder();
	}
	return 0;
}

SHORT CDriverAdaptorPlatfromCtrl::Preset(SHORT dwPoint, LPCTSTR DeviceType, LPCTSTR params)
{
	return 0;
}
SHORT CDriverAdaptorPlatfromCtrl::CallPreset(SHORT dwPoint, LPCTSTR DeviceType, LPCTSTR params)
{
	BOOL bRet = FALSE;
	PARAMS *pParams = NULL;

	if (m_mapFactory.Lookup((CString)DeviceType,pParams))
	{
		bRet = pParams->pDriverAdaptorPat->CallPreset(dwPoint);
	}
	return bRet;
}


int CDriverAdaptorPlatfromCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;	
	// TODO:  在此添加您专用的创建代码
	CRect rect;
	GetWindowRect(&rect);
	//CString strTemp1 = "";
	//strTemp1.Format("x = %d, y = %d, bx = %d, by = %d", rect.left,rect.top, rect.bottom,rect.right);
	//MessageBox(strTemp1);
	for (int nLoop = 0; nLoop < MAX_CHILDWND; nLoop ++)
	{	
		m_pDlgOutPut[nLoop] = new CDlgOutput(this);	
		m_pDlgOutPut[nLoop]->Create(IDD_DIALOG_OUTPUT,this);
		m_pDlgOutPut[nLoop]->m_rect = rect;
		//	m_pDlgOutPut[nLoop]->m_nHight = rect.Height();
		//	LPCSTR name = AfxRegisterWndClass(NULL);
		//	char *czName =(LPSTR )name;
		//	BOOL bRet = m_pDlgOutPut[nLoop]->CreateEx(WS_CLIPCHILDREN, AfxRegisterWndClass(NULL),"view",WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,CRect(0,0,0,0),this,IDD_DIALOG_OUTPUT);
		m_pDlgOutPut[nLoop]->m_curIndex = nLoop;
		m_pDlgOutPut[nLoop]->ShowWindow(SW_HIDE);
	}

	CString strTemp;

	m_pDlgOutPut[0]->m_nWidth = rect.Width();
	m_pDlgOutPut[0]->m_nHight = rect.Height();
	m_pDlgOutPut[0]->MoveWindow(0,0,rect.Width(),rect.Height());
	m_pDlgOutPut[0]->m_static.MoveWindow(0,0,rect.Width(),rect.Height());
	/*m_pDlgOutPut[0]->m_recodeBtn.MoveWindow(10,30,20,20);
	m_pDlgOutPut[0]->m_cloudLeftUp.MoveWindow(0,0,32,32);
	m_pDlgOutPut[0]->m_cloudRightUp.MoveWindow(rect.Width() - 32,0,rect.Width(),32);
	m_pDlgOutPut[0]->m_cloudLeftDown.MoveWindow(0,rect.Height() - 32 - 25, 32,rect.Height());
	m_pDlgOutPut[0]->m_cloudRightDown.MoveWindow(rect.Width() - 32,rect.Height() - 32 - 25, rect.Width(),rect.Height());
	m_pDlgOutPut[0]->m_cloudUp.MoveWindow(rect.Width() / 2 - 16,0,32,32);
	m_pDlgOutPut[0]->m_cloudDown.MoveWindow(rect.Width() / 2 - 16,rect.Height() - 32 - 25,32,rect.Height());
	m_pDlgOutPut[0]->m_cloudLeft.MoveWindow(0,(rect.Height() - 25) / 2 - 16, 32,32);
	m_pDlgOutPut[0]->m_cloudRight.MoveWindow(rect.Width() - 32, (rect.Height() - 25) / 2 - 16,rect.Width(), 32);
	m_pDlgOutPut[0]->m_recodeBtn.MoveWindow(rect.Width()/2,5,20,20);
	m_pDlgOutPut[0]->m_captureImage.MoveWindow(rect.Width()/2 + (rect.Width()/ 14) * 1,5,20,20);
	m_pDlgOutPut[0]->m_cloudBtn.MoveWindow(rect.Width()/2 + (rect.Width()/ 14) * 2,5,20,20);
	m_pDlgOutPut[0]->m_voiceSound.MoveWindow(rect.Width() / 2 + (rect.Width()/ 14) * 3,5, 20,20);
	m_pDlgOutPut[0]->m_digitalZoom.MoveWindow(rect.Width() / 2 + (rect.Width()/ 14) * 4,5, 20,20);
	m_pDlgOutPut[0]->m_playBackBtn.MoveWindow(rect.Width() / 2 + (rect.Width()/ 14) * 5,5, 20,20);
	m_pDlgOutPut[0]->m_closeBtn.MoveWindow(rect.Width() / 2 + (rect.Width()/ 14) * 6,5, 20,20);
	*/
	m_pDlgOutPut[0]->ShowWindow(SW_SHOW);
	m_pDlgOutPut[0]->DrawBorder();
	return 0;
}


BSTR CDriverAdaptorPlatfromCtrl::GetIPAddress(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	return m_strIpAddr.AllocSysString();
}


void CDriverAdaptorPlatfromCtrl::SetIPAddress(LPCTSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	m_strIpAddr = newVal;
	SetModifiedFlag();
}

bool CDriverAdaptorPlatfromCtrl::InitSocket()
{
	WSADATA wsdata;

	int nRet = WSAStartup(MAKEWORD(2,2), &wsdata);

	if (0 != nRet)
	{
		DWORD dwErr = WSAGetLastError();
		LOG4CXX_INFO(logger,"InitSocket errCode:"<<dwErr);
		return false;
	}

	SOCKET socketTemp = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

	SOCKADDR_IN serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port   = htons(21);
	serverAddr.sin_addr.S_un.S_addr = inet_addr("192.168.102.153");

	nRet = connect(socketTemp, (SOCKADDR *)&serverAddr, sizeof(serverAddr));

	if (SOCKET_ERROR == nRet)
	{
		DWORD dwErr = WSAGetLastError();
		LOG4CXX_INFO(logger,"InitSocket errCode:"<<dwErr);
		closesocket(socketTemp);
		return false;
	}

	setTimeout(socketTemp, true, 10000);

	char recvBuf[1024] = {0};
	
	ftpRecv(socketTemp, recvBuf, 1024);

	if (recvBuf[0] != '2')
	{
		LOG4CXX_INFO(logger,"InitSocket errCode:"<<recvBuf);
		closesocket(socketTemp);
		return false;
	}

	//发送登录命令
	char command[32] = {0};

	strcpy(command,"USER ftpadmin\r\n");	
	ftpSend(socketTemp, command, strlen(command));

	memset(recvBuf, 0, 1024);
	ftpRecv(socketTemp, recvBuf, 1024);
	if (recvBuf[0] != '2' || recvBuf[0] != '3')
	{
		LOG4CXX_INFO(logger,"InitSocket errCode:"<<recvBuf);
		closesocket(socketTemp);
		return false;
	}

	//发送登陆密码
	memset(command, 0, 32);
	strcpy(command,"PASS ftpadmin123\r\n");	
	ftpSend(socketTemp, command, strlen(command));

	memset(recvBuf, 0, 1024);
	ftpRecv(socketTemp, recvBuf, 1024);
	if (recvBuf[0] != '2')
	{
		LOG4CXX_INFO(logger,"InitSocket errCode:"<<recvBuf);
		closesocket(socketTemp);
		return false;
	}

	//切换目录
	memset(command, 0, 32);
	strcpy(command,"CWD /home/ftpadmin\r\n");
	ftpSend(socketTemp, command, strlen(command));

	memset(recvBuf, 0, 1024);
	ftpRecv(socketTemp, recvBuf, 1024);
	if (recvBuf[0] != '2')
	{
		LOG4CXX_INFO(logger,"InitSocket errCode:"<<recvBuf);
		closesocket(socketTemp);
		return false;
	}

	//选择ascii编码传输
	memset(command, 0, 32);
	strcpy(command,"TYPE A\r\n");
	ftpSend(socketTemp, command, strlen(command));

	memset(recvBuf, 0, 1024);
	ftpRecv(socketTemp, recvBuf, 1024);
	if (recvBuf[0] != '2')
	{
		LOG4CXX_INFO(logger,"InitSocket errCode:"<<recvBuf);
		closesocket(socketTemp);
		return false;
	}

	//被动模式
	memset(command, 0, 32);
	strcpy(command,"PASV\r\n");
	ftpSend(socketTemp, command, strlen(command));

	memset(recvBuf, 0, 1024);
	ftpRecv(socketTemp, recvBuf, 1024);
	if (recvBuf[0] != '2')
	{
		LOG4CXX_INFO(logger,"InitSocket errCode:"<<recvBuf);
		closesocket(socketTemp);
		return false;
	}

	//去FTP服务器返回回来的端口号，数据连接需要链接到此端口号上进行数据传输
	const char *pListen = strchr(recvBuf, '(');
	pListen ++;

	//这里用联合体是因为联合体是按低地址开始存储的，且共用同一个内存控件，ip用4个字节来存储，端口号用两个字节存储
	union
	{
		unsigned char b[4];
		unsigned long ui;
	}ip;
	union
	{
		unsigned char b[2];
		unsigned short up;
	}port;

	unsigned char ip_port[6];
	sscanf(pListen,"%u,%u,%u,%u,%u,%u",&ip_port[0],&ip_port[1],&ip_port[2],&ip_port[3],&ip_port[4],&ip_port[5],&ip_port[6]);
	ip.b[3] = ip_port[0];
	ip.b[2] = ip_port[1];
	ip.b[1] = ip_port[2];
	ip.b[0] = ip_port[3];
	port.b[1] = ip_port[4];
	port.b[0] = ip_port[5];

	return true;
}

void CDriverAdaptorPlatfromCtrl::ftpRecv(SOCKET inSocket, char* buffer, int nLen)
{
	int recvByte = recv(inSocket, buffer, nLen, 0);

	if (SOCKET_ERROR == recvByte)
	{
		DWORD dwErr = WSAGetLastError();
		LOG4CXX_INFO(logger,"InitSocket errCode:"<<dwErr);
	}
}

void CDriverAdaptorPlatfromCtrl::ftpSend(SOCKET inSocket, char* command, int nLen)
{
	int sendByte = send(inSocket, command, nLen, 0);

	if (SOCKET_ERROR == sendByte)
	{
		DWORD dwErr = WSAGetLastError();
		LOG4CXX_INFO(logger,"InitSocket errCode:"<<dwErr);
	}
}

void CDriverAdaptorPlatfromCtrl::setTimeout(SOCKET inSocket,bool brecv,int timeout)
{
	if (inSocket == INVALID_SOCKET) return;
		
    setsockopt(inSocket,SOL_SOCKET,brecv?SO_RCVTIMEO:SO_SNDTIMEO,(char*)&timeout,sizeof(timeout));
}

