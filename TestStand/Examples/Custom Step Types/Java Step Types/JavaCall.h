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

#define  EDITPANEL                        1
#define  EDITPANEL_TEXTMSG_3              2       /* control type: textMsg, callback function: (none) */
#define  EDITPANEL_OK                     3       /* control type: command, callback function: Java_OkCallback */
#define  EDITPANEL_CANCEL                 4       /* control type: command, callback function: Java_CancelCallback */
#define  EDITPANEL_CLASS_TO_LOAD          5       /* control type: string, callback function: (none) */
#define  EDITPANEL_FOUND_PATH             6       /* control type: string, callback function: (none) */
#define  EDITPANEL_BROWSE_FOR_Java_LIB    7       /* control type: command, callback function: Java_Select_Class_to_Load */
#define  EDITPANEL_JAVA_METHOD            8       /* control type: string, callback function: (none) */
#define  EDITPANEL_TEXTMSG                9       /* control type: textMsg, callback function: (none) */
#define  EDITPANEL_METHOD_PARAMS          10      /* control type: string, callback function: Java_SelectFunction */
#define  EDITPANEL_NEW_ARG                11      /* control type: command, callback function: Create_New_Arg */
#define  EDITPANEL_INPUT_DATA_TYPE        12      /* control type: ring, callback function: SelectInpDataType */
#define  EDITPANEL_DELETE_ARG             13      /* control type: command, callback function: Remove_Arg */
#define  EDITPANEL_ENTER_INPUT_ARG        14      /* control type: string, callback function: Java_EnterInputExpression */
#define  EDITPANEL_BROWSE_FOR_EXPRESSION  15      /* control type: command, callback function: UpdateList */
#define  EDITPANEL_DECORATION_2           16      /* control type: deco, callback function: (none) */
#define  EDITPANEL_TEXTMSG_2              17      /* control type: textMsg, callback function: (none) */
#define  EDITPANEL_OUTARGUMENTS_RING      18      /* control type: string, callback function: (none) */
#define  EDITPANEL_OUTPUT_DATA_TYPE       19      /* control type: ring, callback function: Output_Data_ValueChanged */
#define  EDITPANEL_ENTER_OUTPUT_ARG       20      /* control type: string, callback function: (none) */
#define  EDITPANEL_BROWSE_OUTPUT_EXPRESS  21      /* control type: command, callback function: (none) */
#define  EDITPANEL_DECORATION_3           22      /* control type: deco, callback function: (none) */
#define  EDITPANEL_DECORATION_4           23      /* control type: deco, callback function: (none) */

#define  PANEL                            2
#define  PANEL_OK                         2       /* control type: command, callback function: ClassPath_OkCallback */
#define  PANEL_CANCEL                     3       /* control type: command, callback function: ClassPath_CancelCallback */
#define  PANEL_BROWSE_FOR_Classpath       4       /* control type: command, callback function: Select_ClassPath */
#define  PANEL_JAVA_CLASSPATH             5       /* control type: string, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK ClassPath_CancelCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ClassPath_OkCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Create_New_Arg(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Java_CancelCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Java_EnterInputExpression(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Java_OkCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Java_Select_Class_to_Load(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Java_SelectFunction(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Output_Data_ValueChanged(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Remove_Arg(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Select_ClassPath(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SelectInpDataType(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK UpdateList(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
