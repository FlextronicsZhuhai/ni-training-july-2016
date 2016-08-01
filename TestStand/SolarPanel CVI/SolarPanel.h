

//==============================================================================
// Include files

#include "cvidef.h"
#include "SimulationDriver.h"
#include "analysis.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// External variables

//==============================================================================
// Global functions



void ControllerBoardTempTest (char dmmNameIn [], char psuNameIn [], int dmmChannelIn, double lineInVoltage, double* temperature, Error* errorInfo);
void VoltageOutputTest (char dmmNameIn [], char psuNameIn [], int dmmChannelIn, double lineInVoltage, double* ACout, Error* errorInfo);
void ACFrequencyTest (char scopeNameIn [], int dmmChannelIn, double* measFreqOut, double* measAmplOut, double* measPhaseOut, double waveformDataOut [], Error* errorInfo);
void PanelOutputVoltageTest (char dmmNameIn [], int dmmChannelIn, double* measVoltageOut, Error* errorInfo);
