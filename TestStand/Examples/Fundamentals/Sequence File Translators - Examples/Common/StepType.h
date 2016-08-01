#ifndef __CVIStepTypeExample__Header__
#define __CVIStepTypeExample__Header__

#include "tsutil.h"

extern __declspec(dllexport) void _stdcall Configure(double minACFrequency, double maxACFrequency, int *handle);
extern __declspec(dllexport) void _stdcall ExecuteStep(int handle, double ACFrequency, boolean *testPassed, double *RMSValue);
extern __declspec(dllexport) void _stdcall Close(int handle);
#endif /* __CVIStepTypeExample__Header__ */
