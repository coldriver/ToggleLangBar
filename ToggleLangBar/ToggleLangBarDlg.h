// ToggleLangBarDlg.h : �w�b�_�[ �t�@�C��
//

#pragma once


// CToggleLangBarDlg �_�C�A���O
class CToggleLangBarDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CToggleLangBarDlg(CWnd* pParent = NULL);	// �W���R���X�g���N�^

// �_�C�A���O �f�[�^
	enum { IDD = IDD_TOGGLELANGBAR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �T�|�[�g

private:
	DWORD dwLangBarStatus;

// ����
protected:
	HICON m_hIcon;

	// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickBtnToggleLangBar();
};
