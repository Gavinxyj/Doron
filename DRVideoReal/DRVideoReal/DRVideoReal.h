#pragma once

// DRVideoReal.h : DRVideoReal.DLL ����ͷ�ļ�

#if !defined( __AFXCTL_H__ )
#error "�ڰ������ļ�֮ǰ������afxctl.h��"
#endif

#include "resource.h"       // ������
#include <set>

// CDRVideoRealApp : �й�ʵ�ֵ���Ϣ������� DRVideoReal.cpp��
typedef std::set<HWND> THWNDCollection;
class CDRVideoRealApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();

private:
	static LRESULT CALLBACK GetMessageProc(int nCode, WPARAM wParam, LPARAM lParam); 
	HHOOK m_hHook; 

};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

