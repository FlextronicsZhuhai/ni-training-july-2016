using System;
using NationalInstruments.TestStand.Interop.API;
using System.Runtime.InteropServices;

namespace NationalInstruments.TestStand.Examples.ComputerMotherboard
{
	/// <summary>
	/// Used to simulate a computer motherboard test.
	/// </summary>
	public class Computer : IDisposable
	{
		private SimulationDialog mDialog = null;
        private simulationData mDialogData;
        SequenceContext mSequenceContext;

		public Computer(NationalInstruments.TestStand.Interop.API.SequenceContext sequenceContext)
		{
            mSequenceContext = sequenceContext;
		}

		public void ComputerSequenceSimulationDialog(out bool errorOccurred, out int errorCode, out String errorMsg)
		{
			errorOccurred = false;
			errorCode = 0;
			errorMsg = String.Empty;

			try
			{
                /* The "using" block will execute the code inside and then dispose of the variable declared in the parenthesis. 
                 * It provides two key advantages over not using this approach:
                      1) Forces explicit garbage collection
                      2) Protects the developer from inadvertently using a variable later in the application 
                 *       where it is not intended to be used. 
                */
                using (this.mDialog = new SimulationDialog(mSequenceContext))
                {
                    this.mDialog.InitializeTerminationStateChecking();
                    this.mDialog.ShowDialog();

                    //retrieve the data from the dialog and store it before disposing the dialog
                    this.mDialogData = mDialog.dialogData;
                }
			}
			catch (COMException e)
			{
				errorOccurred = true;
				errorMsg = e.Message;
				errorCode = e.ErrorCode;
			}
		}

		public void VacuumOn(out bool errorOccurred, out int errorCode, out String errorMsg)
		{
			errorOccurred = false;
			errorCode = 0;
			errorMsg = String.Empty;

			try
			{
				//Turns Vacuum Table On
			}
			catch (COMException e)
			{
				errorOccurred = true;
				errorMsg = e.Message;
				errorCode = e.ErrorCode;
			}
		}

		public bool PowerupTest(out bool errorOccurred, out int errorCode, out String errorMsg)
		{
			errorOccurred = false;
			errorCode = 0;
			errorMsg = String.Empty;

			try
			{
				//Powerup Test
                return !this.mDialogData.PowerFail;
			}
			catch (COMException e)
			{
				errorOccurred = true;
				errorMsg = e.Message;
				errorCode = e.ErrorCode;
				return false;
			}
		}

		public bool RegisterTest(out bool errorOccurred, out int errorCode, out String errorMsg)
		{
			errorOccurred = false;
			errorCode = 0;
			errorMsg = String.Empty;

			try
			{
				//Register Test
				return true;
			}
			catch (COMException e)
			{
				errorOccurred = true;
				errorMsg = e.Message;
				errorCode = e.ErrorCode;
				return false;
			}
		}

		public bool InstrSetTest(out bool errorOccurred, out int errorCode, out String errorMsg)
		{
			errorOccurred = false;
			errorCode = 0;
			errorMsg = String.Empty;

			try
			{
				//Instruction Set Test
                return !this.mDialogData.CpuFail;
			}
			catch (COMException e)
			{
				errorOccurred = true;
				errorMsg = e.Message;
				errorCode = e.ErrorCode;
				return false;
			}
		}

		public bool CacheTest(out bool errorOccurred, out int errorCode, out String errorMsg)
		{
			errorOccurred = false;
			errorCode = 0;
			errorMsg = String.Empty;

			try
			{
				//Cache Test
				return true;
			}
			catch (COMException e)
			{
				errorOccurred = true;
				errorMsg = e.Message;
				errorCode = e.ErrorCode;
				return false;
			}
		}

		public bool FPUTest(out bool errorOccurred, out int errorCode, out String errorMsg)
		{
			errorOccurred = false;
			errorCode = 0;
			errorMsg = String.Empty;

			try
			{
				//FPU Test
				return true;
			}
			catch (COMException e)
			{
				errorOccurred = true;
				errorMsg = e.Message;
				errorCode = e.ErrorCode;
				return false;
			}
		}

		public bool ROMTest(out bool errorOccurred, out int errorCode, out String errorMsg)
		{
			errorOccurred = false;
			errorCode = 0;
			errorMsg = String.Empty;

			try
			{
				//ROM Test
                return !this.mDialogData.RomFail;
			}
			catch (COMException e)
			{
				errorOccurred = true;
				errorMsg = e.Message;
				errorCode = e.ErrorCode;
				return false;
			}
		}

		public bool RAMTest(out bool errorOccurred, out int errorCode, out String errorMsg)
		{
			errorOccurred = false;
			errorCode = 0;
			errorMsg = String.Empty;

			try
			{
				//RAM Test
                return !this.mDialogData.RamFail;
			}
			catch (COMException e)
			{
				errorOccurred = true;
				errorMsg = e.Message;
				errorCode = e.ErrorCode;
				return false;
			}
		}

		public double VideoTest(out bool errorOccurred, out int errorCode, out String errorMsg)
		{
			errorOccurred = false;
			errorCode = 0;
			errorMsg = String.Empty;

			try
			{
				//Video Test
                return this.mDialogData.VideoValue;
			}
			catch (COMException e)
			{
				errorOccurred = true;
				errorMsg = e.Message;
				errorCode = e.ErrorCode;
				return 0.0;
			}
		}

		public double KeyboardTest(out bool errorOccurred, out int errorCode, out String errorMsg)
		{
			errorOccurred = false;
			errorCode = 0;
			errorMsg = String.Empty;

			try
			{
				//Keyboard Test
                return this.mDialogData.KeyboardValue;
			}
			catch (COMException e)
			{
				errorOccurred = true;
				errorMsg = e.Message;
				errorCode = e.ErrorCode;
				return 0;
			}
		}

		public bool RegisterDiagnostics(out bool errorOccurred, out int errorCode, out String errorMsg)
		{
			errorOccurred = false;
			errorCode = 0;
			errorMsg = String.Empty;

			try
			{
				//Register Diagnostics
				return true;
			}
			catch (COMException e)
			{
				errorOccurred = true;
				errorMsg = e.Message;
				errorCode = e.ErrorCode;
				return false;
			}
		}

		public bool InstrSetDiagnostics(out bool errorOccurred, out int errorCode, out String errorMsg)
		{
			errorOccurred = false;
			errorCode = 0;
			errorMsg = String.Empty;

			try
			{
				//Instruction Set Diagnostics
                return !this.mDialogData.CpuFail;
			}
			catch (COMException e)
			{
				errorOccurred = true;
				errorMsg = e.Message;
				errorCode = e.ErrorCode;
				return false;
			}
		}

		public bool CacheDiagnostics(out bool errorOccurred, out int errorCode, out String errorMsg)
		{
			errorOccurred = false;
			errorCode = 0;
			errorMsg = String.Empty;

			try
			{
				//Cache Diagnostics
				return true;
			}
			catch (COMException e)
			{
				errorOccurred = true;
				errorMsg = e.Message;
				errorCode = e.ErrorCode;
				return false;
			}
		}

		public bool FPUDiagnostics(out bool errorOccurred, out int errorCode, out String errorMsg)
		{
			errorOccurred = false;
			errorCode = 0;
			errorMsg = String.Empty;

			try
			{
				//FPU Diagnostics
				return true;
			}
			catch (COMException e)
			{
				errorOccurred = true;
				errorMsg = e.Message;
				errorCode = e.ErrorCode;
				return false;
			}
		}

		public bool ROMDiagnostics(out bool errorOccurred, out int errorCode, out String errorMsg)
		{
			errorOccurred = false;
			errorCode = 0;
			errorMsg = String.Empty;

			try
			{
				//ROM Diagnostics
				return false;
			}
			catch (COMException e)
			{
				errorOccurred = true;
				errorMsg = e.Message;
				errorCode = e.ErrorCode;
				return false;
			}
		}

		public bool RAMDiagnostics(out bool errorOccurred, out int errorCode, out String errorMsg)
		{
			errorOccurred = false;
			errorCode = 0;
			errorMsg = String.Empty;

			try
			{
				//RAM Diagnostics
				return false;
			}
			catch (COMException e)
			{
				errorOccurred = true;
				errorMsg = e.Message;
				errorCode = e.ErrorCode;
				return false;
			}
		}

		public double VideoDiagnostics(out bool errorOccurred, out int errorCode, out String errorMsg)
		{
			errorOccurred = false;
			errorCode = 0;
			errorMsg = String.Empty;

			try
			{
				//Video Diagnostics
				return 0.003;
			}
			catch (COMException e)
			{
				errorOccurred = true;
				errorMsg = e.Message;
				errorCode = e.ErrorCode;
				return 0.0;
			}
		}

		public bool KeyboardDiagnostics(out bool errorOccurred, out int errorCode, out String errorMsg)
		{
			errorOccurred = false;
			errorCode = 0;
			errorMsg = String.Empty;

			try
			{
				//Keyboard Diagnostics
				return false;
			}
			catch (COMException e)
			{
				errorOccurred = true;
				errorMsg = e.Message;
				errorCode = e.ErrorCode;
				return false;
			}
		}

		public double PowerupDiagnostics(out bool errorOccurred, out int errorCode, out String errorMsg)
		{
			errorOccurred = false;
			errorCode = 0;
			errorMsg = String.Empty;

			try
			{
				//Powerup Diagnostics
				return 4.75;
			}
			catch (COMException e)
			{
				errorOccurred = true;
				errorMsg = e.Message;
				errorCode = e.ErrorCode;
				return 0.0;
			}
		}

		public void VacuumOff(out bool errorOccurred, out int errorCode, out String errorMsg)
		{
			errorOccurred = false;
			errorCode = 0;
			errorMsg = String.Empty;

			try
			{
				//Turns Vacuum Table Off
			}
			catch (COMException e)
			{
				errorOccurred = true;
				errorMsg = e.Message;
				errorCode = e.ErrorCode;
			}
		}

		#region IDisposable Members

		public void Dispose()
		{
			if (this.mDialog != null)
			{
				this.mDialog.Dispose();
				this.mDialog = null;
			}
		}

		#endregion
	}
}
