
// MonitorVideoStatusDlg.h : ͷ�ļ�
//

#pragma once
#include "OracelOperator.h"
#include <vector>
#include <map>
// CMonitorVideoStatusDlg �Ի���
class CMonitorVideoStatusDlg : public CDialogEx
{
// ����
public:
	CMonitorVideoStatusDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MONITORVIDEOSTATUS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
	static DWORD WINAPI ThreadProc(LPVOID lpParameter);
	void CheckPoint();
private:
	COracelOperator *m_pOracle;
	HANDLE	m_hThread;
	std::map<char*, int>m_mapStatus;
	int m_loginHandle;
	bool bFlag;
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
};
