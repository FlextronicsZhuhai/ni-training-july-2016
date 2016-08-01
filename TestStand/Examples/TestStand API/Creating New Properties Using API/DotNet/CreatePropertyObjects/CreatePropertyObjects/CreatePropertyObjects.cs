using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NationalInstruments.TestStand.Interop.API;    // TestStand Core API.  Add <TestStand>\API\DotNet\Assemblies\CurrentVersion\NationalInstruments.TestStand.Interop.API.dll to the project as a reference.
using System.Runtime.InteropServices;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Title:       CreatePropertyObjects.cs
//
// Description: This file holds the four methods used in the "Creating New Properties Using API.seq"
//              example.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


namespace CreatePropertyObjects
{
    public class TestStandSequenceCalls
    {

        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        //
        //	This method creates a new PropertyObject using the NewPropertyObject() method that is then inserted as a Local
        //  variable with the name "MyString".
        //
        public void CreateNewPropertyObject(SequenceContext seqContext, out bool errorOccurred, out int errorCode, out String errorMsg)
        {
            errorOccurred = false;
            errorCode = 0;
            errorMsg = String.Empty;

            try
            {
                // Create a new PropertyObject and store it.
                PropertyObject temperaryObjectReference = seqContext.Engine.NewPropertyObject(PropertyValueTypes.PropValType_String, false, "", 0);
                temperaryObjectReference.Name = "MyString";
                
                // Insert Property into Locals.
                seqContext.Locals.InsertSubProperty("", 0, 0, temperaryObjectReference);

                // Assign Value to Property.
                seqContext.Locals.SetValString("MyString", 0, "New PropertyObject");

            }
            catch (COMException e)
            {
                errorOccurred = true;
                errorMsg = e.Message;
                errorCode = e.ErrorCode;
            }
        }

        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        //
        //	This method creates a new PropertyObject using the SetValString(), SetValNumber(), and SetValBoolean() methods.
        //
        public void SetValMethods(SequenceContext seqContext, out bool errorOccurred, out int errorCode, out String errorMsg)
        {
            errorOccurred = false;
            errorCode = 0;
            errorMsg = String.Empty;

            try
            {
                // Create a new propertyObject with the SetValString() method and store it as a Local variable.
				// Option "PropertyOptions.PropOption_InsertIfMissing" inserts the property if it does not exist.
                PropertyObject sequencePropertyObject = seqContext.Sequence.AsPropertyObject();
                sequencePropertyObject.SetValString("Locals.MyString", PropertyOptions.PropOption_InsertIfMissing, "Using SetValString");

                // Create a new PropertyObject with the SetValNumber() method and store it as a Local variable.
				sequencePropertyObject.SetValNumber("Locals.MyNumber", PropertyOptions.PropOption_InsertIfMissing, 5);

                //  Create a new PropertyObject with the SetValBoolean() method and store it as a Local variable.
				sequencePropertyObject.SetValBoolean("Locals.MyBoolean", PropertyOptions.PropOption_InsertIfMissing, true);

            }
            catch (COMException e)
            {
                errorOccurred = true;
                errorMsg = e.Message;
                errorCode = e.ErrorCode;
            }
        }
       
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        //
        //	This method creates a new complex PropertyObject container as a Local variable and the fields are added using the
        //  NewSubProperty() method.
        //
        public void CreateNewContainer(SequenceContext seqContext, out bool errorOccurred, out int errorCode, out String errorMsg)
        {
            errorOccurred = false;
            errorCode = 0;
            errorMsg = String.Empty;

            try
            {
                // Create a container called ComplexContainer with a field called String.
				seqContext.Locals.SetValString("ComplexContainer.String", PropertyOptions.PropOption_InsertIfMissing, "This is a string");

                // Since "Error" is a defined type in TestStand, an instance of it can be created by inserting a subproperty with the NamedType value type. 
                seqContext.Locals.NewSubProperty("ComplexContainer.Error", PropertyValueTypes.PropValType_NamedType, false, "Error", 0);

                // Create a new subproperty as an array.
                seqContext.Locals.NewSubProperty("ComplexContainer.Array", PropertyValueTypes.PropValType_Number, true, "Array", 0);

                // Set ValVariant can assign a value to an array and will resize the array as needed.  However, the array must be initially created with 
                // NewSubProperty() as shown previously.
                double[] array1 = new double[] {0,1,2,3,4,5};
                seqContext.Locals.SetValVariant("ComplexContainer.Array", 0, array1);

            }
            catch (COMException e)
            {
                errorOccurred = true;
                errorMsg = e.Message;
                errorCode = e.ErrorCode;
            }
        }

        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        //
        //	This method creates a new complex PropertyObject container as a Local variable and the fields are added using the
        //  NewSubProperty methods.
        //
        public void InsertPropertyObjectIntoStepResults(SequenceContext seqContext, out bool errorOccurred, out int errorCode, out String errorMsg)
        {
            errorOccurred = false;
            errorCode = 0;
            errorMsg = String.Empty;

            try
            {
                // Set the string and number special result.
                PropertyObject stepPropertyObject = seqContext.Step.AsPropertyObject();
				stepPropertyObject.SetValString("Result.SpecialResults.String", PropertyOptions.PropOption_InsertIfMissing, "This is an extra result added to the report");
				stepPropertyObject.SetValNumber("Result.SpecialResults.Number", PropertyOptions.PropOption_InsertIfMissing, 10);
                
                // Set PropFlags_IncludeInReport flag to specify to include this property in the report.
                stepPropertyObject.SetFlags("Result.SpecialResults", 0,  PropertyFlags.PropFlags_IncludeInReport);

            }
            catch (COMException e)
            {
                errorOccurred = true;
                errorMsg = e.Message;
                errorCode = e.ErrorCode;
            }
        }
    }
}
