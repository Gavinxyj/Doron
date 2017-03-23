#pragma once


// CZoom �Ի���
class CVideoReal;
class CZoom : public CDialogEx
{
	DECLARE_DYNAMIC(CZoom)

public:
	CZoom(CVideoReal *pVideoCtrl, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CZoom();

// �Ի�������
	enum { IDD = IDD_DIALOG_ZOOM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
private:
	CVideoReal *m_pVideoCtrl;

public:
	afx_msg void OnClose();
};
