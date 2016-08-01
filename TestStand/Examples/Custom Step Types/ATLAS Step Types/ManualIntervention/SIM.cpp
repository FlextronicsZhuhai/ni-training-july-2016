#include "cem.h"
#include "key.h"
#include "util.h"

//BEGIN{DFW}:SIM:24:0
int doSIM_24_Setup (double BITR, double WDLN, short TROL, long UUTL, long TEQT, short BUSM)
//END{DFW}
{
    Display("\033[34;4mSIM fnc = 24(cem) setup\n\033[m\033[34m");
    DISPLAYDOUBLE(BITR); Display(", ");
    DISPLAYDOUBLE(WDLN); Display(", ");
    DISPLAYSHORT(TROL); Display(", ");
    DISPLAYLONG(UUTL); Display(", ");
    DISPLAYLONG(TEQT); Display(", ");
    DISPLAYSHORT(BUSM); Display("\n\033[m");

    PCHAR* pDATA = NULL; 
    int nCntDATA = 0;
    DATUM *p;
    if (p = GetDatum(M_DATA, K_SET)) 
    {
        if (DatTyp(p) != TXTV)  
            return TypeErr("data");
        pDATA = (PCHAR*)p->dat_val.dat_txt;
        nCntDATA = DatCnt(p);
    }

    if (pDATA != NULL) 
    {
        Display("\033[34mpDATA:");
        char msg[1000];
        for (int cnt = 0; cnt < nCntDATA; cnt ++)
        {
            sprintf(msg, " '%s'", pDATA[cnt]);
            Display(msg);
        }
        Display("\n\033[m");
    }
    return 0;
}

//BEGIN{DFW}:SIM:21:0
int doSIM_21_Setup (double BITR, double MAXT, double WDLN, short PRCD, short STRD, short TROL, short WAIT, short BUSM, short BUSS)
//END{DFW}
{
    Display("\033[34;4mSIM fnc = 21(cem) setup\n\033[m\033[34m");
    DISPLAYDOUBLE(BITR); Display(", ");
    DISPLAYDOUBLE(MAXT); Display(", ");
    DISPLAYDOUBLE(WDLN); Display(", ");
    DISPLAYSHORT(PRCD); Display(", ");
    DISPLAYSHORT(STRD); Display(", ");
    DISPLAYSHORT(TROL); Display(", ");
    DISPLAYSHORT(WAIT); Display(", ");
    DISPLAYSHORT(BUSM); Display(", ");
    DISPLAYSHORT(BUSS); Display("\n\033[m");
    return 0;
}

//BEGIN{DFW}:SIM:22:0
int doSIM_22_Setup (double BITR, double MAXT, double WDLN, short PRCD, short STRD, short TROL, short WAIT, short BUSM, short BUSS)
//END{DFW}
{
    Display("\033[34;4mSIM fnc = 22(cem) setup\n\033[m\033[34m");
    DISPLAYDOUBLE(BITR); Display(", ");
    DISPLAYDOUBLE(MAXT); Display(", ");
    DISPLAYDOUBLE(WDLN); Display(", ");
    DISPLAYSHORT(PRCD); Display(", ");
    DISPLAYSHORT(STRD); Display(", ");
    DISPLAYSHORT(TROL); Display(", ");
    DISPLAYSHORT(WAIT); Display(", ");
    DISPLAYSHORT(BUSM); Display(", ");
    DISPLAYSHORT(BUSS); Display("\n\033[m");
    return 0;
}

//BEGIN{DFW}:SIM:23:2
int doSIM_23_Fetch (void)
//END{DFW}
{
    PCHAR* pDATA = NULL; 
    int nCntDATA = 0, nSizeDATA = 0;

    Display("\033[34;4mSIM fnc = 23(cem) fetch\n\033[m\033[34m");
    DATUM *p;
    if (p = FthDat())
    {
        if (DatTyp(p) != TXTV)  
            return TypeErr("data");
        pDATA = (PCHAR*) p->dat_val.dat_txt;
        nSizeDATA = DatSiz(p);
        nCntDATA = DatCnt(p);
    }

    Display("pDATA: ");
    const char* Array[] = {"one", "two", "three", "four", "five", "six"};
    int nArraySize = sizeof(Array) / sizeof(Array[0]);
    for (int i = 0; i < nCntDATA && i < nArraySize; i++)
    {
        strcpy(pDATA[i], Array[i]);
        Display((char*)(Array[i])); 
        Display(", ");
    }
    Display("\n\033[m");
    FthCnt(i);
    return 0;
}

//BEGIN{DFW}:SIM:23:0
int doSIM_23_Setup (double BITR, double WDLN, short TROL, long UUTL, long TEQT, short BUSM, long* pDATA, int nCntDATA)
//END{DFW}
{
    Display("\033[34;4mSIM fnc = 23(cem) setup\n\033[m\033[34m");
    char buf[1000];
    sprintf(buf, "pDATA = 0x%08X, nCntDATA = %d, ", pDATA, nCntDATA);
    Display(buf);
    DISPLAYDOUBLE(BITR); Display(", ");
    DISPLAYDOUBLE(WDLN); Display(", ");
    DISPLAYSHORT(TROL); Display(", ");
    DISPLAYLONG(UUTL); Display(", ");
    DISPLAYLONG(TEQT); Display(", ");
    DISPLAYSHORT(BUSM); Display("\n");
    if (pDATA)
    {
        Display("pDATA:");
        long* pCur = pDATA;
        for (int i = 0; i < nCntDATA; i++)
        {
            sprintf(buf, "%d, ", *pCur++);
            Display(buf);
        }
        Display("\n");
    }

    Display("\033[m");
    return 0;
}
