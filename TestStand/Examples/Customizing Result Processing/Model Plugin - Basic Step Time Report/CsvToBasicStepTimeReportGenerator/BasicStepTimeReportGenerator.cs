using System;
using Microsoft.Office.Interop.Excel;
using Microsoft.Win32;
using System.Diagnostics;
using System.IO;
using System.Runtime.InteropServices;

namespace CsvToBasicStepTimeReportGenerator
{
	class BasicStepTimeReportGenerator
	{
		/// <summary>
		/// Verifies the path of csv file and basic step time report are valid. This function will not handle exceptions when 
		/// the given file paths are not valid.
		/// If the given paths are valid, then it uses internal function to create basic step time report.
		/// </summary>
		/// <param name="csvReportPath">Path of CSV report</param>
		/// <param name="basicStepTimeReportPath">Path where basic step time report needs to be created</param>
		/// <param name="displayReport">True if the created basic step time report needs to be displayed</param>
		internal static void CreateBasicStepTimeReport(string csvReportPath, string basicStepTimeReportPath, bool displayReport)
		{
			IsPathValid(csvReportPath, true, true);
			IsPathValid(basicStepTimeReportPath, false, true);

			CreateBasicStepTimeReport_Internal(System.IO.Path.GetFullPath(csvReportPath),
				System.IO.Path.GetFullPath(basicStepTimeReportPath), displayReport);
		}

		/// <summary>
		/// Using Microsoft Office Excel Interop APIs, creates a new excel file (containing raw data) from the CSV file and 
		/// calls macro to create processed results
		/// </summary>
		/// <param name="csvReportPath">Path of CSV report</param>
		/// <param name="basicStepTimeReportPath">Path where basic step time report needs to be created</param>
		/// <param name="displayReport">True if the created basic step time report needs to be displayed</param>
		private static void CreateBasicStepTimeReport_Internal(string csvReportPath, string basicStepTimeReportPath, bool displayReport)
		{
			Application app = ExcelApplication.Instance.App;
			Workbooks books = null;
			Workbook csvBook = null;
			Workbook basicStepTimeReportBook = null;
			string uniqueFilePath = null;

			object missingType = System.Reflection.Missing.Value;

			try
			{
				// Initially make the visibility as false. Otherwise, the display will flicker when creating processed data.
				app.Visible = false;

				// DisplayAlerts will be set to false in order to not display warning message when deleting the worksheet / creating new workbook
				app.DisplayAlerts = false;

				// Copy the template excel file to the basic step time report path
				string currentExecutingAssemblyPath = System.Reflection.Assembly.GetExecutingAssembly().Location;
				string currentExecutingAssemblyDir = System.IO.Path.GetDirectoryName(currentExecutingAssemblyPath);

				System.IO.File.Copy(currentExecutingAssemblyDir + System.IO.Path.DirectorySeparatorChar + mBasicStepTimeReportFileName, basicStepTimeReportPath, true);

				books = app.Workbooks;

				// Convert the csv file into an xls file and save it in a temporary file
				// 2 represents a csv file
				csvBook = books.Open(csvReportPath, missingType, false, 2, missingType, missingType, missingType, missingType, missingType, missingType, missingType, missingType, missingType, missingType, missingType);

				XlCalculation oldCalculation = app.Calculation;
				app.Calculation = XlCalculation.xlCalculationManual;

				Worksheet csvWorkSheet = csvBook.Worksheets[1] as Worksheet;

				if (ValidateCsvFile(csvWorkSheet) == false)
					throw new ArgumentException("The specified CSV file is invalid. Use the CSV file the Basic Step Time Report Generator created.");

				// Copy the raw data from the csv file to the basic step time report and delete the temporary file
				basicStepTimeReportBook = books.Open(basicStepTimeReportPath, missingType, false, missingType, missingType, missingType, missingType, missingType, missingType, missingType, missingType, missingType, missingType, missingType, missingType);
				Worksheet rawDataWorksheet = basicStepTimeReportBook.Worksheets[1] as Worksheet;

				Range csvWorkSheetUsedRange = csvWorkSheet.UsedRange;
				Range firstCellInRawData = rawDataWorksheet.Cells[1, 1] as Range;
				firstCellInRawData.get_Resize(csvWorkSheetUsedRange.Rows.Count, csvWorkSheetUsedRange.Columns.Count).Value2 = csvWorkSheetUsedRange.Value2;

				rawDataWorksheet.Name = "Raw Data";

				csvBook.Close(false, missingType, missingType);
				csvBook = null;

				// Create a button in the raw data sheet and assign the macro which will re-create the processed result to the button
				((_Worksheet)rawDataWorksheet).Activate();

				// Create a button and assign the macro for OnAction event.
				Range cell1ToInsertButton = rawDataWorksheet.Cells[2, 4] as Range;
				Range cell2ToInsertButton = rawDataWorksheet.Cells[3, 4] as Range;
				Shape button = rawDataWorksheet.Shapes.AddFormControl(XlFormControl.xlButtonControl,
					(int)(double)cell1ToInsertButton.Left, (int)(double)cell1ToInsertButton.Top, (int)(double)cell1ToInsertButton.Width, (int)((double)cell1ToInsertButton.Height + (double)cell2ToInsertButton.Height));

				button.TextFrame.Characters(missingType, missingType).Text = "Regenerate Processed Data and Graphs";
				button.OnAction = "CreateProcessedData";

				rawDataWorksheet.Cells.EntireColumn.AutoFit();

				rawDataWorksheet.Protect(missingType, missingType, missingType, missingType, missingType, missingType,
					missingType, missingType, missingType, missingType, missingType, missingType, missingType, missingType,
					missingType, missingType);

				// Execute the macro to create the processed result
				app.GetType().InvokeMember("Run",
					System.Reflection.BindingFlags.Default |
					System.Reflection.BindingFlags.InvokeMethod,
					null, app, new Object[] { "CreateProcessedData" }, System.Globalization.CultureInfo.CurrentCulture);

				// Display the basic step time report if required
				app.Visible = displayReport;
				app.Calculation = oldCalculation;
				app.DisplayAlerts = true;

				basicStepTimeReportBook.Save();

				// If the report is displayed, the application will be closed by clicking the close button.
				// Otherwise close the application
				if (!displayReport)
				{
					basicStepTimeReportBook.Close(true, missingType, missingType);
					basicStepTimeReportBook = null;

					books.Close();
					books = null;
				}
				else
					shouldQuitExcelApplication = false;
			}
			catch (Exception)
			{
				if (basicStepTimeReportBook != null)
					basicStepTimeReportBook.Close(false, missingType, missingType);

				if (csvBook != null)
					csvBook.Close(false, missingType, missingType);

				if (books != null)
					books.Close();

				if (System.IO.File.Exists(uniqueFilePath))
					System.IO.File.Delete(uniqueFilePath);

				if (System.IO.File.Exists(basicStepTimeReportPath))
					System.IO.File.Delete(basicStepTimeReportPath);

				throw;
			}
		}

		/// <summary>
		/// Validates if the speicified csv file is created using Basic Step Time Report Generator
		/// </summary>
		/// <param name="rawDataSheet">Worksheet present inside csv file (csv file will contain only one worksheet)</param>
		/// <returns>Tru if csv file is created using Basic Step Time Report Generator</returns>
		private static bool ValidateCsvFile(Worksheet rawDataSheet)
		{
			bool fileCreatedByBasicStepTimeReport = true;

			// The first two rows contains station id and operator
			object firstRowFirstColObject = (rawDataSheet.Cells[1, 1] as Range).Value2;
			string firstRowFirstCol = (firstRowFirstColObject != null) ? firstRowFirstColObject.ToString() : "";
			object secondRowFirstColObject = (rawDataSheet.Cells[2, 1] as Range).Value2;
			string secondRowFirstCol = (secondRowFirstColObject != null) ? secondRowFirstColObject.ToString() : "";

			if (string.IsNullOrEmpty(firstRowFirstCol) || !firstRowFirstCol.Equals("Station ID", StringComparison.OrdinalIgnoreCase) ||
					string.IsNullOrEmpty(secondRowFirstCol) || !secondRowFirstCol.Equals("Operator", StringComparison.OrdinalIgnoreCase))
				fileCreatedByBasicStepTimeReport = false;
			else
			{
				int i = 1;
				const int maxTries = 999;

				for (; i < maxTries; ++i)
				{
					object cellObject1 = (rawDataSheet.Cells[i, 1] as Range).Value2;
					string cell1 = (cellObject1 != null) ? cellObject1.ToString() : "";
					// Find the row that contains the table header and verify its value
					if (!string.IsNullOrEmpty(cell1) && cell1.Equals("SequenceFile", StringComparison.OrdinalIgnoreCase))
					{
						object cell2 = (rawDataSheet.Cells[i, 2] as Range).Value2;
						object cell3 = (rawDataSheet.Cells[i, 3] as Range).Value2;
						object cell4 = (rawDataSheet.Cells[i, 4] as Range).Value2;
						object cell5 = (rawDataSheet.Cells[i, 5] as Range).Value2;
						object cell6 = (rawDataSheet.Cells[i, 6] as Range).Value2;
						object cell7 = (rawDataSheet.Cells[i, 7] as Range).Value2;
						object cell8 = (rawDataSheet.Cells[i, 8] as Range).Value2;
						object cell9 = (rawDataSheet.Cells[i, 9] as Range).Value2;
						object cell10 = (rawDataSheet.Cells[i, 10] as Range).Value2;
						object cell11 = (rawDataSheet.Cells[i, 11] as Range).Value2;
						object cell12 = (rawDataSheet.Cells[i, 12] as Range).Value2;
						object cell13 = (rawDataSheet.Cells[i, 13] as Range).Value2;
						object cell14 = (rawDataSheet.Cells[i, 14] as Range).Value2;
						object cell15 = (rawDataSheet.Cells[i, 15] as Range).Value2;
						object cell16 = (rawDataSheet.Cells[i, 16] as Range).Value2;
						object cell17 = (rawDataSheet.Cells[i, 17] as Range).Value2;
						object cell18 = (rawDataSheet.Cells[i, 18] as Range).Value2;
						object cell19 = (rawDataSheet.Cells[i, 19] as Range).Value2;
						object cell20 = (rawDataSheet.Cells[i, 20] as Range).Value2;

						if (cell2 == null || !cell2.ToString().Equals("Sequence", StringComparison.OrdinalIgnoreCase) ||
							cell3 == null || !cell3.ToString().Equals("StepGroup", StringComparison.OrdinalIgnoreCase) ||
							cell4 == null || !cell4.ToString().Equals("StepID", StringComparison.OrdinalIgnoreCase) ||
							cell5 == null || !cell5.ToString().Equals("ParentID", StringComparison.OrdinalIgnoreCase) ||
							cell6 == null || !cell6.ToString().Equals("StepName", StringComparison.OrdinalIgnoreCase) ||
							cell7 == null || !cell7.ToString().Equals("StepType", StringComparison.OrdinalIgnoreCase) ||
							cell8 == null || !cell8.ToString().Equals("Id", StringComparison.OrdinalIgnoreCase) ||
							cell9 == null || !cell9.ToString().Equals("Status", StringComparison.OrdinalIgnoreCase) ||
							cell10 == null || !cell10.ToString().Equals("StartTime", StringComparison.OrdinalIgnoreCase) ||
							cell11 == null || !cell11.ToString().Equals("TotalTime", StringComparison.OrdinalIgnoreCase) ||
							cell12 == null || !cell12.ToString().Equals("ModuleTime", StringComparison.OrdinalIgnoreCase) ||
							cell13 == null || !cell13.ToString().Equals("SequenceCallSequenceFileName", StringComparison.OrdinalIgnoreCase) ||
							cell14 == null || !cell14.ToString().Equals("SequenceCallSequenceName", StringComparison.OrdinalIgnoreCase) ||
							cell15 == null || !cell15.ToString().Equals("NumLoops", StringComparison.OrdinalIgnoreCase) ||
							cell16 == null || !cell16.ToString().Equals("EndingLoopIndex", StringComparison.OrdinalIgnoreCase) ||
							cell17 == null || !cell17.ToString().Equals("LoopIndex", StringComparison.OrdinalIgnoreCase) ||
							cell18 == null || !cell18.ToString().Equals("UUTSerialNumber", StringComparison.OrdinalIgnoreCase) ||
							cell19 == null || !cell19.ToString().Equals("BatchSerialNumber", StringComparison.OrdinalIgnoreCase) ||
							cell20 == null || !cell20.ToString().Equals("TestSocketIndex", StringComparison.OrdinalIgnoreCase))
						{
							fileCreatedByBasicStepTimeReport = false;
						}

						break;
					}
				}

				if (i == maxTries)
					fileCreatedByBasicStepTimeReport = false;
			}

			return fileCreatedByBasicStepTimeReport;
		}

		/// <summary>
		/// Checks if a give file path is valid. Based on value of shouldFileExists, this also checks if a file needs to exists
		/// in the specified file path. Based on value of throwException, this either throws exception on error or returns false.
		/// </summary>
		/// <param name="filePath">File path which needs to be validated</param>
		/// <param name="shouldFileExists">If true, checks for the existance of the file</param>
		/// <param name="throwException">If true, throws an exception if the file is invalid.</param>
		/// <returns>True if file path is valid.</returns>
		private static bool IsPathValid(string filePath, bool shouldFileExists, bool throwException)
		{
			bool isPathValid = false;

			try
			{
				// This does not create a file but check if path is valid or not
				new System.IO.FileInfo(System.IO.Path.GetFullPath(filePath));

				if (shouldFileExists)
				{
					if (System.IO.File.Exists(filePath))
						isPathValid = true;
					else if (throwException)
						throw new System.IO.FileNotFoundException("File " + filePath + " does not exist.");
				}
				else
					isPathValid = true;
			}
			catch (Exception)
			{
				// Expeced exceptions: 
				// ArgumentNullException, SecurityException, ArgumentException, UnauthorizedAccessException, PathTooLongException, NotSupportedException

				if (throwException)
					throw;
			}

			return isPathValid;
		}


		[System.Runtime.InteropServices.DllImport("Msi", CharSet = CharSet.Unicode, ExactSpelling = true)]
		private static extern int MsiQueryFeatureStateW(string szProduct, string szFeature); // P/INVOKE REVIEWED 2013-05-21 TestStand 14.0

		/// <summary>
		/// Checks if Excel application is a 64 bit application
		/// </summary>
		/// <returns>True if Excel is a 64 bit application</returns>
		private static bool IsUsing64BitExcel()
		{
			// 64 bit instance uses registry under 64 bit hive and 32 bit instance uses registry under 32 bit hive.
			// We check the bitness of the instance using the existance of the registry

			bool isExcel64bit = false;

			if (Environment.Is64BitOperatingSystem)
			{
				Application app = ExcelApplication.Instance.App;

				string registryKeyPath = @"SOFTWARE\Microsoft\Office\" + app.Version + @"\Common";
				RegistryKey registryKey = RegistryKey.OpenBaseKey(RegistryHive.LocalMachine, RegistryView.Registry64).OpenSubKey(registryKeyPath);

				if (registryKey != null)
					isExcel64bit = true;
			}

			return isExcel64bit;
		}

		/// <summary>
		/// Checks if VBA is enabled by looking under the Registry key specified in the parameter
		/// </summary>
		/// <param name="rootKey">Registry key under which function checks if VBA is enabled or not. 
		/// In this case, it can be either HKLM or HKCU
		/// </param>
		/// <returns>False if VBA is disabled else will return true</returns>
		private static bool IsVbaEnabled(RegistryKey rootKey)
		{
			bool isVbaEnabled = true;

			Application app = ExcelApplication.Instance.App;

			string registryKeyPath = @"SOFTWARE\Microsoft\Office\" + app.Version + @"\Common";

			RegistryKey registryKey = rootKey.OpenSubKey(registryKeyPath);

			if (registryKey != null)
			{
				int vbaOff = (int)registryKey.GetValue("VBAOff", 0);

				if (vbaOff > 0)
					isVbaEnabled = false;
			}

			return isVbaEnabled;
		}

		/// <summary>
		/// VBA is used to create the processed data and graphs. This function checks for existance
		/// of VBA and checks if it is enabled.
		/// </summary>
		/// <param name="errorMessage">Error Message</param>
		/// <returns>True if VBA can be used in the machine</returns>
		private static bool CanUseVbaInExcel(ref string errorMessage)
		{
			bool vbaInstalledAndEnabled = true;

			Application app = ExcelApplication.Instance.App;

			int installStatus = MsiQueryFeatureStateW(app.ProductCode, "VBAFiles");

			if (installStatus == -1)
			{
				// Office 365 specifies the status of VBAFiles installation as Unknown.
				// Using a sample vba script, check if we can execute VBA
				if (!CanExecuteVbaInExcel())
				{
					vbaInstalledAndEnabled = false;
					errorMessage = "Please verify Visual Basic for Application is installed and enabled.";
				}
			}
			else if (!(installStatus == 1 || installStatus == 3 || installStatus == 4))
			{
				vbaInstalledAndEnabled = false;
				errorMessage = "Please install Visual Basic for Application and retry the operation.";
			}
			else
			{
				// If VBA component is installed, check if it is enabled
				RegistryView bitness = IsUsing64BitExcel() ? RegistryView.Registry64 : RegistryView.Registry32;
				RegistryKey localMachine = RegistryKey.OpenBaseKey(RegistryHive.LocalMachine, bitness);
				RegistryKey currentUser = RegistryKey.OpenBaseKey(RegistryHive.CurrentUser, bitness);

				if (!IsVbaEnabled(localMachine) || !IsVbaEnabled(currentUser))
				{
					vbaInstalledAndEnabled = false;
					errorMessage = "Please enable Visual Basic for Application and retry the operation.";
				}
			}

			return vbaInstalledAndEnabled;
		}

		/// <summary>
		/// Using smaple VBA script, verify if we can executed VBA script in the machine.
		/// </summary>
		/// <returns>True if VBA script can be executed in the machine</returns>
		private static bool CanExecuteVbaInExcel()
		{
			Application app = ExcelApplication.Instance.App;
			Workbooks books = null;
			Workbook basicStepTimeReportBook = null;
			object missingType = System.Reflection.Missing.Value;
			bool canExecuteVbaInExcel = false;

			try
			{
				// Initially make the visibility as false. Otherwise, it will display the template excel file.
				app.Visible = false;

				// DisplayAlerts will be set to false in order to not display warning message
				app.DisplayAlerts = false;

				// Calculate path of the template excel file
				string currentExecutingAssemblyPath = System.Reflection.Assembly.GetExecutingAssembly().Location;
				string currentExecutingAssemblyDir = System.IO.Path.GetDirectoryName(currentExecutingAssemblyPath);
				string templateExcelFilePath = currentExecutingAssemblyDir + System.IO.Path.DirectorySeparatorChar + mBasicStepTimeReportFileName;

				// If the template file does not exists, we will later show the error
				if (System.IO.File.Exists(templateExcelFilePath))
				{
					books = app.Workbooks;

					basicStepTimeReportBook = books.Open(templateExcelFilePath, missingType, false, missingType, missingType,
						missingType, missingType, missingType, missingType, missingType, missingType, missingType, missingType,
							missingType, missingType);


					// Execute the macro to check if we can execute VBA scripts
					app.GetType().InvokeMember("Run",
						System.Reflection.BindingFlags.Default |
						System.Reflection.BindingFlags.InvokeMethod,
						null, app, new Object[] { "EmptySubroutine" }, System.Globalization.CultureInfo.CurrentCulture);
				}

				canExecuteVbaInExcel = true;
			}
			finally
			{
				if (basicStepTimeReportBook != null)
					basicStepTimeReportBook.Close(false, missingType, missingType);

				if (books != null)
					books.Close();

				app.DisplayAlerts = true;
			}

			return canExecuteVbaInExcel;
		}

		/// <summary>
		/// Microsoft Office Excel adds many COM types into the registry
		/// In the registry, if a COM type with progid "Excel.Application" is installed, 
		/// then, it means that Microsoft Office Excel is installed
		/// </summary>
		/// <returns>True if Microsoft Office Excel is installed.</returns>
		internal static bool IsExcelInstalled()
		{
			bool excelInstalled = false;

			if (Type.GetTypeFromProgID("Excel.Application") != null)
				excelInstalled = true;

			return excelInstalled;
		}

		/// <summary>
		/// Checks if Basic Step Time Report Generator supports installed version of Microsoft Office Excel. 
		/// The supported version of Microsoft Excel is 2007 SP2 and above
		/// </summary>
		/// <param name="app">Instance of Microsoft Office Application</param>
		/// <returns>True if Basic Step Time Report Generator supports installed version of Microsoft Office Excel</returns>
		internal static bool CanSupportInstalledExcelVersion()
		{
			Application app = ExcelApplication.Instance.App;
			bool canSupportInstalledExcelVersion = true;

			string version = app.Version;
			int majorVersionStrLen = version.Contains(".") ? version.IndexOf('.') : version.Length;
			int majorVersion = Convert.ToInt32(version.Substring(0, majorVersionStrLen));

			// Major version of Microsoft Office Excel 2007 is 12. Earlier version of Microsoft Office Excel is not supported.
			if (majorVersion < 12)
				canSupportInstalledExcelVersion = false;
			else if (majorVersion == 12)
			{
				// If Office 2007 is installed (there exists only 32 bit version), get the File version of Excel.exe and 
				// check if required service packs is installed or not.
				RegistryKey localMachineReg = RegistryKey.OpenBaseKey(RegistryHive.LocalMachine, RegistryView.Registry32);
				string registryKeyPath = @"SOFTWARE\Microsoft\Office\12.0\Common\InstallRoot";
				RegistryKey registryKey = localMachineReg.OpenSubKey(registryKeyPath);

				if (registryKey != null)
				{
					string excelDir = registryKey.GetValue("Path").ToString();

					FileVersionInfo fileVersionInfo = FileVersionInfo.GetVersionInfo(Path.Combine(excelDir, "Excel.exe"));

					if (fileVersionInfo != null)
					{
						string fileVersion = fileVersionInfo.FileVersion;

						// If the Microsoft Office Excel being used is Office 2007, check for the service packs. 
						// Basic Step Time Report Generator supports Office 2007 SP2 and above.
						// File version "12.0.4518.1014" represents Excel without any service packs
						// File version "12.0.6214.1000" represents Excel with SP1
						if (fileVersion.Equals("12.0.4518.1014", StringComparison.OrdinalIgnoreCase) || 
							fileVersion.Equals("12.0.6214.1000", StringComparison.OrdinalIgnoreCase))
						{
							canSupportInstalledExcelVersion = false;
						}
					}
					else
						canSupportInstalledExcelVersion = false;
				}
				else
					canSupportInstalledExcelVersion = false;
			}

			return canSupportInstalledExcelVersion;
		}

		/// <summary>
		/// Checks for the following necessary pre requisites for generating Basic Step Time Report
		/// 1. Supported version of Microsoft Office Excel should be installed
		/// 2. Template Excel file should be present in the directory containing the executable
		/// </summary>
		/// <param name="errorMessage">Error message if any pre-requisite is not satisfied</param>
		/// <returns>True if all pre-requisites are satisfied</returns>
		internal static bool CanCreateBasicStepTimeReport(ref string errorMessage)
		{
			bool createBasicStepTimeReport = true;

			// Check if supported version of Excel is installed
			if (!IsExcelInstalled())
			{
				createBasicStepTimeReport = false;
				errorMessage = "Unable to create a basic step time report in Microsoft Excel format. " +
					"Install Microsoft Office 2007 SP2 or later and use CsvToBasicStepTimeReportGenerator.exe to generate a basic step time report in Excel format.";
			}
			else
			{
				// Verify if installed Excel can be supported
				if (!CanSupportInstalledExcelVersion())
				{
					createBasicStepTimeReport = false;

					errorMessage = "The Basic Step Time Report Generator requires Microsoft Office Excel 2007 SP2 or later to generate a report in Excel format. " +
							"Install a supported version of Microsoft Office Excel and try creating a basic step time report in Excel format again.";
				}
				else
				{
					// Check if VBA is installed and Enabled
					if (CanUseVbaInExcel(ref errorMessage))
					{
						// Check if template excel file is present
						string currentExecutingAssemblyPath = System.Reflection.Assembly.GetExecutingAssembly().Location;
						string directoryContainingTemplateExcel = System.IO.Path.GetDirectoryName(currentExecutingAssemblyPath);
						string templateFilePath = System.IO.Path.Combine(directoryContainingTemplateExcel, mBasicStepTimeReportFileName);

						if (!System.IO.File.Exists(templateFilePath))
						{
							createBasicStepTimeReport = false;
							errorMessage = "Unable to find the " + mBasicStepTimeReportFileName + " file in the " + directoryContainingTemplateExcel + " directory. " +
								"Copy the " + mBasicStepTimeReportFileName + " to the directory and try creating the basic step time report again.";
						}
					}
					else
						createBasicStepTimeReport = false;
				}
			}

			return createBasicStepTimeReport;
		}

		private static bool shouldQuitExcelApplication = true;

		private const string mBasicStepTimeReportFileName = "BasicStepTimeReport.xls";

		/// <summary>
		/// Creates a singleton for Excel Application instance. 
		/// Creating an instance of Application creates a new process for Excel.exe. 
		/// We need only one instance to display the generated report. 
		/// Note: This class assumes that at any given point of time, only of one thread will be 
		/// executing inside the class.
		/// </summary>
		internal sealed class ExcelApplication: IDisposable
		{
			private bool _disposed;
			private static readonly ExcelApplication instance = new ExcelApplication();

			private ExcelApplication() { }

			internal static ExcelApplication Instance
			{
				get
				{
					return instance;
				}
			}

			private Application mApp = null;

			internal Application App
			{
				get
				{
					// Create the Excel Application instance the first time it is used.
					if (mApp == null)
						mApp = new Application();

					return mApp;
				}
			}

			/// <summary>
			/// Implements Dispose method of IDisposable interface
			/// </summary>
			public void Dispose()
			{
				Dispose(true);
				GC.SuppressFinalize(this);
			}

			/// <summary>
			/// If calling from Dispose method, instance of Excel Application is released if necessary.
			/// The instance will not be released if generated Excel report is displayed.
			/// </summary>
			/// <param name="disposing">True if calling from Dispose.</param>
			private void Dispose(bool disposing)
			{
				if (!_disposed)
				{
					if (disposing)
					{
						// shouldQuitExcelApplication will be false if Display Excel report is enabled.
						// If Display Excel report is enabled, then closing the Excel dialog will 
						// release the mApp resource
						if (mApp != null && shouldQuitExcelApplication == true)
						{
							mApp.Quit();
							mApp = null;
						}
					}

					// Indicate that the instance has been disposed.
					_disposed = true;
				}
			}

			~ExcelApplication()
			{
				Dispose(false);
			}
		}
	}
}
