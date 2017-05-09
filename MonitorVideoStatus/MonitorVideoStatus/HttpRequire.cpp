#include "HttpRequire.h"
#include <list>
#include <algorithm>

#if defined(_DEBUG)
#pragma comment (lib, "libcurld.lib")
#else
#pragma comment (lib, "libcurl.lib")
#endif
#pragma comment (lib, "ws2_32.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "wldap32.lib")

#define _USE_FIDDLER_PROXY  0

CHttpRequire::CHttpRequire()
{
    // input arguments
    m_strUrl = "";
    m_strHttpHead = "";
    m_strCookieStr = "";
    m_nAuthMethod = BASIC;
    m_strUser = "";
    m_strPwd = "";
    m_strServerIp = "";
    m_strCheckStr = "";
    m_strPostStr = "";
    m_bCheckWay = false;
    m_nRepeatTime = 0;
    m_nRequireMethod = REQ_GET;
    m_nChkRedircount = -1;
    m_nMaxRedircount = RELOCATE_LEVEL;
    m_nTimeout = TRANSFER_TIMEOUT;

    // output
    m_nHttpRetCode = -1;
    m_dRespondTime = -1;
    m_dDnsParseTime = -1;
    m_dDownSpeed = -1;
    m_dConnectTime = -1;
    m_dDnsParseTime = -1;
    m_dAppCounnectTime = 0;
    m_dPretransferTime = -1;
    m_dStartTransferTime = -1;
    m_dTotalTime = -1;
    m_dRedirectTime = -1;
    m_nRedirectCount = 0;
    m_nRetCode = RC_ERROR_RUN;
    m_strEffectiveUrl = "";
    m_strRedirectUrl = "";

    // usage
    m_strPageContent = "";
    m_strRetHead = "";
    m_strDomain = "";

    m_lProtoList.push_back("http");
    m_lProtoList.push_back("https");

    m_mapForm.clear();

    m_pCurl = NULL;
}

CHttpRequire::~CHttpRequire()
{
    CleanupCurl();
}

int progress(void* clientp, double dltotal, double dlnow, double ultotal, double ulnow)
{
    return 0;
}

bool CHttpRequire::InitCurl(CURL * curl, const std::string & strUrl, int nReqWay, curl_slist *& http_headers)
{
    CURLcode cRet = CURLE_OK;
    //set url
    printf("-------------url:%s\n", strUrl.c_str());
    m_strDomain = GetDomain(strUrl);


    //set head
    //curl_slist * http_headers = NULL;
    GetHttpHead(http_headers);

    //get url
    std::string tstrUrl = GetUrl(strUrl);

    printf("------------httpurl: %s\n", tstrUrl.c_str());

    cRet = curl_easy_setopt(curl, CURLOPT_URL, tstrUrl.c_str());

    if (cRet != CURLE_OK)
    {
        printf("Set curl option failed: CURLOPT_URL: %d\n", cRet);
        return false;
    }

    cRet = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, http_headers);

    if (cRet != CURLE_OK)
    {
        printf("Set curl option failed: CURLOPT_HTTPHEADER: %d\n", cRet);
        return false;
    }


    //set request way
    switch (nReqWay)
    {
        case REQ_GET:
            break;

        case REQ_FORMPOST_NAME:
            {
                curl_httppost *post = NULL;
                curl_httppost *last = NULL;

                curl_formadd(&post, &last, CURLFORM_COPYNAME, "name", CURLFORM_FILECONTENT, m_strPostStr.c_str(), CURLFORM_END);
                curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
                break;
            }

        case REQ_FORMPOST_FILE:
            {
                curl_httppost *post = NULL;
                curl_httppost *last = NULL;

                curl_formadd(&post, &last, CURLFORM_COPYNAME, "file", CURLFORM_FILECONTENT, m_strPostStr.c_str(), CURLFORM_END);
                curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
                break;
            }

        case REQ_FORMPOST_MULTIPART_FORMDATA:
            {
#if _DEBUG && _USE_FIDDLER_PROXY
                curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
                curl_easy_setopt(curl, CURLOPT_PROXY, "127.0.0.1:8888"); // 设置FIDDLER的本地代理
#endif

                curl_httppost *post = NULL;
                curl_httppost *last = NULL;

                HttpFormDataMap::iterator iter;

                for (iter = m_mapForm.begin(); iter != m_mapForm.end(); ++iter)
                {
                    curl_formadd(&post, &last, CURLFORM_PTRNAME, iter->first.c_str(), CURLFORM_PTRCONTENTS, iter->second.c_str(), CURLFORM_CONTENTSLENGTH, iter->second.length(), CURLFORM_END);
                }

                curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);

                if (cRet != CURLE_OK)
                {
                    printf("Set curl option failed: CURLOPT_HTTPPOST: %d\n", cRet);
                    return false;
                }

                //curl_formfree(post);
                break;
            }

        case REQ_POST:
        case REQ_PUT:
        case REQ_DELETE:
            {
                if (!m_strPostStr.empty())
                {
                    cRet = curl_easy_setopt(curl, CURLOPT_POSTFIELDS, m_strPostStr.c_str());

                    if (cRet != CURLE_OK)
                    {
                        printf("Set curl option failed: CURLOPT_POSTFIELDS: %d\n", cRet);
                        return false;
                    }

                    cRet = curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, m_strPostStr.length());

                    if (cRet != CURLE_OK)
                    {
                        printf("Set curl option failed: CURLOPT_POSTFIELDSIZE: %d\n", cRet);
                        return false;
                    }
                }

                if (nReqWay == REQ_PUT)
                {
                    cRet = curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");

                    if (cRet != CURLE_OK)
                    {
                        printf("Set curl option failed: CURLOPT_PUT: %d\n", cRet);
                        return false;
                    }

                    break;
                }
                else if (nReqWay == REQ_DELETE)
                {
                    cRet = curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");

                    if (cRet != CURLE_OK)
                    {
                        printf("Set curl option failed: CURLOPT_PUT: %d\n", cRet);
                        return false;
                    }

                    break;
                }

                break;
            }

        case REQ_HEAD:
            {
                cRet = curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "HEAD");

                if (cRet != CURLE_OK)
                {
                    printf("Set curl option failed: CURLOPT_CUSTOMREQUEST: %d\n", cRet);
                    return false;
                }

                cRet = curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);

                if (cRet != CURLE_OK)
                {
                    printf("Set curl option failed: CURLOPT_NOBODY: %d\n", cRet);
                    return false;
                }

                break;
            }

        default:
            ;
    }

    // set http auth
    if (m_strUser != "" && m_strPwd != "")
    {
        std::string strUP = m_strUser + ":";
        strUP += m_strPwd;
        cRet = curl_easy_setopt(curl, CURLOPT_USERPWD, strUP.c_str());

        if (cRet != CURLE_OK)
        {
            printf("Set curl option failed: CURLOPT_USERPWD: %d\n", cRet);
            return false;
        }

        cRet = curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);

        if (cRet != CURLE_OK)
        {
            printf("Set curl option failed: CURLOPT_HTTPAUTH: %d\n", cRet);
            return false;
        }
    }

    // set cookie
    if (m_strCookieStr != "")
    {
        if (m_strCookieStr[m_strCookieStr.length() - 1] != ';')
            m_strCookieStr += ';';

        cRet = curl_easy_setopt(curl, CURLOPT_COOKIE, m_strCookieStr.c_str());

        if (cRet != CURLE_OK)
        {
            printf("Set curl option failed: CURLOPT_COOKIE: %d\n", cRet);
            return false;
        }
    }

    // set ssl
    cRet = curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

    if (cRet != CURLE_OK)
    {
        printf("Set curl option failed: CURLOPT_SSL_VERIFYPEER: %d\n", cRet);
        return false;
    }

    cRet = curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    if (cRet != CURLE_OK)
    {
        printf("Set curl option failed: CURLOPT_SSL_VERIFYHOST: %d\n", cRet);
        return false;
    }

    //curl_easy_setopt(curl,CURLOPT_CAINFO,Nas::GetProcessPath("/cert/pc-calist.pem").c_str());
    //curl_easy_setopt(curl,CURLOPT_SSLCERT,Nas::GetProcessPath("/cert/pc-cert.pem").c_str());
    ////curl_easy_setopt(curl,CURLOPT_SSLCERTPASSWD,"password");
    //curl_easy_setopt(curl,CURLOPT_SSLCERTTYPE,"PEM");
    //curl_easy_setopt(curl,CURLOPT_SSLKEY,Nas::GetProcessPath("/cert/pc-privkey.pem").c_str());
    ////curl_easy_setopt(curl,CURLOPT_SSLKEYPASSWD,"password");
    //curl_easy_setopt(curl,CURLOPT_SSLKEYTYPE,"PEM");

    //set time out
    cRet = curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, HTTP_TIMEOUT);

    if (cRet != CURLE_OK)
    {
        printf("Set curl option failed: CURLOPT_CONNECTTIMEOUT: %d\n", cRet);
        return false;
    }

    cRet = curl_easy_setopt(curl, CURLOPT_TIMEOUT, m_nTimeout);

    if (cRet != CURLE_OK)
    {
        printf("Set curl option failed: CURLOPT_TIMEOUT: %d\n", cRet);
        return false;
    }

    // set redirecte
    cRet = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    if (cRet != CURLE_OK)
    {
        printf("Set curl option failed: CURLOPT_FOLLOWLOCATION: %d\n", cRet);
        return false;
    }

    cRet = curl_easy_setopt(curl, CURLOPT_MAXREDIRS, m_nMaxRedircount);

    if (cRet != CURLE_OK)
    {
        printf("Set curl option failed: CURLOPT_MAXREDIRS: %d\n", cRet);
        return false;
    }

    // set data process function and buffer
    m_strPageContent.clear();
    m_strRetHead.clear();
    cRet = curl_easy_setopt(curl, CURLOPT_WRITEDATA, &m_strPageContent);

    if (cRet != CURLE_OK)
    {
        printf("Set curl option failed: CURLOPT_WRITEDATA: %d\n", cRet);
        return false;
    }

    cRet = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, LoadHttpContent);

    if (cRet != CURLE_OK)
    {
        printf("Set curl option failed: CURLOPT_WRITEFUNCTION: %d\n", cRet);
        return false;
    }

    cRet = curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, LoadHttpHead);

    if (cRet != CURLE_OK)
    {
        printf("Set curl option failed: CURLOPT_HEADERFUNCTION: %d\n", cRet);
        return false;
    }

    cRet = curl_easy_setopt(curl, CURLOPT_WRITEHEADER, &m_strRetHead);

    if (cRet != CURLE_OK)
    {
        printf("Set curl option failed: CURLOPT_WRITEHEADER: %d\n", cRet);
        return false;
    }

    cRet = curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);

    if (cRet != CURLE_OK)
    {
        printf("Set curl option failed: CURLOPT_NOPROGRESS: %d\n", cRet);
        return false;
    }

    /*指定显示进度的回调函数   */
    curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progress);

    cRet = curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);

    if (cRet != CURLE_OK)
    {
        printf("Set curl option failed: CURLOPT_NOSIGNAL: %d\n", cRet);
        return false;
    }

    //debug
    //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    //curl_easy_setopt(curl, CURLOPT_IGNORE_CONTENT_LENGTH, 1L);
    return true;
}

bool CHttpRequire::Http()
{
    curl_slist * http_headers = NULL;
    m_nRetCode = RC_OK;
    InitCurl(m_pCurl, m_strUrl, m_nRequireMethod, http_headers);
	
    if (!CheckProto(m_strUrlProto))
    {
        return false;
    }
    //printf("log: initial curl  %s finished\n",m_strUrl.c_str());
	
    bool bRet = HttpRequire(m_pCurl);
    int nTime = m_nRepeatTime;
	
    while (!bRet && nTime > 0)
    {
        bRet = HttpRequire(m_pCurl);
        nTime--;
#ifdef _LINUX
        usleep(50);
#else
        Sleep(50);
#endif
    }

    m_mapForm.clear();

    curl_slist_free_all(http_headers);
    //curl_global_cleanup();
	printf("Htpp =%d\n",bRet);
    return bRet;
}

bool CHttpRequire::HttpRequire(CURL * curl)
{
    //printf("log: httprequire %s\n",m_strUrl.c_str());
    //    if(m_strServerIp == "")
    //        return false;
    CURLcode ret = CURLE_OK;
    printf("--------------------start perform\n");
    ret = curl_easy_perform(curl);
    printf("---------------------mid preform\n");

    if (ret != CURLE_OK)
    {
        switch (ret)
        {
            case CURLE_COULDNT_CONNECT:
                {
                    printf("ERROR:TimeOut can't connect to the host.\n");
                    m_nRetCode = RC_ERROR_TIMEOUT;
                    break;
                }

            case CURLE_HTTP_RETURNED_ERROR:
                {
                    printf("ERROR:HTTP return false.");
                    m_nRetCode = RC_ERROR_HTTPFALSE;
                    break;
                }

            case CURLE_SSL_ENGINE_INITFAILED:
                {
                    printf("ERROR:SSL can't be initialized.");
                    m_nRetCode = RC_ERROR_INITCURLFAILED;
                    break;
                }

            case CURLE_COULDNT_RESOLVE_HOST:
                {
                    printf("ERROR:Couldn't resolve host.");
                    m_nRetCode = RC_ERROR_RESOLVE_HOST;
                    break;
                }

            case CURLE_TOO_MANY_REDIRECTS:
                {
                    printf("ERROR:locate too deep.");
                    m_nRetCode = RC_ERROR_LOCATE_TOODEEP;
                    break;
                }

            default:
                {
                    printf("ERROR:correspond failed.");
                    m_nRetCode = RC_ERROR_REQ;
                }
        }
    }

    printf("--------------------end perform\n");

    //printf("log: httprequire %s finished\n",m_strUrl.c_str());
    //get return code

    if (m_nRetCode != RC_OK && m_nRetCode != RC_ERROR_LOCATE_TOODEEP)
        return false;

    int code = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &m_nHttpRetCode);

    if (code != CURLE_OK)
    {
        m_nHttpRetCode = 0;

        if (m_nRetCode == RC_OK)
        {
            m_nRetCode = RC_ERROR_OPT_INFO;
        }
    }

    code = curl_easy_getinfo(curl, CURLINFO_NAMELOOKUP_TIME, &m_dDnsParseTime);

    if (code != CURLE_OK)
    {
        m_dDnsParseTime = -1;

        if (m_nRetCode == RC_OK)
        {
            m_nRetCode = RC_ERROR_OPT_INFO;
        }
    }

    code = curl_easy_getinfo(curl, CURLINFO_CONNECT_TIME, &m_dConnectTime);

    if (code != CURLE_OK)
    {
        m_dRespondTime = -1;

        if (m_nRetCode == RC_OK)
        {
            m_nRetCode = RC_ERROR_OPT_INFO;
        }
    }

    //    code = curl_easy_getinfo(curl, CURLINFO_APPCONNECT_TIME, &m_dAppCounnectTime);
    //    if (code != CURLE_OK)
    //    {
    //        m_dAppCounnectTime = -1;
    //        if(m_nRetCode == RC_OK)
    //        {
    //            m_nRetCode = RC_ERROR_OPT_INFO;
    //        }
    //    }

    code = curl_easy_getinfo(curl, CURLINFO_PRETRANSFER_TIME, &m_dPretransferTime);

    if (code != CURLE_OK)
    {
        m_dPretransferTime = -1;

        if (m_nRetCode == RC_OK)
        {
            m_nRetCode = RC_ERROR_OPT_INFO;
        }
    }

    code = curl_easy_getinfo(curl, CURLINFO_STARTTRANSFER_TIME, &m_dStartTransferTime);

    if (code != CURLE_OK)
    {
        m_dStartTransferTime = -1;

        if (m_nRetCode == RC_OK)
        {
            m_nRetCode = RC_ERROR_OPT_INFO;
        }
    }

    code = curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &m_dTotalTime);

    if (code != CURLE_OK)
    {
        m_dTotalTime = -1;

        if (m_nRetCode == RC_OK)
        {
            m_nRetCode = RC_ERROR_OPT_INFO;
        }
    }

    code = curl_easy_getinfo(curl, CURLINFO_REDIRECT_TIME, &m_dRedirectTime);

    if (code != CURLE_OK)
    {
        m_dRedirectTime = -1;

        if (m_nRetCode == RC_OK)
        {
            m_nRetCode = RC_ERROR_OPT_INFO;
        }
    }

    code = curl_easy_getinfo(curl, CURLINFO_SPEED_DOWNLOAD, &m_dDownSpeed);

    if (code != CURLE_OK)
    {
        m_dDownSpeed = -1;

        if (m_nRetCode == RC_OK)
        {
            m_nRetCode = RC_ERROR_OPT_INFO;
        }
    }

    code = curl_easy_getinfo(curl, CURLINFO_REDIRECT_COUNT, &m_nRedirectCount);

    if (code != CURLE_OK)
    {
        m_nRedirectCount = 0;

        if (m_nRetCode == RC_OK)
        {
            m_nRetCode = RC_ERROR_OPT_INFO;
        }
    }

    char * cServerIp = NULL;
    code = curl_easy_getinfo(curl, CURLINFO_PRIMARY_IP, &cServerIp);

    if (code != CURLE_OK)
    {
        m_strServerIp = "";

        if (m_nRetCode == RC_OK)
        {
            m_nRetCode = RC_ERROR_OPT_INFO;
        }
    }
    else
    {
        if (strlen(cServerIp) != 0)
            m_strServerIp = cServerIp;
    }

    char * cEffectiveURL = NULL;
    code = curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &cEffectiveURL);

    if (code != CURLE_OK)
    {
        m_strEffectiveUrl = "";

        if (m_nRetCode == RC_OK)
        {
            m_nRetCode = RC_ERROR_OPT_INFO;
        }
    }
    else
    {
        if (cEffectiveURL != NULL)
            m_strEffectiveUrl = cEffectiveURL;
    }

    char * cRedirectURL = NULL;
    code = curl_easy_getinfo(curl, CURLINFO_REDIRECT_URL, &cRedirectURL);

    if (code != CURLE_OK)
    {
        m_strRedirectUrl = "";

        if (m_nRetCode == RC_OK)
        {
            m_nRetCode = RC_ERROR_OPT_INFO;
        }
    }
    else
    {
        if (cRedirectURL != NULL)
            m_strRedirectUrl = cRedirectURL;
    }


    if (m_nChkRedircount != -1 && m_nChkRedircount != m_nRedirectCount)
    {
        if (m_nRetCode == RC_OK)
        {
            m_nRetCode = RC_ERROR_REDIRCOUNT_CHK_FAILED;
        }
    }

    if (m_dDnsParseTime != -1 && m_dConnectTime != -1)
    {
        m_dConnectTime -= m_dDnsParseTime;
    }

    if (m_dTotalTime != -1 && m_dRedirectTime != -1)
    {
        m_dRespondTime = m_dTotalTime + m_dRedirectTime;
    }

    if (m_nRetCode != RC_OK)
        return false;

    bool bRet = CheckHttpContent(m_strPageContent);

    if (!bRet)
        m_nRetCode = RC_ERROR_CHECKCONTENT_FAILED;

    return true;
}

size_t CHttpRequire::LoadHttpHead(void *buffer, size_t size, size_t nmemb, void *stream)
{
    std::string * strHead = (std::string *)stream;
    strHead->append((char *)buffer, size * nmemb);
    printf("%s\n", (char*)buffer);
    return size * nmemb;
}

size_t CHttpRequire::LoadHttpContent(void *buffer, size_t size, size_t nmemb, char *userp)
{
    size_t segsize = size * nmemb;
    std::string * strContent = (std::string *)userp;
    strContent->append((char *)buffer, segsize);
    /* return the number of bytes received, indicating to curl that all is okay */
    //printf("%s",buffer);
    return segsize;
}

void CHttpRequire::GetHttpHead(curl_slist* &http_headers)
{
    int spos = 0, epos = 0;

    while (epos != m_strHttpHead.length() - 1)
    {
        epos = static_cast<int>(m_strHttpHead.find("\r\n", spos));

        if (epos <= 0)
        {
            break;
        }

        std::string strItem = m_strHttpHead.substr(spos, epos - spos);
        http_headers = curl_slist_append(http_headers, strItem.c_str());
        spos = epos + 2;
    }

    if (spos < static_cast<int>(m_strHttpHead.length() - 1) && spos > 0)
    {
        std::string strLast = m_strHttpHead.substr(spos, m_strHttpHead.length() - spos - 1);
        http_headers = curl_slist_append(http_headers, strLast.c_str());
    }

    if (m_strServerIp != "")
    {
        std::string strHost = "Host: " + m_strDomain;
        printf("Host: %s\n", strHost.c_str());
        http_headers = curl_slist_append(http_headers, strHost.c_str());
    }

    http_headers = curl_slist_append(http_headers, "User-Agent: Mozilla/5.0");
}

std::string CHttpRequire::GetDomain(const std::string &strUrl)
{
    if (strUrl == "")
    {
        return "";
    }

    //modify get domain function
    int spos = static_cast<int>(strUrl.find("://"));

    if (spos < 0)
    {
        return "";
    }

    m_strUrlProto = strUrl.substr(0, spos);
    printf("-------------url:%s-------------\n", strUrl.c_str());
    spos = spos + 3;
    int epos = static_cast<int>(strUrl.find("/", spos));
    std::string strDomain = "";

    if (epos < 0)
    {
        strDomain = strUrl.substr(spos);
    }
    else
        strDomain = strUrl.substr(spos, epos - spos);

    return strDomain;
}

std::string CHttpRequire::GetUrl(const std::string& strUrl)
{
    std::string retUrl = strUrl;

    if (m_strServerIp != "")
    {
        retUrl = m_strUrlProto + "://" + m_strServerIp;
        int spos = strUrl.find("/", m_strUrlProto.length() + 3);
        retUrl += strUrl.substr(spos);
    }

    return retUrl;
}

bool CHttpRequire::CheckHttpContent(const std::string& strPageContent)
{
    if (m_strCheckStr == "")
        return true;

    int pos = static_cast<int>(strPageContent.find(m_strCheckStr));

    if ((m_bCheckWay && pos < 0) || (!m_bCheckWay && pos >= 0))
    {
        return false;
    }
    else
        return true;
}

bool CHttpRequire::CheckProto(const std::string& strProto)
{
    std::list<std::string>::iterator it = m_lProtoList.begin();
    std::string lowStr = strProto;
    std::transform(lowStr.begin(), lowStr.end(), lowStr.begin(), ::tolower);

    for (; it != m_lProtoList.end(); it++)
    {
        if (lowStr == *it)
        {
            return true;
        }
    }

    return false;
}

bool CHttpRequire::CreateCurl()
{
    if (m_pCurl == NULL)
    {
        m_pCurl = curl_easy_init();

        if (!m_pCurl)
        {
            printf("HttpRequire: initial easy curl failed!\n");
            return false;
        }
    }

    return true;
}

bool CHttpRequire::CleanupCurl()
{
    if (m_pCurl)
    {
        curl_easy_cleanup(m_pCurl);
        m_pCurl = NULL;
    }

    return true;
}

bool CHttpRequire::ResetHttpReq()
{
    m_strUrl = "";
    m_strHttpHead = "";
    m_strCookieStr = "";
    m_nAuthMethod = BASIC;
    m_strUser = "";
    m_strPwd = "";
    m_strServerIp = "";
    m_strCheckStr = "";
    m_strPostStr = "";
    m_bCheckWay = false;
    m_nRepeatTime = 0;
    m_nRequireMethod = REQ_GET;
    m_nChkRedircount = -1;
    m_nMaxRedircount = RELOCATE_LEVEL;
    m_nTimeout = TRANSFER_TIMEOUT;

    //output
    m_nHttpRetCode = -1;
    m_dRespondTime = -1;
    m_dDnsParseTime = -1;
    m_dDownSpeed = -1;
    m_dConnectTime = -1;
    m_dDnsParseTime = -1;
    m_dAppCounnectTime = 0;
    m_dPretransferTime = -1;
    m_dStartTransferTime = -1;
    m_dTotalTime = -1;
    m_dRedirectTime = -1;
    m_nRedirectCount = 0;
    m_nRetCode = RC_ERROR_RUN;
    m_strEffectiveUrl = "";
    m_strRedirectUrl = "";

    //usage
    m_strPageContent = "";
    m_strRetHead = "";
    m_strDomain = "";

    curl_easy_reset(m_pCurl);
    return true;
}

