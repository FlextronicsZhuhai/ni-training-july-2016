#include "tsutil.h"

#define ERROR_MESSAGE_SIZE 1024

//Demonstrates how to cast object references in order to access class-specific properties and methods
__declspec(dllexport) void CastToMoreGenericClass(CAObjHandle seqContextCVI, char* version, char* comment, short *errorOccurred, long *errorCode, char errorMsg[ERROR_MESSAGE_SIZE])
{
	char *commentRef = NULL;
	char *versionRef = NULL;
	CAObjHandle seqFileAsPropObj = 0;
	TSObj_PropertyObjectFile seqFileAsPropObjFile = 0;
	TSObj_SeqFile seqFile = 0;
	int error = 0;  
	ErrMsg errMsg = "";
	ERRORINFO errorInfo;

	//Obtain a Reference to the Current Sequence File
	tsErrChk(TS_SeqContextGetSequenceFile(seqContextCVI, &errorInfo, &seqFile));
	
	//Since the version property is a member of the PropertyObjectFile class, you must cast the sequenceFile object to this class to access it
	tsErrChk(TS_SeqFileAsPropertyObjectFile(seqFile, &errorInfo, &seqFileAsPropObjFile));	
	tsErrChk(TS_PropertyObjectFileGetVersion(seqFileAsPropObjFile, &errorInfo, &versionRef));
	strcpy(version, versionRef);
	
	//Since the comment property is a member of the PropertyObject class, you must cast the sequenceFile object to this class to access it
	tsErrChk(TS_SeqFileAsPropertyObject(seqFile, &errorInfo, &seqFileAsPropObj));	
	tsErrChk(TS_PropertyGetComment(seqFileAsPropObj, &errorInfo, &commentRef));
	strcpy(comment, commentRef); 
	
	/*
	Note: the casting functions can be ommitted, but it is good practice to include them to improve code readability and avoid class conflicts.
	Example of code implemented without using a casting function:
		
			tsErrChk(TS_PropertyObjectFileGetVersion(seqFile, &errorInfo, &versionRef));
	*/
	
Error:
	// Close all references.  you must close both the reference to the object before casting and the references created by casting 
	CA_DiscardObjHandle(seqFileAsPropObjFile);
	CA_DiscardObjHandle(seqFileAsPropObj);
	CA_DiscardObjHandle(seqFile);
	CA_FreeMemory(versionRef);
	CA_FreeMemory(commentRef);  

	// If an error occurred, set the error flag to cause a run-time error in TestStand.
	if (error < 0)
	{
		*errorOccurred = TRUE;
		*errorCode = error;
		strncpy(errorMsg, errMsg, ERROR_MESSAGE_SIZE);
		errorMsg[ERROR_MESSAGE_SIZE-1] = 0;
	}
}



//Demonstrates how to cast to a more specific class to access the properties or methods of that class
__declspec(dllexport) void CastToMoreSpecificClass(CAObjHandle seqContextCVI, char* resultStatus, double *secondsExecuting, short *errorOccurred, long *errorCode, char errorMsg[ERROR_MESSAGE_SIZE])
{

	CAObjHandle seqContextAsPropObj = 0;
	CAObjHandle executionPropObj = 0;
	CAObjHandle stepPropObj = 0;

	char *resultStatusRef = NULL;

	int error = 0;  
	ErrMsg errMsg = "";
	ERRORINFO errorInfo;

	tsErrChk(TS_SeqContextAsPropertyObject(seqContextCVI, &errorInfo, &seqContextAsPropObj));
	
	//since there is no casting function avilable for more specific classes, use the propertyObject directly without casting
	//you must be sure that the object is a member of the child class or a run-time error will occur
	tsErrChk(TS_PropertyGetPropertyObject(seqContextAsPropObj, &errorInfo, "Runstate.Sequence.Main[0]", 0, &stepPropObj));	
	tsErrChk(TS_StepGetResultStatus(stepPropObj, &errorInfo, &resultStatusRef));
	strcpy(resultStatus, resultStatusRef);
	
	
	tsErrChk(TS_PropertyGetPropertyObject(seqContextAsPropObj, &errorInfo, "Runstate.Execution", 0, &executionPropObj));	
	tsErrChk(TS_ExecutionGetSecondsExecuting(executionPropObj, &errorInfo, secondsExecuting));
   	
Error:
	// Close all references.
	CA_DiscardObjHandle(seqContextAsPropObj);
	CA_DiscardObjHandle(executionPropObj);
	CA_DiscardObjHandle(stepPropObj);

	CA_FreeMemory(resultStatusRef);
 

	// If an error occurred, set the error flag to cause a run-time error in TestStand.
	if (error < 0)
	{
		*errorOccurred = TRUE;
		*errorCode = error;
		strncpy(errorMsg, errMsg, ERROR_MESSAGE_SIZE);
		errorMsg[ERROR_MESSAGE_SIZE-1] = 0;
	}
}
