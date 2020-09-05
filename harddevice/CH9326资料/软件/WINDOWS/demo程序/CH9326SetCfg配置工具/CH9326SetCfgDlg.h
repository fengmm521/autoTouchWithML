// CH9326SetCfgDlg.h : header file
//

#if !defined(AFX_CH9326SETCFGDLG_H__09E86BAC_3611_40A0_98E0_D9BEFEAE7C14__INCLUDED_)
#define AFX_CH9326SETCFGDLG_H__09E86BAC_3611_40A0_98E0_D9BEFEAE7C14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCH9326SetCfgDlg dialog

class CCH9326SetCfgDlg : public CDialog
{
// Construction
public:
	void OnCheckRadioState();
	void InitSelDev();
	CCH9326SetCfgDlg(CWnd* pParent = NULL);	// standard constructor
	HANDLE m_hHID;
	USHORT m_wIODir;
	USHORT m_wIOData;
	UCHAR m_ucRate;
	UCHAR m_ucCheck;
	UCHAR m_ucStop;
	UCHAR m_ucData;
	UCHAR m_ucInterval;
// Dialog Data
	//{{AFX_DATA(CCH9326SetCfgDlg)
	enum { IDD = IDD_CH9326SETCFG_DIALOG };
	CEdit	m_ctrlStatus;
	CEdit	m_ctrlCHABA;
	CComboBox	m_ctrlStop;
	CComboBox	m_ctrlSelDev;
	CComboBox	m_ctrlRate;
	CComboBox	m_ctrlData;
	CComboBox	m_ctrlCheck;
	CString	m_strMS;
	CString	m_strPID;
	CString	m_strPS;
	CString	m_strSS;
	CString	m_strVID;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCH9326SetCfgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCH9326SetCfgDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnDeviceNotification(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMyChangeDevice(WPARAM wParam, LPARAM lParam);
	afx_msg void OnButtonOpen();
	afx_msg void OnButtonSetreport();
	afx_msg void OnButtonSetCfg();
	afx_msg void OnButtonGetCfg();
	afx_msg void OnRadioIo5Input();
	afx_msg void OnRadioIo5Output();
	afx_msg void OnRadioIo5High();
	afx_msg void OnRadioIo5Low();
	afx_msg void OnRadioIo6Input();
	afx_msg void OnRadioIo6Output();
	afx_msg void OnRadioIo6High();
	afx_msg void OnRadioIo6Low();
	afx_msg void OnRadioIo7Input();
	afx_msg void OnRadioIo7Output();
	afx_msg void OnRadioIo7High();
	afx_msg void OnRadioIo7Low();
	afx_msg void OnRadioIo8Input();
	afx_msg void OnRadioIo8Output();
	afx_msg void OnRadioIo8High();
	afx_msg void OnRadioIo8Low();
	afx_msg void OnRadioIo9Input();
	afx_msg void OnRadioIo9Output();
	afx_msg void OnRadioIo9High();
	afx_msg void OnRadioIo9Low();
	afx_msg void OnRadioIo10Input();
	afx_msg void OnRadioIo10Output();
	afx_msg void OnRadioIo10High();
	afx_msg void OnRadioIo10Low();
	afx_msg void OnRadioIo11Input();
	afx_msg void OnRadioIo11Output();
	afx_msg void OnRadioIo11High();
	afx_msg void OnRadioIo11Low();
	afx_msg void OnRadioIo12Input();
	afx_msg void OnRadioIo12Output();
	afx_msg void OnRadioIo12High();
	afx_msg void OnRadioIo12Low();
	afx_msg void OnRadioIo13Input();
	afx_msg void OnRadioIo13Output();
	afx_msg void OnRadioIo13High();
	afx_msg void OnRadioIo13Low();
	afx_msg void OnRadioIo14Input();
	afx_msg void OnRadioIo14Output();
	afx_msg void OnRadioIo14High();
	afx_msg void OnRadioIo14Low();
	afx_msg void OnRadioIo15Input();
	afx_msg void OnRadioIo15Output();
	afx_msg void OnRadioIo15High();
	afx_msg void OnRadioIo15Low();
	afx_msg void OnRadioIo16Input();
	afx_msg void OnRadioIo16Output();
	afx_msg void OnRadioIo16High();
	afx_msg void OnRadioIo16Low();
	afx_msg void OnSelchangeComboCheck();
	afx_msg void OnSelchangeComboData();
	afx_msg void OnSelchangeComboRate();
	afx_msg void OnSelchangeComboStop();
	afx_msg void OnButtonSetio();
	afx_msg void OnButtonSetOutput();
	afx_msg void OnButtonGetio();
	afx_msg void OnCheckVid();
	afx_msg void OnCheckPid();
	afx_msg void OnCheckMs();
	afx_msg void OnCheckPs();
	afx_msg void OnCheckSs();
	afx_msg void OnButtonSetDefualt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CH9326SETCFGDLG_H__09E86BAC_3611_40A0_98E0_D9BEFEAE7C14__INCLUDED_)
