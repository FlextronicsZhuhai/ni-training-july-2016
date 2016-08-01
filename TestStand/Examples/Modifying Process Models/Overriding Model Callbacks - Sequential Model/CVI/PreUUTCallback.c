#include "stdtst.h"
#include "tsutil.h"
#include "toolbox.h"
#include <userint.h>
#include "PreUUTCallback.h"


#define GET_SERIAL_NUMBER       0
#define FOUND_SERIAL_NUMBER     1
#define DATABASE_LOOKUP         2
#define FOUND_IN_DATABASE       3
#define GET_LIMITS              4
#define FOUND_LIMITS            5   
#define QUIT                    100


int __declspec(dllexport) __cdecl IdentifyUUT(CAObjHandle context, char SerialNumber[1024])
{
    int             error=0;
    int             result=0;
    int             panel;
    
    *SerialNumber = '\0';
    errChk( panel = LoadPanelEx (0, "PreUUTCallback.uir", PANEL, __CVIUserHInst));
        // Initialize Panel
    errChk( SetCtrlAttribute (panel, PANEL_NUMERICSLIDE, ATTR_VISIBLE, 0));
    errChk( SetCtrlAttribute (panel, PANEL_SERIALNUMBERSTRING, ATTR_VISIBLE, 0));
    errChk( SetCtrlVal (panel, PANEL_STRING, "Scan serial number and part number"));
    errChk( InstallPopup(panel));   // Display panel and wait for input 
    
        // Check for Terminate or Abort Execution from TestStand
    errChk( TS_CancelDialogIfExecutionStops(panel, context)); 
    errChk( result = RunUserInterface());
    
    if (result == EVENT_DLG_DONE_OK)  // Did the user hit the Stop Testing button?
        GetCtrlVal (panel, PANEL_SERIALNUMBERSTRING, SerialNumber);
    
    
Error:  
    if (panel > 0)
        DiscardPanel(panel);

    if (error < 0)
        return error;
    else
        return result;
}    

////////////////////////////////////////////////////////////////////////////////
// 
// This function is called by the Timer Control on the panel
// This is function is a state machine where "operation" holds the next state to execute
//
int CVICALLBACK TimerCallback (int panel, int control, int event,
    void *callbackData, int eventData1, int eventData2)
{
        
    char        serialNumber[1024];
    static int  percentComplete = 0; // progress status bar
    static int  operation = FOUND_SERIAL_NUMBER; // Holds next state of state machine
    char        messageString[256]; // string that is displayed on panel

    switch (event) {
        case EVENT_TIMER_TICK:
            switch (operation) {
                case GET_SERIAL_NUMBER:
                    operation = FOUND_SERIAL_NUMBER; // set next state of state machine
                    break;

                case FOUND_SERIAL_NUMBER:
                    srand(clock());
                    sprintf(serialNumber, "%d", rand());
                    sprintf(messageString,"Found serial number %s",serialNumber);
                    SetCtrlAttribute (panel, PANEL_SERIALNUMBERSTRING, ATTR_VISIBLE, 1);
                    SetCtrlVal (panel, PANEL_SERIALNUMBERSTRING, serialNumber); 
                    SetCtrlVal (panel, PANEL_STRING, messageString);
                    operation = DATABASE_LOOKUP; // set next state of state machine
                    break;
                    
                case DATABASE_LOOKUP:
                    percentComplete += 20;
                    SetCtrlAttribute (panel, PANEL_NUMERICSLIDE, ATTR_VISIBLE, 1);
                    sprintf (messageString, "Database Lookup - %d Percent Complete", percentComplete);                                 
                    SetCtrlVal (panel, PANEL_STRING, messageString);
                    SetCtrlVal (panel, PANEL_NUMERICSLIDE, percentComplete);
                    if (percentComplete >= 100) {
                        percentComplete = 0;
                        operation = FOUND_IN_DATABASE; // set next state of state machine
                    }
                    break;
                    
                case FOUND_IN_DATABASE:
                    SetCtrlAttribute (panel, PANEL_NUMERICSLIDE, ATTR_VISIBLE, 0);
                    SetCtrlVal (panel, PANEL_STRING, "Found part number in database");
                    operation = GET_LIMITS; // set next state of state machine
                    break;
                    
                case GET_LIMITS:
                    percentComplete += 40;
                    if (percentComplete > 100)
                        percentComplete = 100;
                    SetCtrlAttribute (panel, PANEL_NUMERICSLIDE, ATTR_VISIBLE, 1);
                    sprintf (messageString, "Loading limits - %d Percent Complete", percentComplete);                                  
                    SetCtrlVal (panel, PANEL_STRING, messageString);
                    SetCtrlVal (panel, PANEL_NUMERICSLIDE, percentComplete);
                    if (percentComplete >= 100) {
                        percentComplete = 0;
                        operation = FOUND_LIMITS; // set next state of state machine
                    }
                    break;
                    
                case FOUND_LIMITS:
                    SetCtrlAttribute (panel, PANEL_NUMERICSLIDE, ATTR_VISIBLE, 0);
                    SetCtrlVal (panel, PANEL_STRING, "Loaded limits");
                    operation = QUIT; // set next state of state machine
                    break;
                    
                    
                case QUIT:
                    operation = GET_SERIAL_NUMBER; // reset next state of state machine to beginning
                    QuitUserInterface (EVENT_DLG_DONE_OK);
                    break;
            }

            break;
    }
    return 0;
}

int CVICALLBACK Cancel (int panel, int control, int event,
    void *callbackData, int eventData1, int eventData2)
{
    switch (event) {
        case EVENT_COMMIT:
            QuitUserInterface (EVENT_DLG_DONE_CANCEL);
            break;
    }       
    return 0;
}
