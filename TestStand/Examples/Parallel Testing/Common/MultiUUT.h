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

#define  CHAMBER                          1       /* callback function: TemperatureChamberPanelCallback */
#define  CHAMBER_THERMOMETER              2       /* control type: scale, callback function: (none) */
#define  CHAMBER_TEMPDISPLAY              3       /* control type: numeric, callback function: (none) */
#define  CHAMBER_TARGET                   4       /* control type: numeric, callback function: (none) */
#define  CHAMBER_DIFFERENCE               5       /* control type: numeric, callback function: (none) */
#define  CHAMBER_TARGETMARKER             6       /* control type: scale, callback function: (none) */
#define  CHAMBER_PICTURERING              7       /* control type: pictRing, callback function: (none) */
#define  CHAMBER_DECORATION               8       /* control type: deco, callback function: (none) */
#define  CHAMBER_DECORATION_2             9       /* control type: deco, callback function: (none) */
#define  CHAMBER_TIMER                    10      /* control type: timer, callback function: ChamberTimerFunction */

#define  PULSE                            2
#define  PULSE_CANVAS                     2       /* control type: canvas, callback function: (none) */
#define  PULSE_GRAPH                      3       /* control type: graph, callback function: (none) */
#define  PULSE_SWITCH_POSITION            4       /* control type: numeric, callback function: (none) */
#define  PULSE_PICTURE                    5       /* control type: picture, callback function: (none) */
#define  PULSE_PICTURE_2                  6       /* control type: picture, callback function: (none) */
#define  PULSE_DECORATION_2               7       /* control type: deco, callback function: (none) */

#define  SWEEP                            3       /* callback function: SweepPanelCallback */
#define  SWEEP_UUTSTRING                  2       /* control type: string, callback function: (none) */
#define  SWEEP_SIGNAL                     3       /* control type: pictRing, callback function: (none) */
#define  SWEEP_NOISE_LEVEL                4       /* control type: scale, callback function: (none) */
#define  SWEEP_WINDOW                     5       /* control type: ring, callback function: (none) */
#define  SWEEP_PEAK_FREQ                  6       /* control type: numeric, callback function: (none) */
#define  SWEEP_POWER_PEAK                 7       /* control type: numeric, callback function: (none) */
#define  SWEEP_DISPLAY                    8       /* control type: ring, callback function: (none) */
#define  SWEEP_SCALING                    9       /* control type: ring, callback function: (none) */
#define  SWEEP_GRAPH1                     10      /* control type: graph, callback function: (none) */
#define  SWEEP_GRAPH2                     11      /* control type: graph, callback function: (none) */
#define  SWEEP_DECORATION                 12      /* control type: deco, callback function: (none) */
#define  SWEEP_DECORATION_2               13      /* control type: deco, callback function: (none) */
#define  SWEEP_DECORATION_4               14      /* control type: deco, callback function: (none) */
#define  SWEEP_DECORATION_5               15      /* control type: deco, callback function: (none) */
#define  SWEEP_TEXTMSG_4                  16      /* control type: textMsg, callback function: (none) */
#define  SWEEP_TEXTMSG_7                  17      /* control type: textMsg, callback function: (none) */
#define  SWEEP_TEXTMSG_6                  18      /* control type: textMsg, callback function: (none) */
#define  SWEEP_TEXTMSG_3                  19      /* control type: textMsg, callback function: (none) */
#define  SWEEP_TIMER                      20      /* control type: timer, callback function: SweepTimerFunction */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK ChamberTimerFunction(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SweepPanelCallback(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SweepTimerFunction(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK TemperatureChamberPanelCallback(int panel, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
