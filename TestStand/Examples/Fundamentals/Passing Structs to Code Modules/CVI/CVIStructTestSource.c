#include <userint.h>
#include <ansi_c.h>
#define true 1
#define false 0

/* 
  CVI struct that mimics the container in TestStand.
*/
struct CVIStructExample {
	double Float64;
	char String[256];
	double Array[2];
	unsigned char Bool;
};

/* 
  Unpack the struct from TestStand:
  Passes a struct (cviStruct), unpacks it, and sets the returned_<name> parameters
  to the individual elements of cviStruct.
*/
void __declspec(dllexport) PassStructAndUnpack(struct CVIStructExample *cviStruct, 
	double *returned_Float64, char returned_String[256], double returned_Array[2], 
	unsigned char *returned_Bool)
{
	if(cviStruct)
	{
		*returned_Float64 = cviStruct->Float64;
		strncpy(returned_String, cviStruct->String, 255);
		//ensure that the string is NUL terminated
		returned_String[255] = 0;
		returned_Array[0] = cviStruct->Array[0];
		returned_Array[1] = cviStruct->Array[1];
		*returned_Bool = cviStruct->Bool;
	}
}

/* 
  Pack the struct from TestStand with new values:
  Passes a struct (cviStruct) and modifies its values. These updates are reflected
  in TestStand's CVIStruct.
*/

void __declspec(dllexport) PassStructAndModify(struct CVIStructExample *cviStruct)
{

	if(cviStruct)
	{
		cviStruct->Float64 = 10.25;
		strncpy(cviStruct->String, "String Modified by DLL", 255);
		//ensure that the string is NUL terminated 
		cviStruct->String[255] = 0;
		cviStruct->Array[0] = 3.14;
		cviStruct->Array[1] = 1592;
		cviStruct->Bool = true;
	}
}
