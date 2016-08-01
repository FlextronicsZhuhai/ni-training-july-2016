#include "extcode.h"
#pragma pack(push)
#pragma pack(1)

#ifdef __cplusplus
extern "C" {
#endif
typedef struct {
	int32_t dimSize;
	double Numeric[1];
	} TD2;
typedef TD2 **TD2Hdl;

typedef struct {
	double Numeric;
	LStrHandle String;
	TD2Hdl Array;
	LVBoolean Boolean;
	} TD1;


void __cdecl UnbundleStruct(TD1 *Cluster, double *Numeric, char String[], 
	int32_t StrLen, double Array[], int32_t ArrayLen, LVBoolean *Boolean);
void __cdecl BundleStruct(LVBoolean *Boolean, double Array[], 
	int32_t Arraylen, char String[], double Numeric, TD1 *outputCluster);

long __cdecl LVDLLStatus(char *errStr, int errStrLen, void *module);

#ifdef __cplusplus
} // extern "C"
#endif

#pragma pack(pop)

