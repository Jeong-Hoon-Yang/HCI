#include "pch.h"
#include "MyData.h"

CMyData::CMyData() {
	m_mystart = CPoint(0, 0);
	m_myend = CPoint(0, 0);
	m_pencolor = RGB(0, 0, 0);
	m_mystr = CString("");
}

CMyData::CMyData(CPoint st, CPoint end, COLORREF col, CString str) {
	m_mystart = st;
	m_myend = end;
	m_pencolor = col;
	m_mystr = str;
}

CMyData::~CMyData() {}

void CMyData::SetStartPoint(CPoint pt) {
	m_mystart = pt;
}

void CMyData::SetEndPoint(CPoint pt) {
	m_myend = pt;
}

void CMyData::SetMyString(CString str) {
	m_mystr = str;
}

void CMyData::SetPenColor(COLORREF col) {
	m_pencolor = col;
}

CPoint* CMyData::GetStartPoint() {
	return &m_mystart;
}

CPoint* CMyData::GetEndPoint() {
	return &m_myend;
}

CString* CMyData::GetString() {
	return &m_mystr;
}

COLORREF* CMyData::GetPenColor() {
	return &m_pencolor;
}