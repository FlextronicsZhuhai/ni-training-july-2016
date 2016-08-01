using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using NationalInstruments.TestStand.Interop.API;
using System.Runtime.InteropServices;

namespace TerminationMonitorExample
{
    public partial class TerminationMonitorExampleForm : Form
    {
        private NationalInstruments.TestStand.Interop.API.PropertyObject mTerminationMonitorData; //stores data for the Termination Monitor function
        private NationalInstruments.TestStand.Interop.API.SequenceContext mSequenceContext; //sequence context from the TestStand execution


        public TerminationMonitorExampleForm(NationalInstruments.TestStand.Interop.API.SequenceContext seqContext)
        {
            this.mSequenceContext = seqContext;
            InitializeComponent(); 
        }

        //This function initializes the termination monitor and starts the timer to cause the code to poll for execution termination
        public void InitializeTerminationStateChecking()
        {
            // the Execution.InitTerminationMonitor() function creates the initial termination monitor data property object 
            // the Execution.GetTerminationMonitorStatus method uses.
            this.mTerminationMonitorData = this.mSequenceContext.Execution.InitTerminationMonitor();

            //If the sequence context is valid, enable the timer callback to monitor the TestStand execution status
            if (this.mSequenceContext != null)
            {
                this.terminationTimer.Enabled = true;
            }
        }

        //This timer ticks every 100ms and checks the status of the TestStand execution to determine whether the dialog needs to close
        private void terminationTimer_Tick(object sender, EventArgs e)
        {
            if (this.mSequenceContext != null)
            {
                if (this.mSequenceContext.Execution != null)
                {
                    // If the termination monitor status returns True, the TestStand execution has been terminated or aborted.
                    // This function monitors an execution so the calling code can abort what it is doing and exit if the user requests that the execution terminate or abort.
                    if (this.mSequenceContext.Execution.GetTerminationMonitorStatus(this.mTerminationMonitorData, this.mSequenceContext))
                    {
                        this.Close();
                    }
                }
            }
        }

        private void StopButton_Click(object sender, EventArgs e)
        {
            this.Close();
        }

    }
}
