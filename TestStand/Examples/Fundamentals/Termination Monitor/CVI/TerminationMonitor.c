#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "tsutil.h"
#include <stdlib.h>
#include <stdio.h>
#include <utility.h>
#include <formatio.h>
#include <userint.h>
#include <string.h>
#include "TerminationMonitor.h"

void __declspec(dllexport) __stdcall TerminationMonitorExample(CAObjHandle seqContextCVI,char reportText[1024],
	short *errorOccurred, long *errorCode, 
    char errorMsg[1024])
{
	int panelHandle = 0;
	const char uirName[255] = "TerminationMonitor.uir";
	
	//Since this is a DLL being called externally from TestStand, the UIR must be explicitly loaded with LoadPanelEx
	panelHandle = LoadPanelEx(0, uirName, PANEL, __CVIUserHInst);
	
	if(panelHandle < 0)
    {
        *errorOccurred = TRUE;
        *errorCode = panelHandle;
        sprintf(errorMsg,"Error number %d attempting to load panel from %s", panelHandle, uirName);
    }
	
	DisplayPanel(panelHandle);
	
	/*
	This function installs a timer callback for a CVI user interface dialog box.  
	The timer callback monitors the TestStand engine to detect when execution terminates or aborts. 
	If execution stops, the timer callback cancels the dialog box by making the following call:
   	
	QuitUserInterface(EVENT_DLG_DONE_CANCEL);
	
	This function assumes that your program controls the dialog box through a call to RunUserInterface.
	*/
	TS_CancelDialogIfExecutionStops(panelHandle, seqContextCVI);
	
	RunUserInterface();
	
	DiscardPanel(panelHandle);
}

int CVICALLBACK quit (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

    if(event == EVENT_COMMIT)
    {
        QuitUserInterface(0);
    }
    
    return 0;
}
