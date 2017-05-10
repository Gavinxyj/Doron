
// MonitorVideoStatusDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MonitorVideoStatus.h"
#include "MonitorVideoStatusDlg.h"
#include "afxdialogex.h"
#include "tmcp_interface_sdk.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMonitorVideoStatusDlg �Ի���




CMonitorVideoStatusDlg::CMonitorVideoStatusDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMonitorVideoStatusDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pOracle = new COracelOperator();
	if (NULL != m_pOracle)
	{
		m_pOracle->ConnectionOracle();
		if (NULL != m_pOracle->getConnection())
		{
			m_pOracle->queryData();
		}
	}
	bFlag = false;
	m_loginHandle = -1;
	DWORD dwThreadId = 0;
	m_hThread = NULL;
	Platform::Plat_Init();
}

void CMonitorVideoStatusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMonitorVideoStatusDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CMonitorVideoStatusDlg ��Ϣ�������

BOOL CMonitorVideoStatusDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	m_loginHandle = Platform::Plat_LoginCMS("13.53.147.200","admin", "Doron1234","8011");

	if (-1 == m_loginHandle)
	{
		int dwErrorCode = Platform::Plat_GetLastError();
		Platform::Plat_Free();
		LOG4CXX_ERROR(m_pOracle->logger,"dwErrorCode = "<<dwErrorCode);
	//	return FALSE;
	}

	DWORD dwThreadId = 0;
	m_hThread = CreateThread(NULL, 0, ThreadProc, this, 0, &dwThreadId);
	Sleep(1000);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMonitorVideoStatusDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMonitorVideoStatusDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMonitorVideoStatusDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

DWORD WINAPI CMonitorVideoStatusDlg::ThreadProc(LPVOID lpParameter)
{
	CMonitorVideoStatusDlg *pDlg = (CMonitorVideoStatusDlg*)lpParameter;
	LOG4CXX_INFO(pDlg->m_pOracle->logger,"Server start!");
	std::string url = "http://192.168.102.127:21999/com.doron.tompiservice.interfaces.http.TDMSInterfaceHttp";
	char szBody[1024] = {0};
	char szTime[64]   = {0};
	SYSTEMTIME time;
	std::string body = "{\"arguments\":[{\"sbbh\":\"%s\",\"sbzt\":\"%s\",\"ztbhsj\":\"%s\"},{\"gjjb\":\"01\",\"xxly\":\"0\",\"gzlb\":\"01\",\"fssj\":\"%s\",\"xxms\":\"\",\"gjr\":\"\",\"gjrdh\":\"\"}],\"methodName\":\"setEquipmentStatus\",\"parameterTypes\":[\"com.doron.tompiservice.model.Status\",\"com.doron.tompiservice.model.Fault\"]}";
	while (!pDlg->bFlag)
	{
		LOG4CXX_INFO(pDlg->m_pOracle->logger, "I am stayed");
		memset(szTime, 0, 64);
		memset(szBody, 0, 1024);
		GetLocalTime(&time);
		sprintf_s(	szTime, "%04d-%02d-%02d %02d-%02d-%02d",
				    time.wYear,
					time.wMonth,
					time.wDay,
					time.wHour,
					time.wMinute,
					time.wSecond);

		pDlg->CheckPoint();
		std::map<char*, int>::iterator iter = pDlg->m_mapStatus.begin();
		for (;iter != pDlg->m_mapStatus.end(); iter ++)
		{
			LOG4CXX_DEBUG(pDlg->m_pOracle->logger, "VideoId = " << iter->first << "status = " << iter->second);
			std::map<std::string, std::string>::iterator findit = pDlg->m_pOracle->m_mapData.find(iter->first);
			
			if (findit != pDlg->m_pOracle->m_mapData.end())
			{
				sprintf_s(szBody, body.c_str(), iter->first, iter->second, szTime, szTime);
				std::string response = pDlg->m_pOracle->httpRequest(url, szBody, REQ_POST, 1);

				if (response == "")
				{
					LOG4CXX_INFO(pDlg->m_pOracle->logger, "VideoId = " << iter->first << "mapId = " << findit->second);
				}
			}
		}

		Sleep(1000 * 60);
	}

	LOG4CXX_INFO(pDlg->m_pOracle->logger,"Server End!");
	return 0;
}

void CMonitorVideoStatusDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	bFlag = true;
	Sleep(1000);
	if (NULL != m_pOracle)
	{
		delete m_pOracle;
		m_pOracle = NULL;
	}

	if (NULL != m_hThread)
	{
		CloseHandle(m_hThread);
	}
	Platform::Plat_LogoutCMS(m_loginHandle);
	Platform::Plat_Free();
	CDialogEx::OnClose();
}

void CMonitorVideoStatusDlg::CheckPoint()
{
	m_mapStatus.clear();

	if (-1 != m_loginHandle)
	{
		if (Platform::Plat_QueryResource(3,m_loginHandle) == 0)
		{
			do
			{
				char * szId = Platform::Plat_GetValueStr(Camera::camera_id, m_loginHandle);
				long currentState = -1;			
				Platform::Plat_GetResourceState(szId, 0, &currentState, m_loginHandle);			
				m_mapStatus.insert(std::make_pair(szId, currentState));
			}while (Platform::Plat_MoveNext(m_loginHandle) != -1);
		}
	}
	
}