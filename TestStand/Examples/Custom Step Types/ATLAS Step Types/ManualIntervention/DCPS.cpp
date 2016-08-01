#include "cem.h"
#include "key.h"
#include "util.h"

//BEGIN{DFW}:DCPS:1:0
int doDCPS_1_Setup (double CURR, double VOLT)
//END{DFW}
{
    Display("\033[34;4mDCPS fnc = 1(cem) setup\n\033[m\033[34m");
    DISPLAYDOUBLE(CURR); Display(", ");
    DISPLAYDOUBLE(VOLT); Display("\n\033[m");
    return 0;
}

