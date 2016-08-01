// Note:	This application has a manifest file in the project. This manifest file includes the Microsoft.Windows.Common-Controls which 
//			enables the application to display controls using the XP theme that the operating system selects.
//			A post build event embeds this manifest file into the executable.
//			In order for the manifest file to enable the executable to display with the XP theme:
//			1. The manifest file must have the same name as the executable. For example, if your executable is named MyExecutable.exe, your manifest file is required to have the name MyExecutable.exe.manifest.
//			2. The manifest file must include the Microsoft.Windows.Common-Controls.
//			3. The manifest file must reside in the same directory as the executable.
//			Also note that if you enable the Project Properties>>Debug>>Enable Visual Studio Hosting Process option, the XP theme adaption does not occur when debugging the executable
//			because the Visual Studio environment creates the process and does not allow the manifest file to be embedded into the executable.

// This example shows the basic architecture of a TestStand user interface application.  
// This example is for demonstrational purposes and not intended for use in real applications as-is.  
// Refer to the TestStand help for more information on using this example.

using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;

// TestStand Core API 
using NationalInstruments.TestStand.Interop.API;

// TestStand User Interface Controls
using NationalInstruments.TestStand.Interop.UI;
using NationalInstruments.TestStand.Interop.UI.Support;

// .net specific functions for use with TestStand APIs (TSUtil)
using NationalInstruments.TestStand.Utility;
 
namespace TestExec
{
	/// <summary>
	/// Summary description for MainForm.
	/// </summary>
	public class MainForm : System.Windows.Forms.Form
	{
		private NationalInstruments.TestStand.Interop.UI.Ax.AxApplicationMgr axApplicationMgr;
		private System.Windows.Forms.Timer GCTimer;
		private NationalInstruments.TestStand.Interop.UI.Ax.AxSequenceFileViewMgr axSequenceFileViewMgr;
		private System.ComponentModel.IContainer components;

		private const int WM_QUERYENDSESSION = 0x11;
		private TextBox currentSeqFilePathTextBox;
		private System.Windows.Forms.Label curFileLabel;
		private System.Windows.Forms.Label testResultslabel;
		private DataGridView dataGridView1;
		private DataGridViewTextBoxColumn ReportFilePath;
		private DataGridViewTextBoxColumn TestResult;
		private System.Windows.Forms.Button openSeqFileButton;
		private System.Windows.Forms.Button executeButton;

		// flag that will be set to true if the user tries to shut down windows
		private bool		sessionEnding = false;

		public MainForm()
		{
			// Required for Windows Form Designer support
			InitializeComponent();

			// NOTE: Add any constructor code after InitializeComponent call
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if (components != null) 
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
			this.axApplicationMgr = new NationalInstruments.TestStand.Interop.UI.Ax.AxApplicationMgr();
			this.GCTimer = new System.Windows.Forms.Timer(this.components);
			this.axSequenceFileViewMgr = new NationalInstruments.TestStand.Interop.UI.Ax.AxSequenceFileViewMgr();
			this.currentSeqFilePathTextBox = new System.Windows.Forms.TextBox();
			this.curFileLabel = new System.Windows.Forms.Label();
			this.testResultslabel = new System.Windows.Forms.Label();
			this.dataGridView1 = new System.Windows.Forms.DataGridView();
			this.ReportFilePath = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.TestResult = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.openSeqFileButton = new System.Windows.Forms.Button();
			this.executeButton = new System.Windows.Forms.Button();
			((System.ComponentModel.ISupportInitialize)(this.axApplicationMgr)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.axSequenceFileViewMgr)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
			this.SuspendLayout();
			// 
			// axApplicationMgr
			// 
			this.axApplicationMgr.Enabled = true;
			this.axApplicationMgr.Location = new System.Drawing.Point(303, 60);
			this.axApplicationMgr.Name = "axApplicationMgr";
			this.axApplicationMgr.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axApplicationMgr.OcxState")));
			this.axApplicationMgr.Size = new System.Drawing.Size(32, 32);
			this.axApplicationMgr.TabIndex = 16;
			this.axApplicationMgr.ExitApplication += new System.EventHandler(this.axApplicationMgr_ExitApplication);
			this.axApplicationMgr.ReportError += new NationalInstruments.TestStand.Interop.UI.Ax._ApplicationMgrEvents_ReportErrorEventHandler(this.axApplicationMgr_ReportError);
			this.axApplicationMgr.DisplaySequenceFile += new NationalInstruments.TestStand.Interop.UI.Ax._ApplicationMgrEvents_DisplaySequenceFileEventHandler(this.axApplicationMgr_DisplaySequenceFile);
			this.axApplicationMgr.EndExecution += new NationalInstruments.TestStand.Interop.UI.Ax._ApplicationMgrEvents_EndExecutionEventHandler(this.axApplicationMgr_EndExecution);
			// 
			// GCTimer
			// 
			this.GCTimer.Interval = 3000;
			this.GCTimer.Tick += new System.EventHandler(this.GCTimerTick);
			// 
			// axSequenceFileViewMgr
			// 
			this.axSequenceFileViewMgr.Enabled = true;
			this.axSequenceFileViewMgr.Location = new System.Drawing.Point(341, 60);
			this.axSequenceFileViewMgr.Name = "axSequenceFileViewMgr";
			this.axSequenceFileViewMgr.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axSequenceFileViewMgr.OcxState")));
			this.axSequenceFileViewMgr.Size = new System.Drawing.Size(32, 32);
			this.axSequenceFileViewMgr.TabIndex = 17;
			// 
			// currentSeqFilePathTextBox
			// 
			this.currentSeqFilePathTextBox.Location = new System.Drawing.Point(13, 31);
			this.currentSeqFilePathTextBox.Name = "currentSeqFilePathTextBox";
			this.currentSeqFilePathTextBox.ReadOnly = true;
			this.currentSeqFilePathTextBox.Size = new System.Drawing.Size(689, 20);
			this.currentSeqFilePathTextBox.TabIndex = 24;
			// 
			// curFileLabel
			// 
			this.curFileLabel.AutoSize = true;
			this.curFileLabel.Location = new System.Drawing.Point(13, 12);
			this.curFileLabel.Name = "curFileLabel";
			this.curFileLabel.Size = new System.Drawing.Size(112, 13);
			this.curFileLabel.TabIndex = 25;
			this.curFileLabel.Text = "Current Sequence File";
			// 
			// testResultslabel
			// 
			this.testResultslabel.AutoSize = true;
			this.testResultslabel.Location = new System.Drawing.Point(13, 82);
			this.testResultslabel.Name = "testResultslabel";
			this.testResultslabel.Size = new System.Drawing.Size(66, 13);
			this.testResultslabel.TabIndex = 26;
			this.testResultslabel.Text = "Test Results";
			// 
			// dataGridView1
			// 
			this.dataGridView1.AllowUserToAddRows = false;
			this.dataGridView1.AllowUserToDeleteRows = false;
			this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
			this.dataGridView1.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.ReportFilePath,
            this.TestResult});
			this.dataGridView1.Location = new System.Drawing.Point(12, 98);
			this.dataGridView1.Name = "dataGridView1";
			this.dataGridView1.Size = new System.Drawing.Size(689, 397);
			this.dataGridView1.TabIndex = 27;
			// 
			// ReportFilePath
			// 
			this.ReportFilePath.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
			this.ReportFilePath.HeaderText = "Report File Path";
			this.ReportFilePath.Name = "ReportFilePath";
			// 
			// TestResult
			// 
			this.TestResult.HeaderText = "Test Result";
			this.TestResult.Name = "TestResult";
			// 
			// openSeqFileButton
			// 
			this.openSeqFileButton.Location = new System.Drawing.Point(416, 57);
			this.openSeqFileButton.Name = "openSeqFileButton";
			this.openSeqFileButton.Size = new System.Drawing.Size(140, 23);
			this.openSeqFileButton.TabIndex = 28;
			this.openSeqFileButton.Text = "Open Sequence File";
			this.openSeqFileButton.UseVisualStyleBackColor = true;
			this.openSeqFileButton.Click += new System.EventHandler(this.openSeqFileButton_Click);
			// 
			// executeButton
			// 
			this.executeButton.Location = new System.Drawing.Point(562, 57);
			this.executeButton.Name = "executeButton";
			this.executeButton.Size = new System.Drawing.Size(140, 23);
			this.executeButton.TabIndex = 29;
			this.executeButton.Text = "Execute";
			this.executeButton.UseVisualStyleBackColor = true;
			this.executeButton.Click += new System.EventHandler(this.executeButton_Click);
			// 
			// MainForm
			// 
			this.ClientSize = new System.Drawing.Size(713, 505);
			this.Controls.Add(this.executeButton);
			this.Controls.Add(this.openSeqFileButton);
			this.Controls.Add(this.dataGridView1);
			this.Controls.Add(this.testResultslabel);
			this.Controls.Add(this.curFileLabel);
			this.Controls.Add(this.currentSeqFilePathTextBox);
			this.Controls.Add(this.axSequenceFileViewMgr);
			this.Controls.Add(this.axApplicationMgr);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.MaximizeBox = false;
			this.Name = "MainForm";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "Simple Test Executive Operator Interface Example";
			this.Closing += new System.ComponentModel.CancelEventHandler(this.MainForm_Closing);
			this.Load += new System.EventHandler(this.MainForm_Load);
			((System.ComponentModel.ISupportInitialize)(this.axApplicationMgr)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.axSequenceFileViewMgr)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();

		}
		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main(string[] args)
		{
			LaunchTestStandApplicationInNewDomain.Launch(new LaunchTestStandApplicationInNewDomain.MainEntryPointDelegateWithArgs(MainEntryPoint), args);
		}

		static private void MainEntryPoint(string[] args)
		{
			NationalInstruments.TestStand.Utility.ApplicationWrapper.Run(new MainForm());
		}

		private void MainForm_Load(object sender, System.EventArgs e)
		{
			try
			{

		     	// If this UI is running in a CLR other than the one TestStand uses,
				// then it needs its own GCTimer for that version of the CLR. If it's running in the
				// same CLR as TestStand then the engine's gctimer enabled by the ApplicationMgr
				// is sufficient. See the API help for Engine.DotNetGarbageCollectionInterval for more details.
				if (System.Environment.Version.ToString() != axApplicationMgr.GetEngine().DotNetCLRVersion)
					this.GCTimer.Enabled = true;	

				axApplicationMgr.Start();	// start up the TestStand User Interface Components. this also logs in the user
			}
			catch (Exception theException)
			{
				MessageBox.Show(this, theException.Message, "Error");
				Application.Exit();
			}		
		}

		// handle request to close form (via Windows close box, for example)
		private void MainForm_Closing(object sender, System.ComponentModel.CancelEventArgs e)
		{
			// Don't set e.Cancel to true if windows is shutting down.
			// Doing so would prevent windows from shutting down or logging out.
			if (!sessionEnding)
			{
				// initiate shutdown and cancel close if shutdown is not complete.  The applicationMgr will
				// send the ExitApplication event when shutdown is complete and we can close then
				if (axApplicationMgr.Shutdown() == false)
					e.Cancel = true;		
			}
		}

		protected override void WndProc(ref Message msg)
		{
			// set the sessionEnding flag so I will know the form is closing because the user
			// is trying to shutdown, restart, or logoff windows
			if (msg.Msg == WM_QUERYENDSESSION)
			{
				sessionEnding = true;
				Application.Exit();
			}

			base.WndProc(ref msg);
		}

		// It is now ok to exit, close the form
		private void axApplicationMgr_ExitApplication(object sender, System.EventArgs e)
		{
			Environment.ExitCode = this.axApplicationMgr.ExitCode;
			Close();

			TSHelper.DoSynchronousGCForCOMObjectDestruction();
		}

		// ApplicationMgr sends this event to handle any errors it detects.  For example, if a TestStand menu command
		// generates an error, this handler displays it
		private void axApplicationMgr_ReportError(object sender, NationalInstruments.TestStand.Interop.UI.Ax._ApplicationMgrEvents_ReportErrorEvent e)
		{
			MessageBox.Show(this, ErrorMessage.AppendCodeAndDescription(this.axApplicationMgr, e.errorMessage, e.errorCode), "Error", MessageBoxButtons.OK, MessageBoxIcon.Stop); 		
		}

		// the ApplicationMgr sends this event to request that the UI display a particular sequence file
		private void axApplicationMgr_DisplaySequenceFile(object sender, NationalInstruments.TestStand.Interop.UI.Ax._ApplicationMgrEvents_DisplaySequenceFileEvent e)
		{
			axSequenceFileViewMgr.SequenceFile = e.file;
			//Set the current sequence file to be the newly opened sequence file.
			currentSeqFilePathTextBox.Text = e.file.Path;
		}

		private void axApplicationMgr_EndExecution(object sender, NationalInstruments.TestStand.Interop.UI.Ax._ApplicationMgrEvents_EndExecutionEvent e)
		{
			string reportFileLocation = e.exec.Report.Location;
			if(reportFileLocation != "")
				dataGridView1.Rows.Add(reportFileLocation, e.exec.ResultStatus);
		}


		// Release all objects periodically.  .NET lets COM objects pile up on the managed heap, seemingly even objects you don't know about such
		// as parameters to unhandled ActiveX events.  This timer ensures that all COM objects are released in a timely manner,
		// thus preventing the performance hiccup that could occur when .NET finally decides to collect garbage. Also, this timer
		// ensures that actions triggered by object destruction run in a timely manner. For example: sequence file unload callbacks.
		private void GCTimerTick(object sender, System.EventArgs e)
		{
			System.GC.Collect(); // force .net garbage collection		
		}

		private void openSeqFileButton_Click(object sender, EventArgs e)
		{
			axApplicationMgr.GetCommand(CommandKinds.CommandKind_OpenSequenceFile, 0).Execute(true);
		}

		private void executeButton_Click(object sender, EventArgs e)
		{
			if (axSequenceFileViewMgr.SequenceFile != null)
			{
				axSequenceFileViewMgr.GetCommand(CommandKinds.CommandKind_ExecutionEntryPoints_Set, 0).Execute(true);
			}
			else
			{
				MessageBox.Show("You must open a sequence file before you can execute.");
			}
		}


	}
}
