#include <cvirte.h>
#include <userint.h>
#include "TestExec.h"	// UIR header
#include "tsutil.h"		// Helpful CVI functions for TestStand
#include "tsui.h"		// API's for the TestStand ActiveX controls
#include "tsuisupp.h"

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

} MainPanel;

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

	// start up the TestStand User Interface Components. this also logs in the user
	tsErrChk( TSUI_ApplicationMgrStart(gMainWindow.applicationMgr, &errorInfo));

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

// the ApplicationMgr sends this event when an execution is complete
HRESULT CVICALLBACK ApplicationMgr_OnEndExecution(CAObjHandle caServerObjHandle, void *caCallbackData, TSUIObj_Execution  exec)
{
	char *reportLocation = "";
	TSObj_Report reportObj = 0;
	ERRORINFO ErrorInfo;
	int	error = 0;

	tsErrChk(TS_ExecutionGetReport(exec, &ErrorInfo, &reportObj));
	tsErrChk(TS_ReportGetLocation(reportObj, &ErrorInfo, &reportLocation));
	if(strcmp(reportLocation, ""))
	{
		char *resultStatus;
		tsErrChk(TS_ExecutionGetResultStatus(exec, &ErrorInfo, &resultStatus));
		InsertTableRows(gMainWindow.panel, MAINPANEL_TABLE , 1, 1, VAL_CELL_STRING);
		SetTableCellVal(gMainWindow.panel, MAINPANEL_TABLE , MakePoint(1,1) , reportLocation);
		SetTableCellVal(gMainWindow.panel, MAINPANEL_TABLE , MakePoint(2,1) , resultStatus);
	}

Error:
	CA_DiscardObjHandle(reportObj);
	CA_FreeMemory(reportLocation);

	DisplayError(error);
	return error < 0 ? E_FAIL : S_OK;
}

///////////////////////////////////////////////////////////////////////////

// the ApplicationMgr sends this event to request that the UI display a particular sequence file
HRESULT CVICALLBACK ApplicationMgr_OnDisplaySequenceFile(CAObjHandle caServerObjHandle, void *caCallbackData, TSUIObj_SequenceFile file, enum TSUIEnum_SequenceFileDisplayReasons reason)
{
	ERRORINFO ErrorInfo;
	char *seqFilePathName = NULL;
	int	error = 0;

	tsErrChk( TSUI_SequenceFileViewMgrSetByRefSequenceFile(gMainWindow.sequenceFileViewMgr, &errorInfo, file));
	tsErrChk( TS_SeqFileGetPath(file, &ErrorInfo, &seqFilePathName));
	errChk(SetCtrlVal(gMainWindow.panel, MAINPANEL_CUR_SEQ_FILE_TEXTBOX, seqFilePathName));

Error:
	CA_FreeMemory(seqFilePathName);
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

// obtain ActiveX control handles and register ActiveX event callbacks
static int SetupActiveXControls(void)
{
	int			error = 0;

	// get handles to ActiveX controls
	errChk( GetObjHandleFromActiveXCtrl(gMainWindow.panel, MAINPANEL_APPLICATIONMGR, 		&gMainWindow.applicationMgr));
	errChk( GetObjHandleFromActiveXCtrl(gMainWindow.panel, MAINPANEL_SEQUENCEFILEVIEWMGR,	&gMainWindow.sequenceFileViewMgr));

	// register ActiveX control event callbacks
	errChk( TSUI__ApplicationMgrEventsRegOnExitApplication(gMainWindow.applicationMgr, 		ApplicationMgr_OnExitApplication, NULL, 1, NULL));
	errChk( TSUI__ApplicationMgrEventsRegOnReportError(gMainWindow.applicationMgr, 			ApplicationMgr_OnReportError, NULL, 1, NULL));
	errChk( TSUI__ApplicationMgrEventsRegOnDisplaySequenceFile(gMainWindow.applicationMgr,	ApplicationMgr_OnDisplaySequenceFile, NULL, 1, NULL));
	errChk( TSUI__ApplicationMgrEventsRegOnEndExecution(gMainWindow.applicationMgr,		 	ApplicationMgr_OnEndExecution, NULL, 1, NULL));


Error:
	return error;
}

int CVICALLBACK OpenSequenceFileCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	TSUIObj_Command commandObj = 0;
	ERRORINFO ErrorInfo;
	int error = 0;

	switch (event)
	{
		case EVENT_COMMIT:
			tsErrChk(TSUI_ApplicationMgrGetCommand(gMainWindow.applicationMgr, &ErrorInfo, TSUIConst_CommandKind_OpenSequenceFile, 0, &commandObj));
			tsErrChk(TSUI_CommandExecute(commandObj, &ErrorInfo, VTRUE));
			break;
	}

Error:
	CA_DiscardObjHandle(commandObj); 
	DisplayError(error);
	return 0;
}

int CVICALLBACK ExecuteCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	TSUIObj_SequenceFile currentSeqFile = 0;
	TSUIObj_Command commandObj = 0;
	int error = 0;

	switch (event)
	{
		case EVENT_COMMIT:
			tsErrChk(TSUI_SequenceFileViewMgrGetSequenceFile(gMainWindow.sequenceFileViewMgr, &errorInfo, &currentSeqFile));
			if(currentSeqFile == 0)
			{
				MessagePopup("Error", "You must open a sequence file before you can execute.");
			}
			else
			{
				tsErrChk(TSUI_SequenceFileViewMgrGetCommand(gMainWindow.sequenceFileViewMgr, &errorInfo, TSUIConst_CommandKind_ExecutionEntryPoints_Set, 0, &commandObj));
				tsErrChk(TSUI_CommandExecute(commandObj, &errorInfo, VTRUE));
			}
			break;
	}

Error:
	CA_DiscardObjHandle(commandObj);
	CA_DiscardObjHandle(currentSeqFile);

	DisplayError(error);
	return 0;
}
