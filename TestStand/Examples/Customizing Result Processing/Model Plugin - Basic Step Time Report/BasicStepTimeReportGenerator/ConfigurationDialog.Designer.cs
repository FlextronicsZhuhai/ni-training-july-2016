namespace BasicStepTimeReportGenerator
{
	partial class ConfigurationDialog
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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ConfigurationDialog));
			this.directoryLabel = new System.Windows.Forms.Label();
			this.directoryTextBox = new System.Windows.Forms.TextBox();
			this.directoryBrowseButton = new System.Windows.Forms.Button();
			this.fileFormatLabel = new System.Windows.Forms.Label();
			this.fileFormatValue = new System.Windows.Forms.Label();
			this.launchExcelFileCheckBox = new System.Windows.Forms.CheckBox();
			this.helpButton = new System.Windows.Forms.Button();
			this.okButton = new System.Windows.Forms.Button();
			this.cancelButton = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// directoryLabel
			// 
			this.directoryLabel.AutoSize = true;
			this.directoryLabel.Location = new System.Drawing.Point(11, 25);
			this.directoryLabel.Name = "directoryLabel";
			this.directoryLabel.Size = new System.Drawing.Size(185, 13);
			this.directoryLabel.TabIndex = 0;
			this.directoryLabel.Text = "DIRECTORY_TO_STORE_REPORT";
			// 
			// directoryTextBox
			// 
			this.directoryTextBox.Location = new System.Drawing.Point(147, 24);
			this.directoryTextBox.Name = "directoryTextBox";
			this.directoryTextBox.Size = new System.Drawing.Size(544, 20);
			this.directoryTextBox.TabIndex = 1;
			this.directoryTextBox.TextChanged += new System.EventHandler(this.directoryTextBox_TextChanged);
			// 
			// directoryBrowseButton
			// 
			this.directoryBrowseButton.Location = new System.Drawing.Point(697, 24);
			this.directoryBrowseButton.Name = "directoryBrowseButton";
			this.directoryBrowseButton.Size = new System.Drawing.Size(35, 19);
			this.directoryBrowseButton.TabIndex = 2;
			this.directoryBrowseButton.Text = "...";
			this.directoryBrowseButton.UseVisualStyleBackColor = true;
			this.directoryBrowseButton.Click += new System.EventHandler(this.directoryBrowseButton_Click);
			// 
			// fileFormatLabel
			// 
			this.fileFormatLabel.AutoSize = true;
			this.fileFormatLabel.Location = new System.Drawing.Point(12, 57);
			this.fileFormatLabel.Name = "fileFormatLabel";
			this.fileFormatLabel.Size = new System.Drawing.Size(117, 13);
			this.fileFormatLabel.TabIndex = 3;
			this.fileFormatLabel.Text = "FILE_NAME_FORMAT";
			// 
			// fileFormatValue
			// 
			this.fileFormatValue.AutoSize = true;
			this.fileFormatValue.Location = new System.Drawing.Point(144, 57);
			this.fileFormatValue.Name = "fileFormatValue";
			this.fileFormatValue.Size = new System.Drawing.Size(129, 13);
			this.fileFormatValue.TabIndex = 4;
			this.fileFormatValue.Text = "RESULT_FILE_FORMAT";
			// 
			// launchExcelFileCheckBox
			// 
			this.launchExcelFileCheckBox.AutoSize = true;
			this.launchExcelFileCheckBox.Location = new System.Drawing.Point(12, 84);
			this.launchExcelFileCheckBox.Name = "launchExcelFileCheckBox";
			this.launchExcelFileCheckBox.Size = new System.Drawing.Size(224, 17);
			this.launchExcelFileCheckBox.TabIndex = 5;
			this.launchExcelFileCheckBox.Text = "&LAUNCH_BASIC_STEP_TIME_REPORT";
			this.launchExcelFileCheckBox.UseVisualStyleBackColor = true;
			this.launchExcelFileCheckBox.CheckedChanged += new System.EventHandler(this.launchExcelFileCheckBox_CheckedChanged);
			// 
			// helpButton
			// 
			this.helpButton.Location = new System.Drawing.Point(13, 118);
			this.helpButton.Name = "helpButton";
			this.helpButton.Size = new System.Drawing.Size(58, 27);
			this.helpButton.TabIndex = 6;
			this.helpButton.Text = "&HELP";
			this.helpButton.UseVisualStyleBackColor = true;
			this.helpButton.Click += new System.EventHandler(this.helpButton_Click);
			// 
			// okButton
			// 
			this.okButton.Location = new System.Drawing.Point(610, 118);
			this.okButton.Name = "okButton";
			this.okButton.Size = new System.Drawing.Size(58, 27);
			this.okButton.TabIndex = 7;
			this.okButton.Text = "&OK";
			this.okButton.UseVisualStyleBackColor = true;
			this.okButton.Click += new System.EventHandler(this.okButton_Click);
			// 
			// cancelButton
			// 
			this.cancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.cancelButton.Location = new System.Drawing.Point(674, 118);
			this.cancelButton.Name = "cancelButton";
			this.cancelButton.Size = new System.Drawing.Size(58, 27);
			this.cancelButton.TabIndex = 8;
			this.cancelButton.Text = "&CANCEL";
			this.cancelButton.UseVisualStyleBackColor = true;
			this.cancelButton.Click += new System.EventHandler(this.cancelButton_Click);
			// 
			// ConfigurationDialog
			// 
			this.AcceptButton = this.okButton;
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.CancelButton = this.cancelButton;
			this.ClientSize = new System.Drawing.Size(750, 165);
			this.Controls.Add(this.cancelButton);
			this.Controls.Add(this.okButton);
			this.Controls.Add(this.helpButton);
			this.Controls.Add(this.launchExcelFileCheckBox);
			this.Controls.Add(this.fileFormatValue);
			this.Controls.Add(this.fileFormatLabel);
			this.Controls.Add(this.directoryBrowseButton);
			this.Controls.Add(this.directoryTextBox);
			this.Controls.Add(this.directoryLabel);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.MaximizeBox = false;
			this.MaximumSize = new System.Drawing.Size(760, 197);
			this.MinimizeBox = false;
			this.MinimumSize = new System.Drawing.Size(760, 197);
			this.Name = "ConfigurationDialog";
			this.Text = "BASIC_STEP_TIME_REPORT_CONFIGURATION";
			this.HelpRequested += new System.Windows.Forms.HelpEventHandler(this.ConfigurationDialog_HelpRequested);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label directoryLabel;
		private System.Windows.Forms.TextBox directoryTextBox;
		private System.Windows.Forms.Button directoryBrowseButton;
		private System.Windows.Forms.Label fileFormatLabel;
		private System.Windows.Forms.Label fileFormatValue;
		private System.Windows.Forms.CheckBox launchExcelFileCheckBox;
		private System.Windows.Forms.Button helpButton;
		private System.Windows.Forms.Button okButton;
		private System.Windows.Forms.Button cancelButton;
	}
}