#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "..\Shared\TclStepProperties.h"


#define EDIT_DIALOG_STRING			"EDIT_DIALOG_STRING"
#define OPERATION_TYPE				"OPERATION_TYPE_STRING"
#define OPERATION_EXEC_FILE			"OPERATION_EXEC_FILE"
#define OPERATION_EVAL_EXPR			"OPERATION_EVAL_EXPR"
#define OPERATION_RESET_INTERP		"OPERATION_RESET_INTERP"
#define OPERATION_EVAL_LITERAL		"OPERATION_EVAL_LITERAL"
#define OK_BUTTON					"OK_BUTTON"
#define CANCEL_BUTTON				"CANCEL_BUTTON"
#define FILE_PATH_LABEL				"FILE_PATH_LABEL"
#define FILE_BY_EXPR_LABEL			"FILE_BY_EXPR_LABEL"
#define FILE_FILTER					"FILE_FILTER"
#define TCL_EXPRESSION_LABEL		"TCL_EXPRESSION_LABEL"
#define INTERPRETER_TO_USE			"INTERPRETER_TO_USE"
#define INTERPRETER_THREAD			"INTERPRETER_THREAD"
#define INTERPRETER_STEP			"INTERPRETER_STEP"
#define INTERPRETER_EXECUTION		"INTERPRETER_EXECUTION"
#define INTERPRETER_GLOBAL			"INTERPRETER_GLOBAL"
#define INTERPRETER_REFERENCE		"INTERPRETER_REFERENCE"
#define CREATE_INTERP_LABEL			"CREATE_INTERP_LABEL"
#define INTERPRETER_REFERENCE_LABEL "INTERPRETER_REFERENCE_LABEL"
#define PARAMETERS_LABEL			"PARAMETERS_LABEL"
#define PARAMETER_NAME_LABEL		"PARAMETER_NAME_LABEL"
#define PARAMETER_DIRECTION_LABEL	"PARAMETER_DIRECTION_LABEL"
#define PARAMETER_VALUE_LABEL		"PARAMETER_VALUE_LABEL"
#define PARAMTABLE_NAME_LABEL		"PARAMTABLE_NAME_LABEL"
#define PARAMTABLE_DIRECTION_LABEL	"PARAMTABLE_DIRECTION_LABEL"
#define PARAMTABLE_VALUE_LABEL		"PARAMTABLE_VALUE_LABEL"
#define PARAMETER_ADD				"PARAMETER_ADD"
#define PARAMETER_REMOVE			"PARAMETER_REMOVE"
#define PARAMETER_MOVE_UP			"PARAMETER_MOVE_UP"
#define PARAMETER_MOVE_DOWN			"PARAMETER_MOVE_DOWN"
#define PARAMETER_NAME_DEFAULT		"PARAMETER_NAME_DEFAULT"
#define PARAMETER_INPUT				"PARAMETER_INPUT"
#define PARAMETER_OUTPUT			"PARAMETER_OUTPUT"
#define PARAMETER_INPUTOUTPUT		"PARAMETER_INPUTOUTPUT"
#define CONSOLE_INPUT 				"CONSOLE_INPUT"
#define CONSOLE_OUTPUT 				"CONSOLE_OUTPUT"
#define CONSOLE_DISPLAY_OPTION		"CONSOLE_DISPLAY_OPTION"
#define RESULT_EXPRESSION			"RESULT_EXPRESSION"
#define CONSOLE_DISPLAY_SHOW_INIT   "CONSOLE_DISPLAY_SHOW_INIT"
#define CONSOLE_DISPLAY_SHOW_ALWAYS "CONSOLE_DISPLAY_SHOW_ALWAYS"
#define CONSOLE_DISPLAY_SHOW_NEVER	"CONSOLE_DISPLAY_SHOW_NEVER"
#define CONSOLE_DISPLAY_HIDE		"CONSOLE_DISPLAY_HIDE"
#define CONSOLE_OPTIONS				"CONSOLE_OPTIONS"
#define INTERP_OPTIONS				"INTERP_OPTIONS"
#define BROWSE_FOR_FILE				"BROWSE_FOR_FILE"
#define ERROR_IN_EXPRESSION_TITLE	"ERROR_IN_EXPRESSION_TITLE"
#define FILE_PATH_EXPR_ERROR		"FILE_PATH_EXPR_ERROR"
#define GOTO_ERROR_IN_EXPRESSION	"GOTO_ERROR_IN_EXPRESSION"
#define TCL_SCRIPT_EXPR_ERROR		"TCL_SCRIPT_EXPR_ERROR"
#define RESULT_EXPR_ERROR			"RESULT_EXPR_ERROR"
#define INTERPRETER_REFERENCE_ERROR	"INTERPRETER_REFERENCE_ERROR"
#define CONSOLE_DISPLAY_EXPR_ERROR	"CONSOLE_DISPLAY_EXPR_ERROR"
#define CONSOLE_INPUT_EXPR_ERROR	"CONSOLE_INPUT_EXPR_ERROR"
#define CONSOLE_OUTPUT_EXPR_ERROR	"CONSOLE_OUTPUT_EXPR_ERROR"
#define PARAMETER_EXPR_ERROR		"PARAMETER_EXPR_ERROR"

//dialog constants
#define TCL_OPERATION_EXEC_FILE_IDX		0
#define TCL_OPERATION_EVAL_EXPR_IDX		2
#define TCL_OPERATION_RESET_INTERP_IDX	3
#define TCL_OPERATION_EVAL_LITERAL_IDX	1

#define TCL_EXEC_OPTION_STEP_IDX		0
#define TCL_EXEC_OPTION_THREAD_IDX		1
#define TCL_EXEC_OPTION_EXECUTION_IDX	2
#define TCL_EXEC_OPTION_GLOBAL_IDX		3
#define TCL_EXEC_OPTION_REF_IDX			4

#define PARAMETER_INPUT_IDX				0
#define PARAMETER_OUTPUT_IDX			1
#define PARAMETER_INPUTOUTPUT_IDX		2

#define PARAMETER_COLUMN_NAME_IDX		0
#define PARAMETER_COLUMN_DIR_IDX		1
#define PARAMETER_COLUMN_VAL_IDX		2

#define SHOW_WINDOW_INIT_IDX			0
#define SHOW_WINDOW_ALWAYS_IDX			1
#define SHOW_WINDOW_NEVER_IDX			2
#define HIDE_WINDOW_IDX					3

#define SHOW_WINDOW_INIT_EXPR			"0"
#define SHOW_WINDOW_ALWAYS_EXPR			"1"
#define SHOW_WINDOW_NEVER_EXPR			"2"
#define HIDE_WINDOW_EXPR				"3"
// CTclEditDialog dialog

class CTclEditDialog : public CDialog
{
	DECLARE_DYNAMIC(CTclEditDialog)

public:
	CTclEditDialog(SequenceContextPtr context, CWnd* pParent = NULL);   // standard constructor
	virtual ~CTclEditDialog();

// Dialog Data
	enum { IDD = IDD_TCLEDITDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	//properties
	_bstr_t m_defaultParamName;
	_bstr_t m_inputValString;
	_bstr_t m_outputValString;
	_bstr_t m_inputOutputString;
	int m_parameterSelectedIndex;
	SequenceContextPtr m_context;

	//methods
	void LocalizeDialog(void);
	void TransferValues(int transferToDialog);
	void UpdateVisibility(void);
	void UpdateParamButtonVisibility(int index);
	void PopulateParameters();
	BOOL ValidateDialog();
	BOOL CheckExpressionAndDisplayError(IEnginePtr engine, IExpressionEditPtr expressionEdit, _bstr_t errorString);
	BOOL CheckParameterError(_bstr_t parameterVal, int index);
	//event handlers
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeOperationCombobox();
	afx_msg void OnBnClickedFileByExprCheck();
	DECLARE_EVENTSINK_MAP()	
	void ButtonClickFilePath(LPDISPATCH btn);
	afx_msg void OnCbnSelchangeInterpOpt();
	afx_msg void OnBnClickedAddButton();
	afx_msg void OnBnClickedRemoveButton();
	afx_msg void OnLvnItemchangedParameterList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeParamDir();
	afx_msg void OnEnChangeParamName();
	afx_msg void OnBnClickedMoveUp();
	afx_msg void OnBnClickedMoveDown();	
	void ChangeParamValueExpr();

	//controls

	//general controls
	CStatic m_executionOptionLabel;
	IExpressionEditPtr m_interpRefExpr;
	CWnd * m_interpRefExprWnd;
	CComboBox m_executionOptionComboBox;
	CStatic m_interpreterReferenceLabel;	
	CStatic m_consoleDisplayLabel;
	CButton m_okButton;
	CButton m_cancelButton;
	IExpressionEditPtr m_showConsoleExpr;
	CWnd * m_showConsoleExprWnd;
	CStatic m_inputLabel;
	IExpressionEditPtr m_inputExpr;
	CWnd * m_inputExprWnd;
	CStatic m_outputLabel;
	IExpressionEditPtr m_outputExpr;
	CWnd * m_outputExprWnd;

	//operation controls
	CComboBox m_operationComboBox;
	CStatic m_filePathLabel;
	IExpressionEditPtr m_filePathExpr;
	CWnd * m_filePathExprWnd;
	IExpressionEditPtr m_filePath;
	CWnd * m_filePathWnd;
	CButton m_fileByExprCheckbox;
	CStatic m_tclExpressionLabel;
	IExpressionEditPtr m_tclExpr;
	CWnd * m_tclExprWnd;
	CStatic m_resultExprLabel;
	IExpressionEditPtr m_scriptResultExpr;
	CWnd * m_scriptResultExprWnd;
	IExpressionEditPtr m_scriptLiteralExpr;
	CWnd * m_scriptLiteralExprWnd;

	//parameters
	CStatic m_parameterGroupBox;
	CStatic m_parameterNameLabel;
	CEdit m_parameterName;
	CStatic m_parameterDirectionLabel;
	CComboBox m_paramDirectionComboBox;
	CStatic m_parameterValueLabel;
	IExpressionEditPtr m_paramValue;
	CWnd* m_paramValueWnd;
	CListCtrl m_parameterList;
	CButton m_addParamButton;
	CButton m_removeParamButton;
	CButton m_moveParamUpButton;
	CButton m_moveParamDownButton;

	CStatic m_interpreterOptionsGroupBox;
	CStatic m_consoleOptionsGroupBox;
	CEdit m_fullPath;
	void ChangeFilePath();
	CStatic m_operationTypeLabel;
};
