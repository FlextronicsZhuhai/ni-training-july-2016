#include <ansi_c.h>
#include "tsutil.h"
#include "TextTranslator.h"

#define BUFSIZE  1024
//Global Error Variables
//need not declare them in each and every function
int 		error = 0;
ErrMsg 		errMsg = {'\0'};
ERRORINFO	errorInfo; 

void DeleteMemory( char** memPtr, const int count)
{
	int i = 0;
	for (i = 0; i < count ; ++i)
		free(memPtr[i]);
}

/*
Break the given input strings on the seperator and store the values 
in the tokens array. Return the number of tokens found which will be
used to delete the array.
*/
int SplitOnSeparator( char* inputString, const char separator, char **tokens, const int maxTokens)
{
	int j = 0;
	
	while(j < maxTokens)
	{
		char *pCh = strchr(inputString, separator);
		
		if ( pCh )
		{
			size_t size = (pCh - inputString);
			
			tokens[j] = malloc( size+1);
			memcpy(tokens[j], inputString, size);
			tokens[j++][size]='\0';
			inputString = pCh+1;
		}
		else
			break;
	}
	//copy the last token 
	if ( strlen(inputString) && j < maxTokens)
	{
		size_t len = strlen(inputString);
		
		tokens[j] = malloc( len + 1);
		strncpy(tokens[j], inputString, len);
		tokens[j++][len] = '\0';
	}
	return j;
}

void ReadTillDelim(char* buffer, char* delim, CAObjHandle *readPtr)
{	
	unsigned char 	*ch = (unsigned char*)'\n';
	long 			numBytes = 1;
	SAFEARRAY 		*psa;
	VBOOL 			endofStream;
	int 			i = 0;
	
	tsErrChk(TS_InputStreamGetIsEndofStream (*readPtr, &errorInfo, &endofStream));
	while ( !endofStream )
	{
		tsErrChk(TS_InputStreamReadBytes( *readPtr, &errorInfo, 1, &psa));
		SafeArrayAccessData(psa, (void**)(&ch));
		if ( strchr(delim, *ch) )
		{
			long val = 0;
			
			/*if(*ch == '\r' )
			{
				//remove the \n character after the \r is encountered by moving
				//one past the current delimiter.
				TS_InputStreamGetOffset (*readPtr, &errorInfo,
										&val);
				TS_InputStreamSetOffset (*readPtr, &errorInfo,
										++val);
			}*/
			SafeArrayUnaccessData(psa);
			break;
		}
		buffer[i]=*ch;
		++i;
		SafeArrayUnaccessData(psa);
		tsErrChk(TS_InputStreamGetIsEndofStream (*readPtr, &errorInfo, &endofStream));
	}
	buffer[i] = '\0';
	
	Error:  
	return;
}

char* GetAdapterName(const char *stepType)
{
	char* ret = "None Adapter";
	
	if ( strcmp(stepType, "DisplayGraph") == 0)
		strcpy(ret, "");
	else if(strcmp(stepType, "MessagePopup") != 0)
		error = -1;		
	return ret;
}

// Parses "Name:Type"
void ParseTypeValue(CAObjHandle obj, char* inputLine, char* val, ERRORINFO *errorInfoPtr)
{
	SAFEARRAY 	*psa;
	char 		*tokens[2] = {0};
	int 		numTokens = SplitOnSeparator(inputLine, ':', tokens, 2);
	
	// token[0] == Name 
	// token[1] == Type (Can be boolean,string,number)
	if (  numTokens != 2 )
	{
		// Invalid file format.
		// raise error
		//
		error = -1;
		strcpy( errMsg, "Error in parsing file, invalid number of arguments");
	}
	if (strcmp(tokens[1],"boolean") == 0)
	{
		VBOOL newVal =  (strcmp(val,"true")==0);
		
		tsErrChk(TS_PropertySetValBoolean(obj,
                                          &errorInfo,
                                          tokens[0],
                                          TS_PropOption_NoOptions,
                                          newVal));
	}
	else if (strcmp(tokens[1], "string") == 0)
	{
		tsErrChk(TS_PropertySetValString(obj,
                                          &errorInfo,
										  tokens[0],
										  TS_PropOption_NoOptions,
										  val));
	}
	else if (strcmp(tokens[1], "number") == 0)
	{
		double numVal=0;
		
		numVal = atof(val);
		tsErrChk(TS_PropertySetValNumber(obj,
                                         &errorInfo,
										 tokens[0],
										 TS_PropOption_NoOptions,
										 numVal));
	}
	else
	{
		// Invalid type.
		//   raise error;
		error = TS_Err_UnknownType;
		strcpy(errorInfoPtr->description, "Invalid Type");
	}
	
	Error:
	DeleteMemory(tokens, numTokens);
	if(error < 0)
	{
		errorInfoPtr->sCode = error;
	}
}

void ParseResultValue(CAObjHandle obj, CAObjHandle step, char* inputLine)
{
	SAFEARRAY 	*psa;
	char 		expression[1024]={0}; 
	char 		*tokens[2] = {0};
	CAObjHandle propertyObject;
	char 		*nameType[2] = {0}; 
	int 		numNameTypes = 0;
	int 		numTokens = SplitOnSeparator(inputLine, '=', tokens, 2);
	
	// token[0] == Name:Type (Type can be boolean,string,number) 
	// token[1] == Value 
	if ( numTokens == 2 )
	{
		numNameTypes = SplitOnSeparator(tokens[0], ':', nameType, 2);
		//nameType[0] will have the name of the result property of the step and 
		//nameType[1] will have the type
		if (strcmp(nameType[1], "boolean") == 0)
		{
			tsErrChk(TS_PropertySetValBoolean(obj,
                                          	  &errorInfo,
						                  	  tokens[1],
						                  	  TS_PropOption_InsertIfMissing,
						                  	  0));
						                  
		}
		else if (strcmp(nameType[1], "string") == 0)
		{
			tsErrChk(TS_PropertySetValString(obj,
                                         	 &errorInfo,
						                 	 tokens[1],
						                 	 TS_PropOption_InsertIfMissing,
						                 	 ""));
		}
		else if (strcmp(nameType[1], "number") == 0)
		{			
			tsErrChk(TS_PropertySetValNumber(obj,
        	                             	 &errorInfo,
						                 	 tokens[1],
						                 	 TS_PropOption_InsertIfMissing,
						                 	 0));
		}
		else
		{
			// Invalid type.
			// flag error;
			//
			error = TS_Err_UnknownType;
			strcpy(errMsg, "Invalid Step Type");
		}
		strcat(expression,  "Locals.");
		strcat(expression, tokens[1]);
		strcat(expression, "= Step.") ;
		strcat(expression, nameType[0]);
		tsErrChk(TS_StepAsPropertyObject(step,
                                     &errorInfo,
                                     &propertyObject));
		tsErrChk(TS_PropertySetValString(propertyObject,
                                     &errorInfo,
                                     "TS.PostExpr",
                                     0,
                                     expression));
    	}
    else
    {
    	//Trying to set an Invalid Property flag error
    	error = -1;
		strcpy(errMsg, "Invalid Property Type");
    }
    
	Error:
	DeleteMemory(tokens, numTokens);
	DeleteMemory(nameType, numNameTypes);
	CA_DiscardObjHandle(propertyObject); 
}

// Parses : Name:Type=Value
void ParseParameters(CAObjHandle step, char *inputLine, ERRORINFO *errorInfoPtr)
{
	int 		error = 0;
    ErrMsg 		errMsg = {'\0'};
	SAFEARRAY 	*psa;
	ERRORINFO 	errorInfo;
	char 		*tokens[2] = {0};
	int 		numTokens = SplitOnSeparator(inputLine, '=', tokens, 2);
	
	// token[0] == Name:Type
	// token[1] == Value
	CAObjHandle propertyObject;
	if ( numTokens == 2 )
	{
		tsErrChk(TS_StepAsPropertyObject(step,
                                     &errorInfo,
                                     &propertyObject));
		ParseTypeValue(propertyObject, 
					   tokens[0], 
					   tokens[1], 
					   &errorInfo);
		if ( errorInfo.sCode < 0)
		{
			error = errorInfo.sCode;
			goto Error;
		}
	}
	else
	{
	 	// Invalid file format.
		//Parse error invalid number of tokens
		error = -1;
		strcpy( errMsg, "Error in parsing file, invalid number of arguments");
	}
		
	Error:
	DeleteMemory(tokens, numTokens);
	CA_DiscardObjHandle(propertyObject);
	if(error < 0)
	{
		*errorInfoPtr = errorInfo;
	}
}

// Parses: StepName,StepType,Result,Property,Property.... \r\n
// Where: 1) Result is Name:Type
//        2) Property is Name:Type=Value
CAObjHandle CommaSeparatedStepParser(CAObjHandle engine, CAObjHandle seq, char *inputLine, ERRORINFO *errorInfoPtr)
{
	int 		error = 0;
    ErrMsg 		errMsg = {'\0'};
	SAFEARRAY 	*psa;
	ERRORINFO 	errorInfo;
	char 		*tokens[128] = {0};   //assuming that the number of tokens does not reach more than 128
	CAObjHandle retStepPtr = 0; 
	int 		numTokens = SplitOnSeparator(inputLine, ',', tokens, 128);
	int 		i = 0;
	CAObjHandle locals = 0;
	char 		*adapterName;
	
	if (numTokens < 3)
	{
		// Invalid file format.
		// raise error.
		error = -1;
		strcpy( errMsg, "Error in parsing file, invalid number of arguments");
		goto Error;
	}
	// tokens[0] == Step Name
	// tokens[1] == Step Type
	// tokens[2] == Return Value (can be empty string :"")
	// tokens[3] == Step Property
	// ...
	// tokens[n] == Step Property
	adapterName = GetAdapterName(tokens[1]);
	tsErrChk(TS_EngineNewStep(engine,
							  &errorInfo,
							  adapterName,
							  tokens[1],
							  &retStepPtr));
	tsErrChk(TS_StepSetName(retStepPtr,
							&errorInfo,
							tokens[0]));
	if ( strcmp(tokens[2],"") != 0)
	{
		tsErrChk(TS_SequenceGetLocals(seq,
		 	                          &errorInfo,
		 	                          &locals));
		ParseResultValue(locals, retStepPtr, tokens[2]);
	}
	//start processing from the 4th parameter leaving the 
	//the step name, step type and result value.
	for (i=3; i < numTokens; ++i)
	{
		ParseParameters(retStepPtr, tokens[i], &errorInfo);
		if ( errorInfo.sCode < 0)
		{
			error = errorInfo.sCode;
			goto Error;
		}
	}
	
	Error:
	DeleteMemory(tokens, numTokens);
	if ( locals )
		CA_DiscardObjHandle(locals);
	if( error < 0)
	{
		if(retStepPtr)
			CA_DiscardObjHandle(retStepPtr);
		retStepPtr = 0;
		*errorInfoPtr = errorInfo;
	}
	return retStepPtr;
}

int  Translate(CAObjHandle engine, CAObjHandle readStream, CAObjHandle *seqFile, ERRORINFO *errorInfoPtr)
{
	
	CAObjHandle 	sequenceObject;
	int 			numSteps = 0;
	char 			*seqName = "MainSequence";
	char 			buf[BUFSIZE];
	VBOOL 			isEndofStream = 0;
	char 			*tokens[10];
	CAObjHandle 	stepObject = 0;
	CAObjHandle 	propertyObjectFile = 0;
	CAObjHandle 	typeUsageList = 0;
	CAObjHandle 	stepasPropertyObject = 0;
	CAObjHandle 	propObjectFile = 0;
	char 			versionInfo[128]; //MAX_VERSION_STRING_LENGTH
	
	tsErrChk(TS_EngineNewSequence (engine, &errorInfo, &sequenceObject));
	tsErrChk(TS_SequenceSetName (sequenceObject, &errorInfo, seqName));
	tsErrChk(TS_InputStreamSetOffset(readStream, &errorInfo, (long)strlen(_header)));
	ReadTillDelim(buf, "\r\n", &readStream);//Move the stream pointer past the version info.
	tsErrChk(TS_InputStreamGetIsEndofStream(readStream, &errorInfo, &isEndofStream));
	while ( !isEndofStream  )
	{
		int 	isValidSequenceFile = 1;
		char 	inputLine[1024];
		
		memset(buf, 0, 1024);
		tsErrChk(TS_EngineLoadTypePaletteFilesEx(engine, 
												 &errorInfo,
												 TS_ConflictHandler_UseGlobalType, 
												 0));
		ReadTillDelim(buf, "\r\n", &readStream);
		StringCopyMax(inputLine, buf, 1024/*max input line size*/);
		if (strlen(buf) )
		{
			int totalTokens = SplitOnSeparator(buf, ',', tokens, sizeof(tokens)/sizeof(tokens[0])); 
			
			isValidSequenceFile = totalTokens > 3;
			if (isValidSequenceFile)
			{
				VARIANT_BOOL val;
				
				stepObject =   CommaSeparatedStepParser(engine,
														sequenceObject,
														inputLine, 
														&errorInfo);
				if(errorInfo.sCode != TS_Err_NoError)
				{										
					error = errorInfo.sCode;
					goto Error;
				}
				tsErrChk(TS_SequenceInsertStep (sequenceObject,
												&errorInfo,
												stepObject,
												numSteps++,
												TS_StepGroup_Main));
				//Attach the types to the sequence file.
				tsErrChk(TS_SeqFileAsPropertyObjectFile(*seqFile,
														&errorInfo, 
														&propertyObjectFile));
				tsErrChk(TS_PropertyObjectFileGetTypeUsageList(propertyObjectFile, 
															   &errorInfo, 
															   &typeUsageList));
				tsErrChk(TS_StepAsPropertyObject(stepObject, 
												 &errorInfo, 
												 &stepasPropertyObject));
				tsErrChk(TS_TypeUsageListAddUsedTypes(typeUsageList, 
													  &errorInfo, 
													  stepasPropertyObject, 
													  &val));
				CA_DiscardObjHandle(stepObject);
				CA_DiscardObjHandle(propertyObjectFile);
				CA_DiscardObjHandle(typeUsageList);
				CA_DiscardObjHandle(stepasPropertyObject);
			}
			DeleteMemory(tokens, totalTokens);
		}
		if (!isValidSequenceFile)
		{
			// do the error handling
			error = TS_Err_FileNotConvertableToSeqFile;
			errorInfo.sCode = TS_Err_FileNotConvertableToSeqFile;
			strcpy(errorInfo.description, "Invalid Input File.");
			goto Error;
		}
		tsErrChk(TS_InputStreamGetIsEndofStream(readStream, &errorInfo, &isEndofStream));
	}
	//Set the version property of the Sequence File.
	tsErrChk(TS_SeqFileAsPropertyObjectFile(*seqFile, 
		                                    &errorInfo,
											&propObjectFile));
	versionInfo[0] = 0;
	GetFileVersionFromHeader(readStream, 
							 versionInfo);
	if( versionInfo[0] == 0) strcpy(versionInfo, "0.0.0.0");
	tsErrChk(TS_PropertyObjectFileSetVersion(propObjectFile,
											 &errorInfo, 
											 versionInfo));
	tsErrChk(TS_SeqFileInsertSequence (*seqFile, &errorInfo, sequenceObject));
	
	Error:  
    if ( error < 0 )
    {
		if(stepObject)
			CA_DiscardObjHandle(stepObject);
		if(propertyObjectFile)
			CA_DiscardObjHandle(propertyObjectFile);
		if(typeUsageList)
			CA_DiscardObjHandle(typeUsageList);
		if(stepasPropertyObject)
			CA_DiscardObjHandle(stepasPropertyObject);
		// If an error occurred, set the error flag to cause a run-time error in TestStand.
    	*errorInfoPtr = errorInfo;
	}
	CA_DiscardObjHandle(sequenceObject);
	CA_DiscardObjHandle(propObjectFile);
    return error;
}

void GetHeaderDescription(CAObjHandle readStream, char *headerInfo)
{
	char 		*buf;
	SAFEARRAY 	*psa;
	VBOOL 		endofStream;
	int 		i = 0,size = 0;
	
	//Always reset the stream pointer to the beginning
	//This will ensure the Header will be correctly read,
	//even if there are multiple formats and each format has its own header
	tsErrChk(TS_InputStreamSetOffset(readStream, &errorInfo, 0));
	tsErrChk(TS_InputStreamGetIsEndofStream (readStream, &errorInfo, &endofStream));
	tsErrChk(TS_InputStreamGetLength(readStream, &errorInfo, &size));
	if(endofStream || size < strlen(_header))
	{
		headerInfo[0] = '\0';
		return;
	}
	tsErrChk(TS_InputStreamReadBytes(readStream, &errorInfo, (long)strlen(_header), &psa));
	SafeArrayAccessData(psa, (void**)(&buf));
	strncpy(headerInfo, buf, strlen(_header));
	headerInfo[strlen(_header)] = '\0';	 
	SafeArrayUnaccessData(psa);
	
	Error:
	if ( error < 0)
	{
		headerInfo[0] = '\0';	
	}
}

void GetFileVersionFromHeader(CAObjHandle readStream, char *versionInfo)
{
	char 		buf[128];
	SAFEARRAY 	*psa;
	VBOOL 		endofStream;
	int 		i = 0,size = 0;
	
	//Always reset the stream pointer to the beginning
	//This will ensure the Header will be correctly read,
	//even if there are multiple formats and each format has its own header
	tsErrChk(TS_InputStreamSetOffset(readStream, &errorInfo, 0));
	tsErrChk(TS_InputStreamGetIsEndofStream (readStream, &errorInfo, &endofStream));
	tsErrChk(TS_InputStreamGetLength(readStream, &errorInfo, &size));
		
	ReadTillDelim(buf, ":", &readStream);
	ReadTillDelim(buf, ":", &readStream);
	ReadTillDelim(versionInfo,"\r\n", &readStream);
	versionInfo[MAX_VERSION_STRING_LENGTH - 1] = 0;
	Error:
	if ( error < 0)
	{
		versionInfo[0] = '\0';	
	}
}
