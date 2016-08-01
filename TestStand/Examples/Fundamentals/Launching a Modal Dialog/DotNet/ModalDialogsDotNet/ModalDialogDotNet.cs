using System;
using System.Runtime.InteropServices;
using NationalInstruments.TestStand.Interop.API;

namespace ModalDialogsDotNet
{
	public class ModalDialogDotNet
	{
		public void ShowDialog(SequenceContext seqContext, out bool errorOccurred, out int errorCode, out String errorMsg)
		{

			errorOccurred = false;
			errorCode = 0;
			errorMsg = String.Empty;

			Engine engine = seqContext.Engine;

			try
			{
				// notify the engine that a modal dialog is about to be opened
				bool shouldAbort = false;
				int modalId = engine.NotifyStartOfModalDialogEx(seqContext, out shouldAbort);
			
				// open dialog
				if (!shouldAbort)
				{
					ModalDialog dialog = new ModalDialog();
					dialog.ShowDialog();
				}

				// notify the engine that the modal dialog has been closed
				engine.NotifyEndOfModalDialog(modalId);

			}
			catch (COMException e)
			{
				errorOccurred = true;
				errorMsg = e.Message;
				errorCode = e.ErrorCode;
			}
		}
	}
}
