#include "cem.h"
#include "key.h"
#include "util.h"

//BEGIN{DFW}:WAVEFORM:1:0
int doWAVEFORM_1_Setup (double* pSTIM, int nCntSTIM, double FREQ, double SMPW, double VOLT)
//END{DFW}
{
    Display("\033[34;4mWAVEFORM fnc = 1(cem) setup\n\033[m\033[34m");
    char buf[1000];
    sprintf(buf, 
            "pStim = 0x%08X, nCntSTIM = %d, ",
            pSTIM, nCntSTIM);
    Display(buf);
    DISPLAYDOUBLE(FREQ); Display(", ");
    DISPLAYDOUBLE(SMPW); Display(", ");
    DISPLAYDOUBLE(VOLT); Display("\n\033[m");

    if (pSTIM)
    {
        Display("\033[34mDATA:");
        char buf[1000];
        for (int i = 0; i < nCntSTIM; i++)
        {
            sprintf(buf, " %4.2f,", pSTIM[i]);
            Display(buf);
        }
        Display("\n\033[m");
    }
    return 0;
}

//BEGIN{DFW}:WAVEFORM:2:2
int doWAVEFORM_2_Fetch (double* pSMPL, int nCntSMPL)
//END{DFW}
{
    // incomplete reading for matrice
    Display("\033[34;4mWAVEFORM fnc = 2(cem) fetch\n\033[m\033[34m");
    char buf[1000];
    sprintf(buf, 
            "pSMPL = 0x%08X, nCntSMPL = %d\n",
            pSMPL,
            nCntSMPL);
    Display(buf); 

    int i = 0;
    if (pSMPL)
    {
        Display("pSmpl: ");
        for (; i < nCntSMPL - 2 && i >= 0; i++)
        {
            pSMPL[i] = i + 0.7;
            sprintf(buf, "%g, ", pSMPL[i]);
            Display(buf);
        }
        Display("\n");
    }
    Display("\033[m");
    return i;
}

//BEGIN{DFW}:WAVEFORM:2:0
int doWAVEFORM_2_Setup (double MinSMPL, double MaxSMPL, double SMPW, double VOLT)
//END{DFW}
{
    Display("\033[34;4mWAVEFORM fnc = 2(cem) setup\n\033[m\033[34m");
    DISPLAYDOUBLE(MinSMPL); Display(", ");
    DISPLAYDOUBLE(MaxSMPL); Display(", ");
    DISPLAYDOUBLE(SMPW); Display(", ");
    DISPLAYDOUBLE(VOLT); Display("\n\033[m");
    return (int) 0;
}

