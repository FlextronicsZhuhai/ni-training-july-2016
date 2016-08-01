Attribute VB_Name = "EditModuleFunctions"
Public Function DisplayExpBrowser(ExpText As String) As String
    
    Dim SelStart As Long
    Dim SelEnd As Long
    Dim selectedExpression As String
    Dim selectedOK As Boolean
        
    selectedOK = gEngine.DisplayBrowseExprDialogEx("Select value expression", _
                                gSeqContext, ExpText, 0, 0, "", 0, _
                                selectedExpression, SelStart, SelEnd)
    
    If selectedOK = True Then
        DisplayExpBrowser = selectedExpression
    Else
        DisplayExpBrowser = ExpText
    End If
          
End Function
Public Function UpdateFunctionList(mVEELib As Library)

    Dim numFunc As Integer
    Dim funcNames() As String
    Dim i As Integer

    ' Get number of VEE functions in Library
    numFunc = mVEELib.UserFunctions.Count
    ' Correct for zero-based combo box
    numFunc = numFunc - 1

    ReDim funcNames(numFunc)
    ' Clear all items out of combo box
    EditModule.VEEFunction.Clear
       
    ' Add function names to combobox
    i = 0
    Do While i <= numFunc
        funcNames(i) = mVEELib.UserFunctions.Item(i).Name
        EditModule.VEEFunction.AddItem funcNames(i), i
        i = i + 1
    Loop
    
End Function
Public Function UpdateArgs(mFunc As UserFunction, isInput As Boolean, isOutput As Boolean)
    
    Dim i As Integer
    Dim numOutArgs As Integer
    Dim numInArgs As Integer
    Dim argName As String
    Dim VEEDataType As Integer
    
    ' Clear Lists and controls
    EditModule.InputArgList.Clear
    EditModule.InputExp.Text = ""
    EditModule.InputType.Text = ""
    EditModule.OutputArgList.Clear
    EditModule.OutputExp.Text = ""
    
    numOutArgs = mFunc.OutputArguments.Count
    numInArgs = mFunc.InputArguments.Count
    
    ' Check to see if there are input args to load
    If numInArgs > 0 And isInput Then
        ' Account for zero based combo box
        numInArgs = numInArgs - 1
        ReDim gInputArgs(numInArgs, 2)
        
        ' Load arguments into combo box
        i = 0
        Do While i <= numInArgs
            argName = mFunc.InputArguments.Item(i).Name
            EditModule.InputArgList.AddItem argName, i
            gInputArgs(i, 0) = argName
            VEEDataType = mFunc.InputArguments.Item(i).DataType
            gInputArgs(i, 2) = ConvertVEEDataType(VEEDataType)
            i = i + 1
        Loop
       
        ' Set Active Controls on dialog
        EditModule.InputArgList.Text = gInputArgs(0, 0)
        EditModule.InputType.Text = gInputArgs(0, 2)
    Else
        Erase gInputArgs
    End If
    
    ' Check to see if there are output args to load
    If numOutArgs > 0 And isOutput Then
        ' Account for zero based combo box
        numOutArgs = numOutArgs - 1
        ReDim gOutputArgs(numOutArgs, 1)
        
        ' Load arguments into combo box
        i = 0
        Do While i <= numOutArgs
            argName = mFunc.OutputArguments.Item(i).Name
            EditModule.OutputArgList.AddItem argName, i
            gOutputArgs(i, 0) = argName
            i = i + 1
        Loop
    
        ' Set Active Controls on dialog
        EditModule.OutputArgList.Text = gOutputArgs(0, 0)
    Else
        Erase gOutputArgs
    End If

End Function

Public Function LoadInOutValsFromTS(mFunc As UserFunction)

    Dim sizeOfTSInput As Integer
    Dim sizeOfTSOutput As Integer
    Dim numVEEInputs As Integer
    Dim numVEEOutputs As Integer
      
    ' Get size of input and output arrays from TestStand divide by numbre of dimensions
    sizeOfTSInput = (gSeqContextPropObj.GetPropertyObject("Step.Result.Input", 0).GetNumElements) / 3
    sizeOfTSOutput = (gSeqContextPropObj.GetPropertyObject("Step.Result.Output", 0).GetNumElements) / 2
    
    ' Get the number of VEE inputs and outputs
    numVEEInputs = mFunc.InputArguments.Count
    numVEEOutputs = mFunc.OutputArguments.Count
    
    ' Compare the TS values and VEE input values subtract 1 for zero based Arg array index
    If numVEEInputs > 0 Or sizeOfTSInput > 0 Then
        CompareVals numVEEInputs - 1, sizeOfTSInput - 1, mFunc, "Input"
    Else
        Erase gInputArgs
    End If
    If numVEEOutputs > 0 Or sizeOfTSOutput > 0 Then
        CompareVals numVEEOutputs - 1, sizeOfTSOutput - 1, mFunc, "Output"
    Else
        Erase gOutputArgs
    End If
    
End Function

Private Sub CompareVals(numVEE As Integer, numTS As Integer, mFunc As UserFunction, Directn As String)
    
    Dim MsgResult As VBA.VbMsgBoxResult
    Dim Msg As String
        
    If numVEE <> numTS Then
        ' Ask the user what they want to do with the existing parameter info
        Msg = "There is a variation with the number of " & Directn & " and those assigned." _
                & vbNewLine & "Do you want to reload?"
        MsgResult = MsgBox(Msg, vbYesNoCancel, "VEE Conflict")
        
        ' Handle user selection
        Select Case (MsgResult)
            Case vbYes
                ' Discard stored values and update args
                If Directn = "Input" Then
                    ReDim gInputArgs(numVEE, 2)
                    UpdateArgs mFunc, True, False
                Else
                    ReDim gOutputArgs(numVEE, 1)
                    UpdateArgs mFunc, False, True
                End If
            
            Case vbNo
                ' Keep data and load all present arguments from function
                If Directn = "Input" Then
                    ReDim gInputArgs(numTS, 2)
                    ReadTSValues gInputArgs, "Input", numTS
                Else
                    ReDim gOutputArgs(numTS, 1)
                    ReadTSValues gOutputArgs, "Output", numTS
                End If
                
            Case vbCancel
                ' Goto end of FormLoad
                ' GoTo clearERR
        
        End Select
    
    Else
        If Directn = "Input" Then
            ReDim gInputArgs(numTS, 2)
            ReadTSValues gInputArgs, "Input", numTS
        Else
            ReDim gOutputArgs(numTS, 1)
            ReadTSValues gOutputArgs, "Output", numTS
        End If
    End If

End Sub

Private Sub ReadTSValues(ArgArray() As Variant, Directn As String, numIterations As Integer)
    
    Dim i As Integer
        
    Do While i <= numIterations
        ' Load Argument
        ArgArray(i, 0) = gSeqContextPropObj.GetValVariant("Step.Result." + Directn + "[" + _
                                                        Str(i) + "][0]", 0)
        ' Add items to combo box on panel
        If Directn = "Input" Then
            EditModule.InputArgList.AddItem ArgArray(i, 0), i
        Else
            EditModule.OutputArgList.AddItem ArgArray(i, 0), i
        End If
        
        ' Load Expression
        ArgArray(i, 1) = gSeqContextPropObj.GetValVariant("Step.Result." + Directn + "[" + _
                                                        Str(i) + "][1]", 0)
        ' Type is only valid for input argument
        If Directn = "Input" Then
            ' Load Type
            ArgArray(i, 2) = gSeqContextPropObj.GetValVariant("Step.Result." + Directn + "[" _
                                                            + Str(i) + "][2]", 0)
        End If
        i = i + 1
    Loop

End Sub

Private Function ConvertVEEDataType(enumVal As Integer) As String

    Dim retVal As String
    
    Select Case (enumVal)
        Case 0:
            retVal = "Any"
        Case 1:
            retVal = "U Int16"
        Case 2:
            retVal = "U Int32"
        Case 3:
            retVal = "Real 32"
        Case 4:
            retVal = "Real 64"
        Case 5:
            retVal = "Complex"
        Case 6:
            retVal = "PComplex"
        Case 7:
            retVal = "Text"
        Case 10:
            retVal = "Cord"
        Case 12:
            retVal = "Record"
        Case 14:
            retVal = "Waveform"
        Case 15:
            retVal = "Spectrum"
        Case 18:
            retVal = "U Int8"
        Case Else:
            retVal = "Undetermined Type"
    End Select

    ConvertVEEDataType = retVal

End Function

Public Sub DimControls(OnOff As Boolean, Directn As String)

    If Directn = "Input" Then
        EditModule.InputArgList.Enabled = OnOff
        EditModule.InputExp.Enabled = OnOff
        EditModule.InputType.Enabled = OnOff
        EditModule.BrowseInExp.Enabled = OnOff
        
    Else ' Ouput
        EditModule.OutputArgList.Enabled = OnOff
        EditModule.OutputExp.Enabled = OnOff
        EditModule.BrowseOutExp.Enabled = OnOff
    End If

End Sub
