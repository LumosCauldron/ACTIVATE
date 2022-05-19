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

struct bytes // NEVER CHANGE THIS STRUCTURE (DIRECTORY TRANSFER operations rely on the Bytes object shape in memory)
{
	u64 len;
	u8* array;
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
	u64 i;
	for (i = 0; i < ptr->len; ++i)
	{
		if (!(*(ptr->array + i)))
			printf("NUL");
		else
			putchar(*(ptr->array + i));
	}
	//printf("\n%lld in length\n", ptr->len);
	PLN(1);
} // BYTES

void PRINTHEXBYTES(Bytes* ptr)
{
	if (!goodptr(ptr, "NULLPTR PTR GIVEN TO PRINTHEXBYTES", FUNC_RETURN))
		return;
	u64 i;
	register u8 hold;
	for (i = 0; i < ptr->len; ++i)		// To make spacing even, check if 1 digit or 2 digits
	{
		
		hold = *(ptr->array + i);
		if (hold > 0xf) 
			printf("%x ",  hold);
		else 					    
			printf(" %x ", hold);
		if (i % 32 == 0 && i)
			PLN(1);
	}
	PLN(1);
} // HEXBYTES


// char* compatible
u8* movewhilenul(u8* bytes)	// Checks initial value
{
	while (!(*(bytes))) ++bytes;
	return bytes;
}

u8* moveuntilnul(u8* bytes)	// Skips initial value
{
	while (*(++bytes));
	return bytes;
}

i64 countuntilnul(u8* bytes)	// Beats strlen over the head with a sledgehammer
{
	if (!bytes)
		return 0;
	register u64 i = 0;
	while (*(bytes++))
		++i;
	return i;
}
u8 bytescmp_wnul(u8* s1, u8* s2) // Beats strcmp over the head with a sledgehammer
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
u64 bytescpy_wnul(u8* s1, u8* s2) // Beats strcpy over the head with a sledgehammer
{
	if (!s1 || !s2)
		return 0;
	u8* holder = s1;
	while (*s2)
	{
		*s1 = *(s2++);
		++s1;
	}
	*s1 = 0;	// Assign nuls	
	return abs(s1 - holder);
}
u8* nbytesto(u8* dest, u8* src, u64 len)
{
	if (!len)
		return dest;
	goodptr(dest, "NULLPTR DEST GIVEN TO NBYTESTO", NOFUNC_RETURN);
	if (!goodptr(src, NOMSG, FUNC_RETURN) || dest == src)
		return dest;

	register u64 blocks   = len / sizeof(u64);		// Hold number of 8-byte 'blocks' to copy
	register u64 leftover = len % sizeof(u64);		// Hold number of 'leftover' bytes
	register u64 i;
	if (dest > src && dest < (src + len))	   // If destination is in the middle of the src string, do what is in the "else" clause but backwards
	{
		u64* destptr = (u64*)(dest);		// long integer pointer to beginning of 'dest'
		u64* srcptr  = (u64*)(src);		// long integer pointer to beginning of 'src'
		for (i = 1; i <= leftover; ++i)
			*(dest + len - i) = *(src + len - i);
		for (i = blocks - 1; i >= 0; --i)
			*(destptr + i) = *(srcptr + i);
	}
	else
	{
		u64* destptr = (u64*)(dest);		// long integer pointer to beginning of 'dest'
		u64* srcptr  = (u64*)(src);		// long integer pointer to beginning of 'src'
		for (i = 0; i < blocks; ++i)				// Write to destination in 8-byte blocks
			*(destptr + i) = *(srcptr + i);			// e.g. "thisisastring" : copies "thisisas" in one shot
		for (i = leftover; i > 0; --i)				// Write 'leftover' bytes to destination
			*(dest + len - i) = *(src + len - i);
	}
	return dest;
}

u8 containschar(u8 c, u8* str, u64 sz)	// Returns true as soon as 1 matching char is found to be contained by 'str'
{
	while (sz)
		if (*(str + (--sz)) == c)	// Dark magic
			return 1;
	return 0;
}

u8 containschars(u8* cstr, u8* str, u64 sz)	// Returns true as soon as 1 of the char values in c-string parameter 'cstr' match with a char value within 'str'
{
	register u64 clen = countuntilnul(cstr);
	while (sz)
		if (containschar(*(str + (--sz)), cstr, clen))	// Dark magic
			return 1;
	return 0;
}

u8* findchar(u8 c, u8* str, u64 sz)	 // Returns pointer to character of string that matches searched-for char value in parameter 'c'
{
	register i64 i = -1;
	while (++i < sz)
		if (*(str + i) == c)			// Dark magic
			return (str + i);
	return NULLPTR;
}

u8* findchars(u8* cstr, u8* str, u64 sz)  // Returns pointer to character of string that matches any searched-for char values in c-string parameter 'cstr'
{
	register u64 clen = countuntilnul(cstr);
	register i64 i = -1;
	while (++i < sz)
		if (containschar(*(str + i), cstr, clen)) // Dark magic
			return (str + i);
	return NULLPTR;
}

void zeroarray(u8* ptr, u64 len)	// Zeros out an array
{
	register u64 blocks    = len / sizeof(u64);	// Hold number of 8-byte 'blocks' to copy
	register u64 leftover  = len % sizeof(u64);	// Hold number of 'leftover' bytes
	u64* blockptr = (u64*)(ptr);			// long integer pointer to beginning of 'ptr'
	register u64 i;

	for (i = 0; i < blocks; ++i)	// Write zero out array in 8-byte blocks
		*(blockptr + i) = 0;	// e.g. "thisisastring" : zeros out "thisisas" in one shot
	for (i = 1; i <= leftover; ++i)	// Write 'leftover' bytes starting from the last position
		*(ptr + len - i) = 0;   // Zeros out 'leftover' bytes
}

// Creation tools
Bytes* static_bytes(u8* bytes, i64 num)	// Make insert byte array without creating new string on the heap
{
	if (num < 0)					// Check if 'num' is zero
		return NULLPTR;	
	Bytes* neword = MALLOC(sizeof(Bytes)); 		// Make space for struct
	neword->array = bytes;
	neword->len   = num; 				// Set length
	return neword;	   				// Return heap byte array
}
Bytes* dynamic_bytes(u8* bytes, i64 num)	// Make byte array in heap [Length ACCESSIBLE]
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
	register u64 len = ptr->len;		// Place in register for speed
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
Bytes* concatbytes(Bytes* front, Bytes* back, u8 between, u8 freeold);

u8 eqstr(u8* s1, u8* s2) { return !bytescmp_wnul(s1, s2); }	// Wrapper for bytescmp_wnul()
u8 eqbytes(Bytes* s1, Bytes* s2)
{
	if (!s1 && !s2)
		return 1;
	if (!s1 || !s2)
		return 0;
	if (s1->len != s2->len)	
		return 0;

	register u64 blocks    = s1->len / sizeof(u64);	// Hold number of 8-byte 'blocks' to copy
	register u64 leftover  = s1->len % sizeof(u64);	// Hold number of 'leftover' bytes
	u64* s1ptr    = (u64*)(s1->array);	// long integer pointer to beginning of 's1->array'
	u64* s2ptr    = (u64*)(s2->array);	// long integer pointer to beginning of 's2->array'
	register u64 i;

	for (i = 0; i < blocks; ++i)	// Compare strings 8 bytes at a time
		if (*(s1ptr + i) != *(s2ptr + i))
			return 0;
	for (i = 1; i <= leftover; ++i)	// Compare 'leftover' bytes starting from the last position
		if (*(s1->array + s1->len - i) != *(s2->array + s1->len - i))	// Use 's1->len' for indexing 's2->array' because its most likely stored in cache memory
			return 0;
	return 1;
}

u8 fastmatch(u8* strptr1, u8* strptr2, u64 len)	// Returns '1' if strings are equal (counter-intuitive to 'memcmp' usage)
{
	if (!strptr1 && !strptr2)
		return 1;
	if (!strptr1 || !strptr2)
		return 0;
	register u64 blocks    = len / sizeof(u64);	// Hold number of 8-byte 'blocks' to copy
	register u64 leftover  = len % sizeof(u64);	// Hold number of 'leftover' bytes
	u64* s1ptr    = (u64*)(strptr1);	// long integer pointer to beginning of 'strptr1'
	u64* s2ptr    = (u64*)(strptr2);	// long integer pointer to beginning of 'strptr2'
	register u64 i;
	for (i = 0; i < blocks; ++i)	// Compare strings 8 bytes at a time
		if (*(s1ptr + i) != *(s2ptr + i))
			return 0;
	for (i = 1; i <= leftover; ++i)	// Compare 'leftover' bytes starting from the last position
		if (*(strptr1 + len - i) != *(strptr2 + len - i))
			return 0;
	return 1;
}

Bytes* extractstr(u8* f, u8* b)	// Extract and make new string from substring in string 
{					// (parameters must be valid pointers and "b" points to next character in the larger string)
	if (!f || !b)
		return NULLPTR;
	if (!(f - b))
		return NULLPTR;
	u64 len = abs((int)(f - b));
	Bytes* neword = dynamic_bytes(f, len);
	return neword;
}

Bytes* substr(Bytes* str, Bytes* origin)	// Returns substring in string (must be freed thereafter)
{
	if (!str || !origin)
		return NULLPTR;
	register u64 slen = str->len;	// Distance in bytes between f and b, holder will hold string of bytes between f and b (b inclusive)
	register u64 olen = origin->len;
	if (slen > olen)
		return NULLPTR; // THROW("SUBSTRING TO BE FOUND SHOULD BE LESS THAN OR EQUAL TO ORIGINAL STRING");
	u8* f = origin->array;				// Assign array pointer
	while (f <= (u8*)(origin->array + olen - slen))	// While not passed the end of the original string
	{
		if (fastmatch(f, str->array, slen))
			return dynamic_bytes(f, slen);
		++f;
	}
	return NULLPTR;
}

u8* substr_loc(Bytes* str, Bytes* origin)	// Returns pointer to substring in string
{
	if (!str || !origin)
		return NULLPTR;
	register u64 slen = str->len;	// Distance in bytes between f and b, holder will hold string of bytes between f and b (b inclusive)
	register u64 olen = origin->len;
	if (slen > olen)
		return NULLPTR; 	// THROW("SUBSTRING TO BE FOUND SHOULD BE LESS THAN OR EQUAL TO ORIGINAL STRING");
	u8* f = origin->array;	// Assign struct copy (array pointer is copied)
	while (f <= (u8*)(origin->array + olen - slen))	// While not passed the end of the original string
	{
		if (fastmatch(f, str->array, slen))
			return f;		// Holds address in origin's array at which substring begins
		++f;
	}
	return NULLPTR;
}

u32 numsubstr(Bytes* str, Bytes* origin)	// Find number of all substrings in a string
{
	register u32 i = 0;					// Holds count		
	u8* ptr = substr_loc(str, origin);			// Get first instance of substring in string
	register u64 len = origin->len;	// Set length for quicker memory accesses
	while (ptr)						// While another instance found, count it
	{
		u8* holdptr = ptr;				// Save pointer's previous position pointing to somewhere in origin's byte array
		Bytes* holder = dynamic_bytes(ptr, (u64)(len - abs(ptr - origin->array)));  // Create new Bytes object with only unchecked portion of byte array
		ptr = substr_loc(str, holder);			// "ptr" is pushed farther down the string
		if (!ptr)					// If substring instance not found	
			break;
		ptr = holdptr + abs(ptr - holder->array) + str->len; 		// Move pointer passed the substring found.
		free_bytes(&holder);			// Free unecessary heap memory to prevent mem. leak
		++i;    				// Each substring instance is counted
	}
	return i;
}

u8* delsubstr(Bytes* origin, u8* f, u8* b)	// Deletes string between 'f' and 'b' pointers (string must be dynamicly allocated with NULL) (PTRS alread validated by "rmsubstr")
{
	goodptr(origin, "NULLPTR ORIGIN GIVEN TO DELSUBSTR", NOFUNC_RETURN);
	if (origin->len == abs(f - b))	// Check if will become empty string, then zero out everything.
	{ 
		FREE(&(origin->array)); 
		origin->array = NULLPTR; 
		origin->len = 0; 
		return NULLPTR;
	}
	register u32 frontpiece = abs(f - origin->array);
	register i32 backpiece = origin->len - abs(b - origin->array);	// Example: Take out "str" from "butterstrfly" ---> Front piece = "butter" | Backpiece = "fly"
	u8* newarray = MALLOC(frontpiece + backpiece + 1);		// Make space
	nbytesto(newarray, origin->array, frontpiece);			// Copy up to front of substring to be deleted
	nbytesto(newarray + frontpiece, b, backpiece);			// Start after end of substring and continue copying
	newarray[frontpiece + backpiece] = 0;				// Nul
	FREE(&(origin->array));						// Get rid of old array
	origin->array = newarray;
	origin->len = frontpiece + backpiece;
	return origin->array;						// Return u8* pointer to array
}

Bytes* rmsubstr(Bytes* str, Bytes* origin)	// Returns pointer to Bytes object without an instance of the specified substring
{
	u8* holder = substr_loc(str, origin);	// Find string
	if (holder)
		delsubstr(origin, holder, holder + str->len);	// Delete
	return origin;
}

u8* rmsubstr_loc(Bytes* str, Bytes* origin)	// Returns pointer to the location of where the string was removed 
{
	u8* holder = substr_loc(str, origin);
	if (holder)
	{
		delsubstr(origin, holder, holder + str->len);	// Delete
		return origin->array;
	}
	else
		return NULLPTR;
}

u32 rmsubstr_all(Bytes* str, Bytes* origin)	// Removes all substrings from byte object and returns number of substrings removed
{
	u8* holder;
	register i32 i = 0;
	do
	{
		holder = rmsubstr_loc(str, origin);	// Delete until none left
		++i;					// Count removal
	} while (holder);
	return --i;
}

void scanreplace(Bytes* bytes, u8 bad, u8 good)
{
	register u64 i;
	register u64 len = bytes->len;
	for(i = 0; i < len; ++i)
		if(*(bytes->array+i) == bad)
			(*(bytes->array+i)) = good;
}

Bytes* concatbytes(Bytes* front, Bytes* back, u8 between, u8 freeold) // Attach 2 strings together, place a "between" character in the middle, choose whether to discard old strings
{
	register u64 flen = 0;
	if (!back) 						// Return if no piece exists to concatenate
		return NULLPTR;	
	if (front)
		flen = front->len;				// For efficient mem. accesses
	u64 space = flen + back->len + (between != 0); 		// +1 if "between" is set to a character
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

Bytes* appendstr(Bytes* bstr, u8* str, u64 len)
{
	if (!bstr)	// If no 'bstr' just make it from scratch
		return dynamic_bytes(str, len);
	bstr->array = REALLOC(bstr->array, bstr->len + len + 1);	// Make more space
	nbytesto(bstr->array + bstr->len, str, len);			// Append string
	bstr->len += len;						// Update length
	*(bstr->array + bstr->len) = 0;					// Nul-terminate
	return bstr;
}

u8* copystr(Bytes* str)		// Returns copy of a Bytes class byte array
{
	goodptr(str, "NULLPTR STR GIVEN TO COPYSTR", NOFUNC_RETURN);
	u8* newarray = MALLOC(str->len + 1);
	newarray = nbytesto(newarray, str->array, str->len + 1);
	*(newarray + str->len) = 0;
	return newarray;
}

Bytes* appendctostr(Bytes* str, u8 c)		// Returns Bytes* pointer to array that was just modified
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

Bytes* prependctostr(u8 c, Bytes* str)  // Returns Bytes* pointer to string that was just modified
{
	if (!str)
	{
		Bytes* holder = dynamic_bytes(NULLPTR, 1);
		*(holder->array) = c;
		return holder;
	}
	str->array = REALLOC(str->array, str->len + 2);      // one for extra char and one for nul
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

Bytes* chop(Bytes* str, u8* ptr)	// Remove contents at and after ptr (MUST USE ASSIGNMENT IN CASE POINTER IS FREED)
{
	if (!ptr || !str)	// If bad pointers
		return str;
	if (ptr == str->array)
	{
		free_bytes(&str);
		return NULLPTR;
	}
	register u64 newlen = abs(ptr - str->array);	// Get new length before moving pointer (REALLOC may more the array pointer in the bytes object)
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
void replacebytes(Bytes* origin, Bytes* bytes, i64 offset, u8 directionfromoffset)	// Starts replacing bytes at specified byte (e.g. forwards  : offset is 2nd byte --> actual offset is +1 from array pointer)
{						//					    					    (e.g. backwards : offset is 45th spot out of 50 --> actual offset is -offset from nul-terminator spot)
	goodptr(origin, "NULLPTR ORIGIN GIVEN TO REPLACEBYTES", NOFUNC_RETURN);	
	if(!goodptr(bytes, "NULLPTR BYTES GIVEN TO REPLACEBYTES", FUNC_RETURN))
		return;
	if (offset > origin->len)
	{
		PRINT("OFFSET LARGER THAN ORIGINAL STRING LENGTH IN REPLACEBYTES");
		return;
	}
	if (abs(((i64)(origin->array + offset) * (directionfromoffset == 1) + (i64)(origin->array + origin->len  - offset) * (!directionfromoffset)) - (i64)origin->array) + bytes->len > origin->len)	// Light switch logic depends on 'directionfromoffset'
	{
		PRINT("REPLACEMENT BYTESTRING LENGTH GOES PAST ORIGIN BOUNDARIES IN REPLACEBYTES");
		return;
	}
	if (directionfromoffset)	// If right
		nbytesto(origin->array + offset, bytes->array, bytes->len);
	else				// If left
		nbytesto(origin->array + origin->len - offset, bytes->array, bytes->len);
}

Bytes* splitbytes(Bytes* origin, u8* divideptr)	// Split bytes into 2 objects (Front portion is assigned to origin, back portion is returned as a 'Bytes' pointer)
{
	goodptr(origin, "NULLPTR ORIGIN GIVEN TO SPLITBYTES", NOFUNC_RETURN);		    // Check original pointer
	if (!goodptr(divideptr, "NULLPTR SPLIT POSITION GIVEN TO SPLITBYTES", FUNC_RETURN)) // Check position pointer
		return NULLPTR;		
	register u64 ptr_offset_fromfront = abs(divideptr - origin->array);	    // Get offset from start
	register i64 ptr_offset_fromback  = origin->len - ptr_offset_fromfront;     // Get offset from end
	if (ptr_offset_fromfront > origin->len || divideptr < origin->array)	    // Check that 'ptr' is within byte string boundaries
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
Bytes* insertbytes(Bytes** newbytes, Bytes** origin, u8* divideptr, i64 (*sectionremover)(u8*, i64), u8 freeold)
{
	register i64 numtoremove = 0;
	goodptr(origin, "NULLPTR ORIGIN ADDRESS GIVEN TO INSERTBYTES", NOFUNC_RETURN); 	   // Check 'origin' pointer address
	goodptr(*origin, "NULLPTR ORIGIN GIVEN TO INSERTBYTES", NOFUNC_RETURN);		   // Check 'origin' pointer address
	goodptr(newbytes, "NULLPTR NEWBYTES ADDRESS GIVEN TO INSERTBYTES", NOFUNC_RETURN); // Check 'newbytes' pointer address
	goodptr(*newbytes, "NULLPTR NEWBYTES GIVEN TO INSERTBYTES", NOFUNC_RETURN);	   // Check 'newbytes' pointer
	if (!goodptr(divideptr, "NULLPTR SPLIT POSITION GIVEN TO SPLIT", FUNC_RETURN))	   // Check position pointer
		return NULLPTR;
	register u64 ptr_offset_fromfront = abs(divideptr - (*origin)->array);	   // Get offset from start
	register i64 ptr_offset_fromback  = (*origin)->len - ptr_offset_fromfront;  // Get offset from end
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
Bytes* getword(u32 n, Bytes* str, u8 justpointer)	// Gets nth word in string
{
	register u32 w = 0; 	// Holds number of words already scanned in string
	register u64 i = 0;	// Holds string index
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

// ************************************************ ENCRYPTION ************************************************ // 

Bytes* encrypt7(Bytes* str)
{
	return str;
}

Bytes* decrypt7(Bytes* str)
{
	return str;
}

#endif
