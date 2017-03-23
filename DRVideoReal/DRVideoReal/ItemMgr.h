#pragma once
#include <vector>
#include "clientsdk_types.h"

typedef struct _WINSTYLE
{
	CRect rect;
	int   nWindowId;	//��¼��갴��ȥ�Ĵ���ID
	int   nCurWindowId; //��¼��굯���ǵĴ���ID
	_WINSTYLE()
	{
		ZeroMemory(rect, sizeof(rect));
		nWindowId    = 0;
		nCurWindowId = 0;
	}

	~_WINSTYLE()
	{
		ZeroMemory(rect, sizeof(rect));
		nWindowId    = 0;
		nCurWindowId = 0;
	}
}WINSTYLE, *PWINSTYLE;
typedef struct _TALKINFO
{
	char devId[64];			//�豸ID
	char username[32];		//�û���
	char password[32];		//����
	char clientMsId[32];	//�ͻ��˽��������ID
	char clientMsIp[32];	//�ͻ��˽��������IP
	char devMsId[32];		//�豸���������ID
	int  clientMsPort;		//�ͻ��˽���������˿�

	_TALKINFO()
	{
		memset(devId, 0, 64);
		memset(username, 0, 32);
		memset(password, 0, 32);
		memset(clientMsId, 0, 32);
		memset(clientMsIp, 0, 32);
		memset(devMsId, 0, 32);
		clientMsPort = -1;
	}

	~_TALKINFO()
	{
		memset(devId, 0, 64);
		memset(username, 0, 32);
		memset(password, 0, 32);
		memset(clientMsId, 0, 32);
		memset(clientMsIp, 0, 32);
		memset(devMsId, 0, 32);
		clientMsPort = -1;
	}
}TALKINFO, *PTALKINFO;
/*
typedef struct _FILEINFO
{
	int  channel;			//ͨ��ID
	char fileName[256];
	int  size;
	char startTime[32];
	char endTime[32];
	char driveNo[8];
	char startCluster[8];	//��ʼ�غ�
	char fileType[8];		//¼���ļ�����
	char pbtData[8];
	char devId[64];			//ǰ���豸ID

	_FILEINFO()
	{
		channel = 0;
		size	= 0;
		memset(fileName, 0, 256);
		memset(startTime, 0, 32);
		memset(endTime, 0, 32);
		memset(driveNo, 0, 8);
		memset(startCluster, 0, 8);
		memset(fileType, 0, 8);
		memset(pbtData, 0, 8);
		memset(devId, 0, 64);
	}

	~_FILEINFO()
	{
		channel = 0;
		size	= 0;
		memset(fileName, 0, 256);
		memset(startTime, 0, 32);
		memset(endTime, 0, 32);
		memset(driveNo, 0, 8);
		memset(startCluster, 0, 8);
		memset(fileType, 0, 8);
		memset(pbtData, 0, 8);
		memset(devId, 0, 64);
	}
}FILEINFO,*PFILEINFO;*/
typedef struct _DOWNLOADINFO
{
	char devId[64];			//�豸ID
	char caption[64];
	char username[32];		//�û���
	char password[32];		//����
	char clientMsId[32];		//�ͻ��˽��������ID
	char clientMsIp[32];		//�ͻ��˽��������IP
	int  clientMsPort;		//�ͻ��˽���������˿�
	char hostName[32];		//��������
	char devMsId[32];		//�豸���������ID
	int  playType;
	char moduleS[64];		//Ŀ��ģ��ID
	ClientFileInfo *pFileInfo;

	_DOWNLOADINFO()
	{
		clientMsPort	= 0;
		playType		= 0;
		memset(devId, 64, 0);
		memset(caption, 64, 0);
		memset(username, 32, 0);
		memset(password, 32, 0);
		memset(devMsId, 32, 0);
		memset(clientMsId, 32, 0);
		memset(clientMsIp, 32, 0);
		memset(hostName, 32, 0);
		memset(moduleS, 64, 0);
		pFileInfo	= NULL;
	}
	~_DOWNLOADINFO()
	{
		clientMsPort	= 0;
		playType		= 0;
		memset(devId, 64, 0);
		memset(caption, 64, 0);
		memset(username, 32, 0);
		memset(password, 32, 0);
		memset(devMsId, 32, 0);
		memset(clientMsId, 32, 0);
		memset(clientMsIp, 32, 0);
		memset(hostName, 32, 0);
		memset(moduleS, 64, 0);
		
		if (NULL != pFileInfo)
		{
			delete pFileInfo;
			pFileInfo = NULL;
		}
	}
	
}DOWNLOADINFO, *PDOWNLOADINFO;

typedef struct _CONNECTINFO
{
	char devId[64];			//�豸ID
	char objId[64];
	char username[32];		//�û���
	char password[32];		//����
	char clientMsId[32];		//�ͻ��˽��������ID
	char clientMsIp[32];		//�ͻ��˽��������IP
	int  clientMsPort;		//�ͻ��˽���������˿�
	char devMsId[32];		//�豸���������ID
	int  channel;			//ͨ��ID
	int  dataType;			//��������
	char hostCaption[32];
	int  videoEnable;
	int  switchTime;
	char caption[32];
	int  isAlarm;
	char alarmMsg[32];
	int  isAudio;
	char authority[32];
	int  actionPlanType;
	int  manualMenu;
	char hostName[32];		//��������
	int  nLoginId;
	RealPlayInfo info;
	_CONNECTINFO()
	{
		clientMsPort = -1;
		channel		 = -1;
		dataType	 = -1;
		videoEnable	 = -1;
		switchTime	 = -1;
		isAlarm	     = -1;
		isAudio		 = -1;		
		manualMenu	 = -1;
		actionPlanType = -1;
		nLoginId	 = -1;
		memset(devId, 0, 64);
		memset(objId, 0, 64);
		memset(clientMsIp, 0, 32);	
		memset(clientMsId, 0, 32);
		memset(username, 0, 32);
		memset(password, 0, 32);
		memset(devMsId, 0, 32);
		memset(hostName, 0, 32);
		memset(hostCaption, 0, 32);
		memset(caption, 0, 32);
		memset(alarmMsg, 0 ,32);
		memset(authority, 0, 32);
		ZeroMemory(&info, sizeof(RealPlayInfo));
	}
	~_CONNECTINFO()
	{
		clientMsPort = -1;
		channel		 = -1;
		dataType	 = -1;
		videoEnable	 = -1;
		switchTime	 = -1;
		isAlarm	     = -1;
		isAudio		 = -1;		
		manualMenu	 = -1;
		nLoginId	 = -1;
		actionPlanType = -1;
		memset(devId, 0, 64);
		memset(objId, 0, 64);
		memset(clientMsIp, 0, 32);	
		memset(clientMsId, 0, 32);
		memset(username, 0, 32);
		memset(password, 0, 32);
		memset(devMsId, 0, 32);
		memset(hostName, 0, 32);
		memset(hostCaption, 0, 32);
		memset(caption, 0, 32);
		memset(alarmMsg, 0 ,32);
		memset(authority, 0, 32);
		ZeroMemory(&info, sizeof(RealPlayInfo));
		ZeroMemory(&info, sizeof(RealPlayInfo));
	}
}CONNECTINFO, *PCONNECTINFO;

typedef struct _SCREENINFO
{
	int x;                      //���м���
	int y;                      //���м���
	int z;                      //������ʽ
	std::vector<std::size_t>  btninfo;   //������ť
	std::vector<std::size_t>  mniinfo;   //���Ʋ˵�

	_SCREENINFO()
	{
		x = 0;
		y = 0;
		z = 0;
		btninfo.clear();
		mniinfo.clear();
	}
	~_SCREENINFO()
	{
		x = 0;
		y = 0;
		z = 0;
		btninfo.clear();
		mniinfo.clear();
	}
}SCREENINFO, *PSCREENINFO;

typedef struct _VIDEOPARAM
{
	int bright;
	int contrast;
	int saturation;
	int hue;
	int volumn;

	_VIDEOPARAM()
	{
		bright		= 0;
		contrast	= 0;
		saturation	= 0;
		hue			= 0;
		volumn		= 0;
	}

	~_VIDEOPARAM()
	{
		bright		= 0;
		contrast	= 0;
		saturation	= 0;
		hue			= 0;
		volumn		= 0;
	}
}VIDEOPARAM, *PVIDEOPARAM;

typedef struct _OTHERINFO
{
	char packtime[16];
	char capturepath[256];
	char downloadpath[256];

	_OTHERINFO()
	{
		memset(packtime, 0, 16);
		memset(capturepath, 0, 256);
		memset(downloadpath, 0, 256);
	}

	~_OTHERINFO()
	{
		memset(packtime, 0, 16);
		memset(capturepath, 0, 256);
		memset(downloadpath, 0, 256);
	}
}OTHERINFO, *POTHERINFO;
typedef struct _DISKPLANINFO
{
	char diskpolicytype[8];
	char diskList[16];
	char diskdeltype[8];
	
	_DISKPLANINFO()
	{
		memset(diskdeltype, 0, 8);
		memset(diskpolicytype, 0, 8);
		memset(diskList, 0, 16);
	}
	~_DISKPLANINFO()
	{
		memset(diskdeltype, 0, 8);
		memset(diskpolicytype, 0, 8);
		memset(diskList, 0, 16);
	}
}DISKPLANINFO,*PDISKPLANINFO;
typedef struct _CAMERA_SWITCH
{
	//����
	char caption[32];
	//ͨ��
	char ch[8];
	//��������
	char data_type[8];
	//��������
	char host_caption[32];
	//�豸ID
	char host_id[128];
	//objId
	char objId[128];
	//�û���
	char username[32];
	//����
	char password[32];
	//�ͻ��˽��������ID
	char client_sup_id[32];
	//�豸�˽��������ID
	char sup_id[32];
	//�ͻ��˽��������ID
	char client_sup_ip[32];
	//�ͻ��˽���������˿�
	int  client_sup_port;

	char cameraAuthoritys[64];
	//�л�ʱ��
	int  time;

	int  index;

	bool videoEnable;

	_CAMERA_SWITCH()
	{
		memset(caption, 0, 32);
		memset(ch, 0, 8);
		memset(data_type, 0, 8);
		memset(host_id, 0, 128);
		memset(objId, 0, 128);
		memset(username, 0, 32);
		memset(password, 0, 32);
		memset(client_sup_id, 0, 32);
		memset(sup_id, 0, 32);
		memset(client_sup_ip, 0, 32);
		memset(cameraAuthoritys, 0, 64);
		client_sup_port = 0;
		time           = 0;
		index			= 0;
		videoEnable		= false;
	}

	~_CAMERA_SWITCH()
	{
		memset(caption, 0, 32);
		memset(ch, 0, 8);
		memset(data_type, 0, 8);
		memset(host_id, 0, 128);
		memset(objId, 0, 128);
		memset(username, 0, 32);
		memset(password, 0, 32);
		memset(client_sup_id, 0, 32);
		memset(sup_id, 0, 32);
		memset(client_sup_ip, 0, 32);
		memset(cameraAuthoritys, 0, 64);
		client_sup_port = 0;
		time           = 0;
		index			= 0;
		videoEnable		= false;
	}
}CAMERA_SWITCH, *PCAMERA_SWITCH;
typedef struct _SWITCH_TIMES
{
	char strat[32];
	char end[32];
	char objId[128];
	std::vector<PCAMERA_SWITCH> vecCameraSwitch;

	_SWITCH_TIMES()
	{
		memset(strat, 0, 32);
		memset(end, 0, 32);
		memset(objId, 0, 128);
		vecCameraSwitch.clear();
	}

	~_SWITCH_TIMES()
	{
		memset(strat, 0, 32);
		memset(end, 0, 32);
		memset(objId, 0, 128);
		if (0 != vecCameraSwitch.size())
		{
			std::vector<PCAMERA_SWITCH>::iterator iter = vecCameraSwitch.begin();
			for (; iter != vecCameraSwitch.end(); iter ++)
			{
				delete *iter;
				*iter = NULL;
			}
			vecCameraSwitch.clear();
		}
	}

}SWITCH_TIMES, *PSWITCH_TIMES;
typedef struct _SWITCHS
{
	char objId[128];
	char template_id[32];
	std::vector<PSWITCH_TIMES> vecSwitchTimes;

	_SWITCHS()
	{
		memset(objId, 0, 128);
		memset(template_id, 0, 32);
		vecSwitchTimes.clear();
	}

	~_SWITCHS()
	{
		memset(objId, 0, 128);
		memset(template_id, 0, 32);
		if (0 != vecSwitchTimes.size())
		{
			std::vector<PSWITCH_TIMES>::iterator iter = vecSwitchTimes.begin();
			for (; iter != vecSwitchTimes.end(); iter ++)
			{
				delete *iter;
				*iter = NULL;
			}
			vecSwitchTimes.clear();
		}
	}
}SWITCHS,*PSWITCHS;

typedef struct _TEMPLATELIST
{
	char ch[8];
	std::vector<PSWITCHS> vecSwitchs;

	_TEMPLATELIST()
	{
		memset(ch, 0, 8);
		vecSwitchs.clear();
	}

	~_TEMPLATELIST()
	{
		if (0 != vecSwitchs.size())
		{
			std::vector<PSWITCHS>::iterator iter = vecSwitchs.begin();
			for (; iter != vecSwitchs.end(); iter ++)
			{
				delete *iter;
				*iter = NULL;
			}
			vecSwitchs.clear();
		}
	}

}TEMPLATELIST, *PTEMPLATELIST;

typedef struct _ITEMDATA
{
	char username[128];
	char password[128];
	char  client_sup_id[32];
	char client_sup_ip[128];
	int  client_sup_port;
	int  ocxType;
	int  userLevel;
	char buttons[1024];
	char menus[1024];
	std::vector<PTEMPLATELIST>vecTemplateList;
	POTHERINFO    pOtherInfo;
	PDISKPLANINFO pDiskPlanInfo;
	PSCREENINFO   pScreenInfo;
	_ITEMDATA()
	{
		memset(username, 0, 128);
		memset(password, 0, 128);
		memset(client_sup_ip, 0, 128);
		memset(buttons, 0, 1024);
		memset(menus, 0, 1024);
		memset(client_sup_id, 0, 32);
		vecTemplateList.clear();
		pOtherInfo		= NULL;
		pDiskPlanInfo	= NULL;
		pScreenInfo		= NULL;
		client_sup_port = 0;
		ocxType         = -1;
		userLevel       = 0;
	}

    ~_ITEMDATA()
	{
		memset(username, 0, 128);
		memset(password, 0, 128);
		memset(client_sup_ip, 0, 128);
		memset(buttons, 0, 1024);
		memset(menus, 0, 1024);
		memset(client_sup_id, 0, 32);
		client_sup_port = 0;
		ocxType         = -1;
		userLevel		= 0;
		if (0 != vecTemplateList.size())
		{
			std::vector<PTEMPLATELIST>::iterator iter = vecTemplateList.begin();
			for (; iter != vecTemplateList.end(); iter ++)
			{
				delete *iter;
				*iter = NULL;
			}
			vecTemplateList.clear();
		}

		if (NULL != pDiskPlanInfo)
		{
			delete pDiskPlanInfo;
			pDiskPlanInfo = NULL;
		}

		if (NULL != pOtherInfo)
		{
			delete pOtherInfo;
			pOtherInfo = NULL;
		}

		if (NULL != pScreenInfo)
		{
			delete pScreenInfo;
			pScreenInfo = NULL;
		}
	}
}ITEMDATA, *PITEMDATA;



class CItemMgr
{
public:
	CItemMgr(void);
	~CItemMgr(void);
};
