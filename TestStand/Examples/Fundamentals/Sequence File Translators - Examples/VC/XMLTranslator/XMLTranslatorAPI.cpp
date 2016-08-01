// XMLTranslatorAPI.cpp Implementation File.
// Implements the methods defined in the <TestStand Directory>\API\DLLInterfaces\TranslatorInterface.h. 
//For more information refer to the TranslatorInterface.h under the
//<TestStand>\API\DLLInterfaces\ directory.
//Refer to Chapter 15, Sequence File Translators, in the TestStand Reference Manual 
//for more information about using and creating sequence file translators.

#include "stdafx.h"
#define TESTXMLFORMATAPIEXPORT
#include "TranslatorInterface.h"
#include "XMLTranslator.h"

using namespace TS;
static const char CURRENT_FILE_VERSION[] = "4.0.0.2";
static const char CURRENT_FILE_FORMAT_VERSION[] = "4.0.0.0";

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

//Returns the number of file formats supported.
long __declspec(dllexport) GetTranslatorCount()
{
	return (long)TranslatorCollection::GetTranslatorCollection().size();
}

//Returns the extensions supported.
void __declspec(dllexport) GetExtension(long index, char* fileExtension, long maxfileExtensionLengthInBytes, TSError *error, char* errorMsg, long maxErrorMsgLengthInBytes)
{
	if(index >= 0 && index < TranslatorCollection::GetTranslatorCollection().size())
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

//Returns the description of the file format.
void __declspec(dllexport) GetDescription(long index, char* description, long maxDescriptionLengthInBytes, TSError *error, char* errorMsg, long maxErrorMsgLengthInBytes)
{
	if(index >= 0 && index < TranslatorCollection::GetTranslatorCollection().size())
	{
		Translator *translator = TranslatorCollection::GetTranslator(index,error, errorMsg, maxErrorMsgLengthInBytes);
		if (translator)
			strncpy_s(description, maxDescriptionLengthInBytes, translator->GetInfo().description.c_str(), _TRUNCATE);
	}
	else
	{
		*error = TS_Err_IndexOutOfRange;
		strcpy_s(errorMsg, maxErrorMsgLengthInBytes, "\nInvalid translator index.\n");
	}
}

//Reads from the InputStream and translates the file to a TestStand Sequence File.
void __declspec(dllexport) TranslateToSequenceFile(long translationIndex, IDispatch *engine, IDispatch *readStream, IDispatch *sequenceFile, TSError *error, char* errorMsg, long maxErrorMsgLengthInBytes)
{
	if (sequenceFile == NULL || readStream == NULL || engine == NULL)
	{
		*error = TS_Err_FileNotConvertableToSeqFile;
		strcpy_s(errorMsg, maxErrorMsgLengthInBytes, "Invalid Argument");
	}
	else
	{
		try
		{
			Translator *translator = TranslatorCollection::GetTranslator(translationIndex, error, errorMsg, maxErrorMsgLengthInBytes);
			if (translator)
			{
				((IEngine*)engine)->LoadTypePaletteFilesEx(ConflictHandler_UseGlobalType, 0);
				translator->Translate(engine, readStream, sequenceFile, error, errorMsg, maxErrorMsgLengthInBytes);
			}
		}
		catch(...)
		{
			*error = TS_Err_FileNotConvertableToSeqFile;
			strcpy_s(errorMsg, maxErrorMsgLengthInBytes ,"\nError occurred while translating to a TestStand sequence file - Invalid file format.\n");
		}
	}	
}

//Check the header of the file and check whether it matches any of the file formats.
long __declspec(dllexport) CanTranslate(const char *fileExtension, IDispatch *readStream, long *translationIndex, TSError *error, char* errorMsg, long maxErrorMsgLengthInBytes)
{
	if ( readStream == NULL )
	{
		return 0;// Not found
	}
	std::string buf;
	const size_t totalTranslators = TranslatorCollection::GetTranslatorCollection().size();
	try 
	{
		for ( size_t i = 0; i < totalTranslators; i++ )
		{
			if ( TranslatorCollection::GetTranslator(i)->CanTranslate(fileExtension,
																	 (InputStream*)readStream,
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
		for ( size_t i = 0; i < totalTranslators; i++ ) 
		{
			if ( TranslatorCollection::GetTranslator(i)->CanTranslate(fileExtension,
																	 (InputStream*)readStream,
																	  error,
																	  errorMsg, 
																	  maxErrorMsgLengthInBytes,
																	  false)) // <-- don't check for fileExtension
			{
				*translationIndex = (long)i;
				return 1;//found
			}
		}
	}
	catch(...)
	{
		*error = TS_Err_NoError;//reset the error and return 0 to indicate failure.

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

//Returns the file format version of the file.
void __declspec(dllexport) GetFileFormatVersion(long index, const char* path, IDispatch *readStream, char* fileFormatVersion, long maxFileFormatVersionLengthInBytes, TSError *error, char* errorMsg, long maxErrorMsgLengthInBytes)
{
	std::string fileFormatVersionStr;
	try
	{
		TranslatorCollection::GetTranslator(index)->GetFileFormatVersion(fileFormatVersionStr, (InputStreamPtr)readStream, error, errorMsg, maxErrorMsgLengthInBytes);
		strncpy_s(fileFormatVersion, maxFileFormatVersionLengthInBytes, fileFormatVersionStr.c_str(), _TRUNCATE);
	}
	catch(...)
	{
		*error = TS_Err_ValueIsInvalidOrOutOfRange;
		strcpy_s(errorMsg, maxErrorMsgLengthInBytes, "\n Error getting File Format Version.\n");
		strcpy_s(fileFormatVersion, 1, "");
	}
}

//Returns the file version of the file.
void __declspec(dllexport) GetFileVersion(long index, const char* path, IDispatch *readStream, char* fileVersion, long maxFileVersionLengthInBytes, TSError *error, char* errorMsg, long maxErrorMsgLengthInBytes)
{
	std::string fileVersionStr;
	try
	{
		TranslatorCollection::GetTranslator(index)->GetFileVersion(fileVersionStr, (InputStreamPtr)readStream, error, errorMsg, maxErrorMsgLengthInBytes);
		strncpy_s(fileVersion, maxFileVersionLengthInBytes, fileVersionStr.c_str(), _TRUNCATE);
	}
	catch(...)
	{
		*error = TS_Err_ValueIsInvalidOrOutOfRange;
		strcpy_s(errorMsg, maxErrorMsgLengthInBytes, "\n Error getting File Version.\n");
		strcpy_s(fileVersion, 1, "");
	}
}

//Compares the file version with the current version.
long __declspec(dllexport) IsCurrentFileVersion(long index, const char* path, IDispatch *readStream, TSError *error, char* errorMsg, long maxErrorMsgLengthInBytes)
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
	
	GetFileVersion(index, path, readStream, version, kMaxVersionLength, error, errorMsg, maxErrorMsgLengthInBytes);
	if( *error == TS_Err_NoError)
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

	*error = TS_Err_NoError; // reset the error, Error implies new file.
	return kFileIsNewer;
}
