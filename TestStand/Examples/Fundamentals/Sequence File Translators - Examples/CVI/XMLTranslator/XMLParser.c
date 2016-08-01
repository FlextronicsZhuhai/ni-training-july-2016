#include "tsutil.h"
#include <cvirte.h>		
#include "tsapicvi.h"
#include "msxmldom.h"  
extern const char _header[];

long LoadFile(CAObjHandle readStream, MSXMLObj_IXMLDOMDocument *rootElement, ERRORINFO *errorInfoPtr)
{
	int 		error = 0;
    ErrMsg 		errMsg = {'\0'};
	SAFEARRAY 	*psa;
	VBOOL 		endofStream;
	long 		numBytes ;
	VBOOL 		isSuccessful = 0;
	ERRORINFO 	errorInfo;
	char 		*buffer = "";
	
	tsErrChk(TS_InputStreamSetOffset(readStream, &errorInfo, 0));
	tsErrChk(TS_InputStreamGetLength(readStream, &errorInfo, &numBytes));
	tsErrChk(TS_InputStreamGetIsEndofStream (readStream, &errorInfo, &endofStream));
	if ( !endofStream )
	{
		char* ch; 
		buffer = (char*) malloc(numBytes*sizeof(char) + 1);
		
		tsErrChk(TS_InputStreamReadBytes( readStream, &errorInfo, numBytes, &psa));
		SafeArrayAccessData(psa, (void**)(&ch));
		strncpy(buffer, ch, numBytes);
		buffer[numBytes] = '\0';
		SafeArrayUnaccessData(psa);
		errChk(MSXML_NewDOMDocumentIXMLDOMDocument (NULL,
                                              0,
                                              0,
                                              0,
                                              rootElement));
        errChk(MSXML_IXMLDOMDocumentloadXML (*rootElement,
                                             &errorInfo,
                                             buffer,
                                             &isSuccessful));
    }
	
	Error:  
    if ( error < 0 )
    {
    	// If an error occurred, populate the error information into the parameter passed.
    	*errorInfoPtr = errorInfo;
    }
	free(buffer);
    return isSuccessful;
}

void GetStepList(MSXMLObj_IXMLDOMDocument rootElement, MSXMLObj_IXMLDOMNodeList* stepList, ERRORINFO *errorInfo)
{
	int 						error = 0;
	ErrMsg 						errMsg = {'\0'};
	MSXMLObj_IXMLDOMNodeList 	childList;
	MSXMLObj_IXMLDOMNode     	fileNode, TestDescriptionNode;
	MSXMLObj_IXMLDOMNodeList 	sequenceList;
	MSXMLObj_IXMLDOMNode     	sequenceNode;
	
	errChk(MSXML_IXMLDOMDocumentGetchildNodes(rootElement,
									   errorInfo, 
									   &childList));
	errChk(MSXML_IXMLDOMNodeListGetitem(childList, 
								 		errorInfo, 
								 		1,
								 		&fileNode));
	errChk(MSXML_IXMLDOMNodeGetchildNodes(fileNode,
									   	  errorInfo, 
									   	  &sequenceList));
	errChk(MSXML_IXMLDOMNodeListGetitem(sequenceList, 
		                         		errorInfo, 
								 		1,
								 		&TestDescriptionNode));
	errChk(MSXML_IXMLDOMNodeGetchildNodes(TestDescriptionNode,
									   	  errorInfo, 
									   	  &sequenceList));
	errChk(MSXML_IXMLDOMNodeListGetitem(sequenceList, 
		                         		errorInfo, 
								 		0,
								 		&sequenceNode));
	errChk(MSXML_IXMLDOMNodeGetchildNodes(sequenceNode,
									   	  errorInfo, 
									   	  stepList));
	
	Error:
	CA_DiscardObjHandle(childList);
	CA_DiscardObjHandle(fileNode);
	CA_DiscardObjHandle(TestDescriptionNode);
	CA_DiscardObjHandle(sequenceList);
	CA_DiscardObjHandle(sequenceNode);
	if ( error < 0 )
	{
		*stepList = 0;
	}
}

void GetHeader(CAObjHandle readStream, char *headerString, ERRORINFO *errorInfo)
{
	MSXMLObj_IXMLDOMDocument 		rootElement;
	MSXMLObj_IXMLDOMNodeList 		childList, fileTag;
	MSXMLObj_IXMLDOMNode     		TestDescriptionNode, HeaderNode, headerDescription;
	MSXMLObj_IXMLDOMNamedNodeMap 	headerAttributes; 
	int 							error = 0;
	char 							*headerStr;
	
	if( !LoadFile(readStream, &rootElement, errorInfo))
	{
		 strcpy(headerString, "");
		 return;
	}
	errChk(MSXML_IXMLDOMDocumentGetchildNodes(rootElement,
									   errorInfo, 
									   &childList));
	errChk(MSXML_IXMLDOMNodeListGetitem(childList, 
								 		errorInfo, 
								 		1,
								 		&TestDescriptionNode));
	errChk(MSXML_IXMLDOMNodeGetchildNodes(TestDescriptionNode,
									   	  errorInfo, 
									   	  &fileTag));
	errChk(MSXML_IXMLDOMNodeListGetitem(fileTag, 
		                         		errorInfo, 
								 		0,
								 		&HeaderNode));
	errChk(MSXML_IXMLDOMNodeGetattributes(HeaderNode, 
										  errorInfo, 
										  &headerAttributes)); 
	errChk(MSXML_IXMLDOMNamedNodeMapgetNamedItem(headerAttributes, 
												 errorInfo, 
												 "description", 
												 &headerDescription));
	errChk(	MSXML_IXMLDOMNodeGettext(headerDescription, 
									 errorInfo, 
									 &headerStr));
	
	StringCopyMax(headerString, headerStr, strlen(_header)+1);
    
	Error:
	if(rootElement)
		CA_DiscardObjHandle(rootElement);
	if(childList)
		CA_DiscardObjHandle(childList);
	if(fileTag)
		CA_DiscardObjHandle(fileTag);
	if(TestDescriptionNode)
		CA_DiscardObjHandle(TestDescriptionNode);
	if(HeaderNode)
		CA_DiscardObjHandle(HeaderNode);
	if(headerDescription)
		CA_DiscardObjHandle(headerDescription);
	if(headerAttributes)
		CA_DiscardObjHandle(headerAttributes);
	if (error < 0)
	{
		headerString = "";	
	}
	return;
}

void GetFileVersionFromHeader(CAObjHandle readStream, char *fileVersionString, ERRORINFO *errorInfoPtr)
{
	MSXMLObj_IXMLDOMDocument 		rootElement;
	MSXMLObj_IXMLDOMNodeList 		childList, fileTag;
	MSXMLObj_IXMLDOMNode     		TestDescriptionNode, HeaderNode, fileVersion;
	MSXMLObj_IXMLDOMNamedNodeMap 	headerAttributes; 
	int 							error = 0;
	ERRORINFO 						errorInfo;
	char 							*versionStr;
	
	LoadFile(readStream, &rootElement, &errorInfo);
	errChk(MSXML_IXMLDOMDocumentGetchildNodes(rootElement,
									   &errorInfo, 
									   &childList));
	errChk(MSXML_IXMLDOMNodeListGetitem(childList, 
								 		&errorInfo, 
								 		1,
								 		&TestDescriptionNode));
	errChk(MSXML_IXMLDOMNodeGetchildNodes(TestDescriptionNode,
									   	  &errorInfo, 
									   	  &fileTag));
	errChk(MSXML_IXMLDOMNodeListGetitem(fileTag, 
		                         		&errorInfo, 
								 		0,
								 		&HeaderNode));
	errChk(MSXML_IXMLDOMNodeGetattributes(HeaderNode, 
										  &errorInfo, 
										  &headerAttributes)); 
	errChk(MSXML_IXMLDOMNamedNodeMapgetNamedItem(headerAttributes, 
												 &errorInfo, 
												 "fileversion", 
												 &fileVersion));
	errChk(	MSXML_IXMLDOMNodeGettext(fileVersion, 
									 &errorInfo, 
									 &versionStr));
	strcpy(fileVersionString, versionStr);
    						 		
	Error:
	CA_DiscardObjHandle(rootElement);
	CA_DiscardObjHandle(childList);
	CA_DiscardObjHandle(fileTag);
	CA_DiscardObjHandle(TestDescriptionNode);
	CA_DiscardObjHandle(HeaderNode);
	CA_DiscardObjHandle(fileVersion);
	CA_DiscardObjHandle(headerAttributes);
	*errorInfoPtr = errorInfo; 
	if (error < 0)
	{
		fileVersionString = "";	
	}
	return;
}

void GetFileFormatVersionFromHeader(CAObjHandle readStream, char *fileFormatVersionString, ERRORINFO *errorInfo)
{
	MSXMLObj_IXMLDOMDocument 		rootElement;
	MSXMLObj_IXMLDOMNodeList 		childList, fileTag;
	MSXMLObj_IXMLDOMNode     		TestDescriptionNode, HeaderNode, fileFormatVersion;
	MSXMLObj_IXMLDOMNamedNodeMap 	headerAttributes; 
	int 							error = 0;
	char 							*versionStr;
	
	LoadFile(readStream, &rootElement, errorInfo);
	errChk(MSXML_IXMLDOMDocumentGetchildNodes(rootElement,
									   errorInfo, 
									   &childList));
	errChk(MSXML_IXMLDOMNodeListGetitem(childList, 
								 		errorInfo, 
								 		1,
								 		&TestDescriptionNode));
	errChk(MSXML_IXMLDOMNodeGetchildNodes(TestDescriptionNode,
									   	  errorInfo, 
									   	  &fileTag));
	errChk(MSXML_IXMLDOMNodeListGetitem(fileTag, 
		                         		errorInfo, 
								 		0,
								 		&HeaderNode));
	errChk(MSXML_IXMLDOMNodeGetattributes(HeaderNode, 
										  errorInfo, 
										  &headerAttributes)); 
	errChk(MSXML_IXMLDOMNamedNodeMapgetNamedItem(headerAttributes, 
												 errorInfo, 
												 "fileformatversion", 
												 &fileFormatVersion));
	errChk(	MSXML_IXMLDOMNodeGettext(fileFormatVersion, 
									 errorInfo, 
									 &versionStr));
	strcpy(fileFormatVersionString, versionStr);
    						 		
	Error:
	CA_DiscardObjHandle(rootElement);
	CA_DiscardObjHandle(childList);
	CA_DiscardObjHandle(fileTag);
	CA_DiscardObjHandle(TestDescriptionNode);
	CA_DiscardObjHandle(HeaderNode);
	CA_DiscardObjHandle(fileFormatVersion);
	CA_DiscardObjHandle(headerAttributes);
	if (error < 0)
	{
		
		fileFormatVersionString = "";	
	}
	return;
}

char* GetStepType(CAObjHandle stepPtr, ERRORINFO *errorInfo)
{
	int 							error = 0;
	ErrMsg 							errMsg = {'\0'};
	MSXMLObj_IXMLDOMNamedNodeMap 	stepAttributes;
	MSXMLObj_IXMLDOMNode    		stepType;
	char 							*type;
	
	errChk(MSXML_IXMLDOMNodeGetattributes(stepPtr, 
										  errorInfo, 
										  &stepAttributes)); 
	errChk(MSXML_IXMLDOMNamedNodeMapgetNamedItem(stepAttributes, 
												 errorInfo, 
												 "type", 
												 &stepType));
	errChk(	MSXML_IXMLDOMNodeGettext(stepType, 
									 errorInfo, 
									 &type));
										
	Error:
	if ( error < 0 )
	{	
	  type = NULL; 
	}
	CA_DiscardObjHandle(stepAttributes);
	CA_DiscardObjHandle(stepType);
	return type;
}

char* GetStepName(CAObjHandle stepPtr, ERRORINFO *errorInfo)
{
	
	int 							error = 0;
	ErrMsg 							errMsg = {'\0'};
	MSXMLObj_IXMLDOMNamedNodeMap 	stepAttributes;
	MSXMLObj_IXMLDOMNode    		stepName;
	char 							*name;
	
	errChk(MSXML_IXMLDOMNodeGetattributes(stepPtr, 
										  errorInfo, 
										  &stepAttributes)); 
	errChk(MSXML_IXMLDOMNamedNodeMapgetNamedItem(stepAttributes, 
												 errorInfo, 
												 "name", 
												 &stepName));
	errChk(	MSXML_IXMLDOMNodeGettext(stepName, 
									 errorInfo, 
									 &name));
										
	Error:
	if ( error < 0 )
	{		
	  name = NULL; 
	}
	CA_DiscardObjHandle(stepAttributes);
	CA_DiscardObjHandle(stepName);
	return name;
}

long GetStepProperties(CAObjHandle stepPtr, char** propertyNameArray, char** propertyValArray, char** propertyTypeArray, ERRORINFO *errorInfo)
{
	
	int 							error = 0;
	ErrMsg 							errMsg = {'\0'};
	int 							i = 0;
	long 							numProperties = 0;
	MSXMLObj_IXMLDOMNodeList 		stepList;
	MSXMLObj_IXMLDOMNode     		stepPropertyItem;
	MSXMLObj_IXMLDOMNamedNodeMap 	stepAttributes;
	MSXMLObj_IXMLDOMNode    		propertyName;
	MSXMLObj_IXMLDOMNode    		propertyVal;
	MSXMLObj_IXMLDOMNode    		propertyType;
	
	errChk(MSXML_IXMLDOMNodeGetchildNodes(stepPtr,
									   	  errorInfo, 
									   	  &stepList));
	errChk(MSXML_IXMLDOMNodeListGetlength(stepList, 
										  errorInfo, 
										  &numProperties));
	for (i = 0; i < numProperties; ++i)
	{
		char *stepName;
		
		errChk(MSXML_IXMLDOMNodeListGetitem(stepList,
											errorInfo, 
											i, 
											&stepPropertyItem));
		errChk(MSXML_IXMLDOMNodeGetnodeName(stepPropertyItem, 
											errorInfo, 
											&stepName));
		if ( strcmp(stepName, "Result") != 0)
		{
			char *name;
			char *value;
			char *type;
			errChk(MSXML_IXMLDOMNodeGetattributes(stepPropertyItem, 
										 		  errorInfo, 
										  		  &stepAttributes)); 
			errChk(MSXML_IXMLDOMNamedNodeMapgetNamedItem(stepAttributes, 
												 		 errorInfo, 
												 		 "dataProperty", 
												 		 &propertyName));
			errChk(MSXML_IXMLDOMNodeGettext(propertyName, 
											errorInfo, 
											&name));
			errChk(MSXML_IXMLDOMNodeGetfirstChild(stepPropertyItem, 
			 									  errorInfo, 
			 									  &propertyVal));
			errChk(	MSXML_IXMLDOMNodeGettext(propertyVal, 
											 errorInfo, 
											 &value));
			errChk(MSXML_IXMLDOMNamedNodeMapgetNamedItem(stepAttributes, 
												 		 errorInfo, 
												 		 "type", 
												 		 &propertyType));
			errChk(MSXML_IXMLDOMNodeGettext(propertyType, 
											errorInfo, 
											&type));
			propertyNameArray[i] = (char*) malloc(sizeof(name[0]) * (strlen(name) + 1));
			propertyValArray[i] = (char*) malloc(sizeof(value[0]) * (strlen(value) + 1));
			propertyTypeArray[i] = (char*) malloc(sizeof(value[0]) * (strlen(type) + 1));			
			strcpy(propertyNameArray[i], name);
			strcpy(propertyValArray[i], value);
			strcpy(propertyTypeArray[i], type);
			
			CA_DiscardObjHandle(stepAttributes);
			CA_DiscardObjHandle(propertyName);
			CA_DiscardObjHandle(propertyVal);
			CA_DiscardObjHandle(propertyType);
		}
	}
	
	Error:
		CA_DiscardObjHandle(stepList);
		CA_DiscardObjHandle(stepPropertyItem);
	if ( error < 0 )
	{
		CA_DiscardObjHandle(stepAttributes);
		CA_DiscardObjHandle(propertyName);
		CA_DiscardObjHandle(propertyVal);
		CA_DiscardObjHandle(propertyType);
	}
	return numProperties;
}

long GetNumProperties(CAObjHandle stepPtr, ERRORINFO *errorInfo)
{
	int 						error = 0;
	ErrMsg 						errMsg = {'\0'};
	long 						numProperties = 0;
	long 						length = 0;
	int 						i = 0;
	MSXMLObj_IXMLDOMNodeList 	stepList;
	CAObjHandle  				stepPropertyItem;
	
	errChk(MSXML_IXMLDOMNodeGetchildNodes(stepPtr,
									   	  errorInfo, 
									   	  &stepList));
	errChk(MSXML_IXMLDOMNodeListGetlength(stepList, 
										  errorInfo, 
										  &length));
	for (i = 0; i < length; ++i)
	{
		char *stepName;
		
		errChk(MSXML_IXMLDOMNodeListGetitem(stepList,
											errorInfo, 
											i, 
											&stepPropertyItem));
		errChk(MSXML_IXMLDOMNodeGetnodeName(stepPropertyItem, 
											errorInfo, 
											&stepName));
		//if the step has a result property do not include it in the count.
		//This will be processed seperately.
		if ( strcmp(stepName, "Result") != 0)
			++numProperties;
	}
	
	Error:
	CA_DiscardObjHandle(stepPropertyItem);
	CA_DiscardObjHandle(stepList);
	return numProperties;
}

long StepHasResult(CAObjHandle currentStep)
{
	int 						error = 0;
	ERRORINFO 					errorInfo;
	ErrMsg 						errMsg = {'\0'};
	long 						hasResult = 0;
	long 						length = 0;
	int 						i = 0;
	MSXMLObj_IXMLDOMNodeList 	stepList;
	CAObjHandle 				stepPropertyItem;
	
	errChk(MSXML_IXMLDOMNodeGetchildNodes(currentStep,
									   	  &errorInfo, 
									   	  &stepList));
	errChk(MSXML_IXMLDOMNodeListGetlength(stepList, 
										  &errorInfo, 
										  &length));
	for (i = 0; i < length; ++i)
	{
		
		
		char *stepName;
		
		errChk(MSXML_IXMLDOMNodeListGetitem(stepList,
											&errorInfo, 
											i, 
											&stepPropertyItem));
		errChk(MSXML_IXMLDOMNodeGetnodeName(stepPropertyItem, 
											&errorInfo, 
											&stepName));
		if ( strcmp(stepName, "Result") == 0)
		{
			hasResult = 1;
			break;
		}
	}
	
	Error:
	CA_DiscardObjHandle(stepPropertyItem);
	CA_DiscardObjHandle(stepList);
	return hasResult;
}

//Process any result that the step may return.
void GetResultData(CAObjHandle currentStep, char *resultName, char *resultType, char *resultVal, ERRORINFO *errorInfo)
{
	int 							error = 0;
	ErrMsg 							errMsg = {'\0'};
	int 							i = 0;
	long 							numProperties;
	MSXMLObj_IXMLDOMNodeList     	stepList;
	MSXMLObj_IXMLDOMNode         	stepPropertyItem;
	MSXMLObj_IXMLDOMNamedNodeMap 	stepAttributes;
	MSXMLObj_IXMLDOMNode         	propertyName;
	MSXMLObj_IXMLDOMNode         	propertyType;
	MSXMLObj_IXMLDOMNode         	propertyVal;
	
	errChk(MSXML_IXMLDOMNodeGetchildNodes(currentStep,
									   	  errorInfo, 
									   	  &stepList));
	errChk(MSXML_IXMLDOMNodeListGetlength(stepList, 
										  errorInfo, 
										  &numProperties));
	for (i = 0; i < numProperties; ++i)
	{
		char *stepName;
		
		errChk(MSXML_IXMLDOMNodeListGetitem(stepList,
											errorInfo, 
											i, 
											&stepPropertyItem));
		errChk(MSXML_IXMLDOMNodeGetnodeName(stepPropertyItem, 
											errorInfo, 
											&stepName));
		if ( strcmp(stepName, "Result") == 0)
		{
			char *name;
			char *type;
			char *val;
			
			errChk(MSXML_IXMLDOMNodeGetattributes(stepPropertyItem, 
										 		  errorInfo, 
										  		  &stepAttributes)); 
			errChk(MSXML_IXMLDOMNamedNodeMapgetNamedItem(stepAttributes, 
												 		 errorInfo, 
												 		 "dataProperty", 
												 		 &propertyName));
			errChk(MSXML_IXMLDOMNodeGettext(propertyName, 
											errorInfo, 
											&name));
			errChk(MSXML_IXMLDOMNamedNodeMapgetNamedItem(stepAttributes, 
												 		 errorInfo, 
												 		 "type", 
												 		 &propertyType));
			errChk(MSXML_IXMLDOMNodeGettext(propertyType, 
											errorInfo, 
											&type));
			errChk(MSXML_IXMLDOMNamedNodeMapgetNamedItem(stepAttributes, 
												 		 errorInfo, 
												 		 "value", 
												 		 &propertyVal));
			errChk(MSXML_IXMLDOMNodeGettext(propertyVal, 
											errorInfo, 
											&val));
			strcpy(resultName, name);
			strcpy(resultType, type);
			strcpy(resultVal, val);
			
			CA_DiscardObjHandle(stepAttributes);
			CA_DiscardObjHandle(propertyName);
			CA_DiscardObjHandle(propertyType);
			CA_DiscardObjHandle(propertyVal);
		}
	}
	
	Error:
		CA_DiscardObjHandle(stepList);
		CA_DiscardObjHandle(stepPropertyItem);
	if ( error < 0 )
	{
		CA_DiscardObjHandle(stepAttributes);
		CA_DiscardObjHandle(propertyName);
		CA_DiscardObjHandle(propertyType); 
		CA_DiscardObjHandle(propertyVal);	
	}
}
