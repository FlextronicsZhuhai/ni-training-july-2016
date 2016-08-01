// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__FF4C7097_1F62_4A89_A2BC_B1D46574CB13__INCLUDED_)
#define AFX_STDAFX_H__FF4C7097_1F62_4A89_A2BC_B1D46574CB13__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif
#define _ATL_APARTMENT_THREADED

#include <afxwin.h>
#include <afxdisp.h>
#include <afxmt.h>
#include <afxtempl.h>
#include <atlbase.h>

//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>

// The PAWS RTS ActiveX API. Change the path to these files to reflect the installation
//  of PAWS on the local machine. The files are located in <PAWS>\tyx\com
#import "C:\usr\tyx\com\rtsax.dll" no_registry raw_interfaces_only \
    raw_native_types, named_guids rename_namespace("RTSAX")
#import "C:\usr\tyx\com\ComUtil.dll" no_registry raw_interfaces_only, \
    raw_native_types, named_guids no_namespace

// TestStand API, TestStand UI ActiveX controls API, and utilities for using these APIs in C++
// The file is located in <TestStand>\API\VC
#include "tsutilCPP.h"

// using allows us to not type the namespace qualifier in front of each api call
using namespace TS;
using namespace TSUI;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__FF4C7097_1F62_4A89_A2BC_B1D46574CB13__INCLUDED)
