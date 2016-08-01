using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;
using System.Windows.Forms;

namespace CheckStepNameLength
{
	internal partial class ConfigureCheckStepNameLengthDialog : Form
	{
		private int mMaximumStepNameLength;

		public ConfigureCheckStepNameLengthDialog(int maximumStepNameLength)
		{
			InitializeComponent();

			this.mMaxStepNameLengthUpDown.Maximum = decimal.MaxValue;

			// Initialize textbox to the current maximum length
			this.mMaxStepNameLengthUpDown.Value = maximumStepNameLength;
		}

		public int MaximumStepNameLength
		{
			get { return this.mMaximumStepNameLength; }
		}

		protected override void OnFormClosing(FormClosingEventArgs e)
		{
			base.OnFormClosing(e);

			if (this.DialogResult == DialogResult.OK)
			{
				// Get new maximum length
				this.mMaximumStepNameLength = (int) this.mMaxStepNameLengthUpDown.Value;
			}
		}
	}
}
