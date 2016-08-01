//typeDefs

struct simulationData
{
   int PowerOn;
   int Battery;
   int LCD;
   int Antenna;
   int Microphone;
   int Speakers;
   int Buttons;
};

//functions

int InitializeUUT(char instrumentName[1024]);
int InitializeTester(char instrumentName[1024]);
int CloseUUT(int instHandle);
int CloseTester(int instHandle);

int UUTPowerOn(int instHandle, int* result, struct simulationData *simData); 
int MeasureUUTBatteryVoltage(int instHandle, struct simulationData *simData, double* measurement); 
int ButtonActuatorPressButton(int instHandle, char ButtonToTest[1024]);
int GetButtonState(int instHandle, char ButtonToTest[1024], struct simulationData *simData, int* result); 
int ButtonActuatorReleaseButton(int instHandle, char ButtonToTest[1024]);
int MeasureUUTPowerVoltage(int instHandle, struct simulationData *simData, double* measurement);
int MeasureUUTPowerCurrent(int instHandle, struct simulationData *simData,  double* measurement); 
