#pragma once
#include <afx.h>
#include <afxtempl.h>
class CMyDraw :
    public CObject
{
    DECLARE_SERIAL(CMyDraw)

public:
    CMyDraw();
    CMyDraw(const CMyDraw& t);
    ~CMyDraw();
    CMyDraw& operator=(const CMyDraw& t);

    void Serialize(CArchive& ar);

    // make Set & Get function Here
	void SetType(int type);
    void SetRect(CRect rect);
    void SetStartPoint(CPoint point);
    void SetEndPoint(CPoint point);
    void SetPenColor(COLORREF pencol);
    void SetBrushColor(COLORREF brushcol);

    int* GetType();
    CRect* GetRect();
    CPoint* GetStartPoint();
    CPoint* GetEndPoint();
    COLORREF* GetPenColor();
    COLORREF* GetBrushColor();

private:
    int m_type; //1 : rectangle, 2 : ellipse, 3 : line
    CRect m_rect;   //save start_point & end_point
    CPoint m_spoint, m_epoint;  //save start_point & end_point for draw line
    COLORREF m_pencol;  //pen color
    COLORREF m_brushcol;    //bruch_color
};

