// Class.cpp : Implementation of CBenchmarkApp and DLL registration.

#include "stdafx.h"
#include "Benchmark.h"
#include "Class.h"

/////////////////////////////////////////////////////////////////////////////
//

STDMETHODIMP CClass::InterfaceSupportsErrorInfo(REFIID riid)
{
    static const IID* arr[] = 
    {
        &IID_IClass,
    };

    for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
    {
        if (InlineIsEqualGUID(*arr[i],riid))
            return S_OK;
    }
    return S_FALSE;
}

STDMETHODIMP CClass::DoNothing()
{
    return S_OK;
}
