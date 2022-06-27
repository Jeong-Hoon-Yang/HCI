
// HW3Doc.cpp: CHW3Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "HW3.h"
#endif

#include "HW3Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CHW3Doc

IMPLEMENT_DYNCREATE(CHW3Doc, CDocument)

BEGIN_MESSAGE_MAP(CHW3Doc, CDocument)
	ON_COMMAND(ID_FIGURE_RECTANGLE, &CHW3Doc::OnFigureRectangle)
	ON_UPDATE_COMMAND_UI(ID_FIGURE_RECTANGLE, &CHW3Doc::OnUpdateFigureRectangle)
	ON_COMMAND(ID_FIGURE_ELLIPSE, &CHW3Doc::OnFigureEllipse)
	ON_UPDATE_COMMAND_UI(ID_FIGURE_ELLIPSE, &CHW3Doc::OnUpdateFigureEllipse)
	ON_COMMAND(ID_FIGURE_LINE, &CHW3Doc::OnFigureLine)
	ON_UPDATE_COMMAND_UI(ID_FIGURE_LINE, &CHW3Doc::OnUpdateFigureLine)
	ON_COMMAND(ID_PEN_BLACK, &CHW3Doc::OnPenBlack)
	ON_UPDATE_COMMAND_UI(ID_PEN_BLACK, &CHW3Doc::OnUpdatePenBlack)
	ON_COMMAND(ID_PEN_RED, &CHW3Doc::OnPenRed)
	ON_UPDATE_COMMAND_UI(ID_PEN_RED, &CHW3Doc::OnUpdatePenRed)
	ON_COMMAND(ID_PEN_GREEN, &CHW3Doc::OnPenGreen)
	ON_UPDATE_COMMAND_UI(ID_PEN_GREEN, &CHW3Doc::OnUpdatePenGreen)
	ON_COMMAND(ID_PEN_BLUE, &CHW3Doc::OnPenBlue)
	ON_UPDATE_COMMAND_UI(ID_PEN_BLUE, &CHW3Doc::OnUpdatePenBlue)
	ON_COMMAND(ID_BRUSH_RED, &CHW3Doc::OnBrushRed)
	ON_UPDATE_COMMAND_UI(ID_BRUSH_RED, &CHW3Doc::OnUpdateBrushRed)
	ON_COMMAND(ID_BRUSH_GREEN, &CHW3Doc::OnBrushGreen)
	ON_UPDATE_COMMAND_UI(ID_BRUSH_GREEN, &CHW3Doc::OnUpdateBrushGreen)
	ON_COMMAND(ID_BRUSH_BLUE, &CHW3Doc::OnBrushBlue)
	ON_UPDATE_COMMAND_UI(ID_BRUSH_BLUE, &CHW3Doc::OnUpdateBrushBlue)
	ON_COMMAND(ID_BRUSH_WHITE, &CHW3Doc::OnBrushWhite)
	ON_UPDATE_COMMAND_UI(ID_BRUSH_WHITE, &CHW3Doc::OnUpdateBrushWhite)
	ON_COMMAND(ID_FIGURE_POLYGON, &CHW3Doc::OnFigurePolygon)
	ON_UPDATE_COMMAND_UI(ID_FIGURE_POLYGON, &CHW3Doc::OnUpdateFigurePolygon)
END_MESSAGE_MAP()


// CHW3Doc 생성/소멸

CHW3Doc::CHW3Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CHW3Doc::~CHW3Doc()
{
}

BOOL CHW3Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.
	m_mylist.RemoveAll();
	m_curDraw.SetPenColor(1);	//Default type = rectangle
	m_curDraw.SetPenColor(RGB(0, 0, 0));
	m_curDraw.SetBrushColor(RGB(255, 255, 255));
	m_curDraw.SetStartPoint({ 0,0 });
	m_curDraw.SetEndPoint({ 0,0 });

	//pencol, brushcol 초기화 여기서 설정해야함
	return TRUE;
}




// CHW3Doc serialization

void CHW3Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
		m_curDraw.Serialize(ar);
		m_mylist.Serialize(ar);
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
		m_curDraw.Serialize(ar);
		m_mylist.Serialize(ar);
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CHW3Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CHW3Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CHW3Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CHW3Doc 진단

#ifdef _DEBUG
void CHW3Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHW3Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CHW3Doc 명령


void CHW3Doc::OnFigureRectangle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_curDraw.SetType(1);
	SetModifiedFlag();
}


void CHW3Doc::OnUpdateFigureRectangle(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(*m_curDraw.GetType() == 1);
}


void CHW3Doc::OnFigureEllipse()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_curDraw.SetType(2);
	SetModifiedFlag();
}


void CHW3Doc::OnUpdateFigureEllipse(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(*m_curDraw.GetType() == 2);
}


void CHW3Doc::OnFigureLine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_curDraw.SetType(3);
	SetModifiedFlag();
}


void CHW3Doc::OnUpdateFigureLine(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(*m_curDraw.GetType() == 3);
}

void CHW3Doc::OnFigurePolygon()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_curDraw.SetType(4);
	SetModifiedFlag();
}


void CHW3Doc::OnUpdateFigurePolygon(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(*m_curDraw.GetType() == 4);
}



void CHW3Doc::OnPenBlack()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_curDraw.SetPenColor(RGB(0, 0, 0));
	SetModifiedFlag();
}


void CHW3Doc::OnUpdatePenBlack(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(*m_curDraw.GetPenColor() == RGB(0, 0, 0));
}


void CHW3Doc::OnPenRed()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_curDraw.SetPenColor(RGB(255, 0, 0));
	SetModifiedFlag();
}


void CHW3Doc::OnUpdatePenRed(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(*m_curDraw.GetPenColor() == RGB(255, 0, 0));
}


void CHW3Doc::OnPenGreen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_curDraw.SetPenColor(RGB(0, 255, 0));
	SetModifiedFlag();
}


void CHW3Doc::OnUpdatePenGreen(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(*m_curDraw.GetPenColor() == RGB(0, 255, 0));
}


void CHW3Doc::OnPenBlue()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_curDraw.SetPenColor(RGB(0, 0, 255));
	SetModifiedFlag();
}


void CHW3Doc::OnUpdatePenBlue(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(*m_curDraw.GetPenColor() == RGB(0, 0, 255));
}


void CHW3Doc::OnBrushRed()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_curDraw.SetBrushColor(RGB(255, 0, 0));
	SetModifiedFlag();
}


void CHW3Doc::OnUpdateBrushRed(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(*m_curDraw.GetBrushColor() == RGB(255, 0, 0));
}


void CHW3Doc::OnBrushGreen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_curDraw.SetBrushColor(RGB(0, 255, 0));
	SetModifiedFlag();
}


void CHW3Doc::OnUpdateBrushGreen(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(*m_curDraw.GetBrushColor() == RGB(0, 255, 0));
}


void CHW3Doc::OnBrushBlue()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_curDraw.SetBrushColor(RGB(0, 0, 255));
	SetModifiedFlag();
}


void CHW3Doc::OnUpdateBrushBlue(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(*m_curDraw.GetBrushColor() == RGB(0, 0, 255));
}


void CHW3Doc::OnBrushWhite()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_curDraw.SetBrushColor(RGB(255, 255, 255));
	SetModifiedFlag();
}


void CHW3Doc::OnUpdateBrushWhite(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(*m_curDraw.GetBrushColor() == RGB(255, 255, 255));
}
