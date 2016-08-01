using System;
using System.Runtime.InteropServices;
using NationalInstruments.TestStand.Interop.API;

namespace NationalInstruments.TestStand.Examples.AccessingArraysDotNet
{
	public class DotNetArrayAccessor
	{
		public void FillLocalArray(SequenceContext sequenceContext, out bool errorOccurred, out int errorCode, out string errorMsg)
		{
			errorOccurred = false;
			errorCode = 0;
			errorMsg = string.Empty;

			// get the Locals PropertyObject from the SequenceContext
			PropertyObject locals = sequenceContext.Locals;

			if (locals.Exists("NumericArray", 0))
			{
				try
				{
					// since this is a numeric array, it can be cast to a double[] 
					double[] doubleArr = (double[]) locals.GetValVariant("NumericArray", 0);

					// fill the array
					for (int i = 0; i < doubleArr.Length; i++)
					{
						doubleArr[i] = i;
					}

					// store the array back in Locals
					locals.SetValVariant("NumericArray", 0, doubleArr);
				}
				catch (InvalidCastException e)
				{
					errorOccurred = true;
					errorMsg = e.Message;
				}
				catch (COMException e)
				{
					errorOccurred = true;
					errorMsg = e.Message;
					errorCode = e.ErrorCode;
				}

			}
			
		}

		public void Create2DArray(SequenceContext sequenceContext, out bool errorOccurred, out int errorCode, out string errorMsg)
		{
			errorOccurred = false;
			errorCode = 0;
			errorMsg = string.Empty;

			try
			{
				// create and fill the 2d array
				double[,] arr2d = new double[10, 10];
				for (int i = 0; i < arr2d.GetLength(0); i++)
				{
					for (int j = 0; j < arr2d.GetLength(1); j++)
					{
						arr2d[i, j] = i * 10 + j;
					}
				}

				// since this is an array, we can't use the PropOption_InsertIfMissing, so we must create
				// the property explicitly before setting a value to it
				PropertyObject locals = sequenceContext.Locals;
				locals.NewSubProperty("2DArray", PropertyValueTypes.PropValType_Number, true, "", 0);
				locals.SetValVariant("2DArray", 0, arr2d);
			}
			catch (COMException e)
			{
				errorOccurred = true;
				errorMsg = e.Message;
				errorCode = e.ErrorCode;
			}

		}

		public void Access2DArray(SequenceContext sequenceContext, out bool errorOccurred, out int errorCode, out string errorMsg)
		{
			errorOccurred = false;
			errorCode = 0;
			errorMsg = string.Empty;

			try
			{
				PropertyObject locals = sequenceContext.Locals;

				if (locals.Exists("2DArray", 0))
				{
					// since this is a 2d numeric array, it is cast to double[,]
					double[,] arr2d = (double[,]) locals.GetValVariant("2DArray", 0);
				}
			}
			catch (COMException e)
			{
				errorOccurred = true;
				errorMsg = e.Message;
				errorCode = e.ErrorCode;
			}
		}

		public void CreateStringArray(SequenceContext sequenceContext, out bool errorOccurred, out int errorCode, out string errorMsg)
		{
			errorOccurred = false;
			errorCode = 0;
			errorMsg = String.Empty;

			try
			{

				// create and fill array
				string[] strArr = new string[10];
				for (int i = 0; i < strArr.Length; i++)
				{
					strArr[i] = "String" + i;
				}

				PropertyObject locals = sequenceContext.Locals;
				if (!locals.Exists("StringArray", 0))
				{
					// since this is an array, we can't use the PropOption_InsertIfMissing, so we must create
					// the property explicitly before setting a value to it
					locals.NewSubProperty("StringArray", PropertyValueTypes.PropValType_String, true, "", 0);
				}
				locals.SetValVariant("StringArray", 0, strArr);
			}
			catch (COMException e)
			{
				errorOccurred = true;
				errorMsg = e.Message;
				errorCode = e.ErrorCode;
			}

		}

		public void AccessStringArray(SequenceContext sequenceContext, out bool errorOccurred, out int errorCode, out string errorMsg)
		{
			errorOccurred = false;
			errorCode = 0;
			errorMsg = String.Empty;

			try
			{
				PropertyObject locals = sequenceContext.Locals;

				if (locals.Exists("StringArray", 0))
				{
					string[] strArr = (string[])locals.GetValVariant("StringArray", 0);
				}
			}
			catch (InvalidCastException e)
			{
				errorOccurred = true;
				errorMsg = e.Message;
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
