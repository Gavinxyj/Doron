#include "../DriverAdaptorPlatfrom/StdAfx.h"
#include "Hk8600InterfaceImpl.h"
#include "../DriverAdaptorPlatfrom/DriverAdaptorPlatfromCtrl.h"
#include "tmcp_interface_sdk.h"

CHk8600InterfaceImpl::CHk8600InterfaceImpl()
{
	m_LoginId = -1;
	m_playId  = -1;
	Platform::Plat_Init();
}


CHk8600InterfaceImpl::~CHk8600InterfaceImpl(void)
{
	Platform::Plat_Free();
}

BOOL CHk8600InterfaceImpl::OpenConnection(LPCTSTR strIp, DWORD dwPort, LPCTSTR userName, LPCTSTR password)
{
	LOG4CXX_INFO(m_pDriverCtrl->logger,"CHk8600InterfaceImpl::OpenConnection()----Start");
	CString strPort = "";
	strPort.Format("%d",dwPort);
	AfxMessageBox(strPort);
	m_LoginId = Platform::Plat_LoginCMS(strIp,(const char*)userName, (const char*)password,(LPTSTR)(LPCTSTR)strPort);

	if (-1 == m_LoginId)
	{
		int dwErrorCode = Platform::Plat_GetLastError();
		Platform::Plat_Free();
		LOG4CXX_INFO(m_pDriverCtrl->logger,"dwErrorCode = "<<dwErrorCode);
		return FALSE;
	}
	LOG4CXX_INFO(m_pDriverCtrl->logger,"CHk8600InterfaceImpl::OpenConnection()----End");
	return TRUE;
}

BOOL CHk8600InterfaceImpl::CloseConnection()
{
	LOG4CXX_INFO(m_pDriverCtrl->logger,"CHk8600InterfaceImpl::CloseConnection()----Start");
	if (-1 != m_LoginId)
	{
		int ret = Platform::Plat_LogoutCMS(m_LoginId);

		int dwErrorCode = Platform::Plat_GetLastError();

		if (-1 == ret)
		{
			LOG4CXX_INFO(m_pDriverCtrl->logger,"dwErrorCode = "<<dwErrorCode);
			return FALSE;
		}
	}
	else
	{
		LOG4CXX_INFO(m_pDriverCtrl->logger,"m_LoginId = "<<m_LoginId);
		return FALSE;
	}

	LOG4CXX_INFO(m_pDriverCtrl->logger,"CHk8600InterfaceImpl::CloseConnection()----End");
	return TRUE;
}

BOOL CHk8600InterfaceImpl::StartRealPlay(CStatic *pStaticCtrl)
{
	LOG4CXX_INFO(m_pDriverCtrl->logger,"CHk8600InterfaceImpl::StartRealPlay()----Start");
	if (-1 != m_LoginId)
	{
		char szCameraId[32] = {0};
		CString strUrl = Platform::Plat_QueryRealStreamURL(szCameraId,m_LoginId);
	    m_playId = Platform::Plat_PlayVideo(strUrl,(long)pStaticCtrl->GetSafeHwnd(), m_LoginId);

		if (m_playId < 0)
		{
			int dwErrorCode = Platform::Plat_GetLastError();
			LOG4CXX_INFO(m_pDriverCtrl->logger,"dwErrorCode = "<<dwErrorCode);
			return FALSE;
		}
	}
	else
	{
		LOG4CXX_INFO(m_pDriverCtrl->logger,"m_LoginId = "<<m_LoginId);
		return FALSE;
	}
	LOG4CXX_INFO(m_pDriverCtrl->logger,"CHk8600InterfaceImpl::StartRealPlay()----End");
	return TRUE;
}

BOOL CHk8600InterfaceImpl::StopRealPlay()
{
	LOG4CXX_INFO(m_pDriverCtrl->logger,"CHk8600InterfaceImpl::StopRealPlay()----Start");
	if (-1 != m_playId)
	{
		int nRet = Platform::Plat_StopVideo(m_playId);

		if (-1 == nRet)
		{
			int dwErrorCode = Platform::Plat_GetLastError();
			LOG4CXX_INFO(m_pDriverCtrl->logger,"dwErrorCode = "<<dwErrorCode);
			return FALSE;
		}
	}
	else
	{
		LOG4CXX_INFO(m_pDriverCtrl->logger,"m_LoginId = "<<m_LoginId);
		return FALSE;
	}
	m_pStaticCtrl->Invalidate();
	LOG4CXX_INFO(m_pDriverCtrl->logger,"CHk8600InterfaceImpl::StopRealPlay()----End");
	return TRUE;
}

BOOL CHk8600InterfaceImpl::CloudPatControl(DWORD dwCommand, DWORD dwStartEndFlag, DWORD dwSpeed)
{
	if(-1 != m_LoginId)
	{
		int nRet = Platform::Plat_ControlCamera("cameraId",dwCommand,dwStartEndFlag,dwSpeed,0,0,NULL,m_LoginId);

		if (-1 == nRet)
		{
			int dwErrorCode = Platform::Plat_GetLastError();
			LOG4CXX_INFO(m_pDriverCtrl->logger,"dwErrorCode = "<<dwErrorCode);
			return FALSE;
		}
	}
	else
	{
		LOG4CXX_INFO(m_pDriverCtrl->logger,"m_LoginId = "<<m_LoginId);
		return FALSE;
	}
	return TRUE;
}

BOOL CHk8600InterfaceImpl::CallPreset(DWORD dwPoint)
{
	return TRUE;
}

BOOL CHk8600InterfaceImpl::CapturePicture(LPCTSTR filePath, DWORD imageType, DWORD imageSize, DWORD imageQuality, DWORD dwChannelId)
{
	return TRUE;
}

BOOL CHk8600InterfaceImpl::DownLoadFile(LPCTSTR srcFileName, LPCTSTR saveFileName)
{
	return TRUE;
}

BOOL CHk8600InterfaceImpl::PausePlayBack(DWORD dwFlag)
{
	return TRUE;
}

BOOL CHk8600InterfaceImpl::PlayBack(LPCTSTR fileName)
{
	return TRUE;
}

BOOL CHk8600InterfaceImpl::Preset(DWORD dwPoint)
{
	return TRUE;
}

BOOL CHk8600InterfaceImpl::StartRecord(LPCTSTR filePath, DWORD dwChannelId /* = 1 */)
{
	return TRUE;
}

BOOL CHk8600InterfaceImpl::StopPlayBack()
{
	return TRUE;
}

BOOL CHk8600InterfaceImpl::StopRecord()
{
	return TRUE;
}

BOOL CHk8600InterfaceImpl::StartRealPlayFtp()
{
	return TRUE;
}