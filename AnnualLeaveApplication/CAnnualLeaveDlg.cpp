// CAnnualLeaveDlg.cpp: 구현 파일
//

#include "pch.h"
#include "AnnualLeaveApplication.h"
#include "afxdialogex.h"
#include "CAnnualLeaveDlg.h"
#include "CResultDlg.h"

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
    DDX_Control(pDX, IDC_DATETIMEPICKER_DAY_START, m_dateDayoffStart);
    DDX_Control(pDX, IDC_DATETIMEPICKER_DAY_END, m_dateDayoffEnd);
	DDX_Control(pDX, IDC_COMBO_DAYOFF_REASON, m_comboDayOffType);
    DDX_Control(pDX, IDC_LIST_DAYOFF_TYPE, m_listDayOffType);
}


BEGIN_MESSAGE_MAP(CAnnualLeaveDlg, CDialogEx)
    ON_CBN_SELCHANGE(IDC_COMBO_VACATION_WORK, &CAnnualLeaveDlg::OnCbnSelchangeComboVacationWork)
    ON_CBN_SELCHANGE(IDC_COMBO_WORK_SITE, &CAnnualLeaveDlg::OnCbnSelchangeComboWorkSite)
    ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_WORK_START_DATE, &CAnnualLeaveDlg::OnDtnDatetimechangeDatetimepickerWorkStartDate)
    ON_BN_CLICKED(IDC_BUTTON_CALCULATE, &CAnnualLeaveDlg::OnBnClickedButtonCalculate)
    ON_BN_CLICKED(IDC_BUTTON_ADD_DATE, &CAnnualLeaveDlg::OnBnClickedButtonAddDate)
    ON_BN_CLICKED(IDC_BUTTON_DEL_DATE, &CAnnualLeaveDlg::OnBnClickedButtonDelDate)
END_MESSAGE_MAP()


// CAnnualLeaveDlg 메시지 처리기
BOOL CAnnualLeaveDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    
    m_listDayOffType.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

    m_listDayOffType.InsertColumn(0, _T("사유"), LVCFMT_LEFT, 80);
    m_listDayOffType.InsertColumn(1, _T("기간"), LVCFMT_LEFT, 180);
    m_listDayOffType.InsertColumn(2, _T("출근 간주"), LVCFMT_LEFT, 80);

   
    CHeaderCtrl* pHeader = m_listDayOffType.GetHeaderCtrl();
    if (pHeader && m_fontHeaderBold.m_hObject == NULL) {
        LOGFONT lf = { 0 };
        CFont* pOldFont = pHeader->GetFont();
        if (pOldFont) {
            pOldFont->GetLogFont(&lf);
        }
        lf.lfWeight = FW_BOLD;   // Bold
        m_fontHeaderBold.CreateFontIndirect(&lf);
        pHeader->SetFont(&m_fontHeaderBold);
    }

    m_nWorkTypeSel = 0;
    m_nWorkplaceSel = 0;


    // 콤보박스 초기화
    m_comboWorkType.AddString(_T("상시근무자"));
    m_comboWorkType.AddString(_T("비상시근무자"));
    m_comboWorkType.SetCurSel(0);

    m_comboWorkplace.AddString(_T("직속기관"));
    m_comboWorkplace.AddString(_T("학교"));
    m_comboWorkplace.SetCurSel(0);

    m_comboDayOffType.AddString(_T("여름방학"));
	m_comboDayOffType.AddString(_T("겨울방학"));
	m_comboDayOffType.AddString(_T("출산전후휴가"));
	m_comboDayOffType.AddString(_T("연차유급휴가"));
	m_comboDayOffType.AddString(_T("예비군"));
	m_comboDayOffType.AddString(_T("공가"));
    m_comboDayOffType.AddString(_T("유급주휴일"));
    m_comboDayOffType.AddString(_T("대체공휴일"));
    m_comboDayOffType.AddString(_T("질병휴직"));
    m_comboDayOffType.AddString(_T("노조전임휴직"));
    m_comboDayOffType.AddString(_T("행방불명휴직"));
    m_comboDayOffType.AddString(_T("공직선출휴직"));
    m_comboDayOffType.AddString(_T("유학휴직"));
    // 5월 1일 근로자의 날은 자동으로 추가되므로 별도로 추가하지 않음
    m_comboDayOffType.SetCurSel(0);

    UpdateDayOffTypeCombo(m_nWorkTypeSel);

    // 날짜 선택기 초기값 현재 날짜로 설정
    CTime curTime = CTime::GetCurrentTime();
    SYSTEMTIME sysTime;
    curTime.GetAsSystemTime(sysTime);
    m_dateStartDate.SetTime(&sysTime);

    m_ctStartDate = curTime;

    return TRUE;
}
void CAnnualLeaveDlg::OnCbnSelchangeComboVacationWork()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    m_nWorkTypeSel = m_comboWorkType.GetCurSel();

    // 비상시근무자일 때는 사유 콤보박스 항목 제한
    UpdateDayOffTypeCombo(m_nWorkTypeSel);
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
int CAnnualLeaveDlg::CalculateAnnualLeaveWithAttendance(
    const CTime& joinDate,
    const CTime& today,
    int workType           // 0=상시근무자, 1=비상시근무자
)
{
    // 1. 기준일 설정: 직속기관(0)은 1/1, 학교(1)은 3/1 기준 (예전 내용 없으면 기본 joinDate 기준)
    // (여기서는 joinDate 기준으로 간단 처리, 필요시 인자로 추가 가능)

    int years = today.GetYear() - joinDate.GetYear();
    int months = today.GetMonth() - joinDate.GetMonth();
    int days = today.GetDay() - joinDate.GetDay();

    if (days < 0) months--;
    if (months < 0)
    {
        years--;
        months += 12;
    }

    if (years < 0) years = 0;

    // 2. 기본 연차 계산
    int baseLeave = (workType == 0) ? 15 : 12;  // 상시 15일, 비상시 12일
    int leave = 0;

    if (years < 1)
    {
        // 1개월당 1일 (최대 11일)
        int totalMonths = months + (days >= 0 ? 1 : 0);
        if (totalMonths > 11) totalMonths = 11;
        leave = totalMonths;
    }
    else
    {
        leave = baseLeave + ((years - 1) / 2);
        if (leave > 25) leave = 25;
    }

    // 3. 출근율 계산 (직접 함수 호출 또는 별도 계산)
    double attendanceRate = CalculateAttendanceRate(workType);

    // 4. 출근율 80% 이상이면 3일 추가
    if (attendanceRate >= 80.0)
    {
        leave += 3;
    }

    // 최대 25일 제한
    if (leave > 25) leave = 25;

    return leave;
}

void CAnnualLeaveDlg::OnBnClickedButtonCalculate()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    CTime today = CTime::GetCurrentTime();

    // 기본 공무원 연차 계산 함수 호출
    int annualLeaveDays = CalculateAnnualLeaveWithAttendance(m_ctStartDate, today, m_nWorkTypeSel);

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

    CResultDlg dlgResult;
    dlgResult.SetResultString(strResult);
    dlgResult.DoModal(); // 모달로 결과 창 띄우기
}

void CAnnualLeaveDlg::UpdateDayOffTypeCombo(int workType)
{
    m_comboDayOffType.ResetContent();

    if (workType == 1) // 비상시근무자
    {
        // 방학 사유 미포함
        m_comboDayOffType.AddString(_T("출산전후휴가"));
        m_comboDayOffType.AddString(_T("연차유급휴가"));
        m_comboDayOffType.AddString(_T("예비군"));
        m_comboDayOffType.AddString(_T("공가"));
        m_comboDayOffType.AddString(_T("유급주휴일"));
        m_comboDayOffType.AddString(_T("대체공휴일"));
        m_comboDayOffType.AddString(_T("질병휴직"));
        m_comboDayOffType.AddString(_T("노조전임휴직"));
        m_comboDayOffType.AddString(_T("행방불명휴직"));
        m_comboDayOffType.AddString(_T("공직선출휴직"));
        m_comboDayOffType.AddString(_T("유학휴직"));
    }
    else // 상시근무자
    {
        m_comboDayOffType.AddString(_T("여름방학"));
        m_comboDayOffType.AddString(_T("겨울방학"));
        m_comboDayOffType.AddString(_T("출산전후휴가"));
        m_comboDayOffType.AddString(_T("연차유급휴가"));
        m_comboDayOffType.AddString(_T("예비군"));
        m_comboDayOffType.AddString(_T("공가"));
        m_comboDayOffType.AddString(_T("유급주휴일"));
        m_comboDayOffType.AddString(_T("대체공휴일"));
        m_comboDayOffType.AddString(_T("질병휴직"));
        m_comboDayOffType.AddString(_T("노조전임휴직"));
        m_comboDayOffType.AddString(_T("행방불명휴직"));
        m_comboDayOffType.AddString(_T("공직선출휴직"));
        m_comboDayOffType.AddString(_T("유학휴직"));
    }

    m_comboDayOffType.SetCurSel(0);
}

void CAnnualLeaveDlg::OnBnClickedButtonAddDate()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    // 1. 사유 콤보박스 선택값 얻기
    CString reason;
    int reasonSel = m_comboDayOffType.GetCurSel();
    if (reasonSel != CB_ERR)
        m_comboDayOffType.GetLBText(reasonSel, reason);
    else
        reason = _T("사유없음");

    // 2. 날짜 가져오기
    CTime startDate, endDate;
    m_dateDayoffStart.GetTime(startDate);
    m_dateDayoffEnd.GetTime(endDate);

    // 3. 유효성 검사 - 종료일이 시작일보다 빠른지
    if (endDate < startDate) {
        AfxMessageBox(_T("종료일이 시작일보다 빠릅니다. 날짜를 확인해 주세요."));
        return;
    }

    // 4. 기간 문자열 생성
    CString periodStr = startDate.Format(_T("%Y-%m-%d")) + _T(" ~ ") + endDate.Format(_T("%Y-%m-%d"));

    // --- 출근 간주 여부 판단 ---

    // 출근 간주 가능한 사유 배열
    static const CString attendanceReasons[] = {
        _T("여름방학"), _T("겨울방학"), _T("출산전후휴가"), _T("연차유급휴가"),
        _T("예비군"), _T("공가"), _T("유급주휴일"), _T("대체공휴일")
    };

    CString attendanceStr = _T("X"); // 기본은 출근 간주 NO

    // 리스트 내 사유와 비교
    for (const auto& attReason : attendanceReasons)
    {
        if (reason == attReason)
        {
            attendanceStr = _T("O");
            break;
        }
    }

    DayOffRecord record;
    record.reason = reason;
    record.startDate = startDate;
    record.endDate = endDate;
    record.countedAsAttendance = (attendanceStr == _T("O"));

    m_dayOffRecords.push_back(record);

    int nItem = m_listDayOffType.GetItemCount();
    m_listDayOffType.InsertItem(nItem, reason);           // 사유
    m_listDayOffType.SetItemText(nItem, 1, periodStr);    // 기간
    m_listDayOffType.SetItemText(nItem, 2, attendanceStr);// 출근 간주
}

void CAnnualLeaveDlg::OnBnClickedButtonDelDate()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    int nSel = m_listDayOffType.GetNextItem(-1, LVNI_SELECTED);
    if (nSel == -1)
    {
        AfxMessageBox(_T("삭제할 항목을 선택해주세요."));
        return;
    }

    // 선택된 모든 항목 삭제 (역순으로 처리하면 인덱스 문제 없음)
    while (nSel != -1)
    {
        m_listDayOffType.DeleteItem(nSel);
        nSel = m_listDayOffType.GetNextItem(-1, LVNI_SELECTED);
    }

    // 벡터에서도 삭제
    if (nSel >= 0 && nSel < (int)m_dayOffRecords.size())
    {
        m_dayOffRecords.erase(m_dayOffRecords.begin() + nSel);
    }
}

int CAnnualLeaveDlg::CountSaturdaysInYear(int year)
{
    int saturdayCount = 0;
    CTime date(year, 1, 1, 0, 0, 0);
    CTime endDate(year, 12, 31, 0, 0, 0);

    while (date <= endDate)
    {
        if (date.GetDayOfWeek() == 7) // 7 == 토요일
            saturdayCount++;

        date += 24 * 60 * 60; // 하루 증가
    }

    return saturdayCount;
}

int CAnnualLeaveDlg::CountDaysExcludeSaturday(const CTime& startDate, const CTime& endDate)
{
    int count = 0;
    CTime date = startDate;
    while (date <= endDate)
    {
        if (date.GetDayOfWeek() != 7) // 토요일 제외
            count++;
        date += 24 * 60 * 60; // 1일 증가
    }
    return count;
}

double CAnnualLeaveDlg::CalculateAttendanceRate(int workType)
{
    CTime now = CTime::GetCurrentTime();
    int lastYear = now.GetYear() - 1;

    int saturdays = CountSaturdaysInYear(lastYear);

    int totalDaysInYear = (lastYear % 400 == 0 || (lastYear % 4 == 0 && lastYear % 100 != 0)) ? 366 : 365;
    int totalDaysNoSaturday = totalDaysInYear - saturdays;

    CTime periodStart(lastYear, 1, 1, 0, 0, 0);
    CTime periodEnd(lastYear, 12, 31, 23, 59, 59);

    int workDays = CalculateWorkDaysAuto(periodStart, periodEnd);

    if (totalDaysNoSaturday <= 0) totalDaysNoSaturday = 1;  // 안전장치

    // 출근 간주 휴가 기간 토요일 제외한 일수 합산 (예: m_dayOffRecords 기준)
    int attendanceCountedDays = 0;
    int vacationCountedDays = 0;

    for (const auto& record : m_dayOffRecords)
    {
        if (!record.countedAsAttendance)
            continue;

        attendanceCountedDays += CountDaysExcludeSaturday(record.startDate, record.endDate);

        if (workType == 1 && (record.reason == _T("여름방학") || record.reason == _T("겨울방학")))
        {
            vacationCountedDays += CountDaysExcludeSaturday(record.startDate, record.endDate);
        }
    }

    double numerator = workDays + attendanceCountedDays + (workType == 1 ? vacationCountedDays : 0);
    double attendanceRate = (numerator / totalDaysNoSaturday) * 100.0;

    if (attendanceRate > 100.0) attendanceRate = 100.0;
    else if (attendanceRate < 0.0) attendanceRate = 0.0;

    return attendanceRate;
}

// 주말(토,일) 개수 계산 함수
int CAnnualLeaveDlg::CountWeekendsInPeriod(const CTime& startDate, const CTime& endDate)
{
    int count = 0;
    CTime date = startDate;
    while (date <= endDate)
    {
        int dayOfWeek = date.GetDayOfWeek();
        if (dayOfWeek == 1 || dayOfWeek == 7)  // 일요일=1, 토요일=7
            count++;
        date += 24 * 60 * 60; // 하루 증가
    }
    return count;
}

// 휴가 기간 내 날짜 수 계산 (토요일/일요일 포함)
// 근무일수 계산 시 제외할 총 휴가 일수
int CAnnualLeaveDlg::CountDaysOff(const CTime& startDate, const CTime& endDate)
{
    int daysOff = 0;
    for (const auto& record : m_dayOffRecords)
    {
        // 기간 겹치는 휴가 범위 계산: 시작일과 종료일이 겹치는 부분 계산
        CTime s = (record.startDate < startDate) ? startDate : record.startDate;
        CTime e = (record.endDate > endDate) ? endDate : record.endDate;

        if (s <= e) {
            CTimeSpan diff = e - s;
            daysOff = (int)diff.GetDays() + 1;
        }
    }
    return daysOff;
}

// 자동 근무일수 계산
int CAnnualLeaveDlg::CalculateWorkDaysAuto(const CTime& periodStart, const CTime& periodEnd)
{
    CTimeSpan diff = periodEnd - periodStart;
    int totalDays = (int)diff.GetDays() + 1;
    int weekends = CountWeekendsInPeriod(periodStart, periodEnd);
    int daysOff = CountDaysOff(periodStart, periodEnd);

    int workDays = totalDays - weekends - daysOff;

    if (workDays < 0) workDays = 0;

    return workDays;
}