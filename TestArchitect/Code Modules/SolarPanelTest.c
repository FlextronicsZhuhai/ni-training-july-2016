//==============================================================================
// Include files

#include <analysis.h>
#include "SolarPanelTest.h"

//==============================================================================
// Global functions

void ControllerBoardThermalTest (char* dmm, char* powerSupply, int socket, double lineInVoltage, double* temperature, Error* errorInfo)        
{
   Sim_Fixture_SetAmbientTemperature(60, errorInfo);
   Sim_PowerSupply_GenerateOutputVoltageDC(powerSupply, 0, socket, lineInVoltage, errorInfo);
   Sim_Dmm_Configure(dmm, DC, errorInfo);
   Sim_Dmm_ReadTemperature(dmm,10, socket,KTypeThermocouple, temperature, errorInfo);
}	  

void VoltageOutputTest (char* dmm, char* powerSupply, int DMMChannel, int socket, double lineInVoltage, double* ACout, Error* errorInfo)        
{
   Sim_PowerSupply_GenerateOutputVoltageDC(powerSupply, 0, socket, lineInVoltage, errorInfo);
   Sim_Dmm_Configure(dmm, AC, errorInfo);
   Sim_Dmm_ReadVoltage(dmm, DMMChannel, socket, ACout, errorInfo);
}

void ACFrequencyTest (char* scope, int socket, double* frequency, double* waveformData, Error* errorInfo)        
{
   double amplitude;
   double phase;
   
   int numSamples = 1000;
   int samplesPerSecond = 1000; 
   
   Sim_Scope_Configure(scope, numSamples, samplesPerSecond, errorInfo);
   Sim_Scope_ReadWaveform(scope, 3, socket, waveformData, errorInfo);
   SingleToneInfo(waveformData, numSamples, 1 / (double)samplesPerSecond, NULL, frequency, &amplitude, &phase);
}

void PanelOutputVoltageTest(char* dmm, int socket, double* voltage, Error* errorInfo)
{
   Sim_Dmm_Configure(dmm, DC, errorInfo);
   Sim_Dmm_ReadVoltage(dmm, 6, socket, voltage, errorInfo);
}
