#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "tools.h"

typedef void (*MISSION0)(void);
typedef void (*MISSION1)(void*);
typedef void (*MISSION2)(void*, void*);
typedef void (*MISSION3)(void*, void*, void*);
typedef void (*MISSION4)(void*, void*, void*, void*);
typedef void (*MISSION5)(void*, void*, void*, void*, void*);
typedef void (*MISSION6)(void*, void*, void*, void*, void*, void*);
typedef void (*MISSION7)(void*, void*, void*, void*, void*, void*, void*);

struct mission
{
	void* objective;			// Holds function to call
	u64* equipment;				// Holds parameters as 8 byte integers OR sizeof(u64) byte integers
	u8 numtools;				// Indicates number of parameters in 'equipment' array (up to 7 parameters allowed)
	u8 cleanaction;				// Indicates what structures to free after finishing execution
};

typedef struct mission Mission;
typedef u64 MISSIONTOOL;

#define TOOL1 (*((*order)->equipment))	// Used for fast indexing of parameters given to function
#define TOOL2 (*((*order)->equipment + 1))
#define TOOL3 (*((*order)->equipment + 2))
#define TOOL4 (*((*order)->equipment + 3))
#define TOOL5 (*((*order)->equipment + 4))
#define TOOL6 (*((*order)->equipment + 5))
#define TOOL7 (*((*order)->equipment + 6))

#define NOFREEMISSION  0		// For 'missionstart' and 'missionclean'
#define FREEEQUIP      1
#define FREEMISSION    2

#define EMPTYTOOLSET   NULLPTR
#define ZEROTOOLS      0

MISSIONTOOL* assign1tool(u64 item1)
{
	u64* ptr = MALLOC(sizeof(u64));
	*ptr = item1;
	return ptr;
}
// ** 2 ** //
MISSIONTOOL* assign2tools(u64 item1,
			  u64 item2)
{
	u64* ptr = MALLOC(sizeof(u64) * 2);
	*ptr       = item1;
	*(ptr + 1) = item2;
	return ptr;
}
// ** 3 ** //
MISSIONTOOL* assign3tools(u64 item1,
			  u64 item2,
			  u64 item3)
{
	u64* ptr = MALLOC(sizeof(u64) * 3);
	*ptr       = item1;
	*(ptr + 1) = item2;
	*(ptr + 2) = item3;
	return ptr;
}
// ** 4 ** //
MISSIONTOOL* assign4tools(u64 item1,
			  u64 item2,
			  u64 item3,
			  u64 item4)
{
	u64* ptr = MALLOC(sizeof(u64) * 4);
	*ptr       = item1;
	*(ptr + 1) = item2;
	*(ptr + 2) = item3;
	*(ptr + 3) = item4;
	return ptr;
}
// ** 5 ** //
MISSIONTOOL* assign5tools(u64 item1,
			  u64 item2,
			  u64 item3,
			  u64 item4,
			  u64 item5)
{
	u64* ptr = MALLOC(sizeof(u64) * 5);
	*ptr       = item1;
	*(ptr + 1) = item2;
	*(ptr + 2) = item3;
	*(ptr + 3) = item4;
	*(ptr + 4) = item5;
	return ptr;
}
// ** 6 ** //
MISSIONTOOL* assign6tools(u64 item1,
			  u64 item2,
			  u64 item3,
			  u64 item4,
			  u64 item5,
			  u64 item6)
{
	u64* ptr = MALLOC(sizeof(u64) * 6);
	*ptr       = item1;
	*(ptr + 1) = item2;
	*(ptr + 2) = item3;
	*(ptr + 3) = item4;
	*(ptr + 4) = item5;
	*(ptr + 5) = item6;
	return ptr;
}
// ** 7 ** //
MISSIONTOOL* assign7tools(u64 item1,
			  u64 item2,
			  u64 item3,
			  u64 item4,
			  u64 item5,
			  u64 item6,
			  u64 item7)
{
	u64* ptr = MALLOC(sizeof(u64) * 7);
	*ptr       = item1;
	*(ptr + 1) = item2;
	*(ptr + 2) = item3;
	*(ptr + 3) = item4;
	*(ptr + 4) = item5;
	*(ptr + 5) = item6;
	*(ptr + 6) = item7;
	return ptr;
}

Mission* missionplan(void* function, u64* equipment, u8 numtools, u8 cleanaction) // Create a mission package 
{													 // Ensure numtools == number of equipment elements
	Mission* ptr     = MALLOC(sizeof(Mission));
	ptr->objective   = function;	// Holds address of function
	ptr->equipment   = equipment;	// Holds pointer to array of u64 integers
	ptr->numtools    = numtools;	// Records number of elements in large integer array
	ptr->cleanaction = cleanaction;	// What actions to take to free memory when done
	return ptr;
}

static inline void missionscrubequip(Mission** ptr)	// Force frees a mission object (SAME AS 'missionclean()' WHEN FREEMISSION FLAG IS SET)
{
	if (!goodptr(ptr, "NULLPTR PTR ADDRESS GIVEN TO MISSIONSCRUB", FUNC_RETURN))
		return;
	if (!goodptr(*ptr, "NULLPTR PTR GIVEN TO MISSIONSCRUB", FUNC_RETURN))
		return;
	if ((*ptr)->equipment)
		FREE(&((*ptr)->equipment));	// Frees 'mission_object.equipment' by address of pointer to mission object (in short, frees equipment array and zeros out the pointer)
}

static inline void missionscruball(Mission** ptr)	// Force frees a mission object (SAME AS 'missionclean()' WHEN FREEMISSION FLAG IS SET)
{
	if (!goodptr(ptr, "NULLPTR PTR ADDRESS GIVEN TO MISSIONSCRUB", FUNC_RETURN))
		return;
	if (!goodptr(*ptr, "NULLPTR PTR GIVEN TO MISSIONSCRUB", FUNC_RETURN))
		return;
	if ((*ptr)->equipment)
		FREE(&((*ptr)->equipment));	// Frees 'mission_object.equipment' by address of pointer to mission object (in short, frees equipment array and zeros out the pointer)
	FREE(ptr);
}

void missionclean(Mission** ptr)	// Frees mission object based off set parameters from within
{
	switch((*ptr)->cleanaction)
	{
		case FREEEQUIP     : missionscrubequip(ptr);	// Frees 'mission_object.equipment' by address of pointer to mission object 
				     break;			// (in short, frees equipment array and zeros out the pointer)
		case FREEMISSION   : missionscruball(ptr);	// Frees 'mission_object.equipment' by address of pointer to mission object
	}			     				// (in short, frees equipment array and zeros out the pointer)
}

void missionstart(Mission** order)	// Executes whatever function is passed in as a "module" (Usually for executing on elements handled in larger functions that loop through filesystems or arrays)
{					// Equipment array and numtools MUST be consistent (e.g 3 elements in 'equipment' means numtools == 3) !!! IMPERATIVE !!!
	if (!goodptr(order, "NULLPTR ORDER ADDRESS GIVEN TO MISSIONSTART", FUNC_RETURN))
		return;
	if (!goodptr(*order, "NULLPTR ORDER GIVEN TO MISSIONSTART", FUNC_RETURN))
		return;
	if ((*order)->numtools)
		if (!goodptr((*order)->equipment, "NULLPTR ORDER->EQUIPMENT GIVEN TO MISSIONSTART", FUNC_RETURN))
			return;
	switch((*order)->numtools)	// Casts and executes function
	{
		case 0 : ;
			  MISSION0 executor0 = (MISSION0)((*order)->objective);
			(*executor0)();
			  break;
		case 1 : ;
			  MISSION1 executor1 = (MISSION1)((*order)->objective);
			(*executor1)((void*)TOOL1);
			  break;
		case 2 : ;
			  MISSION2 executor2 = (MISSION2)((*order)->objective);
			(*executor2)((void*)TOOL1, (void*)TOOL2);
			  break;
		case 3 : ;
			  MISSION3 executor3 = (MISSION3)((*order)->objective);
			(*executor3)((void*)TOOL1, (void*)TOOL2, (void*)TOOL3);
			  break;
		case 4 : ;
			  MISSION4 executor4 = (MISSION4)((*order)->objective);
			(*executor4)((void*)TOOL1, (void*)TOOL2, (void*)TOOL3, (void*)TOOL4);
			  break;
		case 5 : ;
			  MISSION5 executor5 = (MISSION5)((*order)->objective);
			(*executor5)((void*)TOOL1, (void*)TOOL2, (void*)TOOL3, (void*)TOOL4, (void*)TOOL5);
			  break;
		case 6 : ;
			  MISSION6 executor6 = (MISSION6)((*order)->objective);
			(*executor6)((void*)TOOL1, (void*)TOOL2, (void*)TOOL3, (void*)TOOL4, (void*)TOOL5, (void*)TOOL6);
			  break;
		case 7 : ;
			  MISSION7 executor7 = (MISSION7)((*order)->objective);
			(*executor7)((void*)TOOL1, (void*)TOOL2, (void*)TOOL3, (void*)TOOL4, (void*)TOOL5, (void*)TOOL6, (void*)TOOL7);
	}
	missionclean(order);
}

#endif
