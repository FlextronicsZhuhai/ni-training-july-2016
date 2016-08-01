#pragma once
#include "afxwin.h"


// CConfigureCheckStepNameLengthDialog dialog

class CConfigureCheckStepNameLengthDialog : public CDialog
{
	DECLARE_DYNAMIC(CConfigureCheckStepNameLengthDialog)

public:
	CConfigureCheckStepNameLengthDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CConfigureCheckStepNameLengthDialog();

	int GetMaximumStepNameLength();
	void SetMaximumStepNameLength(int maximumStepNameLength);

// Dialog Data
	enum { IDD = IDD_CONFIG_STEP_NAME_LENGTH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit MaxStepNameLengthEdit;
protected:
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();

private:
	int mMaximumStepNameLength;
};
