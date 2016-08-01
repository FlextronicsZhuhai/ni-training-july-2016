// This is an example of an instrumentation step type implemented in CVI.
// The step type controls a HP34401A DMM using its specific IVI driver.
//
// This file compiles to a DLL with two entry points that the example step type calls.
//
// The step type's EditSubstep calls EditHP34401aStep() to display a dialog in which the
// user configures a step.
//
// The step type's PostSubstep calls ExecuteHP34401aStep() to perform the runtime DMM operation 
// that a step instance specifies.
//
// Refer to the readme.txt file in the project for additional information.
//

#include <cvirte.h>
#include "tsapicvi.h"
#include "tsutil.h"
#include <userint.h>
#include "HP34401aStepTypePanels.h"
#include "HP34401aStepType.h"
#include "toolbox.h"        
#include "easytab.h"
#include "sessionmgr.h"
#include "hp34401a.h"


#define kUIRFile                    "HP34401aStepTypePanels.uir"    // user interface file that contains the panels for the step type editing dialog
#define kExprBtnGap                 6                              // number of pixels between string controls and their associated expression browser buttons
#define kResourceStringsCategory    "HP34401_STEP_TYPE_EXAMPLE"     // the section name in Example_HP34401aStepType.ini file from the example loads all user viewable strings

    // We can store our measurement to either a plain TestStand numeric variable or in a TestStand variable of type HP34401aExampleSinglePoint
#define kSinglePoint_TypeName       "HP34401aExampleSinglePoint"    // name of a Custom data type

    // Setting sources must be one of these TestStand datatypes
#define kExampleConfigType          "HP34401aExampleConfig"
#define kExampleSelfTestType        "HP34401aExampleSelfTest"
#define kExampleReadType            "HP34401aExampleRead"


    // The names of step properties that you can edit or view in the dialog

    // step subproperties:
#define kLogicalNamePropertyName            "LogicalName"
#define kOperationPropertyName              "Operation"
#define kSettingsSourcePropertyName         "SettingsSource"
#define kMeasFunctionPropertyName           "MeasFunction"
    // step.configuration subproperties:
#define kRangePropertyName                  "Range"
#define kResolutionPropertyName             "Resolution"
#define kACMinFrequencyPropertyName         "ACMinFreq"
#define kACMaxFrequencyPropertyName         "ACMaxFreq"
#define kTriggerSourcePropertyName          "TriggerSource"
#define kTriggerDelayPropertyName           "TriggerDelay"
    // step.read subproperties:
#define kReadDestinationPropertyName        "Dest"
#define kReadTimeoutPropertyName            "Timeout"
    // step.selfTest subproperties:
#define kSelfTestDestinationPropertyName    "Dest"
#define kSelfTestMsgPropertyName            "Message"
    // step.result subproperties
#define kSinglePointPropertyPath            "Step.Result.SinglePoint"


    // sub-property names of the IviSinglePoint TestStand datatype
#define kIVISinglePoint_MeasurementPropertyName     "Measurement"
#define kIVISinglePoint_MeasurementTypePropertyName "Type"


    // valid values for the operation property 
typedef enum
    {
    kHP34401a_Configure = 0,
    kHP34401a_Read,
    kHP34401a_SelfTest,
    kHP34401a_NumOperations  // number of possible operations
    } HP34401aOperation;


    // Note: This example provides configurable setting source for all operations.  This is just for 
    //       illustration purposes.  You might not want to allow the user to select a configuration source
    //       for operations that have few (or no) settings.
    
    // default setting source for each operation (relative to the sequence context)
char *defaultSettingSources[kHP34401a_NumOperations] = 
    {
    "Step.Configuration",   // defaultSettingSources[kHP34401a_Configure]
    "Step.Read",            // defaultSettingSources[kHP34401a_Read]
    "Step.SelfTest"         // defaultSettingSources[kHP34401a_SelfTest]
    };
    

  // The following property maps make it easier to move values between the 
  // a step instance and the corresponding controls on its editing dialog

    // a mapping of step properties to dialog controls for a panel
PropertyMap gMeasPanelMap = 
    {
	{kMeasFunctionPropertyName,     MEAS_FUNCTION},
    {kRangePropertyName,            MEAS_RANGE},
    {kResolutionPropertyName,       MEAS_RESOLUTION},
    {kACMinFrequencyPropertyName,   MEAS_AC_MIN_FREQ},
    {kACMaxFrequencyPropertyName,   MEAS_AC_MAX_FREQ},
    {0, 0}
    };

    // a mapping of step properties to dialog controls for a panel
PropertyMap gMainPanelMap = 
    {
    {kLogicalNamePropertyName,  MAIN_PANEL_LOGICAL_NAME},
    {kOperationPropertyName,    MAIN_PANEL_OPERATION},
    {0, 0}
    };

    // a mapping of step properties to dialog controls for a panel
PropertyMap gTriggeringPanelMap = 
    {
    {kTriggerSourcePropertyName,    TRIGGERING_SOURCE},
    {kTriggerDelayPropertyName,     TRIGGERING_DELAY},
    {0, 0}
    };

    // a mapping of step properties to dialog controls for a panel
PropertyMap gReadPanelMap = 
    {
    {kReadDestinationPropertyName,  READ_READING},
    {kReadTimeoutPropertyName,      READ_TIMEOUT},
    {0, 0}
    };

    // a mapping of step properties to dialog controls for a panel
PropertyMap gSelfTestPanelMap = 
    {
    {kSelfTestDestinationPropertyName,  SELF_TEST_PASSED},
    {kSelfTestMsgPropertyName,          SELF_TEST_MESSAGE},
    {0, 0}
    };

    // a mapping of step properties to dialog controls for a panel
PropertyMap gSettingsPanelMap = 
    {
    {kSettingsSourcePropertyName,   SETTINGS_SOURCE},
    {0, 0}
    };

    // The following struct represents the editing dialog.  Each panel holds a pointer to this
    // structure in its callback data.  Thus, any dialog callback function can access
    // this shared dialog information
typedef struct 
    {
    CAObjHandle engine;                 // the TestStand engine
    CAObjHandle context;                // the SequenceContext
    CAObjHandle step;                   // the step we are editing
    int         mainPanel;              // the main parent panel for the dialog
    int         measTab;                // child panel for the measurement tab
    int         triggeringTab;          // child panel for the triggering tab
    int         readTab;                // child panel for the read tab
    int         selfTestTab;            // child panel for the self test tab
    int         settingsTab;            // child panel for the settings tab
    int         changed;                // set to TRUE if the user makes a change
    
        // This array of string holds the setting source for each operation.  While in the dialog 
        // we maintain a separate setting source for each operation so the user can the switch between the operation and
        // have the correct setting source for the operation without wiping out the setting source value they might have
        // specified for another operation.  An alternate way to implement this would be to display a separate settings source tab
        // control for each operation
    char    *   settingSources[kHP34401a_NumOperations];  
    } DialogData;


    // possible special values for the operation parameter to ExchangeProperties()
#define kExchangeAllValues              -1


    // helper functions:
static int UpdateTabVisibility(DialogData *dlg);
static int ExchangeProperties(DialogData *dlg, int moveValuesToCtrls, int operation, char *settingSources[], ErrMsg errMsg);
static int UpdateSelectedSettingSource(DialogData *dlg);
static int CreateExpressionControls(DialogData *dlg);
static int InitLogicalNameRing(DialogData *dlg);
static int CheckSettingsSourceType(DialogData *dlg, CAObjHandle source, char *expectedTypeName, ErrMsg errMsg);
    

////////////////////////////////////////////////////////////   

    // This function moves step property values into the dialog controls or vice-versa
    //
    // pass kExchangeAllValues to the operation parameter to exchange all values.  
    // otherwise pass the index of the specify operation to exchange values for 
static int ExchangeProperties(DialogData *dlg, int moveValuesToCtrls, int operation, char *settingSources[], ErrMsg errMsg)
    {
    int         error = 0;
    CAObjHandle configureSettings = 0;
    CAObjHandle readSettings = 0;
    CAObjHandle selfTestSettings = 0;
    
    if (operation == kExchangeAllValues)
        {
            // These values always come from the same step properties no matter what the settingsSource is
        errChk( TS_ExchangePropertyAndCtrlVals(dlg->step, dlg->mainPanel,   gMainPanelMap,      moveValuesToCtrls, errMsg));
        errChk( TS_ExchangePropertyAndCtrlVals(dlg->step, dlg->settingsTab, gSettingsPanelMap,  moveValuesToCtrls, errMsg));

        if (moveValuesToCtrls)
            errChk( UpdateSelectedSettingSource(dlg));
        }

        //////////////////////
        // The source of the remaining values depends on the settingsSource
        
        // For each operation:
        //  1) Evaluate the setting source. Typically at most one source will not be set to its default value of a step sub-property
        //  2) move the values to or from the source


    if (settingSources == NULL) // use the settingSources in the dialog unless we are passed specific setting source to use
        settingSources = dlg->settingSources;

    if (operation == kExchangeAllValues || operation == kHP34401a_Configure)
        {
        errChk ( TS_EvaluateAndGetEx (dlg->engine, dlg->context, settingSources[kHP34401a_Configure], kEvalTypeObject, 0, 
                                    &configureSettings, kResourceStringsCategory, "SETTINGS_SRC_EVAL_ERR", errMsg));

        errChk( CheckSettingsSourceType(dlg, configureSettings, kExampleConfigType, errMsg));
    
        errChk( TS_ExchangePropertyAndCtrlVals(configureSettings, dlg->measTab,         gMeasPanelMap,      moveValuesToCtrls, errMsg));
        errChk( TS_ExchangePropertyAndCtrlVals(configureSettings, dlg->triggeringTab,   gTriggeringPanelMap, moveValuesToCtrls, errMsg));
        }

    if (operation == kExchangeAllValues || operation == kHP34401a_Read)
        {
        errChk ( TS_EvaluateAndGetEx (dlg->engine, dlg->context, settingSources[kHP34401a_Read], kEvalTypeObject, 0,
                                    &readSettings, kResourceStringsCategory, "SETTINGS_SRC_EVAL_ERR", errMsg));
                                    
        errChk( CheckSettingsSourceType(dlg, readSettings, kExampleReadType, errMsg));
        
        errChk( TS_ExchangePropertyAndCtrlVals(readSettings, dlg->readTab, gReadPanelMap, moveValuesToCtrls, errMsg));
        }
        
    if (operation == kExchangeAllValues || operation == kHP34401a_SelfTest)
        {
        errChk ( TS_EvaluateAndGetEx (dlg->engine, dlg->context, settingSources[kHP34401a_SelfTest], kEvalTypeObject, 0,
                                    &selfTestSettings, kResourceStringsCategory, "SETTINGS_SRC_EVAL_ERR", errMsg));
                                    
        errChk( CheckSettingsSourceType(dlg, selfTestSettings, kExampleSelfTestType, errMsg));

        errChk( TS_ExchangePropertyAndCtrlVals(selfTestSettings, dlg->selfTestTab, gSelfTestPanelMap, moveValuesToCtrls, errMsg));
        }
    
Error:
    CA_DiscardObjHandle(configureSettings);
    CA_DiscardObjHandle(readSettings);
    CA_DiscardObjHandle(selfTestSettings);
    return error;
    }
    
/////////////////////////////////////////////////////

    // make sure that the variable or property the user gives us to store the settings is of the appropriate datatype
static int CheckSettingsSourceType(DialogData *dlg, CAObjHandle source, char *expectedTypeName, ErrMsg errMsg)
{
    int                             error = 0;
    ERRORINFO                       errorInfo;
    enum TSEnum_PropertyValueTypes  type;
    char *                          typeName = 0;
    VBOOL                           unusedVBool;
    char *                          msg = 0;
    
    *errMsg = '\0';
    
        // get the data type of the property or variable the user specified to store the settings in    
    tsErrChk( TS_PropertyGetType (source, &errorInfo, "", 0, &unusedVBool, &unusedVBool, &typeName, &type));
    
    if (StrICmp(typeName, expectedTypeName) != 0) // is it the type we expect?
        {
        char    foundMsg[256];

            // get the type mismatch error message
        errChk( TS_AllocResourceString (dlg->engine, kResourceStringsCategory, "WRONG_SETTINGS_TYPE_ERR", "", &msg));
        errChk( TS_GetResourceString (dlg->engine, kResourceStringsCategory, "FOUND", "", sizeof(foundMsg), foundMsg));

        nullChk( AppendString(&msg, expectedTypeName, -1)); // append the type we expected

        if (*typeName)  // if the type found was a named type, add its name to the error message
            {
            nullChk( AppendString(&msg, foundMsg, -1));
            nullChk( AppendString(&msg, typeName, -1));
            }

        nullChk( AppendString(&msg, ".", -1));
        strcpy(errMsg, msg);
        
        errChk( TS_Err_UnexpectedType);
        }
    
Error:
    free(msg);
    CA_FreeMemory(typeName);
    return error;
}
    
////////////////////////////////////////////////////////////

    // fill logical name drop down ring with all names that use the hp34401a driver
static int InitLogicalNameRing(DialogData *dlg)
{
    int         error = 0;
    ERRORINFO   errorInfo;
    CAObjHandle mgr = 0;
    SAFEARRAY   *names = 0; 
    char **     cNames = 0;
    int         index;
    size_t         numElements;
    char        buf[2048];
    
    errChk( SM_NewIInstrSessionMgr (NULL, 1, LOCALE_NEUTRAL, 0, &mgr));
    
    // We query for IVI names spefically.  If we specify emptyString as the query category the session 
    // manager also searches through the VISA names, which can be slow.
    
        // add all IVI names that support this instrument.  You might choose to remove the SMConst_ReturnVirtualInstruments
        // constant so that only logical names appear in the ring
    tsErrChkMsgPopup( SM_IInstrSessionMgrGetNames (mgr, &errorInfo, "IVI", SMConst_ReturnLogicalNames | SMConst_ReturnVirtualInstruments, "SpecificPrefix=HP34401a", &names));
    
    errChk( CA_SafeArrayTo1DArray (&names, CAVT_CSTRING, &cNames, &numElements));  // convert from SAFEARRAY to C array
    
    errChk( ClearListCtrl (dlg->mainPanel, MAIN_PANEL_LOGICAL_NAME_RING));
    
    if (numElements == 0)
        {
        errChk( TS_GetResourceString (dlg->engine, kResourceStringsCategory, "NO_SESSION_AVAILABLE", "", sizeof(buf), buf));
        errChk( InsertListItem (dlg->mainPanel, MAIN_PANEL_LOGICAL_NAME_RING, -1, buf, "\"?\""));
        }
    else    
    for (index = 0; index < numElements; index++)
        {
        sprintf(buf, "\"%s\"", cNames[index]);  // put quotes around the values because they must be string expressions
        errChk( InsertListItem (dlg->mainPanel, MAIN_PANEL_LOGICAL_NAME_RING, -1, cNames[index], buf));
        CA_FreeMemory(cNames[index]);  
        }

Error:
    CA_FreeMemory(cNames);
    CA_SafeArrayDestroy(names);
    CA_DiscardObjHandle(mgr);
    
    return error;
}

////////////////////////////////////////////////////////////

    // create a TSEditCtrl for each control that edits a TestStand expression
static int CreateExpressionControls(DialogData *dlg)
    {
    char *exprButnText = " f(x)";
    int                 error = 0;
    TS_ExprCtrl_Flags   flags = kTS_ExprCtrl_CheckEvaluation;
	
    errChk( TS_ExprCtrl_Create(dlg->context, dlg->mainPanel, MAIN_PANEL_LOGICAL_NAME, MAIN_PANEL_LOGICAL_NAME_RING, 0, kExprBtnGap, exprButnText, flags));

    errChk( TS_ExprCtrl_Create(dlg->context, dlg->measTab, MEAS_FUNCTION, MEAS_FUNCTION_RING, 0, kExprBtnGap, exprButnText, flags));
    errChk( TS_ExprCtrl_Create(dlg->context, dlg->measTab, MEAS_RANGE, MEAS_RANGE_RING, 0, kExprBtnGap, exprButnText, flags));
    errChk( TS_ExprCtrl_Create(dlg->context, dlg->measTab, MEAS_RESOLUTION, -1, 0, kExprBtnGap, exprButnText, flags));
    errChk( TS_ExprCtrl_Create(dlg->context, dlg->measTab, MEAS_AC_MIN_FREQ, -1, 0, kExprBtnGap, exprButnText, flags));
    errChk( TS_ExprCtrl_Create(dlg->context, dlg->measTab, MEAS_AC_MAX_FREQ, -1, 0, kExprBtnGap, exprButnText, flags));

    errChk( TS_ExprCtrl_Create(dlg->context, dlg->readTab, READ_READING, -1, 0, kExprBtnGap, exprButnText, flags));
    errChk( TS_ExprCtrl_Create(dlg->context, dlg->readTab, READ_TIMEOUT, READ_TIMEOUT_RING, 0, kExprBtnGap, exprButnText, flags));

    errChk( TS_ExprCtrl_Create(dlg->context, dlg->triggeringTab, TRIGGERING_SOURCE, TRIGGERING_SOURCE_RING, 0, kExprBtnGap, exprButnText, flags));
    errChk( TS_ExprCtrl_Create(dlg->context, dlg->triggeringTab, TRIGGERING_DELAY, TRIGGERING_DELAY_RING, 0, kExprBtnGap, exprButnText, flags));

    errChk( TS_ExprCtrl_Create(dlg->context, dlg->selfTestTab, SELF_TEST_PASSED, -1, 0, kExprBtnGap, exprButnText, flags | kTS_ExprCtrl_AllowEmpty));
    errChk( TS_ExprCtrl_Create(dlg->context, dlg->selfTestTab, SELF_TEST_MESSAGE, -1, 0, kExprBtnGap, exprButnText, flags | kTS_ExprCtrl_AllowEmpty));

    errChk( TS_ExprCtrl_Create(dlg->context, dlg->settingsTab, SETTINGS_SOURCE, SETTINGS_SOURCE_RING, 0, kExprBtnGap, exprButnText, flags));

Error:
    return error;
    }

////////////////////////////////////////////////////////////

    // This function is called by the edit-substep for the step type. 
__declspec(dllexport) void _stdcall EditHP34401aStep(CAObjHandle context, int readOnly)
    {
    int             error = 0;
    ERRORINFO       errorInfo;
    ErrMsg          errMsg = "";
    DialogData      dlg;
    TSModalData     modalData = InitialModalData;
    int             dlgResult;
    int             index;
    int             oldLabelAdjustmentState = FALSE;

        // setup the dialog structure that all callbacks share via the panel callback data
    memset (&dlg, 0, sizeof(dlg));
    dlg.context = context;
    dlg.changed = FALSE;
    
        // init the default setting source string for each operation that has a setting source
    for (index = 0; index < kHP34401a_NumOperations; index++)
        nullChk( dlg.settingSources[index] = StrDup(defaultSettingSources[index]));

        // get the TestStand engine from the sequenceContext. It is needed to get resource strings among other things
    tsErrChk( TS_SeqContextGetEngine (context, &errorInfo, &dlg.engine));   
    
        // get the step we are editing
    tsErrChk( TS_SeqContextGetStep (context, &errorInfo, &dlg.step));   
   
    
    errChk( GetSystemAttribute (ATTR_DISABLE_LABEL_POSITION_ADJUSTMENT, &oldLabelAdjustmentState));
    errChk( SetSystemAttribute (ATTR_DISABLE_LABEL_POSITION_ADJUSTMENT, TRUE));     // we don't want labels to move just because of font size changes
    errChk( dlg.mainPanel = LoadPanelEx (0, kUIRFile, MAIN_PANEL, __CVIUserHInst));  // load the main dialog panel 
 
        // Load the child panels for each of the tabs on the dialog
    errChk(GetPanelHandleFromTabPage(dlg.mainPanel, MAIN_PANEL_TAB, 0, &(dlg.measTab)));
	errChk(GetPanelHandleFromTabPage(dlg.mainPanel, MAIN_PANEL_TAB, 1, &(dlg.triggeringTab))); 
	errChk(GetPanelHandleFromTabPage(dlg.mainPanel, MAIN_PANEL_TAB, 2, &(dlg.readTab))); 
	errChk(GetPanelHandleFromTabPage(dlg.mainPanel, MAIN_PANEL_TAB, 3, &(dlg.selfTestTab)));
	errChk(GetPanelHandleFromTabPage(dlg.mainPanel, MAIN_PANEL_TAB, 4, &(dlg.settingsTab))); 

    errChk( SetSystemAttribute (ATTR_DISABLE_LABEL_POSITION_ADJUSTMENT, oldLabelAdjustmentState)); // done loading panels, restore attribute
  
        // DialogData holds any information that a dialog callback might need.
    errChk( SetPanelAttribute (dlg.mainPanel,       ATTR_CALLBACK_DATA, &dlg));
    errChk( SetPanelAttribute (dlg.measTab,         ATTR_CALLBACK_DATA, &dlg));
    errChk( SetPanelAttribute (dlg.triggeringTab,   ATTR_CALLBACK_DATA, &dlg));
    errChk( SetPanelAttribute (dlg.readTab,         ATTR_CALLBACK_DATA, &dlg));
    errChk( SetPanelAttribute (dlg.selfTestTab,     ATTR_CALLBACK_DATA, &dlg));
    errChk( SetPanelAttribute (dlg.settingsTab,     ATTR_CALLBACK_DATA, &dlg));
  
        // create expression editing controls
    errChk( CreateExpressionControls(&dlg));
    
        // load control labels and panel titles from the string resource files so they are in the current language
    errChk( TS_LoadPanelResourceStrings(context, 0, dlg.mainPanel, kResourceStringsCategory));
        
		// initialize the logical name ring
    errChk( InitLogicalNameRing(&dlg));
    
        // read the properties from the step we are editing and place them in controls on the dialog
      
		error = ExchangeProperties(&dlg, TRUE, kExchangeAllValues, NULL, errMsg);
    if (error < 0)
        {
        char    title[256];
        
        errChk( TS_GetResourceString (dlg.engine, kResourceStringsCategory, "CANT_LOAD_SETTINGS_ERR_TITLE", "", sizeof(title), title));
        
        MessagePopup(title, errMsg);
        errMsg[0] = '\0';
        error = 0;  // error has been handled
        }
         
        // show/hide appropriate tabs
    errChk( UpdateTabVisibility(&dlg));
  
        // if this dialog is displayed as part of an execution, it should automatically abort if the execution is terminated
    errChk( TS_CancelDialogIfExecutionStops (dlg.mainPanel, context));
    
        // make the edit dialog modal to the application
    tsErrChk( TS_StartModalDialog (dlg.engine, &errorInfo, &modalData));

        // select an initially active control
    errChk( SetActiveCtrl(dlg.mainPanel, MAIN_PANEL_OPERATION));
 
        // display the edit dialog
    errChk( InstallPopup(dlg.mainPanel));
     
        // process user interface events and dispatch control callbacks
    errChk( dlgResult = RunUserInterface());
    
Error:
    SetSystemAttribute (ATTR_DISABLE_LABEL_POSITION_ADJUSTMENT, oldLabelAdjustmentState);
    CA_DiscardObjHandle(dlg.engine);        // we allocated it, we must release it
    CA_DiscardObjHandle(dlg.step);          // we allocated it, we must release it
    
        // free the setting source strings
    for (index = 0; index < kHP34401a_NumOperations; index++)
        free(dlg.settingSources[index]);
    
        // discard the main panel.  This automatically discards the child panels
        // balance the call to TS_StartModalDialog
    TS_EndModalDialogAndDiscard(&errorInfo, &modalData, dlg.mainPanel); 

        // if the error is a CVI UIL or Toolbox error code, convert it to a TestStand error code
    error = CVIToTestStandError(error, errMsg, sizeof(ErrMsg));
    
        // set step.error.msg, step.error.code, and step.error.occurred
    if (error < 0)
        TS_SetStepError (context, error, errMsg); 
    else    
        TS_ClearStepError(context);
    }

////////////////////////////////////////////////////////////

    // callback for the edit dialog's OK button
int CVICALLBACK OkCallback (int panel, int control, int event,
        void *callbackData, int eventData1, int eventData2)
    {
    int         error = 0;
    ERRORINFO   errorInfo;
    DialogData  *dlg;
    int         isOk;
    ErrMsg      errMsg = "";
    int         close = FALSE;

    GetChainedPanelCallbackData(panel, "", (void **)&dlg);
    
    switch (event)
        {
        case EVENT_COMMIT:
                // make sure all expression control have valid values
            tsErrChk( TS_ExprCtrl_CheckAll(&errorInfo, dlg->context, dlg->mainPanel, kTS_CheckChildPanel_Visible, 0, &isOk));
            
            if (!isOk)
                goto Error; // user can't exit dialog with an error
        
            if (dlg->changed)
                {
                int     operation;
                long    flags;
                
                tsErrChk( TS_IncSequenceFileChangeCount(dlg->context, &errorInfo));
            
                    // set the step properties from the values in the dialog controls
                errChk( ExchangeProperties(dlg, FALSE, kExchangeAllValues, NULL, errMsg));
                    
                    // in case any settings sources are no longer in the step, store the same settings to the step 
                    // this is not critical and we don't check for errors
                ExchangeProperties(dlg, FALSE, kExchangeAllValues, defaultSettingSources, errMsg);              

                    // Because the IviSinglePoint data type sets the IncludeInReport flag, we must hide the step.result.singlePoint property 
                    // when we aren't performing a read operation so that step.result.singlePoint does not appear in the report.  
                    // We already hide the step.result.singlePoint.channel sub-property in the step type definition because we don't use it.
                    // The only reason we use the IviSinglePoint dataType for out step.result.singlePoint property is that the default 
                    // database schemas automatically log all instances of this type (among others) in the result tables. This lets us 
                    // get both our measurement and reading type logged with no database schema editing
                GetCtrlVal(dlg->mainPanel, MAIN_PANEL_OPERATION, &operation);   // get selected operation
                
                tsErrChk( TS_PropertyGetFlags (dlg->context, &errorInfo, kSinglePointPropertyPath, 0, &flags));
                
                switch (operation)
                    {
                    case kHP34401a_Configure:
                    case kHP34401a_SelfTest: 
                        tsErrChk( TS_PropertySetFlags (dlg->context, &errorInfo, kSinglePointPropertyPath, 0, flags | TS_PropFlags_Hidden));
                        break;
                    case kHP34401a_Read:
                        tsErrChk( TS_PropertySetFlags (dlg->context, &errorInfo, kSinglePointPropertyPath, 0, flags & ~TS_PropFlags_Hidden));
                        break;
                    }
                }
        
            close = TRUE;
            break;
        }

Error:
    if (error < 0)      // if the setting source is bad, they can still choose to exit the dialog
        {
        char    title[256];
        char    msg[1024];
        char    msgWithError[2048];
    
        errChk( TS_GetResourceString (dlg->engine, kResourceStringsCategory, "CANT_SAVE_SETTINGS_ERR_TITLE", "", sizeof(title), title));
        errChk( TS_GetResourceString (dlg->engine, kResourceStringsCategory, "CANT_SAVE_SETTINGS_ERR", "", sizeof(msg), msg));
    
        sprintf(msgWithError, msg, errMsg);
    
        close = ConfirmPopup(title, msgWithError);
        }

    if (close)
        QuitUserInterface(EVENT_DLG_DONE_OK); // exit the dialog

    return 0;
    }

////////////////////////////////////////////////////////////

    // callback for the edit dialog's Cancel button
int CVICALLBACK CancelCallback (int panel, int control, int event,
        void *callbackData, int eventData1, int eventData2)
    {
    switch (event)
        {
        case EVENT_COMMIT:
            QuitUserInterface(EVENT_DLG_DONE_CANCEL);
            break;
        }
        
    return 0;
    }

////////////////////////////////////////////////////////////

    // Note:    The strings in this function are not language specific on the assumption that 
    //          driver error descriptions are not language specific either
static void GetHP34401aErrMsg(int instrHandle, ErrMsg errMsg)
{   
    int     primaryError;
    int     secondaryError;
    char    elaboration[256] = "";
    char    *errMsgPtr = errMsg;
    int     errBufSize = sizeof(ErrMsg);
    int     result;
    
    *errMsg = '\0';
    
    result = hp34401a_GetErrorInfo (instrHandle, &primaryError, &secondaryError, elaboration);
    
    if (result >= 0) // if we got the error info
        {
        char    primaryErrorBuffer[256] = "";
        char    secondaryErrorBuffer[256] = "";
        
        sprintf(errMsgPtr, "Error: 0x%x", primaryError);
        errMsgPtr += strlen(errMsgPtr);
        
        hp34401a_error_message (instrHandle, primaryError, primaryErrorBuffer);
        if (*primaryErrorBuffer)
            {
            sprintf(errMsgPtr, " '%s'", primaryErrorBuffer);
            errMsgPtr += strlen(errMsgPtr);
            }
            
        if (secondaryError != 0)
            {
            sprintf(errMsgPtr, ", Secondary Error: 0x%x", secondaryError);
            errMsgPtr += strlen(errMsgPtr);
            
            hp34401a_error_message (instrHandle, primaryError, secondaryErrorBuffer);
            if (*secondaryErrorBuffer)
                {
                sprintf(errMsgPtr, " '%s'", secondaryErrorBuffer);
                errMsgPtr += strlen(errMsgPtr);
                }
            }
                
        if (*elaboration)
            {
            sprintf(errMsgPtr, ", Elaboration: '%s'", elaboration);
            errMsgPtr += strlen(errMsgPtr);
            }
        }
    else
        {
        sprintf(errMsgPtr, "Error 0x%x occurred when retrieving error information.", result);
        errMsgPtr += strlen(errMsgPtr);
        }
}

////////////////////////////////////////////////////////////

    // This function is called when a step that is setup to configure the instrument executes.
static int Configure(CAObjHandle context, CAObjHandle engine, CAObjHandle settingSource, int instrHandle, ErrMsg errMsg)
{
    ERRORINFO       errorInfo;
    int             error = 0;
    int             measFunction;
    double          range;
    double          resolution;
    double          ACMinFreq = 0;
    double          ACMaxFreq = 0;
    int             triggerSource;
    double          triggerDelay;
    char *          measFunctionExpr = NULL;
    char *          rangeExpr = NULL;
    char *          resolutionExpr = NULL;
    char *          ACMinFreqExpr = NULL;
    char *          ACMaxFreqExpr = NULL;
    char *          triggerSourceExpr = NULL;
    char *          triggerDelayExpr = NULL;
    int             ACBandwidthNeeded = FALSE;

        // get the expressions for the configuration values from the setting source properties
    tsErrChk( TS_PropertyGetValString (settingSource, &errorInfo, kMeasFunctionPropertyName, 0, &measFunctionExpr));
    tsErrChk( TS_PropertyGetValString (settingSource, &errorInfo, kRangePropertyName, 0, &rangeExpr));
    tsErrChk( TS_PropertyGetValString (settingSource, &errorInfo, kResolutionPropertyName, 0, &resolutionExpr));
    tsErrChk( TS_PropertyGetValString (settingSource, &errorInfo, kTriggerSourcePropertyName, 0, &triggerSourceExpr));
    tsErrChk( TS_PropertyGetValString (settingSource, &errorInfo, kTriggerDelayPropertyName, 0, &triggerDelayExpr));
    
        // evaluate the expressions to get the configuration values
    errChk( TS_EvaluateAndGetEx(engine, context, measFunctionExpr, kEvalTypeIntegerNumber, 0, &measFunction, kResourceStringsCategory, "MEAS_EXPR_ERR", errMsg));
    errChk( TS_EvaluateAndGetEx(engine, context, rangeExpr, kEvalTypeNumber, 0, &range, kResourceStringsCategory, "RANGE_EXPR_ERR", errMsg));
    errChk( TS_EvaluateAndGetEx(engine, context, resolutionExpr, kEvalTypeNumber, 0, &resolution, kResourceStringsCategory, "RESOLUTION_EXPR_ERR", errMsg));
    errChk( TS_EvaluateAndGetEx(engine, context, triggerSourceExpr, kEvalTypeIntegerNumber, 0, &triggerSource, kResourceStringsCategory, "TRIG_SRC_EXPR_ERR", errMsg));
    errChk( TS_EvaluateAndGetEx(engine, context, triggerDelayExpr, kEvalTypeNumber, 0, &triggerDelay, kResourceStringsCategory, "TRIG_DELAY_EXPR_ERR", errMsg));
    
        // only AC measurements require the AC bandwidth to be set
    switch (measFunction)
        {
        case HP34401A_VAL_AC_VOLTS:
        case HP34401A_VAL_AC_CURRENT:
            ACBandwidthNeeded = TRUE;
            break;
         }
         
        // if we need AC bandwidth min and max, get their expressions and evaluate them
    if (ACBandwidthNeeded)
        {
        tsErrChk( TS_PropertyGetValString (settingSource, &errorInfo, kACMinFrequencyPropertyName, 0, &ACMinFreqExpr));
        tsErrChk( TS_PropertyGetValString (settingSource, &errorInfo, kACMaxFrequencyPropertyName, 0, &ACMaxFreqExpr));
        
        errChk( TS_EvaluateAndGetEx(engine, context, ACMinFreqExpr, kEvalTypeNumber, 0, &ACMinFreq, kResourceStringsCategory, "AC_MIN_FREQ_EXPR_ERR", errMsg));
        errChk( TS_EvaluateAndGetEx(engine, context, ACMaxFreqExpr, kEvalTypeNumber, 0, &ACMaxFreq, kResourceStringsCategory, "AC_MAX_FREQ_EXPR_ERR", errMsg));
        }   
    
        // set the measurement function, range, and resolution
    error = hp34401a_ConfigureMeasurement (instrHandle, measFunction, range, resolution);
    if (error < 0)
        {
        GetHP34401aErrMsg(instrHandle, errMsg);
        errChk( error);
        }

        // set the trigger source and delay
    error = hp34401a_ConfigureTrigger (instrHandle, triggerSource, triggerDelay);
    if (error < 0)
        {
        GetHP34401aErrMsg(instrHandle, errMsg);
        errChk( error);
        }
        
        // set the AC bandwidth for AC measurements
    if (ACBandwidthNeeded)
        {
        error = hp34401a_ConfigureACBandwidth (instrHandle, ACMinFreq, ACMaxFreq);
        if (error < 0)
            {
            GetHP34401aErrMsg(instrHandle, errMsg);
            errChk( error);
            }
        }

Error:
    CA_FreeMemory(measFunctionExpr);
    CA_FreeMemory(rangeExpr);
    CA_FreeMemory(resolutionExpr);
    CA_FreeMemory(ACMinFreqExpr);
    CA_FreeMemory(ACMaxFreqExpr);
    CA_FreeMemory(triggerSourceExpr);
    CA_FreeMemory(triggerDelayExpr);
    return error;
}

////////////////////////////////////////////////////////////

    // This function is called when a step that is setup to read from the instrument executes.
static int Read(CAObjHandle context, CAObjHandle engine, CAObjHandle settingSource, int instrHandle, ErrMsg errMsg)
{
    ERRORINFO       errorInfo;
    int             error = 0;
    char *          readDestExpr = NULL;
    char *          readTimeoutExpr = NULL;
    int             readTimeout;
    CAObjHandle     destination = 0;
    CAObjHandle     stepDestination = 0;
    double          reading = Random(0.0, 10.0);    // init to simulation default in case user has an IVI version < 1.1
    VBOOL           unusedVBool;
    enum TSEnum_PropertyValueTypes  type;
    char *          typeName = NULL;
    int             function;
    int             readDestinationIsThisStep;
    
        // get the expressions for the read setting values from the setting source properties
    tsErrChk( TS_PropertyGetValString (settingSource, &errorInfo, kReadDestinationPropertyName, 0, &readDestExpr));
    tsErrChk( TS_PropertyGetValString (settingSource, &errorInfo, kReadTimeoutPropertyName, 0, &readTimeoutExpr));

        // evaluate the expressions to get the read setting values
    errChk( TS_EvaluateAndGetEx(engine, context, readDestExpr, kEvalTypeObject, 0, &destination, kResourceStringsCategory, "READ_DEST_EXPR_ERR", errMsg));
    errChk( TS_EvaluateAndGetEx(engine, context, readTimeoutExpr, kEvalTypeIntegerNumber, 0, &readTimeout, kResourceStringsCategory, "READ_TIMEOUT_EXPR_ERR", errMsg));
    
    readDestinationIsThisStep = StrICmp(readDestExpr, kSinglePointPropertyPath) == 0;
    
        // if we are not storing the data in the step explicitly, get a reference to the Step.Result.SinglePoint property so we can store it there too
    if (!readDestinationIsThisStep)
        tsErrChk( TS_PropertyGetPropertyObject (context, &errorInfo, kSinglePointPropertyPath, 0, &stepDestination));       
    
        // call the instrument to perform a read operation
    error = hp34401a_Read (instrHandle, readTimeout, &reading);
    if (error < 0)
        {
        GetHP34401aErrMsg(instrHandle, errMsg);
        errChk( error);
        }

        // get the measurement type
    error = hp34401a_GetAttributeViInt32 (instrHandle, "", HP34401A_ATTR_FUNCTION, &function);
    if (error < 0)
        {
        GetHP34401aErrMsg(instrHandle, errMsg);
        errChk( error);
        }

        // store the measured value in SinglePoint.Measurement of the step result, if that isn't the destination
    if (!readDestinationIsThisStep)
        tsErrChk( TS_PropertySetValNumber (stepDestination, &errorInfo, kIVISinglePoint_MeasurementPropertyName, 0, reading));
        
        // store the measurement type in SinglePoint.Type of the step result, if that wasn't the destination
    if (!readDestinationIsThisStep)
        tsErrChk( TS_PropertySetValNumber (stepDestination, &errorInfo, kIVISinglePoint_MeasurementTypePropertyName, 0, function));

    
        // get the data type of the property or variable the user specified to store the reading in 
    tsErrChk( TS_PropertyGetType (destination, &errorInfo, "", 0, &unusedVBool, &unusedVBool, &typeName, &type));
    
        // are we storing to an IviSinglePoint datatype?
    if (StrICmp(typeName, kSinglePoint_TypeName) == 0)
        {
            // store the measured value in SinglePoint.Measurement of the destination
        tsErrChk( TS_PropertySetValNumber (destination, &errorInfo, kIVISinglePoint_MeasurementPropertyName, 0, reading));
        
            // store the measurement type in SinglePoint.Type of the destination
        tsErrChk( TS_PropertySetValNumber (destination, &errorInfo, kIVISinglePoint_MeasurementTypePropertyName, 0, function));

        }
    else    // if not an IviSinglePoint, it must be a plain numeric variable
        tsErrChk( TS_PropertySetValNumber (destination, &errorInfo, "", 0, reading));  

Error:
    CA_FreeMemory(readDestExpr);
    CA_FreeMemory(readTimeoutExpr);
    CA_FreeMemory(typeName);
    CA_DiscardObjHandle(destination);
    CA_DiscardObjHandle(stepDestination);
    return error;
}

////////////////////////////////////////////////////////////

    // This function is called when a step that is setup to perform a self test on the instrument executes.
static int SelfTest(CAObjHandle context, CAObjHandle engine, CAObjHandle settingSource, int instrHandle, ErrMsg errMsg)
{
    ERRORINFO       errorInfo;
    int             error = 0;
    char *          selfTestResultExpr = NULL;
    char *          selfTestMsgExpr = NULL;
    char            selfTestMessage[256] = "No error."; // init to simulation default in case user has an IVI version < 1.1
    short           selfTestResult = TRUE;              // init to simulation default in case user has an IVI version < 1.1
    CAObjHandle     resultObj = 0;
    CAObjHandle     msgObj = 0;

        // get the expressions for the self test output expressions from the setting source properties
    tsErrChk( TS_PropertyGetValString (settingSource, &errorInfo, kSelfTestDestinationPropertyName, 0, &selfTestResultExpr));
    tsErrChk( TS_PropertyGetValString (settingSource, &errorInfo, kSelfTestMsgPropertyName, 0, &selfTestMsgExpr));

        // call the instrument to perform a self-test
    error = hp34401a_self_test (instrHandle, &selfTestResult, selfTestMessage);
    if (error < 0)
        {
        GetHP34401aErrMsg(instrHandle, errMsg);
        errChk( error);
        }
        
        // if the user specified a location to store the pass/fail result, store it
    if (*selfTestResultExpr)           
        {
        errChk( TS_EvaluateAndGetEx(engine, context, selfTestResultExpr, kEvalTypeObject, 0, &resultObj, kResourceStringsCategory, "SELF_TEST_RESULT_EXPR_ERR", errMsg));
        error = TS_PropertySetValBoolean (resultObj, &errorInfo, "", 0, (VBOOL)(selfTestResult == 0 ? VTRUE : VFALSE));
        if (error < 0) // insert an elaboration string into errorInfo before jumping to Error:
            {
            TS_InsertResourceStringInBuffer(engine, kResourceStringsCategory, "SELF_TEST_MSG_EXPR_ERR", TRUE, errorInfo.description, sizeof(errorInfo.description));
            tsErrChk( error);
            }
        }

        // if the user specified a location to stored the returned self test message, store it
    if (*selfTestMsgExpr)          
        {
        errChk( TS_EvaluateAndGetEx(engine, context, selfTestMsgExpr, kEvalTypeObject, 0, &msgObj, kResourceStringsCategory, "SELF_TEST_MSG_EXPR_ERR", errMsg));
        error = TS_PropertySetValString (msgObj, &errorInfo, "", 0, selfTestMessage);
        if (error < 0) // insert an elaboration string into errorInfo before jumping to Error:
            {
            TS_InsertResourceStringInBuffer(engine, kResourceStringsCategory, "SELF_TEST_MSG_EXPR_ERR", TRUE, errorInfo.description, sizeof(errorInfo.description));
            tsErrChk( error);
            }
        }

Error:
    CA_FreeMemory(selfTestResultExpr);
    CA_FreeMemory(selfTestMsgExpr);
    CA_DiscardObjHandle(resultObj);
    CA_DiscardObjHandle(msgObj);
    return error;
}

////////////////////////////////////////////////////////////

    // The step type PostSubstep calls this function when the step executes.  This function examines
    // the steps properties to determine the action to perform and the settings to apply. 
__declspec(dllexport) void _stdcall ExecuteHP34401aStep(CAObjHandle context)
{
    ERRORINFO       errorInfo;
    ErrMsg          errMsg = "";
    int             error = 0;
    double          operation;
    CAObjHandle     settingSource = 0;
    CAObjHandle     step = 0;
    CAObjHandle     session = 0;
    CAObjHandle     engine = 0;
    int          	instrHandle;
    char *          settingSourceExpr = 0;
    char *          logicalNameExpr = 0;
    char *          logicalName = 0;
    char            sessionPropName[2048];
    VARIANT 		vtHandle = CA_DefaultValueVariant();  
	
        // get the TestStand engine from the sequenceContext. It is needed to get resource strings among other things
    tsErrChk( TS_SeqContextGetEngine (context, &errorInfo, &engine));   

        // get the step we are executing
    tsErrChk( TS_SeqContextGetStep (context, &errorInfo, &step));   

        // get the operation to execute
    tsErrChk( TS_PropertyGetValNumber (step, &errorInfo, kOperationPropertyName, 0, &operation));
    
        // get the expression for the setting source
    tsErrChk( TS_PropertyGetValString (step, &errorInfo, kSettingsSourcePropertyName, 0, &settingSourceExpr));
    
        // evaluate the expression to get the property object that holds the settings
    errChk( TS_EvaluateAndGetEx(engine, context, settingSourceExpr, kEvalTypeObject, 0, &settingSource, kResourceStringsCategory, "SETTINGS_SRC_EVAL_ERR", errMsg));

        // get the expression for the logical name source
    tsErrChk( TS_PropertyGetValString (step, &errorInfo, kLogicalNamePropertyName, 0, &logicalNameExpr));

        // evaluate the expression to get the logical name
    errChk( TS_EvaluateAndGetEx(engine, context, logicalNameExpr, kEvalTypeString, 0, &logicalName, kResourceStringsCategory, "LOGICAL_NAME_EXPR_ERR", errMsg));
    
        // get the instrument session from the session manager. using the session manager helps us to 
        // share instrument handles with other components and helps to prevent unnecessary re-initilizations
        // of the instrument
    tsErrChk( SM_GetSession(logicalName, &session, &errorInfo));
    
        // Attach a reference to the session to the current TestStand execution object.  Thus, the session will exist for the 
        // life of the execution and the instrument will not be re-initialized each time the instrument handle is requested for
        // from session during the execution.  If the reference already exists, it is harmlessly over-written with the same value.
    sprintf(sessionPropName,  "RunState.Execution.HP34401A_session_named_%s", logicalName);
    tsErrChk( TS_PropertySetValIDispatch (context, &errorInfo, sessionPropName, TS_PropOption_InsertIfMissing, session));
    
        // Ask the session for the instrument handle.  We do not close the instrument handle.  The session closes
        // it when the last reference to the session is disposed.
    tsErrChk( SM_GetHandleEx(session, "", SMConst_SpecificDriver, &vtHandle, &errorInfo));
	CA_VariantGetLong(&vtHandle, &instrHandle);
    
        // execute the operation
    switch ((int)operation)
        {
        case kHP34401a_Configure:
            errChk( Configure(context, engine, settingSource, instrHandle, errMsg));
            break;
        case kHP34401a_Read:
            errChk( Read(context, engine, settingSource, instrHandle, errMsg));
            break;      
        case kHP34401a_SelfTest:
            errChk( SelfTest(context, engine, settingSource, instrHandle, errMsg));
            break;
        }
    
Error:
    CA_FreeMemory(logicalNameExpr);
    CA_FreeMemory(logicalName);
    CA_FreeMemory(settingSourceExpr);
    SM_ReleaseSession(session);
    CA_DiscardObjHandle(settingSource);
    CA_DiscardObjHandle(step);
    CA_DiscardObjHandle(engine);
    
        // if the error is a CVI UIL or Toolbox error code, convert it to a TestStand error code
    error = CVIToTestStandError(error, errMsg, sizeof(ErrMsg));
    
    if (error < 0)
        TS_SetStepError (context, error, errMsg); // set step.error.msg, step.error.code, and step.error.occurred
}

////////////////////////////////////////////////////////////

    // Determine the selected operation and show and hide dialog tabs accordingly
static int UpdateTabVisibility(DialogData *dlg)
{
    int error = 0;
    int operation;
    int showMeas = FALSE;
    int showRead = FALSE;
    int showTrigger = FALSE;
    int showSelfTest = FALSE;
    int tabToActivate = 0;
    
    errChk( GetCtrlVal(dlg->mainPanel, MAIN_PANEL_OPERATION, &operation));
    
    switch (operation)
        {
        case kHP34401a_Configure: 
            showMeas = TRUE;
            showTrigger = TRUE;
            tabToActivate = 0;
            break;
        case kHP34401a_Read: 
            showRead = TRUE;
            tabToActivate = 2;
            break;
        case kHP34401a_SelfTest:
            showSelfTest = TRUE;
            tabToActivate = 3;
            break;
        }
	
	
	//set in reverse because the tab index is for visible tabs only	
	errChk( SetTabPageAttribute(dlg->mainPanel, MAIN_PANEL_TAB, 3, ATTR_VISIBLE, showSelfTest));    
	errChk( SetTabPageAttribute(dlg->mainPanel, MAIN_PANEL_TAB, 2, ATTR_VISIBLE, showRead)); 	
	errChk( SetTabPageAttribute(dlg->mainPanel, MAIN_PANEL_TAB, 1, ATTR_VISIBLE, showTrigger));  
    errChk( SetTabPageAttribute(dlg->mainPanel, MAIN_PANEL_TAB, 0, ATTR_VISIBLE, showMeas));
	
	errChk( SetActiveTabPage(dlg->mainPanel, MAIN_PANEL_TAB, tabToActivate));

Error:
    return error;
}

////////////////////////////////////////////////////////////

    // Callback for the operation control on the editing dialog
int CVICALLBACK OperationCallback (int panel, int control, int event,
        void *callbackData, int eventData1, int eventData2)
{
    int         error = 0;
    DialogData  *dlg;
    int         operation;
    
    GetChainedPanelCallbackData(panel, "", (void **)&dlg);

    switch (event)
        {
        case EVENT_COMMIT:
            dlg->changed = TRUE;
            UpdateTabVisibility(dlg);   // the operation changed, show and hide the appropriate tabs

            GetCtrlVal(dlg->mainPanel, MAIN_PANEL_OPERATION, &operation);   // get selected operation

                // restore the settingSource value for the new operation
            errChk( TS_ExprCtrl_SetValue (dlg->settingsTab, SETTINGS_SOURCE, dlg->settingSources[operation]));
            break;
        }

Error:      
    if (error < 0) 
        QuitUserInterface(error); // report error from callback
        
    return 0;
}

////////////////////////////////////////////////////////////

    // This function is the callback for all editing dialog controls that do not have a specific callback.
    // It marks the dialog as having made a change if the user changes a control value
int CVICALLBACK ChangeCallback (int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
    int         error = 0;
    DialogData  *dlg = 0;
    
    errChk(GetChainedPanelCallbackData(panel, "", (void **)&dlg));
    
    switch (event)
        {
        case EVENT_VAL_CHANGED:
            if (dlg)
                dlg->changed = TRUE;
            break;
        }
        
Error:
    if (error < 0) 
        QuitUserInterface(error); // report error from callback

    return 0;
}

////////////////////////////////////////////////////////////

    // This function is the callback for the setting source control on the editing dialog.
int CVICALLBACK SettingsSourceCallback (int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
    int         error = 0;
    DialogData  *dlg;
    char        title[256];
    char        message[1024];
    
    GetChainedPanelCallbackData(panel, "", (void **)&dlg);

    switch (event)
        {
        case EVENT_VAL_CHANGED:
            dlg->changed = TRUE;
            errChk( UpdateSelectedSettingSource(dlg));
            break;
        case EVENT_COMMIT:
            errChk( TS_GetResourceString (dlg->engine, kResourceStringsCategory, "RELOAD_SETTINGS_TITLE", "", sizeof(title), title));
            errChk( TS_GetResourceString (dlg->engine, kResourceStringsCategory, "RELOAD_SETTINGS_PROMPT", "", sizeof(message), message));
            
                // The user just changed the settingSource.  Ask if they want to reload the dialog control
                // values from their new source of settings
            if (ConfirmPopup (title, message) == 1)
                {
                int     operation;
                ErrMsg  errMsg = "";
                
                GetCtrlVal(dlg->mainPanel, MAIN_PANEL_OPERATION, &operation);   // get selected operation
                error = ExchangeProperties(dlg, TRUE, operation, NULL, errMsg);
                
                if (error < 0)
                    {
//                    EasyTab_SetAttribute (dlg->mainPanel, MAIN_PANEL_TAB_CANVAS, ATTR_EASY_TAB_ACTIVE_PANEL, panel);
                    SetActiveCtrl(panel, control);
                    
                    errChk( TS_GetResourceString (dlg->engine, kResourceStringsCategory, "CANT_LOAD_SETTINGS_ERR_TITLE", "", sizeof(title), title));
                    MessagePopup(title, errMsg);
                    error = 0;  // non-fatal error
                    }
                }
            break;
        }

Error:      
    if (error < 0) 
        QuitUserInterface(error); // report error from callback

    return 0;
}

////////////////////////////////////////////////////////////

    // Get the value of settingsSource from the control and store it in our
    // array of setting sources so we can remember it if the user goes to another operation and 
    // then comes back to this operation
static int UpdateSelectedSettingSource(DialogData *dlg)
{
    int     error = 0;
    char *  settingsSource = NULL;
    int     operation;
    
    errChk( TS_ExprCtrl_GetValue (dlg->settingsTab, SETTINGS_SOURCE, &settingsSource));
    GetCtrlVal(dlg->mainPanel, MAIN_PANEL_OPERATION, &operation);   // get selected operation
    free(dlg->settingSources[operation]);                           // dispose the current value for that operation
    dlg->settingSources[operation] = settingsSource;                // store the new value
    settingsSource = NULL;

Error:
    free(settingsSource);
    return error;
}

////////////////////////////////////////////////////////////

int CVICALLBACK LogicalNameRingCallback (int panel, int control, int event,
        void *callbackData, int eventData1, int eventData2)
{
    int         error = 0;
    DialogData  *dlg;
    
    GetChainedPanelCallbackData(panel, "", (void **)&dlg);
    
    switch (event)
        {
        case EVENT_KEYPRESS:
        case EVENT_LEFT_CLICK:
                // when the user activates the logical name drop down ring, update the name list in case user changed the configuration files while the dialog is up
            errChk( InitLogicalNameRing(dlg));
            break;
        case EVENT_VAL_CHANGED:
            dlg->changed = TRUE;
            break;
        }

Error:
    if (error < 0) 
        QuitUserInterface(error); // report error from callback

    return 0;
}

////////////////////////////////////////////////////////////

int __stdcall DllMain (HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
        {
        case DLL_PROCESS_ATTACH:
            if (InitCVIRTE (hinstDLL, 0, 0) == 0)
                return 0;     /* out of memory */
            break;
        case DLL_PROCESS_DETACH:
            CloseCVIRTE ();
            break;
        }
    
    return 1;
}

////////////////////////////////////////////////////////////

int __stdcall DllEntryPoint (HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    /* Included for compatibility with Borland */
    return DllMain (hinstDLL, fdwReason, lpvReserved);
}
