#include "StdAfx.h"
#include "OracelOperator.h"


COracelOperator::COracelOperator(void)
{
	m_pConn = NULL;
	m_pEnv  = NULL;
	m_mapData.clear();

	CString strPath;
	char szPath[256] = {0};

	DWORD dwCode = GetCurrentDirectory(sizeof(szPath), szPath);

	if(0 == dwCode)
	{
		DWORD dwErr = GetLastError();
		//	LOG4CXX_INFO(ftpLogger,"GetCurrentDirectory errCode:"<<dwErr);
		return ;
	}
	strPath.Format("%s\\config\\config.properties", szPath);
	
	PropertyConfigurator::configure(strPath.GetBuffer());
	logger = Logger::getLogger("debugLogger");
}


COracelOperator::~COracelOperator(void)
{
	if (NULL != m_pConn)
	{
		m_pEnv->terminateConnection(m_pConn);
	}

	if (NULL != m_pEnv)
	{
		Environment::terminateEnvironment(m_pEnv);
	}
}

void COracelOperator::ConnectionOracle()
{

	m_pEnv = Environment::createEnvironment(Environment::DEFAULT);//创建连接对象指针 

	std::string name = "doron_tomp";
	std::string pass = "doron1234";
	//std::string srvName = "192.168.102.37:1521/tomp";
	std::string srvName = "13.53.147.230:1521/dorondb";
	try
	{
		m_pConn = m_pEnv->createConnection(name, pass, srvName);	
	}
	catch(SQLException e)
	{
		LOG4CXX_ERROR(logger, "errCode = "<<(e.getErrorCode()) << "message = " << (e.getMessage()));
	}
}

void COracelOperator::queryData()
{
	Statement *pStmt = NULL;
	ResultSet *rs = NULL;
	std::string sql = "select sxjbh, sbbh from V_TDMS_CAM";
	try
	{
		if (NULL != m_pConn)
		{
			pStmt = m_pConn->createStatement(sql);//创建一个Statement对象

			rs = pStmt->executeQuery();//执行SQL语句
			if (NULL != rs)
			{			
				while (rs->next()) 
				{
					std::string sxjbh = rs->getString(1);
					std::string sbbh = rs->getString(2);
					m_mapData.insert(make_pair(sxjbh, sbbh));
					LOG4CXX_DEBUG(logger, "sxjbh ="<<(sxjbh.c_str())<<";sbbh = "<< (sbbh.c_str()));
				}
				pStmt->closeResultSet(rs);
				m_pConn->terminateStatement(pStmt);
			}
		}
	}
	catch (SQLException& e)
	{
		LOG4CXX_ERROR(logger, "errCode = "<<(e.getErrorCode()) << "message = " << (e.getMessage()));
	}
}

std::string COracelOperator::AsciiToUTF8(const char* szAnsi)
{
	if (szAnsi == NULL) return "";

	_bstr_t bstrTmp(szAnsi);
	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)bstrTmp, -1, NULL, 0, NULL, NULL);
	char *buffer = new char[nLen + 1];
	ZeroMemory(buffer, nLen + 1);
	::WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)bstrTmp, -1, buffer, nLen, NULL, NULL);
	std::string utf8_string(buffer);
	delete[] buffer;

	return utf8_string;
}

std::string COracelOperator::UTF8ToAscii(const char* szUTF8)
{
	if (szUTF8 == NULL) return "";

	int nLen = ::MultiByteToWideChar(CP_UTF8, 0, szUTF8, -1, NULL, 0);
	WCHAR *buffer = new WCHAR[nLen + 1];
	ZeroMemory(buffer, sizeof(WCHAR) * (nLen + 1));
	::MultiByteToWideChar(CP_UTF8, 0, szUTF8, -1, buffer, nLen);
	std::string ansi_string(_bstr_t((wchar_t*)buffer));
	delete[] buffer;

	return ansi_string;
}

std::string COracelOperator::httpRequest(std::string url, std::string body, int method, bool utf_8)
{
	CHttpRequire http;

	http.CreateCurl();
	http.ResetHttpReq();

	// ASCII转UTF-8
	std::string body_utf8 = utf_8 ? AsciiToUTF8(body.c_str()) : body;

	// 发送HTTP请求
	http.SetHttpOpt(url, "", "", BASIC, "", "", "", "", body_utf8, method, true, 1, -1);

	bool success = false;
	int count = 3;

	do
	{
		if (http.Http())
		{
			success = true;
			break;
		}
		count--;
	}
	while (count > 0);

	int http_code = http.GetHttpCode();
	
	std::string content = http.GetPageContent();

	if (!success || http_code != 200 || content.empty())
	{
		return "";
	}

	// UTF-8转ASCII
	return utf_8 ? UTF8ToAscii(content.c_str()) : content;
}