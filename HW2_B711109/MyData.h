#pragma once

#include <math.h>
#include <time.h>

class CMyData
{
public:
	CMyData();
	CMyData(CPoint st, CPoint end, COLORREF col, CString str);
	~CMyData();
	//Set Function
	void SetStartPoint(CPoint pt);
	void SetEndPoint(CPoint pt);
	void SetMyString(CString st);
	void SetPenColor(COLORREF col);

	//Get Function
	CPoint* GetStartPoint();
	CPoint* GetEndPoint();
	CString* GetString();
	COLORREF* GetPenColor();

private:
	CPoint m_mystart;
	CPoint m_myend;
	COLORREF m_pencolor;
	CString m_mystr;
};