// DisplayingProgressAndStatus.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "math.h"
#include <mbstring.h>
#include "tsapivc.h"
using namespace TS;
#include "DisplayingProgressAndStatus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//  Note!
//
//      If this DLL is dynamically linked against the MFC
//      DLLs, any functions exported from this DLL which
//      call into MFC must have the AFX_MANAGE_STATE macro
//      added at the very beginning of the function.
//
//      For example:
//
//      extern "C" BOOL PASCAL EXPORT ExportedFunction()
//      {
//          AFX_MANAGE_STATE(AfxGetStaticModuleState());
//          // normal function body here
//      }
//
//      It is very important that this macro appear in each
//      function, prior to any calls into MFC.  This means that
//      it must appear as the first statement within the 
//      function, even before any object variable declarations
//      as their constructors may generate calls into the MFC
//      DLL.
//
//      Please see MFC Technical Notes 33 and 58 for additional
//      details.
//

/////////////////////////////////////////////////////////////////////////////
// CDisplayingProgressAndStatusApp

BEGIN_MESSAGE_MAP(CDisplayingProgressAndStatusApp, CWinApp)
    //{{AFX_MSG_MAP(CDisplayingProgressAndStatusApp)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisplayingProgressAndStatusApp construction

CDisplayingProgressAndStatusApp::CDisplayingProgressAndStatusApp()
{
    // NOTE: add construction code here,
    // Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDisplayingProgressAndStatusApp object

CDisplayingProgressAndStatusApp theApp;
#define errMsgLen 1024

static void CheckForUserTermination(ExecutionPtr& execution, bool& quit);

extern "C" {

void __declspec(dllexport) __stdcall Test(SequenceContext *seqContext,  short *errorOccurred,  long *errorCode,  char errorMsg[errMsgLen])
{
    
    try
        {
        CString             statusMessage;
        double              timeLimit = 8;      // in seconds 
        ThreadPtr           thread;
        ExecutionPtr        execution;
        bool                quit = false;

            // Get the thread that is executing from the Sequence Context   
        thread = seqContext->GetThread();
        execution = seqContext->GetExecution();
    
        CTime startTime = CTime::GetCurrentTime();
        CTimeSpan elapsedTime = CTime::GetCurrentTime() - startTime;
        while (elapsedTime.GetTotalSeconds() < timeLimit) 
            {
            CheckForUserTermination(execution, quit);
            if (quit)
                break;

                // Updated percent complete progress bar        
            thread->PostUIMessage(UIMsg_ProgressPercent, (elapsedTime.GetTotalSeconds() * 100) / timeLimit, "", TRUE);
            
                // Display percent finished in Status Bar, in increments of 10   
            statusMessage.Format("%d Percent Completed", 10 * (long)ceil((elapsedTime.GetTotalSeconds() * 10) / timeLimit));
            thread->PostUIMessage(UIMsg_ProgressText, 0, _bstr_t(statusMessage), TRUE);

                // Delay for 1 second   
            Sleep(1000);    
            elapsedTime = CTime::GetCurrentTime() - startTime;
            }
    
        if (!quit)
            {
                // Display test complete message in the message bar             
            thread->PostUIMessage(UIMsg_ProgressText, 0, "Test Completed", TRUE);
        
                // Display percent complete progress bar - 100% complete        
            thread->PostUIMessage(UIMsg_ProgressPercent, 100, "", TRUE);
            }
        }
       
     catch (_com_error &com_error)  /* TestStand API only throws this kind of exception */
        {
        *errorOccurred = TRUE;
        _bstr_t desc = com_error.Description();
        _mbsnbcpy_s((unsigned char *)errorMsg, errMsgLen,(unsigned char *)LPCTSTR(desc), errMsgLen - 1);
        errorMsg[errMsgLen - 1] = '\0';
        *errorCode = (short)HRESULT_CODE(com_error.Error());
        }    
}

} //extern "C"

static void CheckForUserTermination(ExecutionPtr& execution, bool& quit)
{
    enum Enum_ExecutionRunStates            runState;
    enum Enum_ExecutionTerminationStates    termState;
    
    execution->GetStates((ExecutionRunStates *)&runState, (ExecutionTerminationStates *)&termState);
    quit = (termState != ExecTermState_Normal);
}
