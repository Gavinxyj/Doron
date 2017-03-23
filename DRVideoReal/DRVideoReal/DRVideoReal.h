#pragma once

// DRVideoReal.h : DRVideoReal.DLL 的主头文件

#if !defined( __AFXCTL_H__ )
#error "在包括此文件之前包括“afxctl.h”"
#endif

#include "resource.h"       // 主符号
#include <set>

// CDRVideoRealApp : 有关实现的信息，请参阅 DRVideoReal.cpp。
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

