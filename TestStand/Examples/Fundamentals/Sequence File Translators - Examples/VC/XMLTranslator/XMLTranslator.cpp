// TestFormat.cpp : Defines the entry point for the DLL application.
//
#include "StdAfx.h"
#include "XMLTranslator.h"
#include "XMLParser.h"
#include<map>

using namespace TS;

///////////////////////// TranslatorCollection /////////////////////////////////
TranslatorCollection::TranslatorCollection()
{
	InitAllTranslators();
}

void TranslatorCollection::InitAllTranslators()
{
	TranslatorInfo translatorInfos[]={
  //{ headerLength, user file fileExtension, format description                         , header info         }
	{31           , "xml"              , "MSVC Example - XML Format"                      , "VC Sample Test Description File" }};
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
		strcpy_s(errorMsg, maxErrorMsgLengthInBytes, "Index Out of range.");
	}
	return ret;
}

//////////////////////////////// Translator ////////////////////////////////////
Translator::Translator(const TranslatorInfo info):
m_TranslatorInfo(info),
m_totalSteps(0)
{
	m_XMLParser = new XMLParser();
}

//Check if the header info matches any of the supported file format headers.
bool Translator::CanTranslate(const char *fileExtension, InputStream* readStream, TSError *error, char* errorMsg, long maxErrorMsgLengthInBytes, bool checkfileExtension/*=true*/)
{
	bool ret = false;
	readStream->Offset = 0;
	GetParser()->LoadFile(readStream);
	MSXML2::IXMLDOMNodePtr header = GetParser()->GetHeader(readStream);
	std::string description = header->Getattributes()->getNamedItem("description")->text;
	if (  !m_TranslatorInfo.headerInfo.compare( description))
	{
		readStream->Offset = 0;
		ret = true;
	}
	return ret;
}

void Translator::Translate(IEnginePtr engine, InputStreamPtr readStream, SequenceFilePtr seqFile, TSError *error, char* errorMsg, long maxErrorMsgLengthInBytes)
{	
	GetParser()->LoadFile(readStream);
	std::string seqName = GetParser()->GetSequenceName();
	SequencePtr seq = engine->NewSequence();
	seq->Name = seqName.c_str();
	seqFile->InsertSequence(seq);
	m_totalSteps = 0;
	MSXML2::IXMLDOMNodeListPtr stepList = GetParser()->GetStepList();
	for ( int i = 0; i < stepList->length; ++i)
	{
		MSXML2::IXMLDOMNodePtr currentStep = stepList->Getitem(i);
		AddStep(engine, currentStep, GetParser()->GetStepProperties(currentStep), GetParser()->GetStepName(currentStep), seqFile, seqName);
	}
	//set the version property on the SequenceFile object
	std::string versionInfo;
	GetFileVersion(versionInfo, readStream, error, errorMsg, maxErrorMsgLengthInBytes);
	if( *error == TS_Err_NoError)
		seqFile->AsPropertyObjectFile()->Version = versionInfo.c_str();
}

void Translator::AddStep(IEnginePtr engine, MSXML2::IXMLDOMNodePtr currentStep, std::map<std::string, std::string> stepProperties, std::string stepName, SequenceFilePtr seqFile, std::string parentSeqName)
{
	SequencePtr seq = seqFile->GetSequenceByName(parentSeqName.c_str());
	std::string stepTypeString = GetParser()->GetStepType(currentStep);
	StepPtr newStep = engine->NewStep(GetAdapter(stepTypeString).c_str() ,GetStepType(stepTypeString).c_str());
	newStep->Name = stepName.c_str();
	PropertyObjectPtr stepPropObject = newStep->AsPropertyObject();
	SetStepProperties(currentStep, stepPropObject, stepProperties);
	if ( GetParser()->StepHasResult( currentStep))
	{	
		std::map<std::string, std::string> resultData = GetParser()->GetResultData(currentStep);
		AddReportVariable(newStep->AsPropertyObject(), seq, resultData);
	}
	seq->InsertStep(newStep, m_totalSteps, StepGroup_Main);
	m_totalSteps++;
	//Add the step to the TypeUsagelist of the sequence file
	seqFile->AsPropertyObjectFile()->GetTypeUsageList()->AddUsedTypes(newStep->AsPropertyObject());
}

//For each of the step properties in the source file assign the value specified.
void Translator::SetStepProperties(MSXML2::IXMLDOMNodePtr currentStep, PropertyObjectPtr stepPropertyObject, std::map<std::string, std::string> stepProperties)
{
	if ( stepProperties.size() )
	{
		std::map<std::string, std::string>::iterator j;
		size_t i;
		for( i = 0, j = stepProperties.begin(); i < stepProperties.size(); ++i, ++j)
		{	std::string type = currentStep->childNodes->Getitem((long)i)->attributes->getNamedItem("type")->text;
			if(0 == type.compare("string"))
				stepPropertyObject->SetValString((j->first).c_str() , PropOption_NoOptions, (j->second).c_str());
			else if(0 == type.compare("bool"))
				stepPropertyObject->SetValBoolean((j->first).c_str() , PropOption_NoOptions, (j->second=="true"));
			else if(0 == type.compare("number"))
			{
				double val = atof((j->second).c_str());
				stepPropertyObject->SetValNumber((j->first).c_str() , PropOption_NoOptions, val);
			}
			else
				throw std::exception("Unsupported Data type used in Step properties.");
		}
	}
}

//If the step has a result value create a local variable to hold the result and add a post expression 
//to the step to assign the result value to the local variable.
void Translator::AddReportVariable(PropertyObjectPtr propertyObject, SequencePtr sequence, std::map<std::string, std::string> resultData)
{
	std::string expression = "Locals." + (resultData.find("localVal"))->second;
	expression += "= Step." + (resultData.find("resultVal"))->second;
	if ( resultData.find("type")->second == "string")
	{
		sequence->Locals->SetValString(((resultData.find("localVal"))->second).c_str(), PropOption_InsertIfMissing, "");
	}
	else if ( resultData.find("type")->second == "number" )
	{
		sequence->Locals->SetValNumber(((resultData.find("localVal"))->second).c_str(), PropOption_InsertIfMissing, 0);
	}
	else if (resultData.find("type")->second == "bool")
	{
		sequence->Locals->SetValBoolean(((resultData.find("localVal"))->second).c_str(), PropOption_InsertIfMissing, 0);
	}
	else
		throw std::exception("Unsupported Data type used in the Result.");
	propertyObject->SetValString("TS.PostExpr", 0, expression.c_str());
}

void Translator::GetFileVersion(std::string &fileVersion, InputStream *readStream, TSError *error, char *errorMsg, long maxErrorMsgLengthInBytes)
{
	readStream->Offset = 0;
	GetParser()->LoadFile(readStream);
	MSXML2::IXMLDOMNodePtr header = GetParser()->GetHeader(readStream);
	fileVersion = header->Getattributes()->getNamedItem("fileversion")->text;
}

void Translator::GetFileFormatVersion(std::string &fileFormatVersion, InputStream *readStream, TSError *error, char *errorMsg, long maxErrorMsgLengthInBytes)
{
	readStream->Offset = 0;
	GetParser()->LoadFile(readStream);
	MSXML2::IXMLDOMNodePtr header = GetParser()->GetHeader(readStream);
	fileFormatVersion = header->Getattributes()->getNamedItem("fileformatversion")->text;
}

std::string Translator:: GetAdapter(const std::string stepString)
{
	std::string adapterString;
	if (0 == stepString.compare("MsgBox"))
		adapterString = "None Adapter";
	if(0 == stepString.compare("DISPLAYGRAPH"))
		adapterString = "";
	return adapterString;
}

std::string Translator::GetStepType(const std::string stepString)
{
	std::string stepType;
	if (0 == stepString.compare("MsgBox"))
		stepType = "MessagePopup";
	else if(0 == stepString.compare("DISPLAYGRAPH"))
		stepType = "DisplayGraph";
	else
		throw std::exception("Invalid Step Type.");
	return stepType;
}

