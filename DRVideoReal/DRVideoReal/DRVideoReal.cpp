// DRVideoReal.cpp : CDRVideoRealApp �� DLL ע���ʵ�֡�

#include "stdafx.h"
#include "DRVideoReal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



CDRVideoRealApp theApp;

const GUID CDECL _tlid = { 0xD20038C9, 0x1AE7, 0x44E0, { 0x9A, 0x4D, 0xD8, 0x6B, 0xE1, 0x2E, 0x3C, 0x17 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


// CDRVideoRealApp::InitInstance - DLL ��ʼ��

BOOL CDRVideoRealApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: �ڴ�������Լ���ģ���ʼ�����롣
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



// CDRVideoRealApp::ExitInstance - DLL ��ֹ

int CDRVideoRealApp::ExitInstance()
{
	// TODO: �ڴ�������Լ���ģ����ֹ���롣
	UnhookWindowsHookEx((HHOOK)m_hHook);  
	return COleControlModule::ExitInstance();
}



// DllRegisterServer - ������ӵ�ϵͳע���

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - �����ϵͳע������Ƴ�

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