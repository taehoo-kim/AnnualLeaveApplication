#pragma once
#include "afxdialogex.h"
#include <set>
#include <afxdtctl.h>

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
	CMonthCalCtrl m_calendar;      // 달력 컨트롤
	CListBox m_listBox;            // 선택 날짜 리스트박스
	std::set<COleDateTime> m_selectedDates; // 선택된 날짜 저장용 set

	CComboBox m_comboWorkType;      // 방학중 근무 여부 콤보박스
	CComboBox m_comboWorkplace;     // 근무지 콤보박스
	CDateTimeCtrl m_dateStartDate;  // 근무시작일 날짜 선택기

	CDateTimeCtrl m_dateSummerVacationStart; // 여름방학 시작일
	CDateTimeCtrl m_dateSummerVacationEnd;   // 여름방학 종료일
	CDateTimeCtrl m_dateWinterVacationStart; // 겨울방학 시작일
	CDateTimeCtrl m_dateWinterVacationEnd;   // 겨울방학 종료일

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
	afx_msg void OnMcnSelchangeMonthcalendar(NMHDR* pNMHDR, LRESULT* pResult);

	void UpdateSelectedDateList();
	void SetVacationDateControlsEnable(BOOL bEnable);

	afx_msg void OnDtnDatetimechangeDatetimepickerSummerVacationStart(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDtnDatetimechangeDatetimepickerSummerVacationEnd(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDtnDatetimechangeDatetimepickerWinterVacationStart(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDtnDatetimechangeDatetimepickerWinterVacationEnd(NMHDR* pNMHDR, LRESULT* pResult);
};
