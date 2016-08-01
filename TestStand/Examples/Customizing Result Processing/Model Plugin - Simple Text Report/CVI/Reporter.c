//==============================================================================
//
// Title:       Reporter.c
//
// Created on:  9/16/2011 at 7:32:33 PM by Jed Beach.
//
//==============================================================================

#include <time.h>

// The #define below suppresses the warning:
//
//  "ShObjIdl.h"(1330,2)   Warning: Empty declaration.
//
// we would otherwise get from including Shlobj.h.  We only need Shlobj.h
// for SHCreateDirectoryEx(), so #defining this away does not cause any
// problems.  The warning is harmless but it was decided this example
// would be cleaner with the warning suppressed.
//
// See also: http://forums.ni.com/t5/LabWindows-CVI/ShObjIdl-h-quot-Empty-declaration-quot-warning-with-CVI-9-0/td-p/895485
//
// If you prefer, you can comment out the #define below, which will restore
// the warning.
#define tagSHCONTF shcontf_dummy { shcontf_dummy } shcontf_dummy_typedef; enum tagSHCONTF
#include <Shlobj.h>

#include "Reporter.h"

#include <tsapicvi.h>
#include <tsutil.h>
#include <toolbox.h>

#include "Utils.h"


//========================================================================
// CONSTANTS
//========================================================================

static const char MISSING[] = "<MISSING>";

//
// Keys for column definitions.  See ProcessOneResult().
//

static const char KEY_SEQUENCE[]      = "[SEQUENCE]";
static const char KEY_SEQUENCE_FILE[] = "[SEQUENCE_FILE]";
static const char KEY_THREAD_ID[]     = "[THREAD_ID]";
static const char KEY_TIME[]          = "[TIME]";
static const char KEY_DATE[]          = "[DATE]";

//
// Paths to PropertyObject members.
//

// Path relative to Result containers.
static const char P_TS_SequenceCall[] = "TS.SequenceCall";
static const char P_TS_PostAction[] = "TS.PostAction";
static const char P_TS_Server[] = "TS.Server";
static const char P_TS_StartTime[] = "TS.StartTime";
static const char P_TS_ThreadComplete[] = "TS.ThreadComplete";
static const char P_AsyncId[] = "AsyncId";
static const char P_AsyncMode[] = "AsyncMode";

// Path relative to TS.SequenceCall or TS.PostAction.
static const char P_Sequence[] = "Sequence";
static const char P_SequenceFile[] = "SequenceFile";
static const char P_ResultList[] = "ResultList";



// Path relative to NI_SimpleTextReport_CVIRuntimeVariables
static const char P_EngineStartTimeUtc[] = "EngineStartTimeUtc";

//========================================================================
// FUNCTION PROTOTYPES FOR STATIC FUNCTIONS
//========================================================================

static int ProcessResultListImp(CAObjHandle, CAObjHandle, CAObjHandle, CAObjHandle, const char *, const char *, int, ErrMsg);
static int ProcessOneResult(CAObjHandle, CAObjHandle, CAObjHandle, CAObjHandle, const char *, const char *, int, BOOL, ErrMsg);
static int AppendReportColumn(SimpleStringBuilder *, const char *, size_t, size_t *, BOOL);
static int TsToLocalTime(double, CAObjHandle, unsigned int *, unsigned int *, unsigned int *, unsigned int *, unsigned int *, unsigned int *, double *, unsigned int *, ErrMsg);
static BOOL IsHandledCallback( const char * ); 

// Append one row to the report.
//
// reportSection -- A handle to the ReportSection object to write the
//        output to.
// columns -- A handle to an PropertyObject representing an array of
//        strings that are to be output in columns.  Passing null
//        is legal and indicates that an empty row is to be appended
//        to the report.
// padColumns -- Pass TRUE if columns are to be padded for better looking
//        display.  Pass FALSE if no extra whitespace is to be used.
// stepResultErrorMsg -- A handle to a string to return an error message
//        if necessary.
//
// return -- Greater than or equal to 0 on success, less than 0 on failure.
int AppendReportRow(
	CAObjHandle reportSection,
	CAObjHandle columns,
	BOOL padColumns,
	CAObjHandle stepResultErrorMsg)
{
	int error = TS_Err_NoError;
	ErrMsg errMsg = {0};
	ERRORINFO errorInfo = {0};

	char * columnString = NULL;
	SimpleStringBuilder reportText = {0};
	TSObj_ReportSections subsections = 0;

	// There is nothing special about 1024.  It is just a reasonable
	// working size large enough that in typical scenarios, newRow
	// will not have to reallocate its internal buffer.
	errChk( SSB_Reserve(&reportText, 1024) );

	if (columns)
	{
		long numColumns = 0;

		tsErrChk( TS_PropertyGetNumElements(columns, &errorInfo, &numColumns) );

		size_t previousFieldLength = 0;

		for (long columnIndex = 0; columnIndex < numColumns; ++columnIndex)
		{
			tsErrChk( TS_PropertyGetValStringByOffset(columns, &errorInfo, columnIndex, TS_PropOption_NoOptions, &columnString) );

			errChk( AppendReportColumn(&reportText, columnString, columnIndex, &previousFieldLength, padColumns) );

			CLEAR(columnString, CA_FreeMemory);
		}
	}

	errChk( SSB_Append(&reportText, "\n") );

	tsErrChk( TS_ReportSectionGetReportSubsections(reportSection,&errorInfo, &subsections) );
	tsErrChk( TS_ReportSectionsInsert(subsections, &errorInfo, -1, "", SSB_GetString(&reportText), "", NULL) );

Error:

	SSB_Destroy(&reportText);
	CLEAR(columnString, CA_FreeMemory);
	CLEAR(subsections, CA_DiscardObjHandle);

	TS_PropertySetValString(stepResultErrorMsg, NULL, "", TS_PropOption_NoOptions, errMsg);

	return error;
}

// Append a single column to the report.
//
// columnData -- A pointer to the SimpleStringBuilder object
//        to write the output to.
// data -- The string to write in the current column.
// columnIndex -- The index of the current column.
//previousFieldLength -- In/Out: A pointer to the length of the previous
//        field must be passed.  The size of the new column including
//        any escaping is stored back.  Cannot be null.
// padColumns -- Pass TRUE if columns are to be padded for a better looking
//        display.  Pass FALSE if no extra whitespace is to be used.
//
// return -- Greater than or equal to 0 on success, less than 0 on failure.
static int AppendReportColumn(
	SimpleStringBuilder * columnData,
	const char * data,
	size_t columnIndex,
	size_t * previousFieldLength,
	BOOL padColumns)
{
	int error = TS_Err_NoError;

	Assert(columnData != 0);
	Assert(previousFieldLength != 0);

	// Treat null data an as empty string.
	if (!data)
	{
		data = "";
	}

	// In any column other than the very first, a comma and whitepace
	// padding must be appended to the previous column.
	if (columnIndex > 0)
	{
		errChk( SSB_Append(columnData, ",") );

		if (padColumns)
		{
			// The minimum column width is simply hardcoded here, but it
			// need not be.  It could be included in the options and
			// controlled from the Options dialog, for example.
			const size_t desiredFieldWidth = 24;
			size_t spaceNeeded = 1; // At least one space is always needed.
			*previousFieldLength += 1; // +1 for the comma.

			if (desiredFieldWidth > *previousFieldLength)
			{
				spaceNeeded = desiredFieldWidth - *previousFieldLength;
			}

			errChk( SSB_AppendChars(columnData, ' ', spaceNeeded) );
		}
	}

	errChk( SSB_CsvEscapeAndAppend(columnData, data, FALSE, previousFieldLength) );

Error:

	return error;
}

// ProcessResultList() is a wrapper for ProcessResultListImp() that handles
// passing back error information to the sequence file.
//
// reportSection -- A handle to the ReportSection to which new data will
//        be added.
// resultList -- A handle to the ResultList containing results to be added
//        to the report
// options -- A handle to the standard options associated with this
//        report plug-in.
// runtimeVariables -- A handle to the runtime variables associated with
//        this report plug-in.
// sequence -- The name of the sequence with which hResultList is
//        associated.
// sequenceFile -- The path of the sequence file containing sequence.
// threadId -- The id of the thread sequence ran on.
// stepResultErrorMsg -- A handle to a string to return an error message
//        if necessary.
//
// return -- Greater than or equal to 0 on success, less than 0 on failure.
int ProcessResultList(
	CAObjHandle reportSection,
	CAObjHandle resultList,
	CAObjHandle options,
	CAObjHandle runtimeVariables,
	const char * sequence,
	const char * sequenceFile,
	int threadId,
	CAObjHandle stepResultErrorMsg)
{
	ErrMsg errMsg = {0};

	const int error = ProcessResultListImp(reportSection, resultList, options, runtimeVariables, sequence, sequenceFile, threadId, errMsg);

	TS_PropertySetValString(stepResultErrorMsg, NULL, "", TS_PropOption_NoOptions, errMsg);

	return error;
}


// ProcessResultListImp() is the main method for generating the report body.
// It takes a ResultList, generates the report rows for it, and appends
// them to the report.
// 
// ProcessResultListImp() is recursive.  If a sequence call is encountered,
// ProcessResultListImp() will invoke itself on the ResultList attached to
// that sequence call.
//
// reportSection -- A handle to the ReportSection to which new data will
//        be added.
// resultList -- A handle to the ResultList containing results to be added
//        to the report
// options -- A handle to the standard options associated with this
//        report plug-in.
// runtimeVariables -- A handle to the runtime variables associated with
//        this report plug-in.
// sequence -- The name of the sequence with which hResultList is
//        associated.
// sequenceFile -- The path of the sequence file containing sequence.
// threadId -- The id of the thread sequence ran on.
// errMsg -- A buffer to hold an error message should an error occur.
//        The buffer must have at least ERRMSG_SIZE bytes.
//
// return -- Greater than or equal to 0 on success, less than 0 on failure.
static int ProcessResultListImp(
	CAObjHandle reportSection,
	CAObjHandle resultList,
	CAObjHandle options,
	CAObjHandle runtimeVariables,
	const char * sequence,
	const char * sequenceFile,
	int threadId,
	ErrMsg errMsg)
{
	int error = TS_Err_NoError;
	ERRORINFO errorInfo = {0};

	CAObjHandle result = 0;

	long numResults = 0;
	tsErrChk( TS_PropertyGetNumElements(resultList, &errorInfo, &numResults) );

	for (long resultIndex = 0; resultIndex < numResults; ++resultIndex)
	{
		tsErrChk( TS_PropertyGetPropertyObjectByOffset(resultList, &errorInfo, resultIndex, TS_PropOption_NoOptions, &result) );

		errChk( ProcessOneResult(
			reportSection,
			result,
			options,
			runtimeVariables,
			sequence,
			sequenceFile,
			threadId,
			TRUE,
			errMsg) );

		CLEAR(result, CA_DiscardObjHandle);
	}

Error:

	CLEAR(result, CA_DiscardObjHandle);

	return error;
}

// ProcessResultListOtf() is the entry point for processing OTF results.
// It is very similar to ProcessResultList() but handles the additional
// requirements involved with on-the-fly reporting..
// 
// ProcessResultListOtf() is only ever invoked from the "Model Plugin -
// OnTheFly Step Results" callback in the NI_SimpleTextReport_CVI.seq
// sequence file.
//
// reportSection -- A handle to the ReportSection to which new data will
//        be added.
// resultList -- A handle to the ResultList containing results to be added
//        to the report
// parentIds -- The array of parent IDs passed to the "Model Plugin -
//        OnTheFly Step Results" callback.
// callbackNames -- The array of callback names passed to the "Model Plugin
//        - OnTheFly Step Results" callback.
// options -- A handle to the standard options associated with this
//        report plug-in.
// runtimeVariables -- A handle to the runtime variables associated with
//        this report plug-in.
// sequence -- The name of the sequence with which hResultList is
//        associated.
// sequenceFile -- The path of the sequence file containing sequence.
// threadId -- The id of the thread sequence ran on.
// stepResultErrorMsg -- A handle to a string to return an error message
//        if necessary.
//
// return -- Greater than or equal to 0 on success, less than 0 on failure.
int ProcessResultListOtf(
	CAObjHandle reportSection,
	CAObjHandle resultList,
	int parentIds[],
	const char * callbackNames[],
	CAObjHandle options,
	CAObjHandle runtimeVariables,
	const char * sequence,
	const char * sequenceFile,
	int threadId,
	CAObjHandle stepResultErrorMsg)
{
	int error = TS_Err_NoError;
	ErrMsg errMsg = {0};
	ERRORINFO errorInfo = {0};

	CAObjHandle result = 0;

	errChk( parentIds? TS_Err_NoError : TS_Err_InvalidPointer );
	errChk( callbackNames? TS_Err_NoError : TS_Err_InvalidPointer );

	long numResults = 0;
	tsErrChk( TS_PropertyGetNumElements(resultList, &errorInfo, &numResults) );

	for (long resultIndex = 0; resultIndex < numResults; ++resultIndex)
	{
        // Skip all results that are not SequenceCall callbacks.  Non-
		// SequenceCall results are not present in the non-OTF case.
		if (IsHandledCallback(callbackNames[resultIndex]))
		{
			tsErrChk( TS_PropertyGetPropertyObjectByOffset(resultList, &errorInfo, resultIndex, TS_PropOption_NoOptions, &result) );

			VBOOL threadCompletePropertyExists = VFALSE;

			tsErrChk( TS_PropertyExists(result, &errorInfo, P_TS_ThreadComplete, TS_PropOption_NoOptions, &threadCompletePropertyExists) );

			// In the OTF case, some results are not actually step
			// results, but instead indicate the completion of a new
			// thread.  A simple way to get only the step results is
			// to filter out results containing a TS.ThreadComplete
			// property.
			if (!threadCompletePropertyExists)
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

				BOOL processSubsequenceCalls = FALSE;

				VBOOL asyncModeExists = VFALSE;
				tsErrChk( TS_PropertyExists(result, &errorInfo, P_AsyncMode, TS_PropOption_NoOptions, &asyncModeExists) );

				if (asyncModeExists)
				{
					VBOOL asyncMode = VFALSE;
					tsErrChk( TS_PropertyGetValBoolean(result, &errorInfo, P_AsyncMode, TS_PropOption_NoOptions, &asyncMode) );
					processSubsequenceCalls = !asyncMode;
				}
				else
				{
					VBOOL serverExists = VFALSE;
					tsErrChk( TS_PropertyExists(result, &errorInfo, P_TS_Server, TS_PropOption_NoOptions, &serverExists) );
					processSubsequenceCalls = !!serverExists;
				}

				errChk( ProcessOneResult(
					reportSection,
					result,
					options,
					runtimeVariables,
					sequence,
					sequenceFile,
					threadId,
					processSubsequenceCalls,
					errMsg) );

				CLEAR(result, CA_DiscardObjHandle);
			}
		}
	}

Error:

	CLEAR(result, CA_DiscardObjHandle);

	TS_PropertySetValString(stepResultErrorMsg, NULL, "", TS_PropOption_NoOptions, errMsg);

	return error;
}


// ProcessOneResult() is a helper method for ProcessResultList() and
// ProcessResultListOtf() that performs processing on an individual Result.
// This is where the details of which columns are reported, how they are
// formatted, etc. are handled.
//
// reportSection -- A handle to the ReportSection to which new data will
//        be added.
// result -- A handle to the Result object with data to be added to the
//        report.
// options -- A handle to the standard options associated with this
//        report plug-in.
// runtimeVariables -- A handle to the runtime variables associated with
//        this report plug-in.
// sequence -- The name of the sequence with which hResult is
//        associated.
// sequenceFile -- The path of the sequence file containing sequence.
// threadId -- The id of the thread sequence ran on.
// processSubsequenceCalls -- Pass true if ResultLists attached to
//        TS.SequenceCall objects should be processed.  Pass false to
//        ignore them.
// errMsg -- A buffer to hold an error message should an error occur.
//        The buffer must have at least ERRMSG_SIZE bytes.
//
// return -- Greater than or equal to 0 on success, less than 0 on failure.
static int ProcessOneResult(
	CAObjHandle reportSection,
	CAObjHandle result,
	CAObjHandle options,
	CAObjHandle runtimeVariables,
	const char * sequence,
	const char * sequenceFile,
	int threadId,
	BOOL processSubsequenceCalls,
	ErrMsg errMsg)
{
	int error = TS_Err_NoError;
	ERRORINFO errorInfo = {0};

	char * key             = NULL;       // clean up with CA_FreeMemory().
	char * propertyString  = NULL;       // clean up with CA_FreeMemory().
	char * subsequence     = NULL;       // clean up with CA_FreeMemory().
	char * subsequenceFile = NULL;       // clean up with CA_FreeMemory().
	SimpleStringBuilder reportText = {0};// clean up with SSB_Destroy().
	CAObjHandle reportColumns = 0;       // clean up with CA_DiscardObjHandle().
	CAObjHandle columnDefinition = 0;    // clean up with CA_DiscardObjHandle().
	CAObjHandle subsequenceProperty = 0; // clean up with CA_DiscardObjHandle().
	CAObjHandle resultList = 0;	         // clean up with CA_DiscardObjHandle().
	TSObj_ReportSections subsections = 0;// clean up with CA_DiscardObjHandle().


	// There is nothing special about 1024.  It is just a reasonable
	// working size large enough that in typical scenarios, reportText
	// will not have to reallocate its internal buffer.
	errChk( SSB_Reserve(&reportText, 1024) );

	// stringBuffer is a working buffer to format items for columns that
	// require special formating.
	//
	// Make sure stringBuffer is large enough for any of the places it may
	// be used.  The current value of 128 is over 2x the worst case that
	// could possibly occur with the current code.  Even so, make sure
	// to use safe functions like snprintf() instead sprintf().
	char stringBuffer[128];
	const size_t stringBufferLength = sizeof(stringBuffer) / sizeof(char);

	size_t previousFieldLength = 0;

	VBOOL vPadColumns = VFALSE;
	tsErrChk( TS_PropertyGetValBoolean(options, &errorInfo, "PadColumns", TS_PropOption_NoOptions, &vPadColumns) );
	const BOOL padColumns = !!vPadColumns;

	tsErrChk( TS_PropertyGetPropertyObject(options, &errorInfo, "ReportColumns", TS_PropOption_NoOptions, &reportColumns) );

	long numColumns = 0;
	tsErrChk( TS_PropertyGetNumElements(reportColumns, &errorInfo, &numColumns) );

	// This loop and switch process the current result.
	for (int columnIndex = 0; columnIndex < numColumns; ++columnIndex)
	{
		const char * columnString = MISSING;

		tsErrChk( TS_PropertyGetPropertyObjectByOffset(reportColumns, &errorInfo, columnIndex, TS_PropOption_NoOptions, &columnDefinition) );
		tsErrChk( TS_PropertyGetValString(columnDefinition, &errorInfo, "Key", TS_PropOption_NoOptions, &key) );

		if (!_mbscmp(key, KEY_SEQUENCE))
		{
			columnString = sequence? sequence : "";
		}
		else if (!_mbscmp(key, KEY_SEQUENCE_FILE))
		{
			columnString = sequenceFile? sequenceFile : "";
		}
		else if (!_mbscmp(key, KEY_THREAD_ID))
		{
			snprintf( stringBuffer, stringBufferLength, "%d", threadId );
			columnString = stringBuffer;
		}
		else if (!_mbscmp(key, KEY_TIME))
		{
			double tsTime = -1;
			unsigned int hour   = -1;
			unsigned int minute = -1;
			unsigned int second = -1;
			double millisecond = -1;

			tsErrChk( TS_PropertyGetValNumber(result, &errorInfo, P_TS_StartTime, TS_PropOption_NoOptions, &tsTime) );

			errChk( TsToLocalTime(tsTime, runtimeVariables, NULL, NULL, NULL, &hour, &minute, &second, &millisecond, NULL, errMsg) );
			millisecond *= 1000.0;  // Convert from fractional seconds to integer milliseconds.

			snprintf(stringBuffer, stringBufferLength, "%02u:%02u:%02u.%03d", hour, minute, second, (int)millisecond);
			columnString = stringBuffer;
		}
		else if (!_mbscmp(key, KEY_DATE))
		{
			double tsTime = -1;
			unsigned int year  = -1;
			unsigned int month = -1;
			unsigned int day   = -1;

			tsErrChk( TS_PropertyGetValNumber(result, &errorInfo, P_TS_StartTime, TS_PropOption_NoOptions, &tsTime) );

			errChk( TsToLocalTime(tsTime, runtimeVariables, &year, &month, &day, NULL, NULL, NULL, NULL, NULL, errMsg) );

			snprintf(stringBuffer, stringBufferLength, "%04u/%02u/%02u", year, month, day);
			columnString = stringBuffer;
		}
		else
		{
			// key did not match any of the special cases, so try using
			// it as a look-up string.

			VBOOL propertyExists = VFALSE;

			tsErrChk( TS_PropertyExists(result, &errorInfo, key, TS_PropOption_NoOptions, &propertyExists) );

			if (propertyExists)
			{
				tsErrChk( TS_PropertyGetFormattedValue(result, &errorInfo, key, TS_PropOption_NoOptions, "", VTRUE, "", &propertyString) );
				columnString = propertyString; // Do not CLEAR propertyString until finished with columnString.
			}
		}

		errChk( AppendReportColumn(&reportText, columnString, columnIndex, &previousFieldLength, padColumns) );

		CLEAR(columnDefinition, CA_DiscardObjHandle);
		CLEAR(propertyString, CA_FreeMemory);
		CLEAR(key, CA_FreeMemory);
	}

	errChk( SSB_Append( &reportText, "\n" ) );

	tsErrChk( TS_ReportSectionGetReportSubsections(reportSection, &errorInfo, &subsections) );
	tsErrChk( TS_ReportSectionsInsert(subsections, &errorInfo, -1, "", SSB_GetString(&reportText), "", NULL) );

	//
	// Done processing the current result.  Process attached ResultList if necessary.
	//

	if (processSubsequenceCalls)
	{
        // If this result contains TS.SequenceCall or TS.PostAction
        // members, each of those members may have a ResultList
        // that needs to be processed.

		const char * subsequenceProperties[] = { P_TS_SequenceCall, P_TS_PostAction, NULL };

		for( int ii=0; NULL != subsequenceProperties[ii]; ++ii )
		{
			const char * const subsequenceType = subsequenceProperties[ii];

			VBOOL subsequenceExists = VFALSE;
			tsErrChk( TS_PropertyExists(result, &errorInfo, subsequenceType, TS_PropOption_NoOptions, &subsequenceExists) );

			if (subsequenceExists)
			{
				tsErrChk( TS_PropertyGetPropertyObject(result, &errorInfo, subsequenceType, TS_PropOption_NoOptions, &subsequenceProperty) );

				VBOOL resultListExists = VFALSE;
				tsErrChk( TS_PropertyExists(subsequenceProperty, &errorInfo, P_ResultList, TS_PropOption_NoOptions, &resultListExists) );

				if (resultListExists)
				{
					//
					// Update the thread id if there is a new thread.
					//
					VBOOL asyncIdExists = VFALSE;
					tsErrChk( TS_PropertyExists(result, &errorInfo, P_AsyncId, TS_PropOption_NoOptions, &asyncIdExists) );

					if (asyncIdExists)
					{
						double doubleThreadId = -1;
						tsErrChk( TS_PropertyGetValNumber(result, &errorInfo, P_AsyncId, TS_PropOption_NoOptions, &doubleThreadId) );
						threadId = (int)doubleThreadId;
					}

					tsErrChk( TS_PropertyGetValString(subsequenceProperty, &errorInfo, P_Sequence,     TS_PropOption_NoOptions, &subsequence) );
					tsErrChk( TS_PropertyGetValString(subsequenceProperty, &errorInfo, P_SequenceFile, TS_PropOption_NoOptions, &subsequenceFile) );

					tsErrChk( TS_PropertyGetPropertyObject(subsequenceProperty, &errorInfo, P_ResultList,   TS_PropOption_NoOptions, &resultList) );

					errChk( ProcessResultListImp(
						reportSection,
						resultList,
						options,
						runtimeVariables,
						subsequence,
						subsequenceFile,
						threadId,
						errMsg) );

					CLEAR(subsequence, CA_FreeMemory);
					CLEAR(subsequenceFile, CA_FreeMemory);
					CLEAR(resultList, CA_DiscardObjHandle);
				}
				
				CLEAR(subsequenceProperty, CA_DiscardObjHandle);
			}
		}
	}

Error:

	CLEAR(key, CA_FreeMemory);
	CLEAR(propertyString, CA_FreeMemory);
	CLEAR(subsequence, CA_FreeMemory);
	CLEAR(subsequenceFile, CA_FreeMemory);
	CLEAR(reportColumns, CA_DiscardObjHandle);
	CLEAR(columnDefinition, CA_DiscardObjHandle);
	CLEAR(subsequenceProperty, CA_DiscardObjHandle);
	CLEAR(resultList, CA_DiscardObjHandle);
	CLEAR(subsections, CA_DiscardObjHandle);
	SSB_Destroy(&reportText);

	return error;
}

// Converts a TestStand step time value to local calendar time components
// using the current system time zone setting.
//
// Pass NULL for any unneeded output parameters.
//
// tsTime -- Number of seconds since the engine started.
// runtimeVariables -- A handle to the RuntimeVariables for this plug-in.
// year -- Output, the year in local calendar time.  May be null.
// month -- Output, the month in local calendar time.  May be null.
// day -- Output, the day of month in local calendar time.  Day will be
//        in the range [1,31].  May be null.
// hour -- Output hour in local calendar time.  May be null.
// minute -- Output, the minute in local calendar time.  May be null.
// second -- Output, the second in local calendar time.  May be null.
// fractionOfSecond -- Output, the fractional seconds in local calendar time.
//            The value will be on the interval [0.000, 1.000).  May be
//            null.
// weekDay -- Output, the day of week in local calendar time.  Day will
//        be in the range [0,6]; 0 is Sunday.
// errMsg -- A buffer to hold an error message should an error occur.
//        The buffer must have at least ERRMSG_SIZE bytes.
//
// return -- Greater than or equal to 0 on success, less than 0 on failure.
static int TsToLocalTime(
	double tsTime,
	CAObjHandle runtimeVariables,
	unsigned int * year,
	unsigned int * month,
	unsigned int * day,
	unsigned int * hour,
	unsigned int * minute,
	unsigned int * second,
	double * fractionOfSecond,
	unsigned int * weekDay,
	ErrMsg errMsg)
{
	int error = TS_Err_NoError;
	ERRORINFO errorInfo = {0};

	// tsTime is in seconds since the engine started.  TestStand Engine
	// start time is in seconds since 1970.  The
	// CVIAbsoluteTimeFromCVIANSITime() function takes time in seconds
	// since 1900.  Convert tsTime to UTC time with January 1, 1900 epoch.

	double engineStartTimeUtc = 0;
	tsErrChk( TS_PropertyGetValNumber(runtimeVariables, &errorInfo, P_EngineStartTimeUtc, TS_PropOption_NoOptions, &engineStartTimeUtc) );

	double epoch1970 = 0;
	MakeDateTime(0, 0, 0, 1, 1, 1970, &epoch1970);

	tsTime += engineStartTimeUtc; // seconds since 1970 epoch
	tsTime += epoch1970;          // seconds since 1900 epoch

	CVIAbsoluteTime absoluteTime = {0};
	errChk( CVIAbsoluteTimeFromCVIANSITime((time_t)tsTime, &absoluteTime) );

	errChk( CVIAbsoluteTimeToLocalCalendar(absoluteTime, year, month, day, hour, minute, second, NULL, weekDay) );

	// fractionOfSecond requires special handling because although
	// CVIAbsoluteTimeToLocalCalendar() theoretically provides the
	// millisecond, fractional seconds were truncated when tsTime was
	// cast to time_t when passed to CVIAbsoluteTimeFromCVIANSITime().
	if (fractionOfSecond)
	{
		double integerPart_UNUSED;
		*fractionOfSecond = modf(tsTime, &integerPart_UNUSED);
	}

Error:

	return error;
}

// Generate a unique file name with reportBaseName and ending with
// dotExtension in the given reportDirectory.  If the file requested already
// exists, attempt to make it unique by successively appending "_2", "_3",
// etc. to the reportBaseName.  Give up after maxTries.
//
// reportPath -- Output:  A handle to the string to write the unique
//        path to.
// reportDirectory -- The directory to put the report in.
// reportBaseName -- The base name for the report file.
// dotExtension -- The extension to use, including the '.' character.
//        The Simple Text Report currently passes ".log" for this parameter.
// maxTries -- The number of attempts to make a file name before giving up.
//        If a number greater than 1024 is passed, only 1024 attempts will
//        be made.
// stepResultErrorMsg -- A handle to a string to return an error message
//        if necessary.
//
// return -- Greater than or equal to 0 on success, less than 0 on failure.
int GenerateUniqueReportPath(
	CAObjHandle reportPath,
	const char * reportDirectory,
	const char * reportBaseName,
	const char * dotExtension,
	size_t maxTries,
	CAObjHandle stepResultErrorMsg)
{
	int error = TS_Err_NoError;
	ErrMsg errMsg = {0};
	ERRORINFO errorInfo = {0};

	SimpleStringBuilder sbCleanedBaseName = {0};    // clean up with SSB_Destroy()
	SimpleStringBuilder sbPathBaseName = {0};       // clean up with SSB_Destroy()
	SimpleStringBuilder sbReportPath = {0};         // clean up with SSB_Destroy()
	SimpleStringBuilder sbOriginalReportPath = {0}; // clean up with SSB_Destroy()
	HANDLE file = INVALID_HANDLE_VALUE;             // clean up with CloseHandle()
	char * errorMessageBuffer = NULL;               // clean up with LocalFree()

	int lastError = ERROR_SUCCESS;

    // Clean up any invalid characters that may be in the base name.
    // We need to clean this up because reportBaseName is constructed
    // from the UUT serial number and other inputs that are not
    // necessarily paths.  We do not clean either reportDirectory
    // or dotExtension because these are explicitly file elements
    // already.  If these are invalid, we want a run time error.
	errChk( SSB_Set(&sbCleanedBaseName, reportBaseName) );
	SSB_ReplaceInvalidFileNameCharacters(&sbCleanedBaseName);
	
	errChk( SSB_Append(&sbPathBaseName, reportDirectory) );

	if (!SSB_EndsWithChar(&sbPathBaseName, '\\'))
	{
		errChk( SSB_Append(&sbPathBaseName, "\\") );
	}

	errChk( SSB_Append(&sbPathBaseName, SSB_GetString(&sbCleanedBaseName)) );

	errChk( SSB_Set(&sbReportPath, SSB_GetString(&sbPathBaseName)) );
	errChk( SSB_Append(&sbReportPath, dotExtension) );

	// Hold on to the first version of the report path in case we need it
	// for an error message.
	errChk( SSB_Set(&sbOriginalReportPath, SSB_GetString(&sbReportPath)) );

	// stringBuffer is a working buffer to format items for columns that
	// require special formating.
	//
	// Make sure stringBuffer is large enough for any of the places it may
	// be used.  Even so, make sure to use safe functions like snprintf()
	// instead sprintf().
	char stringBuffer[1024];
	const size_t stringBufferLength = sizeof(stringBuffer) / sizeof(char);

	{
		lastError = SHCreateDirectoryEx(NULL, reportDirectory, NULL);

		switch (lastError)
		{
			case ERROR_SUCCESS:		   // fall through.
			case ERROR_ALREADY_EXISTS: // fall through.
			case ERROR_FILE_EXISTS:    // do nothing.
				break;

			default:
			{
				error = TS_Err_IOError;

				const DWORD flags = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM;
				FormatMessage(flags, NULL, lastError, 0, (LPTSTR)&errorMessageBuffer, 1, NULL);

				snprintf(stringBuffer, stringBufferLength, "Failed to create result directory \"%s\".\nError 0x%x: %s", reportDirectory, lastError, errorMessageBuffer? errorMessageBuffer : "");
				MessagePopup("Error attempting to create output directory.", stringBuffer);

				CLEAR(errorMessageBuffer, LocalFree);

				goto Error;
			}
		}
	}

	BOOL success = FALSE;

	// Limit the number of tries to avoid accidentally make this function
	// take a forever.
	{
		const size_t TRY_LIMIT = 1024;

		if (maxTries > TRY_LIMIT)
		{
			maxTries = TRY_LIMIT;
		}
	}

	for (int retry=2; retry < (maxTries+2); ++retry)
	{
		file = CreateFile(SSB_GetString(&sbReportPath), GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

		if (INVALID_HANDLE_VALUE != file)
		{
			CloseHandle(file); file = INVALID_HANDLE_VALUE;
			success = TRUE;
			tsErrChk( TS_PropertySetValString(reportPath, &errorInfo, "", TS_PropOption_NoOptions, SSB_GetString(&sbReportPath)) );
			break;
		}

		lastError = GetLastError();

		if (lastError != ERROR_FILE_EXISTS)
		{
			error = TS_Err_IOError;

			const DWORD flags = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM;
			FormatMessage(flags, NULL, lastError, 0, (LPTSTR)&errorMessageBuffer, 1, NULL);

			snprintf(stringBuffer, stringBufferLength, "Failed to create result file \"%s\".\nError 0x%x: %s", SSB_GetString(&sbOriginalReportPath), lastError, errorMessageBuffer? errorMessageBuffer : "");
			MessagePopup("Error attempting to create output file.", stringBuffer);

			CLEAR(errorMessageBuffer, LocalFree);

			goto Error;
		}

		snprintf( stringBuffer, stringBufferLength, "_%d", retry );

		errChk( SSB_Set(&sbReportPath, SSB_GetString(&sbPathBaseName)) );
		errChk( SSB_Append(&sbReportPath,stringBuffer) );
		errChk( SSB_Append(&sbReportPath,dotExtension) );
	}

	if (!success)
	{
		error = TS_Err_FileAlreadyExists;

		const char * ellipsis = "";

		// Make sure that sbOriginalPath will (plus the rest of the error
		// message) will fit in stringBuffer.
		const size_t TRUNC = 600;

		Assert((TRUNC + 256) < stringBufferLength); // 256 is more than enough space for the rest of the message.

		if (SSB_GetLengthInBytes(&sbOriginalReportPath) > TRUNC)
		{
			SSB_Truncate(&sbOriginalReportPath, TRUNC);
			ellipsis = "...";
		}

		snprintf(
			stringBuffer,
			stringBufferLength,
			"Unable to create  unique filename for \"%s%s\" after %d attempts.",
			SSB_GetString(&sbOriginalReportPath),
			ellipsis,
			maxTries);

		MessagePopup("Error", stringBuffer);
	}


Error:

	SSB_Destroy(&sbCleanedBaseName);
	SSB_Destroy(&sbPathBaseName);
	SSB_Destroy(&sbReportPath);
	SSB_Destroy(&sbOriginalReportPath);
	CLEAR(errorMessageBuffer, LocalFree);

	if (file != INVALID_HANDLE_VALUE)
	{
		CloseHandle(file); file = INVALID_HANDLE_VALUE;
	}

	TS_PropertySetValString(stepResultErrorMsg, NULL, "", TS_PropOption_NoOptions, errMsg);

	return error;
}

static BOOL IsHandledCallback( const char * callbackName )
{
	if( callbackName )
	{
		return !strcmp(callbackName, "SequenceCall") || !strcmp(callbackName, "PostAction");
	}
	
	return FALSE;
}
