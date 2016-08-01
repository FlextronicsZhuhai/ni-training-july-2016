/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2014. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1
#define  PANEL_OKBUTTON                   2       /* control type: command, callback function: ClosePanel */
#define  PANEL_NUMERICGAUGE               3       /* control type: scale, callback function: (none) */
#define  PANEL_EXECSTATE                  4       /* control type: ring, callback function: (none) */
#define  PANEL_STATIONOPTION              5       /* control type: radioButton, callback function: (none) */
#define  PANEL_TESTTIMER                  6       /* control type: timer, callback function: GetDataCallback */
#define  PANEL_POLLEXECUTION              7       /* control type: timer, callback function: PollTestStandExecStatus */
#define  PANEL_THREADOPTION               8       /* control type: radioButton, callback function: (none) */
#define  PANEL_TEXTMSG                    9       /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK ClosePanel(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK GetDataCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK PollTestStandExecStatus(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
