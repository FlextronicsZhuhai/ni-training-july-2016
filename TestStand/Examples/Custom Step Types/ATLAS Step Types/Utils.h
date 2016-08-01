#if !defined(_UTILS_H_)
#define _UTILS_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Strings
#define ATLAS_STEP_TYPE_STRING  _T("ATLAS_STEP_TYPE_EXAMPLE")

// Error Checking
#define RAISE_ERROR(_err)       _com_issue_error((HRESULT)_err)
#define THROW_ERROR(_err,_desc) TSUTIL::ThrowCompilerComException(_err, (LPCTSTR)_desc) 
#define THROW_IF_FAILED(_hr)    if (FAILED(_hr)) _com_issue_error(_hr)
#define RETURN_IF_FAILED(_hr)   if (FAILED(_hr)) return _hr

// Utility Functions
extern  CString GetResourceString (const TS::IEnginePtr& engine, LPCTSTR category, LPCTSTR symbol);
extern  void    SizeCheckBoxToContent(CButton &checkBox);

#endif
