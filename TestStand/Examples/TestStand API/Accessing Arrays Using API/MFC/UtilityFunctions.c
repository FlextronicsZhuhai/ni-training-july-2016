#include <userint.h>
#include <analysis.h>
#include <cvirte.h>    /* Needed if linking in external compiler; harmless otherwise */
#include "tsutil.h"


    // Note: You can call CVI Library functions directly from a VC++ project if you include
    // CVIRT.LIB.  This file exists to create a DLL that will export these two CVI functions 
    // for use in VC++ examples that must be buildable even if CVI is not installed and
    // CVIRT.LIB is not available

int __stdcall DllMain (HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            if (InitCVIRTE (hinstDLL, 0, 0) == 0)    /* Needed if linking in external compiler; harmless otherwise */
                return 0;     /* out of memory */
            break;
        case DLL_PROCESS_DETACH:
            CloseCVIRTE ();    /* Needed if linking in external compiler; harmless otherwise */
            break;
    }
    
    return 1;
}

int __stdcall DllEntryPoint (HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    /* Included for compatibility with Borland */

    return DllMain (hinstDLL, fdwReason, lpvReserved);
}

int CVI_YGraphPopup(struct IDispatch *engineDisp, char* title, double* numArray, unsigned int numElements) 
{
    int             error = 0;
    ERRORINFO       errorInfo;
    ErrMsg          errMsg = "";    
    TSModalData     modalData = INITIAL_MODAL_DATA;
    CAObjHandle     engine = 0;
    
    tsErrChk(CA_CreateObjHandleFromIDispatch (engineDisp, 0, &engine));
    // NOTE: For CVI Dialogs we must use the tsutil TS_StartModalDialog
    // and TS_EndModalDialog functions instead of using the Engine class
    // methods NotifyStartOfModalDialog and NotifyEndOfModalDialog
    // directly.
    tsErrChk(TS_StartModalDialog(engine, &errorInfo, &modalData));
    errChk(YGraphPopup(title, numArray, numElements, VAL_DOUBLE));

Error:

    TS_EndModalDialog(&errorInfo, &modalData);
    
    // NOTE: don't call CA_DiscardObjHandle on the engine
    // because it was passed in as a parameter and we didn't
    // add a reference to it with CA_CreateObjHandleFromIDispatch.
    return error;
}


int CVI_SinePattern (double* numArray, unsigned int numElements, double numCycles)
{
    return SinePattern (numElements, 1.0, 0.0, numCycles, numArray);
}
    
