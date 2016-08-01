// ExecuteTPS.cpp : Implementation of CExecuteTPS
#include "stdafx.h"
#include "ATLAS_StepType.h"
#include "Utils.h"
#include "ATLASParameter.h"
#include "ConfigureExecutionDlg.h"
#include "ManualInterventionDlg.h"
#include "ExecuteTPS.h"

/////////////////////////////////////////////////////////////////////////////
// Utilities

#define PRE_API_FUNC_CODE   \
    HRESULT retval = S_OK;  \
    try {   \
    AFX_MANAGE_STATE(AfxGetStaticModuleState())

#define CATCH_ALL_AND_SET_ERROR_INFO(seqContext) \
        catch (_com_error &com_except) {    \
            retval = com_except.Error();    \
            TSError teErrorCode = (TSError)(short)HRESULT_CODE(retval); \
            ::ReportErrorStatus(seqContext, teErrorCode, (const char *)com_except.Description());   \
        }   \
        catch(TSError teErrorCode) {    \
            retval = (HRESULT) teErrorCode; \
            ::ReportErrorStatus(seqContext, teErrorCode, NULL); \
        }   \
        catch(HRESULT errorCode) {  \
            retval = errorCode; \
            ::ReportErrorStatus(seqContext, (TSError) errorCode, NULL); \
        }   \
        catch(int errorCode) {  \
            retval = (HRESULT) errorCode;   \
            ::ReportErrorStatus(seqContext, (TSError) errorCode, NULL); \
        }   \
        catch (...) \
        {   \
            TSError teErrorCode = TS::TS_Err_UnexpectedSystemError; \
            retval = (HRESULT) teErrorCode; \
            ::ReportErrorStatus(seqContext, teErrorCode, NULL); \
        }

#define POST_API_FUNC_CODE(seqContext)  \
    }   \
    CATCH_ALL_AND_SET_ERROR_INFO(seqContext)    \
    return retval;

#define V2CBOOL(_vb)            (_vb==VARIANT_TRUE)
#define C2VBOOL(_cb)            (_cb?VARIANT_TRUE:VARIANT_FALSE)
#define ERROR_TPSAlreadyOpen    0x80043220

#define TPS_PROP                            "PAWSTPSServer"         // Reference
#define TS_PROP                             "TS"                    // Container
#define STEP_PROP                           "Step"                  // String
#define RESULT_PROP                         "Result"                // Object
#define STATUS_PROP                         "Status"                // String
#define REPORT_TEXT_PROP                    "ReportText"            // String
#define MUTEXNAMEORREF_PROP                 "MutexNameOrRef"        // String
#define SDATA_PROP                          "SData"                 // Container
#define TPSFILEPATH_PROP                    "TPSFilePath"           // String
#define EXECUTE_REMOTELY_PROP               "ExecuteRemotely"       // Boolean
#define REMOTE_HOST_NAME_EXPR_PROP          "RemoteHostNameExpr"    // String
#define PARAMETERS_PROP                     "Parameters"            // Container
#define PARAMETER_NAME_PROP                 "Name"                  // String
#define PARAMETER_DATA_TYPE_PROP            "DataType"              // String
#define PARAMETER_PASS_MODE_PROP            "PassMode"              // Number
#define PARAMETER_IS_GLOBAL_VAR_PROP        "IsGlobalVariable"      // Boolean
#define PARAMETER_VALUE_EXPR_PROP           "ValueExpression"       // String
#define ERROR_PROP                          "Error"                 // Object
#define ERROR_OCCURRED_PROP                 "Occurred"              // Boolean
#define ERROR_CODE_PROP                     "Code"                  // Numeric
#define ERROR_MESSAGE_PROP                  "Msg"                   // String

static const CString ksAtlasLockNamePrefixExpr = _T("\"*ATLAS_LOCK_\"");
static const CString ksLocalHostLockNameExpr = _T("\"*ATLAS_LOCK_LOCAL_HOST\"");

class CExternalSuspender
{
public:
    CExternalSuspender(const TS::ThreadPtr& threadPtr) : 
        m_ThreadPtr(threadPtr)
    {
        m_ExternallySuspendedState = m_ThreadPtr->ExternallySuspended;
        m_ThreadPtr->ExternallySuspended = VARIANT_TRUE;
    }
    ~CExternalSuspender()
    {
        m_ThreadPtr->ExternallySuspended = m_ExternallySuspendedState;
    }
private:
    const TS::ThreadPtr& m_ThreadPtr;
    VARIANT_BOOL m_ExternallySuspendedState;
};

/* ======================================================================================================== **
    SetStepError
** -------------------------------------------------------------------------------------------------------- */

static void SetStepError (
    TS::IEnginePtr &engine,
    TS::StepPtr &step, 
    TS::TSError teErrorCode, 
    const char *errorMsg)
{
    CString errorString;
    if (errorMsg == NULL)
    {
        CComBSTR tmpBSTR;

        engine->GetErrorString(teErrorCode, &tmpBSTR);

        errorString = tmpBSTR;
    } else {
        errorString = errorMsg;
    }

    TS::PropertyObjectPtr stepPropObj = step->AsPropertyObject();

    stepPropObj->SetValString(RESULT_PROP "." ERROR_PROP "." ERROR_MESSAGE_PROP, 0, LPCTSTR(errorString));
    stepPropObj->SetValNumber(RESULT_PROP "." ERROR_PROP "." ERROR_CODE_PROP, 0, teErrorCode);
    stepPropObj->SetValBoolean(RESULT_PROP "." ERROR_PROP "." ERROR_OCCURRED_PROP, 0, VARIANT_TRUE);
}

/* ======================================================================================================== **
    ReportErrorStatus
** -------------------------------------------------------------------------------------------------------- */

static void ReportErrorStatus (TS::SequenceContextPtr& seqContext, TSError teErrorCode, const char *errorMsg)
{
    try
    {
        StepPtr step = seqContext->GetStep();
        IEnginePtr engine = seqContext->GetEngineAsDispatch();

        ::SetStepError(engine, step, teErrorCode, errorMsg);

    } catch (...) {
        CString errorString;

        errorString.Format(_T("Unable to report error to caller:\n")
                           _T("Error code = %d"),
                           teErrorCode);

        if (errorMsg != NULL) {
            errorString += _T("\nError message = ");
            errorString += errorMsg;
        }

        ::MessageBox(NULL,  // owner window
                     errorString,
                     _T("ATLAS Substeps DLL"),
                     MB_OK | MB_ICONERROR);
    }
}

/* ======================================================================================================== **
    StepResults - report TPS execution results to TestStand
** -------------------------------------------------------------------------------------------------------- */
typedef enum {
    Normal  = 0, 
    Skipped = 1,
} StepResults;

/* ======================================================================================================== **
    SetStepResultStatus - sets step result status in TestStand according to TPS execution
** -------------------------------------------------------------------------------------------------------- */
static HRESULT SetStepResultStatus(
    const RTSAX::ITpsServerExPtr& spTpsServerEx, 
    const TS::IEnginePtr& enginePtr,
    const TS::PropertyObjectPtr& seqContext, 
    StepResults status)
{
    // If TPS execution was normal, then check for faults.
    long faultCount = 0;
    if (status == Normal)
        RETURN_IF_FAILED(spTpsServerEx->get_FaultCounter(&faultCount));

    // Set the text according to the status
    CString statusText, reportText;
    switch (status)
    {
        case Skipped:
            // report TPS was not executed
            statusText = GetResourceString(enginePtr, _T("STEP RESULT STATUS"), _T("Skipped"));
            break;

        case Normal:
            // handles Normal failed case
            if (faultCount > 0) 
            {
                // report TPS execution failed (faults found)
                statusText = GetResourceString(enginePtr, _T("STEP RESULT STATUS"), _T("Failed"));

                // report how many faults were found
                reportText.Format(GetResourceString(enginePtr, ATLAS_STEP_TYPE_STRING, _T("FAULT_COUNT")), faultCount);
                seqContext->SetValString(STEP_PROP "." RESULT_PROP "." REPORT_TEXT_PROP, 0, (LPCTSTR)reportText);       
                break;
            }

        // handles Normal passed case
        default: 
            // report TPS execution completed
            statusText = GetResourceString(enginePtr, _T("STEP RESULT STATUS"), _T("Done"));
    }

    // Set the step result status text 
    seqContext->SetValString(STEP_PROP "." RESULT_PROP "." STATUS_PROP, 0, (LPCTSTR)statusText);

    return S_OK;
}


/* ======================================================================================================== **
    ReadWriteParameters
** -------------------------------------------------------------------------------------------------------- */
static HRESULT ReadWriteParameters (
    TS::PropertyObjectPtr& parametersPropObj, 
    const RTSAX::ITpsServerExPtr& spTpsServerEx, 
    const TS::PropertyObjectPtr& seqContext,
    bool doWrite)
{
    CComPtr<IDispatch> spDspParameters;
    CComPtr<IDataBag> spDataBagParameters;
    CComPtr<IDispatch> spDspResults;
    CComPtr<IDataColl> spDataCollResults;
    long nbrResults = 0;
    HRESULT hr;

    const long numParameters = parametersPropObj->GetNumElements();
    for (long i = 0; i < numParameters; i++)
    {
        TS::PropertyObjectPtr parameterPropObj = 
            parametersPropObj->GetPropertyObjectByOffset(i, PropOption_NoOptions);
        TS::PropertyObjectPtr parameterNamePropObj = 
            parameterPropObj->GetPropertyObject(PARAMETER_NAME_PROP, PropOption_NoOptions);
        TS::PropertyObjectPtr parameterDataTypePropObj = 
            parameterPropObj->GetPropertyObject(PARAMETER_DATA_TYPE_PROP, PropOption_NoOptions);
        TS::PropertyObjectPtr parameterPassModePropObj = 
            parameterPropObj->GetPropertyObject(PARAMETER_PASS_MODE_PROP, PropOption_NoOptions);
        TS::PropertyObjectPtr parameterIsGlobalVarPropObj = 
            parameterPropObj->GetPropertyObject(PARAMETER_IS_GLOBAL_VAR_PROP, PropOption_NoOptions);
        TS::PropertyObjectPtr parameterValueExpressionPropObj = 
            parameterPropObj->GetPropertyObject(PARAMETER_VALUE_EXPR_PROP, PropOption_NoOptions);

        CATLASParameter parameter;
        parameter.m_Name = (LPCTSTR) parameterNamePropObj->GetValString(L"", PropOption_NoOptions);
        parameter.m_ValueType = (ValueTypes) (long) 
            parameterDataTypePropObj->GetValNumber(L"", PropOption_NoOptions);
        parameter.m_PassMode = (PassModes) (long) 
            parameterPassModePropObj->GetValNumber(L"", PropOption_NoOptions);
        parameter.m_IsGlobalVariable = 
            V2CBOOL(parameterIsGlobalVarPropObj->GetValBoolean(L"", PropOption_NoOptions));
        parameter.m_ValueExpression = (LPCTSTR) 
            parameterValueExpressionPropObj->GetValString(L"", PropOption_NoOptions);

        TS::PropertyObjectPtr valuePropObj;
        _variant_t value;

        if (doWrite)
        {
            if ((parameter.m_PassMode == Write) || (parameter.m_PassMode == ReadWrite))
            {
                valuePropObj = seqContext->Evaluate((LPCTSTR) parameter.m_ValueExpression);
                switch(parameter.m_ValueType)
                {
                    case Number:
                        value = valuePropObj->GetValNumber(L"", PropOption_NoOptions);
                        break;
                    case String:
                        value = (const wchar_t*) valuePropObj->GetValString(L"", PropOption_NoOptions);
                        break;
                    case Boolean:
                        value = (bool) V2CBOOL(valuePropObj->GetValBoolean(L"", PropOption_NoOptions));
                        break;
                    default:
                        break;
                }

                if (parameter.m_IsGlobalVariable)
                {
                    hr = spTpsServerEx->PutData(CComBSTR(parameter.m_Name), value);
                    RETURN_IF_FAILED(hr);
                }
                else    // Parameter
                {
                    if (spDataBagParameters == NULL)
                    {
                        hr = spTpsServerEx->get_Parameters(&spDspParameters);
                        RETURN_IF_FAILED(hr);
                        hr = spDspParameters->QueryInterface(&spDataBagParameters);
                        RETURN_IF_FAILED(hr);
                    }

                    hr = spDataBagParameters->Put(CComBSTR(parameter.m_Name), value);
                    RETURN_IF_FAILED(hr);
                }
            }
        }
        else    // read
        {
            if ((parameter.m_PassMode == Read) || (parameter.m_PassMode == ReadWrite))
            {
                if (parameter.m_IsGlobalVariable)
                {
                    hr = spTpsServerEx->GetData(CComBSTR(parameter.m_Name), &value);
                    RETURN_IF_FAILED(hr);
                }
                else    // Results
                {
                    if (spDataCollResults == NULL)
                    {
                        hr = spTpsServerEx->get_Results(&spDspResults);
                        RETURN_IF_FAILED(hr);
                        hr = spDspResults->QueryInterface(&spDataCollResults);
                        RETURN_IF_FAILED(hr);
                        hr = spDataCollResults->get_Count(&nbrResults);
                        RETURN_IF_FAILED(hr);
                    }

                    for (long l = 1; l <= nbrResults; l++)
                    {
                        CComPtr<IData> spData;
                        hr = spDataCollResults->get_Item(l, &spData);
                        RETURN_IF_FAILED(hr);

                        CComBSTR sName;
                        hr = spData->get_Name(&sName);
                        RETURN_IF_FAILED(hr);

                        if (sName == (LPCSTR)parameter.m_Name)
                        {
                            hr = spData->get_Value(&value);
                            RETURN_IF_FAILED(hr);
                            break;
                        }
                    }
                }

                valuePropObj = seqContext->Evaluate((LPCTSTR) parameter.m_ValueExpression);
                switch(parameter.m_ValueType)
                {
                    case Number:
                        valuePropObj->SetValNumber(L"", PropOption_NoOptions, value.dblVal);
                        break;
                    case String:
                        valuePropObj->SetValString(L"", PropOption_NoOptions, value.bstrVal);
                        break;
                    case Boolean:
                        valuePropObj->SetValBoolean(L"", PropOption_NoOptions, value.boolVal);
                        break;
                    default:
                        break;
                }
            }
        }
    }

    return S_OK;
}

/* ======================================================================================================== **
    SetParameters
** -------------------------------------------------------------------------------------------------------- */

static void SetParameters (
    const TS::PropertyObjectPtr& parametersPropObj, 
    CATLASParameterArray& parameters)
{
    const long numParameters = parametersPropObj->GetNumElements();
    for (long i = 0; i < numParameters; i++)
    {
        TS::PropertyObjectPtr parameterPropObj = 
            parametersPropObj->GetPropertyObjectByOffset(i, PropOption_NoOptions);
        TS::PropertyObjectPtr parameterNamePropObj = 
            parameterPropObj->GetPropertyObject(PARAMETER_NAME_PROP, PropOption_NoOptions);
        TS::PropertyObjectPtr parameterDataTypePropObj = 
            parameterPropObj->GetPropertyObject(PARAMETER_DATA_TYPE_PROP, PropOption_NoOptions);
        TS::PropertyObjectPtr parameterPassModePropObj = 
            parameterPropObj->GetPropertyObject(PARAMETER_PASS_MODE_PROP, PropOption_NoOptions);
        TS::PropertyObjectPtr parameterIsGlobalVarPropObj = 
            parameterPropObj->GetPropertyObject(PARAMETER_IS_GLOBAL_VAR_PROP, PropOption_NoOptions);
        TS::PropertyObjectPtr parameterValueExpressionPropObj = 
            parameterPropObj->GetPropertyObject(PARAMETER_VALUE_EXPR_PROP, PropOption_NoOptions);

        CATLASParameter* parameter = new CATLASParameter;
        parameter->m_Name = (LPCTSTR) parameterNamePropObj->GetValString(L"", PropOption_NoOptions);
        parameter->m_ValueType = (ValueTypes) (long) 
            parameterDataTypePropObj->GetValNumber(L"", PropOption_NoOptions);
        parameter->m_PassMode = (PassModes) (long) 
            parameterPassModePropObj->GetValNumber(L"", PropOption_NoOptions);
        parameter->m_IsGlobalVariable = 
            V2CBOOL(parameterIsGlobalVarPropObj->GetValBoolean(L"", PropOption_NoOptions));
        parameter->m_ValueExpression = (LPCTSTR) 
            parameterValueExpressionPropObj->GetValString(L"", PropOption_NoOptions);
        parameters.Add(parameter);
    }
}

/* ======================================================================================================== **
    GetParameters
** -------------------------------------------------------------------------------------------------------- */

static void GetParameters (
    const CATLASParameterArray& parameters, 
    TS::PropertyObjectPtr& parametersPropObj)
{
    const long numParameters = parameters.GetSize();
    parametersPropObj->SetNumElements(numParameters,PropOption_NoOptions);
    for (long i = 0; i < numParameters; i++)
    {
        CATLASParameter* parameter = parameters[i];
        TS::PropertyObjectPtr parameterPropObj = 
            parametersPropObj->GetPropertyObjectByOffset(i, PropOption_NoOptions);
        TS::PropertyObjectPtr parameterNamePropObj = 
            parameterPropObj->GetPropertyObject(PARAMETER_NAME_PROP, PropOption_NoOptions);
        TS::PropertyObjectPtr parameterDataTypePropObj = 
            parameterPropObj->GetPropertyObject(PARAMETER_DATA_TYPE_PROP, PropOption_NoOptions);
        TS::PropertyObjectPtr parameterPassModePropObj = 
            parameterPropObj->GetPropertyObject(PARAMETER_PASS_MODE_PROP, PropOption_NoOptions);
        TS::PropertyObjectPtr parameterIsGlobalVarPropObj = 
            parameterPropObj->GetPropertyObject(PARAMETER_IS_GLOBAL_VAR_PROP, PropOption_NoOptions);
        TS::PropertyObjectPtr parameterValueExpressionPropObj = 
            parameterPropObj->GetPropertyObject(PARAMETER_VALUE_EXPR_PROP, PropOption_NoOptions);

        parameterNamePropObj->SetValString(L"", PropOption_NoOptions, (LPCTSTR) parameter->m_Name);
        parameterDataTypePropObj->SetValNumber(L"", PropOption_NoOptions, (double) parameter->m_ValueType);
        parameterPassModePropObj->SetValNumber(L"", PropOption_NoOptions, (double) parameter->m_PassMode);
        parameterIsGlobalVarPropObj->SetValBoolean(L"", PropOption_NoOptions, C2VBOOL(parameter->m_IsGlobalVariable));
        parameterValueExpressionPropObj->SetValString(L"", PropOption_NoOptions, (LPCTSTR) parameter->m_ValueExpression);
    }
}

/////////////////////////////////////////////////////////////////////////////
// CExecuteTPS

/* ======================================================================================================== **
    InterfaceSupportsErrorInfo
** -------------------------------------------------------------------------------------------------------- */

STDMETHODIMP CExecuteTPS::InterfaceSupportsErrorInfo(REFIID riid)
{
    static const IID* arr[] = 
    {
        &IID_IExecuteTPS
    };
    for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        if (InlineIsEqualGUID(*arr[i],riid))
            return S_OK;
    }
    return S_FALSE;
}

/* ======================================================================================================== **
    EditStep
** -------------------------------------------------------------------------------------------------------- */

STDMETHODIMP CExecuteTPS::EditStep (
    TS::SequenceContext *sequenceContext,
    long reserved, 
    long *changeCount)
{
    SequenceContextPtr seqContext = sequenceContext;

    PRE_API_FUNC_CODE

    ::AfxEnableControlContainer();

    TS::IEnginePtr enginePtr = seqContext->GetEngine();
    TS::PropertyObjectPtr stepPropObj = seqContext->GetStep()->AsPropertyObject();
    TS::PropertyObjectPtr sDataPropObj = stepPropObj->GetPropertyObject(SDATA_PROP, 0);
    TS::PropertyObjectPtr tpsFilePathPropObj = sDataPropObj->GetPropertyObject(TPSFILEPATH_PROP, 0);
    TS::PropertyObjectPtr executeRemotelyPropObj = sDataPropObj->GetPropertyObject(EXECUTE_REMOTELY_PROP, 0);
    TS::PropertyObjectPtr remoteHostNameExprPropObj = sDataPropObj->GetPropertyObject(REMOTE_HOST_NAME_EXPR_PROP, 0);
    TS::PropertyObjectPtr parametersPropObj = sDataPropObj->GetPropertyObject(PARAMETERS_PROP, 
        PropOption_NoOptions);

    CATLASParameters parameters;
    SetParameters(parametersPropObj,parameters.m_Parameters);

    CConfigureExecutionDlg dlg(enginePtr,seqContext,FALSE,parameters.m_Parameters);

    dlg.m_TPS = (LPCTSTR) tpsFilePathPropObj->GetValString(L"", 0);
    dlg.m_ExecuteRemotely = (BOOL) (executeRemotelyPropObj->GetValBoolean(L"", 0) == VARIANT_TRUE);
    dlg.m_RemoteHostNameExpr = (LPCTSTR) remoteHostNameExprPropObj->GetValString(L"", 0);

    *changeCount = seqContext->GetSequenceFile()->GetChangeCount();

    if (dlg.DoModal() == IDOK)
    {
        tpsFilePathPropObj->SetValString(L"", 0, (LPCTSTR) dlg.m_TPS);
        executeRemotelyPropObj->SetValBoolean(L"", 0, dlg.m_ExecuteRemotely ? VARIANT_TRUE : VARIANT_FALSE);
        remoteHostNameExprPropObj->SetValString(L"", 0, (LPCTSTR) dlg.m_RemoteHostNameExpr);

        // Set the Step Lock Name Expression
        CString lockNameExpr = dlg.m_ExecuteRemotely ? 
            (ksAtlasLockNamePrefixExpr + _T(" + ") + dlg.m_RemoteHostNameExpr) : 
            ksLocalHostLockNameExpr;
        TS::PropertyObjectPtr tsPropObj = stepPropObj->GetPropertyObject(TS_PROP, 0);
        TS::PropertyObjectPtr sMutexNameOrRefPropObj = tsPropObj->GetPropertyObject(MUTEXNAMEORREF_PROP, 0);
        sMutexNameOrRefPropObj->SetValString(L"", 0, (LPCTSTR) lockNameExpr);

        GetParameters(parameters.m_Parameters,parametersPropObj);

        (*changeCount)++;
    }

    POST_API_FUNC_CODE(seqContext)
}

/* ======================================================================================================== **
    IterateExecutionStateMachine
** -------------------------------------------------------------------------------------------------------- */

bool CExecuteTPS::IterateExecutionStateMachine (
    const RunModes& runMode, 
    ExecutionStates& executionState, 
    const TS::IEnginePtr& enginePtr,
    TS::PropertyObjectPtr& parametersPropObj, 
    const TS::PropertyObjectPtr& seqContextPropObj,
    const RTSAX::ITpsServerExPtr& spTpsServerEx)
{
    HRESULT hr;
    const RTSAX::RtsAxState rtsState = m_RTSServerState.GetState();
    bool done = false;
    switch (executionState)
    {
        case ES_ATTACHING:
            // if still doing the Attach
            if (rtsState == RTSAX::RTSAX_STATE_DETACHED)
            {
                // Do Nothing, wait for the Attach to complete
                // Assumption is that the RTS Server will complete the Attach quickly, especially before
                // the execution is terminated/aborted or paused
            }
            // if done with the Attach
            else if (rtsState == RTSAX::RTSAX_STATE_UNLOADED)
            {
                if (runMode == RM_NORMAL)
                {
                    // Load TPS
                    executionState = ES_LOADING;
                    hr = spTpsServerEx->Load(m_TPSFilePath.m_str);
                    if (hr == ERROR_TPSAlreadyOpen)
                        HandleTPSAlreadyLoaded(enginePtr, executionState, seqContextPropObj, spTpsServerEx);    
                    else
                        THROW_IF_FAILED(hr);
                }
                else if (runMode == RM_TERMINATING)
                {
                    // End execution
                    executionState = ES_UNLOADED;
                }
                else if (runMode == RM_PAUSED)
                {
                    // Transition to the Attached state
                    // will start the TPS loading when (and if) the TestStand run state goes to Normal
                    executionState = ES_ATTACHED;
                }
                else    // invalid run mode
                {           
                    THROW_ERROR(TS_Err_ProgramError, GetResourceString(enginePtr, ATLAS_STEP_TYPE_STRING, _T("INVALID_RUN_MODE_ERR")));
                }
            }
            // if there is already a TPS loaded when we attach, ask to unload the TPS or skip execution
            else if (rtsState == RTSAX::RTSAX_STATE_READY  || 
                     rtsState == RTSAX::RTSAX_STATE_HALTED || 
                     rtsState == RTSAX::RTSAX_STATE_FINISH)
            {
                HandleTPSAlreadyLoaded(enginePtr, executionState, seqContextPropObj, spTpsServerEx);
            }
            // another TPS is currently executing. We cannot execute requested TPS.
            else if (rtsState == RTSAX::RTSAX_STATE_RUNNING)
            {
                THROW_ERROR(TS_Err_OperationInProgress, GetResourceString(enginePtr, ATLAS_STEP_TYPE_STRING, _T("OTHER_TPS_RUNNING_ERR")));
            }

            // otherwise, the RTS Server is in an invalid state
            else
            {
                THROW_ERROR(TS_Err_AccessDenied, GetResourceString(enginePtr, ATLAS_STEP_TYPE_STRING, _T("RTS_INVALID_STATE_ERR")));
            }
            break;

        case ES_ATTACHED:
            if (rtsState == RTSAX::RTSAX_STATE_UNLOADED)
            {
                if (runMode == RM_NORMAL)
                {
                    // Load TPS
                    executionState = ES_LOADING;
                    hr = spTpsServerEx->Load(m_TPSFilePath.m_str);
                    THROW_IF_FAILED(hr);
                }
                else if (runMode == RM_TERMINATING)
                {
                    // End execution
                    executionState = ES_UNLOADED;
                }
                else if (runMode == RM_PAUSED)
                {
                    // Do Nothing, wait
                }
                else    // invalid run mode
                {
                    THROW_ERROR(TS_Err_ProgramError, GetResourceString(enginePtr, ATLAS_STEP_TYPE_STRING, _T("INVALID_RUN_MODE_ERR")));
                }
            }
            // if there is already a TPS loaded
            else if (rtsState == RTSAX::RTSAX_STATE_READY  || 
                     rtsState == RTSAX::RTSAX_STATE_HALTED || 
                     rtsState == RTSAX::RTSAX_STATE_FINISH || 
                     rtsState == RTSAX::RTSAX_STATE_RUNNING)
            {
                // Do Nothing, wait for unload to finish
            }
            // otherwise, the RTS Server is in an invalid state
            else
            {
                THROW_ERROR(TS_Err_AccessDenied, GetResourceString(enginePtr, ATLAS_STEP_TYPE_STRING, _T("RTS_INVALID_STATE_ERR")));
            }
            break;

        case ES_LOADING:
            // if haven't started or still doing the Load
            if ((rtsState == RTSAX::RTSAX_STATE_UNLOADED) || 
                (rtsState == RTSAX::RTSAX_STATE_RUNNING)  ||
                (rtsState == RTSAX::RTSAX_STATE_HALTED))
            {
                // Do Nothing, regardless of the TestStand run mode, have to wait to finish loading
                // assuming that the RTS Server will start loading the TPS quickly, especially before
                // the execution is terminated/aborted or paused
            }
            // if done with the Load
            else if (rtsState == RTSAX::RTSAX_STATE_READY)
            {
                // Check run mode and proceed accordingly
                if (runMode == RM_NORMAL)
                {
                    // Read the parameters from the Step and 
                    // Write the parameters (Global Variables and Parameters) to the TPS Server
                    hr = ReadWriteParameters(parametersPropObj,spTpsServerEx,seqContextPropObj,true);
                    THROW_IF_FAILED(hr);

                    // Run the TPS
                    executionState = ES_RUNNING;
                    hr = spTpsServerEx->Run();
                    THROW_IF_FAILED(hr);
                }
                else if (runMode == RM_TERMINATING)
                {
                    // Unload TPS
                    executionState = ES_UNLOADING;
                    hr = spTpsServerEx->Unload();
                    THROW_IF_FAILED(hr);
                }
                else if (runMode == RM_PAUSED)
                {
                    // Transition to the Loaded state
                    // wait to start running the TPS when the TestStand run state goes to Normal
                    executionState = ES_LOADED;
                }
                else    // invalid run mode
                {
                    THROW_ERROR(TS_Err_ProgramError, GetResourceString(enginePtr, ATLAS_STEP_TYPE_STRING, _T("INVALID_RUN_MODE_ERR")));
                }
            }
            // otherwise, the RTS Server is in an invalid state
            else
            {
                THROW_ERROR(TS_Err_ModuleLoadFailure, GetResourceString(enginePtr, ATLAS_STEP_TYPE_STRING, _T("RTS_LOADING_FAILED_ERR")));
            }
            break;

        case ES_LOADED:
            if (rtsState == RTSAX::RTSAX_STATE_READY)
            {
                if (runMode == RM_NORMAL)
                {
                    // Read the parameters from the Step and 
                    // Write the parameters (Global Variables and Parameters) to the TPS Server
                    hr = ReadWriteParameters(parametersPropObj,spTpsServerEx,seqContextPropObj,true);
                    THROW_IF_FAILED(hr);

                    // Run the TPS
                    executionState = ES_RUNNING;
                    hr = spTpsServerEx->Run();
                    THROW_IF_FAILED(hr);
                }
                else if (runMode == RM_TERMINATING)
                {
                    // Unload TPS
                    executionState = ES_UNLOADING;
                    hr = spTpsServerEx->Unload();
                    THROW_IF_FAILED(hr);
                }
                else if (runMode == RM_PAUSED)
                {
                    // Do Nothing, wait
                }
                else    // invalid run mode
                {
                    THROW_ERROR(TS_Err_ProgramError, GetResourceString(enginePtr, ATLAS_STEP_TYPE_STRING, _T("INVALID_RUN_MODE_ERR")));
                }
            }
            // otherwise, the RTS Server is in an invalid state
            else
            {
                THROW_ERROR(TS_Err_AccessDenied, GetResourceString(enginePtr, ATLAS_STEP_TYPE_STRING, _T("RTS_INVALID_STATE_ERR")));
            }
            break;

        case ES_RUNNING:
            // if haven't started running the TPS
            if (rtsState == RTSAX::RTSAX_STATE_READY)
            {
                // Do Nothing, wait for the RTS Server to start running the TPS
                // assuming that the RTS Server will start running the TPS quickly, especially before
                // the execution is terminated/aborted or paused
            }
            // if still running the TPS
            else if (rtsState == RTSAX::RTSAX_STATE_RUNNING)
            {
                if (runMode == RM_NORMAL)
                {
                    // Do Nothing, continue running the TPS
                }
                // if we are terminating or paused, halt the execution of the TPS
                else if ((runMode == RM_TERMINATING) || (runMode == RM_PAUSED))
                {
                    // Halt the TPS execution
                    executionState = ES_HALTING;
                    hr = spTpsServerEx->Halt();
                    THROW_IF_FAILED(hr);
                }
                else    // invalid run mode
                {
                    THROW_ERROR(TS_Err_ProgramError, GetResourceString(enginePtr, ATLAS_STEP_TYPE_STRING, _T("INVALID_RUN_MODE_ERR")));
                }
            }
            // if done running the TPS
            else if (rtsState == RTSAX::RTSAX_STATE_FINISH)
            {
                // if the TS run mode is normal or terminating, start the unloading of the TPS
                if ((runMode == RM_NORMAL) || (runMode == RM_TERMINATING))
                {
                    // Read the parameters from the TPS Server and copy them to the Step
                    hr = ReadWriteParameters(parametersPropObj,spTpsServerEx,seqContextPropObj,false);
                    THROW_IF_FAILED(hr);

                    // Set the TestStand step status
                    hr = SetStepResultStatus(spTpsServerEx, enginePtr, seqContextPropObj, Normal);
                    THROW_IF_FAILED(hr);

                    // Unload TPS
                    executionState = ES_UNLOADING;
                    hr = spTpsServerEx->Unload();
                    THROW_IF_FAILED(hr);
                }
                else if (runMode == RM_PAUSED)
                {
                    // Do Nothing, wait to unload when the TestStand run mode is Normal or Terminating
                }
                else    // invalid run mode
                {
                    THROW_ERROR(TS_Err_ProgramError, GetResourceString(enginePtr, ATLAS_STEP_TYPE_STRING, _T("INVALID_RUN_MODE_ERR")));
                }
            }
            // if the RTS Server was in the HALTED state and then restarted running, 
            // but the RTS Server is still in the HALTED state
            else if (rtsState == RTSAX::RTSAX_STATE_HALTED)
            {
                // Do Nothing, wait for the RTS Server to transition out of the HALTED state
            }
            // otherwise, the RTS Server is in an invalid state
            else
            {
                THROW_ERROR(TS_Err_AccessDenied, GetResourceString(enginePtr, ATLAS_STEP_TYPE_STRING, _T("RTS_INVALID_STATE_ERR")));
            }
            break;

        case ES_HALTING:
            // if still running the TPS
            if (rtsState == RTSAX::RTSAX_STATE_RUNNING)
            {
                // Do Nothing, regardless of the TestStand run state, have to wait til the execution of 
                // the TPS is halted
                // assuming that the RTS Server will quickly halt running of the TPS, especially before
                // the execution is terminated/aborted or paused
            }
            // if were are halted or execution finised
            else if (rtsState == RTSAX::RTSAX_STATE_HALTED ||
                     rtsState == RTSAX::RTSAX_STATE_FINISH)
            {
                // transition to the halted state
                executionState = ES_HALTED;
            }
            // otherwise, the RTS Server is in an invalid state
            else
            {
                THROW_ERROR(TS_Err_AccessDenied, GetResourceString(enginePtr, ATLAS_STEP_TYPE_STRING, _T("RTS_INVALID_STATE_ERR")));
            }
            break;

        case ES_HALTED:
            if (rtsState == RTSAX::RTSAX_STATE_HALTED)
            {
                if (runMode == RM_NORMAL)
                {
                    // Resume running the TPS
                    executionState = ES_RUNNING;
                    hr = spTpsServerEx->Run();
                    THROW_IF_FAILED(hr);
                }
                else if (runMode == RM_TERMINATING)
                {
                    // Unload TPS
                    executionState = ES_UNLOADING;
                    hr = spTpsServerEx->Unload();
                    THROW_IF_FAILED(hr);
                }
                else if (runMode == RM_PAUSED)
                {
                    // Do Nothing, wait
                }
                else    // invalid run mode
                {
                    THROW_ERROR(TS_Err_ProgramError, GetResourceString(enginePtr, ATLAS_STEP_TYPE_STRING, _T("INVALID_RUN_MODE_ERR")));
                }
            }
            else if (runMode != RM_PAUSED)
            {
                // TestStand execution is no longer paused. Resume running the TPS. If the RTS 
                // server state has changed (TPS execution has been halted or resumed), TestStand 
                // will be appropriately updated in the state below.
                executionState = ES_RUNNING;            
            }
            break;

        case ES_UNLOADING:
            // if still unloading the TPS or haven't started the unload
            if ((rtsState == RTSAX::RTSAX_STATE_RUNNING) || 
                (rtsState == RTSAX::RTSAX_STATE_FINISH) || 
                (rtsState == RTSAX::RTSAX_STATE_READY) || 
                (rtsState == RTSAX::RTSAX_STATE_HALTED))
            {
                // Do Nothing, continue with Unload
            }
            // if done unloading the TPS
            else if (rtsState == RTSAX::RTSAX_STATE_UNLOADED)
            {
                // Regardless of run mode
                executionState = ES_UNLOADED;
            }
            // otherwise, the RTS Server is in an invalid state
            else
            {
                THROW_ERROR(TS_Err_AccessDenied, GetResourceString(enginePtr, ATLAS_STEP_TYPE_STRING, _T("RTS_INVALID_STATE_ERR")));
            }
            break;

        case ES_UNLOADED:
            // regardless of run mode, finish TPS execution
            Sleep(500);
            done = true;
            break;

        default:
            ATLASSERT(FALSE);
            break;
    }

    return done;
}

/* ======================================================================================================== **
    GetTPSServer
** -------------------------------------------------------------------------------------------------------- */
void CExecuteTPS::GetTPSServer (const TS::IEnginePtr &engine, RTSAX::ITpsServerExPtr& spTpsServerEx)
{
    const TS::PropertyObjectPtr engineGlobalsPropObj = engine->TemporaryGlobals;
    if (engineGlobalsPropObj != NULL)
        spTpsServerEx = engineGlobalsPropObj->GetValInterface(TPS_PROP, PropOption_InsertIfMissing);
    else
        spTpsServerEx = NULL;   // cannot load engine properties
}

/* ======================================================================================================== **
    HandleRTSError
** -------------------------------------------------------------------------------------------------------- */

void CExecuteTPS::HandleRTSError (const TS::IEnginePtr &engine)
{
    // Format the original error message.
    CString errMsg;
    errMsg.Format(GetResourceString(engine, ATLAS_STEP_TYPE_STRING, _T("RTS_ERROR_OCCURRED_ERR")), m_RTSErrorMsg);

    THROW_ERROR(TS_Err_OperationFailed, errMsg);
}

/* ======================================================================================================== **
    HandleTPSAlreadyLoaded
** -------------------------------------------------------------------------------------------------------- */

void CExecuteTPS::HandleTPSAlreadyLoaded (
        const TS::IEnginePtr &enginePtr, 
        ExecutionStates& executionState, 
        const TS::PropertyObjectPtr& seqContextPropObj,
        const RTSAX::ITpsServerExPtr& spTpsServerEx)
{
    // ask the user if we should unload the currently loaded TPS to continue 
    // executing this step or if we should skip execution of the requested TPS.
    int reply = ::MessageBox((HWND)enginePtr->AppMainHwnd, 
                            GetResourceString(enginePtr, ATLAS_STEP_TYPE_STRING, _T("UNLOAD_TPS_DLG_TEXT")),
                            GetResourceString(enginePtr, ATLAS_STEP_TYPE_STRING, _T("UNLOAD_TPS_DLG_TITLE")),
                            MB_YESNO | MB_ICONQUESTION);

    if (reply == IDYES)
    {
        // Unload TPS and continue normally
        executionState = ES_ATTACHED;
        HRESULT hr = spTpsServerEx->Unload();
        THROW_IF_FAILED(hr);
    }
    else
    {
        // Skip execution.
        executionState = ES_UNLOADED;

        // Set the TestStand step status as skipped
        HRESULT hr = SetStepResultStatus(spTpsServerEx, enginePtr, seqContextPropObj, Skipped);
        THROW_IF_FAILED(hr);
    }
}

/* ======================================================================================================== **
    WaitForManualIntervention
** -------------------------------------------------------------------------------------------------------- */

void CExecuteTPS::WaitForManualIntervention (
    const TS::IEnginePtr &engine, 
    const TS::ExecutionPtr& execution,
    const RTSAX::ITpsServerExPtr& spTpsServerEx)
{
    CManualInterventionDlg miDlg(engine);

    miDlg.Create(CManualInterventionDlg::IDD);
    miDlg.ShowWindow(SW_SHOW);

    // If the user hit the Continue button (and supposedly intervened in the TPS execution)
    // and manual intervention is still required
    if (miDlg.Display(execution, spTpsServerEx) && m_ManualInterventionRequired)
    {
        m_ManualInterventionRequired = false;

        const RTSAX::RtsAxState rtsState = m_RTSServerState.GetState();

        // if the RTS Server is in the correct state, reset the RTS Server MANUALINTERVENTION variable
        if ((rtsState == RTSAX::RTSAX_STATE_READY) || 
            (rtsState == RTSAX::RTSAX_STATE_FINISH) || 
            (rtsState == RTSAX::RTSAX_STATE_RUNNING) || 
            (rtsState == RTSAX::RTSAX_STATE_HALTED))
        {
            // signal the TPS Server to proceed
            HRESULT hr = spTpsServerEx->ManualIntervention();
            THROW_IF_FAILED(hr);
        }
    }
}

/* ======================================================================================================== **
    GetRunMode
** -------------------------------------------------------------------------------------------------------- */

bool CExecuteTPS::GetRunMode (const TS::ExecutionPtr& executionPtr, RunModes& runMode)
{
    bool done = false;

    // check TestStand Execution States
    ExecutionRunStates runState;
    ExecutionTerminationStates termState;
    executionPtr->GetStates(&runState,&termState);

    // if operating normally 
    if (runState == ExecRunState_Running)
    {
        runMode = RM_NORMAL;
    }
    // if in the process of aborting/terminating the execution
    else if (runState == ExecRunState_Paused)
    {
        runMode = RM_PAUSED;
    }
    // otherwise, if the execution is stopped
    else if (runState == ExecRunState_Stopped)  // this should NOT happen!
    {
        ATLASSERT(FALSE);
        runMode = RM_TERMINATING;
    }
    else
    {
        ATLASSERT(FALSE);
        runMode = RM_NORMAL;
    }

    // if normally operating
    if (termState == ExecTermState_Normal)
    {
        // Do Nothing
    }
    // if in the process of aborting/terminating the execution
    else if ((termState == ExecTermState_Aborting) || 
             (termState == ExecTermState_Terminating) || 
             (termState == ExecTermState_TerminatingInteractive))
    {
        // if not alreading trying to terminate, start termination process
        runMode = RM_TERMINATING;
    }
    // if in the process of killing threads
    else if (termState == ExecTermState_KillingThreads)
        // immediately terminate the execution of the step, which will destroy the TPS & RTS Servers
        // this is potentially dangerous and probably should be avoided
    {
        runMode = RM_TERMINATING;
        done = true;
    }
    else
        ATLASSERT(FALSE);

    return done;
}

/* ======================================================================================================== **
    ExecuteTPS
** -------------------------------------------------------------------------------------------------------- */

STDMETHODIMP CExecuteTPS::ExecuteTPS (TS::SequenceContext *sequenceContext)
{
    TS::SequenceContextPtr seqContext = sequenceContext;

    PRE_API_FUNC_CODE
    HRESULT hr = 0;

    const TS::IEnginePtr enginePtr = seqContext->GetEngine();
    const TS::ThreadPtr threadPtr = seqContext->GetThread();
    const TS::ExecutionPtr executionPtr = seqContext->Execution;
    const TS::PropertyObjectPtr seqContextPropObj = seqContext->AsPropertyObject();
    const TS::PropertyObjectPtr stepPropObj = seqContext->GetStep()->AsPropertyObject();
    const TS::PropertyObjectPtr sDataPropObj = stepPropObj->GetPropertyObject(SDATA_PROP, 0);
    const TS::PropertyObjectPtr tpsFilePathPropObj = sDataPropObj->GetPropertyObject(TPSFILEPATH_PROP, 0);
    const TS::PropertyObjectPtr executeRemotelyPropObj = sDataPropObj->GetPropertyObject(EXECUTE_REMOTELY_PROP, 0);
    TS::PropertyObjectPtr parametersPropObj = sDataPropObj->GetPropertyObject(PARAMETERS_PROP, 
        PropOption_NoOptions);

    // Check if a TPS file was specified
    CComBSTR relativeTPSPath = (const wchar_t*) tpsFilePathPropObj->GetValString(L"", 0);
    if ((relativeTPSPath.m_str == NULL) || (relativeTPSPath == L""))
        RAISE_ERROR(TS_Err_ModuleNotSpecified);

    // Locate TPS file for execution
    VARIANT_BOOL cancelled, fileFound;
    fileFound = enginePtr->FindFile((const wchar_t*)relativeTPSPath, &m_TPSFilePath, &cancelled, 
                                        FindFile_PromptHonorUserPreference, 
                                        FindFile_AddDirToSrchList_No, 
                                        VARIANT_FALSE, vtMissing);

    // If the file was not found, throw an error
    if (fileFound == VARIANT_FALSE)
        RAISE_ERROR(TS_Err_FileWasNotFound);

    // Check for remote execution
    bool executeRemotely = (executeRemotelyPropObj->GetValBoolean(L"", 0) == VARIANT_TRUE);

    // If it was set to execute remotely, but the host name expression was not specified, assume to run locally
    CComBSTR remoteHostName;
    if (executeRemotely)
    {
        const TS::PropertyObjectPtr remoteHostNameExprPropObj = sDataPropObj->GetPropertyObject(REMOTE_HOST_NAME_EXPR_PROP, 0);
        const CComBSTR remoteHostNameExpr = (const wchar_t*) remoteHostNameExprPropObj->GetValString(L"", 0);
        const TS::PropertyObjectPtr remoteHostNamePropObj = seqContextPropObj->EvaluateEx((const wchar_t*)remoteHostNameExpr.m_str, EvalOption_AllowEmptyExpression);
        if (remoteHostNamePropObj == NULL)
            executeRemotely = false;
        else
            remoteHostName = (const wchar_t*) remoteHostNamePropObj->GetValString(L"", 0);
    }

    // Set the internal run mode to normal
    RunModes runMode = RM_NORMAL;

    // Initialize execution state
    ExecutionStates executionState = ES_ATTACHING;

    // Get the TPS Server
    RTSAX::ITpsServerExPtr spTpsServerEx;
    GetTPSServer(enginePtr, spTpsServerEx);

    // If the TPS Server does not already exist, then create it and attach to RTS 
    if (spTpsServerEx == NULL)
    {
        // Set RTS Server State to initial state
        m_RTSServerState = RTSAX::RTSAX_STATE_DETACHED;

        // Create the TPS Server. 
        hr = spTpsServerEx.CreateInstance(RTSAX::CLSID_TpsServer);
        
        // If the TPS Server does not exist, give a more informative error than the default one
        if (hr == REGDB_E_CLASSNOTREG || hr == REGDB_E_IIDNOTREG)
            THROW_ERROR(hr, GetResourceString(enginePtr, ATLAS_STEP_TYPE_STRING, _T("PAWS_NOT_FOUND_ERR")));
        else 
            THROW_IF_FAILED(hr);

        // Store TPS Server as a TestStand Engine global property. The TPS Server will be released by the TestStand Engine 
        //  when the engine is closed.
        enginePtr->TemporaryGlobals->SetValInterface(TPS_PROP, PropOption_InsertIfMissing, spTpsServerEx);
		enginePtr->TemporaryGlobals->SetValInterface("TestStandOutOfProcess_PAWSTPSServer", PropOption_InsertIfMissing, (IDispatch *)this);

		// Put TPS Server in asynchronous mode
        hr = spTpsServerEx->put_Synchronous(VARIANT_FALSE);
        THROW_IF_FAILED(hr);

        // Setup up Event Sink Advise
        hr = DispEventAdvise(spTpsServerEx);
        THROW_IF_FAILED(hr);

        // Attach the TPS Server to the RTS Server
        hr = executeRemotely ? spTpsServerEx->Attach(_variant_t(remoteHostName.m_str)) : spTpsServerEx->Attach();
        THROW_IF_FAILED(hr);
    }
    else
    {
        // Set RTS Server State to current state from TPS server
        long state = 0;
        spTpsServerEx->get_State(&state);
        m_RTSServerState.SetState((RTSAX::RtsAxState)state);

        // Setup up Event Sink Advise
        hr = DispEventAdvise(spTpsServerEx);
        THROW_IF_FAILED(hr);
    }

    // Set the flag that indicates that this thread can be suspended (will reset in destructor)
    CExternalSuspender externalSuspender(threadPtr);

    // Loop until done
    for(;;)
    {
        if (!m_RTSErrorMsg.IsEmpty())
            HandleRTSError(enginePtr); 

        // If manual intervention is required, begin the Manual Intervention dialog
        if (m_ManualInterventionRequired)
            WaitForManualIntervention(enginePtr,executionPtr,spTpsServerEx);

        // Get the run mode (possilbly post MI dialog), break if necessary (i.e., killing threads)
        if (GetRunMode(executionPtr,runMode))
            break;

        // Run TPS Execution State Machine, if done break out of loop
        if (IterateExecutionStateMachine(runMode,executionState,enginePtr,parametersPropObj,seqContextPropObj,spTpsServerEx))
            break;
    }

    // Unadvise from Event Sink
    hr = DispEventUnadvise(spTpsServerEx);
    THROW_IF_FAILED(hr);

    POST_API_FUNC_CODE(seqContext)
}

/* ======================================================================================================== **
    OnRtsState
** -------------------------------------------------------------------------------------------------------- */

void __stdcall CExecuteTPS::OnRtsState(long lState)
{
    m_RTSServerState = (RTSAX::RtsAxState) lState;
}

/* ======================================================================================================== **
    OnRtsTps
** -------------------------------------------------------------------------------------------------------- */

void __stdcall CExecuteTPS::OnRtsTps(BSTR pTps)
{
}

/* ======================================================================================================== **
    OnRtsMiEnable
** -------------------------------------------------------------------------------------------------------- */

void __stdcall CExecuteTPS::OnRtsMiEnable(VARIANT_BOOL varBool)
{
    // Only check for manual intervention if we have a TPS loaded
    const RTSAX::RtsAxState rtsState = m_RTSServerState.GetState();
    if (rtsState != RTSAX::RTSAX_STATE_DETACHED && rtsState != RTSAX::RTSAX_STATE_UNLOADED) 
        m_ManualInterventionRequired = (varBool != VARIANT_FALSE);
}

/* ======================================================================================================== **
    OnRtsOutput
** -------------------------------------------------------------------------------------------------------- */

void __stdcall CExecuteTPS::OnRtsOutput(BSTR pMsg)
{
}

/* ======================================================================================================== **
    OnRtsDisplay
** -------------------------------------------------------------------------------------------------------- */

void __stdcall CExecuteTPS::OnRtsDisplay(BSTR pMsg)
{
}

/* ======================================================================================================== **
    OnRtsInfo
** -------------------------------------------------------------------------------------------------------- */

void __stdcall CExecuteTPS::OnRtsInfo(BSTR pMsg)
{
}

/* ======================================================================================================== **
    OnRtsWarning
** -------------------------------------------------------------------------------------------------------- */

void __stdcall CExecuteTPS::OnRtsWarning(BSTR pMsg)
{
}

/* ======================================================================================================== **
    OnRtsError
** -------------------------------------------------------------------------------------------------------- */

void __stdcall CExecuteTPS::OnRtsError(BSTR pMsg)
{
    m_RTSErrorMsg = pMsg;
}
