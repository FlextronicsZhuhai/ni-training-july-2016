using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NationalInstruments.TestStand.Interop.API;
using System.Runtime.InteropServices;

namespace TerminationMonitorExample
{
    public class TerminationMonitorExample
    {
        private TerminationMonitorExampleForm dialog = null;

        public TerminationMonitorExample(NationalInstruments.TestStand.Interop.API.SequenceContext seqContext)
        {
            this.dialog = new TerminationMonitorExampleForm(seqContext);

            //calls a function in the form code which starts the Termination Monitor
            this.dialog.InitializeTerminationStateChecking(); 
        }
        public void startExample(out bool errorOccurred, out int errorCode, out String errorMsg)
        {
            errorOccurred = false;
            errorCode = 0;
            errorMsg = String.Empty;

            try
            {
                this.dialog.ShowDialog();
            }
            catch (COMException e)
            {
                errorOccurred = true;
                errorMsg = e.Message;
                errorCode = e.ErrorCode;
            }
        }

        #region IDisposable Members

        public void Dispose()
        {
            if (this.dialog != null)
            {
                this.dialog.Dispose();
                this.dialog = null;
            }
        }

        #endregion

    }
}
