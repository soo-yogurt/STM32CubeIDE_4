#pragma once
#include <vector>
using namespace std;
// CNewDlg1 대화 상자


#include "MFCApplication10Dlg.h"
class CNewDlg1 : public CDialogEx
{
	DECLARE_DYNAMIC(CNewDlg1)

public:
	CNewDlg1(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CNewDlg1();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEWDLG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	void SetNewDlgList(CString msg);
	void SetNewDlgDatas(vector<CString> _data, int len);
	virtual BOOL OnInitDialog();
	CListCtrl m_newDlg1List;
	CString m_myMsg;
	vector<CString> mydata;
	vector<int> sum;
	CMFCApplication10Dlg* dlgPtr;
	void SetParentPtr(CMFCApplication10Dlg* dlg);


	afx_msg void OnDestroy();

};
