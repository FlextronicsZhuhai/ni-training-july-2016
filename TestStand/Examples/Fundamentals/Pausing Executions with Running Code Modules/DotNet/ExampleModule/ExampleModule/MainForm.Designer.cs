namespace ExampleModule
{
	partial class MainForm
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
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
			this.getData = new System.Windows.Forms.Timer(this.components);
			this.pollTestStandExecStatus = new System.Windows.Forms.Timer(this.components);
			this.label1 = new System.Windows.Forms.Label();
			this.ExecStatus = new System.Windows.Forms.ComboBox();
			this.label2 = new System.Windows.Forms.Label();
			this.label3 = new System.Windows.Forms.Label();
			this.threadProp = new System.Windows.Forms.CheckBox();
			this.stationOption = new System.Windows.Forms.CheckBox();
			this.OKButton = new System.Windows.Forms.Button();
			this.simulateTest = new System.Windows.Forms.TrackBar();
			((System.ComponentModel.ISupportInitialize)(this.simulateTest)).BeginInit();
			this.SuspendLayout();
			// 
			// getData
			// 
			this.getData.Enabled = true;
			this.getData.Interval = 20;
			this.getData.Tick += new System.EventHandler(this.getData_Tick);
			// 
			// pollTestStandExecStatus
			// 
			this.pollTestStandExecStatus.Enabled = true;
			this.pollTestStandExecStatus.Tick += new System.EventHandler(this.pollTestStandExecStatus_Tick);
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(533, 87);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(79, 13);
			this.label1.TabIndex = 1;
			this.label1.Text = "Test Simulation";
			// 
			// ExecStatus
			// 
			this.ExecStatus.Enabled = false;
			this.ExecStatus.FormattingEnabled = true;
			this.ExecStatus.Items.AddRange(new object[] {
            "Running",
            "Paused"});
			this.ExecStatus.Location = new System.Drawing.Point(536, 174);
			this.ExecStatus.Name = "ExecStatus";
			this.ExecStatus.Size = new System.Drawing.Size(202, 21);
			this.ExecStatus.TabIndex = 2;
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(536, 156);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(139, 13);
			this.label2.TabIndex = 1;
			this.label2.Text = "TestStand Execution Status";
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point(12, 9);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(493, 104);
			this.label3.TabIndex = 1;
			this.label3.Text = resources.GetString("label3.Text");
			// 
			// threadProp
			// 
			this.threadProp.AutoSize = true;
			this.threadProp.CheckAlign = System.Drawing.ContentAlignment.TopLeft;
			this.threadProp.Enabled = false;
			this.threadProp.Location = new System.Drawing.Point(32, 124);
			this.threadProp.Name = "threadProp";
			this.threadProp.Size = new System.Drawing.Size(437, 43);
			this.threadProp.TabIndex = 3;
			this.threadProp.Text = resources.GetString("threadProp.Text");
			this.threadProp.UseVisualStyleBackColor = true;
			// 
			// stationOption
			// 
			this.stationOption.AutoSize = true;
			this.stationOption.CheckAlign = System.Drawing.ContentAlignment.TopLeft;
			this.stationOption.Enabled = false;
			this.stationOption.Location = new System.Drawing.Point(32, 174);
			this.stationOption.Name = "stationOption";
			this.stationOption.Size = new System.Drawing.Size(433, 43);
			this.stationOption.TabIndex = 4;
			this.stationOption.Text = resources.GetString("stationOption.Text");
			this.stationOption.UseVisualStyleBackColor = true;
			// 
			// OKButton
			// 
			this.OKButton.Location = new System.Drawing.Point(645, 235);
			this.OKButton.Name = "OKButton";
			this.OKButton.Size = new System.Drawing.Size(104, 23);
			this.OKButton.TabIndex = 5;
			this.OKButton.Text = "OK";
			this.OKButton.UseVisualStyleBackColor = true;
			this.OKButton.Click += new System.EventHandler(this.OKButton_Click);
			// 
			// simulateTest
			// 
			this.simulateTest.Location = new System.Drawing.Point(536, 107);
			this.simulateTest.Maximum = 100;
			this.simulateTest.Name = "simulateTest";
			this.simulateTest.Size = new System.Drawing.Size(202, 45);
			this.simulateTest.TabIndex = 6;
			this.simulateTest.TickFrequency = 10;
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(759, 266);
			this.Controls.Add(this.simulateTest);
			this.Controls.Add(this.OKButton);
			this.Controls.Add(this.stationOption);
			this.Controls.Add(this.threadProp);
			this.Controls.Add(this.ExecStatus);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.label1);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.Name = "MainForm";
			this.Text = "Example Code Module";
			this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.formClosed);
			((System.ComponentModel.ISupportInitialize)(this.simulateTest)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Timer getData;
		private System.Windows.Forms.Timer pollTestStandExecStatus;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.ComboBox ExecStatus;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.CheckBox threadProp;
		private System.Windows.Forms.CheckBox stationOption;
		private System.Windows.Forms.Button OKButton;
		private System.Windows.Forms.TrackBar simulateTest;
	}
}

