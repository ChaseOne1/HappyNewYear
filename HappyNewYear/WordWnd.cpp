// WordWnd.cpp: 实现文件
//
#pragma warning(disable:6031)

#include "pch.h"
#include "HappyNewYear.h"
#include "WordWnd.h"

//祝福窗口
#define WORD_WIDTH 585	
#define WORD_HEIGHT 255
#define BG_PERCENT 0.7	//背景占宽比

#define STEXT_SIZE 300	//短祝福字体高(宽自动/单位十分之一磅)
#define LTEXT_SIZE 180	//长祝福字体高(宽自动/单位十分之一磅)

#define WORD_START 130	//祝福语起始UINT ID
#define WORD_NUM 25		//祝福语数量

#define FONT_START 200	//字体名起始UINT ID
#define FONT_NUM 9		//字体数目

constexpr INT BG_WIDTH = static_cast<INT>(WORD_WIDTH * BG_PERCENT);


// CWordWnd

IMPLEMENT_DYNCREATE(CWordWnd, CFrameWnd)

CWordWnd::CWordWnd() :m_BgColor(RGB(0, 0, 0)), m_szFontName("宋体"), m_szWord("祝福")
{
}

CWordWnd::~CWordWnd()
{
}


BEGIN_MESSAGE_MAP(CWordWnd, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CWordWnd 消息处理程序

int CWordWnd::OnCreate(LPCREATESTRUCT data)
{
	CRect parentRect, currRect;
	INT sysWidth = 0, sysHeight = 0;
	this->GetWindow(GW_OWNER)->GetWindowRect(&parentRect);
	sysWidth = ::GetSystemMetrics(SM_CXFULLSCREEN);
	sysHeight = ::GetSystemMetrics(SM_CYFULLSCREEN);
	do
	{
		currRect.left = rand() % (sysWidth - WORD_WIDTH);
		currRect.top = rand() % (sysHeight - WORD_HEIGHT);
		currRect.right = currRect.left + WORD_WIDTH;
		currRect.bottom = currRect.top + WORD_HEIGHT;
	} while (parentRect.PtInRect(CPoint(currRect.left, currRect.top))
		|| parentRect.PtInRect(CPoint(currRect.right, currRect.top))
		|| parentRect.PtInRect(CPoint(currRect.left, currRect.bottom))
		|| parentRect.PtInRect(CPoint(currRect.right, currRect.bottom)));
	this->MoveWindow(&currRect, FALSE);

	//Font
	m_szFontName.LoadStringW(rand() % FONT_NUM + FONT_START);

	//Color
	static UINT Index = WORD_START;
	m_BgColor = RGB(rand() % 255, rand() % 255, rand() % 255);

	//Word
	m_szWord.LoadStringW(Index++ >= WORD_NUM + WORD_START ?
		Index = WORD_START : Index - 1);
	return 0;
}

void CWordWnd::OnPaint()
{
	CPaintDC dc(this);
	//BackGround
	CRect bgRect;
	this->GetClientRect(&bgRect);
	bgRect.left = (bgRect.right >> 1) - (BG_WIDTH >> 1);
	bgRect.right = (bgRect.right >> 1) + (BG_WIDTH >> 1);
	CBrush& brush = CBrush(m_BgColor);
	dc.FillRect(bgRect, &brush);
	brush.DeleteObject();

	//Word
	CFont font;
	INT size = STEXT_SIZE;
	if (m_szWord.GetLength() > 8)
		size = LTEXT_SIZE;
	BOOL bLoadResult = font.CreatePointFont(size, this->m_szFontName);
	while(!bLoadResult)
		m_szFontName.LoadStringW(rand() % FONT_NUM + FONT_START);
	dc.SetTextColor(RGB(0, 0, 0));
	dc.SetBkMode(TRANSPARENT);
	dc.SelectObject(font);
	dc.DrawText(m_szWord, &bgRect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	font.DeleteObject();
}
