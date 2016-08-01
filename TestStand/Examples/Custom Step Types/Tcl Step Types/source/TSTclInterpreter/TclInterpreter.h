// TclInterpreter.h : Declaration of the CTclInterpreter

#pragma once
#include "resource.h"       // main symbols
#include "C:\Tcl\include\tcl.h" // To compile this project you need to install ActiveState ActiveTcl and update the path on this line to use the path to the installation directory. See Readme.doc
#include "TSTclInterpreter.h"
#include <vector>

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

typedef void (__cdecl *FINDEXECUTABLE_PROC)(const char *); 
typedef const char *  (__cdecl *GETVERSIONPROC)(int * major, int * minor, int * patchLevel, int *type);
typedef Tcl_Interp * (__cdecl *CREATEINTERP_PROC)(); 
typedef Tcl_DriverOutputProc * (__cdecl *GETCHANNELOUTPUT_PROC)(Tcl_ChannelType * chanType); 

typedef Tcl_Channel (__cdecl *GETSTDCHANNELPROC)(int type); 
typedef Tcl_ChannelType * (__cdecl *GETCHANNELTYPEPROC)(Tcl_Channel chan); 
typedef int (__cdecl *EVALPROC)(Tcl_Interp * interp, const char * string); 	
typedef Tcl_Obj * (__cdecl *GETOBJRESULTPROC)(Tcl_Interp * interp);	
typedef int (__cdecl *EXPRBOOLEANPROC)(Tcl_Interp * interp, const char * str, int * ptr);
typedef int  (__cdecl *EVALFILEPROC)(Tcl_Interp * interp, const char * fileName);	
typedef int (__cdecl *INITPROC)(Tcl_Interp * interp);
typedef const char * (__cdecl *SETVARPROC)(Tcl_Interp * interp, const char * varName, const char * newValue, int flags);
typedef const char *  (__cdecl *GETVARPROC)(Tcl_Interp * interp, const char * varName, int flags);

typedef Tcl_Channel (__cdecl *CREATECHANNELPROC)(const Tcl_ChannelType *typePtr, const char *chanName, ClientData instanceData, int mask);
typedef void  (__cdecl *SETSTDCHANNELPROC)(Tcl_Channel channel, int type);
typedef void  (__cdecl *REGISTERCHANNELPROC)(Tcl_Interp *interp,Tcl_Channel chan);
typedef int  (__cdecl *ISCHANNELREGISTEREDPROC)(Tcl_Interp *interp,Tcl_Channel chan);

typedef int  (__cdecl *UNREGISTERCHANNELPROC)(Tcl_Interp *interp,Tcl_Channel chan);
typedef Tcl_Channel  (__cdecl *STACKCHANNELPROC)(Tcl_Interp *interp, const Tcl_ChannelType *typePtr,ClientData instanceData, int mask,Tcl_Channel prevChan);
typedef void  (__cdecl *CREATECHANNELHANDLERPROC)(Tcl_Channel chan, int mask,Tcl_ChannelProc *proc, ClientData clientData);
typedef ClientData  (__cdecl *GETCHANNELINSTANCEDATAPROC)(Tcl_Channel chan);
typedef int  (__cdecl *ISCHANNELEXISTINGPROC)(const char *channelName);



class TclWrapper
{
public:
	
	static bool IsInitialized();
	//~TclWrapper();

	static void LoadTcl(SequenceContextPtr context, char dllVersion[]);
	static bool UseUnicode();

	static void FindExecutable(const char * argv0);
	static Tcl_Interp * CreateInterp();
	static Tcl_DriverOutputProc * ChannelOutput(Tcl_ChannelType * chanType);

	static Tcl_Channel GetStdChannel(int type);
	static Tcl_ChannelType * GetChannelType(Tcl_Channel chan);
	static int Eval(Tcl_Interp * interp, const char * string);
	static Tcl_Obj * GetObjResult(Tcl_Interp * interp);
	static int ExprBoolean(Tcl_Interp * interp, const char * str, int * ptr);
	static int EvalFile(Tcl_Interp * interp, const char * fileName);
	static int Init(Tcl_Interp * interp);
	static const char * SetVar(Tcl_Interp * interp, const char * varName, const char * newValue, int flags);
	static const char * GetVar(Tcl_Interp * interp, const char * varName, int flags);
	static void GetVersion(int * major, int * minor, int * patchLevel, int *type);
	
	static void SetStdChannel(Tcl_Channel channel, int type);
	static Tcl_Channel CreateChannel(const Tcl_ChannelType *typePtr, const char *chanName, ClientData instanceData, int mask);
	static void RegisterChannel(Tcl_Interp *interp,Tcl_Channel chan);
	static int UnregisterChannel(Tcl_Interp *interp,Tcl_Channel chan);
	static int IsChannelRegistered(Tcl_Interp *interp,Tcl_Channel chan);

	static Tcl_Channel StackChannel(Tcl_Interp *interp, const Tcl_ChannelType *typePtr,ClientData instanceData, int mask,Tcl_Channel prevChan);
	static void CreateChannelHandler(Tcl_Channel chan, int mask,Tcl_ChannelProc *proc, ClientData clientData);
	static ClientData GetChannelInstanceData(Tcl_Channel chan);
	static int IsChannelExisting(const char *channelName);

	

private:

	static HMODULE sModule;
	static bool sIsInitialized;
	static bool sUseUnicode;


	static FINDEXECUTABLE_PROC FindExecutableProc;
	static CREATEINTERP_PROC CreateInterpProc;
	static GETCHANNELOUTPUT_PROC ChannelOutputProc;

	static GETSTDCHANNELPROC GetStdChannelProc;
	static GETCHANNELTYPEPROC GetChannelTypeProc;
	static EVALPROC EvalProc;
	static GETOBJRESULTPROC GetObjResultProc;
	static EXPRBOOLEANPROC ExprBooleanProc;
	static EVALFILEPROC EvalFileProc;
	static INITPROC InitProc;
	static SETVARPROC SetVarProc;
	static GETVARPROC GetVarProc;
	static GETVERSIONPROC GetVersionProc;

	static CREATECHANNELPROC CreateChannelProc;
	static SETSTDCHANNELPROC SetStdChannelProc;
	static REGISTERCHANNELPROC RegisterChannelProc;
	static UNREGISTERCHANNELPROC UnregisterChannelProc;
	static ISCHANNELREGISTEREDPROC IsChannelRegisteredProc;

	static STACKCHANNELPROC StackChannelProc;
	static CREATECHANNELHANDLERPROC CreateChannelHandlerProc;
	static GETCHANNELINSTANCEDATAPROC GetChannelInstanceDataProc;
	static ISCHANNELEXISTINGPROC IsChannelExistingProc;



};
bool TclWrapper::sIsInitialized = false;
bool TclWrapper::sUseUnicode = false;
GETVERSIONPROC TclWrapper::GetVersionProc = NULL;
FINDEXECUTABLE_PROC TclWrapper::FindExecutableProc= NULL;
CREATEINTERP_PROC TclWrapper::CreateInterpProc= NULL;
GETCHANNELOUTPUT_PROC TclWrapper::ChannelOutputProc=NULL;
GETSTDCHANNELPROC TclWrapper::GetStdChannelProc= NULL;
GETCHANNELTYPEPROC TclWrapper::GetChannelTypeProc= NULL;
EVALPROC TclWrapper::EvalProc= NULL;
GETOBJRESULTPROC TclWrapper::GetObjResultProc= NULL;
EXPRBOOLEANPROC TclWrapper::ExprBooleanProc= NULL;
EVALFILEPROC TclWrapper::EvalFileProc= NULL;
INITPROC TclWrapper::InitProc= NULL;
SETVARPROC TclWrapper::SetVarProc= NULL;
GETVARPROC TclWrapper::GetVarProc= NULL;
HMODULE TclWrapper::sModule = NULL;

CREATECHANNELPROC TclWrapper::CreateChannelProc = NULL;
SETSTDCHANNELPROC TclWrapper::SetStdChannelProc = NULL;
REGISTERCHANNELPROC TclWrapper::RegisterChannelProc = NULL;
UNREGISTERCHANNELPROC TclWrapper::UnregisterChannelProc = NULL;
ISCHANNELREGISTEREDPROC TclWrapper::IsChannelRegisteredProc = NULL;

STACKCHANNELPROC TclWrapper::StackChannelProc = NULL;
CREATECHANNELHANDLERPROC TclWrapper::CreateChannelHandlerProc = NULL;
GETCHANNELINSTANCEDATAPROC TclWrapper::GetChannelInstanceDataProc = NULL;
ISCHANNELEXISTINGPROC TclWrapper::IsChannelExistingProc = NULL;


// CTclInterpreter

class ATL_NO_VTABLE CTclInterpreter :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTclInterpreter, &CLSID_TclInterpreter>,
	public ISupportErrorInfo,
	public IDispatchImpl<ITclInterpreter, &IID_ITclInterpreter, &LIBID_TSTclInterpreterLib>
{
public:
	CTclInterpreter();
	~CTclInterpreter();


DECLARE_REGISTRY_RESOURCEID(IDR_TCLINTERPRETER)


BEGIN_COM_MAP(CTclInterpreter)
	COM_INTERFACE_ENTRY(ITclInterpreter)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{	
	}

	void RedirectStreams(SequenceContextPtr context);
	void ResetStreams();

private:
	Tcl_Interp * m_interp;
	void SetParameters(SequenceContextPtr context);
	void GetParameters(SequenceContextPtr context);
	void ReportError(_bstr_t errorDescription);
	void InitInterpreter(SequenceContextPtr context);

public:
	STDMETHOD(ExecuteStep)(IDispatch * context);
	//_bstr_t m_output;
	BYTE *m_outputBytes;
	size_t m_outputNumBytes;

	BYTE *m_inputBytes;
	size_t m_inputNumBytes;
public:
	STDMETHOD(get_ProcessID)(DWORD* pVal);
};

OBJECT_ENTRY_AUTO(__uuidof(TclInterpreter), CTclInterpreter)

int OutputProc(ClientData instanceData, const char * buf, int toWrite, int * errorCodePtr);
int InputProc(ClientData instanceData, char *buf, int bufSize, int *errorCodePtr);

