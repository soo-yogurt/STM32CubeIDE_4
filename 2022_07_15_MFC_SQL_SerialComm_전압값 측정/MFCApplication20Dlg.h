
// MFCApplication20Dlg.h: 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "SerialCom.h"

// CMFCApplication20Dlg 대화 상자
class CMFCApplication20Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCApplication20Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	CSerialComm* m_comm;
	LRESULT		OnThreadClosed(WPARAM length, LPARAM lpara);
	LRESULT		OnReceive(WPARAM length, LPARAM lpara);
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION20_DIALOG };
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
	BOOL comport_state;

	CComboBox m_combo_comport_list;
	CComboBox m_combo_baudrate_list;
	CString m_str_comport;
	CString m_combo_baudrate;
	CEdit m_receive_value_now_data;
	CListCtrl m_value_1_data_list;
	CListCtrl m_value_2_data_list;
	afx_msg void OnBnClickedBtConnect();
	afx_msg void OnBnClickedButtonReadAdc();
	afx_msg void OnBnClickedButton1Reset();
	afx_msg void OnBnClickedButton2Reset();
	afx_msg void OnCbnSelchangeComboComport();
	afx_msg void OnCbnSelchangeComboBaudrate();
	CDateTimeCtrl m_datatime_picker;
	CDateTimeCtrl m_time_picker;

	CSliderCtrl m_slider;
	CEdit m_slider_value;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeSliderValue();


	CTime sel_date;
	CString user_set_time;


	afx_msg void OnBnClickedRadioSelect();

};
