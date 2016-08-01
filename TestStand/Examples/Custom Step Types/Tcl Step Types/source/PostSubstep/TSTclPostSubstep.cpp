// TSTclPostSubstep.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "TSTclPostSubstep.h"
#include "..\Shared\TclError.h"
#include "..\TSTclInterpreter\TSTclInterpreter_i.c"

static HANDLE sMutex = NULL;

#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		sMutex = CreateMutex(NULL, FALSE, NULL);
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		CloseHandle(sMutex);
		break;
	}
    return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif

void ReportError(PropertyObjectPtr step, TclError error)
{
	step->SetValBoolean(TCL_STEP_ERROR_OCCURED, 0, VARIANT_TRUE);
	step->SetValNumber(TCL_STEP_ERROR_CODE, 0, error.error);
	step->SetValString(TCL_STEP_ERROR_MSG, 0, error.description);
}

class PerInterpreterLock
{
public:

	PerInterpreterLock(DWORD processId)
	{
		char nameBuf[256];
		sprintf_s(nameBuf, "National Instruments TestStand TCL Interpreter Mutex 0x%x", processId);
		mMutex = CreateMutex(NULL, FALSE, nameBuf);
		if(!mMutex)
			throw TclError(TS::TS_Err_UnableToAllocateSystemResource, _bstr_t(""));

		WaitForSingleObject(mMutex, INFINITE);
	}
	~PerInterpreterLock()
	{
		ReleaseMutex(mMutex);
		CloseHandle(mMutex);
	}

private:
	HANDLE mMutex;
};

__declspec(dllexport) void ExecuteStep(SequenceContext * context)
{
	WaitForSingleObject(sMutex, INFINITE);
	bool haveMutex = true;
	try
	{
		PropertyObjectPtr step = context->GetStep()->AsPropertyObject();
		//check operation

				double operation = step->GetValNumber(TCL_STEP_TYPE_OPERATION, 0);
		double interpreterToUse = step->GetValNumber(TCL_STEP_TYPE_EXECUTION_OPTION, 0);
		_bstr_t interpLookupString = GetInterpLookupString(context, interpreterToUse);

		if (operation == TCL_OPERATION_RESET)
		{
			//create interpreter no matter what
			CreateInterpreter(context, GetBaseObject(context, interpreterToUse), interpLookupString);
			ReleaseMutex(sMutex);
			haveMutex = false;
		}
		else if(operation==TCL_OPERATION_EVAL_FILE || operation==TCL_OPERATION_EVAL_EXPR_VAL || operation == TCL_OPERATION_EVAL_LITERAL)
		{
			ITclInterpreterPtr interpRef = CheckAndCreateInterpreter(context, GetBaseObject(context, interpreterToUse), interpLookupString);
			
			ReleaseMutex(sMutex);
			haveMutex = false;
			
			unsigned long processID;

			try
			{
				processID = interpRef->ProcessID;
			}
			catch (_com_error err)
			{
				//there was an error getting the property, sever is not available, so create it
				WaitForSingleObject(sMutex, INFINITE);
				bool haveMutex = true;
				interpRef = CreateInterpreter(context, GetBaseObject(context, interpreterToUse), interpLookupString);
				ReleaseMutex(sMutex);
				haveMutex = false;
				processID = interpRef->ProcessID;
			}

			PerInterpreterLock lock(processID);
			interpRef->ExecuteStep(context);
		}
		else
			throw TclError(ERROR_PROPERTY_INVALID, context->Engine->GetResourceString(TCL_STEP_TYPE_SECTION, "OPERATION_INVALID_ERROR" , vtMissing, &vtMissing));
	}
	catch (TclError error)
	{
		ReportError(context->Step->AsPropertyObject(), error);
	}
	catch (_com_error err)
	{
		ReportError(context->Step->AsPropertyObject(), TclError(err));
	}
	catch (...)
	{
		ReportError(context->Step->AsPropertyObject(), TclError(ERROR_UNKNOWN, context->Engine->GetResourceString(TCL_STEP_TYPE_SECTION, "UNKNOWN_ERROR" , vtMissing, &vtMissing)));
	}
	if (haveMutex)
		ReleaseMutex(sMutex);
}


PropertyObjectPtr GetBaseObject(SequenceContextPtr context, double option)
{
	if(option == TCL_EXECUTION_OPTION_STEP)
		return NULL;

	else if (option == TCL_EXECUTION_OPTION_THREAD)
		return context->Thread->RunTimeVariables;

	else if (option == TCL_EXECUTION_OPTION_EXECUTION)
		return context->Execution->RunTimeVariables;

	else if (option == TCL_EXECUTION_OPTION_GLOBAL)
		return context->Engine->TemporaryGlobals;

	else if (option == TCL_EXECUTION_OPTION_REF)
		return context->AsPropertyObject()->EvaluateEx(context->Step->AsPropertyObject()->GetValString(TCL_STEP_TYPE_INTERP_REF_EXPR, 0),0);
	
	else
		throw TclError(ERROR_PROPERTY_INVALID, context->Engine->GetResourceString(TCL_STEP_TYPE_SECTION, "INTERPRETER_TO_USE_INVALID_ERROR" , vtMissing, &vtMissing));

}

_bstr_t GetInterpLookupString(SequenceContextPtr context, double option)
{
	if(option == TCL_EXECUTION_OPTION_STEP || option == TCL_EXECUTION_OPTION_REF)
		return _bstr_t("");

	else if (option == TCL_EXECUTION_OPTION_THREAD || option== TCL_EXECUTION_OPTION_EXECUTION || option == TCL_EXECUTION_OPTION_GLOBAL)
		return _bstr_t(TCL_INTERP_LOCATION);
	else
		throw TclError(ERROR_PROPERTY_INVALID, context->Engine->GetResourceString(TCL_STEP_TYPE_SECTION, "INTERPRETER_TO_USE_INVALID_ERROR" , vtMissing, &vtMissing));
}


ITclInterpreterPtr CheckAndCreateInterpreter(SequenceContextPtr context, PropertyObjectPtr baseObj, _bstr_t lookupString)
{
	if (baseObj == NULL)
		return CreateInterpreter(context, baseObj, lookupString);

	if (baseObj->Exists(lookupString, 0))
	{
		ITclInterpreterPtr interpreter = baseObj->GetValInterface(lookupString, 0);
		if(interpreter == NULL)
			return CreateInterpreter(context, baseObj, lookupString);
		return interpreter;
	}
	else
		return CreateInterpreter(context, baseObj, lookupString);
}

ITclInterpreterPtr CreateInterpreter(SequenceContextPtr context, PropertyObjectPtr baseObj, _bstr_t lookupString)
{
	ITclInterpreterPtr interpreter;
	HRESULT result = interpreter.CreateInstance(CLSID_TclInterpreter);
	if (result== S_OK)
	{	
		if (baseObj != NULL)
			baseObj->SetValInterface(lookupString, 0x1, interpreter);
	}
	else if(result==REGDB_E_CLASSNOTREG)
		throw TclError(ERROR_CLASS_NOT_REGISTERED, context->Engine->GetResourceString(TCL_STEP_TYPE_SECTION, "CLASS_NOT_REGISTER_ERROR" , vtMissing, &vtMissing));
	else
	{
		throw TclError(ERROR_UNKNOWN, context->Engine->GetResourceString(TCL_STEP_TYPE_SECTION, "UNKNOWN_ERROR_CREATE", vtMissing, &vtMissing));
	}
	return interpreter;
}


