using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.Text;

using NationalInstruments.TestStand.Interop.API;
using NationalInstruments.TestStand.Utility;

using System.Diagnostics.CodeAnalysis;

namespace SimpleTextReport
{
    // See Types for NI_SimpleTextReport_DotNet.seq.  For each of these
    // types, the "Allow Objects of This Type to be Passed as .Net Structs"
    // box is checked on the ".Net Struct Passing" tab of the properties
    // dialog.
    #region structs directly representing TestStand types


    [SuppressMessage("Microsoft.Naming", "CA1707:IdentifiersShouldNotContainUnderscores", Justification = "This struct exactly matches the name of a TestStand container.")]
    [SuppressMessage("Microsoft.Performance", "CA1815:OverrideEqualsAndOperatorEqualsOnValueTypes")]    
    public struct NI_SimpleTextReport_DotNetOptions
    {
        [SuppressMessage("Microsoft.Design", "CA1051:DoNotDeclareVisibleInstanceFields")]
        public bool PadColumns;
        [SuppressMessage("Microsoft.Design", "CA1051:DoNotDeclareVisibleInstanceFields")]
        public string ResultDirectory;
        [SuppressMessage("Microsoft.Design", "CA1051:DoNotDeclareVisibleInstanceFields")]
        public NI_SimpleTextReport_DotNetColumnDefinition[] ReportColumns;
    }

    [SuppressMessage("Microsoft.Naming", "CA1707:IdentifiersShouldNotContainUnderscores", Justification = "This struct exactly matches the name of a TestStand container.")]
    [SuppressMessage("Microsoft.Performance", "CA1815:OverrideEqualsAndOperatorEqualsOnValueTypes")]    
    public struct NI_SimpleTextReport_DotNetRuntimeVariables
    {
        [SuppressMessage("Microsoft.Design", "CA1051:DoNotDeclareVisibleInstanceFields")]
        public bool ReportBatchSerialNumber;
        [SuppressMessage("Microsoft.Design", "CA1051:DoNotDeclareVisibleInstanceFields")]
        public bool ReportTestSocketIndex;
        [SuppressMessage("Microsoft.Design", "CA1051:DoNotDeclareVisibleInstanceFields")]
        public double EngineStartTimeUtc;
    }

    [SuppressMessage("Microsoft.Naming", "CA1707:IdentifiersShouldNotContainUnderscores", Justification = "This struct exactly matches the name of a TestStand container.")]
    [SuppressMessage("Microsoft.Performance", "CA1815:OverrideEqualsAndOperatorEqualsOnValueTypes")]    
    public struct NI_SimpleTextReport_DotNetColumnDefinition
    {
        [SuppressMessage("Microsoft.Design", "CA1051:DoNotDeclareVisibleInstanceFields")]
        public string Key;
        [SuppressMessage("Microsoft.Design", "CA1051:DoNotDeclareVisibleInstanceFields")]
        public string DisplayName;
    }

    #endregion

    /// <summary>The Reporter class handles many aspects of generating,
    /// formatting, and saving the Simple Text Report.</summary>
    public static class Reporter
    {
        // This section contains specific PropertyObject paths used by the
        // Reporter class.
        
        #region PropertyObject Paths

        // Paths relative to a Result container.
        private const string P_TS = "TS";        
        private const string P_TS_SequenceCall = P_TS + ".SequenceCall";
        private const string P_TS_PostAction = P_TS + ".PostAction";
        private const string P_TS_Server = P_TS + ".Server";        
        private const string P_TS_StartTime = P_TS + ".StartTime";
        private const string P_TS_ThreadComplete = P_TS + ".ThreadComplete";
        private const string P_AsyncId = "AsyncId";
        private const string P_AsyncMode = "AsyncMode";

        // Paths relative to either TS.SequenceCall or TS.PostAction.
        private const string P_Sequence = "Sequence";
        private const string P_SequenceFile = "SequenceFile";
        private const string P_ResultList = "ResultList";

        #endregion

        private static bool IsHandledCallback(string callbackName)
        {
            return (callbackName == "SequenceCall") || (callbackName == "PostAction");
        }

        /// <summary>ProcessResultList() is the main method for generating
        /// the report body.  It takes a ResultList, generates the report
        /// rows for it, and appends them to the report.
        /// 
        /// ProcessResultList() is recursive.  If a sequence call is
        /// encountered, ProcessResultList() will invoke itself on the
        /// ResultList for that sequence call.</summary>
        /// <param name="reportSection">The ReportSection to which the
        /// new data will be appended.</param>
        /// <param name="resultList">The ResultList containing results to
        /// be added to the report.</param>
        /// <param name="options">The standard options associated with
        /// the report plug-in.</param>
        /// <param name="runtimeVariables">Runtime variables associated
        /// with the report plug-in.</param>
        /// <param name="sequence">The name of the sequence with which
        /// resultList is associated.</param>
        /// <param name="sequenceFile">The name of the sequence file
        /// containing sequence.</param>
        /// <param name="threadId">The id of the thread sequence ran
        /// on.</param>
        [SuppressMessage("Microsoft.Design", "CA1045:DoNotPassTypesByReference", MessageId = "2#")]
        [SuppressMessage("Microsoft.Design", "CA1045:DoNotPassTypesByReference", MessageId = "3#")]        
        public static void ProcessResultList(
            ReportSection reportSection,
            PropertyObject resultList,
            ref NI_SimpleTextReport_DotNetOptions options,
            ref NI_SimpleTextReport_DotNetRuntimeVariables runtimeVariables,
            string sequence,
            string sequenceFile,
            int threadId)
        {
            int numElements = resultList.GetNumElements();

            for (int resultIndex = 0; resultIndex < numElements; ++resultIndex)
            {
                PropertyObject result = resultList.GetPropertyObjectByOffset(resultIndex, 0);

                ProcessOneResult(
                    reportSection,
                    result,
                    ref options,
                    ref runtimeVariables,
                    sequence,
                    sequenceFile,
                    threadId,
                    true);
            }
        }


        /// <summary>ProcessResultListOtf() is the entry point for processing
        /// OTF results.  It is very similar to
        /// <see cref="SimpleTextReport.Reporter.ProcessResultList(ReportSection,PropertyObject,ref NI_SimpleTextReport_DotNetOptions,ref NI_SimpleTextReport_DotNetRuntimeVariables,string,string,int)">ProcessResultList()</see>,
        /// but handles the additional requirements involved with OTF.
        /// 
        /// ProcessResultListOtf() is only ever invoked from the "Model
        /// Plugin - OnTheFly Step Results" callback in the
        /// NI_SimpleTextReport_DotNet.seq sequence file.</summary>
        /// <param name="reportSection">The ReportSection to which the
        /// new data will be appended.</param>
        /// <param name="resultList">The ResultList containing results to
        /// be added to the report.</param>
        /// <param name="parentIds">The step ids of the parent steps for
        /// the ResultList.  See model plug-in documentation for "Model
        /// Plugin - OnTheFly Step Results" for more information.</param>
        /// <param name="callbackNames">The names of the callbacks associated
        /// with the results in resultList. See model plug-in documentation
        /// for "Model Plugin - OnTheFly Step Results" for more information.
        /// </param>
        /// <param name="options">The standard options associated with
        /// the report plug-in.</param>
        /// <param name="runtimeVariables">Runtime variables associated
        /// with the report plug-in.</param>
        /// <param name="sequence">The name of the sequence with which
        /// resultList is associated.</param>
        /// <param name="sequenceFile">The name of the sequence file
        /// containing sequence.</param>
        /// <param name="threadId">The id of the thread sequence ran
        /// on.</param>
        [SuppressMessage("Microsoft.Naming", "CA1704:IdentifiersShouldBeSpelledCorrectly", MessageId = "Otf")]
        [SuppressMessage("Microsoft.Design", "CA1045:DoNotPassTypesByReference", MessageId = "4#")]
        [SuppressMessage("Microsoft.Design", "CA1045:DoNotPassTypesByReference", MessageId = "5#")]
        public static void ProcessResultListOtf(
            ReportSection reportSection,
            PropertyObject resultList,
            int [] parentIds,
            string [] callbackNames,
            ref NI_SimpleTextReport_DotNetOptions options,
            ref NI_SimpleTextReport_DotNetRuntimeVariables runtimeVariables,
            string sequence,
            string sequenceFile,
            int threadId )
        {
            int numElements = resultList.GetNumElements();

            for (int resultIndex = 0; resultIndex < numElements; ++resultIndex)
            {
                // Skip all results that are not SequenceCall callbacks.
                // Non-SequenceCall results are not present in the non-OTF case.
                if (IsHandledCallback(callbackNames[resultIndex]))
                {
                    PropertyObject result = resultList.GetPropertyObjectByOffset(resultIndex, 0);

                    // In the OTF case, some results are not actually step
                    // results, but instead indicate the completion of a new
                    // thread.  A simple way to get only the step results is
                    // to filter out results containing a TS.ThreadComplete
                    // property.
                    if (!result.Exists(P_TS_ThreadComplete, 0))
                    {
                        // Process subsequence results recursively only for sequence
                        // calls with the "Use Remote Computer" or "Use New Execution"
                        // Execution Option.  Do not process recursively for "None" or
                        // "Use New Thread."  This option can be determined per the
                        // following table:
                        //
                        // Execution Option      |  AsyncMode				 | TS.Server
                        // ----------------------+---------------------------+-------------------------
                        // "None"                |  Property does not exist. | Property does not exist.
                        // "Use New Thread"      |  True                     | Property does not exist.
                        // "Use New Execution"   |  False                    | Property does not exist.
                        // "Use Remote Computer" |  Property does not exist. | Exists.

                        bool processSubsequenceCalls = false;

                        if (result.Exists(P_AsyncMode, 0))
                        {
                            bool asyncMode = result.GetValBoolean(P_AsyncMode, 0);
                            processSubsequenceCalls = !asyncMode;
                        }
                        else
                        {
                            processSubsequenceCalls = result.Exists(P_TS_Server, 0);
                        }

                        ProcessOneResult(
                            reportSection,
                            result,
                            ref options,
                            ref runtimeVariables,
                            sequence,
                            sequenceFile,
                            threadId,
                            processSubsequenceCalls);
                    }
                }
            }
        }

        /// <summary>ProcessOneResult() is a helper method for 
        /// <see cref="SimpleTextReport.Reporter.ProcessResultList(ReportSection,PropertyObject,ref NI_SimpleTextReport_DotNetOptions,ref NI_SimpleTextReport_DotNetRuntimeVariables,string,string,int)">ProcessResultList()</see>,
        /// and
        /// <see cref="SimpleTextReport.Reporter.ProcessResultListOtf(ReportSection,PropertyObject,int[], String[],ref NI_SimpleTextReport_DotNetOptions,ref NI_SimpleTextReport_DotNetRuntimeVariables,string,string,int)">ProcessResultListOtf()</see>
        /// that performs processing on an individual Result.  This is where
        /// the details of which columns are reported, how they are
        /// formatted, etc. are handled.</summary>
        /// <param name="reportSection">The ReportSection to which the
        /// new data will be appended.</param>
        /// <param name="result">The result to be added to the report.</param>
        /// <param name="options">The standard options associated with
        /// the report plug-in.</param>
        /// <param name="runtimeVariables">Runtime variables associated
        /// with the report plug-in.</param>
        /// <param name="sequence">The name of the sequence with which
        /// resultList is associated.</param>
        /// <param name="sequenceFile">The name of the sequence file
        /// containing sequence.</param>
        /// <param name="threadId">The id of the thread sequence ran
        /// on.</param>
        /// <param name="processSubsequenceCalls">Pass true if ResultLists
        /// attached to TS.SequenceCall objects should be processed.  Pass
        /// false to ignore them.</param>
        private static void ProcessOneResult(
            ReportSection reportSection,
            PropertyObject result,
            ref NI_SimpleTextReport_DotNetOptions options,
            ref NI_SimpleTextReport_DotNetRuntimeVariables runtimeVariables,
            string sequence,
            string sequenceFile,
            int threadId,
            bool processSubsequenceCalls)
        {
            NI_SimpleTextReport_DotNetColumnDefinition[] columns = options.ReportColumns;

            string[] reportRowData = new string[columns.Length];

            for (int columnIndex = 0; columnIndex < columns.Length; ++columnIndex)
            {
                // Initialize the data for the current column to indicate
                // it is missing in case it is not handled by the switch()
                // below.
                reportRowData[columnIndex] = "<MISSING>";

                switch (columns[columnIndex].Key)
                {
                    case "[SEQUENCE]":
                        reportRowData[columnIndex] = sequence;
                        break;

                    case "[SEQUENCE_FILE]":
                        reportRowData[columnIndex] = sequenceFile;
                        break;

                    case "[THREAD_ID]":
                        reportRowData[columnIndex] = threadId.ToString(new NumberFormatInfo());
                        break;

                    case "[TIME]":
                        {
                            double stepTime = result.GetValNumber(P_TS_StartTime, 0);
                            DateTime time = TsToLocalTime(stepTime, runtimeVariables.EngineStartTimeUtc);
                            reportRowData[columnIndex] = String.Format(new DateTimeFormatInfo(), "{0:HH}:{0:mm}:{0:ss}.{0:fff}", time);
                        }
                        break;

                    case "[DATE]":
                        {
                            double stepTime = result.GetValNumber(P_TS_StartTime, 0);
                            DateTime date = TsToLocalTime(stepTime, runtimeVariables.EngineStartTimeUtc);
                            reportRowData[columnIndex] = String.Format(new DateTimeFormatInfo(),"{0:yyyy}/{0:MM}/{0:dd}", date);
                        }
                        break;

                    default: // Treat Key as a look-up string.
                        {
                            if (result.Exists(columns[columnIndex].Key, 0))
                            {
                                reportRowData[columnIndex] = result.GetFormattedValue(columns[columnIndex].Key, 0, "", true, "");
                            }
                        }
                        break;
                }
            }

            AppendReportRow(reportSection, reportRowData, ref options);

            //
            // Done processing the current result.  Process attached ResultList if necessary.
            //

            if (processSubsequenceCalls)
            {
                // If this result contains TS.SequenceCall or TS.PostAction
                // members, each of those members may have a ResultList
                // that needs to be processed.

                string[] subsequenceProperties = new string[] { P_TS_SequenceCall, P_TS_PostAction };

                foreach (string subsequenceType in subsequenceProperties)
                {
                    if (result.Exists(subsequenceType + "." + P_ResultList, 0))
                    {
                        // If the subsequence was invoked on a new thread,
                        // the AsyncId member will exist, and threadId
                        // must be updated.
                        if (result.Exists(P_AsyncId, 0))
                        {
                            threadId = (int)result.GetValNumber(P_AsyncId, 0);
                        }

                        sequence = result.GetValString(subsequenceType + "." + P_Sequence, 0);
                        sequenceFile = result.GetValString(subsequenceType + "." + P_SequenceFile, 0);
                        PropertyObject resultList = result.GetPropertyObject(subsequenceType + "." + P_ResultList, 0);

                        ProcessResultList(
                            reportSection,
                            resultList,
                            ref options,
                            ref runtimeVariables,
                            sequence,
                            sequenceFile,
                            threadId);
                    }
                }
            }
        }

        /// <summary>AppendReportRow() appends a single row to the passed
        /// reportSection.  Its primary use is to create the column headings
        /// and rows for the body of the report, but the Simple Text Report
        /// example also uses it to write the header and footer.</summary>
        /// <param name="reportSection">The ReportSection to which the
        /// new data will be appended.</param>
        /// <param name="data">Array of column entries to be written for the
        /// current row.</param>
        /// <param name="options">The standard options associated with
        /// the report.</param>
        [SuppressMessage("Microsoft.Design", "CA1045:DoNotPassTypesByReference", MessageId = "2#")]
        public static void AppendReportRow(ReportSection reportSection, string[] data, ref NI_SimpleTextReport_DotNetOptions options)
        {
            // There is nothing special about 1024.  It is just a reasonable
            // working size large enough that in typical scenarios, newRow
            // will not have to reallocate its internal buffer.
            StringBuilder newRow = new StringBuilder(1024);

            if (null != data)
            {
                for (int columnIndex = 0; columnIndex < data.Length; ++columnIndex)
                {
                    if (columnIndex > 0)
                    {
                        newRow.Append(',');

                        if (options.PadColumns)
                        {
                            // The minimum column width is simply hard-
                            // coded here, but it need not be.  It could be
                            // included in options and controlled from the
                            // Options dialog, for example.
                            int spaceNeded = WhitespacePadding(24, data[columnIndex - 1]);
                            newRow.Append(' ', spaceNeded);
                        }
                    }

                    data[columnIndex] = CsvEscape(data[columnIndex], false);
                    newRow.Append(data[columnIndex]);
                }
            }

            newRow.Append('\n');

            reportSection.ReportSubsections.Insert(-1, "", newRow.ToString(), "");
        }

        /// <summary>Create a DateTime object representing the given
        /// TestStand time.  TestStand generally represents time using
        /// UTC time with the Engine's start time as the epoch (or
        /// reference time).  This method performs the necessary
        /// conversions to produce a DateTime struct in local time.
        /// </summary>
        /// <seealso cref="SimpleTextReport.Reporter.Ts2UtcTime(double,double)">Ts2UtcTime()</seealso>
        /// <param name="tsTime">Time in seconds since the engine
        /// started.</param>
        /// <param name="engineStartTimeUtc">Engine start time, UTC seconds
        /// since January 1, 1970.</param>
        /// <returns>A DateTime object representing tsTime in local
        /// time.</returns>
        private static DateTime TsToLocalTime(double tsTime, double engineStartTimeUtc)
        {
            return Ts2UtcTime(tsTime, engineStartTimeUtc).ToLocalTime();
        }

        /// <summary>TestStand uses midnight on January 1, 1970 as the epoch.
        /// The .Net DateTime struct uses midnight January 1, 0001.
        /// <see cref="SimpleTextReport.Reporter.Ts2UtcTime(double, double)">Ts2UtcTime()</see>
        /// uses EPOCH_1970_TICKS to perform this conversion.</summary>
        private static readonly long EPOCH_1970_TICKS = new DateTime(1970, 1, 1, 0, 0, 0).Ticks;

        /// <summary>Create a DateTime object representing the given
        /// TestStand time in UTC time.  TestStand generally represents
        /// time using UTC time with the Engine's start time as the epoch
        /// (or reference time).  This method performs the necessary
        /// conversions to produce a DateTime struct in UTC time.
        /// </summary>
        /// <seealso cref="SimpleTextReport.Reporter.TsToLocalTime(double,double)">TsToLocalTime()</seealso>
        /// <param name="tsTime">Time in seconds since the engine
        /// started.</param>
        /// <param name="engineStartTimeUtc">Engine start time, UTC seconds
        /// since January 1, 1970.</param>
        /// <returns>A DateTime object representing tsTime in UTC.</returns>
        private static DateTime Ts2UtcTime(double tsTime, double engineStartTimeUtc)
        {
            tsTime += engineStartTimeUtc;       // seconds since 1970 epoch
            tsTime *= TimeSpan.TicksPerSecond;  // 100-nanosecond "ticks" 1970 epoch
            tsTime += EPOCH_1970_TICKS;         // "ticks" 0001 epoch

            DateTime stepTimeUtc = new DateTime((long)tsTime, DateTimeKind.Utc);
            return stepTimeUtc;
        }

        /// <summary>NEED_CSV_ESCAPE is used by
        /// <see cref="SimpleTextReport.Reporter.CsvEscape(string,bool)">CsvEscape()</see>
        /// to find characters that need quoting and escaping.  Per RFC
        /// 4180, commas, quotes, carriage returns, and line feeds must
        /// be quoted and escaped.</summary>
        private static readonly char[] NEED_CSV_ESCAPE = { ',', '"', '\n', '\r' };

        /// <summary>Quote and escape a CSV field per RFC 4180.</summary>
        /// <param name="field">The field to escape.  A null field is
        /// treated as an empty string.</param>
        /// <param name="always">Pass true to quote all fields, even if
        /// not required by RFC 4180 because none of the special characters
        /// are present.  Pass false to leave fields containing no special
        /// characters unchanged.</param>
        /// <returns>The field quoted and escaped, or the original field if
        /// no escaping is required.</returns>
        private static string CsvEscape(string field, bool always)
        {
            // Treat null fields as empty strings.
            if (null == field)
            {
                field = "";
            }

            if (always || (field.IndexOfAny(NEED_CSV_ESCAPE) != -1))
            {

                // Add an extra 16 bytes to the initial capacity to make enough
                // room to avoid reallocation in most cases.  (Only matters for
                // performance.)
                StringBuilder escapedField = new StringBuilder(field.Length + 16);

                escapedField.Append('"');
                escapedField.Append(field);
                escapedField.Replace("\"", "\"\"", 1, field.Length); // Do not escape the initial quote we just prepended.
                escapedField.Append('"');

                field = escapedField.ToString();
            }

            return field;
        }

        /// <summary>Calculate the number of spaces that must be appended
        /// after the previous column to make that column have the desired
        /// minimum field width.</summary>
        /// <param name="desiredFieldWidth">The desired field width.</param>
        /// <param name="previousField">The previous field.  If previousField
        /// is null, it is treated as an empty string.</param>
        /// <returns>The number of spaces such that when appended to a comma
        /// following the previous field, the next field will begin
        /// desiredFieldWidth characters after the start of the previous
        /// field.  If the required padding would be zero or negative
        /// amount, 1 is returned.</returns>
        private static int WhitespacePadding(int desiredFieldWidth, string previousField)
        {
            int spaceNeeded = desiredFieldWidth - 1; // -1 is for the comma.

            // Treat null fields as empty string.

            if (null != previousField)
            {
                spaceNeeded -= previousField.Length;
            }

            
            return (spaceNeeded > 0)? spaceNeeded : 1;  // Always pad with at least 1 space.
        }

        /// <summary>Returns the argument with invalid file name characters
        /// replaced with underscores.</summary>
        /// <param name="fileName">The file name which may contain invalid
        /// characters.</param>
        /// <returns>The file name with invalid characters replaced by the
        /// underscore, '_', character.</returns>
        private static string replaceInvalidFileNameChars(string fileName)
        {
            char[] invalidPathChars = System.IO.Path.GetInvalidFileNameChars();

            foreach (char invalidChar in invalidPathChars)
            {
                fileName = fileName.Replace(invalidChar, '_');
            }

            return fileName;
        }

        /// <summary>Generate a unique file name with reportBaseName and
        /// ending with dotExtension in the given reportDirectory.  If the
        /// file requested already exists, attempt to make it unique by
        /// successively appending "_2", "_3", etc. to the reportBaseName.
        /// Give up after maxTries.</summary>
        /// <param name="reportDirectory">The directory to put the report
        /// in.</param>
        /// <param name="reportBaseName">The base name for the report
        /// file.</param>
        /// <param name="dotExtension">he extension to use, including the
        /// '.' character.</param>
        /// <param name="maxTries">The number of attempts to make a file
        /// name before giving up.  If a number greater than 1024 is
        /// passed, only 1024 attempts will be made.</param>
        /// <returns>A string containing the unique path.</returns>
        public static string GenerateUniqueReportPath(
            string reportDirectory,
            string reportBaseName,
            string dotExtension,
            int maxTries )
        {
            // Clean up any invalid characters that may be in the base name.
            // We need to clean this up because reportBaseName is constructed
            // from the UUT serial number and other inputs that are not
            // necessarily paths.  We do not clean either reportDirectory
            // or dotExtension because these are explicitly file elements
            // already.  If these are invalid, we want a run time error.
            reportBaseName = replaceInvalidFileNameChars(reportBaseName);
            
            System.IO.Directory.CreateDirectory(reportDirectory);

            string pathBaseName = System.IO.Path.Combine(reportDirectory, reportBaseName);

            string reportPath = pathBaseName + dotExtension;

            // Limit the number of tries to avoid accidentally making this function
            // take a forever.
            maxTries = Math.Min(maxTries, 1024);

            for( int retry=0; retry < maxTries; ++retry )
            {
                try
                {
                    System.IO.FileStream stream = System.IO.File.Open(reportPath, System.IO.FileMode.CreateNew);
                    stream.Close();
                    return reportPath;
                }
                catch (System.IO.IOException)
                {
                    reportPath = pathBaseName + "_" + (retry+2) + dotExtension;
                }
            }

            throw new System.IO.IOException("Unable to create unique filename for\"" + pathBaseName + dotExtension + "\" after " + maxTries + " attempts." );
        }
    }

    internal sealed class Utils
    {
        private Utils() { } // Prevent construction.

        // This section contains constants specific to the TestStand method of
        // localization.
        #region Internationalization / Localization

        // The Simple Text Report's section in ModelStrings.ini
        internal const string LOCALIZED_STRING_SECTION = "SIMPLE_TEXT_REPORT_GENERATOR_CONFIGURATION_DIALOG";
        internal const string COMMON_DLG_SECTION = "COMMON_DLG";

        // Most localization can be handled automatically by the Localizer
        // object in the constructor.  Some items in the File Browse
        // dialog need to be handled explicitly.

        internal const string LOCAL_SELECT_DIRECTORY = "SELECT_DIRECTORY";
        internal const string LOCAL_SIMPLE_TEXT_REPORT_OPTIONS = "SIMPLE_TEXT_REPORT_OPTIONS";
        internal const string COMMON_DLG_OK = "ok";

        #endregion

        /// <summary>A simple wrapper method for GetResourceString().  Most
        /// likely you will not need this because you will probably not need
        /// any TestStand resource strings.  It is used here to support
        /// localization.</summary>
        /// <param name="engine">An instance of the TestStand engine.</param>
        /// <param name="category">The category in the resource .ini
        /// file.</param>
        /// <param name="symbol">The string to replace, defined in the
        /// resource .ini file.</param>
        /// <returns>The requested resource string if found, or symbol if the
        /// resource was not found.</returns>
        internal static string RString(Engine engine, string category, string symbol)
        {
            object found_UNUSED;
            return engine.GetResourceString(category, symbol, symbol, out found_UNUSED);
        }
    }
}
