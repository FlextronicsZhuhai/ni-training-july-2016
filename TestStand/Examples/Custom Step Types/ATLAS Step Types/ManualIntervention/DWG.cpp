#include "cem.h"
#include "key.h"
#include "util.h"

//BEGIN{DFW}:DWG:3:2
int doDWG_3_Fetch (PBYTE* pVALU, int nSizVALU, int nCntVALU, PBYTE* pERRO, int nSizERRO, int nCntERRO, long* pERRI, int nCntERRI, short* pISTI, int nCntISTI)
//END{DFW}
{
    Display("\033[34;4mDWG fnc = 3(cem) fetch\n\033[m\033[34m");
    char buf[1000];
    sprintf(buf,
            "pVALU = 0x%08X, nSizVALU = %d, nCntVALU = %d, pERRO = 0x%08X, nSizERRO = %d, nCntERRO = %d, pERRI = 0x%08X, nCntERRI = %d, pISTI = 0x%08X, nCntISTI = %d\n",
            pVALU, nSizVALU, nCntVALU, pERRO, nSizERRO, nCntERRO, 
            pERRI, nCntERRI, pISTI, nCntISTI);
    Display(buf);
    int i = 0;
    if (pVALU != NULL && nSizVALU == 1)
    {
        Display("pVALU: ");
        for (; i < nCntVALU; i++)
        {
            pVALU[i][0] = i + 0x30;
            sprintf(buf, "0x%02x, ", pVALU[i][0]);
            Display(buf);
        }
        Display("\n");
    }
    else if (pERRO != NULL && nSizERRO == 1)
    {
        Display("pERRO: ");
        for (; i < nCntERRO; i++)
        {
            pERRO[i][0] = i + 0xf0;
            sprintf(buf, "0x%02x, ", pERRO[i][0]);
            Display(buf);
        }
        Display("\n");
    }
    else if (pERRI != NULL)
    {
        Display("pERRI: ");
        for (; i < nCntERRI; i++)
        {
            pERRI[i] = i;
            sprintf(buf, "0x%02x, ", pERRI[i]);
            Display(buf);
        }
        Display("\n");
    }
    Display("\033[m");
    return i;
}

//BEGIN{DFW}:DWG:1:3
int doDWG_1_Init (void)
//END{DFW}
{
    Display("\033[34;4mDWG fnc = 1(cem) init\n\033[m");
    return 0;
}

//BEGIN{DFW}:DWG:2:0
int doDWG_2_Setup (long* pPinsSTIM, int nCntPinsSTIM, double VOLTLL0, double VOLTLL1, double WDLN, short PCLS, short TYPE, long REPT)
//END{DFW}
{
    Display("\033[34;4mDWG fnc = 2(cem) setup\n\033[m\033[34m");
    char buf[1000];
    sprintf(buf,
            "pPinsSTIM = 0x%08X, nCntPinsSTIM = %d, ", 
            pPinsSTIM, nCntPinsSTIM);
    Display(buf);
    DISPLAYDOUBLE(VOLTLL0); Display(", ");
    DISPLAYDOUBLE(VOLTLL1); Display(", ");
    DISPLAYDOUBLE(WDLN); Display(", ");
    DISPLAYSHORT(PCLS); Display(", ");
    DISPLAYSHORT(TYPE); Display(", ");
    DISPLAYLONG(REPT); Display("\n");

    if (nCntPinsSTIM)
    {
        Display("pPinsSTIM: ");
        long* pPins = pPinsSTIM;
        for (int i = 0; i < nCntPinsSTIM; i++)
        {
            sprintf(buf, "%d, ", *pPins++);
            Display(buf);
        }
        Display("\n");
    }
    Display("\033[m");
    return 0;
}
//BEGIN{DFW}:DWG:1:0
int doDWG_1_Setup (long ITER, double MAXT, double SDEL, double SNSR, double STMR, long EVXM, long EVWH, short SIMU, short DTMD)
//END{DFW}
{
    Display("\033[34;4mDWG fnc = 1(cem) setup\n\033[m\033[34m");
    DISPLAYLONG(ITER); Display(", ");
    DISPLAYDOUBLE(MAXT); Display(", ");
    DISPLAYDOUBLE(SDEL); Display(", ");
    DISPLAYDOUBLE(SNSR); Display(", ");
    DISPLAYDOUBLE(STMR); Display(", ");
    DISPLAYLONG(EVXM); Display(", ");
    DISPLAYLONG(EVWH); Display(", ");
    DISPLAYSHORT(SIMU); Display(", ");
    DISPLAYSHORT(DTMD); Display("\n\033[m");
    return 0;
}

//BEGIN{DFW}:DWG:1:2
int doDWG_1_Fetch (long* pFLTC, int nCntFLTC)
//END{DFW}
{
    Display("\033[34;4mDWG fnc = 1(cem) fetch\n\033[m\033[34m");
    char buf[1000];
    sprintf(buf, "pFLTC = 0x%08X, nCntFLTC = %d\n", pFLTC, nCntFLTC);
    Display(buf);
    int i = 0;
    if (pFLTC && nCntFLTC == 1)
    {
        *pFLTC = 0;
        Display("pFLTC: 0\n\033[m" );
        return 1;
    }
    Display("\033[m");
    return 0;
}

//BEGIN{DFW}:DWG:2:3
int doDWG_2_Init (long* pPinsSTIM, int nCntPinsSTIM)
//END{DFW}
{
    Display("\033[34;4mDWG fnc = 2(cem) init\n\033[m\033[34m");
    char buf[1000];
    sprintf(buf,
            "pPinsSTIM = 0x%08X, nCntPinsSTIM = %d\n",
            pPinsSTIM, nCntPinsSTIM); 
    if (pPinsSTIM)
    {
        Display("pPinsSTIM: ");
        long* pPins = pPinsSTIM;
        for (int i = 0; i < nCntPinsSTIM; i++)
        {
            sprintf(buf, "%d, ", *pPins++);
            Display(buf);
        }
        Display("\n");
    }
    Display("\033[m");
    return 0;
}

//BEGIN{DFW}:DWG:2:9
int doDWG_2_Load (PBYTE* pSTIM, int nSizSTIM, int nCntSTIM)
//END{DFW}
{
    Display("\033[34;4mDWG fnc = 2(cem) load\n\033[m\033[34m");
    char buf[1000];
    sprintf(buf,
            "pSTIM = 0x%08X, nSizSTIM = %d, nCntSTIM = %d\n",
            pSTIM, nSizSTIM, nCntSTIM); 
    Display(buf);
    if (pSTIM && nSizSTIM == 1)
    {
        Display("pSTIM: ");
        for (int i = 0; i < nCntSTIM; i++)
        {
            sprintf(buf, "0x%02X, ", pSTIM[i][0]);
            Display(buf);
        }
        Display("\n");
    }
    Display("\033[m");
    return 0;
}

//BEGIN{DFW}:DWG:3:0
int doDWG_3_Setup (long MinVALU, long MaxVALU, double VOLTLL0, double VOLTLL1, double WDLN, short PCLS, short TYPE, long EVWH, long FLTC, short ISTI)
//END{DFW}
{
    Display("\033[34;4mDWG fnc = 3(cem) setup\n\033[m\033[34m");
    DISPLAYLONG(MinVALU); Display(", ");
    DISPLAYLONG(MaxVALU); Display(", ");
    DISPLAYDOUBLE(VOLTLL0); Display(", ");
    DISPLAYDOUBLE(VOLTLL1); Display(", ");
    DISPLAYDOUBLE(WDLN); Display(", ");
    DISPLAYSHORT(PCLS); Display(", ");
    DISPLAYSHORT(TYPE); Display(", ");
    DISPLAYSHORT(EVWH); Display(", ");
    DISPLAYSHORT(FLTC); Display(", ");
    DISPLAYSHORT(ISTI); Display("\n\033[m");
    return 0;
}

//BEGIN{DFW}:DWG:3:3
int doDWG_3_Init (long* pPinsVALU, int nCntPinsVALU)
//END{DFW}
{
    Display("\033[34;4mDWG fnc = 3(cem) init\n\033[m\033[34m");
    char buf[1000];
    sprintf(buf, 
            "pPinsVALU = 0x%08X, nCntPinsVALU = %d\n", 
            pPinsVALU, 
            nCntPinsVALU);
    Display(buf);
    if(pPinsVALU)
    {
        Display("pPinsVALU: ");
        long* pPins = pPinsVALU;
        for (int i = 0; i < nCntPinsVALU; i++)
        {
            sprintf(buf, "%d, ", *pPins++);
            Display(buf);
        }
        Display("\n");
    }
    Display("\033[m");
    return 0;
}

//BEGIN{DFW}:DWG:3:9
int doDWG_3_Load (PBYTE* pREFX, int nSizREFX, int nCntREFX, PBYTE* pMASK, int nSizMASK, int nCntMASK, PBYTE* pMSKZ, int nSizMSKZ, int nCntMSKZ)
//END{DFW}
{
    Display("\033[34;4mDWG fnc = 3(cem) load\n\033[m\033[34m");
    char buf[1000];
    sprintf(buf, 
            "pREFX = 0x%08X, nSizREFX = %d, nCntREFX = %d, pMASK = 0x%08X, nSizMASK = %d, nCntMASK = %d, pMSKZ = 0x%08X, nSizMSKZ = %d, nCntMSKZ = %d\n", 
            pREFX, nSizREFX, nCntREFX, pMASK, nSizMASK, nCntMASK, pMSKZ, nSizMSKZ, nCntMSKZ);
    Display(buf);

    if (pREFX && nSizREFX == 1)
    {
        Display("REFX: ");
        for (int i = 0; i < nCntREFX; i++)
        {
            sprintf(buf, "0x%02X, ", pREFX[i][0]);
            Display(buf);
        }
        Display("\n");
    }
    if (pMASK && nSizMASK == 1)
    {
        Display("MASK: ");
        for (int i = 0; i < nCntMASK; i++)
        {
            sprintf(buf, "0x%02X, ", pMASK[i][0]);
            Display(buf);
        }
        Display("\n");
    }
    if (pMSKZ && nSizMSKZ == 1)
    {
        Display("MSKZ: ");
        for (int i = 0; i < nCntMSKZ; i++)
        {
            sprintf(buf, "0x%02X, ", pMSKZ[i][0]);
            Display(buf);
        }
        Display("\n");
    }

    Display("\033[m");
    return 0;
}
