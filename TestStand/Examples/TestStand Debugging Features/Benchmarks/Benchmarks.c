#include "stdtst.h" 

void __declspec(dllexport) __stdcall DLLAdapterTest()
{
}

void DLLEXPORT TX_TEST CVIAdapterTest()
{
}		 

int DLLEXPORT TX_TEST CVIAdapterTestParams(int *numeric, int * errorOccurred, char * errMsg)
{
return 0;
}

int __declspec(dllexport) __stdcall DLLAdapterTestParams(int *numeric, int * errorOccurred, char * errMsg)
{
return 0;
}
