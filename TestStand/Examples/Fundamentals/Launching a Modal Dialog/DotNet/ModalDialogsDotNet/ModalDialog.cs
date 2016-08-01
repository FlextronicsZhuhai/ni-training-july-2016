using System;
using System.Windows.Forms;

namespace ModalDialogsDotNet
{
	public partial class ModalDialog : Form
	{

		public ModalDialog()
		{
			InitializeComponent();
		}

		private void okButton_Click(object sender, EventArgs e)
		{
			this.Close();
		}

	}
}
