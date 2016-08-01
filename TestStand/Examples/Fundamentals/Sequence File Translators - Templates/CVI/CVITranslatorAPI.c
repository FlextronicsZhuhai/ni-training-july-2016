//CVITranslatorAPI.c : Provides a skeletal implementation for the TranslatorInterface.
//For more information refer to the TranslatorInterface.h under the
//<TestStand>\API\DLLInterfaces\ directory.
//Refer to Chapter 15, Sequence File Translators, in the TestStand Reference Manual 
//for more information about using and creating sequence file translators.
#include "tsapicvi.h"
#include <cvirte.h>		
#include "tsutil.h"
#include "TranslatorInterface.h"

long __declspec(dllexport) GetTranslatorCount (void)
{
    //Return the number of File formats supported by the DLL.
	return 0;
}

void __declspec(dllexport) GetExtension (long index,
										 char *extension,
										 long maxExtensionLengthInBytes,
                            			 enum TSEnum_Error *errorCode,
                            			 char *errorMsg,
                            			 long maxErrorMsgLengthInBytes)
{
	if (extension)
		*extension = 0;
}

void __declspec(dllexport) GetDescription (long index,
										   char *description,
										   long maxDescriptionLengthInBytes,
										   enum TSEnum_Error *errorCode,
                              			   char *errorMsg,
                              			   long maxErrorMsgLengthInBytes)
{
	if (description)
		*description = 0;
}

void __declspec(dllexport) GetFileFormatVersion (long index, 
												 const char *path,
												 IDispatch *inputStream,
                               					 char *fileFormatVersion,
                               					 long maxFileFormatVersionLengthInBytes,
                               					 enum TSEnum_Error *errorCode,
                               					 char *errorMsg,
                               					 long maxErrorMsgLengthInBytes)
{
	ERRORINFO      errorInfo;
	int 		   error = 0;
    ErrMsg 		   errMsg = {'\0'};
	
	errorInfo.description[0] = 0;
	if (fileFormatVersion)
	  StringCopyMax(fileFormatVersion, "0.0.0.0", 8);
	
	Error:  
    if ( error < 0 )
    {
    	// If an error occurred, set the error parameters to pass error information to TestStand.
		//Copy the error message description into the errorMsg parameter.
		StringCopyMax(errorMsg, errorInfo.description, maxErrorMsgLengthInBytes);
    }
    *errorCode = error;
}

void __declspec(dllexport) GetFileVersion (long index, 
										   const char *path,
										   IDispatch *inputStream,
                              			   char *fileVersion,
                              			   long maxFileVersionLengthInBytes,
                              			   enum TSEnum_Error *errorCode,
                              			   char *errorMsg,
                              			   long maxErrorMsgLengthInBytes)
{
	ERRORINFO      errorInfo;
	int 		   error = 0;
    ErrMsg 		   errMsg = {'\0'};
	
	errorInfo.description[0] = 0;
	if (fileVersion)
	  StringCopyMax(fileVersion, "0.0.0.0", 8);
	
	Error:  
    if ( error < 0 )
    {
    	// If an error occurred, set the error parameters to pass error information to TestStand.
		//Copy the error message description into the errorMsg parameter.
		StringCopyMax(errorMsg, errorInfo.description, maxErrorMsgLengthInBytes);
    }
    *errorCode = error;
}

long __declspec(dllexport) IsCurrentFileVersion (long index,  
												 const char *path,
												 IDispatch *inputStream,
                                   				 enum TSEnum_Error *errorCode,
                                   				 char *errorMsg,
                                   				 long maxErrorMsgLengthInBytes)
{
	ERRORINFO      errorInfo;
	int 		   error = 0;
    ErrMsg 		   errMsg = {'\0'};

	errorInfo.description[0] = 0;
	//Get the File format version info from the file by reading the file
	//using the readStream pointer. Compare the file format version with the current 
	//File format version and return the result.
	
	Error:  
    if ( error < 0 )
    {
    	// If an error occurred, set the error parameters to pass error information to TestStand.
		//Copy the error message description into the errorMsg parameter.
		StringCopyMax(errorMsg, errorInfo.description, maxErrorMsgLengthInBytes);
    }
    *errorCode = error;
	return 0;
}

void __declspec(dllexport) TranslateToSequenceFile (long index, 
													IDispatch *engine, 
                                                    IDispatch *readStream,
                                                    IDispatch *sequenceFile,
                                                    enum TSEnum_Error *errorCode, 
                                                    char *errorMsg,
                                       				long maxErrorMsgLengthInBytes)
{
	ERRORINFO      errorInfo;
	int 		   error = 0;
    ErrMsg 		   errMsg = {'\0'};
	
	errorInfo.description[0] = 0;
	//Add code to implement the logic for translating a 
	//custom format file into a Sequence File. Use the TestStand API 
	//to create the new Sequence File. For more information on 
	//creating Custom Sequence File Translators refer to the
	//TestStand Reference Manual.
	
	Error:  
    if ( error < 0 )
    {
    	// If an error occurred, set the error parameters to pass error information to TestStand.
		//Copy the error message description into the errorMsg parameter.
		StringCopyMax(errorMsg, errorInfo.description, maxErrorMsgLengthInBytes);
    }
    *errorCode = error;
    return;
}

long __declspec(dllexport) CanTranslate (const char *extension,
										 IDispatch *inputStream,
										 long *index,
                            			 enum TSEnum_Error *errorCode,
                            			 char *errorMsg,
                            			 long maxErrorMsgLengthInBytes)
{
	ERRORINFO      errorInfo;
	int 		   error = 0;
    ErrMsg 		   errMsg = {'\0'};
	
	errorInfo.description[0] = 0;
	//Add code to implement the logic to read the header and 
	//decide whether the file can be translated.
	
	Error:  
    if ( error < 0 )
    {
		//clear all errors and return 0 in case an error occured.
		
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

