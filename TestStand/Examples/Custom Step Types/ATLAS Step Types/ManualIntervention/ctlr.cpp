#include "cem.h"
#include "key.h"
#include <limits.h>
#include <float.h>
//BEGIN{DFW}:CONNECT
int CCALLBACK DoLoad (void)
//END{DFW}
{
    for (int i = 0; i < 10; i++)
        Beep(1000 + 1000*i, 100);
    return 0;
}

//BEGIN{DFW}:DISCONNECT
int CCALLBACK DoUnload (void)
//END{DFW}
{
    for (int i = 10; i >= 0; i--)
        Beep(1000 + 1000*i, 100);
    return 0;
}

