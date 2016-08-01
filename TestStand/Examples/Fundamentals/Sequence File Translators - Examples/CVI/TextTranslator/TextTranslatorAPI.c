//This file implements the methods necessary for creating a SequenceFile
//translator DLL. 
//For more information refer to the TranslatorInterface.h under the
//<TestStand>\API\DLLInterfaces\ directory.
//Refer to Chapter 15, Sequence File Translators, in the TestStand Reference Manual 
//for more information about using and creating sequence file translators.
#include "tsutil.h"
#include "TranslatorInterface.h"
#include "TextTranslator.h"

/**
This Sequence File Translator translates a text file stored on the disk into a Sequence File.
The example text file has a header which contains information about the format and also regarding the 
file and fileformat version. 
The CanTranslate method reads this header information. The method compares this header with the header 
information that should be present in the file format that this supports. If it matches, 
it returns a true value which indicates that the file can be translated by this DLL.

After the header, the source file contains steps which can be translated into corresponding steps of a 
TestStand Sequence File. 
Each line contains sections seperated by commas(,). The sections are 
Step Name, Step Type, Result Value, Property1, Property2,....
Each step should have a step name and a step type. The Result value can be an empty string.
There can be 1 or more properties that can be set on the specified step.
Each step in the file is delimited by the newline character.

A valid step in the text file can be as follows
Display Graph,DisplayGraph,RMSValue:number=RMSValue,ACValue:number=2
where 
Display Graph is the step name 
DisplayGraph  is the step type 
RMSValue:number=localRMSValue indicates that the step returns a numeric value called RMSValue
                         which needs to be stored in the variable localRMSValue.
ACValue:number=2 indicates that the numeric value ACValue on the step needs to be set to 2.

There can be any number of such steps in the file. 
The TranslateToSequenceFile method reads each line from the file and breaks them down 
into the above components and constructs the SequenceFile steps from them.

*/
const char 			CURRENT_FILE_VERSION[] = "4.0.0.6" ;
const int 			NO_OF_TYPES_SUPPORTED = 1;
const char 			_fileextension_supported[] = "cvitf";
const char 			_description[] = "CVI Example - Text Format";
const char 			_header[] = "CVI Sample Test Description File";
const int 			MAX_VERSION_STRING_LENGTH = 128;
int 				numSteps = 0; 

//Returns the number of file formats supported.
long __declspec(dllexport) GetTranslatorCount (void)
{
    return NO_OF_TYPES_SUPPORTED;
}

//Returns the extension of the file format.
void __declspec(dllexport) GetExtension (long index, char *fileExtension, long maxfileExtensionLengthInBytes, enum TSEnum_Error *errorCode, char *errorMsg, long maxErrorMsgLengthInBytes)
{
	if(index >= 0 && index < GetTranslatorCount ())
	{
		if (fileExtension)
			StringCopyMax(fileExtension, _fileextension_supported, maxfileExtensionLengthInBytes);
	}
	else
	{
		*errorCode = TS_Err_IndexOutOfRange;
	}
}

//Returns the description of the file format.
void __declspec(dllexport) GetDescription (long index, char *description, long maxDescriptionLengthInBytes, enum TSEnum_Error *errorCode, char *errorMsg, long maxErrorMsgLengthInBytes)
{
	if(index >= 0 && index < GetTranslatorCount())
	{
		if (description)
			StringCopyMax( description, _description, maxDescriptionLengthInBytes);
	}
	else
	{
		*errorCode = TS_Err_IndexOutOfRange;
	}
}

//Returns the file format version.
void __declspec(dllexport) GetFileFormatVersion (long index, const char *path, IDispatch *inputStream, char *fileFormatVersion, long maxFileFormatVersionLengthInBytes, enum TSEnum_Error *errorCode, char *errorMsg, long maxErrorMsgLengthInBytes)
{
	ERRORINFO 		errorInfo;
	int 			error = 0;
    ErrMsg 			errMsg = {'\0'};
    char 			buf[1024]; 
	char 			versionString[128];//Max Version String Length
    CAObjHandle 	readStream;
	
	CA_CreateObjHandleFromIDispatch(inputStream   ,0 /* don't add ref */, &readStream);
	ReadTillDelim(buf, ":", &readStream);
	ReadTillDelim(versionString,":", &readStream);
	versionString[MAX_VERSION_STRING_LENGTH - 1] = 0;
	if (fileFormatVersion)
		StringCopyMax(fileFormatVersion, versionString, maxFileFormatVersionLengthInBytes);    
}

//Returns the file version.
void __declspec(dllexport) GetFileVersion (long index, const char *path, IDispatch *inputStream, char *fileVersion, long maxFileVersionLengthInBytes, enum TSEnum_Error *errorCode, char *errorMsg, long maxErrorMsgLengthInBytes)
{
	ERRORINFO 		errorInfo;
	int 			error = 0;
    ErrMsg 			errMsg = {'\0'};
    char 			buf[1024];
    char 			versionString[128];//Max Version String Length
    CAObjHandle 	readStream;
	
	CA_CreateObjHandleFromIDispatch(inputStream   ,0 /* don't add ref */, &readStream);
	ReadTillDelim(buf, ":", &readStream);
	ReadTillDelim(buf, ":", &readStream);
	ReadTillDelim(versionString,"\r\n", &readStream);
	versionString[MAX_VERSION_STRING_LENGTH - 1] = 0;
	if (fileVersion)
		StringCopyMax(fileVersion, versionString, maxFileVersionLengthInBytes);

	
}

//Compare the file version with the current file version.
long __declspec(dllexport) IsCurrentFileVersion (long index, const char *path, IDispatch *inputStream, enum TSEnum_Error *errorCode, char *errorMsg, long maxErrorMsgLengthInBytes)
{
	const int kFileIsOlder = -1;
	const int kFileIsNewer = 1;
	const int kFileIsUptoDate = 0;
	char fileVersion[128];//MAX_VERSION_STRING_LENGTH
	char currentVersion[128];
	char currentVersions[4][128];
	char fileVersions[4][128];
	
	fileVersion[0] = 0;
	strcpy(currentVersion, CURRENT_FILE_VERSION);
	
	currentVersions[0][0] = 0;
	currentVersions[1][0] = 0;
	currentVersions[2][0] = 0;
	currentVersions[3][0] = 0;
	fileVersions[0][0] = 0;
	fileVersions[1][0] = 0;
	fileVersions[2][0] = 0;
	fileVersions[3][0] = 0;
	
	GetFileVersion(index, 
				   path, 
				   inputStream, 
				   fileVersion,
				   MAX_VERSION_STRING_LENGTH,
				   errorCode, 
				   errorMsg, 
				   maxErrorMsgLengthInBytes);
	if ( *errorCode == 0)
	{	
		char* pch = NULL;
		int i = 0;
		int result = 0;  
		
		pch = strtok(currentVersion, ".");
		for(i = 0; i < 4; ++i)
		{
			if (pch != NULL)
			{
				strcpy(currentVersions[i], pch);
			}
			pch = strtok(NULL, ".");
		}
		
		pch = strtok(fileVersion, ".");
		for(i = 0; i < 4; ++i)
		{
			if (pch != NULL)
			{
				strcpy(fileVersions[i], pch);
			}
			pch = strtok(NULL, ".");
		}
		
		for(i = 0; i < 4; ++i)
		{
			if (result = atoi(fileVersions[i]) - atoi(currentVersions[i]))
			{
				break;
			}
			
		}
		if( result < 0)
			return kFileIsOlder;
		else if(result > 0)
			return kFileIsNewer;
		else
			return kFileIsUptoDate;
	}	
	return kFileIsNewer;
}

//Read the file and translate the file to a TestStand SequenceFile.
void __declspec(dllexport) TranslateToSequenceFile (long index, IDispatch *enginePtr, IDispatch *readStreamPtr, IDispatch *sequenceFilePtr, enum TSEnum_Error *errorCode, char *errorMsg, long maxErrorMsgLengthInBytes)
{
	ERRORINFO      errorInfo;
	int 		   error = 0;
    ErrMsg 		   errMsg = {'\0'};
	VBOOL          isEndofStream = 0;
	CAObjHandle    stepObject;
	TSObj_Engine   engine;
	TSObj_SeqFile  sequenceFile;
	CAObjHandle    readStream;
	
	CA_CreateObjHandleFromIDispatch(enginePtr       ,0 /* don't add ref */, &engine);
	CA_CreateObjHandleFromIDispatch(sequenceFilePtr,0 /* don't add ref */, &sequenceFile);
	CA_CreateObjHandleFromIDispatch(readStreamPtr   ,0 /* don't add ref */, &readStream);
	error = Translate(engine, readStream, &sequenceFile, &errorInfo);
	
	Error:  
    if ( error < 0 )
    {
		// If an error occurred, set the error flag to cause a run-time error in TestStand.
    	StringCopyMax(errorMsg, errorInfo.description, maxErrorMsgLengthInBytes);
    }
    *errorCode = error;
    return;
}

//Read the header info and check whether it matches with any of 
//the supported file formats.
long __declspec(dllexport) CanTranslate (const char *fileExtension, IDispatch *inputStream, long *index, enum TSEnum_Error *errorCode, char *errorMsg, long maxErrorMsgLengthInBytes)
{
	ERRORINFO 		errorInfo;
	int 			error = 0;
    ErrMsg 			errMsg = {'\0'};
	long 			canTranslate = 0;
	char 			*headerInfo = (char*)malloc(sizeof(char)*1024);
	CAObjHandle 	readStream;
	
	errorInfo.description[0] = '\0';
	headerInfo[0]= '\0';
	CA_CreateObjHandleFromIDispatch(inputStream   ,0 /* don't add ref */, &readStream);
	GetHeaderDescription(readStream, headerInfo);
	if (!strncmp(headerInfo, _header, strlen(_header))) 
	{
	   *index = 0;
	   canTranslate = 1;
	}
	
	Error:  
    if ( error < 0 )
    {
		canTranslate = 0;//set canTranslate to 0 to indicate failure.
		
		////////////////////////////////////////////////////////////////////////////////
		// ***IMPORTANT***
		// Not setting the error code will ensure that other translator DLLs get a 
		// chance for translating this file. 
		// Returning a value other than TS_Err_NoError in the error parameter translates
		// to a fatal translator-error. This will cause TestStand to stop looking for 
		// other translator DLLs and will display a failure message.
    }
    free(headerInfo); 
	*errorCode = error;
	return canTranslate;
}
