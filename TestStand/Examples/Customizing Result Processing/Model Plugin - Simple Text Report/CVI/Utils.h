//==============================================================================
//
// Title:       Utils.h
//
// Created on:  9/20/2011 at 2:56:31 PM by Jed Beach.
//
//==============================================================================

#ifndef __Utils_H__
#define __Utils_H__

#ifdef __cplusplus
    extern "C" {
#endif

#include <ansi_c.h>
#include <tsutil.h>

		
// Clean-up the resources owned by the specified handle/pointer using the
// specified function, and set the handle/pointer to 0.
//
// __handle -- A handle to resource that needs to be cleaned up.
//
// __func -- The function to clean up the resources with.  The function
//         must take __handle as its only argument.
#define CLEAR(__handle, __func)				\
	if(__handle)							\
	{										\
		__func(__handle);					\
		__handle = 0;						\
	}
		

// SimpleStringBuilder and its associated SSB_ methods are a tool for
// building the strings that make up the rows of the.the Simple Text
// Report.
//
// All SimpleStringBuilder structures must be initialized to all 0's
// when declared.  This is equivalent to initializing a pointer to NULL.
// Once initialized to all 0's, any of the SSB_ functions may be called
// on the SimpleStringBuilder.
//
// When you are done with a SimpleStringBuilder, you must clean it up by
// calling SSB_Destroy().  Below is a basic example of how to use
// SimpleStringBuilder.
//
//		int error = 0;
//
//      SimpleStringBuilder mBuilder = {0};
//
//      error = SSB_Append( &mBuilder, "Hello world!" );
//      if( error < 0 ) { goto Error; }
//
//      error = SSB_AppendChars( &mBuilder,'\n', 1 );
//      if( error < 0 ) { goto Error; }
//
//      printf( SSB_GetString(&mBuilder) );
//
//   Error:
//
//      SSB_Destroy( &mBuilder );
//
typedef struct
{
	// The string represented by this object.  May be NULL.  If non-null,
	// the array pointed to will always be a valid, null-terminated string.
	char * data;

	// The current size of the buffer pointed to by data in bytes. If
	// data is NULL, capacityInBytes must be 0.
	size_t capacityInBytes;

	// The current length of the string represented by data.  If data is
	// NULL, lengthInBytes must be 0.
	size_t lengthInBytes;
}
SimpleStringBuilder;


int SSB_Reserve( SimpleStringBuilder *, size_t );
void SSB_Destroy( SimpleStringBuilder * );
int SSB_Set( SimpleStringBuilder *, const char * );
int SSB_Append( SimpleStringBuilder * , const char * );
int SSB_AppendChars( SimpleStringBuilder *, char, size_t );
int SSB_Truncate( SimpleStringBuilder *, size_t );
const char * SSB_GetString( const SimpleStringBuilder * );
size_t SSB_GetLengthInBytes( const SimpleStringBuilder * );

BOOL SSB_EndsWithChar( const SimpleStringBuilder *, int );

int SSB_CsvEscapeAndAppend( SimpleStringBuilder *, const char *, BOOL, size_t *);
void SSB_ReplaceInvalidFileNameCharacters( SimpleStringBuilder * );

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __Utils_H__ */
