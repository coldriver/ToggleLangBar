// ToggleLangBarDlg.h : ヘッダー ファイル
//

#pragma once


// CToggleLangBarDlg ダイアログ
class CToggleLangBarDlg : public CDialog
{
// コンストラクション
public:
	CToggleLangBarDlg(CWnd* pParent = NULL);	// 標準コンストラクタ

// ダイアログ データ
	enum { IDD = IDD_TOGGLELANGBAR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート

private:
	DWORD dwLangBarStatus;

// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickBtnToggleLangBar();
};
