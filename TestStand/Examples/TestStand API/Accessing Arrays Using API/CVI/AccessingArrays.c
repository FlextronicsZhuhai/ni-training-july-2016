#include "stdtst.h"
#include <analysis.h>
#include <tsutil.h>
#include <stdtst.h>
#include <formatio.h>

#define ARRAY_SIZE  3

void __declspec(dllexport) __stdcall FillLocalArray(CAObjHandle seqContextCVI, short *errorOccurred,
    long *errorCode, char errorMsg[1024])
{
    VBOOL           propertyExists;
    ERRORINFO       errorInfo;
    int             error = 0;
    VARIANT         tmpVariant;
    double *        numArray = NULL;
    size_t		    numElements = 0;
    ErrMsg          errMsg = "";
    size_t          i = 0;

    tmpVariant = CA_VariantEmpty();
    
    tsErrChk(TS_PropertyExists(seqContextCVI, &errorInfo, "Locals.NumericArray", 0, &propertyExists));
    if (propertyExists) 
        {
        
        /* Returns the value of the property specified by the lookupString parameter in a variant. Use this 
        method to get the value of an entire array at once.*/
        tsErrChk(TS_PropertyGetValVariant(seqContextCVI, &errorInfo, "Locals.NumericArray", 0, &tmpVariant));
        
        /* Use this function to obtain the number of elements in a
        one-dimensional Safe Array stored in a Variant.*/
        errChk(CA_VariantGet1DArraySize(&tmpVariant, &numElements));
        
        tsNullChk(numArray =(double*) malloc(numElements * sizeof(double))); 
        
        for (i=0; i<numElements; i++)
            numArray[i] = sin((2*3.14) * i *2/ numElements);
        
        errChk(CA_VariantClear(&tmpVariant)); 

            // Create a Safe Array from the one dimensional array passed in the Array parameter, 
            // and store the Safe Array in the VARIANT passed in the Variant parameter.     
            // You can get the array from TestStand or use malloc() to create the array
        errChk(CA_VariantSet1DArray(&tmpVariant, CAVT_DOUBLE, numElements, numArray));
        
            // Set the value of the property the lookupString parameter specifies with a variant. 
            // Use this method to set the value of an entire array at once.     
        tsErrChk(TS_PropertySetValVariant(seqContextCVI, &errorInfo, "Locals.NumericArray", 0, tmpVariant));
        }
    
Error:
    free(numArray);
    CA_VariantClear(&tmpVariant);
    
        // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
        {
        *errorOccurred = TRUE;
    
            // Set the error code and error message
        *errorCode = error;
        strcpy(errorMsg, errMsg);
        }
}


void __declspec(dllexport) __stdcall AccessLocalArray(CAObjHandle seqContextCVI, short *errorOccurred, long *errorCode, char errorMsg[1024])
{
    VBOOL           propertyExists;
    ERRORINFO       errorInfo;
    int             error = 0;
    VARIANT         tmpVariant;
    double *        numArray = NULL;
    size_t		    numElements = 0;
    ErrMsg          errMsg = "";    
    TSModalData     modalData = INITIAL_MODAL_DATA;
	CAObjHandle     engine = 0; 

    tmpVariant = CA_VariantEmpty();

    tsErrChk(TS_PropertyExists(seqContextCVI, &errorInfo, "Locals.NumericArray", 0, &propertyExists));
    if (propertyExists) 
        {
        tsErrChk(TS_PropertyGetValVariant(seqContextCVI, &errorInfo, "Locals.NumericArray", 0, &tmpVariant));
        
            // Convert the one-dimensional Safe Array passed in the Variant parameter   
            // into a dynamically allocated C-style array.  
        errChk(CA_VariantGet1DArray(&tmpVariant, CAVT_DOUBLE, &numArray, &numElements));
        
		tsErrChk(TS_SeqContextGetEngine(seqContextCVI, &errorInfo, &engine))
		
        tsErrChk(TS_StartModalDialog(engine, &errorInfo, &modalData));
        
        errChk(YGraphPopup("Data in TestStand Local Variable", numArray, numElements, VAL_DOUBLE));
        }
        
Error:
    TS_EndModalDialog(&errorInfo, &modalData);
    
        // Free the allocated array 
    CA_FreeMemory(numArray);
    CA_VariantClear(&tmpVariant);

        // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
        {
        *errorOccurred = TRUE;
        
            // Set the error code and message
        *errorCode = error;
        strcpy(errorMsg, errMsg);
        }
}




void __declspec(dllexport) __stdcall Create2DArray(CAObjHandle seqContextCVI,
        short *errorOccurred, long *errorCode, char errorMsg[1024])
{
    int         error = 0;
    ErrMsg      errMsg = {'\0'};
    ERRORINFO   errorInfo;
    double      array2D[2][100] = {0};
    VARIANT     tmpVariant;
    int         i;


        // To dynamically create variables, you would normally use the InsertIfMissing 
        // Property Option.  In TestStand 1.0 and 1.0.1, the InsertIfMissing option does 
        // not work with arrays.
        // This example demonstrates how to create an array using NewSubProperty
    tsErrChk(TS_PropertyNewSubProperty (seqContextCVI, &errorInfo, 
                              "Locals.Array2D", TS_PropValType_Number, VTRUE, "", 0));

        // You do not need to do a TS_PropertySetDimension as TS_PropertySetValVariant 
        //auto dimensions the property object to be atleast as big as the safe array
        //tsErrChk(TS_PropertySetDimensions (seqContextCVI, &errorInfo,
        //                     "Locals.Array2D", 0, "[0][0]", "[1][99]"));
    
    for (i=0; i<100; i++)
        {
        array2D[0][i] = sin((2*3.14) * i / 100);
        array2D[1][i] = cos((2*3.14) * i / 100);
        }

        // Create a Safe Array from the two dimensional array passed in the Array parameter,   
        // and stores the Safe Array in the VARIANT passed in the Variant parameter.
    errChk(CA_VariantSet2DArray (&tmpVariant, CAVT_DOUBLE, 2, 100, array2D));
        
        // Set the value of the property the lookupString parameter specifies with a variant.  
        // Use this method to set the value of an entire array at once.                         
    tsErrChk(TS_PropertySetValVariant(seqContextCVI, &errorInfo, "Locals.Array2D", 0, tmpVariant));
        
Error:  
    // FREE RESOURCES
    CA_VariantClear(&tmpVariant);
    
    // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
        {
        *errorOccurred = TRUE;
        *errorCode = error;
        strcpy(errorMsg, errMsg);
        }
    return;    
}


void __declspec(dllexport) __stdcall Access2DArray(CAObjHandle seqContextCVI, 
                   short *errorOccurred, long *errorCode, char errorMsg[1024])
{
    VBOOL           propertyExists;
    ERRORINFO       errorInfo;
    int             error = 0;
    VARIANT         tmpVariant;
    double *        numArray = NULL;
    size_t		    FirstDimSize = 0, SecondDimSize = 0;
    ErrMsg          errMsg = "";
    TSModalData     modalData = INITIAL_MODAL_DATA;
    CAObjHandle     engine = 0;
    size_t          i = 0;
    


    tmpVariant = CA_VariantEmpty();

    tsErrChk(TS_PropertyExists(seqContextCVI, &errorInfo, "Locals.Array2D", 0, &propertyExists));
    if (propertyExists) 
        {
        tsErrChk(TS_PropertyGetValVariant(seqContextCVI, &errorInfo, "Locals.Array2D", 0, &tmpVariant));
        
            // Convert the two-dimensional Safe Array passed in the Variant parameter   
            // into a dynamically allocated C-style array.      
        errChk(CA_VariantGet2DArray(&tmpVariant, CAVT_DOUBLE, &numArray, &FirstDimSize, &SecondDimSize));
        
        
        tsErrChk(TS_SeqContextGetEngine(seqContextCVI, &errorInfo, &engine));
                    
            // Display YGraphPopup as a modal dialog                    
        tsErrChk(TS_StartModalDialog(engine, &errorInfo, &modalData));
        
            // Remove comments to display waveforms
        for (i=0; i< FirstDimSize; i++)
            errChk(YGraphPopup((i? "Data in TestStand Local Variable(2nd column)":"Data in TestStand Local Variable(1st column)"), &numArray[i*SecondDimSize], SecondDimSize, VAL_DOUBLE));
        
        }

Error:
    TS_EndModalDialog(&errorInfo, &modalData);
    
    if(engine)
        CA_DiscardObjHandle(engine);
    
    CA_FreeMemory(numArray);
    CA_VariantClear(&tmpVariant);
        
    // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
        {
        *errorOccurred = TRUE;
        *errorCode = error;
        strcpy(errorMsg, errMsg);
        }
    return;    
}

void __declspec(dllexport) __stdcall SetStringArray(CAObjHandle seqContextCVI, 
                   short *errorOccurred, long *errorCode, char errorMsg[1024])
{

    VARIANT     tmpVariant;
    int         error = 0;
    ErrMsg      errMsg = {'\0'};
    ERRORINFO   errorInfo;
    char        *strArray[ARRAY_SIZE] = {0};
    int		    i;

    tmpVariant = CA_VariantEmpty();
    
    for (i=0; i<ARRAY_SIZE; i++)
        {
        strArray[i] = (char*)malloc(sizeof(char)*128);
        sprintf(strArray[i], "String%d", i);
        }

    errChk( CA_VariantSet1DArray (&tmpVariant, CAVT_CSTRING, ARRAY_SIZE, strArray));
        
    tsErrChk( TS_PropertySetValVariant(seqContextCVI, &errorInfo, "Locals.StringArray", 0, tmpVariant));
    
Error:  
    // FREE RESOURCES
    CA_VariantClear(&tmpVariant);
    
    for (i=0; i<ARRAY_SIZE; i++)
        free(strArray[i]);

    // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
        {
        *errorOccurred = TRUE;
        *errorCode = error;
        strcpy(errorMsg, errMsg);
        }
    return;    
}


void __declspec(dllexport) __stdcall GetStringArray(CAObjHandle seqContextCVI, 
                   short *errorOccurred, long *errorCode, char errorMsg[1024])
{
    VBOOL           propertyExists = VFALSE;
    VARIANT         tmpVariant;
    int             error = 0;
    ErrMsg          errMsg = {'\0'};
    ERRORINFO       errorInfo;
    int             i;
    size_t		    numElements = 0;
    char            **strArray = NULL;
    char            displayString[1024];
    TSModalData     modalData = INITIAL_MODAL_DATA;
    CAObjHandle     engine = 0;

        
    tmpVariant = CA_VariantEmpty();
    
    tsErrChk(TS_PropertyExists(seqContextCVI, &errorInfo, "Locals.StringArray", 0, &propertyExists));
    if (propertyExists) 
        {
        tsErrChk(TS_PropertyGetValVariant(seqContextCVI, &errorInfo, "Locals.StringArray", 0, &tmpVariant));
        
            // Convert the one-dimensional Safe Array passed in the Variant parameter   
            // into a dynamically allocated C-style array.      
        errChk(CA_VariantGet1DArray (&tmpVariant, CAVT_CSTRING, &strArray, &numElements));

        sprintf(displayString, "%s\n%s\n%s", strArray[0], strArray[1], strArray[2]);
            
        tsErrChk(TS_SeqContextGetEngine(seqContextCVI, &errorInfo, &engine));
        
            // Display MessagePopup as a modal dialog                    
        tsErrChk(TS_StartModalDialog(engine, &errorInfo, &modalData));

        errChk(MessagePopup("String Array from TestStand Local Variable", displayString));
        }

Error:  
    // FREE RESOURCES
    TS_EndModalDialog(&errorInfo, &modalData);
    
    if(engine)
        CA_DiscardObjHandle(engine);

    CA_VariantClear(&tmpVariant);

    if (strArray)
        CA_FreeMemory(strArray);
    
    // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
        {
        *errorOccurred = TRUE;
        *errorCode = error;
        strcpy(errorMsg, errMsg);
        }
    return;    
}
