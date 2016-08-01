#if !defined(AFX_CONFIGUREEXECUTIONDLG_H__6DAEBABD_E486_446A_94D1_FCD804EF8FB0__INCLUDED_)
#define AFX_CONFIGUREEXECUTIONDLG_H__6DAEBABD_E486_446A_94D1_FCD804EF8FB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigureExecutionDlg.h : header file
//

#include "afxcmn.h"
#include "resource.h"
#include "ATLASParameter.h"

/////////////////////////////////////////////////////////////////////////////
// CConfigureExecutionDlg dialog

class CConfigureExecutionDlg : public CDialog
{
// Construction
public:
    CConfigureExecutionDlg(
        const TS::IEnginePtr &engine,
        const TS::SequenceContextPtr &sequenceContext,
        BOOL readOnly, 
        CATLASParameterArray& parameters, 
        CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CConfigureExecutionDlg)
    enum { IDD = IDD_ATLAS };
    CComboBox   m_ParameterPassModeCombo;
    CListBox    m_ParametersListBox;
    CButton m_ExecuteRemotelyButton;
    CComboBox   m_ParameterDataTypeCombo;
    CString m_TPS;
    BOOL    m_ExecuteRemotely;
    CString m_RemoteHostNameExpr;
    BOOL    m_IsGlobalVariable;
    CString m_absoluteTPS;
    CString m_ParameterName;
    //}}AFX_DATA

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CConfigureExecutionDlg)
    public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CConfigureExecutionDlg)
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    virtual void OnCancel();
    afx_msg void OnRemote();
    afx_msg void OnTPSBrowse();
    afx_msg void OnAddParameterButton();
    afx_msg void OnDeleteParameterButton();
    afx_msg void OnParameterValueExprBrowseBtn();
    afx_msg void OnRemoteHostExprEditBrowseBtn(LPDISPATCH btn);
    afx_msg void OnChangeTpsRelativePathEdit();
    afx_msg void OnChangeParameterNameEdit();
    afx_msg void OnSelchangeParametersList();
    afx_msg void OnMoveupParameterButton();
    afx_msg void OnMovedownParameterButton();
    DECLARE_EVENTSINK_MAP()
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    // Attributes
    BOOL                            m_ReadOnly;
    const TS::IEnginePtr            m_Engine;
    const TS::SequenceContextPtr    m_SequenceContext;
    TSUI::IExpressionEditPtr        m_RemoteHostNameExprEdit;
    TSUI::IExpressionEditPtr        m_ParameterValueExprEdit;
    int                             m_SelectedParameterIdx;
    CATLASParameterArray&           m_Parameters;
    CToolTipCtrl                    m_ToolTipCtrl;

    // Operations
    void InitLabels();
    void ShowHideRemoteItems();
    void ShowHideParametersItems();
    bool GetParameterControls();
    void SetParameterControls();
    void SetAbsolutePath();
    void SetButtonImage(int buttonId, int iconId);
    void MoveSelectedParameter(int offset);

    BOOL SyntaxCheckExpression(CDialog &dialog, const TS::IEnginePtr &engine, const CString &expression, 
       const CString &errorMsgTitle, const CString &errorMsgPrefix);
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGUREEXECUTIONDLG_H__6DAEBABD_E486_446A_94D1_FCD804EF8FB0__INCLUDED_)
