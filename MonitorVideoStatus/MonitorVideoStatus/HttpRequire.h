#ifndef HTTPREQUIRE_H
#define HTTPREQUIRE_H

#include <string>
#include "curl/curl.h"
#include "curl/easy.h"

#include <signal.h>

#include <sys/types.h>
#include <list>

#include <setjmp.h>
#include <errno.h>
#include <map>

using namespace std;

#define HTTP_TIMEOUT 20
#define TRANSFER_TIMEOUT 300
#define RELOCATE_LEVEL 15
#define MAX_URL_LEN 65536

static void lock_callback(int mode, int type, char *file, int line)
{
    //(void)file;
    //(void)line;
    //if (mode & CRYPTO_LOCK) {
    //  pthread_mutex_lock(&(lockarray[type]));
    //}
    //else {
    //  pthread_mutex_unlock(&(lockarray[type]));
    //}
}

static unsigned long thread_id(void)
{
    //unsigned long ret;

    //ret=(unsigned long)pthread_self();
    //return(ret);
}

static void init_locks(void)
{
    //int i;

    //lockarray=(pthread_mutex_t *)OPENSSL_malloc(CRYPTO_num_locks() *
    //                                          sizeof(pthread_mutex_t));
    //for (i=0; i<CRYPTO_num_locks(); i++) {
    //  pthread_mutex_init(&(lockarray[i]),NULL);
    //}

    //CRYPTO_set_id_callback((unsigned long (*)())thread_id);
    //CRYPTO_set_locking_callback((void (*)())lock_callback);
}

static void kill_locks(void)
{
    //int i;

    //CRYPTO_set_locking_callback(NULL);
    //for (i=0; i<CRYPTO_num_locks(); i++)
    //  pthread_mutex_destroy(&(lockarray[i]));

    //OPENSSL_free(lockarray);
}

enum _HttpAuthWay
{
    BASIC = 0,
    DIGSET = 1,
    DIGSET_IE = 2,
    NTLM = 3,
};
enum _ReqWay
{
    REQ_GET = 0,
    REQ_POST = 1,
    REQ_HEAD = 2,
    REQ_PUT = 3,
    REQ_DELETE = 4,
    REQ_FORMPOST_NAME = 5,
    REQ_FORMPOST_FILE = 6,
    REQ_FORMPOST_MULTIPART_FORMDATA  = 7,
};
enum _RetCode
{
    RC_OK = 0,
    RC_ERROR_RUN,
    RC_ERROR_REQ,
    RC_ERROR_TIMEOUT,
    RC_ERROR_HTTPFALSE,
    RC_ERROR_SSLINITFAILED,
    RC_ERROR_INITCURLFAILED,
    RC_ERROR_RESOLVE_HOST,
    RC_ERROR_CHECKCONTENT_FAILED,
    RC_ERROR_LOCATE_FAILED,
    RC_ERROR_LOCATE_TOODEEP,
    RC_ERROR_HTTPCODE_FAILED,
    RC_ERROR_OPT_INFO,
    RC_ERROR_DNS_FAILED,
    RC_ERROR_REDIRCOUNT_CHK_FAILED
};

typedef map<std::string, std::string> HttpFormDataMap;

class CHttpRequire
{
private:
    // input arguments
    std::string m_strUrl;
    std::string m_strHttpHead;
    std::string m_strCookieStr;
    int m_nAuthMethod;
    std::string m_strUser;
    std::string m_strPwd;
    std::string m_strServerIp;
    std::string m_strCheckStr;
    std::string m_strPostStr;
    HttpFormDataMap m_mapForm;
    int m_nRequireMethod;
    bool m_bCheckWay;
    int m_nRepeatTime;
    int m_nChkRedircount;
    int m_nMaxRedircount;
    int m_nTimeout;

    // output
    long m_nHttpRetCode;
    double m_dRespondTime;
    double m_dDownSpeed;
    double m_dConnectTime;
    double m_dDnsParseTime;
    double m_dAppCounnectTime;
    double m_dPretransferTime;
    double m_dStartTransferTime;
    double m_dTotalTime;
    double m_dRedirectTime;
    long m_nRedirectCount;
    int m_nRetCode;
    std::string m_strEffectiveUrl;
    std::string m_strRedirectUrl;

    // usage
    std::string m_strPageContent;
    std::string m_strRetHead;
    std::string m_strDomain;
    std::string m_strUrlProto;

    std::list<std::string> m_lProtoList;

    CURL * m_pCurl;

public:
    bool CleanupCurl();
    bool CreateCurl();
    bool ResetHttpReq();

    bool CheckProto(const std::string& strProto);

    static bool InitLibcurl()
    {
        if (curl_global_init(CURL_GLOBAL_ALL) == CURLE_OK)
        {
            init_locks();
            return true;
        }

        return false;
    }

    static void CleanupLibcurl()
    {
        curl_global_cleanup();
        kill_locks();
    }

    static size_t LoadHttpHead(void *buffer, size_t size, size_t nmemb, void *stream);
    static size_t LoadHttpContent(void *buffer, size_t size, size_t nmemb, char *userp);
    void GetHttpHead(curl_slist * &http_headers);
    bool HttpRequire(CURL * curl);
    bool Http();
    bool InitCurl(CURL * curl, const std::string & strUrl, int nReqWay, curl_slist * &http_headers);
    bool CheckHttpContent(const std::string & strPageContent);
    std::string GetDomain(const std::string &strUrl);
    std::string GetUrl(const std::string & strUrl);
    void AddForm(const std::string& key, const std::string& value)
    {
        m_mapForm[key] = value;
    }
    void ClearForm()
    {
        m_mapForm.clear();
    }

    void SetHttpOpt(std::string strUrl,
                    std::string strHttpHead = "",
                    std::string strCookieStr = "",
                    int nAuthMethod = BASIC,
                    std::string strUser = "",
                    std::string strPwd = "",
                    std::string strServerIp = "",
                    std::string strCheckStr = "",
                    std::string strPostStr = "",
                    int nRequireMethod = REQ_GET,
                    bool bCheckWay = true,
                    int nRepeatTime = 1,
                    int nChkRedircount = RELOCATE_LEVEL,
                    int nTimeout = TRANSFER_TIMEOUT)
    {
        m_strUrl = strUrl;
        m_strHttpHead = strHttpHead;
        m_strCookieStr = strCookieStr;
        m_nAuthMethod = nAuthMethod;
        m_strUser = strUser;
        m_strPwd = strPwd;
        m_strServerIp = strServerIp;
        m_strCheckStr = strCheckStr;
        m_strPostStr = strPostStr;
        m_bCheckWay = bCheckWay;
        m_nRepeatTime = nRepeatTime;
        m_nRequireMethod = nRequireMethod;
        m_nChkRedircount = nChkRedircount;
        m_nTimeout = nTimeout;
    }

    // return value
    double GetRespondTime()
    {
        return m_dRespondTime;
    }
    double GetDnsParseTime()
    {
        return m_dDnsParseTime;
    }
    long GetHttpCode()
    {
        return m_nHttpRetCode;
    }
    int GetRetCode()
    {
        return m_nRetCode;
    }
    int GetRedirCount()
    {
        return m_nRedirectCount;
    }
    double GetDownspeed()
    {
        return m_dDownSpeed;
    }
    std::string GetServerIp()
    {
        return m_strServerIp;
    }
    double GetConnectServerTime()
    {
        return m_dConnectTime;
    }
    double GetRedirTime()
    {
        return m_dRedirectTime;
    }
    const std::string & GetEffectiveUrl()
    {
        return m_strEffectiveUrl;
    }
    const std::string & GetRedirectUrl()
    {
        return m_strRedirectUrl;
    }
    std::string GetPageContent()
    {
        return m_strPageContent;
    }
    std::string GetRetHeadContent()
    {
        return m_strRetHead;
    }

public:
    CHttpRequire();
    virtual ~CHttpRequire();
};

#endif    /* HTTPREQUIRE_H */

