//==============================================================================
//
// Title:       Utils.c
//
// Created on:  9/23/2011 at 12:03:08 PM by Jed Beach.
//
//==============================================================================

#include "Utils.h"
#include <toolbox.h>

//==============================================================================
// CONSTANTS
//==============================================================================

static const char EMPTY_STRING[] = "";

//========================================================================
// FUNCTION PROTOTYPES FOR STATIC FUNCTIONS
//========================================================================

static int SSB_Realloc(SimpleStringBuilder *, size_t);
static int SSB_EnsureCapacity(SimpleStringBuilder *, size_t, size_t);
static size_t SSB_ExtraBytes(size_t);
static size_t SSB_CsvEscapedSize(const char *, BOOL);

// Allocate, reallocate, or free the underlying data buffer.  SSB_Realloc()
// has behavior similar to realloc().  If there is no existing data buffer, 
// a new one is created.  If there is an existing data buffer,
// SSB_Realloc() will attempt to reallocate it in-place using realloc().
// If the requested capacity is 0, SSB_Realloc() will free the existing
// buffer.
// 
// In addition, SSB_Realloc() manages lengthInBytes and adds missing
// terminating '\0' chracters when needed.  If the buffer is reduced to a
// size smaller than the existing lengthInBytes + 1, lengthInBytes is
// adjusted to fit within the new buffer and a terminating '\0' is placed
// in the last element of the buffer.  If the existing data pointer was
// NULL and a new buffer is allocated, data[0] is set to '\0'.
//
// ssb -- A pointer to the SimpleStringBuilder structure to modify.
// capacityInBytes -- The new capacity of the SimpleStringBuilder in bytes.
//
// return - 0 on success or less than 0 on failure.
static int SSB_Realloc(SimpleStringBuilder * ssb, size_t capacityInBytes)
{
	if (!ssb)
	{
		return TS_Err_InvalidPointer;
	}

	char * const newData = realloc(ssb->data, capacityInBytes);

	if (capacityInBytes)
	{
		if (!newData)
		{
			return TS_Err_OutOfMemory;
		}

		if (capacityInBytes < (ssb->lengthInBytes + 1))
		{
			ssb->lengthInBytes = capacityInBytes - 1;
		}

		newData[ssb->lengthInBytes] = '\0';
		ssb->data = newData;
		ssb->capacityInBytes = capacityInBytes;
	}
	else // capacityInBytes == 0, so realloc() freed data.
	{
		ssb->data = NULL;
		ssb->lengthInBytes = 0;
		ssb->capacityInBytes = 0;
	}

	Assert(!ssb->lengthInBytes || (ssb->lengthInBytes < ssb->capacityInBytes));
	Assert(ssb->data || !ssb->capacityInBytes);

	return TS_Err_NoError;
}

// If the underlying data buffer already has capacityInBytes, do nothing.
// If the underlying buffer does not have capacityInBytes, grow it to 
// capacityInBytes + extraBytes.
//
// ssb -- A pointer to a SimpleStringBuilder structure.
// capacityInBytes -- The required capacity of the SimpleStringBuilder.
// extraBytes -- The amount of extra memory, over and above capacityInBytes,
//         to allocate if reallocation is required.
//
// return - 0 on success or less than 0 on failure.
static int SSB_EnsureCapacity(SimpleStringBuilder * ssb, size_t capacityInBytes, size_t extraBytes)
{
	if (!ssb)
	{
		return TS_Err_InvalidPointer;
	}

	if (ssb->capacityInBytes < capacityInBytes)
	{
		return SSB_Realloc(ssb, capacityInBytes + extraBytes);
	}

	return TS_Err_NoError;
}

// If the underlying data buffer already has capacityInBytes, do nothing.
// If the underlying buffer does not have capacityInBytes, grow it to 
// capacityInBytes.
//
// ssb -- A pointer to a SimpleStringBuilder structure.
// capacityInBytes -- The required capacity of the SimpleStringBuilder.
//
// return - 0 on success or less than 0 on failure.
int SSB_Reserve(SimpleStringBuilder * ssb, size_t capacityInBytes)
{
	return SSB_EnsureCapacity(ssb, capacityInBytes, 0);
}


// Clean up and release all resources associated with a SimpleStringBuilder.
//
// ssb -- A pointer to a SimpleStringBuilder structure.
void SSB_Destroy(SimpleStringBuilder * ssb)
{
	const int error = SSB_Realloc(ssb, 0);

	Assert(TS_Err_NoError == error);// Although SSB_Realloc() returns an error, it should never do so if 0 is passed for capacityInBytes.

	Assert(!ssb->data);
	Assert(!ssb->capacityInBytes);
	Assert(!ssb->lengthInBytes);
}

// Set the value represented by a SimpleStringBuilder to string.  The
// existing value is replaced.
//
// ssb -- A pointer to a SimpleStringBuilder structure.
// string -- The new string value the SimpleStringBuilder will represent.
//
// return - 0 on success or less than 0 on failure.
int SSB_Set(SimpleStringBuilder * ssb, const char * string)
{
	if (!ssb)
	{
		return TS_Err_InvalidPointer;
	}

	// If there is an existing data buffer, truncate to an empty string.
	if (ssb->data)
	{
		ssb->data[0] = '\0';
		ssb->lengthInBytes = 0;
	}

	Assert(!ssb->lengthInBytes);

	return SSB_Append(ssb, string);
}

// Append the string pointed to by the data argument to the string currently
// represented by the SimpleStringBuilder, growing the underlying data
// buffer if needed.
//
// ssb -- A pointer to a SimpleStringBuilder structure.
// data -- The string to append.  If NULL, nothing is appended.
//
// return - 0 on success or less than 0 on failure.
int SSB_Append(SimpleStringBuilder * ssb, const char * data)
{
	if (!ssb)
	{
		return TS_Err_InvalidPointer;
	}

	// If there is no data, either because it is NULL or an empty string,
	// then there is nothing left to do but return success.
	if (!data || !data[0])
	{
		return TS_Err_NoError;
	}

	// Note that strlen() is correct here, even for multibyte strings
	// (as long as the underlying encoding does not allow for embedded
	// nulls) because this method does everything in terms of the underlying
	// bytes.
	const size_t newDataSizeInBytes = strlen(data) + 1; // +1 for the terminating '\0'.
	const size_t newCapacityInBytes = ssb->lengthInBytes + newDataSizeInBytes;

	const int error = SSB_EnsureCapacity(ssb, newCapacityInBytes, SSB_ExtraBytes(newCapacityInBytes));

	if (error >= 0)
	{
		Assert(ssb->data != 0);
		Assert(ssb->capacityInBytes >= newCapacityInBytes);

		memcpy(ssb->data + ssb->lengthInBytes, data, newDataSizeInBytes);

		ssb->lengthInBytes += (newDataSizeInBytes - 1); // -1 to ignore the terminating '\0'.

		Assert(ssb->lengthInBytes <  ssb->capacityInBytes);
	}

	return error;
}

// Append count copies of the data argument to the string currently
// represented by the SimpleStringBuilder, growing the underlying buffer
// if needed.
//
// Note:  Although somewhat general, this method was created to append
// commas, new lines, carriage returns, tabs and/or spaces.  As such, no
// allowance was made for wide or multibyte characters.  To append
// multibyte characters you must make a string and use SSB_Append().
//
// ssb -- A pointer to a SimpleStringBuilder structure.
// data -- The character to append.
// count -- The number of copies of data to append.
//
// return -- Greater than or equal to 0 on success, less than 0 on failure.
int SSB_AppendChars(SimpleStringBuilder * ssb, char data, size_t count)
{
	if (!ssb)
	{
		return TS_Err_InvalidPointer;
	}

	// Since this method only supports single-byte characters, make sure
	// data is not the lead byte of a multibyte character.
	if (IsDBCSLeadByte(data))
	{
		return TS_Err_ValueIsInvalidOrOutOfRange;
	}

	// If there is nothing to do, just return success.
	if (!count || !data)
	{
		return TS_Err_NoError;
	}

	const size_t newDataSizeInBytes = count + 1; // +1 for the terminating '\0'.
	const size_t newCapacityInBytes = ssb->lengthInBytes + newDataSizeInBytes;

	const int error = SSB_EnsureCapacity(ssb,newCapacityInBytes,SSB_ExtraBytes(newCapacityInBytes));

	if (error >= 0)
	{
		Assert(ssb->data != 0);
		Assert(ssb->capacityInBytes >= newCapacityInBytes);

		memset(ssb->data + ssb->lengthInBytes, data, count);

		ssb->lengthInBytes += count;
		Assert(ssb->lengthInBytes < ssb->capacityInBytes);

		ssb->data[ssb->lengthInBytes] = '\0';
	}

	return error;
}

// Truncate the string represented by a SimpleStringBuilder to lengthInBytes
// bytes, excluding the terminating '\0'.  Note that the final length may
// be less than lengthInBytes if there are multibyte characters in the
// string.
//
// ssb -- A pointer to a SimpleStringBuilder structure.
//
// return -- The length of the new string in bytes on success, less than
//           0 on failure.
int SSB_Truncate(SimpleStringBuilder * ssb, size_t newLengthInBytes)
{
	if (!ssb)
	{
		return TS_Err_InvalidPointer;
	}

	// Is there data to truncate?  If so, does it need to be truncated?
	if (ssb->data && (ssb->lengthInBytes > newLengthInBytes))
	{
		const char * const limit = ssb->data + newLengthInBytes;

		char * end = ssb->data;

		while (end < limit)
		{
			end = _mbsinc(end);
		}

		// If the last character was multibyte, end could have gone
		// one byte further than asked.
		if (end > limit)
		{
			// The previous character must have been two bytes,
			// so move end back two bytes.
			end -= 2;
		}

		Assert((end - ssb->data) < ssb->lengthInBytes);

		ssb->lengthInBytes = end - ssb->data;

		Assert(ssb->lengthInBytes < ssb->capacityInBytes);
		Assert(ssb->lengthInBytes <= newLengthInBytes);

		ssb->data[ssb->lengthInBytes] = '\0';

	}

	return 0;
}


// Get the string associated with this SimpleStringBuilder.  If ssb or
// the underlying data member is NULL, SSB_GetString() will return a
// statically allocated empty string.
//
// Use SSB_GetString() instead of accessing the underlying data member
// directly.
//
// ssb -- A pointer to a SimpleStringBuilder structure.
//
// return -- A pointer to the string represented by the argument.  This
//        be an empty string ("") if the argument or underlying buffer
//        are NULL.
const char * SSB_GetString(const SimpleStringBuilder * ssb)
{
	return (ssb && ssb->data)? ssb->data : EMPTY_STRING;
}

// Get the number of bytes needed to contain the string represented by
// a SimpleStringBuilder, excluding the trailing '\0'.
//
// ssb -- A pointer to a SimpleStringBuilder structure.
//
// return - The length of the represented string in bytes or 0 if ssb is
//        NULL.
size_t SSB_GetLengthInBytes(const SimpleStringBuilder * ssb)
{
	return ssb? ssb->lengthInBytes : 0;
}


// Determines if the string referred to by the SimpleStringBuilder ends
// with charToFind.
//
// ssb -- A pointer to a SimpleStringBuilder structure.
// charToFind -- The character to check for.  It is an int so that multibyte
//        characters can be supported.
//
// return -- TRUE if the string referred to by ssb ends with charToFind,
//        FALSE otherwise.  FALSE will be returned if ssb is NULL.
BOOL SSB_EndsWithChar(const SimpleStringBuilder * ssb, int charToFind)
{
	if (charToFind && ssb && ssb->data)
	{
		const char * last = _mbsrchr(ssb->data, charToFind);

		last += IsDBCSLeadByte(*last)?  2  :  1;

		return !*last;
	}

	return FALSE;
}

// Calculates additional extra bytes to allocate if one of the append
// methods needs to reallocate the underlying data buffer.  The
// calculation is a very simple heuristic.  The goal is to limit the number
// of reallocations when the append methods are called repeatedly.
static size_t SSB_ExtraBytes(size_t bufferSize)
{
	return 16 + bufferSize / 8;
}

//
// ssb -- A pointer to a SimpleStringBuilder structure.
// string -- The string to append.  NULL is treated as an empty string.
// always -- Set to true if all strings should be quoted, even if they
//        contain no special characters.  Pass false to quote only strings
//        that require it to comply with RFC 4180.
// finalLengthInChars -- The length of the argument string as quoted and
//        escaped by this function.  Output parameter, may be NULL if not
//        needed by the caller.
//
// return -- Greater than or equal to 0 on success, less than 0 on failure.
int SSB_CsvEscapeAndAppend(SimpleStringBuilder * ssb, const char * string, BOOL always, size_t * finalLengthInChars) 
{
	if (!ssb)
	{
		return TS_Err_InvalidPointer;
	}

	// Treat NULL as an empty string.
	if (!string)
	{
		string = "";
	}

	const size_t escapedSize = SSB_CsvEscapedSize(string, always);

	// Was any escaping necessary?
	if (!escapedSize)
	{
		if (finalLengthInChars)
		{
			*finalLengthInChars = _mbslen(string);
		}

		// No escaping was necessary, so just use the standard SSB_Append()
		// function.
		return SSB_Append(ssb, string);
	}

	//
	// Escape string while appending it to the existing string.
	//

	Assert(escapedSize >= 3); // 2 quotes + the null at a minimum.

	// Make sure there is enough space in ssb->data for the additional
	// data.
	const size_t newCapacity = escapedSize + ssb->lengthInBytes;

	int error = SSB_EnsureCapacity(ssb, newCapacity, SSB_ExtraBytes(newCapacity));

	if (error < 0)
	{
		return error;
	}

	Assert(ssb->capacityInBytes >= newCapacity);

	char * const escapedString = ssb->data + ssb->lengthInBytes;
	char * escPtr = escapedString;

	*escPtr = '"'; ++escPtr; // Append the initial quote for the new field.

	// Copy the new field to the new buffer, escaping quotes as needed.
	for (const char * srcPtr=string; *srcPtr; ++srcPtr)
	{
		*escPtr = *srcPtr; ++escPtr; // Copy original value.

		if ('"' == *srcPtr)
		{
			*escPtr = '"'; ++escPtr; // Escape quotation marks.
		}
		else if (IsDBCSLeadByte(*srcPtr))
		{
			++srcPtr;

			// Break the loop if we have a partial multibyte character.
			if (!*srcPtr)
			{
				// Put the terminating-null at the end of the original
				// string in the SimpleStringBuilder.  Doing this leaves
				// the value of the SimpleStringBuilder pointed to be ssb
				//  It my have a larger capacity and have been moved to a
				// new location in memory, but the value and length of the
				// string will be the same as before
				// SSB_CsvEscapeAndAppend() was called.  The newly copied
				// data after the null does not matter.
				ssb->data[ssb->lengthInBytes] = '\0';
				return TS_Err_ValueIsInvalidOrOutOfRange; 
			}

			*escPtr = *srcPtr; ++escPtr; // Copy second byte of original value.
		}
	}

	*escPtr = '"';  ++escPtr; // Add closing quote.
	*escPtr = '\0'; ++escPtr; // Add terminating null.

	// Update the SimpleStringBuilder object.
	ssb->lengthInBytes = newCapacity - 1;

	Assert((escPtr - escapedString) == escapedSize);
	Assert((escPtr - ssb->data) == newCapacity);
	Assert(!ssb->data[ssb->lengthInBytes]);

	if (finalLengthInChars)
	{
		*finalLengthInChars = _mbslen(escapedString);
	}

	return error;
}



// Calculate the size of the string if quoted and escaped per RFC 4180,
// including the terminating '\0'
//
// return - 0 if no escaping is necessary.  The number of bytes required
//        to quote stirng and escape any existing quotes.
static size_t SSB_CsvEscapedSize(const char * string, BOOL always)
{
	size_t numQuotes = 0;
	size_t newSize = 0;
	size_t oldSize = 1;  // 1 represents the terminating '\0'.
	BOOL hasSpecialCharacter = FALSE;

	// Treat NULL as an empty string.
	if (!string)
	{
		string = "";
	}

	const char * ptr = string;

	for (; *ptr; ++ptr)
	{
		switch (*ptr)
		{
			case '"' : ++numQuotes; // fall through
			case ',' :              // fall through
			case '\r' :             // fall through
			case '\n' :             // fall through
				hasSpecialCharacter = TRUE;
				break;

			default:  break;
		}

		if (IsDBCSLeadByte(*ptr))
		{
			++ptr;

			// Break the loop if we have a partial multibyte  character.
			if (!*ptr)
			{
				break;
			}
		}
	}

	// Add just the length of the old string.  The null was counted above.
	oldSize += (ptr - string);

	if (always || hasSpecialCharacter)
	{
		newSize = oldSize;   // Space for original string, including the terminating null.
		newSize += 2;        // Space for surrounding quotes.
		newSize += numQuotes;// Space for escaping quotes contained in string.
	}

	return newSize;
}


// Replaces invalid file name characters in the argument with underscore,
// '_', characters.  This function assumes that the file system is Windows
// NTFS.  Win NTFS forbids \/:*?"<>| as well as characters <= 0x1f.
//
// It is safe to pass NULL to this function.  In that case, it simply returns,
// doing nothing.
//
// Note:  The input is modified in place.
// 
// fileName -- The file name which may contain invalid characters.
void SSB_ReplaceInvalidFileNameCharacters( SimpleStringBuilder * fileName )
{
	const char invalidChars[] = { '\\', '/', ':', '*', '?', '"', '<', '>', '|' };
	const size_t numInvalidChars = sizeof(invalidChars)/sizeof(char);

	if (fileName && fileName->data)
	{
		for (char *ptr = fileName->data; *ptr; ptr = _mbsinc(ptr))
		{
			// All of the invalid characters are standard ASCII.  This makes
			// the code below simpler because it can ignore multibyte
			// characters and substitute for the invalid characters in-place.
			if (!_ismbblead(*ptr))
			{
				BOOL isValid = (*ptr > 0x1F);

				for (int ii = 0; isValid && (ii < numInvalidChars); ++ii)
				{
					isValid = (*ptr != invalidChars[ii]);
				}

				if (!isValid)
				{
					*ptr = '_';
				}
			}
		}
	}
}
