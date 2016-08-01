using System;
using System.Runtime.InteropServices;
using NationalInstruments.TestStand.Interop.API;

namespace AccessingPropertiesDotNet
{
	public class DotNetPropertyAccessor
	{
		public void AccessBuiltInProperties(SequenceContext seqContext, out string sequenceName, out int numberOfSteps, out double executionTime, out bool errorOccurred, out int errorCode, out String errorMsg)
		{
			errorOccurred = false;
			errorCode = 0;
			errorMsg = String.Empty;
			sequenceName = "";
			numberOfSteps = 0;
			executionTime = 0;
			
			try
			{
				
				// Use the TestStand API to access built-in properties, such as the current sequence and its name.
				sequenceName = seqContext.Sequence.Name;

				// For some properties, the TestStand API provides a method to get the data, for example the GetNumSteps() method of the Sequence class
				numberOfSteps = seqContext.Sequence.GetNumSteps(StepGroups.StepGroup_Main);

				// The TestStand API also defines that all Execution objects contain a SecondsExecuting property. 
				executionTime = seqContext.Execution.SecondsExecuting;
			}
			catch (COMException e)
			{
				errorOccurred = true;
				errorMsg = e.Message;
				errorCode = e.ErrorCode;
			}
		}

		public void GetStepResults(out string stringtValueTestResult, out double numericLimitTestResult, SequenceContext seqContext, out bool errorOccurred, out int errorCode, out String errorMsg)
		{
			errorOccurred = false;
			errorCode = 0;
			errorMsg = String.Empty;
			stringtValueTestResult = "";
			numericLimitTestResult = 0;

			try
			{
				// This code shows how to obtain the Result property using only dynamic properties.
				// The RunState PropertyObject contains dynamic properties that describe the state of execution in the sequence invocation. 
				// Use the Variables View in TestStand to browse available properties.
				numericLimitTestResult = seqContext.AsPropertyObject().GetValNumber("Runstate.Sequence.Main[\"Numeric Limit Test\"].Result.Numeric", 0);

				// This code shows an alternate approach for attaining the result property.
				// Like RunState, the ThisContext object contains a sequence reference, but unlike RunState, it is a built-in property.
				// i.e. The SequenceContext class defines the Sequence property.  In many cases there are multiple approaches to accessing TestStand properties. 
				stringtValueTestResult = seqContext.Sequence.GetStepByName("String Value Test", StepGroups.StepGroup_Main).AsPropertyObject().GetValString("Result.String", 0);
			}
			catch (COMException e)
			{
				errorOccurred = true;
				errorMsg = e.Message;
				errorCode = e.ErrorCode;
			}
		}

		public void SetStepResults(bool passFail1Result, bool passFail2Result, double[] multipleNumericLimitResults, SequenceContext seqContext, out bool errorOccurred, out int errorCode, out String errorMsg)
		{
			errorOccurred = false;
			errorCode = 0;
			errorMsg = String.Empty;

			try
			{
				// This code shows how to set the Result property using only dynamic properties.
				// The RunState PropertyObject contains dynamic properties that describe the state of execution in the sequence invocation. 
				// Use the Variables View in TestStand to browse available properties.
				seqContext.AsPropertyObject().SetValBoolean("Runstate.Sequence.Main[\"Pass/Fail Test 1\"].Result.PassFail", 0, passFail1Result);

				// This code shows an alternate approach for setting the result property.
				// In this case, the step is accessed using built-in properties. 
				// In many cases there are multiple approaches to access TestStand properties, using either built-in or dynamic properties.
				seqContext.Sequence.GetStepByName("Pass/Fail Test 2", StepGroups.StepGroup_Main).AsPropertyObject().SetValBoolean("Result.PassFail", 0, passFail2Result);

				// Use the TestStand API to set the numeric results for the multiple numeric limit test.  
				// The SetValVariant() method allows you to set the entire array in a single operation.
				seqContext.AsPropertyObject().SetValVariant("Runstate.Sequence.Main[\"Multiple Numeric Limit Test\"].NumericArray", 0, multipleNumericLimitResults);

			}
			catch (COMException e)
			{
				errorOccurred = true;
				errorMsg = e.Message;
				errorCode = e.ErrorCode;
			}
		}

		public void SetVariables(string dynamicPropertyVal, string dynamicRuntimePropertyVal, SequenceContext seqContext, out bool errorOccurred, out int errorCode, out String errorMsg)
		{
			errorOccurred = false;
			errorCode = 0;
			errorMsg = String.Empty;

			try
			{
				// Use the TestStand API to set the Locals.Container.DynamicProperty variable.
				seqContext.AsPropertyObject().SetValString("Locals.Container.DynamicProperty", 0, dynamicPropertyVal);
				
				// Use the TestStand API to create the Locals.Container.RuntimeProperty variable.  
				// Use the InsertIfMissing property option to create the variable if it does not already exist.
				seqContext.AsPropertyObject().SetValString("Locals.Container.DynamicRuntimeProperty", PropertyOptions.PropOption_InsertIfMissing, dynamicRuntimePropertyVal);
			}
			catch (COMException e)
			{
				errorOccurred = true;
				errorMsg = e.Message;
				errorCode = e.ErrorCode;
			}
		}
	}
}
