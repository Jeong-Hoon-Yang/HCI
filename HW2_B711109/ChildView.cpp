// B711109 양정훈
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "Homework2.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildView

CChildView::CChildView()
{
	m_bDrawMode = false;
	m_found = false;
	m_foundpos = NULL;
}

CChildView::~CChildView()
{
	m_mylist.RemoveAll();
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_WM_RBUTTONDBLCLK()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_mylist.GetSize() > 0) {
		dc.SelectStockObject(NULL_BRUSH);
		POSITION pos = m_mylist.GetHeadPosition();
		POSITION fpos = m_fontcol.GetHeadPosition();
		COLORREF m_curfont;
		while (pos != NULL) {
			m_curfont = m_fontcol.GetNext(fpos);
			m_curData = m_mylist.GetNext(pos);
			m_start = *m_curData.GetStartPoint();
			m_end = *m_curData.GetEndPoint();
			CRect rect(m_start.x, m_start.y, m_end.x, m_end.y);
			CPen pen(PS_SOLID, 1, *m_curData.GetPenColor());
			dc.SelectObject(pen);
			dc.Rectangle(rect);
			CString str = *m_curData.GetString();
			CFont font;
			font.CreatePointFont(150, CString("Times"));
			dc.SelectObject(&font);
			dc.SetTextColor(m_curfont);
			dc.DrawText(str, str.GetLength(), &rect, DT_CENTER);
		}
	}
	
	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	SetCapture();
	m_bDrawMode = TRUE;
	m_start = m_end = point;

	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bDrawMode) {
		CClientDC dc(this);
		dc.SelectStockObject(NULL_BRUSH);
		dc.SetROP2(R2_NOT);
		dc.Rectangle(m_start.x, m_start.y, m_end.x, m_end.y);

		dc.SetROP2(R2_NOT);
		m_end = point;
		dc.Rectangle(m_start.x, m_start.y, m_end.x, m_end.y);
	}

	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_bDrawMode = false;
	ReleaseCapture();
	m_end = point;
	//CMyData에 넣어서 CList 저장
	CRect rect(m_start.x, m_start.y, m_end.x, m_end.y);
	rect.NormalizeRect();	//필수!	minpoint < maxpoint
	m_start.x = rect.left;
	m_start.y = rect.top;
	m_end.x = rect.right;
	m_end.y = rect.bottom;

	m_curData.SetStartPoint(m_start);
	m_curData.SetEndPoint(m_end);
	m_curData.SetMyString(CString(""));

	m_mylist.AddTail(m_curData);

	srand((unsigned int)time(NULL));
	COLORREF strcolor = RGB(rand() % 255, rand() % 255, rand() % 255);
	m_fontcol.AddTail(strcolor);

	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_found = false;
	POSITION pos = m_mylist.GetHeadPosition();
	
	while (pos != NULL) {
		m_mylist.GetNext(pos).SetPenColor(RGB(0, 0, 0));
	}

	if (m_mylist.GetSize() > 0) {
		POSITION pos = m_mylist.GetHeadPosition();
		while (pos != NULL) {
			m_foundpos = pos;
			m_curData = m_mylist.GetNext(pos);
			m_start = *m_curData.GetStartPoint();
			m_end = *m_curData.GetEndPoint();
			CRect rect(m_start.x, m_start.y, m_end.x, m_end.y);
			if (rect.PtInRect(point)) {
				m_mylist.GetAt(m_foundpos).SetPenColor(RGB(255, 0, 0));
				m_str = *m_mylist.GetAt(m_foundpos).GetString();
				break;
			}
			m_foundpos = NULL;
		}
	}

	Invalidate();

	CWnd::OnRButtonDown(nFlags, point);
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_foundpos != NULL) {
		m_curData = m_mylist.GetAt(m_foundpos);
		m_start = *m_curData.GetStartPoint();
		m_end = *m_curData.GetEndPoint();
		switch (nChar) {
		case VK_LEFT:
			m_start.x -= 20;
			m_end.x -= 20;
			break;
		case VK_RIGHT:
			m_start.x += 20;
			m_end.x += 20;
			break;
		case VK_UP:
			m_start.y -= 20;
			m_end.y -= 20;
			break;
		case VK_DOWN:
			m_start.y += 20;
			m_end.y += 20;
			break;
		}

		m_mylist.GetAt(m_foundpos).SetStartPoint(m_start);
		m_mylist.GetAt(m_foundpos).SetEndPoint(m_end);

		Invalidate();
	}

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CChildView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_foundpos != NULL) {
		if (nChar == _T('\b')) {
			if (m_str.GetLength() > 0)
				m_str.Delete(m_str.GetLength() - 1, 1);
		}
		else {
			m_str.AppendChar(nChar);
		}
		m_mylist.GetAt(m_foundpos).SetMyString(m_str);

		// 화면을 갱신한다.
		Invalidate();
	}
}


void CChildView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_foundpos != NULL)
	{
		m_mylist.GetAt(m_foundpos).SetPenColor(RGB(0, 0, 0));
		COLORREF pcol = *m_mylist.GetAt(m_foundpos).GetPenColor();
	}
	m_foundpos = NULL;
	Invalidate();

	CWnd::OnRButtonDblClk(nFlags, point);
}
