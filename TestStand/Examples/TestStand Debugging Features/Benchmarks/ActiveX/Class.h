// Class.h: Definition of the CClass class
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLASS_H__765D7274_7FA6_11D2_9CE9_00A024767F0A__INCLUDED_)
#define AFX_CLASS_H__765D7274_7FA6_11D2_9CE9_00A024767F0A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CClass

class CClass : 
    public CComDualImpl<IClass, &IID_IClass, &LIBID_BENCHMARKLib>, 
    public ISupportErrorInfo,
    public CComObjectRoot,
    public CComCoClass<CClass,&CLSID_Class>
{
public:
    CClass() {}
BEGIN_COM_MAP(CClass)
    COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(IClass)
    COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()
//DECLARE_NOT_AGGREGATABLE(CClass) 
// Remove the comment from the line above if you don't want your object to 
// support aggregation. 

DECLARE_REGISTRY_RESOURCEID(IDR_Class)
// ISupportsErrorInfo
    STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IClass
public:
    STDMETHOD(DoNothing)();
};

#endif // !defined(AFX_CLASS_H__765D7274_7FA6_11D2_9CE9_00A024767F0A__INCLUDED_)
