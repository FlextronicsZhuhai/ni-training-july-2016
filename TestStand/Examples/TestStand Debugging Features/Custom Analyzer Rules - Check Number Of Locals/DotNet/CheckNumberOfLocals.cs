using System;
using System.Collections.Generic;
using System.Text;
using NationalInstruments.TestStand.Interop.SequenceAnalyzer;
using NationalInstruments.TestStand.Interop.API;

namespace CheckNumberOfLocals
{
	static public class SequenceAnalyzerModules
	{
		//-------------------------------------------------------------------------------
		// Constants used by this analysis module. These strings must match those
		// in the Edit Analysis Module dialog box.
		//-------------------------------------------------------------------------------
		private const string cRuleId = "NI_CheckNumberOfLocalsCSharpExample";
		private const string cRuleSettingName = "Maximum Number of Locals";

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
		public static void CheckNumberOfLocals(AnalysisContext analysisContext)
		{
			RuleConfiguration ruleConfiguration = analysisContext.GetRuleConfiguration(cRuleId);

			// Perform check only if the rule is enabled.
			if (ruleConfiguration.Enabled)
			{
				PropertyObject ruleData = analysisContext.GetRuleAnalysisData(cRuleId, RuleAnalysisDataScope.RuleAnalysisDataScope_File, GetRuleAnalysisDataOptions.GetRuleAnalysisDataOption_NoOptions);

				if (analysisContext.Transition == AnalysisTransition.AnalysisTransition_BeforeSequenceLocals)
				{
					// Analyzer is about to analyze sequence locals: reset the count
					ruleData.SetValNumber("NumberOfLocals", PropertyOptions.PropOption_InsertIfMissing, 0.0);
				}
				else if (analysisContext.Transition == AnalysisTransition.AnalysisTransition_AfterSequenceLocals)
				{
					// Analyzer has just analyzed sequence locals: check the count.
					// Get the number of locals in this sequence.
					int numberOfLocals;
					numberOfLocals = (int)ruleData.GetValNumber("NumberOfLocals", 0);

					// Get the setting for the rule.
					int maximumNumberOfLocalsAllowed = (int)ruleConfiguration.RuleSettingValues.GetNumberValue(cRuleSettingName);

					// Report message if there are more locals than the maximum specified by the rule setting.
					if (numberOfLocals > maximumNumberOfLocalsAllowed)
					{
						Sequence sequence = analysisContext.Object as Sequence;

						// Create text explaining the violation.
						string text = "Too many locals in sequence '%1': '%2'. The maximum is %3.";
						text = text.Replace("%1", sequence.Name).Replace("%2", numberOfLocals.ToString()).Replace("%3", maximumNumberOfLocalsAllowed.ToString());

						// Create and report the message to the analyzer. Specify sequence locals as the location associated with the message.
						AnalysisMessage message = analysisContext.NewMessage(cRuleId, text, sequence.Locals);
						analysisContext.ReportMessage(message);
					}
				}
				else
				{
					// Analyzer is analyzing a sequence local: increment the count.
					int numberOfLocals = (int)ruleData.GetValNumber("NumberOfLocals", 0);
					ruleData.SetValNumber("NumberOfLocals", 0, numberOfLocals + 1);
				}
			}
		}
	}
}
