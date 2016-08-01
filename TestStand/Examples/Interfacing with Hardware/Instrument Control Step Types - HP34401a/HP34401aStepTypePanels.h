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

#define  MAIN_PANEL                       1
#define  MAIN_PANEL_LOGICAL_NAME          2       /* control type: string, callback function: ChangeCallback */
#define  MAIN_PANEL_LOGICAL_NAME_RING     3       /* control type: ring, callback function: LogicalNameRingCallback */
#define  MAIN_PANEL_OPERATION             4       /* control type: ring, callback function: OperationCallback */
#define  MAIN_PANEL_OKBTN                 5       /* control type: command, callback function: OkCallback */
#define  MAIN_PANEL_CANCELBTN             6       /* control type: command, callback function: CancelCallback */
#define  MAIN_PANEL_TAB                   7       /* control type: tab, callback function: (none) */
#define  MAIN_PANEL_LOGICAL_NAME_LABEL    8       /* control type: textMsg, callback function: (none) */

     /* tab page panel controls */
#define  MEAS_FUNCTION                    2       /* control type: string, callback function: ChangeCallback */
#define  MEAS_FUNCTION_RING               3       /* control type: ring, callback function: (none) */
#define  MEAS_RANGE                       4       /* control type: string, callback function: ChangeCallback */
#define  MEAS_RANGE_RING                  5       /* control type: ring, callback function: (none) */
#define  MEAS_RESOLUTION                  6       /* control type: string, callback function: ChangeCallback */
#define  MEAS_AC_MIN_FREQ                 7       /* control type: string, callback function: ChangeCallback */
#define  MEAS_AC_MAX_FREQ                 8       /* control type: string, callback function: ChangeCallback */
#define  MEAS_AC_MAX_FREQ_LABEL           9       /* control type: textMsg, callback function: (none) */
#define  MEAS_FUNCTION_LABEL              10      /* control type: textMsg, callback function: (none) */
#define  MEAS_RANGE_LABEL                 11      /* control type: textMsg, callback function: (none) */
#define  MEAS_RESOLUTION_LABEL            12      /* control type: textMsg, callback function: (none) */
#define  MEAS_AC_MIN_FREQ_LABEL           13      /* control type: textMsg, callback function: (none) */

     /* tab page panel controls */
#define  READ_READING                     2       /* control type: string, callback function: ChangeCallback */
#define  READ_TIMEOUT                     3       /* control type: string, callback function: ChangeCallback */
#define  READ_TIMEOUT_RING                4       /* control type: ring, callback function: (none) */
#define  READ_READING_LABEL               5       /* control type: textMsg, callback function: (none) */
#define  READ_TIMEOUT_LABEL               6       /* control type: textMsg, callback function: (none) */

     /* tab page panel controls */
#define  SELF_TEST_PASSED                 2       /* control type: string, callback function: ChangeCallback */
#define  SELF_TEST_MESSAGE                3       /* control type: string, callback function: ChangeCallback */
#define  SELF_TEST_PASSED_LABEL           4       /* control type: textMsg, callback function: (none) */
#define  SELF_TEST_MESSAGE_LABEL          5       /* control type: textMsg, callback function: (none) */

     /* tab page panel controls */
#define  SETTINGS_SOURCE                  2       /* control type: string, callback function: SettingsSourceCallback */
#define  SETTINGS_SOURCE_RING             3       /* control type: ring, callback function: (none) */
#define  SETTINGS_SETTINGS_LABEL          4       /* control type: textMsg, callback function: (none) */

     /* tab page panel controls */
#define  TRIGGERING_SOURCE                2       /* control type: string, callback function: ChangeCallback */
#define  TRIGGERING_SOURCE_RING           3       /* control type: ring, callback function: (none) */
#define  TRIGGERING_DELAY                 4       /* control type: string, callback function: ChangeCallback */
#define  TRIGGERING_DELAY_RING            5       /* control type: ring, callback function: (none) */
#define  TRIGGERING_SOURCE_LABEL          6       /* control type: textMsg, callback function: (none) */
#define  TRIGGERING_DELAY_LABEL           7       /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK CancelCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ChangeCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK LogicalNameRingCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OkCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OperationCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SettingsSourceCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
