using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using Microsoft.Win32;

namespace CsvToBasicStepTimeReportGenerator
{
	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();
		}

		private void csvReportBrowseButton_Click(object sender, EventArgs e)
		{
			using (OpenFileDialog openFileDialog = new OpenFileDialog())
			{
				openFileDialog.Filter = "csv file (*.csv)|*.csv";
				openFileDialog.Multiselect = false;
				openFileDialog.CheckFileExists = true;
				openFileDialog.InitialDirectory = csvPathTextBox.Text;
				openFileDialog.Title = "Select CSV File";
				openFileDialog.RestoreDirectory = true;

				if (openFileDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
					csvPathTextBox.Text = openFileDialog.FileName;
			}
		}

		private void basicStepTimeReportBrowseButton_Click(object sender, EventArgs e)
		{
			using (SaveFileDialog saveFileDialog = new SaveFileDialog())
			{
				saveFileDialog.Filter = "Basic Step Time Report (*.xls)|*.xls";
				saveFileDialog.InitialDirectory = basicStepTimeReportPathTextBox.Text;
				saveFileDialog.Title = "Path to Save Basic Step Time Report";
				saveFileDialog.RestoreDirectory = true;

				if (saveFileDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
					basicStepTimeReportPathTextBox.Text = saveFileDialog.FileName;
			}
		}

		private void cancelButton_Click(object sender, EventArgs e)
		{
			Close();
		}

		[System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Globalization", "CA1300")]
		private void okButton_Click(object sender, EventArgs e)
		{
			try
			{
				BasicStepTimeReportGenerator.CreateBasicStepTimeReport(csvPathTextBox.Text, basicStepTimeReportPathTextBox.Text, launchBasicStepTimeReportCheckBox.Checked);
				Close();
			}
			catch (Exception exception)
			{
				MessageBox.Show("Unable to create Basic Step Time Report for the following reason:\n" + exception.Message);
			}			
		}

		private const string mHelpFileName = "Basic_Step_Time_Report.htm";

		private void helpButton_Click(object sender, EventArgs e)
		{
			DisplayHelp();
		}

		private void Form1_HelpRequested(object sender, HelpEventArgs hlpevent)
		{
			DisplayHelp();
		}

		private void DisplayHelp()
		{
			string helpContentDir = System.IO.Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location);
			string helpFile = System.IO.Path.Combine(helpContentDir, mHelpFileName);

			if (!System.IO.File.Exists(helpFile))
			{
				string caption = "Error";
				MessageBox.Show("Unable to find the help.", caption);
			}
			else
				System.Diagnostics.Process.Start(helpFile);
		}
	}
}
