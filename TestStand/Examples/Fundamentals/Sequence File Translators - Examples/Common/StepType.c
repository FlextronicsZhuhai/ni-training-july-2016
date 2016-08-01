// This is an example of an example step type implemented in CVI.
// The step type is used by the Sequence File Translator example 
// to demonstrate hoe the translators can be used.
//
// This file compiles to a DLL with three entry points that the example step type calls.
//
// The step type's Configure method lets the user specify the limits for the test and returns 
// a handle to the user which needs to be used in the future operations. 
//
// The step type's ExecuteStep then takes the actual measurements and the handle 
// returned by the Configure method to check whether the measurement is within the
// acceptable range.
//
// The Close method then clears the initial settings on the instrument.
// Refer to the readme.txt file in the project for additional information.
//

#include <cvirte.h>
#include "tsapicvi.h"
#include "tsutil.h"
#include "toolbox.h"        
#include "FrontPanel.h"



#define kUIRFile                    "FrontPanel.uir"    // user interface file that contains the panels for the step type editing dialog

typedef struct
{
	double minACMeasurement, maxACMeasurement;
	
}ConfigurationData;

int closeButtonClicked = 0;
int panelHandle;
double yArray[3];
///////////////////////////////////////////////////////////
__declspec(dllexport) void _stdcall Configure(double minACMeasurement, double maxACMeasurement, int *handle)
{
	ConfigurationData* handlePtr;
	char handleStr[1024] = {0}; 
	if( minACMeasurement > maxACMeasurement)
	{
		minACMeasurement = 0;
		maxACMeasurement = 5;
	}
	
	handlePtr = (ConfigurationData*)malloc(sizeof(ConfigurationData));
	handlePtr->minACMeasurement =  minACMeasurement;
	handlePtr->maxACMeasurement =  maxACMeasurement;
	*handle = (unsigned int)(handlePtr);
	
}
///////////////////////////////////////////////////////////
// This function is called by the edit-substep for the step type. 
__declspec(dllexport) void _stdcall ExecuteStep(int handle, double ACMeasurement, boolean *testPassed, double *RMSValue)
    {
    int             error = 0;
    ERRORINFO       errorInfo;
    ErrMsg          errMsg = "";
	int dlgResult;
    
	ConfigurationData* handlePtr;
	// get the TestStand engine from the sequenceContext. It is needed to get resource strings among other things
    //tsErrChk( TS_SeqContextGetEngine (context, &errorInfo, &dlg.engine));   
    
    // get the step we are editing
    //tsErrChk( TS_SeqContextGetStep (context, &errorInfo, &dlg.step));   
    if (handle != 0)
		handlePtr = (ConfigurationData*)handle;
	else
	{
		handlePtr = (ConfigurationData*)malloc(sizeof(ConfigurationData));
		handlePtr->maxACMeasurement = 5;
		handlePtr->minACMeasurement = 0;
	}
	yArray[0] = handlePtr->maxACMeasurement;
	yArray[1] = ACMeasurement;
	yArray[2] = handlePtr->minACMeasurement;
	
    errChk( panelHandle = LoadPanelEx(0, kUIRFile, PANEL, __CVIUserHInst));  // load the main dialog panel 
	if (ACMeasurement > handlePtr->minACMeasurement &&
		ACMeasurement < handlePtr->maxACMeasurement)
	{
		SetCtrlAttribute(panelHandle, PANEL_TESTPASSED, ATTR_CTRL_VAL, 1);
		SetCtrlAttribute(panelHandle, PANEL_TIMER, ATTR_VISIBLE, 0);
		SetCtrlAttribute(panelHandle, PANEL_MAXACVALUE , ATTR_CTRL_VAL, handlePtr->maxACMeasurement);
		SetCtrlAttribute(panelHandle, PANEL_MINACVALUE, ATTR_CTRL_VAL, handlePtr->minACMeasurement);
		*testPassed =(boolean) 1;
		*RMSValue = ACMeasurement/sqrt(2);
		SetCtrlAttribute(panelHandle, PANEL_RMSVAL, ATTR_CTRL_VAL, *RMSValue);
		
	}
	else
	{
		SetCtrlAttribute(panelHandle, PANEL_TESTPASSED, ATTR_CTRL_VAL, 0);
		SetCtrlAttribute(panelHandle, PANEL_TIMER, ATTR_VISIBLE, 0);
		SetCtrlAttribute(panelHandle, PANEL_MAXACVALUE , ATTR_CTRL_VAL, handlePtr->maxACMeasurement);
		SetCtrlAttribute(panelHandle, PANEL_MINACVALUE, ATTR_CTRL_VAL, handlePtr->minACMeasurement);
		*testPassed = (boolean)0;
	}
	errChk(DisplayPanel(panelHandle));
	errChk( dlgResult = RunUserInterface());
    closeButtonClicked = 0;
	
    
Error:
    
    
    // discard the main panel.  This automatically discards the child panels
	DiscardPanel(panelHandle);
    //TS_EndModalDialogAndDiscard(&errorInfo, &modalData, dlg.mainPanel); 

    // if the error is a CVI UIL or Toolbox error code, convert it to a TestStand error code
    //error = CVIToTestStandError(error, errMsg, sizeof(ErrMsg));
    
    // set step.error.msg, step.error.code, and step.error.occurred
   // if (error < 0)
       // TS_SetStepError (context, error, errMsg); 
   //else    
       // TS_ClearStepError(context);
	return;
    }

////////////////////////////////////////////////////////////
__declspec(dllexport) void _stdcall Close(int handle)
{
	free((void*) handle);
}


int  CVICALLBACK CloseCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	switch(event)
	{
		case EVENT_COMMIT:
			{
				closeButtonClicked = 1;
				// quit the user interface
                QuitUserInterface (0);
				// disable the timer control
                SetCtrlAttribute(panel,PANEL_TIMER,ATTR_ENABLED,0);
				break;	
			}
	}
	return 0;
}
int  CVICALLBACK TimerCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	switch(event)
	{
		case EVENT_TIMER_TICK:
			{
					PlotStripChart(panelHandle, PANEL_STRIPCHART, yArray, 3, 0, 4, VAL_DOUBLE);
					return 0;
					break;
			}
	}
	return 0;
}

main()
{
	boolean testPassed;
	double RMSValue;
	ExecuteStep(0, 2, &testPassed, &RMSValue);
	
}
