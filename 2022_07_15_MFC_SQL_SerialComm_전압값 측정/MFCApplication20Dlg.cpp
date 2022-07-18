
// MFCApplication20Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication20.h"
#include "MFCApplication20Dlg.h"
#include "afxdialogex.h"
#include <vector>
#include "CValueData.h"
#include "CMysqlController.h"

using std::vector;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int flag = 0;

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

	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMFCApplication20Dlg 대화 상자



CMFCApplication20Dlg::CMFCApplication20Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION20_DIALOG, pParent)
	, m_str_comport(_T(""))
	, m_combo_baudrate(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication20Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO3, m_combo_comport_list);
	DDX_Control(pDX, IDC_COMBO2, m_combo_baudrate_list);
	DDX_CBString(pDX, IDC_COMBO3, m_str_comport);
	DDX_CBString(pDX, IDC_COMBO2, m_combo_baudrate);
	DDX_Control(pDX, IDC_EDIT1, m_receive_value_now_data);
	DDX_Control(pDX, IDC_LIST2, m_value_1_data_list);
	DDX_Control(pDX, IDC_LIST3, m_value_2_data_list);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_datatime_picker);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_time_picker);
	DDX_Control(pDX, IDC_SLIDER_CONTROL, m_slider);
	DDX_Control(pDX, IDC_SLIDER_VALUE, m_slider_value);
}

BEGIN_MESSAGE_MAP(CMFCApplication20Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_BT_CONNECT, &CMFCApplication20Dlg::OnBnClickedBtConnect)
ON_BN_CLICKED(IDC_BUTTON_READ_ADC, &CMFCApplication20Dlg::OnBnClickedButtonReadAdc)
ON_CBN_SELCHANGE(IDC_COMBO3, &CMFCApplication20Dlg::OnCbnSelchangeComboComport)
ON_CBN_SELCHANGE(IDC_COMBO2, &CMFCApplication20Dlg::OnCbnSelchangeComboBaudrate)

ON_MESSAGE(WM_MYCLOSE, &CMFCApplication20Dlg::OnThreadClosed)
ON_MESSAGE(WM_MYRECEIVE, &CMFCApplication20Dlg::OnReceive)

ON_BN_CLICKED(IDC_BUTTON1_RESET, &CMFCApplication20Dlg::OnBnClickedButton1Reset)
ON_BN_CLICKED(IDC_BUTTON2_RESET, &CMFCApplication20Dlg::OnBnClickedButton2Reset)
ON_WM_HSCROLL()
ON_EN_CHANGE(IDC_SLIDER_VALUE, &CMFCApplication20Dlg::OnEnChangeSliderValue)
ON_BN_CLICKED(IDC_RADIO_SELECT, &CMFCApplication20Dlg::OnBnClickedRadioSelect)
END_MESSAGE_MAP()


// CMFCApplication20Dlg 메시지 처리기

BOOL CMFCApplication20Dlg::OnInitDialog()
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

	m_value_1_data_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_value_1_data_list.InsertColumn(0, _T("ID"), LVCFMT_CENTER, 42);
	m_value_1_data_list.InsertColumn(1, _T("VALUE"), LVCFMT_CENTER, 100);
	m_value_1_data_list.InsertColumn(2, _T("TIME"), LVCFMT_CENTER, 200);

	m_value_2_data_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_value_2_data_list.InsertColumn(0, _T("ID"), LVCFMT_CENTER, 42);
	m_value_2_data_list.InsertColumn(1, _T("VALUE"), LVCFMT_CENTER, 100);
	m_value_2_data_list.InsertColumn(2, _T("TIME"), LVCFMT_CENTER, 200);


	GetDlgItem(IDC_BUTTON_READ_ADC)->EnableWindow(FALSE);


	m_slider.SetRange(0, 10);
	m_slider.SetPos(0);
	m_slider.SetLineSize(1);
	m_slider.SetPageSize(1);

	int iPos = m_slider.GetPos();
	CString sPos;
	sPos.Format(_T("%d"), iPos);
	m_slider_value.SetWindowTextA(sPos);
	


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}



void CMFCApplication20Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CMysqlController conn;

	char delete_tb_1[82] = "DELETE FROM tb_adc_button_1 WHERE TIME < DATE_ADD(NOW(), INTERVAL - 10 MINUTE)";
	char delete_tb_2[82] = "DELETE FROM tb_adc_button_2 WHERE TIME < DATE_ADD(NOW(), INTERVAL - 10 MINUTE)";

	if (conn.InsertQuery(delete_tb_1) == false)
	{
		AfxMessageBox(_T("실패"));
	}

	if (conn.InsertQuery(delete_tb_2) == false)
	{
		AfxMessageBox(_T("실패"));
	}

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

void CMFCApplication20Dlg::OnPaint()
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
HCURSOR CMFCApplication20Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


LRESULT	CMFCApplication20Dlg::OnThreadClosed(WPARAM length, LPARAM lpara)
{
	((CSerialComm*)lpara)->HandleClose();
	delete ((CSerialComm*)lpara);

	return 0;
}

vector<char> rxBuffer;

LRESULT CMFCApplication20Dlg::OnReceive(WPARAM length, LPARAM lpara)
{
	CMysqlController conn;
	CString cstr;
	CString str;
	char* data = new char[length + 1];
	int vectorSize;


	if (m_comm)
	{
		m_comm->Receive(data, length);	// Length 길이만큼 데이터 받음.

		for (unsigned int i = 0; i < length; i++)
		{
			rxBuffer.push_back(data[i]);
		}
		vectorSize = rxBuffer.size();
		for (int i = 0; i < vectorSize; i++)
		{
			if (vectorSize > 7 && rxBuffer.at(0) == 'B' && rxBuffer.at(6) == '>')
			{
				// ------------------------------ 버튼 1, 2 --------------------------------------------------------------
				if (rxBuffer.at(1) == '1' || rxBuffer.at(1) == '2') {
					cstr += "INSERT INTO tb_adc_button_";
					cstr += rxBuffer.at(1);
					cstr += "(value) VALUES (";
					cstr += rxBuffer.at(2);
					cstr += rxBuffer.at(3);
					cstr += rxBuffer.at(4);
					cstr += rxBuffer.at(5);
					cstr += ")";
					char* str = new char[cstr.GetLength() + 1];
					strcpy(str, cstr);
					if (conn.InsertQuery(str) == false)
					{
						AfxMessageBox(_T("실패"));
					}
					delete[] str;
					// 버튼 명령어 형식이 맞고 데이터가 처리되었을때 하나 지운다.
					rxBuffer.erase(rxBuffer.begin());
				}
			}// ------------------------------ Read 버튼 --------------------------------------------------------------
			else if (vectorSize > 7 && rxBuffer.at(0) == 'N') {
				if (rxBuffer.at(1) == 'o' && rxBuffer.at(2) == 'w')
				{
					if (rxBuffer.at(7) == '>') {
						str = "";
						str += rxBuffer.at(3);
						str += rxBuffer.at(4);
						str += rxBuffer.at(5);
						str += rxBuffer.at(6);
					}
					m_receive_value_now_data.ReplaceSel(str);
					// 버튼 명령어 형식이 맞고 데이터가 처리되었을때 하나 지운다.
					rxBuffer.erase(rxBuffer.begin());
				}
				else if (rxBuffer.at(1) != 'o')
					// 잘못된 데이터가 들어왔을 경우 지우는 부분이다.
					rxBuffer.erase(rxBuffer.begin());
				// 잘못된 데이터가 들어왔을 경우 지우는 부분이다.
				else if (rxBuffer.at(1) == 'o' && rxBuffer.at(2) != 'w')
					rxBuffer.erase(rxBuffer.begin());
			}// ------------------------------------------------------------------------------------------------
				// 잘못된 데이터가 들어왔을 경우 지우는 부분이다.
			else if (rxBuffer.at(0) != 'N' && rxBuffer.at(0) != 'B')
				rxBuffer.erase(rxBuffer.begin());
		}
	}
	delete[]data;
	return 0;
}










void CMFCApplication20Dlg::OnBnClickedBtConnect()
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
			GetDlgItem(IDC_BUTTON_READ_ADC)->EnableWindow(TRUE);
		}
		else
		{
			AfxMessageBox(_T("ERROR!"));
		}
	}
}


void CMFCApplication20Dlg::OnBnClickedButtonReadAdc()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	// 해당 내용이 전송되면 value값을 돌려 받는다.

	str += _T("<ReturnToValue>\n");
	m_comm->Send(str, str.GetLength());
	m_receive_value_now_data.SetSel(0, -1); // 처음부터 끝까지 선택
	m_receive_value_now_data.Clear(); // 선택한 부분을 지운다.
}

// 시간을 초로 계산해서 해보자
void CMFCApplication20Dlg::OnBnClickedButton1Reset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMysqlController conn;
	vector<CValueData*> table_1_data;
	
	// db_시간을 저장하기 위한 변수들
	CString date, year, month, day;
	CString time, hour, min;

	// Date time picker에서 설정한 값을 저장할 변수
	CString sel_time, sel_AMPM;
	CString sel_hour, sel_minute, sel_second;
	int sel_year, sel_month, sel_day;
	
	// 슬라이더로 추가한 값을 저장하는 변수
	CString sPos;


	m_datatime_picker.GetTime(sel_date);
	m_time_picker.GetWindowTextA(user_set_time);

	UpdateData();

	sel_year = sel_date.GetYear();
	sel_month = sel_date.GetMonth();
	sel_day = sel_date.GetDay();


	AfxExtractSubString(sel_AMPM, user_set_time, 0, ' ');
	AfxExtractSubString(sel_time, user_set_time, 1, ' ');
	
	
	AfxExtractSubString(sel_hour, sel_time, 0, ':');
	AfxExtractSubString(sel_minute, sel_time, 1, ':');
	AfxExtractSubString(sel_second, sel_time, 2, ':');
	


	m_value_1_data_list.DeleteAllItems();

	if (conn.SelectQuery("select * from tb_adc_button_1", table_1_data) == true)
	{
		/*for (int i = 0; i < datas.size(); i++) {
			AfxMessageBox(datas.at(i)->Getvalue());
		}*/
	}
	else
		AfxMessageBox("실패했습니다.");

	m_slider_value.GetWindowTextA(sPos); // 추가 조건 : 슬라이더 값

	if (((CButton*)GetDlgItem(IDC_RADIO_SELECT))->GetCheck() == 1)
	{
		unsigned int data_size = table_1_data.size();
		int j = 0;
		for (unsigned int i = 0; i < data_size; i++) {
			AfxExtractSubString(date, table_1_data.at(j)->Getime(), 0, ' ');
			AfxExtractSubString(year, date, 0, '-');
			AfxExtractSubString(month, date, 1, '-');
			AfxExtractSubString(day, date, 2, '-');

			AfxExtractSubString(time, table_1_data.at(j)->Getime(), 1, ' ');
			AfxExtractSubString(hour, time, 0, ':');
			AfxExtractSubString(min, time, 1, ':');

			int user_time;
			if (sel_AMPM == "오후") {
				user_time = (_ttoi(sel_hour) + 12) * 60 + _ttoi(sel_minute); //사용자가 설정한 시간을 분으로 나타낸다. 
			}
			else {
				user_time = _ttoi(sel_hour)* 60 + _ttoi(sel_minute); //사용자가 설정한 시간을 분으로 나타낸다. 
			}
			int db_time = _ttoi(hour) * 60 + _ttoi(min); //DB에서 받아온 시간을 분으로 나타낸다.

			// 예외처리를 위한 변수 날짜가 하루 넘어간 경우
			int _user_time = user_time + (sel_day * 1440); // 날짜 * 1440, 24시간 * 60 은 1440
			int _db_time = _ttoi(day) * 1440 + db_time;
			
			// 년 월 시가 같으면 if 문을 실행한다.
			if (_ttoi(year) == sel_year && _ttoi(month) == sel_month && _ttoi(day) == sel_day) {
				// time과 db_time의 시간을 비교해서 해당되면 유지 
				if (db_time >= user_time && db_time <= user_time + _ttoi(sPos)) {
					j++;
				}
				else table_1_data.erase(table_1_data.begin() + j); // 아니라면 삭제

			} // 날짜가 하루 넘어간 경우 예외 처리 
			else if (_ttoi(year) == sel_year && _ttoi(month) == sel_month && _ttoi(day) == (sel_day + 1)) {
				if (_db_time >= _user_time && _db_time <= _user_time + _ttoi(sPos)) {
					j++;
				}
				else  table_1_data.erase(table_1_data.begin() + j);
			}
			else  table_1_data.erase(table_1_data.begin() + j);
		}
	}


	for (unsigned int i = 0; i < table_1_data.size(); i++) {
		m_value_1_data_list.InsertItem(i, table_1_data.at(i)->Getid()); // ID
		m_value_1_data_list.SetItem(i, 1, LVIF_TEXT, table_1_data.at(i)->Getvalue(), NULL, NULL, NULL, NULL); // 값
		m_value_1_data_list.SetItem(i, 2, LVIF_TEXT, table_1_data.at(i)->Getime(), NULL, NULL, NULL, NULL); // 타임
	}

	for (unsigned int i = 0; i < table_1_data.size(); i++)
	{
		delete table_1_data[i];
	}

}


void CMFCApplication20Dlg::OnBnClickedButton2Reset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMysqlController conn;

	vector<CValueData*> table_2_datas;

	// db_시간을 저장하기 위한 변수들
	CString date, year, month, day;
	CString time, hour, min;

	// Date time picker에서 설정한 값을 저장할 변수
	CString sel_time, sel_AMPM;
	CString sel_hour, sel_minute, sel_second;
	int sel_year, sel_month, sel_day;

	// 슬라이더로 추가한 값을 저장하는 변수
	CString sPos;


	m_datatime_picker.GetTime(sel_date);
	m_time_picker.GetWindowTextA(user_set_time);

	UpdateData();

	sel_year = sel_date.GetYear();
	sel_month = sel_date.GetMonth();
	sel_day = sel_date.GetDay();


	AfxExtractSubString(sel_AMPM, user_set_time, 0, ' ');
	AfxExtractSubString(sel_time, user_set_time, 1, ' ');
	AfxExtractSubString(sel_hour, sel_time, 0, ':');
	AfxExtractSubString(sel_minute, sel_time, 1, ':');
	AfxExtractSubString(sel_second, sel_time, 2, ':');



	m_value_2_data_list.DeleteAllItems();

	if (conn.SelectQuery("select * from tb_adc_button_2", table_2_datas) == true)
	{
		/*for (int i = 0; i < datas.size(); i++) {
			AfxMessageBox(datas.at(i)->Getvalue());
		}*/
	}
	else
		AfxMessageBox("실패했습니다.");

	m_slider_value.GetWindowTextA(sPos); // 추가 조건 : 슬라이더 값

	if (((CButton*)GetDlgItem(IDC_RADIO_SELECT))->GetCheck() == 1)
	{
		unsigned int data_size = table_2_datas.size();
		int j = 0;
		for (unsigned int i = 0; i < data_size; i++) {
			AfxExtractSubString(date, table_2_datas.at(j)->Getime(), 0, ' ');
			AfxExtractSubString(year, date, 0, '-');
			AfxExtractSubString(month, date, 1, '-');
			AfxExtractSubString(day, date, 2, '-');

			AfxExtractSubString(time, table_2_datas.at(j)->Getime(), 1, ' ');
			AfxExtractSubString(hour, time, 0, ':');
			AfxExtractSubString(min, time, 1, ':');
			/* ------------------------------------------ sel_minute가 이상하게 넘어온다. -------------------- */
			int user_time;
			if (sel_AMPM == "오후") {
				user_time = (_ttoi(sel_hour) + 12) * 60 + _ttoi(sel_minute); //사용자가 설정한 시간을 분으로 나타낸다. 
			}
			else if (sel_AMPM == "오전") {
				user_time = _ttoi(sel_hour) * 60 + _ttoi(sel_minute); //사용자가 설정한 시간을 분으로 나타낸다. 
			}

			int db_time = _ttoi(hour) * 60 + _ttoi(min); //DB에서 받아온 시간을 분으로 나타낸다.

			// 예외처리를 위한 변수 날짜가 하루 넘어간 경우
			int _user_time = user_time + (sel_day * 1440); // 날짜 * 1440, 24시간 * 60 은 1440
			int _db_time = _ttoi(day) * 1440 + db_time;

			// 년 월 시가 같으면 if 문을 실행한다.
			if (_ttoi(year) == sel_year && _ttoi(month) == sel_month && _ttoi(day) == sel_day) {
				// time과 db_time의 시간을 비교해서 해당되면 유지 
				if (db_time >= user_time && db_time <= user_time + _ttoi(sPos)) {
					j++;
				}
				else table_2_datas.erase(table_2_datas.begin() + j); // 아니라면 삭제

			} // 날짜가 하루 넘어간 경우 예외 처리 
			else if (_ttoi(year) == sel_year && _ttoi(month) == sel_month && _ttoi(day) == (sel_day + 1)) {
				if (_db_time >= _user_time && _db_time <= _user_time + _ttoi(sPos)) {
					j++;
				}
				else  table_2_datas.erase(table_2_datas.begin() + j);
			}
			else  table_2_datas.erase(table_2_datas.begin() + j);
		}
	}

	for (unsigned int i = 0; i < table_2_datas.size(); i++) {
		m_value_2_data_list.InsertItem(i, table_2_datas.at(i)->Getid()); // ID
		m_value_2_data_list.SetItem(i, 1, LVIF_TEXT, table_2_datas.at(i)->Getvalue(), NULL, NULL, NULL, NULL); // 값
		m_value_2_data_list.SetItem(i, 2, LVIF_TEXT, table_2_datas.at(i)->Getime(), NULL, NULL, NULL, NULL); // 타임
	}

	for (unsigned int i = 0; i < table_2_datas.size(); i++)
	{
		delete table_2_datas[i];
	}
}


void CMFCApplication20Dlg::OnCbnSelchangeComboComport()
{
	UpdateData();
}



void CMFCApplication20Dlg::OnCbnSelchangeComboBaudrate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
}





void CMFCApplication20Dlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (IDC_SLIDER_CONTROL == pScrollBar->GetDlgCtrlID())
	{
		int iPos = m_slider.GetPos();
			CString sPos;
			sPos.Format(_T("%d"), iPos);
			m_slider_value.SetWindowTextA(sPos);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CMFCApplication20Dlg::OnEnChangeSliderValue()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sPos;
	m_slider_value.GetWindowTextA(sPos);
	int iPos = _ttoi(sPos);
	m_slider.SetPos(iPos);
}



void CMFCApplication20Dlg::OnBnClickedRadioSelect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData();

}




