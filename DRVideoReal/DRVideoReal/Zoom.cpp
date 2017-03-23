// Zoom.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DRVideoReal.h"
#include "Zoom.h"
#include "afxdialogex.h"
#include "VideoReal.h"
#include "JsonParse.h"
// CZoom �Ի���

IMPLEMENT_DYNAMIC(CZoom, CDialogEx)

CZoom::CZoom(CVideoReal *pVideoCtrl, CWnd* pParent /*=NULL*/)
	: m_pVideoCtrl(pVideoCtrl), CDialogEx(CZoom::IDD, pParent)
{

}

CZoom::~CZoom()
{
}

void CZoom::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CZoom, CDialogEx)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CZoom ��Ϣ�������


BOOL CZoom::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	if (m_pVideoCtrl->m_played)
	{
		m_pVideoCtrl->ZoomEnlarge(this->GetSafeHwnd());
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CZoom::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_pVideoCtrl->RemoveZoom(m_pVideoCtrl->m_nLoginId, m_pVideoCtrl->m_nZoomId);
	CDialogEx::OnClose();
}
