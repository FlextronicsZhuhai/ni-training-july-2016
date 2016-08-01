//==============================================================================
//
// Title:       Executing Sequences Using API -LabWindows_CVI.c 
//
// Description:	This file holds the three functions used in the Executing
//				Sequences Using API - LabWindows_CVI for TestStand.
//
//==============================================================================

#include "tsutil.h"

#define ERROR_MESSAGE_SIZE 1024

//==============================================================================
//
//	This function executes a sequence with no process model.
//
//	Inputs:
//		seqContextCVI:			The sequence context.
//		sequenceFileToRun:		The name of the sequence file to run located in the TestStand search directories.
//		sequenceNameParameter:	The name of the sequence to run within the sequence file.
//
//	Outputs:
//		errorOccured:			TRUE or FALSE to represent if an error has occured or not.
//		errorCode:				The error code if errorOccured is TRUE.
//		errorMsg:				The error message if errorOccured is TRUE.
//
void __declspec(dllexport) __stdcall ExecuteWithNoProcessModel(CAObjHandle seqContextCVI, char sequenceFileToRun[1024],
		char sequenceNameParameter[1024], short *errorOccurred, long *errorCode, char errorMsg[ERROR_MESSAGE_SIZE])
{
	CAObjHandle engineHandle = 0;
	TSObj_SeqFile CurrentSeqFileHandle = 0;
	TSObj_SeqFile sequenceFileEx = 0;
	CAObjHandle executionHandle = 0;

	char *absolutePath = 0;
	VARIANT seqFileVar = CA_VariantEmpty ();
	VARIANT seqExecutionVar = CA_VariantEmpty ();
	int error = 0;
	
	ErrMsg errMsg = "";
	ERRORINFO errorInfo;

	// Get the engine handle.
	tsErrChk (TS_SeqContextGetEngine (seqContextCVI, &errorInfo, &engineHandle));

	// Get the sequence file handle.
	tsErrChk (TS_SeqContextGetSequenceFile (seqContextCVI, &errorInfo, &CurrentSeqFileHandle));
	
	// Copy the sequence file handle to a variant variable to be used in the next step. 
	CA_VariantSetObjHandle (&seqFileVar, CurrentSeqFileHandle, CAVT_DISPATCH);
	
	// Find the sequence file's absolute path based on the calling sequence file's directory.
	tsErrChk (TS_EngineFindFile (engineHandle, &errorInfo, sequenceFileToRun,
								 &absolutePath, NULL,
								 TS_FindFile_PromptHonorUserPreference,
								 TS_FindFile_AddDirToSrchList_Ask, 
								 VFALSE, seqFileVar, NULL));

	// Locate and open the sequence file containing the sequence to be executed.
	tsErrChk (TS_EngineGetSeqFileEx (engineHandle, &errorInfo, absolutePath, TS_GetSeqFile_FindFile, TS_ConflictHandler_Error, &sequenceFileEx));

	// Launch a new execution of the specified sequence.
	tsErrChk (TS_EngineNewExecution (engineHandle, &errorInfo, sequenceFileEx, sequenceNameParameter, 0, VFALSE, TS_ExecTypeMask_Normal,
									 CA_DEFAULT_VAL, CA_DEFAULT_VAL, CA_DEFAULT_VAL,&executionHandle));
	
	// Wait for the execution to end.
	CA_VariantSetObjHandle (&seqExecutionVar, seqContextCVI, CAVT_DISPATCH);
	tsErrChk (TS_ExecutionWaitForEndEx (executionHandle, &errorInfo, INFINITE, VTRUE, CA_DEFAULT_VAL, seqExecutionVar, NULL));
		
	// Release the sequence file opened previously.
	tsErrChk (TS_EngineReleaseSeqFileEx (engineHandle, &errorInfo, sequenceFileEx, 0, NULL));


Error:
	// FREE RESOURCES
	CA_FreeMemory(absolutePath);
	CA_VariantClear (&seqExecutionVar);
	CA_DiscardObjHandle (executionHandle);
	CA_DiscardObjHandle (sequenceFileEx);
	CA_VariantClear (&seqFileVar);
	CA_DiscardObjHandle (CurrentSeqFileHandle);
	CA_DiscardObjHandle (engineHandle);
	
	// If an error occurred, set the error flag to cause a run-time error in TestStand.
	if (error < 0)
	{
		*errorOccurred = TRUE;

		// SET THE ERROR CODE AND STRING
		*errorCode = error;
		strncpy(errorMsg, errMsg, ERROR_MESSAGE_SIZE);
		errorMsg[ERROR_MESSAGE_SIZE-1] = 0;
	}
}


//==============================================================================
//
//	This function executes a sequence with a process model.
//
//	Inputs:
//		seqContextCVI:			The sequence context.
//		sequenceFileToRun:		The name of the sequence file to run located in the TestStand search directories.
//		processModelName:		The name of the process model to run located in the TestStand search directoreis.
//		sequenceNameParameter:	The name of the sequence to run within the sequence file.
//
//	Outputs:
//		errorOccured:			TRUE or FALSE to represent if an error has occured or not.
//		errorCode:				The error code if errorOccured is TRUE.
//		errorMsg:				The error message if errorOccured is TRUE.
//
void __declspec(dllexport) __stdcall ExecuteWithProcessModel(CAObjHandle seqContextCVI, char sequenceFileToRun[1024], char processModelName[1024],
		char sequenceNameParameter[1024], short *errorOccurred, long *errorCode, char errorMsg[ERROR_MESSAGE_SIZE])
{
	CAObjHandle engineHandle = 0;
	TSObj_SeqFile CurrentSeqFileHandle = 0;
	TSObj_SeqFile sequenceFileEx = 0;
	TSObj_SeqFile processModelEx = 0;
	CAObjHandle executionHandle = 0;

	char *absolutePath = 0;
	VARIANT seqFileVar = CA_VariantEmpty ();
	VARIANT seqExecutionVar = CA_VariantEmpty ();
	int error = 0;
	
	ErrMsg errMsg = {'\0'};
	ERRORINFO errorInfo;

	// Get the engine handle.
	tsErrChk (TS_SeqContextGetEngine (seqContextCVI, &errorInfo, &engineHandle));
	
	// Get the sequence file handle.
	tsErrChk (TS_SeqContextGetSequenceFile (seqContextCVI, &errorInfo, &CurrentSeqFileHandle));
	
	// Copy the sequence file handle to a variant variable to be used in the next step. 
	CA_VariantSetObjHandle (&seqFileVar, CurrentSeqFileHandle, CAVT_DISPATCH);
	
	// Find the sequence file's absolute path based on the calling sequence file's directory.
	tsErrChk (TS_EngineFindFile (engineHandle, &errorInfo, sequenceFileToRun, &absolutePath, NULL, TS_FindFile_PromptEnable,
								 TS_FindFile_AddDirToSrchList_Yes, VFALSE, seqFileVar, NULL));
	
	// Locate and opens the sequence file containing the sequence to be executed.
	tsErrChk (TS_EngineGetSeqFileEx (engineHandle, &errorInfo, absolutePath, TS_GetSeqFile_FindFile, TS_ConflictHandler_Error, &sequenceFileEx));
	
	// Locate and opens the process model to be used for this execution.
	tsErrChk (TS_EngineGetSeqFileEx (engineHandle, &errorInfo, processModelName, TS_GetSeqFile_FindFile, TS_ConflictHandler_Error, &processModelEx));
	
	
	// Launch a new execution of the sequence using the process model entry point specified.
	tsErrChk (TS_EngineNewExecution (engineHandle, &errorInfo, sequenceFileEx, sequenceNameParameter, processModelEx, VFALSE, TS_ExecTypeMask_Normal,
									 CA_DEFAULT_VAL, CA_DEFAULT_VAL, CA_DEFAULT_VAL,&executionHandle));

   	// Wait for the execution to end.  
	CA_VariantSetObjHandle (&seqExecutionVar, seqContextCVI, CAVT_DISPATCH);
	tsErrChk (TS_ExecutionWaitForEndEx (executionHandle, &errorInfo, INFINITE, VTRUE, CA_DEFAULT_VAL, seqExecutionVar, NULL));
	
	// Release the process model and client sequence file opened previously.
	tsErrChk (TS_EngineReleaseSeqFileEx (engineHandle, &errorInfo, processModelEx, 0, NULL));
	tsErrChk (TS_EngineReleaseSeqFileEx (engineHandle, &errorInfo, sequenceFileEx, 0, NULL));

Error:
	// FREE RESOURCES
	CA_FreeMemory(absolutePath);
	CA_VariantClear (&seqExecutionVar);
	CA_DiscardObjHandle (executionHandle);
	CA_DiscardObjHandle (sequenceFileEx);
	CA_DiscardObjHandle (processModelEx);
	CA_VariantClear (&seqFileVar);
	CA_DiscardObjHandle (CurrentSeqFileHandle);
	CA_DiscardObjHandle (engineHandle);

	// If an error occurred, set the error flag to cause a run-time error in TestStand.
	if (error < 0)
	{
		*errorOccurred = TRUE;

		// SET THE ERROR CODE AND STRING
		*errorCode = error;
		strncpy(errorMsg, errMsg, ERROR_MESSAGE_SIZE);
		errorMsg[ERROR_MESSAGE_SIZE-1] = 0;
	}
}


//==============================================================================
//
//	This function executes a sequence with sequence parameters.
//
//	Inputs:
//		seqContextCVI:			The sequence context.
//		sequenceFileToRun:		The name of the sequence file to run located in the TestStand search directories.
//		sequenceNameParameter:	The name of the sequence to run within the sequence file.
//		numberValue:			A number to be set as a parameter and displayed to the user.
//		stringValue:			A string to be set as a parameter and displayed to the user.
//
//	Outputs:
//		errorOccured:			TRUE or FALSE to represent if an error has occured or not.
//		errorCode:				The error code if errorOccured is TRUE.
//		errorMsg:				The error message if errorOccured is TRUE.
//
void __declspec(dllexport) __stdcall ExecuteWithSequenceParameters(CAObjHandle seqContextCVI, char sequenceFileToRun[1024],
		char sequenceNameParameter[1024], double numberValue, char stringValue[1024], short *errorOccurred, long *errorCode, char errorMsg[ERROR_MESSAGE_SIZE])
{
	
	CAObjHandle engineHandle = 0;
	TSObj_SeqFile CurrentSeqFileHandle = 0;  
	TSObj_Property propertyObject = 0;
	TSObj_SeqFile sequenceFileEx = 0;
	CAObjHandle executionHandle = 0;

	char *absolutePath = 0;
	VARIANT propertyObjectVar = CA_VariantEmpty ();
	VARIANT seqFileVar = CA_VariantEmpty ();
	VARIANT seqExecutionVar = CA_VariantEmpty ();
	int error = 0;
	
	ErrMsg errMsg = "";
	ERRORINFO errorInfo;

	// Get the engine handle.
	tsErrChk (TS_SeqContextGetEngine (seqContextCVI, &errorInfo, &engineHandle));

	// Get the sequence file handle.
	tsErrChk (TS_SeqContextGetSequenceFile (seqContextCVI, &errorInfo, &CurrentSeqFileHandle));
	
	// Copy the sequence handle to a variant variable to be used in the next step. 
	CA_VariantSetObjHandle (&seqFileVar, CurrentSeqFileHandle, CAVT_DISPATCH);
	
	// Find the sequence file's absolute path based on the calling sequence file's directory.
	tsErrChk (TS_EngineFindFile (engineHandle, &errorInfo, sequenceFileToRun, &absolutePath, NULL, TS_FindFile_PromptEnable,
								 TS_FindFile_AddDirToSrchList_Yes, VFALSE, seqFileVar, NULL));

	// Locate and opens the sequence file containing the sequence to be executed.
	tsErrChk (TS_EngineGetSeqFileEx (engineHandle, &errorInfo, absolutePath, TS_GetSeqFile_FindFile, TS_ConflictHandler_Error, &sequenceFileEx));

	// Create a "container" PropertyObject and add a subproperty for each parameter of the sequence to call.
	// Note: Subproperties must be in the same order as parameters appear in the sequence.
	tsErrChk (TS_EngineNewPropertyObject (engineHandle, &errorInfo, TS_PropValType_Container, VFALSE, "Parameters", 0, &propertyObject));
	tsErrChk (TS_PropertySetValNumber (propertyObject, &errorInfo, "NumberVal", 1, numberValue));
	tsErrChk (TS_PropertySetValString (propertyObject, &errorInfo, "StringVal", 1, stringValue));

	// Launch a new execution of the sequence.     
	CA_VariantSetObjHandle (&propertyObjectVar, propertyObject, CAVT_DISPATCH);
	tsErrChk (TS_EngineNewExecution (engineHandle, &errorInfo, sequenceFileEx, sequenceNameParameter, 0, VFALSE, TS_ExecTypeMask_Normal,
									 propertyObjectVar, CA_DEFAULT_VAL, CA_DEFAULT_VAL, &executionHandle));
	
	// Wait for the execution to end.      	
	CA_VariantSetObjHandle (&seqExecutionVar, seqContextCVI, CAVT_DISPATCH);
	tsErrChk (TS_ExecutionWaitForEndEx (executionHandle, &errorInfo, INFINITE, VTRUE, CA_DEFAULT_VAL, seqExecutionVar, NULL));
	
	// Release the sequence file opened previously.
	tsErrChk (TS_EngineReleaseSeqFileEx (engineHandle, &errorInfo, sequenceFileEx, 0, NULL));


Error:
	// FREE RESOURCES
	CA_FreeMemory(absolutePath);
	CA_VariantClear (&seqExecutionVar);
	CA_DiscardObjHandle (executionHandle);
	CA_DiscardObjHandle (sequenceFileEx);
	CA_VariantClear (&propertyObjectVar);
	CA_DiscardObjHandle (propertyObject);
	CA_VariantClear (&seqFileVar);
	CA_DiscardObjHandle (CurrentSeqFileHandle);
	CA_DiscardObjHandle (engineHandle);
	
	// If an error occurred, set the error flag to cause a run-time error in TestStand.
	if (error < 0)
	{
		*errorOccurred = TRUE;

		// SET THE ERROR CODE AND STRING
		*errorCode = error;
		strncpy(errorMsg, errMsg, ERROR_MESSAGE_SIZE);
		errorMsg[ERROR_MESSAGE_SIZE-1] = 0;
	}
}
