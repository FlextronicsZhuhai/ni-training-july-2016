// AccessingArrays.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <mbstring.h>            
#include "math.h"
#include "tsapivc.h"
using namespace TS;
#include "utilityFunctions.h"
#include "AccessingArrays.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

typedef struct tagBOUNDSELEMENT {    
    long lowerBound;    
    long upperBound;
} BOUNDSELEMENT;


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
// CAccessingArraysApp

BEGIN_MESSAGE_MAP(CAccessingArraysApp, CWinApp)
    //{{AFX_MSG_MAP(CAccessingArraysApp)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAccessingArraysApp construction

CAccessingArraysApp::CAccessingArraysApp()
{
    // NOTE: add construction code here,
    // Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAccessingArraysApp object

CAccessingArraysApp theApp;

extern "C" {

void __declspec(dllexport) __stdcall FillLocalArray(SequenceContext *seqContext,  short *errorOccurred,  long *errorCode,  char errorMsg[1024])
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    double *        numArray = NULL;
    unsigned int    numElements;
    double          numCycles = 2.0;
    PropertyObjectPtr   seqContextPOPtr;

    TRY
        // Set sequence context as a property object
    seqContextPOPtr = seqContext->AsPropertyObject();
   
        // The following code shows how to accesses properties via the ActiveX Automation API
    if (seqContextPOPtr->Exists("Locals.NumericArray",0)) 
        {
            // Create a Safe Array from the VARIANT which contains a
            // copy of the Locals.NumericArray. 
        COleSafeArray safeArray;
        safeArray.Attach(seqContextPOPtr->GetValVariant("Locals.NumericArray",0));
    
            // Check the size of the array of data - assuming 1D array  
        numElements = safeArray.GetOneDimSize();

            // Lock array for data access and get a pointer to the data.
            // (assuming it's an array of doubles)
        safeArray.AccessData((void**)&numArray);
        

            // Create sine pattern
        for (unsigned int i=0; i<numElements; i++)
            numArray[i] = sin((2*3.14) * i *numCycles/ numElements);

            // unlock array 
        safeArray.UnaccessData();

            // Set the value of the property the lookupString parameter specifies with a variant.  
            // Use this method to set the value of an entire array at once.                         
        seqContextPOPtr->SetValVariant("Locals.NumericArray", 0, safeArray);

        }
    
    CATCH(COleDispatchException, e) 
        *errorOccurred = TRUE;
        _mbsnbcpy_s((unsigned char *)errorMsg, 1024, (unsigned char *)LPCTSTR(e->m_strDescription), 1024 - 1);
        *(errorMsg + (1024 - 1)) = '\0';
        *errorCode = e->m_scError;

    AND_CATCH(CMemoryException, e)
        *errorOccurred = TRUE;
        e->GetErrorMessage(errorMsg, 1024);
        *(errorMsg + (1024 - 1)) = '\0';
        *errorCode = TS_Err_OutOfMemory;

    END_CATCH 
}

void __declspec(dllexport) __stdcall AccessLocalArray(SequenceContext *seqContext, short *errorOccurred, long *errorCode,  char errorMsg[1024])
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    double *        numArray = NULL;
    unsigned int    numElements;
    PropertyObjectPtr   seqContextPOPtr;

    TRY 
        // Set sequence context as a property object
    seqContextPOPtr = seqContext->AsPropertyObject();

        // The following code shows how to accesses properties via the ActiveX Automation API
    if (seqContextPOPtr->Exists("Locals.NumericArray",0)) 
        {
            // Create a Safe Array from the VARIANT which contains a
            // copy of the Locals.NumericArray. 
        COleSafeArray safeArray;
        safeArray.Attach(seqContextPOPtr->GetValVariant("Locals.NumericArray",0));

            // Check the size of the array of data - assuming 1D array  
        numElements = safeArray.GetOneDimSize( );

            // Lock array for data access and get a pointer to the data.
            // (assuming it's an array of doubles)
        safeArray.AccessData((void**)&numArray);

            // Display data using LabWindows/CVI library function   
        if (CVI_YGraphPopup(seqContext->EngineAsDispatch, "Data in Local Array", numArray, numElements) < 0)
            AfxThrowMemoryException();

            // unlock array 
        safeArray.UnaccessData();
        }

    CATCH(COleDispatchException, e) 
        *errorOccurred = TRUE;
        _mbsnbcpy_s((unsigned char *)errorMsg, 1024, (unsigned char *)LPCTSTR(e->m_strDescription), 1024 - 1);
        *(errorMsg + (1024 - 1)) = '\0';
        *errorCode = e->m_scError;

    AND_CATCH(CMemoryException, e)
        *errorOccurred = TRUE;
        e->GetErrorMessage(errorMsg, 1024);
        *(errorMsg + (1024 - 1)) = '\0';
        *errorCode = TS_Err_OutOfMemory;

    END_CATCH 
}

void __declspec(dllexport) __stdcall Create2DArray(SequenceContext *seqContext, short *errorOccurred, long *errorCode, char errorMsg[1024])
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    double          *array2D;
    DWORD   rgElements[2] = {2,100};
    PropertyObjectPtr   seqContextPOPtr;

    TRY
        // Set sequence context as a property object
    seqContextPOPtr = seqContext->AsPropertyObject();

        // To dynamically create variables, you would normally use the InsertIfMissing 
        // Property Option.  In TestStand 1.0 and 1.0.1, the InsertIfMissing option does 
        // not work with arrays.
        // This example demonstrates how to create an array using NewSubProperty
    seqContextPOPtr->NewSubProperty ("Locals.Array2D", PropValType_Number, TRUE, "", 0);

        // You do not need to do a SetDimension as SetValVariant 
        // auto dimensions the property object to be atleast as big as the safe array
        //  property.SetDimensions ("Locals.Array2D", 0, "[0][0]", "[1][99]");
    
        // Create a Safe Array from the VARIANT which contains a
        // copy of the Locals.NumericArray. 
    COleSafeArray safeArray;
    
        // Create a Safe Array of the required size
    safeArray.Create( VT_R8,2, rgElements); 
                    
                                       
        // Lock array for data access and get a pointer to the data.
        // (assuming it's an array of doubles)         
    safeArray.AccessData((void**)&array2D);

        // Create sine pattern
    for (int i=0; i<100; i++)
        {
        array2D[i] = sin((2*3.14) * i / 100);
        array2D[i+100] = cos((2*3.14) * i / 100);
        }

        // unlock array 
    safeArray.UnaccessData();

        
        // Set the value of the property the lookupString parameter specifies with a variant.  
        // Use this method to set the value of an entire array at once.                         
    seqContextPOPtr->SetValVariant("Locals.Array2D", 0, safeArray);

    CATCH(COleDispatchException, e) 
        *errorOccurred = TRUE;
        _mbsnbcpy_s((unsigned char *)errorMsg, 1024, (unsigned char *)LPCTSTR(e->m_strDescription), 1024 - 1);
        *(errorMsg + (1024 - 1)) = '\0';
        *errorCode = e->m_scError;

    AND_CATCH(CMemoryException, e)
        *errorOccurred = TRUE;
        e->GetErrorMessage(errorMsg, 1024);
        *(errorMsg + (1024 - 1)) = '\0';
        *errorCode = TS_Err_OutOfMemory;

    END_CATCH
}


void __declspec(dllexport) __stdcall Access2DArray(SequenceContext *seqContext,  short *errorOccurred, long *errorCode, char errorMsg[1024])
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    double *        numArray = NULL;
    long            firstDimSize, secondDimSize, numberDimensions;
    BOUNDSELEMENT   *pBounds = NULL;
    PropertyObjectPtr   seqContextPOPtr;

    TRY
        // Set sequence context as a property object
    seqContextPOPtr = seqContext->AsPropertyObject();

    if (seqContextPOPtr->Exists("Locals.Array2D", 0)) 
        {
            // Create a Safe Array from the VARIANT which contains a
            // copy of the Locals.NumericArray. 
        COleSafeArray safeArray;
        safeArray.Attach(seqContextPOPtr->GetValVariant("Locals.Array2D",0));

            // Lock array for data access and get a pointer to the data.
            // (assuming it's an array of doubles)
        safeArray.AccessData((void**)&numArray);

            // Get number of dimensions of safearray
        numberDimensions = safeArray.GetDim();

            // Allocate data to hold dimension sizes
        pBounds = (BOUNDSELEMENT*)malloc(numberDimensions * sizeof(BOUNDSELEMENT));
        if (pBounds == NULL)
            AfxThrowMemoryException();
        
            // Get dimension sizes
        for (long i = 0; i<numberDimensions; i++)
            {
            safeArray.GetLBound(i+1, &pBounds[i].lowerBound);
            safeArray.GetUBound(i+1, &pBounds[i].upperBound);
            }

        if (numberDimensions == 2)  // 2-D array only
            {
            firstDimSize = pBounds[0].upperBound - pBounds[0].lowerBound + 1;
            secondDimSize = pBounds[1].upperBound - pBounds[1].lowerBound + 1;              

                // Display data using LabWindows/CVI library function   
                // Remove comments to display waveforms
            
				if (CVI_YGraphPopup(seqContext->EngineAsDispatch, "Data in Local Array 1", &numArray[0*secondDimSize], secondDimSize) < 0)
                    AfxThrowMemoryException();
                if (CVI_YGraphPopup(seqContext->EngineAsDispatch, "Data in Local Array 2", &numArray[1*secondDimSize], secondDimSize) < 0)
                    AfxThrowMemoryException();
            
            }

        free(pBounds);

            // unlock array 
        safeArray.UnaccessData();
        }

    CATCH(COleDispatchException, e) 
        *errorOccurred = TRUE;
        _mbsnbcpy_s((unsigned char *)errorMsg, 1024, (unsigned char *)LPCTSTR(e->m_strDescription), 1024 - 1);
        *(errorMsg + (1024 - 1)) = '\0';
        *errorCode = e->m_scError;

    AND_CATCH(CMemoryException, e)
        if (pBounds)
            free(pBounds);
        *errorOccurred = TRUE;
        e->GetErrorMessage(errorMsg, 1024);
        *(errorMsg + (1024 - 1)) = '\0';
        *errorCode = TS_Err_OutOfMemory;

    END_CATCH 
}
        
void __declspec(dllexport) __stdcall SetStringArray(SequenceContext *seqContext, short *errorOccurred, long *errorCode, char errorMsg[1024])
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    CString         tempBuffer;
    BSTR            tempBstr;
    PropertyObjectPtr   seqContextPOPtr;

    TRY
        // Set sequence context as a property object
    seqContextPOPtr = seqContext->AsPropertyObject();
   
        // Create a Safe Array of 3 elements of type BSTR
    COleSafeArray safeArray;
    DWORD   rgElements[1] = {3};
    safeArray.Create( VT_BSTR, 1, rgElements );
    
        // Put a string in each element of the safe array
    for (long i=0; i<3; i++)
        {
        tempBuffer.Format("String%d", i);
        tempBstr = tempBuffer.AllocSysString();
        safeArray.PutElement(&i, tempBstr);
        SysFreeString(tempBstr);
        }

        // Set the safe array to the TestStand local variable
    seqContextPOPtr->SetValVariant("Locals.StringArray", 0, safeArray);    
    
    CATCH(COleDispatchException, e) 
        *errorOccurred = TRUE;
        _mbsnbcpy_s((unsigned char *)errorMsg, 1024, (unsigned char *)LPCTSTR(e->m_strDescription), 1024 - 1);
        *(errorMsg + (1024 - 1)) = '\0';
        *errorCode = e->m_scError;

    AND_CATCH(CMemoryException, e)
        *errorOccurred = TRUE;
        e->GetErrorMessage(errorMsg, 1024);
        *(errorMsg + (1024 - 1)) = '\0';
        *errorCode = TS_Err_OutOfMemory;

    END_CATCH 
}


void __declspec(dllexport) __stdcall GetStringArray(SequenceContext *seqContext, short *errorOccurred,  long *errorCode,  char errorMsg[1024])
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    CString         displayString;
    BSTR            bstrElement;
    PropertyObjectPtr   seqContextPOPtr;

    TRY
        // Set sequence context as a property object
    seqContextPOPtr = seqContext->AsPropertyObject();

        // The following code shows how to accesses properties via the ActiveX Automation API
    if (seqContextPOPtr->Exists("Locals.StringArray",0)) 
        {
            // Create a Safe Array from the VARIANT which contains a
            // copy of the Locals.NumericArray. 
        COleSafeArray safeArray;
        safeArray.Attach(seqContextPOPtr->GetValVariant("Locals.StringArray",0));

            // Check the size of the array of data - assuming 1D array  
        unsigned long numElements = safeArray.GetOneDimSize( );

            // Get each element of array - assuming type BSTR
        for (long i=0; i<(long)numElements; i++)
            {
            CString tempString;
            safeArray.GetElement(&i, &bstrElement);
            tempString = bstrElement;
            SysFreeString(bstrElement);
            displayString += tempString + "\n";
            }
            // Get main application window handle so MessageBox is modal
        HWND hwnd = (HWND)seqContext->Engine->GetAppMainHwnd();
        MessageBox(hwnd, displayString, "String Array from TestStand Local Variable", MB_OK);
        }

    CATCH(COleDispatchException, e) 
        *errorOccurred = TRUE;
        _mbsnbcpy_s((unsigned char *)errorMsg, 1024, (unsigned char *)LPCTSTR(e->m_strDescription), 1024 - 1);
        *(errorMsg + (1024 - 1)) = '\0';
        *errorCode = e->m_scError;

    AND_CATCH(CMemoryException, e)
        *errorOccurred = TRUE;
        e->GetErrorMessage(errorMsg, 1024);
        *(errorMsg + (1024 - 1)) = '\0';
        *errorCode = TS_Err_OutOfMemory;

    END_CATCH 
}
            
} //extern "C"
