// CResultDlg.cpp: 구현 파일
//

#include "pch.h"
#include "AnnualLeaveApplication.h"
#include "afxdialogex.h"
#include "CResultDlg.h"


// CResultDlg 대화 상자

IMPLEMENT_DYNAMIC(CResultDlg, CDialogEx)

CResultDlg::CResultDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_RESULT, pParent)
{

}

CResultDlg::~CResultDlg()
{
}

void CResultDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_RESULT, m_staticResult);
}


BEGIN_MESSAGE_MAP(CResultDlg, CDialogEx)
END_MESSAGE_MAP()

BOOL CResultDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_staticResult.SetWindowText(m_strResult);

    LOGFONT lf = { 0 };
    CFont* pOldFont = m_staticResult.GetFont();
    if (pOldFont)
        pOldFont->GetLogFont(&lf);
    else
    {
        lf.lfHeight = 20;
        _tcscpy_s(lf.lfFaceName, _T("맑은 고딕"));
    }

    lf.lfHeight = 20;
    lf.lfWeight = FW_BOLD;

    m_fontLarge.CreateFontIndirect(&lf);

    m_staticResult.SetFont(&m_fontLarge);

	return TRUE;
}

// CResultDlg 메시지 처리기
void CResultDlg::SetResultString(const CString& strResult)
{
	m_strResult = strResult;
}