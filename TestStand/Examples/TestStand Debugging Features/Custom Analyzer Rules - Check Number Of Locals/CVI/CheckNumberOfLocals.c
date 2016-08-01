#include "tsapicvi.h"
#include "tsutil.h"
#include "tsanalyzer.h"

#define CLEAR(__handle, __func)				\
	if(__handle)							\
	{										\
		__func(__handle);					\
		__handle = 0;						\
	}

//-------------------------------------------------------------------------------
// Constants used by this analysis module. These strings must match those in
// the Edit Analysis Module dialog box.
//-------------------------------------------------------------------------------
const char *cRuleId = "NI_CheckNumberOfLocalsCVIExample";
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
int __declspec(dllexport) CheckNumberOfLocals(CAObjHandle analysisContext, ErrMsg errMsg)
{
	int         error = 0;
	ERRORINFO   errorInfo;
	VBOOL		ruleIsEnabled = VFALSE;
	char *		sequenceName = NULL;
	char *		messageText = NULL;
	TSAnalyzerObj_AnalysisMessage message = 0;
	TSAnalyzerObj_RuleConfiguration ruleConfiguration = 0;
	TSAnalyzerObj_RuleSettingValues ruleSettingValues = 0;
	TSObj_Property ruleAnalysisData = 0;
	TSObj_Property sequenceLocals = 0;
	TSObj_Sequence sequence = 0;
	
	tsErrChk(TSAnalyzer_AnalysisContextGetRuleConfiguration (analysisContext, &errorInfo, cRuleId, &ruleConfiguration));
	tsErrChk(TSAnalyzer_RuleConfigurationGetEnabled(ruleConfiguration, &errorInfo, &ruleIsEnabled));
	
	// Perform check only if the rule is enabled.
	if (ruleIsEnabled)
	{
		enum TSAnalyzerEnum_AnalysisTransition transition;
		
		// Get the transition to determine when we're being called.
		tsErrChk(TSAnalyzer_AnalysisContextGetTransition(analysisContext, &errorInfo, &transition));
		tsErrChk(TSAnalyzer_AnalysisContextGetRuleAnalysisData(analysisContext, &errorInfo, cRuleId, TSAnalyzerConst_RuleAnalysisDataScope_File, TSAnalyzerConst_GetRuleAnalysisDataOption_NoOptions, &ruleAnalysisData));
		
		if (transition == TSAnalyzerConst_AnalysisTransition_BeforeSequenceLocals)
		{
		 	// Analyzer is about to analyze sequence locals: reset the count.
			
			tsErrChk(TS_PropertySetValNumber(ruleAnalysisData, &errorInfo, "NumberOfLocals", TS_PropOption_InsertIfMissing, 0.0));
		} 
		else if (transition == TSAnalyzerConst_AnalysisTransition_AfterSequenceLocals)
		{
			// Analyzer has just analyzed sequence locals: check the count.
			
			double numberOfLocals;
			double maximumNumberOfLocalsAllowed;
			
			// Get the number of locals in this sequence.
			tsErrChk(TS_PropertyGetValNumber(ruleAnalysisData, &errorInfo, "NumberOfLocals", 0, &numberOfLocals));
			
			// Get the maximum setting for the rule.
			tsErrChk(TSAnalyzer_RuleConfigurationGetRuleSettingValues(ruleConfiguration, &errorInfo, &ruleSettingValues));
			tsErrChk(TSAnalyzer_RuleSettingValuesGetNumberValue(ruleSettingValues, &errorInfo, cRuleSettingName, &maximumNumberOfLocalsAllowed));
			
			// Report message if there are more locals than the maximum specified by the rule setting.
			if (numberOfLocals > maximumNumberOfLocalsAllowed)
			{
				size_t sequenceNameLength;
				const char *messageFormat = "Too many locals in sequence '%s': '%d'. The maximum is %d.";
				
				tsErrChk(TSAnalyzer_AnalysisContextGetObject(analysisContext, &errorInfo, &sequence));
				tsErrChk(TS_SequenceGetName(sequence, &errorInfo, &sequenceName));
				tsErrChk(TS_SequenceGetLocals(sequence, &errorInfo, &sequenceLocals));
				sequenceNameLength = strlen(sequenceName);

				// Create text explaining the rule violation
				messageText = malloc(strlen(messageFormat) + sequenceNameLength + 20 /* length of digits in INT_MAX * 2 */);
				sprintf(messageText, messageFormat, sequenceName, (int)numberOfLocals, (int)maximumNumberOfLocalsAllowed);
			
				// Create and report the message to the analyzer. Specify sequence locals as the location associated with the message.
				tsErrChk(TSAnalyzer_AnalysisContextNewMessage(analysisContext, &errorInfo, cRuleId, messageText, sequenceLocals, &message));
				tsErrChk(TSAnalyzer_AnalysisContextReportMessage(analysisContext, &errorInfo, message));
			}
		} 
		else
		{
			// Analyzer is analyzing a sequence local: increment the count.
			
			double numberOfLocals;
			tsErrChk(TS_PropertyGetValNumber(ruleAnalysisData, &errorInfo, "NumberOfLocals", 0, &numberOfLocals));
			tsErrChk(TS_PropertySetValNumber(ruleAnalysisData, &errorInfo, "NumberOfLocals", 0, numberOfLocals + 1));
		}
	}
	
Error:
	CLEAR(sequenceName, CA_FreeMemory);
	CLEAR(messageText, free);
	CLEAR(ruleConfiguration, CA_DiscardObjHandle);
	CLEAR(ruleSettingValues, CA_DiscardObjHandle);
	CLEAR(ruleAnalysisData, CA_DiscardObjHandle);
 	CLEAR(sequence, CA_DiscardObjHandle);
 	CLEAR(message, CA_DiscardObjHandle);
	CLEAR(sequenceLocals, CA_DiscardObjHandle);
	
	return error;
}
