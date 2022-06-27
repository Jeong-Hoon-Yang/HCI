
// HW3View.cpp: CHW3View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "HW3.h"
#endif

#include "HW3Doc.h"
#include "HW3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHW3View

IMPLEMENT_DYNCREATE(CHW3View, CView)

BEGIN_MESSAGE_MAP(CHW3View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
//	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// CHW3View 생성/소멸

CHW3View::CHW3View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_bDraw = false;

}

CHW3View::~CHW3View()
{
}

BOOL CHW3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CHW3View 그리기

void CHW3View::OnDraw(CDC* pDC)
{
	CHW3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	POSITION pos = pDoc->m_mylist.GetHeadPosition();
	while (pos != NULL) {
		m_mydraw = pDoc->m_mylist.GetNext(pos);
		CPen pen(PS_SOLID, 3, *m_mydraw.GetPenColor());
		pDC->SelectObject(pen);
		CBrush brush(*m_mydraw.GetBrushColor());
		pDC->SelectObject(brush);

		switch (*m_mydraw.GetType()) {
		case 1:	//rectangle
			pDC->Rectangle(m_mydraw.GetRect());
			break;
		case 2:	//ellipse
			pDC->Ellipse(m_mydraw.GetRect());
			break;
		case 3:	//line
			CPoint pt[2] = { *m_mydraw.GetStartPoint(), *m_mydraw.GetEndPoint() };
			//pDC->MoveTo(*m_mydraw.GetStartPoint());
			//pDC->LineTo(*m_mydraw.GetEndPoint());
			pDC->Polyline(pt, 2);
			break;
		
		}
	}
}


// CHW3View 인쇄

BOOL CHW3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CHW3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CHW3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CHW3View 진단

#ifdef _DEBUG
void CHW3View::AssertValid() const
{
	CView::AssertValid();
}

void CHW3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHW3Doc* CHW3View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHW3Doc)));
	return (CHW3Doc*)m_pDocument;
}
#endif //_DEBUG


// CHW3View 메시지 처리기


void CHW3View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_bDraw = true;
	SetCapture();
	m_start = m_end = point;

	CView::OnLButtonDown(nFlags, point);
}


void CHW3View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//저장하는 코드
	CClientDC dc(this);
	CHW3Doc* pDoc = GetDocument();
		m_bDraw = false;
		ReleaseCapture();
		m_end = point;
		CRect rect(m_start.x, m_start.y, m_end.x, m_end.y);
		rect.NormalizeRect();

		pDoc->m_curDraw.SetStartPoint(m_start);
		pDoc->m_curDraw.SetEndPoint(m_end);
		pDoc->m_curDraw.SetRect(rect);
		pDoc->m_mylist.AddTail(pDoc->m_curDraw);
		pDoc->SetModifiedFlag();

		Invalidate();

	CView::OnLButtonUp(nFlags, point);
}

void CHW3View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bDraw) {
		CClientDC dc(this);
		//기존 도형 지우기
		CHW3Doc* pDoc = GetDocument();
		//Doc 클래스에서 pencol, brushcol 가져와서 설정하고 그리는 코드 추가
		dc.SetROP2(R2_NOTXORPEN);
		CPen pen(PS_SOLID, 3, *pDoc->m_curDraw.GetPenColor());
		dc.SelectObject(pen);
		CBrush brush(*pDoc->m_curDraw.GetBrushColor());
		dc.SelectObject(brush);
		switch(*pDoc->m_curDraw.GetType()){
		case 1:	//rectangle
			dc.Rectangle(m_start.x, m_start.y, m_end.x, m_end.y);
			break;
		case 2:	//ellipse
			dc.Ellipse(m_start.x, m_start.y, m_end.x, m_end.y);
			break;
		case 3:	//line
			CPoint point[2] = { m_start, m_end };
			dc.Polyline(point, 2);
			break;
		}
		//새로운 도형 그리기
		m_end = point;
		switch(*pDoc->m_curDraw.GetType()){
		case 1:	//rectangle
			dc.Rectangle(m_start.x, m_start.y, m_end.x, m_end.y);
			break;
		case 2:	//ellipse
			dc.Ellipse(m_start.x, m_start.y, m_end.x, m_end.y);
			break;
		case 3:	//line
			CPoint point[2] = { m_start, m_end };
			dc.Polyline(point, 2);
			break;
		}
	}

	CView::OnMouseMove(nFlags, point);
}

