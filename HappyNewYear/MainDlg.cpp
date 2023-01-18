﻿
// MainDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "HappyNewYear.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include "WordWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

UINT8 Index = 0;

// CMainDlg 对话框



CMainDlg::CMainDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HAPPYNEWYEAR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAIN_TEXT, m_szMainText);
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMainDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMainDlg 消息处理程序

BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_Font.CreatePointFont(150, TEXT("宋体"));
	m_szMainText.SetFont(&m_Font);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMainDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMainDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if (Index == 0)
	{
		//this->EnableWindow(FALSE);
		this->GetDlgItem(IDOK)->EnableWindow(FALSE);
		CRuntimeClass* pWordWndRunTimeClass = RUNTIME_CLASS(CWordWnd);
		for (INT i = 0; i < 25; i++)
		{
			CWordWnd* pWordWnd = (CWordWnd*)pWordWndRunTimeClass->CreateObject();
			pWordWnd->Create(nullptr, TEXT("祝福"), 
				WS_CAPTION | WS_POPUP, CWordWnd::rectDefault, this);
			this->m_lWordWnd.AddTail(pWordWnd);
			pWordWnd->ShowWindow(SW_NORMAL);
			pWordWnd->UpdateWindow();
			Sleep(200);
		}
		//this->EnableWindow(TRUE);
		this->SetFocus();
		this->SetDlgItemTextW(IDOK, TEXT("收到"));
		this->GetDlgItem(IDOK)->EnableWindow(TRUE);
		this->UpdateData(FALSE);
		++Index;
	}
	else if(Index == 1)
	{
		this->SetDlgItemTextW(IDC_MAIN_TEXT, TEXT("一岁一礼，一寸欢喜\n愿新春已后，吉吉利利，百事都如意！"));
		this->UpdateData(FALSE);
		++Index;
	}
	else
	{
		POSITION pos = m_lWordWnd.GetHeadPosition();
		CWordWnd* wordWnd = nullptr;
		while (pos)
		{
			wordWnd = m_lWordWnd.GetNext(pos);
			wordWnd->DestroyWindow();
			wordWnd = nullptr;
		}
		m_lWordWnd.RemoveAll();
		CDialogEx::OnOK();
	}
}
