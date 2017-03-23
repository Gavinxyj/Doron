#include "../DriverAdaptorPlatfrom/StdAfx.h"
#include "HkInterfaceImpl.h"
#include "../DriverAdaptorPlatfrom/DlgOutput.h"
#include "../DriverAdaptorPlatfrom/DriverAdaptorPlatfromCtrl.h"

LoggerPtr hkLogger;
CHkInterfaceImpl::CHkInterfaceImpl()
{
	NET_DVR_Init();
	// ��ȡ�����ļ�

	//logger = Logger::getLogger("debugLogger");
	m_lPlayHandle		= -1;
	m_TotalFrames		= 0;
	m_TotalFrames		= 0;
	m_bIsRecording		= FALSE;
	m_bIsPlaying		= FALSE;

	PropertyConfigurator::configure("C:\\DriverAdaptor\\config.properties");
	hkLogger = Logger::getLogger("debugLogger");
}
CHkInterfaceImpl::CHkInterfaceImpl(CDriverAdaptorPlatfromCtrl *pDriverCtrl ) : m_pDriverCtrl(pDriverCtrl)
{
	NET_DVR_Init();
	// ��ȡ�����ļ�
	
	//logger = Logger::getLogger("debugLogger");
	m_lPlayHandle		= -1;
	m_TotalFrames		= 0;
	m_TotalFrames		= 0;
	m_bIsRecording		= FALSE;
	m_bIsPlaying		= FALSE;
}


CHkInterfaceImpl::~CHkInterfaceImpl(void)
{
	
	NET_DVR_Cleanup();
}
/************************************************************************/
/* ��������   OpenConnection 
/* ���������� ���豸����
/* ��������� strIp:ip��ַ
			dwPort:�˿ں�
			userName:�û���
			password:����
			dwChannelId:ͨ����
   ����ֵ��   TRUE-�ɹ� FALSE-ʧ��
/************************************************************************/
BOOL CHkInterfaceImpl::OpenConnection(LPCTSTR strIp, DWORD dwPort, LPCTSTR userName, LPCTSTR password)
{
	LOG4CXX_INFO(hkLogger,"OpenConnection start");
	NET_DVR_DEVICEINFO_V30 DeviceInfo;
	ZeroMemory(&DeviceInfo, sizeof(NET_DVR_DEVICEINFO_V30));

	LONG loginId = NET_DVR_Login_V30( (char*)strIp,(WORD)dwPort,(char*)userName,(char*)password,&DeviceInfo);
	
	if(loginId == -1)
	{
		DWORD dwErrCode = NET_DVR_GetLastError();
	
		LOG4CXX_ERROR(hkLogger,"������ʧ�ܣ�������:"<<dwErrCode);
		return dwErrCode;
	}
	m_struDeviceInfo.lLoginID		= loginId;
	m_struDeviceInfo.iDeviceChanNum = DeviceInfo.byChanNum;
	m_struDeviceInfo.iIPChanNum		= DeviceInfo.byIPChanNum;
	m_struDeviceInfo.iStartChan		= DeviceInfo.byStartChan;
	m_struDeviceInfo.iIPStartChan	= DeviceInfo.byStartDChan;
	
	GetDeviceChannelInfo();
	GetDecoderCfg();

	LOG4CXX_INFO(hkLogger,"OpenConnection end");
	return TRUE;
}

/************************************************************************/
/* ��������  CloseConnection 
/* �������������豸����
/* ���������dwChannelId:ͨ����
   ����ֵ��  TRUE-�ɹ� FALSE-ʧ��
/************************************************************************/
BOOL CHkInterfaceImpl::CloseConnection()
{
	LOG4CXX_INFO(hkLogger,"CloseConnection ��ʼ");
	
	if( -1 != m_lPlayHandle )
	{
		if ( m_bIsRecording )
		{
			BOOL bRet = StopRecord();

			if (!bRet) return FALSE;
			
		}
		
		BOOL bRet = NET_DVR_StopRealPlay(m_lPlayHandle);

		if (!bRet) 
		{
			DWORD dwErrCode = NET_DVR_GetLastError();

			LOG4CXX_ERROR(hkLogger,"NET_DVR_StopRealPlay��������:"<<dwErrCode);

			return FALSE;
		}
		
		NET_DVR_Logout_V30(m_struDeviceInfo.lLoginID);
		
		ZeroMemory(&m_struDeviceInfo, sizeof(LOCAL_DEVICE_INFO));
		m_lPlayHandle	= -1;
		m_bIsRecording	= FALSE;
		m_pStaticCtrl->Invalidate();
	}

	LOG4CXX_INFO(hkLogger,"CloseConnection ����");
	return TRUE;
}

/************************************************************************/
/* ��������  StartRealPlay 
/* ������������ʼʵʱԤ��
/* ���������dwChannelId:ͨ����
   ����ֵ��  TRUE-�ɹ� FALSE-ʧ��
/************************************************************************/
BOOL CHkInterfaceImpl::StartRealPlay(CStatic *pStaticCtrl)
{
	LOG4CXX_INFO(hkLogger,"StartRealPlay start");
	m_pStaticCtrl = pStaticCtrl;
	NET_DVR_CLIENTINFO ClientInfo;
	ClientInfo.hPlayWnd     = pStaticCtrl->GetSafeHwnd();
	ClientInfo.lChannel     = 1;
	ClientInfo.lLinkMode    = 0;
	ClientInfo.sMultiCastIP = NULL;

	m_lPlayHandle = NET_DVR_RealPlay_V30(m_struDeviceInfo.lLoginID,&ClientInfo,NULL,NULL,TRUE);	
	
	if(-1 == m_lPlayHandle)
	{
		DWORD dwErrCode = NET_DVR_GetLastError();
		LOG4CXX_ERROR(hkLogger,"StartRealPlay��errorCode:"<<dwErrCode << "; loginId = " << m_struDeviceInfo.lLoginID);
		return dwErrCode;
	}
	LOG4CXX_INFO(hkLogger,"StartRealPlay end");
	m_bIsPlaying = TRUE;
	return TRUE;
}

/************************************************************************/
/* ��������  StopRealPlay 
/* ����������ֹͣʵʱԤ��
/* ���������dwChannelId:ͨ����
   ����ֵ��  TRUE-�ɹ� FALSE-ʧ��
/************************************************************************/
BOOL CHkInterfaceImpl::StopRealPlay()
{
	LOG4CXX_INFO(hkLogger,"StopRealPlay start");
	if(m_lPlayHandle != -1)
	{
		if(m_bIsRecording)  //����¼����ֹͣ
		{
			StopRecord();
		}
		BOOL bRet = NET_DVR_StopRealPlay(m_lPlayHandle);
		
		if (!bRet)
		{
			DWORD dwErrCode = NET_DVR_GetLastError();
			LOG4CXX_ERROR(hkLogger,"StopRealPlay��errorCode:"<<dwErrCode);
			return FALSE;
		}

		m_lPlayHandle=-1;
		m_bIsPlaying = FALSE;
		m_pStaticCtrl->Invalidate();
	}
	LOG4CXX_INFO(hkLogger,"StopRealPlay end");
	return TRUE;
}

/************************************************************************/
/* ��������  PlayBack 
/* �����������ط�
/* ���������fileName:�ļ���
   ����ֵ��  TRUE-�ɹ� FALSE-ʧ��
/************************************************************************/
BOOL CHkInterfaceImpl::PlayBack(LPCTSTR fileName)
{
	LOG4CXX_INFO(hkLogger,"PlayBack start");
	
	if (NULL == fileName)
	{
		LOG4CXX_ERROR(hkLogger,"�ļ���Ϊ�գ�");
		return FALSE;
	}
	
	LONG lHank = NET_DVR_PlayBackByName(m_struDeviceInfo.lLoginID, (char*)fileName, m_pStaticCtrl->GetSafeHwnd());

	if( -1 == lHank)
	{
		DWORD dwErrCode = NET_DVR_GetLastError();
		LOG4CXX_ERROR(hkLogger,"NET_DVR_PlayBackByName��errorCode:"<<dwErrCode);
		return (DWORD)dwErrCode;
	}

	 
	//��ȡ��ǰ��Ƶ�ļ�����֡������ʱ��
	BOOL bRet = FALSE;

	bRet = NET_DVR_PlayBackControl(lHank,NET_DVR_GETTOTALFRAMES,0,&m_TotalFrames);
	if( !bRet )
	{
		DWORD dwErrCode = NET_DVR_GetLastError();
		LOG4CXX_ERROR(hkLogger,"NET_DVR_PlayBackControl��errorCode:"<<dwErrCode);
		return FALSE;
	}
	
	bRet = NET_DVR_PlayBackControl(lHank,NET_DVR_GETTOTALTIME,0,&m_TotalTimes);
	if( !bRet )
	{
		DWORD dwErrCode = NET_DVR_GetLastError();
		LOG4CXX_ERROR(hkLogger,"NET_DVR_PlayBackControl��errorCode:"<<dwErrCode);
		return FALSE;
	}

	//���ò��ź�������Ҫ�������������������
	bRet = NET_DVR_PlayBackControl(lHank,NET_DVR_PLAYSTART,0,NULL);	
	if( !bRet )
	{
		DWORD dwErrCode = NET_DVR_GetLastError();
		LOG4CXX_ERROR(hkLogger,"NET_DVR_PlayBackControl��errorCode:"<<dwErrCode);
		return FALSE;
	}

	//������
	bRet = NET_DVR_PlayBackControl(lHank,NET_DVR_PLAYSTARTAUDIO,0,NULL);
	if( !bRet )
	{
		DWORD dwErrCode = NET_DVR_GetLastError();
		LOG4CXX_ERROR(hkLogger,"NET_DVR_PlayBackControl��errorCode:"<<dwErrCode);
		return FALSE;
	}
	
	m_bIsPlaying = TRUE;
	LOG4CXX_INFO(hkLogger,"PlayBack end");
	return TRUE;
}

/************************************************************************/
/* ��������  StopPlayBack 
/* ����������ֹͣ�ط�
/* �����������
   ����ֵ��  TRUE-�ɹ� FALSE-ʧ��
/************************************************************************/
BOOL CHkInterfaceImpl::StopPlayBack()
{
	LOG4CXX_INFO(hkLogger,"StopPlayBack start");
	if( m_lPlayHandle > 0 )
	{
		BOOL bRet = NET_DVR_StopPlayBack(m_lPlayHandle);
		if( !bRet )
		{
			DWORD dwErrCode = NET_DVR_GetLastError();
			LOG4CXX_ERROR(hkLogger,"NET_DVR_StopPlayBack��errorCode:"<<dwErrCode);
			return FALSE;
		}
		m_lPlayHandle = -1;

		//�ر�����
		bRet = NET_DVR_PlayBackControl(m_lPlayHandle,NET_DVR_PLAYSTOPAUDIO,0,NULL);
		if( !bRet )
		{
			DWORD dwErrCode = NET_DVR_GetLastError();
			LOG4CXX_ERROR(hkLogger,"NET_DVR_PlayBackControl��errorCode:"<<dwErrCode);
			return FALSE;
		}
	}
	LOG4CXX_INFO(hkLogger,"StopPlayBack end");
	return TRUE;
}

/************************************************************************/
/* ��������  CloudPatControl 
/* ������������̨����
/* ���������dwCommand����������
		   dwStartEndFlag����ʼֹͣ��ʶ
		   dwSpeedd:��̨�ٶ�
   ����ֵ��  TRUE-�ɹ� FALSE-ʧ��
/************************************************************************/
BOOL CHkInterfaceImpl::CloudPatControl(DWORD dwCommand, DWORD dwStartEndFlag, DWORD dwSpeed)
{
	LOG4CXX_INFO(hkLogger,"CloudPatControl start");
	if(m_lPlayHandle>=0)
	{
		BOOL bRet;
		
		if( dwSpeed >= 1)
		{
			bRet = NET_DVR_PTZControlWithSpeed(m_lPlayHandle,dwCommand,dwStartEndFlag,dwSpeed);
			if(!bRet)
			{
				DWORD dwErrCode = NET_DVR_GetLastError();
				LOG4CXX_ERROR(hkLogger,"NET_DVR_PTZControlWithSpeed��errorCode:"<<dwErrCode);
				return FALSE;
			}
		}
		else
		{
			bRet = NET_DVR_PTZControl(m_lPlayHandle,dwCommand,dwStartEndFlag);
			if(!bRet)
			{
				DWORD dwErrCode = NET_DVR_GetLastError();
				LOG4CXX_ERROR(hkLogger,"NET_DVR_PTZControl��errorCode:"<<dwErrCode);
				return FALSE;
			}
		}
	}

	LOG4CXX_INFO(hkLogger,"CloudPatControl end");
	return TRUE;
}

/************************************************************************/
/* ��������  PausePlayBack 
/* ������������ͣ�ط�
/* ���������dwFlag��1-��ͣ��0-����
		   
   ����ֵ��  TRUE-�ɹ� FALSE-ʧ��
/************************************************************************/
BOOL CHkInterfaceImpl::PausePlayBack(DWORD dwFlag)
{
	LOG4CXX_INFO(hkLogger,"PausePlayBack start");
	if( m_lPlayHandle >= 0)
	{
		//�������ٶȵ���Ϊ����״̬
		BOOL bRet = NET_DVR_PlayBackControl(m_lPlayHandle,NET_DVR_PLAYNORMAL,0,NULL);
		if(!bRet)
		{
			DWORD dwErrCode = NET_DVR_GetLastError();
			LOG4CXX_ERROR(hkLogger,"NET_DVR_PlayBackControl��errorCode:"<<dwErrCode);
			return FALSE;
		}

		if( 1 == dwFlag && m_bIsPlaying)
		{
			bRet = NET_DVR_PlayBackControl(m_lPlayHandle,NET_DVR_PLAYPAUSE,0,NULL);
			if(!bRet)
			{
				DWORD dwErrCode = NET_DVR_GetLastError();
				LOG4CXX_ERROR(hkLogger,"NET_DVR_PlayBackControl��errorCode:"<<dwErrCode);
				return FALSE;
			}

			m_bIsPlaying = FALSE;
		}
		else
		{
			bRet = NET_DVR_PlayBackControl(m_lPlayHandle,NET_DVR_PLAYRESTART,0,NULL);
			if(!bRet)
			{
				DWORD dwErrCode = NET_DVR_GetLastError();
				LOG4CXX_ERROR(hkLogger,"NET_DVR_PlayBackControl��errorCode:"<<dwErrCode);
				return FALSE;
			}

			m_bIsPlaying = TRUE;
		}
	}
	LOG4CXX_INFO(hkLogger,"PausePlayBack end");
	return TRUE;
}

BOOL CHkInterfaceImpl::DownLoadFile(LPCTSTR srcFileName, LPCTSTR saveFileName)
{
	LOG4CXX_INFO(hkLogger,"DownLoadFile start");
	
	if( NULL == srcFileName && NULL == saveFileName) return FALSE;
	
	strcat_s((char*)saveFileName, sizeof(".mp4"),".mp4");
	
	
	LONG lHand = NET_DVR_GetFileByName(m_struDeviceInfo.lLoginID,(char*)srcFileName,(char*)saveFileName);

	if(lHand >= 0)
	{
		BOOL bRet = NET_DVR_PlayBackControl(lHand, NET_DVR_PLAYSTART, 0, NULL);
	}
	else
	{
		return FALSE;
	}

	LOG4CXX_INFO(hkLogger,"DownLoadFile end");
	return TRUE;
}

/************************************************************************/
/* ��������  StartRecord 
/* ������������ʼ¼��
/* ���������dwChannelId:ͨ����
   ����ֵ��  TRUE-�ɹ� FALSE-ʧ��
/************************************************************************/
BOOL CHkInterfaceImpl::StartRecord(LPCTSTR filePath, DWORD dwChannelId)
{
	LOG4CXX_INFO(hkLogger,"StartRecord start");
	char fileName[256] = {0};
	SYSTEMTIME sysTime;
/*	GetLocalTime(&sysTime);
	sprintf_s(
				fileName,
				"%04d%02d%02d%02d%02d%02d_ch%02d.mp4",
				sysTime.wYear,
				sysTime.wMonth,
				sysTime.wDay,
				sysTime.wHour,
				sysTime.wMinute,
				sysTime.wMilliseconds,
				dwChannelId);
*/
	strncat((char*)filePath,fileName,strlen(fileName));
	
	BOOL bRet = NET_DVR_SaveRealData(m_lPlayHandle, (char*)filePath);

	if(!bRet)
	{
		DWORD dwErrCode = NET_DVR_GetLastError();
		LOG4CXX_ERROR(hkLogger,"NET_DVR_SaveRealData��errorCode:"<<dwErrCode);
		return FALSE;
	}
	LOG4CXX_INFO(hkLogger,"StartRecord end");
	return TRUE;
}

/************************************************************************/
/* ��������  StartRecord 
/* ����������ֹͣ¼��
/* ���������dwChannelId:ͨ����
   ����ֵ��  TRUE-�ɹ� FALSE-ʧ��
/************************************************************************/
BOOL CHkInterfaceImpl::StopRecord()
{
	LOG4CXX_INFO(hkLogger,"StopRecord start");
	if(-1 != m_lPlayHandle)
	{
		BOOL bRet = NET_DVR_StopSaveRealData(m_lPlayHandle);
		if(!bRet)
		{
			DWORD dwErrCode = NET_DVR_GetLastError();
			LOG4CXX_ERROR(hkLogger,"NET_DVR_StopSaveRealData��errorCode:"<<dwErrCode);
			return FALSE;
		}
		m_bIsRecording = FALSE;
		return TRUE;
	}
	LOG4CXX_INFO(hkLogger,"StopRecord end");
	return FALSE;
}

/************************************************************************/
/* ��������  CapturePicture 
/* ����������ͼƬץȡ
/* ���������imageType:ͼƬ���� 0-bmp,1-jpg
		   imageSize:ͼƬ��С
		   imageQuality:ͼƬ����
		   dwChannelId:ͨ����
   ����ֵ��  TRUE-�ɹ� FALSE-ʧ��
/************************************************************************/
BOOL CHkInterfaceImpl::CapturePicture(LPCTSTR filePath, DWORD imageType, DWORD imageSize, DWORD imageQuality, DWORD dwChannelId)
{
	LOG4CXX_INFO(hkLogger,"CapturePicture start");
	if( -1 != m_lPlayHandle)
	{
		char imageName[256] = {0};

	/*	SYSTEMTIME sysTime;
		GetLocalTime(&sysTime);
		
		if ( 0 == imageType)
		{
			sprintf_s(
						imageName,
						"%04d%02d%02d%02d%02d%02d_ch%02d.bmp",
						sysTime.wYear,
						sysTime.wMonth,
						sysTime.wDay,
						sysTime.wHour,
						sysTime.wMinute,
						sysTime.wMilliseconds,
						m_struDeviceInfo.struChanInfo[dwChannelId].iChanIndex);

			strncat((char*)filePath, imageName, strlen(imageName));
			*/
			BOOL bRet = NET_DVR_CapturePicture(m_lPlayHandle,(char*)filePath);
			
			if (!bRet)
			{
				DWORD dwErrCode = NET_DVR_GetLastError();
				LOG4CXX_ERROR(hkLogger,"NET_DVR_CapturePicture��errorCode:"<<dwErrCode);
				return FALSE;
			}
		}
		else if( 1 == imageType )
		{
		/*	sprintf_s(
						imageName,
						"%04d%02d%02d%02d%02d%02d_ch%02d.jpg",
						sysTime.wYear,
						sysTime.wMonth,
						sysTime.wDay,
						sysTime.wHour,
						sysTime.wMinute,
						sysTime.wMilliseconds,
						m_struDeviceInfo.struChanInfo[dwChannelId].iChanIndex);

			strncat((char*)filePath, imageName, strlen(imageName));*/
			//�齨jpg�ṹ
			NET_DVR_JPEGPARA JpgPara = {0};
			JpgPara.wPicSize = (WORD)imageSize;
			JpgPara.wPicQuality = (WORD)imageQuality;

			LONG lChannel = m_struDeviceInfo.struChanInfo[dwChannelId].iChanIndex;

			BOOL bRet = NET_DVR_CaptureJPEGPicture(m_struDeviceInfo.lLoginID, lChannel, &JpgPara, (char*)filePath);

			if (!bRet)
			{
				DWORD dwErrCode = NET_DVR_GetLastError();
				LOG4CXX_ERROR(hkLogger,"NET_DVR_CaptureJPEGPicture��errorCode:"<<dwErrCode);
				return (DWORD) dwErrCode;
			}
		}
	LOG4CXX_INFO(hkLogger,"CapturePicture end");
	return TRUE;
}

/************************************************************************/
/* ��������  GetDecoderCfg 
/* ������������ȡ��̨������Ϣ
/* �����������
   ����ֵ��  ��
/************************************************************************/
void CHkInterfaceImpl::GetDecoderCfg()
{
	
	NET_DVR_DECODERCFG_V30 DecoderCfg;
	DWORD  dwReturned;
	
	BOOL bRet;
	//��ȡͨ����������Ϣ
	for(int index = 0; index < MAX_CHANNUM_V30; index ++)
	{
		if(m_struDeviceInfo.struChanInfo[index].bEnable)
		{
			memset(&DecoderCfg,0,sizeof(NET_DVR_DECODERCFG_V30));
			
			bRet = NET_DVR_GetDVRConfig( 
										m_struDeviceInfo.lLoginID,
										NET_DVR_GET_DECODERCFG_V30 ,
										m_struDeviceInfo.struChanInfo[index].iChanIndex,
										&DecoderCfg,
										sizeof(NET_DVR_DECODERCFG_V30),
										&dwReturned);
			if(!bRet)
			{			
				continue;
			}

			memcpy(&m_struDeviceInfo.struChanInfo[index].struDecodercfg,&DecoderCfg,sizeof(NET_DVR_DECODERCFG_V30));
		}

	}
}

/************************************************************************/
/*��������GetDeviceChannelInfo
  ������������ȡ�豸ͨ����Ϣ
  �����������
  �����������
  ����ֵ���ɹ���0��ʧ�ܣ�1
/************************************************************************/
void CHkInterfaceImpl::GetDeviceChannelInfo()
{
	// TODO: �ڴ����ʵ�ִ���
	NET_DVR_IPPARACFG_V40 IpAccessCfg;
	memset(&IpAccessCfg,0,sizeof(IpAccessCfg));	
	DWORD  dwReturned;

	m_struDeviceInfo.bIPRet = NET_DVR_GetDVRConfig(
													m_struDeviceInfo.lLoginID,
													NET_DVR_GET_IPPARACFG_V40,
													0,
													&IpAccessCfg,
													sizeof(NET_DVR_IPPARACFG_V40),
													&dwReturned);

	
	if(!m_struDeviceInfo.bIPRet)   //��֧��ip����,9000�����豸��֧�ֽ���ģ��ͨ��
	{
		for(int index = 0; index < MAX_ANALOG_CHANNUM; index ++)
		{
			if (index < m_struDeviceInfo.iDeviceChanNum)
			{
				sprintf_s(m_struDeviceInfo.struChanInfo[index].chChanName,"camera%d",index + m_struDeviceInfo.iStartChan);
				m_struDeviceInfo.struChanInfo[index].iChanIndex = index + m_struDeviceInfo.iStartChan;  //ͨ����
				m_struDeviceInfo.struChanInfo[index].bEnable = TRUE;

			}
			else
			{
				m_struDeviceInfo.struChanInfo[index].iChanIndex = -1;
				m_struDeviceInfo.struChanInfo[index].bEnable = FALSE;
				sprintf_s(m_struDeviceInfo.struChanInfo[index].chChanName, "");	
			}
		}
	}
	else        //֧��IP���룬9000�豸
	{
		for(int index = 0; index < MAX_ANALOG_CHANNUM; index ++)  //ģ��ͨ��
		{
			if (index < m_struDeviceInfo.iDeviceChanNum)
			{
				sprintf_s(m_struDeviceInfo.struChanInfo[index].chChanName,"camera%d",index + m_struDeviceInfo.iStartChan);
				m_struDeviceInfo.struChanInfo[index].iChanIndex = index + m_struDeviceInfo.iStartChan;
				if(IpAccessCfg.byAnalogChanEnable[index])
				{
					m_struDeviceInfo.struChanInfo[index].bEnable = TRUE;
				}
				else
				{
					m_struDeviceInfo.struChanInfo[index].bEnable = FALSE;
				}

			}
			else//clear the state of other channel
			{
				m_struDeviceInfo.struChanInfo[index].iChanIndex = -1;
				m_struDeviceInfo.struChanInfo[index].bEnable = FALSE;
				sprintf_s(m_struDeviceInfo.struChanInfo[index].chChanName, "");	
			}		
		}

		//����ͨ��
		for(int index = 0; index < MAX_IP_CHANNEL; index ++)
		{
			if(IpAccessCfg.struStreamMode[index].uGetStream.struChanInfo.byEnable)  //ipͨ������
			{
				m_struDeviceInfo.struChanInfo[index + MAX_ANALOG_CHANNUM].bEnable = TRUE;
				m_struDeviceInfo.struChanInfo[index + MAX_ANALOG_CHANNUM].iChanIndex = index + IpAccessCfg.dwStartDChan;
				sprintf_s(m_struDeviceInfo.struChanInfo[index + MAX_ANALOG_CHANNUM].chChanName,"IP Camera %d",index + 1);

			}
			else
			{
				m_struDeviceInfo.struChanInfo[index + MAX_ANALOG_CHANNUM].bEnable = FALSE;
				m_struDeviceInfo.struChanInfo[index + MAX_ANALOG_CHANNUM].iChanIndex = -1;
			}
		}
	}
}

BOOL CHkInterfaceImpl::Preset(DWORD dwPoint)
{

	if (m_lPlayHandle >= 0)
	{
		if (!NET_DVR_PTZPreset(m_lPlayHandle, SET_PRESET, dwPoint))
		{
			DWORD dwErrorCode = NET_DVR_GetLastError();
			LOG4CXX_ERROR(hkLogger,"Preset��errorCode:"<<dwErrorCode);
			return FALSE;
		}
	}
	else
	{
		if(!NET_DVR_PTZPreset_Other(m_struDeviceInfo.lLoginID,m_struDeviceInfo.struChanInfo[0].iChanIndex, SET_PRESET,dwPoint))
		{
			DWORD dwErrorCode = NET_DVR_GetLastError();
			LOG4CXX_ERROR(hkLogger,"Preset��errorCode:"<<dwErrorCode);
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CHkInterfaceImpl::CallPreset(DWORD dwPoint)
{
	if (m_lPlayHandle >= 0)
	{
		if (!NET_DVR_PTZPreset(m_lPlayHandle, GOTO_PRESET, dwPoint))
		{
			DWORD dwErrorCode = NET_DVR_GetLastError();
			LOG4CXX_ERROR(hkLogger,"Preset��errorCode:"<<dwErrorCode);
			return FALSE;
		}
	}
	else
	{
		if(!NET_DVR_PTZPreset_Other(m_struDeviceInfo.lLoginID,m_struDeviceInfo.struChanInfo[0].iChanIndex, GOTO_PRESET,dwPoint))
		{
			DWORD dwErrorCode = NET_DVR_GetLastError();
			LOG4CXX_ERROR(hkLogger,"Preset��errorCode:"<<dwErrorCode);
			return FALSE;
		}
	}

	return TRUE;

}

BOOL CHkInterfaceImpl::StartRealPlayFtp()
{
	LOG4CXX_INFO(hkLogger,"StartRealPlayFtp start");
	char szBuff[256] = {0};
	NET_DVR_CLIENTINFO ClientInfo;
	ClientInfo.hPlayWnd     = (HWND)szBuff;
	ClientInfo.lChannel     = 1;
	ClientInfo.lLinkMode    = 0;
	ClientInfo.sMultiCastIP = NULL;

	m_lPlayHandle = NET_DVR_RealPlay_V30(m_struDeviceInfo.lLoginID,&ClientInfo,NULL,NULL,TRUE);	

	if(-1 == m_lPlayHandle)
	{
		DWORD dwErrCode = NET_DVR_GetLastError();
		LOG4CXX_ERROR(hkLogger,"StartRealPlayFtp��errorCode:"<<dwErrCode);
		return dwErrCode;
	}
	LOG4CXX_INFO(hkLogger,"StartRealPlayFtp end");
	m_bIsPlaying = TRUE;
	return TRUE;
}