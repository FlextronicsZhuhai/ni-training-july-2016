/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL_CFG                        1
#define  PANEL_CFG_TEXT_RESULTDIRECTORY   2       /* callback function: CbMarkChanged */
#define  PANEL_CFG_BUTTON_BROWSE          3       /* callback function: CbBrowse */
#define  PANEL_CFG_CHECKBOX_ON_THE_FLY    4       /* callback function: CbMarkChanged */
#define  PANEL_CFG_BUTTON_HELP            5       /* callback function: CbHelp */
#define  PANEL_CFG_BUTTON_OK              6       /* callback function: CbOk */
#define  PANEL_CFG_BUTTON_CANCEL          7       /* callback function: CbCancel */
#define  PANEL_CFG_LABEL_RESULTDIRECTORY  8
#define  PANEL_CFG_LABEL_RESULTFILENAME   9
#define  PANEL_CFG_LABEL_RESULTFILEFMT    10


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK CbBrowse(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CbCancel(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CbHelp(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CbMarkChanged(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CbOk(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
