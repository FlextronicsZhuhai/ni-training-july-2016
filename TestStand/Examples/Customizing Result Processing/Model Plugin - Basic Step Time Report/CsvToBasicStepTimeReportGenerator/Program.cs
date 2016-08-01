using System;
using System.Windows.Forms;

namespace CsvToBasicStepTimeReportGenerator
{
	static class Program
	{
		/// <summary>
		/// The main entry point for the application
		/// </summary>
		/// <param name="args">Command line arguments should be passed if the executable should not display UI</param>
		/// <returns>1 if there is any error. 0 if Success.</returns>
		[STAThread]
		[System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Globalization", "CA1300")]
		static int Main(string[] args)
		{
			int returnVal = 0;

			string errorMessage = null;

			if (args.Length == 0)
			{

				if (BasicStepTimeReportGenerator.CanCreateBasicStepTimeReport(ref errorMessage))
				{
					if (args.Length == 0)
					{
						Application.EnableVisualStyles();
						Application.SetCompatibleTextRenderingDefault(false);
						Application.Run(new Form1());
					}
				}
				else
				{
					// Unable to create Basic Step Time Report.

					string caption = "Error";
					MessageBox.Show(errorMessage, caption);
					returnVal = 1;
				}
			}
			else
			{
				if (!AttachConsole(ATTACH_PARENT_PROCESS))
					AllocConsole();
				returnVal = ConsoleMain(args);
				FreeConsole();
			}

			if (ExcelCreationSuccessful == false)
				returnVal = 1;

			// Call dispose if Excel is installed.
			if (BasicStepTimeReportGenerator.IsExcelInstalled())
				BasicStepTimeReportGenerator.ExcelApplication.Instance.Dispose();

			return returnVal;
		}

		[System.Runtime.InteropServices.DllImport("kernel32")]
		private static extern bool AllocConsole(); // P/INVOKE REVIEWED 2013-05-21 TestStand 14.0

		[System.Runtime.InteropServices.DllImport("kernel32")]
		private static extern bool AttachConsole(uint dwProcessId); // P/INVOKE REVIEWED 2013-05-21 TestStand 14.0

		// See msdn documentation for AttachConsole().
		private const uint ATTACH_PARENT_PROCESS = unchecked((uint)-1);

		[System.Runtime.InteropServices.DllImport("kernel32")]
		private static extern bool FreeConsole(); // P/INVOKE REVIEWED 2013-05-21 TestStand 14.0

		private static int ConsoleMain(string[] args)
		{
			int returnVal = 0;
			string errorMessage = null;

			if (BasicStepTimeReportGenerator.CanCreateBasicStepTimeReport(ref errorMessage))
			{
				if (!ArgsIsValid(args))
				{
					Console.Error.WriteLine("Usage: Exe <CsvFilePath> <ReportFilePath> [/display]");
				}
				else
				{
					string csvReportPath = "";
					string basicStepTimeReportPath = "";

					// Get the csvReportPath and basicStepTimeReportPath given in command line arguments
					foreach (string arg in args)
					{
						if (arg.ToLower(System.Globalization.CultureInfo.CurrentCulture) != "/display")
						{
							if (string.IsNullOrEmpty(csvReportPath))
								csvReportPath = arg;
							else
								basicStepTimeReportPath = arg;
						}
					}

					System.Threading.Thread thread = new System.Threading.Thread(delegate()
						{
					CreateBasicStepTimeReport(csvReportPath, basicStepTimeReportPath, args.Length == 3);
						});

					thread.Start();

					// This will start pumping UI messages into the main thread, so that, the main thread is not blocked.
					Application.Run();
				}
			}
			else
			{
				// Unable to create Basic Step Time Report.

				Console.Error.WriteLine(errorMessage);
				returnVal = 1;
			}

			return returnVal;
		}

		/// <summary>
		/// Entry point for thread when using command line arguments to create basic step time report.
		/// </summary>
		/// <param name="csvReportPath">Path of CSV report</param>
		/// <param name="basicStepTimeReportPath">Path where basic step time report needs to be saved</param>
		/// <param name="displayReport">Pass true to display basic step time report after its creation</param>
		static private void CreateBasicStepTimeReport(string csvReportPath, string basicStepTimeReportPath, bool displayReport)
		{
			try
			{
				BasicStepTimeReportGenerator.CreateBasicStepTimeReport(csvReportPath, basicStepTimeReportPath, displayReport);
			}
			catch (Exception e)
			{
				string errorMsg = "Unable to create a basic step time report in Microsoft Excel format for the following reason:\n" + e.Message;
				Console.Error.WriteLine(errorMsg);

				ExcelCreationSuccessful = false;
			}

			// This will stop pumping UI messages and ends the Application.Start method used during creating basic step time report
			// when command line arguments are given.
			Application.Exit();
		}

		/// <summary>
		/// If command line arguments is given to the exe, this will validate the given arguments.
		/// This will check for number of arguments and number of occurrence of /display flag if number of arguments is 3.
		/// </summary>
		/// <param name="args">Command line arguments passed to the exe</param>
		/// <returns>true if command line arguments are valid, else false</returns>
		static private bool ArgsIsValid(string[] args)
		{
			System.Diagnostics.Debug.Assert(args.Length != 0);

			bool isValid = true;

			if (args.Length == 2 || args.Length == 3)
			{
				int noOfTimesDisplayIsPresent = 0;

				foreach (string arg in args)
				{
					if (arg.ToLower(System.Globalization.CultureInfo.CurrentCulture) == "/display")
						++noOfTimesDisplayIsPresent;
				}

				if ((args.Length == 3 && noOfTimesDisplayIsPresent != 1) || (args.Length == 2 && noOfTimesDisplayIsPresent != 0))
					isValid = false;
			}
			else
				isValid = false;

			return isValid;
		}

		static internal bool ExcelCreationSuccessful = true;
	}
}
