namespace CsvToBasicStepTimeReportGenerator
{
	partial class Form1
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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
			this.csvReportPathLabel = new System.Windows.Forms.Label();
			this.csvPathTextBox = new System.Windows.Forms.TextBox();
			this.basicStepTimeReportPathTextBox = new System.Windows.Forms.TextBox();
			this.basicStepTimeReportPathLabel = new System.Windows.Forms.Label();
			this.csvReportBrowseButton = new System.Windows.Forms.Button();
			this.basicStepTimeReportBrowseButton = new System.Windows.Forms.Button();
			this.helpButton = new System.Windows.Forms.Button();
			this.okButton = new System.Windows.Forms.Button();
			this.cancelButton = new System.Windows.Forms.Button();
			this.launchBasicStepTimeReportCheckBox = new System.Windows.Forms.CheckBox();
			this.SuspendLayout();
			// 
			// csvReportPathLabel
			// 
			this.csvReportPathLabel.AutoSize = true;
			this.csvReportPathLabel.Location = new System.Drawing.Point(12, 9);
			this.csvReportPathLabel.Name = "csvReportPathLabel";
			this.csvReportPathLabel.Size = new System.Drawing.Size(100, 13);
			this.csvReportPathLabel.TabIndex = 0;
			this.csvReportPathLabel.Text = "Path of CSV Report";
			// 
			// csvPathTextBox
			// 
			this.csvPathTextBox.Location = new System.Drawing.Point(15, 25);
			this.csvPathTextBox.Name = "csvPathTextBox";
			this.csvPathTextBox.Size = new System.Drawing.Size(382, 20);
			this.csvPathTextBox.TabIndex = 1;
			// 
			// basicStepTimeReportPathTextBox
			// 
			this.basicStepTimeReportPathTextBox.Location = new System.Drawing.Point(15, 74);
			this.basicStepTimeReportPathTextBox.Name = "basicStepTimeReportPathTextBox";
			this.basicStepTimeReportPathTextBox.Size = new System.Drawing.Size(382, 20);
			this.basicStepTimeReportPathTextBox.TabIndex = 4;
			// 
			// basicStepTimeReportPathLabel
			// 
			this.basicStepTimeReportPathLabel.AutoSize = true;
			this.basicStepTimeReportPathLabel.Location = new System.Drawing.Point(12, 58);
			this.basicStepTimeReportPathLabel.Name = "basicStepTimeReportPathLabel";
			this.basicStepTimeReportPathLabel.Size = new System.Drawing.Size(156, 13);
			this.basicStepTimeReportPathLabel.TabIndex = 3;
			this.basicStepTimeReportPathLabel.Text = "Path of Basic Step Time Report";
			// 
			// csvReportBrowseButton
			// 
			this.csvReportBrowseButton.Location = new System.Drawing.Point(403, 25);
			this.csvReportBrowseButton.Name = "csvReportBrowseButton";
			this.csvReportBrowseButton.Size = new System.Drawing.Size(33, 19);
			this.csvReportBrowseButton.TabIndex = 2;
			this.csvReportBrowseButton.Text = "...";
			this.csvReportBrowseButton.UseVisualStyleBackColor = true;
			this.csvReportBrowseButton.Click += new System.EventHandler(this.csvReportBrowseButton_Click);
			// 
			// basicStepTimeReportBrowseButton
			// 
			this.basicStepTimeReportBrowseButton.Location = new System.Drawing.Point(403, 75);
			this.basicStepTimeReportBrowseButton.Name = "basicStepTimeReportBrowseButton";
			this.basicStepTimeReportBrowseButton.Size = new System.Drawing.Size(33, 19);
			this.basicStepTimeReportBrowseButton.TabIndex = 5;
			this.basicStepTimeReportBrowseButton.Text = "...";
			this.basicStepTimeReportBrowseButton.UseVisualStyleBackColor = true;
			this.basicStepTimeReportBrowseButton.Click += new System.EventHandler(this.basicStepTimeReportBrowseButton_Click);
			// 
			// helpButton
			// 
			this.helpButton.Location = new System.Drawing.Point(15, 144);
			this.helpButton.Name = "helpButton";
			this.helpButton.Size = new System.Drawing.Size(65, 28);
			this.helpButton.TabIndex = 7;
			this.helpButton.Text = "&Help";
			this.helpButton.UseVisualStyleBackColor = true;
			this.helpButton.Click += new System.EventHandler(this.helpButton_Click);
			// 
			// okButton
			// 
			this.okButton.Location = new System.Drawing.Point(300, 144);
			this.okButton.Name = "okButton";
			this.okButton.Size = new System.Drawing.Size(65, 28);
			this.okButton.TabIndex = 8;
			this.okButton.Text = "&OK";
			this.okButton.UseVisualStyleBackColor = true;
			this.okButton.Click += new System.EventHandler(this.okButton_Click);
			// 
			// cancelButton
			// 
			this.cancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.cancelButton.Location = new System.Drawing.Point(371, 144);
			this.cancelButton.Name = "cancelButton";
			this.cancelButton.Size = new System.Drawing.Size(65, 28);
			this.cancelButton.TabIndex = 9;
			this.cancelButton.Text = "&Cancel";
			this.cancelButton.UseVisualStyleBackColor = true;
			this.cancelButton.Click += new System.EventHandler(this.cancelButton_Click);
			// 
			// launchBasicStepTimeReportCheckBox
			// 
			this.launchBasicStepTimeReportCheckBox.AutoSize = true;
			this.launchBasicStepTimeReportCheckBox.Checked = true;
			this.launchBasicStepTimeReportCheckBox.CheckState = System.Windows.Forms.CheckState.Checked;
			this.launchBasicStepTimeReportCheckBox.Location = new System.Drawing.Point(15, 111);
			this.launchBasicStepTimeReportCheckBox.Name = "launchBasicStepTimeReportCheckBox";
			this.launchBasicStepTimeReportCheckBox.Size = new System.Drawing.Size(263, 17);
			this.launchBasicStepTimeReportCheckBox.TabIndex = 6;
			this.launchBasicStepTimeReportCheckBox.Text = "Launch Basic Step Time Report in Microsoft &Excel";
			this.launchBasicStepTimeReportCheckBox.UseVisualStyleBackColor = true;
			// 
			// Form1
			// 
			this.AcceptButton = this.okButton;
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.CancelButton = this.cancelButton;
			this.ClientSize = new System.Drawing.Size(452, 190);
			this.Controls.Add(this.launchBasicStepTimeReportCheckBox);
			this.Controls.Add(this.cancelButton);
			this.Controls.Add(this.okButton);
			this.Controls.Add(this.helpButton);
			this.Controls.Add(this.basicStepTimeReportBrowseButton);
			this.Controls.Add(this.csvReportBrowseButton);
			this.Controls.Add(this.basicStepTimeReportPathTextBox);
			this.Controls.Add(this.basicStepTimeReportPathLabel);
			this.Controls.Add(this.csvPathTextBox);
			this.Controls.Add(this.csvReportPathLabel);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.MaximizeBox = false;
			this.MaximumSize = new System.Drawing.Size(462, 222);
			this.MinimizeBox = false;
			this.MinimumSize = new System.Drawing.Size(462, 222);
			this.Name = "Form1";
			this.Text = "Basic Step Time Report Generator";
			this.HelpRequested += new System.Windows.Forms.HelpEventHandler(this.Form1_HelpRequested);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label csvReportPathLabel;
		private System.Windows.Forms.TextBox csvPathTextBox;
		private System.Windows.Forms.TextBox basicStepTimeReportPathTextBox;
		private System.Windows.Forms.Label basicStepTimeReportPathLabel;
		private System.Windows.Forms.Button csvReportBrowseButton;
		private System.Windows.Forms.Button basicStepTimeReportBrowseButton;
		private System.Windows.Forms.Button helpButton;
		private System.Windows.Forms.Button okButton;
		private System.Windows.Forms.Button cancelButton;
		private System.Windows.Forms.CheckBox launchBasicStepTimeReportCheckBox;
	}
}

