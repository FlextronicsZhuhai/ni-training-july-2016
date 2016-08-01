using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

using System.Runtime.InteropServices;

namespace NationalInstruments.TestStand.Examples.MobileDeviceDemo
{
    public class MobileDeviceDemo
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        private SimulationDialog mDialog = null;
        private NationalInstruments.TestStand.Interop.API.SequenceContext mSequenceContext;
            
        public MobileDeviceDemo(NationalInstruments.TestStand.Interop.API.SequenceContext sequenceContext)
		{
            mSequenceContext = sequenceContext;
        }

        public void LaunchSimulationDialog(out bool errorOccurred, out int errorCode, out String errorMsg)
        {
            errorOccurred = false;
            errorCode = 0;
            errorMsg = String.Empty;

            try
            {
                /* The "using" block will execute the code inside and then dispose of the variable declared in the parenthesis. 
                 * It provides two key advantages:
                      1) Forces explicit garbage collection
                      2) Protects the developer from inadvertently using a variable later in the application 
                 *       where it is not intended to be used. 
                 */
                using (mDialog = new SimulationDialog(mSequenceContext))
                {
                    this.mDialog.ShowDialog();
                }
            }
            catch (COMException e)
            {
                errorOccurred = true;
                errorMsg = e.Message;
                errorCode = e.ErrorCode;
            }
        }

        public void InitializeTestFixture(out bool errorOccurred, out int errorCode, out String errorMsg)
        {

            errorOccurred = false;
            errorCode = 0;
            errorMsg = String.Empty; 
            
            try
            {
                //simulate initializing hardware resources
            }
            catch (COMException e)
            {
                errorOccurred = true;
                errorMsg = e.Message;
                errorCode = e.ErrorCode;
            }
        }
        public void DisconnectTestFixture(out bool errorOccurred, out int errorCode, out String errorMsg)
        {
            errorOccurred = false;
            errorCode = 0;
            errorMsg = String.Empty; 
            
            try
            {
                //simulate disconnecting hardware resources
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
