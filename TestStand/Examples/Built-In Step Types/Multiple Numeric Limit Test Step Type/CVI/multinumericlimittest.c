#include "stdtst.h"
#include "tsutil.h"

void __declspec(dllexport) TX_TEST multinumericlimittest1(CAObjHandle sequenceContext, short *errorOccured, long *errorCode)
{
    double tempReading = 0;
    int error = 0;
    ErrMsg errMsg = {'\0'};
    ERRORINFO errorInfo;
    
    // Obtain Voltage 0
    tempReading = Random (3, 5);
    tsErrChk (TS_PropertySetValNumber (sequenceContext, &errorInfo, "Step.NumericArray[0]", 0, tempReading));
                             
    // Obtain Voltage 1
    tempReading = Random (3, 5);
    tsErrChk (TS_PropertySetValNumber (sequenceContext, &errorInfo, "Step.NumericArray[1]", 0, tempReading));
    
    // Obtain Frequency
    tempReading = Random (110, 125);
    tsErrChk (TS_PropertySetValNumber (sequenceContext, &errorInfo, "Step.NumericArray[2]", 0, tempReading));

    // Obtain RMS 
    tempReading = Random (0.5, 1);
    tsErrChk (TS_PropertySetValNumber (sequenceContext, &errorInfo, "Step.NumericArray[3]", 0, tempReading));
    
 
  Error:  
    // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
    {
        *errorOccured = TRUE;
        *errorCode = error;
    }
    
    return;    
}

void __declspec(dllexport) TX_TEST multinumericlimittest2(double measurements[4], short *errorOccured, long *errorCode)
{
    int error = 0;
    ErrMsg errMsg = {'\0'};
    ERRORINFO errorInfo;
    
    // Obtain Voltage 0
    measurements[0] = Random (3, 5);
                             
    // Obtain Voltage 1
    measurements[1] = Random (3, 5);
    
    // Obtain Frequency
    measurements[2] = Random (110, 125);

    // Obtain RMS 
    measurements[3] = Random (0.5, 1);
    

  Error:
    
    // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
    {
        *errorOccured = TRUE;
        *errorCode = error;
    }
    
    return;    
}
