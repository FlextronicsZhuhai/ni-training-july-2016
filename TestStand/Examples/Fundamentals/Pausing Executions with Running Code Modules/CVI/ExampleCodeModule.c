#include <userint.h>
#include "ExampleCodeModule.h"
#include "stdtst.h"
#include "tsutil.h"

void __declspec(dllexport) __stdcall RunTest(CAObjHandle seqContextCVI, int useExternallySuspended, int useStationOption, 
		char reportText[1024], short *errorOccurred, long *errorCode, char errorMsg[1024])
{   	
	VBOOL previousExternallySuspended = VFALSE;
	TSObj_Thread TSThread = 0;
	
	int error = 0;
	ErrMsg errMsg = {'\0'};
	ERRORINFO errorInfo;
 
	
	int hPanel = 0;
	const char uirName[MAX_PATHNAME_LEN] = "ExampleCodeModule.uir";
                       
    hPanel = LoadPanelEx(0, uirName, PANEL, __CVIUserHInst);
    if(hPanel < 0)
    {
        *errorOccurred = TRUE;
        *errorCode = hPanel;
        sprintf(errorMsg,"Error number %d attempting to load panel from %s", hPanel, uirName);
		goto Error;
    }

	//install the timer callback so that the sequenceContext is passed in to the callbackData parameter.
	InstallCtrlCallback(hPanel, PANEL_POLLEXECUTION, PollTestStandExecStatus, (void*)seqContextCVI);
	
	//close the dialog if the TestStand execution is terminated
	TS_CancelDialogIfExecutionStops(hPanel, seqContextCVI);
	
	if(useExternallySuspended)
	{
		tsErrChk(TS_SeqContextGetThread(seqContextCVI, &errorInfo, &TSThread));
		tsErrChk(TS_ThreadGetExternallySuspended(TSThread, &errorInfo, &previousExternallySuspended));
		tsErrChk(TS_ThreadSetExternallySuspended(TSThread, &errorInfo, VTRUE));
	}
	
	SetCtrlVal(hPanel, PANEL_THREADOPTION, useExternallySuspended);
	SetCtrlVal(hPanel, PANEL_STATIONOPTION, useStationOption);
    
	TS_CancelDialogIfExecutionStops(hPanel, seqContextCVI);	
    DisplayPanel(hPanel);
 

	RunUserInterface();
    DiscardPanel(hPanel);
	
	if(useExternallySuspended)
		tsErrChk(TS_ThreadSetExternallySuspended(TSThread, &errorInfo, previousExternallySuspended));

    

Error:

	CA_DiscardObjHandle(TSThread);
	// If an error occurred, set the error flag to cause a run-time error in TestStand.
	if (error < 0)
	{
		*errorOccurred = TRUE;
		*errorCode = error;
		strcpy(errorMsg, errMsg);
	}
}

int CVICALLBACK GetDataCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:
			int isPaused = 0;
			
			GetCtrlVal(panel, PANEL_EXECSTATE, &isPaused) ;
			if(!isPaused)
			{
				double numericVal = 0;
				GetCtrlVal(panel, PANEL_NUMERICGAUGE, &numericVal);
				SetCtrlVal(panel, PANEL_NUMERICGAUGE, (numericVal + .1) - 10 * floor(numericVal / 10));
			}
			break;
	}
	return 0;
}

int CVICALLBACK PollTestStandExecStatus (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int isPaused = 0;
	enum TSEnum_ExecutionTerminationStates execTermState;
	enum TSEnum_ExecutionRunStates execRunState;

	int error = 0;
    ErrMsg errMsg = {'\0'};
    ERRORINFO errorInfo;
			

	
	switch (event)
	{
		case EVENT_TIMER_TICK:
			
			CAObjHandle TSExecution = 0;	
			
			tsErrChk(TS_SeqContextGetExecution((CAObjHandle)callbackData, &errorInfo, &TSExecution));
			tsErrChk(TS_ExecutionGetStates(TSExecution, &errorInfo, &execRunState, &execTermState));
			
			GetCtrlVal(panel, PANEL_EXECSTATE, &isPaused);  
			
			//if state changed to Paused
			if(execRunState == TS_ExecRunState_Paused && !isPaused)
			{
				SetCtrlAttribute(panel, PANEL_NUMERICGAUGE, ATTR_DIMMED, 1);
				SetCtrlVal(panel, PANEL_EXECSTATE, 1);
			}

			//if state changed to running
			else if (execRunState == TS_ExecRunState_Running && isPaused)
			{
				SetCtrlAttribute(panel, PANEL_NUMERICGAUGE, ATTR_DIMMED, 0);
				SetCtrlVal(panel, PANEL_EXECSTATE, 0);
			}
			
			CA_DiscardObjHandle(TSExecution); 
			break;
	}
Error: 	
	return error;
}

int CVICALLBACK ClosePanel (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		QuitUserInterface(0);    
			break;
	}
	return 0;
}
