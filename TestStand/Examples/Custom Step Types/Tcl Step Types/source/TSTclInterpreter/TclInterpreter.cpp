// TclInterpreter.cpp : Implementation of CTclInterpreter

#include "stdafx.h"
#include "TclInterpreter.h"
#include "..\Shared\TclStepProperties.h"
#include "tsvcutil.h"
#include "..\Shared\TclError.h"
#include "windows.h"
#include <assert.h>
#include <atlstr.h>

//create global variable to object so we can access properties 
CTclInterpreter * interp = NULL;
Tcl_DriverOutputProc * outputProc = NULL;

void TclWrapper::LoadTcl(SequenceContextPtr context, char dllVersion[])
{
	_bstr_t moduleNotFound = context->Engine->GetResourceString(TCL_STEP_TYPE_SECTION, "ERROR_MODULE_NOT_FOUND", vtMissing , &vtMissing );
	_bstr_t procNotFound = context->Engine->GetResourceString(TCL_STEP_TYPE_SECTION, "ERROR_PROC_NOT_FOUND", vtMissing , &vtMissing );

	if ((sModule = LoadLibraryEx(dllVersion, NULL, LOAD_WITH_ALTERED_SEARCH_PATH))==NULL)
		throw TclError(ERROR_TCL_NOT_INSTALLED, moduleNotFound);

	if ((FindExecutableProc = (FINDEXECUTABLE_PROC) GetProcAddress(sModule, "Tcl_FindExecutable"))==NULL)
		throw TclError(ERROR_TCL_NOT_INSTALLED, procNotFound);

	if ((CreateInterpProc = (CREATEINTERP_PROC) GetProcAddress(sModule, "Tcl_CreateInterp"))==NULL)
		throw TclError(ERROR_TCL_NOT_INSTALLED, procNotFound);

	if ((GetStdChannelProc = (GETSTDCHANNELPROC) GetProcAddress(sModule, "Tcl_GetStdChannel"))==NULL)
		throw TclError(ERROR_TCL_NOT_INSTALLED, procNotFound);

	if ((GetChannelTypeProc = (GETCHANNELTYPEPROC) GetProcAddress(sModule, "Tcl_GetChannelType")) == NULL)
		throw TclError(ERROR_TCL_NOT_INSTALLED, procNotFound);

	if ((EvalProc = (EVALPROC) GetProcAddress(sModule, "Tcl_Eval")) == NULL)
		throw TclError(ERROR_TCL_NOT_INSTALLED, procNotFound);		

	if ((GetObjResultProc = (GETOBJRESULTPROC) GetProcAddress(sModule, "Tcl_GetObjResult")) == NULL)
		throw TclError(ERROR_TCL_NOT_INSTALLED, procNotFound);	

	if ((ExprBooleanProc = (EXPRBOOLEANPROC) GetProcAddress(sModule, "Tcl_ExprBoolean")) == NULL)
		throw TclError(ERROR_TCL_NOT_INSTALLED, procNotFound);	

	if ((EvalFileProc = (EVALFILEPROC) GetProcAddress(sModule, "Tcl_EvalFile")) == NULL)
		throw TclError(ERROR_TCL_NOT_INSTALLED, procNotFound);	
	
	if ((InitProc = (INITPROC) GetProcAddress(sModule, "Tcl_Init")) == NULL)
		throw TclError(ERROR_TCL_NOT_INSTALLED, procNotFound);	
	
	if ((SetVarProc = (SETVARPROC) GetProcAddress(sModule, "Tcl_SetVar")) == NULL)
		throw TclError(ERROR_TCL_NOT_INSTALLED, procNotFound);	

	if ((GetVarProc = (GETVARPROC) GetProcAddress(sModule, "Tcl_GetVar")) == NULL)
		throw TclError(ERROR_TCL_NOT_INSTALLED, procNotFound);	

	if ((GetVersionProc = (GETVERSIONPROC) GetProcAddress(sModule, "Tcl_GetVersion")) == NULL)
		throw TclError(ERROR_TCL_NOT_INSTALLED, procNotFound);	

	if ((ChannelOutputProc = (GETCHANNELOUTPUT_PROC) GetProcAddress(sModule, "Tcl_ChannelOutputProc"))==NULL)
		throw TclError(ERROR_TCL_NOT_INSTALLED, procNotFound);
	
	if ((CreateChannelProc = (CREATECHANNELPROC) GetProcAddress(sModule, "Tcl_CreateChannel"))==NULL)
		throw TclError(ERROR_TCL_NOT_INSTALLED, procNotFound);
	
	if ((SetStdChannelProc = (SETSTDCHANNELPROC) GetProcAddress(sModule, "Tcl_SetStdChannel"))==NULL)
		throw TclError(ERROR_TCL_NOT_INSTALLED, procNotFound);
	
	if ((RegisterChannelProc = (REGISTERCHANNELPROC) GetProcAddress(sModule, "Tcl_RegisterChannel"))==NULL)
		throw TclError(ERROR_TCL_NOT_INSTALLED, procNotFound);
	
	if ((UnregisterChannelProc = (UNREGISTERCHANNELPROC) GetProcAddress(sModule, "Tcl_UnregisterChannel"))==NULL)
		throw TclError(ERROR_TCL_NOT_INSTALLED, procNotFound);

	if ((IsChannelRegisteredProc = (ISCHANNELREGISTEREDPROC) GetProcAddress(sModule, "Tcl_IsChannelRegistered"))==NULL)
		throw TclError(ERROR_TCL_NOT_INSTALLED, procNotFound);

	if ((StackChannelProc = (STACKCHANNELPROC) GetProcAddress(sModule, "Tcl_StackChannel"))==NULL)
		throw TclError(ERROR_TCL_NOT_INSTALLED, procNotFound);
	
	if ((CreateChannelHandlerProc = (CREATECHANNELHANDLERPROC) GetProcAddress(sModule, "Tcl_CreateChannelHandler"))==NULL)
		throw TclError(ERROR_TCL_NOT_INSTALLED, procNotFound);

	if ((GetChannelInstanceDataProc = (GETCHANNELINSTANCEDATAPROC) GetProcAddress(sModule, "Tcl_GetChannelInstanceData"))==NULL)
		throw TclError(ERROR_TCL_NOT_INSTALLED, procNotFound);

	if ((IsChannelExistingProc = (ISCHANNELEXISTINGPROC) GetProcAddress(sModule, "Tcl_IsChannelExisting"))==NULL)
		throw TclError(ERROR_TCL_NOT_INSTALLED, procNotFound);
	


	int major, minor, patchLevel, type;

	(GetVersionProc)(&major, &minor, &patchLevel, &type);
	
	TclWrapper::sUseUnicode = (major>8) || (major ==8 && minor >=5);
	TclWrapper::sIsInitialized = true;
}


void TclWrapper::FindExecutable(const char *argv0)
{
	(FindExecutableProc)(argv0);
}

Tcl_Interp * TclWrapper::CreateInterp()
{
	return (CreateInterpProc)();
}


Tcl_DriverOutputProc * TclWrapper::ChannelOutput(Tcl_ChannelType * chanType)
{
	return (ChannelOutputProc)(chanType);
}

Tcl_Channel TclWrapper::GetStdChannel(int type)
{
	return (GetStdChannelProc)(type);
}

Tcl_ChannelType * TclWrapper::GetChannelType(Tcl_Channel chan)
{
	return (GetChannelTypeProc)(chan);
}

int TclWrapper::Eval(Tcl_Interp *interp, const char *string)
{
	return (EvalProc)(interp, string);
}

Tcl_Obj * TclWrapper::GetObjResult(Tcl_Interp *interp)
{
	return (GetObjResultProc)(interp);
}

int TclWrapper::ExprBoolean(Tcl_Interp * interp, const char * str, int * ptr)
{
	return (ExprBooleanProc)(interp, str, ptr);
}
int TclWrapper::EvalFile(Tcl_Interp *interp, const char *fileName)
{
	return (EvalFileProc)(interp, fileName);
}

int TclWrapper::Init(Tcl_Interp *interp)
{
	return (InitProc)(interp);
}

const char  * TclWrapper::SetVar(Tcl_Interp *interp, const char *varName, const char *newValue, int flags)
{
	return (SetVarProc)(interp, varName, newValue, flags);
}

const char  * TclWrapper::GetVar(Tcl_Interp *interp, const char *varName, int flags)
{
	return (GetVarProc)(interp, varName, flags);
}

void TclWrapper::GetVersion(int * major, int *  minor, int * patchLevel, int *type)
{
	(GetVersionProc)(major, minor, patchLevel, type);
}
bool TclWrapper::UseUnicode()
{
	return sUseUnicode;
}

bool TclWrapper::IsInitialized()
{
	return sIsInitialized;
}

void TclWrapper::SetStdChannel(Tcl_Channel channel, int type)
{
	(SetStdChannelProc)(channel, type);
}

Tcl_Channel TclWrapper::CreateChannel(const Tcl_ChannelType *typePtr, const char *chanName, ClientData instanceData, int mask)
{
	return (CreateChannelProc)(typePtr, chanName, instanceData, mask);
}

void TclWrapper::RegisterChannel(Tcl_Interp *interp,Tcl_Channel chan)
{
	return (RegisterChannelProc)(interp, chan);
}

int TclWrapper::UnregisterChannel(Tcl_Interp *interp,Tcl_Channel chan)
{
	return (UnregisterChannelProc)(interp, chan);
}

int TclWrapper::IsChannelRegistered(Tcl_Interp *interp,Tcl_Channel chan)
{
	return (IsChannelRegisteredProc)(interp, chan);
}


Tcl_Channel TclWrapper::StackChannel(Tcl_Interp *interp, const Tcl_ChannelType *typePtr,ClientData instanceData, int mask,Tcl_Channel prevChan)
{
	return (StackChannelProc)(interp, typePtr, instanceData, mask, prevChan);
}

void TclWrapper::CreateChannelHandler(Tcl_Channel chan, int mask,Tcl_ChannelProc *proc, ClientData clientData)
{
	return (CreateChannelHandlerProc)(chan, mask, proc, clientData);
}

ClientData TclWrapper::GetChannelInstanceData(Tcl_Channel chan)
{
	return (GetChannelInstanceDataProc)(chan);
}
int TclWrapper::IsChannelExisting(const char *channelName)
{
	return (IsChannelExistingProc)(channelName);
}


class RedirectStreamsController
{
public:
	
	RedirectStreamsController(SequenceContextPtr context, Tcl_Interp * m_interp) :
	  outputRedirected(false), inputRedirected(false), mInterp(NULL), mDefaultOutputChannel(NULL), mDefaultInputChannel(NULL), mOutputProc(NULL), mInputProc(NULL)//	mInterpreter(interpreter)
	{
		PropertyObjectPtr step = context->Step;

		//get channel type for standard channels
		Tcl_Channel standardOutputChan = TclWrapper::GetStdChannel(TCL_STDOUT);
		Tcl_Channel standardInputChan = TclWrapper::GetStdChannel(TCL_STDIN);

		Tcl_ChannelType * chanTypeOutput = TclWrapper::GetChannelType(standardOutputChan);
		Tcl_ChannelType * chanTypeInput = TclWrapper::GetChannelType(standardInputChan);
		mInterp = m_interp;

		//save old procedures value so it can be reset when we are done
		mDefaultOutputChannel = standardOutputChan;
		mDefaultInputChannel = standardInputChan;
		
		//save pointer to the old output function so we can call it to display on the console
		outputProc = TclWrapper::ChannelOutput(chanTypeOutput);
			
		//check to see if we should redirect the console output- do not redirect when the Console Output property is empty
		PropertyObjectPtr output = context->AsPropertyObject()->EvaluateEx(step->GetValString(TCL_OUTPUT_EXPR,0), EvalOption_AllowEmptyExpression);
		if(output != NULL)
		{
			//get the client data for the default channel for use with the new channel.  This is required since we are calling into the default output procedure
			ClientData newInputChanClientData = TclWrapper::GetChannelInstanceData(mDefaultOutputChannel);

			//define a new channel type which is identical to the default channel except that it calls into a custom output procedure (OutputProc)
			static Tcl_ChannelType newInputChanType = {
				"console0",			/* Type name. */
				TCL_CHANNEL_VERSION_5 ,	/* v5 channel */
				chanTypeOutput->closeProc,		/* Close proc. */
				chanTypeOutput->inputProc,		/* Input proc. */
				&OutputProc,		/* Output proc. */
				chanTypeOutput->seekProc,			/* Seek proc. */
				chanTypeOutput->setOptionProc,			/* Set option proc. */
				chanTypeOutput->getOptionProc,			/* Get option proc. */
				chanTypeOutput->watchProc,		/* Watch for events on console. */
				chanTypeOutput->getHandleProc,		/* Get a handle from the device. */
				chanTypeOutput->close2Proc,			/* close2proc. */
				chanTypeOutput->blockModeProc,			/* blockModeproc.*/
				chanTypeOutput->flushProc,			/* flush proc. */
				chanTypeOutput->handlerProc,			/* handler proc. */
				chanTypeOutput->wideSeekProc,			/* wide seek proc */
				chanTypeOutput->threadActionProc,			/* thread action proc */

			};
			
			//because we are calling into the default output channel in addition to the custom channel, stack the new channel onto the existing channel
			TclWrapper::StackChannel(m_interp, &newInputChanType, newInputChanClientData, TCL_WRITABLE | TCL_READABLE, mDefaultOutputChannel);
			outputRedirected = true;
		}
		//only redirect if input is set
		PropertyObjectPtr input = context->AsPropertyObject()->EvaluateEx(step->GetValString(TCL_INPUT_EXPR,0), EvalOption_AllowEmptyExpression);
		if(input != NULL)
		{			
			ClientData newInputChanClientData = TclWrapper::GetChannelInstanceData(mDefaultInputChannel);
			
			//define a new channel type which is identical to the default channel except that it calls into a custom input procedure (InputProc)
			static Tcl_ChannelType newInputChanType = {
				"console1",			/* Type name. */
				TCL_CHANNEL_VERSION_5 ,	/* v5 channel */
				chanTypeInput->closeProc,		/* Close proc. */
				&InputProc,		/* Input proc. */
				chanTypeInput->outputProc,		/* Output proc. */
				chanTypeInput->seekProc,			/* Seek proc. */
				chanTypeInput->setOptionProc,			/* Set option proc. */
				chanTypeInput->getOptionProc,			/* Get option proc. */
				chanTypeInput->watchProc,		/* Watch for events on console. */
				chanTypeInput->getHandleProc,		/* Get a handle from the device. */
				chanTypeInput->close2Proc,			/* close2proc. */
				chanTypeInput->blockModeProc,			/* blockModeproc.*/
				chanTypeInput->flushProc,			/* flush proc. */
				chanTypeInput->handlerProc,			/* handler proc. */
				chanTypeInput->wideSeekProc,			/* wide seek proc */
				chanTypeInput->threadActionProc,			/* thread action proc */
			};
			
			//create a new channel using the new channel type

			newInputChan = TclWrapper::CreateChannel(&newInputChanType, "stdin0", newInputChanClientData, TCL_WRITABLE | TCL_READABLE);
			
			//register the channel with the interpreter
			TclWrapper::RegisterChannel(mInterp, newInputChan);
			
			//reqired to maintain correct reference counts - see TCL documentation
			TclWrapper::RegisterChannel(NULL, newInputChan);
			TclWrapper::SetStdChannel(newInputChan, TCL_STDIN);
			inputRedirected = true;
		}

	}
	~RedirectStreamsController()
	{
		//reset the default input channel as the current input channel if it was modified

		if(inputRedirected)
		{

			TclWrapper::RegisterChannel(mInterp, mDefaultInputChannel);
			TclWrapper::SetStdChannel(mDefaultInputChannel, TCL_STDIN);
			TclWrapper::UnregisterChannel(mInterp, newInputChan);

			inputRedirected = false;
		}
		
		//reset the default output channel as the current output channel if it was modified
		if(outputRedirected)
			TclWrapper::SetStdChannel(mDefaultOutputChannel, TCL_STDOUT);
	}
private:
	
	Tcl_Channel mDefaultOutputChannel;
	Tcl_Channel mDefaultInputChannel;
	
	Tcl_Interp * mInterp;
	Tcl_Channel newInputChan;

	bool outputRedirected;
	bool inputRedirected;

	Tcl_DriverOutputProc * mOutputProc;
	Tcl_DriverInputProc * mInputProc;
};



// CTclInterpreter
STDMETHODIMP CTclInterpreter::ExecuteStep(IDispatch * context)
{
	SequenceContextPtr seqContext(context);
	unsigned int length = 0;
	try
	{
#ifdef DEBUG
		if(seqContext->AsPropertyObject()->Exists("StationGlobals.DebugMode", 0) && seqContext->AsPropertyObject()->GetValBoolean("StationGlobals.DebugMode", 0)==VARIANT_TRUE)
			seqContext->Engine->DisplayAdapterConfigDialog("", VARIANT_FALSE, VARIANT_FALSE, VARIANT_FALSE, VARIANT_FALSE);
#endif
		PropertyObjectPtr step = seqContext->Step;
		
		if (!TclWrapper::IsInitialized())
			InitInterpreter(seqContext);

		//redirect streams in this class.
		RedirectStreamsController resetStreamsController(seqContext, m_interp);
		
		//initialize variables for input and output
		
		PropertyObjectPtr inputObj = seqContext->AsPropertyObject()->EvaluateEx(step->GetValString(TCL_INPUT_EXPR, 0), EvalOption_AllowEmptyExpression);
		if (inputObj!=NULL)
		{	
			_bstr_t input = inputObj->GetValString("", 0);
			// free the previous buffer if any
			free(m_inputBytes);
			m_inputBytes = NULL;

			m_inputNumBytes = strlen(input);
			m_inputBytes = (BYTE *) malloc(m_inputNumBytes);
			memcpy(m_inputBytes, (const char *)input, m_inputNumBytes);

		}
		// free the previous buffer if any
		free(m_outputBytes);
		m_outputBytes = NULL;
		m_outputNumBytes = 0;

		//set console display
		HWND consoleWindow = GetConsoleWindow();

		double consoleDisplayOption = seqContext->AsPropertyObject()->EvaluateEx(step->GetValString(TCL_CONSOLE_DISPLAY_OPTION, 0),0)->GetValNumber("", 0);
		BOOL consoleVisible = IsWindowVisible(consoleWindow);

		if (consoleDisplayOption == TCL_STEP_SHOW_WINDOW_INIT && !consoleVisible)
		{
			ShowWindow(consoleWindow, SW_SHOW);
			SetForegroundWindow(consoleWindow);
			BringWindowToTop(consoleWindow);
		}
		else if  (consoleDisplayOption == TCL_STEP_SHOW_WINDOW_ALWAYS)
		{
			ShowWindow(consoleWindow, SW_SHOW);
			SetForegroundWindow(consoleWindow);
			BringWindowToTop(consoleWindow);
		}
		else if (consoleDisplayOption == TCL_STEP_SHOW_WINDOW_NEVER && !consoleVisible)
			ShowWindow(consoleWindow, SW_SHOW);
		else if (consoleDisplayOption == TCL_STEP_HIDE)
			ShowWindow(consoleWindow, SW_HIDE);
		else if(consoleDisplayOption != TCL_STEP_HIDE && consoleDisplayOption!=TCL_STEP_SHOW_WINDOW_NEVER && consoleDisplayOption!=TCL_STEP_SHOW_WINDOW_ALWAYS && consoleDisplayOption!=TCL_STEP_SHOW_WINDOW_INIT)
			throw TclError(ERROR_PROPERTY_INVALID, seqContext->Engine->GetResourceString(TCL_STEP_TYPE_SECTION, "CONSOLE_DISPLAY_INVALID", vtMissing, &vtMissing));

		//set parameters
		SetParameters(seqContext);

		//determine operation
		double operation = step->GetValNumber(TCL_STEP_TYPE_OPERATION, 0);

		//evaluate expression
		if (operation == TCL_OPERATION_EVAL_EXPR_VAL || operation == TCL_OPERATION_EVAL_LITERAL)
		{
			//evaluate expression in TS for script
			_bstr_t expr = seqContext->AsPropertyObject()->EvaluateEx(step->GetValString(TCL_STEP_TYPE_TCL_EXPR, 0), 0)->GetValString("", 0);

			//evaluate expression in TCL
			int retVal = TclWrapper::Eval(m_interp, expr);
			Tcl_Obj * result = TclWrapper::GetObjResult(m_interp);
			if(retVal == TCL_ERROR)
				throw TclError(ERROR_EVALUATION, _bstr_t(result->bytes));
			else
			{
				PropertyObjectPtr resultObj = seqContext->AsPropertyObject()->EvaluateEx(step->GetValString(TCL_SCRIPT_RESULT_EXPR, 0), EvalOption_AllowEmptyExpression);
				if (resultObj != NULL)
				{
					//check if boolean, if it is, evaluate all Tcl expressions as Boolean
					VARIANT_BOOL isObj, isArray;
					TSUTIL::param_bstr_t typeName;
					if (resultObj->GetType("", 0, &isObj, &isArray, &typeName)==PropValType_Boolean)
					{
						int val;
						switch(TclWrapper::ExprBoolean(m_interp, result->bytes, &val))
						{

							case TCL_ERROR:
								throw TclError(ERROR_EVALUATION, _bstr_t(result->bytes));

							case TCL_OK:
								//set result string
								VARIANT_BOOL valAsVariant = val?VARIANT_TRUE:VARIANT_FALSE;
								resultObj->SetValBoolean("", 0, valAsVariant);
								break;
						}
						
					}
					else
						resultObj->SetValString("", PropOption_CoerceToNumber, result->bytes);
				}
			}

		}

		//evaluate file
		else if (operation == TCL_OPERATION_EVAL_FILE)
		{
			_bstr_t filePath;
			if (step->GetValBoolean(TCL_STEP_TYPE_USE_PATH_EXPR, 0) == VARIANT_TRUE)
				filePath = seqContext->AsPropertyObject()->EvaluateEx(step->GetValString(TCL_STEP_TYPE_PATH_EXPR, 0), 0)->GetValString("", 0);
			else
				filePath = step->GetValString(TCL_STEP_TYPE_PATH, 0);
			TSUTIL::param_bstr_t absPath;
			VARIANT_BOOL userCancelled;
			if(seqContext->Engine->FindFile(filePath, &absPath, &userCancelled, FindFile_PromptDisable, FindFile_AddDirToSrchList_No, VARIANT_FALSE, seqContext->GetSequenceFile().GetInterfacePtr()) == VARIANT_TRUE)
			{
				int retVal = TclWrapper::EvalFile(m_interp, absPath);
				if(retVal == TCL_ERROR)
				{
					Tcl_Obj * result = TclWrapper::GetObjResult(m_interp);
					_bstr_t string = seqContext->Engine->GetResourceString(TCL_STEP_TYPE_SECTION, "EXEC_ERROR", vtMissing, &vtMissing);
					
					char lineNo[16];
					sprintf_s(lineNo, "%d", m_interp->errorLine);
					
					CStringT<char, StrTraitATL<char, ChTraitsOS<char>>> x = string;
					x.Replace("%1", result->bytes);
					x.Replace("%2", lineNo);
					
					_bstr_t expr = x.GetString();
					throw TclError(ERROR_EVALUATION, expr);
				}
			}
		}
		//get parameters
		GetParameters(seqContext);

		//determine location of console output
		PropertyObjectPtr outputLoc = seqContext->AsPropertyObject()->EvaluateEx(step->GetValString(TCL_OUTPUT_EXPR, 0), EvalOption_AllowEmptyExpression);

		if (outputLoc != NULL)
		{
			if(m_outputNumBytes > 0)
			{
				if (TclWrapper::UseUnicode())
				{
					*(m_outputBytes + m_outputNumBytes) = '\0';
					*(m_outputBytes + m_outputNumBytes+1) = '\0';
					outputLoc->SetValString("", 0, (const wchar_t *) m_outputBytes);
				}
				else
				{
					*(m_outputBytes + m_outputNumBytes) = '\0';
					outputLoc->SetValString("", 0, (const char *) m_outputBytes);
				}
			}
			else
				outputLoc->SetValString("", 0, "");
		}

	}
	catch(TclError err)
	{
		ReportError(err.description);
		return err.error;
	}
	catch(_com_error err)
	{
		TclError tclErr = TclError(err);
		ReportError(tclErr.description);
		return tclErr.error;
	}
	catch(...)
	{
		ReportError(_bstr_t("Unknown Error"));
		return ERROR_UNKNOWN;
	}

	return S_OK;
}
void CTclInterpreter::ReportError(_bstr_t errorDescription)
{
	ICreateErrorInfoPtr createErrorInfo;
	IErrorInfoPtr errorInfo;
	CreateErrorInfo(&createErrorInfo);
	createErrorInfo->SetDescription(errorDescription);
	createErrorInfo->QueryInterface(IID_IErrorInfo, (LPVOID FAR*) &errorInfo);
	SetErrorInfo(0, errorInfo);
}

CTclInterpreter::CTclInterpreter() : m_outputBytes(NULL), m_outputNumBytes(0), m_inputBytes(NULL), m_inputNumBytes(0)
{
	interp = this;

}

void CTclInterpreter::InitInterpreter(SequenceContextPtr context)
{
	AllocConsole();
	HWND x = GetConsoleWindow();
	ShowWindow(x, SW_HIDE);
	_bstr_t string = context->Engine->GetResourceString(TCL_STEP_TYPE_SECTION, "INTERPRETER_DIALOG_TITLE", vtMissing , &vtMissing );
	SetConsoleTitle(string);
	string = context->Engine->GetResourceString(TCL_STEP_TYPE_SECTION, "TCL_DLL", vtMissing , &vtMissing );
	TclWrapper::LoadTcl(context, string);
	TCHAR fileName[_MAX_PATH];
	DWORD len = GetModuleFileName(GetModuleHandle(NULL), fileName, _MAX_PATH);
	TclWrapper::FindExecutable(fileName);
	m_interp = TclWrapper::CreateInterp();
	TclWrapper::Init(m_interp);
}

CTclInterpreter::~CTclInterpreter()
{
	interp = NULL;
	free(m_outputBytes);
	free(m_inputBytes);
}

void CTclInterpreter::SetParameters(SequenceContextPtr context)
{
	PropertyObjectPtr parameters = context->Step->AsPropertyObject()->GetPropertyObject(TCL_STEP_PARAMETERS, 0);
	long count = parameters->GetNumElements();
	for (long i = 0; i < count; i++)
	{
		PropertyObjectPtr param = parameters->GetPropertyObjectByOffset(i , 0);
		double paramDir = param->GetValNumber(TCL_STEP_DIRECTION, 0);
		if (paramDir == TCL_STEP_DIRECTION_INPUT || paramDir == TCL_STEP_DIRECTION_INPUT_OUTPUT)
		{
			_bstr_t paramName = param->GetValString(TCL_STEP_NAME, 0);
			_bstr_t paramVal = context->AsPropertyObject()->EvaluateEx(param->GetValString(TCL_STEP_VAL, 0), 0)->GetValString("", PropOption_CoerceFromNumber | PropOption_CoerceFromBoolean);
			TclWrapper::SetVar(m_interp, paramName, paramVal, 0);
		}
	}
}

void CTclInterpreter::GetParameters(SequenceContextPtr context)
{
	PropertyObjectPtr parameters = context->Step->AsPropertyObject()->GetPropertyObject(TCL_STEP_PARAMETERS, 0);
	long count = parameters->GetNumElements();
	for (long i = 0; i < count; i++)
	{
		PropertyObjectPtr param = parameters->GetPropertyObjectByOffset(i , 0);
		double paramDir = param->GetValNumber(TCL_STEP_DIRECTION, 0);
		if (paramDir == TCL_STEP_DIRECTION_OUTPUT || paramDir == TCL_STEP_DIRECTION_INPUT_OUTPUT)
		{
			_bstr_t paramName = param->GetValString(TCL_STEP_NAME, 0);
			_bstr_t expr = param->GetValString(TCL_STEP_VAL, 0);
			PropertyObjectPtr obj = context->AsPropertyObject()->EvaluateEx(expr, 0);
			
			const char * x = TclWrapper::GetVar(m_interp, paramName, 0);
								VARIANT_BOOL isObj, isArray;
			if (x == NULL)
			{
				_bstr_t string = context->Engine->GetResourceString(TCL_STEP_TYPE_SECTION, "ERROR_VARIABLE_NOT_FOUND", vtMissing, &vtMissing);
				CStringT<char, StrTraitATL<char, ChTraitsOS<char>>> cString = string;
				cString.Replace("%1", paramName);
				_bstr_t errorString = cString.GetString();
				throw TclError(ERROR_GET_PARAM, errorString);
			}

			TSUTIL::param_bstr_t typeName;
			if (obj->GetType("", 0, &isObj, &isArray, &typeName)==PropValType_Boolean)
			{
				int val;
				PropertyObjectPtr step = context->Step->AsPropertyObject();
				switch(TclWrapper::ExprBoolean(m_interp, x, &val))
				{
					case TCL_ERROR:
						throw TclError(ERROR_EVALUATION, _bstr_t(TclWrapper::GetObjResult(m_interp)->bytes));
						break;

					case TCL_OK:
						//set result string
						VARIANT_BOOL valAsVariant = val?VARIANT_TRUE:VARIANT_FALSE;
						obj->SetValBoolean("", 0, valAsVariant);
						break;
				}
			}
			else
				obj->SetValString("", PropOption_CoerceToNumber, x);
		}
	}
}

int OutputProc(ClientData instanceData, const char * buf, int numBytesToWrite, int * errorCodePtr)
{

	//allocate enough memory for a null termintator at the end
	BYTE * output = (BYTE *) malloc(numBytesToWrite + interp->m_outputNumBytes + 2);
	//copy the old buffer into the new buffer
	memcpy(output, interp->m_outputBytes, interp->m_outputNumBytes);
	//copy the new text into the buffer
	memcpy(output+interp->m_outputNumBytes, buf, numBytesToWrite);
	interp->m_outputNumBytes += numBytesToWrite;
	free(interp->m_outputBytes);
	interp->m_outputBytes = output;

	//call Tcl's outputproc
	int retval = outputProc(instanceData, buf, numBytesToWrite, errorCodePtr);
	return numBytesToWrite;
}


int InputProc(ClientData instanceData, char *buf, int bufSize, int *errorCodePtr)
{
	
	if(interp->m_inputNumBytes==0)
	{
		return 0;
	}
	
	else if (interp->m_inputNumBytes > (size_t)bufSize)
	{
		int numBytesToCopy = bufSize;
		//copy bytes from input buffer into buf requested
		memcpy (buf, interp->m_inputBytes, numBytesToCopy);
		//shrink buffer by number of bytes requested
		memmove(interp->m_inputBytes, interp->m_inputBytes + numBytesToCopy, interp->m_inputNumBytes - numBytesToCopy);
		interp->m_inputNumBytes -= numBytesToCopy;
		return numBytesToCopy;
	}
	else
	{
		size_t numBytesToCopy = interp->m_inputNumBytes;
		//buffer can hold all the text, so copy it all into buf requested
		memcpy(buf, interp->m_inputBytes, numBytesToCopy);
		free(interp->m_inputBytes);
		interp->m_inputBytes = NULL;
		interp->m_inputNumBytes = 0;
		return (int)numBytesToCopy;
	}

	return -1;

}

STDMETHODIMP CTclInterpreter::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITclInterpreter
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
STDMETHODIMP CTclInterpreter::get_ProcessID(DWORD* pVal)
{
	*pVal = GetCurrentProcessId();

	return S_OK;
}