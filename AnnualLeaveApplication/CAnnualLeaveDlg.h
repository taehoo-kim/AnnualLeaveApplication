#pragma once
#include "afxdialogex.h"
#include <vector>
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

	struct DayOffRecord
	{
		CString reason;       // 사유
		CTime   startDate;    // 시작일
		CTime   endDate;      // 종료일
		bool    countedAsAttendance; // 출근 간주 여부 (O = true, X = false)
	};

	std::vector<DayOffRecord> m_dayOffRecords;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

private:
	CFont m_fontHeaderBold;
	CMonthCalCtrl m_calendar;      // 달력 컨트롤
	CListCtrl m_listDayOffType;

	CComboBox m_comboWorkType;      // 방학중 근무 여부 콤보박스
	CComboBox m_comboWorkplace;     // 근무지 콤보박스
	CComboBox m_comboDayOffType;    // 미출근 유형 콤보박스
	CDateTimeCtrl m_dateStartDate;  // 근무시작일 날짜 선택기

	CDateTimeCtrl m_dateDayoffStart; // 미출근 시작일
	CDateTimeCtrl m_dateDayoffEnd;   // 미출근 종료일

	// 변수 또는 상태 저장용 (DoDataExchange 맵핑 가능)
	int m_nWorkTypeSel;
	int m_nWorkplaceSel;
	CTime m_ctStartDate;
public:
	afx_msg void OnCbnSelchangeComboVacationWork();
	afx_msg void OnCbnSelchangeComboWorkSite();
	afx_msg void OnDtnDatetimechangeDatetimepickerWorkStartDate(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonCalculate();

	int CountSaturdaysInYear(int year);
	int CountDaysExcludeSaturday(const CTime& startDate, const CTime& endDate);
	double CalculateAttendanceRate(int workType);
	int CalculateAnnualLeaveWithAttendance(
		const CTime& joinDate,
		const CTime& today,
		int workType           // 0=상시근무자, 1=비상시근무자
	);
	void UpdateDayOffTypeCombo(int workType);
	int CountWeekendsInPeriod(const CTime& startDate, const CTime& endDate);
	int CountDaysOff(const CTime& startDate, const CTime& endDate);
	int CalculateWorkDaysAuto(const CTime& periodStart, const CTime& periodEnd);
	afx_msg void OnBnClickedButtonAddDate();
	afx_msg void OnBnClickedButtonDelDate();
};
