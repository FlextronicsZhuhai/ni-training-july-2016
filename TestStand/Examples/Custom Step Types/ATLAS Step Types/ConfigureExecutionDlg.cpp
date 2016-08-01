// ConfigureExecution.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Utils.h"
#include "tsvcutil.h"
#include "ATLASParameter.h"
#include "ConfigureExecutionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Remote host expression edit button kinds
const int   REMOTE_HOST_NETWORK_BROWSE_BTN = 1000;  // network browse button

/////////////////////////////////////////////////////////////////////////////
// CConfigureExecutionDlg dialog

CConfigureExecutionDlg::CConfigureExecutionDlg(
        const TS::IEnginePtr &engine,
        const TS::SequenceContextPtr &sequenceContext,
        BOOL readOnly,
        CATLASParameterArray& parameters, 
        CWnd* pParent /*=NULL*/)
    : 
        CDialog(CConfigureExecutionDlg::IDD, pParent), 
        m_Engine(engine),
        m_SequenceContext(sequenceContext),
        m_ReadOnly(readOnly), 
        m_Parameters(parameters)
{
    //{{AFX_DATA_INIT(CConfigureExecutionDlg)
    m_TPS = _T("");
    m_ExecuteRemotely = FALSE;
    m_RemoteHostNameExpr = _T("");
    m_IsGlobalVariable = FALSE;
    m_absoluteTPS = _T("");
    m_ParameterName = _T("");
    //}}AFX_DATA_INIT

    // Create tooltip
    if (!m_ToolTipCtrl.Create(this))
    {
        TRACE("Unable To create ToolTip\n");           
        return ;
    }
}

BOOL CConfigureExecutionDlg::PreTranslateMessage(MSG* pMsg) 
{
    m_ToolTipCtrl.RelayEvent(pMsg);
    return CDialog::PreTranslateMessage(pMsg);
}

void CConfigureExecutionDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CConfigureExecutionDlg)
    DDX_Control(pDX, IDC_PARAMETER_MODE_COMBO, m_ParameterPassModeCombo);
    DDX_Control(pDX, IDC_PARAMETERS_LIST, m_ParametersListBox);
    DDX_Control(pDX, IDC_REMOTE, m_ExecuteRemotelyButton);
    DDX_Control(pDX, IDC_PARAMETER_DATA_TYPE_COMBO, m_ParameterDataTypeCombo);
    DDX_Text(pDX, IDC_TPS, m_TPS);
    DDX_Check(pDX, IDC_REMOTE, m_ExecuteRemotely);
    DDX_Check(pDX, IDC_GLOBAL_VARIABLE_CHECK, m_IsGlobalVariable);
    DDX_Text(pDX, IDC_TPS_FULL_PATH, m_absoluteTPS);
    DDX_Text(pDX, IDC_PARAMETER_NAME_EDIT, m_ParameterName);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CConfigureExecutionDlg, CDialog)
    //{{AFX_MSG_MAP(CConfigureExecutionDlg)
    ON_BN_CLICKED(IDC_REMOTE, OnRemote)
    ON_BN_CLICKED(IDC_BROWSE, OnTPSBrowse)
    ON_BN_CLICKED(IDC_ADD_PARAMETER_BUTTON, OnAddParameterButton)
    ON_BN_CLICKED(IDC_DELETE_PARAMETER_BUTTON, OnDeleteParameterButton)
    ON_EN_CHANGE(IDC_TPS, OnChangeTpsRelativePathEdit)
    ON_EN_CHANGE(IDC_PARAMETER_NAME_EDIT, OnChangeParameterNameEdit)
    ON_LBN_SELCHANGE(IDC_PARAMETERS_LIST, OnSelchangeParametersList)
    ON_BN_CLICKED(IDC_MOVEUP_PARAMETER_BUTTON, OnMoveupParameterButton)
    ON_BN_CLICKED(IDC_MOVEDOWN_PARAMETER_BUTTON, OnMovedownParameterButton)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CConfigureExecutionDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CConfigureExecutionDlg)
    ON_EVENT(CConfigureExecutionDlg, IDC_REMOTE_HOST_EXPR_EDIT, 5 /* ButtonClick */, OnRemoteHostExprEditBrowseBtn, VTS_DISPATCH)
    //}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigureExecutionDlg message handlers

BOOL CConfigureExecutionDlg::OnInitDialog() 
{
    CDialog::OnInitDialog();

    InitLabels();
    SetAbsolutePath();

    // Get sequence context for expression edit controls
    const TS::PropertyObjectPtr seqContext = m_SequenceContext->AsPropertyObject();

    // Set remote hostname expression edit control properties
    CWnd* editCtrl = GetDlgItem(IDC_REMOTE_HOST_EXPR_EDIT);
    editCtrl->GetControlUnknown()->QueryInterface(&m_RemoteHostNameExprEdit);
    m_RemoteHostNameExprEdit->PutRefContext(seqContext);
    m_RemoteHostNameExprEdit->PutRefEngine(m_Engine);
    m_RemoteHostNameExprEdit->PutAllowEmpty(VARIANT_FALSE);
    m_RemoteHostNameExprEdit->PutText((LPCTSTR)m_RemoteHostNameExpr);
    m_RemoteHostNameExprEdit->PutSelLength(-1);
    m_RemoteHostNameExprEdit->PutReadOnly(m_ReadOnly ? VARIANT_TRUE : VARIANT_FALSE);

    // Set parameter value expression edit control properties
    editCtrl = GetDlgItem(IDC_PARAMETER_VALUE_EXPRESSIONEDIT);
    editCtrl->GetControlUnknown()->QueryInterface(&m_ParameterValueExprEdit);
    m_ParameterValueExprEdit->PutRefContext(seqContext);
    m_ParameterValueExprEdit->PutRefEngine(m_Engine);
    m_ParameterValueExprEdit->PutAllowEmpty(VARIANT_FALSE);
    m_ParameterValueExprEdit->PutSelLength(-1);
    m_ParameterValueExprEdit->PutReadOnly(m_ReadOnly ? VARIANT_TRUE : VARIANT_FALSE);

    // Initialize the listbox with parameter names and data
    for (int i = 0; i < m_Parameters.GetSize(); i++)
    {
        m_ParametersListBox.AddString(m_Parameters[i]->m_Name);
        m_ParametersListBox.SetItemDataPtr(i, m_Parameters[i]);
    }

    // Set data type and pass mode comboboxes
    m_ParameterDataTypeCombo.SetCurSel(0);
    m_ParameterPassModeCombo.SetCurSel(0);

    // Set the selected parameter data
    m_SelectedParameterIdx = (m_Parameters.GetSize() > 0) ? 0 : -1;
    m_ParametersListBox.SetCurSel(m_SelectedParameterIdx);
    SetParameterControls();

    GotoDlgCtrl(GetDlgItem(IDC_TPS));

    ShowHideRemoteItems();
    ShowHideParametersItems();

    return FALSE;
}

void CConfigureExecutionDlg::OnOK() 
{
    if (m_ExecuteRemotely)
    {
        if (!SyntaxCheckExpression(*this,m_Engine,(LPCTSTR)m_RemoteHostNameExprEdit->Text,_T("Syntax Error"),_T("")))
            return;

        m_RemoteHostNameExpr = (LPCTSTR)m_RemoteHostNameExprEdit->GetText();
        m_RemoteHostNameExpr.TrimLeft();
        m_RemoteHostNameExpr.TrimRight();
    }
    else
        m_RemoteHostNameExpr = _T("");

    if (!GetParameterControls())    // to get last changes
        return;

    m_Parameters.RemoveAll();
    for (int i = 0; i < m_ParametersListBox.GetCount(); i++)
    {
        CATLASParameter* parameter = (CATLASParameter*) m_ParametersListBox.GetItemDataPtr(i);      
        if (!SyntaxCheckExpression(*this,m_Engine,parameter->m_ValueExpression,_T("Syntax Error"),_T("")))
        {
            m_ParametersListBox.SetCurSel(i);
            OnSelchangeParametersList();    // simulate selection change
            return;
        }
        m_Parameters.Add(parameter);
    }

    CDialog::OnOK();
}

void CConfigureExecutionDlg::OnCancel() 
{
    // need to copy them to the array so they can be deleted
    m_Parameters.RemoveAll();
    for (int i = 0; i < m_ParametersListBox.GetCount(); i++)
        m_Parameters.Add((CATLASParameter*) m_ParametersListBox.GetItemDataPtr(i));
    
    CDialog::OnCancel();
}

void CConfigureExecutionDlg::OnRemote() 
{
    UpdateData(TRUE);
    ShowHideRemoteItems();
}

void CConfigureExecutionDlg::OnTPSBrowse() 
{
    VARIANT_BOOL gotPath;
    std::vector<_bstr_t> pathArr;
    TSUTIL::SafeArray<BSTR, VT_BSTR> selectedPathsArray;
    TSUTIL::SafeArray<BSTR, VT_BSTR> absolutePathsArray;

    CComBSTR intialPath = m_TPS;
    LPCTSTR szFilter = _T("PAWS Files (*.PAW)|*.PAW|All Files (*.*)|*.*||");
    gotPath = m_Engine->DisplayFileDialog(_T(""), _T(""), (LPCTSTR)m_TPS, 
        &selectedPathsArray, &absolutePathsArray, OpenFile_UseRelativePath, "PAW", 
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, vtMissing, NULL, NULL); 

    if (gotPath)
    {
        selectedPathsArray.GetVector(pathArr);
        m_TPS = (LPCTSTR)pathArr[0];

        absolutePathsArray.GetVector(pathArr);
        m_absoluteTPS = (LPCTSTR)pathArr[0];

        UpdateData(FALSE);
    }
}

void CConfigureExecutionDlg::OnAddParameterButton() 
{
    // Create a new parameter entry and assign it a default name
    CATLASParameter* parameter = new CATLASParameter;
    parameter->m_Name.Format(GetResourceString(m_Engine, ATLAS_STEP_TYPE_STRING, _T("DEFAULT_PARAM_NAME")), 
        m_ParametersListBox.GetCount());

    // Add parameter to listbox and update dialog
    m_ParameterName = parameter->m_Name;
    m_SelectedParameterIdx = m_ParametersListBox.AddString(m_ParameterName);
    m_ParametersListBox.SetItemDataPtr(m_SelectedParameterIdx, parameter);
    m_ParametersListBox.SetCurSel(m_SelectedParameterIdx);

    SetParameterControls();
}

void CConfigureExecutionDlg::OnDeleteParameterButton() 
{
    // Delete parameter and reset selection
    delete (CATLASParameter*) m_ParametersListBox.GetItemDataPtr(m_SelectedParameterIdx);
    m_ParametersListBox.DeleteString(m_SelectedParameterIdx);
    m_SelectedParameterIdx--;
    m_ParametersListBox.SetCurSel(m_SelectedParameterIdx);

    SetParameterControls();
    ShowHideParametersItems();
}

void CConfigureExecutionDlg::OnMoveupParameterButton() 
{
    UpdateData();
    MoveSelectedParameter(-1);
    ShowHideParametersItems();
}

void CConfigureExecutionDlg::OnMovedownParameterButton() 
{
    UpdateData();
    MoveSelectedParameter(1);
    ShowHideParametersItems();
}

void CConfigureExecutionDlg::OnRemoteHostExprEditBrowseBtn(LPDISPATCH btn) 
{
    TSUI::ExpressionEditButtonPtr hostBtn = btn;

    // If it's the remote browse button that was hit, show the browse network dialog
    if (hostBtn->Kind == REMOTE_HOST_NETWORK_BROWSE_BTN)
    {
        // Initialize dialog properties
        BROWSEINFO bInfo;
        CWnd *ownerWnd = this;
        LPITEMIDLIST itemIdList = NULL;
        LPITEMIDLIST resultIdList = NULL;
        TCHAR displayNameBuf[MAX_PATH];
        displayNameBuf[0] = _T('\0');
        LPMALLOC malloc = NULL;
        if(::SHGetMalloc(&malloc) != NOERROR)
        {
            return;
        }

        // Prepare and show dialog
        bool okPressed = false;
        try
        {
            CWaitCursor wait;

            // Our location
            ::SHGetSpecialFolderLocation(NULL, CSIDL_NETWORK , &itemIdList);

            // Set dialog properties
            bInfo.hwndOwner = (ownerWnd != NULL) ? ownerWnd->GetSafeHwnd() : ::AfxGetMainWnd()->GetSafeHwnd();
            bInfo.pidlRoot = itemIdList;
            bInfo.pszDisplayName = displayNameBuf;
            bInfo.lpszTitle = _T("");
            bInfo.ulFlags = BIF_BROWSEFORCOMPUTER;
            bInfo.lpfn = NULL;
            bInfo.lParam = 0;
            bInfo.iImage = 0; 

            // Show dialog
            resultIdList = ::SHBrowseForFolder(&bInfo);
            if (resultIdList != NULL)
                okPressed = true;
        }
        catch(...)
        {
        }

        // Cleanup
        if(itemIdList)
            malloc->Free(itemIdList);
        if(resultIdList)
            malloc->Free(resultIdList);
        malloc->Release();

        // Update text
        if (okPressed)
        {
            // add quotes (to make an expression)
            m_RemoteHostNameExpr = CString(_T("\"")) + displayNameBuf + CString(_T("\""));
            m_RemoteHostNameExprEdit->PutText((LPCTSTR)m_RemoteHostNameExpr);
        }
    }
}

void CConfigureExecutionDlg::OnChangeTpsRelativePathEdit() 
{
    UpdateData(TRUE);
    SetAbsolutePath();
}

void CConfigureExecutionDlg::OnChangeParameterNameEdit() 
{
    CATLASParameter* parameter = (CATLASParameter*) m_ParametersListBox.GetItemDataPtr(m_SelectedParameterIdx);
    ((CEdit*)GetDlgItem(IDC_PARAMETER_NAME_EDIT))->GetWindowText(m_ParameterName);
    if (parameter->m_Name != m_ParameterName)
        MoveSelectedParameter(0); // reset parameter name in the listbox

    ShowHideParametersItems();  
}

void CConfigureExecutionDlg::OnSelchangeParametersList() 
{
    if (!GetParameterControls())
    {
        m_ParametersListBox.SetCurSel(m_SelectedParameterIdx);
        return;
    }
    m_SelectedParameterIdx = m_ParametersListBox.GetCurSel();
    SetParameterControls();
    ShowHideParametersItems();
}

/////////////////////////////////////////////////////////////////////////////
// CConfigureExecutionDlg operations

void CConfigureExecutionDlg::InitLabels()
{
    // Set the strings for all the labels in the dialog
    SetWindowText((LPCTSTR)GetResourceString(m_Engine, ATLAS_STEP_TYPE_STRING, _T("ATLAS_DLG_TITLE")));
    SetDlgItemText(IDC_TPS_LABEL, (LPCTSTR)GetResourceString(m_Engine, ATLAS_STEP_TYPE_STRING, _T("TPS_NAME_LABEL")));
    SetButtonImage(IDC_BROWSE, IDI_FILE_BROWSE_ICON);
    SetDlgItemText(IDC_REMOTE, (LPCTSTR)GetResourceString(m_Engine, ATLAS_STEP_TYPE_STRING, _T("REMOTE_CHK_TEXT")));
    SetDlgItemText(IDC_REMOTE_HOST_LABEL, (LPCTSTR)GetResourceString(m_Engine, ATLAS_STEP_TYPE_STRING, _T("REMOTE_HOST_LABEL")));

    SetDlgItemText(IDC_PARAMETERS_LABEL, (LPCTSTR)GetResourceString(m_Engine, ATLAS_STEP_TYPE_STRING, _T("PARAMETERS_LABEL")));
    SetButtonImage(IDC_ADD_PARAMETER_BUTTON, IDI_ADD_PARAMETER_ICON);
    SetButtonImage(IDC_DELETE_PARAMETER_BUTTON, IDI_REMOVE_PARAMETER_ICON);
    SetButtonImage(IDC_MOVEUP_PARAMETER_BUTTON, IDI_MOVEUP_PARAMETER_ICON);
    SetButtonImage(IDC_MOVEDOWN_PARAMETER_BUTTON, IDI_MOVEDOWN_PARAMETER_ICON);

    SetDlgItemText(IDC_PARAMETER_DETAILS_GROUP, (LPCTSTR)GetResourceString(m_Engine, ATLAS_STEP_TYPE_STRING, _T("PARAMETER_DETAILS_LABEL")));
    SetDlgItemText(IDC_PARAMETER_NAME_LABEL, (LPCTSTR)GetResourceString(m_Engine, ATLAS_STEP_TYPE_STRING, _T("PARAMETER_NAME_LABEL")));
    SetDlgItemText(IDC_PARAMETER_TYPE_LABEL, (LPCTSTR)GetResourceString(m_Engine, ATLAS_STEP_TYPE_STRING, _T("PARAMETER_TYPE_LABEL")));
    SetDlgItemText(IDC_PARAMETER_PASS_MODE_LABEL, (LPCTSTR)GetResourceString(m_Engine, ATLAS_STEP_TYPE_STRING, _T("PARAMETER_MODE_LABEL")));
    SetDlgItemText(IDC_GLOBAL_VARIABLE_CHECK, (LPCTSTR)GetResourceString(m_Engine, ATLAS_STEP_TYPE_STRING, _T("GLOBAL_VARIABLE_CHECK")));
    SetDlgItemText(IDC_PARAMETER_VALUE_EXPRESSION_LABEL, (LPCTSTR)GetResourceString(m_Engine, ATLAS_STEP_TYPE_STRING, _T("PARAMETER_VALUE_EXPRESSION_LABEL")));
    SetDlgItemText(IDOK, (LPCTSTR)GetResourceString(m_Engine, _T("COMMON_DLG"), _T("OK_BTN_LABEL")));
    SetDlgItemText(IDCANCEL, (LPCTSTR)GetResourceString(m_Engine, _T("COMMON_DLG"), _T("CANCEL_BTN_LABEL")));
    SizeCheckBoxToContent(m_ExecuteRemotelyButton);
    
    // Add tooltips to the buttons with icons
    m_ToolTipCtrl.AddTool(GetDlgItem(IDC_BROWSE), GetResourceString(m_Engine, ATLAS_STEP_TYPE_STRING, _T("BROWSE_BTN_TIP")));
    m_ToolTipCtrl.AddTool(GetDlgItem(IDC_ADD_PARAMETER_BUTTON), GetResourceString(m_Engine, ATLAS_STEP_TYPE_STRING, _T("ADD_PARAMETER_TIP")));
    m_ToolTipCtrl.AddTool(GetDlgItem(IDC_DELETE_PARAMETER_BUTTON), GetResourceString(m_Engine, ATLAS_STEP_TYPE_STRING, _T("DELETE_PARAMETER_TIP")));
    m_ToolTipCtrl.AddTool(GetDlgItem(IDC_MOVEUP_PARAMETER_BUTTON), GetResourceString(m_Engine, ATLAS_STEP_TYPE_STRING, _T("MOVEUP_PARAMETER_TIP")));
    m_ToolTipCtrl.AddTool(GetDlgItem(IDC_MOVEDOWN_PARAMETER_BUTTON), GetResourceString(m_Engine, ATLAS_STEP_TYPE_STRING, _T("MOVEDOWN_PARAMETER_TIP")));

    // Add type strings to data type combobox
    m_ParameterDataTypeCombo.AddString((LPCTSTR)GetResourceString(m_Engine, ATLAS_STEP_TYPE_STRING, _T("DATA_TYPE_NUMBER")));
    m_ParameterDataTypeCombo.AddString((LPCTSTR)GetResourceString(m_Engine, ATLAS_STEP_TYPE_STRING, _T("DATA_TYPE_STRING")));
    m_ParameterDataTypeCombo.AddString((LPCTSTR)GetResourceString(m_Engine, ATLAS_STEP_TYPE_STRING, _T("DATA_TYPE_BOOLEAN")));

    // Add pass mode strings to pass mode combobox
    m_ParameterPassModeCombo.AddString((LPCTSTR)GetResourceString(m_Engine, ATLAS_STEP_TYPE_STRING, _T("PASS_MODE_READ")));
    m_ParameterPassModeCombo.AddString((LPCTSTR)GetResourceString(m_Engine, ATLAS_STEP_TYPE_STRING, _T("PASS_MODE_WRITE")));
    m_ParameterPassModeCombo.AddString((LPCTSTR)GetResourceString(m_Engine, ATLAS_STEP_TYPE_STRING, _T("PASS_MODE_READ_WRITE")));
}

void CConfigureExecutionDlg::ShowHideRemoteItems() 
{
    GetDlgItem(IDC_REMOTE_HOST_EXPR_EDIT)->EnableWindow(m_ExecuteRemotely);
    GetDlgItem(IDC_REMOTE_HOST_LABEL)->EnableWindow(m_ExecuteRemotely);
}

void CConfigureExecutionDlg::ShowHideParametersItems() 
{
    UpdateData();
    bool parameterSelected = (m_SelectedParameterIdx >= 0);
    bool haveParameterName = m_ParameterName.GetLength() > 0;
    GetDlgItem(IDC_DELETE_PARAMETER_BUTTON)->EnableWindow(parameterSelected);
    GetDlgItem(IDC_MOVEUP_PARAMETER_BUTTON)->EnableWindow(m_SelectedParameterIdx > 0);
    GetDlgItem(IDC_MOVEDOWN_PARAMETER_BUTTON)->EnableWindow(parameterSelected && (m_SelectedParameterIdx < m_ParametersListBox.GetCount()-1));

    GetDlgItem(IDC_PARAMETER_NAME_EDIT)->EnableWindow(parameterSelected);
    GetDlgItem(IDC_GLOBAL_VARIABLE_CHECK)->EnableWindow(parameterSelected && haveParameterName);
    GetDlgItem(IDC_PARAMETER_VALUE_EXPRESSIONEDIT)->EnableWindow(parameterSelected && haveParameterName);

    m_ParameterPassModeCombo.EnableWindow(parameterSelected && haveParameterName);
    m_ParameterDataTypeCombo.EnableWindow(parameterSelected && haveParameterName);
}

bool CConfigureExecutionDlg::GetParameterControls() 
{
    if (m_SelectedParameterIdx < 0)
        return true;
    UpdateData();

    // Update parameter data
    CATLASParameter* parameter = (CATLASParameter*) m_ParametersListBox.GetItemDataPtr(m_SelectedParameterIdx);
    parameter->m_Name = m_ParameterName;
    parameter->m_ValueType = (ValueTypes) m_ParameterDataTypeCombo.GetCurSel();
    parameter->m_PassMode = (PassModes) m_ParameterPassModeCombo.GetCurSel();
    parameter->m_IsGlobalVariable = m_IsGlobalVariable;
    parameter->m_ValueExpression = (LPCTSTR)m_ParameterValueExprEdit->GetText();
    parameter->m_ValueExpression.TrimLeft();
    parameter->m_ValueExpression.TrimRight();
    m_ParametersListBox.SetItemDataPtr(m_SelectedParameterIdx, parameter);

    return true;
}

void CConfigureExecutionDlg::SetParameterControls() 
{
    if (m_SelectedParameterIdx < 0)
        return;

    // Get parameter info for current selection
    CATLASParameter* parameter = (CATLASParameter*) m_ParametersListBox.GetItemDataPtr(m_SelectedParameterIdx);

    // Set control values
    ((CEdit*)GetDlgItem(IDC_PARAMETER_NAME_EDIT))->SetWindowText(parameter->m_Name);
    ((CButton*)GetDlgItem(IDC_GLOBAL_VARIABLE_CHECK))->SetCheck(parameter->m_IsGlobalVariable);
    m_ParameterDataTypeCombo.SetCurSel(parameter->m_ValueType);
    m_ParameterPassModeCombo.SetCurSel(parameter->m_PassMode);
    m_ParameterValueExprEdit->PutText((LPCTSTR)parameter->m_ValueExpression);
}

// Sets the absolute path edit control from the path in the TPS edit control.
void CConfigureExecutionDlg::SetAbsolutePath()
{
    if (m_TPS.IsEmpty())
        m_absoluteTPS = GetResourceString(m_Engine, _T("COMMON_DLG"), _T("EMPTY_FILE_NAME_FULL_PATH_TEXT"));
    else
    {
        CComBSTR absolutePathStr;
		VARIANT_BOOL userCancelled = VARIANT_FALSE;
        if (m_Engine->FindFile((LPCTSTR)m_TPS, &absolutePathStr, &userCancelled, FindFile_PromptDisable, FindFile_AddDirToSrchList_No, VARIANT_FALSE, vtMissing))
            m_absoluteTPS = absolutePathStr;
        else 
            m_absoluteTPS = GetResourceString(m_Engine, _T("COMMON_DLG"), _T("FILE_NOT_FOUND_FULL_PATH_TEXT"));
    }

    UpdateData(FALSE);
}

// Loads and sets the icon on the button 
void CConfigureExecutionDlg::SetButtonImage (int buttonId, int iconResourceId)
{
    HICON icon = (HICON) LoadImage(AfxGetInstanceHandle(),
                                        MAKEINTRESOURCE(iconResourceId),
                                        IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR|LR_SHARED);
    ((CButton*)GetDlgItem(buttonId))->SetIcon(icon);
}

// Moves the selected parameter by the given offset
void CConfigureExecutionDlg::MoveSelectedParameter(int offset) 
{
    // Get old parameter and remove from its current position
    CATLASParameter* parameter = (CATLASParameter*) m_ParametersListBox.GetItemDataPtr(m_SelectedParameterIdx);
    m_ParametersListBox.DeleteString(m_SelectedParameterIdx);
        
    // Insert parameter into new position
    m_SelectedParameterIdx = m_ParametersListBox.InsertString(m_SelectedParameterIdx+offset, m_ParameterName);
    m_ParametersListBox.SetItemDataPtr(m_SelectedParameterIdx, parameter);
    m_ParametersListBox.SetCurSel(m_SelectedParameterIdx);
}

// Synatx checks the passed expression
BOOL CConfigureExecutionDlg::SyntaxCheckExpression(
    CDialog &dialog,
    const TS::IEnginePtr &engine,
    const CString &expression, 
    const CString &errorMsgTitle,
    const CString &errorMsgPrefix)
{
    long startErrPos;
    long endErrPos;
    CComBSTR errorDescription;
    VARIANT_BOOL syntaxIsOK;

    // Check syntax
    syntaxIsOK = engine->CheckExpression(m_SequenceContext->AsPropertyObject(), (LPCTSTR)expression, 
        TS::EvalOption_NoOptions, &errorDescription, &startErrPos, &endErrPos);

    // Show syntax error dialog if neeedd
    if (!syntaxIsOK)
    {
        USES_CONVERSION;
        dialog.MessageBox(OLE2CT(errorDescription.m_str), errorMsgTitle, MB_OK | MB_ICONERROR);
    }
    
    return syntaxIsOK;
}
