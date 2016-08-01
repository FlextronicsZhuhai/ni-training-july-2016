#include <ansi_c.h>
#include <cvirte.h>     /* needed if linking executable in external compiler; harmless otherwise */
#include <userint.h>
#include <analysis.h>
#include <math.h>
#include "multiUUT.h"
#include "tsutil.h"
#include "grid.h"


/////////////////////////////////////////////

#define NB_PTS              512
#define AMPLITUDE           3
#define START_FREQ          0
#define END_FREQ            24000
#define FREQ_STEP           400
#define NUM_FREQ_STEPS      (END_FREQ - START_FREQ)/FREQ_STEP + 1


    // structure to hold information about the SWEEP panel
typedef struct
    {
    double  frequency;
    int     stepNum;
    double  peaks[NUM_FREQ_STEPS];
    double  signalArray[NB_PTS];
    double  noiseArray[NB_PTS];
    double  highStopFreq;
    double  lowStopFreq;
    double  gNoise;
    double  phase;
    double  Converted_Spec[NB_PTS/2];    
    double  Auto_Spec[NB_PTS/2]; 
    double  peakFrequency;
    double  peakPower;
    } SweepPanelInfo;

/////////////////////////////////////////////

int __stdcall DllMain (HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
    {
    switch (fdwReason)
        {
        case DLL_PROCESS_ATTACH:
            if (InitCVIRTE (hinstDLL, 0, 0) == 0)    /* Needed if linking in external compiler; harmless otherwise */
                return 0;     /* out of memory */
            break;
        case DLL_PROCESS_DETACH:
            CloseCVIRTE ();    /* Needed if linking in external compiler; harmless otherwise */
            break;
        }
    
    return 1;
    }


/////////////////////////////////////////////

    // Display a panel that simulates a swept frequency response test
int _export _stdcall FrequencySweepTest(CAObjHandle sequenceContext, int uutIndex, char *uutString, int numUUTs, double *peakFrequency)
    {
    int             error = 0;
    int             panel = 0;
    SweepPanelInfo *panelInfo = NULL;
    static  int     seed = 0;
    Rect            screenRect = MakeRect(0,0,0,0);
    int             savedDecimalPointSetting;
    
    GetSystemAttribute (ATTR_USE_LOCALIZED_DECIMAL_SYMBOL, &savedDecimalPointSetting);
    SetSystemAttribute (ATTR_USE_LOCALIZED_DECIMAL_SYMBOL, VAL_USE_SYSTEM_SETTING);    // dialog contains numerics, use the system decimal point character
    
    nullChk(panelInfo = calloc(sizeof(SweepPanelInfo), 1));

    panelInfo->frequency = START_FREQ;
    SetRandomSeed(++seed); // make sure separate threads don't all get the same random numbers
    panelInfo->lowStopFreq = 2000 + Random(0, 7000);
    panelInfo->highStopFreq = 10000 + Random(0, 4000);
    
    errChk(panel = LoadPanelEx (0, "multiUUT.uir", SWEEP, __CVIUserHInst));
        
    SetPanelAttribute(panel, ATTR_CALLBACK_DATA, (void *)panelInfo);
        
    SetCtrlVal(panel, SWEEP_UUTSTRING, uutString);
    
    GetScreenSize (&screenRect.height, &screenRect.width); // get screen size
    TileGrid_TilePanel(panel, uutIndex, numUUTs, &screenRect, TRUE);
    
    DisplayPanel (panel);
    TS_CancelDialogIfExecutionStops (panel, sequenceContext);
    
    errChk( RunUserInterface());
    
    *peakFrequency = panelInfo->peakFrequency;

Error:
    if (panel > 0)
        DiscardPanel(panel);
        
    SetSystemAttribute (ATTR_USE_LOCALIZED_DECIMAL_SYMBOL, savedDecimalPointSetting); // restore setting so this example does not affect other panels
        
    return error;
    }

/////////////////////////////////////////////

    // on each timer tick, perform a frequency response test at a new frequency
int CVICALLBACK SweepTimerFunction(int panel, int control, int event, void *callbackData,
                            int eventData1, int eventData2)
    {
    int         error = 0;
    int         Win, Signal, Scaling, Display;    
    double      df, Freq_Peak, Power_Peak,  Freq, Amp; 
    char        Unit[20]="V";        
    WindowConst WinConst;    
    int         channel;
    double      sampleRate;
    double      sampleInterval;
    double      cyclesPerSample;
    SweepPanelInfo   *panelInfo;

    GetPanelAttribute(panel, ATTR_CALLBACK_DATA, (void **)&panelInfo);
    
    if (event == EVENT_TIMER_TICK)
        {
        sampleRate  = 200000.0;
        sampleInterval  = 1/ sampleRate;
        cyclesPerSample = panelInfo->frequency / sampleRate ;
        
            // Generate Input Signal according the SIGNAL ring 
        GetCtrlVal(panel, SWEEP_SIGNAL, &Signal);
        switch(Signal)
            {
            case 0:
                SineWave (NB_PTS, AMPLITUDE, cyclesPerSample, &panelInfo->phase, panelInfo->signalArray);
                break;
            case 1:
                SquareWave (NB_PTS, AMPLITUDE, cyclesPerSample, &panelInfo->phase, 50.0, panelInfo->signalArray);
                break;
            case 2:
                TriangleWave (NB_PTS, AMPLITUDE, cyclesPerSample, &panelInfo->phase, panelInfo->signalArray);
                break;
            }   
        
            // Get current control information 
        GetCtrlVal (panel, SWEEP_NOISE_LEVEL, &panelInfo->gNoise);
        panelInfo->gNoise /= 100.0;
        WhiteNoise (NB_PTS, AMPLITUDE * panelInfo->gNoise, -1, panelInfo->noiseArray);
        Add1D (panelInfo->signalArray, panelInfo->noiseArray, NB_PTS, panelInfo->signalArray);
        
            // Display Input Signal 
        DeleteGraphPlot (panel, SWEEP_GRAPH1, -1, VAL_DELAYED_DRAW);
        PlotWaveform (panel, SWEEP_GRAPH1, panelInfo->signalArray, NB_PTS, VAL_DOUBLE, 1.0, 0.0, 0.0, sampleInterval,
                                    VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_GREEN);

            // Butterworth bandpass digital filter
        Bw_BPF (panelInfo->signalArray, NB_PTS, 1/ sampleInterval, panelInfo->lowStopFreq, panelInfo->highStopFreq, 1, panelInfo->signalArray);

            // Apply a Window according the WINDOW Ring control
            // The Win is applied to the input signal in Time Space    
            // Keep Window parameter for later use                   
        GetCtrlVal(panel, SWEEP_WINDOW, &Win);
        ScaledWindow (panelInfo->signalArray, NB_PTS, Win, &WinConst);

        AutoPowerSpectrum (panelInfo->signalArray, NB_PTS, sampleInterval, panelInfo->Auto_Spec, &df);

        PowerFrequencyEstimate (panelInfo->Auto_Spec, NB_PTS/2, -1, WinConst, df, 7, &Freq_Peak, &Power_Peak);
        SetCtrlVal(panel, SWEEP_POWER_PEAK, Power_Peak);
        SetCtrlVal(panel, SWEEP_PEAK_FREQ, Freq_Peak);

            // Get the scale information
            // Convert the spectrum and display the corresponding units 
        GetCtrlVal(panel, SWEEP_SCALING, &Scaling);
        GetCtrlVal(panel, SWEEP_DISPLAY, &Display);
        SpectrumUnitConversion (panelInfo->Auto_Spec, NB_PTS/2, 0, Scaling, Display, df, WinConst, panelInfo->Converted_Spec, Unit);
        SetCtrlAttribute (panel, SWEEP_GRAPH2, ATTR_YNAME, Unit);

            // Display the spectrum
        DeleteGraphPlot (panel, SWEEP_GRAPH2, -1, VAL_DELAYED_DRAW);
        SetCtrlAttribute (panel, SWEEP_GRAPH2, ATTR_REFRESH_GRAPH, 0);
        PlotWaveform (panel, SWEEP_GRAPH2, panelInfo->Converted_Spec, NB_PTS/4 ,VAL_DOUBLE, 1.0, 0.0, 0.0, df,
                                    VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_GREEN);

        PlotWaveform (panel, SWEEP_GRAPH2, panelInfo->peaks, panelInfo->stepNum + 1, VAL_DOUBLE,
                      1.0, 0.0, START_FREQ, FREQ_STEP, VAL_CONNECTED_POINTS,
                      VAL_ASTERISK, VAL_SOLID, 1, VAL_BLUE);

        SetCtrlAttribute (panel, SWEEP_GRAPH2, ATTR_REFRESH_GRAPH, 1);
        GetGraphCursor (panel, SWEEP_GRAPH2, 1, &Freq, &Amp);
        SetGraphCursor(panel, SWEEP_GRAPH2, 1, Freq_Peak, .01);
        
            // remember the frequency with the maximum power
        if (Power_Peak > panelInfo->peakPower)
            {
            panelInfo->peakPower = Power_Peak;
            panelInfo->peakFrequency = Freq_Peak;
            }
            
        panelInfo->peaks[panelInfo->stepNum] = Power_Peak;
        
        panelInfo->frequency += FREQ_STEP;
        panelInfo->stepNum++;
        if (panelInfo->frequency > END_FREQ)
            {
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

    // handle CLOSE and DISCARD for the SWEEP panel
int CVICALLBACK SweepPanelCallback (int panel, int event, void *callbackData,
        int eventData1, int eventData2)
    {
    switch (event)
        {
        case EVENT_CLOSE:
            SetCtrlAttribute(panel, SWEEP_TIMER, ATTR_ENABLED, FALSE);
            QuitUserInterface(0);
            break;
        case EVENT_DISCARD:
            free(callbackData); // free the panelInfo structure
            break;
        }
        
    return 0;
    }
