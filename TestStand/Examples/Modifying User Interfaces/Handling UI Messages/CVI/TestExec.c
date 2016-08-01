#include <cvirte.h>
#include <userint.h>
#include "TestExec.h"	// UIR header
#include "tsutil.h"		// Helpful CVI functions for TestStand
#include "tsui.h"		// API's for the TestStand ActiveX controls
#include "tsuisupp.h"

#define UIMSG_EXAMPLE_PATH "\\..\\..\\UI Message Example.seq"

// Note:	TestStand installs the source code files for the default user interfaces in the <TestStand>\UserInterfaces and <TestStand Public>\UserInterfaces directories.
//			To modify the installed user interfaces or to create new user interfaces, modify the files in the <TestStand Public>\UserInterfaces directory.
//			You can use the read-only source files for the default user interfaces in the <TestStand>\UserInterfaces directory as a reference.
//			National Instruments recommends that you track the changes you make to the user interface source code files so you can integrate the changes with any enhancements in future versions of the TestStand User Interfaces.

// this structure holds the handles to the objects that make up an application window
typedef struct
{
	int			panel;
	CAObjHandle	engine;

	// ActiveX control handles:
	CAObjHandle applicationMgr;
	CAObjHandle sequenceFileViewMgr;
	CAObjHandle executionViewMgr;

	CAObjHandle openFileBtn;
	CAObjHandle runSelectedBtn;
	CAObjHandle tracingEnabledCheckBox;
	CAObjHandle sequenceView;
	CAObjHandle label;
	CAObjHandle sequenceListBox;


} MainPanel;

VBOOL origTracingEnabled;
VBOOL origRequireUserLogin;
VBOOL origPrivelegeCheckingEnabled;

static MainPanel 	gMainWindow;	// the application only has one window

// the presence of these two variables is expected by the tsErrChk macro from tsutil.h.  Usually you declare these variables as locals
// in each function that uses tsErrChk. However, since all the code in this file runs in a single thread, they can be globals for convenience
ERRORINFO	errorInfo = {0, 0, "", "", "", 0, 0};
ErrMsg		errMsg = "";

static int 	SetupActiveXControls(void);
static int	ExitApplication(void);
static void DisplayError(int errorCode);
static void ClearErrorMessage(void);
static int 	MainCallback(int panelOrMenuBarHandle, int controlOrMenuItemID, int event, void *callbackData, int eventData1, int eventData2);

///////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	ssize_t fileSize;
	char dirPath[MAX_PATHNAME_LEN] = "";
	ERRORINFO ErrorInfo;

	TSObj_StationOptions stationOpts = 0;
	int		error = 0;
	long	exitCode = 0;

	nullChk( InitCVIRTE(0, argv, 0));	// initialize CVI runtime engine

	// load the panel for the main window from the .UIR file
	errChk( gMainWindow.panel = LoadPanelEx (0, "TestExec.uir", MAINPANEL, __CVIUserHInst));

	// get ActiveX ctrl handles, register ActiveX event callbacks, and connect TestStand controls
	errChk( SetupActiveXControls());

	errChk( InstallMainCallback(MainCallback, 0, 0));	// handle the EVENT_END_TASK event

	// make a handle to engine conveniently accessible
	tsErrChk( TSUI_ApplicationMgrGetEngine(gMainWindow.applicationMgr, &errorInfo, &gMainWindow.engine));

	//store original station options so they can be restored when the UI is closed
	tsErrChk( TS_EngineGetStationOptions(gMainWindow.engine, &ErrorInfo, &stationOpts));

	tsErrChk( TS_StationOptionsGetEnableUserPrivilegeChecking(stationOpts, &ErrorInfo, &origPrivelegeCheckingEnabled));
	tsErrChk( TS_StationOptionsGetTracingEnabled(stationOpts, &ErrorInfo, &origTracingEnabled));
	tsErrChk( TS_StationOptionsGetRequireUserLogin(stationOpts, &ErrorInfo, &origRequireUserLogin));

	tsErrChk( TS_StationOptionsSetEnableUserPrivilegeChecking(stationOpts, &ErrorInfo, VFALSE));
	tsErrChk( TS_StationOptionsSetTracingEnabled(stationOpts, &ErrorInfo, VTRUE));
	tsErrChk( TS_StationOptionsSetRequireUserLogin(stationOpts, &ErrorInfo, VFALSE));

	CA_DiscardObjHandle(stationOpts);
	stationOpts = 0;
	// start up the TestStand User Interface Components. this also logs in the user
	tsErrChk( TSUI_ApplicationMgrStart(gMainWindow.applicationMgr, &errorInfo));

	// Open the "UI Message Example.seq" sequence file which posts the UI messages handled by this UI.
	// Typically, a TestStand UI should not open a specific sequence file.
	// This example UI opens a specific file for demonstrational purposes only.
	errChk( GetModuleDir(__CVIUserHInst, dirPath));
	strncat( dirPath, UIMSG_EXAMPLE_PATH, MAX_PATHNAME_LEN - 1);
	if(FileExists(dirPath, &fileSize))
		tsErrChk( TSUI_ApplicationMgrOpenSequenceFile(gMainWindow.applicationMgr, &errorInfo, dirPath, NULL));

	// display window and process user input until application exits
	errChk( DisplayPanel(gMainWindow.panel));
	errChk( RunUserInterface());


	errChk( TSUI_ApplicationMgrGetExitCode(gMainWindow.applicationMgr, &errorInfo, &exitCode));

Error:

	if (gMainWindow.panel > 0)
		DiscardPanel(gMainWindow.panel);

	DisplayError(error);

	return exitCode;
}

////////////////////////////////////////////////////////////////////////////////////

int CVICALLBACK MainPanelCallback(int panel, int event, void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_CLOSE:		// EVENT_CLOSE == user clicked on window close box
			ExitApplication(); 	// this function displays error, if any
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////

static int MainCallback(int panelOrMenuBarHandle, int controlOrMenuItemID, int event, void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_END_TASK:	// EVENT_END_TASK can occur when windows shuts down or when the user selects Close from the context menu for the application's task bar item
			if (!ExitApplication() && !eventData1)
				return 1; //  don't immediately exit if we have cleanup to do and the whole computer is not shutting down
			break;
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////

// the ApplicationMgr control sends this event when it is ok to exit the application.
// discard any handles to TestStand objects here at the latest
HRESULT CVICALLBACK ApplicationMgr_OnExitApplication(CAObjHandle caServerObjHandle, void *caCallbackData)
{
	ERRORINFO ErrorInfo;
	int		error = 0;

	CAObjHandle stationOpts = 0;

	//restore station options
	tsErrChk( TS_EngineGetStationOptions(gMainWindow.engine, &ErrorInfo, &stationOpts));
	tsErrChk( TS_StationOptionsSetEnableUserPrivilegeChecking(stationOpts, &ErrorInfo, origPrivelegeCheckingEnabled));
	tsErrChk( TS_StationOptionsSetTracingEnabled(stationOpts, &ErrorInfo, origTracingEnabled));
	tsErrChk( TS_StationOptionsSetRequireUserLogin(stationOpts, &ErrorInfo, origRequireUserLogin));

Error:
	CA_DiscardObjHandle(stationOpts);
	CA_DiscardObjHandle(gMainWindow.engine);
	gMainWindow.engine = 0;

	ExitApplication();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////

// the ApplicationMgr sends this event when the TestStand UI Controls need to display an error
HRESULT CVICALLBACK ApplicationMgr_OnReportError(CAObjHandle caServerObjHandle, void *caCallbackData, long  errorCode, char *errorMessage)
{
	strcpy(errMsg, errorMessage);	// update global errMsg buffer
	DisplayError(errorCode);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////

// the ApplicationMgr sends this event to request that the UI display a particular execution
HRESULT CVICALLBACK ApplicationMgr_OnDisplayExecution(CAObjHandle caServerObjHandle, void *caCallbackData, TSUIObj_Execution execution, enum TSUIEnum_ExecutionDisplayReasons reason)
{
	int	error = 0;

	// bring application to front if we hit a breakpoint
	if (reason == TSUIConst_ExecutionDisplayReason_Breakpoint || reason == TSUIConst_ExecutionDisplayReason_BreakOnRunTimeError)
		errChk( SetActivePanel(gMainWindow.panel));

	tsErrChk( TSUI_ExecutionViewMgrSetByRefExecution(gMainWindow.executionViewMgr, &errorInfo, execution));

Error:
	DisplayError(error);
	return error < 0 ? E_FAIL : S_OK;
}

///////////////////////////////////////////////////////////////////////////

// the ApplicationMgr sends this event to request that the UI display a particular sequence file
HRESULT CVICALLBACK ApplicationMgr_OnDisplaySequenceFile(CAObjHandle caServerObjHandle, void *caCallbackData, TSUIObj_SequenceFile file, enum TSUIEnum_SequenceFileDisplayReasons reason)
{
	int	error = 0;

	tsErrChk( TSUI_SequenceFileViewMgrSetByRefSequenceFile(gMainWindow.sequenceFileViewMgr, &errorInfo, file));

Error:
	DisplayError(error);
	return error < 0 ? E_FAIL : S_OK;
}

///////////////////////////////////////////////////////////////////////////

// call this function to exit the program
static int ExitApplication(void)
{
	int		error = 0;
	VBOOL	canExitNow;

	// The first call to ApplicationMgrShutDown unloads files, logs out, runs unload callbacks, and finally triggers an OnApplicationCanExit event, which calls
	// this function again. When the second call ApplicationMgrShutdown returns true for canExitNow, we call QuitUserInterface, which causes the RunUserInterface call to return.
	tsErrChk( TSUI_ApplicationMgrShutdown(gMainWindow.applicationMgr, &errorInfo, &canExitNow));
	if (canExitNow)
		QuitUserInterface(0);

Error:
	DisplayError(error);
	return canExitNow ? TRUE : FALSE;
}

///////////////////////////////////////////////////////////////////////////

// call this function after you handle an error, unless you handle the error by calling DisplayError, which also calls this function
static void ClearErrorMessage(void)
{
	// clear out error message globals so that a future error that lacks an error description does not
	// unintentionally use the error description from a prior error.
	*errMsg = '\0';
	memset(&errorInfo, 0, sizeof(ERRORINFO));
}

//////////////////////////////////////////////

// displays a message box with the error code, the error message associated with the code, and any error description details
// does nothing if errorCode is not negative
static void DisplayError(int errorCode)
{
	if (errorCode < 0)
	{
		TS_DisplayError(errorCode, errMsg, gMainWindow.engine);	// errMsg is a global, see top of file
		ClearErrorMessage();
	}
}

///////////////////////////////////////////////////////////////////////////

// handles custom UI messages - UI messages with event code greater than UserMessage_Base (10000)
HRESULT CVICALLBACK ApplicationMgr_OnUserMessage(CAObjHandle caServerObjHandle, void *caCallbackData, TSUIObj_UIMessage  uiMsg)
{
	#define UserMsg_UsingSupportedUI 10010
	#define UserMsg_SendStatus 10100
	#define UserMsg_ReadUISetting 10200

	ERRORINFO ErrorInfo;
	char *uiMsgStringData = NULL;
	int seqDialogsEnabled = 0;

	TSObj_Thread currentThread = 0;
	CAObjHandle currentSeqContext = 0;

	long frameID = 0;

	enum TSEnum_UIMessageCodes uiMsgEvent = 0;

	int		error = 0;
	long	exitCode = 0;

	tsErrChk(TS_UIMessageGetEvent(uiMsg, &errorInfo, &uiMsgEvent));
	tsErrChk(TS_UIMessageGetThread(uiMsg, &errorInfo, &currentThread));
	tsErrChk(TS_ThreadGetSequenceContext(currentThread, &errorInfo, 0, &frameID, &currentSeqContext));

	switch (uiMsgEvent)
	{
		case (UserMsg_UsingSupportedUI):
			/* This message is used by a sequence to check if the current user interface supports specific user message
			* codes used.  The user interface sets FileGlobals.UISupportsCustomMessages to true, indicating that
			* custom messages are supported */

			tsErrChk(TS_PropertySetValBoolean(currentSeqContext, &ErrorInfo, "FileGlobals.UISupportsCustomMessages", 0x1, VTRUE));
			break;

		case (UserMsg_SendStatus):
			/* This case shows the recommended approach for sending data from the executing sequence to the UI:
			* 1. The sequence file posts a UI Message with the data to transfer in the stringData, NumericData, or ActiveXData parameters
			* 2. This callback executes and reads the data from the event data and processes it*/

			tsErrChk(TS_UIMessageGetStringData(uiMsg, &errorInfo, &uiMsgStringData));
			tsErrChk(SetCtrlVal(gMainWindow.panel, MAINPANEL_SEQ_STATUS, uiMsgStringData));
			break;
			
		case (UserMsg_ReadUISetting):

			/* This case shows the recommended approach for sending data from the UI to the executing sequence:
			 * 1. The sequence file posts a synchronous UI Message, indicating that it is ready for the UI to
			 * configure the settings.  The execution pauses until the UImessage is handled by a callback.
			 * 2. This callback executes and configures the desired properties while the execution is paused.
			 * 3. Once this callback completes, the sequence resumes executing  */

			tsErrChk(GetCtrlVal(gMainWindow.panel, MAINPANEL_SHOW_SEQ_DLGS, &seqDialogsEnabled));
			tsErrChk(TS_PropertySetValBoolean(currentSeqContext, &ErrorInfo, "FileGlobals.ShowDialogs", TS_PropOption_InsertIfMissing, (int)seqDialogsEnabled));
			break;
	}

Error:
	CA_FreeMemory(uiMsgStringData);
	CA_DiscardObjHandle(currentThread);
	CA_DiscardObjHandle(currentSeqContext);
	
	DisplayError(error);
	return S_OK;
}


// obtain ActiveX control handles and register ActiveX event callbacks
static int SetupActiveXControls(void)
{
	int			error = 0;
	CAObjHandle	connection = 0;

	// get handles to ActiveX controls
	errChk( GetObjHandleFromActiveXCtrl(gMainWindow.panel, MAINPANEL_APPLICATIONMGR, 		&gMainWindow.applicationMgr));
	errChk( GetObjHandleFromActiveXCtrl(gMainWindow.panel, MAINPANEL_SEQUENCEFILEVIEWMGR,	&gMainWindow.sequenceFileViewMgr));
	errChk( GetObjHandleFromActiveXCtrl(gMainWindow.panel, MAINPANEL_EXECUTIONVIEWMGR, 		&gMainWindow.executionViewMgr));

	errChk( GetObjHandleFromActiveXCtrl(gMainWindow.panel, MAINPANEL_OPENFILEBTN, 			&gMainWindow.openFileBtn));
	errChk( GetObjHandleFromActiveXCtrl(gMainWindow.panel, MAINPANEL_RUNSELECTEDBTN,		&gMainWindow.runSelectedBtn));
	errChk( GetObjHandleFromActiveXCtrl(gMainWindow.panel, MAINPANEL_SEQUENCEVIEW, 			&gMainWindow.sequenceView));
	errChk( GetObjHandleFromActiveXCtrl(gMainWindow.panel, MAINPANEL_LABEL,			 		&gMainWindow.label));
	errChk( GetObjHandleFromActiveXCtrl(gMainWindow.panel, MAINPANEL_LISTBOX, 				&gMainWindow.sequenceListBox));

	// register ActiveX control event callbacks
	errChk( TSUI__ApplicationMgrEventsRegOnExitApplication(gMainWindow.applicationMgr, 		ApplicationMgr_OnExitApplication, NULL, 1, NULL));
	errChk( TSUI__ApplicationMgrEventsRegOnReportError(gMainWindow.applicationMgr, 			ApplicationMgr_OnReportError, NULL, 1, NULL));
	errChk( TSUI__ApplicationMgrEventsRegOnDisplaySequenceFile(gMainWindow.applicationMgr,	ApplicationMgr_OnDisplaySequenceFile, NULL, 1, NULL));
	errChk( TSUI__ApplicationMgrEventsRegOnDisplayExecution(gMainWindow.applicationMgr, 	ApplicationMgr_OnDisplayExecution, NULL, 1, NULL));
	errChk( TSUI__ApplicationMgrEventsRegOnUserMessage(gMainWindow.applicationMgr, 			ApplicationMgr_OnUserMessage, NULL, 1, NULL));

	// "Command Connections" are used to configure a TestStand Button or Checkbox control control to execute a specified command when clicked.
	// Changing the cmdKind Input will change the functionality of the button.
	tsErrChk( TSUI_SequenceFileViewMgrConnectCommand(gMainWindow.sequenceFileViewMgr, &errorInfo, gMainWindow.openFileBtn, TSUIConst_CommandKind_OpenSequenceFiles, 0, TSUIConst_CommandConnection_NoOptions, NULL));
	tsErrChk( TSUI_SequenceFileViewMgrConnectCommand(gMainWindow.sequenceFileViewMgr, &errorInfo, gMainWindow.runSelectedBtn, TSUIConst_CommandKind_RunCurrentSequence, 0, TSUIConst_CommandConnection_NoOptions, NULL));

	// "Information Source" Connections are used to display caption, image, and numeric information on Label controls, ExpressionEdit controls, and StatusBar panes.
	// Changing the source Input will change what information is displayed in the connected control.
	tsErrChk( TSUI_SequenceFileViewMgrConnectCaption(gMainWindow.sequenceFileViewMgr, &errorInfo, gMainWindow.label, TSUIConst_CaptionSource_CurrentSequenceFile, VFALSE, NULL));

	// "List Connections" are used to configure a TestStand ComboBox, ListBarPage, or ListBox to display a TestStand List, such as the sequences in the current file.
	// The manager controls provide a separate method for each connection type, so no cmdKind parameter is needed.
	tsErrChk( TSUI_SequenceFileViewMgrConnectSequenceList(gMainWindow.sequenceFileViewMgr, &errorInfo, gMainWindow.sequenceListBox, NULL));

	// "View Connections" are used to activate a SequenceView or ReportView control.
	// The manager controls provide a separate method for each connection type, so no cmdKind parameter is needed.
	tsErrChk( TSUI_ExecutionViewMgrConnectExecutionView(gMainWindow.executionViewMgr, &errorInfo, gMainWindow.sequenceView, TSUIConst_ExecutionViewConnection_NoOptions, NULL));

	// show all step groups at once in the sequence view
	tsErrChk( TSUI_ExecutionViewMgrSetStepGroupMode (gMainWindow.executionViewMgr, &errorInfo, TSUIConst_StepGroupMode_AllGroups));

Error:
	CA_DiscardObjHandle(connection);
	return error;
}

