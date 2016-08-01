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

namespace NationalInstruments.TestStand.Examples.MobileDeviceDemo
{
    
    public partial class SimulationDialog : Form
    {
        private NationalInstruments.TestStand.Interop.API.SequenceContext mSequenceContext;
        private NationalInstruments.TestStand.Interop.API.PropertyObject mTerminationMonitorData;

        public SimulationDialog(NationalInstruments.TestStand.Interop.API.SequenceContext currentContext)
        {
            InitializeComponent();
            
            this.mSequenceContext = currentContext;
			LCD.SelectedIndex = 0;
           
          }

         
        private void OKButton_Click(object sender, EventArgs e)
        {
            
            Close();
            
            string simDataLookupString = "FileGlobals.SimulationData";
            
            mSequenceContext.AsPropertyObject().SetValBoolean(simDataLookupString + ".PowerOn", 0, !Power.Checked);
            mSequenceContext.AsPropertyObject().SetValBoolean(simDataLookupString + ".Battery", 0, !Battery.Checked);
            mSequenceContext.AsPropertyObject().SetValBoolean(simDataLookupString + ".Antenna", 0, !Antenna.Checked);
            mSequenceContext.AsPropertyObject().SetValBoolean(simDataLookupString + ".Microphone", 0, !Microphone.Checked);
            mSequenceContext.AsPropertyObject().SetValBoolean(simDataLookupString + ".Speakers", 0, !Speakers.Checked);
            mSequenceContext.AsPropertyObject().SetValBoolean(simDataLookupString + ".Buttons", 0, !Buttons.Checked);
            mSequenceContext.AsPropertyObject().SetValNumber(simDataLookupString + ".LCD", 0, LCD.SelectedIndex);
        }

        private void SimulationDialog_Shown(object sender, EventArgs e)
        {
            this.Hide();
            double Count = mSequenceContext.AsPropertyObject().GetValNumber("RunState.TestSockets.Count", 0);

            if (Count > 1)
            {
                // If there are multiple sockets, position the dialog based on the test socket so they do not overlap 
                double Index = mSequenceContext.AsPropertyObject().GetValNumber("RunState.TestSockets.MyIndex", 0);
                double Offset = 30;

                double numberOfColumns = Math.Ceiling(Math.Sqrt(Count));
                double numberOfRows = Math.Ceiling(Count / numberOfColumns);
         
                if(numberOfRows > 1)
                    this.Top += (int)((Offset + (numberOfRows - 1) * Height) * ((Math.Floor(Index / numberOfColumns) / (numberOfRows - 1)) - (.5)));
                if(numberOfColumns > 1)
                    this.Left += (int)((Offset + (numberOfColumns - 1) * Width) * ((Math.Floor(Index % numberOfColumns) / (numberOfColumns - 1)) - (.5)));

                Text += " (Test Socket - " + Index.ToString() + ")";


            }                
            //start monitoring for test termination
            InitializeTerminationStateChecking();
            
            this.Show();
            this.TopMost = true;
            this.TopMost = false;
         }

         public void InitializeTerminationStateChecking()
         {
             this.mTerminationMonitorData = this.mSequenceContext.Execution.InitTerminationMonitor();
             if (mSequenceContext != null)
                 cancelDialogTimer.Enabled = true;
         }

         private void cancelDialogTimer_Tick(object sender, EventArgs e)
         {
             //if the execution is terminated, close the dialog
             if (this.mSequenceContext != null)
                 if (this.mSequenceContext.Execution != null)
                     if (this.mSequenceContext.Execution.GetTerminationMonitorStatus(this.mTerminationMonitorData, this.mSequenceContext))
                         Close();
         }

         private void SimulationDialog_FormClosed(object sender, FormClosedEventArgs e)
         {
             cancelDialogTimer.Enabled = false;
             this.Dispose();
		 }
    }
}
