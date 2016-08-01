#include "stdafx.h"
#include <vector>
#include<map>
#import <msxml6.dll> no_registry named_guids
using namespace TS;
class XMLParser;

struct TranslatorInfo
{
	int         headerLength;
	std::string fileExtension;
	std::string description;
	std::string headerInfo;
};

class Translator
{
public:
	Translator(const TranslatorInfo info);
	TranslatorInfo &GetInfo(){return m_TranslatorInfo;};
	bool CanTranslate(	const char *fileExtension,
						InputStream* readStream,
						TSError *error,
						char* errorMsg, 
						long maxErrorMsgLengthInBytes, 
						bool checkfileExtension=true);
	void Translate(IEnginePtr engine, 
				   InputStreamPtr readStream, 
				   SequenceFilePtr seqFile, 
				   TSError* error, 
				   char* errorMsg, 
				   long maxErrorMsgLengthInBytes);
	XMLParser* GetParser() {return m_XMLParser;};
	void GetFileVersion(std::string &fileVersion,
						InputStream* readStream,
						TSError *error,
						char *errorMsg, 
						long maxErrorMsgLengthInBytes);
	void GetFileFormatVersion(std::string &fileFormatVersion,
							  InputStream* readStream,
							  TSError *error,
							  char *errorMsg, 
							  long maxErrorMsgLengthInBytes);
	
private:
	TranslatorInfo m_TranslatorInfo;
	long           m_totalSteps;
	XMLParser	   *m_XMLParser;

private:
	void AddStep(IEnginePtr engine,
				 MSXML2::IXMLDOMNodePtr currentStep,
				 std::map<std::string, std::string> stepProperties,
				 std::string stepName,
				 SequenceFilePtr seqFile, 
				 std::string parentSeqName="MainSequence");
	void SetStepProperties(MSXML2::IXMLDOMNodePtr currentStep,
						   PropertyObjectPtr stepPropertyObject, 
						   std::map<std::string,std::string> stepProperties);
	void AddReportVariable(PropertyObjectPtr propertyObject, 
						   SequencePtr sequence, 
						   std::map<std::string, 
						   std::string> resultData);
	std::string GetAdapter(const std::string stepString);
	std::string GetStepType(const std::string stepString);
	
};


class TranslatorCollection
{
public:
	static std::vector<Translator>& GetTranslatorCollection()
	{
		static TranslatorCollection allTranslators;
		return allTranslators.m_Translators;
	}
	static Translator* GetTranslator(size_t index, TSError *error, char *errorMsg, long maxErrorMsgLengthInBytes);
	static Translator* GetTranslator(size_t index);
private:
	TranslatorCollection();
	void InitAllTranslators();
private:
	std::vector<Translator> m_Translators;
};

