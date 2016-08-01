using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;

using NationalInstruments.TestStand.Interop.API;
using System.Runtime.InteropServices;

namespace NationalInstruments.TestStand.Examples.ComputerMotherboard
{
	/// <summary>
	/// Displays the dialog where test failure is chosen.
	/// </summary>
    public class SimulationDialog : System.Windows.Forms.Form
    {
        private System.Windows.Forms.PictureBox mMotherboardImage;
        private System.Windows.Forms.CheckBox mKeyboardFailCheckBox;
        private System.Windows.Forms.CheckBox mVideoFailCheckBox;
        private System.Windows.Forms.CheckBox mPowerFailCheckBox;
        private System.Windows.Forms.CheckBox mCpuFailCheckBox;
        private System.Windows.Forms.CheckBox mRomFailCheckBox;
        private System.Windows.Forms.CheckBox mRamFailCheckBox;
        private System.Windows.Forms.Timer mSetForegroundTimer;
        private System.Windows.Forms.Timer mCancelDialogTimer;
        private System.Windows.Forms.Button mDoneButton;
        private System.Windows.Forms.ToolTip mToolTip;

        private NationalInstruments.TestStand.Interop.API.PropertyObject mTerminationMonitorData;
        private NationalInstruments.TestStand.Interop.API.SequenceContext mSequenceContext;
        private GroupBox MainGroup;
        private PictureBox pictureBox1;
        private System.ComponentModel.IContainer components;

        public simulationData dialogData = new simulationData();

        public SimulationDialog(NationalInstruments.TestStand.Interop.API.SequenceContext currentContext)
        {
            this.mSequenceContext = currentContext;
            // Required for Windows Form Designer support
            InitializeComponent();
        }

        private void SetForegroundTimer_Tick(object sender, System.EventArgs e)
        {
            this.Activate();
            this.mSetForegroundTimer.Enabled = false;
        }

        public void InitializeTerminationStateChecking()
        {
            this.mTerminationMonitorData = this.mSequenceContext.Execution.InitTerminationMonitor();
            if (this.mSequenceContext != null)
                this.mCancelDialogTimer.Enabled = true;
        }

        private void CancelDialogTimer_Tick(object sender, System.EventArgs e)
        {
            if (this.mSequenceContext != null)
                if (this.mSequenceContext.Execution != null)
                    if (this.mSequenceContext.Execution.GetTerminationMonitorStatus(this.mTerminationMonitorData, this.mSequenceContext))
                        cmdDone_Click(this.mDoneButton, new System.EventArgs());
        }

        private void cmdDone_Click(object sender, System.EventArgs e)
        {
            dialogData.RomFail = this.mRomFailCheckBox.Checked;
            dialogData.RamFail = this.mRamFailCheckBox.Checked; 
            dialogData.CpuFail = this.mCpuFailCheckBox.Checked; 
            dialogData.PowerFail = this.mPowerFailCheckBox.Checked;
            dialogData.VideoValue = this.mVideoFailCheckBox.Checked ? 15.00 : 5.00; 
            dialogData.KeyboardValue = this.mKeyboardFailCheckBox.Checked ? 4.00 : 6.00; 
            this.Hide();
        }

        private void SimulationDialog_Closed(object sender, System.EventArgs e)
        {
            this.mCancelDialogTimer.Enabled = false;
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(SimulationDialog));
            this.mMotherboardImage = new System.Windows.Forms.PictureBox();
            this.mVideoFailCheckBox = new System.Windows.Forms.CheckBox();
            this.mCpuFailCheckBox = new System.Windows.Forms.CheckBox();
            this.mRomFailCheckBox = new System.Windows.Forms.CheckBox();
            this.mRamFailCheckBox = new System.Windows.Forms.CheckBox();
            this.mKeyboardFailCheckBox = new System.Windows.Forms.CheckBox();
            this.mPowerFailCheckBox = new System.Windows.Forms.CheckBox();
            this.mDoneButton = new System.Windows.Forms.Button();
            this.mSetForegroundTimer = new System.Windows.Forms.Timer(this.components);
            this.mToolTip = new System.Windows.Forms.ToolTip(this.components);
            this.mCancelDialogTimer = new System.Windows.Forms.Timer(this.components);
            this.MainGroup = new System.Windows.Forms.GroupBox();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.mMotherboardImage)).BeginInit();
            this.MainGroup.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // mMotherboardImage
            // 
            this.mMotherboardImage.Cursor = System.Windows.Forms.Cursors.Default;
            this.mMotherboardImage.Image = ((System.Drawing.Image)(resources.GetObject("mMotherboardImage.Image")));
            this.mMotherboardImage.Location = new System.Drawing.Point(129, 21);
            this.mMotherboardImage.Name = "mMotherboardImage";
            this.mMotherboardImage.Size = new System.Drawing.Size(368, 447);
            this.mMotherboardImage.TabIndex = 10;
            this.mMotherboardImage.TabStop = false;
            // 
            // mVideoFailCheckBox
            // 
            this.mVideoFailCheckBox.BackColor = System.Drawing.Color.White;
            this.mVideoFailCheckBox.Cursor = System.Windows.Forms.Cursors.Default;
            this.mVideoFailCheckBox.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.mVideoFailCheckBox.ForeColor = System.Drawing.SystemColors.ControlText;
            this.mVideoFailCheckBox.Location = new System.Drawing.Point(40, 152);
            this.mVideoFailCheckBox.Name = "mVideoFailCheckBox";
            this.mVideoFailCheckBox.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.mVideoFailCheckBox.Size = new System.Drawing.Size(110, 21);
            this.mVideoFailCheckBox.TabIndex = 12;
            this.mVideoFailCheckBox.Text = "Video";
            this.mVideoFailCheckBox.UseVisualStyleBackColor = false;
            // 
            // mCpuFailCheckBox
            // 
            this.mCpuFailCheckBox.BackColor = System.Drawing.Color.White;
            this.mCpuFailCheckBox.Cursor = System.Windows.Forms.Cursors.Default;
            this.mCpuFailCheckBox.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.mCpuFailCheckBox.ForeColor = System.Drawing.SystemColors.ControlText;
            this.mCpuFailCheckBox.Location = new System.Drawing.Point(40, 91);
            this.mCpuFailCheckBox.Name = "mCpuFailCheckBox";
            this.mCpuFailCheckBox.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.mCpuFailCheckBox.Size = new System.Drawing.Size(110, 21);
            this.mCpuFailCheckBox.TabIndex = 13;
            this.mCpuFailCheckBox.Text = "CPU";
            this.mCpuFailCheckBox.UseVisualStyleBackColor = false;
            // 
            // mRomFailCheckBox
            // 
            this.mRomFailCheckBox.BackColor = System.Drawing.Color.White;
            this.mRomFailCheckBox.Cursor = System.Windows.Forms.Cursors.Default;
            this.mRomFailCheckBox.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.mRomFailCheckBox.ForeColor = System.Drawing.SystemColors.ControlText;
            this.mRomFailCheckBox.Location = new System.Drawing.Point(40, 59);
            this.mRomFailCheckBox.Name = "mRomFailCheckBox";
            this.mRomFailCheckBox.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.mRomFailCheckBox.Size = new System.Drawing.Size(110, 21);
            this.mRomFailCheckBox.TabIndex = 14;
            this.mRomFailCheckBox.Text = "ROM";
            this.mRomFailCheckBox.UseVisualStyleBackColor = false;
            // 
            // mRamFailCheckBox
            // 
            this.mRamFailCheckBox.BackColor = System.Drawing.Color.White;
            this.mRamFailCheckBox.Cursor = System.Windows.Forms.Cursors.Default;
            this.mRamFailCheckBox.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.mRamFailCheckBox.ForeColor = System.Drawing.SystemColors.ControlText;
            this.mRamFailCheckBox.Location = new System.Drawing.Point(40, 121);
            this.mRamFailCheckBox.Name = "mRamFailCheckBox";
            this.mRamFailCheckBox.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.mRamFailCheckBox.Size = new System.Drawing.Size(110, 21);
            this.mRamFailCheckBox.TabIndex = 15;
            this.mRamFailCheckBox.Text = "RAM";
            this.mRamFailCheckBox.UseVisualStyleBackColor = false;
            // 
            // mKeyboardFailCheckBox
            // 
            this.mKeyboardFailCheckBox.BackColor = System.Drawing.Color.White;
            this.mKeyboardFailCheckBox.Cursor = System.Windows.Forms.Cursors.Default;
            this.mKeyboardFailCheckBox.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.mKeyboardFailCheckBox.ForeColor = System.Drawing.SystemColors.ControlText;
            this.mKeyboardFailCheckBox.Location = new System.Drawing.Point(40, 184);
            this.mKeyboardFailCheckBox.Name = "mKeyboardFailCheckBox";
            this.mKeyboardFailCheckBox.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.mKeyboardFailCheckBox.Size = new System.Drawing.Size(110, 21);
            this.mKeyboardFailCheckBox.TabIndex = 16;
            this.mKeyboardFailCheckBox.Text = "Keyboard";
            this.mKeyboardFailCheckBox.UseVisualStyleBackColor = false;
            // 
            // mPowerFailCheckBox
            // 
            this.mPowerFailCheckBox.BackColor = System.Drawing.Color.White;
            this.mPowerFailCheckBox.Cursor = System.Windows.Forms.Cursors.Default;
            this.mPowerFailCheckBox.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.mPowerFailCheckBox.ForeColor = System.Drawing.SystemColors.ControlText;
            this.mPowerFailCheckBox.Location = new System.Drawing.Point(40, 29);
            this.mPowerFailCheckBox.Name = "mPowerFailCheckBox";
            this.mPowerFailCheckBox.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.mPowerFailCheckBox.Size = new System.Drawing.Size(110, 19);
            this.mPowerFailCheckBox.TabIndex = 11;
            this.mPowerFailCheckBox.Text = "Power";
            this.mPowerFailCheckBox.UseVisualStyleBackColor = false;
            // 
            // mDoneButton
            // 
            this.mDoneButton.BackColor = System.Drawing.SystemColors.Control;
            this.mDoneButton.Cursor = System.Windows.Forms.Cursors.Default;
            this.mDoneButton.Font = new System.Drawing.Font("Arial", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.mDoneButton.ForeColor = System.Drawing.SystemColors.ControlText;
            this.mDoneButton.Location = new System.Drawing.Point(403, 492);
            this.mDoneButton.Name = "mDoneButton";
            this.mDoneButton.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.mDoneButton.Size = new System.Drawing.Size(112, 25);
            this.mDoneButton.TabIndex = 18;
            this.mDoneButton.Text = "OK";
            this.mDoneButton.UseVisualStyleBackColor = true;
            this.mDoneButton.Click += new System.EventHandler(this.cmdDone_Click);
            // 
            // mSetForegroundTimer
            // 
            this.mSetForegroundTimer.Enabled = true;
            this.mSetForegroundTimer.Interval = 500;
            this.mSetForegroundTimer.Tick += new System.EventHandler(this.SetForegroundTimer_Tick);
            // 
            // mCancelDialogTimer
            // 
            this.mCancelDialogTimer.Interval = 500;
            this.mCancelDialogTimer.Tick += new System.EventHandler(this.CancelDialogTimer_Tick);
            // 
            // MainGroup
            // 
            this.MainGroup.Controls.Add(this.mMotherboardImage);
            this.MainGroup.Controls.Add(this.mPowerFailCheckBox);
            this.MainGroup.Controls.Add(this.pictureBox1);
            this.MainGroup.Controls.Add(this.mVideoFailCheckBox);
            this.MainGroup.Controls.Add(this.mKeyboardFailCheckBox);
            this.MainGroup.Controls.Add(this.mCpuFailCheckBox);
            this.MainGroup.Controls.Add(this.mRamFailCheckBox);
            this.MainGroup.Controls.Add(this.mRomFailCheckBox);
            this.MainGroup.Location = new System.Drawing.Point(12, 12);
            this.MainGroup.Name = "MainGroup";
            this.MainGroup.Size = new System.Drawing.Size(503, 474);
            this.MainGroup.TabIndex = 19;
            this.MainGroup.TabStop = false;
            this.MainGroup.Text = "Select Simulated Components to Force Fail";
            // 
            // pictureBox1
            // 
            this.pictureBox1.Cursor = System.Windows.Forms.Cursors.Default;
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.Location = new System.Drawing.Point(7, 24);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(32, 184);
            this.pictureBox1.TabIndex = 10;
            this.pictureBox1.TabStop = false;
            // 
            // SimulationDialog
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(526, 526);
            this.Controls.Add(this.MainGroup);
            this.Controls.Add(this.mDoneButton);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "SimulationDialog";
            this.ShowIcon = false;
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Motherboard Test Simulator";
            this.Closed += new System.EventHandler(this.SimulationDialog_Closed);
            ((System.ComponentModel.ISupportInitialize)(this.mMotherboardImage)).EndInit();
            this.MainGroup.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);

        }
        #endregion

    }

    /// <summary>
    /// Class to store user-specified dialog data
    /// </summary>
    public class simulationData
    {
        public bool RomFail;
        public bool RamFail;
        public bool CpuFail;
        public bool PowerFail;
        public double VideoValue = 5.00;
        public double KeyboardValue = 6.00;
    }
}
