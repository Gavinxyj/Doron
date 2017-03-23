// DriverAdaptorPlatfromPropPage.cpp : CDriverAdaptorPlatfromPropPage 属性页类的实现。

#include "stdafx.h"
#include "DriverAdaptorPlatfrom.h"
#include "DriverAdaptorPlatfromPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CDriverAdaptorPlatfromPropPage, COlePropertyPage)



// 消息映射

BEGIN_MESSAGE_MAP(CDriverAdaptorPlatfromPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CDriverAdaptorPlatfromPropPage, "DRIVERADAPTORP.DriverAdaptorPPropPage.1",
	0x6b79cd4f, 0x83bd, 0x4e17, 0xbd, 0x20, 0xe6, 0x23, 0x14, 0x31, 0xf9, 0x2c)



// CDriverAdaptorPlatfromPropPage::CDriverAdaptorPlatfromPropPageFactory::UpdateRegistry -
// 添加或移除 CDriverAdaptorPlatfromPropPage 的系统注册表项

BOOL CDriverAdaptorPlatfromPropPage::CDriverAdaptorPlatfromPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_DRIVERADAPTORPLATFROM_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CDriverAdaptorPlatfromPropPage::CDriverAdaptorPlatfromPropPage - 构造函数

CDriverAdaptorPlatfromPropPage::CDriverAdaptorPlatfromPropPage() :
	COlePropertyPage(IDD, IDS_DRIVERADAPTORPLATFROM_PPG_CAPTION)
{
}



// CDriverAdaptorPlatfromPropPage::DoDataExchange - 在页和属性间移动数据

void CDriverAdaptorPlatfromPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CDriverAdaptorPlatfromPropPage 消息处理程序
