#pragma once
#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>
#include "json/json.h"
#include "ItemMgr.h"
using namespace log4cxx;

class CJsonParse
{
private:
	CJsonParse(void);
	
private:	
	static CJsonParse* m_pInstance;
public:
	~CJsonParse(void);
public:
	PITEMDATA m_pItemData;
	PCONNECTINFO m_pConnInfo;
	PDOWNLOADINFO m_pDownloadInfo;
	PTALKINFO m_pTalkInfo;
	LoggerPtr logger;
	static CJsonParse* getInstance();
	CMap<CString,LPCTSTR,PCONNECTINFO,PCONNECTINFO>m_mapConnInfo;
public:
	bool parseJsonStr(const char* strJson);
	bool parseJsonConnInfo(const char* strJson);
	bool parseJsonDownloadInfo(const char* strInfo);
	bool parseJsonDiskInfo(const char * strJson, DISKPLANINFO *pDiskInfo, OTHERINFO *pOtherInfo);
	bool parseJsonTalkInfo(const char * strJson);
};

