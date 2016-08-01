VERSION 5.00
Begin VB.Form EditModule 
   Caption         =   "Edit VEE Module"
   ClientHeight    =   6705
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7545
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   6705
   ScaleMode       =   0  'User
   ScaleWidth      =   7545
   StartUpPosition =   2  'CenterScreen
   Begin VB.TextBox OutputExp 
      Height          =   315
      Left            =   2040
      TabIndex        =   8
      Top             =   5280
      Width           =   3975
   End
   Begin VB.TextBox InputExp 
      Height          =   315
      Left            =   2040
      TabIndex        =   5
      Top             =   3840
      Width           =   3975
   End
   Begin VB.CommandButton Cancel 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   6600
      TabIndex        =   11
      Top             =   6120
      Width           =   855
   End
   Begin VB.CommandButton OK 
      Caption         =   "OK"
      Height          =   375
      Left            =   5400
      TabIndex        =   10
      Top             =   6120
      Width           =   855
   End
   Begin VB.ComboBox OutputArgList 
      Height          =   315
      Left            =   2040
      Style           =   2  'Dropdown List
      TabIndex        =   7
      Top             =   4680
      Width           =   3975
   End
   Begin VB.CheckBox DebugOption 
      Caption         =   "Debug"
      Height          =   375
      Left            =   6240
      TabIndex        =   3
      ToolTipText     =   "Set Debug True/ False"
      Top             =   1680
      Width           =   975
   End
   Begin VB.CommandButton Browsefile 
      Caption         =   "Browse"
      Height          =   375
      Left            =   6240
      TabIndex        =   1
      Top             =   360
      Width           =   855
   End
   Begin VB.ComboBox InputArgList 
      Height          =   315
      Left            =   2040
      Style           =   2  'Dropdown List
      TabIndex        =   4
      Top             =   2640
      Width           =   3975
   End
   Begin VB.ComboBox VEEFunction 
      Height          =   315
      Left            =   2040
      Style           =   2  'Dropdown List
      TabIndex        =   2
      Top             =   1680
      Width           =   3975
   End
   Begin VB.Frame Frame1 
      Caption         =   "Specify Module"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   2175
      Left            =   0
      TabIndex        =   12
      Top             =   0
      Width           =   7455
      Begin VB.TextBox FullPath 
         BackColor       =   &H8000000B&
         Height          =   375
         Left            =   2040
         Locked          =   -1  'True
         TabIndex        =   18
         Top             =   840
         Width           =   3975
      End
      Begin VB.TextBox VEELibrary 
         Height          =   375
         Left            =   2040
         TabIndex        =   0
         Top             =   360
         Width           =   3975
      End
      Begin VB.Label Label5 
         Caption         =   "VEE Functions"
         Height          =   255
         Left            =   480
         TabIndex        =   14
         Top             =   1680
         Width           =   1215
      End
      Begin VB.Label Label2 
         Caption         =   "VEE Library To Load"
         Height          =   375
         Left            =   360
         TabIndex        =   13
         Top             =   480
         Width           =   1575
      End
   End
   Begin VB.Frame Frame2 
      Caption         =   "Input"
      Height          =   2175
      Left            =   0
      TabIndex        =   15
      Top             =   2160
      Width           =   7455
      Begin VB.TextBox InputType 
         Height          =   315
         Left            =   2040
         Locked          =   -1  'True
         TabIndex        =   17
         Top             =   1080
         Width           =   3975
      End
      Begin VB.CommandButton BrowseInExp 
         Caption         =   "Browse"
         Height          =   375
         Left            =   6240
         TabIndex        =   6
         Top             =   1680
         Width           =   855
      End
      Begin VB.Label Label8 
         Caption         =   "Expression/Value"
         Height          =   255
         Left            =   480
         TabIndex        =   21
         Top             =   1680
         Width           =   1335
      End
      Begin VB.Label Label7 
         Caption         =   "Type"
         Height          =   375
         Left            =   480
         TabIndex        =   20
         Top             =   1080
         Width           =   1455
      End
      Begin VB.Label Label4 
         Caption         =   "Argument"
         Height          =   375
         Left            =   480
         TabIndex        =   19
         Top             =   480
         Width           =   1335
      End
   End
   Begin VB.Frame Frame3 
      Caption         =   "Output"
      Height          =   1695
      Left            =   0
      TabIndex        =   16
      Top             =   4320
      Width           =   7455
      Begin VB.CommandButton BrowseOutExp 
         Caption         =   "Browse"
         Height          =   375
         Left            =   6240
         TabIndex        =   9
         Top             =   960
         Width           =   855
      End
      Begin VB.Label Label11 
         Caption         =   "Expression/Value"
         Height          =   495
         Left            =   480
         TabIndex        =   23
         Top             =   960
         Width           =   1335
      End
      Begin VB.Label Label9 
         Caption         =   "Argument"
         Height          =   375
         Left            =   480
         TabIndex        =   22
         Top             =   360
         Width           =   735
      End
   End
End
Attribute VB_Name = "EditModule"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' Note: This boolean is needed to swallow all Click and Change events that are
' fired during the loading of the form
Private handleEvent As Boolean
Private Const STEP_DEBUG_PROP As String = "Step.Result.Debug"
Private Const STEP_VEE_LIB_PROP As String = "Step.Result.VEELib"
Private Const STEP_VEE_FUNC_PROP As String = "Step.Result.VEEFunc"
Private Const STEP_VEE_INPUT_PROP As String = "Step.Result.Input"
Private Const STEP_VEE_OUTPUT_PROP As String = "Step.Result.Output"
Private Const FILE_NOT_FOUND As String = "(File Not Found)"
Private Const EMPTY_STRING_CONST As String = ""
Private gCurrLib As String
Private gCurrLibFullPath As String
    

Private Sub Form_Load()
    
    Dim debugVal As Boolean
    Dim foundIt As Boolean
    Dim absolutePath As String
    Dim funcVal As String
    Dim cancelled As Boolean
        
    ' See note in declaration section
    handleEvent = False
    
    ' Clear all controls
    VEELibrary.Text = EMPTY_STRING_CONST
    FullPath.Text = EMPTY_STRING_CONST
    DebugOption.Value = 0
    VEEFunction.Clear
    InputArgList.Clear
    OutputArgList.Clear
    OutputExp.Text = EMPTY_STRING_CONST
    InputExp.Text = EMPTY_STRING_CONST
    InputType.Text = EMPTY_STRING_CONST
           
    ' Load the VEE Server
    Set gVEEServer = New CallServer
        
    ' Load values from TestStand step type and populate controls
    Set gSeqContextPropObj = gSeqContext.AsPropertyObject
    
    ' Set Debug option
    debugVal = gSeqContextPropObj.GetValBoolean(STEP_DEBUG_PROP, 0)
    If debugVal = True Then
        DebugOption.Value = 1
    Else
        DebugOption.Value = 0
    End If
    
    ' Set Library.  This will fire the VEELibrary_Change event which will update
    ' all other controls
    VEELibrary.Text = gSeqContextPropObj.GetValString(STEP_VEE_LIB_PROP, 0)
    If VEELibrary.Text = EMPTY_STRING_CONST Then
        VEEFunction.Enabled = False
        DebugOption.Enabled = False
        DimControls False, "Input"
        DimControls False, "Output"
    End If
    
        
    gCurrLib = VEELibrary.Text
    gCurrLibFullPath = FullPath.Text
    
    ' Reset flag
    handleEvent = True
               
End Sub

Private Sub Browsefile_Click()
    
    Dim selectedOK As Boolean
    Dim absolutePaths() As String
    Dim selectedPaths() As String
    
    selectedOK = gEngine.DisplayFileDialog("Select VEE Library to Load", "OK", _
                                            "", selectedPaths, absolutePaths, 0, _
                                            ".vee", 4100, _
                                            "VEE Library Files (*.vee)|*.vee|")
        
    If selectedOK = True Then
        ' Set library information on form. This will fire VEELibrary_Change event
        gCurrLib = VEELibrary.Text
        gCurrLibFullPath = FullPath.Text
        VEELibrary.Text = selectedPaths(0)
    End If
           
End Sub

Private Sub BrowseInExp_Click()
    InputExp.Text = DisplayExpBrowser(InputExp.Text)
End Sub
Private Sub BrowseInExp_LostFocus()
    gInputArgs(InputArgList.ListIndex, 1) = InputExp.Text
End Sub

Private Sub BrowseOutExp_Click()
    OutputExp.Text = DisplayExpBrowser(OutputExp.Text)
End Sub
Private Sub BrowseOutExp_LostFocus()
    gOutputArgs(OutputArgList.ListIndex, 1) = OutputExp.Text
End Sub

Private Sub InputArgList_Click()
    
    ' Update the expression and type controls
    InputExp.Text = gInputArgs(InputArgList.ListIndex, 1)
    InputType.Text = gInputArgs(InputArgList.ListIndex, 2)
        
End Sub

Private Sub OutputArgList_Click()
    
    ' Update the expression control
    OutputExp.Text = gOutputArgs(OutputArgList.ListIndex, 1)
            
End Sub
Private Sub InputExp_LostFocus()
    
    ' User has moved away from the expression control, we must save their entry
    gInputArgs(InputArgList.ListIndex, 1) = InputExp.Text
        
End Sub
Private Sub OutputExp_LostFocus()
    
    ' User has moved away from the expression control, we must save their entry
    gOutputArgs(OutputArgList.ListIndex, 1) = OutputExp.Text
    
End Sub

Private Sub VEEFunction_Click()

    If handleEvent = True Then
        
        Set gCurrSelectedFunc = gVEELib.UserFunctions.Item(VEEFunction.ListIndex)
    
        ' Get input and output arguments
        UpdateArgs gCurrSelectedFunc, True, True
        If UUBound(gInputArgs) <> -1 Then
            DimControls True, "Input"
        Else
            DimControls False, "Input"
        End If
        If UUBound(gOutputArgList) <> -1 Then
            DimControls True, "Ouput"
        Else
            DimControls False, "Output"
        End If
        
    End If
       
End Sub

Private Sub Cancel_Click()
    Unload Me
End Sub

Private Sub OK_Click()
    
    ' Write values back to TestStand
    
    gSeqContextPropObj.SetValVariant STEP_VEE_INPUT_PROP, 0, gInputArgs
    gSeqContextPropObj.SetValVariant STEP_VEE_OUTPUT_PROP, 0, gOutputArgs
    gSeqContextPropObj.SetValVariant STEP_DEBUG_PROP, 0, DebugOption
    gSeqContextPropObj.SetValVariant STEP_VEE_FUNC_PROP, 0, VEEFunction.Text
    gSeqContextPropObj.SetValVariant STEP_VEE_LIB_PROP, 0, VEELibrary.Text
    
    ' Increment the change count
    gSeqContext.SequenceFile.AsPropertyObjectFile.IncChangeCount
           
    Unload Me
End Sub

Private Sub VEELibrary_Change()
       
    Dim debugVal As Boolean
    Dim foundIt As Boolean
    Dim absolutePath As String
    Dim ItemExists As Boolean
    Dim funcNameElement As String
    Dim funcVal As String
    Dim cancelled As Boolean
       
    On Error GoTo ErrorHandler
       
    ' Init variables
    ItemExists = False
         
    If VEELibrary.Text <> EMPTY_STRING_CONST Then
    
        ' Make sure that TestStand can find the file
        foundIt = gEngine.FindFile(VEELibrary.Text, absolutePath, cancelled, FindFile_PromptDisable, FindFile_AddDirToSrchList_No, False, gSeqContext.SequenceFile)
        
        If foundIt = True And cancelled = False Then
        
            ' Update full path and VEE library
            FullPath.Text = absolutePath
            ' If there are no user functions defined then this will throw an error
            Set gVEELib = gVEEServer.Libraries.Load(absolutePath)
            UpdateFunctionList gVEELib
            VEEFunction.Enabled = True
        
            ' Get the function stored in TestStand
            funcVal = gSeqContextPropObj.GetValString(STEP_VEE_FUNC_PROP, 0)
            ' Make sure that the function name we got from TestStand exists in the
            ' VEE library
            Dim loopCounter As Integer
            loopCounter = 0
            Do
                ItemExists = (EditModule.VEEFunction.List(loopCounter) = funcVal)
                loopCounter = loopCounter + 1
            Loop While (ItemExists = False) And (loopCounter < (EditModule.VEEFunction.ListCount - 1))
                                                        
            If funcVal <> "" And ItemExists = True Then
                Set gCurrSelectedFunc = gVEELib.UserFunctions.Item(funcVal)
                LoadInOutValsFromTS gCurrSelectedFunc
            Else
                Set gCurrSelectedFunc = gVEELib.UserFunctions.Item(0)
                UpdateArgs gCurrSelectedFunc, True, True
            End If
            
            ' Enable controls
            DebugOption.Enabled = True
    
            ' Set current values on dialog
            ' Supress VEEFunction_Click event from running
            handleEvent = False
            VEEFunction.Text = gCurrSelectedFunc.Name
            handleEvent = True

            If UUBound(gInputArgs) <> -1 Then
                ' Re-enable all controls
                DimControls True, "Input"
                InputArgList.Text = gInputArgs(0, 0)
                InputExp.Text = gInputArgs(0, 1)
                InputType.Text = gInputArgs(0, 2)
            Else
                ' Dim all appropriate controls....
                DimControls False, "Input"
    
            End If

            If UUBound(gOutputArgs) <> -1 Then
                ' Re-enable all controls
                DimControls True, "Output"
                 
                OutputArgList.Text = gOutputArgs(0, 0)
                OutputExp.Text = gOutputArgs(0, 1)
            Else
                ' Dim all controls
                DimControls False, "Output"
                    
            End If
            
            gCurrLib = VEELibrary.Text
            gCurrLibFullPath = FullPath.Text
           
        ' Did not find the file
        Else
    
            FullPath.Text = FILE_NOT_FOUND
            VEEFunction.Enabled = False
            DebugOption.Enabled = False
            DimControls False, "Input"
            DimControls False, "Output"

        End If
   
    ' Dim all controls
    Else
         
        FullPath.Text = FILE_NOT_FOUND
        VEEFunction.Enabled = False
        DebugOption.Enabled = False
        DimControls False, "Input"
        DimControls False, "Output"
            
    End If
   
ErrorHandler:
   
    Dim errorMsg As String
    
    errorMsg = "Error Code: " & Str(Err.Number) & vbCrLf & _
             "Source: " & Err.Source & vbCrLf & _
             "Description: " & Err.Description
    
    If Err.Number <> 0 And Err.Source = "VEE" Then
        handleEvent = False
        ' Reset the text in the controls in the case we get an error
        VEELibrary.Text = gCurrLib
        FullPath.Text = gCurrLibFullPath
        MsgBox errorMsg, vbOKOnly, "VEE Step Error"
        handleEvent = True
    End If
    
End Sub

