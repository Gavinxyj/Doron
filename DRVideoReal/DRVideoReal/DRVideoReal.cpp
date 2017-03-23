// DRVideoReal.cpp : CDRVideoRealApp 和 DLL 注册的实现。

#include "stdafx.h"
#include "DRVideoReal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



CDRVideoRealApp theApp;

const GUID CDECL _tlid = { 0xD20038C9, 0x1AE7, 0x44E0, { 0x9A, 0x4D, 0xD8, 0x6B, 0xE1, 0x2E, 0x3C, 0x17 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


// CDRVideoRealApp::InitInstance - DLL 初始化

BOOL CDRVideoRealApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: 在此添加您自己的模块初始化代码。
		/*m_hHook = ::SetWindowsHookEx(  
										WH_GETMESSAGE,  
										GetMessageProc,  
										AfxGetInstanceHandle(),  
										GetCurrentThreadId());  

		ASSERT (m_hHook); */
		return CWinApp::InitInstance();   
	}

	return bInit;
}



// CDRVideoRealApp::ExitInstance - DLL 终止

int CDRVideoRealApp::ExitInstance()
{
	// TODO: 在此添加您自己的模块终止代码。
	UnhookWindowsHookEx((HHOOK)m_hHook);  
	return COleControlModule::ExitInstance();
}



// DllRegisterServer - 将项添加到系统注册表

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - 将项从系统注册表中移除

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}

LRESULT CALLBACK CDRVideoRealApp::GetMessageProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));  
	LPMSG lpMsg = (LPMSG) lParam;  

	if(AfxGetApp()->PreTranslateMessage(lpMsg))  
	{         
		lpMsg->message = WM_NULL;  
		lpMsg->lParam = 0L;  
		lpMsg->wParam = 0;         
	}  

	// Passes the hook information to the next hook procedure in  
	// the current hook chain.  
	return ::CallNextHookEx(theApp.m_hHook, nCode, wParam, lParam);  
}