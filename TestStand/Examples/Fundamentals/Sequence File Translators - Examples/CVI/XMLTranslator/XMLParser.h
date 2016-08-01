#include "tsapicvi.h"
#include "tsutil.h"

long LoadFile(CAObjHandle readStream, 
			  CAObjHandle *rootElement, 
			  ERRORINFO *errorInfoPtr);

void GetHeader(CAObjHandle readStream, 
			   char* headerInfo,
			   ERRORINFO *errorInfoPtr);

void GetFileVersionFromHeader(CAObjHandle readStream, 
							  char *fileVersionString, 
							  ERRORINFO *errorInfoPtr);

void GetFileFormatVersionFromHeader(CAObjHandle readStream, 
							  		char *fileFormatVersionString, 
							  		ERRORINFO *errorInfoPtr);

void GetStepList(CAObjHandle rootElement, 
				 CAObjHandle *stepList, 
				 ERRORINFO *errorInfoPtr);

char* GetStepType(CAObjHandle stepPtr, 
				  ERRORINFO *errorInfoPtr);

char* GetStepName(CAObjHandle stepPtr, 
				  ERRORINFO *errorInfoPtr);

long GetNumProperties(CAObjHandle stepPtr, 
					  ERRORINFO *errorInfoPtr);

long GetStepProperties(CAObjHandle stepPtr, 
					   char** propertyNameArray, 
					   char** properyValArray,
					   char** propertyTypeArray, 
					   ERRORINFO *errorInfoPtr);

long StepHasResult(CAObjHandle currentStep);

void GetResultData(CAObjHandle currentStep, 
			  	   char *resultName, 
			       char *resultType, 
			  	   char *resultVal,  
			  	   ERRORINFO *errorInfoPtr);

