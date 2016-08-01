// CheckStepNameLength.h : main header file for the CheckStepNameLength DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CCheckStepNameLengthApp
// See CheckStepNameLength.cpp for the implementation of this class
//

class CCheckStepNameLengthApp : public CWinApp
{
public:
	CCheckStepNameLengthApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
