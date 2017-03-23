// DriverAdaptorPlatfrom.cpp : CDriverAdaptorPlatfromApp �� DLL ע���ʵ�֡�

#include "stdafx.h"
#include "DriverAdaptorPlatfrom.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CDriverAdaptorPlatfromApp theApp;

const GUID CDECL _tlid = { 0xFB1B6B75, 0xC008, 0x42B2, { 0xAA, 0x5B, 0xE5, 0xCE, 0xE7, 0xA1, 0x1D, 0xCC } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CDriverAdaptorPlatfromApp::InitInstance - DLL ��ʼ��

BOOL CDriverAdaptorPlatfromApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: �ڴ�������Լ���ģ���ʼ�����롣
	}

	return bInit;
}



// CDriverAdaptorPlatfromApp::ExitInstance - DLL ��ֹ

int CDriverAdaptorPlatfromApp::ExitInstance()
{
	// TODO: �ڴ�������Լ���ģ����ֹ���롣

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
