#pragma once
#include "ItemMgr.h"
#include "PreTranslateMsgHook.h"
// CVideoReal 对话框
class CDRVideoRealCtrl;
class CZoom;

class CVideoReal : public CDialogEx
{
	DECLARE_DYNAMIC(CVideoReal)

public:
	CVideoReal(CDRVideoRealCtrl *pRealCtrl, CWnd* pParent = NULL);   // 标准构造函数
	//CVideoReal(CDRVideoRealCtrl *pRealCtrl);
	virtual ~CVideoReal();

// 对话框数据
	enum { IDD = IDD_DIALOG_VIDEO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void DrawBorder();
	bool Capture(LPCTSTR strPath);
	bool StartRecord();
	bool StopRecord();
	bool StopVideo();
	bool StartVideo(CONNECTINFO *connInfo);
	bool PtzControl(Client_PTZ_Command *cmd);
	bool OpenSound();
	bool CloseSound();
	bool StopSwitchSingle();
	bool SetVolumn(int nVolumn);
	bool StartTalk();
	bool StopTalk();
	bool SetVideoParam(int bright, int contrast, int saturation, int hue);
	bool GetVideoParam();
	bool ZoomEnlarge(HWND hWnd);
	bool RemoveZoom(int nLoginId, int nZoomId);
public:
	CDRVideoRealCtrl *m_pRealCtrl;
	int m_curIndex;
	int m_nWidth;
	int m_nHight;
	int m_splitNum;
	bool bActive;
	CRect m_rect;
	bool m_played;
	long  m_nLoginId;
	int m_nTalkId;
	CMenu m_Menu;
	CWnd *m_oldWnd;
	CZoom *m_pZoomDlg;
	VIDEOPARAM *m_videoParam;
	int m_nZoomId;
	CPreTranslateMsgHook* m_pHook;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMenuStopVideo();
	afx_msg void OnMenuSingleRecord();
	afx_msg void OnMenuCapture();
	afx_msg void OnMenuFullscreen();
	afx_msg void OnMenuSingleswitch();
	afx_msg void OnMenuSinglestop();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMenuSetparam();
	afx_msg void OnMenuZoom();
	afx_msg void OnMenuStyle();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};
