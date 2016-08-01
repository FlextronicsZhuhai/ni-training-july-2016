#include "stdtst.h"
#include "tsutil.h"

void __declspec(dllexport) __stdcall GenerateOutputMessages(CAObjHandle seqContextCVI,
        char reportText[1024], short *errorOccurred, long *errorCode, char errorMsg[1024])
{
    int error = 0;
    ERRORINFO                   errorInfo;
    int i =0;
    ErrMsg                      errMsg;
    CAObjHandle                 tsEngine = 0;
    CAObjHandle					outputMessage = 0;
    char						messageText[254];
    div_t result;
    
    tsErrChk(TS_SeqContextGetEngine (seqContextCVI, &errorInfo, &tsEngine));
    
    for(i =0; i<=100; i++)
    {
    	sprintf(messageText,"CVI Generated Output Message: Loop Index %d",i);
    	result = div(i,10);
    	if(result.rem ==0)
    	{
    		 tsErrChk(TS_EngineNewOutputMessage (tsEngine, &errorInfo, messageText, "CVI",
												 TS_OutputMessageSeverity_Information , seqContextCVI, &outputMessage));
			 tsErrChk(TS_OutputMessageSetTextColor (outputMessage, &errorInfo, 0x00800080));
			 tsErrChk(TS_OutputMessageSetIconName(outputMessage, &errorInfo,"cviadp.ico"));
			 tsErrChk(TS_OutputMessagePost(outputMessage,&errorInfo));
			 CA_DiscardObjHandle(outputMessage);
    	}
    }

Error:  
     CA_DiscardObjHandle(tsEngine);
     CA_DiscardObjHandle(outputMessage);
    // FREE RESOURCES
    // if (lastUserName != NULL)
    //     CA_FreeMemory(lastUserName);

    // If an error occurred, set the error flag to cause a run-time error in TestStand.
    if (error < 0)
        {
        // *errorOccurred = TRUE;
    
        // OPTIONALLY SET THE ERROR CODE AND STRING
        // *errorCode = error;
        // strcpy(errorMsg, errMsg);
        }
        CA_DiscardObjHandle(tsEngine);
        CA_DiscardObjHandle(outputMessage); 
}
