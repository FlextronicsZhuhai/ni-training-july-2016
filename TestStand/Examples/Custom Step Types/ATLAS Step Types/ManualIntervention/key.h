#ifndef _LEXKEY_H_
#define _LEXKEY_H_
/*
 *  VERBS
 */
#define V_APP     (   1)    /*  apply                           */
#define V_ARM     (   2)    /*  arm                             */
#define V_CAL     (   3)    /*  calculate                       */
#define V_CHN     (   4)    /*  change                          */
#define V_CMP     (   5)    /*  compare                         */
#define V_CON     (   6)    /*  connect                         */
#define V_CRE     (   7)    /*  create                          */
#define V_DCL     (   8)    /*  declare                         */
#define V_DEF     (   9)    /*  define                          */
#define V_DEL     (  10)    /*  delete                          */
#define V_DIS     (  11)    /*  disconnect                      */
#define V_DO      (  12)    /*  do                              */
#define V_DSB     (  13)    /*  disable                         */
#define V_ELS     (  14)    /*  else                            */
#define V_ENB     (  15)    /*  enable                          */
#define V_END     (  16)    /*  end                             */
#define V_EST     (  17)    /*  establish                       */
#define V_FIN     (  18)    /*  finish                          */
#define V_FOR     (  19)    /*  for                             */
#define V_FTH     (  20)    /*  fetch                           */
#define V_GTO     (  21)    /*  go to                           */
#define V_IDY     (  22)    /*  identify                        */
#define V_IF      (  23)    /*  if                              */
#define V_INC     (  24)    /*  include                         */
#define V_INP     (  25)    /*  input                           */
#define V_INX     (  26)    /*  initiate                        */
#define V_LVE     (  27)    /*  leave                           */
#define V_MEA     (  28)    /*  measure                         */
#define V_MON     (  29)    /*  monitor                         */
#define V_OUT     (  30)    /*  output                          */
#define V_PFM     (  31)    /*  perform                         */
#define V_PRV     (  32)    /*  prove                           */
#define V_RD      (  33)    /*  read                            */
#define V_REM     (  34)    /*  remove                          */
#define V_REQ     (  35)    /*  require                         */
#define V_RES     (  36)    /*  resume                          */
#define V_RST     (  37)    /*  reset                           */
#define V_SET     (  38)    /*  setup                           */
#define V_SNS     (  39)    /*  sense                           */
#define V_STI     (  40)    /*  stimulate                       */
#define V_TRM     (  41)    /*  terminate                       */
#define V_UPD     (  42)    /*  update                          */
#define V_VER     (  43)    /*  verify                          */
#define V_WHL     (  44)    /*  while                           */
#define V_WTF     (  45)    /*  wait for                        */
#define V_XTN     (  46)    /*  extend                          */
#define V__CNT    (  47)    /*  Symbol count                    */
/*
 *  NOUNS
 */
#define N_ACS     (   1)    /*  ac signal                       */
#define N_ADF     (   2)    /*  adf                             */
#define N_AMB     (   3)    /*  ambient conditions              */
#define N_AMS     (   4)    /*  am signal                       */
#define N_ATC     (   5)    /*  atc                             */
#define N_BUS     (   6)    /*  bus protocol                    */
#define N_COM     (   7)    /*  common                          */
#define N_DCF     (   8)    /*  digital configuration           */
#define N_DCS     (   9)    /*  dc signal                       */
#define N_DGT     (  10)    /*  digital test                    */
#define N_DIS     (  11)    /*  displacement                    */
#define N_DME     (  12)    /*  dme                             */
#define N_DOP     (  13)    /*  doppler                         */
#define N_EAR     (  14)    /*  earth                           */
#define N_EMF     (  15)    /*  em field                        */
#define N_EVS     (  16)    /*  events                          */
#define N_EVT     (  17)    /*  event                           */
#define N_EXC     (  18)    /*  exchange                        */
#define N_FLU     (  19)    /*  fluid signal                    */
#define N_FMS     (  20)    /*  fm signal                       */
#define N_HEA     (  21)    /*  heat                            */
#define N_IFF     (  22)    /*  iff                             */
#define N_ILS     (  23)    /*  ils                             */
#define N_IMP     (  24)    /*  impedance                       */
#define N_LCL     (  25)    /*  logic control                   */
#define N_LDT     (  26)    /*  logic data                      */
#define N_LGT     (  27)    /*  light                           */
#define N_LLD     (  28)    /*  logic load                      */
#define N_LRF     (  29)    /*  logic reference                 */
#define N_MAN     (  30)    /*  manometric                      */
#define N_PAC     (  31)    /*  pulsed ac                       */
#define N_PAM     (  32)    /*  pam                             */
#define N_PAT     (  33)    /*  pulsed ac train                 */
#define N_PDC     (  34)    /*  pulsed dc                       */
#define N_PDP     (  35)    /*  pulsed doppler                  */
#define N_PDT     (  36)    /*  pulsed dc train                 */
#define N_PMS     (  37)    /*  pm signal                       */
#define N_RDN     (  38)    /*  random noise                    */
#define N_RDS     (  39)    /*  radar signal                    */
#define N_RPS     (  40)    /*  ramp signal                     */
#define N_RSL     (  41)    /*  resolver                        */
#define N_RTN     (  42)    /*  rotation                        */
#define N_SCS     (  43)    /*  sup car signal                  */
#define N_SFT     (  44)    /*  selftest                        */
#define N_SHT     (  45)    /*  short                           */
#define N_SIM     (  46)    /*  simultaneous                    */
#define N_SQW     (  47)    /*  square wave                     */
#define N_STM     (  48)    /*  stepper motor                   */
#define N_STS     (  49)    /*  step signal                     */
#define N_SYN     (  50)    /*  synchro                         */
#define N_TAC     (  51)    /*  tacan                           */
#define N_TDG     (  52)    /*  timed digital                   */
#define N_TED     (  53)    /*  turbine engine data             */
#define N_TMI     (  54)    /*  time interval                   */
#define N_TMR     (  55)    /*  timer                           */
#define N_TRI     (  56)    /*  triangular wave signal          */
#define N_VBR     (  57)    /*  vibration                       */
#define N_VOR     (  58)    /*  vor                             */
#define N_WAV     (  59)    /*  waveform                        */
#define N__CNT    (  60)    /*  Symbol count                    */
/*
 *  MODIFIERS
 */
#define M_ACCF    (   1)    /*  ac-comp-freq                    */
#define M_ACCO    (   2)    /*  ac-coupling                     */
#define M_ACCP    (   3)    /*  ac-comp                         */
#define M_AGER    (   4)    /*  age-rate                        */
#define M_ALTI    (   5)    /*  alt                             */
#define M_ALTR    (   6)    /*  alt-rate                        */
#define M_AMCP    (   7)    /*  am-comp                         */
#define M_AMMC    (   8)    /*  ampl-mod-c                      */
#define M_AMMF    (   9)    /*  ampl-mod-f                      */
#define M_AMPL    (  10)    /*  ampl-mod                        */
#define M_AMSH    (  11)    /*  am-shift                        */
#define M_ANAC    (  12)    /*  angle-accel                     */
#define M_ANAX    (  13)    /*  angle-accel-x                   */
#define M_ANAY    (  14)    /*  angle-accel-y                   */
#define M_ANAZ    (  15)    /*  angle-accel-z                   */
#define M_ANGL    (  16)    /*  angle                           */
#define M_ANGP    (  17)    /*  angle-phi                       */
#define M_ANGT    (  18)    /*  angle-theta                     */
#define M_ANGX    (  19)    /*  angle-x                         */
#define M_ANGY    (  20)    /*  angle-y                         */
#define M_ANGZ    (  21)    /*  angle-z                         */
#define M_ANRT    (  22)    /*  angle-rate                      */
#define M_ANRX    (  23)    /*  angle-rate-x                    */
#define M_ANRY    (  24)    /*  angle-rate-y                    */
#define M_ANRZ    (  25)    /*  angle-rate-z                    */
#define M_ANSD    (  26)    /*  ant-speed-dev                   */
#define M_APER    (  27)    /*  aperture                        */
#define M_ATMS    (  28)    /*  atmos                           */
#define M_ATTN    (  29)    /*  atten                           */
#define M_BAND    (  30)    /*  bandwidth                       */
#define M_BARP    (  31)    /*  barometric-press                */
#define M_BITP    (  32)    /*  bit-period                      */
#define M_BITR    (  33)    /*  bit-rate                        */
#define M_BTRN    (  34)    /*  bit-transition                  */
#define M_BURD    (  35)    /*  burst-droop                     */
#define M_BURR    (  36)    /*  burst-rep-rate                  */
#define M_BURS    (  37)    /*  burst                           */
#define M_BUSM    (  38)    /*  bus-mode                        */
#define M_BUSP    (  39)    /*  bus-prot                        */
#define M_BUSS    (  40)    /*  bus-spec                        */
#define M_CAMP    (  41)    /*  car-ampl                        */
#define M_CAPA    (  42)    /*  cap                             */
#define M_CCOM    (  43)    /*  count-command                   */
#define M_CDAT    (  44)    /*  count-data                      */
#define M_CFRQ    (  45)    /*  car-freq                        */
#define M_CHAN    (  46)    /*  channel                         */
#define M_CHID    (  47)    /*  channel-ident                   */
#define M_CHRM    (  48)    /*  car-harmonics                   */
#define M_CMDW    (  49)    /*  command-word                    */
#define M_CMPL    (  50)    /*  compl                           */
#define M_CMWB    (  51)    /*  command-word-bit                */
#define M_COMD    (  52)    /*  command                         */
#define M_COND    (  53)    /*  conductance                     */
#define M_COUN    (  54)    /*  count                           */
#define M_CPHS    (  55)    /*  car-phase                       */
#define M_CPKN    (  56)    /*  current-p-neg                   */
#define M_CPKP    (  57)    /*  current-p-pos                   */
#define M_CRAB    (  58)    /*  current-phase-ab                */
#define M_CRAC    (  59)    /*  current-phase-ac                */
#define M_CRBA    (  60)    /*  current-phase-ba                */
#define M_CRBC    (  61)    /*  current-phase-bc                */
#define M_CRCA    (  62)    /*  current-phase-ca                */
#define M_CRCB    (  63)    /*  current-phase-cb                */
#define M_CRCT    (  64)    /*  crc-type                        */
#define M_CRFR    (  65)    /*  center-freq                     */
#define M_CRPA    (  66)    /*  current-phase-a                 */
#define M_CRPB    (  67)    /*  current-phase-b                 */
#define M_CRPC    (  68)    /*  current-phase-c                 */
#define M_CRSD    (  69)    /*  car-resid                       */
#define M_CRSF    (  70)    /*  crest-factor                    */
#define M_CSTS    (  71)    /*  count-status                    */
#define M_CUPK    (  72)    /*  current-p                       */
#define M_CUPP    (  73)    /*  current-pp                      */
#define M_CUR0    (  74)    /*  current-zero                    */
#define M_CUR1    (  75)    /*  current-one                     */
#define M_CURA    (  76)    /*  current-av                      */
#define M_CURI    (  77)    /*  current-inst                    */
#define M_CURL    (  78)    /*  current-lmt                     */
#define M_CURQ    (  79)    /*  current-quies                   */
#define M_CURR    (  80)    /*  current                         */
#define M_CURT    (  81)    /*  current-trms                    */
#define M_CWLV    (  82)    /*  cw-level                        */
#define M_DATA    (  83)    /*  data                            */
#define M_DATL    (  84)    /*  data-word-length                */
#define M_DATP    (  85)    /*  data-word-parity                */
#define M_DATS    (  86)    /*  data-word-sync                  */
#define M_DATT    (  87)    /*  data-word-tr                    */
#define M_DATW    (  88)    /*  data-word                       */
#define M_DBLI    (  89)    /*  dbl-int                         */
#define M_DBND    (  90)    /*  doppler-bandwidth               */
#define M_DBRC    (  91)    /*  debris-count                    */
#define M_DBRS    (  92)    /*  debris-size                     */
#define M_DCCO    (  93)    /*  dc-coupling                     */
#define M_DCOF    (  94)    /*  dc-offset                       */
#define M_DDMD    (  95)    /*  ddm                             */
#define M_DELA    (  96)    /*  delay                           */
#define M_DEWP    (  97)    /*  dewpoint                        */
#define M_DIGS    (  98)    /*  dig-spec                        */
#define M_DIST    (  99)    /*  distance                        */
#define M_DMDS    ( 100)    /*  dominant-mod-sig                */
#define M_DPFR    ( 101)    /*  doppler-freq                    */
#define M_DPSH    ( 102)    /*  doppler-shift                   */
#define M_DROO    ( 103)    /*  droop                           */
#define M_DSFC    ( 104)    /*  diss-factor                     */
#define M_DSTR    ( 105)    /*  distance-r                      */
#define M_DSTX    ( 106)    /*  distance-x                      */
#define M_DSTY    ( 107)    /*  distance-y                      */
#define M_DSTZ    ( 108)    /*  distance-z                      */
#define M_DTMD    ( 109)    /*  do-timed-digital                */
#define M_DTOR    ( 110)    /*  distortion                      */
#define M_DUTY    ( 111)    /*  duty-cycle                      */
#define M_DVST    ( 112)    /*  device-status                   */
#define M_DWBT    ( 113)    /*  data-word-bit                   */
#define M_EFCY    ( 114)    /*  efficacy                        */
#define M_EFFI    ( 115)    /*  eff                             */
#define M_EINM    ( 116)    /*  event-interval                  */
#define M_ERRI    ( 117)    /*  error-index                     */
#define M_ERRO    ( 118)    /*  error                           */
#define M_EVAO    ( 119)    /*  event-after-occurrences         */
#define M_EVDL    ( 120)    /*  event-delay                     */
#define M_EVEO    ( 121)    /*  event-each-occurrence           */
#define M_EVEV    ( 122)    /*  event-every                     */
#define M_EVFO    ( 123)    /*  event-first-occurrence          */
#define M_EVGB    ( 124)    /*  event-gated-by                  */
#define M_EVGF    ( 125)    /*  event-gate-from                 */
#define M_EVGR    ( 126)    /*  event-gate-forever              */
#define M_EVGT    ( 127)    /*  event-gate-to                   */
#define M_EVOU    ( 128)    /*  event-out                       */
#define M_EVSB    ( 129)    /*  event-sync-bit                  */
#define M_EVSF    ( 130)    /*  event-sync-freq                 */
#define M_EVSL    ( 131)    /*  event-slope                     */
#define M_EVSW    ( 132)    /*  event-sync-word                 */
#define M_EVTF    ( 133)    /*  event-time-from                 */
#define M_EVTI    ( 134)    /*  event-indicator                 */
#define M_EVTR    ( 135)    /*  event-time-forever              */
#define M_EVTT    ( 136)    /*  event-time-to                   */
#define M_EVUN    ( 137)    /*  event-until                     */
#define M_EVWH    ( 138)    /*  event-when                      */
#define M_EVXE    ( 139)    /*  event-sense                     */
#define M_EVXM    ( 140)    /*  event-stim                      */
#define M_EXAE    ( 141)    /*  except at every                 */
#define M_EXNM    ( 142)    /*  exchange-number                 */
#define M_FALL    ( 143)    /*  fall-time                       */
#define M_FDST    ( 144)    /*  field-strength                  */
#define M_FLTC    ( 145)    /*  fault-count                     */
#define M_FLTS    ( 146)    /*  fault-test                      */
#define M_FLUT    ( 147)    /*  fluid-type                      */
#define M_FMCP    ( 148)    /*  fm-comp                         */
#define M_FRCE    ( 149)    /*  force                           */
#define M_FRCR    ( 150)    /*  force-rate                      */
#define M_FREQ    ( 151)    /*  freq                            */
#define M_FRQ0    ( 152)    /*  freq-zero                       */
#define M_FRQ1    ( 153)    /*  freq-one                        */
#define M_FRQD    ( 154)    /*  freq-dev                        */
#define M_FRQP    ( 155)    /*  freq-pairing                    */
#define M_FRQQ    ( 156)    /*  freq-quies                      */
#define M_FRQW    ( 157)    /*  freq-window                     */
#define M_FUEL    ( 158)    /*  fuel-supply                     */
#define M_FXDN    ( 159)    /*  flux-dens                       */
#define M_FXIP    ( 160)    /*  flux-dens-in-phase              */
#define M_FXQD    ( 161)    /*  flux-dens-quad                  */
#define M_GSLP    ( 162)    /*  glide-slope                     */
#define M_HAPW    ( 163)    /*  harm-power                      */
#define M_HARM    ( 164)    /*  harmonics                       */
#define M_HARP    ( 165)    /*  harm-phase                      */
#define M_HARV    ( 166)    /*  harm-voltage                    */
#define M_HDSK    ( 167)    /*  handshake                       */
#define M_HIZZ    ( 168)    /*  hiz                             */
#define M_HMDF    ( 169)    /*  hi-mod-freq                     */
#define M_HUMY    ( 170)    /*  humidity                        */
#define M_IASP    ( 171)    /*  ias                             */
#define M_IBHP    ( 172)    /*  invalid-bit-count-hi-pos        */
#define M_IBHW    ( 173)    /*  invalid-bit-count-hi-word       */
#define M_IBLP    ( 174)    /*  invalid-bit-count-lo-pos        */
#define M_IBLW    ( 175)    /*  invalid-bit-count-lo-word       */
#define M_ICOW    ( 176)    /*  invalid-contig-word             */
#define M_ICWB    ( 177)    /*  invalid-command-word-bit        */
#define M_IDSE    ( 178)    /*  ident-sig-ep                    */
#define M_IDSF    ( 179)    /*  ident-sig-freq                  */
#define M_IDSG    ( 180)    /*  ident-sig                       */
#define M_IDSM    ( 181)    /*  ident-sig-mod                   */
#define M_IDSP    ( 182)    /*  invalid-data-word-sync-pos      */
#define M_IDWB    ( 183)    /*  invalid-data-word-bit           */
#define M_IJIT    ( 184)    /*  int-jitter                      */
#define M_ILLU    ( 185)    /*  illum                           */
#define M_IMHP    ( 186)    /*  invalid-manchester-hi-pos       */
#define M_IMHW    ( 187)    /*  invalid-manchester-hi-word      */
#define M_IMLP    ( 188)    /*  invalid-manchester-lo-pos       */
#define M_IMLW    ( 189)    /*  invalid-manchester-lo-word      */
#define M_INDU    ( 190)    /*  ind                             */
#define M_IOCG    ( 191)    /*  invalid-ovr-command-word-gap    */
#define M_IPHS    ( 192)    /*  in-phase                        */
#define M_IRAT    ( 193)    /*  int-rate                        */
#define M_ISTI    ( 194)    /*  illegal-state-indicator         */
#define M_ISWB    ( 195)    /*  invalid-status-word-bit         */
#define M_ITER    ( 196)    /*  iterate                         */
#define M_IVCG    ( 197)    /*  invalid-contig-gap              */
#define M_IVCS    ( 198)    /*  invalid-command-word-sync       */
#define M_IVCW    ( 199)    /*  invalid-command-word            */
#define M_IVDL    ( 200)    /*  invalid-data-word-length        */
#define M_IVDP    ( 201)    /*  invalid-data-word-parity        */
#define M_IVDS    ( 202)    /*  invalid-data-word-sync          */
#define M_IVDT    ( 203)    /*  invalid-data-word-tr            */
#define M_IVDW    ( 204)    /*  invalid-data-word               */
#define M_IVMG    ( 205)    /*  invalid-message-gap             */
#define M_IVOA    ( 206)    /*  invalid-one-amplitude           */
#define M_IVRT    ( 207)    /*  invalid-response-time           */
#define M_IVSW    ( 208)    /*  invalid-status-word             */
#define M_IVWC    ( 209)    /*  invalid-word-count              */
#define M_IVWG    ( 210)    /*  invalid-word-gap                */
#define M_IVWL    ( 211)    /*  invalid-word-length             */
#define M_IVZA    ( 212)    /*  invalid-zero-amplitude          */
#define M_IVZC    ( 213)    /*  invalid-zero-crossing           */
#define M_LMDF    ( 214)    /*  lo-mod-freq                     */
#define M_LMIN    ( 215)    /*  lum-int                         */
#define M_LOCL    ( 216)    /*  localizer                       */
#define M_LUMF    ( 217)    /*  lum-flux                        */
#define M_LUMI    ( 218)    /*  luminance                       */
#define M_LUMT    ( 219)    /*  lum-temp                        */
#define M_MAGB    ( 220)    /*  mag-bearing                     */
#define M_MAGR    ( 221)    /*  mag-bearing-rate                */
#define M_MAMP    ( 222)    /*  mod-ampl                        */
#define M_MANI    ( 223)    /*  manual-intervention             */
#define M_MASF    ( 224)    /*  mass-flow                       */
#define M_MASK    ( 225)    /*  mask-one                        */
#define M_MAXT    ( 226)    /*  max-time                        */
#define M_MCHA    ( 227)    /*  mil-chan                        */
#define M_MDST    ( 228)    /*  message-dist                    */
#define M_MGAP    ( 229)    /*  message-gap                     */
#define M_MMOD    ( 230)    /*  mean-mod                        */
#define M_MODD    ( 231)    /*  mod-dist                        */
#define M_MODE    ( 232)    /*  mode                            */
#define M_MODF    ( 233)    /*  mod-freq                        */
#define M_MODO    ( 234)    /*  mod-offset                      */
#define M_MODP    ( 235)    /*  mod-phase                       */
#define M_MRKB    ( 236)    /*  marker-beacon                   */
#define M_MSKZ    ( 237)    /*  mask-zero                       */
#define M_MSNR    ( 238)    /*  minimum-sense-rate              */
#define M_NEGS    ( 239)    /*  neg-slope                       */
#define M_NHAR    ( 240)    /*  non-harmonics                   */
#define M_NLIN    ( 241)    /*  non-lin                         */
#define M_NOAD    ( 242)    /*  noise-ampl-dens                 */
#define M_NOAV    ( 243)    /*  noise-av                        */
#define M_NOIS    ( 244)    /*  noise                           */
#define M_NOPD    ( 245)    /*  noise-pwr-dens                  */
#define M_NOPK    ( 246)    /*  noise-p                         */
#define M_NOPP    ( 247)    /*  noise-pp                        */
#define M_NOTR    ( 248)    /*  noise-trms                      */
#define M_OAMP    ( 249)    /*  one-amplitude                   */
#define M_OTMP    ( 250)    /*  oper-temp                       */
#define M_OVER    ( 251)    /*  overshoot                       */
#define M_P3DV    ( 252)    /*  p3-dev                          */
#define M_P3LV    ( 253)    /*  p3-level                        */
#define M_PAMP    ( 254)    /*  p-ampl                          */
#define M_PANG    ( 255)    /*  phase-angle                     */
#define M_PARE    ( 256)    /*  parity-even                     */
#define M_PARO    ( 257)    /*  parity-odd                      */
#define M_PATH    ( 258)    /*  path                            */
#define M_PCLS    ( 259)    /*  pulse-class                     */
#define M_PDEV    ( 260)    /*  phase-dev                       */
#define M_PDGN    ( 261)    /*  peak-degen                      */
#define M_PDRP    ( 262)    /*  pair-droop                      */
#define M_PERI    ( 263)    /*  period                          */
#define M_PJIT    ( 264)    /*  phase-jit                       */
#define M_PLAN    ( 265)    /*  pla                             */
#define M_PLAR    ( 266)    /*  pla-rate                        */
#define M_PLID    ( 267)    /*  pulse-ident                     */
#define M_PLSE    ( 268)    /*  pulses-excl                     */
#define M_PLSI    ( 269)    /*  pulses-incl                     */
#define M_PLWD    ( 270)    /*  pulse-width                     */
#define M_PODU    ( 271)    /*  pollution-duration              */
#define M_POLD    ( 272)    /*  pollution-data                  */
#define M_POSD    ( 273)    /*  pollution-start-delay           */
#define M_POSS    ( 274)    /*  pos-slope                       */
#define M_POTY    ( 275)    /*  pollution-type                  */
#define M_POWA    ( 276)    /*  power-av                        */
#define M_POWP    ( 277)    /*  power-p                         */
#define M_POWR    ( 278)    /*  power                           */
#define M_PPOS    ( 279)    /*  pulse-posn                      */
#define M_PRCD    ( 280)    /*  proceed                         */
#define M_PRDF    ( 281)    /*  power-diff                      */
#define M_PRFR    ( 282)    /*  prf                             */
#define M_PRIO    ( 283)    /*  priority                        */
#define M_PROA    ( 284)    /*  press-osc-ampl                  */
#define M_PROF    ( 285)    /*  press-osc-freq                  */
#define M_PRSA    ( 286)    /*  press-a                         */
#define M_PRSG    ( 287)    /*  press-g                         */
#define M_PRSR    ( 288)    /*  press-rate                      */
#define M_PRTY    ( 289)    /*  parity                          */
#define M_PSHI    ( 290)    /*  phase-shift                     */
#define M_PSHT    ( 291)    /*  preshoot                        */
#define M_PSPC    ( 292)    /*  pair-spacing                    */
#define M_PSPE    ( 293)    /*  pulse-spect                     */
#define M_PSPT    ( 294)    /*  pulse-spect-threshold           */
#define M_PWRL    ( 295)    /*  pwr-lmt                         */
#define M_QFAC    ( 296)    /*  q                               */
#define M_QUAD    ( 297)    /*  quad                            */
#define M_RADL    ( 298)    /*  radial                          */
#define M_RADR    ( 299)    /*  radial-rate                     */
#define M_REAC    ( 300)    /*  reactance                       */
#define M_REFF    ( 301)    /*  ref-freq                        */
#define M_REFI    ( 302)    /*  ref-inertial                    */
#define M_REFP    ( 303)    /*  ref-power                       */
#define M_REFU    ( 304)    /*  ref-uut                         */
#define M_REFV    ( 305)    /*  ref-volt                        */
#define M_REFX    ( 306)    /*  ref                             */
#define M_RELB    ( 307)    /*  rel-bearing                     */
#define M_RELH    ( 308)    /*  relative-humidity               */
#define M_RELW    ( 309)    /*  relative-wind                   */
#define M_REPT    ( 310)    /*  repeat                          */
#define M_RESI    ( 311)    /*  res                             */
#define M_RESP    ( 312)    /*  resp                            */
#define M_RING    ( 313)    /*  ringing                         */
#define M_RISE    ( 314)    /*  rise-time                       */
#define M_RLBR    ( 315)    /*  rel-bearing-rate                */
#define M_RMNS    ( 316)    /*  ramp-neg-slope                  */
#define M_RMPS    ( 317)    /*  ramp-pos-slope                  */
#define M_ROUN    ( 318)    /*  rounding                        */
#define M_RPDV    ( 319)    /*  range-pulse-dev                 */
#define M_RPEC    ( 320)    /*  range-pulse-echo                */
#define M_RPHF    ( 321)    /*  ref-phase-freq                  */
#define M_RPLD    ( 322)    /*  ref-pulses-dev                  */
#define M_RPLE    ( 323)    /*  reply-eff                       */
#define M_RPLI    ( 324)    /*  ref-pulses-incl                 */
#define M_RPLX    ( 325)    /*  ref-pulses-excl                 */
#define M_RSPH    ( 326)    /*  resp-hiz                        */
#define M_RSPO    ( 327)    /*  resp-one                        */
#define M_RSPT    ( 328)    /*  response-time                   */
#define M_RSPZ    ( 329)    /*  resp-zero                       */
#define M_RTRS    ( 330)    /*  rotor-speed                     */
#define M_SASP    ( 331)    /*  sample-spacing                  */
#define M_SATM    ( 332)    /*  sample-time                     */
#define M_SBCF    ( 333)    /*  sub-car-freq                    */
#define M_SBCM    ( 334)    /*  sub-car-mod                     */
#define M_SBEV    ( 335)    /*  strobe-to-event                 */
#define M_SDEL    ( 336)    /*  sense-delay                     */
#define M_SERL    ( 337)    /*  serial-lsb-first                */
#define M_SERM    ( 338)    /*  serial-msb-first                */
#define M_SETT    ( 339)    /*  settle-time                     */
#define M_SHFS    ( 340)    /*  shaft-speed                     */
#define M_SIMU    ( 341)    /*  do-simultaneous                 */
#define M_SKEW    ( 342)    /*  skew-time                       */
#define M_SLEW    ( 343)    /*  slew-rate                       */
#define M_SLRA    ( 344)    /*  slant-range-accel               */
#define M_SLRG    ( 345)    /*  slant-range                     */
#define M_SLRR    ( 346)    /*  slant-range-rate                */
#define M_SLSD    ( 347)    /*  sls-dev                         */
#define M_SLSL    ( 348)    /*  sls-level                       */
#define M_SMPL    ( 349)    /*  sample                          */
#define M_SMPW    ( 350)    /*  sample-width                    */
#define M_SNSR    ( 351)    /*  sense-rate                      */
#define M_SPCG    ( 352)    /*  spacing                         */
#define M_SPED    ( 353)    /*  speed                           */
#define M_SPFR    ( 354)    /*  stop-freq                       */
#define M_SPGR    ( 355)    /*  spec-grav                       */
#define M_SPTM    ( 356)    /*  spec-temp                       */
#define M_SQD1    ( 357)    /*  sqtr-dist-1                     */
#define M_SQD2    ( 358)    /*  sqtr-dist-2                     */
#define M_SQD3    ( 359)    /*  sqtr-dist-3                     */
#define M_SQTD    ( 360)    /*  sqtr-dist                       */
#define M_SQTR    ( 361)    /*  sqtr-rate                       */
#define M_SRFR    ( 362)    /*  start-freq                      */
#define M_SSTP    ( 363)    /*  sample-step                     */
#define M_SSTR    ( 364)    /*  sample-start                    */
#define M_STAT    ( 365)    /*  status                          */
#define M_STIM    ( 366)    /*  stim                            */
#define M_STMH    ( 367)    /*  stim-hiz                        */
#define M_STMO    ( 368)    /*  stim-one                        */
#define M_STMP    ( 369)    /*  static-temp                     */
#define M_STMR    ( 370)    /*  stim-rate                       */
#define M_STMZ    ( 371)    /*  stim-zero                       */
#define M_STOP    ( 372)    /*  stop                            */
#define M_STPA    ( 373)    /*  static-press-a                  */
#define M_STPB    ( 374)    /*  stop-bits                       */
#define M_STPG    ( 375)    /*  static-press-g                  */
#define M_STPR    ( 376)    /*  static-press-rate               */
#define M_STRD    ( 377)    /*  standard                        */
#define M_STRT    ( 378)    /*  start                           */
#define M_STWD    ( 379)    /*  status-word                     */
#define M_SUSP    ( 380)    /*  susceptance                     */
#define M_SVCP    ( 381)    /*  save-comp                       */
#define M_SWBT    ( 382)    /*  status-word-bit                 */
#define M_SWMO    ( 383)    /*  sweep-mode                      */
#define M_SWRA    ( 384)    /*  swr                             */
#define M_SWTM    ( 385)    /*  sweep-time                      */
#define M_SYDL    ( 386)    /*  sync-delay                      */
#define M_SYNC    ( 387)    /*  sync                            */
#define M_TASP    ( 388)    /*  tas                             */
#define M_TASY    ( 389)    /*  time-asym                       */
#define M_TCAP    ( 390)    /*  temp-coeff-cap                  */
#define M_TCUR    ( 391)    /*  temp-coeff-current              */
#define M_TEIM    ( 392)    /*  test-equip-imp                  */
#define M_TEMP    ( 393)    /*  temp                            */
#define M_TEQL    ( 394)    /*  test-equip-listener             */
#define M_TEQT    ( 395)    /*  test-equip-talker               */
#define M_TGTA    ( 396)    /*  target-range-accel              */
#define M_TGTD    ( 397)    /*  target-range                    */
#define M_TGTR    ( 398)    /*  target-range-rate               */
#define M_THRT    ( 399)    /*  thrust                          */
#define M_TIEV    ( 400)    /*  time-every                      */
#define M_TIME    ( 401)    /*  time                            */
#define M_TIND    ( 402)    /*  temp-coeff-ind                  */
#define M_TIUN    ( 403)    /*  time-until                      */
#define M_TIWH    ( 404)    /*  time-when                       */
#define M_TJIT    ( 405)    /*  time-jit                        */
#define M_TMON    ( 406)    /*  test-equip-monitor              */
#define M_TOPA    ( 407)    /*  total-press-a                   */
#define M_TOPG    ( 408)    /*  total-press-g                   */
#define M_TOPR    ( 409)    /*  total-press-rate                */
#define M_TORQ    ( 410)    /*  torque                          */
#define M_TPHD    ( 411)    /*  three-phase-delta               */
#define M_TPHY    ( 412)    /*  three-phase-wye                 */
#define M_TREA    ( 413)    /*  temp-coeff-react                */
#define M_TRES    ( 414)    /*  temp-coeff-res                  */
#define M_TRIG    ( 415)    /*  trig                            */
#define M_TRLV    ( 416)    /*  trig-level                      */
#define M_TRMD    ( 417)    /*  trig-mode                       */
#define M_TRN0    ( 418)    /*  trans-zero                      */
#define M_TRN1    ( 419)    /*  trans-one                       */
#define M_TRNO    ( 420)    /*  trig-no                         */
#define M_TRNP    ( 421)    /*  trans-period                    */
#define M_TRNS    ( 422)    /*  trans-sync                      */
#define M_TROL    ( 423)    /*  test-equip-role                 */
#define M_TRTY    ( 424)    /*  trig-type                       */
#define M_TRUE    ( 425)    /*  true                            */
#define M_TRUN    ( 426)    /*  timer-until                     */
#define M_TRWH    ( 427)    /*  timer-when                      */
#define M_TSIM    ( 428)    /*  test-equip-simulate             */
#define M_TTMP    ( 429)    /*  total-temp                      */
#define M_TVOL    ( 430)    /*  temp-coeff-volt                 */
#define M_TYPE    ( 431)    /*  type                            */
#define M_UNDR    ( 432)    /*  undershoot                      */
#define M_UUTL    ( 433)    /*  uut-listener                    */
#define M_UUTT    ( 434)    /*  uut-talker                      */
#define M_VALU    ( 435)    /*  value                           */
#define M_VBAC    ( 436)    /*  vibration-accel                 */
#define M_VBAP    ( 437)    /*  vibration-ampl-p                */
#define M_VBPP    ( 438)    /*  vibration-ampl-pp               */
#define M_VBRT    ( 439)    /*  vibration-rate                  */
#define M_VBTR    ( 440)    /*  vibration-ampl-trms             */
#define M_VEAO    ( 441)    /*  event-after-occurrences-value   */
#define M_VEDL    ( 442)    /*  event-delay-value               */
#define M_VEEO    ( 443)    /*  event-each-occurrence-value     */
#define M_VEFO    ( 444)    /*  event-first-occurrence-value    */
#define M_VEGF    ( 445)    /*  event-gate-for                  */
#define M_VETF    ( 446)    /*  event-time-for                  */
#define M_VINS    ( 447)    /*  voltage-inst                    */
#define M_VLAB    ( 448)    /*  voltage-phase-ab                */
#define M_VLAC    ( 449)    /*  voltage-phase-ac                */
#define M_VLAV    ( 450)    /*  voltage-av                      */
#define M_VLBA    ( 451)    /*  voltage-phase-ba                */
#define M_VLBC    ( 452)    /*  voltage-phase-bc                */
#define M_VLCA    ( 453)    /*  voltage-phase-ca                */
#define M_VLCB    ( 454)    /*  voltage-phase-cb                */
#define M_VLPK    ( 455)    /*  voltage-p                       */
#define M_VLPP    ( 456)    /*  voltage-pp                      */
#define M_VLT0    ( 457)    /*  voltage-zero                    */
#define M_VLT1    ( 458)    /*  voltage-one                     */
#define M_VLTA    ( 459)    /*  voltage-phase-a                 */
#define M_VLTB    ( 460)    /*  voltage-phase-b                 */
#define M_VLTC    ( 461)    /*  voltage-phase-c                 */
#define M_VLTL    ( 462)    /*  volt-lmt                        */
#define M_VLTQ    ( 463)    /*  voltage-quies                   */
#define M_VLTR    ( 464)    /*  voltage-ramped                  */
#define M_VLTS    ( 465)    /*  voltage-stepped                 */
#define M_VOLF    ( 466)    /*  volume-flow                     */
#define M_VOLT    ( 467)    /*  voltage                         */
#define M_VPHF    ( 468)    /*  var-phase-freq                  */
#define M_VPHM    ( 469)    /*  var-phase-mod                   */
#define M_VPKN    ( 470)    /*  voltage-p-neg                   */
#define M_VPKP    ( 471)    /*  voltage-p-pos                   */
#define M_VRMS    ( 472)    /*  voltage-trms                    */
#define M_WAIT    ( 473)    /*  wait                            */
#define M_WAVE    ( 474)    /*  wave-length                     */
#define M_WDLN    ( 475)    /*  word-length                     */
#define M_WDRT    ( 476)    /*  word-rate                       */
#define M_WGAP    ( 477)    /*  word-gap                        */
#define M_WHAT    ( 478)    /*  what                            */
#define M_WIND    ( 479)    /*  wind-speed                      */
#define M_WRDC    ( 480)    /*  word-count                      */
#define M_WTRN    ( 481)    /*  word-transition                 */
#define M_ZAMP    ( 482)    /*  zero-amplitude                  */
#define M_ZCRS    ( 483)    /*  zero-crossing                   */
#define M_ZERO    ( 484)    /*  zero-index                      */
#define M__CNT    ( 485)    /*  Symbol count                    */
/*
 *  MODULETYPES
 */
#define T_ACS     (   1)
#define T_API     (   2)
#define T_ARB     (   3)
#define T_ASA     (   4)
#define T_DCS     (   5)
#define T_DIG     (   6)
#define T_DMM     (   7)
#define T_DWG     (   8)
#define T_FNG     (   9)
#define T_FTM     (  10)
#define T_MBT     (  11)
#define T_MFU     (  12)
#define T_MTR     (  13)
#define T_PAT     (  14)
#define T_PCM     (  15)
#define T_PLG     (  16)
#define T_PSS     (  17)
#define T_PWM     (  18)
#define T_QAL     (  19)
#define T_RSV     (  20)
#define T_RSY     (  21)
#define T_SNG     (  22)
#define T_SRS     (  23)
#define T_VDG     (  24)
#define T__CNT    (  25)    /*  Symbol count                    */
/*
 *  DIMS-A
 */
#define D_1553A   (   1)    /*  mil-1553a                       */
#define D_1553B   (   2)    /*  mil-1553b                       */
#define D_AAI     (   3)    /*  aa-i                            */
#define D_AAN     (   4)    /*  aa-n                            */
#define D_ABI     (   5)    /*  ab-i                            */
#define D_ABN     (   6)    /*  ab-n                            */
#define D_AIR     (   7)    /*  air                             */
#define D_ALLLS   (   8)    /*  all-listener                    */
#define D_ALWAYS  (   9)    /*  always                          */
#define D_AMI     (  10)    /*  ami                             */
#define D_AR429   (  11)    /*  arinc-429                       */
#define D_ARDC    (  12)    /*  ardc                            */
#define D_BIP     (  13)    /*  bip                             */
#define D_CONMD   (  14)    /*  con-mode                        */
#define D_CONRT   (  15)    /*  con-rt                          */
#define D_CRC16   (  16)    /*  crc16                           */
#define D_CRC32   (  17)    /*  crc32                           */
#define D_CSDB    (  18)    /*  csdb                            */
#define D_CSM     (  19)    /*  csm                             */
#define D_CSN     (  20)    /*  csn                             */
#define D_CSOC    (  21)    /*  consecutive-occurrences         */
#define D_CTS     (  22)    /*  cts                             */
#define D_DAVA    (  23)    /*  data-val                        */
#define D_EIA530  (  24)    /*  eia-530                         */
#define D_ERCO    (  25)    /*  error-cond                      */
#define D_EVPRTY  (  26)    /*  even                            */
#define D_FUEL    (  27)    /*  fuel                            */
#define D_GAI     (  28)    /*  ga-i                            */
#define D_GAN     (  29)    /*  ga-n                            */
#define D_GAS     (  30)    /*  gas                             */
#define D_HDB     (  31)    /*  hdb                             */
#define D_HDLC    (  32)    /*  hdlc                            */
#define D_ICAN    (  33)    /*  ican                            */
#define D_ICAO    (  34)    /*  icao                            */
#define D_IEEE488 (  35)    /*  ieee-488                        */
#define D_IMHI    (  36)    /*  hi                              */
#define D_IMLO    (  37)    /*  lo                              */
#define D_LIN     (  38)    /*  lin                             */
#define D_LNGTH   (  39)    /*  length                          */
#define D_LOG     (  40)    /*  log                             */
#define D_MASTR   (  41)    /*  master                          */
#define D_MIP     (  42)    /*  mip                             */
#define D_MONTR   (  43)    /*  monitor                         */
#define D_N2      (  44)    /*  n2                              */
#define D_NEG     (  45)    /*  neg                             */
#define D_NOPRTY  (  46)    /*  none                            */
#define D_NRZ     (  47)    /*  nrz                             */
#define D_ODPRTY  (  48)    /*  odd                             */
#define D_OFF     (  49)    /*  off                             */
#define D_OIL     (  50)    /*  oil                             */
#define D_ON      (  51)    /*  on                              */
#define D_PADD    (  52)    /*  pollution-add                   */
#define D_PAND    (  53)    /*  pollution-and                   */
#define D_PARA    (  54)    /*  parallel                        */
#define D_POR     (  55)    /*  pollution-or                    */
#define D_POS     (  56)    /*  pos                             */
#define D_PRIM    (  57)    /*  primary                         */
#define D_PRTY    (  58)    /*  parity                          */
#define D_PSUB    (  59)    /*  pollution-sub                   */
#define D_PXOR    (  60)    /*  pollution-xor                   */
#define D_REDT    (  61)    /*  redundant                       */
#define D_REWD    (  62)    /*  rec-word                        */
#define D_ROI     (  63)    /*  ro-i                            */
#define D_RON     (  64)    /*  ro-n                            */
#define D_RS232   (  65)    /*  rs-232                          */
#define D_RS422   (  66)    /*  rs-422                          */
#define D_RS423   (  67)    /*  rs-423                          */
#define D_RS449   (  68)    /*  rs-449                          */
#define D_RS485   (  69)    /*  rs-485                          */
#define D_RTCON   (  70)    /*  rt-con                          */
#define D_RTRT    (  71)    /*  rt-rt                           */
#define D_RZ      (  72)    /*  rz                              */
#define D_SERL    (  73)    /*  serial-lsb-first                */
#define D_SERM    (  74)    /*  serial-msb-first                */
#define D_SLAVE   (  75)    /*  slave                           */
#define D_SYNC    (  76)    /*  sync                            */
#define D_T0ANDT1 (  77)    /*  t0-and-t1                       */
#define D_T0ARMT1 (  78)    /*  t0-arm-t1                       */
#define D_T0ORT1  (  79)    /*  t0-or-t1                        */
#define D_TLKLS   (  80)    /*  talker-listener                 */
#define D_TR      (  81)    /*  t-r                             */
#define D_UART    (  82)    /*  uart                            */
#define D_V35     (  83)    /*  v35                             */
#define D_WADC    (  84)    /*  wadc                            */
#define D_WATER   (  85)    /*  water                           */
#define D_XON     (  86)    /*  xon                             */
#define D__CNT    (  87)    /*  Symbol count                    */
/*
 *  DIMS-B
 */
#define R__CNT    (   1)    /*  Symbol count                    */
#endif /* _LEXKEY_H_ */
