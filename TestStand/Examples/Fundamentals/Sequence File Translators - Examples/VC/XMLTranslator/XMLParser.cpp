#include "StdAfx.h"
#include <map>
#include "XMLParser.h"
#include "XMLTranslator.h"
using namespace TS;

XMLParser::XMLParser()
{
	HRESULT hr = m_rootPtr.CreateInstance(MSXML2::CLSID_DOMDocument30);
	if ( FAILED(hr))
		throw std::exception("Failed to create Parser.");
}

bool XMLParser::LoadFile(InputStreamPtr readStream)
{
	const int len = readStream->Length;
	SAFEARRAY *pSA = (readStream->ReadBytes(len));
	char *pCh;
	SafeArrayAccessData(pSA, reinterpret_cast<void**>(&pCh));
	std::string str(pCh, len);
	bool loaded = m_rootPtr->loadXML(str.c_str()) == VARIANT_TRUE;
	SafeArrayUnaccessData(pSA);
	SafeArrayDestroy(pSA);
	return loaded;
}

std::string XMLParser::GetSequenceName()
{
	return std::string(m_rootPtr->childNodes->Getitem(1)->childNodes->Getitem(1)->childNodes->Getitem(0)->attributes->getNamedItem("name")->text);
}

MSXML2::IXMLDOMNodePtr XMLParser::GetHeader(InputStreamPtr readStream)
{
	return m_rootPtr->GetchildNodes()->Getitem(1)->GetchildNodes()->Getitem(0);
}

MSXML2::IXMLDOMNodeListPtr XMLParser::GetStepList()
{
	if (m_rootPtr)
	{
		std::string nodeName = m_rootPtr->childNodes->Getitem(1)->childNodes->Getitem(1)->nodeName;
		return m_rootPtr->childNodes->Getitem(1)->childNodes->Getitem(1)->childNodes->Getitem(0)->childNodes;
	}
	else
		return NULL;
}

std::map<std::string, std::string> XMLParser::GetStepProperties(MSXML2::IXMLDOMNodePtr stepPtr)
{
	std::map<std::string, std::string> properties;
	std::string propertyName;
	std::string propertyValue;
	for ( int i = 0; i < stepPtr->childNodes->Getlength(); ++i)
	{
		if ( strcmp(stepPtr->childNodes->Getitem(i)->nodeName, "Result"))
		{
			propertyName = stepPtr->childNodes->Getitem(i)->attributes->getNamedItem("dataProperty")->text;
			propertyValue = stepPtr->childNodes->Getitem(i)->childNodes->Getitem(0)->text;
			properties.insert(properties.end(), std::pair<std::string, std::string> (propertyName, propertyValue));
		}
	}
	return properties;
}

std::string XMLParser::GetStepName( MSXML2::IXMLDOMNodePtr stepPtr)
{
	return std::string(stepPtr->attributes->getNamedItem("name")->text);	
}

std::string XMLParser::GetStepType(MSXML2::IXMLDOMNodePtr stepPtr)
{
	return std::string(stepPtr->attributes->getNamedItem("type")->text);
}

bool XMLParser::StepHasResult( MSXML2::IXMLDOMNodePtr stepPtr )
{
	bool hasResult = false;
	for ( long i = 0; i < stepPtr->childNodes->length; ++i)
		if ( stepPtr->childNodes->Getitem(i)->nodeName == _bstr_t("Result") )
			hasResult = true;
	return hasResult;
}

std::map<std::string, std::string> XMLParser::GetResultData(MSXML2::IXMLDOMNodePtr stepPtr)
{
	std::map<std::string, std::string> resultData;
	for ( long i = 0; i < stepPtr->childNodes->length; ++i)
	{
		if ( stepPtr->childNodes->Getitem(i)->nodeName == _bstr_t("Result") )
		{
			std::string dataProperty = stepPtr->childNodes->Getitem(i)->attributes->getNamedItem("dataProperty")->text;
			resultData.insert(resultData.end(), std::pair<std::string, std::string>("localVal", dataProperty));
			std::string resultValue = stepPtr->childNodes->Getitem(i)->attributes->getNamedItem("value")->text;
			resultData.insert(resultData.end(), std::pair<std::string, std::string>("resultVal", resultValue));
			std::string resultType = stepPtr->childNodes->Getitem(i)->attributes->getNamedItem("type")->text;
			resultData.insert(resultData.end(), std::pair<std::string, std::string>("type", resultType));
		}
	}
	return resultData;
}
