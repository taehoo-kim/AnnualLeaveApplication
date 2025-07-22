#pragma once
#include "afxdialogex.h"


// CAnnualLeaveDlg 대화 상자

class CAnnualLeaveDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAnnualLeaveDlg)

public:
	CAnnualLeaveDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CAnnualLeaveDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

private:

	CComboBox m_comboWorkType;      // 방학중 근무 여부 콤보박스
	CComboBox m_comboWorkplace;     // 근무지 콤보박스
	CDateTimeCtrl m_dateStartDate;  // 근무시작일 날짜 선택기

	CStatic m_staticResult;          // 근속 결과 표시용 Static 텍스트

	// 변수 또는 상태 저장용 (DoDataExchange 맵핑 가능)
	int m_nWorkTypeSel;
	int m_nWorkplaceSel;
	CTime m_ctStartDate;
public:
	afx_msg void OnCbnSelchangeComboVacationWork();
	afx_msg void OnCbnSelchangeComboWorkSite();
	afx_msg void OnDtnDatetimechangeDatetimepickerWorkStartDate(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonCalculate();
};
