
// MonitorVideoStatus.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMonitorVideoStatusApp:
// �йش����ʵ�֣������ MonitorVideoStatus.cpp
//

class CMonitorVideoStatusApp : public CWinApp
{
public:
	CMonitorVideoStatusApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMonitorVideoStatusApp theApp;