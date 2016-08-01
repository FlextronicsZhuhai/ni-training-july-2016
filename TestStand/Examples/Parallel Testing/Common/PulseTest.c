#include <ansi_c.h>
#include <cvirte.h>     /* needed if linking executable in external compiler; harmless otherwise */
#include <userint.h>
#include "multiuut.h"
#include "tsutil.h"   
#include "toolbox.h"
#include <utility.h>
#include "grid.h"

int gDelayInterval = 100;

    // structure to hold information about the PULSE test
typedef struct 
    {
    int             testSocket;    
    double          numSockets;
    int             xSize;          // in number of UUTs
    int             ySize;          // in number of UUTs
    int             canvasHeight;   // in pixels
    int             canvasWidth;    // in pixels
    int             panel;
    int             threadId;  // of worker thread that runs the user interface for the pulse test panel
    } PulseTestInfo;

/////////////////////////////////////////////

    // There is only one pulse test structure and panel since the pulse test demonstrates the use of an 
    // instrument of which the system contains only instance. Thus, the pulse test is never run on more than one UUT at a time
static PulseTestInfo *  gPulseTestInfo = NULL;  
static int              gThreadInitialized = FALSE;

/////////////////////////////////////////////

    // Returns the rectangle in which to draw the given UUT on the canvas
static void GetUUTRect(int testSocket, Rect *uutRect)
    {
    int     x, y;
    double  width, height;
    
    width = gPulseTestInfo->canvasWidth / gPulseTestInfo->xSize;
    height = gPulseTestInfo->canvasHeight / gPulseTestInfo->ySize;
    
    TileGrid_GetCoordinates(testSocket, gPulseTestInfo->numSockets, &x, &y);    

    uutRect->top = y * height;
    uutRect->left = x * width;
    uutRect->width = width;
    uutRect->height = height;
    
    RectGrow(uutRect, -3, -3);
    }
    
/////////////////////////////////////////////
    
   // draw a UUT as a framed oval with a socket number in the center
static void DrawUUT(int testSocket, int fillColor, int frameColor)
    {
    Rect    uutRect;
    char    socketNumString[256];
    
    GetUUTRect(testSocket, &uutRect);
    
    SetCtrlAttribute (gPulseTestInfo->panel, PULSE_CANVAS, ATTR_PEN_COLOR, frameColor);
    SetCtrlAttribute (gPulseTestInfo->panel, PULSE_CANVAS,ATTR_PEN_FILL_COLOR, fillColor);
    SetCtrlAttribute (gPulseTestInfo->panel, PULSE_CANVAS,ATTR_PEN_WIDTH, 3);
    CanvasDrawOval (gPulseTestInfo->panel, PULSE_CANVAS, uutRect, VAL_DRAW_FRAME_AND_INTERIOR);
    
    sprintf(socketNumString, "%d", testSocket);
    
    RectGrow(&uutRect, -3, -3);
    
    SetCtrlAttribute (gPulseTestInfo->panel, PULSE_CANVAS,ATTR_PEN_FILL_COLOR, VAL_TRANSPARENT);
    CanvasDrawText (gPulseTestInfo->panel, PULSE_CANVAS, socketNumString, VAL_APP_META_FONT, uutRect, VAL_CENTER);    
    }
    
/////////////////////////////////////////////

    // This function executes in a separate worker thread to run the user interface for the pulse test panel
    // Other threads write to the panel's controls but this thread processes the panel's events
int CVICALLBACK PulseTest_RunPanel(void *functionData)
    {
    int error = 0;
    int index;
    
    errChk( gPulseTestInfo->panel = LoadPanelEx (0, "multiUUT.uir", PULSE, __CVIUserHInst));
        
    SetCtrlAttribute(gPulseTestInfo->panel, PULSE_SWITCH_POSITION, ATTR_DIMMED, TRUE);    // dim this control to indicate the switch is inactive
    GetCtrlAttribute(gPulseTestInfo->panel, PULSE_CANVAS, ATTR_WIDTH, &gPulseTestInfo->canvasWidth);
    GetCtrlAttribute(gPulseTestInfo->panel, PULSE_CANVAS, ATTR_HEIGHT, &gPulseTestInfo->canvasHeight);

        // draw all the UUTs in gray to indicate they are currently inactive
    for (index = 0; index < gPulseTestInfo->numSockets; index++)
        DrawUUT(index, VAL_GRAY, VAL_BLACK);
    
    DisplayPanel(gPulseTestInfo->panel);

        // let other threads know that the panel is ready
    gThreadInitialized = TRUE;
    
       // process events for the pulse test panel which is used by many different threads
    errChk( RunUserInterface());
    
Error:
    if (gPulseTestInfo)
        {
        if (gPulseTestInfo->panel > 0)
            DiscardPanel(gPulseTestInfo->panel);
        
        free(gPulseTestInfo);
        gPulseTestInfo = NULL;
        }

    if (error < 0)
        gThreadInitialized = error; // let other threads know that the panel event processing thread generated an error

    return error;
    }

/////////////////////////////////////////////

    // show the pulse test panel if it is not already shown
static int PulseTest_ShowPanel(int testSocket, int numSockets)
    {             
    int error = 0;
    int functionId;
    
    if (!gPulseTestInfo)
        {
        nullChk(gPulseTestInfo = calloc(sizeof(PulseTestInfo), 1));
        
        gPulseTestInfo->numSockets = numSockets;
        TileGrid_GetSize(numSockets, &gPulseTestInfo->xSize, &gPulseTestInfo->ySize);
        
            // We must run the user interface in a worker thread because we want the panel to 
            // a) exist longer than the duration of a single test and
            // b) be used by tests running in many different threads.
            // We need a worker thread because only the thread that creates a panel can process its events
            // 
            // Note that the example sequence does not call any test functions from more than one TestStand thread
            // at a time.  If the sequence did not already guarantee this, these functions would need additional internal 
            // synchronization to protect access to the global variables in this file
            
        gThreadInitialized = FALSE;
        CmtScheduleThreadPoolFunction (DEFAULT_THREAD_POOL_HANDLE, PulseTest_RunPanel, 0, &functionId);        
        
            // wait for the panel to be created
        while (gThreadInitialized == FALSE)  // could wait on an event, but this is easy and just as good
            Sleep(50);
            
        errChk( gThreadInitialized); // in case of error
        
            // get the threadId so we can later run a callback in the worker thread to tell it to quit
        errChk( CmtGetThreadPoolFunctionAttribute (DEFAULT_THREAD_POOL_HANDLE,
                functionId, ATTR_TP_FUNCTION_THREAD_ID, &gPulseTestInfo->threadId));
        }
        
Error:
    return error;
    }

/////////////////////////////////////////////

    // called by in the thread that is processing the panel's events by PostDeferredCallToThread
void ExitPanel(void *callbackData)
    {
    QuitUserInterface((int)callbackData);
    }

/////////////////////////////////////////////

    // remove the pulse test panel if it exists
static int PulseTest_RemovePanel(void)
    {
    int error = 0; 
    
        // use PostDeferredCallToThread because QuitUserInterface must be called in the worker thread because it 
        // is the thread is calling RunUserInterface
    if (gPulseTestInfo)
        {
        errChk( PostDeferredCallToThread (ExitPanel, 0, gPulseTestInfo->threadId));
                    
            // wait for the panel to be destroyed
        while (gPulseTestInfo != NULL)  // could wait on an event, but this is easy and just as good
            Sleep(50);
        }
    
Error:    
    return error;
    }

/////////////////////////////////////////////

    // prepare for a simulated a pulse response test
int _export _stdcall PulseTest_InitializeTest(CAObjHandle sequenceContext, int testSocket, int numSockets)
    {
    int         error = 0;
    static  int seed = 0;             
    
        // does nothing if it is already shown
    errChk( PulseTest_ShowPanel(testSocket, numSockets));
    
        // initial data for this test
    gPulseTestInfo->testSocket = testSocket;
    
    SetRandomSeed(++seed); // make sure separate threads don't all get the same random numbers
    
    DeleteGraphPlot(gPulseTestInfo->panel, PULSE_GRAPH, -1, VAL_IMMEDIATE_DRAW);    // clear the graph
    DrawUUT(gPulseTestInfo->testSocket, VAL_WHITE, VAL_BLACK);     // draw the UUT in white to indicate that it is being tested
    
    Sleep(gDelayInterval);  // simulate time passage due to test execution
    
Error:
    return error;
    }

/////////////////////////////////////////////

    // first element of each array is the pulse length, the remaining elements are the pulse pattern 
int pattern1[] =  {15, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1};
int pattern2[] =  {15, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0};
int pattern3[] =  {22, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1};
int pattern4[] =  {8,  1, 0, 0, 1, 0, 1, 1, 0};
int pattern5[] =  {16, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1};
int pattern6[] =  {37, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1};
 
int *pulseArrayList[6] = {pattern1, pattern2, pattern3, pattern4, pattern5, pattern6};

int _export _stdcall PulseTest_FirePulse(int pulseNumber, double *pulseResponseTime)
    {
    int error = 0;
    
        // clear the graph
    errChk( DeleteGraphPlot(gPulseTestInfo->panel, PULSE_GRAPH, -1, VAL_IMMEDIATE_DRAW));   

        // plot a pulse train
    errChk( PlotY(gPulseTestInfo->panel, PULSE_GRAPH, &pulseArrayList[pulseNumber][1], pulseArrayList[pulseNumber][0], 
            VAL_INTEGER, VAL_THIN_STEP, VAL_NO_POINT, VAL_SOLID, 1, VAL_GREEN));                
            
        // simulate measured response time
    *pulseResponseTime = Random(0.000001, 0.00001); 
    
    Sleep(gDelayInterval);  // simulate time passage due to test execution
    
Error:    
    return error;
    }
    
/////////////////////////////////////////////

    // simulate connecting the switch to the current UUT
int _export _stdcall PulseTest_ConnectSwitch(void)
    {
    int error = 0;

    errChk( SetCtrlVal(gPulseTestInfo->panel, PULSE_SWITCH_POSITION, gPulseTestInfo->testSocket)); 
    errChk( SetCtrlAttribute(gPulseTestInfo->panel, PULSE_SWITCH_POSITION, ATTR_DIMMED, FALSE));
    Sleep(gDelayInterval);  // simulate time passage due to test execution
    
Error:    
    return error;
    }
    
/////////////////////////////////////////////

    // simulate disconnecting the switch
int _export _stdcall PulseTest_DisconnectSwitch(void)
    {
    int error = 0;

    errChk( SetCtrlAttribute(gPulseTestInfo->panel, PULSE_SWITCH_POSITION, ATTR_DIMMED, TRUE));
    Sleep(gDelayInterval);  // simulate time passage due to test execution
    
Error:    
    return error;
    }

/////////////////////////////////////////////
    
    // simulate querying the UUT to determine if it processed the pulses correctly
int _export _stdcall PulseTest_DeterminePassFail(int *passed)
    {
    int error = 0;

    *passed = Random(0.0, 100.0) < 80.0;    // 80% pass rate (for this part of the test)

        // draw the UUT in red or green to indicate whether it passed
    DrawUUT(gPulseTestInfo->testSocket, *passed ? VAL_GREEN : VAL_RED, VAL_BLACK);     
    
    Sleep(gDelayInterval);  // simulate time passage due to test execution
    
Error:    
    return error;
    }

/////////////////////////////////////////////

   // the test is over for the current UUT
int _export _stdcall PulseTest_DeinitializeTest(void)
    {
    int error = 0;

    Sleep(gDelayInterval);  // simulate time passage due to test execution
    
Error:    
    return error;
    }
    
/////////////////////////////////////////////

   // at this point all UUTs are tested and the panel can be hidden
int _export _stdcall PulseTest_Cleanup(void)
    {
    int error = 0;

    errChk( PulseTest_RemovePanel());
        
Error:    
    return error;
    }
    
