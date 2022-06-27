
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "HM1_B711109.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
	m_ptlist.RemoveAll();
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
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
	CBrush br(RGB(255, 0, 0));
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_ptlist.GetSize() > 0)
	{
		POSITION pos = m_ptlist.GetHeadPosition();
		while (pos != NULL)
		{
			CPoint pt = m_ptlist.GetNext(pos);
			dc.SelectStockObject(LTGRAY_BRUSH);
			dc.Rectangle(pt.x - 50, pt.y - 50, pt.x + 50, pt.y + 50);

			dc.SelectObject(&br);
			CPoint* tri_pt = new CPoint[4];
			tri_pt[0].x = pt.x;
			tri_pt[0].y = pt.y - 50;
			tri_pt[1].x = pt.x - 50;
			tri_pt[1].y = pt.y + 50;
			tri_pt[2].x = pt.x + 50;
			tri_pt[2].y = pt.y + 50;
			tri_pt[3].x = pt.x;
			tri_pt[3].y = pt.y - 50;

			dc.Polygon(tri_pt, 4);
		}
	}
	
	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this);
	CPen pen(PS_SOLID, 2, RGB(255, 0, 255));
	dc.SelectObject(&pen);
	dc.Ellipse(point.x - 50, point.y - 50, point.x + 50, point.y + 50);
	
	CRect rect;
	CFont font;
	rect.SetRect(point.x - 25, point.y - 25, point.x + 25, point.y + 25);
/*	CPen rect_pen(PS_NULL, 0, RGB(0, 0, 0));
	CBrush rect_br(RGB(255, 255, 0));
	dc.SelectObject(&rect_pen);
	dc.SelectObject(&rect_br);
	dc.Rectangle(point.x - 25, point.y - 25, point.x + 25, point.y + 25);*/
	font.CreatePointFont(200, CString("Alias"));
	dc.SetTextColor(RGB(0, 0, 255));
	dc.SetBkColor(RGB(255, 255, 0));
	dc.SelectObject(&font);
	dc.DrawText(CString("HCI"), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	

	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_ptlist.AddTail(point);
	Invalidate(NULL);

	CWnd::OnRButtonDown(nFlags, point);
}
