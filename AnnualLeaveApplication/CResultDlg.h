#pragma once
#include "afxdialogex.h"


// CResultDlg 대화 상자

class CResultDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CResultDlg)

public:
	CResultDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CResultDlg();
	void SetResultString(const CString& strResult);

	CStatic m_staticResult;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RESULT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

private:
	CString m_strResult;
	CFont m_fontLarge;
};
