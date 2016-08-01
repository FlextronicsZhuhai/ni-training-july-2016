using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ExampleCodeModule
{
	public class ExampleCodeModuleClass
	{
		public int getCurrentBitnessMethod()
		{
			if (IntPtr.Size == 8)
			{
				return 64;
			}
			else
			{
				return 32;
			}
		}
	}
}
