    
// ExecuteTPS.h : Declaration of the CExecuteTPS

#ifndef __EXECUTETPS_H_
#define __EXECUTETPS_H_

#include "resource.h"       // main symbols
#include "Utils.h"

/////////////////////////////////////////////////////////////////////////////
// CRTSServerState: Wrapper for RTS ActiveX Server State.
class CRTSServerState
{
public:
    CRTSServerState() : 
        m_RTSServerState(RTSAX::RTSAX_STATE_DETACHED)
    {}

    void SetState(RTSAX::RtsAxState rtsState)
    {
        m_CritSect.Lock();
        m_RTSServerState = rtsState;
        m_CritSect.Unlock();
    }
    RTSAX::RtsAxState GetState()
    {
        m_CritSect.Lock();
        // Capture current value of the RTS Server State
        RTSAX::RtsAxState rtsState = m_RTSServerState;
        m_CritSect.Unlock();
        return rtsState;
    }

    void operator=(RTSAX::RtsAxState  rtsState) { SetState(rtsState); }
private:
    RTSAX::RtsAxState m_RTSServerState;
    CCriticalSection m_CritSect;
};

/////////////////////////////////////////////////////////////////////////////
// CExecuteTPS
class ATL_NO_VTABLE CExecuteTPS : 
    public CComObjectRootEx<CComMultiThreadModel>,
    public CComCoClass<CExecuteTPS, &CLSID_ExecuteTPS>,
    public ISupportErrorInfo,
    public IDispatchImpl<IExecuteTPS, &IID_IExecuteTPS, &LIBID_ATLAS_STEPTYPELib>, 
    public IDispEventImpl<1, CExecuteTPS, &RTSAX::DIID__IRtsBaseEvents, &RTSAX::LIBID_RTSAX, 1, 0>
{
public:
    CExecuteTPS() : 
        m_ManualInterventionRequired(false)
    {
    }

DECLARE_REGISTRY_RESOURCEID(IDR_EXECUTETPS)
DECLARE_GET_CONTROLLING_UNKNOWN()
BEGIN_SINK_MAP(CExecuteTPS)
    SINK_ENTRY_EX(1, RTSAX::DIID__IRtsBaseEvents, 0x1, OnRtsTps)
    SINK_ENTRY_EX(1, RTSAX::DIID__IRtsBaseEvents, 0x5, OnRtsState)
    SINK_ENTRY_EX(1, RTSAX::DIID__IRtsBaseEvents, 0x9, OnRtsMiEnable)
    SINK_ENTRY_EX(1, RTSAX::DIID__IRtsBaseEvents, 0xa, OnRtsOutput)
    SINK_ENTRY_EX(1, RTSAX::DIID__IRtsBaseEvents, 0xb, OnRtsDisplay)
    SINK_ENTRY_EX(1, RTSAX::DIID__IRtsBaseEvents, 0xc, OnRtsInfo)
    SINK_ENTRY_EX(1, RTSAX::DIID__IRtsBaseEvents, 0xd, OnRtsWarning)
    SINK_ENTRY_EX(1, RTSAX::DIID__IRtsBaseEvents, 0xe, OnRtsError)
END_SINK_MAP()

BEGIN_COM_MAP(CExecuteTPS)
    COM_INTERFACE_ENTRY(IExecuteTPS)
    COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
    STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IRtsBaseEvents Sink
    void __stdcall OnRtsState(long lState);
    void __stdcall OnRtsTps(BSTR pTps);
    void __stdcall OnRtsMiEnable(VARIANT_BOOL varBool);
    void __stdcall OnRtsOutput(BSTR pMsg);
    void __stdcall OnRtsDisplay(BSTR pMsg);
    void __stdcall OnRtsInfo(BSTR pMsg);
    void __stdcall OnRtsWarning(BSTR pMsg);
    void __stdcall OnRtsError(BSTR pMsg);

// IExecuteTPS
public:
    STDMETHOD(EditStep)(/*[in]*/ TS::SequenceContext *sequenceContext, /*[in]*/ long reserved, /*[out]*/ long *changeCount);
    STDMETHOD(ExecuteTPS)(/*[in]*/ TS::SequenceContext *sequenceContext);

private:
    // Type definitions
    // TPS Execution States
    typedef enum
    {
        ES_ATTACHING    = 0, 
        ES_ATTACHED     = 1,    // idle state when Paused during Attach
        ES_LOADING      = 2, 
        ES_LOADED       = 3,    // idle state when Paused during Load
        ES_RUNNING      = 4, 
        ES_HALTING      = 5, 
        ES_HALTED       = 6,    // idle state when Paused during Run
        ES_UNLOADING    = 7, 
        ES_UNLOADED     = 8
    } ExecutionStates;

    // TestStand Execution States
    typedef enum
    {
        RM_NORMAL       = 0, 
        RM_PAUSED       = 1,    // TestStand is Paused
        RM_TERMINATING  = 2     // TestStand is Aborting or Terminating
    } RunModes;

    // Attributes
    CString  m_RTSErrorMsg;
    CComBSTR m_TPSFilePath;
    CRTSServerState m_RTSServerState;
    bool m_ManualInterventionRequired;

    // Operations
    bool GetRunMode (const TS::ExecutionPtr& executionPtr, RunModes& runMode);
    void GetTPSServer (const TS::IEnginePtr &engine, RTSAX::ITpsServerExPtr& spTpsServerEx);
    void HandleRTSError (const TS::IEnginePtr &engine);
    void HandleTPSAlreadyLoaded (const TS::IEnginePtr &engine, ExecutionStates& executionState, 
        const TS::PropertyObjectPtr& seqContextPropObj,
        const RTSAX::ITpsServerExPtr& spTpsServerEx);
    void WaitForManualIntervention (const TS::IEnginePtr &engine, 
        const TS::ExecutionPtr& executionPtr,
        const RTSAX::ITpsServerExPtr& spTpsServerEx);
    bool IterateExecutionStateMachine (const RunModes& runMode, ExecutionStates& executionState, 
        const TS::IEnginePtr& enginePtr, PropertyObjectPtr& parametersPropObj, 
        const TS::PropertyObjectPtr& seqContextPropObj,
        const RTSAX::ITpsServerExPtr& spTpsServerEx);
};

#endif //__EXECUTETPS_H_
