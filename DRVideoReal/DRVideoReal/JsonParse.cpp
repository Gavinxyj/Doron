#include "StdAfx.h"
#include "JsonParse.h"
#include "ItemMgr.h"
#include <stdlib.h>

CJsonParse* CJsonParse::m_pInstance = NULL;

CJsonParse::CJsonParse(void)
{
	m_pItemData		= NULL;
	m_pConnInfo		= NULL;
	m_pDownloadInfo = NULL;
	m_pTalkInfo		= NULL;
	PropertyConfigurator::configure("C:\\DriverAdaptor\\config.properties");
	logger = Logger::getLogger("debugLogger");
	
}


CJsonParse::~CJsonParse(void)
{
	if (NULL != m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}

	if (NULL != m_pConnInfo)
	{
		delete m_pConnInfo;
		m_pConnInfo = NULL;
	}

	if (NULL != m_pDownloadInfo)
	{
		delete m_pDownloadInfo;
		m_pDownloadInfo = NULL;
	}

	CString strKey = _T("");
	PCONNECTINFO pConn = NULL;
	POSITION pos = m_mapConnInfo.GetStartPosition(); 
	while(pos) 
	{ 
		m_mapConnInfo.GetNextAssoc(pos,strKey,pConn);
		
		if ( NULL != pConn)
		{
			
			delete pConn;
			pConn = NULL;
		}
	} 
	m_mapConnInfo.RemoveAll();
}

CJsonParse* CJsonParse::getInstance()
{
	if (NULL == m_pInstance)
	{
		m_pInstance = new CJsonParse();
	}
	return m_pInstance;
}
bool CJsonParse::parseJsonStr(const char* strJson)
{
	Json::Reader reader;
	Json::Value  root;
	
	if (NULL != m_pItemData)
	{
		delete m_pItemData;
		m_pItemData = NULL;
	}

	m_pItemData = new ITEMDATA();
	bool bRet = reader.parse(strJson, root);

	if (!bRet) return false;
	
	try
	{
		if (!root["templateList"].isNull())
		{
			//获取templateList节点数据
			Json::Value values = root["templateList"];
			char temp[8] = {0};
			for (unsigned int nLoop = 0; nLoop < values.size(); nLoop ++)
			{
				PTEMPLATELIST pTempList = new TEMPLATELIST();


				memset(temp, 0, 8);
				itoa(values[nLoop]["ch"].asInt(), temp, 10);
				strncpy_s(pTempList->ch, temp, 1);

				Json::Value switchs = values[nLoop]["switchs"];
				
				for (unsigned int index = 0; index < switchs.size(); index ++)
				{
					PSWITCHS pSwitchs = new SWITCHS();
					std::string objId = switchs[index]["objId"].asString();			
					strncpy_s(pSwitchs->objId, objId.c_str(), objId.length());
					LOG4CXX_DEBUG(logger, "pSwitchs->objId = "<< pSwitchs->objId);

					std::string templateId = switchs[index]["template_id"].asString();
					strncpy_s(pSwitchs->template_id, templateId.c_str(), templateId.length());
					LOG4CXX_DEBUG(logger, "pSwitchs->template_id = "<< pSwitchs->template_id);

					Json::Value switchTimes = switchs[index]["switch_times"];
					for (unsigned int indexTimes = 0; indexTimes < switchTimes.size(); indexTimes ++)
					{
						PSWITCH_TIMES pSwitchTimes = new SWITCH_TIMES();

						//结束时间
						std::string end = switchTimes[indexTimes]["end"].asString();
						strncpy_s(pSwitchTimes->end, end.c_str(), end.length());
						LOG4CXX_DEBUG(logger, "pSwitchTimes->end = "<< pSwitchTimes->end);

						//objId
						std::string timesObjId = switchTimes[indexTimes]["objId"].asString();
						strncpy_s(pSwitchTimes->objId, timesObjId.c_str(), timesObjId.length());
						LOG4CXX_DEBUG(logger, "pSwitchTimes->objId = "<< pSwitchTimes->objId);

						//开始时间
						std::string start = switchTimes[indexTimes]["start"].asString();
						strncpy_s(pSwitchTimes->strat, start.c_str(), start.length());
						LOG4CXX_DEBUG(logger, "pSwitchTimes->strat = "<< pSwitchTimes->strat);

						Json::Value cameraSwitch = switchTimes[indexTimes]["camera_switch"];
					//	if (!cameraSwitch.isNull())
						{
							for (int cameraIndex = 0; cameraIndex < cameraSwitch.size(); cameraIndex ++)
							{
								PCAMERA_SWITCH pCameraSwitch = new CAMERA_SWITCH();

								//caption
								std::string caption = cameraSwitch[cameraIndex]["caption"].asString();
								strncpy_s(pCameraSwitch->caption, caption.c_str(), caption.length());
								LOG4CXX_DEBUG(logger, "pCameraSwitch->caption = "<< pCameraSwitch->caption);

								//ch
								memset(temp, 0, 8);
								itoa(cameraSwitch[cameraIndex]["ch"].asInt(), temp, 10);
								strncpy_s(pCameraSwitch->ch, temp, 1);
								LOG4CXX_DEBUG(logger,"pCameraSwitch->ch = " << pCameraSwitch->ch);

								//data_type
								memset(temp, 0, 8);
								itoa(cameraSwitch[cameraIndex]["data_type"].asInt(), temp, 10);
								strncpy_s(pCameraSwitch->data_type, temp, 1);
								LOG4CXX_DEBUG(logger,"pCameraSwitch->data_type = " << pCameraSwitch->data_type);

								//host_caption
								std::string host_caption = cameraSwitch[cameraIndex]["host_caption"].asString();
								strncpy_s(pCameraSwitch->host_caption, host_caption.c_str(), host_caption.length());
								LOG4CXX_DEBUG(logger,"pCameraSwitch->host_caption = " << pCameraSwitch->host_caption);

								//host_id
								std::string host_id = cameraSwitch[cameraIndex]["host_id"].asString();
								strncpy_s(pCameraSwitch->host_id, host_id.c_str(), host_id.length());
								LOG4CXX_DEBUG(logger,"pCameraSwitch->host_id = " << pCameraSwitch->host_id);

								//index
								pCameraSwitch->index = cameraSwitch[cameraIndex]["index"].asInt();
								LOG4CXX_DEBUG(logger,"pCameraSwitch->index = " << pCameraSwitch->index);

								//objid
								std::string camerObjId = cameraSwitch[cameraIndex]["objId"].asString();
								strncpy_s(pCameraSwitch->objId, camerObjId.c_str(), camerObjId.length());
								LOG4CXX_DEBUG(logger,"pCameraSwitch->objId = " << pCameraSwitch->objId);

								//sup_id
								std::string sup_id = cameraSwitch[cameraIndex]["sup_id"].asString();
								strncpy_s(pCameraSwitch->sup_id, sup_id.c_str(), sup_id.length());
								LOG4CXX_DEBUG(logger,"pCameraSwitch->sup_id = " << pCameraSwitch->sup_id);

								//time
								pCameraSwitch->time = cameraSwitch[cameraIndex]["time"].asInt();
								LOG4CXX_DEBUG(logger,"pCameraSwitch->time = " << pCameraSwitch->time);

								//client_sup_id
								std::string client_sup_id = cameraSwitch[cameraIndex]["client_sup_id"].asString();
								strncpy_s(pCameraSwitch->client_sup_id, client_sup_id.c_str(), client_sup_id.length());
								LOG4CXX_DEBUG(logger,"pCameraSwitch->client_sup_id = " << pCameraSwitch->client_sup_id);

								//client_sup_ip
								std::string client_sup_ip = cameraSwitch[cameraIndex]["client_sup_ip"].asString();
								strncpy_s(pCameraSwitch->client_sup_ip, client_sup_ip.c_str(), client_sup_ip.length());
								LOG4CXX_DEBUG(logger,"pCameraSwitch->client_sup_ip = " << pCameraSwitch->client_sup_ip);

								pCameraSwitch->client_sup_port = cameraSwitch[cameraIndex]["client_sup_port"].asInt();
								LOG4CXX_DEBUG(logger,"pCameraSwitch->client_sup_port = " << pCameraSwitch->client_sup_port);

								Json::Value cameraAuthoritys = cameraSwitch[cameraIndex]["cameraAuthoritys"];
								if (!cameraAuthoritys.isNull())
								{
									
									for (unsigned int autIndex = 0; autIndex < cameraAuthoritys.size(); autIndex ++)
									{
										memset(temp, 0, 8);
										itoa(cameraAuthoritys[autIndex].asInt(), temp, 10);
										//strncpy(pCameraSwitch->cameraAuthoritys + autIndex, temp, 1);
										strcat(pCameraSwitch->cameraAuthoritys,temp);
										strcat(pCameraSwitch->cameraAuthoritys,",");
									}
									LOG4CXX_DEBUG(logger,"pCameraSwitch->cameraAuthoritys = " << pCameraSwitch->cameraAuthoritys);
								}
								pSwitchTimes->vecCameraSwitch.push_back(pCameraSwitch);
							}
						}
						pSwitchs->vecSwitchTimes.push_back(pSwitchTimes);
					}
					pTempList->vecSwitchs.push_back(pSwitchs);
				}
				m_pItemData->vecTemplateList.push_back(pTempList);
			}
		}
		if (!root["buttons"].isNull())
		{
			//获取buttons节点
			Json::Value btns = root["buttons"];
			int nLen = btns.size();

			char temp[8] = {0};

			for (int nLoop = 0; nLoop < nLen; nLoop ++)
			{
				memset(temp, 0, 8);
				itoa(btns[nLoop].asInt(), temp, 10);
				//strncpy(m_pItemData->buttons + nLoop, temp, 1);		
				strcat(m_pItemData->buttons, temp);
				strcat(m_pItemData->buttons, ",");
			}

			LOG4CXX_DEBUG(logger,"buttons = "<<m_pItemData->buttons);
		}

		if (!root["menus"].isNull())
		{
			//获取menus节点
			Json::Value menus = root["menus"];
			int nLen = menus.size();

			char temp[8] = {0};

			for (int nLoop = 0; nLoop < nLen; nLoop ++)
			{
				memset(temp, 0, 8);
				itoa(menus[nLoop].asInt(), temp, 10);
				strcat(m_pItemData->menus, temp);
				strcat(m_pItemData->menus, ",");
			}
			LOG4CXX_DEBUG(logger,"menus = "<<m_pItemData->buttons);
		}

		if (!root["OcxType"].isNull())
		{
			m_pItemData->ocxType = root["OcxType"].asInt();
			LOG4CXX_DEBUG(logger,"m_pItemData->ocxType = "<<m_pItemData->ocxType);

		}

		if (!root["username"].isNull())
		{
			std::string ocxType = root["username"].asString();
			strncpy(m_pItemData->username, ocxType.c_str(), ocxType.length());
			LOG4CXX_DEBUG(logger,"m_pItemData->username = "<<m_pItemData->username);
		}

		if (!root["password"].isNull())
		{
			std::string password = root["password"].asString();
			strncpy(m_pItemData->password, password.c_str(), password.length());
			LOG4CXX_DEBUG(logger,"m_pItemData->password = "<<m_pItemData->password);
		}

		if (!root["client_sup_ip"].isNull())
		{
			std::string client_sup_ip = root["client_sup_ip"].asString();
			strncpy(m_pItemData->client_sup_ip, client_sup_ip.c_str(), client_sup_ip.length());
			LOG4CXX_DEBUG(logger,"m_pItemData->client_sup_ip = "<<m_pItemData->client_sup_ip);
		}


		if (!root["client_sup_id"].isNull())
		{
			std::string client_sup_id = root["client_sup_id"].asString();
			strncpy(m_pItemData->client_sup_id, client_sup_id.c_str(), client_sup_id.length());
			LOG4CXX_DEBUG(logger,"m_pItemData->client_sup_id = "<<m_pItemData->client_sup_id);
		}

		if (!root["client_sup_port"].isNull())
		{
			m_pItemData->client_sup_port = root["client_sup_port"].asInt();
			LOG4CXX_DEBUG(logger,"m_pItemData->client_sup_port = "<<m_pItemData->client_sup_port);

		}

		if (!root["userLevel"].isNull())
		{
			m_pItemData->userLevel = root["userLevel"].asInt();
			LOG4CXX_DEBUG(logger,"m_pItemData->userLevel = "<<m_pItemData->userLevel);

		}

		PDISKPLANINFO pDiskInfo = new DISKPLANINFO();
		if (!root["diskplaninfo"].isNull())
		{
			//获取diskplaninfo节点
			Json::Value diskInfo = root["diskplaninfo"];			

			char temp[8] = {0};

			itoa(diskInfo["diskpolicytype"].asInt(), temp, 10);
			strncpy(pDiskInfo->diskpolicytype, temp, 1);

			memset(temp, 0, 8);
			itoa(diskInfo["diskdeltype"].asInt(), temp, 10);
			strncpy(pDiskInfo->diskdeltype, temp, 2);

			Json::Value diskList = diskInfo["disklist"];
			int nLen = diskInfo.size();
			for (int nLoop = 0; nLoop < nLen; nLoop ++)
			{
				strncpy(pDiskInfo->diskList + nLoop, diskList[nLoop].asString().c_str(), 1);
			}

			LOG4CXX_DEBUG(logger, "diskpolicytype = " << pDiskInfo->diskpolicytype << "; diskdeltype = "<< pDiskInfo->diskdeltype << "; disklist = "<< pDiskInfo->diskList);
			m_pItemData->pDiskPlanInfo = pDiskInfo;
		}

		
		POTHERINFO pOtherInfo = new OTHERINFO();
		if (!root["otherinfo"].isNull())
		{
			//获取diskplaninfo节点
			Json::Value otherInfo = root["otherinfo"];			

			char temp[8] = {0};

			itoa(otherInfo["packtime"].asInt(), temp, 10);
			strcat(pOtherInfo->packtime, temp);

			std::string capturepath = otherInfo["capturepath"].asString();
			strncpy(pOtherInfo->capturepath, capturepath.c_str(), capturepath.length());

			std::string downloadpath = otherInfo["downloadpath"].asString();
			strncpy(pOtherInfo->downloadpath, downloadpath.c_str(), downloadpath.length());

			LOG4CXX_DEBUG(logger, "packtime = " << pOtherInfo->packtime << "; capturepath = "<< pOtherInfo->capturepath << "; downloadpath = "<< pOtherInfo->downloadpath);
			m_pItemData->pOtherInfo = pOtherInfo;
		}

		PSCREENINFO pScreenInfo = new SCREENINFO;
		
		if (!root["screen"].isNull())
		{
			Json::Value screenInfo = root["screen"];

			pScreenInfo->x = screenInfo["x"].asInt();
			pScreenInfo->y = screenInfo["y"].asInt();
			pScreenInfo->z = screenInfo["z"].asInt();
		}
	}
	catch (...)
	{
		LOG4CXX_ERROR(logger, "json字符串解析异常");
	}
	
	return true;
}

bool CJsonParse::parseJsonConnInfo(const char* strJson)
{

	Json::Reader reader;
	Json::Value  root;

	if (NULL != m_pConnInfo)
	{
		delete m_pConnInfo;
		m_pConnInfo = NULL;
	}

	m_pConnInfo = new CONNECTINFO();

	bool bRet = reader.parse(strJson, root);

	if (!bRet) return false;

	if (!root["devId"].isNull())
	{
		std::string devId = root["devId"].asString();
		strncpy_s(m_pConnInfo->devId, devId.c_str(), devId.length());
		LOG4CXX_DEBUG(logger, "m_pConnInfo->devId = "<<m_pConnInfo->devId);
	}

	if (!root["objId"].isNull())
	{
		std::string objId = root["objId"].asString();
		strncpy_s(m_pConnInfo->objId, objId.c_str(), objId.length());
		LOG4CXX_DEBUG(logger, "m_pConnInfo->objId = "<<m_pConnInfo->objId);
	}

	if (!root["username"].isNull())
	{
		std::string username = root["username"].asString();
		strncpy_s(m_pConnInfo->username, username.c_str(), username.length());
		LOG4CXX_DEBUG(logger, "m_pConnInfo->username = "<<m_pConnInfo->username);
	}

	if (!root["password"].isNull())
	{
		std::string password = root["password"].asString();
		strncpy_s(m_pConnInfo->password, password.c_str(), password.length());
		LOG4CXX_DEBUG(logger, "m_pConnInfo->password = "<<m_pConnInfo->password);
	}

	if (!root["clientMsId"].isNull())
	{
		std::string clientMsId = root["clientMsId"].asString();
		strncpy_s(m_pConnInfo->clientMsId, clientMsId.c_str(), clientMsId.length());
		LOG4CXX_DEBUG(logger, "m_pConnInfo->clientMsId = "<<m_pConnInfo->clientMsId);
	}

	if (!root["clientMsIp"].isNull())
	{
		std::string clientMsIp = root["clientMsIp"].asString();
		strncpy_s(m_pConnInfo->clientMsIp, clientMsIp.c_str(), clientMsIp.length());
		LOG4CXX_DEBUG(logger, "m_pConnInfo->clientMsIp = "<<m_pConnInfo->clientMsIp);
	}

	if (!root["clientMsPort"].isNull())
	{
		int clientMsPort = root["clientMsPort"].asInt();
		m_pConnInfo->clientMsPort = clientMsPort;
		LOG4CXX_DEBUG(logger, "m_pConnInfo->clientMsPort = "<<m_pConnInfo->clientMsPort);
	}

	if (!root["devMsId"].isNull())
	{
		std::string devMsId = root["devMsId"].asString();
		strncpy_s(m_pConnInfo->devMsId, devMsId.c_str(), devMsId.length());
		LOG4CXX_DEBUG(logger, "m_pConnInfo->devMsId = "<<m_pConnInfo->devMsId);
	}

	if (!root["channel"].isNull())
	{
		int channel = root["channel"].asInt();
		m_pConnInfo->channel = channel;
		LOG4CXX_DEBUG(logger, "m_pConnInfo->channel = "<<m_pConnInfo->channel);
	}

	if (!root["dataType"].isNull())
	{
		int dataType = root["dataType"].asInt();
		m_pConnInfo->dataType = dataType;
		LOG4CXX_DEBUG(logger, "m_pConnInfo->dataType = "<<m_pConnInfo->dataType);
	}

	if (!root["hostCaption"].isNull())
	{
		std::string hostCaption = root["hostCaption"].asString();
		strncpy_s(m_pConnInfo->hostCaption, hostCaption.c_str(), hostCaption.length());
		LOG4CXX_DEBUG(logger, "m_pConnInfo->hostCaption = "<<m_pConnInfo->hostCaption);
	}

	if (!root["videoEnable"].isNull())
	{
		int videoEnable = root["videoEnable"].asInt();
		m_pConnInfo->videoEnable = videoEnable;
		LOG4CXX_DEBUG(logger, "m_pConnInfo->videoEnable = "<<m_pConnInfo->videoEnable);
	}

	if (!root["switchTime"].isNull())
	{
		int switchTime = root["switchTime"].asInt();
		m_pConnInfo->switchTime = switchTime;
		LOG4CXX_DEBUG(logger, "m_pConnInfo->switchTime = "<<m_pConnInfo->switchTime);
	}

	if (!root["caption"].isNull())
	{
		std::string caption = root["caption"].asString();
		strncpy_s(m_pConnInfo->caption, caption.c_str(), caption.length());
		LOG4CXX_DEBUG(logger, "m_pConnInfo->caption = "<<m_pConnInfo->caption);
	}

	if (!root["isAlarm"].isNull())
	{
		int isAlarm = root["isAlarm"].asInt();
		m_pConnInfo->isAlarm = isAlarm;
		LOG4CXX_DEBUG(logger, "m_pConnInfo->isAlarm = "<<m_pConnInfo->isAlarm);
	}

	if (!root["alarmMsg"].isNull())
	{
		std::string alarmMsg = root["alarmMsg"].asString();
		strncpy_s(m_pConnInfo->alarmMsg, alarmMsg.c_str(), alarmMsg.length());
		LOG4CXX_DEBUG(logger, "m_pConnInfo->alarmMsg = "<<m_pConnInfo->alarmMsg);
	}

	if (!root["isAudio"].isNull())
	{
		int isAudio = root["isAudio"].asInt();
		m_pConnInfo->isAudio = isAudio;
		LOG4CXX_DEBUG(logger, "m_pConnInfo->isAudio = "<<m_pConnInfo->isAudio);
	}

	if (!root["authority"].isNull())
	{

		Json::Value authority = root["authority"];
		int nLen = authority.size();

		char temp[8] = {0};

		for (int nLoop = 0; nLoop < nLen; nLoop ++)
		{
			memset(temp, 0, 8);
			itoa(authority[nLoop].asInt(), temp, 10);
			strcat(m_pConnInfo->authority, temp);
			strcat(m_pConnInfo->authority, ",");
		}
		LOG4CXX_DEBUG(logger,"m_pConnInfo->authority = "<<m_pConnInfo->authority);
	}
	
	if (!root["actionPlanType"].isNull())
	{
		int actionPlanType = root["actionPlanType"].asInt();
		m_pConnInfo->actionPlanType = actionPlanType;
		LOG4CXX_DEBUG(logger, "m_pConnInfo->actionPlanType = "<<m_pConnInfo->actionPlanType);
	}

	if (!root["manualMenu"].isNull())
	{
		int manualMenu = root["manualMenu"].asInt();
		m_pConnInfo->manualMenu = manualMenu;
		LOG4CXX_DEBUG(logger, "m_pConnInfo->manualMenu = "<<m_pConnInfo->manualMenu);
	}

	if (!root["hostName"].isNull())
	{
		std::string hostName = root["hostName"].asString();
		strncpy_s(m_pConnInfo->hostName, hostName.c_str(), hostName.length());
		LOG4CXX_DEBUG(logger, "m_pConnInfo->hostName = "<<m_pConnInfo->hostName);
	}

	PCONNECTINFO infoTemp = NULL;
	if (!m_mapConnInfo.Lookup(m_pConnInfo->devId,infoTemp))
	{
		if (NULL != m_pConnInfo)
		{
			m_mapConnInfo.SetAt(m_pConnInfo->devId, m_pConnInfo);
		}
	}
	return true;
}

bool CJsonParse::parseJsonDownloadInfo(const char* strInfo)
{
	Json::Reader reader;
	Json::Value  root;	

	if (NULL != m_pDownloadInfo)
	{
		delete m_pDownloadInfo;
		m_pDownloadInfo = NULL;
	}

	bool bRet = reader.parse(strInfo, root);

	if (!bRet) return false;

	if (!root["devId"].isNull())
	{
		std::string devId = root["devId"].asString();
		strncpy_s(m_pDownloadInfo->devId, devId.c_str(), devId.length());
		LOG4CXX_DEBUG(logger, "m_pDownloadInfo->devId = "<<m_pDownloadInfo->devId);
	}

	if (!root["username"].isNull())
	{
		std::string username = root["username"].asString();
		strncpy_s(m_pDownloadInfo->username, username.c_str(), username.length());
		LOG4CXX_DEBUG(logger, "m_pDownloadInfo->username = "<<m_pDownloadInfo->username);
	}

	if (!root["password"].isNull())
	{
		std::string password = root["password"].asString();
		strncpy_s(m_pDownloadInfo->password, password.c_str(), password.length());
		LOG4CXX_DEBUG(logger, "m_pDownloadInfo->password = "<<m_pDownloadInfo->password);
	}

	if (!root["clientMsId"].isNull())
	{
		std::string clientMsId = root["clientMsId"].asString();
		strncpy_s(m_pConnInfo->clientMsId, clientMsId.c_str(), clientMsId.length());
		LOG4CXX_DEBUG(logger, "m_pConnInfo->clientMsId = "<<m_pConnInfo->clientMsId);
	}

	if (!root["clientMsIp"].isNull())
	{
		std::string clientMsIp = root["clientMsIp"].asString();
		strncpy_s(m_pDownloadInfo->clientMsIp, clientMsIp.c_str(), clientMsIp.length());
		LOG4CXX_DEBUG(logger, "m_pDownloadInfo->clientMsIp = "<<m_pDownloadInfo->clientMsIp);
	}

	if (!root["clientMsPort"].isNull())
	{
		int clientMsPort = root["clientMsPort"].asInt();
		m_pDownloadInfo->clientMsPort = clientMsPort;
		LOG4CXX_DEBUG(logger, "m_pDownloadInfo->clientMsPort = "<<m_pDownloadInfo->clientMsPort);
	}

	if (!root["caption"].isNull())
	{
		std::string caption = root["caption"].asString();
		strncpy_s(m_pDownloadInfo->caption, caption.c_str(), caption.length());
		LOG4CXX_DEBUG(logger, "m_pDownloadInfo->caption = "<<m_pDownloadInfo->caption);
	}

	if (!root["hostName"].isNull())
	{
		std::string hostName = root["hostName"].asString();
		strncpy_s(m_pDownloadInfo->hostName, hostName.c_str(), hostName.length());
		LOG4CXX_DEBUG(logger, "m_pDownloadInfo->hostName = "<<m_pDownloadInfo->hostName);
	}

	if (!root["playType"].isNull())
	{
		int playType = root["playType"].asInt();
		m_pDownloadInfo->playType = playType;
		LOG4CXX_DEBUG(logger, "m_pDownloadInfo->playType = "<<m_pDownloadInfo->playType);
	}

	if (!root["moduleS"].isNull())
	{
		std::string moduleS = root["moduleS"].asString();
		strncpy_s(m_pDownloadInfo->hostName, moduleS.c_str(), moduleS.length());
		LOG4CXX_DEBUG(logger, "m_pDownloadInfo->moduleS = "<<m_pDownloadInfo->moduleS);
	}

	ClientFileInfo *pFileInfo = new ClientFileInfo();
	ZeroMemory(pFileInfo, sizeof(ClientFileInfo));
	if (!root["fileInfo"].isNull())
	{
		//获取diskplaninfo节点
		Json::Value fileInfo = root["fileInfo"];	

		if (!fileInfo["channel"].isNull())
		{
			int channel = root["channel"].asInt();
			pFileInfo->ch = channel;
			LOG4CXX_DEBUG(logger, "pFileInfo->ch = "<<pFileInfo->ch);
		}

		if (!fileInfo["fileName"].isNull())
		{
			std::string filename = root["fileName"].asString();
			strncpy_s(pFileInfo->filename, filename.c_str(), filename.length());
			LOG4CXX_DEBUG(logger, "pFileInfo->filename = "<<pFileInfo->filename);
		}

		if (!fileInfo["size"].isNull())
		{
			int size = root["size"].asInt();
			pFileInfo->size = size;
			LOG4CXX_DEBUG(logger, "pFileInfo->size = "<<pFileInfo->size);
		}
/*

		if (!fileInfo["startTime"].isNull())
		{
			std::string startTime = root["startTime"].asString();
			
			strncpy_s(pFileInfo->startTime, startTime.c_str(), startTime.length());
			LOG4CXX_DEBUG(logger, "pFileInfo->startTime = "<<pFileInfo->startTime);
		}

		if (!fileInfo["endTime"].isNull())
		{
			std::string endTime = root["endTime"].asString();
			strncpy_s(pFileInfo->endTime, endTime.c_str(), endTime.length());
			LOG4CXX_DEBUG(logger, "pFileInfo->endTime = "<<pFileInfo->endTime);
		}*/

		if (!fileInfo["driveNo"].isNull())
		{
			int driveno = root["driveNo"].asInt();
			pFileInfo->driveno = driveno;
			LOG4CXX_DEBUG(logger, "pFileInfo->driveno = "<<pFileInfo->driveno);
		}

		if (!fileInfo["startCluster"].isNull())
		{
			int startcluster = root["startCluster"].asInt();
			pFileInfo->startcluster = startcluster;
			LOG4CXX_DEBUG(logger, "pFileInfo->startcluster = "<<pFileInfo->startcluster);
		}

		if (!fileInfo["fileType"].isNull())
		{
			int filetype = root["fileType"].asInt();
			pFileInfo->filetype = filetype;
			LOG4CXX_DEBUG(logger, "pFileInfo->filetype = "<<pFileInfo->filetype);
		}

		if (!fileInfo["pbtData"].isNull())
		{
			std::string pbtData = root["pbtData"].asString();
			strncpy_s(pFileInfo->pbtData, pbtData.c_str(), pbtData.length());
			LOG4CXX_DEBUG(logger, "pFileInfo->pbtData = "<<pFileInfo->pbtData);
		}

		/*if (!fileInfo["devId"].isNull())
		{
			std::string devId = root["devId"].asString();
			strncpy_s(m_pDownloadInfo->devId, devId.c_str(), devId.length());
			LOG4CXX_DEBUG(logger, "m_pDownloadInfo->devId = "<<m_pDownloadInfo->devId);
		}
*/

		m_pDownloadInfo->pFileInfo = pFileInfo;
	}

	return true;
}

bool CJsonParse::parseJsonDiskInfo(const char * strJson, DISKPLANINFO *pDiskInfo, OTHERINFO *pOtherInfo)
{
	if (NULL == pDiskInfo || NULL == pOtherInfo) return false;
	
	Json::Reader reader;
	Json::Value  root;	

	bool bRet = reader.parse(strJson, root);

	if (!bRet) return false;

	if (!root["diskplaninfo"].isNull())
	{
		//获取diskplaninfo节点
		Json::Value diskInfo = root["diskplaninfo"];			

		char temp[8] = {0};

		itoa(diskInfo["diskpolicytype"].asInt(), temp, 10);
		strncpy(pDiskInfo->diskpolicytype, temp, 1);

		memset(temp, 0, 8);
		itoa(diskInfo["diskdeltype"].asInt(), temp, 10);
		strncpy(pDiskInfo->diskdeltype, temp, 2);

		Json::Value diskList = diskInfo["disklist"];
		int nLen = diskInfo.size();
		for (int nLoop = 0; nLoop < nLen; nLoop ++)
		{
			strncpy(pDiskInfo->diskList + nLoop, diskList[nLoop].asString().c_str(), 1);
		}

		LOG4CXX_DEBUG(logger, "diskpolicytype = " << pDiskInfo->diskpolicytype << "; diskdeltype = "<< pDiskInfo->diskdeltype << "; disklist = "<< pDiskInfo->diskList);
	}

	if (!root["otherinfo"].isNull())
	{
		//获取diskplaninfo节点
		Json::Value otherInfo = root["otherinfo"];			

		char temp[8] = {0};

		itoa(otherInfo["packtime"].asInt(), temp, 10);
		strcat(pOtherInfo->packtime, temp);

		std::string capturepath = otherInfo["capturepath"].asString();
		strncpy(pOtherInfo->capturepath, capturepath.c_str(), capturepath.length());

		std::string downloadpath = otherInfo["downloadpath"].asString();
		strncpy(pOtherInfo->downloadpath, downloadpath.c_str(), downloadpath.length());

		LOG4CXX_DEBUG(logger, "packtime = " << pOtherInfo->packtime << "; capturepath = "<< pOtherInfo->capturepath << "; downloadpath = "<< pOtherInfo->downloadpath);
	}

	return true;
}

bool CJsonParse::parseJsonTalkInfo(const char * strJson)
{
	Json::Reader reader;
	Json::Value  root;	

	bool bRet = reader.parse(strJson, root);

	if (!bRet) return false;

	if (NULL != m_pTalkInfo)
	{
		delete m_pTalkInfo;
		m_pTalkInfo = NULL;
	}

	m_pTalkInfo = new TALKINFO();

	if (!root["devId"].isNull())
	{
		std::string devId = root["devId"].asString();
		strncpy_s(m_pTalkInfo->devId, devId.c_str(), devId.length());
		LOG4CXX_DEBUG(logger, "m_pTalkInfo->devId = "<<m_pTalkInfo->devId);
	}

	if (!root["username"].isNull())
	{
		std::string username = root["username"].asString();
		strncpy_s(m_pTalkInfo->username, username.c_str(), username.length());
		LOG4CXX_DEBUG(logger, "m_pTalkInfo->username = "<<m_pTalkInfo->username);
	}

	if (!root["password"].isNull())
	{
		std::string password = root["password"].asString();
		strncpy_s(m_pTalkInfo->password, password.c_str(), password.length());
		LOG4CXX_DEBUG(logger, "m_pTalkInfo->password = "<<m_pTalkInfo->password);
	}

	if (!root["clientMsId"].isNull())
	{
		std::string clientMsId = root["clientMsId"].asString();
		strncpy_s(m_pTalkInfo->clientMsId, clientMsId.c_str(), clientMsId.length());
		LOG4CXX_DEBUG(logger, "m_pTalkInfo->clientMsId = "<<m_pTalkInfo->clientMsId);
	}

	if (!root["clientMsIp"].isNull())
	{
		std::string clientMsIp = root["clientMsIp"].asString();
		strncpy_s(m_pTalkInfo->clientMsIp, clientMsIp.c_str(), clientMsIp.length());
		LOG4CXX_DEBUG(logger, "m_pTalkInfo->clientMsIp = "<<m_pTalkInfo->clientMsIp);
	}

	if (!root["clientMsPort"].isNull())
	{
		int clientMsPort = root["clientMsPort"].asInt();
		m_pTalkInfo->clientMsPort = clientMsPort;
		LOG4CXX_DEBUG(logger, "m_pTalkInfo->clientMsPort = "<<m_pTalkInfo->clientMsPort);
	}

	if (!root["devMsId"].isNull())
	{
		std::string devMsId = root["devMsId"].asString();
		strncpy_s(m_pTalkInfo->devMsId, devMsId.c_str(), devMsId.length());
		LOG4CXX_DEBUG(logger, "m_pTalkInfo->devMsId = "<<m_pTalkInfo->devMsId);
	}

	return true;
}