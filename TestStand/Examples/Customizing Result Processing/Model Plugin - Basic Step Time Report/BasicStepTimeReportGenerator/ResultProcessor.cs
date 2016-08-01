using System;
using NationalInstruments.TestStand.Interop.API;
using System.Collections.Generic;
using System.Text;

namespace BasicStepTimeReportGenerator
{
	class ResultProcessor
	{
		internal ResultProcessor(string parentID, string sequence, string sequenceFile)
		{
			mParentID = parentID;
			mSequence = sequence;
			mSequenceFile = sequenceFile;
			mResults = new LinkedList<string>();

			// parentID will be empty for MainSequence Callback steps present in process model file
			if (string.IsNullOrEmpty(mSequenceFile) && !string.IsNullOrEmpty(parentID))
				mSequenceFile = EMPTY_SEQFILE_NAME;
		}

		/// <summary>
		/// Gets the line (row) to be inserted into CSV file representing heading for each column containing data of Step Result
		/// </summary>
		/// <returns>String representing a line in CSV file to be used as MainSequence Result header</returns>
		internal static string GetResultListHeader()
		{
			string resultListHeader = "SequenceFile,Sequence,StepGroup,StepID,ParentID,StepName,StepType,Id,Status,StartTime,TotalTime,ModuleTime,SequenceCallSequenceFileName,SequenceCallSequenceName,NumLoops,EndingLoopIndex,LoopIndex,UUTSerialNumber,BatchSerialNumber,TestSocketIndex";

			return resultListHeader;
		}

		/// <summary>
		/// Iterates over all the step result present in the given result list and processes the result.
		/// </summary>
		/// <param name="resultList">ResultList representing a sequence call result that contains result of steps in called sequence</param>
		private void ProcessResultList(PropertyObject resultList)
		{
			int numElements = resultList.GetNumElements();

			for (int resultIndex = 0; resultIndex < numElements; ++resultIndex)
			{
				PropertyObject result = resultList.GetPropertyObjectByOffset(resultIndex, 0);
				ProcessOneResult(result);
			}
		}

		/// <summary>
		/// Adds a line (row) containing data from a step result into the string vector which is used to create CSV report.
		/// The function adds SequenceFile, Sequence, StepGroup, StepID, ParentID, StepName, StepType, Id, NumLoops, EndingLoopIndex, LoopIndex, Status, StartTime, TotalTime, ModuleTime
		/// for a given step result.
		/// </summary>
		/// <param name="result">PropertyObject of Result type representing a step result</param>
		internal void ProcessOneResult(PropertyObject result)
		{
			StringBuilder reportForResult = new StringBuilder();

			reportForResult.Append(CsvEscape(mSequenceFile) + ",");
			reportForResult.Append(CsvEscape(mSequence) + ",");
			reportForResult.Append(CsvEscape(result.GetValString(P_TS_StepGroup, PropertyOptions.PropOption_Coerce)) + ",");
			reportForResult.Append(CsvEscape(result.GetValString(P_TS_StepID, PropertyOptions.PropOption_Coerce)) + ",");
			reportForResult.Append(CsvEscape(mParentID) + ",");
			reportForResult.Append(CsvEscape(result.GetValString(P_TS_StepName, PropertyOptions.PropOption_Coerce)) + ",");
			reportForResult.Append(CsvEscape(result.GetValString(P_TS_StepType, PropertyOptions.PropOption_Coerce)) + ",");
			reportForResult.Append(CsvEscape(result.GetValString(P_TS_Id, PropertyOptions.PropOption_Coerce)) + ",");

			reportForResult.Append(CsvEscape(result.GetValString(P_Status, PropertyOptions.PropOption_Coerce)) + ",");
			reportForResult.Append(CsvEscape(result.GetValString(P_TS_StartTime, PropertyOptions.PropOption_Coerce)) + ",");
			reportForResult.Append(CsvEscape(result.GetValString(P_TS_TotalTime, PropertyOptions.PropOption_Coerce)) + ",");

			string moduleTime = "";
			if (result.Exists(P_TS_ModuleTime, 0))
				moduleTime = result.GetValString(P_TS_ModuleTime, PropertyOptions.PropOption_Coerce);
			reportForResult.Append(CsvEscape(moduleTime) + ",");

			string sequenceCallSequenceFileName = "";
			string sequenceCallSequenceName = "";
			if (result.Exists(P_TS_SequenceCall + "." + P_ResultList, 0))
			{
				sequenceCallSequenceFileName = result.GetValString(P_TS_SequenceCall + "." + P_SequenceFile, PropertyOptions.PropOption_Coerce);
				sequenceCallSequenceName = result.GetValString(P_TS_SequenceCall + "." + P_Sequence, PropertyOptions.PropOption_Coerce);

				if (string.IsNullOrEmpty(sequenceCallSequenceFileName))
					sequenceCallSequenceFileName = EMPTY_SEQFILE_NAME;
			}

			reportForResult.Append(CsvEscape(sequenceCallSequenceFileName) + ",");
			reportForResult.Append(CsvEscape(sequenceCallSequenceName) + ",");

			string numLoops = "";
			if (result.Exists(P_TS_NumLoops, 0))
				numLoops = result.GetValString(P_TS_NumLoops, PropertyOptions.PropOption_Coerce);
			reportForResult.Append(CsvEscape(numLoops) + ",");

			string endingLoopIndex = "";
			if (result.Exists(P_TS_EndingLoopIndex, 0))
				endingLoopIndex = result.GetValString(P_TS_EndingLoopIndex, PropertyOptions.PropOption_Coerce);
			reportForResult.Append(CsvEscape(endingLoopIndex) + ",");

			string loopIndex = "";
			if (result.Exists(P_TS_LoopIndex, 0))
				loopIndex = result.GetValString(P_TS_LoopIndex, PropertyOptions.PropOption_Coerce);
			reportForResult.Append(CsvEscape(loopIndex) + ",");

			reportForResult.Append(UutSerialNumber + ",");
			reportForResult.Append(BatchSerialNumber + ",");
			reportForResult.Append(TestSocketIndex);

			mResults.AddLast(reportForResult.ToString());

			// Add lookup string to the callback names like TS.PostAction to process other callbacks
			string[] subsequenceProperties = new string[] { P_TS_SequenceCall };

			foreach (string subsequenceType in subsequenceProperties)
			{
				if (result.Exists(subsequenceType + "." + P_ResultList, 0))
				{
					string parentId = result.GetValString(P_TS_Id, PropertyOptions.PropOption_Coerce);
					string sequence = result.GetValString(subsequenceType + "." + P_Sequence, PropertyOptions.PropOption_Coerce);
					string sequenceFile = result.GetValString(subsequenceType + "." + P_SequenceFile, PropertyOptions.PropOption_Coerce);
					PropertyObject resultList = result.GetPropertyObject(subsequenceType + "." + P_ResultList, 0);

					ResultProcessor subSequenceProcessor = new ResultProcessor(parentId, sequence, sequenceFile);
					subSequenceProcessor.ProcessResultList(resultList);

					LinkedList<string> subSequenceResults = subSequenceProcessor.Results;
					LinkedList<string>.Enumerator resultsEnumerator = subSequenceResults.GetEnumerator();

					while (resultsEnumerator.MoveNext())
						mResults.AddLast(resultsEnumerator.Current);
				}
			}
		}

		#region PropertyObject Paths

		// Paths relative to a Result container.
		private const string P_TS = "TS";
		private const string P_TS_SequenceCall = P_TS + ".SequenceCall";
		private const string P_TS_StepID = P_TS + ".StepId";
		private const string P_TS_StepGroup = P_TS + ".StepGroup";
		private const string P_TS_StepName = P_TS + ".StepName";
		private const string P_TS_StepType = P_TS + ".StepType";
		private const string P_TS_Id = P_TS + ".Id";
		private const string P_TS_NumLoops = P_TS + ".NumLoops";
		private const string P_TS_EndingLoopIndex = P_TS + ".EndingLoopIndex";
		private const string P_TS_LoopIndex = P_TS + ".LoopIndex";
		private const string P_TS_TotalTime = P_TS + ".TotalTime";
		private const string P_TS_ModuleTime = P_TS + ".ModuleTime";
		private const string P_TS_StartTime = P_TS + ".StartTime";

		private const string P_Status = "Status";

		// Paths relative to either TS.SequenceCall or TS.PostAction.
		private const string P_Sequence = "Sequence";
		private const string P_SequenceFile = "SequenceFile";
		private const string P_ResultList = "ResultList";

		#endregion

		private const string EMPTY_SEQFILE_NAME = "UNSAVED_SEQ_FILE";

		private static readonly char[] NEED_CSV_ESCAPE = { ',', '"', '\n', '\r' };

		/// <summary>
		/// Checks if the string needs to be escaped according to CSV standards by checking if the string contains any special characters.
		/// If yes, then double quotes will be added before and after the string and the double quote present in the string will be escaped.
		/// </summary>
		/// <param name="value">String which needs to be escaped to be inserted in CSV file</param>
		/// <returns>String with escaped characters which can be inserted into CSV file</returns>
		internal static string CsvEscape(string value)
		{
			string escapedValue = "";

			if (!string.IsNullOrEmpty(value))
			{
				if (value.IndexOfAny(NEED_CSV_ESCAPE) != -1)
					escapedValue = "\"" + value.Replace("\"", "\"\"") + "\"";
				else
					escapedValue = value;
			}


			return escapedValue;
		}

		public LinkedList<string> Results
		{
			get
			{
				return mResults;
			}
		}

		internal static string UutSerialNumber
		{
			get
			{
				return mUutSerialNumber;
			}

			set
			{
				System.Diagnostics.Debug.Assert(string.IsNullOrEmpty(value) == false);
				mUutSerialNumber = CsvEscape(value);
			}
		}

		internal static string BatchSerialNumber
		{
			get
			{
				return mBatchSerialNumber;
			}

			set
			{
				mBatchSerialNumber = CsvEscape(value);
			}
		}

		internal static string TestSocketIndex
		{
			get
			{
				return mTestSocketIndex;
			}

			set
			{
				mTestSocketIndex = CsvEscape(value);
			}
		}

		private string mParentID;
		private string mSequence;
		private string mSequenceFile;
		private LinkedList<string> mResults;

		[ThreadStatic]
		private static string mUutSerialNumber;
		[ThreadStatic]
		private static string mBatchSerialNumber;
		[ThreadStatic]
		private static string mTestSocketIndex;
	}
}
