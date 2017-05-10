
// MonitorVideoStatusDlg.h : 头文件
//

#pragma once
#include "OracelOperator.h"
#include <vector>
#include <map>
// CMonitorVideoStatusDlg 对话框
class CMonitorVideoStatusDlg : public CDialogEx
{
// 构造
public:
	CMonitorVideoStatusDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MONITORVIDEOSTATUS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
	static DWORD WINAPI ThreadProc(LPVOID lpParameter);
	void CheckPoint();
private:
	COracelOperator *m_pOracle;
	HANDLE	m_hThread;
	std::map<char*, int>m_mapStatus;
	int m_loginHandle;
	bool bFlag;
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
};
