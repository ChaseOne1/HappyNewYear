#pragma once
class CWordView;

// CWordWnd 框架

class CWordWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CWordWnd)
public:
	//CWordWnd(CWnd* pParent = nullptr);
protected:
	CWordWnd();           // 动态创建所使用的受保护的构造函数
	virtual ~CWordWnd();

private:
	COLORREF m_BgColor;
	CString m_szFontName;
	CString m_szWord;
protected:
	DECLARE_MESSAGE_MAP()

	afx_msg int OnCreate(LPCREATESTRUCT);
	afx_msg void OnPaint();
};


