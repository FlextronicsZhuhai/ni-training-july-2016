#include "tsapicvi.h"
#include "combobox.h"
#include <formatio.h>
#include <cvirte.h>     
#include <userint.h>
#include "tsutil.h"
#include "JavaCall.h"
#include "combobox.h"

   
// initially defined in combobox.c
#define COMBO_STRING_CALLBACK   "String Data to Ring"


// Helper Funcs
char * GetPropStr (int controlID, CAObjHandle propHandle, int index, char* prop);
char * GetPropStrExp(int controlID, CAObjHandle propHandle, int index, char* prop);
static VBOOL FoundPath(void);
static int TransferValuesToDialog (void);
static int TransferValuesToTestStand (void); 
int GetCallBackData(int panel, int control, comboCallbackData *  callbackData1);

// Structs
typedef struct 
{
    int             panel;
    CAObjHandle     engine;
    CAObjHandle     context;
    char            errMsg[512];
    int             flag; // to take care combo box text data
} JavaConfigDlg;

typedef struct
{
    int     index;
    char    name[512];
    char    type[512];
    char    value[1024];
} JavaMethodArgs;

int             numOfArgs;
ListType        argList;
JavaConfigDlg   configDlg;

int __declspec(dllexport) __stdcall EditCall(CAObjHandle context)
{
    int         error       = 0;
    int         cancelled   = 0;                      
    int         panelHandle = 0;   
    CAObjHandle seqFile     = 0;
    ERRORINFO   errorInfo;
    ErrMsg      errMsg      = "";
    TSModalData modalData = InitialModalData;
    
    // Reset the number of arguments
    numOfArgs = 0;

    // Load the UI panel
    if ((panelHandle = LoadPanelEx (0, "JavaCall.uir", EDITPANEL, __CVIUserHInst)) < 0)
        return -1;

    // Initialize the configDlg properties
    configDlg.context = context;
    configDlg.panel = panelHandle;      
    tsErrChk (TS_SeqContextGetEngine(context, &errorInfo,&(configDlg.engine)));
    
    // Install the custom combobox
    errChk(Combo_NewComboBox (panelHandle, EDITPANEL_METHOD_PARAMS));
    
    // Convert string controls to expression controls
    tsErrChk(TS_ExprCtrl_Create (context, EDITPANEL, EDITPANEL_ENTER_INPUT_ARG, -1,
                        EDITPANEL_BROWSE_FOR_EXPRESSION, 12, NULL,  kTS_ExprCtrl_AllowEmpty));
    
    tsErrChk(TS_ExprCtrl_Create (context, EDITPANEL, EDITPANEL_ENTER_OUTPUT_ARG, -1,
                         EDITPANEL_BROWSE_OUTPUT_EXPRESS , 12, NULL,  kTS_ExprCtrl_AllowEmpty));
 
    // Convert string control to relative path control
    TS_RelativePathCtrl_Create (configDlg.panel, EDITPANEL_CLASS_TO_LOAD,
                                EDITPANEL_FOUND_PATH, context, 0);
    
    // Create the list to be populated in function below
    argList = ListCreate (sizeof(JavaMethodArgs));
    if (argList == 0 )
    {
        strcpy(errMsg, "Cannot allocate Memory");  
        error = -10000;
        goto Error;
    }

    //Transfer JAVA class information to the panel/dialog box
    errChk (TransferValuesToDialog());

    // Start the UI
    tsErrChk (TS_StartModalDialog(configDlg.engine, &errorInfo, &modalData));
    errChk (InstallPopup (configDlg.panel));
    
    // Determine how interface finishes
    errChk (cancelled = RunUserInterface());

    // If user pressed OK, send data to TestStand
    if (!cancelled) 
    {
        errChk(TransferValuesToTestStand());
        
        // Notify sequence file that it has been altered 
        tsErrChk(TS_SeqContextGetSequenceFile (context, &errorInfo, &seqFile));
        tsErrChk(TS_SeqFileIncChangeCount (seqFile, &errorInfo));
    }
    else if(cancelled < 0)
        error = cancelled;

Error:  
    // Discard the panel and end the modal dialog
    if (panelHandle > 0)
        tsErrChk(TS_EndModalDialogAndDiscard (&errorInfo, &modalData, panelHandle));
    if (seqFile)
        CA_DiscardObjHandle (seqFile);
    if (configDlg.engine)
        CA_DiscardObjHandle (configDlg.engine);
    // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
        TS_SetStepError(context, error, errMsg);     
    ListDispose (argList);      
    return error;
}

int CVICALLBACK Java_OkCallback (int panel, int control, int event,
        void *callbackData, int eventData1, int eventData2)
{   
    switch (event)
        {
        case EVENT_COMMIT:
            // Stop running the UI. The panels are taken care of when the execution returns to
            // the EditCall function after QuitUserInterface executes and returns the exit 
            // value.
            QuitUserInterface (0);
            break;
        }
    return 0;
}

int CVICALLBACK Java_CancelCallback (int panel, int control, int event,
        void *callbackData, int eventData1, int eventData2)
{
    switch (event)
        {
        case EVENT_COMMIT:
            // Stop running the UI. The panels are taken care of when the execution returns to
            // the EditCall function after QuitUserInterface executes and returns the exit 
            // value.
            QuitUserInterface (1);
            break;
        }
    return 0;
}

// Callback for Class browser button
int CVICALLBACK Java_Select_Class_to_Load (int panel, int control, int event,
        void *callbackData, int eventData1, int eventData2)
{
    int             error           = 0;
    ERRORINFO       errorInfo;
    ErrMsg          errMsg          = "";
    char            *currPath       = NULL;
    char            *path           = NULL;
    char            *absPath        = NULL;
    VBOOL           pressedOK       = VFALSE;
    VARIANT         seqFileArg;
    LPDISPATCH      seqFileDispatch;
    CAObjHandle     seqFileH        = 0;
    
    switch (event)
        {
        case EVENT_COMMIT:
            errChk(AllocCtrlValString (configDlg.panel, EDITPANEL_CLASS_TO_LOAD, &currPath));
            tsErrChk(TS_SeqContextGetSequenceFile (configDlg.context, &errorInfo, &seqFileH));
            errChk(CA_GetDispatchFromObjHandle (seqFileH, &seqFileDispatch));
            seqFileArg = CA_VariantDispatch(seqFileDispatch);
            
OpenFileDialog:
            // Display the open file dialog
            tsErrChk(TS_EngineDisplayOpenFileDialog (configDlg.engine, &errorInfo,
                                                     "Select File", "OK", currPath, VTRUE,
                                                     &path, &absPath,
                                                     TS_OpenFile_UseRelativePath, "", 4100,
                                                     "Java Class (*.class)|*.class||",
                                                     seqFileArg, &pressedOK));
            if (pressedOK == VTRUE)
            {
                   if(FindPattern (path, 0, -1, ":\\", 0, 0)!= -1)
                   {
                    MessagePopup ("Error", "Class path cannot be absolute \n Please select a relative path");
                    if (path)
                        CA_FreeMemory(path);
                    if (absPath)
                        CA_FreeMemory(absPath);
                    goto OpenFileDialog;
                   }
                tsErrChk(TS_RelativePathCtrl_SetVal (configDlg.panel, EDITPANEL_CLASS_TO_LOAD,path));
            }
            break;
        }
Error:
    if (currPath)
        free (currPath);
    if (path)
        CA_FreeMemory(path);
    if (absPath)
        CA_FreeMemory(absPath);
    if (seqFileH)
        CA_DiscardObjHandle (seqFileH);
    if (error < 0)
        QuitUserInterface (error);
    return 0;
}

// Delete Button functionality
int CVICALLBACK Remove_Arg (int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
    comboCallbackData   callbackData1   = NULL;
    int                 index           = 0;
    int                 error           = 0;
    JavaMethodArgs      curItem;
    switch (event)
        {
        case EVENT_COMMIT:
            errChk(GetCallBackData(configDlg.panel, EDITPANEL_METHOD_PARAMS, &callbackData1));      
            errChk(GetCtrlIndex (configDlg.panel, callbackData1->ring, &index));
            ListGetItem (argList, &curItem, index+1);
            ListRemoveItem (argList, 0, index+1);

            // Update number of args
            numOfArgs--;

            // Remove the item from the combobox
            Combo_DeleteComboItem (configDlg.panel, EDITPANEL_METHOD_PARAMS, index, 1);
            if(numOfArgs!=0)
            {
                if(index!=0)
                    ListGetItem (argList, &curItem, index);
                // If the user selects to delete the first argument then we must display the second in the list
                else
                    ListGetItem (argList, &curItem, index+1);
                    
                errChk(SetCtrlVal(configDlg.panel, EDITPANEL_METHOD_PARAMS,curItem.name));
                // Update remianing controls depending on current combox index after delete
                errChk(SetCtrlVal (configDlg.panel, EDITPANEL_INPUT_DATA_TYPE, curItem.type));
                errChk(TS_ExprCtrl_SetValue (configDlg.panel, EDITPANEL_ENTER_INPUT_ARG, curItem.value));
            }
            // If there are no more arguments then we must dim all the controls so the user cannot select anything
            // unless they hit add again
            else
            {   
                errChk(SetCtrlVal (configDlg.panel, EDITPANEL_METHOD_PARAMS, ""));
                errChk(SetCtrlAttribute (configDlg.panel, callbackData1->ring, ATTR_DIMMED, 1));
                errChk(TS_ExprCtrl_SetDimmed (configDlg.panel, EDITPANEL_ENTER_INPUT_ARG, 1));
                
                errChk(SetCtrlAttribute (configDlg.panel, EDITPANEL_INPUT_DATA_TYPE, ATTR_DIMMED, 1));
                errChk(SetCtrlAttribute (configDlg.panel, EDITPANEL_DELETE_ARG, ATTR_DIMMED, 1));
                errChk(SetCtrlAttribute (configDlg.panel, EDITPANEL_BROWSE_FOR_EXPRESSION, ATTR_DIMMED, 1));
                errChk(SetCtrlAttribute (configDlg.panel, EDITPANEL_METHOD_PARAMS, ATTR_DIMMED, 1));
            }
        }       
Error:
    if (error < 0)
        QuitUserInterface(error);
    return 0;       
}

int CVICALLBACK Create_New_Arg (int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
    JavaMethodArgs      curItem;
    comboCallbackData   callbackData1   = NULL;
    int                 i               = 0;
    int                 numListItems    = 0;
    int                 error           = 0;
    switch (event)
    {
        case EVENT_COMMIT:
            // Set the argument name to nothing (i.e. Blank String)
            strcpy(curItem.name, "");
            // Set the value to nothing
            strcpy(curItem.value, "");
            // Set the argument type to default of int
            strcpy(curItem.type, "I");  
            
            // Clear the all the fields
            errChk(SetCtrlVal(configDlg.panel, EDITPANEL_METHOD_PARAMS, ""));
            errChk(TS_ExprCtrl_SetValue (configDlg.panel, EDITPANEL_ENTER_INPUT_ARG, ""));
            errChk(SetCtrlVal(configDlg.panel, EDITPANEL_INPUT_DATA_TYPE, curItem.type));
        
            // Insert a blank element into the combobox
            Combo_InsertComboItem (configDlg.panel, EDITPANEL_METHOD_PARAMS, numOfArgs, "");
            errChk(GetCallBackData(configDlg.panel, EDITPANEL_METHOD_PARAMS, &callbackData1));      
            errChk(SetCtrlIndex (configDlg.panel, callbackData1->ring, numOfArgs));
            // If the number of args was zero then we must reactivate all of the controls on the panel
            if (numOfArgs == 0)
            {
                errChk(SetCtrlVal (configDlg.panel, EDITPANEL_METHOD_PARAMS, ""));
                errChk(SetCtrlAttribute (configDlg.panel, callbackData1->ring, ATTR_DIMMED, 0));
                errChk(TS_ExprCtrl_SetDimmed (configDlg.panel, EDITPANEL_ENTER_INPUT_ARG, 0));
                errChk(SetCtrlAttribute (configDlg.panel, EDITPANEL_INPUT_DATA_TYPE, ATTR_DIMMED, 0));
                errChk(SetCtrlAttribute (configDlg.panel, EDITPANEL_DELETE_ARG, ATTR_DIMMED, 0));   
                errChk(SetCtrlAttribute (configDlg.panel, EDITPANEL_BROWSE_FOR_EXPRESSION, ATTR_DIMMED, 0));
                errChk(SetCtrlAttribute (configDlg.panel, EDITPANEL_METHOD_PARAMS, ATTR_DIMMED, 0));
            }
            curItem.index = numOfArgs;
            numOfArgs++;
            // Insert the new element in the list
            ListInsertItem (argList, &curItem, END_OF_LIST);
            break;
        }
Error:
    if (error < 0)
        QuitUserInterface(error);
    return 0;      
}

int CVICALLBACK Java_SelectFunction (int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
    int                 index           = 0;
    int                 vKey            = 0;
    int                 error           = 0;
    JavaMethodArgs      curItem;
    comboCallbackData   callbackData1   = NULL;

    switch (event)
    {
        // When the user hits any key we should update the data
        case EVENT_KEYPRESS:
            configDlg.flag = 1;
            break;
            
        // The user is going to change their selection so we must take whatever is in the input box and 
        // write it to the list
        case EVENT_LEFT_CLICK:
            errChk(GetCallBackData(configDlg.panel, EDITPANEL_METHOD_PARAMS, &callbackData1));      
            errChk(GetCtrlIndex (configDlg.panel, callbackData1->ring, &index));

            // Get the argument from the argument list that is at obtained index
            ListGetItem (argList, &curItem, END_OF_LIST);
            
            // Save the new arugment name
            errChk(GetCtrlVal(configDlg.panel, EDITPANEL_METHOD_PARAMS, curItem.name));
                
            Combo_ReplaceComboItem (configDlg.panel, EDITPANEL_METHOD_PARAMS, index, curItem.name);
                
            // Put the new value back in the list
            ListReplaceItem (argList, &curItem, index+1);
            break;

        // The user has changed their selection of the parameter so we must update all controls accordingly
        case EVENT_VAL_CHANGED:
            errChk(GetCallBackData(configDlg.panel, EDITPANEL_METHOD_PARAMS, &callbackData1));      
            if (configDlg.flag != 1)
            {
                // This will be the index of the current selection
                errChk(GetCtrlIndex (configDlg.panel, callbackData1->ring, &index));
            
                // Get the argument from the argument list that is at obtained index
                ListGetItem (argList, &curItem, index+1);
            
                // Set the values of the other fields to show the arguments properties

                errChk(TS_ExprCtrl_SetValue (configDlg.panel, EDITPANEL_ENTER_INPUT_ARG, curItem.value));
                errChk(SetCtrlVal(configDlg.panel, EDITPANEL_INPUT_DATA_TYPE, curItem.type));
            }
            else 
            {
                errChk(GetCtrlIndex (configDlg.panel, callbackData1->ring, &index));

                // Get the argument from the argument list that is at obtained index
                ListGetItem (argList, &curItem, index+1);
            
                // Save the new arugment name
                errChk(GetCtrlVal(configDlg.panel, EDITPANEL_METHOD_PARAMS, curItem.name));
                
                Combo_ReplaceComboItem (configDlg.panel, EDITPANEL_METHOD_PARAMS, index, curItem.name);
                
                // Put the new value back in the list
                ListReplaceItem (argList, &curItem, index+1);
                configDlg.flag = 0;
            }
            break;
    }
Error:

    if (error < 0)
        QuitUserInterface (error);
    return 0;
}

int CVICALLBACK SelectInpDataType (int panel, int control, int event,
        void *callbackData, int eventData1, int eventData2)
{
    int                 index           = -1;
    int                 error           = 0;
    JavaMethodArgs      curItem;
    comboCallbackData   callbackData1   = NULL;
    switch (event)
    {
        case EVENT_VAL_CHANGED:

            // Get the combobox index
            errChk(GetCallBackData(configDlg.panel, EDITPANEL_METHOD_PARAMS, &callbackData1));      
            errChk(GetCtrlIndex (configDlg.panel, callbackData1->ring, &index));
        
            // Obtain and clear the data type from the list of arguments
            ListGetItem (argList, &curItem, index+1);
            
            // Update the data type in the list of arguments
            errChk(GetCtrlVal (configDlg.panel, EDITPANEL_INPUT_DATA_TYPE, curItem.type));
            
            ListReplaceItem (argList, &curItem, index+1);
            break;  
    }
Error:
    if (error < 0)
        QuitUserInterface (error);
    return 0;
}

// If the user enters an expression manually we must update the List 
// This is beyond just launching the expression browser
int CVICALLBACK Java_EnterInputExpression (int panel, int control, int event,
        void *callbackData, int eventData1, int eventData2)
{
    
    int                 index           = -1;
    int                 error           = 0;
    JavaMethodArgs      curItem;
    comboCallbackData   callbackData1   = NULL;
    char            *   newValue        = NULL;
    ERRORINFO           errorInfo;
    ErrMsg              errMsg;
    
    switch (event)
    {
        case EVENT_VAL_CHANGED:
            errChk(GetCallBackData(configDlg.panel, EDITPANEL_METHOD_PARAMS, &callbackData1));      
            errChk(GetCtrlIndex (configDlg.panel, callbackData1->ring, &index));
            ListGetItem (argList, &curItem, index+1);
            errChk(TS_ExprCtrl_GetValue (configDlg.panel, EDITPANEL_ENTER_INPUT_ARG,&newValue));
            strcpy(curItem.value, newValue);
            ListReplaceItem (argList, &curItem, index+1);
            if(newValue)
                free(newValue);
            break;
    }
Error:
    if (error < 0)
        QuitUserInterface (error);
    return 0;
}

// Callback for OutputDataRing Ctrl
int CVICALLBACK OutputRingDataCallback (int panel, int control, int event,
        void *callbackData, int eventData1, int eventData2)
{
    int     Ctrlindex       = 0 ;
    char    itemValue[2]    = "";
    int     error           = 0;
    switch (event)
        {
        case EVENT_VAL_CHANGED:
            // Write the return value parameters back to TestStand Data Type
            GetCtrlIndex (configDlg.panel, EDITPANEL_OUTPUT_DATA_TYPE, &Ctrlindex);
            GetValueFromIndex (configDlg.panel, EDITPANEL_OUTPUT_DATA_TYPE, Ctrlindex, itemValue);
            if (!strcmp(itemValue,"V"))
            {
                errChk(TS_ExprCtrl_SetDimmed (configDlg.panel, EDITPANEL_ENTER_OUTPUT_ARG,1));
                errChk(SetCtrlAttribute (configDlg.panel, EDITPANEL_OUTARGUMENTS_RING,
                                       ATTR_DIMMED, 1));
                errChk(SetCtrlAttribute (configDlg.panel, EDITPANEL_BROWSE_OUTPUT_EXPRESS,
                                       ATTR_DIMMED, 1));
            }
            else
            {
                errChk(TS_ExprCtrl_SetDimmed (configDlg.panel, EDITPANEL_ENTER_OUTPUT_ARG,0));
                errChk(SetCtrlAttribute (configDlg.panel, EDITPANEL_OUTARGUMENTS_RING,
                                       ATTR_DIMMED, 0));
                errChk(SetCtrlAttribute (configDlg.panel, EDITPANEL_BROWSE_OUTPUT_EXPRESS,
                                       ATTR_DIMMED, 0));
            }
        break;
        }
    return 0;
Error:
    return error;
}

int CVICALLBACK Output_Data_ValueChanged (int panel, int control, int event,
        void *callbackData, int eventData1, int eventData2)
{
    int     error           = 0;  
    char    itemValue[2]    = ""; 
    int     Ctrlindex       = -1;
    switch (event)
        {
        case EVENT_VAL_CHANGED:
            
            errChk(GetCtrlIndex (configDlg.panel, EDITPANEL_OUTPUT_DATA_TYPE, &Ctrlindex));
            errChk(GetValueFromIndex (configDlg.panel, EDITPANEL_OUTPUT_DATA_TYPE, Ctrlindex, itemValue));
            if (!strcmp(itemValue,"V"))
            {
                errChk(TS_ExprCtrl_SetDimmed (configDlg.panel, EDITPANEL_ENTER_OUTPUT_ARG,1));
                errChk(SetCtrlAttribute (configDlg.panel, EDITPANEL_OUTARGUMENTS_RING,ATTR_DIMMED, 1));
                errChk(SetCtrlAttribute (configDlg.panel, EDITPANEL_BROWSE_OUTPUT_EXPRESS,ATTR_DIMMED, 1));
            }
            else 
            {
                errChk(TS_ExprCtrl_SetDimmed (configDlg.panel, EDITPANEL_ENTER_OUTPUT_ARG,0));
                errChk(SetCtrlAttribute (configDlg.panel, EDITPANEL_OUTARGUMENTS_RING,ATTR_DIMMED, 0));
                errChk(SetCtrlAttribute (configDlg.panel, EDITPANEL_BROWSE_OUTPUT_EXPRESS,ATTR_DIMMED, 0));
            }
            break;
        }
    return 0;
Error:
    return -1;
}

//  Helper functions
static VBOOL FoundPath (void)
{
    int         error           = 0;
    char        *absPath        = NULL;
    char        *tempPath       = NULL;
    char        string[512]     = "";
    VBOOL       foundFile = 0;
    VBOOL       canceled;
    VARIANT     seqFileArg;
    CAObjHandle seqFileH        = 0;
    LPDISPATCH  seqFileDispatch = 0;
    ERRORINFO   errorInfo;
    ErrMsg      errMsg;

    tempPath = (char*)malloc(sizeof(char)*MAX_PATHNAME_LEN);
    if (tempPath == NULL)
    {
        strcpy(errMsg, "Cannot allocate Memory");  
        error = -10000;
        goto Error;
   }
    
    // Access the current Absolute Path Value note that if absolute path 'not found' 
    // this function will return empty string. 
    tsErrChk(TS_RelativePathCtrl_GetVal (configDlg.panel, EDITPANEL_CLASS_TO_LOAD,
                                         0, tempPath));
                                         
    if(HasNonWhiteSpace (tempPath))
    // If path is not empty
    {                 
        // Get sequence file object from sequence context
        tsErrChk(TS_SeqContextGetSequenceFile (configDlg.context, &errorInfo, &seqFileH));                                         
        // Attempts to locate file using TestStands FindFile method                                
        // Get the sequence file as a IDispatch            
        CA_GetDispatchFromObjHandle (seqFileH, &seqFileDispatch);
        seqFileArg = CA_VariantDispatch(seqFileDispatch);
        tsErrChk( TS_EngineFindFile (configDlg.engine, &errorInfo, tempPath, &absPath,
                                     &canceled, TS_FindFile_PromptDisable,
                                     TS_FindFile_AddDirToSrchList_Ask, VFALSE,
                                     seqFileArg, &foundFile));
    }
    else
        //path is empty
        foundFile = VFALSE;
        
Error:
    if (tempPath)
        free(tempPath);
    if (absPath)
        CA_FreeMemory (absPath);
    if (seqFileH)   
        CA_DiscardObjHandle(seqFileH);
    if (error < 0)
        QuitUserInterface (error);
    return foundFile;   
}


// Send values from CVI back to TestStand objects
static int TransferValuesToTestStand (void)
{
    size_t             numListItems    = 0;
    int             error           = 0;
    int             index           = 0;
    int             Ctrlindex       = 0;
    CAObjHandle     stepH           = 0;
    CAObjHandle     inputArgH       = 0;
    CAObjHandle     outputArgH      = 0;
    CAObjHandle     Express         = 0;
    CAObjHandle     DType           = 0;
    CAObjHandle     Argname         = 0;
    char            tmp[512]        = "";
    char            upperBounds[16] = "";
    char            lowerBounds[16] = "";
    char            itemValue[2]    = "";
    ERRORINFO       errorInfo;
    ErrMsg          errMsg          = "";
    enum            TSEnum_PropertyValueTypes elementType; 
    JavaMethodArgs  curItem;
    
    //Get current step object from sequence context
    tsErrChk( TS_SeqContextGetStep(configDlg.context, &errorInfo,&stepH)); 
    //Gets the InputArguments of the Java step type as a property object
    tsErrChk (TS_PropertyGetPropertyObject (stepH, &errorInfo, "MethodParams", 0, &inputArgH));
                                        
    //Gets the OutputArguments of the Java step type as a property object
    tsErrChk (TS_PropertyGetPropertyObject (stepH, &errorInfo, "ReturnVal", 0, &outputArgH));
        
    tsErrChk(TS_SetPropertyToCtrlValEx (configDlg.panel, EDITPANEL_CLASS_TO_LOAD, stepH, "ClassName", errMsg));
    tsErrChk(TS_SetPropertyToCtrlValEx (configDlg.panel, EDITPANEL_FOUND_PATH, stepH, "ClassPath", errMsg));
    tsErrChk(TS_SetPropertyToCtrlValEx (configDlg.panel, EDITPANEL_JAVA_METHOD, stepH, "MethodName", errMsg));

    // If the List is empty then set the array in TestStand to be empty as well.  This will handle the void case.
    numListItems = ListNumItems (argList);
    
    if ((numListItems) == 0)
    {
        tsErrChk (TS_PropertyGetPropertyObject (stepH, &errorInfo, "MethodParams.Expression", 0, &Express));
        tsErrChk(TS_PropertySetNumElements (Express, &errorInfo, 0, 0));
        tsErrChk (TS_PropertyGetPropertyObject (stepH, &errorInfo, "MethodParams.DataType", 0, &DType));
        tsErrChk(TS_PropertySetNumElements (DType, &errorInfo, 0, 0));
        tsErrChk (TS_PropertyGetPropertyObject (stepH, &errorInfo, "MethodParams.ArgName", 0, &Argname));
        tsErrChk(TS_PropertySetNumElements (Argname, &errorInfo, 0, 0));    
    }
    else
    {   
        Fmt(lowerBounds, "%s%d%s", "[", 0, "]");
        Fmt(upperBounds, "%s%d%s", "[", numListItems-1, "]");
        tsErrChk(TS_PropertySetDimensions (inputArgH, &errorInfo, "Expression", 0, lowerBounds, upperBounds));
        tsErrChk(TS_PropertySetDimensions (inputArgH, &errorInfo, "DataType", 0, lowerBounds, upperBounds));
        tsErrChk(TS_PropertySetDimensions (inputArgH, &errorInfo, "ArgName", 0, lowerBounds, upperBounds));
        
        for (index = 1; index <= numListItems; index ++)
        {
            // Get item to insert from list of arguments.
            ListGetItem (argList, &curItem, index);
            
            // Set the type of the argument
            Fmt(tmp, "%s%d%s", "DataType[", index-1, "]");
            tsErrChk(TS_PropertySetValString (inputArgH, &errorInfo, tmp, 0, curItem.type));
                
            // Set the value of the argument's expression
            Fmt(tmp, "%s%d%s", "Expression[", index-1, "]");
            tsErrChk(TS_PropertySetValString (inputArgH, &errorInfo, tmp, 0, curItem.value));
                
            // Set the name of the argument
            Fmt(tmp, "%s%d%s", "ArgName[", index-1, "]");
            tsErrChk(TS_PropertySetValString (inputArgH, &errorInfo, tmp, 0, curItem.name));
        }
    }

    // Write the return value parameters back to TestStand
    // Data Type
    errChk(GetCtrlIndex (configDlg.panel, EDITPANEL_OUTPUT_DATA_TYPE, &Ctrlindex));
    errChk(GetValueFromIndex (configDlg.panel, EDITPANEL_OUTPUT_DATA_TYPE, Ctrlindex, itemValue));
    tsErrChk(TS_PropertySetValString (outputArgH, &errorInfo, "DataType", 0, itemValue));
    if (itemValue[0] != 'V')
    {
        // Expression
        tsErrChk(TS_SetPropertyToCtrlValEx (configDlg.panel, EDITPANEL_ENTER_OUTPUT_ARG, outputArgH, "Expression", errMsg));
        // Argument Name
        tsErrChk(TS_SetPropertyToCtrlValEx (configDlg.panel, EDITPANEL_OUTARGUMENTS_RING, outputArgH, "ArgName", errMsg));
    }
    else 
    {
        tsErrChk(TS_PropertySetValString (outputArgH, &errorInfo, "Expression", 0, ""));
        tsErrChk(TS_PropertySetValString (outputArgH, &errorInfo, "ArgName", 0, ""));
    }
Error:
    CA_DiscardObjHandle (inputArgH);
    CA_DiscardObjHandle (outputArgH);   
    CA_DiscardObjHandle (stepH);
    CA_DiscardObjHandle (Express);
    CA_DiscardObjHandle (DType);
    CA_DiscardObjHandle (Argname);
    return error;
}

// initialize dialog's control values with TestStand values.
static int TransferValuesToDialog (void)
{
    int                             error       = 0;
    int                             numElements = 0;
    int                             index       = 0;
    int                             Ctrlindex   = 0;
    ERRORINFO                       errorInfo;
    ErrMsg                          errMsg = "";
    CAObjHandle                     stepH       = 0;
    CAObjHandle                     inputArgH   = 0;
    CAObjHandle                     outputArgH  = 0;
    char                        *   funcName    = NULL;
    char                        *   argVal      = NULL;
    char                        *   upperBounds = NULL;
    char                        *   lowerBounds = NULL;
    char                        *   dataType    = NULL;
    char                        *   className   = NULL;
    enum TSEnum_PropertyValueTypes  elementType;
    VBOOL                           found       = FALSE;
    comboCallbackData               callbackData1 = NULL;
    char                            itemvalue[256];


    //Get current step object from sequence context
    tsErrChk(TS_SeqContextGetStep(configDlg.context, &errorInfo, &stepH));
    //Gets the InputArguments of the Java step type as a property object
    tsErrChk (TS_PropertyGetPropertyObject (stepH, &errorInfo, "MethodParams", 0, &inputArgH));
    //Gets the OutputArguments of the Java step type as a property object
    tsErrChk (TS_PropertyGetPropertyObject (stepH, &errorInfo, "ReturnVal", 0, &outputArgH));
    //Transfers values from properties of the VEE step to the CVI user interface controls
    tsErrChk(TS_PropertyGetValString (stepH, &errorInfo, "ClassName", 0, &className));
    TS_RelativePathCtrl_SetVal(configDlg.panel, EDITPANEL_CLASS_TO_LOAD,className);
    
    tsErrChk(TS_PropertyGetValString (stepH, &errorInfo, "MethodName", 0, &funcName));
    errChk(SetCtrlVal (configDlg.panel, EDITPANEL_JAVA_METHOD, funcName));
    tsErrChk(TS_PropertyGetDimensions (inputArgH, &errorInfo, "Expression", 0, &lowerBounds, &upperBounds, &numElements,
                                       &elementType));
    for (index = 0; index < numElements; index ++)
    {
        // Create a new argument structure for each argument 
        JavaMethodArgs curItem;
     
        // Get the type of the argument
        argVal = GetPropStr (EDITPANEL_INPUT_DATA_TYPE, inputArgH,  index, "DataType");
        
        //store value in container
        strcpy (curItem.type, argVal);
        if (argVal)
            CA_FreeMemory (argVal);
        
        // Get the value of the argument's expression
        argVal = GetPropStrExp (EDITPANEL_ENTER_INPUT_ARG, inputArgH,  index, "Expression"); 
        // update expression control internal values by calling 'SetValue'
        TS_ExprCtrl_SetValue (configDlg.panel, EDITPANEL_ENTER_INPUT_ARG, argVal);
        
        // store value in container
        strcpy (curItem.value, argVal);
        if (argVal)
            CA_FreeMemory (argVal); 
        
        // Get the name of the argument
        argVal = GetPropStr (EDITPANEL_METHOD_PARAMS, inputArgH,  index, "ArgName");
        strcpy (curItem.name, argVal);
        
        // Set index and increment argument count
        curItem.index = numOfArgs;
        numOfArgs++;

        // Insert the argument name into the combobox and list of names
        Combo_InsertComboItem (configDlg.panel, EDITPANEL_METHOD_PARAMS, index, argVal);
        ListInsertItem (argList, &curItem, END_OF_LIST);
        if (argVal)
            CA_FreeMemory (argVal);

    }
    //Setting the right index for the ring control
    errChk(GetCallBackData(configDlg.panel, EDITPANEL_METHOD_PARAMS, &callbackData1));      
    
    if (numElements != 0)
        SetCtrlIndex (configDlg.panel, callbackData1->ring, numElements-1);
    else
    {
        // Dim all controls because we have no arguments
        errChk(SetCtrlVal (configDlg.panel, EDITPANEL_METHOD_PARAMS, ""));
        errChk(SetCtrlAttribute (configDlg.panel, callbackData1->ring, ATTR_DIMMED, 1));
        errChk(TS_ExprCtrl_SetDimmed (configDlg.panel, EDITPANEL_ENTER_INPUT_ARG, 1));
        errChk(SetCtrlAttribute (configDlg.panel, EDITPANEL_INPUT_DATA_TYPE, ATTR_DIMMED, 1));
        errChk(SetCtrlAttribute (configDlg.panel, EDITPANEL_DELETE_ARG, ATTR_DIMMED, 1));
        errChk(SetCtrlAttribute (configDlg.panel, EDITPANEL_BROWSE_FOR_EXPRESSION, ATTR_DIMMED, 1));
        errChk(SetCtrlAttribute (configDlg.panel, EDITPANEL_METHOD_PARAMS, ATTR_DIMMED, 1));
    }
    
    //setting output Arg Values to Dialog
    tsErrChk(TS_PropertyGetValString (outputArgH, &errorInfo, "DataType", 0, &dataType));   
    if (strcmp(dataType,"V") && strcmp(dataType, ""))
    {
        errChk(GetIndexFromValue (configDlg.panel, EDITPANEL_OUTPUT_DATA_TYPE, &Ctrlindex, dataType));
        errChk(SetCtrlIndex (configDlg.panel, EDITPANEL_OUTPUT_DATA_TYPE, Ctrlindex));
        
        tsErrChk(TS_SetCtrlToPropertyValEx (outputArgH, "ArgName", configDlg.panel, EDITPANEL_OUTARGUMENTS_RING, errMsg));
        tsErrChk(TS_SetCtrlToPropertyValEx (outputArgH, "Expression", configDlg.panel, EDITPANEL_ENTER_OUTPUT_ARG, errMsg));
    }
    else
    {
        errChk(TS_ExprCtrl_SetDimmed (configDlg.panel, EDITPANEL_ENTER_OUTPUT_ARG,1));
        errChk(SetCtrlAttribute (configDlg.panel, EDITPANEL_OUTARGUMENTS_RING, ATTR_DIMMED, 1));
        errChk(SetCtrlAttribute (configDlg.panel, EDITPANEL_BROWSE_OUTPUT_EXPRESS, ATTR_DIMMED, 1));
    }
    
Error:
    if(className)
        CA_FreeMemory(className);
    if (upperBounds)
        CA_FreeMemory (upperBounds);
    if (lowerBounds)
        CA_FreeMemory (lowerBounds);
    if (funcName)
        CA_FreeMemory (funcName);
    if (dataType)
        CA_FreeMemory (dataType);
    CA_DiscardObjHandle (inputArgH);
    CA_DiscardObjHandle (outputArgH);   
    CA_DiscardObjHandle (stepH);
    return error;
}

// Overloaded setCtrlVal function, retrieves value from TS property object, returns
//it to caller and assigns it to control
char* GetPropStr (int controlID, CAObjHandle propHandle, int index, char* prop) 
{
    char        tmp[512]    = "";
    char    *   argVal      = NULL;
    int         error       = 0;
    ERRORINFO   errorInfo;
    ErrMsg      errMsg      = "";
    
    Fmt(tmp, "%s%s%d%s", prop,"[", index, "]");
    tsErrChk(TS_PropertyGetValString (propHandle, &errorInfo, tmp, 0, &argVal));
    errChk(SetCtrlVal (configDlg.panel, controlID, argVal));
    
Error:
    return argVal;
}

// special function of the above to work for TS expression Edit controls
char * GetPropStrExp(int controlID, CAObjHandle propHandle, int index, char* prop) 
{
    char        tmp[512]    = "";
    char    *   argVal      = NULL;
    int         error       = 0;
    ERRORINFO   errorInfo;
    ErrMsg      errMsg      = "";
    
    Fmt(tmp, "%s%s%d%s", prop,"[", index, "]");
    
    tsErrChk(TS_PropertyGetValString (propHandle, &errorInfo, tmp, 0, &argVal));
    errChk(TS_ExprCtrl_SetValue (configDlg.panel, controlID, argVal));
    
Error:
    return argVal;
}

int CVICALLBACK UpdateList (int panel, int control, int event,void *callbackData, 
                    int eventData1, int eventData2)
{
    comboCallbackData   callbackData1   = NULL;
    int                 index           = 0;
    int                 error           = 0;
    JavaMethodArgs      curItem;
    char            *   Expression      = NULL;
    ERRORINFO           errorInfo;
    ErrMsg              errMsg          = "";
    switch (event)
        {
        case EVENT_COMMIT:
        
            errChk(GetCallBackData(configDlg.panel, EDITPANEL_METHOD_PARAMS, &callbackData1));      
            errChk(GetCtrlIndex (configDlg.panel, callbackData1->ring, &index));
            ListGetItem (argList, &curItem, index+1);
            tsErrChk(TS_ExprCtrl_GetValue (configDlg.panel, EDITPANEL_ENTER_INPUT_ARG,
                                  &Expression));
            strcpy(curItem.value, Expression);
            // Put the new value back in the list
            ListReplaceItem (argList, &curItem, index+1);
Error:
            if(Expression)
                free(Expression);
            break;
        }
    return 0;
}

// This function takes into account the change made between 6.0 and 7.0
// of how to obtain callBackData from the control
int GetCallBackData(int panel, int control, comboCallbackData * callbackData1)
{
    int         error       = 0;  
    
    if(_CVI_ == 600)
        errChk(GetCtrlAttribute (panel, control, ATTR_CALLBACK_DATA, callbackData1));
    if(_CVI_ >= 700)
        errChk(GetChainedCallbackData (panel, control, COMBO_STRING_CALLBACK,(void *)callbackData1));
Error:
    return error;
}
 
