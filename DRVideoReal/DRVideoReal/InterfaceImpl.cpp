#include "StdAfx.h"
#include "InterfaceImpl.h"
#include "vs_types.h"
#include < Mmsystem.h>
#pragma comment(lib, "Winmm.lib")
CInterfaceImpl * CInterfaceImpl::m_pInterfaceImpl = NULL;

CInterfaceImpl::CInterfaceImpl(void)
{
	m_fd = -1;
}


CInterfaceImpl::~CInterfaceImpl(void)
{
	if (NULL != m_pInterfaceImpl)
	{
		delete m_pInterfaceImpl;
		m_pInterfaceImpl = NULL;
	}

	if (-1 != m_nLoginId)
	{
		dl_sdk_logout(m_nLoginId);
	}
	
}

CInterfaceImpl* CInterfaceImpl::getInitance()
{
	if (NULL == m_pInterfaceImpl)
	{
		m_pInterfaceImpl = new CInterfaceImpl();
	}
	
	return m_pInterfaceImpl;
}

bool CInterfaceImpl::LoginDev(PITEMDATA itemData)
{
	if (NULL == itemData) return false;
	
	m_nLoginId = dl_sdk_login3_by_id(	itemData->client_sup_id,
											"",
											"",
											itemData->client_sup_id,
											itemData->client_sup_id,
											itemData->client_sup_ip,
											itemData->client_sup_port,
											MODULE_MS,
											LOGIN_MS_RES_TYPE
											);

	if (-1 == m_nLoginId) 
	{
		LOG4CXX_INFO(CJsonParse::getInstance()->logger, "��½ʧ��");
		return false;
	}

	LOG4CXX_INFO(CJsonParse::getInstance()->logger, "call LoginDev end " << m_nLoginId);
	return true;
}

bool CInterfaceImpl::InitMsSdk()
{
	if(!dl_sdk_set_max_client_num(512))
	{
		LOG4CXX_INFO(CJsonParse::getInstance()->logger, "�������������ʧ�ܣ�");
		return false;
	}
	
	if (!dl_sdk_startup())
	{
		LOG4CXX_INFO(CJsonParse::getInstance()->logger, "��ʼ��SDKʧ�ܣ�");
		return false;
	}

	char szBuff[256] = {0};

	HMODULE hModule = GetModuleHandle("DRVideoReal.ocx");

	memset(szBuff, 0, 256);
	if (hModule != NULL)
	{
		GetModuleFileName(hModule,szBuff, sizeof(szBuff));
	}

	
	CString dllPath, strTemp;
	strTemp.Format("%s", szBuff);

	dllPath.Format("%s\\win32_player_hik.dll", strTemp.Left(strTemp.ReverseFind('\\')));

	//AfxMessageBox(dllPath);
	HINSTANCE hInstance =  LoadLibraryEx(dllPath.GetBuffer(), NULL,  LOAD_WITH_ALTERED_SEARCH_PATH );
//	HINSTANCE hInstance =  LoadLibrary("C:\\Users\\LX\\Desktop\\DoronVideo\\videoOcx\\win32_player_hik.dll");

	if (NULL == hInstance)
	{
		DWORD dwError = GetLastError();
		LOG4CXX_INFO(CJsonParse::getInstance()->logger, "���ý����ʧ�ܣ� error = " << dwError);
		return false;
	}
	if (!dl_player_set_lib(VH_TYPE_HIK, dllPath.GetBuffer()))
	{
		LOG4CXX_INFO(CJsonParse::getInstance()->logger, "���ý����ʧ�ܣ�");
		return false;
	}
	
	return true;
}

bool CInterfaceImpl::Capture(LPCTSTR strPath, int nLoginId)
{	
	SYSTEMTIME sysTime;
	char fileName[256] = {0};

	GetLocalTime(&sysTime);
	Sleep(10);
	sprintf_s(	
				fileName,
				"%s%04d%02d%02d%02d%02d%02d%03d_%s.bmp",
				strPath,
				sysTime.wYear,
				sysTime.wMonth,
				sysTime.wDay,
				sysTime.wHour,
				sysTime.wMinute,
				sysTime.wSecond,
				sysTime.wMilliseconds,
				CJsonParse::getInstance()->m_pConnInfo->caption
				);

	//strncat((char*)strPath,fileName,strlen(fileName));
	
	BOOL bRet = dl_sdk_capture_bmp(nLoginId,fileName);
	
	if(!bRet) return false;

	return true;
}

bool CInterfaceImpl::PtzControl(Client_PTZ_Command *cmd, int nLoginId)
{
	
	BOOL bRet = dl_sdk_ptz_control(nLoginId, cmd);
	
	if (!bRet) return false;
	
	return true;

}

bool CInterfaceImpl::SetVideoParam(int bright, int contrast, int saturation, int hue, int nLoginId)
{
	if(	(bright < 1 || bright > 10)			|| \
		(contrast < 1 || contrast > 10)		|| \
		(saturation < 1 || saturation > 10) || \
		(hue < 1 || hue > 10) )
	{
		LOG4CXX_INFO(CJsonParse::getInstance()->logger, "SetVideoParam �������ô���");
		return false;
	}

	BOOL bRet = dl_sdk_set_video_effect(nLoginId, bright, contrast, saturation, hue);

	if (!bRet) return false;
	
	return true;
}

bool CInterfaceImpl::OpenSound(int nLoginId)
{

	BOOL bRet = dl_sdk_open_sound(nLoginId);

	if (!bRet) return false;
	
	return true;
}

bool CInterfaceImpl::CloseSound(int nLoginId)
{
	int m_fd = 0;
	BOOL bRet = dl_sdk_close_sound(nLoginId);

	if (!bRet) return false;

	return true;
}

bool CInterfaceImpl::SetVolumn(int volumn, int nLoginId)
{
	if (volumn < 0 || volumn > 100)
	{
		LOG4CXX_INFO(CJsonParse::getInstance()->logger, "SetVolumn �������ô���");
		return false;
	}

	int m_fd = 0;
	BOOL bRet = dl_sdk_volume(nLoginId, volumn);

	if (!bRet) return false;

	return true;
}

long CInterfaceImpl::StartVideo(CONNECTINFO *connInfo)
{
	LOG4CXX_DEBUG(CJsonParse::getInstance()->logger, "connInfo->devId = " << connInfo->devId);
	LOG4CXX_DEBUG(CJsonParse::getInstance()->logger, "connInfo->username = " << connInfo->username);
	LOG4CXX_DEBUG(CJsonParse::getInstance()->logger, "connInfo->password = " << connInfo->password);
	LOG4CXX_DEBUG(CJsonParse::getInstance()->logger, "connInfo->clientMsId = " << connInfo->clientMsId);
	LOG4CXX_DEBUG(CJsonParse::getInstance()->logger, "connInfo->devMsId = " << connInfo->devMsId);
	LOG4CXX_DEBUG(CJsonParse::getInstance()->logger, "connInfo->clientMsIp = " << connInfo->clientMsIp);
	LOG4CXX_DEBUG(CJsonParse::getInstance()->logger, "connInfo->clientMsPort = " << connInfo->clientMsPort);
	LOG4CXX_DEBUG(CJsonParse::getInstance()->logger, "connInfo->info.hPlayWnd = " << connInfo->info.hPlayWnd);
	LOG4CXX_DEBUG(CJsonParse::getInstance()->logger, "connInfo->info.data_type = " << connInfo->info.data_type);
	
	m_fd = dl_sdk_realplay2_ex(connInfo->devId,
								   connInfo->username,
								   connInfo->password,
								   connInfo->clientMsId,
								   connInfo->devMsId,
								   connInfo->clientMsIp,
								   connInfo->clientMsPort,
								   &connInfo->info,
								   NULL,
								   0);


	LOG4CXX_INFO(CJsonParse::getInstance()->logger, "m_fd = " << m_fd);
	
	if (-1 == m_fd) return -1;
	
	return m_fd;
}

bool CInterfaceImpl::StopVideo(int nLoginId)
{
	BOOL bRet = dl_sdk_stop_realplay(nLoginId);

	if (!bRet) return false;

	return true;
}

bool CInterfaceImpl::StartSwitchSingle(LPCTSTR strId)
{
	return true;
}

bool CInterfaceImpl::StopSwitchTemplate()
{
	return true;
}

bool CInterfaceImpl::StartRecord(int nLoginId)
{
	BOOL bRet = dl_sdk_make_key_frame_ex(nLoginId);
	
	if (!bRet) return false;

	SYSTEMTIME time;
	GetLocalTime(&time);
	Sleep(10);
	char fileName[256] = {0};
	sprintf_s(fileName, "E:\\%04d%02d%02d%02d%02d%02d%03d.mp4", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
	
	bRet = dl_sdk_save_realdata(nLoginId,fileName);

	if (!bRet) return false;

	return true;
}

bool CInterfaceImpl::StopRecord(int nLoginId)
{
	BOOL bRet = dl_sdk_stop_save_realdata(nLoginId);

	if(!bRet) return false;


	return true;
}

bool CInterfaceImpl::StartTalk(int nTalkId)
{
	nTalkId = dl_sdk_start_nettalk( CJsonParse::getInstance()->m_pTalkInfo->devId,
									 "",
									 "",
									 CJsonParse::getInstance()->m_pTalkInfo->clientMsId,
									 CJsonParse::getInstance()->m_pTalkInfo->devMsId,
									 CJsonParse::getInstance()->m_pTalkInfo->clientMsIp,
									 CJsonParse::getInstance()->m_pTalkInfo->clientMsPort,
									 MODULE_VS,
									 true,
									 NULL,
									 0);

	if (-1 == nTalkId)
	{
		LOG4CXX_ERROR(CJsonParse::getInstance()->logger, "�Խ�����ʧ�ܣ�");
		return false;
	}
	return true;
}

bool CInterfaceImpl::StopTalk(int takkId)
{
	BOOL bRet = dl_sdk_stop_nettalk(takkId);

	if (!bRet) return false;
	return true;
}

bool CInterfaceImpl::StartSwitchTemplate()
{
	return true;
}

bool CInterfaceImpl::SetScreenStyle(int x, int y, int z)
{
	return true;
}

bool CInterfaceImpl::StartDownload(LPCTSTR strInfo)
{
	bool bRet = CJsonParse::getInstance()->parseJsonDownloadInfo(strInfo);

	if (!bRet) return false;
	
	LOG4CXX_DEBUG(CJsonParse::getInstance()->logger, "m_pDownloadInfo->playType = " << CJsonParse::getInstance()->m_pDownloadInfo->playType);
	LOG4CXX_DEBUG(CJsonParse::getInstance()->logger, "m_pDownloadInfo->pFileInfo->filename = " << CJsonParse::getInstance()->m_pDownloadInfo->pFileInfo->filename);
	LOG4CXX_DEBUG(CJsonParse::getInstance()->logger, "m_pDownloadInfo->devId = " << CJsonParse::getInstance()->m_pDownloadInfo->devId);
	LOG4CXX_DEBUG(CJsonParse::getInstance()->logger, "m_pDownloadInfo->clientMsId = " << CJsonParse::getInstance()->m_pDownloadInfo->clientMsId);
	LOG4CXX_DEBUG(CJsonParse::getInstance()->logger, "m_pDownloadInfo->devMsId = " << CJsonParse::getInstance()->m_pDownloadInfo->devMsId);
	LOG4CXX_DEBUG(CJsonParse::getInstance()->logger, "m_pDownloadInfo->pFileInfo = " << CJsonParse::getInstance()->m_pDownloadInfo->pFileInfo);
	LOG4CXX_DEBUG(CJsonParse::getInstance()->logger, "m_pDownloadInfo->clientMsIp = " << CJsonParse::getInstance()->m_pDownloadInfo->clientMsIp);
	LOG4CXX_DEBUG(CJsonParse::getInstance()->logger, "m_pDownloadInfo->clientMsPort = " << CJsonParse::getInstance()->m_pDownloadInfo->clientMsPort);
	
	if ( CJsonParse::getInstance()->m_pDownloadInfo->playType == 1 && (CJsonParse::getInstance()->m_pDownloadInfo->pFileInfo->filename[0] = '\0'))
	{
		char fileName[256] = {0};

		
		int nFd = dl_sdk_download2_by_time_ex(CJsonParse::getInstance()->m_pDownloadInfo->devId,
										"",
										"",
										CJsonParse::getInstance()->m_pDownloadInfo->clientMsId,
										CJsonParse::getInstance()->m_pDownloadInfo->devMsId,
										CJsonParse::getInstance()->m_pDownloadInfo->pFileInfo,
										fileName,
										MODULE_VOD,
										CJsonParse::getInstance()->m_pDownloadInfo->clientMsIp,
										CJsonParse::getInstance()->m_pDownloadInfo->clientMsPort);
		if (-1 == nFd) 
		{
			LOG4CXX_DEBUG(CJsonParse::getInstance()->logger, "�����ļ�ʧ�ܣ�");
			return false;
		}
	}
	else
	{
		char fileName[256] = {0};
		int nModule = (CJsonParse::getInstance()->m_pDownloadInfo->playType == 1) ? MODULE_VOD : MODULE_VS;

		int nFd = dl_sdk_download2_by_time_ex(CJsonParse::getInstance()->m_pDownloadInfo->devId,
													"",
													"",
													CJsonParse::getInstance()->m_pDownloadInfo->clientMsId,
													CJsonParse::getInstance()->m_pDownloadInfo->devMsId,
													CJsonParse::getInstance()->m_pDownloadInfo->pFileInfo,
													fileName,
													nModule,
													CJsonParse::getInstance()->m_pDownloadInfo->clientMsIp,
													CJsonParse::getInstance()->m_pDownloadInfo->clientMsPort);
		if (-1 == nFd) 
		{
			LOG4CXX_DEBUG(CJsonParse::getInstance()->logger, "�����ļ�ʧ�ܣ�");
			return false;
		}
	}
	return true;
}

bool CInterfaceImpl::StopDownload(int nFd)
{
	BOOL bRet = dl_sdk_stop_download(nFd);

	if (!bRet) return false;

	return true;
}

bool CInterfaceImpl::SetRecordPlan(LPCTSTR strInfo)
{
	DISKPLANINFO *pDiskInfo = new DISKPLANINFO;
	OTHERINFO *pOtherInfo = new OTHERINFO;

	bool bRet = CJsonParse::getInstance()->parseJsonDiskInfo(strInfo, pDiskInfo, pOtherInfo);

	delete pOtherInfo;
	delete pDiskInfo;
	pDiskInfo  = NULL;
	pOtherInfo = NULL;
	return true;
}

bool CInterfaceImpl::SetCapturePath(LPCTSTR strInfo)
{
	if (!PathIsDirectory(strInfo))
	{
		BOOL bRet = CreateDirectory(strInfo, NULL);

		if (!bRet)
		{
			DWORD dwCode = GetLastError();
			LOG4CXX_DEBUG(CJsonParse::getInstance()->logger, "����Ŀ¼ʧ�ܣ������룺 " << dwCode);
			return false;
		}
	}
	return true;
}

bool CInterfaceImpl::StopAllVideo()
{
	return true;
}

bool CInterfaceImpl::MoveNext()
{
	return true;
}

bool CInterfaceImpl::SelectFolder()
{
	return true;
}

bool CInterfaceImpl::SetDownloadPath(LPCTSTR strInfo)
{
	if (!PathIsDirectory(strInfo))
	{
		BOOL bRet = CreateDirectory(strInfo, NULL);

		if (!bRet)
		{
			DWORD dwCode = GetLastError();
			LOG4CXX_DEBUG(CJsonParse::getInstance()->logger, "����Ŀ¼ʧ�ܣ������룺 " << dwCode);
			return false;
		}
	}

	return true;
}

bool CInterfaceImpl::GetVideoParam(int nLoginId, VIDEOPARAM *pVideoParam)
{
	if (NULL == pVideoParam) return false;

	BOOL bRet = dl_sdk_get_video_effect(nLoginId, &pVideoParam->bright, &pVideoParam->contrast, &pVideoParam->saturation, &pVideoParam->hue);
	
	return bRet;
}
bool CInterfaceImpl::ReleaseRes()
{
	return true;
}

bool CInterfaceImpl::PlaySoundFile(LPCTSTR strInfo)
{
	if (NULL == strInfo) return false;
	
	BOOL bRet = PlaySound(strInfo, NULL, SND_ASYNC);

	if (!bRet) return false;
	
	return true;
}

bool CInterfaceImpl::GetCurCameraObjId()
{
	return true;
}

bool CInterfaceImpl::SetActive(int num)
{
	return true;
}

bool CInterfaceImpl::GetMonitorNum()
{
	return true;
}

bool CInterfaceImpl::SetAlarmOut(LPCTSTR strDevInfo, int status)
{
	return true;
}

bool CInterfaceImpl::GetDiskList()
{
	return true;
}

bool CInterfaceImpl::CallHardPlay(LPCTSTR strFileName, int type)
{
	return true;
}

bool CInterfaceImpl::StopSwitchSingle(int nLoginId, int nWindowId, int nTiemOut)
{
	BOOL bRet = dl_sdk_tv_stop_switch(nLoginId, nWindowId, nTiemOut);

	return bRet;
}

bool CInterfaceImpl::ZoomEnlarge(int nLoginId, HWND hWnd, RectZoom* rect_zoom, int count, OUT int* zoom_id)
{
	bool bRet = dl_sdk_add_ezoom(nLoginId, hWnd, rect_zoom, count, zoom_id);

	if (!bRet) return false;
	return true;
}

bool CInterfaceImpl::SetZoom(int nLoginId, int nZoomId, RectZoom &rectZoom)
{
	bool bRet = dl_sdk_set_ezoom(nLoginId, nZoomId, rectZoom);

	if (!bRet) return false;
	
	return true;
}

bool CInterfaceImpl::RemoveZoom(int nLoginId, int nZoomId)
{
	bool bRet = dl_sdk_remove_ezoom(m_nLoginId, nZoomId);

	if (!bRet) return false;

	return true;
}