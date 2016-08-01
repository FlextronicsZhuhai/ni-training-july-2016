//==============================================================================
//
// Title:		Lesson 2-2 CVI
// Purpose:		A short description of the library.
//
// Created on:	7/25/2016 at 2:02:11 PM by Windows User.
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files


#include "SolarPanel.h"



//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?


void ControllerBoardTempTest (char dmmNameIn [], char psuNameIn [], int dmmChannelIn, double lineInVoltage, double* measTempOut, Error* errorInfo)
{
	int testSocket = 0;
	int psuChannel = 0;
	int psuSocket = 0;
	
	Sim_PowerSupply_GenerateOutputVoltageDC(psuNameIn, psuChannel, psuSocket, lineInVoltage, errorInfo);
	Sim_Dmm_Configure(dmmNameIn, TestStand_Instrument_Simulation_SignalTypes_DC, errorInfo);
	Sim_Dmm_ReadTemperature(dmmNameIn, dmmChannelIn, testSocket, KTypeThermocouple, measTempOut, errorInfo);
}

void VoltageOutputTest (char dmmNameIn [], char psuNameIn [], int dmmChannelIn, double lineInVoltage, double* ACout, Error* errorInfo)
{
	int testSocket = 0;  
	
	Sim_PowerSupply_GenerateOutputVoltageDC(psuNameIn, 0, 0, lineInVoltage, errorInfo);
	Sim_Dmm_Configure(dmmNameIn, AC, errorInfo);
	Sim_Dmm_ReadVoltage(dmmNameIn, dmmChannelIn, testSocket, ACout, errorInfo);
}

void ACFrequencyTest (char scopeNameIn [], int scopeChannelIn, double* measFreqOut, double* measAmplOut, double* measPhaseOut, double waveformDataOut [], Error* errorInfo)
{
	int numSamples = 1000;
	int sampleFreq = 1000;
	int testSocket = 0;
	
	Sim_Scope_Configure(scopeNameIn, numSamples, sampleFreq, errorInfo);
	Sim_Scope_ReadWaveform(scopeNameIn, scopeChannelIn, testSocket, waveformDataOut, errorInfo);
	SingleToneInfo(waveformDataOut, numSamples, 1 / (double)sampleFreq, NULL, measFreqOut, measAmplOut, measPhaseOut);
}


void PanelOutputVoltageTest (char dmmNameIn [], int dmmChannelIn, double* measVoltageOut, Error* errorInfo)
{
	int testSocket = 0;
	
	Sim_Dmm_Configure(dmmNameIn, DC, errorInfo);
	Sim_Dmm_ReadVoltage(dmmNameIn, dmmChannelIn, testSocket, measVoltageOut, errorInfo);
}


//==============================================================================
// DLL main entry-point functions

int __stdcall DllMain (HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason) {
		case DLL_PROCESS_ATTACH:
			if (InitCVIRTE (hinstDLL, 0, 0) == 0)
				return 0;	  /* out of memory */
			break;
		case DLL_PROCESS_DETACH:
			CloseCVIRTE ();
			break;
	}
	
	return 1;
}

int __stdcall DllEntryPoint (HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	/* Included for compatibility with Borland */

	return DllMain (hinstDLL, fdwReason, lpvReserved);
}
