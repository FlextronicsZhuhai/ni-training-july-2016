using System;
using System.Collections.Generic;
using System.Text;
using NationalInstruments.TestStand.Interop.API;    // TestStand Core API.  Add <TestStand>\API\DotNet\Assemblies\CurrentVersion\NationalInstruments.TestStand.Interop.API.dll to your project as a reference.
using System.Runtime.InteropServices;

namespace ClassLibrary
{
	public class Class
	{
		public double CalculateAreaOfCircle(double radius)
		{
			return System.Math.PI * System.Math.Pow(radius, 2);
		}
	}
}
