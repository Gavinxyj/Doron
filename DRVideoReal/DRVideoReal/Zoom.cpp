// Zoom.cpp : 实现文件
//

#include "stdafx.h"
#include "DRVideoReal.h"
#include "Zoom.h"
#include "afxdialogex.h"
#include "VideoReal.h"
#include "JsonParse.h"
// CZoom 对话框

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


// CZoom 消息处理程序


BOOL CZoom::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	if (m_pVideoCtrl->m_played)
	{
		m_pVideoCtrl->ZoomEnlarge(this->GetSafeHwnd());
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CZoom::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_pVideoCtrl->RemoveZoom(m_pVideoCtrl->m_nLoginId, m_pVideoCtrl->m_nZoomId);
	CDialogEx::OnClose();
}
