#include <ansi_c.h>
#include <cvirte.h>     /* needed if linking executable in external compiler; harmless otherwise */
#include <userint.h>
#include "multiUUT.h"
#include "tsutil.h" 
#include "toolbox.h"


    // structure to hold information about the CHAMBER panel
typedef struct 
    {
    double  tempDeltaPerTick;    
    double  tempNow;
    double  targetTemp;
    int     numTicks;
    } TempChamberPanelInfo;

/////////////////////////////////////////////

    // Display a panel that simulates changing the temperature in a chamber
int _export _stdcall SetChamberTemperature(CAObjHandle sequenceContext, double tempNow, double targetTemp, double tempChangeTimeInSeconds)
    {
    int                     error = 0;
    int                     panel = 0;
    TempChamberPanelInfo   *panelInfo = NULL;
    double                  interval;
    
    nullChk(panelInfo = calloc(sizeof(TempChamberPanelInfo), 1));

    errChk(panel = LoadPanelEx (0, "multiUUT.uir", CHAMBER, __CVIUserHInst));
        
    SetPanelAttribute(panel, ATTR_CALLBACK_DATA, (void *)panelInfo);
    
    GetCtrlAttribute(panel, CHAMBER_TIMER, ATTR_INTERVAL, &interval);
    
    panelInfo->numTicks = Max(tempChangeTimeInSeconds / interval, 1) + 1;
    panelInfo->tempDeltaPerTick = (targetTemp - tempNow) / panelInfo->numTicks;
    panelInfo->tempNow = tempNow; 
    panelInfo->targetTemp = targetTemp; 
        
    SetCtrlVal(panel, CHAMBER_TARGET, targetTemp);
    SetCtrlVal(panel, CHAMBER_TARGETMARKER, targetTemp);
    
    DisplayPanel (panel);
    TS_CancelDialogIfExecutionStops (panel, sequenceContext);
    
    errChk( RunUserInterface());
    
Error:
    if (panel > 0)
        DiscardPanel(panel);
    
    return error;
    }

/////////////////////////////////////////////

    // on each timer tick, move the temperature towards the setpoint
int CVICALLBACK ChamberTimerFunction(int panel, int control, int event, void *callbackData,
                            int eventData1, int eventData2)
    {
    int                     error = 0;
    TempChamberPanelInfo   *panelInfo;

    GetPanelAttribute(panel, ATTR_CALLBACK_DATA, (void **)&panelInfo);
    
    if (event == EVENT_TIMER_TICK)
        {
        SetCtrlVal(panel, CHAMBER_THERMOMETER, panelInfo->tempNow);
        SetCtrlVal(panel, CHAMBER_TEMPDISPLAY, panelInfo->tempNow);
        SetCtrlVal(panel, CHAMBER_DIFFERENCE, ABS_VAL(panelInfo->targetTemp - panelInfo->tempNow));

        panelInfo->tempNow += panelInfo->tempDeltaPerTick;
        
        if (--panelInfo->numTicks <= 0)
            {   // temperature set correctly, exit panel
            SetCtrlAttribute(panel, control, ATTR_ENABLED, FALSE);
            QuitUserInterface(0);
            }
        }
        
Error:
    if (error < 0)
        QuitUserInterface(error);
            
    return 0;
    }

/////////////////////////////////////////////

    // handle CLOSE and DISCARD for the CHAMBER panel
int CVICALLBACK TemperatureChamberPanelCallback (int panel, int event, void *callbackData,
        int eventData1, int eventData2)
    {
    switch (event)
        {
        case EVENT_CLOSE:
            SetCtrlAttribute(panel, CHAMBER_TIMER, ATTR_ENABLED, FALSE);
            QuitUserInterface(0);
            break;
        case EVENT_DISCARD:
            free(callbackData); // free the panelInfo structure
            break;
        }
        
    return 0;
    }

