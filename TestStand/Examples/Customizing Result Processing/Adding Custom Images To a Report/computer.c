/********************************************************/
/*                                                      */
/*  computer.c                                          */
/*                                                      */
/*  Contains the test functions used by computer.seq to */
/*  simulate testing a computer motherboard.            */
/*  These tests differ from the demo example in that    */
/*  they have HTML links to further diagnostic pages.   */
/*                                                      */
/********************************************************/
#include "tsutil.h"
#include <stdlib.h>
#include <stdio.h>
#include <utility.h>
#include <formatio.h>
#include <userint.h>
#include <string.h>
#include <stdtst.h>
#include "computer.h"


void __declspec(dllexport) __stdcall ComputerSequenceSimulationDialog(CAObjHandle seqContextCVI,
    long *PowerFail, long *CPUFail, long *ROMFail, long *RAMFail, 
    long *KeyboardValue, long *VideoValue, short *errorOccurred, long *errorCode, 
    char errorMsg[1024])
{
    int hPanel = 0;
    int VideoFail = 0;
    int KeyboardFail = 0;
	const char DialogPath [MAX_PATHNAME_LEN] = "computer.uir" ;
                       
    hPanel = LoadPanelEx(0, DialogPath, UUT, __CVIUserHInst);
    if(hPanel < 0)
    {
        *errorOccurred = TRUE;
        *errorCode = hPanel;
        sprintf(errorMsg,"Error number %d attempting to load panel from %s", hPanel, DialogPath);
    }
    else
    {
        InstallCtrlCallback(hPanel, UUT_DONE, &SetupUICallback, (void *) &seqContextCVI);
        DisplayPanel(hPanel);
        TS_CancelDialogIfExecutionStops(hPanel, seqContextCVI);
        RunUserInterface();
    
        GetCtrlVal(hPanel, UUT_POWER, PowerFail);
        GetCtrlVal(hPanel, UUT_CPU, CPUFail);
        GetCtrlVal(hPanel, UUT_VIDEO, &VideoFail);
        GetCtrlVal(hPanel, UUT_ROM, ROMFail);
        GetCtrlVal(hPanel, UUT_RAM, RAMFail);
        GetCtrlVal(hPanel, UUT_KEYBOARD, &KeyboardFail);
        
        *VideoValue = VideoFail ? 15 : 5;
        *KeyboardValue = KeyboardFail ? 4 : 6;
            
        DiscardPanel(hPanel);
    }
}

void __declspec(dllexport) __stdcall VacuumOn(short *errorOccurred, long *errorCode, char errorMsg[1024])
{
    int error = 0;
    ErrMsg errMsg = {'\0'};
    ERRORINFO errorInfo;

Error:  

    // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
    {
        *errorOccurred = TRUE;
        *errorCode = error;
        strcpy(errorMsg, errMsg);
    }
}

void __declspec(dllexport) __stdcall PowerupTest(long PowerFail, char modulePath[1024], char outString[1024], long *result, short *errorOccurred, 
    long *errorCode, char errorMsg[1024])
{
    int error = 0;
    ErrMsg errMsg = {'\0'};
    ERRORINFO errorInfo;
    
    *result = !PowerFail;
	
	if(PowerFail)
	{
		strcpy (outString, "Reset does not clear.  ");

        /* Create HTML link.  This link assumes that the linked file is located in the same directory */
        /* as the DLL that contains this function                                                     */
        strcat (outString, "<A HREF='file:///");
        strcat (outString, modulePath);
        strcat (outString, "\\PowerDiagnostics.html'>Diagnostics documentation</A>");
	}

Error:  

    // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
    {
        *errorOccurred = TRUE;
        *errorCode = error;
        strcpy(errorMsg, errMsg);
    }
}

void __declspec(dllexport) __stdcall RegisterTest(long *result, short *errorOccurred, long *errorCode, char errorMsg[1024])
{
    int error = 0;
    ErrMsg errMsg = {'\0'};
    ERRORINFO errorInfo;
    
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
 
void __declspec(dllexport) __stdcall InstrSetTest(long CPUFail, long *result, short *errorOccurred, 
    long *errorCode, char errorMsg[1024]) 
{
    int error = 0;
    ErrMsg errMsg = {'\0'};
    ERRORINFO errorInfo;
    
    *result = !CPUFail;

Error:  

    // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
    {
        *errorOccurred = TRUE;
        *errorCode = error;
        strcpy(errorMsg, errMsg);
    }
}

void __declspec(dllexport) __stdcall CacheTest(long *result, short *errorOccurred, long *errorCode, char errorMsg[1024])
{
    int error = 0;
    ErrMsg errMsg = {'\0'};
    ERRORINFO errorInfo;
    
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

void __declspec(dllexport) __stdcall FPUTest(long *result, short *errorOccurred, long *errorCode, char errorMsg[1024])
{
    int error = 0;
    ErrMsg errMsg = {'\0'};
    ERRORINFO errorInfo;
    
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
    
    *measurement = VideoValue;

Error:  

    // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
    {
        *errorOccurred = TRUE;
        *errorCode = error;
        strcpy(errorMsg, errMsg);
    }
}

void __declspec(dllexport) __stdcall KeyboardTest(long KeyboardValue, double *measurement, short *errorOccurred, 
    long *errorCode, char errorMsg[1024])
{
    int error = 0;
    ErrMsg errMsg = {'\0'};
    ERRORINFO errorInfo;
    
    *measurement = KeyboardValue;

Error:  

    // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
    {
        *errorOccurred = TRUE;
        *errorCode = error;
        strcpy(errorMsg, errMsg);
    }
}

void __declspec(dllexport) __stdcall RegisterDiagnostics(long *result, short *errorOccurred, long *errorCode, 
    char errorMsg[1024])
{
    int error = 0;
    ErrMsg errMsg = {'\0'};
    ERRORINFO errorInfo;
    
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
 
void __declspec(dllexport) __stdcall InstrSetDiagnostics(long CPUFail, long *result, short *errorOccurred, 
    long *errorCode, char errorMsg[1024]) 
{
    int error = 0;
    ErrMsg errMsg = {'\0'};
    ERRORINFO errorInfo;
    
    *result = !CPUFail;

Error:  

    // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
    {
        *errorOccurred = TRUE;
        *errorCode = error;
        strcpy(errorMsg, errMsg);
    }
}

void __declspec(dllexport) __stdcall CacheDiagnostics(long *result, short *errorOccurred, long *errorCode, char errorMsg[1024])
{
    int error = 0;
    ErrMsg errMsg = {'\0'};
    ERRORINFO errorInfo;
    
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

void __declspec(dllexport) __stdcall FPUDiagnostics(long *result, short *errorOccurred, long *errorCode, char errorMsg[1024])
{
    int error = 0;
    ErrMsg errMsg = {'\0'};
    ERRORINFO errorInfo;
    
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

void __declspec(dllexport) __stdcall ROMDiagnostics(long *result, char modulePath[1024], char outString[1024], short *errorOccurred, 
    long *errorCode, char errorMsg[1024])
{
    int error = 0;
    ErrMsg errMsg = {'\0'};
    ERRORINFO errorInfo;
    
    *result = FALSE;
	
	strcpy (outString, "Access Error:\nROM Bank 4  ");
        
    /* Create HTML link.  This link assumes that the linked file is located in the same directory */
    /* as the DLL that contains this function                                                     */
    strcat (outString, "<A HREF='file:///");
    strcat (outString, modulePath);
    strcat (outString, "\\ROMDiagnostics.html'>Diagnostics documentation</A>");
        

Error:  

    // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
    {
        *errorOccurred = TRUE;
        *errorCode = error;
        strcpy(errorMsg, errMsg);
    }
}
 
void __declspec(dllexport) __stdcall RAMDiagnostics(long *result, char modulePath[1024], char outString[1024], short *errorOccurred, 
    long *errorCode, char errorMsg[1024])
{
    int error = 0;
    ErrMsg errMsg = {'\0'};
    ERRORINFO errorInfo;
    
    *result = FALSE;
	
	strcpy (outString, "Parity Error:\nRAM Bank 0  ");
    
    /* Create HTML link.  This link assumes that the linked file is located in the same directory */
    /* as the DLL that contains this function                                                     */
    strcat (outString, "<A HREF='file:///");
    strcat (outString, modulePath);
    strcat (outString, "\\RAMDiagnostics.html'>Diagnostics documentation</A>");

Error:  

    // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
    {
        *errorOccurred = TRUE;
        *errorCode = error;
        strcpy(errorMsg, errMsg);
    }
}

void __declspec(dllexport) __stdcall VideoDiagnostics(double *measurement, char modulePath[1024], char outString[1024], short *errorOccurred, 
    long *errorCode, char errorMsg[1024])
{
    int error = 0;
    ErrMsg errMsg = {'\0'};
    ERRORINFO errorInfo;
    
    *measurement = 0.003;
	
	strcpy (outString, "no video adapter present  ");

    /* Create HTML link.  This link assumes that the linked file is located in the same directory */
    /* as the DLL that contains this function                                                     */
    strcat (outString, "<A HREF='file:///");
    strcat (outString, modulePath);  
    strcat (outString, "\\VideoDiagnostics.html'>Diagnostics documentation</A>");

Error:  

    // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
    {
        *errorOccurred = TRUE;
        *errorCode = error;
        strcpy(errorMsg, errMsg);
    }
}

void __declspec(dllexport) __stdcall KeyboardDiagnostics(long *result, char modulePath[1024], char outString[1024], short *errorOccurred, 
    long *errorCode, char errorMsg[1024])
{
    int error = 0;
    ErrMsg errMsg = {'\0'};
    ERRORINFO errorInfo;
    
    *result = FALSE;
	
	strcpy (outString, "Cannot detect keyboard interface  ");

    /* Create HTML link.  This link assumes that the linked file is located in the same directory */
    /* as the DLL that contains this function                                                     */
    strcat (outString, "<A HREF='file:///");
    strcat (outString, modulePath);
    strcat (outString, "\\KeyboardDiagnostics.html'>Diagnostics documentation</A>");

Error:  

    // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
    {
        *errorOccurred = TRUE;
        *errorCode = error;
        strcpy(errorMsg, errMsg);
    }
}

void __declspec(dllexport) __stdcall PowerupDiagnostics(double *measurement, short *errorOccurred, 
    long *errorCode, char errorMsg[1024])
{
    int error = 0;
    ErrMsg errMsg = {'\0'};
    ERRORINFO errorInfo;
    
    *measurement = 4.75;

Error:  

    // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
    {
        *errorOccurred = TRUE;
        *errorCode = error;
        strcpy(errorMsg, errMsg);
    }
}

void __declspec(dllexport) __stdcall VacuumOff(short *errorOccurred, long *errorCode, char errorMsg[1024])
{
    int error = 0;
    ErrMsg errMsg = {'\0'};
    ERRORINFO errorInfo;

Error:  

    // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
    {
        *errorOccurred = TRUE;
        *errorCode = error;
        strcpy(errorMsg, errMsg);
    }
}

int CVICALLBACK SetupUICallback (int panel, int control, int event,
        void *callbackData, int eventData1, int eventData2)
{
    int error = 0;
    ErrMsg errMsg = {'\0'};
    ERRORINFO errorInfo;
    
    if(event == EVENT_COMMIT)
    {
        QuitUserInterface(0);
    }
    
Error:  

    if(error < 0)
    {
        return UIEOperationFailed;
    }   
    
    return 0;
}

