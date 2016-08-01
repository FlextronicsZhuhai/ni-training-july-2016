#include <string>
using namespace std;
extern string _getStrDouble(const char* sName, double dValue);
extern string _getStrShort(const char* sName, short shValue);
extern string _getStrLong(const char* sName, long lValue);

extern int TypeErr (const char *);

#define DISPLAYDOUBLE( x ) Display((char*)_getStrDouble(#x, x).c_str())
#define DISPLAYSHORT( x ) Display((char*)_getStrShort(#x, x).c_str())
#define DISPLAYLONG( x ) Display((char*)_getStrLong(#x, x).c_str())
