// ToggleLangBar.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CToggleLangBarApp:
// このクラスの実装については、ToggleLangBar.cpp を参照してください。
//

class CToggleLangBarApp : public CWinApp
{
public:
	CToggleLangBarApp();

// オーバーライド
	public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CToggleLangBarApp theApp;