// CNewDlg1.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication10.h"
#include "CNewDlg1.h"
#include "afxdialogex.h"


// CNewDlg1 대화 상자

IMPLEMENT_DYNAMIC(CNewDlg1, CDialogEx)

CNewDlg1::CNewDlg1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NEWDLG1, pParent)
	, m_myMsg(_T(""))
{

}

CNewDlg1::~CNewDlg1()
{
}

void CNewDlg1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_newDlg1List);
	DDX_Text(pDX, IDC_EDIT1, m_myMsg);
}


BEGIN_MESSAGE_MAP(CNewDlg1, CDialogEx)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CNewDlg1 메시지 처리기


void CNewDlg1::SetNewDlgList(CString msg)
{
	// TODO: 여기에 구현 코드 추가.
	m_myMsg = msg;
}

void CNewDlg1::SetNewDlgDatas(vector<CString> _data, int len)
{
	for (int i = 0; i < len; i++) {
		mydata.push_back(_data.at(i));
	}
	for (int i = 0; i < 12; i++) {
		sum.push_back(0);
	}
}


BOOL CNewDlg1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	UpdateData(false);

	m_newDlg1List.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_newDlg1List.InsertColumn(0, _T("시도"), LVCFMT_CENTER, 50);
	m_newDlg1List.InsertColumn(1, _T("시군구"), LVCFMT_CENTER, 70);
	m_newDlg1List.InsertColumn(2, _T("터널안"), LVCFMT_CENTER, 70);
	m_newDlg1List.InsertColumn(3, _T("교량위"), LVCFMT_CENTER, 70);
	m_newDlg1List.InsertColumn(4, _T("고가도로위"), LVCFMT_CENTER, 100);
	m_newDlg1List.InsertColumn(5, _T("지하차도(도로)내"), LVCFMT_CENTER, 120);
	m_newDlg1List.InsertColumn(6, _T("기타단일로"), LVCFMT_CENTER, 100);
	m_newDlg1List.InsertColumn(7, _T("교차로내"), LVCFMT_CENTER, 80);
	m_newDlg1List.InsertColumn(8, _T("교차로횡단보도내"), LVCFMT_CENTER, 120);
	m_newDlg1List.InsertColumn(9, _T("교차로부근"), LVCFMT_CENTER, 100);
	m_newDlg1List.InsertColumn(10, _T("철긴건널목"), LVCFMT_CENTER, 100);
	m_newDlg1List.InsertColumn(11, _T("기타"), LVCFMT_CENTER, 50);
	m_newDlg1List.InsertColumn(12, _T("불명"), LVCFMT_CENTER, 50);

	int i = 0;
	for (int k = 0; k < mydata.size() / 13; k++) {
		m_newDlg1List.InsertItem(k, mydata.at(i));
		i++;
		m_newDlg1List.SetItem(k, 1, LVIF_TEXT, mydata.at(i), NULL, NULL, NULL, NULL);
		for (int j = 1; j < 12; j++) {
			i++;
			sum.at(j - 1) += _ttoi(mydata.at(i));
			m_newDlg1List.SetItem(k, 1 + j, LVIF_TEXT, mydata.at(i), NULL, NULL, NULL, NULL);
		}
		i++;
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}



void CNewDlg1::SetParentPtr(CMFCApplication10Dlg* dlg)
{
	// TODO: 여기에 구현 코드 추가.
	dlgPtr = dlg;
}


void CNewDlg1::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	dlgPtr->SetSumList(sum);
}

