#ifndef BYTES_H
#define BYTES_H

#include "basic.h"

#define iswhitespace(x)	((x >  8 && x < 14) || x == 32)
#define isnum(x)    	 (x > 47 && x < 58)
#define isalphanum(x)  	((x > 47 && x < 58) || (x > 64 && x < 91) || (x > 96 && x < 123))
#define isal(x)	    	((x > 64 && x < 91) || (x > 96 && x < 123))

#define FREEFRONT 	3	// For 'concatbytes'
#define FREEBACK  	2
#define FREEOLD   	1		
#define NOFREEOLD 	0

#define RIGHT		1	// For 'rotatestr' and 'replacebytes'
#define LEFT		0

#define POINTER		1	// For 'getword'
#define WORD		0

#define COPYBYTES	1
#define NOCOPYBYTES	0

#define NULTERMINATOR   -1	// For 'concatbytes'

#define CIPHER_SPIN	(77)	// For 'encrypt7' and 'decrypt7'

struct bytes // NEVER CHANGE THIS STRUCTURE (DIRECTORY TRANSFER operations rely on the Bytes object shape in memory)
{
	unsigned long long int len;
	char* array;
};
typedef struct bytes Bytes;

// BYTES MACROS

#define FIRSTCHAR(Bytes_ptr) (*((Bytes_ptr)->array))
#define LASTCHAR(Bytes_ptr)  (*((Bytes_ptr)->array + (Bytes_ptr)->len - 1))


// Print tools
void PRINTBYTES(Bytes* ptr)
{
	if (!goodptr(ptr, "NULLPTR PTR GIVEN TO PRINTBYTES", FUNC_RETURN))
		return;
	unsigned long long int i;
	for (i = 0; i < ptr->len; ++i)
	{
		if (!(*(ptr->array + i)))
			printf("NUL");
		else
			putchar(*(ptr->array + i));
	}
	//printf("\n%lld in length\n", ptr->len);
	PLN(1);
}		  // BYTES

void PRINTHEXBYTES(Bytes* ptr)
{
	if (!goodptr(ptr, "NULLPTR PTR GIVEN TO PRINTHEXBYTES", FUNC_RETURN))
		return;
	unsigned long long int i;
	for (i = 0; i < ptr->len; ++i)		// To make spacing even, check if 1 digit or 2 digits
	{
		if ((0x000000ff & *(ptr->array + i)) > 0xf) printf("%x ",  (unsigned int)(0x000000ff & *(ptr->array + i)));
		else 					    printf(" %x ", (unsigned int)(0x000000ff & *(ptr->array + i)));
		if (i % 45 == 0 && i)
			PLN(1);
	}
	PLN(2);
}		  // HEXBYTES


// char* compatible
char* movewhilenul(char* bytes)	// Checks initial value
{
	while (!(*(bytes))) ++bytes;
	return bytes;
}

char* moveuntilnul(char* bytes)	// Skips initial value
{
	while (*(++bytes));
	return bytes;
}

int countuntilnul(char* bytes)	// Beats strlen over the head with a sledgehammer
{
	if (!bytes)
		return 0;
	register long long int i = 0;
	while (*(bytes++))
		++i;
	return i;
}
char bytescmp_wnul(char* s1, char* s2) // Beats strcmp over the head with a sledgehammer
{
	if (!s1 && !s2)
		return 0;
	if (!s1 || !s2)
		return 1;

	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return 1;
		else
		{ 
			++s1; 
			++s2; 
		}
	}

	if (*s1 || *s2)	// If one string is longer (return 1 == NOT EQUAL)
		return 1;
	return 0;	
}
int bytescpy_wnul(char* s1, char* s2) // Beats strcpy over the head with a sledgehammer
{
	if (!s1 || !s2)
		return 0;
	char* holder = s1;
	while (*s2)
	{
		*s1 = *(s2++);
		++s1;
	}
	*s1 = 0;	// Assign nuls	
	return abs(s1 - holder);
}
char* nbytesto(char* dest, char* src, unsigned long long int len)
{
	if (!len)
		return dest;
	goodptr(dest, "NULLPTR DEST GIVEN TO NBYTESTO", NOFUNC_RETURN);
	if (!goodptr(src, NOMSG, FUNC_RETURN) || dest == src)
		return dest;

	register unsigned long long int blocks   = len / sizeof(unsigned long long int);		// Hold number of 8-byte 'blocks' to copy
	register unsigned long long int leftover = len % sizeof(unsigned long long int);		// Hold number of 'leftover' bytes
	register unsigned long long int i;
	if (dest > src && dest < (src + len))	   // If destination is in the middle of the src string, do what is in the "else" clause but backwards
	{
		unsigned long long int* destptr = (unsigned long long int*)(dest);		// long long integer pointer to beginning of 'dest'
		unsigned long long int* srcptr  = (unsigned long long int*)(src);		// long long integer pointer to beginning of 'src'
		for (i = 1; i <= leftover; ++i)
			*(dest + len - i) = *(src + len - i);
		for (i = blocks - 1; i >= 0; --i)
			*(destptr + i) = *(srcptr + i);
	}
	else
	{
		unsigned long long int* destptr = (unsigned long long int*)(dest);		// long long integer pointer to beginning of 'dest'
		unsigned long long int* srcptr  = (unsigned long long int*)(src);		// long long integer pointer to beginning of 'src'
		for (i = 0; i < blocks; ++i)				// Write to destination in 8-byte blocks
			*(destptr + i) = *(srcptr + i);			// e.g. "thisisastring" : copies "thisisas" in one shot
		for (i = leftover; i > 0; --i)				// Write 'leftover' bytes to destination
			*(dest + len - i) = *(src + len - i);
	}
	return dest;
}

char containschar(char c, char* str, unsigned long long int sz)	// Returns true as soon as 1 matching char is found to be contained by 'str'
{
	while (sz)
		if (*(str + (--sz)) == c)	// Dark magic
			return 1;
	return 0;
}

char containschars(char* cstr, char* str, unsigned long long int sz)	// Returns true as soon as 1 of the char values in c-string parameter 'cstr' match with a char value within 'str'
{
	register int clen = countuntilnul(cstr);
	while (sz)
		if (containschar(*(str + (--sz)), cstr, clen))	// Dark magic
			return 1;
	return 0;
}

char* findchar(char c, char* str, unsigned long long int sz)	 // Returns pointer to character of string that matches searched-for char value in parameter 'c'
{
	register long long int i = -1;
	while (++i < sz)
		if (*(str + i) == c)			// Dark magic
			return (str + i);
	return NULLPTR;
}

char* findchars(char* cstr, char* str, unsigned long long int sz)  // Returns pointer to character of string that matches any searched-for char values in c-string parameter 'cstr'
{
	register int clen = countuntilnul(cstr);
	register long long int i = -1;
	while (++i < sz)
		if (containschar(*(str + i), cstr, clen)) // Dark magic
			return (str + i);
	return NULLPTR;
}

void zeroarray(char* ptr, long long int len)	// Zeros out an array
{
	//register long long int i = EMPTY;		// Offset to calibrate indexing
	//while (++i < len)				// Increment before comparing (so -1 is never compared, only 0 and up)
	//	*(ptr + i) ^= *(ptr + i);		// Dereferencing is way faster than indexing

	register unsigned long long int blocks    = len / sizeof(unsigned long long int);	// Hold number of 8-byte 'blocks' to copy
	register unsigned long long int leftover  = len % sizeof(unsigned long long int);	// Hold number of 'leftover' bytes
	unsigned long long int* blockptr = (unsigned long long int*)(ptr);			// long long integer pointer to beginning of 'ptr'
	register unsigned long long int i;

	for (i = 0; i < blocks; ++i)	// Write zero out array in 8-byte blocks
		*(blockptr + i) = 0;	// e.g. "thisisastring" : zeros out "thisisas" in one shot
	for (i = 1; i <= leftover; ++i)	// Write 'leftover' bytes starting from the last position
		*(ptr + len - i) = 0;   // Zeros out 'leftover' bytes
}

// Creation tools
Bytes* static_bytes(char* bytes, long long int num)	// Make insert byte array without creating new string on the heap
{
	if (num < 0)					// Check if 'num' is zero
		return NULLPTR;	
	Bytes* neword = MALLOC(sizeof(Bytes)); 		// Make space for struct
	neword->array = bytes;
	neword->len   = num; 				// Set length
	return neword;	   				// Return heap byte array
}
Bytes* dynamic_bytes(char* bytes, long long int num)	// Make byte array in heap [Length ACCESSIBLE]
{
	if (num < 0)							// Check if bad pointer or num is zero
		return NULLPTR;	
	Bytes* neword = MALLOC(sizeof(Bytes)); 		 		// Make space for struct
	neword->array = MALLOC(num + 1);				// Make space for array and nul
	if (bytes)	   						// Fill only if needed
		neword->array = nbytesto(neword->array, bytes, num); 	// Copy byte array into heap location
	neword->len = num; 					     	// Set length
	*(neword->array + num) = 0;					// Nul-terminate
	return neword;	   						// Return heap byte array
}
int free_static(Bytes** ptr)	// Frees bytes but not 'array' member
{
	if ((*ptr))
	{
		(*ptr)->array = NULLPTR;	// For compatibility with other programmer code
		(*ptr)->len   = 0;
		FREE(ptr);		
		ptr = NULLPTR;			// For compatibility with other programmer code
		return 1;
	}
	return 0;
}
int free_bytes(Bytes** ptr)	// Frees bytes and 'array' member
{
	if ((*ptr))
	{
		FREE(&((*ptr)->array));
		(*ptr)->array = NULLPTR;	// For compatibility with other programmer code
		(*ptr)->len   = 0;
		FREE(ptr);		
		ptr = NULLPTR;			// For compatibility with other programmer code
		return 1;
	}
	return 0;
}
Bytes* copy_bytes(Bytes* ptr)	// Copies Bytes data to and returns a new Bytes instance
{
	if (!ptr)						// Check if bad pointer or num is zero
		return NULLPTR;	
	register unsigned long long int len = ptr->len;		// Place in register for speed
	Bytes* neword = MALLOC(sizeof(Bytes)); 		 	// Make space for struct
	neword->array = MALLOC(len + 1);			// Make space for array (ALL Bytes classes will have a nonzero, positive value, it is ensured by the "dynamic_bytes" function above)
	if (ptr->array)								// Fill only if needed
		neword->array = nbytesto(neword->array, ptr->array, len);	// Copy byte array into new Bytes struct
	neword->len = len; 					     		// Set length
	*(neword->array + len) = 0;						// Nul-terminate
	return neword;		   						// Return heap byte array
}

/* ************************ OPERATIONS ************************ */

// Prototype
Bytes* concatbytes(Bytes* front, Bytes* back, char between, char freeold);

char eqstr(char* s1, char* s2) { return !bytescmp_wnul(s1, s2); }	// Wrapper for bytescmp_wnul()
char eqbytes(Bytes* s1, Bytes* s2)
{
	if (!s1 && !s2)
		return 1;
	if (!s1 || !s2)
		return 0;
	if (s1->len != s2->len)	
		return 0;

	register unsigned long long int blocks    = s1->len / sizeof(unsigned long long int);	// Hold number of 8-byte 'blocks' to copy
	register unsigned long long int leftover  = s1->len % sizeof(unsigned long long int);	// Hold number of 'leftover' bytes
	unsigned long long int* s1ptr    = (unsigned long long int*)(s1->array);	// long long integer pointer to beginning of 's1->array'
	unsigned long long int* s2ptr    = (unsigned long long int*)(s2->array);	// long long integer pointer to beginning of 's2->array'
	register unsigned long long int i;

	for (i = 0; i < blocks; ++i)	// Compare strings 8 bytes at a time
		if (*(s1ptr + i) != *(s2ptr + i))
			return 0;
	for (i = 1; i <= leftover; ++i)	// Compare 'leftover' bytes starting from the last position
		if (*(s1->array + s1->len - i) != *(s2->array + s1->len - i))	// Use 's1->len' for indexing 's2->array' because its most likely stored in cache memory
			return 0;
	return 1;
}

char fastmatch(char* strptr1, char* strptr2, unsigned long long int len)	// Returns '1' if strings are equal (counter-intuitive to 'memcmp' usage)
{
	if (!strptr1 && !strptr2)
		return 1;
	if (!strptr1 || !strptr2)
		return 0;
	register unsigned long long int blocks    = len / sizeof(unsigned long long int);	// Hold number of 8-byte 'blocks' to copy
	register unsigned long long int leftover  = len % sizeof(unsigned long long int);	// Hold number of 'leftover' bytes
	unsigned long long int* s1ptr    = (unsigned long long int*)(strptr1);	// long long integer pointer to beginning of 'strptr1'
	unsigned long long int* s2ptr    = (unsigned long long int*)(strptr2);	// long long integer pointer to beginning of 'strptr2'
	register unsigned long long int i;
	for (i = 0; i < blocks; ++i)	// Compare strings 8 bytes at a time
		if (*(s1ptr + i) != *(s2ptr + i))
			return 0;
	for (i = 1; i <= leftover; ++i)	// Compare 'leftover' bytes starting from the last position
		if (*(strptr1 + len - i) != *(strptr2 + len - i))
			return 0;
	return 1;
}

Bytes* extractstr(char* f, char* b)	// Extract and make new string from substring in string 
{					// (parameters must be valid pointers and "b" points to next character in the larger string)
	if (!f || !b)
		return NULLPTR;
	if (!(f - b))
		return NULLPTR;
	unsigned long long int len = abs((int)(f - b));
	Bytes* neword = dynamic_bytes(f, len);
	return neword;
}

Bytes* substr(Bytes* str, Bytes* origin)	// Returns substring in string (must be freed thereafter)
{
	if (!str || !origin)
		return NULLPTR;
	register unsigned long long int slen = str->len;	// Distance in bytes between f and b, holder will hold string of bytes between f and b (b inclusive)
	register unsigned long long int olen = origin->len;
	if (slen > olen)
		return NULLPTR; // THROW("SUBSTRING TO BE FOUND SHOULD BE LESS THAN OR EQUAL TO ORIGINAL STRING");
	char* f = origin->array;				// Assign array pointer
	while (f <= (char*)(origin->array + olen - slen))	// While not passed the end of the original string
	{
		if (fastmatch(f, str->array, slen))
			return dynamic_bytes(f, slen);
		++f;
	}
	return NULLPTR;
}

char* substr_loc(Bytes* str, Bytes* origin)	// Returns pointer to substring in string
{
	if (!str || !origin)
		return NULLPTR;
	register unsigned long long int slen = str->len;	// Distance in bytes between f and b, holder will hold string of bytes between f and b (b inclusive)
	register unsigned long long int olen = origin->len;
	if (slen > olen)
		return NULLPTR; 	// THROW("SUBSTRING TO BE FOUND SHOULD BE LESS THAN OR EQUAL TO ORIGINAL STRING");
	char* f = origin->array;	// Assign struct copy (array pointer is copied)
	while (f <= (char*)(origin->array + olen - slen))	// While not passed the end of the original string
	{
		if (fastmatch(f, str->array, slen))
			return f;		// Holds address in origin's array at which substring begins
		++f;
	}
	return NULLPTR;
}

int numsubstr(Bytes* str, Bytes* origin)	// Find number of all substrings in a string
{
	register int i = 0;					// Holds count		
	char* ptr = substr_loc(str, origin);			// Get first instance of substring in string
	register unsigned long long int len = origin->len;	// Set length for quicker memory accesses
	while (ptr)						// While another instance found, count it
	{
		char* holdptr = ptr;				// Save pointer's previous position pointing to somewhere in origin's byte array
		Bytes* holder = dynamic_bytes(ptr, (unsigned long long int)(len - abs(ptr - origin->array)));  // Create new Bytes object with only unchecked portion of byte array
		ptr = substr_loc(str, holder);			// "ptr" is pushed farther down the string
		if (!ptr)					// If substring instance not found	
			break;
		ptr = holdptr + abs(ptr - holder->array) + str->len; 		// Move pointer passed the substring found.
		free_bytes(&holder);			// Free unecessary heap memory to prevent mem. leak
		++i;    				// Each substring instance is counted
	}
	return i;
}

char* delsubstr(Bytes* origin, char* f, char* b)	// Deletes string between 'f' and 'b' pointers (string must be dynamicly allocated with NULL) (PTRS alread validated by "rmsubstr")
{
	goodptr(origin, "NULLPTR ORIGIN GIVEN TO DELSUBSTR", NOFUNC_RETURN);
	if (origin->len == abs(f - b))	// Check if will become empty string, then zero out everything.
	{ 
		FREE(&(origin->array)); 
		origin->array = NULLPTR; 
		origin->len = 0; 
		return NULLPTR;
	}
	register int frontpiece = abs(f - origin->array);
	register int backpiece = origin->len - abs(b - origin->array);	// Example: Take out "str" from "butterstrfly" ---> Front piece = "butter" | Backpiece = "fly"
	char* newarray = MALLOC(frontpiece + backpiece + 1);		// Make space
	nbytesto(newarray, origin->array, frontpiece);			// Copy up to front of substring to be deleted
	nbytesto(newarray + frontpiece, b, backpiece);			// Start after end of substring and continue copying
	newarray[frontpiece + backpiece] = 0;				// Nul
	FREE(&(origin->array));						// Get rid of old array
	origin->array = newarray;
	origin->len = frontpiece + backpiece;
	return origin->array;						// Return char* pointer to array
}

Bytes* rmsubstr(Bytes* str, Bytes* origin)	// Returns pointer to Bytes object without an instance of the specified substring
{
	char* holder = substr_loc(str, origin);	// Find string
	if (holder)
		delsubstr(origin, holder, holder + str->len);	// Delete
	return origin;
}

char* rmsubstr_loc(Bytes* str, Bytes* origin)	// Returns pointer to the location of where the string was removed 
{
	char* holder = substr_loc(str, origin);
	if (holder)
	{
		delsubstr(origin, holder, holder + str->len);	// Delete
		return origin->array;
	}
	else
		return NULLPTR;
}

int rmsubstr_all(Bytes* str, Bytes* origin)	// Removes all substrings from byte object and returns number of substrings removed
{
	char* holder;
	register int i = 0;
	do
	{
		holder = rmsubstr_loc(str, origin);	// Delete until none left
		++i;					// Count removal
	} while (holder);
	return --i;
}

void scanreplace(Bytes* bytes, char bad, char good)
{
	register unsigned long long int i;
	register unsigned long long int len = bytes->len;
	for(i = 0; i < len; ++i)
		if(*(bytes->array+i) == bad)
			(*(bytes->array+i)) = good;
}

Bytes* concatbytes(Bytes* front, Bytes* back, char between, char freeold) // Attach 2 strings together, place a "between" character in the middle, choose whether to discard old strings
{
	register unsigned long long int flen = 0;
	if (!back) 						// Return if no piece exists to concatenate
		return NULLPTR;	
	if (front)
		flen = front->len;				// For efficient mem. accesses
	int space = flen + back->len + (between != 0); 		// +1 if "between" is set to a character
	Bytes* neword = dynamic_bytes(NULLPTR, space);
	if (front && flen)				
		nbytesto(neword->array, front->array, flen);
	if (between)						// Insert "between" character
		*(neword->array + flen) = (between * (between != NULTERMINATOR));
	nbytesto(neword->array + flen + (between != 0), back->array, back->len); // Connect strings + in between character if present
	switch(freeold)	// Check for freeing the input strings
	{
		case FREEOLD   : free_bytes(&front); free_bytes(&back); return neword;	// The "FREE" wrapper in "free_bytes" prevents freeing of any potential NULLPTRS
		case FREEFRONT : free_bytes(&front); 		        return neword;
		case FREEBACK  : free_bytes(&back);		        return neword;
	}
	return neword; // Return new string
}

Bytes* appendstr(Bytes* bstr, char* str, int len)
{
	if (!bstr)	// If no 'bstr' just make it from scratch
		return dynamic_bytes(str, len);
	bstr->array = REALLOC(bstr->array, bstr->len + len + 1);	// Make more space
	nbytesto(bstr->array + bstr->len, str, len);			// Append string
	bstr->len += len;						// Update length
	*(bstr->array + bstr->len) = 0;					// Nul-terminate
	return bstr;
}

char* copystr(Bytes* str)		// Returns copy of a Bytes class byte array
{
	goodptr(str, "NULLPTR STR GIVEN TO COPYSTR", NOFUNC_RETURN);
	char* newarray = MALLOC(str->len + 1);
	newarray = nbytesto(newarray, str->array, str->len + 1);
	*(newarray + str->len) = 0;
	return newarray;
}

Bytes* appendctostr(Bytes* str, char c)		// Returns Bytes* pointer to array that was just modified
{
	if (!str) 	// If no 'str' just make it from scratch
	{
		Bytes* holder = dynamic_bytes(NULLPTR, 1);
		*(holder->array) = c;
		return holder;
	}
	str->array = REALLOC(str->array, str->len + 1 + 1); // one for extra char and one for nul
	*(str->array + str->len++) = c;		      	    // Don't forget to increment Bytes class stored length
	*(str->array + str->len)   = 0;			    // Nul-terminate
	return str;
}

Bytes* prependctostr(char c, Bytes* str)  // Returns Bytes* pointer to string that was just modified
{
	if (!str)
	{
		Bytes* holder = dynamic_bytes(NULLPTR, 1);
		*(holder->array) = c;
		return holder;
	}
	str->array = REALLOC(str->array, str->len + 2);  // one for extra char and one for nul
	nbytesto(str->array + 1, str->array, str->len++);    // Don't forget to increment Bytes class stored length
	*(str->array + str->len) = 0;			     // Nul
	*str->array              = c; 
	return str;
}

Bytes* unpendleft(Bytes* str)
{
	goodptr(str, "NULLPTR FILE STRING GIVEN TO UNPENDLEFT", NOFUNC_RETURN);
	Bytes* neword = dynamic_bytes((str->array + 1), str->len - 1);
	str->array = REALLOC(str->array, str->len);
	*(str->array + (--str->len)) = 0;
	nbytesto(str->array, neword->array, str->len);
	free_bytes(&neword);
	return str;
}

Bytes* unpendright(Bytes* str)
{
	goodptr(str, "NULLPTR FILE STRING GIVEN TO UNPENDRIGHT", NOFUNC_RETURN);
	str->array = REALLOC(str->array, str->len);
	*(str->array + (--str->len)) = 0;
	return str;
}

Bytes* chop(Bytes* str, char* ptr)	// Remove contents at and after ptr (MUST USE ASSIGNMENT IN CASE POINTER IS FREED)
{
	if (!ptr || !str)	// If bad pointers
		return str;
	if (ptr == str->array)
	{
		free_bytes(&str);
		return NULLPTR;
	}
	register long long int newlen = abs(ptr - str->array);	// Get new length before moving pointer (REALLOC may more the array pointer in the bytes object)
	if (newlen > str->len)	// If 'ptr' is past end of 'str' array
		return str;
	if (ptr < str->array)
		THROW("**yelling** WHAT SYSTEM HAS STRINGS THAT HAVE DECREASING MEMORY INDEX NUMBERS");
	zeroarray(ptr, str->len - newlen); 		  	// Zero out chopped portion (Supports cleaner memory usage)
	str->array = REALLOC(str->array, newlen + 1);	  	// Reallocate correct space needed including an extra for the Nul-terminator
	*(str->array + str->len) = 0;			  	// Nul-terminate
	str->len   = newlen;				  	// Update string length
	return str;
}

// RIGHT 1
// LEFT  0
void replacebytes(Bytes* origin, Bytes* bytes, long long int offset, char directionfromoffset)	// Starts replacing bytes at specified byte (e.g. forwards  : offset is 2nd byte --> actual offset is +1 from array pointer)
{						//					    					    (e.g. backwards : offset is 45th spot out of 50 --> actual offset is -offset from nul-terminator spot)
	goodptr(origin, "NULLPTR ORIGIN GIVEN TO REPLACEBYTES", NOFUNC_RETURN);	
	if(!goodptr(bytes, "NULLPTR BYTES GIVEN TO REPLACEBYTES", FUNC_RETURN))
		return;
	if (offset > origin->len)
	{
		PRINT("OFFSET LARGER THAN ORIGINAL STRING LENGTH IN REPLACEBYTES");
		return;
	}
	if (abs(((long long int)(origin->array + offset) * (directionfromoffset == 1) + (long long int)(origin->array + origin->len  - offset) * (!directionfromoffset)) - (long long int)origin->array) + bytes->len > origin->len)	// Light switch logic depends on 'directionfromoffset'
	{
		PRINT("REPLACEMENT BYTESTRING LENGTH GOES PAST ORIGIN BOUNDARIES IN REPLACEBYTES");
		return;
	}
	if (directionfromoffset)	// If right
		nbytesto(origin->array + offset, bytes->array, bytes->len);
	else				// If left
		nbytesto(origin->array + origin->len - offset, bytes->array, bytes->len);
}

Bytes* splitbytes(Bytes* origin, char* divideptr)	// Split bytes into 2 objects (Front portion is assigned to origin, back portion is returned as a 'Bytes' pointer)
{
	goodptr(origin, "NULLPTR ORIGIN GIVEN TO SPLITBYTES", NOFUNC_RETURN);		    // Check original pointer
	if (!goodptr(divideptr, "NULLPTR SPLIT POSITION GIVEN TO SPLITBYTES", FUNC_RETURN)) // Check position pointer
		return NULLPTR;		
	register long long int ptr_offset_fromfront = abs(divideptr - origin->array);	    // Get offset from start
	register long long int ptr_offset_fromback  = origin->len - ptr_offset_fromfront;   // Get offset from end
	if (ptr_offset_fromfront > origin->len || divideptr < origin->array)		    // Check that 'ptr' is within byte string boundaries
	{
		PRINT("SPLIT POSITION IS OUT OF ORIGIN BOUNDARIES IN SPLITBYTES");
		return NULLPTR;
	}
	Bytes* secondportion = dynamic_bytes(divideptr, ptr_offset_fromback);		  // Copy back end to its own memory object
	origin->array = REALLOC(origin->array, ptr_offset_fromfront + 1);		  // Reallocate memory for front portion
	*(origin->array + ptr_offset_fromfront) = 0;					  // Nul-terminate front portion
	origin->len = ptr_offset_fromfront;
	return secondportion;
}

// FREEOLD   1
// NOFREEOLD 0
Bytes* insertbytes(Bytes** newbytes, Bytes** origin, char* divideptr, long long int (*sectionremover)(char*, long long int), char freeold)
{
	register long long int numtoremove = 0;
	goodptr(origin, "NULLPTR ORIGIN ADDRESS GIVEN TO INSERTBYTES", NOFUNC_RETURN); 	   // Check 'origin' pointer address
	goodptr(*origin, "NULLPTR ORIGIN GIVEN TO INSERTBYTES", NOFUNC_RETURN);		   // Check 'origin' pointer address
	goodptr(newbytes, "NULLPTR NEWBYTES ADDRESS GIVEN TO INSERTBYTES", NOFUNC_RETURN); // Check 'newbytes' pointer address
	goodptr(*newbytes, "NULLPTR NEWBYTES GIVEN TO INSERTBYTES", NOFUNC_RETURN);	   // Check 'newbytes' pointer
	if (!goodptr(divideptr, "NULLPTR SPLIT POSITION GIVEN TO SPLIT", FUNC_RETURN))	   // Check position pointer
		return NULLPTR;
	register long long int ptr_offset_fromfront = abs(divideptr - (*origin)->array);	   // Get offset from start
	register long long int ptr_offset_fromback  = (*origin)->len - ptr_offset_fromfront;  // Get offset from end
	if (ptr_offset_fromfront > (*origin)->len || divideptr < (*origin)->array)		   // Check that 'ptr' is within byte string boundaries
	{
		PRINT("INSERT POSITION IS OUT OF ORIGIN BOUNDARIES IN INSERTBYTES");
		return NULLPTR;
	}
	
	if (sectionremover)	// Functions passed in should be from "parser.h" [ no need to include parser.h in this file cause we usin' function pointers :) ]
		numtoremove = sectionremover(divideptr, ptr_offset_fromback);
	Bytes* neworigin = dynamic_bytes(NULLPTR, (*origin)->len + (*newbytes)->len - numtoremove);
	nbytesto(neworigin->array, (*origin)->array, ptr_offset_fromfront);
	nbytesto(neworigin->array + ptr_offset_fromfront, (*newbytes)->array, (*newbytes)->len);
	nbytesto(neworigin->array + ptr_offset_fromfront + (*newbytes)->len, (*origin)->array + ptr_offset_fromfront + numtoremove, ptr_offset_fromback - numtoremove);
	if (freeold)
		free_bytes(newbytes);
	return neworigin;
}

// POINTER 1
// WORD	   0
Bytes* getword(int n, Bytes* str, char justpointer)	// Gets nth word in string
{
	register int w = 0; 			// Holds number of words already scanned in string
	register unsigned long long int i = 0;	// Holds string index
	Bytes* neword = NULLPTR;
	if (!str)
		return NULLPTR;
	while(w < n && i < str->len)
	{
		if (iswhitespace(*(str->array + i)))
			++i;
		else if (++w == n)
		{
			if (justpointer)
				return (Bytes*)(str->array + i);
			while(!iswhitespace(*(str->array + i)) && i < str->len)
				neword = appendctostr(neword, *(str->array + (i++)));	// Will make a single character byte array first time
			return neword;
		}
		else
			while (!iswhitespace(*(str->array + i)) && i < str->len)	// Skip word to next whitespace
				++i;
	}	
	return neword;
}

#ifndef MAP_STRNUM_H
#define MAP_STRNUM_H
char* map_decnum_tostr(long long int num, int numdigits) // Function that makes an ascii string representing value in decimal, with a padded amount of digits --> "numdigits"
{ // 18 digits only for the first parameter
	char* newarray = NULLPTR;		// Holds new string
	register long long int digits = 1;	// Tracks number of digits
	register unsigned int i = 0;		// Counts digits and tracks indexing from 'newarray'
	while (num / digits != 0)		// Check to the highest 10th power before going over as a divisor
	{ digits *= 10; ++i; }
	digits /= 10;	// Set back down by 1 power of 10
	register int zeros = (numdigits * (numdigits > 0)) - i;	// Get specified number of padded zeros
	newarray = MALLOC(i + 1 + zeros);		// Get space, +1 for Nul-terminator
	newarray[i + zeros] = '\0';			// Nul-terminate
	for(i = 0; i < zeros; ++i)			// Insert zeros			
		newarray[i] = 0x30;
	while (digits != 0)				// While not all digits placed into 'newarray'
	{
		newarray[i++] = num / digits + 0x30;	// Offset to ASCII value
		num -= ((num / digits) * digits);
		digits /= 10;				// Go down by a power of 10
	}
	return newarray;
}

long long int map_decstr_tolonglongint(Bytes* str) // Dark Magic --> String must only contain numbers (up to 8 digits only)(only dynamic - test more for data section strings)
{
	goodptr(str, "NULLPTR STR GIVEN TO MAP_DECSTR_TOLONGLONGINT", NOFUNC_RETURN);
	register long long int chosen = 0;
	register long long int shift = 0x100;
	register unsigned long long int i;
	register unsigned long long int j;
	register long long int holder;
	for (i = str->len - 1; i >= 0; --i)
	{
		holder = (int)str->array[i];
		for (j =  str->len - 1; j > i; --j)
			holder *= shift; 
		chosen |= holder;
	}
	return chosen;
}
#endif

// ************************************************ ENCRYPTION ************************************************ // 

#ifndef ENCRYPTION_H
#define ENCRYPTION_H

Bytes* reflectstr(Bytes* str)	// Reverse the string
{
	if (!str) return str;	// If no ptr return parameter itself
	int i = 1;
	while(i < str->len)	// While not at beginning of 'str'
		*(str->array + (i++)) += *(str->array + (str->len - i)) - (*(str->array + (str->len - i)) = *(str->array + i));	// ONE LINE SWAP LIKE A BOSS
	return str;
}

Bytes* ccipherstr(Bytes* str, int num)	// Ciphers through and upto (unsigned char)(255) characters, then starts back at (unsigned char)(1)
{
	if (!str) return str;		// If no string return string
	char* ptr = str->array;
	register unsigned long long int len = str->len;
	register unsigned long long int i;
	for (i = 0; i < len; ++i)
	{
		*(ptr + i) = (char)(MOD((int)((*(ptr + i)) + num), 256));
//		if (!(*(ptr + i)) && num > 0)
//			++(*(ptr + i));
//		if (!(*(ptr + i)) && num < 0)
//			(*(ptr + i)) = 255;
	}
	return str;
}

// Surpisingly useful

// COPYBYTES   1
// NOCOPYBYTES 0
Bytes* replacecwith(char original, char b, Bytes* str, char retcopy)
{
	Bytes* holder = str;
	if (retcopy)
		holder = copy_bytes(str);
	register unsigned long long int x = holder->len;
	register unsigned long long int i = 0;
	for (i; i < x; ++i)
		if (*(holder->array + i) == original)
			*(holder->array + i) = b;
	return holder;
}

// RIGHT 1
// LEFT	 0
Bytes* rotatestr(Bytes* str, char dir, int num)	// Rotates string by "num" shifts in direction "dir"
{
	if (!str) return NULLPTR;				// If no string return NULLPTR
	register unsigned long long int len = str->len;		// Gets string length
	if (!MOD(num, len)) return str;				// Checks if no work is needed
	num = abs(MOD((-(!dir) * num + num * dir), len));	// Calibrates char array offset
	char* holder = MALLOC(len);				// Makes a bucket
	register unsigned long long int i;
	for (i = 0; i < len; ++i)
		*(holder + MOD((i + num), len)) = *(str->array + i);	// Fills string with calculated rotation
	str->array = nbytesto(str->array, holder, len);			// Copies result to original string
	FREE(&holder);				 			// Deletes bucket
	return str;
}

// CIPHER_SPIN 77
Bytes* encrypt7(Bytes* str)
{
	if (!str) return NULLPTR;		// If no string return NULLPTR
	rotatestr(str, LEFT, str->len / 2);	
		 reflectstr(str);
			 ccipherstr(str, CIPHER_SPIN);
	return str;
}

Bytes* decrypt7(Bytes* str)
{
	if (!str) return NULLPTR;		// If no string return NULLPTR
	ccipherstr(str, -CIPHER_SPIN);
		reflectstr(str);
			rotatestr(str, RIGHT, str->len / 2);
	return str;
}
#endif	// For ENCRYPTION_H

#endif
