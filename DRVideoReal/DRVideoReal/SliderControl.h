#pragma once

// CSliderControl �Ի���
class CVideoReal;
class CSliderControl : public CDialogEx
{
	DECLARE_DYNAMIC(CSliderControl)

public:
	CSliderControl(CVideoReal *pVideoCtrl, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSliderControl();

// �Ի�������
	enum { IDD = IDD_DIALOG_VIDEOPARAM };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	CVideoReal *m_pVideoCtrl;
	
};
