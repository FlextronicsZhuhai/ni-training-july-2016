// CheckStepNameLength.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "CheckStepNameLength.h"
#include "ConfigureCheckStepNameLengthDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//NOTE: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//


// CCheckStepNameLengthApp

BEGIN_MESSAGE_MAP(CCheckStepNameLengthApp, CWinApp)
END_MESSAGE_MAP()


// CCheckStepNameLengthApp construction

CCheckStepNameLengthApp::CCheckStepNameLengthApp()
{
	// NOTE: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CCheckStepNameLengthApp object

CCheckStepNameLengthApp theApp;


// CCheckStepNameLengthApp initialization

BOOL CCheckStepNameLengthApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

//-------------------------------------------------------------------------------
// Constants used by this analysis module. he Rule Id constant must match the
// Rule Id specified in the Edit Rule dialog box.
//-------------------------------------------------------------------------------
const char *cRuleId = "NI_CheckStepNameLengthVCExample";
const char *cMaximumStepNameLengthPropertyName = "MaximumStepNameLength";
const int cDefaultMaximumStepNameLength = 15;

//-------------------------------------------------------------------------------
// Helper function to get the maximum step name length setting for the rule.
//-------------------------------------------------------------------------------
static int GetMaximumStepNameLength(TSAnalyzer::RuleConfigurationPtr ruleConfiguration)
{
	int maximumStepNameLength = cDefaultMaximumStepNameLength;

	// Must check if the setting exists. It's possible that the user never configured the rule in which case
	// the setting does not exist and we use a default value.
	if (ruleConfiguration->ConfigurationData->Exists(cMaximumStepNameLengthPropertyName, 0))
	{
		maximumStepNameLength = (int) ruleConfiguration->ConfigurationData->GetValNumber(cMaximumStepNameLengthPropertyName, 0);
	}
	return maximumStepNameLength;
}

//-------------------------------------------------------------------------------
// Helper function to set the maximum step name length setting for the rule.
//-------------------------------------------------------------------------------
static void SetMaximumStepNameLength(TSAnalyzer::RuleConfigurationPtr ruleConfiguration, int maximumStepNameLength)
{
	ruleConfiguration->ConfigurationData->SetValNumber(cMaximumStepNameLengthPropertyName, TS::PropOption_InsertIfMissing, maximumStepNameLength);
}

//-------------------------------------------------------------------------------
// Configuration Module for the rule. This function displays a dialog and allows
// the user to specify the maximum step name length setting.
//
// You specify the configuration module for a rule on the Advanced tab of the 
// Edit Rule dialog box.
//-------------------------------------------------------------------------------
void __declspec(dllexport) ConfigureCheckStepNameLength(TSAnalyzer::RuleConfigurationContext *configurationContext)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	TSAnalyzer::RuleConfigurationPtr ruleConfiguration = configurationContext->RuleConfiguration;

	CConfigureCheckStepNameLengthDialog dialog;
	dialog.SetMaximumStepNameLength(::GetMaximumStepNameLength(ruleConfiguration));
	
	// Make dialog modal to TestStand application
	int modalID = configurationContext->Engine->NotifyStartOfModalDialog();

	// Display the dialog
	if (dialog.DoModal() == IDOK)
	{
		// Get user response from the dialog
		int maximumStepNameLength = dialog.GetMaximumStepNameLength();

		// Save the setting
		::SetMaximumStepNameLength(ruleConfiguration, maximumStepNameLength);

		// Update the rule description to contain the setting value
		CString description;
		description.Format("Step names must be less than %d characters", maximumStepNameLength);
		ruleConfiguration->Description = _bstr_t(description);

		// Set modified property so that user is prompted to save when closing project
		configurationContext->IsModified = VARIANT_TRUE;
	}

	configurationContext->Engine->NotifyEndOfModalDialog(modalID);
}

//-------------------------------------------------------------------------------
// Analysis Module for the rule. This function examines a step and reports an
// analysis message if the step name is longer than the maximum step name
// length setting.
//
// You specify the function to be called for an analysis module on the
// Edit Analysis Module dialog box.
//-------------------------------------------------------------------------------
void __declspec(dllexport) CheckStepNameLength(TSAnalyzer::AnalysisContext *analysisContext)
{
	TSAnalyzer::RuleConfigurationPtr ruleConfiguration = analysisContext->GetRuleConfiguration(cRuleId);

	// Perform check only if the rule is enabled.
	if (ruleConfiguration->Enabled)
	{
		TS::StepPtr step = analysisContext->Object;
		// Because the analysis module is configured to be called only on steps, the Object in the analysis context will
		// always be a step. We check for NULL just in case the analysis module was configured incorrectly.
		if (step != NULL)
		{
			// Get the setting for the rule
			int maximumStepNameLength = ::GetMaximumStepNameLength(ruleConfiguration);
			// Get value from step
			int stepNameLength = (int) step->Name.length();

			// Check for violation of rule and report message.
			if (stepNameLength > maximumStepNameLength)
			{
				// Create text explaining the violation.
				CString text;
				text.Format("Step name '%s' is too long (%d). The maximum is %d.", (const char *)step->Name, stepNameLength, maximumStepNameLength);

				// Create and report the message to the analyzer. You can pass a different object for the location or
				// you can pass NULL for the location object and use the AnalysisMessage.Locations property to specify the location
				// after creating the message.
				TSAnalyzer::AnalysisMessagePtr message = analysisContext->NewMessage(cRuleId, _bstr_t(text), analysisContext->Object);
				analysisContext->ReportMessage(message);
			}
		}
	}
}
