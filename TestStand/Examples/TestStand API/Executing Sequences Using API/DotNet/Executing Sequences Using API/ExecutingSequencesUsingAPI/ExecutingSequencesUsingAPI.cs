using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NationalInstruments.TestStand.Interop.API;    // TestStand Core API.  Add <TestStand>\API\DotNet\Assemblies\CurrentVersion\NationalInstruments.TestStand.Interop.API.dll to the project as a reference.
using System.Runtime.InteropServices;


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Title:       Executing Sequences Using API.cs
//
// Description: This file holds the three methods used in the Executing Sequences Using API
//              for TestSTand.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

namespace ExecutingSequencesUsingAPI
{
    public class TestStandSequenceCalls
    {
        
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        //
        //	This method executes a sequence with no process model.
        //
        //	Inputs:
        //		seqContext:	    		The sequence context.
        //		sequenceFileToRun:		The name of the sequence file to run located in the TestStand search directories.
        //		sequenceNameParameter:	The name of the sequence to run within the sequence file.
        //
        //	Outputs:
        //		errorOccured:			TRUE or FALSE to represent if an error has occured or not.
        //		errorCode:				The error code if errorOccured is TRUE.
        //		errorMsg:				The error message if errorOccured is TRUE.
        //
        public void ExecuteWithNoProcessModel(SequenceContext seqContext, string sequenceFileToRun, string sequenceNameParameter,
            out bool errorOccurred, out int errorCode, out String errorMsg)
        {
           
            string absolutePath;
            bool userCancelled;

            errorOccurred = false;
            errorCode = 0;
            errorMsg = String.Empty;

            try
            {
                // Find the sequence file absolute path based on the calling sequence file's directory.
                seqContext.Engine.FindFile(sequenceFileToRun, out absolutePath, out userCancelled, FindFilePromptOptions.FindFile_PromptHonorUserPreference,
                    FindFileSearchListOptions.FindFile_AddDirToSrchList_No, false, seqContext.SequenceFile);

                // Locate and open the sequence file contianing the sequence to be executed.
				SequenceFile targetSeqFile = seqContext.Engine.GetSequenceFileEx(absolutePath);

                // Launch a new execution of the sequence.
				Execution currentExecution = seqContext.Engine.NewExecution(targetSeqFile, sequenceNameParameter, null, false, 0);

                // Wait for the execution to end.
                currentExecution.WaitForEndEx(-1, true, Type.Missing, seqContext);

                // Release the sequence file opened previously.
                seqContext.Engine.ReleaseSequenceFileEx(targetSeqFile, 0);


            }
            catch (COMException e)
            {
                errorOccurred = true;
                errorMsg = e.Message;
                errorCode = e.ErrorCode;
            }
        }

        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        //
        //	This method executes a sequence with a process model.
        //
        //	Inputs:
        //		seqContext: 			The sequence context.
        //		sequenceFileToRun:		The name of the sequence file to run located in the TestStand search directories.
        //		processModelName:		The name of the process model to run located in the TestStand search directoreis.
        //		sequenceNameParameter:	The name of the sequence to run within the sequence file.
        //
        //	Outputs:
        //		errorOccured:			TRUE or FALSE to represent if an error has occured or not.
        //		errorCode:				The error code if errorOccured is TRUE.
        //		errorMsg:				The error message if errorOccured is TRUE.
        //
        public void ExecuteWithProcessModel(SequenceContext seqContext, string sequenceFileToRun, string processModelName, string sequenceNameParameter,
            out bool errorOccurred, out int errorCode, out String errorMsg)
        {

            string absolutePath;
            bool userCancelled;

            errorOccurred = false;
            errorCode = 0;
            errorMsg = String.Empty;

            try
            {
                // Find the sequence file absolute path based on the calling sequence file's directory.
                seqContext.Engine.FindFile(sequenceFileToRun, out absolutePath, out userCancelled, FindFilePromptOptions.FindFile_PromptHonorUserPreference,
                    FindFileSearchListOptions.FindFile_AddDirToSrchList_Ask, false, seqContext.SequenceFile);

                // Locate and open the sequence file contianing the sequence to be executed.
				SequenceFile targetSeqFile = seqContext.Engine.GetSequenceFileEx(absolutePath);

                // Locate and open the process model to be used for this execution.
				SequenceFile processModel = seqContext.Engine.GetSequenceFileEx(processModelName, GetSeqFileOptions.GetSeqFile_FindFile, TypeConflictHandlerTypes.ConflictHandler_Error);

                // Launch a new execution of the sequence file using the specified process model.
				// The SequenceNameParameter is the name of the process model entry point
				Execution currentExecution = seqContext.Engine.NewExecution(targetSeqFile, sequenceNameParameter, processModel, false, 0);

                // Wait for the execution to end.
                currentExecution.WaitForEndEx(-1, true, Type.Missing, seqContext);

                // Release the process model opened previously.
                seqContext.Engine.ReleaseSequenceFileEx(processModel);
                
                // Release the sequence file opened previously.
                seqContext.Engine.ReleaseSequenceFileEx(targetSeqFile, 0);


            }
            catch (COMException e)
            {
                errorOccurred = true;
                errorMsg = e.Message;
                errorCode = e.ErrorCode;
            }
        }

        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        //
        //	This method executes a sequence with sequence parameters.
        //
        //	Inputs:
        //		seqContext: 			The sequence context.
        //		sequenceFileToRun:		The name of the sequence file to run located in the TestStand search directories.
        //		sequenceNameParameter:	The name of the sequence to run within the sequence file.
        //		numberValue:			A number to be set as a parameter and displayed to the user.
        //		stringValue:			A string to be set as a parameter and displayed to the user.
        //
        //	Outputs:
        //		errorOccured:			TRUE or FALSE to represent if an error has occured or not.
        //		errorCode:				The error code if errorOccured is TRUE.
        //		errorMsg:				The error message if errorOccured is TRUE.
        //
        public void ExecuteWithSequenceParameters(SequenceContext seqContext, string sequenceFileToRun, string sequenceNameParameter, double numberValue,
            string stringValue, out bool errorOccurred, out int errorCode, out String errorMsg)
        {

            string absolutePath;
            bool userCancelled;

            errorOccurred = false;
            errorCode = 0;
            errorMsg = String.Empty;

            try
            {
                // Find the sequence file absolute path based on the calling sequence file's directory.
                seqContext.Engine.FindFile(sequenceFileToRun, out absolutePath, out userCancelled, FindFilePromptOptions.FindFile_PromptHonorUserPreference,
					FindFileSearchListOptions.FindFile_AddDirToSrchList_Ask, false, seqContext.SequenceFile);

                // Locate and open the sequence file contianing the sequence to be executed.
				SequenceFile targetSeqFile = seqContext.Engine.GetSequenceFileEx(absolutePath);


                // Create a PropertyObject with a subproperty for each parameter.  Subproperties must be in the same order as parameters appear in the sequence.
				PropertyObject sequenceParameters = seqContext.Engine.NewPropertyObject(PropertyValueTypes.PropValType_Container, false, "", 0);
				sequenceParameters.SetValNumber("NumberVal", PropertyOptions.PropOption_InsertIfMissing, numberValue);    // Use PropOption_InsertIfMissing to create the subproperty if it does not exist.
				sequenceParameters.SetValString("StringVal", PropertyOptions.PropOption_InsertIfMissing, stringValue);

                // Launch a new execution of the sequence.
				Execution currentExecution = seqContext.Engine.NewExecution(targetSeqFile, sequenceNameParameter, null, false, 0, sequenceParameters);

                // Wait for the execution to end.
                currentExecution.WaitForEndEx(-1, true, Type.Missing, seqContext);

                // Release the sequence file opened previously.
                seqContext.Engine.ReleaseSequenceFileEx(targetSeqFile, 0);

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
