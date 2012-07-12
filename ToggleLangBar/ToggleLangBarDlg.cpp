// ToggleLangBarDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "ToggleLangBar.h"
#include "ToggleLangBarDlg.h"
#include <msctf.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// �A�v���P�[�V�����̃o�[�W�������Ɏg���� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

// ����
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


// CToggleLangBarDlg �_�C�A���O




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


// CToggleLangBarDlg ���b�Z�[�W �n���h��

BOOL CToggleLangBarDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "�o�[�W�������..." ���j���[���V�X�e�� ���j���[�ɒǉ����܂��B

	// IDM_ABOUTBOX �́A�V�X�e�� �R�}���h�͈͓̔��ɂȂ���΂Ȃ�܂���B
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

	// ���̃_�C�A���O�̃A�C�R����ݒ肵�܂��B�A�v���P�[�V�����̃��C�� �E�B���h�E���_�C�A���O�łȂ��ꍇ�A
	//  Framework �́A���̐ݒ�������I�ɍs���܂��B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R���̐ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R���̐ݒ�

	// ����o�[�̕\����Ԃ��擾����
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
		// �^�X�N�o�[�ɂ���̂��t���[�e�B���O�Ȃ̂�������m�肽���̂ŁA�}�X�N������B
		dwLangBarStatus = dwLangBarStatus & (TF_SFT_DESKBAND | TF_SFT_HIDDEN);
	}

	CoUninitialize();

	return TRUE;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
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

// �_�C�A���O�ɍŏ����{�^����ǉ�����ꍇ�A�A�C�R����`�悷�邽�߂�
//  ���̃R�[�h���K�v�ł��B�h�L�������g/�r���[ ���f�����g�� MFC �A�v���P�[�V�����̏ꍇ�A
//  ����́AFramework �ɂ���Ď����I�ɐݒ肳��܂��B

void CToggleLangBarDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N���C�A���g�̎l�p�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R���̕`��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ���[�U�[���ŏ��������E�B���h�E���h���b�O���Ă���Ƃ��ɕ\������J�[�\�����擾���邽�߂ɁA
//  �V�X�e�������̊֐����Ăяo���܂��B
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
		// �^�X�N�o�[�i�[�ƃt���[�e�B���O�Ƃ������I�ɃX�C�b�`����
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
