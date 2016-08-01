// AccessingPropertiesAndVariables.cpp : Defines the initialization routines for the DLL.
// 

#include "stdafx.h"
#include "stdlib.h"
#include <mbstring.h>
#include "tsapivc.h"
using namespace TS;
#include "AccessingPropertiesAndVariables.h"

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
// CAccessingPropertiesAndVariablesApp

BEGIN_MESSAGE_MAP(CAccessingPropertiesAndVariablesApp, CWinApp)
    //{{AFX_MSG_MAP(CAccessingPropertiesAndVariablesApp)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAccessingPropertiesAndVariablesApp construction

CAccessingPropertiesAndVariablesApp::CAccessingPropertiesAndVariablesApp()
{
    // NOTE: add construction code here,
    // Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAccessingPropertiesAndVariablesApp object

CAccessingPropertiesAndVariablesApp theApp;

extern "C" {
void __declspec(dllexport) __stdcall NumericLimitTest(SequenceContext *seqContext,  short *errorOccurred,  long *errorCode,  char errorMsg[1024])
{

    try
        {
            // Attach dispatch parameter to the smart pointer.
        PropertyObjectPtr property = seqContext->AsPropertyObject();

        srand((unsigned) clock ());     
        property->SetValNumber("Step.Result.Numeric", 0, rand() % 10);
        }

    catch (_com_error &com_error)   /* TestStand API only throws this kind of exception */
        {
        *errorOccurred = TRUE;
        _bstr_t desc = com_error.Description();
        _mbsnbcpy_s((unsigned char *)errorMsg, 1024,(unsigned char *)LPCTSTR(desc), 1024 - 1);
        errorMsg[1024 - 1] = '\0';        
        *errorCode = (short)HRESULT_CODE(com_error.Error());
        }
}


void __declspec(dllexport) __stdcall PassFailTest(SequenceContext *seqContext,  short *errorOccurred,  long *errorCode,  char errorMsg[1024])
{

    try
        {
            // Attach dispatch parameter to the smart pointer.
        PropertyObjectPtr property = seqContext->AsPropertyObject();

        property->SetValBoolean("Step.Result.PassFail", 0, (short)TRUE);  // TRUE indicates the "Test" passed
        }

    catch (_com_error &com_error)   /* TestStand API only throws this kind of exception */
        {
        *errorOccurred = TRUE;
        _bstr_t desc = com_error.Description();
        _mbsnbcpy_s((unsigned char *)errorMsg, 1024,(unsigned char *)LPCTSTR(desc), 1024 - 1);
        errorMsg[1024 - 1] = '\0';
        *errorCode = (short)HRESULT_CODE(com_error.Error());
        }    
}

    

void __declspec(dllexport) __stdcall AccessLocalVariables(SequenceContext *seqContext,  short *errorOccurred,  long *errorCode,  char errorMsg[1024])
{

    try
        {
            // Attach dispatch parameter to the smart pointer.
        PropertyObjectPtr property = seqContext->AsPropertyObject();

        srand((unsigned) clock ());

            // Note1: You do not have to call property->Exists if you know that the variable
            // you are accessing exists.  
            // Note2: You can also create a new variable and sets its value 
            // with a single call by passing the TS::PropOption_InsertIfMissing option
            // as the second parameter to SetValNumber, SetValString, or SetValBoolean
        if (property->Exists("Locals.NumericValue", 0)) 
            property->SetValNumber("Locals.NumericValue", 0, rand() % 10);
        }

    catch (_com_error &com_error)   /* TestStand API only throws this kind of exception */
        {
        *errorOccurred = TRUE;
        _bstr_t desc = com_error.Description();
        _mbsnbcpy_s((unsigned char *)errorMsg, 1024,(unsigned char *)LPCTSTR(desc), 1024 - 1);
        errorMsg[1024 - 1] = '\0';
        *errorCode = (short)HRESULT_CODE(com_error.Error());
        }
}

} //extern "C"
