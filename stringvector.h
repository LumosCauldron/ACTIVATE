#ifndef STRINGVECTOR_H
#define STRINGVECTOR_H

#include "bytes.h"

#define PREVDIRECTION 	1	// For 'foreach_vectelem'
#define NXTDIRECTION  	0

#define MAKENEW	      	1	// For 'strtovect'
#define MAKEFROM      	0

#define SKIPFIRST    	1 	// For 'strtovect'
#define NOSKIPFIRST   	0

#define VECTGRAB       	1000	// For 'vectgrab'
#define NO_OPTAMT      	0

#define F_STR_B		3	// For 'vecttostr'
#define F_STR_		2
#define _STR_B		1
#define _STR_		0
#define NOMIDCHAR	0

#define VECTITEMS(x)   		((x)->numitems)
#define VECTBYTES(x)   		((x)->numitems * sizeof(Bytes*))
#define VECTALLOC(x)   		((x)->allocated)
#define VECTCURRENT(x) 		((x)->allocated)
#define VECTFULL(x)    		(((x)->numitems * sizeof(Bytes*)) == (x)->allocated)
#define VECTTOP(x)  		((x)->head)
#define VECTBOTTOM(x)     	((x)->end)
#define VECTTOPELEM(x)     	(*((x)->head))
#define VECTBOTTOMELEM(x)  	(*((x)->end))
#define VECTNEXT(x)    		((x) + 1)
#define VECTPREV(x)    		((x) - 1)
#define VECTSLOTS(x)   		(abs((x)->end - (x)->head) + (1 * ((x)->numitems != 0)))
#define VECTELEM(x)		(*(x))

struct svect
{
	Bytes** vptr;
	Bytes** head;
	Bytes** end;
	u64 allocated;
	u32 numitems;
	u8  memlock;	// Stops vectrelease from freeing 'Bytes' objects
};

typedef struct svect Svect;

// NO_OPTAMT 0
Svect* vectgrab(Svect* ptr, u32 optamt)	// Grabs (VECTGRAB * sizeof(Bytes*)) bytes and returns an initialized pointer, updates head, vptr, end, and allocated each call
{
	register u32 allocsz = VECTGRAB;
	if (optamt)
		allocsz = optamt;
	if (!ptr)
	{
		ptr            = MALLOC(sizeof(Svect));
		ptr->head      = CALLOC(sizeof(Bytes*) * allocsz);	// CALLOC IS IMPORTANT HERE
		ptr->vptr      = ptr->head;
		ptr->end       = ptr->head;
		ptr->numitems  = 0;
		ptr->allocated = sizeof(Bytes*) * allocsz;
		ptr->memlock   = 0;
	}
	else
	{
		register u32 vptr_dist = abs(ptr->vptr - ptr->head);
		register u32 end_dist  = abs(ptr->end - ptr->head);
		ptr->head = REALLOC(ptr->head, (ptr->allocated += (allocsz * sizeof(Bytes*))));
		ptr->vptr = ptr->head + vptr_dist;
		ptr->end  = ptr->head + end_dist;
	}
	
	return ptr;
}

void vectmemlock(Svect* vect)		// Set lock on 'Bytes' elements in vector so that they are not freed
{
	vect->memlock = 1;
}

void vectconform(Svect* ptr)	// Saves memory by deallocating the space that the vector is not using
{
	goodptr(ptr, "SVECT NULLPTR GIVEN TO VECTCONFORM", NOFUNC_RETURN);
	if (VECTFULL(ptr))
		return;
	ptr->head = REALLOC(ptr, ptr->allocated = VECTBYTES(ptr));
}

void vectpush(Svect* ptr, Bytes* newstr)	// Connects string to stack of strings
{
	goodptr(ptr, "SVECT NULLPTR GIVEN TO VECTPUSH", NOFUNC_RETURN);
	if (!newstr)
		return;
	if (VECTBYTES(ptr) == ptr->allocated)
		vectgrab(ptr, NO_OPTAMT);
	if (VECTITEMS(ptr))
		++ptr->end;
	(*(ptr->end)) = newstr;
	++VECTITEMS(ptr);
}

void vectpop(Svect* ptr)	// Pops/Frees a vector Bytes element from the end and updates everything
{
	goodptr(ptr, "SVECT NULLPTR GIVEN TO VECTPOP", NOFUNC_RETURN);
	if (!ptr->head)
		return;
	if (ptr->head != ptr->end)
	{
		if (!ptr->memlock)
			FREE(ptr->end--);	// Frees, clears element, and decrements vector end pointer
		else
		{
			*(ptr->end) = NULLPTR;	// Clears element and decrements vector end pointer
			--ptr->end;
		}
	}
	do
	{
		--VECTITEMS(ptr);
	} while (!(*ptr->end));		// While NULLPTR found, track down farthest object from head
}

void vectrelease(Svect** ptr)	// Releases a given vector WITHOUT freeing all its string elements (Make certain that all dynamic Bytes* pointers are freed as well (manually))
{
	goodptr(ptr, "SVECT ADDRESS NULLPTR GIVEN TO VECTRELEASE", NOFUNC_RETURN);
	goodptr(*ptr, "SVECT NULLPTR GIVEN TO VECTRELEASE", NOFUNC_RETURN);
	FREE(&((*ptr)->head));		// Frees pointer to array of 'Bytes*', a.k.a. 'FREE()' frees a vector pointer passed in by reference, hence the reason for a confusing expression
	(*ptr)->head         = NULLPTR;
	(*ptr)->vptr         = NULLPTR;
	(*ptr)->end          = NULLPTR;
	(*ptr)->numitems     = 0;
	(*ptr)->allocated    = 0;
	FREE(ptr);
}

char vectcontains(Svect* vect, Bytes* object)
{
	if (!vect || !object)
		return 0;
	register u32 len = vect->numitems;
	while (--len >= 0)
		if (eqbytes(object, *(vect->end - len)))
			return 1;
	return 0;
}

static inline u64 vectobjlen(Bytes* obj)
{
	if (obj)
		return obj->len;
	return 0;
}

u64 vecttotalbytes(Svect* vect)		// Returns total array length of all 'Bytes' objects stored within the vector
{
	goodptr(vect, "SVECT NULLPTR GIVEN TO FOREACH_VECTELEM", NOFUNC_RETURN);
	if (!VECTITEMS(vect))
		return 0;
	register u64 totalbytes = 0;
	register u32 slots = VECTSLOTS(vect);		// Get number of slots to add up (NULLPTR elements add 0 to 'totalbytes'))
	register u32 i;
	for (i = 0; i < slots; ++i)				// Add up length of all arrays held in vector
		totalbytes += vectobjlen(*(vect->head + i));
	return totalbytes;					// Return  final length
}

// PREVDIRECTION 1
// NXTDIRECTION  0
Bytes** foreach_vectelem(Svect* vect, Bytes** vectptr, u64 (*ptr)(Bytes**), char dir)	// Used to check/modify through a given vector
{
	goodptr(vect, "SVECT NULLPTR GIVEN TO FOREACH_VECTELEM", NOFUNC_RETURN);
	goodptr(vectptr, "BYTES NULLPTR GIVEN TO FOREACH_VECTELEM", NOFUNC_RETURN);
	goodptr(ptr, "FUNCTION NULLPTR GIVEN TO FOREACH_VECTELEM", NOFUNC_RETURN);
	if (!vect->numitems)
		return NULLPTR;
	if (abs(vectptr - vect->head) + abs(vect->end - vectptr) != abs(vect->end - vect->head))
		THROW("BYTES POINTER 'vectptr' NOT IN GIVEN SVECT VECTOR");
	register i32 direction;
	register u32 itemstildone;
	if (dir == PREVDIRECTION)
	{
		itemstildone = (abs(vectptr - vect->head)) + 1;	// Bytes until head
		direction = -1;
	}
	else
	{
		itemstildone = (abs(vectptr - vect->end)) + 1;	// Bytes until end
		direction = 1;
	}
	do
	{
		if (!vectptr)			// Skips holes/gaps of dynamically freed pointers with no strings
			goto gotonext;

		if (ptr(vectptr) == FUNC_RETURN)
			return vectptr;		// Return if signaled by last call to function

		gotonext:	
			vectptr += direction;
	} while (--itemstildone);
	return NULLPTR;
}

void vectdestruct(Svect** vect) // FREES ALL ELEMENTS THEN DESTROYS STRUCTURE (CALL 'VECTRELEASE()' IF ELEMENTS ARE STILL NEEDED BY OTHER PARTS OF PROGRAM OR STRUCTURES)
{
	goodptr(vect, "SVECT NULLPTR ADDRESS GIVEN TO VECTDESTRUCT", NOFUNC_RETURN);
	goodptr(*vect, "SVECT NULLPTR GIVEN TO VECTDESTRUCT", NOFUNC_RETURN);
	if (!(*vect)->memlock)
		foreach_vectelem(*vect, (*vect)->head, (u64 (*)(Bytes**))(free_bytes), NXTDIRECTION);	// *Note: 'free_bytes()' returns an INT type instead of defined "u64" type (we don't care)
	vectrelease(vect);
}

// ********************** EXTENDED FUNCTIONALITY ********************** //

// PREVDIRECTION 1
// NXTDIRECTION  0
// NOMIDCHAR	 0
// fbmidchar  	 3 --> add to boths sides of string
// fbmidchar  	 2 --> add to front side of string
// fbmidchar  	 1 --> add to back  side of string
// fbmidchar  	 0 --> don't add to boundaries of string

Bytes* vecttostr(Svect** vect, Bytes** vectptr, char midchar, u8 dir, u8 fbmidchar)	// Used to check/modify through a given vector
{
	goodptr(vect, "SVECT NULLPTR ADDRESS GIVEN TO VECTTOSTR", NOFUNC_RETURN);
	goodptr(*vect, "SVECT NULLPTR GIVEN TO VECTTOSTR", NOFUNC_RETURN);
	goodptr(vectptr, "VECTPTR ADDRESS NULLPTR GIVEN TO VECTTOSTR", NOFUNC_RETURN);
	if (!(*vect)->numitems)
		return NULLPTR;
	if (abs(vectptr - (*vect)->head) + abs((*vect)->end - vectptr) != abs((*vect)->end - (*vect)->head))
		THROW("BYTES POINTER 'vectptr' NOT IN GIVEN SVECT VECTOR");
	register u32 itemstildone;
	register i32 direction;
	register  u8 extraspace = 0;
	if (midchar)
	{	
		switch(fbmidchar)
		{
			case F_STR_B : ++extraspace;	  // Falls into 'case : F_STR_'
			case F_STR_  : ++extraspace;	  // Extraspace accounts for 2 or 1 extra mid-characters
				       break;
			case _STR_B  : ++extraspace;
		}
		extraspace  += (VECTITEMS(*vect) - 1);
	}
	Bytes* str   = dynamic_bytes(NULLPTR, (vecttotalbytes(*vect) + extraspace) * sizeof(char));	// Get total space needed for final string and add space for all in between middle characters
	char* writer = (char*)(str->array);
	if (midchar)
		if (fbmidchar == F_STR_B || fbmidchar == F_STR_)
		{
			*writer = midchar; // Writes in first mid-character to beginning of string
			++writer; 	   // Increment writer
		}
	if (dir)	// If PREVDIRECTION
	{
		itemstildone = (abs(vectptr - (*vect)->head)) + 1;	// Bytes until head
		direction = -1;
	}
	else
	{
		itemstildone = (abs(vectptr - (*vect)->end)) + 1;	// Bytes until end
		direction = 1;
	}
	do
	{
		if (!vectptr)			// Skips holes/gaps of dynamically freed pointers with no strings
			goto gotonext;
	
		nbytesto((char*)(writer), (*vectptr)->array, (*vectptr)->len);	// Write array to string and move 'writer' forward in accordance with the number of bytes written 
		writer += (((*vectptr)->len) / sizeof(char));
		if (itemstildone > 1 && midchar)			// Insert middle character if specified
		{
			*writer = (midchar * (midchar != NULTERMINATOR));
			++writer;
		}
		
		gotonext:	
			vectptr += direction;				// Go to next vector object
	} while (--itemstildone);
	
	if (midchar)
		if (fbmidchar == F_STR_B || fbmidchar == _STR_B)
			*writer = midchar;
			
	vectdestruct(vect);
	return str;
}

// MAKENEW     1
// MAKEFROM    0
// SKIPFIRST   1
// NOSKIPFIRST 0
Svect* strtovect(Bytes* str, char dlim, u8 skipfirst, u8 opt)	// Creates a vector of strings split by delimiter characters found in original string (skipfirst used to determine if first occurence should be ignored)
{									// ('opt' determines whether the vector should hold pointers to parts of 'str' [MAKEFROM]  OR  newly allocated, in-the-same-order, fragments of 'str'
	if (!goodptr(str, "NULLPTR STR GIVEN TO STRTOVECT", FUNC_RETURN))
		return NULLPTR;
	char* ptr = findchar(dlim, str->array, str->len);		// Should find the first delimiter character in the file path ("register" can be used here as this value is never dereferenced)
	char* lastptrposition = str->array;				// Used for calculating length of fragment 
	Svect* strvect = vectgrab(NULLPTR, 7); 				// SEVEN IS HARDCODED AS AVERAGE EXPECTED AMOUNT OF FRAGMENTS PER RANDOM STRING (vector size starts at 7)
	if (!opt)							// Set memory lock to stop freeing of 'Bytes' elements in 'strvect'
		vectmemlock(strvect);
	if (!ptr || (ptr == (str->array + str->len - 1) && skipfirst))	// Push full string if no delimiters or only delimiter found is the last character of the string
	{
		if (opt)
			vectpush(strvect, dynamic_bytes(str->array, str->len - (ptr != NULLPTR)));	// If 'opt' == MAKENEW (-1 to ommit delimiter if one is found by 'findchar()')
		else
		{
			vectpush(strvect, str);				// Else 'opt' == MAKEFROM
			if (ptr)
				--((VECTBOTTOMELEM(strvect))->len);		// Make sure to ommit delimiter by correcting newly pushed 'Bytes' object.len (if one is found by 'findchar()')
		}
		goto done;
	}
	if (!skipfirst && ptr != lastptrposition)			// If first section before delimiter still important and not the first character of the string
		goto becomedowhileloop;					// Skip first instance of while-loop logic and execute as if code block was configured as a do-while-loop instead of a while-loop
	if (skipfirst)
		lastptrposition = ptr;					// Record last position 'ptr' was at
	while(ptr = findchar(dlim, ptr + 1, abs(str->len - (ptr - str->array)) / sizeof(char))) // While more directory names in filepath (+1 in order to move on from initial finding)
	{
		if (*(ptr - 1) == dlim)		// If delimiter found in the next character (e.g. dlim == '/' in string "file//path"), skip it and update lastpositionptr
		{
			++lastptrposition;
			continue;
		}
		becomedowhileloop: ;
		if (opt)				// move over by 1 to avoid including delimiter character //	// If MAKENEW option, make new fragments of original string and push them to vector
			vectpush(strvect, dynamic_bytes(lastptrposition + ((*lastptrposition == dlim) * sizeof(char)), abs(ptr - lastptrposition) - ((*lastptrposition == dlim) * sizeof(char))));
		else													// Else if MAKEFROM option, push fragments of string to vector
			vectpush(strvect, static_bytes(lastptrposition  + ((*lastptrposition == dlim) * sizeof(char)), abs(ptr - lastptrposition) - ((*lastptrposition == dlim) * sizeof(char))));
		lastptrposition = ptr;											// Record last position 'ptr' was at
	}
	if (*lastptrposition == dlim && lastptrposition == (str->array + str->len - 1))	// If last character is a delimiter character return vector (no need to make last string fragment)
		goto done;
	if (opt)
		vectpush(strvect, dynamic_bytes(lastptrposition + ((*lastptrposition == dlim) * sizeof(char)), str->len - abs(lastptrposition - str->array) - ((*lastptrposition == dlim) * sizeof(char)));
	else
		vectpush(strvect, static_bytes(lastptrposition  + ((*lastptrposition == dlim) * sizeof(char)), str->len - abs(lastptrposition - str->array) - ((*lastptrposition == dlim) * sizeof(char)));
	done:
	return strvect;
}

u64 printvectelem(Bytes** bytes)
{
	goodptr(bytes, "NULLPTR BYTES ADDRESS GIVEN TO PRINTVECT", NOFUNC_RETURN);
	if (!(*bytes))
		PRINT("NULLPTR");
	else
		PRINTBYTES(*bytes);
	return 1;
}

void printvect(Svect* vect)
{
	goodptr(vect, "NULLPTR VECT GIVEN TO PRINTVECTOR", NOFUNC_RETURN);
	foreach_vectelem(vect, vect->head, printvectelem, NXTDIRECTION);
}

void printvectormeta(Svect* vect)
{
	goodptr(vect, "NULLPTR VECT GIVEN TO PRINTVECTORMETA", NOFUNC_RETURN);
	printf("Distance between head and vptr: %ld slots\n", (u64)(abs(vect->vptr - vect->head)));
	printf("Distance between head and end: %ld slots\n" , (u64)(abs(vect->end  - vect->head)));
	printf("Distance between vptr and end: %ld\n slots" , (u64)(abs(vect->end  - vect->vptr)));
	printf("Numitems: %d\n" , vect->numitems);
	printf("Allocated: %ld\n", vect->allocated);
	//printf("VPTR holds --> ");
	//printvectelem(vect->vptr);
}

#endif

