#include "../DriverAdaptorPlatfrom/StdAfx.h"
#include "DhInterfaceImpl.h"
#include "../DriverAdaptorPlatfrom/DriverAdaptorPlatfromCtrl.h"
LoggerPtr logger;

CDhInterfaceImpl::CDhInterfaceImpl()
{
	CLIENT_Init(DisConnectFunc, (DWORD)this);
	m_loginId = 0;
	m_channelCount = 0;
	m_realPlayId = 0;

	
	char szPath[256] = {0};

	DWORD dwCode = GetCurrentDirectory(sizeof(szPath), szPath);

	if(0 == dwCode)
	{
		DWORD dwErr = GetLastError();
		LOG4CXX_INFO(logger,"GetCurrentDirectory errCode:"<<dwErr);
		return;
	}

	CString fileName;
	fileName.Format("%s\\config\\config.ini",szPath);
	PropertyConfigurator::configure(fileName.GetBuffer());
	logger = Logger::getLogger("debugLogger");

}


CDhInterfaceImpl::~CDhInterfaceImpl(void)
{
	CLIENT_Cleanup();
}

BOOL CDhInterfaceImpl::OpenConnection(LPCTSTR strIp, DWORD dwPort, LPCTSTR userName, LPCTSTR password)
{
	LOG4CXX_INFO(logger,"OpenConnection---start");
	NET_DEVICEINFO deviceInfo = {0};
	int dwErrCode = 0;
	LLONG loginId = CLIENT_Login((char*)strIp,dwPort,(char*)userName,(char*)password,&deviceInfo,&dwErrCode);

	if( 0 != loginId)
	{
		m_loginId = loginId;
		m_channelCount = (int)deviceInfo.byChanNum;
		LOG4CXX_INFO(logger,"登陆成功");
		return TRUE;
	}
	else
	{
		LOG4CXX_ERROR(logger,"打开连接失败，错误码:"<<dwErrCode);
	}

	LOG4CXX_INFO(logger,"OpenConnection---end");
	return FALSE;
}

BOOL CDhInterfaceImpl::CloseConnection()
{
	if(m_loginId != 0)
	{
		BOOL bRet = CLIENT_Logout(m_loginId);
		if (bRet)
		{
			m_loginId = 0;
			m_pStaticCtrl->Invalidate();
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CDhInterfaceImpl::StartRealPlay(CStatic *pStaticCtrl)
{
	m_pStaticCtrl = pStaticCtrl;
	m_realPlayId = CLIENT_RealPlay(m_loginId,0,pStaticCtrl->GetSafeHwnd());
	
	DWORD dwErrorCode = CLIENT_GetLastError();
	LOG4CXX_INFO(logger,"m_loginId = "<<m_loginId<<"pCtrl = "<<pStaticCtrl->GetSafeHwnd()<<"nRet = "<<m_realPlayId << "dwErrorCode = " << dwErrorCode);
	if ( 0 != m_realPlayId)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CDhInterfaceImpl::StopRealPlay()
{
	BOOL bRet = CLIENT_StopRealPlay(m_realPlayId);
	if (bRet)
	{
		m_pStaticCtrl->Invalidate();
		return TRUE;
	}
	return FALSE;
}

BOOL CDhInterfaceImpl::CloudPatControl(DWORD dwCommand, DWORD dwStartEndFlag, DWORD dwSpeed)
{
	BOOL bRet = CLIENT_DHPTZControl(m_loginId,0,dwCommand,dwSpeed,dwSpeed,0,(BOOL)dwStartEndFlag);
	if (bRet)
	{
		return TRUE;
	}
	
	return FALSE;
}

BOOL CDhInterfaceImpl::CallPreset(DWORD dwPoint)
{
	return TRUE;
}

BOOL CDhInterfaceImpl::CapturePicture(LPCTSTR filePath, DWORD imageType, DWORD imageSize, DWORD imageQuality, DWORD dwChannelId)
{
	if (!m_realPlayId) return FALSE;
	
	BOOL bRet = CLIENT_CapturePicture(m_realPlayId,filePath);


	return bRet;
}

BOOL CDhInterfaceImpl::DownLoadFile(LPCTSTR srcFileName, LPCTSTR saveFileName)
{
	return TRUE;
}

BOOL CDhInterfaceImpl::PausePlayBack(DWORD dwFlag)
{
	return TRUE;
}

BOOL CDhInterfaceImpl::PlayBack(LPCTSTR fileName)
{
	return TRUE;
}

BOOL CDhInterfaceImpl::Preset(DWORD dwPoint)
{
	return TRUE;
}

BOOL CDhInterfaceImpl::StartRecord(LPCTSTR filePath, DWORD dwChannelId /* = 1 */)
{
	if (!m_realPlayId) return FALSE;
	
	BOOL bRet = CLIENT_SaveRealData(m_realPlayId, filePath);

	return bRet;
}

BOOL CDhInterfaceImpl::StopPlayBack()
{
	return TRUE;
}

BOOL CDhInterfaceImpl::StopRecord()
{
	LOG4CXX_INFO(logger,"StopRecord---->start");
	if (!m_realPlayId) return FALSE;
	
	BOOL bRet = CLIENT_StopSaveRealData(m_realPlayId);
	LOG4CXX_INFO(logger,"StopRecord---->end");
	return bRet;
}

void CALLBACK DisConnectFunc(LONG lLoginID, char *pchDVRIP, LONG nDVRPort, DWORD dwUser)
{
	if(0 != dwUser)
	{
		//网络连接已断开
		
	}
}

BOOL CDhInterfaceImpl::StartRealPlayFtp()
{	
	LOG4CXX_INFO(logger,"StartRealPlayFtp---->start");
	m_realPlayId = CLIENT_RealPlay(m_loginId,0,0);	
	
	if (!m_realPlayId)
	{
		DWORD dwErrorCode = CLIENT_GetLastError();

		LOG4CXX_INFO(logger,"m_loginId = "<<m_loginId<< "dwErrorCode = " << dwErrorCode);
		return FALSE;
	}

	LOG4CXX_INFO(logger,"StartRealPlayFtp---->end");
	
	return TRUE;
}