using System;
using System.Runtime.InteropServices;
using TS = NationalInstruments.TestStand.Interop.API;

namespace DisplayingProgressDotNet
{
	public class ProgressDisplayer
	{
		private TS.Thread seqThread;
		private TS.Execution seqExec;

		public void DisplayProgress(TS.SequenceContext seqContext, out bool errorOccurred, out int errorCode, out String errorMsg)
		{
			errorOccurred = false;
			errorCode = 0;
			errorMsg = String.Empty;

			try
			{
				this.seqThread = seqContext.Thread;
				this.seqExec = seqContext.Execution;

				bool quit;

				DateTime start = DateTime.Now;
				
				// run for 10 seconds
				TimeSpan timeToRun = new TimeSpan(0, 0, 10);

				TimeSpan elapsed;
				do
				{
					elapsed = DateTime.Now - start;

					// post progress to progress bar
					double progPercent = elapsed.Seconds * 100 / timeToRun.Seconds;
					this.PostProgressPercent(progPercent);
				
					// post progress to message in increments of 10%
					String progMessage = Math.Floor(progPercent/10) * 10 + " Percent Complete";
					this.PostProgressMessage(progMessage);

					// wait one second
					System.Threading.Thread.Sleep(1000);

					// check to see if sequence execution has been terminated
					quit = this.CheckQuitState();
				}
				while ((elapsed < timeToRun) && !quit);

				// if finished, update progress bar to 100% and post complete message
				if (!quit)
				{
					this.PostProgressPercent(100);
					this.PostProgressMessage("Test Complete");
				}
			
			}
			catch (COMException e)
			{
				errorOccurred = true;
				errorMsg = e.Message;
				errorCode = e.ErrorCode;
			}

		}

		private void PostProgressMessage(String progMessage)
		{
			this.seqThread.PostUIMessageEx(TS.UIMessageCodes.UIMsg_ProgressText, 0, progMessage, null, true);
		}

		private void PostProgressPercent(double progPercent)
		{
			this.seqThread.PostUIMessageEx(TS.UIMessageCodes.UIMsg_ProgressPercent, progPercent, "", null, true);
		}

		private bool CheckQuitState()
		{
			TS.ExecutionRunStates runState;
			TS.ExecutionTerminationStates termState;

			// if the termination state does not indicate normal execution, we should quit
			this.seqExec.GetStates(out runState, out termState);
			return (termState != TS.ExecutionTerminationStates.ExecTermState_Normal);
		}
	}
}
