//VCTranslatorAPI.cpp : Provides a skeletal implementation for the TranslatorInterface.
//For more information refer to the TranslatorInterface.h under the
//<TestStand>\API\DLLInterfaces\ directory.
//Refer to Chapter 15, Sequence File Translators, in the TestStand Reference Manual 
//for more information about using and creating sequence file translators.
#include "stdafx.h"
#include "TranslatorInterface.h"

long  __declspec(dllexport) GetTranslatorCount()
{
	//returns the number of file formats supported by the DLL.
	return 1;
}

void  __declspec(dllexport) GetExtension(long index, char *extension, long maxExtensionLengthInBytes, TS::TSError *error, char *errorMsg, long maxErrorMsgLengthInBytes)
{
	strncpy(extension, "vctf", maxExtensionLengthInBytes) ;
}

void  __declspec(dllexport)GetDescription(long index, char* description, long maxDescriptionLengthInBytes, TS::TSError *error, char* errorMsg, long maxErrorMsgLengthInBytes)
{
	strncpy(description, "VC Template Format", maxDescriptionLengthInBytes);
}

void __declspec(dllexport)TranslateToSequenceFile(long index, IDispatch *engine, IDispatch *inputStream, IDispatch *sequenceFile, TS::TSError *errorCode, char *errorMsg, long maxErrorMsgLengthInBytes)
{
	try
	{
	//add code to implement the logic for translating a 
	//custom format file into a Sequence File. Use the TestStand API 
	//to create the new Sequence File.
	sequenceFile = NULL;
	}
	catch(...)
	{
		//catch all exceptions and use the error parameters to 
		//to pass the error information back to TestStand.
		*errorCode = TS::TS_Err_NoError; 
	}
}

long  __declspec(dllexport) CanTranslate(const char *extension, IDispatch *readStream, long *translationIndex, TS::TSError *error, char *errorMsg, long maxErrorMsgLengthInBytes)
{
	try
	{
	//add code implement the logic to read the header and 
	//decide whether the file can be translated. 
	}
	catch(...)
	{
		//catch all exceptions and return 0.

		////////////////////////////////////////////////////////////////////////////////
		// ***IMPORTANT***
		// Not setting the error code will ensure that other translator DLLs get a 
		// chance for translating this file. 
		// Returning a value other than TS_Err_NoError in the error parameter translates
		// to a fatal translator-error. This will cause TestStand to stop looking for 
		// other translator DLLs and will display a failure message.
	}
	return 0;
}

void   __declspec(dllexport) GetFileFormatVersion(long translatorIndex, const char *path, IDispatch *readStream, char *fileFormatVersion, long maxFileFormatVersionLengthInBytes, TS::TSError *error, char *errorMsg, long maxErrorMsgLengthInBytes)
{
	try
	{
	//return the file format version supported by the DLL.
	}
	catch(...)
	{
		//catch all exceptions and set the version to the default string
		// "".
	}
	strcpy(fileFormatVersion, "");
}

void   __declspec(dllexport) GetFileVersion(long translatorIndex, const char *path, IDispatch *readStream, char *fileVersion, long maxFileVersionLengthInBytes, TS::TSError *error, char *errorMsg, long maxErrorMsgLengthInBytes)
{
	try
	{
	//return the file version supported by the DLL.
	}
	catch(...)
	{
		//catch all exceptions and set the version to the default string
		// "".
	}
	strcpy(fileVersion, "");
}

long __declspec(dllexport)IsCurrentFileVersion(long translatorIndex, const char *path, IDispatch *readStream, TS::TSError *error, char *errorMsg, long maxErrorMsgLengthInBytes)
{
	try
	{
	//Get the File format version info from the file by reading the file
	//using the readStream pointer. Compare the file format version with the current 
	//File format version and return the result.
	}
	catch(...)
	{
		//use the error parameters to indicate error to TestStand.
	}
		return 0;
}


