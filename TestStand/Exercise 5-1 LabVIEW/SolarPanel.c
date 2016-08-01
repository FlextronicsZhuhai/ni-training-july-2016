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


void ControllerBoardTempTest (char* dmm, char* powerSupply, double lineInVoltage, double* temperature, Error* errorInfo)
{
	Sim_PowerSupply_GenerateOutputVoltageDC(powerSupply, 0, 0, lineInVoltage, errorInfo);
	Sim_Dmm_Configure(dmm, TestStand_Instrument_Simulation_SignalTypes_DC, errorInfo);
	Sim_Dmm_ReadTemperature(dmm, 10, 0, KTypeThermocouple, temperature, errorInfo);
}

void VoltageOutputTest(char* dmm, char* powerSupply, double lineInVoltage, double* DCout, Error* errorInfo)
{
	Sim_PowerSupply_GenerateOutputVoltageDC(powerSupply, 0, 0, lineInVoltage, errorInfo);
	Sim_Dmm_Configure(dmm, DCout, errorInfo);
	Sim_Dmm_ReadVoltage(dmm, 2, 0, DCout, errorInfo);
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
