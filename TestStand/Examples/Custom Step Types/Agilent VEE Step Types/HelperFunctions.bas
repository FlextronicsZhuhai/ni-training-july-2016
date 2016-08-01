Attribute VB_Name = "HelperFunctions"
' This function is required to determine if the argument arrays are empty
' UBound will return an error if the UBound < 0

Public Function UUBound(a As Variant) As Long
    On Error Resume Next
    Dim size As Long
    size = UBound(a)
    If Err = 9 Then
        UUBound = -1
    Else
        UUBound = size
    End If
End Function

Public Function DestroyVariables()

    Set gSeqContext = Nothing
    Set gSeqContextPropObj = Nothing
    Set gEngine = Nothing
    Set gCurrSelectedFunc = Nothing
    Set gVEEServer = Nothing
    Set gVEELib = Nothing
    
    ' Free arrays
    Erase gInputArgs
    Erase gOutputArgs

End Function
