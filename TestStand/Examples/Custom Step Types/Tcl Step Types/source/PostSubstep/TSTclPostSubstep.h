// This class is exported from the TSTclPostSubstep.dll
#include "stdafx.h"
#include "..\Shared\TclStepProperties.h"

class CTSTclPostSubstep {
public:
	CTSTclPostSubstep(void);
private:

};

__declspec(dllexport) void ExecuteStep(SequenceContext * context);
ITclInterpreterPtr CheckAndCreateInterpreter(SequenceContextPtr context, PropertyObjectPtr baseObj, _bstr_t lookupString);
ITclInterpreterPtr CreateInterpreter(SequenceContextPtr context, PropertyObjectPtr baseObj, _bstr_t lookupString);
PropertyObjectPtr GetBaseObject(SequenceContextPtr context, double option);
_bstr_t GetInterpLookupString(SequenceContextPtr context, double option);