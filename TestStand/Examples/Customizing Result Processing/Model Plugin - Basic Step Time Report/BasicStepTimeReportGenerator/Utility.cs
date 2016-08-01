using System;
using NationalInstruments.TestStand.Interop.API;

namespace BasicStepTimeReportGenerator
{
	static class Utility
	{
		/// <summary>
		/// Microsoft Office Excel adds many COM types into the registry
		/// In the registry, if a COM type with progid "Excel.Application" is installed, 
		/// then, it means that Microsoft Office Excel is installed
		/// </summary>
		/// <returns>True if Microsoft Office Excel is installed.</returns>
		internal static bool IsExcelInstalled()
		{
			bool isExcelInstalled = false;

			if (Type.GetTypeFromProgID("Excel.Application") != null)
				isExcelInstalled = true;

			return isExcelInstalled;
		}

		/// <summary>
		/// A simple wrapper method for GetResourceString().  Most
		/// likely you will not need this because you will probably not need
		/// any TestStand resource strings.  It is used here to support
		/// localization.
		/// </summary>
		/// <param name="engine">An instance of the TestStand engine.</param>
		/// <param name="category">The category in the resource .ini
		/// file.</param>
		/// <param name="symbol">The string to replace, defined in the
		/// resource .ini file.</param>
		/// <returns>The requested resource string if found, or symbol if the
		/// resource was not found.</returns>
		internal static string RString(Engine engine, string category, string symbol)
		{
			object found_UNUSED;
			return engine.GetResourceString(category, symbol, symbol, out found_UNUSED);
		}
	}
}
