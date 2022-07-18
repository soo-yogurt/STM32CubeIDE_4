
// MFCApplication8Dlg.h: 헤더 파일
//

#pragma once
#include "CVendingMachine.h"

// CMFCApplication8Dlg 대화 상자
class CMFCApplication8Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCApplication8Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION8_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// my_money
	int m_myMoney = 0;
	// 내용
	CString m_content =(CString)" ";
	CVendingMachine newVendingMachine;

	afx_msg void OnBnClickedAdd500won();
	afx_msg void OnBnClickedAdd1000won();
	afx_msg void OnBnClickedReturnmoney();
	afx_msg void OnBnClickedMenu1();
	afx_msg void OnBnClickedMenu2();
	afx_msg void OnBnClickedMenu3();
	afx_msg void OnBnClickedMenu4();
};
