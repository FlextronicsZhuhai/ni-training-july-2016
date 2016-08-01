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

#define  MAINPANEL                        1       /* callback function: MainPanelCallback */
#define  MAINPANEL_APPLICATIONMGR         2       /* control type: activeX, callback function: (none) */
#define  MAINPANEL_SEQUENCEFILEVIEWMGR    3       /* control type: activeX, callback function: (none) */
#define  MAINPANEL_CUR_SEQ_FILE_TEXTBOX   4       /* control type: string, callback function: (none) */
#define  MAINPANEL_EXECUTE_BTN            5       /* control type: command, callback function: ExecuteCallback */
#define  MAINPANEL_OPEN_SEQ_FILE_BTN      6       /* control type: command, callback function: OpenSequenceFileCallback */
#define  MAINPANEL_TABLE                  7       /* control type: table, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK ExecuteCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MainPanelCallback(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OpenSequenceFileCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
