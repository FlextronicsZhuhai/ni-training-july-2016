#include "tsapicvi.h"
#include "tsutil.h"
#include "tsanalyzer.h"

#include "ConfigureCheckStepNameLength.h"

#define CLEAR(__handle, __func)				\
	if(__handle)							\
	{										\
		__func(__handle);					\
		__handle = 0;						\
	}

//-------------------------------------------------------------------------------
// Constants used by this analysis module. The Rule Id constant must match the
// Rule Id specified in the Edit Rule dialog box.
//-------------------------------------------------------------------------------
const char *cRuleId = "NI_CheckStepNameLengthCVIExample";
const char *cMaximumStepNameLengthPropertyName = "MaximumStepNameLength";
const int cDefaultMaximumStepNameLength = 15;


//-------------------------------------------------------------------------------
// Helper function to display the configure dialog
//-------------------------------------------------------------------------------
static int DisplayConfigureStepNameLengthDialog(CAObjHandle engine, int *maximumStepNameLength)
{
	int 		error = 0;
	ERRORINFO   errorInfo;
	ErrMsg      errMsg = "";
	int 		canceled = 0;
	int 		rulePanel = 0;
 	TSModalData modalData = InitialModalData;

	errChk(rulePanel = LoadPanelEx (0, "ConfigureCheckStepNameLength.uir", RULE_PANEL, __CVIUserHInst));
	// Set the initial value on the control from the setting
	errChk(SetCtrlVal(rulePanel, RULE_PANEL_MAX_STEP_NAME_LENGTH, *maximumStepNameLength));
	
	// Make the edit dialog modal to the application
	tsErrChkMsgPopup(TS_StartModalDialog (engine, &errorInfo, &modalData));

	errChk(InstallPopup(rulePanel));

	if (RunUserInterface() == EVENT_DLG_DONE_OK)
	{
		// Update setting to return to caller.
		errChk(GetCtrlVal(rulePanel, RULE_PANEL_MAX_STEP_NAME_LENGTH, maximumStepNameLength));
	}

Error:
	// Discard the dialog panel.
	TS_EndModalDialogAndDiscard(&errorInfo, &modalData, rulePanel);
	
	return error;
}

//-------------------------------------------------------------------------------
// Helper function to get the maximum step name length setting for the rule.
//-------------------------------------------------------------------------------
static int GetMaximumStepNameLength(TSAnalyzerObj_RuleConfiguration ruleConfiguration, int *maximumStepNameLength)
{
	int         error = 0;
	ERRORINFO   errorInfo;
	ErrMsg      errMsg = "";
	VBOOL		configDataExists = VFALSE;
	TSAnalyzerObj_PropertyObject configurationData = 0;

	// Set to default
	*maximumStepNameLength = cDefaultMaximumStepNameLength;
	
	// Must check if the setting exists. It's possible that the user never configured the rule in which case
	// we use a default value.
	tsErrChk(TSAnalyzer_RuleConfigurationGetConfigurationData(ruleConfiguration, &errorInfo, &configurationData));
	tsErrChk(TS_PropertyExists(configurationData, &errorInfo, cMaximumStepNameLengthPropertyName, 0, &configDataExists));
	if (configDataExists)
	{
		double doubleVal;
		tsErrChk(TS_PropertyGetValNumber(configurationData, &errorInfo, cMaximumStepNameLengthPropertyName, 0, &doubleVal));
		*maximumStepNameLength = (int) doubleVal;
	}
	
Error:
	CLEAR(configurationData, CA_DiscardObjHandle);
	return error;
}

//-------------------------------------------------------------------------------
// Helper function to set the maximum step name length setting for the rule.
//-------------------------------------------------------------------------------
static int SetMaximumStepNameLength(TSAnalyzerObj_RuleConfiguration ruleConfiguration, int maximumStepNameLength)
{
	int         error = 0;
	ERRORINFO   errorInfo;
	ErrMsg      errMsg = "";
	TSAnalyzerObj_PropertyObject configurationData = 0;
	
	tsErrChk(TSAnalyzer_RuleConfigurationGetConfigurationData(ruleConfiguration, &errorInfo, &configurationData));
	tsErrChk(TS_PropertySetValNumber(configurationData, &errorInfo, cMaximumStepNameLengthPropertyName, TS_PropOption_InsertIfMissing, (double)maximumStepNameLength));

Error:
	CLEAR(configurationData, CA_DiscardObjHandle);
	return error;
}

//-------------------------------------------------------------------------------
// Configuration Module for the rule. This function displays a dialog and allows
// the user to specify the maximum step name length setting.
//
// You specify the configuration module for a rule on the Advanced tab of the 
// Edit Rule dialog box.
//-------------------------------------------------------------------------------
int __declspec(dllexport) ConfigureCheckStepNameLength(CAObjHandle configurationContext, ErrMsg errMsg)
{
	int         error = 0;
	ERRORINFO   errorInfo;
	TSAnalyzerObj_RuleConfiguration ruleConfiguration = 0;
	int			maximumStepNameLength;
	int			initialMaximumStepNameLength;
	CAObjHandle	engine = 0;
	
	tsErrChk(TSAnalyzer_RuleConfigurationContextGetRuleConfiguration(configurationContext, &errorInfo, &ruleConfiguration));
	
	errChk(GetMaximumStepNameLength(ruleConfiguration, &initialMaximumStepNameLength));
	maximumStepNameLength = initialMaximumStepNameLength;
	
	tsErrChk(TSAnalyzer_RuleConfigurationContextGetEngine(configurationContext, &errorInfo, &engine));
	
	// Display dialog and get user response 
	errChk(DisplayConfigureStepNameLengthDialog(engine, &maximumStepNameLength));
	
	if (maximumStepNameLength != initialMaximumStepNameLength)
	{
		char description[256];
		
		// Save the setting
		errChk(SetMaximumStepNameLength(ruleConfiguration, maximumStepNameLength));
		
		// Update the rule description to contain the setting value
		sprintf(description, "Step names must be less than %d characters", maximumStepNameLength);
		tsErrChk(TSAnalyzer_RuleConfigurationSetDescription(ruleConfiguration, &errorInfo, description));
		
		// Set modified property so that user is prompted to save when closing project
		tsErrChk(TSAnalyzer_RuleConfigurationContextSetIsModified(configurationContext, &errorInfo, VTRUE));
	}

Error:
	CLEAR(ruleConfiguration, CA_DiscardObjHandle);
	CLEAR(engine, CA_DiscardObjHandle);
	
	return error;
}

//-------------------------------------------------------------------------------
// Analysis Module for the rule. This function examines a step and reports an
// analysis message if the step name is longer than the maximum step name
// length setting.
//
// You specify the function to be called for an analysis module on the
// Edit Analysis Module dialog box.
//-------------------------------------------------------------------------------
int __declspec(dllexport) CheckStepNameLength(CAObjHandle analysisContext, ErrMsg errMsg)
{
	int         error = 0;
	ERRORINFO   errorInfo;
	VBOOL		ruleIsEnabled = VFALSE;
	char *		stepName = NULL;
	char *		messageText = NULL;
	TSAnalyzerObj_AnalysisMessage message = 0;
	TSAnalyzerObj_RuleConfiguration ruleConfiguration = 0;
	CAObjHandle step = 0;
	
	tsErrChk(TSAnalyzer_AnalysisContextGetRuleConfiguration (analysisContext, &errorInfo, cRuleId, &ruleConfiguration));

	tsErrChk(TSAnalyzer_RuleConfigurationGetEnabled(ruleConfiguration, &errorInfo, &ruleIsEnabled));
	
	// Perform check only if the rule is enabled.
	if (ruleIsEnabled)
	{
		int	maximumStepNameLength;
		size_t	stepNameLength;
		
		// Because the analysis module is configured to be called only on steps, the Object in the analysis context will
		// always be a step.
		tsErrChk(TSAnalyzer_AnalysisContextGetObject(analysisContext, &errorInfo, &step));
		
		// Get the setting for the rule
		errChk(GetMaximumStepNameLength(ruleConfiguration, &maximumStepNameLength));
		
		// Get value from step
		tsErrChk(TS_StepGetName(step, &errorInfo, &stepName));
		stepNameLength = strlen(stepName);
	
		// Check for violation of rule and report message.
		if (stepNameLength > maximumStepNameLength)
		{
			const char *messageFormat = "Step name '%s' is too long (%d). The maximum is %d.";
			messageText = malloc(strlen(messageFormat) + stepNameLength + 20 /* length of digits in INT_MAX * 2 */);
			
			// Create text explaining the violation.
			sprintf(messageText, messageFormat, stepName, stepNameLength, maximumStepNameLength);
			
			// Create and report the message to the analyzer. Use step as the location object that the analyzer uses to highlight. You can
			// pass a different object for the location or you can pass 0 for the location object and use the AnalysisMessage.Locations
			// property to specify the location after creating the message.
			tsErrChk(TSAnalyzer_AnalysisContextNewMessage(analysisContext, &errorInfo, cRuleId, messageText, step, &message));
			tsErrChk(TSAnalyzer_AnalysisContextReportMessage(analysisContext, &errorInfo, message));
		}	
	}
	
Error:
	CLEAR(stepName, CA_FreeMemory);
	CLEAR(messageText, free);
	CLEAR(ruleConfiguration, CA_DiscardObjHandle);
 	CLEAR(step, CA_DiscardObjHandle);
 	CLEAR(message, CA_DiscardObjHandle);
	
	return error;
}
