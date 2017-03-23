#include "StdAfx.h"
#include "PreTranslateMsgHook.h"

CPreTranslateMsgHook::CPreTranslateMsgHook(void)
{
}

CPreTranslateMsgHook::~CPreTranslateMsgHook(void)
{
}

LRESULT CPreTranslateMsgHook::WindowProc(UINT msg, WPARAM wp, LPARAM lp)
{
	if(msg == RWM_PRETRANSLATEMSG)
	{
		BOOL bRet = FALSE;
		
		MSG* pMsg  = (MSG*)(lp);
		ASSERT(pMsg);

		CWnd* pWnd = CWnd::FromHandlePermanent(m_hWnd);
		if(pWnd != NULL)		
		{
			bRet = WalkPreTranslateMsg(pWnd->GetSafeHwnd(), pMsg);
		}

		return bRet;
	}	

	return Default();
}

BOOL CPreTranslateMsgHook::WalkPreTranslateMsg(HWND hWndStop, MSG* pMsg)
{
	ASSERT(hWndStop == NULL || ::IsWindow(hWndStop));
	ASSERT(pMsg != NULL);
	
	for (HWND hWnd = pMsg->hwnd; hWnd != NULL; hWnd = ::GetParent(hWnd))
	{
		CWnd* pWnd = CWnd::FromHandlePermanent(hWnd);
		if (pWnd != NULL)
		{
			// target window is a C++ window
			if (pWnd->PreTranslateMessage(pMsg))
				return TRUE; // trapped by target window (eg: accelerators)
		}
		
		// got to hWndStop window without interest
		if (hWnd == hWndStop)
			break;
	}
	
	return FALSE;       // no special processing
}
