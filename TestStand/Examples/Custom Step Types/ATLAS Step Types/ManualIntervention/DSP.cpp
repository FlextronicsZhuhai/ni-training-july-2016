#include "cem.h"
#include "key.h"
#include "util.h"

//BEGIN{DFW}:DSP:1:0
int doDSP_1_Setup (double VOLT, double MinVOLT, double MaxVOLT, long EVOU, short EVSL)
//END{DFW}
{
    Display("\033[34;4mDSP fnc = 1(cem) setup\n\033[m\033[34m");
    DISPLAYDOUBLE(VOLT); Display(", ");
    DISPLAYDOUBLE(MinVOLT); Display(", ");
    DISPLAYDOUBLE(MaxVOLT); Display(", ");
    DISPLAYLONG(EVOU); Display(", ");
    DISPLAYSHORT(EVSL); Display("\n\033[m");
    return 0;
}

//BEGIN{DFW}:DSP:2:0
int doDSP_2_Setup (double VOLT, double MinVOLT, double MaxVOLT, long EVOU, short EVSL)
//END{DFW}
{
    Display("\033[34;4mDSP fnc = 2(cem) setup\n\033[m\033[34m");
    DISPLAYDOUBLE(VOLT); Display(", ");
    DISPLAYDOUBLE(MinVOLT); Display(", ");
    DISPLAYDOUBLE(MaxVOLT); Display(", ");
    DISPLAYLONG(EVOU); Display(", ");
    DISPLAYSHORT(EVSL); Display("\n\033[m");
    return 0;
}

//BEGIN{DFW}:DSP:10:2
double doDSP_10_Fetch (void)
//END{DFW}
{
    Display("\033[34;4mDSP fnc = 10(cem) fetch\n\033[m");
    return (double) 0.1122334455;
}

//BEGIN{DFW}:DSP:10:0
int doDSP_10_Setup (double MAXT, double MinTIME, double MaxTIME, long EVTF, long EVTT)
//END{DFW}
{
    Display("\033[34;4mDSP fnc = 10(cem) setup\n\033[m\033[34m");
    DISPLAYDOUBLE(MAXT); Display(", ");
    DISPLAYDOUBLE(MinTIME); Display(", ");
    DISPLAYDOUBLE(MaxTIME); Display(", ");
    DISPLAYLONG(EVTF); Display(", ");
    DISPLAYLONG(EVTT); Display("\n\033[m");
    return 0;
}
