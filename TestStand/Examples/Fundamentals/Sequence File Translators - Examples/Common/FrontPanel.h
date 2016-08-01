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
#define  PANEL_MAXACVALUE                 2       /* control type: numeric, callback function: (none) */
#define  PANEL_MINACVALUE                 3       /* control type: numeric, callback function: (none) */
#define  PANEL_TESTPASSED                 4       /* control type: LED, callback function: (none) */
#define  PANEL_RMSVAL                     5       /* control type: numeric, callback function: (none) */
#define  PANEL_COMMANDBUTTON              6       /* control type: command, callback function: CloseCB */
#define  PANEL_STRIPCHART                 7       /* control type: strip, callback function: (none) */
#define  PANEL_TIMER                      8       /* control type: timer, callback function: TimerCB */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK CloseCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK TimerCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
