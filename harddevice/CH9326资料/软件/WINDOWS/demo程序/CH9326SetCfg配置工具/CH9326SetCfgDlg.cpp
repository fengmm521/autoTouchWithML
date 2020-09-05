// CH9326SetCfgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CH9326SetCfg.h"
#include "CH9326SetCfgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

UCHAR mCharToBcd(UCHAR iChar)
{
	UCHAR	mBCD;
	if ( iChar >= '0' && iChar <= '9' ) mBCD = iChar -'0';
	else if ( iChar >= 'A' && iChar <= 'F' ) mBCD = iChar - 'A' + 0x0a;
	else if ( iChar >= 'a' && iChar <= 'f' ) mBCD = iChar - 'a' + 0x0a;
//	else mBCD = 0xff;
	else mBCD = 0;
	return( mBCD );
}
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCH9326SetCfgDlg dialog

CCH9326SetCfgDlg::CCH9326SetCfgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCH9326SetCfgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCH9326SetCfgDlg)
	m_strMS = _T("");
	m_strPID = _T("");
	m_strPS = _T("");
	m_strSS = _T("");
	m_strVID = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCH9326SetCfgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCH9326SetCfgDlg)
	DDX_Control(pDX, IDC_EDIT_STATUS, m_ctrlStatus);
	DDX_Control(pDX, IDC_EDIT_CHABA, m_ctrlCHABA);
	DDX_Control(pDX, IDC_COMBO_STOP, m_ctrlStop);
	DDX_Control(pDX, IDC_COMBO_SELECT_DEV, m_ctrlSelDev);
	DDX_Control(pDX, IDC_COMBO_RATE, m_ctrlRate);
	DDX_Control(pDX, IDC_COMBO_DATA, m_ctrlData);
	DDX_Control(pDX, IDC_COMBO_CHECK, m_ctrlCheck);
	DDX_Text(pDX, IDC_EDIT_MSTRING, m_strMS);
	DDX_Text(pDX, IDC_EDIT_PID, m_strPID);
	DDX_Text(pDX, IDC_EDIT_PSTRING, m_strPS);
	DDX_Text(pDX, IDC_EDIT_SSTRING, m_strSS);
	DDX_Text(pDX, IDC_EDIT_VID, m_strVID);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCH9326SetCfgDlg, CDialog)
	//{{AFX_MSG_MAP(CCH9326SetCfgDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_DEVICECHANGE,OnDeviceNotification)
	ON_MESSAGE(MM_MYCHANGEDEVICE,OnMyChangeDevice)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, OnButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_SETREPORT, OnButtonSetreport)
	ON_BN_CLICKED(IDC_BUTTON_SET_CFG, OnButtonSetCfg)
	ON_BN_CLICKED(IDC_BUTTON_GET_CFG, OnButtonGetCfg)
	ON_BN_CLICKED(IDC_RADIO_IO5_INPUT, OnRadioIo5Input)
	ON_BN_CLICKED(IDC_RADIO_IO5_OUTPUT, OnRadioIo5Output)
	ON_BN_CLICKED(IDC_RADIO_IO5_HIGH, OnRadioIo5High)
	ON_BN_CLICKED(IDC_RADIO_IO5_LOW, OnRadioIo5Low)
	ON_BN_CLICKED(IDC_RADIO_IO6_INPUT, OnRadioIo6Input)
	ON_BN_CLICKED(IDC_RADIO_IO6_OUTPUT, OnRadioIo6Output)
	ON_BN_CLICKED(IDC_RADIO_IO6_HIGH, OnRadioIo6High)
	ON_BN_CLICKED(IDC_RADIO_IO6_LOW, OnRadioIo6Low)
	ON_BN_CLICKED(IDC_RADIO_IO7_INPUT, OnRadioIo7Input)
	ON_BN_CLICKED(IDC_RADIO_IO7_OUTPUT, OnRadioIo7Output)
	ON_BN_CLICKED(IDC_RADIO_IO7_HIGH, OnRadioIo7High)
	ON_BN_CLICKED(IDC_RADIO_IO7_LOW, OnRadioIo7Low)
	ON_BN_CLICKED(IDC_RADIO_IO8_INPUT, OnRadioIo8Input)
	ON_BN_CLICKED(IDC_RADIO_IO8_OUTPUT, OnRadioIo8Output)
	ON_BN_CLICKED(IDC_RADIO_IO8_HIGH, OnRadioIo8High)
	ON_BN_CLICKED(IDC_RADIO_IO8_LOW, OnRadioIo8Low)
	ON_BN_CLICKED(IDC_RADIO_IO9_INPUT, OnRadioIo9Input)
	ON_BN_CLICKED(IDC_RADIO_IO9_OUTPUT, OnRadioIo9Output)
	ON_BN_CLICKED(IDC_RADIO_IO9_HIGH, OnRadioIo9High)
	ON_BN_CLICKED(IDC_RADIO_IO9_LOW, OnRadioIo9Low)
	ON_BN_CLICKED(IDC_RADIO_IO10_INPUT, OnRadioIo10Input)
	ON_BN_CLICKED(IDC_RADIO_IO10_OUTPUT, OnRadioIo10Output)
	ON_BN_CLICKED(IDC_RADIO_IO10_HIGH, OnRadioIo10High)
	ON_BN_CLICKED(IDC_RADIO_IO10_LOW, OnRadioIo10Low)
	ON_BN_CLICKED(IDC_RADIO_IO11_INPUT, OnRadioIo11Input)
	ON_BN_CLICKED(IDC_RADIO_IO11_OUTPUT, OnRadioIo11Output)
	ON_BN_CLICKED(IDC_RADIO_IO11_HIGH, OnRadioIo11High)
	ON_BN_CLICKED(IDC_RADIO_IO11_LOW, OnRadioIo11Low)
	ON_BN_CLICKED(IDC_RADIO_IO12_INPUT, OnRadioIo12Input)
	ON_BN_CLICKED(IDC_RADIO_IO12_OUTPUT, OnRadioIo12Output)
	ON_BN_CLICKED(IDC_RADIO_IO12_HIGH, OnRadioIo12High)
	ON_BN_CLICKED(IDC_RADIO_IO12_LOW, OnRadioIo12Low)
	ON_BN_CLICKED(IDC_RADIO_IO13_INPUT, OnRadioIo13Input)
	ON_BN_CLICKED(IDC_RADIO_IO13_OUTPUT, OnRadioIo13Output)
	ON_BN_CLICKED(IDC_RADIO_IO13_HIGH, OnRadioIo13High)
	ON_BN_CLICKED(IDC_RADIO_IO13_LOW, OnRadioIo13Low)
	ON_BN_CLICKED(IDC_RADIO_IO14_INPUT, OnRadioIo14Input)
	ON_BN_CLICKED(IDC_RADIO_IO14_OUTPUT, OnRadioIo14Output)
	ON_BN_CLICKED(IDC_RADIO_IO14_HIGH, OnRadioIo14High)
	ON_BN_CLICKED(IDC_RADIO_IO14_LOW, OnRadioIo14Low)
	ON_BN_CLICKED(IDC_RADIO_IO15_INPUT, OnRadioIo15Input)
	ON_BN_CLICKED(IDC_RADIO_IO15_OUTPUT, OnRadioIo15Output)
	ON_BN_CLICKED(IDC_RADIO_IO15_HIGH, OnRadioIo15High)
	ON_BN_CLICKED(IDC_RADIO_IO15_LOW, OnRadioIo15Low)
	ON_BN_CLICKED(IDC_RADIO_IO16_INPUT, OnRadioIo16Input)
	ON_BN_CLICKED(IDC_RADIO_IO16_OUTPUT, OnRadioIo16Output)
	ON_BN_CLICKED(IDC_RADIO_IO16_HIGH, OnRadioIo16High)
	ON_BN_CLICKED(IDC_RADIO_IO16_LOW, OnRadioIo16Low)
	ON_CBN_SELCHANGE(IDC_COMBO_CHECK, OnSelchangeComboCheck)
	ON_CBN_SELCHANGE(IDC_COMBO_DATA, OnSelchangeComboData)
	ON_CBN_SELCHANGE(IDC_COMBO_RATE, OnSelchangeComboRate)
	ON_CBN_SELCHANGE(IDC_COMBO_STOP, OnSelchangeComboStop)
	ON_BN_CLICKED(IDC_BUTTON_SETIO, OnButtonSetio)
	ON_BN_CLICKED(IDC_BUTTON_SET_OUTPUT, OnButtonSetOutput)
	ON_BN_CLICKED(IDC_BUTTON_GETIO, OnButtonGetio)
	ON_BN_CLICKED(IDC_CHECK_VID, OnCheckVid)
	ON_BN_CLICKED(IDC_CHECK_PID, OnCheckPid)
	ON_BN_CLICKED(IDC_CHECK_MS, OnCheckMs)
	ON_BN_CLICKED(IDC_CHECK_PS, OnCheckPs)
	ON_BN_CLICKED(IDC_CHECK_SS, OnCheckSs)
	ON_BN_CLICKED(IDC_BUTTON_SET_DEFUALT, OnButtonSetDefualt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCH9326SetCfgDlg message handlers

BOOL CCH9326SetCfgDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_hHID = INVALID_HANDLE_VALUE;
	// TODO: Add extra initialization here
	GUID hidGuid;
	//HWND hwnd = NULL;
	CH9326GetHidGuid(&hidGuid);//取得HID类别的GUID
	{		//注意设备插拔只能在2000以后的系统上使用
		HDEVNOTIFY  m_hRegDevNotif;
		DEV_BROADCAST_DEVICEINTERFACE	mNotifyFilter;
		ZeroMemory( &mNotifyFilter, sizeof( mNotifyFilter ) );
		mNotifyFilter.dbcc_size = sizeof( mNotifyFilter );
		mNotifyFilter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;  // 设置监控的设备类型
		mNotifyFilter.dbcc_classguid = hidGuid;  // 设置监控的设备接口类:USB接口
		m_hRegDevNotif = RegisterDeviceNotification(GetSafeHwnd(), &mNotifyFilter, DEVICE_NOTIFY_WINDOW_HANDLE );  // 注册设备事件通知
		//m_hRegDevNotif = RegisterDeviceNotification(hwnd, &mNotifyFilter, DEVICE_NOTIFY_WINDOW_HANDLE );  // 注册设备事件通知
		if ( !m_hRegDevNotif ) {
				//ULONG d = GetLastError();
				return( FALSE );
		}
	}


	m_ctrlRate.AddString(_T("300"));
	m_ctrlRate.AddString(_T("600"));
	m_ctrlRate.AddString(_T("1200"));
	m_ctrlRate.AddString(_T("2400"));
	m_ctrlRate.AddString(_T("4800"));
	m_ctrlRate.AddString(_T("9600"));
	m_ctrlRate.AddString(_T("14400"));
	m_ctrlRate.AddString(_T("19200"));
	m_ctrlRate.AddString(_T("28800"));
	m_ctrlRate.AddString(_T("38400"));
	m_ctrlRate.AddString(_T("57600"));
	m_ctrlRate.AddString(_T("76800"));
	m_ctrlRate.AddString(_T("115200"));
//	m_ctrlRate.AddString(_T("1000000"));
	m_ctrlRate.SetCurSel(5);

	m_ctrlStop.AddString(_T("1位"));
	m_ctrlStop.AddString(_T("2位"));
	m_ctrlStop.SetCurSel(0);
	
	m_ctrlCheck.AddString(_T("奇校验"));
	m_ctrlCheck.AddString(_T("偶校验"));
	m_ctrlCheck.AddString(_T("空白位"));
	m_ctrlCheck.AddString(_T("无校验"));
	m_ctrlCheck.SetCurSel(3);


	m_ctrlData.AddString(_T("5位"));
	m_ctrlData.AddString(_T("6位"));
	m_ctrlData.AddString(_T("7位"));
	m_ctrlData.AddString(_T("8位"));
	m_ctrlData.SetCurSel(3);
	
	GetDlgItem(IDC_EDIT_VID)->EnableWindow(FALSE);  
	GetDlgItem(IDC_EDIT_PID)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT_MSTRING)->EnableWindow(FALSE);  
	GetDlgItem(IDC_EDIT_PSTRING)->EnableWindow(FALSE);  
	GetDlgItem(IDC_EDIT_SSTRING)->EnableWindow(FALSE); 

	InitSelDev();
	m_wIODir = 0 | (1<<11) | (1<<12) | (1<<14);  //IO12，IO13,IO15只能输出
	m_wIOData = 0;
	
	
	GetDlgItem(IDC_RADIO_IO12_INPUT)->EnableWindow(FALSE);  
	GetDlgItem(IDC_RADIO_IO13_INPUT)->EnableWindow(FALSE);  
	GetDlgItem(IDC_RADIO_IO15_INPUT)->EnableWindow(FALSE);  

	m_ucRate = 6;
	m_ucCheck = 4;
	m_ucStop = 1;
	m_ucData = 4;
	m_ucInterval = 0x40;
	OnCheckRadioState();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCH9326SetCfgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCH9326SetCfgDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCH9326SetCfgDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

LRESULT CCH9326SetCfgDlg::OnDeviceNotification(WPARAM wParam, LPARAM lParam)
{
	PDEV_BROADCAST_DEVICEINTERFACE	DevInfo;
	ULONG	mEventStatus;
	//UCHAR	DevId[ MAX_DEVICE_PATH_SIZE ];
	DevInfo = (PDEV_BROADCAST_DEVICEINTERFACE)lParam;  // 设备信息
	if ( wParam == DBT_DEVICEARRIVAL || wParam == DBT_DEVICEREMOVEPENDING || wParam == DBT_DEVICEREMOVECOMPLETE ) {  // 设备插入或移除
		if ( DevInfo -> dbcc_devicetype == DBT_DEVTYP_DEVICEINTERFACE ) {
			
			switch( wParam ) {
				case DBT_DEVICEARRIVAL: mEventStatus = DEVICE_ARRIVAL; break;
				case DBT_DEVICEREMOVEPENDING: mEventStatus = DEVICE_REMOVE_PEND; break;
				case DBT_DEVICEREMOVECOMPLETE: mEventStatus = DEVICE_REMOVE; break;
				default: mEventStatus = DEVICE_REMOVE; break;
			}
			PostMessage(MM_MYCHANGEDEVICE,(DWORD)mEventStatus,0);
			
		}
		return 0;
	}
	return 0;
}
LRESULT CCH9326SetCfgDlg::OnMyChangeDevice(WPARAM wParam, LPARAM lParam)
{
	
	if( wParam == DEVICE_ARRIVAL ){
		m_ctrlCHABA.SetWindowText("有HID设备到达");
		
	}else{
		m_ctrlCHABA.SetWindowText("有HID设备离开");
		//m_bFileStop = 1;
		//m_bStop = 1;
		if(m_hHID != INVALID_HANDLE_VALUE)
			CH9326CloseDevice(m_hHID);
		m_hHID = INVALID_HANDLE_VALUE;
	}
	m_ctrlSelDev.ResetContent();
	InitSelDev();
	
	return 0;
}

void CCH9326SetCfgDlg::InitSelDev()
{
	int deviceNo=0;
	CHAR buf[1024];
	HANDLE hHID;
	
	
	SetLastError(NO_ERROR);
	while(GetLastError()!=ERROR_NO_MORE_ITEMS)
	{
			memset(buf,0,sizeof(buf));
			if( CH9326GetDevicePath(deviceNo,buf,sizeof(buf)) )
			{
				//打开设备,并获得设备句柄
				 hHID=CreateFile(buf,
					GENERIC_READ|GENERIC_WRITE,
					FILE_SHARE_READ|FILE_SHARE_WRITE,
					NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,NULL);
				
				if(hHID==INVALID_HANDLE_VALUE)
				{
					deviceNo++;
					continue;
				}
				CharUpperBuff(buf,strlen(buf));
				m_ctrlSelDev.InsertString(0,(const char *)buf);

				CloseHandle(hHID);
				
			}
			deviceNo++;
		
	}
}

void CCH9326SetCfgDlg::OnButtonOpen() 
{
	// TODO: Add your control notification handler code here
	CString strDev;
	if( m_ctrlSelDev.GetCount() == 0 ) {
		AfxMessageBox("当前系统没有可打开的HID设备");
		return;
	}
	if( m_ctrlSelDev.GetCurSel() == -1 ){
		AfxMessageBox("请选择一个HID设备");
		return;
	}
	if(m_hHID != INVALID_HANDLE_VALUE )
		return;
	m_ctrlSelDev.GetLBText(m_ctrlSelDev.GetCurSel(),strDev);
	//AfxMessageBox(strDev);
	/*
	m_hHID=CreateFile(strDev,
				GENERIC_READ|GENERIC_WRITE,
				FILE_SHARE_READ|FILE_SHARE_WRITE,
				NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,NULL);
	*/
	m_hHID = CH9326OpenDevicePath((PCHAR)LPCTSTR (strDev));

	if(m_hHID==INVALID_HANDLE_VALUE)
	{
		AfxMessageBox("打开HID设备失败");
		return;
	}
	USHORT VID,PID,VER;
	//获取厂商ID和设备ID
	if(!CH9326GetAttributes(m_hHID,&VID,&PID,&VER))
	{
		CH9326CloseDevice(m_hHID);
		return;
	}

	{
		char version[100]="";
		sprintf(version,"设备已连接,VID=%XPID=%X VER=%X ",VID,PID,VER);
		m_ctrlStatus.SetWindowText(version);
		
		USHORT inportlen,outportlen;
		CH9326GetBufferLen(m_hHID,&inportlen,&outportlen);
		CH9326SetTimeOut(m_hHID,3000,3000);
	}
	m_strVID.Format("%04X",VID);
	m_strPID.Format("%04X",PID);
	OnButtonGetCfg() ;
}

void CCH9326SetCfgDlg::OnButtonSetreport() 
{
	// TODO: Add your control notification handler code here
	if(m_hHID==INVALID_HANDLE_VALUE){
		m_ctrlStatus.SetWindowText("设备尚未连接!");
	}


	if(!CH9326SetDefaultRate(m_hHID,m_ucRate,m_ucCheck,m_ucStop,m_ucData,m_ucInterval)) AfxMessageBox("设置不成功!");
	else{
		AfxMessageBox("设置成功!");
	}
}

void CCH9326SetCfgDlg::OnCheckRadioState()
{
	if(m_wIODir & 0x0010){
		CheckRadioButton(IDC_RADIO_IO5_INPUT,IDC_RADIO_IO5_OUTPUT,IDC_RADIO_IO5_OUTPUT);
		GetDlgItem(IDC_RADIO_IO5_HIGH)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO_IO5_LOW)->EnableWindow(TRUE);
	}else{
		CheckRadioButton(IDC_RADIO_IO5_INPUT,IDC_RADIO_IO5_OUTPUT,IDC_RADIO_IO5_INPUT);
		GetDlgItem(IDC_RADIO_IO5_HIGH)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO_IO5_LOW)->EnableWindow(FALSE);
	}
	if(m_wIODir & 0x0020){
		CheckRadioButton(IDC_RADIO_IO6_INPUT,IDC_RADIO_IO6_OUTPUT,IDC_RADIO_IO6_OUTPUT);
		GetDlgItem(IDC_RADIO_IO6_HIGH)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO_IO6_LOW)->EnableWindow(TRUE);
	}else{
		CheckRadioButton(IDC_RADIO_IO6_INPUT,IDC_RADIO_IO6_OUTPUT,IDC_RADIO_IO6_INPUT);
		GetDlgItem(IDC_RADIO_IO6_HIGH)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO_IO6_LOW)->EnableWindow(FALSE);
	}
	if(m_wIODir & 0x0040){
		CheckRadioButton(IDC_RADIO_IO7_INPUT,IDC_RADIO_IO7_OUTPUT,IDC_RADIO_IO7_OUTPUT);
		GetDlgItem(IDC_RADIO_IO7_HIGH)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO_IO7_LOW)->EnableWindow(TRUE);
	}else{
		CheckRadioButton(IDC_RADIO_IO7_INPUT,IDC_RADIO_IO7_OUTPUT,IDC_RADIO_IO7_INPUT);
		GetDlgItem(IDC_RADIO_IO7_HIGH)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO_IO7_LOW)->EnableWindow(FALSE);
	}
	if(m_wIODir & 0x0080){
		CheckRadioButton(IDC_RADIO_IO8_INPUT,IDC_RADIO_IO8_OUTPUT,IDC_RADIO_IO8_OUTPUT);
		GetDlgItem(IDC_RADIO_IO8_HIGH)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO_IO8_LOW)->EnableWindow(TRUE);
	}else{
		CheckRadioButton(IDC_RADIO_IO8_INPUT,IDC_RADIO_IO8_OUTPUT,IDC_RADIO_IO8_INPUT);
		GetDlgItem(IDC_RADIO_IO8_HIGH)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO_IO8_LOW)->EnableWindow(FALSE);
	}

	if(m_wIODir & 0x0100){
		CheckRadioButton(IDC_RADIO_IO9_INPUT,IDC_RADIO_IO9_OUTPUT,IDC_RADIO_IO9_OUTPUT);
		GetDlgItem(IDC_RADIO_IO9_HIGH)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO_IO9_LOW)->EnableWindow(TRUE);
	}else{
		CheckRadioButton(IDC_RADIO_IO9_INPUT,IDC_RADIO_IO9_OUTPUT,IDC_RADIO_IO9_INPUT);
		GetDlgItem(IDC_RADIO_IO9_HIGH)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO_IO9_LOW)->EnableWindow(FALSE);
	}
	if(m_wIODir & 0x0200){
		CheckRadioButton(IDC_RADIO_IO10_INPUT,IDC_RADIO_IO10_OUTPUT,IDC_RADIO_IO10_OUTPUT);
		GetDlgItem(IDC_RADIO_IO10_HIGH)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO_IO10_LOW)->EnableWindow(TRUE);
	}else{
		CheckRadioButton(IDC_RADIO_IO10_INPUT,IDC_RADIO_IO10_OUTPUT,IDC_RADIO_IO10_INPUT);
		GetDlgItem(IDC_RADIO_IO10_HIGH)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO_IO10_LOW)->EnableWindow(FALSE);
	}
	if(m_wIODir & 0x0400){
		CheckRadioButton(IDC_RADIO_IO11_INPUT,IDC_RADIO_IO11_OUTPUT,IDC_RADIO_IO11_OUTPUT);
		GetDlgItem(IDC_RADIO_IO11_HIGH)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO_IO11_LOW)->EnableWindow(TRUE);
	}else{
		CheckRadioButton(IDC_RADIO_IO11_INPUT,IDC_RADIO_IO11_OUTPUT,IDC_RADIO_IO11_INPUT);
		GetDlgItem(IDC_RADIO_IO11_HIGH)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO_IO11_LOW)->EnableWindow(FALSE);
	}
	if(m_wIODir & 0x0800){
		CheckRadioButton(IDC_RADIO_IO12_INPUT,IDC_RADIO_IO12_OUTPUT,IDC_RADIO_IO12_OUTPUT);
		GetDlgItem(IDC_RADIO_IO12_HIGH)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO_IO12_LOW)->EnableWindow(TRUE);
	}else{
		CheckRadioButton(IDC_RADIO_IO12_INPUT,IDC_RADIO_IO12_OUTPUT,IDC_RADIO_IO12_INPUT);
		GetDlgItem(IDC_RADIO_IO12_HIGH)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO_IO12_LOW)->EnableWindow(FALSE);
	}
	if(m_wIODir & 0x1000){
		CheckRadioButton(IDC_RADIO_IO13_INPUT,IDC_RADIO_IO13_OUTPUT,IDC_RADIO_IO13_OUTPUT);
		GetDlgItem(IDC_RADIO_IO13_HIGH)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO_IO13_LOW)->EnableWindow(TRUE);
	}else{
		CheckRadioButton(IDC_RADIO_IO13_INPUT,IDC_RADIO_IO13_OUTPUT,IDC_RADIO_IO13_INPUT);
		GetDlgItem(IDC_RADIO_IO13_HIGH)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO_IO13_LOW)->EnableWindow(FALSE);
	}
	if(m_wIODir & 0x2000){
		CheckRadioButton(IDC_RADIO_IO14_INPUT,IDC_RADIO_IO14_OUTPUT,IDC_RADIO_IO14_OUTPUT);
		GetDlgItem(IDC_RADIO_IO14_HIGH)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO_IO14_LOW)->EnableWindow(TRUE);
	}else{
		CheckRadioButton(IDC_RADIO_IO14_INPUT,IDC_RADIO_IO14_OUTPUT,IDC_RADIO_IO14_INPUT);
		GetDlgItem(IDC_RADIO_IO14_HIGH)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO_IO14_LOW)->EnableWindow(FALSE);
	}
	if(m_wIODir & 0x4000){
		CheckRadioButton(IDC_RADIO_IO15_INPUT,IDC_RADIO_IO15_OUTPUT,IDC_RADIO_IO15_OUTPUT);
		GetDlgItem(IDC_RADIO_IO15_HIGH)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO_IO15_LOW)->EnableWindow(TRUE);
	}else{
		CheckRadioButton(IDC_RADIO_IO15_INPUT,IDC_RADIO_IO15_OUTPUT,IDC_RADIO_IO15_INPUT);
		GetDlgItem(IDC_RADIO_IO15_HIGH)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO_IO15_LOW)->EnableWindow(FALSE);
	}
	if(m_wIODir & 0x8000){
		CheckRadioButton(IDC_RADIO_IO16_INPUT,IDC_RADIO_IO16_OUTPUT,IDC_RADIO_IO16_OUTPUT);
		GetDlgItem(IDC_RADIO_IO16_HIGH)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO_IO16_LOW)->EnableWindow(TRUE);
	}else{
		CheckRadioButton(IDC_RADIO_IO16_INPUT,IDC_RADIO_IO16_OUTPUT,IDC_RADIO_IO16_INPUT);
		GetDlgItem(IDC_RADIO_IO16_HIGH)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO_IO16_LOW)->EnableWindow(FALSE);
	}


	if(m_wIOData & 0x0010){
		CheckRadioButton(IDC_RADIO_IO5_HIGH,IDC_RADIO_IO5_LOW,IDC_RADIO_IO5_HIGH);
	}else{
		CheckRadioButton(IDC_RADIO_IO5_HIGH,IDC_RADIO_IO5_LOW,IDC_RADIO_IO5_LOW);
	}
	if(m_wIOData & 0x0020){
		CheckRadioButton(IDC_RADIO_IO6_HIGH,IDC_RADIO_IO6_LOW,IDC_RADIO_IO6_HIGH);
	}else{
		CheckRadioButton(IDC_RADIO_IO6_HIGH,IDC_RADIO_IO6_LOW,IDC_RADIO_IO6_LOW);
	}
	if(m_wIOData & 0x0040){
		CheckRadioButton(IDC_RADIO_IO7_HIGH,IDC_RADIO_IO7_LOW,IDC_RADIO_IO7_HIGH);
	}else{
		CheckRadioButton(IDC_RADIO_IO7_HIGH,IDC_RADIO_IO7_LOW,IDC_RADIO_IO7_LOW);
	}
	if(m_wIOData & 0x0080){
		CheckRadioButton(IDC_RADIO_IO8_HIGH,IDC_RADIO_IO8_LOW,IDC_RADIO_IO8_HIGH);
	}else{
		CheckRadioButton(IDC_RADIO_IO8_HIGH,IDC_RADIO_IO8_LOW,IDC_RADIO_IO8_LOW);
	}
	if(m_wIOData & 0x0100){
		CheckRadioButton(IDC_RADIO_IO9_HIGH,IDC_RADIO_IO9_LOW,IDC_RADIO_IO9_HIGH);
	}else{
		CheckRadioButton(IDC_RADIO_IO9_HIGH,IDC_RADIO_IO9_LOW,IDC_RADIO_IO9_LOW);
	}
	if(m_wIOData & 0x0200){
		CheckRadioButton(IDC_RADIO_IO10_HIGH,IDC_RADIO_IO10_LOW,IDC_RADIO_IO10_HIGH);
	}else{
		CheckRadioButton(IDC_RADIO_IO10_HIGH,IDC_RADIO_IO10_LOW,IDC_RADIO_IO10_LOW);
	}
	if(m_wIOData & 0x0400){
		CheckRadioButton(IDC_RADIO_IO11_HIGH,IDC_RADIO_IO11_LOW,IDC_RADIO_IO11_HIGH);
	}else{
		CheckRadioButton(IDC_RADIO_IO11_HIGH,IDC_RADIO_IO11_LOW,IDC_RADIO_IO11_LOW);
	}
	if(m_wIOData & 0x0800){
		CheckRadioButton(IDC_RADIO_IO12_HIGH,IDC_RADIO_IO12_LOW,IDC_RADIO_IO12_HIGH);
	}else{
		CheckRadioButton(IDC_RADIO_IO12_HIGH,IDC_RADIO_IO12_LOW,IDC_RADIO_IO12_LOW);
	}
	if(m_wIOData & 0x1000){
		CheckRadioButton(IDC_RADIO_IO13_HIGH,IDC_RADIO_IO13_LOW,IDC_RADIO_IO13_HIGH);
	}else{
		CheckRadioButton(IDC_RADIO_IO13_HIGH,IDC_RADIO_IO13_LOW,IDC_RADIO_IO13_LOW);
	}
	if(m_wIOData & 0x2000){
		CheckRadioButton(IDC_RADIO_IO14_HIGH,IDC_RADIO_IO14_LOW,IDC_RADIO_IO14_HIGH);
	}else{
		CheckRadioButton(IDC_RADIO_IO14_HIGH,IDC_RADIO_IO14_LOW,IDC_RADIO_IO14_LOW);
	}
	if(m_wIOData & 0x4000){
		CheckRadioButton(IDC_RADIO_IO15_HIGH,IDC_RADIO_IO15_LOW,IDC_RADIO_IO15_HIGH);
	}else{
		CheckRadioButton(IDC_RADIO_IO15_HIGH,IDC_RADIO_IO15_LOW,IDC_RADIO_IO15_LOW);
	}
	if(m_wIOData & 0x8000){
		CheckRadioButton(IDC_RADIO_IO16_HIGH,IDC_RADIO_IO16_LOW,IDC_RADIO_IO16_HIGH);
	}else{
		CheckRadioButton(IDC_RADIO_IO16_HIGH,IDC_RADIO_IO16_LOW,IDC_RADIO_IO16_LOW);
	}
}

void CCH9326SetCfgDlg::OnButtonSetCfg() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	UINT uPower;
	CHAR buf[33];
	//CHAR len,CurLen,len2,addr;
	USHORT VID,PID;

	if(m_hHID==INVALID_HANDLE_VALUE)
	{
		m_ctrlStatus.SetWindowText("设备尚未连接!");
		return ;
	}
	memset(buf,0,sizeof(buf));
	
	if( IsDlgButtonChecked(IDC_CHECK_VID) )
	{
		if(m_strVID.GetLength () < 4) {
			AfxMessageBox("VID长度不对");
			return;
		}
		VID =  ( (UCHAR)( (mCharToBcd(m_strVID.GetAt(0)))<<4 ) + mCharToBcd(m_strVID.GetAt(1) ) )<< 8 |
			     (UCHAR)( (mCharToBcd(m_strVID.GetAt(2)))<<4 ) + mCharToBcd(m_strVID.GetAt(3) )  ;
	}else {
		VID = 0x1A86;
	}
	

	if( IsDlgButtonChecked(IDC_CHECK_PID) )
	{
		if(m_strPID.GetLength () < 4) {
			AfxMessageBox("PID长度不对");
			return;
		}
		PID =  ( (UCHAR)( (mCharToBcd(m_strPID.GetAt(0)))<<4 ) + mCharToBcd(m_strPID.GetAt(1) ) )<< 8 |
			     (UCHAR)( (mCharToBcd(m_strPID.GetAt(2)))<<4 ) + mCharToBcd(m_strPID.GetAt(3) )  ;

	}else {
		PID = 0xE010;
	}
	
	
	
	
	if( IsDlgButtonChecked(IDC_CHECK_MS) )
	{
		if(m_strMS.GetLength () == 0  ) 
		{
			AfxMessageBox("厂商字符串长度不对");
			return;
		}
		if( m_strMS.GetLength () > 30)
		{
			AfxMessageBox("厂商字符串长度超过30");
			return;
		}
	}else{
		m_strMS ="WCH.CN 2";
	}
	
	
	if( IsDlgButtonChecked(IDC_CHECK_PS) )
	{
		if(m_strPS.GetLength () == 0 ) 
		{
			AfxMessageBox("产品字符串长度不对");
			return;
		}
		if( m_strPS.GetLength () > 30)
		{
			AfxMessageBox("产品字符串长度超过30");
			return;
		}
	}else{
		m_strPS ="HID To Serial";
	}
	
	if( IsDlgButtonChecked(IDC_CHECK_SS) )
	{
		if(m_strSS.GetLength () == 0 ) 
		{
			AfxMessageBox("序列号字符串长度不对");
			return;
		}
		if( m_strSS.GetLength () > 30)
		{
			AfxMessageBox("序列号字符串长度超过30");
			return;
		}
	}else{
		m_strSS ="12345678";
	}
	uPower = 0x32;

	if(!CH9326SetDeviceCfg(m_hHID,VID,PID,uPower,(PCHAR)(LPCTSTR )m_strMS,m_strMS.GetLength(),
		(PCHAR)(LPCTSTR )m_strPS,m_strPS.GetLength(),(PCHAR)(LPCTSTR )m_strSS,m_strSS.GetLength()) )
	{
		AfxMessageBox("CH9326SetDeviceCfg Error");
	}
}

void CCH9326SetCfgDlg::OnButtonGetCfg() 
{
	// TODO: Add your control notification handler code here
		WCHAR wbuf[64];
	CHAR  buf[128];

	if(m_hHID==INVALID_HANDLE_VALUE)
	{
		m_ctrlStatus.SetWindowText("设备尚未连接!");
		return ;
	}


	CH9326GetManufacturerString(m_hHID,wbuf,64);
	WideCharToMultiByte( CP_ACP,0,wbuf,-1,buf,sizeof(buf),NULL,NULL );
	m_strMS = buf;
	CH9326GetProductString(m_hHID,wbuf,64);
	WideCharToMultiByte( CP_ACP,0,wbuf,-1,buf,sizeof(buf),NULL,NULL );
	m_strPS = buf;
	CH9326GetSerialNumberString(m_hHID,wbuf,64);
	WideCharToMultiByte( CP_ACP,0,wbuf,-1,buf,sizeof(buf),NULL,NULL );
	m_strSS = buf;
	UpdateData(FALSE);
	GetDlgItem(IDC_EDIT_MSTRING)->EnableWindow(TRUE);
	CheckDlgButton(IDC_CHECK_MS,BST_CHECKED);

	GetDlgItem(IDC_EDIT_PSTRING)->EnableWindow(TRUE);
	CheckDlgButton(IDC_CHECK_PS,BST_CHECKED);

	GetDlgItem(IDC_EDIT_SSTRING)->EnableWindow(TRUE);
	CheckDlgButton(IDC_CHECK_SS,BST_CHECKED);

}

void CCH9326SetCfgDlg::OnRadioIo5Input() 
{
	// TODO: Add your control notification handler code here
	m_wIODir &=0xFFEF;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo5Output() 
{
	// TODO: Add your control notification handler code here
	m_wIODir |=0x0010;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo5High() 
{
	// TODO: Add your control notification handler code here
	m_wIOData |= 0x0010;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo5Low() 
{
	// TODO: Add your control notification handler code here
	m_wIOData &= 0xFFEF;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo6Input() 
{
	// TODO: Add your control notification handler code here
	m_wIODir &=0xFFDF;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo6Output() 
{
	// TODO: Add your control notification handler code here
	m_wIODir |=0x0020;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo6High() 
{
	// TODO: Add your control notification handler code here
	m_wIOData |= 0x0020;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo6Low() 
{
	// TODO: Add your control notification handler code here
	m_wIOData &= 0xFFDF;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo7Input() 
{
	// TODO: Add your control notification handler code here
	m_wIODir &=0xFFBF;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo7Output() 
{
	// TODO: Add your control notification handler code here
	m_wIODir |=0x0040;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo7High() 
{
	// TODO: Add your control notification handler code here
	m_wIOData |= 0x0040;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo7Low() 
{
	// TODO: Add your control notification handler code here
	m_wIOData &= 0xFFBF;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo8Input() 
{
	// TODO: Add your control notification handler code here
	m_wIODir &=0xFF7F;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo8Output() 
{
	// TODO: Add your control notification handler code here
	m_wIODir |=0x0080;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo8High() 
{
	// TODO: Add your control notification handler code here
	m_wIOData |= 0x0080;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo8Low() 
{
	// TODO: Add your control notification handler code here
	m_wIOData &= 0xFF7F;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo9Input() 
{
	// TODO: Add your control notification handler code here
	m_wIODir &=0xFEFF;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo9Output() 
{
	// TODO: Add your control notification handler code here
	m_wIODir |=0x0100;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo9High() 
{
	// TODO: Add your control notification handler code here
	m_wIOData |= 0x0100;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo9Low() 
{
	// TODO: Add your control notification handler code here
	m_wIOData &= 0xFEFF;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo10Input() 
{
	// TODO: Add your control notification handler code here
	m_wIODir &=0xFDFF;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo10Output() 
{
	// TODO: Add your control notification handler code here
	m_wIODir |=0x0200;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo10High() 
{
	// TODO: Add your control notification handler code here
	m_wIOData |= 0x0200;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo10Low() 
{
	// TODO: Add your control notification handler code here
	m_wIOData &= 0xFDFF;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo11Input() 
{
	// TODO: Add your control notification handler code here
	m_wIODir &=0xFBFF;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo11Output() 
{
	// TODO: Add your control notification handler code here
	m_wIODir |=0x0400;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo11High() 
{
	// TODO: Add your control notification handler code here
	m_wIOData |= 0x0400;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo11Low() 
{
	// TODO: Add your control notification handler code here
	m_wIOData &= 0xFBFF;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo12Input() 
{
	// TODO: Add your control notification handler code here
	m_wIODir &=0xF7FF;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo12Output() 
{
	// TODO: Add your control notification handler code here
	m_wIODir |=0x0800;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo12High() 
{
	// TODO: Add your control notification handler code here
	m_wIOData |= 0x0800;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo12Low() 
{
	// TODO: Add your control notification handler code here
	m_wIOData &= 0xF7FF;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo13Input() 
{
	// TODO: Add your control notification handler code here
	m_wIODir &=0xEFFF;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo13Output() 
{
	// TODO: Add your control notification handler code here
	m_wIODir |=0x1000;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo13High() 
{
	// TODO: Add your control notification handler code here
	m_wIOData |= 0x1000;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo13Low() 
{
	// TODO: Add your control notification handler code here
	m_wIOData &= 0xEFFF;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo14Input() 
{
	// TODO: Add your control notification handler code here
	m_wIODir &=0xDFFF;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo14Output() 
{
	// TODO: Add your control notification handler code here
	m_wIODir |=0x2000;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo14High() 
{
	// TODO: Add your control notification handler code here
	m_wIOData |= 0x2000;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo14Low() 
{
	// TODO: Add your control notification handler code here
	m_wIOData &= 0xDFFF;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo15Input() 
{
	// TODO: Add your control notification handler code here
	m_wIODir &=0xBFFF;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo15Output() 
{
	// TODO: Add your control notification handler code here
	m_wIODir |=0x4000;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo15High() 
{
	// TODO: Add your control notification handler code here
	m_wIOData |= 0x4000;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo15Low() 
{
	// TODO: Add your control notification handler code here
	m_wIOData &= 0xBFFF;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo16Input() 
{
	// TODO: Add your control notification handler code here
	m_wIODir &=0x7FFF;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo16Output() 
{
	// TODO: Add your control notification handler code here
	m_wIODir |=0x8000;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo16High() 
{
	// TODO: Add your control notification handler code here
	m_wIOData |= 0x8000;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnRadioIo16Low() 
{
	// TODO: Add your control notification handler code here
	m_wIOData &= 0x7FFF;
	OnCheckRadioState();
}

void CCH9326SetCfgDlg::OnSelchangeComboCheck() 
{
	// TODO: Add your control notification handler code here
	CString st;
	m_ctrlCheck.GetLBText( m_ctrlCheck.GetCurSel() ,st);
	if( st == _T("奇校验") ){
		m_ucCheck = 1;
	}else if( st == _T("偶校验") ){
		m_ucCheck = 2;
	}else if( st == _T("空白位") ){
		m_ucCheck = 3;
	}else if( st == _T("无校验") ){
		m_ucCheck = 4;
	}
}

void CCH9326SetCfgDlg::OnSelchangeComboData() 
{
	// TODO: Add your control notification handler code here
	CString st;
	m_ctrlData.GetLBText( m_ctrlData.GetCurSel() ,st);
	if( st == _T("5位")  ){
		m_ucData = 1;
	}else if( st == _T("6位")  ){
		m_ucData = 2;
	}else if( st == _T("7位")  ){
		m_ucData = 3;
	}else if( st == _T("8位")  ){
		m_ucData = 4;
	}
}

void CCH9326SetCfgDlg::OnSelchangeComboRate() 
{
	// TODO: Add your control notification handler code here
	CString st;
	m_ctrlRate.GetLBText( m_ctrlRate.GetCurSel() ,st);
	if(st == _T("300")){
		m_ucRate = 1;
		m_ucInterval = 0xC0;	//300波特率，2字节之间大约要32MS，超时不能小与0xB0
	}else if(st == _T("600")){
		m_ucRate = 2;
		m_ucInterval = 0x80;	//600波特率，2字节之间大约要16MS，超时不能小与0x60
	}else if(st == _T("1200")){
		m_ucRate = 3;
		m_ucInterval = 0x60;	
	}else if(st == _T("2400")){
		m_ucRate = 4;
		m_ucInterval = 0x40;	
	}else if(st == _T("4800")){
		m_ucRate = 5;
		m_ucInterval = 0x30;
	}else if(st == _T("9600")){
		m_ucRate = 6;
		m_ucInterval = 0x40;
	}else if(st == _T("14400")){
		m_ucRate = 7;
		m_ucInterval = 0x30;
	}else if(st == _T("19200")){
		m_ucRate = 8;
		m_ucInterval = 0x30;
	}else if(st == _T("28800")){
		m_ucRate = 9;
		m_ucInterval = 0x30;
	}else if(st == _T("38400")){
		m_ucRate = 10;
		m_ucInterval = 0x30;
	}else if(st == _T("57600")){
		m_ucRate = 11;
		m_ucInterval = 0x30;
	}else if(st == _T("76800")){
		m_ucRate = 12;
		m_ucInterval = 0x30;
	}else if(st == _T("115200")){
		m_ucRate = 13;
		m_ucInterval = 0x30;

	}
}



void CCH9326SetCfgDlg::OnSelchangeComboStop() 
{
	// TODO: Add your control notification handler code here
	CString st;
	m_ctrlStop.GetLBText( m_ctrlStop.GetCurSel() ,st);
	if( st == _T("1位")  ){
		m_ucStop = 1;
	}else if( st == _T("2位")  ){
		m_ucStop = 2;
	}
}

void CCH9326SetCfgDlg::OnButtonSetio() 
{
	// TODO: Add your control notification handler code here
	if(m_hHID==INVALID_HANDLE_VALUE)
	{
		m_ctrlStatus.SetWindowText("设备尚未连接!");
		return ;
	}
	if(!CH9326SetIODir(m_hHID,m_wIODir)) {
		AfxMessageBox("设置方向失败");
	}
}

void CCH9326SetCfgDlg::OnButtonSetOutput() 
{
	// TODO: Add your control notification handler code here
	if(m_hHID==INVALID_HANDLE_VALUE)
	{
		m_ctrlStatus.SetWindowText("设备尚未连接!");
		return ;
	}
	USHORT data;
	data = m_wIOData & m_wIODir;
	if( !CH9326WriteIOData(m_hHID,data) ){
		AfxMessageBox("写io失败");
	}
}

void CCH9326SetCfgDlg::OnButtonGetio() 
{
	// TODO: Add your control notification handler code here
	USHORT data;
	if(m_hHID==INVALID_HANDLE_VALUE)
	{
		m_ctrlStatus.SetWindowText("设备尚未连接!");
		return ;
	}
	if(!CH9326ReadIOData(m_hHID,&data)){
		AfxMessageBox("读io失败");
	}else{
		m_wIOData = (data & 0xFFF0);
		OnCheckRadioState();
	}
}

void CCH9326SetCfgDlg::OnCheckVid() 
{
	// TODO: Add your control notification handler code here
	if( IsDlgButtonChecked(IDC_CHECK_VID) ){
		GetDlgItem(IDC_EDIT_VID)->EnableWindow(TRUE);  
	}else{ 
		GetDlgItem(IDC_EDIT_VID)->EnableWindow(FALSE);  
	}
}

void CCH9326SetCfgDlg::OnCheckPid() 
{
	// TODO: Add your control notification handler code here
	if( IsDlgButtonChecked(IDC_CHECK_PID) )
		GetDlgItem(IDC_EDIT_PID)->EnableWindow(TRUE);  
	else 
		GetDlgItem(IDC_EDIT_PID)->EnableWindow(FALSE); 
}

void CCH9326SetCfgDlg::OnCheckMs() 
{
	// TODO: Add your control notification handler code here
	if( IsDlgButtonChecked(IDC_CHECK_MS) )
		GetDlgItem(IDC_EDIT_MSTRING)->EnableWindow(TRUE);  
	else 
		GetDlgItem(IDC_EDIT_MSTRING)->EnableWindow(FALSE);
}

void CCH9326SetCfgDlg::OnCheckPs() 
{
	// TODO: Add your control notification handler code here
	if( IsDlgButtonChecked(IDC_CHECK_PS) )
		GetDlgItem(IDC_EDIT_PSTRING)->EnableWindow(TRUE);  
	else 
		GetDlgItem(IDC_EDIT_PSTRING)->EnableWindow(FALSE);
}

void CCH9326SetCfgDlg::OnCheckSs() 
{
	// TODO: Add your control notification handler code here
	if( IsDlgButtonChecked(IDC_CHECK_SS) )
		GetDlgItem(IDC_EDIT_SSTRING)->EnableWindow(TRUE);  
	else 
		GetDlgItem(IDC_EDIT_SSTRING)->EnableWindow(FALSE);
}

void CCH9326SetCfgDlg::OnButtonSetDefualt() 
{
	// TODO: Add your control notification handler code here
	if(m_hHID==INVALID_HANDLE_VALUE){
		m_ctrlStatus.SetWindowText("设备尚未连接!");
	}

	CH9326ResetToDefault(m_hHID);
}
