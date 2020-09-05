// CH9326DBGDlg.h : header file
//

#if !defined(AFX_CH9326DBGDLG_H__EE13AD28_B5B5_4998_864A_98A1E0F4B5E3__INCLUDED_)
#define AFX_CH9326DBGDLG_H__EE13AD28_B5B5_4998_864A_98A1E0F4B5E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MyEdit.h"
/////////////////////////////////////////////////////////////////////////////
// CCH9326DBGDlg dialog

class CCH9326DBGDlg : public CDialog
{
// Construction
public:
	void OnCheckRadioState();
	void InitSelDev();
	HANDLE m_hHID;
	CHAR  m_strDevPath[512];
	USHORT m_wIODir;
	USHORT m_wIOData;
	UCHAR m_ucRate;
	UCHAR m_ucCheck;
	UCHAR m_ucStop;
	UCHAR m_ucData;
	UCHAR m_ucInterval;
	BOOL  m_bStop;
	UINT  m_uRecvED;
	CCH9326DBGDlg(CWnd* pParent = NULL);	// standard constructor
	
// Dialog Data
	//{{AFX_DATA(CCH9326DBGDlg)
	enum { IDD = IDD_CH9326DBG_DIALOG };
	CButton	m_cbRecv;
	CEdit	m_mRecvED;
	CEdit	m_ctrlStatus;
	CMyEdit	m_ctrlRecv;
	CEdit	m_ctrlCHABA;
	CComboBox	m_ctrlStop;
	CComboBox	m_ctrlSelDev;
	CComboBox	m_ctrlRate;
	CComboBox	m_ctrlData;
	CComboBox	m_ctrlCheck;
	CString	m_strBuf;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCH9326DBGDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCH9326DBGDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnDeviceNotification(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMyChangeDevice(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSelchangeComboCheck();
	afx_msg void OnSelchangeComboData();
	afx_msg void OnSelchangeComboRate();
	afx_msg void OnSelchangeComboStop();
	afx_msg void OnButtonOpen();
	afx_msg void OnButtonSetreport();
	afx_msg void OnButtonSend();
	afx_msg void OnButtonRecv();
	afx_msg void OnButtonStop();
	afx_msg void OnButtonClear();
	afx_msg void OnRadioIo1Input();
	afx_msg void OnRadioIo1Output();
	afx_msg void OnRadioIo1High();
	afx_msg void OnRadioIo1Low();
	afx_msg void OnRadioIo2Input();
	afx_msg void OnRadioIo2Output();
	afx_msg void OnRadioIo2High();
	afx_msg void OnRadioIo2Low();
	afx_msg void OnButtonSetio();
	afx_msg void OnButtonGetio();
	afx_msg void OnRadioIo3Input();
	afx_msg void OnRadioIo3Output();
	afx_msg void OnRadioIo3High();
	afx_msg void OnRadioIo3Low();
	afx_msg void OnRadioIo4Input();
	afx_msg void OnRadioIo4Output();
	afx_msg void OnRadioIo4High();
	afx_msg void OnRadioIo4Low();
	afx_msg void OnButtonSetOutput();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CH9326DBGDLG_H__EE13AD28_B5B5_4998_864A_98A1E0F4B5E3__INCLUDED_)
