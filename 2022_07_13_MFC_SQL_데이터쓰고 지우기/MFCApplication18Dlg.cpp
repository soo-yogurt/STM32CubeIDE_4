
// MFCApplication18Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication18.h"
#include "MFCApplication18Dlg.h"
#include "afxdialogex.h"
#include "CMysqlController.h"
#include "string.h"
#include "CbookData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

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


// CMFCApplication18Dlg 대화 상자



CMFCApplication18Dlg::CMFCApplication18Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION18_DIALOG, pParent)
	, m_edit_bookName(_T(""))
	, m_edit_author(_T(""))
	, m_edit_price(_T(""))
	, m_edit_other(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication18Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edit_bookName);
	DDX_Text(pDX, IDC_EDIT2, m_edit_author);
	DDX_Text(pDX, IDC_EDIT3, m_edit_price);
	DDX_Text(pDX, IDC_EDIT4, m_edit_other);
	DDX_Control(pDX, IDC_LIST2, m_list);
}

BEGIN_MESSAGE_MAP(CMFCApplication18Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication18Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, &CMFCApplication18Dlg::OnBnClickedButtonRefresh)
	ON_BN_CLICKED(IDC_DELETE_BUTTON, &CMFCApplication18Dlg::OnBnClickedDeleteButton)
END_MESSAGE_MAP()


// CMFCApplication18Dlg 메시지 처리기

BOOL CMFCApplication18Dlg::OnInitDialog()
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


	m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0, _T("ID"), LVCFMT_CENTER, 30);
	m_list.InsertColumn(1, _T("책이름"), LVCFMT_CENTER, 150);
	m_list.InsertColumn(2, _T("저자"), LVCFMT_CENTER, 150);
	m_list.InsertColumn(3, _T("가격"), LVCFMT_CENTER, 70);
	m_list.InsertColumn(4, _T("기타"), LVCFMT_CENTER, 50);
	

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCApplication18Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication18Dlg::OnPaint()
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
HCURSOR CMFCApplication18Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CMFCApplication18Dlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMysqlController conn;
	CString result;
	CString cstr;
	
	UpdateData(true);

	cstr += "Insert into TB_Book(bookname, author, price, other) VALUES(";
	cstr += '\'' + m_edit_bookName + "', '" + m_edit_author + "', " + m_edit_price + ", '" + m_edit_other +"')";
	char* str = new char[cstr.GetLength() + 1];
	strcpy(str, cstr);

	if (conn.InsertQuery(str) == true)
	{
		AfxMessageBox(_T("성공"));
	}
	else
	{
		AfxMessageBox(_T("실패"));
	}
	delete[] str;
}


void CMFCApplication18Dlg::OnBnClickedButtonRefresh()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CMysqlController conn;
	
	vector<CbookData*> books;
	
	if (conn.SelectQuery("select * from TB_Book", books) == true)
	{
		//AfxMessageBox(result);
	}

	m_list.DeleteAllItems();

	for(int i = 0; i < books.size(); i++){
		m_list.InsertItem(i, books.at(i)->Getid()); // ID
		m_list.SetItem(i, 1, LVIF_TEXT, books.at(i)->GetbookName(), NULL, NULL, NULL, NULL); // 책 이름
		m_list.SetItem(i, 2, LVIF_TEXT, books.at(i)->Getauthor(), NULL, NULL, NULL, NULL); // 저자
		m_list.SetItem(i, 3, LVIF_TEXT, books.at(i)->Getprice(), NULL, NULL, NULL, NULL); // 가격
		m_list.SetItem(i, 4, LVIF_TEXT, books.at(i)->Getother(), NULL, NULL, NULL, NULL); // 기타
	}
	
	for (int i = 0; i < books.size(); i++)
	{
		delete books[i];
	}
}


void CMFCApplication18Dlg::OnBnClickedDeleteButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(true);
	int clickindex = m_list.GetSelectionMark();

	CMysqlController conn;
	CString str;

	str = _T("delete from TB_Book where id=");
	CString idNumber = m_list.GetItemText(clickindex, 0);
	str += idNumber;

	if (conn.InsertQuery(LPSTR(LPCTSTR(str))) == true)
	{
		AfxMessageBox(_T("성공"));
		POSITION pos = m_list.GetFirstSelectedItemPosition(); // 선택된 첫 번째 위치를 얻어 와서,
		while (pos != NULL) { // 위치가 유효하다면,
			int nItem = m_list.GetNextSelectedItem(pos); // 그 위치에 해당하는 item의 index 를 얻고,
			m_list.DeleteItem(nItem); // 그 item 을 지운다.
			pos = m_list.GetFirstSelectedItemPosition(); // 선택된 첫번째 위치를 다시 얻어 온다.
		}
	}
	else
	{
		AfxMessageBox(_T(" 실패"));
	}

	UpdateData(false);
}
