#pragma once
#include "subclass.h"

const UINT RWM_PRETRANSLATEMSG = ::RegisterWindowMessage(_T("RWM_PRETRANSLATEMSG"));

class CPreTranslateMsgHook : public CSubclassWnd
{
	typedef CSubclassWnd Super;

public:
	CPreTranslateMsgHook(void);
	virtual ~CPreTranslateMsgHook(void);

protected:	
	LRESULT WindowProc(UINT msg, WPARAM wp, LPARAM lp);
	BOOL WalkPreTranslateMsg(HWND hWndStop, MSG* pMsg);
};
