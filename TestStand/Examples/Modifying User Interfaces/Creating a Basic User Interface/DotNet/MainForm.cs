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
		private NationalInstruments.TestStand.Interop.UI.Ax.AxButton axOpenFileButton;
		private NationalInstruments.TestStand.Interop.UI.Ax.AxApplicationMgr axApplicationMgr;
		private System.Windows.Forms.Timer GCTimer;
		private NationalInstruments.TestStand.Interop.UI.Ax.AxButton axRunSelectedButton;
		private NationalInstruments.TestStand.Interop.UI.Ax.AxSequenceView axSequenceView;
		private NationalInstruments.TestStand.Interop.UI.Ax.AxExecutionViewMgr axExecutionViewMgr;
		private NationalInstruments.TestStand.Interop.UI.Ax.AxSequenceFileViewMgr axSequenceFileViewMgr;
		private System.ComponentModel.IContainer components;
        
		private const int	WM_QUERYENDSESSION = 0x11;
		private NationalInstruments.TestStand.Interop.UI.Ax.AxListBox axSequenceListBox;
		private NationalInstruments.TestStand.Interop.UI.Ax.AxLabel axLabel;
		private NationalInstruments.TestStand.Interop.UI.Ax.AxCheckBox axTracingEnabled;
		private System.Windows.Forms.Label label1;

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
			this.axOpenFileButton = new NationalInstruments.TestStand.Interop.UI.Ax.AxButton();
			this.GCTimer = new System.Windows.Forms.Timer(this.components);
			this.axExecutionViewMgr = new NationalInstruments.TestStand.Interop.UI.Ax.AxExecutionViewMgr();
			this.axSequenceFileViewMgr = new NationalInstruments.TestStand.Interop.UI.Ax.AxSequenceFileViewMgr();
			this.axRunSelectedButton = new NationalInstruments.TestStand.Interop.UI.Ax.AxButton();
			this.axSequenceView = new NationalInstruments.TestStand.Interop.UI.Ax.AxSequenceView();
			this.axSequenceListBox = new NationalInstruments.TestStand.Interop.UI.Ax.AxListBox();
			this.axLabel = new NationalInstruments.TestStand.Interop.UI.Ax.AxLabel();
			this.axTracingEnabled = new NationalInstruments.TestStand.Interop.UI.Ax.AxCheckBox();
			this.label1 = new System.Windows.Forms.Label();
			((System.ComponentModel.ISupportInitialize)(this.axApplicationMgr)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.axOpenFileButton)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.axExecutionViewMgr)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.axSequenceFileViewMgr)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.axRunSelectedButton)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.axSequenceView)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.axSequenceListBox)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.axLabel)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.axTracingEnabled)).BeginInit();
			this.SuspendLayout();
			// 
			// axApplicationMgr
			// 
			this.axApplicationMgr.Enabled = true;
			this.axApplicationMgr.Location = new System.Drawing.Point(715, 566);
			this.axApplicationMgr.Name = "axApplicationMgr";
			this.axApplicationMgr.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axApplicationMgr.OcxState")));
			this.axApplicationMgr.Size = new System.Drawing.Size(32, 32);
			this.axApplicationMgr.TabIndex = 16;
			this.axApplicationMgr.ExitApplication += new System.EventHandler(this.axApplicationMgr_ExitApplication);
			this.axApplicationMgr.ReportError += new NationalInstruments.TestStand.Interop.UI.Ax._ApplicationMgrEvents_ReportErrorEventHandler(this.axApplicationMgr_ReportError);
			this.axApplicationMgr.DisplaySequenceFile += new NationalInstruments.TestStand.Interop.UI.Ax._ApplicationMgrEvents_DisplaySequenceFileEventHandler(this.axApplicationMgr_DisplaySequenceFile);
			this.axApplicationMgr.DisplayExecution += new NationalInstruments.TestStand.Interop.UI.Ax._ApplicationMgrEvents_DisplayExecutionEventHandler(this.axApplicationMgr_DisplayExecution);
			// 
			// axOpenFileButton
			// 
			this.axOpenFileButton.AccessibleRole = System.Windows.Forms.AccessibleRole.TitleBar;
			this.axOpenFileButton.Location = new System.Drawing.Point(3, 5);
			this.axOpenFileButton.Name = "axOpenFileButton";
			this.axOpenFileButton.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axOpenFileButton.OcxState")));
			this.axOpenFileButton.Size = new System.Drawing.Size(167, 24);
			this.axOpenFileButton.TabIndex = 2;
			// 
			// GCTimer
			// 
			this.GCTimer.Interval = 3000;
			this.GCTimer.Tick += new System.EventHandler(this.GCTimerTick);
			// 
			// axExecutionViewMgr
			// 
			this.axExecutionViewMgr.Enabled = true;
			this.axExecutionViewMgr.Location = new System.Drawing.Point(781, 566);
			this.axExecutionViewMgr.Name = "axExecutionViewMgr";
			this.axExecutionViewMgr.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axExecutionViewMgr.OcxState")));
			this.axExecutionViewMgr.Size = new System.Drawing.Size(32, 32);
			this.axExecutionViewMgr.TabIndex = 18;
			// 
			// axSequenceFileViewMgr
			// 
			this.axSequenceFileViewMgr.Enabled = true;
			this.axSequenceFileViewMgr.Location = new System.Drawing.Point(749, 566);
			this.axSequenceFileViewMgr.Name = "axSequenceFileViewMgr";
			this.axSequenceFileViewMgr.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axSequenceFileViewMgr.OcxState")));
			this.axSequenceFileViewMgr.Size = new System.Drawing.Size(32, 32);
			this.axSequenceFileViewMgr.TabIndex = 17;
			// 
			// axRunSelectedButton
			// 
			this.axRunSelectedButton.Location = new System.Drawing.Point(174, 5);
			this.axRunSelectedButton.Name = "axRunSelectedButton";
			this.axRunSelectedButton.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axRunSelectedButton.OcxState")));
			this.axRunSelectedButton.Size = new System.Drawing.Size(167, 24);
			this.axRunSelectedButton.TabIndex = 8;
			// 
			// axSequenceView
			// 
			this.axSequenceView.Enabled = true;
			this.axSequenceView.Location = new System.Drawing.Point(175, 35);
			this.axSequenceView.Name = "axSequenceView";
			this.axSequenceView.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axSequenceView.OcxState")));
			this.axSequenceView.Size = new System.Drawing.Size(637, 537);
			this.axSequenceView.TabIndex = 12;
			// 
			// axSequenceListBox
			// 
			this.axSequenceListBox.Location = new System.Drawing.Point(3, 35);
			this.axSequenceListBox.Name = "axSequenceListBox";
			this.axSequenceListBox.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axSequenceListBox.OcxState")));
			this.axSequenceListBox.Size = new System.Drawing.Size(167, 537);
			this.axSequenceListBox.TabIndex = 20;
			// 
			// axLabel
			// 
			this.axLabel.Location = new System.Drawing.Point(351, 9);
			this.axLabel.Name = "axLabel";
			this.axLabel.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axLabel.OcxState")));
			this.axLabel.Size = new System.Drawing.Size(37, 13);
			this.axLabel.TabIndex = 21;
			this.axLabel.TabStop = false;
			// 
			// axTracingEnabled
			// 
			this.axTracingEnabled.Location = new System.Drawing.Point(678, 8);
			this.axTracingEnabled.Name = "axTracingEnabled";
			this.axTracingEnabled.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axTracingEnabled.OcxState")));
			this.axTracingEnabled.Size = new System.Drawing.Size(133, 20);
			this.axTracingEnabled.TabIndex = 22;
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(1, 577);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(712, 13);
			this.label1.TabIndex = 23;
			this.label1.Text = "Note: This example is for demonstrational purposes and has limited functionality." +
    " It is not intended for use in deployed applications without modification.";
			// 
			// MainForm
			// 
			this.ClientSize = new System.Drawing.Size(816, 595);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.axTracingEnabled);
			this.Controls.Add(this.axLabel);
			this.Controls.Add(this.axSequenceListBox);
			this.Controls.Add(this.axSequenceView);
			this.Controls.Add(this.axRunSelectedButton);
			this.Controls.Add(this.axSequenceFileViewMgr);
			this.Controls.Add(this.axExecutionViewMgr);
			this.Controls.Add(this.axOpenFileButton);
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
			((System.ComponentModel.ISupportInitialize)(this.axOpenFileButton)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.axExecutionViewMgr)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.axSequenceFileViewMgr)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.axRunSelectedButton)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.axSequenceView)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.axSequenceListBox)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.axLabel)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.axTracingEnabled)).EndInit();
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
				// Connect TestStand buttons to commands

				// "Command Connections" are used to configure a TestStand Button or Checkbox control control to execute a specified command when clicked.  
				// Changing the cmdKind Input will change the functionality of the button. 
				axSequenceFileViewMgr.ConnectCommand(axOpenFileButton, CommandKinds.CommandKind_OpenSequenceFiles, 0, CommandConnectionOptions.CommandConnection_NoOptions);
				axSequenceFileViewMgr.ConnectCommand(axRunSelectedButton, CommandKinds.CommandKind_RunCurrentSequence, 0, CommandConnectionOptions.CommandConnection_NoOptions);
				axApplicationMgr.ConnectCommand(axTracingEnabled, CommandKinds.CommandKind_TracingEnabled);
				
				// "Information Source" Connections are used to display caption, image, and numeric information on Label controls, ExpressionEdit controls, and StatusBar panes.  
				// Changing the source Input will change what information is displayed in the connected control. 
				axSequenceFileViewMgr.ConnectCaption(axLabel,CaptionSources.CaptionSource_CurrentSequenceFile, false);
	
				// "List Connections" are used to configure a TestStand ComboBox, ListBarPage, or ListBox to display a TestStand List, such as the sequences in the current file.  
				// The manager controls provide a separate method for each connection type, so no cmdKind parameter is needed. 
				axSequenceFileViewMgr.ConnectSequenceList(axSequenceListBox);


				// "View Connections" are used to activate a SequenceView or ReportView control.  
				// The manager controls provide a separate method for each connection type, so no cmdKind parameter is needed. 					  
				axExecutionViewMgr.ConnectExecutionView(axSequenceView, ExecutionViewOptions.ExecutionViewConnection_NoOptions);

				
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

		// the ApplicationMgr sends this event to request that the UI display a particular execution
		private void axApplicationMgr_DisplayExecution(object sender, NationalInstruments.TestStand.Interop.UI.Ax._ApplicationMgrEvents_DisplayExecutionEvent e)
		{
			// bring application to front if we hit a breakpoint
			if (e.reason == ExecutionDisplayReasons.ExecutionDisplayReason_Breakpoint || e.reason == ExecutionDisplayReasons.ExecutionDisplayReason_BreakOnRunTimeError)
				this.Activate();

			axExecutionViewMgr.Execution = e.exec;
		}

		// the ApplicationMgr sends this event to request that the UI display a particular sequence file
		private void axApplicationMgr_DisplaySequenceFile(object sender, NationalInstruments.TestStand.Interop.UI.Ax._ApplicationMgrEvents_DisplaySequenceFileEvent e)
		{
			axSequenceFileViewMgr.SequenceFile = e.file;
		}

		// Release all objects periodically.  .NET lets COM objects pile up on the managed heap, seemingly even objects you don't know about such
		// as parameters to unhandled ActiveX events.  This timer ensures that all COM objects are released in a timely manner,
		// thus preventing the performance hiccup that could occur when .NET finally decides to collect garbage. Also, this timer
		// ensures that actions triggered by object destruction run in a timely manner. For example: sequence file unload callbacks.
		private void GCTimerTick(object sender, System.EventArgs e)
		{
			System.GC.Collect(); // force .net garbage collection		
		}

	}
}
