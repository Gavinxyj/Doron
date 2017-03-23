// SliderControl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DRVideoReal.h"
#include "SliderControl.h"
#include "afxdialogex.h"
#include "VideoReal.h";
#include "JsonParse.h"
// CSliderControl �Ի���

IMPLEMENT_DYNAMIC(CSliderControl, CDialogEx)

CSliderControl::CSliderControl(CVideoReal *pVideoCtrl, CWnd* pParent /*=NULL*/)
	: m_pVideoCtrl(pVideoCtrl), CDialogEx(CSliderControl::IDD, pParent)
{
}

/*
CSliderControl::CSliderControl(CVideoReal *pVideoCtrl): m_pVideoCtrl(pVideoCtrl)
{

}*/
CSliderControl::~CSliderControl()
{
}

void CSliderControl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSliderControl, CDialogEx)
	ON_WM_VSCROLL()
END_MESSAGE_MAP()


// CSliderControl ��Ϣ�������


BOOL CSliderControl::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CPoint point;
	CRect  rect;
	GetCursorPos(&point);
	GetWindowRect(&rect);
	MoveWindow(point.x - 200,point.y - 200,rect.Width(),rect.Height());
	((CSliderCtrl *)GetDlgItem(IDC_SLIDER1))->SetRange(1, 10);
	((CSliderCtrl *)GetDlgItem(IDC_SLIDER2))->SetRange(1, 10);
	((CSliderCtrl *)GetDlgItem(IDC_SLIDER3))->SetRange(1, 10);
	((CSliderCtrl *)GetDlgItem(IDC_SLIDER4))->SetRange(1, 10);
	((CSliderCtrl *)GetDlgItem(IDC_SLIDER1))->SetPos(10);
	((CSliderCtrl *)GetDlgItem(IDC_SLIDER2))->SetPos(10);
	((CSliderCtrl *)GetDlgItem(IDC_SLIDER3))->SetPos(10);
	((CSliderCtrl *)GetDlgItem(IDC_SLIDER4))->SetPos(10);
	if (NULL != m_pVideoCtrl)
	{
		m_pVideoCtrl->GetVideoParam();

		if (NULL != m_pVideoCtrl->m_videoParam)
		{
			((CSliderCtrl *)GetDlgItem(IDC_SLIDER1))->SetRange(1, 10);
			((CSliderCtrl *)GetDlgItem(IDC_SLIDER2))->SetRange(1, 10);
			((CSliderCtrl *)GetDlgItem(IDC_SLIDER3))->SetRange(1, 10);
			((CSliderCtrl *)GetDlgItem(IDC_SLIDER4))->SetRange(1, 10);

			((CSliderCtrl *)GetDlgItem(IDC_SLIDER1))->SetPos(m_pVideoCtrl->m_videoParam->bright);
			((CSliderCtrl *)GetDlgItem(IDC_SLIDER2))->SetPos(m_pVideoCtrl->m_videoParam->contrast);
			((CSliderCtrl *)GetDlgItem(IDC_SLIDER3))->SetPos(m_pVideoCtrl->m_videoParam->saturation);
			((CSliderCtrl *)GetDlgItem(IDC_SLIDER4))->SetPos(m_pVideoCtrl->m_videoParam->hue);
		}

	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CSliderControl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (NULL != pScrollBar)
	{
		CSliderCtrl *pSliderCtrl = (CSliderCtrl*)pScrollBar;
		
		int bright		= pSliderCtrl->GetPos();
		int contrast	= pSliderCtrl->GetPos();
		int saturation  = pSliderCtrl->GetPos();
		int hue			= pSliderCtrl->GetPos();
		m_pVideoCtrl->SetVideoParam(bright, contrast, saturation, hue);
	}
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}
