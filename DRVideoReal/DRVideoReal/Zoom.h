#pragma once


// CZoom 对话框
class CVideoReal;
class CZoom : public CDialogEx
{
	DECLARE_DYNAMIC(CZoom)

public:
	CZoom(CVideoReal *pVideoCtrl, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CZoom();

// 对话框数据
	enum { IDD = IDD_DIALOG_ZOOM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
private:
	CVideoReal *m_pVideoCtrl;

public:
	afx_msg void OnClose();
};
