#include <cvirte.h>     
#include <userint.h>
#include "tsutil.h"
#include "tsapicvi.h"
#include "JavaCall.h"

static int panelHandle;

CAObjHandle seqContext;

int __declspec(dllexport) __stdcall EditClassPath(CAObjHandle context)
{
    int         error       = 0;
    int         canceled    = 0;                      
    ERRORINFO   errorInfo;
    ErrMsg      errMsg      = "";
    CAObjHandle stepH       = 0;
    CAObjHandle seqFileH    = 0;
    TSModalData modalData   = InitialModalData;

    // Save the context for later reference
    seqContext = context;
  
    // Load the UI panel
    if ((panelHandle = LoadPanelEx (0, "JavaCall.uir", PANEL, __CVIUserHInst)) < 0)
        return -1;

    // Get current step object from sequence context
    tsErrChk(TS_SeqContextGetStep (context, &errorInfo, &stepH));
    
    // Transfer class path from properties of the Java step to the CVI user interface
    tsErrChk(TS_SetCtrlToPropertyVal (stepH, "ClassPath", panelHandle, PANEL_JAVA_CLASSPATH));

    // Start the UI
    tsErrChk (TS_StartModalDialog(context, &errorInfo, &modalData));
    errChk (InstallPopup (panelHandle));
    errChk (canceled = RunUserInterface());

    if (!canceled) 
    {
        TS_SetPropertyToCtrlValEx (panelHandle, PANEL_JAVA_CLASSPATH, stepH, "ClassPath", errMsg);
        // Update the sequence file change count
        TS_SeqContextGetSequenceFile (context, &errorInfo, &seqFileH);
        tsErrChk(TS_SeqFileIncChangeCount (seqFileH, &errorInfo));
    }

Error:  

    // Discard the panels loaded 
    if (panelHandle > 0)
        TS_EndModalDialogAndDiscard (&errorInfo, &modalData, panelHandle);
    
    if (stepH)
        CA_DiscardObjHandle (stepH);
    if(seqFileH)
        CA_DiscardObjHandle (seqFileH);

    // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
        TS_SetStepError(context, error, errMsg);     
        
    return error;
}


int CVICALLBACK ClassPath_OkCallback (int panel, int control, int event,
        void *callbackData, int eventData1, int eventData2)
{
    switch (event)
        {
        case EVENT_COMMIT:
            QuitUserInterface (0);
            break;
        }
    return 0;
}

int CVICALLBACK ClassPath_CancelCallback (int panel, int control, int event,
        void *callbackData, int eventData1, int eventData2)
{
    switch (event)
        {
        case EVENT_COMMIT:
            QuitUserInterface (1);
            break;
        }
    return 0;
}

int CVICALLBACK Select_ClassPath (int panel, int control, int event,
        void *callbackData, int eventData1, int eventData2)
{
    size_t numelements;
    char **selPaths= NULL;
    VBOOL okPress;
    SAFEARRAY *absPaths= NULL;
    SAFEARRAY *selectedPaths= NULL;
    int stringlenght = 0, i;
    int error = 0;
    ERRORINFO   errorInfo;
    ErrMsg      errMsg = "";
    char * myarray = NULL;
    CAObjHandle engine= 0; 
    
    switch (event)
    {
        
        
        case EVENT_COMMIT:
            tsErrChk(TS_SeqContextGetEngine (seqContext, &errorInfo,&engine));
            tsErrChk(TS_EngineDisplayFileDialog (engine, &errorInfo, "Select Paths", "OK", "C:",
                                        &selectedPaths, &absPaths,
                                        TS_OpenFile_SelectDirectoriesOnly|TS_OpenFile_UseAbsolutePath, "", TS_WinFileDlg_ALLOWMULTISELECT|4096,
                                        "", CA_DEFAULT_VAL, NULL, NULL, &okPress));
                
             if(selectedPaths != NULL)
             {
                CA_SafeArrayTo1DArray (&selectedPaths, CAVT_CSTRING, &selPaths,
                                   &numelements);
                if (okPress) 
                {
                    for(i = 0; i < numelements; i++)
                        stringlenght += strlen(selPaths[i]);
                    myarray = (char*) malloc((stringlenght+numelements+1)*sizeof(char));
                    strcpy(myarray, "");
                    for(i = 0; i < numelements; i++)
                    {
                        strcat(myarray,selPaths[i]);
                        strcat(myarray,";");
                    }
                    
                SetCtrlVal(panelHandle, PANEL_JAVA_CLASSPATH,myarray);
                }
            }
            break;
        }
    
Error:
    if(selectedPaths)
        CA_SafeArrayDestroy(selectedPaths);

    if(absPaths)
        CA_SafeArrayDestroy(absPaths);
    if(selPaths)
        CA_FreeMemory(selPaths);

    if (engine)
        CA_DiscardObjHandle (engine);
        
    if(myarray)
        free(myarray);
        
    if (error < 0)
    {
        TS_SetStepError(seqContext, error, errMsg);     
    }
    return error;
}

