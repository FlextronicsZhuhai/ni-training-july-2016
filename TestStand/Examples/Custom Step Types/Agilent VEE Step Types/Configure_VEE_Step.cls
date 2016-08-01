VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Configure_VEE_Step"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True

Public Function Configure_VEE_Step(SeqContext As SequenceContext) As Integer

    Dim modalId As Long
    Dim notUsedBool As Boolean

    Set gSeqContext = SeqContext
    Set gEngine = SeqContext.Engine

    ' Load the Edit Module Form
    Load EditModule

    ' Tell TestStand to focus on form
    If gEngine.MajorVersion() > 1 Then
        modalId = gEngine.RegisterModalWindow(Nothing, EditModule.hWnd, notUsedBool)
    End If
    
    ' Display the form
    EditModule.Show vbModal

ErrorHandler:

    'Tell TestStand to no longer focus on form
    If (modalId) Then
        If (gEngine.MajorVersion() > 1) Then
            gEngine.UnregisterModalWindow modalId
            modalId = 0
        End If
    End If

    Unload EditModule
    HelperFunctions.DestroyVariables
    
    Err.Clear

End Function

