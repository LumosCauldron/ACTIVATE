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

char bssstart;		// Keep this, this gets put in the first portion of the BSS section as uninitialized data

// _____ C STD LIBRARIES _____ 

#ifdef WINCODE
	#include <windows.h>	// For 'Sleep()'
#endif

#ifdef UNIXCODE
	#include <unistd.h>		// For 'sleep()'
#endif

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#ifdef WINCODE
	#include <sysinfoapi.h>
#endif

#ifdef UNIXCODE
	#include <sys/sysinfo.h>
#endif
// _____ C STD LIBRARIES ______________________________


// _____ ERROR CHECKING _____ 
#ifdef ERRORCHECKING
	#include <errno.h>
	#define PRINTERRORS	 1
	#define NOMSG	  	 (char*)(0)
#endif
// _____ ERROR CHECKING ______________________________

#include "crucialcode/apex.h"

#define NULLPTR 	 (void*)(0)
#define at(x) 		 (&x)
#define EMPTY 		 -1

#define FUNC_RETURN    	 101
#define NOFUNC_RETURN 	 0

#define STEALTH	     0
#define SCRUB		 1	// FORENSIC RESISTANCE 
#define NOSCRUB		 0

#define STACK_ABOVE_HEAP 1	// Meaning ESP subtracts to make space 
#define HEAP_ABOVE_STACK 2	// Meaning ESP adds to make space

char orientation  = 0;
char architecture = 0;
char cores = 0;

int MOD(long long int x, long long int y) { return ((x % y) * (x >= 0)) + ((y - (abs(x) % y)) * (x < 0)); }

void THROW(char* str); /* PROTO */
void PRINT(char* str)                     { if (!str) THROW("NULLPTR GIVEN TO PRINT"); printf("%s\n", str); }

void EXIT(char stop)  { if (stop) exit(0); }

void THROW(char* str) { PRINT(str); exit(9); }

void* MALLOC(long long int space)
{
	void* ptr = NULLPTR; ptr = malloc(space);
	if (!ptr) { perror("MALLOC ERROR"); EXIT(1); }
	return ptr;
}

void* REALLOC(void* ptr, long long int space)
{
	ptr = realloc(ptr, space);
	if (!ptr) { perror("REALLOC ERROR"); EXIT(1); }
	return ptr;
}

void* CALLOC(long long int space)
{
	void* ptr = NULLPTR; ptr = calloc(1, space);
	if (!ptr) { perror("CALLOC ERROR"); EXIT(1); }
	return ptr;
}


// ** ENVIRONMENT DETECTING ** //
char arch()
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
	volatile char unsigned stackptr;
	char* heapptr = MALLOC(1);
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
		cores = (char)(sysinfo.dwNumberOfProcessors);
	#endif // _______________________________________________________________________
	#ifdef UNIXCODE
		cores = (char)get_nprocs();
	#endif // _______________________________________________________________________

	if (!cores)
		cores = 1;
}

// *************************** //


			// Parameters are actually void** pointers
void FREE(void* ptr)	// Can cast to any pointer type because we are just freeing a pointer
{
	if (!orientation)	// If not initialized initialize
		stackorient();
	if (*((char**)(ptr))) 
	{
		volatile unsigned char stackptr;	
		if (orientation == STACK_ABOVE_HEAP && *((char**)(ptr)) < (char*)(&stackptr) && *((char**)(ptr)) > (char*)(&bssstart))
			goto freepointer;
		else if (orientation == HEAP_ABOVE_STACK && *((char**)(ptr)) < (char*)(&stackptr) && *((char**)(ptr)) < (char*)(&bssstart))
			goto freepointer;
		else if (!orientation)
			goto freepointer;
		else
			return;
			
		freepointer:
			free(*((char**)(ptr)));
			*((char**)(ptr)) = NULLPTR;	// For safety and reuse of the pointer passed in by reference
	}
}

void PLN(char num)          	  
{ 
	for (num; num > 0; --num) 
		putchar('\n');  
}       	   // NEW LINES

// Error checking
char goodptr(void* ptr, char* errormsg, char ret) // Checks given pointer, if error message != NOMSG 'errormsg' will be printed, 
{						  // 'ret' determines whether or not to print and exit, or return a notifying value to its caller
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
