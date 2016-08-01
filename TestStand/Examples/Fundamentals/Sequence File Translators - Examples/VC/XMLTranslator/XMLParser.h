#import <msxml6.dll> no_registry named_guids
#include<map>
#include<string>
using namespace TS;

class XMLParser
{
public:
	XMLParser();
	bool LoadFile(InputStreamPtr);
	MSXML2::IXMLDOMNodePtr GetHeader(InputStreamPtr);
	MSXML2::IXMLDOMNodeListPtr GetStepList();
	std::map<std::string, std::string> GetStepProperties(MSXML2::IXMLDOMNodePtr stepPtr);
	std::string GetStepName( MSXML2::IXMLDOMNodePtr stepPtr);
	std::string GetStepType( MSXML2::IXMLDOMNodePtr stepPtr);
	std::string GetSequenceName();
	bool StepHasResult( MSXML2::IXMLDOMNodePtr stepPtr );
	std::map<std::string, std::string> GetResultData(MSXML2::IXMLDOMNodePtr stepPtr);
private:
	MSXML2::IXMLDOMDocument2Ptr m_rootPtr;
	
};
