#include "tsutil.h"
#include "MobileDeviceTest.h"
  
//*********************************************
//Test Functions
//********************************************* 

//Power on the UUT, and indicate if the powerOn failed
void __declspec(dllexport) __stdcall PowerOnTest(int *result, struct simulationData *simData,
		char reportText[1024], short *errorOccurred, long *errorCode, char errorMsg[1024])
{
	int error = 0;
	int UUTCtrlHandle;
	
	errChk(UUTCtrlHandle = InitializeUUT("UUTController"));
	errChk(UUTPowerOn(UUTCtrlHandle, result, simData));

Error:
	CloseUUT(UUTCtrlHandle);  
	
	if (error < 0)
	{
		*errorOccurred = TRUE;
		*errorCode = error;
	}
}

//Test the voltage of the battery
void __declspec(dllexport) __stdcall BatteryVoltageTest(double *measurement, struct simulationData *simData,  
		char reportText[1024], short *errorOccurred, long *errorCode, char errorMsg[1024])
{
	int error = 0;
	int DMMHandle;

	errChk(DMMHandle = InitializeTester("TesterDMM"));
	errChk(MeasureUUTBatteryVoltage(DMMHandle, simData, measurement));
	
Error:
	CloseTester(DMMHandle);  
	if (error < 0)
	{
		*errorOccurred = TRUE;
		*errorCode = error;
	
	}
}

//Test the specified button by having the test fixture actuator press it, and returning the state from the UUT Controller
__declspec(dllexport) void ButtonTest(char *ButtonToTest, int *result, struct simulationData *simData, 
		char reportText[1024], short *errorOccurred, long *errorCode, char errorMsg[1024])
{
 	int error = 0;
	int BtnActuatorHandle;
	int UUTCtrlHandle; 
	
	errChk(BtnActuatorHandle = InitializeTester("ButtonActuator"));
	errChk(UUTCtrlHandle = InitializeUUT("UUTController"));
	
	errChk(ButtonActuatorPressButton(BtnActuatorHandle, ButtonToTest));
	errChk(GetButtonState(BtnActuatorHandle, ButtonToTest, simData, result)); 
	errChk(ButtonActuatorReleaseButton(BtnActuatorHandle, ButtonToTest)); 
	
Error:
	 
	CloseUUT(UUTCtrlHandle);
	CloseTester(BtnActuatorHandle);
	
	if (error < 0)
	{
		*errorOccurred = TRUE;
		*errorCode = error;
	
	}
}

//Measure the current across the power supply pin
void __declspec(dllexport) __stdcall PowerPinCurrentDiagnostic(double *measurement, struct simulationData *simData, 
		char reportText[1024], short *errorOccurred, long *errorCode, char errorMsg[1024])
{
	int error = 0;
	int DMMHandle;

	errChk(DMMHandle = InitializeTester("TesterDMM"));
	errChk(MeasureUUTPowerCurrent(DMMHandle, simData, measurement)); 
	
Error:
	CloseTester(DMMHandle);  
	if (error < 0)
	{
		*errorOccurred = TRUE;
		*errorCode = error;
	
	}
}

//Measure the voltage across the power supply pin 
void __declspec(dllexport) __stdcall PowerPinVoltageDiagnostic(double *measurement, struct simulationData *simData, 
		char reportText[1024], short *errorOccurred, long *errorCode, char errorMsg[1024])
{
	int error = 0;
	int DMMHandle;

	errChk(DMMHandle = InitializeTester("TesterDMM"));
	errChk(MeasureUUTPowerVoltage(DMMHandle, simData, measurement));
	
Error:
	CloseTester(DMMHandle);
	
	if (error < 0)
	{
		*errorOccurred = TRUE;
		*errorCode = error;
	
	}
}

//*********************************************
//Internal Functions
//********************************************* 

int InitializeUUT(char instrumentName[1024])
{
	//This function simulates initializing a reference to the UUT testing hardware.	
	//in a real application, an actual instrument handle would be provided by the driver
	return 1;
}

int InitializeTester(char instrumentName[1024])
{
	//This function simulates initializing a reference to the test fixture hardware.
	//in a real application, an actual instrument handle would be provided by the driver
	return 2;
}

int CloseUUT(int instHandle)
{
	//This function simulates closing a reference to the UUT testing hardware.	
	return 0;
}

int CloseTester(int instHandle)
{
	//This function simulates closing a reference to the UUT testing hardware.	
	return 0;
}

int UUTPowerOn(int instHandle, int* result, struct simulationData *simData)
{
	if(simData->PowerOn)
	{
		*result = TRUE;
	}
	else
	{
		*result = FALSE;
	}
	return 0;
}

int MeasureUUTBatteryVoltage(int instHandle, struct simulationData *simData, double* measurement) 
{
	if(simData->Battery)
	{
		*measurement = 3.725 + rand() / RAND_MAX * .1;
	}
	else
	{
		*measurement = 3.3 + rand() / RAND_MAX * .2;
	}
	return 0;
}


int ButtonActuatorPressButton(int instHandle, char ButtonToTest[1024])
{
	//simulate the test fixture actuator pressing the specified UUT button
	
	return 0;
}


int ButtonActuatorReleaseButton(int instHandle, char ButtonToTest[1024])
{
	//simulate the test fixture actuator releasing the specified UUT button

	return 0;
}


int GetButtonState(int instHandle, char ButtonToTest[1024], struct simulationData *simData, int* result)
{
	//if the button test is set to fail, fail the home button test
	if(simData->Buttons)
	{
		*result = TRUE;
	}
	else
	{
		if (strcmp(ButtonToTest, "Home"))
		{
			*result = TRUE;
		}
		else
		{
			*result = FALSE;
		}
	}
	return 0;
}


int MeasureUUTPowerVoltage(int instHandle, struct simulationData *simData, double* measurement)
{
	if(simData->PowerOn)
	{
		*measurement = 3.725 + rand() / RAND_MAX * .1;
	}
	else
	{
		*measurement = 3.3 + rand() / RAND_MAX* .2;
	}
	return 0;
}


int MeasureUUTPowerCurrent(int instHandle, struct simulationData *simData,  double* measurement) 
{
	if(simData->PowerOn)
	{
		*measurement = 300 + rand() / RAND_MAX * 5;
	}
	else
	{
		*measurement = 200 + rand() / RAND_MAX* 20;
	}
	return 0;
}
