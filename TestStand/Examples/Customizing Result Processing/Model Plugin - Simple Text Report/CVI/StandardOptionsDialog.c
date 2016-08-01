//==============================================================================
//
// Title:       StandardOptionsDialog.c
//
// Created on:  9/8/2011 by Jed Beach.
//
//==============================================================================


#include "StandardOptionsDialog.h"

#include <tsapicvi.h>
#include <cvirte.h>
#include <tsutil.h>
#include <userint.h>
#include <windows.h>

#include "Utils.h"

//========================================================================
// TYPES
//========================================================================


// The DialogState structure stores the state variables of a given
// instance of the panel.  Create one of these in RunDialog() and pass
// its address to InitOptionsDialog().  To clean up, pass its address to
// DisposeOptionsDialog().
typedef struct
{
	int mainPanel;     // Handle to the dialog's main panel.
	BOOL changed;      // Flag set to true if/when the user has changed something.
	CAObjHandle engine;// Handle to the TestStand Engine instance.
	TSModalData modalData;
}
DialogState;

// There is a macro called InitialModalData, but it is defined such that
// it only be used in a variable initialization line.  NULL_TSModalData
// can be used anywhere.
const static TSModalData NULL_TSModalData = {0};

//========================================================================
// CONSTANTS
//========================================================================

// The name of the Options dialog's .uir file.  Needed by LoadPanelEx().
static const char UIR_FILE[] = "StandardOptionsDialog.uir";

//
// Paths to PropertyObject members.
//

static const char P_Base_ProcessOnTheFly[] = "Base.ProcessOnTheFly";
static const char P_PluginSpecific_Options_ResultDirectory[] = "PluginSpecific.Options.ResultDirectory";

//
// String constants related to localization.
//

static char LOCALIZED_STRING_SECTION[] = "SIMPLE_TEXT_REPORT_GENERATOR_CONFIGURATION_DIALOG";
static char LOCAL_SELECT_DIRECTORY[] = "SELECT_DIRECTORY";

static char COMMON_DLG_SECTION[] = "COMMON_DLG";
static char COMMON_DLG_OK[] = "ok";

//========================================================================
// FUNCTION PROTOTYPES FOR STATIC FUNCTIONS
//========================================================================

static int InitOptionsDialog(DialogState *, CAObjHandle, ErrMsg);
static void DisposeOptionsDialog(DialogState *);
static int UpdateDialogFromConfig(const DialogState *, CAObjHandle);
static int UpdateConfigFromDialog(const DialogState *, CAObjHandle);
static void DoBrowseDialog(int);
static void DoMarkChanged(int);
static void DoHelp(int);
static BOOL DoOk(int);


// Standard implementation of DllMain().  Nothing special was done for
// the plug-in.
int __stdcall DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			if (InitCVIRTE (hinstDLL, 0, 0) == 0)
			{
				return 0; /* out of memory */
			}
		}
		break;

		case DLL_PROCESS_DETACH:
		{
			if (!CVIRTEHasBeenDetached()) /* Do not call CVI functions if cvirte.dll has already been detached. */
			{
				CloseCVIRTE ();
			}
		}
		break;
	}

	return 1;
}

// Standard implementation of DllEntryPoint().  Nothing special was done for
// the plug-in.
int __stdcall DllEntryPoint(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	/* Included for compatibility with Borland */

	return DllMain(hinstDLL, fdwReason, lpvReserved);
}

// Initialize the members of the passed DialogState structure.  Call
// DisposeOptionsDialog() to clean up.
//
// dialogState - Pointer to DialogState object for this panel instance.  The
//          caller needs to have allocated the structure.  InitOptionsDialog()
//          initializes its members.
//
// engine -- A handle to a TestStand Engine instance.
// errMsg -- A buffer to hold an error message should an error occur.
//        The buffer must have at least ERRMSG_SIZE bytes.
//
// return -- Greater than or equal to 0 on success, less than 0 on failure.
static int InitOptionsDialog(DialogState * dialogState, CAObjHandle engine, ErrMsg errMsg)
{
	int error = TS_Err_NoError;
	ERRORINFO errorInfo = {0};

	int fontSize = 0;

	VBOOL shouldAbort = VFALSE;

	Assert(dialogState != 0);

	dialogState->engine = engine;

	dialogState->modalData = NULL_TSModalData;
	tsErrChk( TS_StartModalDialogEx(dialogState->engine, &errorInfo, 0, &shouldAbort, &dialogState->modalData) );

	if (shouldAbort)
	{
		// There is no specific error code for abort.  Returning -1
		// communicates to the caller, DisplayOptionsDialog(), that it
		// should abort.
		error = -1;
		goto Error;
	}

	dialogState->mainPanel = LoadPanelEx(0, UIR_FILE, PANEL_CFG, __CVIUserHInst);

	if (dialogState->mainPanel < 0)
	{
		error = dialogState->mainPanel;
		dialogState->mainPanel = 0;
		errChk(error);
	}

	// Set the callback data so that callbacks have access to the
	// DialogState data.
	errChk( SetPanelAttribute(dialogState->mainPanel, ATTR_CALLBACK_DATA, dialogState) );

	// TestStand-specific approach for localizing strings in the UI.
	errChk( TS_LoadPanelResourceStrings(0, dialogState->engine, dialogState->mainPanel, LOCALIZED_STRING_SECTION) );

	errChk( GetCtrlAttribute(dialogState->mainPanel, PANEL_CFG_LABEL_RESULTDIRECTORY, ATTR_TEXT_POINT_SIZE, &fontSize) );
	errChk( SetCtrlAttribute(dialogState->mainPanel, PANEL_CFG_LABEL_RESULTFILEFMT,   ATTR_TEXT_POINT_SIZE,  fontSize) );

Error:

	return error;
}


// Discard the panel and clean-up DialogState.
//
// dialogState - Pointer to DialogState object for this panel instance. The
//         structure itself is not freed.
static void DisposeOptionsDialog(DialogState * dialogState)
{
	if (dialogState)
	{
		// Ignore errors below.  No matter what happens, clean up as much
		// as possible.
		if (dialogState->mainPanel > 0)
		{
			DiscardPanel(dialogState->mainPanel);
		}

		dialogState->mainPanel = 0;

		TS_EndModalDialog( NULL, &(dialogState->modalData) );
		dialogState->modalData = NULL_TSModalData;

		dialogState->engine = 0; // DialogState does not own the engine, so just null out the handle.
	}
}

// Update the dialog box with data from the model plug-in configuration.
//
// dialogState -- Pointer to DialogState object for this panel instance.
//
// config -- A handle to a PropertyObject of type NI_ModelPlugin.  It must
//         have the appropriate specialization for the Simple Text Report plug-in.
//
// return -- Greater than or equal to 0 on success, less than 0 on failure.
static int UpdateDialogFromConfig(const DialogState * dialogState, CAObjHandle config)
{
	int error = TS_Err_NoError;

	ErrMsg errMsg = {0};

	Assert(dialogState != 0);

	errChk( TS_SetCtrlToPropertyValEx(config, P_Base_ProcessOnTheFly,                   dialogState->mainPanel, PANEL_CFG_CHECKBOX_ON_THE_FLY,  errMsg) );
	errChk( TS_SetCtrlToPropertyValEx(config, P_PluginSpecific_Options_ResultDirectory, dialogState->mainPanel, PANEL_CFG_TEXT_RESULTDIRECTORY, errMsg) );

Error:

	return error;
}


// Update the model plug-in configuration from the state of the dialog box.
//
// dialogState -- Pointer to DialogState object for this panel instance.  The
//         pointer must not be null.
//
// config -- A handle to a PropertyObject of type NI_ModelPlugin.  It must
//         have the appropriate specialization for the Simple Text Report plug-in.
//         The handle must not be null.
//
// return -- Greater than or equal to 0 on success, less than 0 on failure.
static int UpdateConfigFromDialog( const DialogState * dialogState, CAObjHandle config )
{
	int error = TS_Err_NoError;

	ErrMsg errMsg = {0};

	Assert(dialogState != 0);

	errChk( TS_SetPropertyToCtrlValEx(dialogState->mainPanel, PANEL_CFG_CHECKBOX_ON_THE_FLY,  config, P_Base_ProcessOnTheFly,                   errMsg) );
	errChk( TS_SetPropertyToCtrlValEx(dialogState->mainPanel, PANEL_CFG_TEXT_RESULTDIRECTORY, config, P_PluginSpecific_Options_ResultDirectory, errMsg) );

Error:

	return error;
}

// NI_SimpleTextReport_CVI.seq calls DisplayOptionsDialog() from the
// "Model Plugin - Configure Standard Options" callback to create and
// display an instance of the Options dialog box.
//
// simpleTextReportPlugin -- A handle to a PropertyObject of type
//         NI_ModelPlugin.  It must have the appropriate specialization
//         for the Simple Text Report plug-in.
//
// engine -- A handle to a TestStand Engine instance.  The calling
//         sequence should pass RunState.Engine.
//
// returns -- TRUE if changes were made and should be applied, FALSE
//         otherwise.
BOOL DisplayOptionsDialog(CAObjHandle simpleTextReportPlugin, CAObjHandle engine)
{
	int error = TS_Err_NoError;
	ErrMsg errMsg = {0};

	BOOL applyChanges = FALSE;
	DialogState dialogState = {0};

	errChk( InitOptionsDialog(&dialogState, engine, errMsg) );

	errChk( UpdateDialogFromConfig(&dialogState, simpleTextReportPlugin) );
	errChk( InstallPopup(dialogState.mainPanel) );

	if (RunUserInterface())
	{
		errChk( UpdateConfigFromDialog(&dialogState, simpleTextReportPlugin) );
		applyChanges = TRUE;
	}

Error:

	TS_DisplayError(error, errMsg, engine);

	DisposeOptionsDialog(&dialogState);

	return applyChanges;
}


// Callback for the "Cancel" button.
int CVICALLBACK CbCancel( int panel, int control, int event, void *callbackData, int eventData1, int eventData2 )
{
	switch (event)
	{
		case EVENT_COMMIT:
			QuitUserInterface(0);
			break;

		default: break; // Do nothing.
	}


	return 0;
}

// Callback for the "OK" button.
int CVICALLBACK CbOk(int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			QuitUserInterface(DoOk(panel));
			break;

		default: break; // Do nothing.
	}

	return 0;
}

// Helper function for CbOK().
//
// panel -- Handle to the dialog's main panel.
//
// Return -- TRUE if the dialog has changes, FALSE if the dialog has not
//         been changed.
static BOOL DoOk(int panel)
{
	int error = TS_Err_NoError;

	const DialogState * dialogState = NULL;

	errChk( GetPanelAttribute(panel, ATTR_CALLBACK_DATA, &dialogState) );
	errChk( dialogState? TS_Err_NoError : TS_Err_InvalidPointer );

	return dialogState->changed;

Error:

	TS_DisplayError(error, NULL, 0);

	// If there is an error, give up on saving changes.
	return FALSE;
}


// Callback for the "Help" button.
int CVICALLBACK CbHelp(int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			DoHelp(panel);
			break;

		default: break; // Do nothing.
	}

	return 0;
}

// Helper function for CbHelp().
//
// panel -- Handle to the dialog's main panel.
static void DoHelp(int panel)
{
	int error = TS_Err_NoError;
	ErrMsg errMsg = {0};
	ERRORINFO errorInfo = {0};
	
	char * helpDir = NULL; // Free with CA_FreeMemory().
	SimpleStringBuilder helpFile = {0};

	const DialogState * dialogState = NULL;
	long hWnd_UNUSED = 0;
	const int SimpleTextReportDlgHelpId = 8186;
	
	errChk( GetPanelAttribute(panel, ATTR_CALLBACK_DATA, &dialogState) );
	errChk( dialogState? TS_Err_NoError : TS_Err_InvalidPointer );

	errChk( TS_EngineGetTestStandPath(dialogState->engine, &errorInfo, TS_TestStandPath_TestStand, &helpDir) );
	
	SSB_Set(&helpFile, helpDir);
	
	if (!SSB_EndsWithChar(&helpFile, '\\'))
	{
		errChk( SSB_Append(&helpFile, "\\") );
	}
	
	errChk( SSB_Append(&helpFile, "Doc\\Help\\TSSuppRef.chm") );

	tsErrChk( TS_EngineDisplayHelpTopic(dialogState->engine, &errorInfo, SimpleTextReportDlgHelpId, SSB_GetString(&helpFile), "", "", "", "", &hWnd_UNUSED) );

Error:

	TS_DisplayError(error, errMsg, 0);
	
	CLEAR(helpDir, CA_FreeMemory);
	SSB_Destroy(&helpFile);
}

// Callback for widgets that need to report they have been changed but do
// not otherwise require action.  For example, when a user checks or
// unchecks any checkbox, the only immediately required action is updating
// the changed member of the DialogState.
int CVICALLBACK CbMarkChanged(int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			DoMarkChanged(panel);
			break;

		default: break; // Do nothing.
	}

	return 0;
}

// Helper function for CbMarkChanged().
//
// panel -- Handle to the dialog's main panel.
static void DoMarkChanged(int panel)
{
	int error = TS_Err_NoError;

	DialogState * dialogState = NULL;

	errChk( GetPanelAttribute(panel, ATTR_CALLBACK_DATA, &dialogState) );
	errChk( dialogState? TS_Err_NoError : TS_Err_InvalidPointer );

	dialogState->changed = TRUE;

Error:

	TS_DisplayError(error, NULL, 0);
}

// Callback for the "..." (browse) button.
int CVICALLBACK CbBrowse(int panel, int control, int event,void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			DoBrowseDialog(panel);
			break;

		default: break; // Do nothing.
	}


	return 0;
}

// Helper function for CbBrowse().
//
// panel -- Handle to the dialog's main panel.
static void DoBrowseDialog(int panel)
{
	int error = TS_Err_NoError;
	ErrMsg errMsg = {0};
	ERRORINFO errorInfo = {0};

	SAFEARRAY * absolutePaths   = NULL; // clean up with CA_SafeArrayDestroy()
	char ** absolutePathsArray  = NULL; // clean up with CA_FreeMemory()
	char * dialogTitle          = NULL; // clean up with free()
	char * okButtonText         = NULL; // clean up with free()
	char * currentPath          = NULL; // clean up with free()
	DialogState * dialogState   = NULL; // Do not clean up.

	const int dialogFlags       = TS_OpenFile_SelectDirectoriesOnly | TS_OpenFile_UseAbsolutePath;
	VARIANT currentFile         = CA_DEFAULT_VAL;
	VBOOL pressedOk             = VFALSE;

	errChk( GetPanelAttribute(panel, ATTR_CALLBACK_DATA, &dialogState) );
	errChk( dialogState? TS_Err_NoError : TS_Err_InvalidPointer );

	//
	// Localize text for dialog title and OK button.
	//

	errChk( TS_AllocResourceString(dialogState->engine, COMMON_DLG_SECTION, COMMON_DLG_OK, COMMON_DLG_OK, &okButtonText) );
	errChk( TS_AllocResourceString(dialogState->engine, LOCALIZED_STRING_SECTION, LOCAL_SELECT_DIRECTORY, LOCAL_SELECT_DIRECTORY, &dialogTitle) );


	// Retrieve the current path from the Result Directory text box.
	errChk( AllocateCtrlValString(dialogState->mainPanel, PANEL_CFG_TEXT_RESULTDIRECTORY, &currentPath) );

	// Display the file browse dialog box.
	tsErrChk( TS_EngineDisplayFileDialog(
		dialogState->engine,
		&errorInfo,
		dialogTitle,
		okButtonText,
		currentPath,
		NULL,				// Selected Paths
		&absolutePaths,
		dialogFlags,
		"",					// Default Extension
		0,					// Win32Flags
		"",					// File Filter
		CA_DEFAULT_VAL,		// Current File
		NULL,				// File Filter Index
		NULL,				// Directory History List
		&pressedOk) );


	if (pressedOk)
	{
		size_t numElements = 0;

		CA_SafeArrayTo1DArrayEx(&absolutePaths, CAVT_CSTRING, 0, &absolutePathsArray, &numElements);

		if (numElements == 1)
		{
			// Only update the path if the updated path is actually
			// different from the original one.
			if (_mbscmp(currentPath, absolutePathsArray[0]))
			{
				dialogState->changed = TRUE;
				errChk( SetCtrlVal(dialogState->mainPanel, PANEL_CFG_TEXT_RESULTDIRECTORY, absolutePathsArray[0]) );
			}
		}
	}

Error:

	TS_DisplayError( error, errMsg, dialogState? dialogState->engine : 0 );

	CLEAR(currentPath, free);
	CLEAR(dialogTitle, free);
	CLEAR(okButtonText, free);
	CLEAR(absolutePathsArray, CA_FreeMemory);
	CLEAR(absolutePaths, CA_SafeArrayDestroy);
}
