// TSTclInterpreter.cpp : Implementation of WinMain


#include "stdafx.h"
#include "resource.h"
#include "TSTclInterpreter.h"


class CTSTclInterpreterModule : public CAtlExeModuleT< CTSTclInterpreterModule >
{
public :
	DECLARE_LIBID(LIBID_TSTclInterpreterLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_TSTCLINTERPRETER, "{A405C397-F84B-4ACA-9AC3-85DA337B45E4}")
	HRESULT RegisterClassObjects(DWORD, DWORD);

};

CTSTclInterpreterModule _AtlModule;

HRESULT CTSTclInterpreterModule::RegisterClassObjects(DWORD dwClsContext, DWORD dwFlags) throw()
{
    // example of modifying default behavior when CoRegisterClassObject is called
    dwFlags &= ~REGCLS_MULTIPLEUSE;
        dwFlags |= REGCLS_SINGLEUSE;
        return __super::RegisterClassObjects(dwClsContext, dwFlags);
}


//
extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, 
                                LPTSTR /*lpCmdLine*/, int nShowCmd)
{
    return _AtlModule.WinMain(nShowCmd);
}