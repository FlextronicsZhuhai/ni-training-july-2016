#include "tsapicvi.h"
#include "tsutil.h"   
#include <formatio.h>
#include <utility.h>
#include <ansi_c.h>

// The definition below is required for compatibility with 
// the "jni_md.h" file provided by SUN Microsystems, Inc.
#define __int64 long  

#include "jni.h"
#include "winbase.h"

// Global references to the JVM and its environment
static JNIEnv       *env    = NULL;
static JavaVM       *jvm    = NULL;


// declare function prototypes 
typedef jint (JNICALL *NI_CreateJavaVM)(JavaVM **pvm, void **penv, void *args);
BOOL  buildHeader(CAObjHandle *inputArgH, int numArgs, char* type, char ** header ,int *error, ErrMsg *errMsg);


// Function definitions
///////////////////////////////////////////////////////////////////////////////
int __stdcall DllMain (HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    char ModuleAddress[248];
    switch (fdwReason)
        {
        case DLL_PROCESS_ATTACH:
            if (InitCVIRTE (hinstDLL, 0, 0) == 0)
                return 0;     /* out of memory */
            if (GetModuleFileName(hinstDLL, ModuleAddress, 248)==0)
                return 0;
            if(LoadLibrary(ModuleAddress)== NULL)
                return 0;
            break;
        case DLL_PROCESS_DETACH:
            CloseCVIRTE ();
            break;
        }
    return 1;
}

BOOL __declspec(dllexport) __stdcall IsJVMInstalled(CAObjHandle seqContextCVI)
{
    unsigned int        actualSize          = 0;
    char    *           javaVer             = NULL; 
    char    *           javaRegDllLoc       = NULL;
    char    *           javaDllLoc          = NULL;
    char    *           JavaSubRegKey       = "SOFTWARE\\JavaSoft\\Java Runtime Environment"; 
    char    *           JavaRegKey          = "HKEY_LOCAL_MACHINE\\SOFTWARE\\JavaSoft\\Java Runtime Environment"; 
    int                 error               = 0;
    ErrMsg              errMsg              = {'\0'};

    
    if(RegReadString (REGKEY_HKLM,JavaSubRegKey,"CurrentVersion", NULL,0, &actualSize)) 
    {
        error = -1;
        goto Error;
    }
    
    javaVer = (char*)malloc(sizeof(char)*actualSize);             
    if(javaVer == NULL)
    {
        strcpy(errMsg, "Cannot allocate Memory");  
        error = -10000;
        goto Error;
    }
    if(RegReadString (REGKEY_HKLM,JavaSubRegKey,"CurrentVersion", javaVer,actualSize, &actualSize)) 
    {
        error = -1;
        goto Error;
    }
        
    javaRegDllLoc = (char*)malloc(strlen(JavaSubRegKey)+strlen("\\")+strlen(javaVer)+1);
    if(javaRegDllLoc == NULL)
    {
        strcpy(errMsg, "Cannot allocate Memory");  
        error = -10000;
        goto Error;
    }
    strcpy(javaRegDllLoc,JavaSubRegKey);
    strcat(javaRegDllLoc,"\\");
    strcat(javaRegDllLoc,javaVer);
    
    if(RegReadString (REGKEY_HKLM,javaRegDllLoc,"RuntimeLib", NULL,0, &actualSize))
    {
        error = -1;
        goto Error;
    }
    
    javaDllLoc = (char*)malloc(sizeof(char)*actualSize);              
    if(javaDllLoc == NULL)
    {
        strcpy(errMsg, "Cannot allocate Memory");  
        error = -10000;
        goto Error;
    }
    if(RegReadString (REGKEY_HKLM,javaRegDllLoc,"RuntimeLib", javaDllLoc,actualSize, &actualSize)) 
    {
        error = -1;
        goto Error;
    }

Error:
    if(javaVer)
        free(javaVer);
    if(javaRegDllLoc)
        free(javaRegDllLoc);
    if(javaDllLoc)
        free(javaDllLoc);
        
    // Just return false    
    if (error == -1)
        return FALSE;
    
    if(error == -10000)
    {
        // Return error if unable to allocate memory.
        TS_SetStepError(seqContextCVI, error, errMsg);
        return FALSE;
    }
    
    return TRUE;
}

BOOL GetJavaRTMModule(HMODULE *jvmModule, int *error, ErrMsg *errMsg )
{
    unsigned int        actualSize          = 0;
    char    *           javaVer             = NULL; 
    char    *           javaRegDllLoc       = NULL;
    char    *           javaDllLoc          = NULL;
    char    *           JavaSubRegKey       = "SOFTWARE\\JavaSoft\\Java Runtime Environment";
    char    *           JavaRegKey          = "HKEY_LOCAL_MACHINE\\SOFTWARE\\JavaSoft\\Java Runtime Environment";
    
    if(RegReadString (REGKEY_HKLM,JavaSubRegKey,"CurrentVersion", NULL,0, &actualSize)) 
    {
        strcpy(*errMsg, "Unable to find registry keys for Java runtime at ");
        strcat(*errMsg, JavaRegKey);
        *error = -7000;
        goto Error;
    }
    
    javaVer = (char*)malloc(sizeof(char)*actualSize);             
    if(javaVer == NULL)
    {
        strcpy(*errMsg, "Cannot allocate Memory");  
        *error = -10000;
        goto Error;
    }
    if(RegReadString (REGKEY_HKLM,JavaSubRegKey,"CurrentVersion", javaVer,actualSize, &actualSize)) 
    {
        strcpy(*errMsg, "Unable to find registry keys for Java runtime at ");
        strcat(*errMsg, JavaRegKey);
        *error = -7000;
        goto Error;
    }
    javaRegDllLoc = (char*)malloc(strlen(JavaSubRegKey)+strlen("\\")+strlen(javaVer)+1);
    if(javaRegDllLoc == NULL)
    {
        strcpy(*errMsg, "Cannot allocate Memory");  
        *error = -10000;
        goto Error;
    }
    strcpy(javaRegDllLoc,JavaSubRegKey);
    strcat(javaRegDllLoc,"\\");
    strcat(javaRegDllLoc,javaVer);
    
    if(RegReadString (REGKEY_HKLM,javaRegDllLoc,"RuntimeLib", NULL,0, &actualSize)) 
    {
        strcpy(*errMsg, "Unable to find registry keys for Java at ");
        strcat(*errMsg, javaRegDllLoc);
        *error = -7500;
        goto Error;
    }
    
    javaDllLoc = (char*)malloc(sizeof(char)*actualSize);              
    if(javaDllLoc == NULL)
    {
        strcpy(*errMsg, "Cannot allocate Memory");  
        *error = -10000;
        goto Error;
    }
    if(RegReadString (REGKEY_HKLM,javaRegDllLoc,"RuntimeLib", javaDllLoc,actualSize, &actualSize)) 
    {
        strcpy(*errMsg, "Unable to find registry keys for Java at ");
        strcat(*errMsg, javaRegDllLoc);
        *error = -7500;
        goto Error;
    }
    
    // Load jvm.dll
    *jvmModule = LoadLibrary(javaDllLoc);
    if(*jvmModule == NULL)
    {
		//in 64-bit Java, the registry key incorrectly specified the JVM location as in the client folder, but it is actually located in the server folder.  
		//Replace "client" with "server" to work around the issue
		CopyBytes(javaDllLoc,FindPattern(javaDllLoc, 0, -1, "client", 1,0)  ,"server",0,6);
		
		    *jvmModule = LoadLibrary(javaDllLoc);
		    if(*jvmModule == NULL)
		    {		 
				strcpy(*errMsg, "Unable to find runtime dll for Java at ");
		        strcat(*errMsg, javaDllLoc);
		        *error = -8000;
		        goto Error;
			}	
    }

Error:
    if(javaVer)
        free(javaVer);
    if(javaRegDllLoc)
        free(javaRegDllLoc);
    if(javaDllLoc)
        free(javaDllLoc);
    if (*error < 0)
    {
        return TRUE;
    }
    return FALSE;
}


BOOL GetJavaFuncs (NI_CreateJavaVM *fpCreateJVM,HMODULE jvmModule, int *error,ErrMsg *errMsg)
{
    if(jvmModule)
    {
        //gets the required function address
        *fpCreateJVM =  (NI_CreateJavaVM) GetProcAddress (jvmModule, "JNI_CreateJavaVM");
        if (!*fpCreateJVM) 
        {
            strcpy(*errMsg, "Unable to find CreateJavaVM function in JVM.dll");
            *error = -9000;
            goto Error;
        }
    }
    else 
        *error = -9000;
Error:
    if(*error < 0 )
    {
        return TRUE;
    }
    return FALSE;

}

/*************************************************************************

    This is the code that invokes the JVM and calls the specified method
    
**************************************************************************/

int __declspec(dllexport) __stdcall StartJVM(CAObjHandle seqContextCVI)
{
    JavaVMInitArgs      vm_args;
    int                 error               = 0;
    ErrMsg              errMsg              = {'\0'};
    char    *           tClassPath          = NULL;
    char    *           userClassPath       = NULL;
    JavaVMAttachArgs    JVMAttachArgs       = {JNI_VERSION_1_4,NULL,NULL};
    HMODULE             jvmModule           = 0;
    ERRORINFO           errorInfo;
    JavaVMOption        options[1];
    NI_CreateJavaVM     fpCreateJVM;
    
    // Create JVM if it doesnt already exist
    if (jvm==NULL) 
    {    
        // Load jvm.dll
        if(GetJavaRTMModule(&jvmModule,&error,&errMsg))
            goto Error;
        if(GetJavaFuncs(&fpCreateJVM,jvmModule, &error,&errMsg))
            goto Error;
    
        // Get the path of the user class
        tsErrChk(TS_PropertyGetValString(seqContextCVI, &errorInfo, "Step.ClassPath", 
                                            0, &tClassPath));
                                            
        userClassPath = (char*)malloc(strlen(tClassPath)+strlen("-Djava.class.path=")+1);
        
        strcpy(userClassPath,"-Djava.class.path=");
        strcat(userClassPath,tClassPath);
        
        vm_args.version = JNI_VERSION_1_4;
        options[0].optionString = userClassPath; /* user classes */
        vm_args.options = options;
        vm_args.nOptions = 1;
        vm_args.ignoreUnrecognized = JNI_TRUE;
        
        // Create the Java VM using new error checking
        error = fpCreateJVM(&jvm,(void**)&env,&vm_args);
        if(error < 0)
        {
            strcpy(errMsg,"Could not launch JVM.");  
            goto Error;
        }
    }
    // If JVM already exists simply make sure this thread is attached
    error = (*jvm)->AttachCurrentThread(jvm, (void**)&env, &JVMAttachArgs); 
    if(error < 0 ) 
        strcpy(errMsg,"Could not Attach current thread to JVM.");  
    
    
    // By default JVM returns single digit error codes; these are wrapped in 
    // TS style error codes for easier interpretation by customer.
    switch (error)
    {
    case (-1): 
        {
        // any -1 case is mapped to -1001, reasons include JVM start issues: 
        // could not launch, could not attach thread, could not detach thread
        error = -1001;
        break;
        }
    case (-2):
        {
        // -2 case mapped to -1002: thread detached from JVM
        error = -1002;
        break;
        }
    case (-3):
        {
        // -3 case mapped to -1003: could not launch JVM (version error)
        error = -1003;
        break;
        }
    case (-4):
        {
        // -4 case mapped to -1004: out of memory
        error = -1004;
        break;
        }
    case (-5):
        {
        // -5 case mapped to -1005: JVM already exists
        error = -1005;
        break;
        }
    case (-6):
        {
        // -6 case mapped to -1006: invalid arguement
        error = -1006;
        break;
        }
    }// end switch
        
    
// Handle error case:
Error:
    if(tClassPath)
        CA_FreeMemory(tClassPath);
    if(userClassPath)
        free(userClassPath);
    if (error < 0)
    {
        if (env)
                (*env)->ExceptionClear(env);
        // Returns the error provided by the JVM. The error codes are defined by JNI in the JNI Specification
        TS_SetStepError(seqContextCVI, error, errMsg);
    }
    
    return error;
}


// Invoke a method as specified
void __declspec(dllexport) __stdcall InvokeJavaMethod(CAObjHandle seqContext) 
{    
    // My declarations
    CAObjHandle     stepH               = 0;
    CAObjHandle     inputArgH           = 0;
    CAObjHandle     outputArgH          = 0;        
    jclass          cls					= NULL;
    jmethodID       mid					= NULL;
    jint            retVal				= 0;
    jobject         obj                 = 0;
    jvalue*         argPtr              = 0;
    char        *   className           = NULL;
    char        *   classPath           = NULL;
    char        *   methodName          = NULL;
    char        *   methodType          = NULL;
    char        *   metHeader           = NULL;
    char        *   argVal2             = NULL;
    char        *   retExpr             = NULL;
    char        *   argVal              = NULL;
    char        *   lowerBounds         = NULL;
    char        *   upperBounds         = NULL;
    char        *   tClassName          = NULL;
    char        *   retstring           = NULL;
    char            retcharstring[2]    = "";
    char            tArgType[128]       = "";
    size_t             tlength             = 0;
    int             index               = 0;
    int             numElems            = 0;
    int             error               = 0;
    double          tFloat              = 0.0;  // variable to hold double returned by TS before casting to float
    jstring     *   stringRef           = NULL;
    int             refCount            = 0;    
    ErrMsg          errMsg              = {'\0'};
    ERRORINFO       errorInfo;
    enum            TSEnum_PropertyValueTypes elemType;
    
    // Get a handle to the step
    tsErrChk(TS_SeqContextGetStep (seqContext, &errorInfo, &stepH));
    
    // Get the classname and method name to invoke
    tsErrChk(TS_PropertyGetValString (stepH, &errorInfo, "ClassName", 0, &tClassName));
    
    // Extract the classname from the path
    tlength = strlen(tClassName);
    if (tlength <7)
    {
        strcpy(errMsg, "Incorrect class name");  
        error = -2000;
        goto Error;
    }
    // need to sub 6 and add 1 because of removing .class from the class name
    
    className = (char*) malloc((tlength-5)*sizeof(char));
    if(className == NULL)
    {
        strcpy(errMsg, "Cannot allocate Memory");  
        error = -10000;
        goto Error;
    }
    Fmt(className,"%s<%s[t46]", tClassName);
    
    tsErrChk(TS_PropertyGetValString (stepH, &errorInfo, "MethodName", 0, &methodName));
 
    // Gets the InputArguments of the Java step type as a property object
    tsErrChk (TS_PropertyGetPropertyObject (stepH, &errorInfo, "MethodParams", 0,
                                        &inputArgH));

    // Gets the Output Argument of the Java step type as a property object
    tsErrChk (TS_PropertyGetPropertyObject (stepH, &errorInfo, "ReturnVal", 0,
                                        &outputArgH));

    // Get the number of input arguments
    tsErrChk (TS_PropertyGetDimensions (inputArgH, &errorInfo, "DataType", 0,
                              &lowerBounds, &upperBounds, &numElems,
                              &elemType));

    // Search for the class
    if ((env!=NULL)&&(jvm!=NULL)) 
    {
    
        cls = (*env)->FindClass(env, className);
        if (cls == 0) 
        {
            strcpy(errMsg, "Cannot find class");
            error = -1500;
            goto Error;
        }
        
        // Allocate object to call
        obj = (*env)->AllocObject(env, cls);
        if (obj == NULL) 
        {
            strcpy(errMsg, "Incorrect class name");
            error = -2000;
            goto Error;
        }

        // Get the type of the return value
        tsErrChk(TS_PropertyGetValString (outputArgH, &errorInfo, "DataType", 0, &methodType));

        // Get the expression for the return value
        tsErrChk(TS_PropertyGetValString (outputArgH, &errorInfo, "Expression", 0, &retExpr));
        
        
        
        // Build the method header
        errChk(buildHeader(&inputArgH, numElems, methodType, &metHeader, &error, &errMsg));
        
            
        // Get the method ID
        mid = (*env)->GetMethodID(env, cls, methodName, metHeader);
        if (mid == 0) 
        {
            strcpy(errMsg, "Cannot find method");  
            error = -3000;
            goto Error;
        }
    

        // Use number of arguments to build array of parameters to pass to method
        argPtr = (jvalue *)(int)malloc(sizeof(jvalue) * numElems);
        if((argPtr == NULL)&&(numElems > 0))
        {
            strcpy(errMsg, "Cannot allocate Memory");  
            error = -10000;
            goto Error;
        }
        
        // 1 needs to be added to numElements because we might have
        // a string return value.
        stringRef = (jstring*)(int)malloc(sizeof(jstring)*numElems+1);
        
        if((stringRef == NULL)&&(numElems > 0))
        {
            strcpy(errMsg, "Cannot allocate Memory");  
            error = -10000;
            goto Error;
        }
        
                              
        // Fill values in array of parameters
        for (index =0; index < numElems; index++) 
        {
            // Get argument's type
            Fmt(tArgType, "%s%d%s", "DataType[", index, "]");
            tsErrChk(TS_PropertyGetValString (inputArgH, &errorInfo, tArgType, 0, &argVal));

            // Prepare to get the expression
            Fmt(tArgType, "%s%d%s", "Expression[", index, "]");
            tsErrChk(TS_PropertyGetValString (inputArgH, &errorInfo, tArgType, 0, &argVal2));
            

            // Set appropriate part of object
            switch(argVal[0]) 
            {
                case 'I':
                    {
                        int tempint = 4;
                        // Get the expression
                        tsErrChk(TS_EvaluateAndGet (seqContext, argVal2, kEvalTypeIntegerNumber, 0,
                             &tempint, errMsg));
                        argPtr[index].i = tempint;
                    }
                    break;
                case 'Z':
                    // Get the expression
                    tsErrChk(TS_EvaluateAndGet (seqContext, argVal2, kEvalTypeBoolean, 0,
                           &(argPtr[index].z), errMsg));
                    break;
                case 'B':
                    // Get the expression
                    tsErrChk(TS_EvaluateAndGet (seqContext, argVal2, kEvalTypeIntegerNumber, 0,
                           &(argPtr[index].b), errMsg));
                    break;
                case 'C':
                    // Free memory to store the character
                    if (argVal)
                    {
                        CA_FreeMemory(argVal);
                        argVal = NULL;
                    }
                    
                    // Get the expression
                    tsErrChk(TS_EvaluateAndGet (seqContext, argVal2, kEvalTypeString, 0,
                                                &argVal, errMsg));
                    argPtr[index].c = argVal[0];
                    break;
                case 'S':
                    // Get the expression
                    tsErrChk(TS_EvaluateAndGet (seqContext, argVal2, kEvalTypeIntegerNumber, 0,
                           &(argPtr[index].s), errMsg));
                    break;
                case 'J':
                    // Get the expression
                    tsErrChk(TS_EvaluateAndGet (seqContext, argVal2, kEvalTypeIntegerNumber, 0,
                           &(argPtr[index].j), errMsg));
                    break;
                case 'F':
                    // Get the expression
                    tsErrChk(TS_EvaluateAndGet (seqContext, argVal2, kEvalTypeNumber, 0,
                           &tFloat,errMsg));
                    argPtr[index].f = (float)tFloat;
                    break;
                case 'D':
                    // Get the expression
                    tsErrChk(TS_EvaluateAndGet (seqContext, argVal2, kEvalTypeNumber, 0,
                           &(argPtr[index].d), errMsg));
                    break;
                case 'A':
                    // String case
                    if (argVal)
                    {
                        CA_FreeMemory(argVal);
                        argVal = NULL;
                    }
            
                    // Get the expression
                    tsErrChk(TS_EvaluateAndGet (seqContext, argVal2, kEvalTypeString, 0,
                           &argVal, errMsg));

                    stringRef[refCount] = (*env)->NewStringUTF(env, argVal);
                    argPtr[index].l = stringRef[refCount];
                    refCount++;
                    break;
                
            }
            if (argVal!= NULL)
            {
                CA_FreeMemory(argVal);
                argVal = NULL;
            }
            if(argVal2!= NULL)
            {
                CA_FreeMemory(argVal2);
                argVal2 = NULL;
            }
        }

        // Invoke the method, and store returned value (if applicable) 
        if (StrICmp(methodType, "I") == 0) 
        {
            int retVal = (*env)->CallIntMethodA(env, obj, mid, argPtr);             
            // Save the value in TestStand
            tsErrChk(TS_PropertySetValNumber (seqContext, &errorInfo, retExpr, 0, retVal));
        }
        else if (StrICmp(methodType, "Z") == 0)
        {
            int retVal = (*env)->CallBooleanMethodA(env, obj, mid, argPtr);             
            // Save the value in TestStand
            tsErrChk(TS_PropertySetValBoolean (seqContext, &errorInfo, retExpr, 0, (VBOOL)retVal));
        }
        else if (StrICmp(methodType, "B") == 0)
        {
            int retVal = (*env)->CallByteMethodA(env, obj, mid, argPtr);                
            // Save the value in TestStand
            tsErrChk(TS_PropertySetValNumber (seqContext, &errorInfo, retExpr, 0, retVal));
        }
        else if (StrICmp(methodType, "C") == 0)
        {
            char retVal = (char)(*env)->CallCharMethodA(env, obj, mid, argPtr);               
            // Save the value in TestStand
            retcharstring[0] = retVal;
            tsErrChk(TS_PropertySetValString (seqContext, &errorInfo, retExpr, 0, retcharstring));
        }
        else if (StrICmp(methodType, "S") == 0)
        {
            int retVal = (char)(*env)->CallShortMethodA(env, obj, mid, argPtr);               
            // Save the value in TestStand
            tsErrChk(TS_PropertySetValNumber (seqContext, &errorInfo, retExpr, 0, retVal));
        }
        else if (StrICmp(methodType, "J") == 0)
        {
            long retVal = (*env)->CallLongMethodA(env, obj, mid, argPtr);               
            // Save the value in TestStand
            tsErrChk(TS_PropertySetValNumber (seqContext, &errorInfo, retExpr, 0, retVal));
        }
        else if (StrICmp(methodType, "F") == 0)
        {
            float retVal = (*env)->CallFloatMethodA(env, obj, mid, argPtr);             
            // Save the value in TestStand
            tsErrChk(TS_PropertySetValNumber (seqContext, &errorInfo, retExpr, 0, retVal));
        }
        else if (StrICmp(methodType, "D") == 0)
        {
            double retVal = (*env)->CallDoubleMethodA(env, obj, mid, argPtr);               
            // Save the value in TestStand
            tsErrChk(TS_PropertySetValNumber (seqContext, &errorInfo, retExpr, 0, retVal));
        }
        else if (StrICmp(methodType, "V") == 0)
        {

            (*env)->CallVoidMethodA(env, obj, mid, argPtr);             
        }
        else if (StrICmp(methodType, "A") == 0) 
        {
            // It is a string
            jstring retVal = (*env)->CallObjectMethodA(env, obj, mid, argPtr);

            // Check for error in reading string
            if (retVal == NULL) 
            {
                strcpy(errMsg,"Error reading returned string");
                error = -4000;
                goto Error;
            }
            else 
            {
                // String was returned. Translate string and transfer to TestStand.
                const char *str = (*env)->GetStringUTFChars(env, retVal, 0);
                retstring = (char*) malloc((strlen(str)+1)*sizeof(char));
                if(retstring == NULL)
                {
                    strcpy(errMsg, "Cannot allocate Memory");  
                    error = -10000;
                    goto Error;
                }
                strcpy(retstring,str);
                (*env)->ReleaseStringUTFChars(env, retVal, str);
                tsErrChk(TS_PropertySetValString (seqContext, &errorInfo, retExpr, 0, retstring));
                
				if(stringRef != NULL)
				{
	                stringRef[refCount] = retVal;
	                refCount++;
				}
            }
        }
        else
            TS_SetStepError (seqContext, -5000, "Invalid return type found");
    }
    else
        TS_SetStepError (seqContext, -6000, "Error - JVM not invoked. Please start JVM first.");

    
Error:  
    // FREE RESOURCES
    // Release string parameter references
    if(stringRef)
        free(stringRef);
    if (metHeader)
        free(metHeader);
    if(className)
        free(className);
    if (argPtr)
        free(argPtr);
    if (argVal != NULL)
        CA_FreeMemory(argVal);      
    if(argVal2 != NULL)
        CA_FreeMemory(argVal2);
    if(retstring != NULL)
        free(retstring);
    CA_FreeMemory(retExpr);
    CA_FreeMemory(tClassName);
    CA_FreeMemory(classPath);
    CA_FreeMemory(methodName);
    CA_FreeMemory(methodType);
    CA_FreeMemory(lowerBounds);
    CA_FreeMemory(upperBounds);
    
    CA_DiscardObjHandle(stepH);
    CA_DiscardObjHandle(inputArgH);
    CA_DiscardObjHandle(outputArgH);
    

    // Release reference
    if(obj != NULL && *env != NULL)
        (*env) -> DeleteLocalRef(env, obj);
        
    if(cls != NULL && *env != NULL)
        (*env) -> DeleteLocalRef(env, cls);
        
	while (refCount > 0)
    {
        refCount--;
		if (*env != NULL)
       		(*env) -> DeleteLocalRef(env, stringRef[refCount]);
    }
	
    // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
        {
            if (env)
                (*env)->ExceptionClear(env);
            TS_SetStepError (seqContext, error, errMsg);
        }
    return; 
}

// Invoke a method as specified
void __declspec(dllexport) __stdcall InvokeStaticJavaMethod(CAObjHandle seqContext) 
{    
    // My declarations
    CAObjHandle     stepH               = 0;
    CAObjHandle     inputArgH           = 0;
    CAObjHandle     outputArgH          = 0;        
    jclass          cls					= NULL;
    jmethodID       mid;
    jint            retVal;
    jvalue*         argPtr              = 0;
    char        *   className           = NULL;
    char        *   classPath           = NULL;
    char        *   methodName          = NULL;
    char        *   methodType          = NULL;
    char        *   metHeader           = NULL;
    char        *   argVal2             = NULL;
    char        *   retExpr             = NULL;
    char        *   argVal              = NULL;
    char        *   lowerBounds         = NULL;
    char        *   upperBounds         = NULL;
    char        *   tClassName          = NULL;
    char        *   retstring           = NULL;
    char            retcharstring[2]    = "";
    char            tArgType[128]       = "";
    size_t             tlength             = 0;
    int             index               = 0;
    int             numElems            = 0;
    int             error               = 0;
    double          tFloat              = 0.0;          // variable to hold double returned by TS before casting to float
    jstring     *   stringRef           = NULL;
    int             refCount            = 0;    
    ErrMsg          errMsg              = {'\0'};
    ERRORINFO       errorInfo;
    enum            TSEnum_PropertyValueTypes elemType;
    
    // Get a handle to the step
    tsErrChk(TS_SeqContextGetStep (seqContext, &errorInfo,&stepH));
    
    // Get the classname and method name to invoke
    tsErrChk(TS_PropertyGetValString (stepH, &errorInfo, "ClassName", 0, &tClassName));
    
    // Extract the classname from the path
    tlength = strlen(tClassName);
    if (tlength <7)
    {
        strcpy(errMsg, "Incorrect class name");  
        error = -2000;
        goto Error;
    }
    // need to sub 6 and add 1 because of removing .class from the class name
    className = (char*) malloc((tlength-5)*sizeof(char));
    if(className == NULL)
    {
        strcpy(errMsg, "Cannot allocate Memory");  
        error = -10000;
        goto Error;
    }
    Fmt(className,"%s<%s[t46]", tClassName);
    
    tsErrChk(TS_PropertyGetValString (stepH, &errorInfo, "MethodName", 0, &methodName));
 
    // Gets the InputArguments of the Java step type as a property object
    tsErrChk (TS_PropertyGetPropertyObject (stepH, &errorInfo, "MethodParams", 0,
                                        &inputArgH));

    // Gets the Output Argument of the Java step type as a property object
    tsErrChk (TS_PropertyGetPropertyObject (stepH, &errorInfo, "ReturnVal", 0,
                                        &outputArgH));

    // Get the number of input arguments
    tsErrChk (TS_PropertyGetDimensions (inputArgH, &errorInfo, "DataType", 0,
                              &lowerBounds, &upperBounds, &numElems,
                              &elemType));

    // Search for the class
    if ((env!=NULL)&&(jvm!=NULL)) 
    {
        cls = (*env)->FindClass(env, className);
        if (cls == 0) 
        {
            strcpy(errMsg, "Cannot find class");
            error = -1500;
            goto Error;
        }
        
        // Get the type of the return value
        tsErrChk(TS_PropertyGetValString (outputArgH, &errorInfo, "DataType", 0, &methodType));

        // Get the expression for the return value
        tsErrChk(TS_PropertyGetValString (outputArgH, &errorInfo, "Expression", 0, &retExpr));
        
        // Build the method header
        errChk(buildHeader(&inputArgH, numElems, methodType, &metHeader, &error, &errMsg));
            
        // Get the method ID
        mid = (*env)->GetStaticMethodID(env, cls, methodName, metHeader);
        if (mid == 0) 
        {
            strcpy(errMsg, "Cannot find method");  
            error = -3000;
            goto Error;
        }

        // Use number of arguments to build array of parameters to pass to method
        argPtr =(jvalue*)(int)malloc(sizeof(jvalue) * numElems);
        if((argPtr == NULL)&&(numElems > 0))
        {
            strcpy(errMsg, "Cannot allocate Memory");  
            error = -10000;
            goto Error;
        }
            
        stringRef = (jstring*)(int)malloc(sizeof(jstring)*numElems);

        // Fill values in array of parameters
        for (index =0; index < numElems; index++) 
        {
            // Get argument's type
            Fmt(tArgType, "%s%d%s", "DataType[", index, "]");
            tsErrChk(TS_PropertyGetValString (inputArgH, &errorInfo, tArgType, 0, &argVal));

            // Prepare to get the expression
            Fmt(tArgType, "%s%d%s", "Expression[", index, "]");
            tsErrChk(TS_PropertyGetValString (inputArgH, &errorInfo, tArgType, 0, &argVal2));

            // Set appropriate part of object
            switch(argVal[0]) 
            {
                case 'I':
                    // Get the expression
                    tsErrChk(TS_EvaluateAndGet (seqContext, argVal2, kEvalTypeIntegerNumber, 0,
                           &(argPtr[index].i), errMsg));
                    break;
                case 'Z':
                    // Get the expression
                    tsErrChk(TS_EvaluateAndGet (seqContext, argVal2, kEvalTypeBoolean, 0,
                           &(argPtr[index].z), errMsg));
                    break;
                case 'B':
                    // Get the expression
                    tsErrChk(TS_EvaluateAndGet (seqContext, argVal2, kEvalTypeIntegerNumber, 0,
                           &(argPtr[index].b), errMsg));
                    break;
                case 'C':
                    // Free memory to store the character
                    if (argVal)
                    {
                        CA_FreeMemory(argVal);
                        argVal = NULL;
                    }
                    
                    // Get the expression
                    tsErrChk(TS_EvaluateAndGet (seqContext, argVal2, kEvalTypeString, 0,
                                                &argVal, errMsg));
                    argPtr[index].c = argVal[0];
                    break;
                case 'S':
                    // Get the expression
                    tsErrChk(TS_EvaluateAndGet (seqContext, argVal2, kEvalTypeIntegerNumber, 0,
                           &(argPtr[index].s), errMsg));
                    break;
                case 'J':
                    // Get the expression
                    tsErrChk(TS_EvaluateAndGet (seqContext, argVal2, kEvalTypeIntegerNumber, 0,
                           &(argPtr[index].j), errMsg));
                    break;
                case 'F':
                    // Get the expression
                    tsErrChk(TS_EvaluateAndGet (seqContext, argVal2, kEvalTypeNumber, 0,
                           &tFloat, errMsg));
                    argPtr[index].f = (float)tFloat;
                    break;
                case 'D':
                    // Get the expression
                    tsErrChk(TS_EvaluateAndGet (seqContext, argVal2, kEvalTypeNumber, 0,
                           &(argPtr[index].d), errMsg));
                    break;
                case 'A':
                    // String case
                    if (argVal)
                    {
                        CA_FreeMemory(argVal);
                        argVal = NULL;
                    }
            
                    // Get the expression
                    tsErrChk(TS_EvaluateAndGet (seqContext, argVal2, kEvalTypeString, 0,
                           &argVal, errMsg));

                    // Save reference
                    stringRef[refCount] = (*env)->NewStringUTF(env, argVal);
                    argPtr[index].l = stringRef[refCount];
                    refCount++;
                    break;
            }
            if (argVal!= NULL)
            {
                CA_FreeMemory(argVal);
                argVal = NULL;
            }
            if(argVal2!= NULL)
            {
                CA_FreeMemory(argVal2);
                argVal2 = NULL;
            }
        }
        
        // Invoke the method, and store returned value (if applicable) 
        if (StrICmp(methodType, "I") == 0) 
        {
            int retVal = (*env)->CallStaticIntMethodA(env, cls, mid, argPtr);               
            // Save the value in TestStand
            tsErrChk(TS_PropertySetValNumber (seqContext, &errorInfo, retExpr, 0, retVal));
        }
        else if (StrICmp(methodType, "Z") == 0)
        {
            int retVal = (*env)->CallStaticBooleanMethodA(env, cls, mid, argPtr);               
            // Save the value in TestStand
            tsErrChk(TS_PropertySetValBoolean (seqContext, &errorInfo, retExpr, 0, (VBOOL)retVal));
        }
        else if (StrICmp(methodType, "B") == 0)
        {
            int retVal = (*env)->CallStaticByteMethodA(env, cls, mid, argPtr);              
            // Save the value in TestStand
            tsErrChk(TS_PropertySetValNumber (seqContext, &errorInfo, retExpr, 0, retVal));
        }
        else if (StrICmp(methodType, "C") == 0)
        {
            char retVal = (char)(*env)->CallStaticCharMethodA(env, cls, mid, argPtr);             

            // Save the value in TestStand
            retcharstring[0] = retVal;
            tsErrChk(TS_PropertySetValString (seqContext, &errorInfo, retExpr, 0, retcharstring));
        }
        else if (StrICmp(methodType, "S") == 0)
        {
            int retVal = (*env)->CallStaticShortMethodA(env, cls, mid, argPtr);             
            // Save the value in TestStand
            tsErrChk(TS_PropertySetValNumber (seqContext, &errorInfo, retExpr, 0, retVal));
        }
        else if (StrICmp(methodType, "J") == 0)
        {
            long retVal = (*env)->CallStaticLongMethodA(env, cls, mid, argPtr);             
            // Save the value in TestStand
            tsErrChk(TS_PropertySetValNumber (seqContext, &errorInfo, retExpr, 0, retVal));
        }
        else if (StrICmp(methodType, "F") == 0)
        {
            float retVal = (*env)->CallStaticFloatMethodA(env, cls, mid, argPtr);               
            // Save the value in TestStand
            tsErrChk(TS_PropertySetValNumber (seqContext, &errorInfo, retExpr, 0, retVal));
        }
        else if (StrICmp(methodType, "D") == 0)
        {
            double retVal = (*env)->CallStaticDoubleMethodA(env, cls, mid, argPtr);             
            // Save the value in TestStand
            tsErrChk(TS_PropertySetValNumber (seqContext, &errorInfo, retExpr, 0, retVal));
        }
        else if (StrICmp(methodType, "V") == 0)
        {

            (*env)->CallStaticVoidMethodA(env, cls, mid, argPtr);               
        }
        else if (StrICmp(methodType, "A") == 0) 
        {
            // It is a string
            jstring retVal = (*env)->CallStaticObjectMethodA(env, cls, mid, argPtr);

            // Check for error in reading string
            if (retVal == NULL) 
            {
                strcpy(errMsg,"Error reading returned string");
                error = -4000;
                goto Error;
            }
            else {
                // String was returned. Translate string and transfer to TestStand.
                const char *str = (*env)->GetStringUTFChars(env, retVal, 0);
                retstring = (char*) malloc((strlen(str)+1)*sizeof(char));
                if(retstring == NULL)
                {
                    strcpy(errMsg, "Cannot allocate Memory");  
                    error = -10000;
                    goto Error;
                }
                strcpy(retstring,str);
                (*env)->ReleaseStringUTFChars(env, retVal, str);
                (*env)->ReleaseStringUTFChars(env, retVal, NULL);
                tsErrChk(TS_PropertySetValString (seqContext, &errorInfo, retExpr, 0, retstring));

                // save string reference
                if(stringRef != NULL)
				{
					stringRef[refCount] = retVal;
             	  	refCount++;
				}
            }
        }
        else
            TS_SetStepError (seqContext, -5000, "Invalid return type found");
        
    }
    else
        TS_SetStepError (seqContext, -6000, "Error - JVM not invoked. Please start JVM first.");

    
Error:  
    // FREE RESOURCES
    if(stringRef)
        free(stringRef);
    if (metHeader)
        free(metHeader);
    if(className)
        free(className);
    if (argPtr)
        free(argPtr);
    if (argVal != NULL)
        CA_FreeMemory(argVal);      
    if(argVal2 != NULL)
        CA_FreeMemory(argVal2);
    if(retstring != NULL)
        free(retstring);
    CA_FreeMemory(retExpr);
    CA_FreeMemory(tClassName);
    CA_FreeMemory(classPath);
    CA_FreeMemory(methodName);
    CA_FreeMemory(methodType);
    CA_FreeMemory(lowerBounds);
    CA_FreeMemory(upperBounds);
    
    CA_DiscardObjHandle(stepH);
    CA_DiscardObjHandle(inputArgH);
    CA_DiscardObjHandle(outputArgH);

    
    // Delete the class reference
    if(cls != NULL && *env != NULL)
        (*env) -> DeleteLocalRef(env, cls);

	// Release string parameter references
    while (refCount > 0)
    {
        refCount--;
		if (*env != NULL)
    		(*env) -> DeleteLocalRef(env, stringRef[refCount]);
        //(*env)->ReleaseStringUTFChars(env, stringRef[refCount], NULL);
    }
	
    // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
    {
        if (env)
            (*env)->ExceptionClear(env);
        TS_SetStepError (seqContext, error, errMsg);
    }
    return; 
}

// Detach the thread from JVM
void __declspec(dllexport) __stdcall ExitJVM(CAObjHandle seqContext) 
{
    int     error = 0;
    if (jvm)
    {
        // Untill JDK 1.4, the VM cannot be destroyed. DestroyJavaVM always returns an error code,
        //  and so the JVM is not actually destroyed. All we do is detach the thread to let the JVM
        //  know that we are no longer using it. 
        errChk((*jvm)->DetachCurrentThread(jvm));
    }
    
Error:
    if (error < 0 ) 
    {
         TS_SetStepError (seqContext, error, "Unable to detach current thread from JVM");
    }
}


// Builds the header for a method to call through JNI 
BOOL  buildHeader(CAObjHandle *inputArgH, int numArgs, char* returnType, char ** header ,int *error, ErrMsg *errMsg)
{
    int         index           = 0;
    char        tHeader[128]    = "";
    char        passType[128]   = {'('};
    char    *   type            = 0;
    ERRORINFO   errorInfo;
    
    // Build the passed parameters section of the method header
    for (index = 0; index < numArgs; index++) 
    {
        Fmt(tHeader, "%s%d%s", "DataType[", index, "]");
        if(TS_PropertyGetValString (*inputArgH, &errorInfo, tHeader, 0, &type))
        {
            strcpy(*errMsg,errorInfo.description);
            *error = errorInfo.sCode;
        }
        
        // Special cases for strings and void header
        switch (type[0]) 
        {
            case 'A':
                CA_FreeMemory(type);
                type = (char*)malloc((strlen("Ljava/lang/String;")+1)*sizeof(char));
                if(type == NULL)
                {
                    strcpy(*errMsg, "Cannot allocate Memory");  
                    *error = -10000;
                    goto Error;
                }
                strcpy(type,"Ljava/lang/String;");
                Fmt(passType, "%s%s", passType, type);
                free(type);
                break;
            case 'V':
                Fmt(passType, "%s%s", passType, "");
                CA_FreeMemory(type);
                if (numArgs > 1)
                {
                    *error = -3500;
                    strcpy(*errMsg, "Too many arguments passed for void method \n Results will be unreliable");
                    goto Error;
                }
                break;
            default:
                // Concatenate type to the header
                Fmt(passType, "%s%s", passType, type);
                CA_FreeMemory(type);
                break;
        }
    }
    Fmt(passType, "%s%s", passType, ")");

    // Introduce special case for string return types
    if (returnType[0] == 'A') 
    {
        strcat (passType,"Ljava/lang/String;");
    }
    else
        // Concatenate the return type to the method header
        strcat (passType, returnType);
    
    *header = (char*)malloc((strlen(passType)+1)*sizeof(char));
    if(header == NULL)
    {
        strcpy(*errMsg, "Cannot allocate Memory");  
        *error = -10000;
        goto Error;
    }
    strcpy(*header,passType);
    
    
Error:
    if (*error < 0)
    {
        return TRUE;
    }
    return FALSE;
}

