#include "pch.h"
#include "CMyDraw.h"

IMPLEMENT_SERIAL(CMyDraw, CObject, 1)

CMyDraw::CMyDraw() {
	m_type = 1;
	CRect rect(0, 0, 0, 0);
	m_rect = rect;
	m_pencol = RGB(0, 0, 0);
	m_brushcol = RGB(255, 255, 255);
	m_spoint = (0, 0);
	m_epoint = (0, 0);
}

CMyDraw::CMyDraw(const CMyDraw& t) {
	m_rect = t.m_rect;
	m_type = t.m_type;
	m_pencol = t.m_pencol;
	m_brushcol = t.m_brushcol;
	m_spoint = t.m_spoint;
	m_epoint = t.m_epoint;
}

CMyDraw::~CMyDraw() {
}

CMyDraw& CMyDraw::operator=(const CMyDraw& t) {
	m_rect = t.m_rect;
	m_type = t.m_type;
	m_pencol = t.m_pencol;
	m_brushcol = t.m_brushcol;
	m_spoint = t.m_spoint;
	m_epoint = t.m_epoint;
	return *this;
}

void CMyDraw::Serialize(CArchive& ar) {
	CObject::Serialize(ar);
	
	if (ar.IsStoring()) {	//저장하기
		ar << m_rect << m_type << m_pencol << m_brushcol;
	}
	else {	//불러오기
		ar >> m_rect >> m_type >> m_pencol >> m_brushcol;
	}
}

void CMyDraw::SetType(int type) {
	m_type = type;
}

void CMyDraw::SetRect(CRect rect) {
	m_rect = rect;
}

void CMyDraw::SetPenColor(COLORREF pencol) {
	m_pencol = pencol;
}

void CMyDraw::SetBrushColor(COLORREF brushcol) {
	m_brushcol = brushcol;
}

void CMyDraw::SetStartPoint(CPoint point) {
	m_spoint = point;
}

void CMyDraw::SetEndPoint(CPoint point) {
	m_epoint = point;
}

int* CMyDraw::GetType() {
	return &m_type;
}

CRect* CMyDraw::GetRect() {
	return &m_rect;
}

COLORREF* CMyDraw::GetPenColor() {
	return &m_pencol;
}

COLORREF* CMyDraw::GetBrushColor() {
	return &m_brushcol;
}

CPoint* CMyDraw::GetStartPoint() {
	return &m_spoint;
}

CPoint* CMyDraw::GetEndPoint() {
	return &m_epoint;
}