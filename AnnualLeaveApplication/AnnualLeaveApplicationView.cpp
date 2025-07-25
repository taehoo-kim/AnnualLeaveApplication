﻿
// AnnualLeaveApplicationView.cpp: CAnnualLeaveApplicationView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "AnnualLeaveApplication.h"
#endif

#include "AnnualLeaveApplicationDoc.h"
#include "AnnualLeaveApplicationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAnnualLeaveApplicationView

IMPLEMENT_DYNCREATE(CAnnualLeaveApplicationView, CView)

BEGIN_MESSAGE_MAP(CAnnualLeaveApplicationView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CAnnualLeaveApplicationView 생성/소멸

CAnnualLeaveApplicationView::CAnnualLeaveApplicationView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CAnnualLeaveApplicationView::~CAnnualLeaveApplicationView()
{
}

BOOL CAnnualLeaveApplicationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CAnnualLeaveApplicationView 그리기

void CAnnualLeaveApplicationView::OnDraw(CDC* /*pDC*/)
{
	CAnnualLeaveApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CAnnualLeaveApplicationView 인쇄

BOOL CAnnualLeaveApplicationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CAnnualLeaveApplicationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CAnnualLeaveApplicationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CAnnualLeaveApplicationView 진단

#ifdef _DEBUG
void CAnnualLeaveApplicationView::AssertValid() const
{
	CView::AssertValid();
}

void CAnnualLeaveApplicationView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAnnualLeaveApplicationDoc* CAnnualLeaveApplicationView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAnnualLeaveApplicationDoc)));
	return (CAnnualLeaveApplicationDoc*)m_pDocument;
}
#endif //_DEBUG


// CAnnualLeaveApplicationView 메시지 처리기
