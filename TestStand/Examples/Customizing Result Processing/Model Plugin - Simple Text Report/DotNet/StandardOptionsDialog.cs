using System;
using System.Diagnostics;
using System.Globalization;
using System.Windows.Forms;

using NationalInstruments.TestStand.Interop.API;
using NationalInstruments.TestStand.Utility;

using System.Diagnostics.CodeAnalysis;

namespace SimpleTextReport
{
    /// <summary>StandardOptionsDialog is the dialog box spawned when the
    /// user presses the options button in the Report Options dialog
    /// box.</summary>
    public partial class StandardOptionsDialog : Form
    {
        /// <summary>NI_SimpleTextReport_DotNet.seq calls Display() from
        /// the "Model Plugin - Configure Standard Options" callback to
        /// create and display an instance of the Options dialog
        /// box.</summary>
        /// <param name="simpleTextReportPlugin">A PropertyObject of
		/// type NI_ModelPlugin.  It must have the appropriate specialization
        /// for the Simple Text Report plug-in.</param>
        /// <param name="engine">A TestStand Engine instance.  The calling
        /// sequence should pass RunState.Engine.</param>
        /// <returns>true if changes were made and should be applied, false
		/// otherwise.</returns>
        [SuppressMessage("Microsoft.Naming", "CA1704:IdentifiersShouldBeSpelledCorrectly", MessageId = "Plugin")]
        public static bool Display(PropertyObject simpleTextReportPlugin, Engine engine)
		{
            StandardOptionsDialog dialog = new StandardOptionsDialog(simpleTextReportPlugin, engine);            

			return dialog.RunDialog();
		}

		/// <summary>Constructor.</summary>
        /// <seealso cref="SimpleTextReport.StandardOptionsDialog.Display(PropertyObject,Engine)">Display()</seealso>
        /// <param name="simpleTextReportPlugin">A PropertyObject of
        /// type NI_ModelPlugin.  It must have the appropriate specialization
        /// for the Simple Text Report plug-in.</param>
        /// <param name="engine">A TestStand Engine instance.</param>
        private StandardOptionsDialog(PropertyObject simpleTextReportPlugin, Engine engine)
		{
            InitializeComponent(); // Standard Windows Form call.

            mConfig = simpleTextReportPlugin;
            mEngine = engine;

            updateCtrlFromConfig();            

            // TestStand-specific localization approach.
            Localizer localizer = new Localizer(mEngine);
            localizer.LocalizeForm(this, Utils.LOCALIZED_STRING_SECTION, false);
		}

		/// <summary>Update all widget data from mConfig.  This is a helper
        /// method for the constructor.</summary>
        /// <seealso cref="SimpleTextReport.StandardOptionsDialog.updateConfigFromCtrl()">updateConfigFromCtrl()</seealso>
        private void updateCtrlFromConfig()
		{
            mCtrl_directoryTextBox.Text = mConfig.GetValString(P_PluginSpecific_Options_ResultDirectory, PropertyOptions.PropOption_NoOptions);
            mCtrl_otfCheckbox.Checked = mConfig.GetValBoolean(P_Base_ProcessOnTheFly, PropertyOptions.PropOption_NoOptions);

            // Setting these values will trigger the changed events, so
            // clear the changed flag.
            mChanged = false;
		}

		/// <summary>Update mConfig based on the state of the Form.
        /// Currently, this method is called only from the OK
        /// button handler.  If you add an "Apply" button, you would
        /// call it from that handler as well.</summary>
        /// <seealso cref="SimpleTextReport.StandardOptionsDialog.updateCtrlFromConfig()">updateCtrlFromConfig()</seealso>
        private void updateConfigFromCtrl()
		{
            mConfig.SetValString(P_PluginSpecific_Options_ResultDirectory, PropertyOptions.PropOption_NoOptions, mCtrl_directoryTextBox.Text);
            mConfig.SetValBoolean(P_Base_ProcessOnTheFly, PropertyOptions.PropOption_NoOptions, mCtrl_otfCheckbox.Checked);
		}

		/// <summary>Execute the Simple Text Report Options dialog.  The
		/// dialog is modal.
        /// <see cref="SimpleTextReport.StandardOptionsDialog.Display(PropertyObject,Engine)">Display()</see>
        /// invokes this method.</summary>
		/// <returns>true if changes were made and should be applied; false
		/// otherwise.</returns>
		private bool RunDialog()
		{
            bool shouldAbort = false;

            int modalId = mEngine.NotifyStartOfModalDialogEx(null, out shouldAbort);

			try
			{
				if (shouldAbort)
				{
					return false;
				}

				this.ShowDialog();
			}
			finally
			{
				mEngine.NotifyEndOfModalDialog(modalId);
			}

			return mApplyChanges;
		}

		#region UI Event Handlers

        /// <param name="sender">ignored</param>
        /// <param name="e">ignored</param>
        private void mCtrl_directoryTextBox_TextChanged(object sender, EventArgs e)
		{
            // Set the mChanged flag to indicate something has changed.
            // Update mConfig only if and when the user presses the OK button.
            mChanged = true;
		}

        /// <param name="sender">ignored</param>
        /// <param name="e">ignored</param>
        private void mCtrl_otfCheckbox_CheckedChanged(object sender, EventArgs e)
        {
            // Set the mChanged flag to indicate something has changed.
            // Update mConfig only if and when the user presses the OK button.
            mChanged = true;
        }

        /// <summary>Apply changes and close the dialog.</summary>
        /// <param name="sender">ignored</param>
        /// <param name="e">ignored</param>
        private void mCtrl_okButton_Click(object sender, EventArgs e)
		{
			// If changes have been made, update mConfig and set the
            // mApplyChanges flag so that RunDialog() can inform its
            // caller that changes were made.
            if( mChanged )
			{
                updateConfigFromCtrl();
                mApplyChanges = true;
			}

			this.Close();
		}

        /// <summary>Quit the dialog without applying changes.</summary>
        /// <param name="sender">ignored</param>
        /// <param name="e">ignored</param>
        private void mCtrl_cancelButton_Click(object sender, EventArgs e)
		{
			this.Close();
		}

        private const int SimpleTextReportDlgHelpId = 8186;

        /// <summary>Display help for this dialog.</summary>
        /// <param name="sender">ignored</param>
        /// <param name="e">ignored</param>
        private void mCtrl_helpButton_Click(object sender, EventArgs e)
		{
            string helpDir = System.IO.Path.Combine(mEngine.GetTestStandPath(TestStandPaths.TestStandPath_TestStand), @"Doc\Help");
            string helpFile = System.IO.Path.Combine(helpDir, "TSSuppRef.chm");

            // Since this example is a part of TestStand, the help for this
            // dialog is contained in the TestStand help file and displayed
            // via the engine.

            mEngine.DisplayHelpTopic(SimpleTextReportDlgHelpId, helpFile, "", "", "", "");

            // If you would like your plug-in to display help, you will need
            // to create a help file and display it.  One simple way to do
            // this is with the .Net Help class as shown below:
            //
            //  Help.ShowHelp(this, @"C:\Your_Directory\Your_Help.chm");
		}

        /// <summary>Display the File Browse dialog allowing the user to
        /// browse to the desired directory.</summary>
        /// <param name="sender">ignored</param>
        /// <param name="e">ignored</param>
        private void mCtrl_browseButton_Click(object sender, EventArgs e)
		{
            // TestStand-specific localization approach.
            string dlgTitle     = Utils.RString(mEngine, Utils.LOCALIZED_STRING_SECTION, Utils.LOCAL_SELECT_DIRECTORY);
            string okButtonText = Utils.RString(mEngine, Utils.COMMON_DLG_SECTION, Utils.COMMON_DLG_OK);

            string[] selectedPaths_UNUSED = null;
            string[] absolutePaths = null;
            int openFileDialogFlags = OpenFileDialogOptions.OpenFile_SelectDirectoriesOnly | OpenFileDialogOptions.OpenFile_UseAbsolutePath;
            object fileFilterIndex = System.Type.Missing;
            object dirHistoryList  = System.Type.Missing;

            bool ok = mEngine.DisplayFileDialog(
				dlgTitle,
				okButtonText,
				this.mCtrl_directoryTextBox.Text, // initialPath
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
                if (absolutePaths[0] != this.mCtrl_directoryTextBox.Text)
                {
                    mCtrl_directoryTextBox.Text = absolutePaths[0];
                }
            }
		}

		#endregion

        /// <summary>mConfig is a reference to the PropertyObject representing
        /// the model plug-in's configuration.  After using it to initialize
        /// the user interface, it is not used again until/unless the user
        /// presses the OK button, which stores the updated settings back
        /// to mConfig.
        /// </summary>
		private readonly PropertyObject mConfig;

        /// <summary>An instance of the Engine.</summary>
        private readonly Engine mEngine;
		
		/// <summary>Indicates if the dialog box has been changed.  This does
        /// not mean the user has pressed the OK button.  It just means that
        /// if the user does press OK button, there have been changes which
        /// need to be stored back to the plug-in.</summary>
        private bool mChanged = false;
		
        /// <summary>Indicates that changes were made and the OK button
        /// has been pressed.</summary>
        /// <seealso cref="SimpleTextReport.StandardOptionsDialog.RunDialog()">RunDialog()</seealso>
        private bool mApplyChanges = false;

		// This section contains specific members of the ProperyObject,
        // mConfig, used by the dialog.  These paths are relative to
        // NI_ModelPlugin.
        #region PropertyObject Paths

        private const string P_PluginSpecific_Options = "PluginSpecific.Options";
        private const string P_PluginSpecific_Options_ResultDirectory = P_PluginSpecific_Options + ".ResultDirectory";
        private const string P_Base_ProcessOnTheFly = "Base.ProcessOnTheFly";
		
		#endregion
    }
}