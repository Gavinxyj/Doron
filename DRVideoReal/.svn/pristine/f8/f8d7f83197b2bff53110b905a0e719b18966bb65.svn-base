// DRVideoRealPropPage.cpp : CDRVideoRealPropPage 属性页类的实现。

#include "stdafx.h"
#include "DRVideoReal.h"
#include "DRVideoRealPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CDRVideoRealPropPage, COlePropertyPage)



// 消息映射

BEGIN_MESSAGE_MAP(CDRVideoRealPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CDRVideoRealPropPage, "DRVIDEOREAL.DRVideoRealPropPage.1",
	0xee727a2e, 0xe878, 0x4b49, 0xa9, 0xd3, 0x5d, 0x4d, 0x7, 0xb7, 0x41, 0xc6)



// CDRVideoRealPropPage::CDRVideoRealPropPageFactory::UpdateRegistry -
// 添加或移除 CDRVideoRealPropPage 的系统注册表项

BOOL CDRVideoRealPropPage::CDRVideoRealPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_DRVIDEOREAL_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CDRVideoRealPropPage::CDRVideoRealPropPage - 构造函数

CDRVideoRealPropPage::CDRVideoRealPropPage() :
	COlePropertyPage(IDD, IDS_DRVIDEOREAL_PPG_CAPTION)
{
}



// CDRVideoRealPropPage::DoDataExchange - 在页和属性间移动数据

void CDRVideoRealPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CDRVideoRealPropPage 消息处理程序
