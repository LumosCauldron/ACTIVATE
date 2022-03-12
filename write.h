#ifndef WRITE_H
#define WRITE_H

#define CREATE 1
#define APPEND 0

#include "read.h"

void FWRITE(char* ptr, long long int amt, FILE* stream)
{
	fwrite(ptr, 1, amt, stream);
}

void writefromnetwork(char* str, long long int len, long long int numbytes_handled, FILE* stream, char close)	// Writes bytes to a stream
{
	if (!stream)
		THROW("NULL STREAM GIVEN TO WRITE_BYTES");
	register int numbytes_fromprevsignal = numbytes_handled % (NETMEMLIMIT + FILEMEMLIMIT);
	register int numbytes_tonextsignal   = (NETMEMLIMIT + FILEMEMLIMIT) - numbytes_fromprevsignal;
	if (!numbytes_fromprevsignal)	// If last read was NETMEMLIMIT + FILEMEMLIMIT bytes long the return first byte
		FWRITE(str + 1, len - 1, stream);
	else				// If last read was less, check for signal in case signal character exists in the middle
	{
		if ((numbytes_fromprevsignal + len) > (NETMEMLIMIT + FILEMEMLIMIT))	// If signal character in the middle, find and skip it while writing
		{
			FWRITE(str, numbytes_tonextsignal, stream);						// Write up to signal character
			FWRITE(str + numbytes_tonextsignal + 1, len - numbytes_tonextsignal - 1, stream);	// Write the the rest skipping the character
		}
		else									// Else carry on and just write everything without skipping a character
			FWRITE(str, len, stream);
	}
	cleanup:
	if (close)
		FCLOSE(stream);
}

void writefast(char* str, long long int len, FILE* stream, char close)	// Writes bytes to a stream
{
	if (!stream)
		THROW("NULL STREAM GIVEN TO WRITE_BYTES");
	FWRITE(str, len, stream);
	if (close)
		FCLOSE(stream);
}

void write_bytes(Bytes* str, FILE* stream, char close)	// Writes bytes to a stream
{
	if (!stream)
		THROW("NULL STREAM GIVEN TO WRITE_BYTES");
	register unsigned long long int len = str->len;
	unsigned char* ptr = str->array;
	register unsigned long long int i;
	for (i = 0; i < len; ++i)
		fputc(*(ptr + i), stream);
	if (close)
		FCLOSE(stream);
}
char overwritechar(FILE* stream, char c, unsigned long long int offset, int mode)		// Seeks file position and overwrites character
{
	char check = fseek(stream, offset, mode);
	if (check)
		return 0;
	fputc(c, stream);
	return 1;
}
char overwritestr(FILE* stream, char* str, unsigned long long int offset, int mode)	// Seeks file position and overwrites string
{
	if (!str)
		return 0;
	char check = fseek(stream, offset, mode);
	if (check)
		return 0;
	fputs(str, stream);
	return 1;
}

// CREATE 1 
// APPEND 0
void writefile(char* file, char create, Bytes* str)	// Opens/Creates file, writes string to it, the closes file
{
	FILE* stream = NULLPTR;				// Make stream
	if (create) stream = FOPEN(file, "w+");		// Create file
	else	    stream = FOPEN(file, "a");		// Append to existing
	writefast(str->array, str->len, stream, NOCLOSEFILE);
	FCLOSE(stream);					// Close file
}
void filter_file(char* oldfile, Bytes* rmstr, char* newfile)	// Creates new file without specified string in old file
{
	Bytes* filter = readfile(oldfile);	  // Read in file
	remove(oldfile);
	if (!filter)
		return;
	if (eqstr(rmstr->array, "\\r"))
	{
		*(rmstr->array)     = '\\';
		*(rmstr->array + 1) = 'r';
		*(rmstr->array + 2) = 0;
		rmstr->array = REALLOC(rmstr->array, rmstr->len-- - 1);
	}
	if (eqstr(rmstr->array, "\\n"))
	{
		*(rmstr->array)     = '\\';
		*(rmstr->array + 1) = 'n';
		*(rmstr->array + 2) = 0;
		rmstr->array = REALLOC(rmstr->array, rmstr->len-- - 1);
	}
	if (eqstr(rmstr->array, "\\t"))
	{
		*(rmstr->array)     = '\\';
		*(rmstr->array + 1) = 't';
		*(rmstr->array + 2) = 0;
		rmstr->array = REALLOC(rmstr->array, rmstr->len-- - 1);
	}
	if (eqstr(rmstr->array, "\\0"))
	{
		*(rmstr->array)     = '\\';
		*(rmstr->array + 1) = '0';
		*(rmstr->array + 2) = 0;
		rmstr->array = REALLOC(rmstr->array, rmstr->len-- - 1);
	}
	rmsubstr_all(rmstr, filter); 		   // Remove all substrings from 'filter'
	if (!newfile || eqstr(newfile, ""))
		newfile = "result.filter";
	writefile(newfile, CREATE, filter);	   // Print result to a file
	free_bytes(&filter);			   // Free byte array holding filtered file contents
}

#endif
