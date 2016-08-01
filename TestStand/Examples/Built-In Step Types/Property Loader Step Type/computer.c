#include "tsutil.h"
#include <stdlib.h>
#include <stdio.h>
#include <utility.h>
#include <formatio.h>
#include <userint.h>
#include <string.h>
#include "computer.h"


void __declspec(dllexport) __stdcall PowerupTest(long PowerFail, double *measurement, short *errorOccurred, 
    long *errorCode, char errorMsg[1024])
{
    int error = 0;
    ErrMsg errMsg = {'\0'};
    ERRORINFO errorInfo;
    
    *measurement = 12 + (rand()%4);  /* value from 12 to 15 */
	
	if(PowerFail)
		*measurement += 4;		     /* make sure the value is 16 or more */

Error:  

    // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
    {
        *errorOccurred = TRUE;
        *errorCode = error;
        strcpy(errorMsg, errMsg);
    }
}

void __declspec(dllexport) __stdcall ROMTest(long ROMFail, long *result, short *errorOccurred, 
    long *errorCode, char errorMsg[1024])
{
    int error = 0;
    ErrMsg errMsg = {'\0'};
    ERRORINFO errorInfo;
    
    *result = !ROMFail;

Error:  

    // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
    {
        *errorOccurred = TRUE;
        *errorCode = error;
        strcpy(errorMsg, errMsg);
    }
}
 
void __declspec(dllexport) __stdcall RAMTest(long RAMFail, long *result, short *errorOccurred, 
    long *errorCode, char errorMsg[1024])
{
    int error = 0;
    ErrMsg errMsg = {'\0'};
    ERRORINFO errorInfo;
    
    *result = !RAMFail;

Error:  

    // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
    {
        *errorOccurred = TRUE;
        *errorCode = error;
        strcpy(errorMsg, errMsg);
    }
}

void __declspec(dllexport) __stdcall VideoTest(long VideoValue, double *measurement, short *errorOccurred, 
    long *errorCode, char errorMsg[1024])
{
    int error = 0;
    ErrMsg errMsg = {'\0'};
    ERRORINFO errorInfo;
    
    *measurement = 65;
	
	if (VideoValue)
        measurement += VideoValue;  /* make sure the value is 76 or more */

Error:  

    // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
    {
        *errorOccurred = TRUE;
        *errorCode = error;
        strcpy(errorMsg, errMsg);
    }
}

void __declspec(dllexport) __stdcall KeyboardTest(long KeyboardValue, long *result, short *errorOccurred, 
    long *errorCode, char errorMsg[1024])
{
    int error = 0;
    ErrMsg errMsg = {'\0'};
    ERRORINFO errorInfo;
    
    if(KeyboardValue > 5)
		*result = FALSE;
	else
		*result = TRUE;

Error:  

    // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
    {
        *errorOccurred = TRUE;
        *errorCode = error;
        strcpy(errorMsg, errMsg);
    }
}

void __declspec(dllexport) __stdcall ROMDiagnostics(char outString[1024], short *errorOccurred, 
    long *errorCode, char errorMsg[1024])
{
    int error = 0;
    ErrMsg errMsg = {'\0'};
    ERRORINFO errorInfo;
	
	strcpy (outString, "Access Error:\nROM Bank 5"); 

Error:  

    // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
    {
        *errorOccurred = TRUE;
        *errorCode = error;
        strcpy(errorMsg, errMsg);
    }
}
 
void __declspec(dllexport) __stdcall RAMDiagnostics(char outString[1024], short *errorOccurred, 
    long *errorCode, char errorMsg[1024])
{
    int error = 0;
    ErrMsg errMsg = {'\0'};
    ERRORINFO errorInfo;
    
	strcpy (outString, "Parity Error:\nRAM Bank 0");

Error:  

    // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
    {
        *errorOccurred = TRUE;
        *errorCode = error;
        strcpy(errorMsg, errMsg);
    }
}

void __declspec(dllexport) __stdcall VideoDiagnostics(char outString[1024], short *errorOccurred, 
    long *errorCode, char errorMsg[1024])
{
    int error = 0;
    ErrMsg errMsg = {'\0'};
    ERRORINFO errorInfo;
	
	strcpy (outString, "no video adapter present");

Error:  

    // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
    {
        *errorOccurred = TRUE;
        *errorCode = error;
        strcpy(errorMsg, errMsg);
    }
}

void __declspec(dllexport) __stdcall KeyboardDiagnostics(char outString[1024], short *errorOccurred, 
    long *errorCode, char errorMsg[1024])
{
    int error = 0;
    ErrMsg errMsg = {'\0'};
    ERRORINFO errorInfo;
    
	strcpy (outString, "Keyboard not found");

Error:  

    // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
    {
        *errorOccurred = TRUE;
        *errorCode = error;
        strcpy(errorMsg, errMsg);
    }
}
