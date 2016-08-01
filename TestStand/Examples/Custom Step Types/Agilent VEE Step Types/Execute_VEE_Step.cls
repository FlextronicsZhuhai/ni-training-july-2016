VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Execute_VEE_Step"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Public Function Execute_VEE_Step(SeqContext As SequenceContext, FilePath As String, FuncName As String, Veedbg As Boolean) As Integer

    Dim i, j As Integer
    Dim inputArray() As Variant
    Dim outputArray() As Variant
    Dim OutputExp() As Variant
    Dim numInputs, numOutputs As Integer
    Dim sizeOfTSInputs, sizeOfTSOutputs As Integer
    Dim VEEInputArray(), VEEOutputArray() As Variant
    Dim TSOutputArray() As Variant
    Dim absPath As String
    Dim foundIt, cancelled As Boolean
               
    ' Initalize Variables
    i = 0
    j = 0
    
    Set gEngine = SeqContext.Engine
        
    ' Find the file specified in FilePath variable
    foundIt = gEngine.FindFile(FilePath, absPath, cancelled, , , , SeqContext.SequenceFile)
    
    If foundIt = True Then
    
        Set gSeqContextPropObj = SeqContext.AsPropertyObject
        Set gVEEServer = New CallServer
    
        ' Set debug option
        gVEEServer.Debug = Veedbg
        
        Set gVEELib = gVEEServer.Libraries.Load(absPath)
        Set gCurrSelectedFunc = gVEELib.UserFunctions.Item(FuncName)
        
        ' Get the number of inputs and outputs from the VEE server
        numInputs = gCurrSelectedFunc.InputArguments.Count - 1
        numOutputs = gCurrSelectedFunc.OutputArguments.Count - 1
        
        sizeOfTSOutputs = (gSeqContextPropObj.GetPropertyObject("Step.Result.Output", 0).GetNumElements) / 2
    
        ' If we have inputs then we must create an array with them to pass to the VEE Function
        If numInputs >= 0 Then
            ReDim VEEInputArray(numInputs) As Variant
            Do While i <= numInputs
                VEEInputArray(i) = gSeqContextPropObj.Evaluate(gSeqContextPropObj.GetValVariant("Step.Result.Input[" + Str(i) + "][1]", 0))
                i = i + 1
            Loop
        End If
        
        ' If we have outputs then we must create an array with them to pass to the VEE Function
        If numOutputs >= 0 Then
            ReDim VEEOutputArray(numOutputs) As Variant
        End If
    
        ' We have both inputs and outputs
        If numInputs >= 0 And numOutputs >= 0 Then
            gCurrSelectedFunc.Call VEEInputArray, VEEOutputArray
        ' We have no inputs only outputs
        ElseIf numInputs < 0 And numOuputs >= 0 Then
            gCurrSelectedFunc.Call , VEEOutputArray
        ' We have no outputs, just inputs
        ElseIf numInputs >= 0 And numOutputs < 0 Then
            gCurrSelectedFunc.Call VEEInputArray
        ' We have no inputs or outputs
        Else
            gCurrSelectedFunc.Call
        End If
    
        If numOutputs >= 0 Then
            
            ReDim TSOutputArray(numOutputs)
            Do While j <= numOutputs
                TSOutputArray(j) = gSeqContextPropObj.GetValVariant("Step.Result.Output[" + Str(j) + "][1]", 0)
                If TSOutputArray(j) <> "" Then
                    gSeqContextPropObj.SetValVariant TSOutputArray(j), 0, VEEOutputArray(j)
                End If
            j = j + 1
            Loop
        End If
    Else
        MsgBox "Unable to find file " + FilePath
    End If
    
ErrorHandler:
  
    HelperFunctions.DestroyVariables
    Err.Clear

End Function



