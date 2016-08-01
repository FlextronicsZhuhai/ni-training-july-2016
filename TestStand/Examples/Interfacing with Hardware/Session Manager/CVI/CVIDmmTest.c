#include "stdtst.h"
#include "tsutil.h"
#include "sessionmgr.h"
#include "ividmm.h"

    // This example test module aquires the instrument session by name.  Provided that
    // another reference to the session exists, this module does not recreate or 
    // reinitialize the session.
void __declspec(dllexport) __stdcall ReadDMM(double *measurement, const char *logicalName, 
        short *errorOccurred, long *errorCode, char errorMsg[1024])
{
    int error = 0;
    ErrMsg errMsg = {'\0'};
    ERRORINFO errorInfo;
    ViSession   handle;
	VARIANT vtHandle = CA_DefaultValueVariant();
    CAObjHandle session = 0;

       // get a reference to the session
    tsErrChk( SM_GetSession(logicalName, &session, &errorInfo));

        // get the driver handle (you don't need to release it)
    tsErrChk( SM_GetHandleEx(session, NULL, SMConst_ClassDriver,
                          &vtHandle, &errorInfo));

	CA_VariantGetLong(&vtHandle, &handle);
	
		// call the instrument as much as you want:
    errChk( IviDmm_Read (handle, 5000, measurement));

Error:  
    SM_ReleaseSession(session);  

    // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
        {
         *errorOccurred = TRUE;
         *errorCode = error;
         strcpy(errorMsg, errMsg);
        }
}

/////////////////////////////////////////////////

    // This example test module aquires the instrument session by name.  Provided that
    // another reference to the session exists, this module does not recreate or 
    // reinitialize the session.
void __declspec(dllexport) __stdcall ConfigureDMMForVoltageMeasurements(const char *logicalName,
        short *errorOccurred, long *errorCode, char errorMsg[1024])
{
    int error = 0;
    ErrMsg errMsg = {'\0'};
    ERRORINFO errorInfo;
    ViSession   handle;
	VARIANT vtHandle = CA_DefaultValueVariant();
    CAObjHandle session = 0; 

       // get a reference to the session
    tsErrChk( SM_GetSession(logicalName, &session, &errorInfo));

        // get the driver handle (you don't need to release it)
    tsErrChk( SM_GetHandleEx(session, NULL, SMConst_ClassDriver,
                          &vtHandle, &errorInfo));

	CA_VariantGetLong(&vtHandle, &handle);

        // call the instrument as much as you want:
    errChk( IviDmm_ConfigureMeasurement(handle, IVIDMM_VAL_DC_VOLTS, IVIDMM_VAL_AUTO_RANGE_ON, 0.001));
        
Error:  
    SM_ReleaseSession(session);  

    // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
        {
         *errorOccurred = TRUE;
         *errorCode = error;
         strcpy(errorMsg, errMsg);
        }
}

/////////////////////////////////////////////////

    // We can get the session without a code module by using the ActiveX adapter to call
    // IInstrSessionMgr.GetInstrSession.  However, this acquires the session in the TestStand application
    // process.  In order to acquire the session in the same process as the test modules that use it, we acquire 
    // it in a test module.  This ensures that the code functions correctly if you configure the CVI Adapter
    // to execute test modules in an external process.
void __declspec(dllexport) __stdcall GetDMMSession(CAObjHandle *session,
        const char *logicalName, short *errorOccurred, long *errorCode, char errorMsg[1024])
{
    int error = 0;
    ErrMsg errMsg = {'\0'};
    ERRORINFO errorInfo;
                
    // get a reference to the session
    tsErrChk( SM_GetSession(logicalName, session, &errorInfo));
                
Error:   

    // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
        {
         *errorOccurred = TRUE;
         *errorCode = error;
         strcpy(errorMsg, errMsg);
        }        
}     
