using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using NationalInstruments.TestStand.Interop.API;
using NationalInstruments.TestStand.Interop.SequenceAnalyzer;

namespace CheckStepNameLength
{
	static public class SequenceAnalyzerModules
	{
		//-------------------------------------------------------------------------------
		// Constants used by this analysis module. he Rule Id constant must match the
		// Rule Id specified in the Edit Rule dialog box.
		//-------------------------------------------------------------------------------
		const string cRuleId = "NI_CheckStepNameLengthCSharpExample";
		const string cMaximumStepNameLengthPropertyName = "MaximumStepNameLength";
		const int cDefaultMaximumStepNameLength = 15;

		//-------------------------------------------------------------------------------
		// Helper function to get the maximum step name length setting for the rule.
		//-------------------------------------------------------------------------------
		static private int GetMaximumStepNameLength(RuleConfiguration ruleConfiguration)
		{
			int maximumStepNameLength = cDefaultMaximumStepNameLength;

			// Must check if the setting exists. It's possible that the user never configured the rule in which case
			// the setting does not exist and we use a default value.
			if (ruleConfiguration.ConfigurationData.Exists(cMaximumStepNameLengthPropertyName, 0))
			{
				maximumStepNameLength = (int)ruleConfiguration.ConfigurationData.GetValNumber(cMaximumStepNameLengthPropertyName, 0);
			}
			return maximumStepNameLength;
		}

		//-------------------------------------------------------------------------------
		// Helper function to set the maximum step name length setting for the rule.
		//-------------------------------------------------------------------------------
		static private void SetMaximumStepNameLength(RuleConfiguration ruleConfiguration, int maximumStepNameLength)
		{
			ruleConfiguration.ConfigurationData.SetValNumber(cMaximumStepNameLengthPropertyName, PropertyOptions.PropOption_InsertIfMissing, maximumStepNameLength);
		}

		//-------------------------------------------------------------------------------
		// Configuration Module for the rule. This function displays a dialog and allows
		// the user to specify the maximum step name length setting.
		//
		// You specify the configuration module for a rule on the Advanced tab of the 
		// Edit Rule dialog box.
		//-------------------------------------------------------------------------------
		static public void ConfigureCheckStepNameLength(RuleConfigurationContext configurationContext)
		{
			RuleConfiguration ruleConfiguration = configurationContext.RuleConfiguration;
			int maximumStepNameLength = GetMaximumStepNameLength(ruleConfiguration);
			ConfigureCheckStepNameLengthDialog dialog = new ConfigureCheckStepNameLengthDialog(maximumStepNameLength);

			// Make dialog modal to TestStand application
			int modalID = configurationContext.Engine.NotifyStartOfModalDialog();

			if (dialog.ShowDialog() == DialogResult.OK)
			{
				// Get user response from the dialog
				maximumStepNameLength = dialog.MaximumStepNameLength;

				// Save the setting
				SetMaximumStepNameLength(ruleConfiguration, maximumStepNameLength);

				// Update the rule description to contain the setting value
				string description = "Step names must be less than %1 characters";
				description = description.Replace("%1", maximumStepNameLength.ToString());
				ruleConfiguration.Description = description;

				// Set modified property so that user is prompted to save when closing project
				configurationContext.IsModified = true;
			}

			configurationContext.Engine.NotifyEndOfModalDialog(modalID);
		}

		//-------------------------------------------------------------------------------
		// Analysis Module for the rule. This function examines a step and reports an
		// analysis message if the step name is longer than the maximum step name
		// length setting.
		//
		// You specify the function to be called for an analysis module on the
		// Edit Analysis Module dialog box.
		//-------------------------------------------------------------------------------
		static public void CheckStepNameLength(AnalysisContext analysisContext)
		{
			RuleConfiguration ruleConfiguration = analysisContext.GetRuleConfiguration(cRuleId);

			// Perform check only if the rule is enabled.
			if (ruleConfiguration.Enabled)
			{
				Step step = analysisContext.Object as Step;
				// Because the analysis module is configured to be called only on steps, the Object in the analysis context will
				// always be a step. We check for NULL just in case the analysis module was configured incorrectly.
				if (step != null)
				{
					// Get the setting for the rule
					int maximumStepNameLength = GetMaximumStepNameLength(ruleConfiguration);
					// Get value from step
					int stepNameLength = step.Name.Length;

					// Check for violation of rule and report message.
					if (stepNameLength > maximumStepNameLength)
					{
						// Create text explaining the violation.
						string text = "Step name '%1' is too long (%2). The maximum is %3.";
						text = text.Replace("%1", step.Name).Replace("%2", stepNameLength.ToString()).Replace("%3", maximumStepNameLength.ToString());

						// Create and report the message to the analyzer. You can pass a different object for the location or
						// you can pass NULL for the location object and use the AnalysisMessage.Locations property to specify the location
						// after creating the message.
						AnalysisMessage message = analysisContext.NewMessage(cRuleId, text, analysisContext.Object);
						analysisContext.ReportMessage(message);
					}
				}
			}
		}
	}
}
	