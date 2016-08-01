#include "stdafx.h"
#include <vector>

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
	bool CanTranslate  (const char *fileExtension,
						TS::InputStream* readStream,
						TS::TSError *error,
						char *errorMsg, 
						long maxErrorMsgLengthInBytes, 
						bool checkfileExtension=true);
	void GetFileVersion(std::string &fileVersion,
						TS::InputStream* readStream,
						TS::TSError *error,
						char *errorMsg, 
						long maxErrorMsgLengthInBytes);
	void GetFileFormatVersion(std::string &fileFormatVersion,
							  TS::InputStream* readStream,
							  TS::TSError *error,
							  char *errorMsg, 
							  long maxErrorMsgLengthInBytes);
	void Translate(TS::IEnginePtr engine, 
		           TS::InputStreamPtr readStream, 
				   TS::SequenceFilePtr seqFile, 
				   TS::TSError* error, 
				   char *errorMsg, 
				   long maxErrorMsgLengthInBytes);
	
private:
	TranslatorInfo m_TranslatorInfo;
};

class TranslatorCollection
{
public:
	static std::vector<Translator>& GetTranslatorCollection()
	{
		static TranslatorCollection allTranslators;
		return allTranslators.m_Translators;
	}
	static Translator* GetTranslator(size_t index, TS::TSError *error, char *errorMsg, long maxErrorMsgLengthInBytes);
	static Translator* GetTranslator(size_t index);
private:
	TranslatorCollection();
	void InitAllTranslators();
private:
	std::vector<Translator> m_Translators;
};

namespace TranslatorUtility
{
	void Tokenize(const std::string inputstring, 
				  char seperator, 
				  std::vector<std::string >& tokens);
	void ReadTillDelim( TS::InputStreamPtr readPtr,
		                std::string &buffer, 
						const std::string &delim
						);
};