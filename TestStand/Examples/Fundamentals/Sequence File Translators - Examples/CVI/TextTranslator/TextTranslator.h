#include "tsapicvi.h"

extern const char 			CURRENT_FILE_VERSION[] ;
extern const int 			NO_OF_TYPES_SUPPORTED;
extern const char 			_fileextension_supported[];
extern const char 			_description[];
extern const char 			_header[];
extern const int 			MAX_VERSION_STRING_LENGTH;

int  Translate(CAObjHandle engine, 
			   CAObjHandle readStream, 
			   CAObjHandle *seqFile, 
			   ERRORINFO *errorInfo);

void DeleteMemory(char** memPtr,
				  const int count);

void ReadTillDelim(char* buffer,
				   char* delim,
				   CAObjHandle *readStreamPtr); 

int SplitOnSeparator(char* inputString,
					 const char separator,
					 char **tokens,
					 const int maxTokens);

CAObjHandle CommaSeparatedStepParser(CAObjHandle engine,
									 CAObjHandle sequence,
									 char *inputLine, 
									 ERRORINFO *errorInfo);

void GetHeaderDescription(CAObjHandle inputStream,
						  char *headerInfo);

void GetFileVersionFromHeader(CAObjHandle readStream, 
						  	  char *versionInfo);


