#pragma once
#include <iostream>
#include "occi.h"
#include <map>
using namespace oracle::occi;
class COracelOperator
{
public:
	COracelOperator(void);
	~COracelOperator(void);
public:
	void ConnectionOracle();
	void queryData(std::string strSql);
	std::string AsciiToUTF8(const char* szAnsi);
	std::string UTF8ToAscii(const char* szUTF8);
	std::string httpRequest(std::string url, std::string body, int method, bool utf_8);
private:
	Connection *m_pConn;
	Environment *m_pEnv;
	LoggerPtr logger;
	std::map<std::string,std::string>m_mapData;
};

