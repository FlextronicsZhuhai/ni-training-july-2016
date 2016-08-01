using System;
using System.Windows.Forms;
using NationalInstruments.TestStand.Interop.API;

namespace BasicStepTimeReportGenerator
{
	public partial class ConfigurationDialog : Form
	{
		/// <summary>
		/// Displays the configuration dialog
		/// </summary>
		/// <param name="reportOptions">PropertyObject having report options</param>
		/// <param name="engine">Instance of TS Engine</param>
		/// <returns>True if report options is modified</returns>
		public static bool DisplayConfigurationDialog(PropertyObject reportOptions, Engine engine)
		{
			bool returnValue = false;

			using (ConfigurationDialog dialog = new ConfigurationDialog(reportOptions, engine))
			{
				returnValue = dialog.RunDialog();
			}

			return returnValue;
		}

		private ConfigurationDialog(PropertyObject reportOptions, Engine engine)
		{
			mConfigurationModified = false;

			InitializeComponent();

			mEngine = engine;
			mReportOptions = reportOptions;

			LocalizeForm(engine);

			UpdateControlsFromConfig();

			if (!Utility.IsExcelInstalled())
				launchExcelFileCheckBox.Enabled = false;
		}

		/// <summary>
		/// Using TS mechanism to do localization, all the lables in the form will be localized
		/// </summary>
		/// <param name="engine">Instance of TS Engine</param>
		private void LocalizeForm(Engine engine)
		{
			string category = "BASIC_STEP_TIME_REPORT_GENERATOR_CONFIGURATION_DIALOG";

			this.Text = Utility.RString(engine, category, this.Text);
			this.cancelButton.Text = Utility.RString(engine, category, this.cancelButton.Text);
			this.okButton.Text = Utility.RString(engine, category, this.okButton.Text);
			this.helpButton.Text = Utility.RString(engine, category, this.helpButton.Text);
			this.launchExcelFileCheckBox.Text = Utility.RString(engine, category, this.launchExcelFileCheckBox.Text);
			this.fileFormatValue.Text = Utility.RString(engine, category, this.fileFormatValue.Text);
			this.fileFormatLabel.Text = Utility.RString(engine, category, this.fileFormatLabel.Text);
			this.directoryLabel.Text = Utility.RString(engine, category, this.directoryLabel.Text);
		}

		/// <summary>
		/// Updates the value of controls present in the Form as per values present in report options
		/// </summary>
		private void UpdateControlsFromConfig()
		{
			launchExcelFileCheckBox.Checked = mReportOptions.GetValBoolean("LaunchBasicStepTimeReport", 0);
			directoryTextBox.Text = mReportOptions.GetValString("Directory", 0);
		}

		/// <summary>
		/// Updates the report options based on the values of controls present in the Form
		/// </summary>
		private void UpdateConfigFromControls()
		{
			mReportOptions.SetValBoolean("LaunchBasicStepTimeReport", 0, launchExcelFileCheckBox.Checked);
			mReportOptions.SetValString("Directory", 0, directoryTextBox.Text);
		}

		/// <summary>
		/// Starts a modal dialog which displays all the report options.
		/// </summary>
		/// <returns>True if user has modified report options</returns>
		private bool RunDialog()
		{
			bool applyChanges = false;

			bool shouldAbort = false;

			int modalId = mEngine.NotifyStartOfModalDialogEx(null, out shouldAbort);
			if (!shouldAbort)
			{
				try
				{
					this.ShowDialog();
				}
				finally
				{
					mEngine.NotifyEndOfModalDialog(modalId);
				}
			}

			return applyChanges;
		}

		private readonly Engine mEngine;
		private readonly PropertyObject mReportOptions;
		private bool mConfigurationModified;

		private void directoryTextBox_TextChanged(object sender, EventArgs e)
		{
			mConfigurationModified = true;
		}

		private void launchExcelFileCheckBox_CheckedChanged(object sender, EventArgs e)
		{
			mConfigurationModified = true;
		}

		private void directoryBrowseButton_Click(object sender, EventArgs e)
		{
			string dlgTitle = "Select Directory to Store Reports";
			string okButtonText = "OK";

			string[] selectedPaths_UNUSED = null;
			string[] absolutePaths = null;
			int openFileDialogFlags = OpenFileDialogOptions.OpenFile_SelectDirectoriesOnly | OpenFileDialogOptions.OpenFile_UseAbsolutePath;
			object fileFilterIndex = System.Type.Missing;
			object dirHistoryList = System.Type.Missing;

			bool ok = mEngine.DisplayFileDialog(
				dlgTitle,
				okButtonText,
				directoryTextBox.Text, // initialPath
				out selectedPaths_UNUSED,
				out absolutePaths,
				openFileDialogFlags,
				"",                               // defaultExtension
				0,                                // win32Flags
				"",                               // fileFilter
				System.Type.Missing,              // currentFile
				ref fileFilterIndex,
				ref dirHistoryList);

			if (ok && absolutePaths.GetLength(0) == 1)
			{
				// Only update the path if the updated path is actually
				// different from the original one.
				if (absolutePaths[0] != this.directoryTextBox.Text)
					directoryTextBox.Text = absolutePaths[0];
			}
		}

		private void helpButton_Click(object sender, EventArgs e)
		{
			DisplayHelpDialog();
		}

		private void okButton_Click(object sender, EventArgs e)
		{
			if (mConfigurationModified)
				UpdateConfigFromControls();

			Close();
		}

		private void cancelButton_Click(object sender, EventArgs e)
		{
			mConfigurationModified = false;
			Close();
		}

		private void ConfigurationDialog_HelpRequested(object sender, HelpEventArgs hlpevent)
		{
			DisplayHelpDialog();
		}

		private void DisplayHelpDialog()
		{
			string helpDir = System.IO.Path.Combine(mEngine.GetTestStandPath(TestStandPaths.TestStandPath_TestStand), @"Doc\Help");
			string helpFile = System.IO.Path.Combine(helpDir, "TSRef.chm");

			// 9957 is help id for Configuration dialog of Basic Step Time Report Generator
			mEngine.DisplayHelpTopic(9957, helpFile, "", "", "", "");
		}
	}
}
