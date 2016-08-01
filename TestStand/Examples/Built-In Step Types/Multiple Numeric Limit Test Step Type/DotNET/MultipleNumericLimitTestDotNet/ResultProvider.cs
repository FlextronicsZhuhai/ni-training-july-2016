
using System;
using System.Runtime.InteropServices;
using NationalInstruments.TestStand.Interop.API;

namespace NationalInstruments.TestStand.Examples.MultipleNumericLimitTestDotNet
{
	public class ResultProvider
	{

		public void FillArraySlotsIndividually(SequenceContext sequenceContext, out bool errorOccurred, out int errorCode, out string errorMsg)
		{

			errorOccurred = false;
			errorCode = 0;
			errorMsg = string.Empty;

			PropertyObject scPropObj = sequenceContext.AsPropertyObject();
			
			Random rand = new Random();

			try
			{
				scPropObj.SetValNumber("Step.NumericArray[0]", 0, rand.Next(3, 5));
				scPropObj.SetValNumber("Step.NumericArray[1]", 0, rand.Next(3, 5));
				scPropObj.SetValNumber("Step.NumericArray[2]", 0, rand.Next(110, 125));
				scPropObj.SetValNumber("Step.NumericArray[3]", 0, (rand.NextDouble() % 0.5) + 0.5);
				
			}
			catch (COMException e)
			{
				errorOccurred = true;
				errorMsg = e.Message;
				errorCode = e.ErrorCode;
			}

			
		}

		public void FillGivenArray(double[] measurements, out bool errorOccurred, out int errorCode, out string errorMsg)
		{

			errorOccurred = false;
			errorCode = 0;
			errorMsg = string.Empty;

			Random rand = new Random();

			try
			{
				measurements[0] = rand.Next(3, 5);
				measurements[1] = rand.Next(3, 5);
				measurements[2] = rand.Next(110, 125);
				measurements[3] = (rand.NextDouble() % 0.5) + 0.5;

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
