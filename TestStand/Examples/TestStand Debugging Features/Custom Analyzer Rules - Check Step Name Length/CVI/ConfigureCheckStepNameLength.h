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

#define  RULE_PANEL                       1
#define  RULE_PANEL_MAX_STEP_NAME_LENGTH  2       /* control type: numeric, callback function: (none) */
#define  RULE_PANEL_OK_BUTTON             3       /* control type: command, callback function: ConfigRule_OKCallback */
#define  RULE_PANEL_CANCEL_BUTTON         4       /* control type: command, callback function: ConfigRule_CancelCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK ConfigRule_CancelCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ConfigRule_OKCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
