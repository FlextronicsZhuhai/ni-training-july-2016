
//-------------------------------------------------------------------------------
// These are needed in order to use the TestStand API and Sequence Analyzer API
#include "tsapivc.cpp"
#include "tsanalyzervc.cpp"
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// Constants used by this analysis module. These strings must match those
// in the Edit Analysis Module dialog box.
//-------------------------------------------------------------------------------
const char *cRuleId = "NI_CheckNumberOfLocalsVCExample";
const char *cRuleSettingName = "Maximum Number of Locals";

//-------------------------------------------------------------------------------
// Analysis Module for the rule. This function counts the locals in a sequence
// and reports a message if there are more than the maximum number specified by
// the rule setting.
//
// You specify the function to be called for an analysis module on the
// Edit Analysis Module dialog box. This analysis module must be configured to
// be called for:
//	these Kinds of Objects: Sequence Locals
//	these Transitions: Before Sequence Locals, After Sequence Locals
//-------------------------------------------------------------------------------
void __declspec(dllexport) CheckNumberOfLocals(TSAnalyzer::AnalysisContext *analysisContext)
{
	TSAnalyzer::RuleConfigurationPtr ruleConfiguration = analysisContext->GetRuleConfiguration(cRuleId);

	// Perform check only if the rule is enabled.
	if (ruleConfiguration->Enabled)
	{
		TS::PropertyObjectPtr ruleData = analysisContext->GetRuleAnalysisData(cRuleId, TSAnalyzer::RuleAnalysisDataScope_File, TSAnalyzer::GetRuleAnalysisDataOption_NoOptions);

		if (analysisContext->Transition == TSAnalyzer::AnalysisTransition_BeforeSequenceLocals)
		{
			// Analyzer is about to analyze sequence locals: reset the count
			ruleData->SetValNumber("NumberOfLocals", TS::PropOption_InsertIfMissing, 0.0);
		}
		else if (analysisContext->Transition == TSAnalyzer::AnalysisTransition_AfterSequenceLocals)
		{
			// Analyzer has just analyzed sequence locals: check the count.
			// Get the number of locals in this sequence.
			int numberOfLocals;
			numberOfLocals = (int) ruleData->GetValNumber("NumberOfLocals", 0);

			// Get the setting for the rule.
			int maximumNumberOfLocalsAllowed = (int) ruleConfiguration->RuleSettingValues->GetNumberValue(cRuleSettingName);

			// Report message if there are more locals than the maximum specified by the rule setting.
			if (numberOfLocals > maximumNumberOfLocalsAllowed)
			{
				TS::SequencePtr sequence = analysisContext->Object;

				// Create text explaining the violation.
				char text[1024];
				sprintf_s(text, sizeof(text), "Too many locals in sequence '%s': '%d'. The maximum is %d.", (const char *)sequence->Name, numberOfLocals, maximumNumberOfLocalsAllowed);

				// Create and report the message to the analyzer. Specify sequence locals as the location associated with the message.
				TSAnalyzer::AnalysisMessagePtr message = analysisContext->NewMessage(cRuleId, _bstr_t(text), sequence->Locals);
				analysisContext->ReportMessage(message);
			}
		}
		else
		{
			// Analyzer is analyzing a sequence local: increment the count.
			int numberOfLocals = (int) ruleData->GetValNumber("NumberOfLocals", 0);
			ruleData->SetValNumber("NumberOfLocals", 0, numberOfLocals + 1);
		}
	}
}
