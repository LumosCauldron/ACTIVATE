#ifndef BASIC_H
#define BASIC_H

// _____ DETECT PLATFORM _____
#ifdef __unix__         
	#define UNIXCODE
#elif defined(_WIN32) || defined(WIN32) 
	#define WINCODE
#else
	#error WHAT_ARE_YOU_DOING
#endif
// _____ DETECT PLATFORM ______________________________

#define ERRORCHECKING

#include <stdint.h>

#ifndef _TYPE_H_
#define _TYPE_H_
typedef uint8_t   u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t    i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;

typedef char normchar; //enemychar
#endif

u8 bssstart;		// Keep this, this gets put in the first portion of the BSS section as uninitialized data

// _____ WIN32 AND UNIX DIFFERENCES _____ 

#ifdef WINCODE
	#include <windows.h>	// For 'Sleep()'
	#include <sysinfoapi.h>
	
	#define SLASH '\\'	// For tacking on file names to file paths and concatenating paths
	char* DRIVELABEL;
#endif

#ifdef UNIXCODE
	#include <unistd.h>	// For 'sleep()'
	#include <sys/sysinfo.h>
	
	#define SLASH '/'	// For tacking on file names to file paths and concatenating paths
	
#endif

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

// _____ WIN32 AND UNIX DIFFERENCES ______________________________


// _____ ERROR CHECKING _____ 
#ifdef ERRORCHECKING
	#include <errno.h>
	#define PRINTERRORS	 1
	#define NOMSG	  	 (char*)(0)
#endif
// _____ ERROR CHECKING ______________________________

#define NULLPTR 	 (void*)(0)
#define at(x) 		 (&x)
#define EMPTY 		 -1

#define FUNC_RETURN    	 101
#define NOFUNC_RETURN 	 0

#define STEALTH	         0
#define SCRUB		 1	// FORENSIC RESISTANCE 
#define NOSCRUB		 0

#define STACK_ABOVE_HEAP 1	// Meaning ESP subtracts to make space 
#define HEAP_ABOVE_STACK 2	// Meaning ESP adds to make space

u8 orientation  = 0;
u8 architecture = 0;
u8 cores = 0;

int MOD(u64 x, u64 y) 
{ 
	return x % y;
}

void THROW(char* str); /* PROTO */
void PRINT(char* str)                     { if (!str) THROW("NULLPTR GIVEN TO PRINT"); printf("%s\n", str); }

void EXIT(u8 stop)  { if (stop) exit(0); }

void THROW(char* str) { PRINT(str); exit(9); }

void* MALLOC(u64 space)
{
	//PRINT("MALLOCED SPACE");
	void* ptr = NULLPTR; ptr = malloc(space);
	if (!ptr) { perror("MALLOC ERROR"); EXIT(1); }
	return ptr;
}

void* REALLOC(void* ptr, u64 space)
{
	//PRINT("REALLOCED SPACE");
	ptr = realloc(ptr, space);
	if (!ptr) { perror("REALLOC ERROR"); EXIT(1); }
	return ptr;
}

void* CALLOC(u64 space)
{
	//PRINT("CALLOCED SPACE");
	void* ptr = NULLPTR; ptr = calloc(1, space);
	if (!ptr) { perror("CALLOC ERROR"); EXIT(1); }
	return ptr;
}


// ** ENVIRONMENT DETECTING ** //
void setarch()
{
	switch(sizeof(void*))
	{
		case   8 : architecture =  64; break;
		case   4 : architecture =  32; break;
		case   2 : architecture =  16; break;
		case   1 : architecture =   8; break;
		case  16 : architecture = 128; break;
	}
}

void stackorient()
{
	volatile u8 stackptr;
	u8* heapptr = MALLOC(1);
	if ((void*)heapptr < (void*)&stackptr)
		orientation = STACK_ABOVE_HEAP;	// 'ABOVE' MEANING IN DIAGRAM (LOOK UP COMMON STACK/HEAP DIAGRAM) <-- most common architecture
	else		
		orientation = HEAP_ABOVE_STACK; // 'ABOVE' MEANING IN DIAGRAM (LOOK UP COMMON STACK/HEAP DIAGRAM) <-- rare
}

void setcores()
{
	#ifdef WINCODE
		SYSTEM_INFO sysinfo;
		GetSystemInfo(&sysinfo);
		cores = (u8)(sysinfo.dwNumberOfProcessors);
	#endif // _______________________________________________________________________
	#ifdef UNIXCODE
		cores = (u8)get_nprocs();
	#endif // _______________________________________________________________________

	if (!cores)
		cores = 1;
}

void setfilesysenv()
{
	#ifdef WINCODE
		DRIVELABEL    = MALLOC(4);
		DRIVELABEL[0] = 'C';
		DRIVELABEL[1] = ':';
		DRIVELABEL[2] = SLASH;
		DRIVELABEL[3] = 0;
	#endif // _______________________________________________________________________
}

void CALIBRATE()
{
	setarch();
	setcores();
	setfilesysenv();
}

void DECALIBRATE()
{
	#ifdef WINCODE
		FREE(&DRIVELABEL);
	#endif // _______________________________________________________________________
}

// *************************** //


			// Parameters are actually void** pointers
void FREE(void* ptr)	// Can cast to any pointer type because we are just freeing a pointer
{
	if (!orientation)	// If not initialized initialize
		stackorient();
	if (*((u8**)(ptr))) 
	{
		volatile u8 stackptr;	
		if (orientation == STACK_ABOVE_HEAP && *((u8**)(ptr)) < (u8*)(&stackptr) && *((u8**)(ptr)) > (u8*)(&bssstart))
			goto freepointer;
		else if (orientation == HEAP_ABOVE_STACK && *((u8**)(ptr)) < (u8*)(&stackptr) && *((u8**)(ptr)) < (u8*)(&bssstart))
			goto freepointer;
		else if (!orientation)
			goto freepointer;
		else
			return;
		freepointer:
			free(*((u8**)(ptr)));
			*((u8**)(ptr)) = NULLPTR;	// For safety and reuse of the pointer passed in by reference
			//PRINT("FREED SPACE");
	}
}

void PLN(u8 num)          	  
{ 
	for (num; num > 0; --num) 
		putchar('\n');  
}       	   // NEW LINES

// Error checking
static inline u8 goodptr(void* ptr, char* errormsg, u8 ret) // Checks given pointer, if error message != NOMSG 'errormsg' will be printed, 
{						 	 // 'ret' determines whether or not to print and exit, or return a notifying value to its caller
	if (!ptr)
	{
		if (ret == FUNC_RETURN)
		{
			if (errormsg && PRINTERRORS)
				PRINT(errormsg); 
			return 0;
		}
		else
			THROW(errormsg);
	}
	return 1;
}

#endif
