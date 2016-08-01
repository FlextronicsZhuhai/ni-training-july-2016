namespace SimpleTextReport
{
    partial class StandardOptionsDialog
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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(StandardOptionsDialog));
			this.mCtrl_directoryLabel = new System.Windows.Forms.Label();
			this.mCtrl_resultFileNameLabel = new System.Windows.Forms.Label();
			this.mCtrl_resultFileFormatLabel = new System.Windows.Forms.Label();
			this.mCtrl_otfCheckbox = new System.Windows.Forms.CheckBox();
			this.mCtrl_helpButton = new System.Windows.Forms.Button();
			this.mCtrl_okButton = new System.Windows.Forms.Button();
			this.mCtrl_cancelButton = new System.Windows.Forms.Button();
			this.mCtrl_browseButton = new System.Windows.Forms.Button();
			this.mCtrl_directoryTextBox = new System.Windows.Forms.TextBox();
			this.SuspendLayout();
			// 
			// mCtrl_directoryLabel
			// 
			this.mCtrl_directoryLabel.AutoSize = true;
			this.mCtrl_directoryLabel.Location = new System.Drawing.Point(12, 24);
			this.mCtrl_directoryLabel.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
			this.mCtrl_directoryLabel.Name = "mCtrl_directoryLabel";
			this.mCtrl_directoryLabel.Size = new System.Drawing.Size(119, 13);
			this.mCtrl_directoryLabel.TabIndex = 0;
			this.mCtrl_directoryLabel.Text = "RESULT_DIRECTORY";
			// 
			// mCtrl_resultFileNameLabel
			// 
			this.mCtrl_resultFileNameLabel.AutoSize = true;
			this.mCtrl_resultFileNameLabel.Location = new System.Drawing.Point(12, 55);
			this.mCtrl_resultFileNameLabel.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
			this.mCtrl_resultFileNameLabel.Name = "mCtrl_resultFileNameLabel";
			this.mCtrl_resultFileNameLabel.Size = new System.Drawing.Size(115, 13);
			this.mCtrl_resultFileNameLabel.TabIndex = 0;
			this.mCtrl_resultFileNameLabel.Text = "RESULT_FILE_NAME";
			// 
			// mCtrl_resultFileFormatLabel
			// 
			this.mCtrl_resultFileFormatLabel.AutoSize = true;
			this.mCtrl_resultFileFormatLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.mCtrl_resultFileFormatLabel.Location = new System.Drawing.Point(166, 55);
			this.mCtrl_resultFileFormatLabel.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
			this.mCtrl_resultFileFormatLabel.Name = "mCtrl_resultFileFormatLabel";
			this.mCtrl_resultFileFormatLabel.Size = new System.Drawing.Size(129, 13);
			this.mCtrl_resultFileFormatLabel.TabIndex = 0;
			this.mCtrl_resultFileFormatLabel.Text = "RESULT_FILE_FORMAT";
			// 
			// mCtrl_otfCheckbox
			// 
			this.mCtrl_otfCheckbox.AutoSize = true;
			this.mCtrl_otfCheckbox.Location = new System.Drawing.Point(15, 84);
			this.mCtrl_otfCheckbox.Margin = new System.Windows.Forms.Padding(2);
			this.mCtrl_otfCheckbox.Name = "mCtrl_otfCheckbox";
			this.mCtrl_otfCheckbox.Size = new System.Drawing.Size(165, 17);
			this.mCtrl_otfCheckbox.TabIndex = 3;
			this.mCtrl_otfCheckbox.Text = "ON_&THE_FLY_REPORTING";
			this.mCtrl_otfCheckbox.UseVisualStyleBackColor = true;
			this.mCtrl_otfCheckbox.CheckedChanged += new System.EventHandler(this.mCtrl_otfCheckbox_CheckedChanged);
			// 
			// mCtrl_helpButton
			// 
			this.mCtrl_helpButton.Location = new System.Drawing.Point(15, 125);
			this.mCtrl_helpButton.Margin = new System.Windows.Forms.Padding(2);
			this.mCtrl_helpButton.Name = "mCtrl_helpButton";
			this.mCtrl_helpButton.Size = new System.Drawing.Size(75, 26);
			this.mCtrl_helpButton.TabIndex = 4;
			this.mCtrl_helpButton.Text = "&HELP";
			this.mCtrl_helpButton.UseVisualStyleBackColor = true;
			this.mCtrl_helpButton.Click += new System.EventHandler(this.mCtrl_helpButton_Click);
			// 
			// mCtrl_okButton
			// 
			this.mCtrl_okButton.Location = new System.Drawing.Point(632, 125);
			this.mCtrl_okButton.Margin = new System.Windows.Forms.Padding(2);
			this.mCtrl_okButton.Name = "mCtrl_okButton";
			this.mCtrl_okButton.Size = new System.Drawing.Size(75, 26);
			this.mCtrl_okButton.TabIndex = 5;
			this.mCtrl_okButton.Text = "&oK";
			this.mCtrl_okButton.UseVisualStyleBackColor = true;
			this.mCtrl_okButton.Click += new System.EventHandler(this.mCtrl_okButton_Click);
			// 
			// mCtrl_cancelButton
			// 
			this.mCtrl_cancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.mCtrl_cancelButton.Location = new System.Drawing.Point(713, 125);
			this.mCtrl_cancelButton.Margin = new System.Windows.Forms.Padding(2);
			this.mCtrl_cancelButton.Name = "mCtrl_cancelButton";
			this.mCtrl_cancelButton.Size = new System.Drawing.Size(75, 26);
			this.mCtrl_cancelButton.TabIndex = 6;
			this.mCtrl_cancelButton.Text = "&CANCEL";
			this.mCtrl_cancelButton.UseVisualStyleBackColor = true;
			this.mCtrl_cancelButton.Click += new System.EventHandler(this.mCtrl_cancelButton_Click);
			// 
			// mCtrl_browseButton
			// 
			this.mCtrl_browseButton.Location = new System.Drawing.Point(758, 19);
			this.mCtrl_browseButton.Margin = new System.Windows.Forms.Padding(2);
			this.mCtrl_browseButton.Name = "mCtrl_browseButton";
			this.mCtrl_browseButton.Size = new System.Drawing.Size(30, 27);
			this.mCtrl_browseButton.TabIndex = 2;
			this.mCtrl_browseButton.Text = "...";
			this.mCtrl_browseButton.UseVisualStyleBackColor = true;
			this.mCtrl_browseButton.Click += new System.EventHandler(this.mCtrl_browseButton_Click);
			// 
			// mCtrl_directoryTextBox
			// 
			this.mCtrl_directoryTextBox.Location = new System.Drawing.Point(169, 21);
			this.mCtrl_directoryTextBox.Margin = new System.Windows.Forms.Padding(2);
			this.mCtrl_directoryTextBox.Name = "mCtrl_directoryTextBox";
			this.mCtrl_directoryTextBox.Size = new System.Drawing.Size(574, 20);
			this.mCtrl_directoryTextBox.TabIndex = 1;
			this.mCtrl_directoryTextBox.TextChanged += new System.EventHandler(this.mCtrl_directoryTextBox_TextChanged);
			// 
			// StandardOptionsDialog
			// 
			this.AcceptButton = this.mCtrl_okButton;
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
			this.CancelButton = this.mCtrl_cancelButton;
			this.ClientSize = new System.Drawing.Size(800, 167);
			this.Controls.Add(this.mCtrl_directoryTextBox);
			this.Controls.Add(this.mCtrl_browseButton);
			this.Controls.Add(this.mCtrl_cancelButton);
			this.Controls.Add(this.mCtrl_okButton);
			this.Controls.Add(this.mCtrl_helpButton);
			this.Controls.Add(this.mCtrl_otfCheckbox);
			this.Controls.Add(this.mCtrl_resultFileFormatLabel);
			this.Controls.Add(this.mCtrl_resultFileNameLabel);
			this.Controls.Add(this.mCtrl_directoryLabel);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.Margin = new System.Windows.Forms.Padding(2);
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "StandardOptionsDialog";
			this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "SIMPLE_TEXT_REPORT_OPTIONS";
			this.ResumeLayout(false);
			this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label mCtrl_directoryLabel;
        private System.Windows.Forms.Label mCtrl_resultFileNameLabel;
        private System.Windows.Forms.Label mCtrl_resultFileFormatLabel;
        private System.Windows.Forms.CheckBox mCtrl_otfCheckbox;
        private System.Windows.Forms.Button mCtrl_helpButton;
        private System.Windows.Forms.Button mCtrl_okButton;
        private System.Windows.Forms.Button mCtrl_cancelButton;
        private System.Windows.Forms.Button mCtrl_browseButton;
        private System.Windows.Forms.TextBox mCtrl_directoryTextBox;
    }
}