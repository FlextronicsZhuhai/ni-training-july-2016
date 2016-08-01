using System;
using System.Runtime.InteropServices;

namespace NationalInstruments.TestStand.Examples.DisplayArrayInReportDotNet
{
	public class ArrayCreator
	{
		public void GetArray(out double[] resultArray, out bool errorOccurred, out int errorCode, out String errorMsg)
		{
			int numElements = 1024;
			
			errorOccurred = false;
			errorCode = 0;
			errorMsg = String.Empty;
			resultArray = new double[numElements];

			try
			{
				for (int i = 0; i < numElements; i++)
				{
					resultArray[i] = Math.Sin((double)i / numElements * 2 * Math.PI);
				}
			}
			catch (Exception e)
			{
				errorOccurred = true;
				errorMsg = e.Message;
			}
		}
		public void Get2DArray(out double[,] resultArray, out bool errorOccurred, out int errorCode, out String errorMsg)
		{
			int numElements = 6;

			errorOccurred = false;
			errorCode = 0;
			errorMsg = String.Empty;
			resultArray = new double[3, numElements];

			try
			{
				for (int i = 0; i < numElements; i++)
				{
					resultArray[0, i] = ((double)i / 2)-1;
					resultArray[1, i] = (double)i;
					resultArray[2, i] = (double)i * 2 + 1;
				}
			}
			catch (Exception e)
			{
				errorOccurred = true;
				errorMsg = e.Message;
			}
		}

	}
}
