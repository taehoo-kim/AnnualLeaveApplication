// CAnnualLeaveDlg.cpp: 구현 파일
//

#include "pch.h"
#include "AnnualLeaveApplication.h"
#include "afxdialogex.h"
#include "CAnnualLeaveDlg.h"

#include <atlconv.h>

// CAnnualLeaveDlg 대화 상자

IMPLEMENT_DYNAMIC(CAnnualLeaveDlg, CDialogEx)

CAnnualLeaveDlg::CAnnualLeaveDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG, pParent)
{

}

CAnnualLeaveDlg::~CAnnualLeaveDlg()
{
}

void CAnnualLeaveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

    // 컨트롤 변수 연동
    DDX_Control(pDX, IDC_COMBO_VACATION_WORK, m_comboWorkType);
    DDX_Control(pDX, IDC_COMBO_WORK_SITE, m_comboWorkplace);
    DDX_Control(pDX, IDC_DATETIMEPICKER_WORK_START_DATE, m_dateStartDate);
    DDX_Control(pDX, IDC_DATETIMEPICKER_SUMMER_VACATION_START, m_dateSummerVacationStart);
    DDX_Control(pDX, IDC_DATETIMEPICKER_SUMMER_VACATION_END, m_dateSummerVacationEnd);
	DDX_Control(pDX, IDC_DATETIMEPICKER_WINTER_VACATION_START, m_dateWinterVacationStart);
	DDX_Control(pDX, IDC_DATETIMEPICKER_WINTER_VACATION_END, m_dateWinterVacationEnd);
    DDX_Control(pDX, IDC_STATIC_RESULT, m_staticResult);
    DDX_Control(pDX, IDC_MONTHCALENDAR1, m_calendar);
    DDX_Control(pDX, IDC_LIST_CUSTOMIZING_DAYS, m_listBox);

}


BEGIN_MESSAGE_MAP(CAnnualLeaveDlg, CDialogEx)
    ON_CBN_SELCHANGE(IDC_COMBO_VACATION_WORK, &CAnnualLeaveDlg::OnCbnSelchangeComboVacationWork)
    ON_CBN_SELCHANGE(IDC_COMBO_WORK_SITE, &CAnnualLeaveDlg::OnCbnSelchangeComboWorkSite)
    ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_WORK_START_DATE, &CAnnualLeaveDlg::OnDtnDatetimechangeDatetimepickerWorkStartDate)
    ON_BN_CLICKED(IDC_BUTTON_CALCULATE, &CAnnualLeaveDlg::OnBnClickedButtonCalculate)
    ON_NOTIFY(MCN_SELCHANGE, IDC_MONTHCALENDAR1, &CAnnualLeaveDlg::OnMcnSelchangeMonthcalendar)
    ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_SUMMER_VACATION_START, &CAnnualLeaveDlg::OnDtnDatetimechangeDatetimepickerSummerVacationStart)
    ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_SUMMER_VACATION_END, &CAnnualLeaveDlg::OnDtnDatetimechangeDatetimepickerSummerVacationEnd)
    ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_WINTER_VACATION_START, &CAnnualLeaveDlg::OnDtnDatetimechangeDatetimepickerWinterVacationStart)
    ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_WINTER_VACATION_END, &CAnnualLeaveDlg::OnDtnDatetimechangeDatetimepickerWinterVacationEnd)
END_MESSAGE_MAP()


// CAnnualLeaveDlg 메시지 처리기
BOOL CAnnualLeaveDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    m_nWorkTypeSel = 0;
    m_nWorkplaceSel = 0;
    // 콤보박스 초기화
    m_comboWorkType.AddString(_T("상시근무자"));
    m_comboWorkType.AddString(_T("비상시근무자"));
    m_comboWorkType.SetCurSel(0);

    m_comboWorkplace.AddString(_T("직속기관"));
    m_comboWorkplace.AddString(_T("학교"));
    m_comboWorkplace.SetCurSel(0);

    SetVacationDateControlsEnable(FALSE);

    // 날짜 선택기 초기값 현재 날짜로 설정
    CTime curTime = CTime::GetCurrentTime();
    SYSTEMTIME sysTime;
    curTime.GetAsSystemTime(sysTime);
    m_dateStartDate.SetTime(&sysTime);

    m_ctStartDate = curTime;

    // 초기 결과 텍스트 공백
    m_staticResult.SetWindowText(_T("근무지: \n근무형태: \n계산된 연차 일수: 일\n\n%s"));

    return TRUE;
}
void CAnnualLeaveDlg::OnCbnSelchangeComboVacationWork()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    m_nWorkTypeSel = m_comboWorkType.GetCurSel();

    // "비상시근무자"(1) 일 때만 방학 날짜 컨트롤 활성화
    if (m_nWorkTypeSel == 1)
    {
        SetVacationDateControlsEnable(TRUE);
    }
    else
    {
        SetVacationDateControlsEnable(FALSE);
    }
}

void CAnnualLeaveDlg::OnCbnSelchangeComboWorkSite()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    m_nWorkplaceSel = m_comboWorkplace.GetCurSel();
}

void CAnnualLeaveDlg::OnDtnDatetimechangeDatetimepickerWorkStartDate(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_dateStartDate.GetTime(m_ctStartDate);
    *pResult = 0;
}

// 연차 계산 함수
int CalculateAnnualLeave(const CTime& joinDate, const CTime& today)
{
    int years = today.GetYear() - joinDate.GetYear();
    int months = today.GetMonth() - joinDate.GetMonth();
    int days = today.GetDay() - joinDate.GetDay();

    if (days < 0) months--;
    if (months < 0)
    {
        years--;
        months += 12;
    }

    if (years < 1)
    {
        int totalMonths = months + (days >= 0 ? 1 : 0); // 일수가 0 이상이면 한 달 추가
        if (totalMonths > 11) totalMonths = 11;
        return totalMonths;  // 1개월당 1일 계산, 최대 11일
    }
    else
    {
        int leave = 15 + ((years - 1) / 2); // 1년 이상은 15일 + 2년마다 1일씩 가산
        if (leave > 25) leave = 25;         // 최대 25일까지
        return leave;
    }
}

void CAnnualLeaveDlg::OnBnClickedButtonCalculate()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    CTime today = CTime::GetCurrentTime();

    // 기본 공무원 연차 계산 함수 호출
    int annualLeaveDays = CalculateAnnualLeave(m_ctStartDate, today);

    // 근무지 텍스트
    CString strStandardDate = (m_nWorkplaceSel == 0)
        ? _T("직속기관: 1월 1일 기준")
        : _T("학교: 3월 1일 기준");

    // 방학중 근무 여부 텍스트
    CString strWorkType;
    m_comboWorkType.GetLBText(m_nWorkTypeSel, strWorkType);

    // 결과 문자열에 연차 일수 포함 출력
    CString strResult;
    strResult.Format(_T("근무지: %s\n근무형태: %s\n계산된 연차 일수: %d일\n\n%s"),
        (m_nWorkplaceSel == 0) ? _T("직속기관") : _T("학교"),
        strWorkType,
        annualLeaveDays,
        strStandardDate);

    m_staticResult.SetWindowText(strResult);
}

void CAnnualLeaveDlg::OnMcnSelchangeMonthcalendar(NMHDR* pNMHDR, LRESULT* pResult)
{
    SYSTEMTIME st;
    if (m_calendar.GetCurSel(&st)) // 현재 선택된 날짜 얻기
    {
        COleDateTime clickedDate(st);

        // 이미 선택한 날짜인지 확인
        auto it = m_selectedDates.find(clickedDate);
        if (it != m_selectedDates.end()) {
            // 이미 있으면 해제(삭제)
            m_selectedDates.erase(it);
        }
        else {
            // 없으면 추가
            m_selectedDates.insert(clickedDate);
        }

        UpdateSelectedDateList();
    }

    *pResult = 0;
}

void CAnnualLeaveDlg::UpdateSelectedDateList()
{
    m_listBox.ResetContent();

    for (const auto& dt : m_selectedDates)
    {
        CString strDate = dt.Format(_T("%Y-%m-%d"));
        m_listBox.AddString(strDate);
    }
}

void CAnnualLeaveDlg::OnDtnDatetimechangeDatetimepickerSummerVacationStart(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    *pResult = 0;
}

void CAnnualLeaveDlg::OnDtnDatetimechangeDatetimepickerSummerVacationEnd(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    *pResult = 0;
}

void CAnnualLeaveDlg::OnDtnDatetimechangeDatetimepickerWinterVacationStart(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    *pResult = 0;
}

void CAnnualLeaveDlg::OnDtnDatetimechangeDatetimepickerWinterVacationEnd(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    *pResult = 0;
}

// 방학 날짜 컨트롤 활성/비활성 토글 함수
void CAnnualLeaveDlg::SetVacationDateControlsEnable(BOOL bEnable)
{
    m_dateSummerVacationStart.EnableWindow(bEnable);
    m_dateSummerVacationEnd.EnableWindow(bEnable);
    m_dateWinterVacationStart.EnableWindow(bEnable);
    m_dateWinterVacationEnd.EnableWindow(bEnable);

    // 선택 해제 및 초기화 추가 (필요하면)
    if (!bEnable)
    {
        // 초기값 현재 날짜 또는 빈값 넣기 (원하는 초기화 로직으로 수정 가능)
        CTime curTime = CTime::GetCurrentTime();
        SYSTEMTIME sysTime;
        curTime.GetAsSystemTime(sysTime);

        m_dateSummerVacationStart.SetTime(&sysTime);
        m_dateSummerVacationEnd.SetTime(&sysTime);
        m_dateWinterVacationStart.SetTime(&sysTime);
        m_dateWinterVacationEnd.SetTime(&sysTime);
    }
}