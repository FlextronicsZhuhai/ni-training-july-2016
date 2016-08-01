#include "cem.h"
#include "key.h"
#include <limits.h>
#include <float.h>
EXTERNC int lod_mode;
/*
 *  VERBS
 */
DECLAREC short v__cnt = V__CNT;
DECLAREC char *VCiilTxt [] = {
    "","APP","ARM","CAL","CHN","CMP","CON","CRE",
    "DCL","DEF","DEL","DIS","DO","DSB","ELS","ENB",
    "END","EST","FIN","FOR","FTH","GTO","IDY","IF",
    "INC","INP","INX","LVE","MEA","MON","OUT","PFM",
    "PRV","RD","REM","REQ","RES","RST","SET","SNS",
    "STI","TRM","UPD","VER","WHL","WTF","XTN",};
/*
 *  NOUNS
 */
DECLAREC short n__cnt = N__CNT;
DECLAREC char *NCiilTxt [] = {
    "","ACS","ADF","AMB","AMS","ATC","BUS","COM",
    "DCF","DCS","DGT","DIS","DME","DOP","EAR","EMF",
    "EVS","EVT","EXC","FLU","FMS","HEA","IFF","ILS",
    "IMP","LCL","LDT","LGT","LLD","LRF","MAN","PAC",
    "PAM","PAT","PDC","PDP","PDT","PMS","RDN","RDS",
    "RPS","RSL","RTN","SCS","SFT","SHT","SIM","SQW",
    "STM","STS","SYN","TAC","TDG","TED","TMI","TMR",
    "TRI","VBR","VOR","WAV",};
/*
 *  MODIFIERS
 */
DECLAREC short m__cnt = M__CNT;
DECLAREC char *MCiilTxt [] = {
    "","ACCF","ACCO","ACCP","AGER","ALTI","ALTR","AMCP",
    "AMMC","AMMF","AMPL","AMSH","ANAC","ANAX","ANAY","ANAZ",
    "ANGL","ANGP","ANGT","ANGX","ANGY","ANGZ","ANRT","ANRX",
    "ANRY","ANRZ","ANSD","APER","ATMS","ATTN","BAND","BARP",
    "BITP","BITR","BTRN","BURD","BURR","BURS","BUSM","BUSP",
    "BUSS","CAMP","CAPA","CCOM","CDAT","CFRQ","CHAN","CHID",
    "CHRM","CMDW","CMPL","CMWB","COMD","COND","COUN","CPHS",
    "CPKN","CPKP","CRAB","CRAC","CRBA","CRBC","CRCA","CRCB",
    "CRCT","CRFR","CRPA","CRPB","CRPC","CRSD","CRSF","CSTS",
    "CUPK","CUPP","CUR0","CUR1","CURA","CURI","CURL","CURQ",
    "CURR","CURT","CWLV","DATA","DATL","DATP","DATS","DATT",
    "DATW","DBLI","DBND","DBRC","DBRS","DCCO","DCOF","DDMD",
    "DELA","DEWP","DIGS","DIST","DMDS","DPFR","DPSH","DROO",
    "DSFC","DSTR","DSTX","DSTY","DSTZ","DTMD","DTOR","DUTY",
    "DVST","DWBT","EFCY","EFFI","EINM","ERRI","ERRO","EVAO",
    "EVDL","EVEO","EVEV","EVFO","EVGB","EVGF","EVGR","EVGT",
    "EVOU","EVSB","EVSF","EVSL","EVSW","EVTF","EVTI","EVTR",
    "EVTT","EVUN","EVWH","EVXE","EVXM","EXAE","EXNM","FALL",
    "FDST","FLTC","FLTS","FLUT","FMCP","FRCE","FRCR","FREQ",
    "FRQ0","FRQ1","FRQD","FRQP","FRQQ","FRQW","FUEL","FXDN",
    "FXIP","FXQD","GSLP","HAPW","HARM","HARP","HARV","HDSK",
    "HIZZ","HMDF","HUMY","IASP","IBHP","IBHW","IBLP","IBLW",
    "ICOW","ICWB","IDSE","IDSF","IDSG","IDSM","IDSP","IDWB",
    "IJIT","ILLU","IMHP","IMHW","IMLP","IMLW","INDU","IOCG",
    "IPHS","IRAT","ISTI","ISWB","ITER","IVCG","IVCS","IVCW",
    "IVDL","IVDP","IVDS","IVDT","IVDW","IVMG","IVOA","IVRT",
    "IVSW","IVWC","IVWG","IVWL","IVZA","IVZC","LMDF","LMIN",
    "LOCL","LUMF","LUMI","LUMT","MAGB","MAGR","MAMP","MANI",
    "MASF","MASK","MAXT","MCHA","MDST","MGAP","MMOD","MODD",
    "MODE","MODF","MODO","MODP","MRKB","MSKZ","MSNR","NEGS",
    "NHAR","NLIN","NOAD","NOAV","NOIS","NOPD","NOPK","NOPP",
    "NOTR","OAMP","OTMP","OVER","P3DV","P3LV","PAMP","PANG",
    "PARE","PARO","PATH","PCLS","PDEV","PDGN","PDRP","PERI",
    "PJIT","PLAN","PLAR","PLID","PLSE","PLSI","PLWD","PODU",
    "POLD","POSD","POSS","POTY","POWA","POWP","POWR","PPOS",
    "PRCD","PRDF","PRFR","PRIO","PROA","PROF","PRSA","PRSG",
    "PRSR","PRTY","PSHI","PSHT","PSPC","PSPE","PSPT","PWRL",
    "QFAC","QUAD","RADL","RADR","REAC","REFF","REFI","REFP",
    "REFU","REFV","REFX","RELB","RELH","RELW","REPT","RESI",
    "RESP","RING","RISE","RLBR","RMNS","RMPS","ROUN","RPDV",
    "RPEC","RPHF","RPLD","RPLE","RPLI","RPLX","RSPH","RSPO",
    "RSPT","RSPZ","RTRS","SASP","SATM","SBCF","SBCM","SBEV",
    "SDEL","SERL","SERM","SETT","SHFS","SIMU","SKEW","SLEW",
    "SLRA","SLRG","SLRR","SLSD","SLSL","SMPL","SMPW","SNSR",
    "SPCG","SPED","SPFR","SPGR","SPTM","SQD1","SQD2","SQD3",
    "SQTD","SQTR","SRFR","SSTP","SSTR","STAT","STIM","STMH",
    "STMO","STMP","STMR","STMZ","STOP","STPA","STPB","STPG",
    "STPR","STRD","STRT","STWD","SUSP","SVCP","SWBT","SWMO",
    "SWRA","SWTM","SYDL","SYNC","TASP","TASY","TCAP","TCUR",
    "TEIM","TEMP","TEQL","TEQT","TGTA","TGTD","TGTR","THRT",
    "TIEV","TIME","TIND","TIUN","TIWH","TJIT","TMON","TOPA",
    "TOPG","TOPR","TORQ","TPHD","TPHY","TREA","TRES","TRIG",
    "TRLV","TRMD","TRN0","TRN1","TRNO","TRNP","TRNS","TROL",
    "TRTY","TRUE","TRUN","TRWH","TSIM","TTMP","TVOL","TYPE",
    "UNDR","UUTL","UUTT","VALU","VBAC","VBAP","VBPP","VBRT",
    "VBTR","VEAO","VEDL","VEEO","VEFO","VEGF","VETF","VINS",
    "VLAB","VLAC","VLAV","VLBA","VLBC","VLCA","VLCB","VLPK",
    "VLPP","VLT0","VLT1","VLTA","VLTB","VLTC","VLTL","VLTQ",
    "VLTR","VLTS","VOLF","VOLT","VPHF","VPHM","VPKN","VPKP",
    "VRMS","WAIT","WAVE","WDLN","WDRT","WGAP","WHAT","WIND",
    "WRDC","WTRN","ZAMP","ZCRS","ZERO",};
/*
 *  MODULETYPES
 */
DECLAREC short t__cnt = T__CNT;
DECLAREC char *TCiilTxt [] = {
    "","ACS","API","ARB","ASA","DCS","DIG","DMM",
    "DWG","FNG","FTM","MBT","MFU","MTR","PAT","PCM",
    "PLG","PSS","PWM","QAL","RSV","RSY","SNG","SRS",
    "VDG",};
/*
 *  DIMS-A
 */
DECLAREC short d__cnt = D__CNT;
DECLAREC char *DCiilTxt [] = {
    "","1553A","1553B","AAI","AAN","ABI","ABN","AIR",
    "ALLLS","ALWAYS","AMI","AR429","ARDC","BIP","CONMD","CONRT",
    "CRC16","CRC32","CSDB","CSM","CSN","CSOC","CTS","DAVA",
    "EIA530","ERCO","EVPRTY","FUEL","GAI","GAN","GAS","HDB",
    "HDLC","ICAN","ICAO","IEEE488","IMHI","IMLO","LIN","LNGTH",
    "LOG","MASTR","MIP","MONTR","N2","NEG","NOPRTY","NRZ",
    "ODPRTY","OFF","OIL","ON","PADD","PAND","PARA","POR",
    "POS","PRIM","PRTY","PSUB","PXOR","REDT","REWD","ROI",
    "RON","RS232","RS422","RS423","RS449","RS485","RTCON","RTRT",
    "RZ","SERL","SERM","SLAVE","SYNC","T0ANDT1","T0ARMT1","T0ORT1",
    "TLKLS","TR","UART","V35","WADC","WATER","XON",};
/*
 *  DIMS-B
 */
DECLAREC short r__cnt = R__CNT;
DECLAREC char *RCiilTxt [] = {
    "",};
extern int doACPS_1_Setup (double CURR, double FREQ, double VOLT);
extern int doDCPS_1_Setup (double CURR, double VOLT);
extern int doDSP_1_Setup (double VOLT, double MinVOLT, double MaxVOLT, long EVOU, short EVSL);
extern int doDSP_10_Setup (double MAXT, double MinTIME, double MaxTIME, long EVTF, long EVTT);
extern double doDSP_10_Fetch (void);
extern int doDSP_2_Setup (double VOLT, double MinVOLT, double MaxVOLT, long EVOU, short EVSL);
extern int doDWG_1_Setup (long ITER, double MAXT, double SDEL, double SNSR, double STMR, long EVXM, long EVWH, short SIMU, short DTMD);
extern int doDWG_1_Fetch (long* pFLTC, int nCntFLTC);
extern int doDWG_1_Init (void);
extern int doDWG_2_Setup (long* pPinsSTIM, int nCntPinsSTIM, double VOLTLL0, double VOLTLL1, double WDLN, short PCLS, short TYPE, long REPT);
extern int doDWG_2_Init (long* pPinsSTIM, int nCntPinsSTIM);
extern int doDWG_2_Load (PBYTE* pSTIM, int nSizSTIM, int nCntSTIM);
extern int doDWG_3_Setup (long MinVALU, long MaxVALU, double VOLTLL0, double VOLTLL1, double WDLN, short PCLS, short TYPE, long EVWH, long FLTC, short ISTI);
extern int doDWG_3_Fetch (PBYTE* pVALU, int nSizVALU, int nCntVALU, PBYTE* pERRO, int nSizERRO, int nCntERRO, long* pERRI, int nCntERRI, short* pISTI, int nCntISTI);
extern int doDWG_3_Init (long* pPinsVALU, int nCntPinsVALU);
extern int doDWG_3_Load (PBYTE* pREFX, int nSizREFX, int nCntREFX, PBYTE* pMASK, int nSizMASK, int nCntMASK, PBYTE* pMSKZ, int nSizMSKZ, int nCntMSKZ);
extern int doSIM_21_Setup (double BITR, double MAXT, double WDLN, short PRCD, short STRD, short TROL, short WAIT, short BUSM, short BUSS);
extern int doSIM_22_Setup (double BITR, double MAXT, double WDLN, short PRCD, short STRD, short TROL, short WAIT, short BUSM, short BUSS);
extern int doSIM_23_Setup (double BITR, double WDLN, short TROL, long UUTL, long TEQT, short BUSM, long* pDATA, int nCntDATA);
extern int doSIM_23_Fetch (void);
extern int doSIM_24_Setup (double BITR, double WDLN, short TROL, long UUTL, long TEQT, short BUSM);
extern int doWAVEFORM_1_Setup (double* pSTIM, int nCntSTIM, double FREQ, double SMPW, double VOLT);
extern int doWAVEFORM_2_Setup (double MinSMPL, double MaxSMPL, double SMPW, double VOLT);
extern int doWAVEFORM_2_Fetch (double* pSMPL, int nCntSMPL);
extern int CCALLBACK DoLoad (void);
extern int CCALLBACK DoUnload (void);
extern int TypeErr (const char *);
extern int BusErr (const char *);
DECLAREC char *DevTxt [] = {
    "",
    "!Controller:CH0",
    "ACPS:CH1",
    "DCPS:CH1",
    "DSP:CH1",
    "DSP:CH10",
    "DSP:CH2",
    "DWG:CH1",
    "DWG:CH2",
    "DWG:CH3",
    "SIM:CH21",
    "SIM:CH22",
    "SIM:CH23",
    "SIM:CH24",
    "WAVEFORM:CH1",
    "WAVEFORM:CH2",
};
DECLAREC int DevCnt = 16;
int CCALLBACK wrapFunc1(void)
{
    DATUM *p;
    int nRtn = 1;
    double CURR = - DBL_MAX;
    double FREQ = - DBL_MAX;
    double VOLT = - DBL_MAX;
    if (p = GetDatum(M_CURR, K_SET)) {
        if (DatTyp(p) != DECV)  return TypeErr("current");
        CURR = (double) p->dat_val.dat_dec[0];
    }
    if (p = GetDatum(M_FREQ, K_SET)) {
        if (DatTyp(p) != DECV)  return TypeErr("freq");
        FREQ = (double) p->dat_val.dat_dec[0];
    }
    if (p = GetDatum(M_VOLT, K_SET)) {
        if (DatTyp(p) != DECV)  return TypeErr("voltage");
        VOLT = (double) p->dat_val.dat_dec[0];
    }
    nRtn = doACPS_1_Setup (CURR, FREQ, VOLT);
    if (nRtn < 0)   BusErr ("ACPS");
    return 0;
}
int CCALLBACK wrapFunc2(void)
{
    DATUM *p;
    int nRtn = 1;
    double CURR = - DBL_MAX;
    double VOLT = - DBL_MAX;
    if (p = GetDatum(M_CURR, K_SET)) {
        if (DatTyp(p) != DECV)  return TypeErr("current");
        CURR = (double) p->dat_val.dat_dec[0];
    }
    if (p = GetDatum(M_VOLT, K_SET)) {
        if (DatTyp(p) != DECV)  return TypeErr("voltage");
        VOLT = (double) p->dat_val.dat_dec[0];
    }
    nRtn = doDCPS_1_Setup (CURR, VOLT);
    if (nRtn < 0)   BusErr ("DCPS");
    return 0;
}
int CCALLBACK wrapFunc3(void)
{
    DATUM *p;
    int nRtn = 1;
    double VOLT = - DBL_MAX;
    double MinVOLT = - DBL_MAX;
    double MaxVOLT = - DBL_MAX;
    long EVOU = LONG_MIN;
    short EVSL = SHRT_MIN;
    if (p = GetDatum(M_VOLT, K_SET)) {
        if (DatTyp(p) != DECV)  return TypeErr("voltage");
        VOLT = (double) p->dat_val.dat_dec[0];
    }
    if (p = GetDatum(M_VOLT, K_SRN)) {
        if (DatTyp(p) != DECV)  return TypeErr("voltage min");
        MinVOLT = (double) p->dat_val.dat_dec[0];
    }
    if (p = GetDatum(M_VOLT, K_SRX)) {
        if (DatTyp(p) != DECV)  return TypeErr("voltage max");
        MaxVOLT = (double) p->dat_val.dat_dec[0];
    }
    if (p = GetDatum(M_EVOU, K_SET)) {
        if (DatTyp(p) != INTV)  return TypeErr("event-out");
        EVOU = (long) p->dat_val.dat_int[0];
    }
    if (p = GetDatum(M_EVSL, K_SET)) {
        if (DatTyp(p) != DSCV)  return TypeErr("event-slope");
        EVSL = (short) p->dat_val.dat_dsc[0];
    }
    nRtn = doDSP_1_Setup (VOLT, MinVOLT, MaxVOLT, EVOU, EVSL);
    if (nRtn < 0)   BusErr ("DSP");
    return 0;
}
int CCALLBACK wrapFunc4(void)
{
    DATUM *p;
    int nRtn = 1;
    double MAXT = - DBL_MAX;
    double MinTIME = - DBL_MAX;
    double MaxTIME = - DBL_MAX;
    long EVTF = LONG_MIN;
    long EVTT = LONG_MIN;
    if (p = GetDatum(M_MAXT, K_SET)) {
        if (DatTyp(p) != DECV)  return TypeErr("max-time");
        MAXT = (double) p->dat_val.dat_dec[0];
    }
    if (p = GetDatum(M_TIME, K_SRN)) {
        if (DatTyp(p) != DECV)  return TypeErr("time min");
        MinTIME = (double) p->dat_val.dat_dec[0];
    }
    if (p = GetDatum(M_TIME, K_SRX)) {
        if (DatTyp(p) != DECV)  return TypeErr("time max");
        MaxTIME = (double) p->dat_val.dat_dec[0];
    }
    if (p = GetDatum(M_EVTF, K_SET)) {
        if (DatTyp(p) != INTV)  return TypeErr("event-time-from");
        EVTF = (long) p->dat_val.dat_int[0];
    }
    if (p = GetDatum(M_EVTT, K_SET)) {
        if (DatTyp(p) != INTV)  return TypeErr("event-time-to");
        EVTT = (long) p->dat_val.dat_int[0];
    }
    nRtn = doDSP_10_Setup (MAXT, MinTIME, MaxTIME, EVTF, EVTT);
    if (nRtn < 0)   BusErr ("DSP");
    return 0;
}
int CCALLBACK wrapFunc5(void)
{
    DATUM *p;
    int nRtn = 1;
    p = FthDat();
    if (FthMod () == M_TIME) {
        if (DatTyp(p) != DECV)  return TypeErr("time");
        p->dat_val.dat_dec[0] = doDSP_10_Fetch ();
    }
    FthCnt(nRtn);
    return 0;
}
int CCALLBACK wrapFunc6(void)
{
    DATUM *p;
    int nRtn = 1;
    double VOLT = - DBL_MAX;
    double MinVOLT = - DBL_MAX;
    double MaxVOLT = - DBL_MAX;
    long EVOU = LONG_MIN;
    short EVSL = SHRT_MIN;
    if (p = GetDatum(M_VOLT, K_SET)) {
        if (DatTyp(p) != DECV)  return TypeErr("voltage");
        VOLT = (double) p->dat_val.dat_dec[0];
    }
    if (p = GetDatum(M_VOLT, K_SRN)) {
        if (DatTyp(p) != DECV)  return TypeErr("voltage min");
        MinVOLT = (double) p->dat_val.dat_dec[0];
    }
    if (p = GetDatum(M_VOLT, K_SRX)) {
        if (DatTyp(p) != DECV)  return TypeErr("voltage max");
        MaxVOLT = (double) p->dat_val.dat_dec[0];
    }
    if (p = GetDatum(M_EVOU, K_SET)) {
        if (DatTyp(p) != INTV)  return TypeErr("event-out");
        EVOU = (long) p->dat_val.dat_int[0];
    }
    if (p = GetDatum(M_EVSL, K_SET)) {
        if (DatTyp(p) != DSCV)  return TypeErr("event-slope");
        EVSL = (short) p->dat_val.dat_dsc[0];
    }
    nRtn = doDSP_2_Setup (VOLT, MinVOLT, MaxVOLT, EVOU, EVSL);
    if (nRtn < 0)   BusErr ("DSP");
    return 0;
}
int CCALLBACK wrapFunc7(void)
{
    DATUM *p;
    int nRtn = 1;
    long ITER = LONG_MIN;
    double MAXT = - DBL_MAX;
    double SDEL = - DBL_MAX;
    double SNSR = - DBL_MAX;
    double STMR = - DBL_MAX;
    long EVXM = LONG_MIN;
    long EVWH = LONG_MIN;
    short SIMU = SHRT_MIN;
    short DTMD = SHRT_MIN;
    if (p = GetDatum(M_ITER, K_SET)) {
        if (DatTyp(p) != INTV)  return TypeErr("iterate");
        ITER = (long) p->dat_val.dat_int[0];
    }
    if (p = GetDatum(M_MAXT, K_SET)) {
        if (DatTyp(p) != DECV)  return TypeErr("max-time");
        MAXT = (double) p->dat_val.dat_dec[0];
    }
    if (p = GetDatum(M_SDEL, K_SET)) {
        if (DatTyp(p) != DECV)  return TypeErr("sense-delay");
        SDEL = (double) p->dat_val.dat_dec[0];
    }
    if (p = GetDatum(M_SNSR, K_SET)) {
        if (DatTyp(p) != DECV)  return TypeErr("sense-rate");
        SNSR = (double) p->dat_val.dat_dec[0];
    }
    if (p = GetDatum(M_STMR, K_SET)) {
        if (DatTyp(p) != DECV)  return TypeErr("stim-rate");
        STMR = (double) p->dat_val.dat_dec[0];
    }
    if (p = GetDatum(M_EVXM, K_SET)) {
        if (DatTyp(p) != INTV)  return TypeErr("event-stim");
        EVXM = (long) p->dat_val.dat_int[0];
    }
    if (p = GetDatum(M_EVWH, K_SET)) {
        if (DatTyp(p) != INTV)  return TypeErr("event-when");
        EVWH = (long) p->dat_val.dat_int[0];
    }
    if (p = GetDatum(M_SIMU, K_SET)) {
        if (DatTyp(p) != DSCV)  return TypeErr("do-simultaneous");
        SIMU = (short) p->dat_val.dat_dsc[0];
    }
    if (p = GetDatum(M_DTMD, K_SET)) {
        if (DatTyp(p) != DSCV)  return TypeErr("do-timed-digital");
        DTMD = (short) p->dat_val.dat_dsc[0];
    }
    nRtn = doDWG_1_Setup (ITER, MAXT, SDEL, SNSR, STMR, EVXM, EVWH, SIMU, DTMD);
    if (nRtn < 0)   BusErr ("DWG");
    return 0;
}
int CCALLBACK wrapFunc8(void)
{
    DATUM *p;
    int nRtn = 1;
    long* pFLTC =  NULL; int nCntFLTC = 0;
    p = FthDat();
    if (FthMod () == M_FLTC) {
        if (DatTyp(p) != INTV)  return TypeErr("fault-count");
        pFLTC = (long*) p->dat_val.dat_int;
        nCntFLTC = DatCnt (p);
    }
    nRtn = doDWG_1_Fetch (pFLTC, nCntFLTC);
    if (nRtn < 0)   BusErr ("DWG");
    FthCnt(nRtn);
    return 0;
}
int CCALLBACK wrapFunc9(void)
{
    if (doDWG_1_Init() < 0) BusErr ("DWG");
    return 0;
}
int CCALLBACK wrapFunc10(void)
{
    DATUM *p;
    int nRtn = 1;
    long* pPinsSTIM =  NULL; int nCntPinsSTIM = 0;
    double VOLTLL0 = - DBL_MAX;
    double VOLTLL1 = - DBL_MAX;
    double WDLN = - DBL_MAX;
    short PCLS = SHRT_MIN;
    short TYPE = SHRT_MIN;
    long REPT = LONG_MIN;
    if (p = GetDatum(M_STIM, K_CDP)) {
        if (DatTyp(p) != INTV)  return TypeErr("stim pins");
        pPinsSTIM = (long*) p->dat_val.dat_int;
        nCntPinsSTIM = DatCnt (p);
    }
    if (p = GetDatum((M_VOLT | LL0), K_SET)) {
        if (DatTyp(p) != DECV)  return TypeErr("voltage (LL0)");
        VOLTLL0 = (double) p->dat_val.dat_dec[0];
    }
    if (p = GetDatum((M_VOLT | LL1), K_SET)) {
        if (DatTyp(p) != DECV)  return TypeErr("voltage (LL1)");
        VOLTLL1 = (double) p->dat_val.dat_dec[0];
    }
    if (p = GetDatum(M_WDLN, K_SET)) {
        if (DatTyp(p) != DECV)  return TypeErr("word-length");
        WDLN = (double) p->dat_val.dat_dec[0];
    }
    if (p = GetDatum(M_PCLS, K_SET)) {
        if (DatTyp(p) != DSCV)  return TypeErr("pulse-class");
        PCLS = (short) p->dat_val.dat_dsc[0];
    }
    if (p = GetDatum(M_TYPE, K_SET)) {
        if (DatTyp(p) != DSCV)  return TypeErr("type");
        TYPE = (short) p->dat_val.dat_dsc[0];
    }
    if (p = GetDatum(M_REPT, K_SET)) {
        if (DatTyp(p) != INTV)  return TypeErr("repeat");
        REPT = (long) p->dat_val.dat_int[0];
    }
    nRtn = doDWG_2_Setup (pPinsSTIM, nCntPinsSTIM, VOLTLL0, VOLTLL1, WDLN, PCLS, TYPE, REPT);
    if (nRtn < 0)   BusErr ("DWG");
    return 0;
}
int CCALLBACK wrapFunc11(void)
{
    DATUM *p;
    int nRtn = 1;
    long* pPinsSTIM =  NULL; int nCntPinsSTIM = 0;
    if (p = GetDatum(M_STIM, K_FDD)) {
        if (DatTyp(p) != INTV)  return TypeErr("stim pins");
        pPinsSTIM = (long*) p->dat_val.dat_int;
        nCntPinsSTIM = DatCnt (p);
    }
    nRtn = doDWG_2_Init (pPinsSTIM, nCntPinsSTIM);
    if (nRtn < 0)   BusErr ("DWG");
    return 0;
}
int CCALLBACK wrapFunc12(void)
{
    DATUM *p;
    int nRtn = 1;
    PBYTE* pSTIM =  NULL; int nSizSTIM = 0; int nCntSTIM = 0;
    if (lod_mode == M_STIM) {
        p = GetDatum(M_STIM, K_LOD);
        if (DatTyp(p) != DIGV)  return TypeErr("stim");
        pSTIM = (PBYTE*) p->dat_val.dat_dig;
        nSizSTIM = DatSiz (p);
        nCntSTIM = DatCnt (p);
    }
    nRtn = doDWG_2_Load (pSTIM, nSizSTIM, nCntSTIM);
    if (nRtn < 0)   BusErr ("DWG");
    return 0;
}
int CCALLBACK wrapFunc13(void)
{
    DATUM *p;
    int nRtn = 1;
    long MinVALU = LONG_MIN;
    long MaxVALU = LONG_MIN;
    double VOLTLL0 = - DBL_MAX;
    double VOLTLL1 = - DBL_MAX;
    double WDLN = - DBL_MAX;
    short PCLS = SHRT_MIN;
    short TYPE = SHRT_MIN;
    long EVWH = LONG_MIN;
    long FLTC = LONG_MIN;
    short ISTI = SHRT_MIN;
    if (p = GetDatum(M_VALU, K_SRN)) {
        if (DatTyp(p) != INTV)  return TypeErr("value min");
        MinVALU = (long) p->dat_val.dat_int[0];
    }
    if (p = GetDatum(M_VALU, K_SRX)) {
        if (DatTyp(p) != INTV)  return TypeErr("value max");
        MaxVALU = (long) p->dat_val.dat_int[0];
    }
    if (p = GetDatum((M_VOLT | LL0), K_SET)) {
        if (DatTyp(p) != DECV)  return TypeErr("voltage (LL0)");
        VOLTLL0 = (double) p->dat_val.dat_dec[0];
    }
    if (p = GetDatum((M_VOLT | LL1), K_SET)) {
        if (DatTyp(p) != DECV)  return TypeErr("voltage (LL1)");
        VOLTLL1 = (double) p->dat_val.dat_dec[0];
    }
    if (p = GetDatum(M_WDLN, K_SET)) {
        if (DatTyp(p) != DECV)  return TypeErr("word-length");
        WDLN = (double) p->dat_val.dat_dec[0];
    }
    if (p = GetDatum(M_PCLS, K_SET)) {
        if (DatTyp(p) != DSCV)  return TypeErr("pulse-class");
        PCLS = (short) p->dat_val.dat_dsc[0];
    }
    if (p = GetDatum(M_TYPE, K_SET)) {
        if (DatTyp(p) != DSCV)  return TypeErr("type");
        TYPE = (short) p->dat_val.dat_dsc[0];
    }
    if (p = GetDatum(M_EVWH, K_SET)) {
        if (DatTyp(p) != INTV)  return TypeErr("event-when");
        EVWH = (long) p->dat_val.dat_int[0];
    }
    if (p = GetDatum(M_FLTC, K_SET)) {
        if (DatTyp(p) != INTV)  return TypeErr("fault-count");
        FLTC = (long) p->dat_val.dat_int[0];
    }
    if (p = GetDatum(M_ISTI, K_SET)) {
        if (DatTyp(p) != BLNV)  return TypeErr("illegal-state-indicator");
        ISTI = (short) p->dat_val.dat_bln[0];
    }
    nRtn = doDWG_3_Setup (MinVALU, MaxVALU, VOLTLL0, VOLTLL1, WDLN, PCLS, TYPE, EVWH, FLTC, ISTI);
    if (nRtn < 0)   BusErr ("DWG");
    return 0;
}
int CCALLBACK wrapFunc14(void)
{
    DATUM *p;
    int nRtn = 1;
    PBYTE* pVALU =  NULL; int nSizVALU = 0; int nCntVALU = 0;
    PBYTE* pERRO =  NULL; int nSizERRO = 0; int nCntERRO = 0;
    long* pERRI =  NULL; int nCntERRI = 0;
    short* pISTI =  NULL; int nCntISTI = 0;
    p = FthDat();
    if (FthMod () == M_VALU) {
        if (DatTyp(p) != DIGV)  return TypeErr("value");
        pVALU = (PBYTE*) p->dat_val.dat_dig;
        nSizVALU = DatSiz (p);
        nCntVALU = DatCnt (p);
    }
    if (FthMod () == M_ERRO) {
        if (DatTyp(p) != DIGV)  return TypeErr("error");
        pERRO = (PBYTE*) p->dat_val.dat_dig;
        nSizERRO = DatSiz (p);
        nCntERRO = DatCnt (p);
    }
    if (FthMod () == M_ERRI) {
        if (DatTyp(p) != INTV)  return TypeErr("error-index");
        pERRI = (long*) p->dat_val.dat_int;
        nCntERRI = DatCnt (p);
    }
    if (FthMod () == M_ISTI) {
        if (DatTyp(p) != BLNV)  return TypeErr("illegal-state-indicator");
        pISTI = (short*) p->dat_val.dat_bln;
        nCntISTI = DatCnt (p);
    }
    nRtn = doDWG_3_Fetch (pVALU, nSizVALU, nCntVALU, pERRO, nSizERRO, nCntERRO, pERRI, nCntERRI, pISTI, nCntISTI);
    if (nRtn < 0)   BusErr ("DWG");
    FthCnt(nRtn);
    return 0;
}
int CCALLBACK wrapFunc15(void)
{
    DATUM *p;
    int nRtn = 1;
    long* pPinsVALU =  NULL; int nCntPinsVALU = 0;
    if (p = GetDatum(M_VALU, K_FDD)) {
        if (DatTyp(p) != INTV)  return TypeErr("value pins");
        pPinsVALU = (long*) p->dat_val.dat_int;
        nCntPinsVALU = DatCnt (p);
    }
    nRtn = doDWG_3_Init (pPinsVALU, nCntPinsVALU);
    if (nRtn < 0)   BusErr ("DWG");
    return 0;
}
int CCALLBACK wrapFunc16(void)
{
    DATUM *p;
    int nRtn = 1;
    PBYTE* pREFX =  NULL; int nSizREFX = 0; int nCntREFX = 0;
    PBYTE* pMASK =  NULL; int nSizMASK = 0; int nCntMASK = 0;
    PBYTE* pMSKZ =  NULL; int nSizMSKZ = 0; int nCntMSKZ = 0;
    if (lod_mode == M_REFX) {
        p = GetDatum(M_REFX, K_LOD);
        if (DatTyp(p) != DIGV)  return TypeErr("ref");
        pREFX = (PBYTE*) p->dat_val.dat_dig;
        nSizREFX = DatSiz (p);
        nCntREFX = DatCnt (p);
    }
    if (lod_mode == M_MASK) {
        p = GetDatum(M_MASK, K_LOD);
        if (DatTyp(p) != DIGV)  return TypeErr("mask-one");
        pMASK = (PBYTE*) p->dat_val.dat_dig;
        nSizMASK = DatSiz (p);
        nCntMASK = DatCnt (p);
    }
    if (lod_mode == M_MSKZ) {
        p = GetDatum(M_MSKZ, K_LOD);
        if (DatTyp(p) != DIGV)  return TypeErr("mask-zero");
        pMSKZ = (PBYTE*) p->dat_val.dat_dig;
        nSizMSKZ = DatSiz (p);
        nCntMSKZ = DatCnt (p);
    }
    nRtn = doDWG_3_Load (pREFX, nSizREFX, nCntREFX, pMASK, nSizMASK, nCntMASK, pMSKZ, nSizMSKZ, nCntMSKZ);
    if (nRtn < 0)   BusErr ("DWG");
    return 0;
}
int CCALLBACK wrapFunc17(void)
{
    DATUM *p;
    int nRtn = 1;
    double BITR = - DBL_MAX;
    double MAXT = - DBL_MAX;
    double WDLN = - DBL_MAX;
    short PRCD = SHRT_MIN;
    short STRD = SHRT_MIN;
    short TROL = SHRT_MIN;
    short WAIT = SHRT_MIN;
    short BUSM = SHRT_MIN;
    short BUSS = SHRT_MIN;
    if (p = GetDatum(M_BITR, K_SET)) {
        if (DatTyp(p) != DECV)  return TypeErr("bit-rate");
        BITR = (double) p->dat_val.dat_dec[0];
    }
    if (p = GetDatum(M_MAXT, K_SET)) {
        if (DatTyp(p) != DECV)  return TypeErr("max-time");
        MAXT = (double) p->dat_val.dat_dec[0];
    }
    if (p = GetDatum(M_WDLN, K_SET)) {
        if (DatTyp(p) != DECV)  return TypeErr("word-length");
        WDLN = (double) p->dat_val.dat_dec[0];
    }
    if (p = GetDatum(M_PRCD, K_SET)) {
        if (DatTyp(p) != DSCV)  return TypeErr("proceed");
        PRCD = (short) p->dat_val.dat_dsc[0];
    }
    if (p = GetDatum(M_STRD, K_SET)) {
        if (DatTyp(p) != DSCV)  return TypeErr("standard");
        STRD = (short) p->dat_val.dat_dsc[0];
    }
    if (p = GetDatum(M_TROL, K_SET)) {
        if (DatTyp(p) != DSCV)  return TypeErr("test-equip-role");
        TROL = (short) p->dat_val.dat_dsc[0];
    }
    if (p = GetDatum(M_WAIT, K_SET)) {
        if (DatTyp(p) != DSCV)  return TypeErr("wait");
        WAIT = (short) p->dat_val.dat_dsc[0];
    }
    if (p = GetDatum(M_BUSM, K_SET)) {
        if (DatTyp(p) != DSCV)  return TypeErr("bus-mode");
        BUSM = (short) p->dat_val.dat_dsc[0];
    }
    if (p = GetDatum(M_BUSS, K_SET)) {
        if (DatTyp(p) != DSCV)  return TypeErr("bus-spec");
        BUSS = (short) p->dat_val.dat_dsc[0];
    }
    nRtn = doSIM_21_Setup (BITR, MAXT, WDLN, PRCD, STRD, TROL, WAIT, BUSM, BUSS);
    if (nRtn < 0)   BusErr ("SIM");
    return 0;
}
int CCALLBACK wrapFunc18(void)
{
    DATUM *p;
    int nRtn = 1;
    double BITR = - DBL_MAX;
    double MAXT = - DBL_MAX;
    double WDLN = - DBL_MAX;
    short PRCD = SHRT_MIN;
    short STRD = SHRT_MIN;
    short TROL = SHRT_MIN;
    short WAIT = SHRT_MIN;
    short BUSM = SHRT_MIN;
    short BUSS = SHRT_MIN;
    if (p = GetDatum(M_BITR, K_SET)) {
        if (DatTyp(p) != DECV)  return TypeErr("bit-rate");
        BITR = (double) p->dat_val.dat_dec[0];
    }
    if (p = GetDatum(M_MAXT, K_SET)) {
        if (DatTyp(p) != DECV)  return TypeErr("max-time");
        MAXT = (double) p->dat_val.dat_dec[0];
    }
    if (p = GetDatum(M_WDLN, K_SET)) {
        if (DatTyp(p) != DECV)  return TypeErr("word-length");
        WDLN = (double) p->dat_val.dat_dec[0];
    }
    if (p = GetDatum(M_PRCD, K_SET)) {
        if (DatTyp(p) != DSCV)  return TypeErr("proceed");
        PRCD = (short) p->dat_val.dat_dsc[0];
    }
    if (p = GetDatum(M_STRD, K_SET)) {
        if (DatTyp(p) != DSCV)  return TypeErr("standard");
        STRD = (short) p->dat_val.dat_dsc[0];
    }
    if (p = GetDatum(M_TROL, K_SET)) {
        if (DatTyp(p) != DSCV)  return TypeErr("test-equip-role");
        TROL = (short) p->dat_val.dat_dsc[0];
    }
    if (p = GetDatum(M_WAIT, K_SET)) {
        if (DatTyp(p) != DSCV)  return TypeErr("wait");
        WAIT = (short) p->dat_val.dat_dsc[0];
    }
    if (p = GetDatum(M_BUSM, K_SET)) {
        if (DatTyp(p) != DSCV)  return TypeErr("bus-mode");
        BUSM = (short) p->dat_val.dat_dsc[0];
    }
    if (p = GetDatum(M_BUSS, K_SET)) {
        if (DatTyp(p) != DSCV)  return TypeErr("bus-spec");
        BUSS = (short) p->dat_val.dat_dsc[0];
    }
    nRtn = doSIM_22_Setup (BITR, MAXT, WDLN, PRCD, STRD, TROL, WAIT, BUSM, BUSS);
    if (nRtn < 0)   BusErr ("SIM");
    return 0;
}
int CCALLBACK wrapFunc19(void)
{
    DATUM *p;
    int nRtn = 1;
    double BITR = - DBL_MAX;
    double WDLN = - DBL_MAX;
    short TROL = SHRT_MIN;
    long UUTL = LONG_MIN;
    long TEQT = LONG_MIN;
    short BUSM = SHRT_MIN;
    long* pDATA =  NULL; int nCntDATA = 0;
    if (p = GetDatum(M_BITR, K_SET)) {
        if (DatTyp(p) != DECV)  return TypeErr("bit-rate");
        BITR = (double) p->dat_val.dat_dec[0];
    }
    if (p = GetDatum(M_WDLN, K_SET)) {
        if (DatTyp(p) != DECV)  return TypeErr("word-length");
        WDLN = (double) p->dat_val.dat_dec[0];
    }
    if (p = GetDatum(M_TROL, K_SET)) {
        if (DatTyp(p) != DSCV)  return TypeErr("test-equip-role");
        TROL = (short) p->dat_val.dat_dsc[0];
    }
    if (p = GetDatum(M_UUTL, K_SET)) {
        if (DatTyp(p) != INTV)  return TypeErr("uut-listener");
        UUTL = (long) p->dat_val.dat_int[0];
    }
    if (p = GetDatum(M_TEQT, K_SET)) {
        if (DatTyp(p) != INTV)  return TypeErr("test-equip-talker");
        TEQT = (long) p->dat_val.dat_int[0];
    }
    if (p = GetDatum(M_BUSM, K_SET)) {
        if (DatTyp(p) != DSCV)  return TypeErr("bus-mode");
        BUSM = (short) p->dat_val.dat_dsc[0];
    }
    if (p = GetDatum(M_DATA, K_SET)) {
        if (DatTyp(p) != INTV)  return TypeErr("data");
        pDATA = (long*) p->dat_val.dat_int;
        nCntDATA = DatCnt (p);
    }
    nRtn = doSIM_23_Setup (BITR, WDLN, TROL, UUTL, TEQT, BUSM, pDATA, nCntDATA);
    if (nRtn < 0)   BusErr ("SIM");
    return 0;
}
int CCALLBACK wrapFunc20(void)
{
    if (doSIM_23_Fetch() < 0)   BusErr ("SIM");
    return 0;
}
int CCALLBACK wrapFunc21(void)
{
    DATUM *p;
    int nRtn = 1;
    double BITR = - DBL_MAX;
    double WDLN = - DBL_MAX;
    short TROL = SHRT_MIN;
    long UUTL = LONG_MIN;
    long TEQT = LONG_MIN;
    short BUSM = SHRT_MIN;
    if (p = GetDatum(M_BITR, K_SET)) {
        if (DatTyp(p) != DECV)  return TypeErr("bit-rate");
        BITR = (double) p->dat_val.dat_dec[0];
    }
    if (p = GetDatum(M_WDLN, K_SET)) {
        if (DatTyp(p) != DECV)  return TypeErr("word-length");
        WDLN = (double) p->dat_val.dat_dec[0];
    }
    if (p = GetDatum(M_TROL, K_SET)) {
        if (DatTyp(p) != DSCV)  return TypeErr("test-equip-role");
        TROL = (short) p->dat_val.dat_dsc[0];
    }
    if (p = GetDatum(M_UUTL, K_SET)) {
        if (DatTyp(p) != INTV)  return TypeErr("uut-listener");
        UUTL = (long) p->dat_val.dat_int[0];
    }
    if (p = GetDatum(M_TEQT, K_SET)) {
        if (DatTyp(p) != INTV)  return TypeErr("test-equip-talker");
        TEQT = (long) p->dat_val.dat_int[0];
    }
    if (p = GetDatum(M_BUSM, K_SET)) {
        if (DatTyp(p) != DSCV)  return TypeErr("bus-mode");
        BUSM = (short) p->dat_val.dat_dsc[0];
    }
    nRtn = doSIM_24_Setup (BITR, WDLN, TROL, UUTL, TEQT, BUSM);
    if (nRtn < 0)   BusErr ("SIM");
    return 0;
}
int CCALLBACK wrapFunc22(void)
{
    DATUM *p;
    int nRtn = 1;
    double* pSTIM =  NULL; int nCntSTIM = 0;
    double FREQ = - DBL_MAX;
    double SMPW = - DBL_MAX;
    double VOLT = - DBL_MAX;
    if (p = GetDatum(M_STIM, K_SET)) {
        if (DatTyp(p) != DECV)  return TypeErr("stim");
        pSTIM = (double*) p->dat_val.dat_dec;
        nCntSTIM = DatCnt (p);
    }
    if (p = GetDatum(M_FREQ, K_SET)) {
        if (DatTyp(p) != DECV)  return TypeErr("freq");
        FREQ = (double) p->dat_val.dat_dec[0];
    }
    if (p = GetDatum(M_SMPW, K_SET)) {
        if (DatTyp(p) != DECV)  return TypeErr("sample-width");
        SMPW = (double) p->dat_val.dat_dec[0];
    }
    if (p = GetDatum(M_VOLT, K_SET)) {
        if (DatTyp(p) != DECV)  return TypeErr("voltage");
        VOLT = (double) p->dat_val.dat_dec[0];
    }
    nRtn = doWAVEFORM_1_Setup (pSTIM, nCntSTIM, FREQ, SMPW, VOLT);
    if (nRtn < 0)   BusErr ("WAVEFORM");
    return 0;
}
int CCALLBACK wrapFunc23(void)
{
    DATUM *p;
    int nRtn = 1;
    double MinSMPL = - DBL_MAX;
    double MaxSMPL = - DBL_MAX;
    double SMPW = - DBL_MAX;
    double VOLT = - DBL_MAX;
    if (p = GetDatum(M_SMPL, K_SRN)) {
        if (DatTyp(p) != DECV)  return TypeErr("sample min");
        MinSMPL = (double) p->dat_val.dat_dec[0];
    }
    if (p = GetDatum(M_SMPL, K_SRX)) {
        if (DatTyp(p) != DECV)  return TypeErr("sample max");
        MaxSMPL = (double) p->dat_val.dat_dec[0];
    }
    if (p = GetDatum(M_SMPW, K_SET)) {
        if (DatTyp(p) != DECV)  return TypeErr("sample-width");
        SMPW = (double) p->dat_val.dat_dec[0];
    }
    if (p = GetDatum(M_VOLT, K_SET)) {
        if (DatTyp(p) != DECV)  return TypeErr("voltage");
        VOLT = (double) p->dat_val.dat_dec[0];
    }
    nRtn = doWAVEFORM_2_Setup (MinSMPL, MaxSMPL, SMPW, VOLT);
    if (nRtn < 0)   BusErr ("WAVEFORM");
    return 0;
}
int CCALLBACK wrapFunc24(void)
{
    DATUM *p;
    int nRtn = 1;
    double* pSMPL =  NULL; int nCntSMPL = 0;
    p = FthDat();
    if (FthMod () == M_SMPL) {
        if (DatTyp(p) != DECV)  return TypeErr("sample");
        pSMPL = (double*) p->dat_val.dat_dec;
        nCntSMPL = DatCnt (p);
    }
    nRtn = doWAVEFORM_2_Fetch (pSMPL, nCntSMPL);
    if (nRtn < 0)   BusErr ("WAVEFORM");
    FthCnt(nRtn);
    return 0;
}
/*
 *  Device Init
 */
EXTERNC MODDAT *BldModDat (MODDAT *, short);
DECLAREC int DevInx ()
{
    MODDAT *p_mod;
    DevDat = (DEVDAT *) Room (DevCnt *  sizeof (DEVDAT));
/*
 *  !Controller:CH0
 */
    p_mod = (MODDAT *) 0;
    DevDat[1].d_modlst = p_mod;
    DevDat[1].d_fncP = 0;
    DevDat[1].d_acts[A_CON] = DoLoad;
    DevDat[1].d_acts[A_DIS] = DoUnload;
/*
 *  ACPS:CH1
 */
    p_mod = (MODDAT *) 0;
    p_mod = BldModDat (p_mod, (short) M_CURR);
    p_mod = BldModDat (p_mod, (short) M_FREQ);
    p_mod = BldModDat (p_mod, (short) M_VOLT);
    DevDat[2].d_modlst = p_mod;
    DevDat[2].d_fncP = 1;
    DevDat[2].d_acts[A_FNC] = wrapFunc1;
/*
 *  DCPS:CH1
 */
    p_mod = (MODDAT *) 0;
    p_mod = BldModDat (p_mod, (short) M_CURR);
    p_mod = BldModDat (p_mod, (short) M_VOLT);
    DevDat[3].d_modlst = p_mod;
    DevDat[3].d_fncP = 1;
    DevDat[3].d_acts[A_FNC] = wrapFunc2;
/*
 *  DSP:CH1
 */
    p_mod = (MODDAT *) 0;
    p_mod = BldModDat (p_mod, (short) M_VOLT);
    p_mod = BldModDat (p_mod, (short) M_EVOU);
    p_mod = BldModDat (p_mod, (short) M_EVSL);
    DevDat[4].d_modlst = p_mod;
    DevDat[4].d_fncP = 1;
    DevDat[4].d_acts[A_FNC] = wrapFunc3;
/*
 *  DSP:CH10
 */
    p_mod = (MODDAT *) 0;
    p_mod = BldModDat (p_mod, (short) M_MAXT);
    p_mod = BldModDat (p_mod, (short) M_TIME);
    p_mod = BldModDat (p_mod, (short) M_EVTF);
    p_mod = BldModDat (p_mod, (short) M_EVTT);
    DevDat[5].d_modlst = p_mod;
    DevDat[5].d_fncP = 10;
    DevDat[5].d_acts[A_FNC] = wrapFunc4;
    DevDat[5].d_acts[A_FTH] = wrapFunc5;
/*
 *  DSP:CH2
 */
    p_mod = (MODDAT *) 0;
    p_mod = BldModDat (p_mod, (short) M_VOLT);
    p_mod = BldModDat (p_mod, (short) M_EVOU);
    p_mod = BldModDat (p_mod, (short) M_EVSL);
    DevDat[6].d_modlst = p_mod;
    DevDat[6].d_fncP = 2;
    DevDat[6].d_acts[A_FNC] = wrapFunc6;
/*
 *  DWG:CH1
 */
    p_mod = (MODDAT *) 0;
    p_mod = BldModDat (p_mod, (short) M_ITER);
    p_mod = BldModDat (p_mod, (short) M_MAXT);
    p_mod = BldModDat (p_mod, (short) M_SDEL);
    p_mod = BldModDat (p_mod, (short) M_SNSR);
    p_mod = BldModDat (p_mod, (short) M_STMR);
    p_mod = BldModDat (p_mod, (short) M_EVXM);
    p_mod = BldModDat (p_mod, (short) M_EVWH);
    p_mod = BldModDat (p_mod, (short) M_FLTC);
    p_mod = BldModDat (p_mod, (short) M_SIMU);
    p_mod = BldModDat (p_mod, (short) M_DTMD);
    DevDat[7].d_modlst = p_mod;
    DevDat[7].d_fncP = 1;
    DevDat[7].d_acts[A_FNC] = wrapFunc7;
    DevDat[7].d_acts[A_FTH] = wrapFunc8;
    DevDat[7].d_acts[A_INX] = wrapFunc9;
/*
 *  DWG:CH2
 */
    p_mod = (MODDAT *) 0;
    p_mod = BldModDat (p_mod, (short) M_STIM);
    p_mod = BldModDat (p_mod, (short) M_VOLT);
    p_mod = BldModDat (p_mod, (short) M_WDLN);
    p_mod = BldModDat (p_mod, (short) M_PCLS);
    p_mod = BldModDat (p_mod, (short) M_TYPE);
    p_mod = BldModDat (p_mod, (short) M_REPT);
    DevDat[8].d_modlst = p_mod;
    DevDat[8].d_fncP = 2;
    DevDat[8].d_acts[A_FNC] = wrapFunc10;
    DevDat[8].d_acts[A_INX] = wrapFunc11;
    DevDat[8].d_acts[A_LOD] = wrapFunc12;
/*
 *  DWG:CH3
 */
    p_mod = (MODDAT *) 0;
    p_mod = BldModDat (p_mod, (short) M_VALU);
    p_mod = BldModDat (p_mod, (short) M_VOLT);
    p_mod = BldModDat (p_mod, (short) M_WDLN);
    p_mod = BldModDat (p_mod, (short) M_PCLS);
    p_mod = BldModDat (p_mod, (short) M_TYPE);
    p_mod = BldModDat (p_mod, (short) M_EVWH);
    p_mod = BldModDat (p_mod, (short) M_ERRO);
    p_mod = BldModDat (p_mod, (short) M_ERRI);
    p_mod = BldModDat (p_mod, (short) M_FLTC);
    p_mod = BldModDat (p_mod, (short) M_MASK);
    p_mod = BldModDat (p_mod, (short) M_MSKZ);
    p_mod = BldModDat (p_mod, (short) M_REFX);
    p_mod = BldModDat (p_mod, (short) M_ISTI);
    DevDat[9].d_modlst = p_mod;
    DevDat[9].d_fncP = 3;
    DevDat[9].d_acts[A_FNC] = wrapFunc13;
    DevDat[9].d_acts[A_FTH] = wrapFunc14;
    DevDat[9].d_acts[A_INX] = wrapFunc15;
    DevDat[9].d_acts[A_LOD] = wrapFunc16;
/*
 *  SIM:CH21
 */
    p_mod = (MODDAT *) 0;
    p_mod = BldModDat (p_mod, (short) M_BITR);
    p_mod = BldModDat (p_mod, (short) M_MAXT);
    p_mod = BldModDat (p_mod, (short) M_WDLN);
    p_mod = BldModDat (p_mod, (short) M_PRCD);
    p_mod = BldModDat (p_mod, (short) M_STRD);
    p_mod = BldModDat (p_mod, (short) M_TROL);
    p_mod = BldModDat (p_mod, (short) M_WAIT);
    p_mod = BldModDat (p_mod, (short) M_BUSM);
    p_mod = BldModDat (p_mod, (short) M_BUSS);
    DevDat[10].d_modlst = p_mod;
    DevDat[10].d_fncP = 21;
    DevDat[10].d_acts[A_FNC] = wrapFunc17;
/*
 *  SIM:CH22
 */
    p_mod = (MODDAT *) 0;
    p_mod = BldModDat (p_mod, (short) M_BITR);
    p_mod = BldModDat (p_mod, (short) M_MAXT);
    p_mod = BldModDat (p_mod, (short) M_WDLN);
    p_mod = BldModDat (p_mod, (short) M_PRCD);
    p_mod = BldModDat (p_mod, (short) M_STRD);
    p_mod = BldModDat (p_mod, (short) M_TROL);
    p_mod = BldModDat (p_mod, (short) M_WAIT);
    p_mod = BldModDat (p_mod, (short) M_BUSM);
    p_mod = BldModDat (p_mod, (short) M_BUSS);
    DevDat[11].d_modlst = p_mod;
    DevDat[11].d_fncP = 22;
    DevDat[11].d_acts[A_FNC] = wrapFunc18;
/*
 *  SIM:CH23
 */
    p_mod = (MODDAT *) 0;
    p_mod = BldModDat (p_mod, (short) M_BITR);
    p_mod = BldModDat (p_mod, (short) M_DATA);
    p_mod = BldModDat (p_mod, (short) M_WDLN);
    p_mod = BldModDat (p_mod, (short) M_TROL);
    p_mod = BldModDat (p_mod, (short) M_UUTL);
    p_mod = BldModDat (p_mod, (short) M_TEQT);
    p_mod = BldModDat (p_mod, (short) M_BUSM);
    DevDat[12].d_modlst = p_mod;
    DevDat[12].d_fncP = 23;
    DevDat[12].d_acts[A_FNC] = wrapFunc19;
    DevDat[12].d_acts[A_FTH] = wrapFunc20;
/*
 *  SIM:CH24
 */
    p_mod = (MODDAT *) 0;
    p_mod = BldModDat (p_mod, (short) M_BITR);
    p_mod = BldModDat (p_mod, (short) M_DATA);
    p_mod = BldModDat (p_mod, (short) M_WDLN);
    p_mod = BldModDat (p_mod, (short) M_TROL);
    p_mod = BldModDat (p_mod, (short) M_UUTL);
    p_mod = BldModDat (p_mod, (short) M_TEQT);
    p_mod = BldModDat (p_mod, (short) M_BUSM);
    DevDat[13].d_modlst = p_mod;
    DevDat[13].d_fncP = 24;
    DevDat[13].d_acts[A_FNC] = wrapFunc21;
/*
 *  WAVEFORM:CH1
 */
    p_mod = (MODDAT *) 0;
    p_mod = BldModDat (p_mod, (short) M_FREQ);
    p_mod = BldModDat (p_mod, (short) M_SMPW);
    p_mod = BldModDat (p_mod, (short) M_STIM);
    p_mod = BldModDat (p_mod, (short) M_VOLT);
    DevDat[14].d_modlst = p_mod;
    DevDat[14].d_fncP = 1;
    DevDat[14].d_acts[A_FNC] = wrapFunc22;
/*
 *  WAVEFORM:CH2
 */
    p_mod = (MODDAT *) 0;
    p_mod = BldModDat (p_mod, (short) M_SMPL);
    p_mod = BldModDat (p_mod, (short) M_SMPW);
    p_mod = BldModDat (p_mod, (short) M_VOLT);
    DevDat[15].d_modlst = p_mod;
    DevDat[15].d_fncP = 2;
    DevDat[15].d_acts[A_FNC] = wrapFunc23;
    DevDat[15].d_acts[A_FTH] = wrapFunc24;
    return 0;
}
