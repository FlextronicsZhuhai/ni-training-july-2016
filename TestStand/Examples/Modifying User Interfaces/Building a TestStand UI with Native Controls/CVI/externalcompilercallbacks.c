#pragma pack(4)
typedef struct {char *name; void *address; unsigned long isFunction:1; unsigned long reserved:31;} ExeSymbol;
int __cdecl ExecuteCallback (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int __cdecl MainPanelCallback (int panel, int event, void *callbackData, int eventData1, int eventData2);
int __cdecl OpenSequenceFileCallback (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int __UICallbackSymbolCount = 3;
ExeSymbol __UICallbackSymbols [3] =
{
 {"_ExecuteCallback", ExecuteCallback, 1, 0},
 {"_MainPanelCallback", MainPanelCallback, 1, 0},
 {"_OpenSequenceFileCallback", OpenSequenceFileCallback, 1, 0}
};
