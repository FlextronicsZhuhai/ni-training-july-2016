namespace NationalInstruments.TestStand.Examples.MobileDeviceDemo
{
    partial class SimulationDialog
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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(SimulationDialog));
			this.OKButton = new System.Windows.Forms.Button();
			this.Power = new System.Windows.Forms.CheckBox();
			this.LCD = new System.Windows.Forms.ComboBox();
			this.Battery = new System.Windows.Forms.CheckBox();
			this.Antenna = new System.Windows.Forms.CheckBox();
			this.Microphone = new System.Windows.Forms.CheckBox();
			this.Speakers = new System.Windows.Forms.CheckBox();
			this.Buttons = new System.Windows.Forms.CheckBox();
			this.label1 = new System.Windows.Forms.Label();
			this.controlBox = new System.Windows.Forms.GroupBox();
			this.pictureBox2 = new System.Windows.Forms.PictureBox();
			this.pictureBox1 = new System.Windows.Forms.PictureBox();
			this.cancelDialogTimer = new System.Windows.Forms.Timer(this.components);
			this.controlBox.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
			this.SuspendLayout();
			// 
			// OKButton
			// 
			this.OKButton.Location = new System.Drawing.Point(423, 398);
			this.OKButton.Name = "OKButton";
			this.OKButton.Size = new System.Drawing.Size(125, 23);
			this.OKButton.TabIndex = 0;
			this.OKButton.Text = "OK";
			this.OKButton.UseVisualStyleBackColor = true;
			this.OKButton.Click += new System.EventHandler(this.OKButton_Click);
			// 
			// Power
			// 
			this.Power.AutoSize = true;
			this.Power.Location = new System.Drawing.Point(40, 24);
			this.Power.Name = "Power";
			this.Power.Size = new System.Drawing.Size(56, 17);
			this.Power.TabIndex = 1;
			this.Power.Text = "Power";
			this.Power.UseVisualStyleBackColor = true;
			// 
			// LCD
			// 
			this.LCD.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.LCD.FormattingEnabled = true;
			this.LCD.Items.AddRange(new object[] {
            "No Issues",
            "Dead Pixels",
            "Incorrect Brightness"});
			this.LCD.Location = new System.Drawing.Point(40, 203);
			this.LCD.Name = "LCD";
			this.LCD.Size = new System.Drawing.Size(116, 21);
			this.LCD.TabIndex = 2;
			// 
			// Battery
			// 
			this.Battery.AutoSize = true;
			this.Battery.Location = new System.Drawing.Point(40, 53);
			this.Battery.Name = "Battery";
			this.Battery.Size = new System.Drawing.Size(59, 17);
			this.Battery.TabIndex = 4;
			this.Battery.Text = "Battery";
			this.Battery.UseVisualStyleBackColor = true;
			// 
			// Antenna
			// 
			this.Antenna.AutoSize = true;
			this.Antenna.Location = new System.Drawing.Point(40, 81);
			this.Antenna.Name = "Antenna";
			this.Antenna.Size = new System.Drawing.Size(66, 17);
			this.Antenna.TabIndex = 5;
			this.Antenna.Text = "Antenna";
			this.Antenna.UseVisualStyleBackColor = true;
			// 
			// Microphone
			// 
			this.Microphone.AutoSize = true;
			this.Microphone.Location = new System.Drawing.Point(40, 110);
			this.Microphone.Name = "Microphone";
			this.Microphone.Size = new System.Drawing.Size(82, 17);
			this.Microphone.TabIndex = 6;
			this.Microphone.Text = "Microphone";
			this.Microphone.UseVisualStyleBackColor = true;
			// 
			// Speakers
			// 
			this.Speakers.AutoSize = true;
			this.Speakers.Location = new System.Drawing.Point(40, 138);
			this.Speakers.Name = "Speakers";
			this.Speakers.Size = new System.Drawing.Size(71, 17);
			this.Speakers.TabIndex = 7;
			this.Speakers.Text = "Speakers";
			this.Speakers.UseVisualStyleBackColor = true;
			// 
			// Buttons
			// 
			this.Buttons.AutoSize = true;
			this.Buttons.Location = new System.Drawing.Point(40, 167);
			this.Buttons.Name = "Buttons";
			this.Buttons.Size = new System.Drawing.Size(62, 17);
			this.Buttons.TabIndex = 8;
			this.Buttons.Text = "Buttons";
			this.Buttons.UseVisualStyleBackColor = true;
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.BackColor = System.Drawing.Color.Transparent;
			this.label1.Location = new System.Drawing.Point(39, 189);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(28, 13);
			this.label1.TabIndex = 9;
			this.label1.Text = "LCD";
			// 
			// controlBox
			// 
			this.controlBox.BackColor = System.Drawing.SystemColors.Window;
			this.controlBox.Controls.Add(this.pictureBox2);
			this.controlBox.Controls.Add(this.pictureBox1);
			this.controlBox.Controls.Add(this.Buttons);
			this.controlBox.Controls.Add(this.Speakers);
			this.controlBox.Controls.Add(this.Microphone);
			this.controlBox.Controls.Add(this.Antenna);
			this.controlBox.Controls.Add(this.Battery);
			this.controlBox.Controls.Add(this.LCD);
			this.controlBox.Controls.Add(this.Power);
			this.controlBox.Controls.Add(this.label1);
			this.controlBox.Location = new System.Drawing.Point(12, 10);
			this.controlBox.Name = "controlBox";
			this.controlBox.Size = new System.Drawing.Size(535, 382);
			this.controlBox.TabIndex = 10;
			this.controlBox.TabStop = false;
			this.controlBox.Text = "Select Components to Fail";
			// 
			// pictureBox2
			// 
			this.pictureBox2.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox2.Image")));
			this.pictureBox2.Location = new System.Drawing.Point(5, 15);
			this.pictureBox2.Name = "pictureBox2";
			this.pictureBox2.Size = new System.Drawing.Size(29, 212);
			this.pictureBox2.TabIndex = 12;
			this.pictureBox2.TabStop = false;
			// 
			// pictureBox1
			// 
			this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
			this.pictureBox1.Location = new System.Drawing.Point(194, 15);
			this.pictureBox1.Name = "pictureBox1";
			this.pictureBox1.Size = new System.Drawing.Size(331, 357);
			this.pictureBox1.TabIndex = 11;
			this.pictureBox1.TabStop = false;
			// 
			// cancelDialogTimer
			// 
			this.cancelDialogTimer.Tick += new System.EventHandler(this.cancelDialogTimer_Tick);
			// 
			// SimulationDialog
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.BackColor = System.Drawing.SystemColors.Window;
			this.ClientSize = new System.Drawing.Size(558, 429);
			this.Controls.Add(this.controlBox);
			this.Controls.Add(this.OKButton);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "SimulationDialog";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Simulation Dialog";
			this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.SimulationDialog_FormClosed);
			this.Shown += new System.EventHandler(this.SimulationDialog_Shown);
			this.controlBox.ResumeLayout(false);
			this.controlBox.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
			this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button OKButton;
        private System.Windows.Forms.CheckBox Power;
        private System.Windows.Forms.ComboBox LCD;
        private System.Windows.Forms.CheckBox Battery;
        private System.Windows.Forms.CheckBox Antenna;
        private System.Windows.Forms.CheckBox Microphone;
        private System.Windows.Forms.CheckBox Speakers;
        private System.Windows.Forms.CheckBox Buttons;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox controlBox;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Timer cancelDialogTimer;
		private System.Windows.Forms.PictureBox pictureBox2;
    }
}

