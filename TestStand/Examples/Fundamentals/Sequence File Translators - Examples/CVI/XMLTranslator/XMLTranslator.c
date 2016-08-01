#include "XMLTranslator.h" 
#include "XMLParser.h"
#include "msxmldom.h"  
extern const char 	CURRENT_FILE_FORMAT_VERSION[];
extern const char 	CURRENT_FILE_VERSION[];
extern const int 	MAX_VERSION_STRING_LENGTH;

void DeleteMemory( char** memPtr, const int count)
{
	int i = 0;
	for (i = 0; i < count ; ++i)
		free(memPtr[i]);
   
}

int  Translate(CAObjHandle engine, CAObjHandle readStream, CAObjHandle *seqFile, ERRORINFO *errorInfoPtr)
{	
	int 						error = 0;
	ErrMsg 						errMsg = {'\0'};
	MSXMLObj_IXMLDOMDocument 	rootElement = 0; 
	MSXMLObj_IXMLDOMNode 		currentStep = 0;
	CAObjHandle 				sequenceObject= 0;
	CAObjHandle 				stepObj = 0;
	CAObjHandle 				propertyObjectFile = 0;
	CAObjHandle 				typeUsageList = 0;
	CAObjHandle 				stepasPropertyObject = 0;
	CAObjHandle 				propObjectFile = 0;
	MSXMLObj_IXMLDOMNodeList 	stepList = 0;
	ERRORINFO 					errorInfo;
	int 						m_totalSteps = 0;
	char 						*stepName = 0;
	char 						versionInfo[128];//MAX_VERSION_STRING_LENGTH
	
	if ( LoadFile(readStream, &rootElement, errorInfoPtr))
	{
		int 			numSteps;
		int 			i;
		const char 		*seqName = "MainSequence"; 
		VARIANT_BOOL 	val;
		
		tsErrChk(TS_EngineNewSequence(engine, 
									  &errorInfo, 
									  &sequenceObject));
		tsErrChk(TS_SequenceSetName(sequenceObject, 
									&errorInfo, 
									seqName));
		tsErrChk(TS_SeqFileInsertSequence(*seqFile, 
										  &errorInfo, 
										  sequenceObject));
		tsErrChk(TS_EngineLoadTypePaletteFilesEx(engine, 
												 &errorInfo,
												 TS_ConflictHandler_UseGlobalType, 
												 0));
		GetStepList(rootElement, 
					&stepList, 
					&errorInfo);
		errChk(MSXML_IXMLDOMNodeListGetlength(stepList,
                                              &errorInfo,
                                              &numSteps));
		for ( i = 0; i < numSteps; ++i)
		{
		
			errChk(MSXML_IXMLDOMNodeListGetitem(stepList,
										 	    errorInfoPtr, 
										 		i, 
										 		&currentStep));
			stepName = GetStepName(currentStep, 
								   &errorInfo);
			stepObj = AddStep(engine, 
							  currentStep, 
							  stepName, 
							  *seqFile, 
							  seqName, 
							  &errorInfo);
			if( errorInfo.sCode != TS_Err_NoError)
			{
				CA_FreeMemory(stepName);
				error = errorInfo.sCode;
				goto Error;
			}
			tsErrChk(TS_SequenceInsertStep(sequenceObject, 
										   &errorInfo, 
										   stepObj, 
										   m_totalSteps, 
										   TS_StepGroup_Main));
            if (StepHasResult(currentStep))
			{	
				char resultName[1024];
				char resultType[128];
				char resultVal[1024];
				
				//If the Step can return some result create a Local variable
				//of the same type and set it to the result value.
				GetResultData(currentStep, 
							  resultName, 
							  resultType, 
							  resultVal,  
							  &errorInfo);
				AddResultProperty(stepObj, 
							sequenceObject, 
							resultName, 
							resultType, 
							resultVal, 
							&errorInfo);
			}
			//Once the Step in created and inserted into the Sequence, add 
			//the Step to the TypeUsageList of the Sequence File.
			tsErrChk(TS_SeqFileAsPropertyObjectFile(*seqFile,
													&errorInfo, 
													&propertyObjectFile));
			tsErrChk(TS_PropertyObjectFileGetTypeUsageList(propertyObjectFile, 
														   &errorInfo, 
														   &typeUsageList));
			tsErrChk(TS_StepAsPropertyObject(stepObj, 
											 &errorInfo, 
											 &stepasPropertyObject));
			tsErrChk(TS_TypeUsageListAddUsedTypes(typeUsageList, 
												  &errorInfo, 
												  stepasPropertyObject, 
												  &val));
			++m_totalSteps;
			
			CA_FreeMemory(stepName);
			CA_DiscardObjHandle(stepObj);
			CA_DiscardObjHandle(propertyObjectFile);
			CA_DiscardObjHandle(typeUsageList);
			CA_DiscardObjHandle(stepasPropertyObject);
			CA_DiscardObjHandle(currentStep);
		}
	}
	//Set the version property on the Sequence file to the current file version number.
	tsErrChk(TS_SeqFileAsPropertyObjectFile(*seqFile, 
		                                    &errorInfo,
											&propObjectFile));
	versionInfo[0] = 0;
	GetFileVersionFromHeader(readStream, 
							 versionInfo, 
							 &errorInfo);
	if( versionInfo[0] == 0) strcpy(versionInfo, "0.0.0.0");
	tsErrChk(TS_PropertyObjectFileSetVersion(propObjectFile,
											 &errorInfo, 
											 versionInfo));	
	
	Error:
	CA_DiscardObjHandle(sequenceObject);
	CA_DiscardObjHandle(propObjectFile); 
	if ( error < 0 )
	{
		*errorInfoPtr = errorInfo;
		if(currentStep)
			CA_DiscardObjHandle(currentStep);
		if(stepObj)
			CA_DiscardObjHandle(stepObj);
		if(propertyObjectFile)
			CA_DiscardObjHandle(propertyObjectFile);
		if(typeUsageList)
			CA_DiscardObjHandle(typeUsageList);
		if(stepasPropertyObject)
			CA_DiscardObjHandle(stepasPropertyObject);
	}
	return error;
}

//creates a new step object and sets the properties to the 
//appropriate value.
CAObjHandle AddStep(CAObjHandle engine, CAObjHandle currentStep, char *stepName,  CAObjHandle seqFile, const char *seqName, ERRORINFO *errorInfoPtr)
{

	int error = 0;
	ErrMsg 			errMsg = {'\0'};
	ERRORINFO 		errorInfo;
	char 			**propertyNameArray;
	char 			**propertyValArray;
	char 			**propertyTypeArray;
	CAObjHandle 	newStep = 0;
	CAObjHandle 	stepPropertyObj = 0;
	int 			i = 0;
	char 			adapterName[128];
	char 			stepTypeEnum[128];
	char 			*stepTypeString;
	long 			numProperties = GetNumProperties(currentStep, 
										  			 &errorInfo);
 
	propertyNameArray = (char**) ( malloc( numProperties * sizeof(char*))); 
	propertyValArray = (char**) ( malloc( numProperties * sizeof(char*))); 
	propertyTypeArray = (char**) ( malloc( numProperties * sizeof(char*)));
	GetStepProperties(currentStep, 
 					  propertyNameArray, 
 				   	  propertyValArray, 
					  propertyTypeArray,
 				   	  &errorInfo);
	stepTypeString = GetStepType(currentStep, 
							     &errorInfo);
	GetAdapter(stepTypeString, 
			   adapterName);
	if(!adapterName) 
	{
		error = -1;
		goto Error;
	}
	GetStepTypeEnum(stepTypeString,
					stepTypeEnum);
	tsErrChk(TS_EngineNewStep(engine, 
                           	  &errorInfo, 
                          	  adapterName,
                           	  stepTypeEnum, 
                           	  &newStep));
	tsErrChk(TS_StepSetName(newStep, 
 							&errorInfo, 
 							stepName));
	tsErrChk(TS_StepAsPropertyObject(newStep, 
 								  	 &errorInfo, 
 								  	 &stepPropertyObj));
	for ( i =0; i < numProperties; ++i)
  	{
		SetStepProperties(stepPropertyObj,
						  propertyNameArray[i],
						  propertyValArray[i],
						  propertyTypeArray[i],
						  &errorInfo);
		if( errorInfo.sCode != TS_Err_NoError)
		{
			error = errorInfo.sCode;
			goto Error;
		}
		
	}
		
	Error:
 	CA_DiscardObjHandle(stepPropertyObj);
 	if ( error < 0)
	{
		if(newStep)
			CA_DiscardObjHandle(newStep);
		newStep = 0; 
		*errorInfoPtr = errorInfo;
		
 	 }
	DeleteMemory(propertyNameArray,
				 numProperties);
	DeleteMemory(propertyValArray,
				 numProperties);
	DeleteMemory(propertyTypeArray,
				 numProperties);
	return newStep;
}
				   
void AddResultProperty(CAObjHandle stepObj, CAObjHandle sequenceObject, char *resultName, char *resultType, char *resultVal, ERRORINFO *errorInfoPtr)
{
	int 			error = 0;
    ErrMsg 			errMsg = {'\0'};
 	ERRORINFO 		errorInfo;
	CAObjHandle 	locals; 
	char 			expression[1024];
	
	strcpy(expression, "Locals.");
	strcat(expression, resultName);
	strcat(expression, "= Step.");
	strcat(expression, resultVal);
	tsErrChk(TS_SequenceGetLocals(sequenceObject, 
	                              &errorInfo, 
	                              &locals));
	if ( strcmp(resultType, "string") == 0)
		tsErrChk(TS_PropertySetValString(locals, 
	 								     &errorInfo, 
	 								     resultName, 
	 								     TS_PropOption_InsertIfMissing, 
	 								     ""));
	if ( strcmp(resultType, "number") == 0)
		tsErrChk(TS_PropertySetValNumber(locals, 
	 								     &errorInfo, 
	 								     resultName, 
	 								     TS_PropOption_InsertIfMissing, 
	 								     0));
	if ( strcmp(resultType, "bool") == 0)
		tsErrChk(TS_PropertySetValBoolean(locals, 
	 								      &errorInfo, 
	 								      resultName, 
	 								      TS_PropOption_InsertIfMissing,
	 								      0));
    //Set the post expression so that it assigns the result value 
	//to the local variable created.
	tsErrChk(TS_StepSetPostExpression(stepObj, 
    								  &errorInfo, 
    								  expression));
    
	Error:
	CA_DiscardObjHandle(locals);
	if ( error < 0 )
	{
		*errorInfoPtr = errorInfo;
   	}
}

void GetAdapter(const char *stepType, char *adapterName)
{
  if(0 == strcmp(stepType, "MsgBox"))
	  strcpy(adapterName, "None Adapter");
  else if (0 == strcmp(stepType, "DISPLAYGRAPH"))
	  strcpy(adapterName, "");
  else
	  *adapterName = 0;
}

void GetStepTypeEnum(const char *stepType, char *stepTypeEnum)
{
	if(0 == strcmp(stepType, "MsgBox"))
		strcpy(stepTypeEnum, "MessagePopup");
  	else if (0 == strcmp(stepType, "DISPLAYGRAPH"))
		strcpy(stepTypeEnum, "DisplayGraph");
	
}

void SetStepProperties(CAObjHandle stepPropertyObj, char *propertyName, char *value, char *type, ERRORINFO *errorInfoPtr)
{
	int 			error = 0;
    ErrMsg 			errMsg = {'\0'};
 	ERRORINFO 		errorInfo;
	
	if ( strcmp(type, "string") == 0)
		tsErrChk(TS_PropertySetValString(stepPropertyObj, 
	 								     &errorInfo, 
	 								     propertyName, 
	 								     TS_PropOption_NoOptions,
	 								     value));
	else if ( strcmp(type, "number") == 0)
	{
		double val = atof(value);
		tsErrChk(TS_PropertySetValNumber(stepPropertyObj, 
	 								     &errorInfo, 
	 								     propertyName, 
	 								     TS_PropOption_NoOptions, 
	 								     val));
	}
	else if ( strcmp(type, "bool") == 0)
	{
		VBOOL val = (strcmp(value,"true") == 0);
		tsErrChk(TS_PropertySetValBoolean(stepPropertyObj, 
	 								      &errorInfo, 
	 								      propertyName, 
	 								      TS_PropOption_NoOptions,
	 								      val));
	}
	else
	{
		error = -1;
		errorInfo.sCode = TS_Err_UnknownVariableOrProperty;
		strcpy(errorInfo.description, "Unsupported Data type used in Step properties.");
	}
	
	Error:
	if( error < 0)
	{
		*errorInfoPtr = errorInfo;	
	}
}
