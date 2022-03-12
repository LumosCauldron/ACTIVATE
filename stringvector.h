#ifndef STRINGVECTOR_H
#define STRINGVECTOR_H

#define PREVDIRECTION 1	// For 'foreach_vect'
#define NXTDIRECTION  0

#define VECTGRAB       1000
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

Svect* vectgrab(Svect* ptr)	// Grabs (VECTGRAB * sizeof(Bytes*)) bytes and returns an initialized pointer, updates head, vptr, end, and allocated each call
{
	if (!ptr)
	{
		ptr            = MALLOC(sizeof(Svect));
		ptr->head      = CALLOC(sizeof(Bytes*) * VECTGRAB);
		ptr->vptr      = ptr->head;
		ptr->end       = ptr->head;
		ptr->numitems  = 0;
		ptr->allocated = sizeof(Bytes*) * VECTGRAB;
	}
	else
	{
		register int vptr_dist = abs(ptr->vptr - ptr->head);
		register int end_dist  = abs(ptr->end - ptr->head);
		ptr->head      = REALLOC(ptr->head, (ptr->allocated += (VECTGRAB * sizeof(Bytes*))));
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
		vectgrab(ptr);
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

void vectrelease(Svect** ptr)	// Destroys a given vector
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

void vectdestruct(Svect** vector)
{
	foreach_vect(*vector, (*vector)->head, free_bytes, NXTDIRECTION);
	vectrelease(vector);
}

// PREVDIRECTION 1
// NXTDIRECTION  0
Bytes* vecttostr(Svect** vect, Bytes** vectptr, char midchar, char dir)	// Used to check/modify through a given vector
{
	goodptr(vect, "SVECT NULLPTR ADDRESS GIVEN TO FOREACH_VECT", NOFUNC_RETURN);
	goodptr(*vect, "SVECT NULLPTR GIVEN TO FOREACH_VECT", NOFUNC_RETURN);
	goodptr(vectptr, "BYTES NULLPTR GIVEN TO FOREACH_VECT", NOFUNC_RETURN);
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

