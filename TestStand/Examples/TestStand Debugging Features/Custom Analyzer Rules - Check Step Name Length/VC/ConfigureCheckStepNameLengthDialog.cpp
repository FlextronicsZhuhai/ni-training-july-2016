// ConfigureCheckStepNameLengthDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CheckStepNameLength.h"
#include "ConfigureCheckStepNameLengthDialog.h"


// CConfigureCheckStepNameLengthDialog dialog

IMPLEMENT_DYNAMIC(CConfigureCheckStepNameLengthDialog, CDialog)

CConfigureCheckStepNameLengthDialog::CConfigureCheckStepNameLengthDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigureCheckStepNameLengthDialog::IDD, pParent)
{

}

CConfigureCheckStepNameLengthDialog::~CConfigureCheckStepNameLengthDialog()
{
}

void CConfigureCheckStepNameLengthDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, MaxStepNameLengthEdit);
}


BEGIN_MESSAGE_MAP(CConfigureCheckStepNameLengthDialog, CDialog)
END_MESSAGE_MAP()


// CConfigureCheckStepNameLengthDialog message handlers

void CConfigureCheckStepNameLengthDialog::OnOK()
{
	// Set the maximum from the value in the control
	// (We're assuming the text is a valid number)
	CString editControlText;
	MaxStepNameLengthEdit.GetWindowText(editControlText);
	mMaximumStepNameLength = _tstoi(editControlText);

	CDialog::OnOK();
}

BOOL CConfigureCheckStepNameLengthDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString text;
	text.Format("%d", mMaximumStepNameLength);

	MaxStepNameLengthEdit.SetWindowText(text);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigureCheckStepNameLengthDialog::SetMaximumStepNameLength(int maximumStepNameLength)
{
	mMaximumStepNameLength = maximumStepNameLength;
}

int CConfigureCheckStepNameLengthDialog::GetMaximumStepNameLength()
{
	return mMaximumStepNameLength;
}