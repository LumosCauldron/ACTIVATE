#ifndef STRINGVECTOR_H
#define STRINGVECTOR_H

#define PREVDIRECTION 1	// For 'foreach_vect'
#define NXTDIRECTION  0

#define MAKENEW	      1 // For 'strtovect'
#define MAKEFROM      0

#define SKIPFIRST     1 // For 'strtovect'
#define NOSKIPFIRST   0

#define VECTGRAB       1000
#define NO_OPTAMT      0
#define VECTITEMS(x)   (x->numitems)
#define VECTBYTES(x)   (x->numitems * sizeof(Bytes*))
#define VECTALLOC(x)   (x->allocated)
#define VECTCURRENT(x) (x->allocated)
#define VECTFULL(x)    ((x->numitems * sizeof(Bytes*)) == x->allocated)
#define VECTTOP(x)     (*(x->end))
#include "bytes.h"

struct svect
{
	Bytes** vptr;
	Bytes** head;
	Bytes** end;
	long long int allocated;
	long long int numitems;
};

typedef struct svect Svect;

// NO_OPTAMT 0
Svect* vectgrab(Svect* ptr, unsigned long long int optamt)	// Grabs (VECTGRAB * sizeof(Bytes*)) bytes and returns an initialized pointer, updates head, vptr, end, and allocated each call
{
	register unsigned long long int allocsz = VECTGRAB;
	if (optamt)
		allocsz = optamt;
	if (!ptr)
	{
		ptr            = MALLOC(sizeof(Svect));
		ptr->head      = CALLOC(sizeof(Bytes*) * allocsz);
		ptr->vptr      = ptr->head;
		ptr->end       = ptr->head;
		ptr->numitems  = 0;
		ptr->allocated = sizeof(Bytes*) * allocsz;
	}
	else
	{
		register int vptr_dist = abs(ptr->vptr - ptr->head);
		register int end_dist  = abs(ptr->end - ptr->head);
		ptr->head      = REALLOC(ptr->head, (ptr->allocated += (allocsz * sizeof(Bytes*))));
		ptr->vptr      = ptr->head + vptr_dist;
		ptr->end       = ptr->head + end_dist;
	}
	return ptr;
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
		FREE(ptr->end--);
	do
	{
		--VECTITEMS(ptr);
	} while (!(*ptr->end));		// While NULLPTR found, track down farthest object from head
}

void vectrelease(Svect** ptr)	// Releases a given vector WITHOUT freeing all its string elements
{
	goodptr(ptr, "SVECT ADDRESS NULLPTR GIVEN TO VECTRELEASE", NOFUNC_RETURN);
	FREE(&((*ptr)->head));		// Frees pointer to array of 'Bytes*' and 'FREE()' frees pointers passed in by reference, hence the reason for a confusing expression
	(*ptr)->head         = NULLPTR;	// Make certain that all dynamic Bytes* pointers are freed as well (manually)
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
	register int len = vect->numitems;
	while (--len >= 0)
		if (eqbytes(object, *(vect->end - len)))
			return 1;
	return 0;
}

// PREVDIRECTION 1
// NXTDIRECTION  0
Bytes** foreach_vect(Svect* vect, Bytes** vectptr, int (*ptr)(Bytes**), char dir)	// Used to check/modify through a given vector
{
	goodptr(vect, "SVECT NULLPTR GIVEN TO FOREACH_VECT", NOFUNC_RETURN);
	goodptr(vectptr, "BYTES NULLPTR GIVEN TO FOREACH_VECT", NOFUNC_RETURN);
	goodptr(ptr, "FUNCTION NULLPTR GIVEN TO FOREACH_VECT", NOFUNC_RETURN);
	if (!vect->numitems)
		return NULLPTR;
	if (abs(vectptr - vect->head) + abs(vect->end - vectptr) != abs(vect->end - vect->head))
		THROW("BYTES POINTER 'vectptr' NOT IN GIVEN SVECT VECTOR");
	register int direction;
	register int itemstildone;
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

void vectdestruct(Svect** vector) // FREES ALL ELEMENTS THEN DESTROYS STRUCTURE (CALL 'VECTRELEASE()' IF ELEMENTS ARE STILL NEEDED BY OTHER PARTS OF PROGRAM OR STRUCTURES)
{
	foreach_vect(*vector, (*vector)->head, free_bytes, NXTDIRECTION);
	vectrelease(vector);
}

// ********************** EXTENDED FUNCTIONALITY ********************** //

// PREVDIRECTION 1
// NXTDIRECTION  0
Bytes* vecttostr(Svect** vect, Bytes** vectptr, char midchar, char dir)	// Used to check/modify through a given vector
{
	goodptr(vect, "SVECT NULLPTR ADDRESS GIVEN TO FOREACH_VECT", NOFUNC_RETURN);
	goodptr(*vect, "SVECT NULLPTR GIVEN TO FOREACH_VECT", NOFUNC_RETURN);
	goodptr(vectptr, "VECTPTR ADDRESS NULLPTR GIVEN TO FOREACH_VECT", NOFUNC_RETURN);
	if (!(*vect)->numitems)
		return NULLPTR;
	if (abs(vectptr - (*vect)->head) + abs((*vect)->end - vectptr) != abs((*vect)->end - (*vect)->head))
		THROW("BYTES POINTER 'vectptr' NOT IN GIVEN SVECT VECTOR");
	register int direction;
	register int itemstildone;
	Bytes* str = NULLPTR;
	if (dir == PREVDIRECTION)
	{
		itemstildone = (abs(vectptr - (*vect)->head)) + 1;	// Bytes until head
		direction = -1;
	}
	else
	{
		itemstildone = (abs(vectptr - (*vect)->end)) + 1;	// Bytes until end
		direction = 1;
	}
	register int numitemstildone = itemstildone;
	do
	{
		if (!vectptr)			// Skips holes/gaps of dynamically freed pointers with no strings
			goto gotonext;

		if (itemstildone == numitemstildone)
			str = copy_bytes(*vectptr);
		else
			str = concatbytes(str, *vectptr, midchar, FREEFRONT);

		gotonext:	
			vectptr += direction;
	} while (--itemstildone);
	vectdestruct(vect);
	return str;
}

// MAKENEW     1
// MAKEFROM    0
// SKIPFIRST   1
// NOSKIPFIRST 0
Svect* strtovect(Bytes* str, char dlim, char skipfirst, char opt)	// Creates a vector of strings split by delimiter characters found in original string (skipfirst used to determine if first occurence should be ignored)
{									// ('opt' determines whether the vector holds pointers to parts of string [MAKEFROM]  OR  newly allocated, in-the-same-order, fragments of the string)
	if (!goodptr(vect, "STR NULLPTR GIVEN TO STRTOVECT", FUNC_RETURN))
		return NULLPTR;
	register char* ptr = findchar(delim, str->array, str->len);	// Should find the first delimiter character in the file path ("register" can be used here as this value is never dereferenced)
	char* lastptrposition = str->array;				// Used for calculating length of fragment 
	Svect* strvect = vectgrab(NULLPTR, 7); 				// SEVEN IS HARDCODED AS AVERAGE EXPECTED AMOUNT OF FRAGMENTS PER RANDOM STRING (vector size starts at 7)
	if (!ptr || (ptr == (str->array + str->len - 1) && skipfirst))
	{
		vectpush(strvect, static_bytes(str->array, str->len));	// Push full string if no delimiters or only delimiter found is the last character of the string when 'skipfirst' option is set
		goto done;
	}
	if (!skipfirst && ptr != lastptrposition)			// If first section before delimiter still important and not the first character of the string
		goto becomedowhileloop;					// Skip first instance of while-loop logic and execute as if code block was configured as a do-while-loop instead of a while-loop
	if (skipfirst)
		lastptrposition = ptr;					// Record last position 'ptr' was at
	while(ptr = findchar(delim, ptr + 1, str->len))			// While more directory names in filepath (+1 in order to move on from initial finding)
	{
		becomedowhileloop: ;
		if (opt)				// move over by 1 to avoid including delimiter character //	// If MAKENEW option, make new fragments of original string and push them to vector
			vectpush(strvect, dynamic_bytes(lastptrposition + (*lastptrposition == dlim), abs(ptr - lastptrposition) - (*lastptrposition == dlim)));
		else													// Else if MAKEFROM option, push fragments of string to vector
			vectpush(strvect, static_bytes(lastptrposition + (*lastptrposition == dlim), abs(ptr - lastptrposition) - (*lastptrposition == dlim)));
		lastptrposition = ptr;											// Record last position 'ptr' was at
	}
	if (*lastptrposition == dlim && lastptrposition == (str->array + str->len - 1))	// If last character is a delimiter character return vector (no need to make last string fragment)
		goto done;
	if (opt)
		vectpush(strvect, dynamic_bytes(lastptrposition + (*lastptrposition == dlim), str->len - abs(lastptrposition - str->array) - (*lastptrposition == dlim)));
	else
		vectpush(strvect, static_bytes(lastptrposition + (*lastptrposition == dlim), str->len - abs(lastptrposition - str->array) - (*lastptrposition == dlim)));
	done:
	return strvect;
}

int printvect(Bytes** bytes)
{
	if (!(*bytes))
		PRINT("NULLPTR");
	else
		PRINT((*bytes)->array);
	PLN(0);	
	return 1;
}

void printvector(Svect* vector)
{
	foreach_vect(vector, vector->head, printvect, NXTDIRECTION);
}

void printvectormeta(Svect* vector)
{
	printf("Distance between head and vptr: %lld\n", (long long int)(vector->vptr - vector->head));
	printf("Distance between head and end: %lld\n" , (long long int)(vector->end - vector->head));
	printf("Distance between vptr and end: %lld\n" , (long long int)(vector->end - vector->vptr));
	printf("Numitems: %lld\n" , vector->numitems);
	printf("Allocated: %lld\n", vector->allocated);
	//printf("VPTR holds --> ");
	//printvect(vector->vptr);
}

#endif

