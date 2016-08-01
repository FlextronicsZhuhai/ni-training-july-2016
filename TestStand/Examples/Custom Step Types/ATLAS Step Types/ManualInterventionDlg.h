// ManualInterventionDlg.h: interface for the CManualInterventionDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MANUALINTERVENTIONDLG_H__346FFC84_4258_45C0_9699_4AAFC4BDA69D__INCLUDED_)
#define AFX_MANUALINTERVENTIONDLG_H__346FFC84_4258_45C0_9699_4AAFC4BDA69D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CManualInterventionDlg dialog

class CManualInterventionDlg : public CDialog
{
// Construction
public:
    CManualInterventionDlg(
        const TS::IEnginePtr& engine, 
        CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CManualInterventionDlg)
    enum { IDD = IDD_MANUAL_INTERVENTION };
        // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA

    bool Display(const TS::ExecutionPtr& execution, const RTSAX::ITpsServerExPtr& tpsServer);

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CManualInterventionDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CManualInterventionDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnContinue();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    // Attributes
    const TS::IEnginePtr&   m_Engine;
    bool                    m_ManualInterventionHandled;

    // Operations
    void InitLabels();
};

#endif // !defined(AFX_MANUALINTERVENTIONDLG_H__346FFC84_4258_45C0_9699_4AAFC4BDA69D__INCLUDED_)
