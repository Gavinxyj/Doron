#pragma once

// CSliderControl 对话框
class CVideoReal;
class CSliderControl : public CDialogEx
{
	DECLARE_DYNAMIC(CSliderControl)

public:
	CSliderControl(CVideoReal *pVideoCtrl, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSliderControl();

// 对话框数据
	enum { IDD = IDD_DIALOG_VIDEOPARAM };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	CVideoReal *m_pVideoCtrl;
	
};
