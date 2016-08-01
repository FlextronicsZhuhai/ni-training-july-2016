#include "tsutil.h"


void __declspec(dllexport) __stdcall AccessBuiltInProperties( CAObjHandle seqContextCVI, char* seqName, long *numSteps, double *executionTime, short *errorOccurred,
    long *errorCode, char errorMsg[1024])
{
	char *seqNameRef = 0;
	TSObj_Sequence sequenceRef = 0; 
	TSObj_Execution executionRef = 0;
	
    ERRORINFO   errorInfo;
    ErrMsg      errMsg = {'\0'};
    int         error = 0;

	// Use the TestStand API to access built-in properties, such as the current sequence and its name.
	TS_SeqContextGetSequence(seqContextCVI, &errorInfo, &sequenceRef);
	TS_SequenceGetName(sequenceRef, &errorInfo, &seqNameRef); 
	strcpy(seqName, seqNameRef);

	// For some properties, the TestStand API provides a method to get the data, for example the GetNumSteps() method of the Sequence class.
	TS_SequenceGetNumSteps(sequenceRef, &errorInfo, TS_StepGroup_Main, numSteps);
	
	// The TestStand API also defines that all Execution objects contain a SecondsExecuting property. 
	TS_SeqContextGetExecution(seqContextCVI, &errorInfo, &executionRef); 
	TS_ExecutionGetSecondsExecuting(executionRef, &errorInfo, executionTime);
   

Error:
    //release references
	CA_DiscardObjHandle(sequenceRef);
	CA_DiscardObjHandle(executionRef);
	CA_FreeMemory(seqNameRef);
	
	// If an error occurred, set the error flag to cause a run-time error in TestStand.
	if (error < 0)
        {
        *errorOccurred = TRUE;
    
        *errorCode = error;
        strcpy(errorMsg, errMsg);
        }
}


void __declspec(dllexport) __stdcall GetStepResults( CAObjHandle seqContextCVI, char* stringValueTestResult, double* numericLimitTestResult, short *errorOccurred, 
    long *errorCode, char errorMsg[1024])
{
    
    CAObjHandle seqContextAsPropObj = 0;   
    TSObj_Sequence sequenceRef = 0;
	TSObj_Step stepRef = 0;     
	CAObjHandle stepAsPropObj = 0;   
	
	char *stringValTestResultRef = 0;
    
	int         error = 0;
    ErrMsg      errMsg = {'\0'};
    ERRORINFO   errorInfo;
    
	// This code shows how to obtain the Result property using only dynamic properties.
	// The RunState PropertyObject contains dynamic properties that describe the state of execution in the sequence invocation. 
	// Use the Variables View in TestStand to browse available properties.
	TS_SeqContextAsPropertyObject(seqContextCVI, &errorInfo, &seqContextAsPropObj);
	TS_PropertyGetValNumber(seqContextAsPropObj, &errorInfo, "Runstate.Sequence.Main[\"Numeric Limit Test\"].Result.Numeric", 0, numericLimitTestResult);
	

	// This code shows an alternate approach for attaining the result property.
	// Like RunState, the ThisContext object contains a sequence reference, but unlike RunState,  it is a built-in property.
	// i.e. The SequenceContext class defines the sequence property.  In many cases there are multiple approaches to accessing TestStand properties. 
	TS_SeqContextGetSequence(seqContextCVI, &errorInfo, &sequenceRef); 
	TS_SequenceGetStepByName(sequenceRef, &errorInfo, "String Value Test", TS_StepGroup_Main, &stepRef);
	TS_StepAsPropertyObject(stepRef, &errorInfo, &stepAsPropObj);
	TS_PropertyGetValString(stepAsPropObj, &errorInfo, "Result.String", 0, &stringValTestResultRef); 
	strcpy(stringValueTestResult, stringValTestResultRef);
	
	
Error:  
	//release references 
    CA_DiscardObjHandle(seqContextAsPropObj);
	CA_DiscardObjHandle(sequenceRef); 
	CA_DiscardObjHandle(stepRef); 
	CA_DiscardObjHandle(stepAsPropObj);
	CA_FreeMemory(stringValTestResultRef);

	// If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
        {
        *errorOccurred = TRUE;
    
        *errorCode = error;
        strcpy(errorMsg, errMsg);
        }
}

void __declspec(dllexport) __stdcall SetStepResults(VBOOL passFail1Result, VBOOL passFail2Result, double multipleNumericLimitResults[], int size, CAObjHandle seqContextCVI, short *errorOccurred, 
    long *errorCode, char errorMsg[1024])
{
    VARIANT multipleNumericLimitResultsVariant = {0};
    CAObjHandle stepAsPropObj = 0;
    TSObj_Step stepRef = 0;
    TSObj_Sequence sequenceRef = 0;
    CAObjHandle seqContextAsPropObj = 0;
	
	int 		numElements = 0;
    int         error = 0;
    ErrMsg      errMsg = {'\0'};
    ERRORINFO   errorInfo;
    
    // This code shows how to set the Result property using only dynamic properties.
	// The RunState PropertyObject contains dynamic properties that describe the state of execution in the sequence invocation. 
	// Use the Variables View in TestStand to browse available properties.
	TS_SeqContextAsPropertyObject(seqContextCVI, &errorInfo, &seqContextAsPropObj);
	TS_PropertySetValBoolean(seqContextAsPropObj, &errorInfo, "Runstate.Sequence.Main[\"Pass/Fail Test 1\"].Result.PassFail", 0, passFail1Result);

	// This code shows an alternate approach for setting the result property.
	// In this case, the step is accessed using built-in properties. 
	// In many cases there are multiple approaches to access TestStand properties, using either built-in or dynamic properties.
	TS_SeqContextGetSequence(seqContextCVI, &errorInfo, &sequenceRef); 
	TS_SequenceGetStepByName(sequenceRef, &errorInfo, "Pass/Fail Test 2", TS_StepGroup_Main, &stepRef);
	TS_StepAsPropertyObject(stepRef, &errorInfo, &stepAsPropObj);
	TS_PropertySetValBoolean(stepAsPropObj, &errorInfo, "Result.PassFail", 0, passFail2Result); 

	// Use the TestStand API to set the numeric results for the multiple numeric limit test.  
	// The SetValVariant() method allows you to set the entire array in a single operation.
	multipleNumericLimitResultsVariant = CA_VariantEmpty();
	
	//Copy the input array to a variant for use with the SetValVariant() method.
	CA_VariantSet1DArray(&multipleNumericLimitResultsVariant, CAVT_DOUBLE, size, multipleNumericLimitResults);
	
	TS_PropertySetValVariant(seqContextAsPropObj, &errorInfo, "Runstate.Sequence.Main[\"Multiple Numeric Limit Test\"].NumericArray", 0, multipleNumericLimitResultsVariant);

Error:  
    //release references 
	CA_VariantClear(&multipleNumericLimitResultsVariant); 
 	
	CA_DiscardObjHandle(seqContextAsPropObj);
	CA_DiscardObjHandle(sequenceRef); 
	CA_DiscardObjHandle(stepRef); 
	CA_DiscardObjHandle(stepAsPropObj); 
	
	// If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
        {
        *errorOccurred = TRUE;
    
        *errorCode = error;
        strcpy(errorMsg, errMsg);
        }
}

void __declspec(dllexport) __stdcall SetVariables(CAObjHandle seqContextCVI, char* dynamicPropertyVal, char* dynamicRuntimePropertyVal, short *errorOccurred, 
    long *errorCode, char errorMsg[1024])
{
    CAObjHandle seqContextAsPropObj = 0;
	
    ERRORINFO   errorInfo;
    int         error = 0;
    ErrMsg      errMsg = {'\0'};

	// Use the TestStand API to set the Locals.Container.DynamicProperty variable.
	TS_SeqContextAsPropertyObject(seqContextCVI, &errorInfo, &seqContextAsPropObj);    
	TS_PropertySetValString(seqContextAsPropObj, &errorInfo, "Locals.Container.DynamicProperty", 0, dynamicPropertyVal);

	// Use the TestStand API to create the Locals.Container.RuntimeProperty variable.  
	// Use the InsertIfMissing property option to create the variable if it does not already exist.
	TS_PropertySetValString(seqContextAsPropObj, &errorInfo, "Locals.Container.DynamicRuntimeProperty", TS_PropOption_InsertIfMissing, dynamicRuntimePropertyVal); 

Error:
    //release references 
	CA_DiscardObjHandle(seqContextAsPropObj);  
		
	// If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
        {
        *errorOccurred = TRUE;
    
        *errorCode = error;
        strcpy(errorMsg, errMsg);
        }
}
