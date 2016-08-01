//TextTranslator.cpp Implementation file.
#include "stdafx.h"
#include "TextTranslator.h"
using namespace TS;

std::string GetAdapterName(const std::string & stepType)
{
	std::string ret = NoneAdapterKeyName;
	if ( stepType.compare("DisplayGraph") == 0)
		ret = "";
	else if( stepType.compare("MessagePopup") != 0)
		throw std::exception("Step Type not supported.");
	return ret;
}

// Parses "Name:Type"
void ParseTypeValue(PropertyObjectPtr propertyObj, const std::string &inputLine, std::string val = "")
{
	std::vector<std::string> tokens;
	TranslatorUtility::Tokenize(inputLine, ':', tokens);
	// token[0] == Name 
	// token[1] == Type (Can be boolean,string,number)
	if ( tokens.size() != 2 )
	{
		// Invalid file format.
		throw std::exception("Invalid number of arguments");
	}
	if ( val.size() == 0)
	{
		//tokens[1] will now contain a type value pair and hence we must get only the type part 
		//into tokens[1] and we will store the name of the variable in tokens[0]. 
		std::vector<std::string> nameVal;
		TranslatorUtility::Tokenize(tokens[1], '=', nameVal);
		tokens[0] = nameVal[1];
		tokens[1] = nameVal[0];
	}
	if (tokens[1].compare("boolean") == 0)
	{
		propertyObj->SetValBoolean(tokens[0].c_str(), PropOption_NoOptions, !val.compare("true"));
	}
	else if (tokens[1].compare("string") == 0)
		propertyObj->SetValString(tokens[0].c_str(), PropOption_NoOptions, val.c_str());
	else if (tokens[1].compare("number") == 0)
	{
		double numVal=atof(val.c_str());
		propertyObj->SetValNumber(tokens[0].c_str(), PropOption_NoOptions, numVal);
	}
	else
	{
		// Invalid type.
		throw std::exception("Type Unknown.");
	}
}

//If the step has a Result value then create a local variable for storing the result 
//and create a post expression for the step assigning the result value to the local variable.
void ParseResultValue(PropertyObjectPtr propertyObj, StepPtr step, const std::string &inputLine)
{
	std::vector<std::string> tokens;
	TranslatorUtility::Tokenize(inputLine, '=', tokens);
	// token[0] == Name:Type (Type can be boolean,string,number) 
	// token[1] == Value 
	if ( tokens.size() != 2 )
	{
		// Invalid file format.
		throw std::exception("Invalid number of Arguments.");
	}
	std::vector<std::string> nameType;
	TranslatorUtility::Tokenize(tokens[0], ':', nameType);
	//nameType[0] will have the name of the result property of the step and 
	//nameType[1] will have the type
	if (nameType[1].compare("boolean") == 0)
	{
		propertyObj->SetValBoolean(tokens[1].c_str(), PropOption_InsertIfMissing, false);
	}
	else if (nameType[1].compare("string") == 0)
		propertyObj->SetValString(tokens[1].c_str(), PropOption_InsertIfMissing, "");
	else if (nameType[1].compare("number") == 0)
		propertyObj->SetValNumber(tokens[1].c_str(), PropOption_InsertIfMissing, 0);
	else
	{
		// Invalid type.
		throw std::exception("Type Unknown.");
	}
	std::string expression = "Locals.";
	expression.append(tokens[1].append("= Step.")) ;
	expression.append(nameType[0]);
	step->AsPropertyObject()->SetValString("TS.PostExpr", 0, expression.c_str());;
}

// Parses : Name:Type=Value
void ParseParameters(StepPtr step, const std::string &inputLine)
{
	std::vector<std::string> tokens;
	TranslatorUtility::Tokenize(inputLine, '=', tokens);
	// token[0] == Name:Type
	// token[1] == Value
	if ( tokens.size() != 2 )
	{
		// Invalid file format.
		//throw exception;
		throw std::exception("Insufficient Parameters for creating the step.");
	}
	ParseTypeValue(step->AsPropertyObject(),tokens[0], tokens[1]);
}

// Parses: StepName,StepType,Result,Property,Property.... \r\n
// Where: 1) Result is Name:Type
//        2) Property is Name:Type=Value
StepPtr CommaSeparatedStepParser(IEnginePtr engine, SequencePtr seq, const std::string &inputLine)
{
	std::vector<std::string> tokens;
	TranslatorUtility::Tokenize(inputLine, ',', tokens);
	if (tokens.size() < 3)
	{
		// Invalid file format.
		throw std::exception("Invalid Number of Arguments.");
	}
	// tokens[0] == Step Name
	// tokens[1] == Step Type
	// tokens[2] == Return Value (can be empty string :"")
	// tokens[3] == Step Property
	// ...
	// tokens[n] == Step Property
	StepPtr retStepPtr;
	retStepPtr = engine->NewStep(GetAdapterName(tokens[1]).c_str(), tokens[1].c_str());
	retStepPtr->Name = tokens[0].c_str();
	if (tokens[2].compare("") != 0)
		ParseResultValue(seq->Locals, retStepPtr, tokens[2]);
	for (size_t i=3; i < tokens.size(); ++i)
		ParseParameters(retStepPtr, tokens[i]);
	return retStepPtr;
}

///////////////////////// TranslatorCollection /////////////////////////////////
TranslatorCollection::TranslatorCollection()
{
	InitAllTranslators();
}

void TranslatorCollection::InitAllTranslators()
{
	TranslatorInfo translatorInfos[]={
  //{ headerLength, user file fileExtension, format description, header info, }
	{31, "vctf", "MSVC Example - Text Format"   ,"VC Sample Test Description File"}};

	const int totalTranslators=sizeof(translatorInfos)/sizeof(translatorInfos[0]);
	for (int i=0; i < totalTranslators; ++i)
	{
		m_Translators.push_back( Translator(translatorInfos[i]) ); 	
	}
}

Translator* TranslatorCollection::GetTranslator(size_t index)
{
	Translator *ret = NULL;
	if(index >= 0 && index < GetTranslatorCollection().size())
		ret = &GetTranslatorCollection()[index];
	return ret;
}

Translator* TranslatorCollection::GetTranslator(size_t index,TSError *error, char *errorMsg, long maxErrorMsgLengthInBytes)
{
	Translator *ret = GetTranslator(index);
	if(ret == NULL)
	{
		*error = TS_Err_IndexOutOfRange;
		strcpy_s(errorMsg, maxErrorMsgLengthInBytes, "\n Index Out of range \n");
	}
	return ret;
}

//////////////////////////////// Translator ////////////////////////////////////
Translator::Translator(const TranslatorInfo info):
m_TranslatorInfo(info)
{
}

bool Translator::CanTranslate(const char *fileExtension, InputStream* readStream, TSError *error, char *errorMsg, long maxErrorMsgLengthInBytes, bool checkfileExtension/*=true*/)
{
	bool ret = false;
	if ( !checkfileExtension || m_TranslatorInfo.fileExtension.compare(fileExtension))
	{
		readStream->Offset = 0;
		unsigned char *pCh;
		SAFEARRAY *psa;
		psa = (readStream->ReadBytes(m_TranslatorInfo.headerLength));
		SafeArrayAccessData(psa, reinterpret_cast<void**>(&pCh));
		ret = !memcmp(pCh, m_TranslatorInfo.headerInfo.c_str(), m_TranslatorInfo.headerLength);
		SafeArrayUnaccessData( psa );
		SafeArrayDestroy( psa);
	}
	return ret;
}

void Translator::Translate(IEnginePtr engine, InputStreamPtr readStream, SequenceFilePtr seqFile, TSError *error, char *errorMsg, long maxErrorMsgLengthInBytes)
{	
	SequencePtr seq = engine->NewSequence();
	seq->Name = "MainSequence";
	seqFile->InsertSequence(seq);
	std::string buf;
	buf.reserve(1024);
	readStream->Offset = 0;
	TranslatorUtility::ReadTillDelim(readStream, buf, "\r\n"); // Skip the first line, which is a header line

	int totalSteps = 0;
	while ( !readStream->IsEndofStream )
	{
		buf.clear();
		TranslatorUtility::ReadTillDelim(readStream, buf, "\r\n");
		if ( buf.size())
		{
			StepPtr newStep = CommaSeparatedStepParser( engine, seq, buf); // will throw exception for invalid steps
			seq->InsertStep(newStep, totalSteps++, StepGroup_Main);
			//Add the type to the TypeUsageList of the Sequence File.
			seqFile->AsPropertyObjectFile()->GetTypeUsageList()->AddUsedTypes(newStep->AsPropertyObject());
		}
	}
	//Read the version Info from the header and set it on the created SequenceFile.
	std::string versionInfo;
	GetFileVersion( versionInfo, readStream, error, errorMsg, maxErrorMsgLengthInBytes);
	if (*error == TS_Err_NoError)
		seqFile->AsPropertyObjectFile()->Version = versionInfo.c_str();
}

void Translator::GetFileVersion(std::string &fileVersion, InputStream *readStream, TSError *error, char *errorMsg, long maxErrorMsgLengthInBytes)
{
	readStream->Offset = (int)m_TranslatorInfo.headerInfo.length()+ 1;
	std::string versionStr;
	TranslatorUtility::ReadTillDelim(readStream, versionStr, "\r\n");
	size_t it = versionStr.find_first_of(":");
	if ( it >= 0 && it < versionStr.size() )
	{
		fileVersion = versionStr.substr(it + 1, versionStr.size() - it - 1);
		// Trim leading and trailing spaces
		std::string::size_type first = fileVersion.find_first_not_of(" \t\r\n"),
		                        last = fileVersion.find_last_not_of(" \t\r\n");
		fileVersion = fileVersion.substr( first, last-first+1);
	}
	else
		fileVersion = "0.0.0.0";
}

void Translator::GetFileFormatVersion(std::string &fileFormatVersion, InputStream *readStream, TSError *error, char *errorMsg, long maxErrorMsgLengthInBytes)
{
	readStream->Offset = (int)m_TranslatorInfo.headerInfo.length() + 1;
	std::string versionStr;
	TranslatorUtility::ReadTillDelim(readStream, versionStr, "\r\n");
	size_t it = versionStr.find_first_of(":");
	if ( it >= 0 && it < versionStr.size())
	{	
		fileFormatVersion = versionStr.substr(0, it);
		//make sure that the version string does not contain any whitespaces
		std::string::size_type first = fileFormatVersion.find_first_not_of(" \t\r\n");
		std::string::size_type last = fileFormatVersion.find_last_not_of(" \t\r\n");
		fileFormatVersion = fileFormatVersion.substr(first, last-first+1);
	}
	else
		fileFormatVersion = "0.0.0.0";
}

////////////////////////////// TranslatorUtility ///////////////////////////////
void TranslatorUtility::ReadTillDelim(InputStreamPtr readPtr, std::string &buffer, const std::string &delims)
{	
	long numBytes = 1;
	unsigned char *pCh;
	SAFEARRAY *psa;
	while ( !readPtr->IsEndofStream )
	{
		psa = (readPtr->ReadBytes(numBytes));
		SafeArrayAccessData(psa, reinterpret_cast<void**>(&pCh));
		if (delims.find(*pCh) != -1)
		{
			SafeArrayUnaccessData(psa);
			break;
		}
		buffer+=*pCh;
		SafeArrayUnaccessData(psa);
		SafeArrayDestroy(psa);
	}
}

void TranslatorUtility::Tokenize( const std::string inputstring, char seperator, std::vector<std::string>&  tokens)
{
	//Tokenize the string based on the seperator and return the tokens in the vector.
	size_t inputLength = inputstring.length();
	size_t i      = 0, 
		offset = 0;
	do
	{
		i = inputstring.find_first_of( seperator, offset);
		if ( i != -1)
		{
			tokens.push_back(inputstring.substr(offset, i - offset));
			offset = i + 1;
		}
	}while(i != -1);

	i=inputstring.find_last_of(seperator);
	if (i == -1)//If there is only one token and hence no seperator is found.
		tokens.push_back(inputstring);
	else if ( (inputLength-i) > 1)//Add the last token to the vector.
		tokens.push_back(inputstring.substr(i+1, inputLength-i-1));
}
