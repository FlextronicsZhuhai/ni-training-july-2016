using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NationalInstruments.TestStand.Interop.API;
using System.Runtime.InteropServices;

namespace TypeCastingAPIClasses
{
	public class TypeCastingExample
	{
		///Demonstrates how to cast object references in order to access class-specific properties and methods    
		public void CastToMoreGenericClass(SequenceContext seqContext, out string version, out string comment, bool errorOccurred, int errorCode, string errorMsg)
		{
			errorOccurred = false;
			errorCode = 0;
			errorMsg = String.Empty;
			
			version = "";
			comment = "";
			
			try
			{
				SequenceFile SeqFile = seqContext.SequenceFile;

				//Since the version property is a member of the PropertyObjectFile class, you must cast the sequenceFile object to this class to access it
				version = SeqFile.AsPropertyObjectFile().Version;

				//Since the comment property is a member of the PropertyObject class, you must cast the sequenceFile object to this class to access it
				comment = SeqFile.AsPropertyObject().Comment;
			}
			
			//handle errors
			catch (COMException e)
			{
				errorOccurred = true;
				errorMsg = e.Message;
				errorCode = e.ErrorCode;
			}
		}

		///Demonstrates how to cast to a more specific class to access the properties or methods of that class       
		public void CastToMoreSpecificClass(SequenceContext seqContext, out string resultStatus, out double secondsExecuting, bool errorOccurred, int errorCode, string errorMsg)
		{
			errorOccurred = false;
			errorCode = 0;
			errorMsg = String.Empty;

			resultStatus = "";
			secondsExecuting = 0;

			try
			{
				//Get a reference to the first step in the sequence using the GetPropertyObject method, then cast it to the step class to access the ResultStatus property
				Step firstStep = (Step)seqContext.AsPropertyObject().GetPropertyObject("Runstate.Sequence.Main[0]", 0);
				resultStatus = firstStep.ResultStatus;

				//Get a reference to the execution using the GetPropertyObject method, then cast it to the execution class to access the SecondsExecuting property
				Execution currentExec = (Execution)seqContext.AsPropertyObject().GetPropertyObject("Runstate.Execution", 0);
				secondsExecuting = currentExec.SecondsExecuting;
			}

			//handle errors
			catch (COMException e)
			{
				errorOccurred = true;
				errorMsg = e.Message;
				errorCode = e.ErrorCode;
			}
		}
	}
}
