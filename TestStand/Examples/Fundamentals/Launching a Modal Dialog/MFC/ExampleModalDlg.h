#if !defined(AFX_EXAMPLEMODALDLG_H__ABCC501B_B22F_474A_BB82_1DA17C8A3455__INCLUDED_)
#define AFX_EXAMPLEMODALDLG_H__ABCC501B_B22F_474A_BB82_1DA17C8A3455__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExampleModalDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExampleModalDlg dialog

class CExampleModalDlg : public CDialog
{
// Construction
public:
    CExampleModalDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CExampleModalDlg)
    enum { IDD = IDD_MODAL_DIALOG };
        // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CExampleModalDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CExampleModalDlg)
    virtual void OnOK();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXAMPLEMODALDLG_H__ABCC501B_B22F_474A_BB82_1DA17C8A3455__INCLUDED_)
