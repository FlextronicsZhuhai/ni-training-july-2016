#include "tsutil.h"

#define ERROR_MESSAGE_SIZE 1024

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//	This function creates a new PropertyObject using the NewPropertyObject() method and then inserts it as a Local
//  variable with the name "MyString".
//
void __declspec(dllexport) __stdcall CreateNewPropertyObject(CAObjHandle seqContextCVI,
		char reportText[1024], short *errorOccurred, long *errorCode, char errorMsg[ERROR_MESSAGE_SIZE])
{
	CAObjHandle engineHandle = 0;
	CAObjHandle localsHandle = 0;
	TSObj_Property newPropertyObject = 0;
	
	int error = 0;
	ErrMsg errMsg = {'\0'};
	ERRORINFO errorInfo;
	
	// Get the engine handle.
	tsErrChk (TS_SeqContextGetEngine (seqContextCVI, &errorInfo, &engineHandle));
	
	// Get the locals handle.
	tsErrChk (TS_SeqContextGetLocals (seqContextCVI, &errorInfo, &localsHandle));

	// Create a new PropertyObject.
	tsErrChk (TS_EngineNewPropertyObject (engineHandle, &errorInfo,TS_PropValType_String, VFALSE, "", 0,&newPropertyObject));
	
	// Set the name of the new PropertyObject.	
	tsErrChk (TS_PropertySetName (newPropertyObject, &errorInfo, "MyString"));
	
	// Insert Property into Locals.	
	tsErrChk (TS_PropertyInsertSubProperty (localsHandle, &errorInfo, "", 0, 0,newPropertyObject));
	
	// Assign Value to Property.	
	tsErrChk (TS_PropertySetValString (localsHandle, &errorInfo, "MyString", 0,"New PropertyObject"));
	
	

Error:
	// FREE RESOURCES
	CA_DiscardObjHandle(newPropertyObject);
	CA_DiscardObjHandle(localsHandle);
	CA_DiscardObjHandle(engineHandle);

	// If an error occurred, set the error flag to cause a run-time error in TestStand.
	if (error < 0)
	{
		*errorOccurred = TRUE;

		// SET THE ERROR CODE AND STRING
		*errorCode = error;
		strcpy(errorMsg, errMsg);
	}
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//	This function creates a new PropertyObject using the SetValString(), SetValNumber(), and SetValBoolean() methods.
//
void __declspec(dllexport) __stdcall SetValMethods(CAObjHandle seqContextCVI,
		char reportText[1024], short *errorOccurred, long *errorCode, char errorMsg[ERROR_MESSAGE_SIZE])
{
	CAObjHandle sequenceHandle = 0;
	CAObjHandle asPropertyObject = 0;
	
	int error = 0;
	ErrMsg errMsg = {'\0'};
	ERRORINFO errorInfo;
	

	// Get the sequence handle.
	tsErrChk (TS_SeqContextGetSequence (seqContextCVI, &errorInfo, &sequenceHandle));
	
	// Get a reference for the sequence AsPropertyObject.
	tsErrChk (TS_SequenceAsPropertyObject (sequenceHandle, NULL, &asPropertyObject));

	// Create a new PropertyObject with the SetValString() method and store it as a Local variable.  Option 0x1 inserts the property if it does not exist. 
	tsErrChk (TS_PropertySetValString (asPropertyObject, &errorInfo,"Locals.MyString", TS_PropOption_InsertIfMissing, "Using SetValString"));
	
	// Create a new PropertyObject with the SetValNumber() method and store it as a Local Variable.
	tsErrChk (TS_PropertySetValNumber (asPropertyObject, &errorInfo,"Locals.MyNumber", TS_PropOption_InsertIfMissing, 5));
	
	// Create a new PropertyObject with the SetValBoolean() method and store it as a Local Variable. 
	tsErrChk (TS_PropertySetValBoolean (asPropertyObject, &errorInfo,"Locals.MyBoolean", TS_PropOption_InsertIfMissing, VTRUE));

	
Error:
	// FREE RESOURCES
	CA_DiscardObjHandle(asPropertyObject);
	CA_DiscardObjHandle(sequenceHandle);

	// If an error occurred, set the error flag to cause a run-time error in TestStand.
	if (error < 0)
	{
		*errorOccurred = TRUE;

		// SET THE ERROR CODE AND STRING
		*errorCode = error;
		strncpy(errorMsg, errMsg, ERROR_MESSAGE_SIZE);
		errorMsg[ERROR_MESSAGE_SIZE-1] = 0;
	}
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//	This function creates a new complex PropertyObject container as a Local variable and the fields are added using the
//  NewSubProperty methods.
//
void __declspec(dllexport) __stdcall CreateNewContainer(CAObjHandle seqContextCVI,
		char reportText[1024], short *errorOccurred, long *errorCode, char errorMsg[ERROR_MESSAGE_SIZE])
{
	CAObjHandle localsHandle = 0;
	TSObj_Property propertyObject = 0;
	VARIANT arrayVariant = CA_VariantEmpty ();
	double arrayData[] = {0,1,2,3,4,5};
	
	
	int error = 0;
	ErrMsg errMsg = {'\0'};
	ERRORINFO errorInfo;
	

	// Get the Locals handle.
	tsErrChk (TS_SeqContextGetLocals (seqContextCVI, &errorInfo, &localsHandle));
	
	// Create a container called ComplexContainer with a field called String.	
	tsErrChk (TS_PropertySetValString (localsHandle, &errorInfo,"ComplexContainer.String", TS_PropOption_InsertIfMissing,"This is a String"));

	// Since "Error" is a defined type in TestStand, an instance of it can be created by inserting a subproperty with the NamedType value type.
	tsErrChk (TS_PropertyNewSubProperty (localsHandle, &errorInfo,"ComplexContainer.Error",TS_PropValType_NamedType, VFALSE, "Error",0));
	
	// Create a new subproperty as an array.
	tsErrChk (TS_PropertyNewSubProperty (localsHandle, &errorInfo,"ComplexContainer.Array",TS_PropValType_Number, VTRUE, "Array", 0));
	
	// Get the PropertyObject handle for the array.
	tsErrChk (TS_PropertyGetPropertyObject (localsHandle, &errorInfo,"ComplexContainer.Array", 0,&propertyObject));	
	
	// Convert the arrayData to a variant.
	CA_VariantSet1DArray (&arrayVariant, CAVT_DOUBLE, 6, arrayData);
	
	
	//SetValVariant() can assign a value to an array and will resize the array as needed.  However, the array must be initially created with NewSubProperty() as shown previously.
	tsErrChk (TS_PropertySetValVariant (localsHandle, &errorInfo,"ComplexContainer.Array", 0, arrayVariant));
	

Error:
	// FREE RESOURCES
	CA_VariantClear(&arrayVariant);
	CA_DiscardObjHandle(propertyObject);
	CA_DiscardObjHandle(localsHandle);

	// If an error occurred, set the error flag to cause a run-time error in TestStand.
	if (error < 0)
	{
		*errorOccurred = TRUE;

		// SET THE ERROR CODE AND STRING
		*errorCode = error;
		strncpy(errorMsg, errMsg, ERROR_MESSAGE_SIZE);
		errorMsg[ERROR_MESSAGE_SIZE-1] = 0;
	}
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//	This function creates a new complex PropertyObject container as a Local variable and the fields are added using the
//  NewSubProperty methods.
//
void __declspec(dllexport) __stdcall CreatePropertyObjectInResultContainer(CAObjHandle seqContextCVI,
		char reportText[1024], short *errorOccurred, long *errorCode, char errorMsg[ERROR_MESSAGE_SIZE])
{
	CAObjHandle stepHandle = 0;
	TSObj_Property asPropertyObject = 0;
	
	int error = 0;
	ErrMsg errMsg = {'\0'};
	ERRORINFO errorInfo;
	

	// Get the step handle.
	tsErrChk (TS_SeqContextGetStep (seqContextCVI, &errorInfo, &stepHandle));
	
	// Get a reference for the step AsPropertyObject.	
	tsErrChk (TS_StepAsPropertyObject (stepHandle, &errorInfo, &asPropertyObject));
	
	// Create a container called SpecialResults in Results and create a field called String.
	tsErrChk (TS_PropertySetValString (asPropertyObject, &errorInfo, "Result.SpecialResults.String",
									   TS_PropOption_InsertIfMissing,"This is an extra result added to the report"));
	// Create a field called Number in SpecialResults.
	tsErrChk (TS_PropertySetValNumber (asPropertyObject, &errorInfo,"Result.SpecialResults.Number", TS_PropOption_InsertIfMissing, 10));

	// Set TS_PropFlags_IncludeInReport flag to specify to include the SpecialReults in the report.
	tsErrChk (TS_PropertySetFlags (asPropertyObject, &errorInfo,"Result.SpecialResults", 0, TS_PropFlags_IncludeInReport));
	
	

Error:
	// FREE RESOURCES
	CA_DiscardObjHandle(asPropertyObject);
	CA_DiscardObjHandle(stepHandle);

	// If an error occurred, set the error flag to cause a run-time error in TestStand.
	if (error < 0)
	{
		*errorOccurred = TRUE;

		// SET THE ERROR CODE AND STRING
		*errorCode = error;
		strncpy(errorMsg, errMsg, ERROR_MESSAGE_SIZE);
		errorMsg[ERROR_MESSAGE_SIZE-1] = 0;
	}
}
