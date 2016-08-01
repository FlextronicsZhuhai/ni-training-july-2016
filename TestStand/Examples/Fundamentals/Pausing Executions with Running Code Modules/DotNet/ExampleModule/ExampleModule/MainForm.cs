using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using NationalInstruments.TestStand.Interop.API;

namespace ExampleModule
{
	public partial class MainForm : Form
	{
		private SequenceContext gSeqContext;
		private bool gThreadSetting;
		private bool gStationOption;
		private PropertyObject mTerminationMonitorData;

		public MainForm(SequenceContext seqContext, bool threadSetting, bool stationOption)
		{
			gSeqContext = seqContext;
			gThreadSetting = threadSetting;
			gStationOption = stationOption;

			InitializeComponent();
		}

		public void InitializeControls()
		{
			ExecStatus.SelectedIndex = 0;
			threadProp.Checked = gThreadSetting;
			stationOption.Checked = gStationOption;
		}

		private void getData_Tick(object sender, EventArgs e)
		{
			if (ExecStatus.SelectedIndex == 0)
			{
				simulateTest.Value++;
				simulateTest.Value = simulateTest.Value % 100;
			}
		}

		private void pollTestStandExecStatus_Tick(object sender, EventArgs e)
		{
			ExecutionRunStates currentRunState;
			ExecutionTerminationStates currentTermState;

			if (this.gSeqContext != null)
				if (this.gSeqContext.Execution != null)
				{
					//get the state of the execution.  the currentRunState parameter indicates whether the execution is paused or running.
					gSeqContext.Execution.GetStates(out currentRunState, out currentTermState);

					if (ExecStatus.SelectedIndex == 0 && currentRunState == ExecutionRunStates.ExecRunState_Paused) //state changed to paused
					{
						simulateTest.Enabled = false;
						ExecStatus.SelectedIndex = 1;

					}
					else if (ExecStatus.SelectedIndex == 1 && currentRunState != ExecutionRunStates.ExecRunState_Paused)  //state changed to running
					{
						simulateTest.Enabled = true;
						ExecStatus.SelectedIndex = 0;
					}

					//check if the TestStand execution has been terminated
					if(mTerminationMonitorData != null)
						if (gSeqContext.Execution.GetTerminationMonitorStatus(mTerminationMonitorData, gSeqContext))
							OKButton_Click(OKButton, new System.EventArgs());
				}
		}

		private void OKButton_Click(object sender, EventArgs e)
		{
			this.Close();
		}

		private void formClosed(object sender, FormClosedEventArgs e)
		{
			this.Close();
		}

		public void InitializeTerminationStateChecking()
		{
			this.mTerminationMonitorData = gSeqContext.Execution.InitTerminationMonitor();
		}

	}
	public class ExampleModule : IDisposable
	{
		private MainForm mDialog = null;

		public void RunTest(SequenceContext seqContext, bool threadSetting, bool stationOption)
		{
			bool previousExternallySuspended = false;

			mDialog = new MainForm(seqContext, threadSetting, stationOption);
			mDialog.InitializeTerminationStateChecking();

			mDialog.InitializeControls();

			if (threadSetting)
			{
				previousExternallySuspended = seqContext.Thread.ExternallySuspended;
				seqContext.Thread.ExternallySuspended = true;
			}

			this.mDialog.ShowDialog();

			if (threadSetting)
				seqContext.Thread.ExternallySuspended = previousExternallySuspended;

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
