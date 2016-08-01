#include <userint.h>
#include "tsapicvi.h" 
#include "tsutil.h"

#include "ConfigureCheckStepNameLength.h"


int __stdcall DllMain (HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
		case DLL_PROCESS_ATTACH:
			if (InitCVIRTE (hinstDLL, 0, 0) == 0)		
				return 0;	/* out of memory */
			break;
		case DLL_PROCESS_DETACH:
			if (!CVIRTEHasBeenDetached())		/* Do not call CVI functions if cvirte.dll has already been detached. */
			{
				CloseCVIRTE ();		
			}
			break;
	}

	return 1;
}

 
int CVICALLBACK ConfigRule_OKCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			QuitUserInterface(EVENT_DLG_DONE_OK);
			break;
	}
	return 0;
}

int CVICALLBACK ConfigRule_CancelCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			QuitUserInterface(EVENT_DLG_DONE_CANCEL);
			break;
	}
	return 0;
}
