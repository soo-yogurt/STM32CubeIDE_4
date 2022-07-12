
// MFCApplication16Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication16.h"
#include "MFCApplication16Dlg.h"
#include "afxdialogex.h"
#include <stdio.h>
#include "string.h"
#include <vector>

using std::vector;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:

};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)

END_MESSAGE_MAP()


// CMFCApplication16Dlg 대화 상자



CMFCApplication16Dlg::CMFCApplication16Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION16_DIALOG, pParent)
	, m_str_comport(_T(""))
	, m_combo_baudrate(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication16Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo_comport_list);
	DDX_Control(pDX, IDC_COMBO2, m_combo_baudrate_list);
	DDX_CBString(pDX, IDC_COMBO1, m_str_comport);
	DDX_CBString(pDX, IDC_COMBO2, m_combo_baudrate);
	DDX_Control(pDX, IDC_EDIT_RCV_VIEW1, m_edit_rcv_view_1);
	DDX_Control(pDX, IDC_EDIT_RCV_VIEW2, m_edit_rcv_view_2);
	DDX_Control(pDX, IDC_EDIT_RCV_VIEW3, m_edit_rcv_view_3);
}

BEGIN_MESSAGE_MAP(CMFCApplication16Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LED_1, &CMFCApplication16Dlg::OnBnClickedButtonLed1)
	ON_BN_CLICKED(IDC_BUTTON_LED_2, &CMFCApplication16Dlg::OnBnClickedButtonLed2)
	ON_BN_CLICKED(IDC_BUTTON_LED_3, &CMFCApplication16Dlg::OnBnClickedButtonLed3)
	ON_BN_CLICKED(IDC_BT_CONNECT, &CMFCApplication16Dlg::OnBnClickedBtConnect)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMFCApplication16Dlg::OnCbnSelchangeComboComport)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CMFCApplication16Dlg::OnCbnSelchangeComboBaudrate)


	ON_MESSAGE(WM_MYCLOSE, &CMFCApplication16Dlg::OnThreadClosed)
	ON_MESSAGE(WM_MYRECEIVE, &CMFCApplication16Dlg::OnReceive)

END_MESSAGE_MAP()


// CMFCApplication16Dlg 메시지 처리기

BOOL CMFCApplication16Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_edit_rcv_view_1.ReplaceSel(_T("LED 1번의 상태는"));
	m_edit_rcv_view_2.ReplaceSel(_T("LED 2번의 상태는"));
	m_edit_rcv_view_3.ReplaceSel(_T("LED 3번의 상태는"));


	m_combo_comport_list.AddString(_T("COM1"));
	m_combo_comport_list.AddString(_T("COM2"));
	m_combo_comport_list.AddString(_T("COM3"));
	m_combo_comport_list.AddString(_T("COM4"));
	m_combo_comport_list.AddString(_T("COM5"));
	m_combo_comport_list.AddString(_T("COM6"));
	m_combo_comport_list.AddString(_T("COM7"));
	m_combo_comport_list.AddString(_T("COM8"));
	m_combo_comport_list.AddString(_T("COM9"));
	m_combo_comport_list.AddString(_T("COM10"));

	m_combo_baudrate_list.AddString(_T("9600"));
	m_combo_baudrate_list.AddString(_T("19200"));
	m_combo_baudrate_list.AddString(_T("115200"));


	comport_state = false;
	GetDlgItem(IDC_BT_CONNECT)->SetWindowText(_T("OPEN"));
	m_str_comport = _T("COM6");
	m_combo_baudrate = _T("115200");
	UpdateData(FALSE);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCApplication16Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplication16Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplication16Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


LRESULT	CMFCApplication16Dlg::OnThreadClosed(WPARAM length, LPARAM lpara)
{
	((CSerialComm*)lpara)->HandleClose();
	delete ((CSerialComm*)lpara);

	return 0;
}

#define MODE
vector<char> rxBuffer;


LRESULT CMFCApplication16Dlg::OnReceive(WPARAM length, LPARAM lpara)
{
	CString str;

#ifdef MODE
	CString led1 = 0;
	CString led2 = 0;
	CString led3 = 0;
	int flag = 0;
#else MODE
	uint8_t led1 = 0;
	uint8_t led2 = 0;
	uint8_t led3 = 0;
#endif MODE

	
	char* data = new char[length + 1];

	if (m_comm)
	{
		m_comm->Receive(data, length);	// Length 길이만큼 데이터 받음.

		if (flag == 0) {
			for (unsigned int i = 0; i < length; i++)
			{
				rxBuffer.push_back(data[i]);
			}
			for (unsigned int i = 0; i < length; i++)
			{
				if (rxBuffer.at(0) != '<')
					rxBuffer.erase(rxBuffer.begin());
				else if (rxBuffer.at(0) == '<') {
					if (rxBuffer.at(1) == 'L' && rxBuffer.at(2) == 'E' && rxBuffer.at(3) == 'D')
					{ 
						if (rxBuffer.at(4) == '3' && rxBuffer.at(8) == '>') {
							led1 == rxBuffer.at(5);
							led2 == rxBuffer.at(6);
						}
					}


				}
			}
		}
		else if (flag == 1) {
			for (unsigned int i = 0; i < length; i++)
			{
				rxBuffer.push_back(data[i]);
			}
		}



	
		 




		//if (rxBuffer.size() > 9 && (rxBuffer.at(0) != '<'))
		//{
		//	rxBuffer.clear();
		//	vector<char>().swap(rxBuffer);
		//}
		//else if (str.GetLength() >= 8)
		//{
		//	if (rxBuffer.at(0) == '<' && rxBuffer.at(8) == '>') {
		//		for (unsigned int i = 0; i < rxBuffer.size(); i++) {
		//			str += rxBuffer.at(i);
		//		}
		//	}
		//}		
		m_edit_rcv_view_1.ReplaceSel(str);
		UpdateData(true);
	}
	
#ifdef MODE
	if (str.GetLength() >= 8) {
		if ((str[8] == '>') && (str[0] == '<')) {
			if ((str.Find("<LED3") != -1)) {
				led1 = rxBuffer.at(5);
				led2 = rxBuffer.at(6);
				led3 = rxBuffer.at(7);
			}

			if (led1 == '0')
			{
				m_edit_rcv_view_1.SetWindowTextA(_T("OFF"));
			}
			else if (led1 == '1')
			{
				m_edit_rcv_view_1.SetWindowTextA(_T("ON"));
			}

			if (led2 == '0')
			{
				m_edit_rcv_view_2.SetWindowTextA(_T("OFF"));
			}
			else if (led2 == '1')
			{
				m_edit_rcv_view_2.SetWindowTextA(_T("ON"));
			}

			if (led3 == '0')
			{
				m_edit_rcv_view_3.SetWindowTextA(_T("OFF"));
			}
			else if (led3 == '1')
			{
				m_edit_rcv_view_3.SetWindowTextA(_T("ON"));
			}
			rxBuffer.clear();
			vector<char>().swap(rxBuffer);
		}
	}

#else MODE

	if ((data[8] == '>') && (data[0] == '<')) {
		char* p;
		if ((p = strstr((char*)data, "<LED3")) != 0) {
			led1 = *(p + 5) - '0';
			led2 = *(p + 6) - '0';
			led3 = *(p + 7) - '0';
		}

		if (led1 == 0)
		{
			m_edit_rcv_view_1.SetWindowTextA(_T("OFF"));
		}
		else if (led1 == 1)
		{
			m_edit_rcv_view_1.SetWindowTextA(_T("ON"));
		}

		if (led2 == 0)
		{
			m_edit_rcv_view_2.SetWindowTextA(_T("OFF"));
		}
		else if (led2 == 1)
		{
			m_edit_rcv_view_2.SetWindowTextA(_T("ON"));
		}

		if (led3 == 0)
		{
			m_edit_rcv_view_3.SetWindowTextA(_T("OFF"));
		}
		else if (led3 == 1)
		{
			m_edit_rcv_view_3.SetWindowTextA(_T("ON"));
		}
}
#endif MODE
	delete []data;
	return 0;
}


void CMFCApplication16Dlg::OnBnClickedBtConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (comport_state)
	{
		if (m_comm)        //컴포트가존재하면
		{
			m_comm->Close();
			m_comm = NULL;
			AfxMessageBox(_T("COM 포트닫힘"));
			comport_state = false;
			GetDlgItem(IDC_BT_CONNECT)->SetWindowText(_T("OPEN"));
			GetDlgItem(IDC_BUTTON_LED_1)->EnableWindow(false);
			GetDlgItem(IDC_BUTTON_LED_2)->EnableWindow(false);
			GetDlgItem(IDC_BUTTON_LED_3)->EnableWindow(false);
		}
	}
	else
	{
		m_comm = new CSerialComm(_T("\\\\.\\") + m_str_comport, m_combo_baudrate, _T("None"), _T("8 Bit"), _T("1 Bit"));         // initial Comm port
		if (m_comm->Create(GetSafeHwnd()) != 0) //통신포트를열고윈도우의핸들을넘긴다.
		{
			AfxMessageBox(_T("COM 포트열림"));
			comport_state = true;
			GetDlgItem(IDC_BT_CONNECT)->SetWindowText(_T("CLOSE"));
			GetDlgItem(IDC_BUTTON_LED_1)->EnableWindow(true);
			GetDlgItem(IDC_BUTTON_LED_2)->EnableWindow(true);
			GetDlgItem(IDC_BUTTON_LED_3)->EnableWindow(true);
		}
		else
		{
			AfxMessageBox(_T("ERROR!"));
		}

	}
}


void CMFCApplication16Dlg::OnCbnSelchangeComboComport()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
}




void CMFCApplication16Dlg::OnCbnSelchangeComboBaudrate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
}

void CMFCApplication16Dlg::OnBnClickedButtonLed1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;

	str += _T("<LED3100>\n");
	m_comm->Send(str, str.GetLength());
}


void CMFCApplication16Dlg::OnBnClickedButtonLed2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	str += _T("<LED3010>\n");
	m_comm->Send(str, str.GetLength());
}


void CMFCApplication16Dlg::OnBnClickedButtonLed3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	str += _T("<LED3001>\n");
	m_comm->Send(str, str.GetLength());
}
