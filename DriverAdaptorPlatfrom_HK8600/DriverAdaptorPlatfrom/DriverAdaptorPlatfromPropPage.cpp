// DriverAdaptorPlatfromPropPage.cpp : CDriverAdaptorPlatfromPropPage ����ҳ���ʵ�֡�

#include "stdafx.h"
#include "DriverAdaptorPlatfrom.h"
#include "DriverAdaptorPlatfromPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CDriverAdaptorPlatfromPropPage, COlePropertyPage)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CDriverAdaptorPlatfromPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CDriverAdaptorPlatfromPropPage, "DRIVERADAPTORP.DriverAdaptorPPropPage.1",
	0x6b79cd4f, 0x83bd, 0x4e17, 0xbd, 0x20, 0xe6, 0x23, 0x14, 0x31, 0xf9, 0x2c)



// CDriverAdaptorPlatfromPropPage::CDriverAdaptorPlatfromPropPageFactory::UpdateRegistry -
// ��ӻ��Ƴ� CDriverAdaptorPlatfromPropPage ��ϵͳע�����

BOOL CDriverAdaptorPlatfromPropPage::CDriverAdaptorPlatfromPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_DRIVERADAPTORPLATFROM_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CDriverAdaptorPlatfromPropPage::CDriverAdaptorPlatfromPropPage - ���캯��

CDriverAdaptorPlatfromPropPage::CDriverAdaptorPlatfromPropPage() :
	COlePropertyPage(IDD, IDS_DRIVERADAPTORPLATFROM_PPG_CAPTION)
{
}



// CDriverAdaptorPlatfromPropPage::DoDataExchange - ��ҳ�����Լ��ƶ�����

void CDriverAdaptorPlatfromPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CDriverAdaptorPlatfromPropPage ��Ϣ�������
