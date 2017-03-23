// VideoReal.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DRVideoReal.h"
#include "VideoReal.h"
#include "afxdialogex.h"
#include "DRVideoRealCtrl.h"
#include "InterfaceImpl.h"
#include "SliderControl.h"
#include "Zoom.h"
#include "DialogMessageHook.h"
// CVideoReal �Ի���
static BOOL bFullScreen = FALSE;
static BOOL rFullScreen = FALSE;
int num = 0;
static bool bFlag = false;
IMPLEMENT_DYNAMIC(CVideoReal, CDialogEx)

CVideoReal::CVideoReal(CDRVideoRealCtrl *pRealCtrl, CWnd* pParent /*=NULL*/)
	: m_pRealCtrl(pRealCtrl), CDialogEx(CVideoReal::IDD, pParent)
{
	m_Menu.LoadMenuA(IDR_MENU_BAR);
	m_curIndex = 0;
	m_nWidth   = 0;
	m_nHight   = 0;
	m_splitNum = 0;
	m_rect	   = 0;
	m_nZoomId  = -1;
	m_nLoginId = -1;
	m_nTalkId  = -1;
	bActive	   = false;
	m_played   = false;
	m_oldWnd   = NULL;
	m_pZoomDlg = NULL;

	m_pHook = NULL;

	//if(Create(IDD_DIALOG_VIDEO, pParent))
	{
		m_pHook = new CPreTranslateMsgHook();
		m_pHook->HookWindow(GetDesktopWindow()->GetSafeHwnd());

		ShowWindow(SW_SHOW);
	}	
}

CVideoReal::~CVideoReal()
{
	if (NULL != m_videoParam)
	{
		delete m_videoParam;
		m_videoParam = NULL;
	}

	if (NULL != m_pZoomDlg)
	{
		delete m_pZoomDlg;
		m_pZoomDlg = NULL;
	}

	CDialogMessageHook::UninstallHook(this->GetSafeHwnd());
}

void CVideoReal::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVideoReal, CDialogEx)
	ON_WM_LBUTTONDOWN()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_MENU_32786, &CVideoReal::OnMenuStopVideo)
	ON_COMMAND(ID_MENU_SINGLERECORD, &CVideoReal::OnMenuSingleRecord)
	ON_COMMAND(ID_MENU_CAPTURE, &CVideoReal::OnMenuCapture)
	ON_COMMAND(ID_MENU_FULLSCREEN, &CVideoReal::OnMenuFullscreen)
	ON_COMMAND(ID_MENU_SINGLESWITCH, &CVideoReal::OnMenuSingleswitch)
	ON_COMMAND(ID_MENU_SINGLESTOP, &CVideoReal::OnMenuSinglestop)
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_MENU_SETPARAM, &CVideoReal::OnMenuSetparam)
	ON_COMMAND(ID_MENU_ZOOM, &CVideoReal::OnMenuZoom)
	ON_COMMAND(ID_MENU_STYLE, &CVideoReal::OnMenuStyle)
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()


// CVideoReal ��Ϣ�������

void CVideoReal::DrawBorder()
{

	CPen *pOldPen = NULL;
	CPen pen;
	CRect rc;
	GetWindowRect(&rc);
	m_pRealCtrl->ScreenToClient(&rc);

	if (this->m_curIndex == m_pRealCtrl->m_curWndIndex)
	{
		pen.CreatePen(PS_SOLID,5,RGB(255, 127, 36));
	}
	else
	{
		pen.CreatePen(PS_SOLID,5,RGB(125, 125, 116));
	}
//	rc.right  += 2;
//	rc.bottom += 2;

	CDC *pDC = m_pRealCtrl->GetDC();
	pDC->SelectStockObject(NULL_BRUSH);
	pOldPen = pDC->SelectObject(&pen);
	pDC->Rectangle(&rc);
	ReleaseDC(pDC);
}

void CVideoReal::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	m_pRealCtrl->m_curWndIndex = this->m_curIndex;

	for (int nLoop = 0; nLoop < MAX_CHILDWND; nLoop ++)
	{
		m_pRealCtrl->m_pVideoReal[nLoop]->DrawBorder();
	}

	SetFocus();
	GetWindowRect(&m_pRealCtrl->m_rect);
	m_pRealCtrl->ScreenToClient(m_pRealCtrl->m_rect);
	m_pRealCtrl->ScreenToClient(&point);
	m_pRealCtrl->m_prePoint = point;
	m_pRealCtrl->m_preWndIndex = this->m_curIndex;
	LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "OnLButtonDown m_curWndIndex = " << this->m_curIndex);
	/*MSG message;  
	DWORD st = GetTickCount();  
    while (1)  
    {  
        if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))  
        {  
            TranslateMessage(&message);  
            DispatchMessage(&message);  
            if (message.message == WM_LBUTTONDBLCLK)  
            {
				LOG4CXX_INFO(CJsonParse::getInstance()->logger, "OnLButtonDown ---> OnLButtonDblClk");
			
				//::SendMessage(this->GetSafeHwnd(),WM_LBUTTONDBLCLK,0,0);
                break; 
            }  
        }  
        DWORD et = GetTickCount();  
        if (et - st > 200)  
        {  
            num = 0;  
			LOG4CXX_INFO(CJsonParse::getInstance()->logger, "OnLButtonDown");
            break;  
        }  
    }  */
	CDialogEx::OnLButtonDown(nFlags, point);
}


HBRUSH CVideoReal::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	
	return CreateSolidBrush(RGB(0,0,0));
}


BOOL CVideoReal::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	
	return CDialogEx::OnEraseBkgnd(pDC);
}

bool CVideoReal::Capture(LPCTSTR strPath)
{
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance ʵ����ʧ�� ");
		return false;
	}

	bool bRet = CInterfaceImpl::getInitance()->Capture(strPath, m_nLoginId);

	return bRet;
}

bool CVideoReal::StartRecord()
{
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance ʵ����ʧ�� ");
		return false;
	}

	bool bRet = false;
	if (-1 != m_nLoginId)
	{
		bool bRet = CInterfaceImpl::getInitance()->StartRecord(m_nLoginId);

		LOG4CXX_DEBUG(CJsonParse::getInstance()->logger, "StartRecord this = " << this << ";m_nLoginId = " << m_nLoginId << "bRet = " << bRet);
	}
	
	
	return bRet;
}

bool CVideoReal::StopRecord()
{
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance ʵ����ʧ�� ");
		return false;
	}

	bool bRet = false;
	if (-1 != m_nLoginId)
	{
		
		bRet = CInterfaceImpl::getInitance()->StopRecord(m_nLoginId);
		LOG4CXX_DEBUG(CJsonParse::getInstance()->logger, "StopRecord this = " << this << ";m_nLoginId = " << m_nLoginId << "bRet = " << bRet);
	}
    

	return bRet;
}

bool CVideoReal::StopVideo()
{
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance ʵ����ʧ�� ");
		return false;
	}
	
	bool bRet = CInterfaceImpl::getInitance()->StopVideo(m_nLoginId);

	LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "m_nLoginId = " << m_nLoginId << ";ret = " << bRet);
	m_nLoginId = -1;

	Invalidate();

	if (bRet) m_played = false;
	
	return bRet;
}

bool CVideoReal::StartVideo(CONNECTINFO *connInfo)
{
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance ʵ����ʧ�� ");
		return false;
	}
	m_nLoginId = CInterfaceImpl::getInitance()->StartVideo(connInfo);
	
	if (-1 == m_nLoginId)  return false;
		
	
	m_played = true;

	return true;
}

void CVideoReal::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	LOG4CXX_INFO(CJsonParse::getInstance()->logger, "OnLButtonDblClk");
	if (m_splitNum < 4)
	{
		return;
	}
	CRect rect;
	GetWindowRect(&rect);
	//ClientToScreen(&point);
	ScreenToClient(&rect);
	//if (rect.PtInRect(point))
	
	{
		if(!bFullScreen)
		{
			m_pRealCtrl->m_curWndIndex = this->m_curIndex;

			for (int nLoop = 0; nLoop < MAX_CHILDWND; nLoop ++)
			{
				m_pRealCtrl->m_pVideoReal[nLoop]->ShowWindow(SW_HIDE);
			}

			this->ShowWindow(SW_SHOW);
			m_nWidth = m_rect.Width();
			m_nHight = m_rect.Height();
			this->MoveWindow(0,0,m_rect.Width(),m_rect.Height());

			bFullScreen = TRUE;
		}
		else
		{
			
			m_pRealCtrl->SplitScreen(m_splitNum);

			/************************************************************************ /
			/ * ����껬���ϲ����ڣ�˫��ȫ�����ڣ��ٴ�˫���ָ�ԭ������ʾ���,�����bFlag����Ǽ�¼�����
			/ * �����Ĳ����� �����ʱ������˷����������ڻָ�ԭ������ʾ�����* /
			/ ************************************************************************/
		//	if (bFlag)
			{
				/*std::vector<WINSTYLE>::iterator iter = m_pRealCtrl->m_oldRect.begin();

				for (; iter != m_pRealCtrl->m_oldRect.end(); iter ++)
				{
					m_pRealCtrl->m_pVideoReal[iter->nWindowId]->MoveWindow(iter->rect.left, iter->rect.top,iter->rect.right, iter->rect.bottom);
					m_pRealCtrl->m_pVideoReal[iter->nWindowId]->DrawBorder();
					m_pRealCtrl->m_pVideoReal[iter->nWindowId]->Invalidate();
				}*/

				POSITION pos = m_pRealCtrl->m_mapRect.GetStartPosition(); 
				int nWindowId = 0;
				PWINSTYLE winStyle = NULL;
				while(pos) 
				{ 
					m_pRealCtrl->m_mapRect.GetNextAssoc(pos,nWindowId,winStyle);
					m_pRealCtrl->m_pVideoReal[nWindowId]->MoveWindow(winStyle->rect.left, winStyle->rect.top,winStyle->rect.right, winStyle->rect.bottom);
					m_pRealCtrl->m_pVideoReal[nWindowId]->DrawBorder();
					m_pRealCtrl->m_pVideoReal[nWindowId]->Invalidate();
				} 
				//m_mapConnInfo.RemoveAll();
				bFlag = false;
			//	m_pRealCtrl->m_oldRect.clear();
			}	
			bFullScreen = FALSE;
			
		}
	}
	
	CDialogEx::OnLButtonDblClk(nFlags, point);
}

bool CVideoReal::PtzControl(Client_PTZ_Command *cmd)
{
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance ʵ����ʧ�� ");
		return false;
	}

	bool bRet = CInterfaceImpl::getInitance()->PtzControl(cmd, m_nLoginId);

	return bRet;
}

bool CVideoReal::OpenSound()
{
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance ʵ����ʧ�� ");
		return false;
	}

	bool bRet = CInterfaceImpl::getInitance()->OpenSound(m_nLoginId);

	return bRet;
}

bool CVideoReal::CloseSound()
{
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance ʵ����ʧ�� ");
		return false;
	}

	bool bRet = CInterfaceImpl::getInitance()->CloseSound(m_nLoginId);
	
	return bRet;
}

bool CVideoReal::StopSwitchSingle()
{
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance ʵ����ʧ�� ");
		return false;
	}

	bool bRet = CInterfaceImpl::getInitance()->StopSwitchSingle(m_nLoginId,m_curIndex,0);

	return bRet;
}
void CVideoReal::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	ClientToScreen(&point);
	//if (rect.PtInRect(point))
	{
		m_Menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);

	}
	CDialogEx::OnRButtonDown(nFlags, point);
}

bool CVideoReal::SetVolumn(int nVolumn)
{
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance ʵ����ʧ�� ");
		return false;
	}
	
	bool bRet = CInterfaceImpl::getInitance()->SetVolumn(nVolumn, m_nLoginId);

	return bRet;
}

bool CVideoReal::StartTalk()
{
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance ʵ����ʧ�� ");
		return false;
	}

	bool bRet = CInterfaceImpl::getInitance()->StartTalk(m_nTalkId);

	return bRet;
}

bool CVideoReal::StopTalk()
{
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance ʵ����ʧ�� ");
		return false;
	}

	bool bRet = CInterfaceImpl::getInitance()->StopTalk(m_nTalkId);

	return bRet;
}

bool CVideoReal::SetVideoParam(int bright, int contrast, int saturation, int hue)
{
	bool bRet = false;
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance ʵ����ʧ�� ");
		return false;
	}

	if (-1 != m_nLoginId)
	{
	    bRet = CInterfaceImpl::getInitance()->SetVideoParam(bright, contrast, saturation, hue, m_nLoginId);
	}
	return bRet;
}

bool CVideoReal::GetVideoParam()
{
	bool bRet = false;
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance ʵ����ʧ�� ");
		return false;
	}

	if (-1 != m_nLoginId)
	{
		if (NULL != m_videoParam)
		{
			delete m_videoParam;
			m_videoParam = NULL;
		}
		m_videoParam = new VIDEOPARAM;
		bRet = CInterfaceImpl::getInitance()->GetVideoParam(m_nLoginId, m_videoParam);
	}
	return bRet;
}

bool CVideoReal::ZoomEnlarge(HWND hWnd)
{
	bool bRet = false;
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance ʵ����ʧ�� ");
		return false;
	}

	if (-1 != m_nLoginId)
	{
		RectZoom rect = {0};
		
		bRet = CInterfaceImpl::getInitance()->ZoomEnlarge(m_nLoginId, hWnd, &rect, 1, &m_nZoomId);

		if (!bRet) return false;
		
		rect.left = 0;
		rect.top  = 0;
		rect.right = 400;
		rect.bottom = 200;
		bRet = CInterfaceImpl::getInitance()->SetZoom(m_nLoginId, m_nZoomId, rect);
		
		LOG4CXX_DEBUG(CJsonParse::getInstance()->logger, "m_nLoginId = " << m_nLoginId << ";bRet = " << bRet << ";m_nZoomId = " << m_nZoomId);
		
		bRet = CInterfaceImpl::getInitance()->RemoveZoom(m_nLoginId, m_nZoomId);
		Invalidate();
	}
	return true;
}

bool CVideoReal::RemoveZoom(int nLoginId, int nZoomId)
{
	bool bRet = false;
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance ʵ����ʧ�� ");
		return false;
	}
	if (-1 != m_nLoginId)
	{
		bRet = CInterfaceImpl::getInitance()->RemoveZoom(m_nLoginId, nZoomId);
		Invalidate();
		LOG4CXX_DEBUG(CJsonParse::getInstance()->logger, "RemoveZoom ---> m_nLoginId = " << m_nLoginId << ";bRet = " << bRet << ";nZoomId = " << nZoomId);
	}

	return bRet;
}
void CVideoReal::OnMenuStopVideo()
{
	// TODO: �ڴ���������������
	bool bRet = false;

	if (NULL != CInterfaceImpl::getInitance())
	{
		bRet = CInterfaceImpl::getInitance()->StopVideo(m_nLoginId);
		m_nLoginId = -1;
		Invalidate();
	}

	if (bRet) m_played = false;

	if (m_played)
	{
		if (!bRet) MessageBox("ֹͣ��Ƶʧ��!");
	}
	
}


void CVideoReal::OnMenuSingleRecord()
{
	// TODO: �ڴ���������������
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance ʵ����ʧ�� ");
		return ;
	}

	bool bRet = CInterfaceImpl::getInitance()->StartRecord(m_nLoginId);
	
	if (!bRet) MessageBox("��ʼ¼��ʧ��!");
	
}


void CVideoReal::OnMenuCapture()
{
	// TODO: �ڴ���������������
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance ʵ����ʧ�� ");
		return ;
	}

	bool bRet = false;
	if (this->m_played)
	{
		if (CJsonParse::getInstance()->m_pItemData->pOtherInfo->capturepath[0] == '\0')
		{
			CInterfaceImpl::getInitance()->Capture(m_pRealCtrl->m_curMoudlePath, m_nLoginId);
		}
		else
		{
			bRet = CInterfaceImpl::getInitance()->Capture(CJsonParse::getInstance()->m_pItemData->pOtherInfo->capturepath, m_nLoginId);
		}
	}

	if (!bRet) MessageBox("ץ��ʧ��!");
}


void CVideoReal::OnMenuFullscreen()
{
	// TODO: �ڴ���������������
	int nWidth = GetSystemMetrics(SM_CXSCREEN);
	int nHight = GetSystemMetrics(SM_CYSCREEN);
	
	if (!rFullScreen)
	{
		m_oldWnd = GetParent();
		SetParent(GetDesktopWindow());
		//this->SetWindowPos(&wndTop,0,0, nWidth, nHight, SWP_SHOWWINDOW);
		ModifyStyle(WS_CAPTION, 0, 0);
		SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
		ShowWindow(SW_SHOWMAXIMIZED);

		m_Menu.GetSubMenu(0)->CheckMenuItem(ID_MENU_FULLSCREEN, MF_CHECKED|MF_BYCOMMAND);
		m_Menu.GetSubMenu(0)->EnableMenuItem(ID_MENU_STYLE, MF_BYCOMMAND | MF_DISABLED);
		rFullScreen = TRUE;
	}
	else
	{
		if (NULL != m_oldWnd)
		{
			SetParent(m_oldWnd);
			ModifyStyle(WS_CAPTION,0,0);
			SendMessage(WM_SYSCOMMAND, SC_SCREENSAVE, 0);
			ShowWindow(SW_SHOWNORMAL);
			m_Menu.GetSubMenu(0)->CheckMenuItem(ID_MENU_FULLSCREEN, MF_UNCHECKED|MF_BYCOMMAND);
			m_Menu.GetSubMenu(0)->EnableMenuItem(ID_MENU_STYLE, MF_BYCOMMAND | MF_ENABLED);
			rFullScreen = FALSE;
		}
	}
	
	

	//LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "strMenu = " << strMenu);
}


void CVideoReal::OnMenuSingleswitch()
{
	// TODO: �ڴ���������������
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance ʵ����ʧ�� ");
		return ;
	}

	bool bRet = CInterfaceImpl::getInitance()->StartSwitchSingle("id");

	if (!bRet) MessageBox("��֡�л�����ʧ��!");
}



void CVideoReal::OnMenuSinglestop()
{
	// TODO: �ڴ���������������
	if (NULL == CInterfaceImpl::getInitance())
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "CInterfaceImpl::getInitance ʵ����ʧ�� ");
		return ;
	}

	bool bRet = CInterfaceImpl::getInitance()->StopSwitchSingle(m_nLoginId,m_curIndex,0);

	if (!bRet) MessageBox("ֹͣ��֡�л�ʧ��!");
}


void CVideoReal::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CRect rect;
	GetWindowRect(&rect);
	m_pRealCtrl->ScreenToClient(rect);
	
	if (m_pRealCtrl->m_preWndIndex != m_curIndex && !m_played)
	{
		PWINSTYLE winStyleTemp = new WINSTYLE;

		//������򻬶������ң�����
		if ((rect.right - m_pRealCtrl->m_rect.left) > 0 && (rect.bottom - m_pRealCtrl->m_rect.top) > 0)
		{
			LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "OnLButtonUp m_pRealCtrl->m_preWndIndex = " <<m_pRealCtrl->m_preWndIndex << ";m_curIndex = " << m_curIndex);
			
			/************************************************************************/
			/* ������жϳ����ǣ���������󻬶��ϲ��˴��ڣ������»��������ʱ����һ�����󻬶��ϲ��Ĵ���
			/* �����½ǵ��������Ҫ�ȵ�ǰ�����Ĵ�����������ʱ��ͺϲ��Ĵ��ڵ�right�����ȡ���ֵ��
			/* bottom��ȥ��ǰ�������ڵ�bottom����*/
			/************************************************************************/
			if (m_pRealCtrl->m_rect.right < rect.right)
			{
				if (rect.bottom < m_pRealCtrl->m_rect.bottom)
				{
					m_pRealCtrl->m_pVideoReal[m_pRealCtrl->m_preWndIndex]->MoveWindow(m_pRealCtrl->m_rect.left, m_pRealCtrl->m_rect.top, rect.right - m_pRealCtrl->m_rect.left, m_pRealCtrl->m_rect.bottom - m_pRealCtrl->m_rect.top);
					winStyleTemp->rect.left   = m_pRealCtrl->m_rect.left;
					winStyleTemp->rect.top    = m_pRealCtrl->m_rect.top;
					winStyleTemp->rect.right  = rect.right - m_pRealCtrl->m_rect.left;
					winStyleTemp->rect.bottom = m_pRealCtrl->m_rect.bottom - m_pRealCtrl->m_rect.top;
				}
				else
				{
					m_pRealCtrl->m_pVideoReal[m_pRealCtrl->m_preWndIndex]->MoveWindow(m_pRealCtrl->m_rect.left, m_pRealCtrl->m_rect.top, rect.right - m_pRealCtrl->m_rect.left, rect.bottom - m_pRealCtrl->m_rect.top);
					winStyleTemp->rect.left   = m_pRealCtrl->m_rect.left;
					winStyleTemp->rect.top    = m_pRealCtrl->m_rect.top;
					winStyleTemp->rect.right  = rect.right - m_pRealCtrl->m_rect.left;
					winStyleTemp->rect.bottom = rect.bottom - m_pRealCtrl->m_rect.top;
				}
			}
			else
			{
				m_pRealCtrl->m_pVideoReal[m_pRealCtrl->m_preWndIndex]->MoveWindow(m_pRealCtrl->m_rect.left, m_pRealCtrl->m_rect.top, m_pRealCtrl->m_rect.right - m_pRealCtrl->m_rect.left, rect.bottom - m_pRealCtrl->m_rect.top);
				winStyleTemp->rect.left   = m_pRealCtrl->m_rect.left;
				winStyleTemp->rect.top    = m_pRealCtrl->m_rect.top;
				winStyleTemp->rect.right  = m_pRealCtrl->m_rect.right - m_pRealCtrl->m_rect.left;
				winStyleTemp->rect.bottom = rect.bottom - m_pRealCtrl->m_rect.top;
			}
			m_pRealCtrl->m_pVideoReal[m_pRealCtrl->m_preWndIndex]->DrawBorder();
			m_pRealCtrl->m_pVideoReal[m_pRealCtrl->m_preWndIndex]->Invalidate();
			m_pRealCtrl->m_pVideoReal[m_pRealCtrl->m_preWndIndex]->BringWindowToTop();
		}
		else
		{   
			//��귴�컬������������
			LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "OnLButtonUp m_pRealCtrl->m_preWndIndex = " <<m_pRealCtrl->m_preWndIndex << ";m_curIndex = " << m_curIndex);
			/************************************************************************/
			/* ������жϳ����ǣ���������󻬶��ϲ��˴��ں������ϻ����ͻ������������һ���Ǻϲ����ڵ���
			/* �Ͻ�����ҪС�ڵ�ǰ���������꣬һ���Ǵ��ڵ�ǰ����������*/
			/************************************************************************/
			if (m_pRealCtrl->m_rect.left >= rect.left)
			{
				/************************************************************************/
				/* ������жϳ�������������ϻ����ˣ�Ȼ�����»����ˣ������󻬶������ʱ��ϲ�������Ҫ�����ϻ����Ĵ���
				/* Ϊ����ȥMoveWindow */
				/************************************************************************/
				if (m_pRealCtrl->m_rect.top < rect.top)
				{
					m_pRealCtrl->m_pVideoReal[m_pRealCtrl->m_preWndIndex]->MoveWindow(rect.left,m_pRealCtrl->m_rect.top, m_pRealCtrl->m_rect.right - rect.left, m_pRealCtrl->m_rect.bottom - m_pRealCtrl->m_rect.top);
					winStyleTemp->rect.left   = rect.left;
					winStyleTemp->rect.top    = m_pRealCtrl->m_rect.top;
					winStyleTemp->rect.right  = m_pRealCtrl->m_rect.right - rect.left;
					winStyleTemp->rect.bottom = m_pRealCtrl->m_rect.bottom - m_pRealCtrl->m_rect.top;
				}
				else
				{
					m_pRealCtrl->m_pVideoReal[m_pRealCtrl->m_preWndIndex]->MoveWindow(rect.left,rect.top, m_pRealCtrl->m_rect.right - rect.left, m_pRealCtrl->m_rect.bottom - rect.top);
					winStyleTemp->rect.left   = rect.left;
					winStyleTemp->rect.top    = rect.top;
					winStyleTemp->rect.right  = m_pRealCtrl->m_rect.right - rect.left;
					winStyleTemp->rect.bottom = m_pRealCtrl->m_rect.bottom - rect.top;
				}
				
			}
			else
			{
				m_pRealCtrl->m_pVideoReal[m_pRealCtrl->m_preWndIndex]->MoveWindow(m_pRealCtrl->m_rect.left, rect.top, rect.right - m_pRealCtrl->m_rect.left, m_pRealCtrl->m_rect.bottom - rect.top);
				winStyleTemp->rect.left   = m_pRealCtrl->m_rect.left;
				winStyleTemp->rect.top    = rect.top;
				winStyleTemp->rect.right  = rect.right - m_pRealCtrl->m_rect.left;
				winStyleTemp->rect.bottom = m_pRealCtrl->m_rect.bottom - rect.top;
			}
		
			m_pRealCtrl->m_pVideoReal[m_pRealCtrl->m_preWndIndex]->DrawBorder();
			m_pRealCtrl->m_pVideoReal[m_pRealCtrl->m_preWndIndex]->Invalidate();
			m_pRealCtrl->m_pVideoReal[m_pRealCtrl->m_preWndIndex]->BringWindowToTop();
		}
		
		PWINSTYLE winStyle = NULL;
		if (!m_pRealCtrl->m_mapRect.Lookup(m_pRealCtrl->m_preWndIndex, winStyle))
		{
			winStyle = new WINSTYLE;
			memcpy(winStyle, winStyleTemp, sizeof(WINSTYLE));
			winStyle->nWindowId   = m_pRealCtrl->m_preWndIndex;
			winStyle->nCurWindowId= m_curIndex;
			m_pRealCtrl->m_mapRect.SetAt(m_pRealCtrl->m_preWndIndex, winStyle);
			
			delete winStyleTemp;
			winStyleTemp = NULL;
		}
		else
		{
			memcpy(winStyle, winStyleTemp, sizeof(WINSTYLE));
			winStyle->nWindowId   = m_pRealCtrl->m_preWndIndex;
			winStyle->nCurWindowId= m_curIndex;
			m_pRealCtrl->m_mapRect.SetAt(m_pRealCtrl->m_preWndIndex, winStyle);

			delete winStyleTemp;
			winStyleTemp = NULL;
		}
		
		LOG4CXX_DEBUG(CJsonParse::getInstance()->logger, "m_pRealCtrl->m_rect.left = " << m_pRealCtrl->m_rect.left);
		LOG4CXX_DEBUG(CJsonParse::getInstance()->logger, "m_pRealCtrl->m_rect.top = " << m_pRealCtrl->m_rect.top);
		LOG4CXX_DEBUG(CJsonParse::getInstance()->logger, "m_pRealCtrl->m_rect.Width = " <<m_pRealCtrl->m_rect.Width());
		LOG4CXX_DEBUG(CJsonParse::getInstance()->logger, "m_pRealCtrl->m_rect.Height = " << m_pRealCtrl->m_rect.Height());

		LOG4CXX_DEBUG(CJsonParse::getInstance()->logger, "rect.right = " << rect.right);
		LOG4CXX_DEBUG(CJsonParse::getInstance()->logger, "rect.bottom = " << rect.bottom);
		bFlag = true;
	}
	else
	{
		if (!m_played) return;

		m_pRealCtrl->ScreenToClient(&point);
		RectZoom rect = {0};
		rect.left = m_pRealCtrl->m_prePoint.x;
		rect.top  = m_pRealCtrl->m_prePoint.y;
		rect.right = point.x;
		rect.bottom = point.y;

		CInterfaceImpl::getInitance()->SetZoom(m_nLoginId, m_nZoomId, rect);
	}
	
	CDialogEx::OnLButtonUp(nFlags, point);
}

void CVideoReal::OnMenuSetparam()
{
	// TODO: �ڴ���������������
	CSliderControl sliderDlg(this);
	
	sliderDlg.DoModal();
}


void CVideoReal::OnMenuZoom()
{
	// TODO: �ڴ���������������
	//CZoom zoomDlg(this);
	if (!m_played) return;
	
	if (NULL == m_pZoomDlg)
	{
		m_pZoomDlg = new CZoom(this);
		m_pZoomDlg->Create(IDD_DIALOG_ZOOM, this);
	}
	
	m_pZoomDlg->ShowWindow(SW_SHOWNORMAL);
}


void CVideoReal::OnMenuStyle()
{
	// TODO: �ڴ���������������
//	if (!m_played) return;
	int nWindowId = 0;
	WINSTYLE *pWinStyle = NULL;
	POSITION pos = m_pRealCtrl->m_mapRect.GetStartPosition(); 
	while(pos) 
	{ 
		m_pRealCtrl->m_mapRect.GetNextAssoc(pos,nWindowId,pWinStyle);
		if ( NULL != pWinStyle)
		{
			delete pWinStyle;
			pWinStyle = NULL;
		}
	} 
	m_pRealCtrl->m_mapRect.RemoveAll();
	m_pRealCtrl->SplitScreen(m_splitNum);
}



BOOL CVideoReal::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	LOG4CXX_DEBUG(CJsonParse::getInstance()->logger, "pMsg->message = " << pMsg->message << "pMsg->wParam = " << pMsg->wParam);
	if (pMsg->message == WM_KEYDOWN)
	{
		LOG4CXX_DEBUG(CJsonParse::getInstance()->logger, "pMsg->message = " << WM_KEYDOWN);
	}
	//return FALSE;
	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL CVideoReal::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CVideoReal::OnKillFocus(CWnd* pNewWnd)
{
	
	CDialogEx::OnKillFocus(pNewWnd);

	if (rFullScreen)
	{
		SetParent(m_oldWnd);
		ModifyStyle(WS_CAPTION,0,0);
		SendMessage(WM_SYSCOMMAND, SC_SCREENSAVE, 0);
		ShowWindow(SW_SHOWNORMAL);
		m_Menu.GetSubMenu(0)->CheckMenuItem(ID_MENU_FULLSCREEN, MF_UNCHECKED|MF_BYCOMMAND);
		m_Menu.GetSubMenu(0)->EnableMenuItem(ID_MENU_STYLE, MF_BYCOMMAND | MF_ENABLED);
		rFullScreen = FALSE;
	}
	// TODO: �ڴ˴������Ϣ����������
}
