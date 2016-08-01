//==============================================================================
// Include files

#include "cvidef.h"
#include "SimulationDriver.h" 

//==============================================================================
// Global functions

void ControllerBoardThermalTest (char* dmm, char* powerSupply, int socket, double lineInVoltage, double* temperature, Error* errorInfo);
void VoltageOutputTest (char* dmm, char* powerSupply, int DMMChannel, int socket, double lineInVoltage, double* ACout, Error* errorInfo);                
void ACFrequencyTest (char* scope, int socket, double* frequency, double* waveformData, Error* errorInfo);   
void PanelOutputVoltageTest(char* dmm, int socket, double* voltage, Error* errorInfo);
