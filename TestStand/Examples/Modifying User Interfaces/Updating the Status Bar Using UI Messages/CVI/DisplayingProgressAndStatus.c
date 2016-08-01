#include "tsutil.h"
#include "stdtst.h"
#include <utility.h>

static int CheckForUserTermination(CAObjHandle execution, int *quit);

void __declspec(dllexport) __stdcall Test(CAObjHandle seqContextCVI,  
    CAObjHandle thread,  short *errorOccurred,  long *errorCode,  char errorMsg[1024])
{
    double      currentTime, startTime, timeLimit = 8;      // in seconds 
    ERRORINFO   errorInfo;
    int         error = 0;
    char        statusMessage[512];
    CAObjHandle execution = 0;
    int         quit = FALSE;
    ErrMsg      errMsg = {'\0'};

        // Get the execution
    tsErrChkMsgPopup(TS_SeqContextGetExecution(seqContextCVI, &errorInfo, &execution));

    startTime = currentTime = Timer();
    while ((currentTime - startTime ) < timeLimit) 
        {
        errChk(CheckForUserTermination(execution, &quit));
        if (quit)
            break;
            
            // Update percent complete progress bar         
        tsErrChk(TS_ThreadPostUIMessage(thread, &errorInfo, TS_UIMsg_ProgressPercent, ((currentTime-startTime) * 100) / timeLimit, "", VTRUE));     
        
            // Display percent finished in Status Bar, in increments of 10   
        sprintf(statusMessage,"%d percent finished", 10 * RoundRealToNearestInteger(((currentTime-startTime) * 10) / timeLimit));
        tsErrChk(TS_ThreadPostUIMessage(thread, &errorInfo, TS_UIMsg_ProgressText, 0, statusMessage, VTRUE));

            // Simulate running test 
        Delay(1);      
        currentTime = Timer();
        }
    
    if (!quit)
        {
            // Display test complete message in the message bar             
        tsErrChk(TS_ThreadPostUIMessage(thread, &errorInfo, TS_UIMsg_ProgressText, 0, "Test Finished", VTRUE));
    
            // Display percent complete progress bar - 100% complete                                                
        tsErrChk(TS_ThreadPostUIMessage(thread, &errorInfo, TS_UIMsg_ProgressPercent, 100, "", VTRUE));
        }

Error:
    CA_DiscardObjHandle(execution);
    
        // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
        {
        *errorOccurred = TRUE;
    
        *errorCode = error;
        strcpy(errorMsg, errMsg);
        }
}

static int CheckForUserTermination(CAObjHandle execution, int *quit)
{
    int error = 0;
    ERRORINFO errorInfo;
    enum TSEnum_ExecutionRunStates runState;
    enum TSEnum_ExecutionTerminationStates termState;
    
    
    tsErrChkMsgPopup(TS_ExecutionGetStates(execution, &errorInfo, &runState, &termState));
    *quit = (termState != TS_ExecTermState_Normal);
    
Error:
    return error;
}
