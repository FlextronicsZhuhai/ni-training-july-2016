#include <userint.h>
#include "DisplayPanel.h"
#include "stdtst.h"
#include "tsutil.h"

int panelIndex = 0;

int __declspec(dllexport) StartCounterDialog(CAObjHandle seqContext, char executionName[1024], char CounterVariable[1024])
{
    int panelWidth;
    int panelLeft;
    int error = 0;
    int panelHandle = 0; 
    
    errChk(panelHandle = LoadPanelEx(0, "DisplayPanel.uir", PANEL, __CVIUserHInst));
	
	//tile the panels so all instances are visible
	GetPanelAttribute(panelHandle, ATTR_LEFT, &panelLeft); 
	GetPanelAttribute(panelHandle, ATTR_WIDTH, &panelWidth); 
	SetPanelAttribute(panelHandle, ATTR_LEFT, panelLeft + panelIndex * (panelWidth + 30));
	panelIndex++;  	

	//Close the dialog if the TestStand execution is terminated
	TS_CancelDialogIfExecutionStops(panelHandle, seqContext);
    
	SetCtrlAttribute(panelHandle, PANEL_COUNTER, ATTR_LABEL_TEXT, executionName); 
	SetPanelAttribute(panelHandle, ATTR_TITLE, executionName);
	SetCtrlVal(panelHandle, PANEL_STRING, CounterVariable);

	//install the timer callback so that the sequenceContext is passed in to the callbackData parameter.
	InstallCtrlCallback(panelHandle,PANEL_TIMER, GetCounterValue, (void*)seqContext);

    DisplayPanel(panelHandle);   
    errChk(RunUserInterface());
	
Error:  
	DiscardPanel(panelHandle);
	panelIndex--;
    return error;    
}

int CVICALLBACK GetCounterValue (int panel, int control, int event,
        void *callbackData, int eventData1, int eventData2)
{
    VBOOL stopFlag = 0;
    double timeSinceLastCall = 0;
    double totalTime = 0;
    int error = 0;
    ErrMsg errMsg = {'\0'};
    ERRORINFO errorInfo;
    double counter = 0.0;
    char* TestStandCounterVariable = malloc(sizeof(char)*1024);
	
    switch (event)
        {
        case EVENT_TIMER_TICK:
        
			//get the value of the counter variable using the provided lookup String
			GetCtrlVal(panel, PANEL_STRING, TestStandCounterVariable);
            tsErrChk(TS_PropertyGetValNumber ((CAObjHandle)callbackData, &errorInfo,
                         TestStandCounterVariable, 0,
                         &counter));

            errChk(SetCtrlVal (panel, PANEL_COUNTER, counter));
			GetTimerTickData(&totalTime, &timeSinceLastCall);
			
		    //Check if the Stop flag has been set.  If it has, end the code module
			tsErrChk(TS_PropertyGetValBoolean ((CAObjHandle)callbackData, &errorInfo,
                        "FileGlobals.Stop", 0,
                        &stopFlag));
			if (stopFlag)
			QuitUserInterface(0);
			

            break;
        }
Error:
    
    return error;
}

int CVICALLBACK Stop (int panel, int control, int event,
        void *callbackData, int eventData1, int eventData2)
{
    int error = 0;
    ErrMsg errMsg = {'\0'};
    ERRORINFO errorInfo;

    switch (event)
        {
        case EVENT_COMMIT:
         	QuitUserInterface(0);
        break;
        }
Error:

    return error;
}
