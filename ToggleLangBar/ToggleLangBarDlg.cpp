// ToggleLangBarDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ToggleLangBar.h"
#include "ToggleLangBarDlg.h"
#include <msctf.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ダイアログ データ
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CToggleLangBarDlg ダイアログ




CToggleLangBarDlg::CToggleLangBarDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CToggleLangBarDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CToggleLangBarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CToggleLangBarDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_ONOFF, &CToggleLangBarDlg::OnClickBtnToggleLangBar)
END_MESSAGE_MAP()


// CToggleLangBarDlg メッセージ ハンドラ

BOOL CToggleLangBarDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// 言語バーの表示状態を取得する
	HRESULT hr;
	ITfLangBarMgr* pLangBarMgr;

	CoInitialize(NULL);
	hr = CoCreateInstance(CLSID_TF_LangBarMgr,
							NULL,
							CLSCTX_INPROC_SERVER,
							IID_ITfLangBarMgr,
							(void**)&pLangBarMgr);

	if (SUCCEEDED(hr)) {
		pLangBarMgr->GetShowFloatingStatus(&dwLangBarStatus);
		pLangBarMgr->Release();
		// タスクバーにいるのかフローティングなのかだけを知りたいので、マスクかける。
		dwLangBarStatus = dwLangBarStatus & (TF_SFT_DESKBAND | TF_SFT_HIDDEN);
	}

	CoUninitialize();

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CToggleLangBarDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CToggleLangBarDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CToggleLangBarDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CToggleLangBarDlg::OnClickBtnToggleLangBar()
{
	HRESULT hr;
	ITfLangBarMgr* pLangBarMgr;

	CoInitialize(NULL);
	hr = CoCreateInstance(CLSID_TF_LangBarMgr,
							NULL,
							CLSCTX_INPROC_SERVER,
							IID_ITfLangBarMgr,
							(void**)&pLangBarMgr);

	if (SUCCEEDED(hr)) {
		// タスクバー格納とフローティングとを強制的にスイッチする
		if (dwLangBarStatus == TF_SFT_DESKBAND) {
			pLangBarMgr->ShowFloating(TF_SFT_SHOWNORMAL);
			dwLangBarStatus = TF_SFT_SHOWNORMAL;
		} else {
			pLangBarMgr->ShowFloating(TF_SFT_DESKBAND);
			dwLangBarStatus = TF_SFT_DESKBAND;
		}
		pLangBarMgr->Release();
	}

	CoUninitialize();

	return;
}
