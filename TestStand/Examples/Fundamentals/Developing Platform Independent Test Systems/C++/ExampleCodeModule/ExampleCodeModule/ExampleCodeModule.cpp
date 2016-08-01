// This is the main DLL file.

#include "stdafx.h"

#include "ExampleCodeModule.h"

 __declspec(dllexport) int getCurrentPlatformFunc()
{
	#ifdef _WIN64
		return 64;
	#else 
		return 32;
	#endif
}
