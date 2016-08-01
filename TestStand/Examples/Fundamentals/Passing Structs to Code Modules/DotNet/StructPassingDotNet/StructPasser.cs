using NationalInstruments.TestStand.Interop.API;

namespace StructPassingDotNet
{
	public struct AllTypes
	{
		public char Char;
		public int Integer32;
		public short Integer16;
		public float Real32;
		public double Real64;
		public float[] NumberArray;
		public string String;
		public bool Bool;
		public SequenceContext SequenceContext;
	}

	public class StructPasser
	{
		private AllTypes _allTypes;

		public void SetStructByVal(AllTypes allTypes, out bool errorOccurred, out int errorCode, out string errorMsg)
		{
			errorOccurred = false;
			errorCode = 0;
			errorMsg = string.Empty;

			_allTypes = allTypes;

		}

		public void SetStructByRef(ref AllTypes allTypes, out bool errorOccurred, out int errorCode, out string errorMsg)
		{
			errorOccurred = false;
			errorCode = 0;
			errorMsg = string.Empty;

			_allTypes = allTypes;

		}

		public void GetStructByRef(out AllTypes allTypes, out bool errorOccurred, out int errorCode, out string errorMsg)
		{
			errorOccurred = false;
			errorCode = 0;
			errorMsg = string.Empty;

			allTypes = _allTypes;
		}
	}
}
