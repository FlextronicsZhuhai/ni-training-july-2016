#include "tsapicvi.h"

int Translate(CAObjHandle engine, 
			  CAObjHandle readStream, 
			  CAObjHandle *seqFile, 
			  ERRORINFO *errorInfo);

CAObjHandle AddStep(CAObjHandle engine, 
					CAObjHandle currentStep, 
					char *stepName,  
					CAObjHandle seqFile, 
					const char *seqName, 
					ERRORINFO *errorInfo);

void AddResultProperty(CAObjHandle currentStep, 
				 	   CAObjHandle	 sequenceObject, 
				 	   char *resultName, 
				 	   char *resultType, 
				 	   char *resultVal, 
				 	   ERRORINFO *errorInfoPtr);

void GetAdapter(const char *stepType,
				char *adapterName);

void GetStepTypeEnum(const char *stepType,
					 char *stepTypeEnum);

void DeleteMemory(char** memPtr,
				  const int count);

void SetStepProperties(CAObjHandle stepPropertyObj, 
					   char *propertyName,
					   char *value,
					   char *type, 
					   ERRORINFO *errorInfoPtr);
