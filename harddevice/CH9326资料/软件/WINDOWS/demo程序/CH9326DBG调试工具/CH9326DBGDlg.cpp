// CH9326DBGDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CH9326DBG.h"
#include "CH9326DBGDlg.h"

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

VOID  DbgPrint (LPCTSTR lpFormat,...)
{
   CHAR TextBufferTmp[500]="";    
   
   va_list arglist;
   va_start(arglist, lpFormat);
   vsprintf(TextBufferTmp,lpFormat,arglist);
   va_end(arglist);
   strcat(TextBufferTmp,"\r\n");
   OutputDebugString(TextBufferTmp);
   return ;
}
UINT  SendThreadFunction(LPVOID lpParameter)
{

	CCH9326DBGDlg * pThis  = (CCH9326DBGDlg *)lpParameter;
	HANDLE hEventObject=CreateEvent(NULL,TRUE,TRUE,"");

	if(pThis->m_hHID==INVALID_HANDLE_VALUE)
	{
		pThis->m_ctrlStatus.SetWindowText("设备尚未连接!");
		return 0;
	}
	
	UCHAR buf[64],len;
	UCHAR OutputReport[64];
	memset(buf,0,64);
	memset(OutputReport,0,64);
	len = pThis->m_strBuf.GetLength();
	if( len > 62)  len = 62;		//CH9326WriteData一次最大只能发送31个字节
	memcpy(buf,pThis->m_strBuf,len);
	
	for( UINT i = 0,j=0 ; buf[i] != 0 ; i+=2,j++)
	{
		OutputReport[j] = (UCHAR)( (mCharToBcd(buf[i]))<<4 ) + mCharToBcd(buf[i+1]);
	}
	len = j;
	if(!CH9326WriteData(pThis->m_hHID,OutputReport,len,hEventObject)) {
		pThis->m_ctrlStatus.SetWindowText("发送数失败");
	}

	CloseHandle(hEventObject);
	return 0;
}	

UINT  RecvThreadFunction(LPVOID lpParameter   )
{
	UCHAR recvDataBuf[1024];
	CCH9326DBGDlg * pThis  = (CCH9326DBGDlg *)lpParameter;

	if(pThis->m_hHID==INVALID_HANDLE_VALUE)
	{
		pThis->m_ctrlStatus.SetWindowText("设备尚未连接!");
		return 0;
	}
	if(!CH9326InitThreadData(pThis->m_hHID)){
		pThis->m_ctrlStatus.SetWindowText("CH9326InitThreadData Error");
		return 0;
	}
	pThis->m_bStop = 0;
	pThis->m_cbRecv.EnableWindow(FALSE);
	while(!pThis->m_bStop)
	{
		
		ULONG len = sizeof(recvDataBuf);
		if(!CH9326ReadThreadData(pThis->m_hHID,recvDataBuf,&len) ) break;
		if(len != 0)
		{
			CHAR tem[1024*3];
			memset(tem,0,sizeof(tem));
			for(UINT i=0,j=0;i< len ;i++,j+=3)
			{
				sprintf(&tem[j],"%02X ",(UCHAR)recvDataBuf[i]);
			}

			
			pThis->m_ctrlRecv.AppendText(tem);
			CString st;
			pThis->m_uRecvED += len;
			st.Format("已接受:%d",pThis->m_uRecvED);
			pThis->m_mRecvED.SetWindowText(st);
		}
		
	}
	CH9326StopThread(pThis->m_hHID);
	DbgPrint("RecvThreadFunction Exit");
	pThis->m_cbRecv.EnableWindow();
	
	return 0;
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
// CCH9326DBGDlg dialog

CCH9326DBGDlg::CCH9326DBGDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCH9326DBGDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCH9326DBGDlg)
	m_strBuf = _T("");
	m_uRecvED = 0;
	
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCH9326DBGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCH9326DBGDlg)
	DDX_Control(pDX, IDC_BUTTON_RECV, m_cbRecv);
	DDX_Control(pDX, IDC_EDIT_RECVED, m_mRecvED);
	DDX_Control(pDX, IDC_EDIT_STATUS, m_ctrlStatus);
	DDX_Control(pDX, IDC_EDIT_RECV, m_ctrlRecv);
	DDX_Control(pDX, IDC_EDIT_CHABA, m_ctrlCHABA);
	DDX_Control(pDX, IDC_COMBO_STOP, m_ctrlStop);
	DDX_Control(pDX, IDC_COMBO_SELECT_DEV, m_ctrlSelDev);
	DDX_Control(pDX, IDC_COMBO_RATE, m_ctrlRate);
	DDX_Control(pDX, IDC_COMBO_DATA, m_ctrlData);
	DDX_Control(pDX, IDC_COMBO_CHECK, m_ctrlCheck);
	DDX_Text(pDX, IDC_EDIT_SEND, m_strBuf);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCH9326DBGDlg, CDialog)
	//{{AFX_MSG_MAP(CCH9326DBGDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_DEVICECHANGE,OnDeviceNotification)
	ON_MESSAGE(MM_MYCHANGEDEVICE,OnMyChangeDevice)
	ON_CBN_SELCHANGE(IDC_COMBO_CHECK, OnSelchangeComboCheck)
	ON_CBN_SELCHANGE(IDC_COMBO_DATA, OnSelchangeComboData)
	ON_CBN_SELCHANGE(IDC_COMBO_RATE, OnSelchangeComboRate)
	ON_CBN_SELCHANGE(IDC_COMBO_STOP, OnSelchangeComboStop)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, OnButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_SETREPORT, OnButtonSetreport)
	ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_RECV, OnButtonRecv)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnButtonClear)
	ON_BN_CLICKED(IDC_RADIO_IO1_INPUT, OnRadioIo1Input)
	ON_BN_CLICKED(IDC_RADIO_IO1_OUTPUT, OnRadioIo1Output)
	ON_BN_CLICKED(IDC_RADIO_IO1_HIGH, OnRadioIo1High)
	ON_BN_CLICKED(IDC_RADIO_IO1_LOW, OnRadioIo1Low)
	ON_BN_CLICKED(IDC_RADIO_IO2_INPUT, OnRadioIo2Input)
	ON_BN_CLICKED(IDC_RADIO_IO2_OUTPUT, OnRadioIo2Output)
	ON_BN_CLICKED(IDC_RADIO_IO2_HIGH, OnRadioIo2High)
	ON_BN_CLICKED(IDC_RADIO_IO2_LOW, OnRadioIo2Low)
	ON_BN_CLICKED(IDC_BUTTON_SETIO, OnButtonSetio)
	ON_BN_CLICKED(IDC_BUTTON_GETIO, OnButtonGetio)
	ON_BN_CLICKED(IDC_RADIO_IO3_INPUT, OnRadioIo3Input)
	ON_BN_CLICKED(IDC_RADIO_IO3_OUTPUT, OnRadioIo3Output)
	ON_BN_CLICKED(IDC_RADIO_IO3_HIGH, OnRadioIo3High)
	ON_BN_CLICKED(IDC_RADIO_IO3_LOW, OnRadioIo3Low)
	ON_BN_CLICKED(IDC_RADIO_IO4_INPUT, OnRadioIo4Input)
	ON_BN_CLICKED(IDC_RADIO_IO4_OUTPUT, OnRadioIo4Output)
	ON_BN_CLICKED(IDC_RADIO_IO4_HIGH, OnRadioIo4High)
	ON_BN_CLICKED(IDC_RADIO_IO4_LOW, OnRadioIo4Low)
	ON_BN_CLICKED(IDC_BUTTON_SET_OUTPUT, OnButtonSetOutput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCH9326DBGDlg message handlers

BOOL CCH9326DBGDlg::OnInitDialog()
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
	
	InitSelDev();
	m_wIODir = 0;
	m_wIOData = 0;

	m_ucRate = 6;
	m_ucCheck = 4;
	m_ucStop = 1;
	m_ucData = 4;
	m_ucInterval = 0x40;
	OnCheckRadioState();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCH9326DBGDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCH9326DBGDlg::OnPaint() 
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
HCURSOR CCH9326DBGDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
LRESULT CCH9326DBGDlg::OnDeviceNotification(WPARAM wParam, LPARAM lParam)
{
	PDEV_BROADCAST_DEVICEINTERFACE	DevInfo;
	ULONG	mEventStatus;
	BOOL bCurrentDev = FALSE;
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
			//CH9326GetDevicePath返回的字符串全转化成大写
			CharUpperBuff(( LPTSTR )&DevInfo -> dbcc_name,strlen(( LPTSTR )&DevInfo -> dbcc_name));
			if(strcmp(m_strDevPath,DevInfo -> dbcc_name) == 0 )
			{
				bCurrentDev = TRUE;
				
			}
			PostMessage(MM_MYCHANGEDEVICE,(DWORD)mEventStatus,(DWORD)bCurrentDev);
		}
		return 0;
	}
	return 0;
}
LRESULT CCH9326DBGDlg::OnMyChangeDevice(WPARAM wParam, LPARAM lParam)
{
	BOOL bCurrentDev;
	bCurrentDev = (BOOL)lParam;
	if( wParam == DEVICE_ARRIVAL ){
		m_ctrlCHABA.SetWindowText("有HID设备到达");
		
	}else{
		m_ctrlCHABA.SetWindowText("有HID设备离开");
		//m_bFileStop = 1;
		if(bCurrentDev)
		{
			m_bStop = 1;
			if(m_hHID != INVALID_HANDLE_VALUE)
				CH9326CloseDevice(m_hHID);
			m_hHID = INVALID_HANDLE_VALUE;
			memset(m_strDevPath,0,sizeof(m_strDevPath));
		}
	}
	m_ctrlSelDev.ResetContent();
	InitSelDev();
	
	return 0;
}

void CCH9326DBGDlg::InitSelDev()
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

void CCH9326DBGDlg::OnSelchangeComboCheck() 
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

void CCH9326DBGDlg::OnSelchangeComboData() 
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

void CCH9326DBGDlg::OnSelchangeComboRate() 
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

void CCH9326DBGDlg::OnSelchangeComboStop() 
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

void CCH9326DBGDlg::OnButtonOpen() 
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
		memset(m_strDevPath,0,sizeof(m_strDevPath));
		strcpy(m_strDevPath,(PCHAR)LPCTSTR (strDev));
	}

}

void CCH9326DBGDlg::OnButtonSetreport() 
{
	// TODO: Add your control notification handler code here
	if(m_hHID==INVALID_HANDLE_VALUE){
		m_ctrlStatus.SetWindowText("设备尚未连接!");
	}


	if(!CH9326SetRate(m_hHID,m_ucRate,m_ucCheck,m_ucStop,m_ucData,m_ucInterval)) AfxMessageBox("设置不成功!");
	else{
		AfxMessageBox("设置成功!");
	}
}

void CCH9326DBGDlg::OnButtonSend() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	AfxBeginThread(SendThreadFunction,this,THREAD_PRIORITY_NORMAL,0,0,NULL); 
}

void CCH9326DBGDlg::OnButtonRecv() 
{
	// TODO: Add your control notification handler code here
	AfxBeginThread(RecvThreadFunction,this,THREAD_PRIORITY_NORMAL,0,0,NULL); 
}

void CCH9326DBGDlg::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	m_bStop = 1;
}

void CCH9326DBGDlg::OnButtonClear() 
{
	// TODO: Add your control notification handler code here
	CString st;
	m_uRecvED = 0;
	st.Format("已接受:%d",m_uRecvED);
	m_mRecvED.SetWindowText(st);

	m_ctrlRecv.SetWindowText("");
}

void CCH9326DBGDlg::OnCheckRadioState()
{
	if(m_wIODir & 0x01){
		CheckRadioButton(IDC_RADIO_IO1_INPUT,IDC_RADIO_IO1_OUTPUT,IDC_RADIO_IO1_OUTPUT);
		GetDlgItem(IDC_RADIO_IO1_HIGH)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO_IO1_LOW)->EnableWindow(TRUE);
	}else{
		CheckRadioButton(IDC_RADIO_IO1_INPUT,IDC_RADIO_IO1_OUTPUT,IDC_RADIO_IO1_INPUT);
		GetDlgItem(IDC_RADIO_IO1_HIGH)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO_IO1_LOW)->EnableWindow(FALSE);
	}
	if(m_wIODir & 0x02){
		CheckRadioButton(IDC_RADIO_IO2_INPUT,IDC_RADIO_IO2_OUTPUT,IDC_RADIO_IO2_OUTPUT);
		GetDlgItem(IDC_RADIO_IO2_HIGH)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO_IO2_LOW)->EnableWindow(TRUE);
	}else{
		CheckRadioButton(IDC_RADIO_IO2_INPUT,IDC_RADIO_IO2_OUTPUT,IDC_RADIO_IO2_INPUT);
		GetDlgItem(IDC_RADIO_IO2_HIGH)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO_IO2_LOW)->EnableWindow(FALSE);
	}
	
	if(m_wIODir & 0x04){
		CheckRadioButton(IDC_RADIO_IO3_INPUT,IDC_RADIO_IO3_OUTPUT,IDC_RADIO_IO3_OUTPUT);
		GetDlgItem(IDC_RADIO_IO3_HIGH)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO_IO3_LOW)->EnableWindow(TRUE);
	}else{
		CheckRadioButton(IDC_RADIO_IO3_INPUT,IDC_RADIO_IO3_OUTPUT,IDC_RADIO_IO3_INPUT);
		GetDlgItem(IDC_RADIO_IO3_HIGH)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO_IO3_LOW)->EnableWindow(FALSE);
	}
	

	if(m_wIODir & 0x08){
		CheckRadioButton(IDC_RADIO_IO4_INPUT,IDC_RADIO_IO4_OUTPUT,IDC_RADIO_IO4_OUTPUT);
		GetDlgItem(IDC_RADIO_IO4_HIGH)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO_IO4_LOW)->EnableWindow(TRUE);
	}else{
		CheckRadioButton(IDC_RADIO_IO4_INPUT,IDC_RADIO_IO4_OUTPUT,IDC_RADIO_IO4_INPUT);
		GetDlgItem(IDC_RADIO_IO4_HIGH)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO_IO4_LOW)->EnableWindow(FALSE);
	}

	if(m_wIOData & 0x01){
		CheckRadioButton(IDC_RADIO_IO1_HIGH,IDC_RADIO_IO1_LOW,IDC_RADIO_IO1_HIGH);
	}else{
		CheckRadioButton(IDC_RADIO_IO1_HIGH,IDC_RADIO_IO1_LOW,IDC_RADIO_IO1_LOW);
	}

	if(m_wIOData & 0x02){
		CheckRadioButton(IDC_RADIO_IO2_HIGH,IDC_RADIO_IO2_LOW,IDC_RADIO_IO2_HIGH);
	}else{
		CheckRadioButton(IDC_RADIO_IO2_HIGH,IDC_RADIO_IO2_LOW,IDC_RADIO_IO2_LOW);
	}
	if(m_wIOData & 0x04){
		CheckRadioButton(IDC_RADIO_IO3_HIGH,IDC_RADIO_IO3_LOW,IDC_RADIO_IO3_HIGH);
	}else{
		CheckRadioButton(IDC_RADIO_IO3_HIGH,IDC_RADIO_IO3_LOW,IDC_RADIO_IO3_LOW);
	}
	if(m_wIOData & 0x08){
		CheckRadioButton(IDC_RADIO_IO4_HIGH,IDC_RADIO_IO4_LOW,IDC_RADIO_IO4_HIGH);
	}else{
		CheckRadioButton(IDC_RADIO_IO4_HIGH,IDC_RADIO_IO4_LOW,IDC_RADIO_IO4_LOW);
	}
}

void CCH9326DBGDlg::OnRadioIo1Input() 
{
	// TODO: Add your control notification handler code here
	m_wIODir &=0xFFFE;
	OnCheckRadioState();
}

void CCH9326DBGDlg::OnRadioIo1Output() 
{
	// TODO: Add your control notification handler code here
	m_wIODir |=0x01;
	OnCheckRadioState();
}

void CCH9326DBGDlg::OnRadioIo1High() 
{
	// TODO: Add your control notification handler code here
	m_wIOData |= 0x01;
	OnCheckRadioState();
}

void CCH9326DBGDlg::OnRadioIo1Low() 
{
	// TODO: Add your control notification handler code here
	m_wIOData &= 0xFFFE;
	OnCheckRadioState();
}

void CCH9326DBGDlg::OnRadioIo2Input() 
{
	// TODO: Add your control notification handler code here
	m_wIODir &=0xFFFD;
	OnCheckRadioState();
}

void CCH9326DBGDlg::OnRadioIo2Output() 
{
	// TODO: Add your control notification handler code here
	m_wIODir |=0x02;
	OnCheckRadioState();
}

void CCH9326DBGDlg::OnRadioIo2High() 
{
	// TODO: Add your control notification handler code here
	m_wIOData |= 0x02;
	OnCheckRadioState();
}

void CCH9326DBGDlg::OnRadioIo2Low() 
{
	// TODO: Add your control notification handler code here
	m_wIOData &= 0xFFFD;
	OnCheckRadioState();
}

void CCH9326DBGDlg::OnButtonSetio() 
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

void CCH9326DBGDlg::OnButtonGetio() 
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
		m_wIOData = (data & 0x000F);
		OnCheckRadioState();
	}
}

void CCH9326DBGDlg::OnRadioIo3Input() 
{
	// TODO: Add your control notification handler code here
	m_wIODir &=0xFFFB;
	OnCheckRadioState();
}

void CCH9326DBGDlg::OnRadioIo3Output() 
{
	// TODO: Add your control notification handler code here
	m_wIODir |=0x04;
	OnCheckRadioState();
}

void CCH9326DBGDlg::OnRadioIo3High() 
{
	// TODO: Add your control notification handler code here
	m_wIOData |= 0x04;
	OnCheckRadioState();
}

void CCH9326DBGDlg::OnRadioIo3Low() 
{
	// TODO: Add your control notification handler code here
	m_wIOData &= 0xFFFB;
	OnCheckRadioState();
}

void CCH9326DBGDlg::OnRadioIo4Input() 
{
	// TODO: Add your control notification handler code here
	m_wIODir &=0xFFF7;
	OnCheckRadioState();
}

void CCH9326DBGDlg::OnRadioIo4Output() 
{
	// TODO: Add your control notification handler code here
	m_wIODir |=0x08;
	OnCheckRadioState();
}

void CCH9326DBGDlg::OnRadioIo4High() 
{
	// TODO: Add your control notification handler code here
	m_wIOData |= 0x08;
	OnCheckRadioState();
}

void CCH9326DBGDlg::OnRadioIo4Low() 
{
	// TODO: Add your control notification handler code here
	m_wIOData &= 0xFFF7;
	OnCheckRadioState();
}

void CCH9326DBGDlg::OnButtonSetOutput() 
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
