using System;
using System.Collections.Generic;
using NationalInstruments.TestStand.Interop.API;

namespace BasicStepTimeReportGenerator
{
	static public class ReportGenerator
	{
		/// <summary>
		/// Generate a unique file name with reportBaseName and
		/// ending with dotExtension in the given reportDirectory.  If the
		/// file requested already exists, attempt to make it unique by
		/// successively appending "_2", "_3", etc. to the reportBaseName.
		/// Give up after maxTries.
		/// </summary>
		/// <param name="reportDirectory">
		/// The directory to put the report in.
		/// </param>
		/// <param name="reportBaseName">
		/// The base name for the report
		/// file.
		/// </param>
		/// <param name="dotExtension">
		/// The extension to use, excluding the '.' character.
		/// </param>
		/// <param name="maxTries">
		/// The number of attempts to make a file
		/// name before giving up.  If a number greater than 1024 is
		/// passed, only 1024 attempts will be made.
		/// </param>
		/// <returns>A string containing the unique file name.</returns>
        public static string GenerateUniqueReportPath(
            string reportDirectory,
            string reportBaseName,
            string[] dotExtension,
            int maxTries )
        {
			reportBaseName = GetValidFileNameForExcel(reportBaseName);
			string uniqueFileName = reportBaseName;

			System.Diagnostics.Debug.Assert(dotExtension.Length != 0);

			if (!System.IO.Directory.Exists(reportDirectory))
				System.IO.Directory.CreateDirectory(reportDirectory);

            // Limit the number of tries to avoid accidentally making this function
            // take a forever.
            maxTries = Math.Min(maxTries, 1024);
			int retry = 1;

			while (true)
			{
				// Find unique file name for the first extension
				for (; retry <= maxTries; ++retry)
				{
					string reportPathForFirstExtension = System.IO.Path.Combine(reportDirectory, uniqueFileName) + "." + dotExtension[0];

					if (!System.IO.File.Exists(reportPathForFirstExtension))
					{
						System.IO.FileStream stream = System.IO.File.Open(reportPathForFirstExtension, System.IO.FileMode.CreateNew);
						stream.Close();
						break;
					}
					else
						uniqueFileName = reportBaseName + "_" + (retry);
				}

				if (retry > maxTries)
					throw new System.IO.IOException("Unable to create unique filename for\"" + System.IO.Path.Combine(reportDirectory, reportBaseName) + "\" after " + maxTries + " attempts.");

				bool isFileNameUniqueForAllExtension = true;

				// Check if the unique file name for the first extension is also valid for all extensions
				for (int i = 1; i < dotExtension.Length; ++i)
				{
					string reportPathForFirstExtension = System.IO.Path.Combine(reportDirectory, uniqueFileName) + "." + dotExtension[i];

					try
					{
						System.IO.FileStream stream = System.IO.File.Open(reportPathForFirstExtension, System.IO.FileMode.CreateNew);
						stream.Close();
					}
					catch (System.IO.IOException)
					{
						isFileNameUniqueForAllExtension = false;
						break;
					}
				}

				// If the file name is unique for all the extensions, break the loop
				if (isFileNameUniqueForAllExtension)
					break;
			}

			return uniqueFileName;
        }

		/// <summary>
		/// Replaces invalid chars for a filename with a space
		/// </summary>
		/// <param name="fileName">Name of file whose invalid chars needs to be replaced</param>
		/// <returns>Valid file name for Microsoft Office Excel</returns>
		private static string GetValidFileNameForExcel(string fileName)
		{
			string validFileName = fileName;

			char[] invalidChars = System.IO.Path.GetInvalidFileNameChars();

			foreach (char invalidChar in invalidChars)
				validFileName = validFileName.Replace(invalidChar, '_');

			validFileName = validFileName.Replace('#', '_');  // # represents separator for worksheet name in Excel. Hence, making it invalid.

			return validFileName;
		}

		/// <summary>
		/// Creates CSV report by using ResultProcessor class to process the ResultList.
		/// </summary>
		/// <param name="reportPath">Path of CSV report</param>
		/// <param name="csvHeader">UUT header information to be inserted into CSV report</param>
		/// <param name="resultList">MainSequence Result</param>
		/// <param name="clientSequenceFilePath">Path of executed sequence file</param>
		[System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Naming", "CA1709")]
		public static void CreateCSVReport(String reportPath, String csvHeader, PropertyObject mainSequenceCallbackResult, string clientSequenceFilePath, 
			string uutSerialNumber, string batchSerialNumber, string testSocketIndex)
		{
			using (System.IO.StreamWriter csvReport = new System.IO.StreamWriter(reportPath))
			{
				// Write the header
				csvReport.WriteLine(csvHeader);

				csvReport.WriteLine(ResultProcessor.GetResultListHeader());

				// mainSequenceCallbackResult can be null when result recording is disabled in station option
				if (mainSequenceCallbackResult != null)
				{
					// Convert the required contents of ResultList into CSV format and insert into the report

					ResultProcessor.UutSerialNumber = uutSerialNumber;
					ResultProcessor.BatchSerialNumber = batchSerialNumber;
					ResultProcessor.TestSocketIndex = testSocketIndex;

					ResultProcessor mainResultProcessor = new ResultProcessor("", "", "");
					mainResultProcessor.ProcessOneResult(mainSequenceCallbackResult);

					LinkedList<string>.Enumerator resultsEnumerator = mainResultProcessor.Results.GetEnumerator();
					while (resultsEnumerator.MoveNext())
						csvReport.WriteLine(resultsEnumerator.Current);
				}
			}
		}

		/// <summary>
		/// Creates a line (row) in CSV file for given UUT information. The values of the line 
		/// will be escaped if necessary.
		/// </summary>
		/// <param name="label">The label of UUT information</param>
		/// <param name="value">The value of UUT information</param>
		/// <returns>String representing line in CSV file with given UUT information</returns>
		[System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Naming", "CA1709:IdentifiersShouldBeCasedCorrectly")]
		public static string GetRowDataForUUTHeader(string label, string value)
		{
			return ResultProcessor.CsvEscape(label) + "," + ResultProcessor.CsvEscape(value);
		}
    }
}
