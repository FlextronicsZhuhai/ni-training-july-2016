//This file implements the methods necessary for creating a SequenceFile
//translator DLL. 
//For more information refer to the TranslatorInterface.h under the
//<TestStand>\API\DLLInterfaces\ directory.
//Refer to Chapter 15, Sequence File Translators, in the TestStand Reference Manual 
//for more information about using and creating sequence file translators.

#include "tsapicvi.h"
#include <cvirte.h>		
#include "tsutil.h"
#include "TranslatorInterface.h"
#include "XMLTranslator.h"
#include "XMLParser.h"

/**
This Sequence File Translator translates a xml file stored on the disk into a Sequence File.
The example xml file has a header node which contains information about the format and also regarding the 
file and fileformat version. 
The CanTranslate method reads this header information. The method compares this header with the header 
information that should be present in the file format that this supports. If it matches, 
it returns a true value which indicates that the file can be translated by this DLL.

After the header node, the source file contains steps which can be translated into correspondng steps of a 
TestStand Sequence File. 
Each step tag has the following attributes and child nodes, 
name attribute which gives the step name,
type attribute which defines the step type,
Data child node which contains information regarding the step properties and 
an optional Result node which contains information about the return value of the step.
A valid step in the example file can be as follows
<Step name="Display Graph" type="DISPLAYGRAPH">
			<Data dataProperty="ACValue" type = "number">
				<Value>
					2
				</Value>
			</Data>
		<Result dataProperty="RMSValue" value="RMSValue" type="number"/>
</Step>
There can be any number of such steps in the file. 
The TranslateToSequenceFile method reads each node from the file and 
constructs the SequenceFile steps from them.
*/
const int 	NO_OF_TYPES_SUPPORTED = 1;
const char 	_fileextension_supported[] = "xml";
const char 	_description[] = "CVI Example - XML Format";
const char 	_header[] = "CVI Sample Test Description File";
const char 	CURRENT_FILE_VERSION[] = "4.0.0.3";
const char 	CURRENT_FILE_FORMAT_VERSION[] = "4.0.0.0";
const int 	MAX_VERSION_STRING_LENGTH = 128;
int 		numSteps = 0; 

//Returns the number of file formats supported.
long __declspec(dllexport) GetTranslatorCount (void)
{
    return NO_OF_TYPES_SUPPORTED;
}

//Returns the extension of the file format.
void __declspec(dllexport) GetExtension (long index, char *fileExtension, long maxFileExtensionLengthInBytes, enum TSEnum_Error *errorCode, char *errorMsg, long maxErrorMsgLengthInBytes)
{
	if(index >= 0 && index < GetTranslatorCount ())
	{	
		if (fileExtension)
			StringCopyMax(fileExtension, _fileextension_supported, maxFileExtensionLengthInBytes);
	}
	else
	{
		*errorCode = TS_Err_IndexOutOfRange;
	}
}

//Returns the description of the file format.
void __declspec(dllexport) GetDescription (long index, char *description, long maxDescriptionLengthInBytes, enum TSEnum_Error *errorCode, char *errorMsg, long maxErrorMsgLengthInBytes)
{
	if(index >= 0 && index < GetTranslatorCount ())
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
	CAObjHandle 	readStream;
	char 			fileFormatVersionString[128]; //MAX_VERSION_STRING_LENGTH
	
	errorInfo.description[0] ='\0';
	errChk(CA_CreateObjHandleFromIDispatch(inputStream  ,0 /* don't add ref */, &readStream));
	GetFileFormatVersionFromHeader(readStream, fileFormatVersionString, &errorInfo);
	fileFormatVersion[MAX_VERSION_STRING_LENGTH - 1] = '\0';
	StringCopyMax( fileFormatVersion, fileFormatVersionString, maxFileFormatVersionLengthInBytes);
	
	Error:
	if ( error < 0 )
	{
		fileFormatVersion = '\0';
		StringCopyMax(errorMsg, errorInfo.description, maxErrorMsgLengthInBytes);
		*errorCode = errorInfo.sCode;
	}    
}

//Returns the file version.
void __declspec(dllexport) GetFileVersion (long index, const char *path, IDispatch *inputStream, char *fileVersion, long maxFileVersionLengthInBytes, enum TSEnum_Error *errorCode, char *errorMsg, long maxErrorMsgLengthInBytes)
{
	ERRORINFO 		errorInfo;
	int 			error = 0;
    ErrMsg 			errMsg = {'\0'};
	CAObjHandle 	readStream;
	char 			fileVersionString[128];//MAX_VERSION_STRING_LENGTH 

	errorInfo.description[0] ='\0';
	errChk(CA_CreateObjHandleFromIDispatch(inputStream  ,0 /* don't add ref */, &readStream));
	GetFileVersionFromHeader(readStream, fileVersionString, &errorInfo);
	fileVersion[MAX_VERSION_STRING_LENGTH - 1] = '\0';
	StringCopyMax( fileVersion, fileVersionString, maxFileVersionLengthInBytes);
	
	Error:
	if ( errorInfo.sCode < 0 )
	{
		fileVersion = '\0';
		StringCopyMax(errorMsg, errorInfo.description, maxErrorMsgLengthInBytes);
		*errorCode = errorInfo.sCode;
	}
}

//Compare the file version with the current file version.
long __declspec(dllexport) IsCurrentFileVersion (long index, const char *path, IDispatch *inputStream, enum TSEnum_Error *errorCode, char *errMsg, long maxErrorMsgLengthInBytes)
{
	const int kFileIsOlder = -1;
	const int kFileIsNewer = 1;
	const int kFileIsUptoDate = 0;
	char fileVersion[128]; //MAX_VERSION_STRING_LENGTH
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
				   errMsg, 
				   maxErrorMsgLengthInBytes);
	if( *errorCode == 0)
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
	errChk(Translate(engine, readStream, &sequenceFile, &errorInfo));
	
	Error:  
    if ( error < 0 )
    {
    	// If an error occurred, set the error flag to cause a run-time error in TestStand.
    	StringCopyMax(errorMsg, errorInfo.description, maxErrorMsgLengthInBytes);
    }
    *errorCode = error;
    return;
}

// Read the header info and check whether it matches with any of the supported 
// file formats. Returns  1 if can translate, 0 if cannot translate item.
long __declspec(dllexport) CanTranslate (const char *fileExtension, IDispatch *inputStream, long *index, enum TSEnum_Error *errorCode, char *errorMsg, long maxErrorMsgLengthInBytes)
{	
	ERRORINFO 		errorInfo;
	int 			error = 0;
    ErrMsg 			errMsg = {'\0'};
	CAObjHandle 	readStream;
	long 			canTranslate = 0;
	char 			*headerInfo = malloc(sizeof(char)*(strlen(_header) + 2 )); 

	errorInfo.description[0] ='\0';
	errChk(CA_CreateObjHandleFromIDispatch(inputStream  ,0 /* don't add ref */, &readStream));
	GetHeader(readStream, headerInfo, &errorInfo);
	if (!strncmp(headerInfo, _header, strlen(_header)))
	{
	   *index = 0;
	   canTranslate = 1;
	 }
	
	Error:  
    if ( errorInfo.sCode < 0 )
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
	return canTranslate;
}

