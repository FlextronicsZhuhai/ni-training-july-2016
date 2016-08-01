#include <limits.h>
#include <float.h>
#include <stdio.h>
#include <string>
using namespace std;

string _getStrDouble(const char *sName, double dValue)
{
    static char sValue[100];
    if (dValue != - DBL_MAX)
        sprintf(sValue, "%s = %g", sName, dValue);
    else
        sprintf(sValue, "%s = n/a", sName);
    
    return sValue;
}

string _getStrShort(const char *sName, short shValue)
{
    static char sValue[100];
    if (shValue !=  SHRT_MIN)
        sprintf(sValue, "%s = %d", sName, shValue);
    else
        sprintf(sValue, "%s = n/a", sName);
    
    return sValue;
}

string _getStrLong(const char *sName, long lValue)
{
    static char sValue[100];
    if (lValue !=  LONG_MIN)
        sprintf(sValue, "%s = %ld", sName, lValue);
    else
        sprintf(sValue, "%s = n/a", sName);
    
    return sValue;
}
