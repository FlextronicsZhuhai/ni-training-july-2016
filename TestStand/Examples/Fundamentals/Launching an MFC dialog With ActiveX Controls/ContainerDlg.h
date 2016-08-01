#if !defined(AFX_CONTAINERDLG_H__0902A56E_C27B_11D2_A3EC_006008CA11D4__INCLUDED_)
#define AFX_CONTAINERDLG_H__0902A56E_C27B_11D2_A3EC_006008CA11D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ContainerDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CContainerDlg dialog

class CContainerDlg : public CDialog
{
// Construction
public:
    CContainerDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CContainerDlg)
    enum { IDD = IDD_CONTAINER_DLG };
        // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CContainerDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CContainerDlg)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTAINERDLG_H__0902A56E_C27B_11D2_A3EC_006008CA11D4__INCLUDED_)
