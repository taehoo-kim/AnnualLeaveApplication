
// AnnualLeaveApplication.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "AnnualLeaveApplication.h"
#include "MainFrm.h"
#include "CAnnualLeaveDlg.h"

#include "AnnualLeaveApplicationDoc.h"
#include "AnnualLeaveApplicationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAnnualLeaveApplicationApp

BEGIN_MESSAGE_MAP(CAnnualLeaveApplicationApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CAnnualLeaveApplicationApp::OnAppAbout)
	// 표준 파일을 기초로 하는 문서 명령입니다.
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// 표준 인쇄 설정 명령입니다.
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// CAnnualLeaveApplicationApp 생성

CAnnualLeaveApplicationApp::CAnnualLeaveApplicationApp() noexcept
{

	// 다시 시작 관리자 지원
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 애플리케이션을 공용 언어 런타임 지원을 사용하여 빌드한 경우(/clr):
	//     1) 이 추가 설정은 다시 시작 관리자 지원이 제대로 작동하는 데 필요합니다.
	//     2) 프로젝트에서 빌드하려면 System.Windows.Forms에 대한 참조를 추가해야 합니다.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 아래 애플리케이션 ID 문자열을 고유 ID 문자열로 바꾸십시오(권장).
	// 문자열에 대한 서식: CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("AnnualLeaveApplication.AppID.NoVersion"));

	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}

// 유일한 CAnnualLeaveApplicationApp 개체입니다.

CAnnualLeaveApplicationApp theApp;


// CAnnualLeaveApplicationApp 초기화

BOOL CAnnualLeaveApplicationApp::InitInstance()
{
	// 공용 컨트롤 초기화 (필요 시)
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// OLE 초기화
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();
	EnableTaskbarInteraction(FALSE);

	// 필요시 RichEdit, 레지스트리 설정 등 유지

	SetRegistryKey(_T("로컬 애플리케이션 마법사에서 생성된 애플리케이션"));
	LoadStdProfileSettings(4);

	// 다이얼로그 실행
	CAnnualLeaveDlg dlg;              // 본인의 다이얼로그 클래스명 사용
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

	// 다이얼로그 종료 후 앱 종료
	return FALSE;
}

int CAnnualLeaveApplicationApp::ExitInstance()
{
	//TODO: 추가한 추가 리소스를 처리합니다.
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// CAnnualLeaveApplicationApp 메시지 처리기


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// 대화 상자를 실행하기 위한 응용 프로그램 명령입니다.
void CAnnualLeaveApplicationApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CAnnualLeaveApplicationApp 메시지 처리기



