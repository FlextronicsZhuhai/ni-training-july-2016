//TextTranslatorAPI.cpp Implementation File.
//Implements the methods defined in the <TestStand Directory>\API\DLLInterfaces\TranslatorInterface.h. 
//For more information refer to the TranslatorInterface.h under the
//<TestStand>\API\DLLInterfaces\ directory.
//Refer to Chapter 15, Sequence File Translators, in the TestStand Reference Manual 
//for more information about using and creating sequence file translators.
#include "stdafx.h"
#include "TranslatorInterface.h"
#include "TextTranslator.h"

using namespace TS;
static const char CURRENT_FILE_VERSION[] = "4.0.0.1";
static const char CURRENT_FILE_FORMAT_VERSION[] = "4.0.0.0";

/**
This Sequence File Translator translates a text file stored on the disk into a Sequence File.
The example text file has a header which contains information about the format and also regarding the 
file and fileformat version. 
The CanTranslate method reads the header information. The method compares this header with the header 
information that should be present in the file format that this supports. If it matches, 
it returns a true value which indicates that the file can be translated by this DLL.

After the header, the source file contains steps which can be translated into correspondng steps of a 
TestStand Sequence File. 
Each line contains sections seperated by commas(,). The sections are 
Step Name, Step Type, Result Value, Property1, Property2,...
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

long GetTranslatorCount()
{
	//Returns the number of translators supported.
	return (long)TranslatorCollection::GetTranslatorCollection().size();
}

void  GetExtension(long index, char* fileExtension, long maxfileExtensionLengthInBytes, TSError *error, char* errorMsg, long maxErrorMsgLengthInBytes)
{
	//return the file extension supported.
	if( index >= 0 && index < TranslatorCollection::GetTranslatorCollection().size())
	{
		Translator *translator = TranslatorCollection::GetTranslator(index, error, errorMsg, maxErrorMsgLengthInBytes);
		if (translator)
			strncpy_s(fileExtension, maxfileExtensionLengthInBytes, translator->GetInfo().fileExtension.c_str(), _TRUNCATE);
	}
	else
	{
		*error = TS_Err_IndexOutOfRange;
		strcpy_s(errorMsg, maxErrorMsgLengthInBytes, "\nInvalid translator index.\n");
	}
}

void  GetDescription(long index, char* description, long maxDescriptionLengthInBytes, TSError *error, char* errorMsg, long maxErrorMsgLengthInBytes)
{
	//Return the description describing the file format.
	if( index >= 0 && index < TranslatorCollection::GetTranslatorCollection().size())
	{
		Translator *translator = TranslatorCollection::GetTranslator(index, error, errorMsg, maxErrorMsgLengthInBytes);
		if (translator)
			strncpy_s(description, maxDescriptionLengthInBytes, translator->GetInfo().description.c_str(), _TRUNCATE);
	}
	else
	{
		*error = TS_Err_IndexOutOfRange;
		strcpy_s(errorMsg, maxErrorMsgLengthInBytes, "\nInvalid translator index.\n");
	}
}

void  TranslateToSequenceFile(long translationIndex, IDispatch *engine, IDispatch *readStream, IDispatch *sequenceFile, TSError *error, char* errorMsg, long maxErrorMsgLengthInBytes)
{
	//Make sure that the input parameters are never NULL.
	if (sequenceFile == NULL || readStream == NULL || engine == NULL)
	{
		*error = TS_Err_FileNotConvertableToSeqFile;
		strcpy_s(errorMsg, maxErrorMsgLengthInBytes, "\n Invalid Argument \n");
	}
	else
	{
		//Check to see if any of the Translators in the collection support this file format.
		try
		{
			Translator *translator = TranslatorCollection::GetTranslator(translationIndex, error, errorMsg, maxErrorMsgLengthInBytes);
			if (translator)
			{
				((TS::IEngine*)engine)->LoadTypePaletteFilesEx(ConflictHandler_UseGlobalType, 0);
				translator->Translate(engine, readStream, sequenceFile, error, errorMsg, maxErrorMsgLengthInBytes);
			}
		}
		catch(...)
		{
			//This catch block ensures that no exceptions escape form this function.
			sequenceFile = NULL;
			*error = TS::TS_Err_FileNotConvertableToSeqFile;
			strcpy_s(errorMsg, maxErrorMsgLengthInBytes, "\nError occurred while translating to a TestStand sequence file - Invalid file format.\n");
		}
	}	
}

long  CanTranslate(const char *fileExtension, IDispatch *readStream, long *translationIndex, TSError *error, char* errorMsg, long maxErrorMsgLengthInBytes)
{
	//Make sure that all the parameters are valid.
	if ( readStream == NULL )
	{
		*error = TS_Err_InvalidPointer;
		return 0;// Not found
	}
	std::string buf;
	const size_t totalTranslators = TranslatorCollection::GetTranslatorCollection().size();
	//Make sure that none of the exceptions thrown escapes from this method. Use the error parameters passed to 
	//the function to return any error conditions.
	try
	{
		for ( size_t i = 0; i < totalTranslators; i++ )
		{
			if ( TranslatorCollection::GetTranslator(i)->CanTranslate(fileExtension,
																	  (TS::InputStream*)readStream,
																	  error,
																	  errorMsg, 
																	  maxErrorMsgLengthInBytes,
																	  true))
			{
				*translationIndex = (long)i;
				return 1;//found
			}
		}
		// Now do the same thing without checking for fileExtension
		// (Notice the last parameter in the CanTranslate of Translator)
		for ( int i = 0; i < totalTranslators; i++ ) 
		{
			if ( TranslatorCollection::GetTranslator(i)->CanTranslate(fileExtension,
																	  (TS::InputStream*)readStream,
																	  error,
																	  errorMsg, 
																	  maxErrorMsgLengthInBytes,
																	  false)) // <-- don't check for fileExtension
			{
				*translationIndex = i;
				return 1;//found
			}
		}
	}
	catch(...)//Catch all exceptions
	{
		*error = TS_Err_NoError;//clear all the errors and return 0. 

		////////////////////////////////////////////////////////////////////////////////
		// ***IMPORTANT***
		// Not setting the error code will ensure that other translator DLLs get a 
		// chance for translating this file. 
		// Returning a value other than TS_Err_NoError in the error parameter translates
		// to a fatal translator-error. This will cause TestStand to stop looking for 
		// other translator DLLs and will display a failure message.

	}
	return 0;// Not found
}

void  GetFileFormatVersion(long index, const char* path, IDispatch *readStream, char *fileFormatVersion, long maxFileFormatVersionLengthInBytes, TSError *error, char *errorMsg, long maxErrorMsgLengthInBytes)
{
	std::string fileFormatVersionStr;
	fileFormatVersionStr.reserve(maxFileFormatVersionLengthInBytes+1);
	//Make sure no exception is thrown from this method.
	try 
	{
		TranslatorCollection::GetTranslator(index)->GetFileFormatVersion(fileFormatVersionStr,(TS::InputStreamPtr) readStream, error, errorMsg, maxErrorMsgLengthInBytes);
		if(*error == TS_Err_NoError)
			strncpy_s(fileFormatVersion, maxFileFormatVersionLengthInBytes, fileFormatVersionStr.c_str(),_TRUNCATE);
		else
			strncpy_s(fileFormatVersion, maxFileFormatVersionLengthInBytes, "0.0.0.0",_TRUNCATE);
	}
	catch(...)
	{
		*error = TS_Err_ValueIsInvalidOrOutOfRange;
		strcpy_s(errorMsg, maxErrorMsgLengthInBytes, "\n Error getting File Format Version \n");
		strcpy_s(fileFormatVersion, 1, "");
	}
}

void  GetFileVersion(long index, const char *path, IDispatch *readStream, char *fileVersion, long maxFileVersionLengthInBytes, TSError *error, char *errorMsg, long maxErrorMsgLengthInBytes)
{
	//Make sure no exception is thrown from this method.
	try 
	{
		std::string fileVersionStr;
		TranslatorCollection::GetTranslator(index)->GetFileVersion(fileVersionStr,(TS::InputStreamPtr) readStream, error, errorMsg, maxErrorMsgLengthInBytes);
		//make sure that the version string does not contain any whitespaces
		strncpy_s(fileVersion, maxFileVersionLengthInBytes, fileVersionStr.c_str(), _TRUNCATE);
	}
	catch(...)
	{
		*error = TS_Err_ValueIsInvalidOrOutOfRange;
		strcpy_s(errorMsg, maxErrorMsgLengthInBytes, "\n Error getting File Version \n");
		strcpy_s(fileVersion, 1, "");
	}
}

long  IsCurrentFileVersion(long index, const char *path, IDispatch *readStream, TSError *error, char *errorMsg, long maxErrorMsgLengthInBytes)
{
	const int kFileIsOlder = -1;
    const int kFileIsNewer =  1;
    const int kFileIsUptoDate = 0;
	const int kMaxVersionLength = 128;
	char version[kMaxVersionLength];
	char currentVersion[128];
	char currentVersions[4][128];
	char fileVersions[4][128];
	
	version[0] = 0;
	strcpy(currentVersion, CURRENT_FILE_VERSION);
	
	currentVersions[0][0] = 0;
	currentVersions[1][0] = 0;
	currentVersions[2][0] = 0;
	currentVersions[3][0] = 0;
	fileVersions[0][0] = 0;
	fileVersions[1][0] = 0;
	fileVersions[2][0] = 0;
	fileVersions[3][0] = 0;
	
	GetFileVersion(index, path, (TS::InputStream*)readStream, version, kMaxVersionLength, error, errorMsg, maxErrorMsgLengthInBytes);
	if (*error == TS_Err_NoError)
	{
		char* pch = NULL;
		int i = 0;
		int res = 0;  
		
		pch = strtok(currentVersion, ".");
		for(i = 0; i < 4; ++i)
		{
			if (pch != NULL)
			{
				strcpy(currentVersions[i], pch);
			}
			pch = strtok(NULL, ".");
		}
		
		pch = strtok(version, ".");
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
			if (res = atoi(fileVersions[i]) - atoi(currentVersions[i]))
			{
				break;
			}
			
		}
		if(res < 0)
			return kFileIsOlder;
		else if(res > 0)
			return kFileIsNewer;
		else
			return kFileIsUptoDate;
	}
	*error = TS_Err_NoError;
	return kFileIsNewer;
}
