// DRVideoRealPropPage.cpp : CDRVideoRealPropPage ����ҳ���ʵ�֡�

#include "stdafx.h"
#include "DRVideoReal.h"
#include "DRVideoRealPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CDRVideoRealPropPage, COlePropertyPage)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CDRVideoRealPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CDRVideoRealPropPage, "DRVIDEOREAL.DRVideoRealPropPage.1",
	0xee727a2e, 0xe878, 0x4b49, 0xa9, 0xd3, 0x5d, 0x4d, 0x7, 0xb7, 0x41, 0xc6)



// CDRVideoRealPropPage::CDRVideoRealPropPageFactory::UpdateRegistry -
// ��ӻ��Ƴ� CDRVideoRealPropPage ��ϵͳע�����

BOOL CDRVideoRealPropPage::CDRVideoRealPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_DRVIDEOREAL_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CDRVideoRealPropPage::CDRVideoRealPropPage - ���캯��

CDRVideoRealPropPage::CDRVideoRealPropPage() :
	COlePropertyPage(IDD, IDS_DRVIDEOREAL_PPG_CAPTION)
{
}



// CDRVideoRealPropPage::DoDataExchange - ��ҳ�����Լ��ƶ�����

void CDRVideoRealPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CDRVideoRealPropPage ��Ϣ�������
