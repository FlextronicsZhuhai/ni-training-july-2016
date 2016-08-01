#include "cem.h"
#include "key.h"
#include "util.h"

//BEGIN{DFW}:ACPS:1:0
int doACPS_1_Setup (double CURR, double FREQ, double VOLT)
//END{DFW}
{
    Display("\033[34;4mACPS fnc = 1(cem) setup\n\033[m\033[34m");
    DISPLAYDOUBLE(CURR); Display(", ");
    DISPLAYDOUBLE(VOLT); Display(", ");
    DISPLAYDOUBLE(FREQ); Display("\n\033[m");
    return (int) 0;
}

