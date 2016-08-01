// Note:	This application has a manifest file in the project. This manifest file includes the Microsoft.Windows.Common-Controls which 
//			enables the application to display controls using the XP theme that the operating system selects.
//			A post build event embeds this manifest file into the executable.
//			In order for the manifest file to enable the executable to display with the XP theme:
//			1. The manifest file must have the same name as the executable. For example, if your executable is named MyExecutable.exe, your manifest file is required to have the name MyExecutable.exe.manifest.
//			2. The manifest file must include the Microsoft.Windows.Common-Controls.
//			3. The manifest file must reside in the same directory as the executable.
//			Also note that if you enable the Project Properties>>Debug>>Enable Visual Studio Hosting Process option, the XP theme adaption does not occur when debugging the executable
//			because the Visual Studio environment creates the process and does not allow the manifest file to be embedded into the executable.

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
		private NationalInstruments.TestStand.Interop.UI.Ax.AxButton axEntryPoint1Button;
		private NationalInstruments.TestStand.Interop.UI.Ax.AxButton axRunSelectedButton;
		private NationalInstruments.TestStand.Interop.UI.Ax.AxSequenceView axSequenceView;
		private NationalInstruments.TestStand.Interop.UI.Ax.AxExecutionViewMgr axExecutionViewMgr;
		private NationalInstruments.TestStand.Interop.UI.Ax.AxSequenceFileViewMgr axSequenceFileViewMgr;
		private NationalInstruments.TestStand.Interop.UI.Ax.AxButton axBreakResumeButton;
		private NationalInstruments.TestStand.Interop.UI.Ax.AxButton axTerminateRestartButton;
		private System.ComponentModel.IContainer components;

		private const int WM_QUERYENDSESSION = 0x11;
		private NationalInstruments.TestStand.Interop.UI.Ax.AxSequenceView axSequenceViewExec;
		private NationalInstruments.TestStand.Interop.UI.Ax.AxStatusBar axStatusBar1;
		private GroupBox groupBox1;
		private System.Windows.Forms.Label label20;
		private System.Windows.Forms.Label label19;
		private TabPage infoPage;
		private GroupBox statusBarGrp;
		private System.Windows.Forms.Label label25;
		private System.Windows.Forms.Label label27;
		private System.Windows.Forms.Label label24;
		private System.Windows.Forms.ComboBox StatusPane2Control;
		private System.Windows.Forms.Label label26;
		private System.Windows.Forms.Label label23;
		private System.Windows.Forms.ComboBox StatusPane1Control;
		private System.Windows.Forms.ComboBox StatusPane3Control;
		private System.Windows.Forms.ComboBox StatusPane4Control;
		private GroupBox LabelGrp;
		private System.Windows.Forms.Label label22;
		private System.Windows.Forms.Label label21;
		private System.Windows.Forms.ComboBox ExecLabelControl;
		private System.Windows.Forms.ComboBox SeqFileLabelControl;
		private NationalInstruments.TestStand.Interop.UI.Ax.AxLabel axLabel2;
		private NationalInstruments.TestStand.Interop.UI.Ax.AxLabel axLabel1;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.CheckBox useLongNames;
		private TabPage commandPage;
		private GroupBox CheckBoxGrp;
		private System.Windows.Forms.Label label18;
		private System.Windows.Forms.ComboBox checkBoxControl;
		private NationalInstruments.TestStand.Interop.UI.Ax.AxCheckBox axCheckBox1;
		private GroupBox ButtonGrp;
		private System.Windows.Forms.Label label17;
		private System.Windows.Forms.Label label16;
		private System.Windows.Forms.Label label15;
		private System.Windows.Forms.ComboBox ExecMgrButtonControl;
		private System.Windows.Forms.ComboBox SeqFileMgrButtonControl;
		private System.Windows.Forms.ComboBox AppMgrButtonControl;
		private NationalInstruments.TestStand.Interop.UI.Ax.AxButton axButton3;
		private NationalInstruments.TestStand.Interop.UI.Ax.AxButton axButton2;
		private NationalInstruments.TestStand.Interop.UI.Ax.AxButton axButton1;
		private System.Windows.Forms.Label label3;
		private TabPage listPage;
		private GroupBox ListBarGrp;
		private System.Windows.Forms.Label label12;
		private System.Windows.Forms.Label label11;
		private System.Windows.Forms.Label label10;
		private System.Windows.Forms.ComboBox ListBarControlPage2;
		private System.Windows.Forms.ComboBox ListBarControlPage1;
		private NationalInstruments.TestStand.Interop.UI.Ax.AxListBar axListBar1;
		private GroupBox ListBoxGrp;
		private System.Windows.Forms.Label label14;
		private System.Windows.Forms.Label label9;
		private System.Windows.Forms.ComboBox ListBoxControl;
		private NationalInstruments.TestStand.Interop.UI.Ax.AxListBox axListBox1;
		private GroupBox comboBoxGrp;
		private System.Windows.Forms.Label label13;
		private System.Windows.Forms.Label label8;
		private System.Windows.Forms.ComboBox comboBoxControl;
		private NationalInstruments.TestStand.Interop.UI.Ax.AxComboBox axComboBox1;
		private System.Windows.Forms.Label label2;
		private TabPage viewPage;
		private GroupBox reportViewGrp;
		private System.Windows.Forms.Label label7;
		private NationalInstruments.TestStand.Interop.UI.Ax.AxReportView axReportView;
		private GroupBox variablesViewGrp;
		private System.Windows.Forms.Label label6;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.ComboBox variablesViewControl;
		private NationalInstruments.TestStand.Interop.UI.Ax.AxVariablesView axVariablesView;
		private System.Windows.Forms.Label label1;
		private TabControl tabControl1;
		private SplitContainer splitContainer1;
		private SplitContainer splitContainer2;
		private SplitContainer splitContainer3;
		private SplitContainer splitContainer4;
		private SplitContainer splitContainer5;
		private SplitContainer splitContainer7;
		private SplitContainer splitContainer6;
		private System.Windows.Forms.Button ViewHelp;

		// flag that will be set to true if the user tries to shut down windows
		private bool sessionEnding = false;

		public MainForm()
		{
			// Required for Windows Form Designer support
			InitializeComponent();

			// TODO: Add any constructor code after InitializeComponent call
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose(bool disposing)
		{
			if (disposing)
			{
				if (components != null)
				{
					components.Dispose();
				}
			}
			base.Dispose(disposing);
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
			this.axEntryPoint1Button = new NationalInstruments.TestStand.Interop.UI.Ax.AxButton();
			this.axRunSelectedButton = new NationalInstruments.TestStand.Interop.UI.Ax.AxButton();
			this.axSequenceView = new NationalInstruments.TestStand.Interop.UI.Ax.AxSequenceView();
			this.axBreakResumeButton = new NationalInstruments.TestStand.Interop.UI.Ax.AxButton();
			this.axTerminateRestartButton = new NationalInstruments.TestStand.Interop.UI.Ax.AxButton();
			this.axSequenceViewExec = new NationalInstruments.TestStand.Interop.UI.Ax.AxSequenceView();
			this.axStatusBar1 = new NationalInstruments.TestStand.Interop.UI.Ax.AxStatusBar();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.splitContainer1 = new System.Windows.Forms.SplitContainer();
			this.label20 = new System.Windows.Forms.Label();
			this.label19 = new System.Windows.Forms.Label();
			this.infoPage = new System.Windows.Forms.TabPage();
			this.splitContainer7 = new System.Windows.Forms.SplitContainer();
			this.LabelGrp = new System.Windows.Forms.GroupBox();
			this.label22 = new System.Windows.Forms.Label();
			this.label21 = new System.Windows.Forms.Label();
			this.ExecLabelControl = new System.Windows.Forms.ComboBox();
			this.SeqFileLabelControl = new System.Windows.Forms.ComboBox();
			this.axLabel2 = new NationalInstruments.TestStand.Interop.UI.Ax.AxLabel();
			this.axLabel1 = new NationalInstruments.TestStand.Interop.UI.Ax.AxLabel();
			this.statusBarGrp = new System.Windows.Forms.GroupBox();
			this.label25 = new System.Windows.Forms.Label();
			this.label27 = new System.Windows.Forms.Label();
			this.label24 = new System.Windows.Forms.Label();
			this.StatusPane2Control = new System.Windows.Forms.ComboBox();
			this.label26 = new System.Windows.Forms.Label();
			this.label23 = new System.Windows.Forms.Label();
			this.StatusPane1Control = new System.Windows.Forms.ComboBox();
			this.StatusPane3Control = new System.Windows.Forms.ComboBox();
			this.StatusPane4Control = new System.Windows.Forms.ComboBox();
			this.label4 = new System.Windows.Forms.Label();
			this.useLongNames = new System.Windows.Forms.CheckBox();
			this.commandPage = new System.Windows.Forms.TabPage();
			this.splitContainer6 = new System.Windows.Forms.SplitContainer();
			this.ButtonGrp = new System.Windows.Forms.GroupBox();
			this.label17 = new System.Windows.Forms.Label();
			this.label16 = new System.Windows.Forms.Label();
			this.label15 = new System.Windows.Forms.Label();
			this.ExecMgrButtonControl = new System.Windows.Forms.ComboBox();
			this.SeqFileMgrButtonControl = new System.Windows.Forms.ComboBox();
			this.AppMgrButtonControl = new System.Windows.Forms.ComboBox();
			this.axButton3 = new NationalInstruments.TestStand.Interop.UI.Ax.AxButton();
			this.axButton2 = new NationalInstruments.TestStand.Interop.UI.Ax.AxButton();
			this.axButton1 = new NationalInstruments.TestStand.Interop.UI.Ax.AxButton();
			this.CheckBoxGrp = new System.Windows.Forms.GroupBox();
			this.label18 = new System.Windows.Forms.Label();
			this.checkBoxControl = new System.Windows.Forms.ComboBox();
			this.axCheckBox1 = new NationalInstruments.TestStand.Interop.UI.Ax.AxCheckBox();
			this.label3 = new System.Windows.Forms.Label();
			this.listPage = new System.Windows.Forms.TabPage();
			this.splitContainer4 = new System.Windows.Forms.SplitContainer();
			this.comboBoxGrp = new System.Windows.Forms.GroupBox();
			this.label13 = new System.Windows.Forms.Label();
			this.label8 = new System.Windows.Forms.Label();
			this.comboBoxControl = new System.Windows.Forms.ComboBox();
			this.axComboBox1 = new NationalInstruments.TestStand.Interop.UI.Ax.AxComboBox();
			this.splitContainer5 = new System.Windows.Forms.SplitContainer();
			this.ListBoxGrp = new System.Windows.Forms.GroupBox();
			this.label14 = new System.Windows.Forms.Label();
			this.label9 = new System.Windows.Forms.Label();
			this.ListBoxControl = new System.Windows.Forms.ComboBox();
			this.axListBox1 = new NationalInstruments.TestStand.Interop.UI.Ax.AxListBox();
			this.ListBarGrp = new System.Windows.Forms.GroupBox();
			this.label12 = new System.Windows.Forms.Label();
			this.label11 = new System.Windows.Forms.Label();
			this.label10 = new System.Windows.Forms.Label();
			this.ListBarControlPage2 = new System.Windows.Forms.ComboBox();
			this.ListBarControlPage1 = new System.Windows.Forms.ComboBox();
			this.axListBar1 = new NationalInstruments.TestStand.Interop.UI.Ax.AxListBar();
			this.label2 = new System.Windows.Forms.Label();
			this.viewPage = new System.Windows.Forms.TabPage();
			this.splitContainer2 = new System.Windows.Forms.SplitContainer();
			this.variablesViewGrp = new System.Windows.Forms.GroupBox();
			this.label6 = new System.Windows.Forms.Label();
			this.label5 = new System.Windows.Forms.Label();
			this.variablesViewControl = new System.Windows.Forms.ComboBox();
			this.axVariablesView = new NationalInstruments.TestStand.Interop.UI.Ax.AxVariablesView();
			this.reportViewGrp = new System.Windows.Forms.GroupBox();
			this.label7 = new System.Windows.Forms.Label();
			this.axReportView = new NationalInstruments.TestStand.Interop.UI.Ax.AxReportView();
			this.label1 = new System.Windows.Forms.Label();
			this.tabControl1 = new System.Windows.Forms.TabControl();
			this.splitContainer3 = new System.Windows.Forms.SplitContainer();
			this.ViewHelp = new System.Windows.Forms.Button();
			((System.ComponentModel.ISupportInitialize)(this.axApplicationMgr)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.axOpenFileButton)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.axExecutionViewMgr)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.axSequenceFileViewMgr)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.axEntryPoint1Button)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.axRunSelectedButton)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.axSequenceView)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.axBreakResumeButton)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.axTerminateRestartButton)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.axSequenceViewExec)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.axStatusBar1)).BeginInit();
			this.groupBox1.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
			this.splitContainer1.Panel1.SuspendLayout();
			this.splitContainer1.Panel2.SuspendLayout();
			this.splitContainer1.SuspendLayout();
			this.infoPage.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.splitContainer7)).BeginInit();
			this.splitContainer7.Panel1.SuspendLayout();
			this.splitContainer7.Panel2.SuspendLayout();
			this.splitContainer7.SuspendLayout();
			this.LabelGrp.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.axLabel2)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.axLabel1)).BeginInit();
			this.statusBarGrp.SuspendLayout();
			this.commandPage.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.splitContainer6)).BeginInit();
			this.splitContainer6.Panel1.SuspendLayout();
			this.splitContainer6.Panel2.SuspendLayout();
			this.splitContainer6.SuspendLayout();
			this.ButtonGrp.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.axButton3)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.axButton2)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.axButton1)).BeginInit();
			this.CheckBoxGrp.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.axCheckBox1)).BeginInit();
			this.listPage.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.splitContainer4)).BeginInit();
			this.splitContainer4.Panel1.SuspendLayout();
			this.splitContainer4.Panel2.SuspendLayout();
			this.splitContainer4.SuspendLayout();
			this.comboBoxGrp.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.axComboBox1)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.splitContainer5)).BeginInit();
			this.splitContainer5.Panel1.SuspendLayout();
			this.splitContainer5.Panel2.SuspendLayout();
			this.splitContainer5.SuspendLayout();
			this.ListBoxGrp.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.axListBox1)).BeginInit();
			this.ListBarGrp.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.axListBar1)).BeginInit();
			this.viewPage.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).BeginInit();
			this.splitContainer2.Panel1.SuspendLayout();
			this.splitContainer2.Panel2.SuspendLayout();
			this.splitContainer2.SuspendLayout();
			this.variablesViewGrp.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.axVariablesView)).BeginInit();
			this.reportViewGrp.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.axReportView)).BeginInit();
			this.tabControl1.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.splitContainer3)).BeginInit();
			this.splitContainer3.Panel1.SuspendLayout();
			this.splitContainer3.Panel2.SuspendLayout();
			this.splitContainer3.SuspendLayout();
			this.SuspendLayout();
			// 
			// axApplicationMgr
			// 
			this.axApplicationMgr.Enabled = true;
			this.axApplicationMgr.Location = new System.Drawing.Point(537, 9);
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
			this.axOpenFileButton.Location = new System.Drawing.Point(6, 13);
			this.axOpenFileButton.Name = "axOpenFileButton";
			this.axOpenFileButton.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axOpenFileButton.OcxState")));
			this.axOpenFileButton.Size = new System.Drawing.Size(171, 25);
			this.axOpenFileButton.TabIndex = 2;
			// 
			// GCTimer
			// 
			this.GCTimer.Enabled = true;
			this.GCTimer.Interval = 333;
			this.GCTimer.Tick += new System.EventHandler(this.GCTimerTick);
			// 
			// axExecutionViewMgr
			// 
			this.axExecutionViewMgr.Enabled = true;
			this.axExecutionViewMgr.Location = new System.Drawing.Point(604, 9);
			this.axExecutionViewMgr.Name = "axExecutionViewMgr";
			this.axExecutionViewMgr.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axExecutionViewMgr.OcxState")));
			this.axExecutionViewMgr.Size = new System.Drawing.Size(32, 32);
			this.axExecutionViewMgr.TabIndex = 18;
			// 
			// axSequenceFileViewMgr
			// 
			this.axSequenceFileViewMgr.Enabled = true;
			this.axSequenceFileViewMgr.Location = new System.Drawing.Point(570, 9);
			this.axSequenceFileViewMgr.Name = "axSequenceFileViewMgr";
			this.axSequenceFileViewMgr.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axSequenceFileViewMgr.OcxState")));
			this.axSequenceFileViewMgr.Size = new System.Drawing.Size(32, 32);
			this.axSequenceFileViewMgr.TabIndex = 17;
			// 
			// axEntryPoint1Button
			// 
			this.axEntryPoint1Button.Location = new System.Drawing.Point(355, 13);
			this.axEntryPoint1Button.Name = "axEntryPoint1Button";
			this.axEntryPoint1Button.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axEntryPoint1Button.OcxState")));
			this.axEntryPoint1Button.Size = new System.Drawing.Size(171, 25);
			this.axEntryPoint1Button.TabIndex = 6;
			// 
			// axRunSelectedButton
			// 
			this.axRunSelectedButton.Location = new System.Drawing.Point(181, 13);
			this.axRunSelectedButton.Name = "axRunSelectedButton";
			this.axRunSelectedButton.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axRunSelectedButton.OcxState")));
			this.axRunSelectedButton.Size = new System.Drawing.Size(171, 25);
			this.axRunSelectedButton.TabIndex = 8;
			// 
			// axSequenceView
			// 
			this.axSequenceView.Dock = System.Windows.Forms.DockStyle.Fill;
			this.axSequenceView.Enabled = true;
			this.axSequenceView.Location = new System.Drawing.Point(0, 0);
			this.axSequenceView.Name = "axSequenceView";
			this.axSequenceView.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axSequenceView.OcxState")));
			this.axSequenceView.Size = new System.Drawing.Size(493, 239);
			this.axSequenceView.TabIndex = 12;
			// 
			// axBreakResumeButton
			// 
			this.axBreakResumeButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.axBreakResumeButton.Location = new System.Drawing.Point(828, 13);
			this.axBreakResumeButton.Name = "axBreakResumeButton";
			this.axBreakResumeButton.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axBreakResumeButton.OcxState")));
			this.axBreakResumeButton.Size = new System.Drawing.Size(171, 25);
			this.axBreakResumeButton.TabIndex = 13;
			// 
			// axTerminateRestartButton
			// 
			this.axTerminateRestartButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.axTerminateRestartButton.Location = new System.Drawing.Point(650, 13);
			this.axTerminateRestartButton.Name = "axTerminateRestartButton";
			this.axTerminateRestartButton.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axTerminateRestartButton.OcxState")));
			this.axTerminateRestartButton.Size = new System.Drawing.Size(171, 25);
			this.axTerminateRestartButton.TabIndex = 14;
			// 
			// axSequenceViewExec
			// 
			this.axSequenceViewExec.Dock = System.Windows.Forms.DockStyle.Fill;
			this.axSequenceViewExec.Enabled = true;
			this.axSequenceViewExec.Location = new System.Drawing.Point(0, 0);
			this.axSequenceViewExec.Name = "axSequenceViewExec";
			this.axSequenceViewExec.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axSequenceViewExec.OcxState")));
			this.axSequenceViewExec.Size = new System.Drawing.Size(496, 239);
			this.axSequenceViewExec.TabIndex = 22;
			// 
			// axStatusBar1
			// 
			this.axStatusBar1.Enabled = true;
			this.axStatusBar1.Location = new System.Drawing.Point(-3, 711);
			this.axStatusBar1.Name = "axStatusBar1";
			this.axStatusBar1.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axStatusBar1.OcxState")));
			this.axStatusBar1.Size = new System.Drawing.Size(1019, 19);
			this.axStatusBar1.TabIndex = 24;
			this.axStatusBar1.TabStop = false;
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.splitContainer1);
			this.groupBox1.Controls.Add(this.label20);
			this.groupBox1.Controls.Add(this.label19);
			this.groupBox1.Controls.Add(this.axTerminateRestartButton);
			this.groupBox1.Controls.Add(this.axSequenceFileViewMgr);
			this.groupBox1.Controls.Add(this.axBreakResumeButton);
			this.groupBox1.Controls.Add(this.axExecutionViewMgr);
			this.groupBox1.Controls.Add(this.axApplicationMgr);
			this.groupBox1.Controls.Add(this.axRunSelectedButton);
			this.groupBox1.Controls.Add(this.axEntryPoint1Button);
			this.groupBox1.Controls.Add(this.axOpenFileButton);
			this.groupBox1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.groupBox1.Location = new System.Drawing.Point(0, 0);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(1005, 305);
			this.groupBox1.TabIndex = 25;
			this.groupBox1.TabStop = false;
			// 
			// splitContainer1
			// 
			this.splitContainer1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.splitContainer1.Location = new System.Drawing.Point(6, 60);
			this.splitContainer1.Name = "splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this.splitContainer1.Panel1.Controls.Add(this.axSequenceView);
			// 
			// splitContainer1.Panel2
			// 
			this.splitContainer1.Panel2.Controls.Add(this.axSequenceViewExec);
			this.splitContainer1.Size = new System.Drawing.Size(993, 239);
			this.splitContainer1.SplitterDistance = 493;
			this.splitContainer1.TabIndex = 23;
			// 
			// label20
			// 
			this.label20.AutoSize = true;
			this.label20.Location = new System.Drawing.Point(503, 44);
			this.label20.Name = "label20";
			this.label20.Size = new System.Drawing.Size(372, 13);
			this.label20.TabIndex = 3;
			this.label20.Text = "TestStand UI SequenceView Control (Connected to ExecutionView Manager)";
			// 
			// label19
			// 
			this.label19.AutoSize = true;
			this.label19.Location = new System.Drawing.Point(6, 44);
			this.label19.Name = "label19";
			this.label19.Size = new System.Drawing.Size(390, 13);
			this.label19.TabIndex = 3;
			this.label19.Text = "TestStand UI SequenceView Control (Connected to SequenceFileView Manager)";
			// 
			// infoPage
			// 
			this.infoPage.Controls.Add(this.splitContainer7);
			this.infoPage.Controls.Add(this.label4);
			this.infoPage.Controls.Add(this.useLongNames);
			this.infoPage.Location = new System.Drawing.Point(4, 22);
			this.infoPage.Name = "infoPage";
			this.infoPage.Padding = new System.Windows.Forms.Padding(3);
			this.infoPage.Size = new System.Drawing.Size(997, 371);
			this.infoPage.TabIndex = 3;
			this.infoPage.Text = "Info Source Connections";
			this.infoPage.UseVisualStyleBackColor = true;
			// 
			// splitContainer7
			// 
			this.splitContainer7.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.splitContainer7.IsSplitterFixed = true;
			this.splitContainer7.Location = new System.Drawing.Point(8, 59);
			this.splitContainer7.Name = "splitContainer7";
			// 
			// splitContainer7.Panel1
			// 
			this.splitContainer7.Panel1.Controls.Add(this.LabelGrp);
			// 
			// splitContainer7.Panel2
			// 
			this.splitContainer7.Panel2.Controls.Add(this.statusBarGrp);
			this.splitContainer7.Size = new System.Drawing.Size(983, 280);
			this.splitContainer7.SplitterDistance = 492;
			this.splitContainer7.TabIndex = 17;
			// 
			// LabelGrp
			// 
			this.LabelGrp.Controls.Add(this.label22);
			this.LabelGrp.Controls.Add(this.label21);
			this.LabelGrp.Controls.Add(this.ExecLabelControl);
			this.LabelGrp.Controls.Add(this.SeqFileLabelControl);
			this.LabelGrp.Controls.Add(this.axLabel2);
			this.LabelGrp.Controls.Add(this.axLabel1);
			this.LabelGrp.Dock = System.Windows.Forms.DockStyle.Fill;
			this.LabelGrp.Location = new System.Drawing.Point(0, 0);
			this.LabelGrp.Name = "LabelGrp";
			this.LabelGrp.Size = new System.Drawing.Size(492, 280);
			this.LabelGrp.TabIndex = 15;
			this.LabelGrp.TabStop = false;
			this.LabelGrp.Text = "Label Control";
			// 
			// label22
			// 
			this.label22.AutoSize = true;
			this.label22.Location = new System.Drawing.Point(6, 110);
			this.label22.Name = "label22";
			this.label22.Size = new System.Drawing.Size(240, 13);
			this.label22.TabIndex = 9;
			this.label22.Text = "Select Caption Source (ExecutionView Manager):";
			// 
			// label21
			// 
			this.label21.AutoSize = true;
			this.label21.Location = new System.Drawing.Point(6, 24);
			this.label21.Name = "label21";
			this.label21.Size = new System.Drawing.Size(258, 13);
			this.label21.TabIndex = 9;
			this.label21.Text = "Select Caption Source (SequenceFileView Manager):";
			// 
			// ExecLabelControl
			// 
			this.ExecLabelControl.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.ExecLabelControl.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.ExecLabelControl.FormattingEnabled = true;
			this.ExecLabelControl.Location = new System.Drawing.Point(7, 127);
			this.ExecLabelControl.Name = "ExecLabelControl";
			this.ExecLabelControl.Size = new System.Drawing.Size(478, 21);
			this.ExecLabelControl.TabIndex = 8;
			this.ExecLabelControl.SelectedIndexChanged += new System.EventHandler(this.ExecLabelControl_SelectedIndexChanged);
			// 
			// SeqFileLabelControl
			// 
			this.SeqFileLabelControl.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.SeqFileLabelControl.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.SeqFileLabelControl.FormattingEnabled = true;
			this.SeqFileLabelControl.Location = new System.Drawing.Point(7, 41);
			this.SeqFileLabelControl.Name = "SeqFileLabelControl";
			this.SeqFileLabelControl.Size = new System.Drawing.Size(478, 21);
			this.SeqFileLabelControl.TabIndex = 7;
			this.SeqFileLabelControl.SelectedIndexChanged += new System.EventHandler(this.SeqFileLabelControl_SelectedIndexChanged);
			// 
			// axLabel2
			// 
			this.axLabel2.Location = new System.Drawing.Point(28, 154);
			this.axLabel2.Name = "axLabel2";
			this.axLabel2.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axLabel2.OcxState")));
			this.axLabel2.Size = new System.Drawing.Size(43, 13);
			this.axLabel2.TabIndex = 1;
			this.axLabel2.TabStop = false;
			// 
			// axLabel1
			// 
			this.axLabel1.Location = new System.Drawing.Point(28, 68);
			this.axLabel1.Name = "axLabel1";
			this.axLabel1.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axLabel1.OcxState")));
			this.axLabel1.Size = new System.Drawing.Size(43, 13);
			this.axLabel1.TabIndex = 0;
			this.axLabel1.TabStop = false;
			// 
			// statusBarGrp
			// 
			this.statusBarGrp.Controls.Add(this.label25);
			this.statusBarGrp.Controls.Add(this.label27);
			this.statusBarGrp.Controls.Add(this.label24);
			this.statusBarGrp.Controls.Add(this.StatusPane2Control);
			this.statusBarGrp.Controls.Add(this.label26);
			this.statusBarGrp.Controls.Add(this.label23);
			this.statusBarGrp.Controls.Add(this.StatusPane1Control);
			this.statusBarGrp.Controls.Add(this.StatusPane3Control);
			this.statusBarGrp.Controls.Add(this.StatusPane4Control);
			this.statusBarGrp.Dock = System.Windows.Forms.DockStyle.Fill;
			this.statusBarGrp.Location = new System.Drawing.Point(0, 0);
			this.statusBarGrp.Name = "statusBarGrp";
			this.statusBarGrp.Size = new System.Drawing.Size(487, 280);
			this.statusBarGrp.TabIndex = 16;
			this.statusBarGrp.TabStop = false;
			this.statusBarGrp.Text = "StatusBar Control";
			// 
			// label25
			// 
			this.label25.AutoSize = true;
			this.label25.Location = new System.Drawing.Point(7, 66);
			this.label25.Name = "label25";
			this.label25.Size = new System.Drawing.Size(283, 13);
			this.label25.TabIndex = 9;
			this.label25.Text = "Pane 2 - Select Caption Source (ExecutionView Manager):";
			// 
			// label27
			// 
			this.label27.AutoSize = true;
			this.label27.Location = new System.Drawing.Point(5, 219);
			this.label27.Name = "label27";
			this.label27.Size = new System.Drawing.Size(387, 13);
			this.label27.TabIndex = 9;
			this.label27.Text = "Note: The TestStand StatusBar control is located at the bottom of the UI window";
			// 
			// label24
			// 
			this.label24.AutoSize = true;
			this.label24.Location = new System.Drawing.Point(8, 23);
			this.label24.Name = "label24";
			this.label24.Size = new System.Drawing.Size(276, 13);
			this.label24.TabIndex = 9;
			this.label24.Text = "Pane 1 - Select Image Source (ExecutionView Manager):";
			// 
			// StatusPane2Control
			// 
			this.StatusPane2Control.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.StatusPane2Control.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.StatusPane2Control.FormattingEnabled = true;
			this.StatusPane2Control.Location = new System.Drawing.Point(6, 83);
			this.StatusPane2Control.Name = "StatusPane2Control";
			this.StatusPane2Control.Size = new System.Drawing.Size(475, 21);
			this.StatusPane2Control.TabIndex = 12;
			this.StatusPane2Control.SelectedIndexChanged += new System.EventHandler(this.StatusPane2Control_SelectedIndexChanged);
			// 
			// label26
			// 
			this.label26.AutoSize = true;
			this.label26.Location = new System.Drawing.Point(5, 154);
			this.label26.Name = "label26";
			this.label26.Size = new System.Drawing.Size(301, 13);
			this.label26.TabIndex = 9;
			this.label26.Text = "Pane 4 - Select Caption Source (SequenceFileView Manager):";
			// 
			// label23
			// 
			this.label23.AutoSize = true;
			this.label23.Location = new System.Drawing.Point(5, 110);
			this.label23.Name = "label23";
			this.label23.Size = new System.Drawing.Size(294, 13);
			this.label23.TabIndex = 9;
			this.label23.Text = "Pane 3 - Select Image Source (SequenceFileView Manager):";
			// 
			// StatusPane1Control
			// 
			this.StatusPane1Control.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.StatusPane1Control.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.StatusPane1Control.FormattingEnabled = true;
			this.StatusPane1Control.Location = new System.Drawing.Point(6, 40);
			this.StatusPane1Control.Name = "StatusPane1Control";
			this.StatusPane1Control.Size = new System.Drawing.Size(475, 21);
			this.StatusPane1Control.TabIndex = 11;
			this.StatusPane1Control.SelectedIndexChanged += new System.EventHandler(this.StatusPane1Control_SelectedIndexChanged);
			// 
			// StatusPane3Control
			// 
			this.StatusPane3Control.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.StatusPane3Control.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.StatusPane3Control.FormattingEnabled = true;
			this.StatusPane3Control.Location = new System.Drawing.Point(6, 127);
			this.StatusPane3Control.Name = "StatusPane3Control";
			this.StatusPane3Control.Size = new System.Drawing.Size(475, 21);
			this.StatusPane3Control.TabIndex = 10;
			this.StatusPane3Control.SelectedIndexChanged += new System.EventHandler(this.StatusPane3Control_SelectedIndexChanged);
			// 
			// StatusPane4Control
			// 
			this.StatusPane4Control.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.StatusPane4Control.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.StatusPane4Control.FormattingEnabled = true;
			this.StatusPane4Control.Location = new System.Drawing.Point(6, 171);
			this.StatusPane4Control.Name = "StatusPane4Control";
			this.StatusPane4Control.Size = new System.Drawing.Size(475, 21);
			this.StatusPane4Control.TabIndex = 9;
			this.StatusPane4Control.SelectedIndexChanged += new System.EventHandler(this.StatusPane4Control_SelectedIndexChanged);
			// 
			// label4
			// 
			this.label4.AutoSize = true;
			this.label4.Location = new System.Drawing.Point(5, 6);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(746, 39);
			this.label4.TabIndex = 14;
			this.label4.Text = resources.GetString("label4.Text");
			// 
			// useLongNames
			// 
			this.useLongNames.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.useLongNames.AutoSize = true;
			this.useLongNames.Location = new System.Drawing.Point(15, 345);
			this.useLongNames.Name = "useLongNames";
			this.useLongNames.Size = new System.Drawing.Size(219, 17);
			this.useLongNames.TabIndex = 13;
			this.useLongNames.Text = "Use Long Name for Caption Connections";
			this.useLongNames.UseVisualStyleBackColor = true;
			// 
			// commandPage
			// 
			this.commandPage.Controls.Add(this.splitContainer6);
			this.commandPage.Controls.Add(this.label3);
			this.commandPage.Location = new System.Drawing.Point(4, 22);
			this.commandPage.Name = "commandPage";
			this.commandPage.Padding = new System.Windows.Forms.Padding(3);
			this.commandPage.Size = new System.Drawing.Size(997, 371);
			this.commandPage.TabIndex = 2;
			this.commandPage.Text = "Command Connections";
			this.commandPage.UseVisualStyleBackColor = true;
			// 
			// splitContainer6
			// 
			this.splitContainer6.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.splitContainer6.IsSplitterFixed = true;
			this.splitContainer6.Location = new System.Drawing.Point(7, 64);
			this.splitContainer6.Name = "splitContainer6";
			// 
			// splitContainer6.Panel1
			// 
			this.splitContainer6.Panel1.Controls.Add(this.ButtonGrp);
			// 
			// splitContainer6.Panel2
			// 
			this.splitContainer6.Panel2.Controls.Add(this.CheckBoxGrp);
			this.splitContainer6.Size = new System.Drawing.Size(984, 301);
			this.splitContainer6.SplitterDistance = 494;
			this.splitContainer6.TabIndex = 11;
			// 
			// ButtonGrp
			// 
			this.ButtonGrp.Controls.Add(this.label17);
			this.ButtonGrp.Controls.Add(this.label16);
			this.ButtonGrp.Controls.Add(this.label15);
			this.ButtonGrp.Controls.Add(this.ExecMgrButtonControl);
			this.ButtonGrp.Controls.Add(this.SeqFileMgrButtonControl);
			this.ButtonGrp.Controls.Add(this.AppMgrButtonControl);
			this.ButtonGrp.Controls.Add(this.axButton3);
			this.ButtonGrp.Controls.Add(this.axButton2);
			this.ButtonGrp.Controls.Add(this.axButton1);
			this.ButtonGrp.Dock = System.Windows.Forms.DockStyle.Fill;
			this.ButtonGrp.Location = new System.Drawing.Point(0, 0);
			this.ButtonGrp.Name = "ButtonGrp";
			this.ButtonGrp.Size = new System.Drawing.Size(494, 301);
			this.ButtonGrp.TabIndex = 9;
			this.ButtonGrp.TabStop = false;
			this.ButtonGrp.Text = "Button Control";
			// 
			// label17
			// 
			this.label17.AutoSize = true;
			this.label17.Location = new System.Drawing.Point(5, 183);
			this.label17.Name = "label17";
			this.label17.Size = new System.Drawing.Size(238, 13);
			this.label17.TabIndex = 9;
			this.label17.Text = "Select Command Kind (ExecutionView Manager):";
			// 
			// label16
			// 
			this.label16.AutoSize = true;
			this.label16.Location = new System.Drawing.Point(5, 102);
			this.label16.Name = "label16";
			this.label16.Size = new System.Drawing.Size(256, 13);
			this.label16.TabIndex = 8;
			this.label16.Text = "Select Command Kind (SequenceFileView Manager):";
			// 
			// label15
			// 
			this.label15.AutoSize = true;
			this.label15.Location = new System.Drawing.Point(5, 17);
			this.label15.Name = "label15";
			this.label15.Size = new System.Drawing.Size(220, 13);
			this.label15.TabIndex = 7;
			this.label15.Text = "Select Command Kind (Application Manager):";
			// 
			// ExecMgrButtonControl
			// 
			this.ExecMgrButtonControl.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.ExecMgrButtonControl.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.ExecMgrButtonControl.FormattingEnabled = true;
			this.ExecMgrButtonControl.Location = new System.Drawing.Point(8, 200);
			this.ExecMgrButtonControl.Name = "ExecMgrButtonControl";
			this.ExecMgrButtonControl.Size = new System.Drawing.Size(479, 21);
			this.ExecMgrButtonControl.TabIndex = 6;
			this.ExecMgrButtonControl.SelectedIndexChanged += new System.EventHandler(this.ExecMgrButtonControl_SelectedIndexChanged);
			// 
			// SeqFileMgrButtonControl
			// 
			this.SeqFileMgrButtonControl.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.SeqFileMgrButtonControl.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.SeqFileMgrButtonControl.FormattingEnabled = true;
			this.SeqFileMgrButtonControl.Location = new System.Drawing.Point(8, 119);
			this.SeqFileMgrButtonControl.Name = "SeqFileMgrButtonControl";
			this.SeqFileMgrButtonControl.Size = new System.Drawing.Size(479, 21);
			this.SeqFileMgrButtonControl.TabIndex = 5;
			this.SeqFileMgrButtonControl.SelectedIndexChanged += new System.EventHandler(this.SeqFileMgrButtonControl_SelectedIndexChanged);
			// 
			// AppMgrButtonControl
			// 
			this.AppMgrButtonControl.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.AppMgrButtonControl.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.AppMgrButtonControl.FormattingEnabled = true;
			this.AppMgrButtonControl.Location = new System.Drawing.Point(8, 34);
			this.AppMgrButtonControl.Name = "AppMgrButtonControl";
			this.AppMgrButtonControl.Size = new System.Drawing.Size(479, 21);
			this.AppMgrButtonControl.TabIndex = 4;
			this.AppMgrButtonControl.SelectedIndexChanged += new System.EventHandler(this.AppMgrButtonControl_SelectedIndexChanged);
			// 
			// axButton3
			// 
			this.axButton3.Location = new System.Drawing.Point(14, 227);
			this.axButton3.Name = "axButton3";
			this.axButton3.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axButton3.OcxState")));
			this.axButton3.Size = new System.Drawing.Size(192, 23);
			this.axButton3.TabIndex = 0;
			// 
			// axButton2
			// 
			this.axButton2.Location = new System.Drawing.Point(14, 146);
			this.axButton2.Name = "axButton2";
			this.axButton2.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axButton2.OcxState")));
			this.axButton2.Size = new System.Drawing.Size(192, 23);
			this.axButton2.TabIndex = 0;
			// 
			// axButton1
			// 
			this.axButton1.Location = new System.Drawing.Point(14, 61);
			this.axButton1.Name = "axButton1";
			this.axButton1.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axButton1.OcxState")));
			this.axButton1.Size = new System.Drawing.Size(192, 23);
			this.axButton1.TabIndex = 0;
			// 
			// CheckBoxGrp
			// 
			this.CheckBoxGrp.Controls.Add(this.label18);
			this.CheckBoxGrp.Controls.Add(this.checkBoxControl);
			this.CheckBoxGrp.Controls.Add(this.axCheckBox1);
			this.CheckBoxGrp.Dock = System.Windows.Forms.DockStyle.Fill;
			this.CheckBoxGrp.Location = new System.Drawing.Point(0, 0);
			this.CheckBoxGrp.Name = "CheckBoxGrp";
			this.CheckBoxGrp.Size = new System.Drawing.Size(486, 301);
			this.CheckBoxGrp.TabIndex = 10;
			this.CheckBoxGrp.TabStop = false;
			this.CheckBoxGrp.Text = "CheckBox Control";
			// 
			// label18
			// 
			this.label18.AutoSize = true;
			this.label18.Location = new System.Drawing.Point(4, 17);
			this.label18.Name = "label18";
			this.label18.Size = new System.Drawing.Size(220, 13);
			this.label18.TabIndex = 8;
			this.label18.Text = "Select Command Kind (Application Manager):";
			// 
			// checkBoxControl
			// 
			this.checkBoxControl.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.checkBoxControl.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.checkBoxControl.FormattingEnabled = true;
			this.checkBoxControl.Location = new System.Drawing.Point(6, 34);
			this.checkBoxControl.Name = "checkBoxControl";
			this.checkBoxControl.Size = new System.Drawing.Size(472, 21);
			this.checkBoxControl.TabIndex = 7;
			this.checkBoxControl.SelectedIndexChanged += new System.EventHandler(this.checkBoxControl_SelectedIndexChanged);
			// 
			// axCheckBox1
			// 
			this.axCheckBox1.Location = new System.Drawing.Point(27, 61);
			this.axCheckBox1.Name = "axCheckBox1";
			this.axCheckBox1.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axCheckBox1.OcxState")));
			this.axCheckBox1.Size = new System.Drawing.Size(236, 32);
			this.axCheckBox1.TabIndex = 1;
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point(6, 6);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(678, 39);
			this.label3.TabIndex = 8;
			this.label3.Text = resources.GetString("label3.Text");
			// 
			// listPage
			// 
			this.listPage.Controls.Add(this.splitContainer4);
			this.listPage.Controls.Add(this.label2);
			this.listPage.Location = new System.Drawing.Point(4, 22);
			this.listPage.Name = "listPage";
			this.listPage.Padding = new System.Windows.Forms.Padding(3);
			this.listPage.Size = new System.Drawing.Size(997, 371);
			this.listPage.TabIndex = 1;
			this.listPage.Text = "List Connections";
			this.listPage.UseVisualStyleBackColor = true;
			// 
			// splitContainer4
			// 
			this.splitContainer4.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.splitContainer4.IsSplitterFixed = true;
			this.splitContainer4.Location = new System.Drawing.Point(6, 59);
			this.splitContainer4.Name = "splitContainer4";
			// 
			// splitContainer4.Panel1
			// 
			this.splitContainer4.Panel1.Controls.Add(this.comboBoxGrp);
			// 
			// splitContainer4.Panel2
			// 
			this.splitContainer4.Panel2.Controls.Add(this.splitContainer5);
			this.splitContainer4.Size = new System.Drawing.Size(986, 306);
			this.splitContainer4.SplitterDistance = 323;
			this.splitContainer4.TabIndex = 11;
			// 
			// comboBoxGrp
			// 
			this.comboBoxGrp.Controls.Add(this.label13);
			this.comboBoxGrp.Controls.Add(this.label8);
			this.comboBoxGrp.Controls.Add(this.comboBoxControl);
			this.comboBoxGrp.Controls.Add(this.axComboBox1);
			this.comboBoxGrp.Dock = System.Windows.Forms.DockStyle.Fill;
			this.comboBoxGrp.Location = new System.Drawing.Point(0, 0);
			this.comboBoxGrp.Name = "comboBoxGrp";
			this.comboBoxGrp.Size = new System.Drawing.Size(323, 306);
			this.comboBoxGrp.TabIndex = 8;
			this.comboBoxGrp.TabStop = false;
			this.comboBoxGrp.Text = "ComboBox Control";
			// 
			// label13
			// 
			this.label13.AutoSize = true;
			this.label13.Location = new System.Drawing.Point(6, 112);
			this.label13.Name = "label13";
			this.label13.Size = new System.Drawing.Size(160, 13);
			this.label13.TabIndex = 5;
			this.label13.Text = "TestStand UI ComboBox Control";
			// 
			// label8
			// 
			this.label8.AutoSize = true;
			this.label8.Location = new System.Drawing.Point(5, 22);
			this.label8.Name = "label8";
			this.label8.Size = new System.Drawing.Size(158, 13);
			this.label8.TabIndex = 4;
			this.label8.Text = "Configure ComboBox to Display:";
			// 
			// comboBoxControl
			// 
			this.comboBoxControl.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.comboBoxControl.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.comboBoxControl.FormattingEnabled = true;
			this.comboBoxControl.Location = new System.Drawing.Point(8, 39);
			this.comboBoxControl.Name = "comboBoxControl";
			this.comboBoxControl.Size = new System.Drawing.Size(305, 21);
			this.comboBoxControl.TabIndex = 3;
			this.comboBoxControl.SelectedIndexChanged += new System.EventHandler(this.comboBoxControl_SelectedIndexChanged);
			// 
			// axComboBox1
			// 
			this.axComboBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.axComboBox1.Location = new System.Drawing.Point(8, 129);
			this.axComboBox1.Name = "axComboBox1";
			this.axComboBox1.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axComboBox1.OcxState")));
			this.axComboBox1.Size = new System.Drawing.Size(305, 22);
			this.axComboBox1.TabIndex = 0;
			// 
			// splitContainer5
			// 
			this.splitContainer5.Dock = System.Windows.Forms.DockStyle.Fill;
			this.splitContainer5.IsSplitterFixed = true;
			this.splitContainer5.Location = new System.Drawing.Point(0, 0);
			this.splitContainer5.Name = "splitContainer5";
			// 
			// splitContainer5.Panel1
			// 
			this.splitContainer5.Panel1.Controls.Add(this.ListBoxGrp);
			// 
			// splitContainer5.Panel2
			// 
			this.splitContainer5.Panel2.Controls.Add(this.ListBarGrp);
			this.splitContainer5.Size = new System.Drawing.Size(659, 306);
			this.splitContainer5.SplitterDistance = 333;
			this.splitContainer5.TabIndex = 0;
			// 
			// ListBoxGrp
			// 
			this.ListBoxGrp.Controls.Add(this.label14);
			this.ListBoxGrp.Controls.Add(this.label9);
			this.ListBoxGrp.Controls.Add(this.ListBoxControl);
			this.ListBoxGrp.Controls.Add(this.axListBox1);
			this.ListBoxGrp.Dock = System.Windows.Forms.DockStyle.Fill;
			this.ListBoxGrp.Location = new System.Drawing.Point(0, 0);
			this.ListBoxGrp.Name = "ListBoxGrp";
			this.ListBoxGrp.Size = new System.Drawing.Size(333, 306);
			this.ListBoxGrp.TabIndex = 9;
			this.ListBoxGrp.TabStop = false;
			this.ListBoxGrp.Text = "ListBox Control";
			// 
			// label14
			// 
			this.label14.AutoSize = true;
			this.label14.Location = new System.Drawing.Point(6, 110);
			this.label14.Name = "label14";
			this.label14.Size = new System.Drawing.Size(143, 13);
			this.label14.TabIndex = 6;
			this.label14.Text = "TestStand UI ListBox Control";
			// 
			// label9
			// 
			this.label9.AutoSize = true;
			this.label9.Location = new System.Drawing.Point(5, 22);
			this.label9.Name = "label9";
			this.label9.Size = new System.Drawing.Size(141, 13);
			this.label9.TabIndex = 5;
			this.label9.Text = "Configure ListBox to Display:";
			// 
			// ListBoxControl
			// 
			this.ListBoxControl.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.ListBoxControl.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.ListBoxControl.FormattingEnabled = true;
			this.ListBoxControl.Location = new System.Drawing.Point(8, 39);
			this.ListBoxControl.Name = "ListBoxControl";
			this.ListBoxControl.Size = new System.Drawing.Size(319, 21);
			this.ListBoxControl.TabIndex = 4;
			this.ListBoxControl.SelectedIndexChanged += new System.EventHandler(this.ListBoxControl_SelectedIndexChanged);
			// 
			// axListBox1
			// 
			this.axListBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.axListBox1.Location = new System.Drawing.Point(7, 127);
			this.axListBox1.Name = "axListBox1";
			this.axListBox1.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axListBox1.OcxState")));
			this.axListBox1.Size = new System.Drawing.Size(320, 172);
			this.axListBox1.TabIndex = 1;
			// 
			// ListBarGrp
			// 
			this.ListBarGrp.Controls.Add(this.label12);
			this.ListBarGrp.Controls.Add(this.label11);
			this.ListBarGrp.Controls.Add(this.label10);
			this.ListBarGrp.Controls.Add(this.ListBarControlPage2);
			this.ListBarGrp.Controls.Add(this.ListBarControlPage1);
			this.ListBarGrp.Controls.Add(this.axListBar1);
			this.ListBarGrp.Dock = System.Windows.Forms.DockStyle.Fill;
			this.ListBarGrp.Location = new System.Drawing.Point(0, 0);
			this.ListBarGrp.Name = "ListBarGrp";
			this.ListBarGrp.Size = new System.Drawing.Size(322, 306);
			this.ListBarGrp.TabIndex = 10;
			this.ListBarGrp.TabStop = false;
			this.ListBarGrp.Text = "ListBar Control";
			// 
			// label12
			// 
			this.label12.AutoSize = true;
			this.label12.Location = new System.Drawing.Point(6, 110);
			this.label12.Name = "label12";
			this.label12.Size = new System.Drawing.Size(141, 13);
			this.label12.TabIndex = 7;
			this.label12.Text = "TestStand UI ListBar Control";
			// 
			// label11
			// 
			this.label11.AutoSize = true;
			this.label11.Location = new System.Drawing.Point(5, 64);
			this.label11.Name = "label11";
			this.label11.Size = new System.Drawing.Size(188, 13);
			this.label11.TabIndex = 7;
			this.label11.Text = "Configure Page 2 of ListBar to Display:";
			// 
			// label10
			// 
			this.label10.AutoSize = true;
			this.label10.Location = new System.Drawing.Point(5, 22);
			this.label10.Name = "label10";
			this.label10.Size = new System.Drawing.Size(188, 13);
			this.label10.TabIndex = 7;
			this.label10.Text = "Configure Page 1 of ListBar to Display:";
			// 
			// ListBarControlPage2
			// 
			this.ListBarControlPage2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.ListBarControlPage2.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.ListBarControlPage2.FormattingEnabled = true;
			this.ListBarControlPage2.Location = new System.Drawing.Point(8, 81);
			this.ListBarControlPage2.Name = "ListBarControlPage2";
			this.ListBarControlPage2.Size = new System.Drawing.Size(307, 21);
			this.ListBarControlPage2.TabIndex = 6;
			this.ListBarControlPage2.SelectedIndexChanged += new System.EventHandler(this.ListBarControlPage2_SelectedIndexChanged);
			// 
			// ListBarControlPage1
			// 
			this.ListBarControlPage1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.ListBarControlPage1.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.ListBarControlPage1.FormattingEnabled = true;
			this.ListBarControlPage1.Location = new System.Drawing.Point(8, 39);
			this.ListBarControlPage1.Name = "ListBarControlPage1";
			this.ListBarControlPage1.Size = new System.Drawing.Size(307, 21);
			this.ListBarControlPage1.TabIndex = 5;
			this.ListBarControlPage1.SelectedIndexChanged += new System.EventHandler(this.ListBarControlPage1_SelectedIndexChanged);
			// 
			// axListBar1
			// 
			this.axListBar1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.axListBar1.Enabled = true;
			this.axListBar1.Location = new System.Drawing.Point(8, 127);
			this.axListBar1.Name = "axListBar1";
			this.axListBar1.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axListBar1.OcxState")));
			this.axListBar1.Size = new System.Drawing.Size(307, 172);
			this.axListBar1.TabIndex = 2;
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(6, 7);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(751, 39);
			this.label2.TabIndex = 7;
			this.label2.Text = resources.GetString("label2.Text");
			// 
			// viewPage
			// 
			this.viewPage.Controls.Add(this.splitContainer2);
			this.viewPage.Controls.Add(this.label1);
			this.viewPage.Location = new System.Drawing.Point(4, 22);
			this.viewPage.Name = "viewPage";
			this.viewPage.Padding = new System.Windows.Forms.Padding(3);
			this.viewPage.Size = new System.Drawing.Size(997, 371);
			this.viewPage.TabIndex = 0;
			this.viewPage.Text = "View Connections";
			this.viewPage.UseVisualStyleBackColor = true;
			// 
			// splitContainer2
			// 
			this.splitContainer2.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.splitContainer2.Location = new System.Drawing.Point(6, 59);
			this.splitContainer2.Name = "splitContainer2";
			// 
			// splitContainer2.Panel1
			// 
			this.splitContainer2.Panel1.Controls.Add(this.variablesViewGrp);
			this.splitContainer2.Panel1MinSize = 300;
			// 
			// splitContainer2.Panel2
			// 
			this.splitContainer2.Panel2.Controls.Add(this.reportViewGrp);
			this.splitContainer2.Panel2MinSize = 300;
			this.splitContainer2.Size = new System.Drawing.Size(985, 306);
			this.splitContainer2.SplitterDistance = 486;
			this.splitContainer2.TabIndex = 6;
			// 
			// variablesViewGrp
			// 
			this.variablesViewGrp.Controls.Add(this.label6);
			this.variablesViewGrp.Controls.Add(this.label5);
			this.variablesViewGrp.Controls.Add(this.variablesViewControl);
			this.variablesViewGrp.Controls.Add(this.axVariablesView);
			this.variablesViewGrp.Dock = System.Windows.Forms.DockStyle.Fill;
			this.variablesViewGrp.Location = new System.Drawing.Point(0, 0);
			this.variablesViewGrp.Name = "variablesViewGrp";
			this.variablesViewGrp.Size = new System.Drawing.Size(486, 306);
			this.variablesViewGrp.TabIndex = 4;
			this.variablesViewGrp.TabStop = false;
			this.variablesViewGrp.Text = "VariablesView Control";
			// 
			// label6
			// 
			this.label6.AutoSize = true;
			this.label6.Location = new System.Drawing.Point(6, 62);
			this.label6.Name = "label6";
			this.label6.Size = new System.Drawing.Size(175, 13);
			this.label6.TabIndex = 4;
			this.label6.Text = "TestStand UI VariablesView Control";
			// 
			// label5
			// 
			this.label5.AutoSize = true;
			this.label5.Location = new System.Drawing.Point(6, 21);
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size(131, 13);
			this.label5.TabIndex = 3;
			this.label5.Text = "Connect VariablesView to:";
			// 
			// variablesViewControl
			// 
			this.variablesViewControl.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.variablesViewControl.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.variablesViewControl.FormattingEnabled = true;
			this.variablesViewControl.Items.AddRange(new object[] {
            "Sequence File View Manager",
            "Execution View Manager"});
			this.variablesViewControl.Location = new System.Drawing.Point(7, 38);
			this.variablesViewControl.Name = "variablesViewControl";
			this.variablesViewControl.Size = new System.Drawing.Size(473, 21);
			this.variablesViewControl.TabIndex = 2;
			this.variablesViewControl.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
			// 
			// axVariablesView
			// 
			this.axVariablesView.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.axVariablesView.Location = new System.Drawing.Point(7, 79);
			this.axVariablesView.Name = "axVariablesView";
			this.axVariablesView.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axVariablesView.OcxState")));
			this.axVariablesView.Size = new System.Drawing.Size(473, 221);
			this.axVariablesView.TabIndex = 1;
			// 
			// reportViewGrp
			// 
			this.reportViewGrp.Controls.Add(this.label7);
			this.reportViewGrp.Controls.Add(this.axReportView);
			this.reportViewGrp.Dock = System.Windows.Forms.DockStyle.Fill;
			this.reportViewGrp.Location = new System.Drawing.Point(0, 0);
			this.reportViewGrp.Name = "reportViewGrp";
			this.reportViewGrp.Size = new System.Drawing.Size(495, 306);
			this.reportViewGrp.TabIndex = 5;
			this.reportViewGrp.TabStop = false;
			this.reportViewGrp.Text = "ReportView Control";
			// 
			// label7
			// 
			this.label7.AutoSize = true;
			this.label7.Location = new System.Drawing.Point(3, 21);
			this.label7.Name = "label7";
			this.label7.Size = new System.Drawing.Size(387, 13);
			this.label7.TabIndex = 5;
			this.label7.Text = "TestStand UI ReportView Control (Always connected to ExecutionViewManager)";
			// 
			// axReportView
			// 
			this.axReportView.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.axReportView.Enabled = true;
			this.axReportView.Location = new System.Drawing.Point(6, 38);
			this.axReportView.Name = "axReportView";
			this.axReportView.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axReportView.OcxState")));
			this.axReportView.Size = new System.Drawing.Size(483, 262);
			this.axReportView.TabIndex = 0;
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(6, 7);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(993, 39);
			this.label1.TabIndex = 3;
			this.label1.Text = resources.GetString("label1.Text");
			// 
			// tabControl1
			// 
			this.tabControl1.Controls.Add(this.viewPage);
			this.tabControl1.Controls.Add(this.listPage);
			this.tabControl1.Controls.Add(this.commandPage);
			this.tabControl1.Controls.Add(this.infoPage);
			this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.tabControl1.Location = new System.Drawing.Point(0, 0);
			this.tabControl1.Name = "tabControl1";
			this.tabControl1.SelectedIndex = 0;
			this.tabControl1.Size = new System.Drawing.Size(1005, 397);
			this.tabControl1.TabIndex = 23;
			// 
			// splitContainer3
			// 
			this.splitContainer3.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.splitContainer3.Location = new System.Drawing.Point(6, -1);
			this.splitContainer3.Name = "splitContainer3";
			this.splitContainer3.Orientation = System.Windows.Forms.Orientation.Horizontal;
			// 
			// splitContainer3.Panel1
			// 
			this.splitContainer3.Panel1.Controls.Add(this.groupBox1);
			this.splitContainer3.Panel1MinSize = 254;
			// 
			// splitContainer3.Panel2
			// 
			this.splitContainer3.Panel2.Controls.Add(this.ViewHelp);
			this.splitContainer3.Panel2.Controls.Add(this.tabControl1);
			this.splitContainer3.Panel2MinSize = 350;
			this.splitContainer3.Size = new System.Drawing.Size(1005, 706);
			this.splitContainer3.SplitterDistance = 305;
			this.splitContainer3.TabIndex = 7;
			// 
			// ViewHelp
			// 
			this.ViewHelp.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.ViewHelp.BackColor = System.Drawing.Color.Transparent;
			this.ViewHelp.Location = new System.Drawing.Point(857, 54);
			this.ViewHelp.Name = "ViewHelp";
			this.ViewHelp.Size = new System.Drawing.Size(138, 25);
			this.ViewHelp.TabIndex = 6;
			this.ViewHelp.Text = "Additional Information...";
			this.ViewHelp.UseVisualStyleBackColor = false;
			this.ViewHelp.Click += new System.EventHandler(this.ViewHelp_Click);
			// 
			// MainForm
			// 
			this.ClientSize = new System.Drawing.Size(1018, 730);
			this.Controls.Add(this.axStatusBar1);
			this.Controls.Add(this.splitContainer3);
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.MinimumSize = new System.Drawing.Size(1034, 768);
			this.Name = "MainForm";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "Connecting UI Controls Example";
			this.Closing += new System.ComponentModel.CancelEventHandler(this.MainForm_Closing);
			this.Load += new System.EventHandler(this.MainForm_Load);
			((System.ComponentModel.ISupportInitialize)(this.axApplicationMgr)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.axOpenFileButton)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.axExecutionViewMgr)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.axSequenceFileViewMgr)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.axEntryPoint1Button)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.axRunSelectedButton)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.axSequenceView)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.axBreakResumeButton)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.axTerminateRestartButton)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.axSequenceViewExec)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.axStatusBar1)).EndInit();
			this.groupBox1.ResumeLayout(false);
			this.groupBox1.PerformLayout();
			this.splitContainer1.Panel1.ResumeLayout(false);
			this.splitContainer1.Panel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
			this.splitContainer1.ResumeLayout(false);
			this.infoPage.ResumeLayout(false);
			this.infoPage.PerformLayout();
			this.splitContainer7.Panel1.ResumeLayout(false);
			this.splitContainer7.Panel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.splitContainer7)).EndInit();
			this.splitContainer7.ResumeLayout(false);
			this.LabelGrp.ResumeLayout(false);
			this.LabelGrp.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.axLabel2)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.axLabel1)).EndInit();
			this.statusBarGrp.ResumeLayout(false);
			this.statusBarGrp.PerformLayout();
			this.commandPage.ResumeLayout(false);
			this.commandPage.PerformLayout();
			this.splitContainer6.Panel1.ResumeLayout(false);
			this.splitContainer6.Panel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.splitContainer6)).EndInit();
			this.splitContainer6.ResumeLayout(false);
			this.ButtonGrp.ResumeLayout(false);
			this.ButtonGrp.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.axButton3)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.axButton2)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.axButton1)).EndInit();
			this.CheckBoxGrp.ResumeLayout(false);
			this.CheckBoxGrp.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.axCheckBox1)).EndInit();
			this.listPage.ResumeLayout(false);
			this.listPage.PerformLayout();
			this.splitContainer4.Panel1.ResumeLayout(false);
			this.splitContainer4.Panel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.splitContainer4)).EndInit();
			this.splitContainer4.ResumeLayout(false);
			this.comboBoxGrp.ResumeLayout(false);
			this.comboBoxGrp.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.axComboBox1)).EndInit();
			this.splitContainer5.Panel1.ResumeLayout(false);
			this.splitContainer5.Panel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.splitContainer5)).EndInit();
			this.splitContainer5.ResumeLayout(false);
			this.ListBoxGrp.ResumeLayout(false);
			this.ListBoxGrp.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.axListBox1)).EndInit();
			this.ListBarGrp.ResumeLayout(false);
			this.ListBarGrp.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.axListBar1)).EndInit();
			this.viewPage.ResumeLayout(false);
			this.viewPage.PerformLayout();
			this.splitContainer2.Panel1.ResumeLayout(false);
			this.splitContainer2.Panel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).EndInit();
			this.splitContainer2.ResumeLayout(false);
			this.variablesViewGrp.ResumeLayout(false);
			this.variablesViewGrp.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.axVariablesView)).EndInit();
			this.reportViewGrp.ResumeLayout(false);
			this.reportViewGrp.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.axReportView)).EndInit();
			this.tabControl1.ResumeLayout(false);
			this.splitContainer3.Panel1.ResumeLayout(false);
			this.splitContainer3.Panel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.splitContainer3)).EndInit();
			this.splitContainer3.ResumeLayout(false);
			this.ResumeLayout(false);

		}
		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>

		//enums used to populate comboBox controls
		private enum ViewManagers
		{
			SequenceFileViewManager,
			ExecutionViewManager
		}
		private enum ListConnections
		{
			ExecutionList,
			CallStack,
			ThreadList,
			SequenceList,
			SequenceFileList,
			StepGroupList
		}
		private enum ButtonCommandKinds
		{
			CommandKind_NotACommand = 0,
			CommandKind_Container = 1,
			CommandKind_Separator = 2,
			CommandKind_Custom = 3,
			CommandKind_OpenSequenceFile = 20,
			CommandKind_Close = 21,
			CommandKind_CloseAll = 22,
			CommandKind_CloseCompletedExecutions = 23,
			CommandKind_OpenWorkspaceBrowser = 24,
			CommandKind_Login = 25,
			CommandKind_Logout = 26,
			CommandKind_LoginLogout = 27,
			CommandKind_UnloadAllModules = 28,
			CommandKind_MRUFile = 29,
			CommandKind_Exit = 30,
			CommandKind_Restart = 40,
			CommandKind_RunEntryPoint = 41,
			CommandKind_RunEntryPointOnSelectedSteps = 42,
			CommandKind_LoopEntryPointOnSelectedSteps = 43,
			CommandKind_RunCurrentSequence = 44,
			CommandKind_RunSpecificSequence = 45,
			CommandKind_RunSelectedSteps = 46,
			CommandKind_RunSelectedStepsUsingEntryPointsSubmenu = 47,
			CommandKind_LoopOnSelectedSteps = 48,
			CommandKind_LoopOnSelectedStepsUsingEntryPointsSubmenu = 49,
			CommandKind_BreakOnFirstStep = 50,
			CommandKind_BreakOnStepFailure = 51,
			CommandKind_BreakOnSequenceFailure = 52,
			CommandKind_TracingEnabled = 53,
			CommandKind_ToggleBreakpoint = 60,
			CommandKind_SetRunModeSubmenu = 61,
			CommandKind_RunModeForcePass = 62,
			CommandKind_RunModeForceFail = 63,
			CommandKind_RunModeSkip = 64,
			CommandKind_RunModeNormal = 65,
			CommandKind_Resume = 66,
			CommandKind_StepInto = 67,
			CommandKind_StepOver = 68,
			CommandKind_StepOut = 69,
			CommandKind_SetNextStep = 70,
			CommandKind_Break = 71,
			CommandKind_BreakResume = 72,
			CommandKind_Terminate = 73,
			CommandKind_TerminateRestart = 74,
			CommandKind_Abort = 75,
			CommandKind_BreakAll = 76,
			CommandKind_TerminateAll = 77,
			CommandKind_AbortAll = 78,
			CommandKind_ResumeAll = 79,
			CommandKind_DisplayBreakpointsAndWatchExpressions = 80,
			CommandKind_DisplayBreakpointSettings = 81,
			CommandKind_BreakpointSubmenu = 85,
			CommandKind_ConfigureAdapters = 90,
			CommandKind_ConfigureStationOptions = 91,
			CommandKind_ConfigureSearchDirectories = 92,
			CommandKind_ConfigureExternalViewers = 93,
			CommandKind_ToolItem = 100,
			CommandKind_CustomizeTools = 101,
			CommandKind_ExecutionEntryPointInsertionMarker = 110,
			CommandKind_ExecutionEntryPointDefaultMenuInsertionMarker = 111,
			CommandKind_ConfigurationEntryPointInsertionMarker = 112,
			CommandKind_ConfigurationEntryPointDefaultMenuInsertionMarker = 113,
			CommandKind_SequenceViewConfiguration = 116,
			CommandKind_SequenceViewConfigurationsSubmenu = 118,
			CommandKind_DefaultFileMenu_Set = 120,
			CommandKind_DefaultExecuteMenu_Set = 121,
			CommandKind_DefaultDebugMenu_Set = 123,
			CommandKind_DefaultConfigureMenu_Set = 124,
			CommandKind_DefaultToolsMenu_Set = 125,
			CommandKind_DefaultSequenceViewContextMenu_Set = 126,
			CommandKind_DefaultListBarContextMenu_Set = 127,
			CommandKind_DefaultEditMenu_Set = 128,
			CommandKind_DefaultSequenceListContextMenu_Set = 129,
			CommandKind_SequenceViewConfigurations_Set = 139,
			CommandKind_MRUFiles_Set = 140,
			CommandKind_ExecutionEntryPoints_Set = 141,
			CommandKind_RunSequences_Set = 142,
			CommandKind_RunSelectedStepsUsingEntryPoints_Set = 143,
			CommandKind_LoopOnSelectedStepsUsingEntryPoints_Set = 144,
			CommandKind_ConfigurationEntryPoints_Set = 145,
			CommandKind_Tools_Set = 146,
			CommandKind_OpenSequenceFiles = 147,
			CommandKind_LockUnlock = 148,
			CommandKind_ConfigureSequenceViews = 149,
			CommandKind_Edit_Undo = 200,
			CommandKind_Edit_Redo = 201,
			CommandKind_Edit_Rename = 202,
			CommandKind_Edit_Cut = 203,
			CommandKind_Edit_Copy = 204,
			CommandKind_Edit_Paste = 205,
			CommandKind_Edit_Delete = 206,
			CommandKind_Edit_InsertStep = 207,
			CommandKind_Edit_Save = 208,
			CommandKind_Edit_SaveAs = 209,
			CommandKind_Edit_SaveAll = 210,
			CommandKind_Edit_NewSequenceFile = 211,
			CommandKind_Edit_StepProperties = 212,
			CommandKind_Edit_SequenceProperties = 213,
			CommandKind_Edit_SequenceFileProperties = 214,
			CommandKind_Edit_SpecifyModule = 215,
			CommandKind_Edit_EditCode = 216,
			CommandKind_Edit_EditStep = 217,
			CommandKind_Edit_Preconditions = 218,
			CommandKind_SelectAll = 219,
			CommandKind_Edit_SelectDefaultAdapter = 220,
			CommandKind_Edit_InsertSequence = 221,
			CommandKind_Edit_SequenceFileCallbacks = 222,
			CommandKind_Edit_EditPaths = 223,
			CommandKind_Edit_EncapsulateSelectedSteps = 224,
			CommandKind_Edit_InsertStepsSubmenu = 300,
			CommandKind_Edit_EncapsulateSelectedStepsSubmenu = 303,
			CommandKind_Edit_InsertSteps_Set = 340,
			CommandKind_Edit_SelectDefaultAdapters_Set = 342,
			CommandKind_Edit_EncapsulateSelectedSteps_Set = 343,
			CommandKind_ShowInList = 400,
			CommandKind_ShowInVariables = 401,
			CommandKind_ShowTestStandHelp = 420,
			CommandKind_ShowGuideToDocumentation = 421,
			CommandKind_ShowHelpTopic = 422,
			CommandKind_ShowTestStandWebResources = 423,
			CommandKind_ShowTestStandDiscussionForum = 424,
			CommandKind_ShowPatents = 425,
			CommandKind_DefaultHelpMenu_Set = 440,
			CommandKind_Edit_Attributes = 450,
			CommandKind_Edit_AdvancedSequenceListSubmenu = 451,
			CommandKind_ShowUpdateService = 452,
			CommandKind_ShowExamples = 453,
			CommandKind_ShowGettingStarted = 454
		}
		private enum CheckBoxCommandKinds
		{
			CommandKind_BreakonFirstStep = 50,
			CommandKind_BreakOnSequenceFailure = 52,
			CommandKind_BreakOnStepFailure = 51,
			CommandKind_ToggleBreakPoint = 60,
			CommandKind_TracingEnabled = 53
		}
		private enum SeqFileViewCaptionSources
		{
			CaptionSource_NotASource = 0,
			CaptionSource_MacroExpression = 1,
			CaptionSource_UserName = 8,
			CaptionSource_CurrentSequenceFile = 11,
			CaptionSource_CurrentSequenceFileComment = 12,
			CaptionSource_CurrentSequence = 13,
			CaptionSource_CurrentSequenceComment = 14,
			CaptionSource_CurrentStepGroup = 15,
			CaptionSource_SelectedSteps_ZeroBased = 20,
			CaptionSource_SelectedTests_OneBased = 21,
			CaptionSource_NumberOfSteps = 22,
			CaptionSource_NumberOfTests = 23,
			CaptionSource_CurrentProcessModelFile = 27,
			CaptionSource_Time = 30,
			CaptionSource_Date = 31,
			CaptionSource_CurrentSequenceFile_WithoutFileState = 32,
			CaptionSource_CurrentSequenceFile_FileStateOnly = 33
		}
		private enum ExecViewCaptionSources
		{
			CaptionSource_NotASource = 0,
			CaptionSource_MacroExpression = 1,
			CaptionSource_UUTSerialNumber = 2,
			CaptionSource_UUTStatus = 3,
			CaptionSource_BatchSerialNumber = 4,
			CaptionSource_BatchStatus = 5,
			CaptionSource_BatchState = 6,
			CaptionSource_ModelState = 7,
			CaptionSource_UserName = 8,
			CaptionSource_ProgressText = 9,
			CaptionSource_ProgressPercent = 10,
			CaptionSource_CurrentSequenceFile = 11,
			CaptionSource_CurrentSequenceFileComment = 12,
			CaptionSource_CurrentSequence = 13,
			CaptionSource_CurrentSequenceComment = 14,
			CaptionSource_CurrentStepGroup = 15,
			CaptionSource_CurrentStep = 16,
			CaptionSource_CurrentStepComment = 17,
			CaptionSource_CurrentStepIndex_ZeroBased = 18,
			CaptionSource_CurrentTestIndex_OneBased = 19,
			CaptionSource_SelectedSteps_ZeroBased = 20,
			CaptionSource_SelectedTests_OneBased = 21,
			CaptionSource_NumberOfSteps = 22,
			CaptionSource_NumberOfTests = 23,
			CaptionSource_CurrentExecution = 24,
			CaptionSource_CurrentThread = 25,
			CaptionSource_CurrentCallStackEntry = 26,
			CaptionSource_CurrentProcessModelFile = 27,
			CaptionSource_ReportLocation = 28,
			CaptionSource_TestSocketIndex = 29,
			CaptionSource_Time = 30,
			CaptionSource_Date = 31,
			CaptionSource_CurrentSequenceFile_WithoutFileState = 32,
			CaptionSource_CurrentSequenceFile_FileStateOnly = 33
		}
		private enum SeqFileViewImageSources
		{
			ImageSource_CurrentSequenceFile = 11,
			ImageSource_CurrentSequence = 12,
			ImageSource_CurrentStepGroup = 13,
			ImageSource_CurrentProcessModelFile = 24
		}
		private enum ExecViewImageSources
		{
			ImageSource_NotASource = 0,
			ImageSource_UUTStatus = 3,
			ImageSource_BatchStatus = 5,
			ImageSource_BatchState = 6,
			ImageSource_ModelState = 7,
			ImageSource_CurrentSequenceFile = 11,
			ImageSource_CurrentSequence = 12,
			ImageSource_CurrentStepGroup = 13,
			ImageSource_CurrentStep = 14,
			ImageSource_CurrentExecution = 21,
			ImageSource_CurrentThread = 22,
			ImageSource_CurrentCallStackEntry = 23,
			ImageSource_CurrentProcessModelFile = 24,
			ImageSource_CurrentAdapter = 25
		}

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

				// connect sequence view to execution view manager									  
				axExecutionViewMgr.ConnectExecutionView(axSequenceViewExec, ExecutionViewOptions.ExecutionViewConnection_NoOptions);
				axSequenceFileViewMgr.ConnectSequenceView(axSequenceView);

				// connect report view to execution view manager									  
				axExecutionViewMgr.ConnectReportView(axReportView);

				// connect TestStand buttons to commands
				axSequenceFileViewMgr.ConnectCommand(axOpenFileButton, CommandKinds.CommandKind_OpenSequenceFiles, 0, CommandConnectionOptions.CommandConnection_EnableImage);
				axSequenceFileViewMgr.ConnectCommand(axEntryPoint1Button, CommandKinds.CommandKind_ExecutionEntryPoints_Set, 0, CommandConnectionOptions.CommandConnection_EnableImage);
				axSequenceFileViewMgr.ConnectCommand(axRunSelectedButton, CommandKinds.CommandKind_RunCurrentSequence, 0, CommandConnectionOptions.CommandConnection_EnableImage);
				axExecutionViewMgr.ConnectCommand(axBreakResumeButton, CommandKinds.CommandKind_BreakResume, 0, CommandConnectionOptions.CommandConnection_EnableImage);
				axExecutionViewMgr.ConnectCommand(axTerminateRestartButton, CommandKinds.CommandKind_TerminateRestart, 0, CommandConnectionOptions.CommandConnection_EnableImage);

				// show all step groups at once in the sequence view
				axExecutionViewMgr.StepGroupMode = StepGroupModes.StepGroupMode_AllGroups;

				// configure comboBox controls (used to dynamically change the connections of the TestStand Controls)

				// view connections
				variablesViewControl.DataSource = Enum.GetNames(typeof(ViewManagers));
				comboBoxControl.DataSource = Enum.GetNames(typeof(ListConnections));
				comboBoxControl.Text = ListConnections.ExecutionList.ToString();

				// list connections
				ListBoxControl.DataSource = Enum.GetNames(typeof(ListConnections));
				ListBoxControl.Text = ListConnections.SequenceList.ToString();
				ListBarControlPage1.DataSource = Enum.GetNames(typeof(ListConnections));
				ListBarControlPage1.Text = ListConnections.SequenceFileList.ToString();
				ListBarControlPage2.DataSource = Enum.GetNames(typeof(ListConnections));
				ListBarControlPage2.Text = ListConnections.ExecutionList.ToString();

				// command connections
				AppMgrButtonControl.DataSource = Enum.GetNames(typeof(ButtonCommandKinds));
				AppMgrButtonControl.Text = ButtonCommandKinds.CommandKind_LoginLogout.ToString();
				SeqFileMgrButtonControl.DataSource = Enum.GetNames(typeof(ButtonCommandKinds));
				SeqFileMgrButtonControl.Text = ButtonCommandKinds.CommandKind_RunSelectedSteps.ToString();
				ExecMgrButtonControl.DataSource = Enum.GetNames(typeof(ButtonCommandKinds));
				ExecMgrButtonControl.Text = ButtonCommandKinds.CommandKind_Terminate.ToString();
				checkBoxControl.DataSource = Enum.GetNames(typeof(CheckBoxCommandKinds));
				checkBoxControl.Text = CheckBoxCommandKinds.CommandKind_TracingEnabled.ToString();

				// info source connections
				ExecLabelControl.DataSource = Enum.GetNames(typeof(ExecViewCaptionSources));
				ExecLabelControl.Text = ExecViewCaptionSources.CaptionSource_NumberOfSteps.ToString();
				SeqFileLabelControl.DataSource = Enum.GetNames(typeof(SeqFileViewCaptionSources));
				SeqFileLabelControl.Text = SeqFileViewCaptionSources.CaptionSource_Time.ToString();

				StatusPane1Control.DataSource = Enum.GetNames(typeof(ExecViewImageSources));
				StatusPane1Control.Text = ExecViewImageSources.ImageSource_ModelState.ToString();
				StatusPane2Control.DataSource = Enum.GetNames(typeof(ExecViewCaptionSources));
				StatusPane2Control.Text = ExecViewCaptionSources.CaptionSource_CurrentExecution.ToString();
				StatusPane3Control.DataSource = Enum.GetNames(typeof(SeqFileViewImageSources));
				StatusPane3Control.Text = SeqFileViewImageSources.ImageSource_CurrentSequence.ToString();
				StatusPane4Control.DataSource = Enum.GetNames(typeof(SeqFileViewCaptionSources));
				StatusPane4Control.Text = SeqFileViewCaptionSources.CaptionSource_CurrentSequence.ToString();

				axApplicationMgr.Start();	// start up the TestStand User Interface Components. this also logs in the user

				// Open an example sequence file and run it
				// Typically, a TestStand UI should not open a specific sequence file.  
				// This example UI opens a specific file for demonstrational purposes only.

				string exampleSequencePath = "\\..\\..\\..\\Connecting UI Controls.seq";
				//string exampleSequencePath = "Demos\\dotNet\\Computer Motherboard Test\\Computer Motherboard Test Sequence.seq";
				string absPath;

				absPath = System.IO.Path.GetDirectoryName(Application.ExecutablePath) + exampleSequencePath;
				if (System.IO.File.Exists(absPath))
				{
					axApplicationMgr.OpenSequenceFile(absPath);
					axSequenceFileViewMgr.GetCommand(CommandKinds.CommandKind_RunCurrentSequence).Execute(true);
				}


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
			Close();

			GC.Collect(); // force .net garbage collection to ensure ensure all TestStand objects are freed before the TestStand engine unloads 							
			GC.WaitForPendingFinalizers();
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
		// as parameters to unhandled ActiveX events.  This timer ensures that all COM objects release in a timely manner,
		// thus preventing the performance hiccup that could occur when .NET finally decides to collect garbage. Also, this timer
		// ensures that actions triggered by object destruction run in a timely manner. For example: sequence file unload callbacks.
		private void GCTimerTick(object sender, System.EventArgs e)
		{
			System.GC.Collect(); // force .net garbage collection		
		}

		// ------------- ComboBox callbacks

		private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
		{
			try
			{
				ViewManagers selectedValue = (ViewManagers)Enum.Parse(typeof(ViewManagers), ((System.Windows.Forms.ComboBox)sender).Text);
				if (selectedValue == ViewManagers.ExecutionViewManager)
					axExecutionViewMgr.ConnectVariables(axVariablesView);
				else if (selectedValue == ViewManagers.SequenceFileViewManager)
					axSequenceFileViewMgr.ConnectVariables(axVariablesView);
			}
			catch (Exception theException)
			{
				MessageBox.Show(this, theException.Message, "Error");
			}
		}

		// List Connections

		private void configureListConnection(object comboBoxControl, object axControl)
		{
			try
			{
				ListConnections selectedValue = (ListConnections)Enum.Parse(typeof(ListConnections), ((System.Windows.Forms.ComboBox)comboBoxControl).Text);
				switch (selectedValue)
				{
					case ListConnections.CallStack:
						axExecutionViewMgr.ConnectCallStack(axControl);
						break;
					case ListConnections.ExecutionList:
						axExecutionViewMgr.ConnectExecutionList(axControl);
						break;
					case ListConnections.SequenceFileList:
						axSequenceFileViewMgr.ConnectSequenceFileList(axControl, false);
						break;
					case ListConnections.SequenceList:
						axSequenceFileViewMgr.ConnectSequenceList(axControl);
						break;
					case ListConnections.StepGroupList:
						axSequenceFileViewMgr.ConnectStepGroupList(axControl);
						break;
					case ListConnections.ThreadList:
						axExecutionViewMgr.ConnectThreadList(axControl);
						break;
				}
			}
			catch (Exception theException)
			{
				MessageBox.Show(this, theException.Message, "Error");
			}
		}


		private void comboBoxControl_SelectedIndexChanged(object sender, EventArgs e)
		{
			configureListConnection(sender, axComboBox1);
		}

		private void ListBoxControl_SelectedIndexChanged(object sender, EventArgs e)
		{
			configureListConnection(sender, axListBox1);
		}

		private void ListBarControlPage1_SelectedIndexChanged(object sender, EventArgs e)
		{
			configureListConnection(sender, axListBar1.Pages[0]);
		}

		private void ListBarControlPage2_SelectedIndexChanged(object sender, EventArgs e)
		{
			configureListConnection(sender, axListBar1.Pages[1]);
		}

		private void AppMgrButtonControl_SelectedIndexChanged(object sender, EventArgs e)
		{
			try
			{
				ButtonCommandKinds selectedValue = (ButtonCommandKinds)Enum.Parse(typeof(ButtonCommandKinds), ((System.Windows.Forms.ComboBox)sender).Text);
				axApplicationMgr.ConnectCommand(axButton1, (CommandKinds)selectedValue);
			}
			catch (Exception theException)
			{
				MessageBox.Show(this, theException.Message, "Error");
			}
		}

		private void SeqFileMgrButtonControl_SelectedIndexChanged(object sender, EventArgs e)
		{
			try
			{
				ButtonCommandKinds selectedValue = (ButtonCommandKinds)Enum.Parse(typeof(ButtonCommandKinds), ((System.Windows.Forms.ComboBox)sender).Text);
				axSequenceFileViewMgr.ConnectCommand(axButton2, (CommandKinds)selectedValue);
			}
			catch (Exception theException)
			{
				MessageBox.Show(this, theException.Message, "Error");
			}

		}

		private void ExecMgrButtonControl_SelectedIndexChanged(object sender, EventArgs e)
		{
			try
			{
				ButtonCommandKinds selectedValue = (ButtonCommandKinds)Enum.Parse(typeof(ButtonCommandKinds), ((System.Windows.Forms.ComboBox)sender).Text);
				axExecutionViewMgr.ConnectCommand(axButton3, (CommandKinds)selectedValue);
			}
			catch (Exception theException)
			{
				MessageBox.Show(this, theException.Message, "Error");
			}
		}


		private void checkBoxControl_SelectedIndexChanged(object sender, EventArgs e)
		{
			try
			{
				CheckBoxCommandKinds selectedValue = (CheckBoxCommandKinds)Enum.Parse(typeof(CheckBoxCommandKinds), ((System.Windows.Forms.ComboBox)sender).Text);
				axApplicationMgr.ConnectCommand(axCheckBox1, (CommandKinds)selectedValue);
			}
			catch (Exception theException)
			{
				MessageBox.Show(this, theException.Message, "Error");
			}
		}

		private void SeqFileLabelControl_SelectedIndexChanged(object sender, EventArgs e)
		{
			try
			{
				SeqFileViewCaptionSources selectedValue = (SeqFileViewCaptionSources)Enum.Parse(typeof(SeqFileViewCaptionSources), ((System.Windows.Forms.ComboBox)sender).Text);
				axSequenceFileViewMgr.ConnectCaption(axLabel1, (CaptionSources)selectedValue, useLongNames.Checked);
			}
			catch (Exception theException)
			{
				MessageBox.Show(this, theException.Message, "Error");
			}
		}

		private void ExecLabelControl_SelectedIndexChanged(object sender, EventArgs e)
		{
			try
			{
				ExecViewCaptionSources selectedValue = (ExecViewCaptionSources)Enum.Parse(typeof(ExecViewCaptionSources), ((System.Windows.Forms.ComboBox)sender).Text);
				axExecutionViewMgr.ConnectCaption(axLabel2, (CaptionSources)selectedValue, useLongNames.Checked);
			}
			catch (Exception theException)
			{
				MessageBox.Show(this, theException.Message, "Error");
			}
		}

		//Events for changing the Status bar panes

		private void StatusPane1Control_SelectedIndexChanged(object sender, EventArgs e)
		{
			ExecViewImageSources selectedValue = (ExecViewImageSources)Enum.Parse(typeof(ExecViewImageSources), ((System.Windows.Forms.ComboBox)sender).Text);
			axExecutionViewMgr.ConnectImage(axStatusBar1.Panes[0], (ImageSources)selectedValue);
		}

		private void StatusPane2Control_SelectedIndexChanged(object sender, EventArgs e)
		{
			try
			{
				ExecViewCaptionSources selectedValue = (ExecViewCaptionSources)Enum.Parse(typeof(ExecViewCaptionSources), ((System.Windows.Forms.ComboBox)sender).Text);
				axExecutionViewMgr.ConnectCaption(axStatusBar1.Panes[1], (CaptionSources)selectedValue, useLongNames.Checked);
			}
			catch (Exception theException)
			{
				MessageBox.Show(this, theException.Message, "Error");
			}
		}

		private void StatusPane3Control_SelectedIndexChanged(object sender, EventArgs e)
		{
			try
			{
				SeqFileViewImageSources selectedValue = (SeqFileViewImageSources)Enum.Parse(typeof(SeqFileViewImageSources), ((System.Windows.Forms.ComboBox)sender).Text);
				axSequenceFileViewMgr.ConnectImage(axStatusBar1.Panes[2], (ImageSources)selectedValue);
			}
			catch (Exception theException)
			{
				MessageBox.Show(this, theException.Message, "Error");
			}
		}

		private void StatusPane4Control_SelectedIndexChanged(object sender, EventArgs e)
		{
			try
			{
				SeqFileViewCaptionSources selectedValue = (SeqFileViewCaptionSources)Enum.Parse(typeof(SeqFileViewCaptionSources), ((System.Windows.Forms.ComboBox)sender).Text);
				axSequenceFileViewMgr.ConnectCaption(axStatusBar1.Panes[3], (CaptionSources)selectedValue, useLongNames.Checked);
			}
			catch (Exception theException)
			{
				MessageBox.Show(this, theException.Message, "Error");
			}
		}

		private enum TabPageNames
		{
			viewPage = 8300,
			listPage = 8299,
			commandPage = 8298,
			infoPage = 8297
		}

		private void ViewHelp_Click(object sender, EventArgs e)
		{
			try
			{
				int helpID = (int)Enum.Parse(typeof(TabPageNames), tabControl1.SelectedTab.Name);
					axApplicationMgr.GetEngine().DisplayHelpTopic(helpID, "TSFundamentals.chm");
			}
			catch (Exception theException)
			{
				MessageBox.Show(this, theException.Message, "Error");
			}
		}

	}
}