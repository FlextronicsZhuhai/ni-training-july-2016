#include "tsapicvi.h"
#include <ansi_c.h>
#include "toolbox.h"
#include <stdtst.h>  

/********************************************************/
/*                                                      */
/*  LimitLoader.c                                       */
/*                                                      */
/*  Contains the test functions used by LimitLoader.seq */
/*  to demonstrate the LimitLoader functionality.       */
/*                                                      */
/********************************************************/

static int pumpTest;
static int valveTest;
static int tankTest;

static char message[500]; /* big because of potential long pathnames */

void GetStepLimits(CAObjHandle context, double* highLimit, double* lowLimit)
{
    ERRORINFO errorInfo;
    TS_PropertyGetValNumber (context, &errorInfo, "Step.Limits.High", 0, highLimit);
    TS_PropertyGetValNumber (context, &errorInfo, "Step.Limits.Low", 0, lowLimit);
}

void TX_TEST DLLEXPORT RandomFailSetup(tTestData *data, tTestError *err)
{
    int failArea = RAND_MAX * 0.75;
    tankTest = rand() > failArea;
    valveTest = rand() > failArea;
    pumpTest = rand() > failArea;
}

void TX_TEST DLLEXPORT TankTest(tTestData *data,tTestError *error)
{
    double lowLimit;
    double highLimit;
    error->errorFlag=FALSE;
    GetStepLimits (data->seqContextCVI, &highLimit, &lowLimit);
    if (!tankTest)
    {
        data->measurement = Random (lowLimit, highLimit);
        data->result = PASS;
    }
    else
    {
        data->measurement = Random (0, lowLimit);
        data->result = FAIL;
    }
}

void TX_TEST DLLEXPORT ValveTest(tTestData *data,tTestError *error)
{
    double lowLimit;
    double highLimit;
    error->errorFlag=FALSE;
    GetStepLimits (data->seqContextCVI, &highLimit, &lowLimit);
    if (!valveTest)
    {
        data->measurement = Random (lowLimit, highLimit);
        data->result = PASS;
    }
    else
    {
        data->measurement = Random (0, lowLimit);
        data->result = FAIL;
    }
}

void TX_TEST DLLEXPORT PumpTest(tTestData *data,tTestError *error)
{
    double lowLimit;
    double highLimit;
    error->errorFlag=FALSE;
    GetStepLimits (data->seqContextCVI, &highLimit, &lowLimit);
    if (!pumpTest)
    {
        data->measurement = Random (lowLimit, highLimit);
        data->result = PASS;
    }
    else
    {
        data->measurement = Random (0, lowLimit);
        data->result = FAIL;
    }
}
