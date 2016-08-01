// StructTest.cpp : Defines the entry point for the DLL application.
//
/*
This example DLL shows how to pass structure data to/from Teststand. Examples are given for three byte packing schemes:
8, 4, and 1. All examples are given for testing purposes as the code for each packing scheme is the same.
The Setxxx functions take a structure as input and stores its data in a global variable. The corresponding
Getxxx functions, store the data from the global variable to a struct pointer passed in as a parameter. For testing
purposes, you should Get the same data as you Set.
*/

#include "stdafx.h"
#include <unknwn.h>
#include <oleauto.h>
#include <stdlib.h>

#pragma pack (push)

#pragma pack(8)
//eight byte packing
typedef struct tagAllDataTypesPacked8 {
char    cC;
long    lLong;
short   sShort;
WORD    wWord;
DWORD   dwDword;
float   fFloat;
double  dDouble;
float   *lpFloatArray;
char    cBuff[64];
char    *lpC;
BOOL    bBool;
struct IDispatch *lpIDispatch;
} ALLDATATYPESPACKED8, *LPALLDATATYPESPACKED8;

#pragma pack (4)
//four byte packing
typedef struct tagAllDataTypesPacked4 {
char    cC;
long    lLong;
short   sShort;
WORD    wWord;
DWORD   dwDword;
float   fFloat;
double  dDouble;
float   *lpFloatArray;
char    cBuff[64];
char    *lpC;
BOOL    bBool;
struct IDispatch *lpIDispatch;
} ALLDATATYPESPACKED4, *LPALLDATATYPESPACKED4;

#pragma pack (1)
//one byte packing
typedef struct tagAllDataTypesPacked1 {
char    cC;
long    lLong;
short   sShort;
WORD    wWord;
DWORD   dwDword;
float   fFloat;
double  dDouble;
float   *lpFloatArray;
char    cBuff[64];
char    *lpC;
BOOL    bBool;
struct IDispatch *lpIDispatch;
} ALLDATATYPESPACKED1, *LPALLDATATYPESPACKED1;

#pragma pack (pop)

//pre-defined float array size
#define FLOAT_ARRAY_CNT     10
#define FLOAT_ARRAY_SIZE    FLOAT_ARRAY_CNT*sizeof(float)

//pre-defined string array size
#define LPC_SIZE	64

//global variables to hold values between calls
ALLDATATYPESPACKED8 gsPacked8;
ALLDATATYPESPACKED4 gsPacked4;
ALLDATATYPESPACKED1 gsPacked1;


BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        //allocate the pre-defined sized char and float arrays
        gsPacked8.lpC = (char *)malloc(LPC_SIZE);
        gsPacked4.lpC = (char *)malloc(LPC_SIZE);
        gsPacked1.lpC = (char *)malloc(LPC_SIZE);

        gsPacked8.lpFloatArray = (float *)malloc(FLOAT_ARRAY_SIZE);
        gsPacked4.lpFloatArray = (float *)malloc(FLOAT_ARRAY_SIZE);
        gsPacked1.lpFloatArray = (float *)malloc(FLOAT_ARRAY_SIZE);

        gsPacked8.lpIDispatch = NULL;
        gsPacked4.lpIDispatch = NULL;
        gsPacked1.lpIDispatch = NULL;
        break;

    case DLL_PROCESS_DETACH:
        free(gsPacked8.lpC);
        free(gsPacked4.lpC);
        free(gsPacked1.lpC);

        free(gsPacked8.lpFloatArray);
        free(gsPacked4.lpFloatArray);
        free(gsPacked1.lpFloatArray);

        if (gsPacked8.lpIDispatch)
            gsPacked8.lpIDispatch->Release ();
        if (gsPacked4.lpIDispatch)
            gsPacked4.lpIDispatch->Release ();
        if (gsPacked1.lpIDispatch)
            gsPacked1.lpIDispatch->Release ();
    }
    
    return TRUE;
}

/*
The xxxByRef funtions take a pointer to the structure, the xxxByVal functions take the structure passed on the stack.
*/

extern "C" {

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//eight byte packing
void __declspec(dllexport) __stdcall SetStructPacked8ByRef(LPALLDATATYPESPACKED8 lpPacked8,
        int *errorOccurred, long *errorCode, wchar_t errorMsg[1024])
    {
    char *lpC;
    float *lpF;
    try
        {
            //save value of our pointers because they will get over written
            lpF = gsPacked8.lpFloatArray;
            lpC = gsPacked8.lpC;
            if (gsPacked8.lpIDispatch)
                gsPacked8.lpIDispatch->Release ();
            *(LPALLDATATYPESPACKED8)&gsPacked8 = *lpPacked8;
            gsPacked8.lpIDispatch->AddRef ();
            gsPacked8.lpFloatArray = lpF;
            memcpy(gsPacked8.lpFloatArray,lpPacked8->lpFloatArray,FLOAT_ARRAY_SIZE);
            gsPacked8.lpC = lpC;
            strcpy_s(gsPacked8.lpC, LPC_SIZE, lpPacked8->lpC);
        }
        
    catch (...)
        {
        *errorOccurred = TRUE;
        }
    }


void __declspec(dllexport) __stdcall GetStructPacked8ByRef(LPALLDATATYPESPACKED8 lpPacked8, 
                                    long *errorOccurred,  long *errorCode,  wchar_t errorMsg[1024])
    {
    char *lpC;
    float *lpF;
    try
        {
            //save value of our pointers because they will get over written
            lpF = lpPacked8->lpFloatArray;
            lpC = lpPacked8->lpC;
            if (lpPacked8->lpIDispatch)
                lpPacked8->lpIDispatch->Release ();
            *lpPacked8 = *(LPALLDATATYPESPACKED8)&gsPacked8;
            lpPacked8->lpIDispatch->AddRef();
            lpPacked8->lpFloatArray = lpF;
            memcpy(lpPacked8->lpFloatArray, gsPacked8.lpFloatArray, FLOAT_ARRAY_SIZE);
            lpPacked8->lpC = lpC;
            strcpy_s(lpPacked8->lpC, LPC_SIZE, gsPacked8.lpC);
        }
        
    catch (...)
        {
        *errorOccurred = TRUE;
        }
    }


void __declspec(dllexport) __stdcall SetStructPacked8ByVal(ALLDATATYPESPACKED8 sPacked8,  
            long *errorOccurred,  long *errorCode,  wchar_t errorMsg[1024])
    {
    char *lpC;
    float *lpF;
    try
        {
            //save value of our pointers because they will get over written
            lpF = gsPacked8.lpFloatArray;
            lpC = gsPacked8.lpC;
            if (gsPacked8.lpIDispatch)
                gsPacked8.lpIDispatch->Release ();
            *(LPALLDATATYPESPACKED8)&gsPacked8 = *(LPALLDATATYPESPACKED8)&sPacked8;
            gsPacked8.lpIDispatch->AddRef ();
            gsPacked8.lpFloatArray = lpF;
            memcpy(gsPacked8.lpFloatArray,sPacked8.lpFloatArray,FLOAT_ARRAY_SIZE);
            gsPacked8.lpC = lpC;
            strcpy_s(gsPacked8.lpC, LPC_SIZE, sPacked8.lpC);
        }
        
    catch (...)
        {
        *errorOccurred = TRUE;
        }
    }

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//four byte packing
void __declspec(dllexport) __stdcall SetStructPacked4ByRef(LPALLDATATYPESPACKED4 lpPacked4,  
            long *errorOccurred,  long *errorCode,  wchar_t errorMsg[1024])
    {
    char *lpC;
    float *lpF;
    try
        {
            lpF = gsPacked4.lpFloatArray;
            lpC = gsPacked4.lpC;
            if (gsPacked4.lpIDispatch)
                gsPacked4.lpIDispatch->Release ();
            *(LPALLDATATYPESPACKED4)&gsPacked4 = *lpPacked4;
            gsPacked4.lpIDispatch->AddRef ();
            gsPacked4.lpFloatArray = lpF;
            memcpy(gsPacked4.lpFloatArray,lpPacked4->lpFloatArray,FLOAT_ARRAY_SIZE);
            gsPacked4.lpC = lpC;
            strcpy_s(gsPacked4.lpC, LPC_SIZE, lpPacked4->lpC);
        }
        
    catch (...)
        {
        *errorOccurred = TRUE;
        }
    }


void __declspec(dllexport) __stdcall GetStructPacked4ByRef(LPALLDATATYPESPACKED4 lpPacked4, 
                                    long *errorOccurred,  long *errorCode,  wchar_t errorMsg[1024])
    {
    char *lpC;
    float *lpF;
    try
        {
            //save value of our pointers because they will get over written
            lpF = lpPacked4->lpFloatArray;
            lpC = lpPacked4->lpC;
            if (lpPacked4->lpIDispatch)
                lpPacked4->lpIDispatch->Release ();
            *lpPacked4 = *(LPALLDATATYPESPACKED4)&gsPacked4;
            lpPacked4->lpIDispatch->AddRef();
            lpPacked4->lpFloatArray = lpF;
            memcpy(lpPacked4->lpFloatArray, gsPacked4.lpFloatArray, FLOAT_ARRAY_SIZE);
            lpPacked4->lpC = lpC;
            strcpy_s(lpPacked4->lpC, LPC_SIZE, gsPacked4.lpC);
        }
        
    catch (...)
        {
        *errorOccurred = TRUE;
        }
    }


void __declspec(dllexport) __stdcall SetStructPacked4ByVal(ALLDATATYPESPACKED4 sPacked4,  
            long *errorOccurred,  long *errorCode,  wchar_t errorMsg[1024])
    {
    char *lpC;
    float *lpF;
    try
        {
            //save value of our pointers because they will get over written
            lpF = gsPacked4.lpFloatArray;
            lpC = gsPacked4.lpC;
            if (gsPacked4.lpIDispatch)
                gsPacked4.lpIDispatch->Release ();
            *(LPALLDATATYPESPACKED4)&gsPacked4 = *(LPALLDATATYPESPACKED4)&sPacked4;
            gsPacked4.lpIDispatch->AddRef ();
            gsPacked4.lpFloatArray = lpF;
            memcpy(gsPacked4.lpFloatArray,sPacked4.lpFloatArray,FLOAT_ARRAY_SIZE);
            gsPacked4.lpC = lpC;
            strcpy_s(gsPacked4.lpC, LPC_SIZE, sPacked4.lpC);
        }
        
    catch (...)
        {
        *errorOccurred = TRUE;
        }
    }

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//one byte packing
void __declspec(dllexport) __stdcall SetStructPacked1ByRef(LPALLDATATYPESPACKED1 lpPacked1,  
            long *errorOccurred,  long *errorCode,  wchar_t errorMsg[1024])
    {
    char *lpC;
    float *lpF;
    try
        {
            lpF = gsPacked1.lpFloatArray;
            lpC = gsPacked1.lpC;
            if (gsPacked1.lpIDispatch)
                gsPacked1.lpIDispatch->Release ();
            *(LPALLDATATYPESPACKED1)&gsPacked1 = *lpPacked1;
            gsPacked1.lpIDispatch->AddRef ();
            gsPacked1.lpFloatArray = lpF;
            memcpy(gsPacked1.lpFloatArray,lpPacked1->lpFloatArray,FLOAT_ARRAY_SIZE);
            gsPacked1.lpC = lpC;
            strcpy_s(gsPacked1.lpC, LPC_SIZE, lpPacked1->lpC);
        }
        
    catch (...)
        {
        *errorOccurred = TRUE;
        }
    }


void __declspec(dllexport) __stdcall GetStructPacked1ByRef(LPALLDATATYPESPACKED1 lpPacked1, 
                                    long *errorOccurred,  long *errorCode,  wchar_t errorMsg[1024])
    {
    char *lpC;
    float *lpF;
    try
        {
            //save value of our pointers because they will get over written
            lpF = lpPacked1->lpFloatArray;
            lpC = lpPacked1->lpC;
            if (lpPacked1->lpIDispatch)
                lpPacked1->lpIDispatch->Release ();
            *lpPacked1 = *(LPALLDATATYPESPACKED1)&gsPacked1;
            lpPacked1->lpIDispatch->AddRef();
            lpPacked1->lpFloatArray = lpF;
            memcpy(lpPacked1->lpFloatArray, gsPacked1.lpFloatArray, FLOAT_ARRAY_SIZE);
            lpPacked1->lpC = lpC;
            strcpy_s(lpPacked1->lpC, LPC_SIZE, gsPacked1.lpC);
        }
        
    catch (...)
        {
        *errorOccurred = TRUE;
        }
    }


void __declspec(dllexport) __stdcall SetStructPacked1ByVal(ALLDATATYPESPACKED1 sPacked1,  
            long *errorOccurred,  long *errorCode,  wchar_t errorMsg[1024])
    {
    char *lpC;
    float *lpF;
    try
        {
            //save value of our pointers because they will get over written
            lpF = gsPacked1.lpFloatArray;
            lpC = gsPacked1.lpC;
            if (gsPacked1.lpIDispatch)
                gsPacked1.lpIDispatch->Release ();
            *(LPALLDATATYPESPACKED1)&gsPacked1 = *(LPALLDATATYPESPACKED1)&sPacked1;
            gsPacked1.lpIDispatch->AddRef ();
            gsPacked1.lpFloatArray = lpF;
            memcpy(gsPacked1.lpFloatArray,sPacked1.lpFloatArray,FLOAT_ARRAY_SIZE);
            gsPacked1.lpC = lpC;
            strcpy_s(gsPacked1.lpC, LPC_SIZE, sPacked1.lpC);
        }
        
    catch (...)
        {
        *errorOccurred = TRUE;
        }
    }

}

