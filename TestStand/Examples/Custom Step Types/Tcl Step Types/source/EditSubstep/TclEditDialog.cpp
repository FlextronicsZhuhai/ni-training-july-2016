// TclEditDialog.cpp : implementation file
//

#include "stdafx.h"
#include "TclEditStep.h"
#include "TclEditDialog.h"
#include "tsvcutil.h"

// CTclEditDialog dialog

IMPLEMENT_DYNAMIC(CTclEditDialog, CDialog)

CTclEditDialog::CTclEditDialog(SequenceContextPtr context, CWnd* pParent /*=NULL*/)
	: CDialog(CTclEditDialog::IDD, pParent)
{
	this->m_context = context;
	this->m_parameterSelectedIndex = -1;
}

CTclEditDialog::~CTclEditDialog()
{
}

#ifndef nullChk
#define nullChk(fCall) if ((fCall) == 0) \
{error = -12; goto Error;} else
#endif

int TS_EscapeText (const char *srcTextPtr, char **destTextPtr)
{
	int         error = 0;
	const unsigned char  *s = (unsigned char *)srcTextPtr;
	char        *d;
	size_t      srcLen = 0;
	char        buffer[3];
	int         i;
	unsigned int currChar;

	*destTextPtr = NULL;
	srcLen = strlen (srcTextPtr);

	/***********************************************************************/
	/* since a single character can become as large as \xHH, we want the   */
	/* destination string to be 4 times as large as the original plus NULL */
	/***********************************************************************/
	nullChk (*destTextPtr = (char *) malloc (4*srcLen + 1));
	d = *destTextPtr;
	currChar = _mbsnextc(s);
	while (currChar != 0)
		{
		switch(currChar)
			{
			case '\r':
				*d++ = '\\';
				*d++ = 'r';
				break;
			case '\n':
				*d++ = '\\';
				*d++ = 'n';
				break;
			case '\t':
				*d++ = '\\';
				*d++ = 't';
				break;
			case '"':
				*d++ = '\\';
				*d++ = '"';
				break;
			case '\\':
				*d++ = '\\';
				*d++ = '\\';
				break;
			default:
				if (currChar <= 255 && iscntrl(currChar))
					{
					*d++ = '\\';
					*d++ = 'x';
					sprintf_s (buffer, "%02x", currChar);
					for (i=0; buffer[i]; i++)
						*d++ = buffer[i];
					}
				else
					{
					if(IsDBCSLeadByte(*(unsigned char *)s))
						{
						*d++ = *s;
						*d++ = *(s+1);
						}
					else
						*d++ = *s;
					}
				break;
			}
		s = _mbsinc(s);
		currChar = _mbsnextc((unsigned char *) s);
		}

	*d = '\0';

Error:
	return error;
}


void CTclEditDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_okButton);
	DDX_Control(pDX, IDCANCEL, m_cancelButton);
	DDX_Control(pDX, IDC_OPERATION_COMBOBOX, m_operationComboBox);
	DDX_Control(pDX, IDC_FILE_PATH_LABEL, m_filePathLabel);
	DDX_Control(pDX, IDC_FILE_BY_EXPR_CHECK, m_fileByExprCheckbox);
	DDX_Control(pDX, IDC_TCL_EXPRESSION_LABEL, m_tclExpressionLabel);
	DDX_Control(pDX, IDC_INTERP_OPT_LABEL, m_executionOptionLabel);
	DDX_Control(pDX, IDC_INTERP_OPT, m_executionOptionComboBox);
	DDX_Control(pDX, IDC_INTERP_REF_LABEL, m_interpreterReferenceLabel);
	DDX_Control(pDX, IDC_PARAMETER_LIST, m_parameterList);
	DDX_Control(pDX, IDC_ADD_BUTTON, m_addParamButton);
	DDX_Control(pDX, IDC_REMOVE_BUTTON, m_removeParamButton);
	DDX_Control(pDX, IDC_MOVE_UP, m_moveParamUpButton);
	DDX_Control(pDX, IDC_MOVE_DOWN, m_moveParamDownButton);
	DDX_Control(pDX, IDC_PARAMETER_GROUPBOX, m_parameterGroupBox);
	DDX_Control(pDX, IDC_PARAM_NAME, m_parameterName);
	DDX_Control(pDX, IDC_PARAM_DIR, m_paramDirectionComboBox);
	DDX_Control(pDX, IDC_PARAM_NAME_LABEL, m_parameterNameLabel);
	DDX_Control(pDX, IDC_PARAM_DIR_LABEL, m_parameterDirectionLabel);
	DDX_Control(pDX, IDC_PARAM_VALUE_LABEL, m_parameterValueLabel);
	DDX_Control(pDX, IDC_INPUT_LABEL, m_inputLabel);
	DDX_Control(pDX, IDC_OUTPUT_LABEL, m_outputLabel);
	DDX_Control(pDX, IDC_SHOW_CONSOLE, m_consoleDisplayLabel);
	DDX_Control(pDX, IDC_RESULT_EXPR_LABEL, m_resultExprLabel);
	DDX_Control(pDX, IDC_INTERP_OPTIONS_GROUPBOX, m_interpreterOptionsGroupBox);
	DDX_Control(pDX, IDC_CONSOLE_OPTIONS, m_consoleOptionsGroupBox);
	DDX_Control(pDX, IDC_FILEPATH, m_fullPath);
	DDX_Control(pDX, IDC_OPERATION_LABEL, m_operationTypeLabel);
}


BEGIN_MESSAGE_MAP(CTclEditDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CTclEditDialog::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_OPERATION_COMBOBOX, &CTclEditDialog::OnCbnSelchangeOperationCombobox)
	ON_BN_CLICKED(IDC_FILE_BY_EXPR_CHECK, &CTclEditDialog::OnBnClickedFileByExprCheck)
	ON_CBN_SELCHANGE(IDC_INTERP_OPT, &CTclEditDialog::OnCbnSelchangeInterpOpt)
	ON_BN_CLICKED(IDC_ADD_BUTTON, &CTclEditDialog::OnBnClickedAddButton)
	ON_BN_CLICKED(IDC_REMOVE_BUTTON, &CTclEditDialog::OnBnClickedRemoveButton)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_PARAMETER_LIST, &CTclEditDialog::OnLvnItemchangedParameterList)
	ON_CBN_SELCHANGE(IDC_PARAM_DIR, &CTclEditDialog::OnCbnSelchangeParamDir)
ON_EN_CHANGE(IDC_PARAM_NAME, &CTclEditDialog::OnEnChangeParamName)
ON_BN_CLICKED(IDC_MOVE_UP, &CTclEditDialog::OnBnClickedMoveUp)
ON_BN_CLICKED(IDC_MOVE_DOWN, &CTclEditDialog::OnBnClickedMoveDown)
END_MESSAGE_MAP()


// CTclEditDialog message handlers

void CTclEditDialog::LocalizeDialog(void)
{
	IEnginePtr engine = this->m_context->Engine;
	_bstr_t string;

	//set dialog title
	string = engine->GetResourceString(TCL_STEP_TYPE_SECTION, EDIT_DIALOG_STRING, vtMissing , &vtMissing );
	this->SetWindowText(string);
	
	//set ok button
	string = engine->GetResourceString(TCL_STEP_TYPE_SECTION, OK_BUTTON, vtMissing, &vtMissing);
	m_okButton.SetWindowText(string);

	//set cancel button
	string = engine->GetResourceString(TCL_STEP_TYPE_SECTION, CANCEL_BUTTON, vtMissing, &vtMissing);
	m_cancelButton.SetWindowText(string);

	//set operation label
	string = engine->GetResourceString(TCL_STEP_TYPE_SECTION, OPERATION_TYPE, vtMissing, &vtMissing);
	m_operationTypeLabel.SetWindowText(string);

	//set operation combobox
	string = engine->GetResourceString(TCL_STEP_TYPE_SECTION, OPERATION_TYPE, vtMissing, &vtMissing);
	m_operationComboBox.SetWindowText(string);
	string = engine->GetResourceString(TCL_STEP_TYPE_SECTION, OPERATION_EXEC_FILE, vtMissing, &vtMissing);
	m_operationComboBox.AddString(string);
	string = engine->GetResourceString(TCL_STEP_TYPE_SECTION, OPERATION_EVAL_LITERAL, vtMissing, &vtMissing);
	m_operationComboBox.AddString(string);
	string = engine->GetResourceString(TCL_STEP_TYPE_SECTION, OPERATION_EVAL_EXPR, vtMissing, &vtMissing);
	m_operationComboBox.AddString(string);
	string = engine->GetResourceString(TCL_STEP_TYPE_SECTION, OPERATION_RESET_INTERP, vtMissing, &vtMissing);
	m_operationComboBox.AddString(string);

	//set filepath label
	string = engine->GetResourceString(TCL_STEP_TYPE_SECTION, FILE_PATH_LABEL, vtMissing, &vtMissing);
	m_filePathLabel.SetWindowText(string);

	//set file by expression label
	string = engine->GetResourceString(TCL_STEP_TYPE_SECTION, FILE_BY_EXPR_LABEL, vtMissing, &vtMissing);
	m_fileByExprCheckbox.SetWindowText(string);	

	//set Tcl Expression label
	string = engine->GetResourceString(TCL_STEP_TYPE_SECTION, TCL_EXPRESSION_LABEL, vtMissing, &vtMissing);
	m_tclExpressionLabel.SetWindowText(string);	
	
	//set result expression
	string = engine->GetResourceString(TCL_STEP_TYPE_SECTION, RESULT_EXPRESSION, vtMissing, &vtMissing);
	m_resultExprLabel.SetWindowText(string);

	//set execution option label
	string = engine->GetResourceString(TCL_STEP_TYPE_SECTION, INTERPRETER_TO_USE, vtMissing, &vtMissing);
	m_executionOptionLabel.SetWindowText(string);

	//set execution option combobox
	string = engine->GetResourceString(TCL_STEP_TYPE_SECTION, INTERPRETER_STEP, vtMissing, &vtMissing);
	m_executionOptionComboBox.AddString(string);
	string = engine->GetResourceString(TCL_STEP_TYPE_SECTION, INTERPRETER_THREAD, vtMissing, &vtMissing);
	m_executionOptionComboBox.AddString(string);
	string = engine->GetResourceString(TCL_STEP_TYPE_SECTION, INTERPRETER_EXECUTION , vtMissing, &vtMissing);
	m_executionOptionComboBox.AddString(string);
	string = engine->GetResourceString(TCL_STEP_TYPE_SECTION, INTERPRETER_GLOBAL, vtMissing, &vtMissing);
	m_executionOptionComboBox.AddString(string);
	string = engine->GetResourceString(TCL_STEP_TYPE_SECTION, INTERPRETER_REFERENCE, vtMissing, &vtMissing);
	m_executionOptionComboBox.AddString(string);

	//set interpreter object reference label
	string = engine->GetResourceString(TCL_STEP_TYPE_SECTION, INTERPRETER_REFERENCE_LABEL, vtMissing, &vtMissing);
	m_interpreterReferenceLabel.SetWindowText(string);

	//set parameter groupbox label
	string = engine->GetResourceString(TCL_STEP_TYPE_SECTION, PARAMETERS_LABEL, vtMissing, &vtMissing);
	m_parameterGroupBox.SetWindowText(string);

	//set parameter list columns
	string = engine->GetResourceString(TCL_STEP_TYPE_SECTION, PARAMTABLE_NAME_LABEL, vtMissing, &vtMissing);
	m_parameterList.InsertColumn(PARAMETER_COLUMN_NAME_IDX, string, 0, 125, -1);
	string = engine->GetResourceString(TCL_STEP_TYPE_SECTION, PARAMTABLE_DIRECTION_LABEL, vtMissing, &vtMissing);
	m_parameterList.InsertColumn(PARAMETER_COLUMN_DIR_IDX, string, 0, 100, -1);
	string = engine->GetResourceString(TCL_STEP_TYPE_SECTION, PARAMTABLE_VALUE_LABEL, vtMissing, &vtMissing);
	m_parameterList.InsertColumn(PARAMETER_COLUMN_VAL_IDX, string, 0 , 225, -1);
	m_parameterList.SetColumnWidth(2,LVSCW_AUTOSIZE_USEHEADER);

	//set parameter defaults
	m_defaultParamName = engine->GetResourceString(TCL_STEP_TYPE_SECTION, PARAMETER_NAME_DEFAULT, vtMissing, &vtMissing);
	m_inputValString = engine->GetResourceString(TCL_STEP_TYPE_SECTION, PARAMETER_INPUT, vtMissing, &vtMissing);
	m_outputValString = engine->GetResourceString(TCL_STEP_TYPE_SECTION, PARAMETER_OUTPUT, vtMissing, &vtMissing);
	m_inputOutputString = engine->GetResourceString(TCL_STEP_TYPE_SECTION, PARAMETER_INPUTOUTPUT, vtMissing, &vtMissing);

	m_paramDirectionComboBox.AddString(m_inputValString);
	m_paramDirectionComboBox.AddString(m_outputValString);
	m_paramDirectionComboBox.AddString(m_inputOutputString);

	//set parameter labels
	string = engine->GetResourceString(TCL_STEP_TYPE_SECTION, PARAMETER_NAME_LABEL, vtMissing, &vtMissing);
	m_parameterNameLabel.SetWindowText(string);
	string = engine->GetResourceString(TCL_STEP_TYPE_SECTION, PARAMETER_DIRECTION_LABEL, vtMissing, &vtMissing);
	m_parameterDirectionLabel.SetWindowText(string);
	string = engine->GetResourceString(TCL_STEP_TYPE_SECTION, PARAMETER_VALUE_LABEL, vtMissing, &vtMissing);
	m_parameterValueLabel.SetWindowText(string);

	//show console label
	string = engine->GetResourceString(TCL_STEP_TYPE_SECTION, CONSOLE_DISPLAY_OPTION, vtMissing, &vtMissing);
	m_consoleDisplayLabel.SetWindowText(string);

	//populate the enum for the show console label.
	string = engine->GetResourceString(TCL_STEP_TYPE_SECTION, CONSOLE_DISPLAY_SHOW_INIT, vtMissing, &vtMissing);
	m_showConsoleExpr->ComboBoxItems->Insert(SHOW_WINDOW_INIT_IDX, SHOW_WINDOW_INIT_EXPR ,string, NULL);
	string = engine->GetResourceString(TCL_STEP_TYPE_SECTION, CONSOLE_DISPLAY_SHOW_ALWAYS, vtMissing, &vtMissing);	
	m_showConsoleExpr->ComboBoxItems->Insert(SHOW_WINDOW_ALWAYS_IDX, SHOW_WINDOW_ALWAYS_EXPR ,string, NULL);
	string = engine->GetResourceString(TCL_STEP_TYPE_SECTION, CONSOLE_DISPLAY_SHOW_NEVER, vtMissing, &vtMissing);
	m_showConsoleExpr->ComboBoxItems->Insert(SHOW_WINDOW_NEVER_IDX, SHOW_WINDOW_NEVER_EXPR ,string, NULL);
	string = engine->GetResourceString(TCL_STEP_TYPE_SECTION, CONSOLE_DISPLAY_HIDE, vtMissing, &vtMissing);
	m_showConsoleExpr->ComboBoxItems->Insert(HIDE_WINDOW_IDX, HIDE_WINDOW_EXPR ,string, NULL);

	//set console input/output labels
	string = engine->GetResourceString(TCL_STEP_TYPE_SECTION, CONSOLE_INPUT, vtMissing, &vtMissing);
	m_inputLabel.SetWindowText(string);
	string = engine->GetResourceString(TCL_STEP_TYPE_SECTION, CONSOLE_OUTPUT, vtMissing, &vtMissing);
	m_outputLabel.SetWindowText(string);

	//set console options group box
	string = engine->GetResourceString(TCL_STEP_TYPE_SECTION, CONSOLE_OPTIONS, vtMissing, &vtMissing);
	m_consoleOptionsGroupBox.SetWindowText(string);

	//set interpreter options group box
	string = engine->GetResourceString(TCL_STEP_TYPE_SECTION, INTERP_OPTIONS, vtMissing, &vtMissing);
	m_interpreterOptionsGroupBox.SetWindowText(string);

	//set tooltip string for the browse folder
	string = engine->GetResourceString(TCL_STEP_TYPE_SECTION, BROWSE_FOR_FILE, vtMissing, &vtMissing);
	m_filePath->Buttons->GetItem(1000, SpecifyButton_ByKind)->ToolTipText = string;
}


void CTclEditDialog::TransferValues(int transferToDialog)
{
	PropertyObjectPtr step = this->m_context->AsPropertyObject()->GetPropertyObject("Step", 0);

	//check direction of transfer
	if(transferToDialog)
	{
		double operation = step->GetValNumber(TCL_STEP_TYPE_OPERATION, 0);
		m_scriptResultExpr->Text = step->GetValString(TCL_SCRIPT_RESULT_EXPR, 0);
		VARIANT_BOOL usePathExpr = step->GetValBoolean(TCL_STEP_TYPE_USE_PATH_EXPR, 0);
		m_filePathExpr->Text = step->GetValString(TCL_STEP_TYPE_PATH_EXPR, 0);
		m_filePath->Text = step->GetValString(TCL_STEP_TYPE_PATH, 0);

		if(usePathExpr==VARIANT_TRUE)
			m_fileByExprCheckbox.SetCheck(BST_CHECKED);
		else
			m_fileByExprCheckbox.SetCheck(BST_UNCHECKED);

		if(operation == TCL_OPERATION_EVAL_EXPR_VAL)
		{
			m_operationComboBox.SetCurSel(TCL_OPERATION_EVAL_EXPR_IDX);
			m_tclExpr->Text = step->GetValString(TCL_STEP_TYPE_TCL_EXPR, 0);
		}
		else if (operation == TCL_OPERATION_EVAL_LITERAL)
		{
			m_operationComboBox.SetCurSel(TCL_OPERATION_EVAL_LITERAL_IDX);
			
			//we store literal scripts and expressions the same way, so we need to unescape the expression for literals
			m_scriptLiteralExpr->Text =m_context->AsPropertyObject()->EvaluateEx(step->GetValString(TCL_STEP_TYPE_TCL_EXPR, 0),0)->GetValString("", 0);
		}

		else if (operation == TCL_OPERATION_EVAL_FILE)
			m_operationComboBox.SetCurSel(TCL_OPERATION_EXEC_FILE_IDX);

		else if (operation == TCL_OPERATION_RESET)
			m_operationComboBox.SetCurSel(TCL_OPERATION_RESET_INTERP_IDX);

		PropertyObjectPtr params = step->GetPropertyObject(TCL_STEP_PARAMETERS, 0);
		int numParams = params->GetNumElements();
		for (int i = 0; i < numParams; i++)
		{
			PropertyObjectPtr param = params->GetPropertyObjectByOffset(i, 0);
			m_parameterList.InsertItem(i, param->GetValString(TCL_STEP_NAME, 0));
			
			double direction =  param->GetValNumber(TCL_STEP_DIRECTION, 0);
			if (direction == TCL_STEP_DIRECTION_INPUT)
				m_parameterList.SetItemText(i, PARAMETER_COLUMN_DIR_IDX, m_inputValString);
			else if (direction == TCL_STEP_DIRECTION_OUTPUT)
				m_parameterList.SetItemText(i, PARAMETER_COLUMN_DIR_IDX, m_outputValString);
			else if (direction == TCL_STEP_DIRECTION_INPUT_OUTPUT)
				m_parameterList.SetItemText(i, PARAMETER_COLUMN_DIR_IDX, m_inputOutputString);
			m_parameterList.SetItemText(i, PARAMETER_COLUMN_VAL_IDX, param->GetValString(TCL_STEP_VAL, 0));
		}
		if(numParams > 0)
				m_parameterList.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);

		//transfer console options
		m_showConsoleExpr->Text = step->GetValString(TCL_CONSOLE_DISPLAY_OPTION, 0);
		m_inputExpr->Text = step->GetValString(TCL_INPUT_EXPR, 0);
		m_outputExpr->Text = step->GetValString(TCL_OUTPUT_EXPR, 0);

		double execOption = step->GetValNumber(TCL_STEP_TYPE_EXECUTION_OPTION, 0);
		if (execOption == TCL_EXECUTION_OPTION_REF)
		{
			m_executionOptionComboBox.SetCurSel(TCL_EXEC_OPTION_REF_IDX);
			m_interpRefExpr->Text = step->GetValString(TCL_STEP_TYPE_INTERP_REF_EXPR, 0);
		}
		else if(execOption == TCL_EXECUTION_OPTION_STEP)
			m_executionOptionComboBox.SetCurSel(TCL_EXEC_OPTION_STEP_IDX);
		else if(execOption == TCL_EXECUTION_OPTION_THREAD)
			m_executionOptionComboBox.SetCurSel(TCL_EXEC_OPTION_THREAD_IDX);
		else if(execOption == TCL_EXECUTION_OPTION_EXECUTION)
			m_executionOptionComboBox.SetCurSel(TCL_EXEC_OPTION_EXECUTION_IDX);
		else if(execOption == TCL_EXECUTION_OPTION_GLOBAL)
			m_executionOptionComboBox.SetCurSel(TCL_EXEC_OPTION_GLOBAL_IDX);
	}
	else //transfer to TS
	{
		int operationType = m_operationComboBox.GetCurSel();

		if ( operationType == TCL_OPERATION_EXEC_FILE_IDX)
		{
			step->SetValNumber(TCL_STEP_TYPE_OPERATION, 0, TCL_OPERATION_EVAL_FILE);
			int fileByExpr = m_fileByExprCheckbox.GetCheck();
			step->SetValBoolean(TCL_STEP_TYPE_USE_PATH_EXPR, 0, (fileByExpr==BST_CHECKED)?VARIANT_TRUE:VARIANT_FALSE);
			if (fileByExpr==BST_CHECKED)
				step->SetValString(TCL_STEP_TYPE_PATH_EXPR, 0, m_filePathExpr->Text);
			else
				step->SetValString(TCL_STEP_TYPE_PATH, 0, m_filePath->Text);
		}
		else if (operationType == TCL_OPERATION_EVAL_EXPR_IDX)
		{
			step->SetValNumber(TCL_STEP_TYPE_OPERATION, 0, TCL_OPERATION_EVAL_EXPR_VAL);
			step->SetValString(TCL_STEP_TYPE_TCL_EXPR, 0, m_tclExpr->Text);
			step->SetValString(TCL_SCRIPT_RESULT_EXPR, 0, m_scriptResultExpr->Text);
		}
		else if (operationType == TCL_OPERATION_EVAL_LITERAL_IDX)
		{
			step->SetValNumber(TCL_STEP_TYPE_OPERATION, 0, TCL_OPERATION_EVAL_LITERAL);
			char * escapedText = NULL;
			//need to escape literal strings to turn into an expression.
			if(TS_EscapeText(m_scriptLiteralExpr->Text, &escapedText)==0)
				step->SetValString(TCL_STEP_TYPE_TCL_EXPR, 0, _bstr_t("\"" +  _bstr_t(escapedText) + "\""));
			free(escapedText);


		}
		if (operationType == TCL_OPERATION_RESET_INTERP_IDX)
			step->SetValNumber(TCL_STEP_TYPE_OPERATION, 0, TCL_OPERATION_RESET);

		else
		{
			PropertyObjectPtr params = step->GetPropertyObject(TCL_STEP_PARAMETERS, 0);
			params->SetNumElements(m_parameterList.GetItemCount(), 0);

			for(int i = 0; i < m_parameterList.GetItemCount(); i++)
			{
				PropertyObjectPtr param = params->GetPropertyObjectByOffset(i, 0);
				param->SetValString(TCL_STEP_NAME, 0, m_parameterList.GetItemText(i, PARAMETER_COLUMN_NAME_IDX).AllocSysString());
				_bstr_t paramDirection = m_parameterList.GetItemText(i, PARAMETER_COLUMN_DIR_IDX);
				if (paramDirection == m_inputValString)
					param->SetValNumber(TCL_STEP_DIRECTION , 0, TCL_STEP_DIRECTION_INPUT);
				else if (paramDirection == m_outputValString)
					param->SetValNumber(TCL_STEP_DIRECTION, 0, TCL_STEP_DIRECTION_OUTPUT);
				else if (paramDirection == m_inputOutputString)
					param->SetValNumber(TCL_STEP_DIRECTION, 0, TCL_STEP_DIRECTION_INPUT_OUTPUT);
				param->SetValString(TCL_STEP_VAL,0 ,m_parameterList.GetItemText(i, PARAMETER_COLUMN_VAL_IDX).AllocSysString());
			}

			step->SetValString(TCL_CONSOLE_DISPLAY_OPTION, 0, m_showConsoleExpr->GetText());
			step->SetValString(TCL_INPUT_EXPR, 0, m_inputExpr->GetText());
			step->SetValString(TCL_OUTPUT_EXPR, 0, m_outputExpr->GetText());
		}
		int executionOption = m_executionOptionComboBox.GetCurSel();

		if (executionOption==TCL_EXEC_OPTION_REF_IDX)
		{
			step->SetValNumber(TCL_STEP_TYPE_EXECUTION_OPTION, 0, TCL_EXECUTION_OPTION_REF);
			step->SetValString(TCL_STEP_TYPE_INTERP_REF_EXPR, 0, m_interpRefExpr->GetText());
		}
		else if(executionOption==TCL_EXEC_OPTION_STEP_IDX)
			step->SetValNumber(TCL_STEP_TYPE_EXECUTION_OPTION, 0, TCL_EXECUTION_OPTION_STEP );	
		else if(executionOption==TCL_EXEC_OPTION_THREAD_IDX)
			step->SetValNumber(TCL_STEP_TYPE_EXECUTION_OPTION, 0, TCL_EXECUTION_OPTION_THREAD );	
		else if(executionOption==TCL_EXEC_OPTION_EXECUTION_IDX)
			step->SetValNumber(TCL_STEP_TYPE_EXECUTION_OPTION, 0, TCL_EXECUTION_OPTION_EXECUTION );	
		else if(executionOption==TCL_EXEC_OPTION_GLOBAL_IDX)
			step->SetValNumber(TCL_STEP_TYPE_EXECUTION_OPTION, 0, TCL_EXECUTION_OPTION_GLOBAL );	
	

		this->m_context->SequenceFile->IncChangeCount();
	}
}

void CTclEditDialog::UpdateVisibility(void)
{

	if (m_operationComboBox.GetCurSel() == TCL_OPERATION_EXEC_FILE_IDX)
	{
		m_filePathLabel.ShowWindow(SW_NORMAL);
		m_fileByExprCheckbox.ShowWindow(SW_NORMAL);
		m_tclExpressionLabel.ShowWindow(SW_HIDE);
		m_tclExprWnd->ShowWindow(SW_HIDE);
		m_scriptResultExprWnd->ShowWindow(SW_HIDE);
		m_resultExprLabel.ShowWindow(SW_HIDE);
		m_scriptLiteralExprWnd->ShowWindow(SW_HIDE);

		if (m_fileByExprCheckbox.GetCheck()==BST_CHECKED)
		{
			m_fullPath.ShowWindow(SW_HIDE);
			m_filePathExprWnd->ShowWindow(SW_NORMAL);	
			m_filePathWnd->ShowWindow(SW_HIDE);
		}
		else
		{
			m_fullPath.ShowWindow(SW_NORMAL);
			m_filePathExprWnd->ShowWindow(SW_HIDE);
			m_filePathWnd->ShowWindow(SW_NORMAL);
		}
	}
	else if (m_operationComboBox.GetCurSel() == TCL_OPERATION_EVAL_EXPR_IDX || m_operationComboBox.GetCurSel() == TCL_OPERATION_EVAL_LITERAL_IDX )
	{
		m_fullPath.ShowWindow(SW_HIDE);
		m_filePathLabel.ShowWindow(SW_HIDE);
		m_filePathExprWnd->ShowWindow(SW_HIDE);
		m_filePathWnd->ShowWindow(SW_HIDE);
		m_fileByExprCheckbox.ShowWindow(SW_HIDE);
		m_tclExpressionLabel.ShowWindow(SW_NORMAL);
		m_scriptResultExprWnd->ShowWindow(SW_NORMAL);
		m_resultExprLabel.ShowWindow(SW_SHOW);
		if (m_operationComboBox.GetCurSel() == TCL_OPERATION_EVAL_EXPR_IDX)
		{
			m_scriptLiteralExprWnd->ShowWindow(SW_HIDE);
			m_tclExprWnd->ShowWindow(SW_NORMAL);
		}
		else
		{
			m_scriptLiteralExprWnd->ShowWindow(SW_NORMAL);
			m_tclExprWnd->ShowWindow(SW_HIDE);
		}
	}
	else
	{
		m_fullPath.ShowWindow(SW_HIDE);
		m_filePathLabel.ShowWindow(SW_HIDE);
		m_filePathExprWnd->ShowWindow(SW_HIDE);
		m_filePathWnd->ShowWindow(SW_HIDE);
		m_fileByExprCheckbox.ShowWindow(SW_HIDE);
		m_tclExpressionLabel.ShowWindow(SW_HIDE);
		m_tclExprWnd->ShowWindow(SW_HIDE);
		m_scriptResultExprWnd->ShowWindow(SW_HIDE);
		m_resultExprLabel.ShowWindow(SW_HIDE);
		m_scriptLiteralExprWnd->ShowWindow(SW_HIDE);
	}
	if (m_operationComboBox.GetCurSel() == TCL_OPERATION_RESET_INTERP_IDX)
	{
		m_parameterGroupBox.EnableWindow(FALSE);
		m_parameterNameLabel.EnableWindow(FALSE);
		m_parameterName.EnableWindow(FALSE);
		m_parameterDirectionLabel.EnableWindow(FALSE);
		m_paramDirectionComboBox.EnableWindow(FALSE);
		m_parameterValueLabel.EnableWindow(FALSE);
		m_paramValueWnd->EnableWindow(FALSE);
		m_parameterList.EnableWindow(FALSE);
		m_addParamButton.EnableWindow(FALSE);
		m_removeParamButton.EnableWindow(FALSE);
		m_moveParamDownButton.EnableWindow(FALSE);
		m_moveParamUpButton.EnableWindow(FALSE);
		m_consoleDisplayLabel.EnableWindow(FALSE);
		m_showConsoleExprWnd->EnableWindow(FALSE);
		m_inputLabel.EnableWindow(FALSE);
		m_outputLabel.EnableWindow(FALSE);
		m_inputExprWnd->EnableWindow(FALSE);
		m_outputExprWnd->EnableWindow(FALSE);
		m_consoleOptionsGroupBox.EnableWindow(FALSE);
	}
	else
	{
		m_parameterGroupBox.EnableWindow(TRUE);
		m_parameterNameLabel.EnableWindow(TRUE);
		m_parameterDirectionLabel.EnableWindow(TRUE);
		m_parameterValueLabel.EnableWindow(TRUE);
		m_parameterList.EnableWindow(TRUE);
		m_addParamButton.EnableWindow(TRUE);
		m_removeParamButton.EnableWindow(TRUE);
		m_moveParamDownButton.EnableWindow(TRUE);
		m_moveParamUpButton.EnableWindow(TRUE);
		m_consoleDisplayLabel.EnableWindow(TRUE);
		m_showConsoleExprWnd->EnableWindow(TRUE);
		m_inputLabel.EnableWindow(TRUE);
		m_outputLabel.EnableWindow(TRUE);
		m_inputExprWnd->EnableWindow(TRUE);
		m_outputExprWnd->EnableWindow(TRUE);
		m_consoleOptionsGroupBox.EnableWindow(TRUE);
		BOOL enableParams = (this->m_parameterSelectedIndex != -1);
		m_parameterName.EnableWindow(enableParams);
		m_paramDirectionComboBox.EnableWindow(enableParams);
		m_paramValueWnd->EnableWindow(enableParams);
		UpdateParamButtonVisibility(m_parameterSelectedIndex);
	}
	if (m_executionOptionComboBox.GetCurSel() == TCL_EXEC_OPTION_REF_IDX)
	{
		m_interpreterReferenceLabel.ShowWindow(SW_SHOW);
		m_interpRefExprWnd->ShowWindow(SW_SHOW);
	}
	else
	{
		m_interpreterReferenceLabel.ShowWindow(SW_HIDE);
		m_interpRefExprWnd->ShowWindow(SW_HIDE);
	}

}

BOOL CTclEditDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_filePathExprWnd = GetDlgItem(IDC_FILE_EXPR);
	m_interpRefExprWnd = GetDlgItem(IDC_INTERP_REF_EXPR);
	m_filePathWnd = GetDlgItem(IDC_FILE_PATH);
	m_tclExprWnd = GetDlgItem(IDC_TCL_EXPR);
	m_paramValueWnd = GetDlgItem(IDC_PARAM_VALUE_EXPR);
	m_showConsoleExprWnd = GetDlgItem(IDC_SHOW_CONSOLE_EXPR);
	m_inputExprWnd = GetDlgItem(IDC_INPUT_EXPR);
	m_outputExprWnd = GetDlgItem(IDC_OUTPUT_EXPR);
	m_scriptResultExprWnd = GetDlgItem(IDC_RESULT_EXPR);
	m_scriptLiteralExprWnd = GetDlgItem(IDC_SCRIPT_LITERAL);

	m_filePathExprWnd->GetControlUnknown()->QueryInterface(&m_filePathExpr);
	m_interpRefExprWnd->GetControlUnknown()->QueryInterface(&m_interpRefExpr);
	m_filePathWnd->GetControlUnknown()->QueryInterface(&m_filePath);
	m_tclExprWnd->GetControlUnknown()->QueryInterface(&m_tclExpr);
	m_paramValueWnd->GetControlUnknown()->QueryInterface(&m_paramValue);
	m_showConsoleExprWnd->GetControlUnknown()->QueryInterface(&m_showConsoleExpr);
	m_inputExprWnd->GetControlUnknown()->QueryInterface(&m_inputExpr);
	m_outputExprWnd->GetControlUnknown()->QueryInterface(&m_outputExpr);
	m_scriptResultExprWnd->GetControlUnknown()->QueryInterface(&m_scriptResultExpr);
	m_scriptLiteralExprWnd->GetControlUnknown()->QueryInterface(&m_scriptLiteralExpr);
	m_interpRefExpr->PutRefContext(m_context->AsPropertyObject());
	m_filePathExpr->PutRefContext(m_context->AsPropertyObject());
	m_tclExpr->PutRefContext(m_context->AsPropertyObject());
	m_paramValue->PutRefContext(m_context->AsPropertyObject());
	m_showConsoleExpr->PutRefContext(m_context->AsPropertyObject());
	m_inputExpr->PutRefContext(m_context->AsPropertyObject());
	m_outputExpr->PutRefContext(m_context->AsPropertyObject());
	m_scriptResultExpr->PutRefContext(m_context->AsPropertyObject());

	m_moveParamDownButton.SetIcon(AfxGetApp()->LoadIcon(IDI_ARROWDOWN));	
	m_moveParamUpButton.SetIcon(AfxGetApp()->LoadIcon(IDI_ARROWUP));	
	m_addParamButton.SetIcon(AfxGetApp()->LoadIcon(IDI_INSERT));
	m_removeParamButton.SetIcon(AfxGetApp()->LoadIcon(IDI_DELETE));

	m_parameterList.SetExtendedStyle(m_parameterList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	ChangeFilePath();

	LocalizeDialog();
	TransferValues(1);
	UpdateVisibility();

	return TRUE;
}

void CTclEditDialog::OnBnClickedOk()
{
	if(ValidateDialog())
	{
		TransferValues(0);
		OnOK();
	}
}

void CTclEditDialog::OnCbnSelchangeOperationCombobox()
{
	UpdateVisibility();
}

void CTclEditDialog::OnBnClickedFileByExprCheck()
{
	UpdateVisibility();
}

BEGIN_EVENTSINK_MAP(CTclEditDialog, CDialog)
	ON_EVENT(CTclEditDialog, IDC_FILE_PATH, 5, CTclEditDialog::ButtonClickFilePath, VTS_DISPATCH)
	ON_EVENT(CTclEditDialog, IDC_PARAM_VALUE_EXPR, 1, CTclEditDialog::ChangeParamValueExpr, VTS_NONE)
	ON_EVENT(CTclEditDialog, IDC_FILE_PATH, 1, CTclEditDialog::ChangeFilePath, VTS_NONE)
END_EVENTSINK_MAP()

void CTclEditDialog::ButtonClickFilePath(LPDISPATCH btn)
{
	ExpressionEditButtonPtr button;
	btn->QueryInterface(&button);
	if(button->GetKind()==1000)
	{
		//set dialog title
		_bstr_t fileFilter = m_context->Engine->GetResourceString(TCL_STEP_TYPE_SECTION, FILE_FILTER, vtMissing , &vtMissing );
		std::vector<_bstr_t> pathArr;
		TSUTIL::SafeArray<BSTR, VT_BSTR> selectedPathsArray;
		TSUTIL::SafeArray<BSTR, VT_BSTR>  absolutePathsArray;
		VARIANT seqFile;

		seqFile.pdispVal = m_context->SequenceFile.GetInterfacePtr();
		seqFile.vt = VT_DISPATCH;

		if(m_context->Engine->DisplayFileDialog("", "", m_filePath->GetText(), &selectedPathsArray, &absolutePathsArray, TS::OpenFile_InitialUnsetUseAbsPathCheck, ".tcl", WinFileDlg_HIDEREADONLY | WinFileDlg_FILEMUSTEXIST,
			fileFilter, seqFile, &vtMissing, &vtMissing))
		{
			 selectedPathsArray.GetVector(pathArr);
			 m_filePath->Text = pathArr[0];
		}
	}
}

void CTclEditDialog::OnCbnSelchangeInterpOpt()
{
	UpdateVisibility();
}

void CTclEditDialog::OnBnClickedAddButton()
{
	int index = m_parameterList.GetItemCount();

	//get default param values
	m_parameterList.InsertItem(index, m_defaultParamName);
	m_parameterList.SetItemText(index, PARAMETER_COLUMN_DIR_IDX, m_inputValString);
	m_parameterList.SetItemText(index, PARAMETER_COLUMN_VAL_IDX, L"\"\"");
	m_parameterList.SetItemState(index, LVIS_SELECTED, LVIS_SELECTED);
}

void CTclEditDialog::OnBnClickedRemoveButton()
{
	if(m_parameterSelectedIndex != -1)
	{
		int oldIndex = m_parameterSelectedIndex;
		m_parameterList.DeleteItem(m_parameterSelectedIndex);
		if(m_parameterList.GetItemCount() >= oldIndex+1)
			m_parameterList.SetItemState(oldIndex, LVIS_SELECTED, LVIS_SELECTED);
		else if(m_parameterList.GetItemCount() > 0)
			m_parameterList.SetItemState(oldIndex-1, LVIS_SELECTED, LVIS_SELECTED);
		else
		{
			UpdateVisibility();
		}
	}
}

void CTclEditDialog::OnLvnItemchangedParameterList(NMHDR *pNMHDR, LRESULT *pResult)
{

	POSITION pos = m_parameterList.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int index = m_parameterList.GetNextSelectedItem(pos);
		if (index != m_parameterSelectedIndex)
		{
			m_parameterSelectedIndex = index;
			PopulateParameters();
			UpdateVisibility();
		}
		UpdateParamButtonVisibility(index);
	}
	else
	{
		m_parameterSelectedIndex = -1;
		UpdateParamButtonVisibility(-1);
	}
}

void CTclEditDialog::UpdateParamButtonVisibility(int index)
{
	if(index == -1)
	{
		m_removeParamButton.EnableWindow(FALSE);
		m_moveParamDownButton.EnableWindow(FALSE);
		m_moveParamUpButton.EnableWindow(FALSE);
	}
	else
	{
		m_removeParamButton.EnableWindow(TRUE);
		if (index == 0)
			m_moveParamUpButton.EnableWindow(FALSE);
		else
			m_moveParamUpButton.EnableWindow(TRUE);
		if (m_parameterList.GetItemCount() > 1 && index < m_parameterList.GetItemCount()-1)
			m_moveParamDownButton.EnableWindow(TRUE);	
		else
			m_moveParamDownButton.EnableWindow(FALSE);
	}
}

void CTclEditDialog::PopulateParameters()
{
	m_parameterName.SetWindowText(m_parameterList.GetItemText(m_parameterSelectedIndex, 0));
	_bstr_t direction = m_parameterList.GetItemText(m_parameterSelectedIndex, 1);
	if(direction == m_inputValString)
		m_paramDirectionComboBox.SetCurSel(PARAMETER_INPUT_IDX);
	else if(direction == m_outputValString)
		m_paramDirectionComboBox.SetCurSel(PARAMETER_OUTPUT_IDX);
	else if(direction == m_inputOutputString)
		m_paramDirectionComboBox.SetCurSel(PARAMETER_INPUTOUTPUT_IDX);
	m_paramValue->Text = m_parameterList.GetItemText(m_parameterSelectedIndex, 2).AllocSysString();

}

void CTclEditDialog::OnCbnSelchangeParamDir()
{
	int index = m_paramDirectionComboBox.GetCurSel();	
	if (index == PARAMETER_INPUT_IDX)
		m_parameterList.SetItemText(m_parameterSelectedIndex, PARAMETER_COLUMN_DIR_IDX, m_inputValString);
	else if (index == PARAMETER_OUTPUT_IDX)
		m_parameterList.SetItemText(m_parameterSelectedIndex, PARAMETER_COLUMN_DIR_IDX, m_outputValString);
	else if (index == PARAMETER_INPUTOUTPUT_IDX)
		m_parameterList.SetItemText(m_parameterSelectedIndex, PARAMETER_COLUMN_DIR_IDX, m_inputOutputString);
	UpdateVisibility();

}

void CTclEditDialog::OnEnChangeParamName()
{
	CString windowText;
	m_parameterName.GetWindowText(windowText);
	m_parameterList.SetItemText(m_parameterSelectedIndex, PARAMETER_COLUMN_NAME_IDX, windowText);
}

void CTclEditDialog::ChangeParamValueExpr()
{
	m_parameterList.SetItemText(m_parameterSelectedIndex, PARAMETER_COLUMN_VAL_IDX, m_paramValue->GetText());
}

void CTclEditDialog::OnBnClickedMoveUp()
{
	if (m_parameterSelectedIndex >= 1)
	{
		CString paramName, paramDir, paramVal;
		int index = m_parameterSelectedIndex;
		paramName = m_parameterList.GetItemText(index, PARAMETER_COLUMN_NAME_IDX);
		paramDir = m_parameterList.GetItemText(index, PARAMETER_COLUMN_DIR_IDX);
		paramVal = m_parameterList.GetItemText(index, PARAMETER_COLUMN_VAL_IDX);
		m_parameterList.DeleteItem(index);
		
		m_parameterList.InsertItem(index-1, paramName);
		m_parameterList.SetItemText(index-1, PARAMETER_COLUMN_DIR_IDX, paramDir);
		m_parameterList.SetItemText(index-1, PARAMETER_COLUMN_VAL_IDX, paramVal);

		m_parameterList.SetItemState(index-1, LVIS_SELECTED, LVIS_SELECTED);
	}
}

void CTclEditDialog::OnBnClickedMoveDown()
{
	if (m_parameterSelectedIndex < m_parameterList.GetItemCount()-1)
	{
		CString paramName, paramDir, paramVal;
		int index = m_parameterSelectedIndex;
		paramName = m_parameterList.GetItemText(index, PARAMETER_COLUMN_NAME_IDX);
		paramDir = m_parameterList.GetItemText(index, PARAMETER_COLUMN_DIR_IDX);
		paramVal = m_parameterList.GetItemText(index, PARAMETER_COLUMN_VAL_IDX);
		m_parameterList.DeleteItem(index);

		m_parameterList.InsertItem(index+1, paramName);
		m_parameterList.SetItemText(index+1, PARAMETER_COLUMN_DIR_IDX, paramDir);
		m_parameterList.SetItemText(index+1, PARAMETER_COLUMN_VAL_IDX, paramVal);

		m_parameterList.SetItemState(index+1, LVIS_SELECTED, LVIS_SELECTED);

	}
}


BOOL CTclEditDialog::CheckExpressionAndDisplayError(IEnginePtr engine, IExpressionEditPtr expressionEdit, _bstr_t errorString)
{
	TSUTIL::param_bstr_t errorDescription;
	long startPos = 0, endPos = 0;
	TSError errorCode = expressionEdit->CheckExpression(&errorDescription,  &startPos, &endPos);
	long result = IDNO;
	
	
	if (errorCode != TS_Err_NoError)
	{
		_bstr_t errorTitle = engine->GetResourceString(TCL_STEP_TYPE_SECTION, ERROR_IN_EXPRESSION_TITLE, vtMissing, &vtMissing);
		_bstr_t errorGoto = engine->GetResourceString(TCL_STEP_TYPE_SECTION, GOTO_ERROR_IN_EXPRESSION , vtMissing, &vtMissing);
		result = engine->DisplayMessageBox(errorTitle, errorString + _bstr_t(errorDescription) + errorGoto, MsgBox_Error, TS::CommonDlgOption_ModalToAppMainWind, MB_YESNO);
		
		if (result == IDYES)
		{
			expressionEdit->SelStart = startPos;
			expressionEdit->SelLength = endPos - startPos;
			GotoDlgCtrl(CWnd::FromHandle((HWND)expressionEdit->GethWnd()));
		}
	}
		
	return (result!= IDYES);


}

BOOL CTclEditDialog::CheckParameterError(_bstr_t parameterVal, int index)
{
	TSUTIL::param_bstr_t errorMsg;
	long startIndex, endIndex;
	IEnginePtr engine = m_context->Engine;
	ExpressionPtr expr = engine->NewExpression();
	expr->Text = parameterVal;
	TSError errorCode = expr->ValidateEvaluationType(engine->NewEvaluationTypes(PropValTypeFlag_String | PropValTypeFlag_Number | PropValTypeFlag_Boolean),
		NULL, m_context->AsPropertyObject(), 0, &errorMsg, &startIndex, &endIndex);
	
	if (errorCode != TS_Err_NoError)
	{
		_bstr_t errorString = engine->GetResourceString(TCL_STEP_TYPE_SECTION, PARAMETER_EXPR_ERROR, vtMissing, &vtMissing);
		_bstr_t errorTitle = engine->GetResourceString(TCL_STEP_TYPE_SECTION, ERROR_IN_EXPRESSION_TITLE, vtMissing, &vtMissing);
		_bstr_t errorGoto = engine->GetResourceString(TCL_STEP_TYPE_SECTION, GOTO_ERROR_IN_EXPRESSION , vtMissing, &vtMissing);
		long result = engine->DisplayMessageBox(errorTitle, errorString + _bstr_t(errorMsg) + errorGoto, MsgBox_Error, TS::CommonDlgOption_ModalToAppMainWind, MB_YESNO);
		
		if (result == IDYES)
		{
			//select the proper item
			m_parameterList.SetItemState(index, LVIS_SELECTED, LVIS_SELECTED);
			m_paramValue->SelStart = startIndex;
			m_paramValue->SelLength = endIndex - startIndex;
			GotoDlgCtrl(CWnd::FromHandle((HWND)m_paramValue->GethWnd()));
			return false;
		}
	}

	return true;
}

BOOL CTclEditDialog::ValidateDialog()
{
	_bstr_t errorString;
	//check if file path expr
	if (m_operationComboBox.GetCurSel()== TCL_OPERATION_EXEC_FILE_IDX && m_fileByExprCheckbox.GetCheck()==BST_CHECKED)
	{
		errorString = m_context->Engine->GetResourceString(TCL_STEP_TYPE_SECTION, FILE_PATH_EXPR_ERROR , vtMissing, &vtMissing);
		if (!CheckExpressionAndDisplayError(m_context->Engine, m_filePathExpr, errorString))
			return false;
	}

	else if (m_operationComboBox.GetCurSel()== TCL_OPERATION_EVAL_EXPR_IDX)
	{
		errorString = m_context->Engine->GetResourceString(TCL_STEP_TYPE_SECTION, TCL_SCRIPT_EXPR_ERROR , vtMissing, &vtMissing);
		if (!CheckExpressionAndDisplayError(m_context->Engine, m_tclExpr, errorString))
			return false;
		errorString = m_context->Engine->GetResourceString(TCL_STEP_TYPE_SECTION, RESULT_EXPR_ERROR, vtMissing, &vtMissing);
		if (!CheckExpressionAndDisplayError(m_context->Engine, m_scriptResultExpr, errorString))
			return false;
	}

	if (m_operationComboBox.GetCurSel() != TCL_OPERATION_RESET_INTERP_IDX)
	{
		//check each parameter
		for(int i = 0; i < m_parameterList.GetItemCount(); i++)
		{
			_bstr_t expr = m_parameterList.GetItemText(i, PARAMETER_COLUMN_VAL_IDX);
			if (!CheckParameterError(expr, i))
				return false;
		}

		//check console display option
		errorString = m_context->Engine->GetResourceString(TCL_STEP_TYPE_SECTION, CONSOLE_DISPLAY_EXPR_ERROR, vtMissing, &vtMissing);
		if (!CheckExpressionAndDisplayError(m_context->Engine, m_showConsoleExpr, errorString))
			return false;
		//check console input
		errorString = m_context->Engine->GetResourceString(TCL_STEP_TYPE_SECTION, CONSOLE_INPUT_EXPR_ERROR, vtMissing, &vtMissing);
		if (!CheckExpressionAndDisplayError(m_context->Engine, m_inputExpr, errorString))
			return false;
		//check console output
		errorString = m_context->Engine->GetResourceString(TCL_STEP_TYPE_SECTION, CONSOLE_OUTPUT_EXPR_ERROR, vtMissing, &vtMissing);
		if (!CheckExpressionAndDisplayError(m_context->Engine, m_outputExpr, errorString))
			return false;
	}
	
	if (this->m_executionOptionComboBox.GetCurSel()==TCL_EXEC_OPTION_REF_IDX)
	{
		errorString = m_context->Engine->GetResourceString(TCL_STEP_TYPE_SECTION, INTERPRETER_REFERENCE_ERROR, vtMissing, &vtMissing);
		if (!CheckExpressionAndDisplayError(m_context->Engine, m_interpRefExpr, errorString))
			return false;
	}

	return true;

}


void CTclEditDialog::ChangeFilePath()
{

	TSUTIL::param_bstr_t absPath;
	VARIANT_BOOL userCancelled;
	
	if(m_filePath->Text==_bstr_t(""))
		m_fullPath.SetWindowText(m_context->Engine->GetResourceString(TCL_STEP_TYPE_SECTION, "NO_FILE_SPECIFIED", vtMissing, &vtMissing));

	else if(m_context->Engine->FindFile(m_filePath->Text, &absPath, &userCancelled, FindFile_PromptDisable, FindFile_AddDirToSrchList_No, VARIANT_FALSE, m_context->GetSequenceFile().GetInterfacePtr()) == VARIANT_TRUE)
		m_fullPath.SetWindowText(absPath);
	else
		m_fullPath.SetWindowText(m_context->Engine->GetResourceString(TCL_STEP_TYPE_SECTION, "FILE_NOT FOUND", vtMissing, &vtMissing));

}
