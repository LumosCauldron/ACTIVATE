#ifndef CONQUER_H
#define CONQUER_H

#include <pthread.h>
#include "functions.h"		// Includes "basic.h", "bytes.h", and "tools.h"

#define MAXTHREADS_S 32
#define SLEEPSAVE  (0.25)	// Used to wait until thread finishes (last resort timing to ensure program's smooth execution)
#define GROUP1	   1
#define GROUP2	   2
#define GROUP3	   3
#define GROUP4	   4

#define LARGEBUFFERSZ 1000000000

struct tid
{
	pthread_t tid;		// Holds thread id
	unsigned int mark;	// Used to identify groups of threads to join (no zero values allowed)
};

typedef struct tid Tid;

// ******************* PROTOTYPES START ******************* //
void addtid(pthread_t, unsigned int);
// *******************  PROTOTYPES END  ******************* //

Tid joinarray[MAXTHREADS_S + 1];
Tid* tidptr = NULLPTR;

void* blackbox(void* package)
{
	Mission* objective = (Mission*)(package);
	missionstart(&objective);
	return NULLPTR;
}

// WRAPPERS

char INIT_THREADATTR(pthread_attr_t* attrptr, int attachedstate)
{
	if (pthread_attr_init(attrptr) == EMPTY)
		return 0;
	if (pthread_attr_setdetachstate(attrptr, attachedstate) == EMPTY)
		return 0;
	pthread_attr_setscope(attrptr, PTHREAD_SCOPE_SYSTEM);		// Indicate thread to execute in kernel space (hopefully)
	return 1;
} 

char DESTROY_THREADATTR(pthread_attr_t* attrptr)
{
	if (pthread_attr_destroy(attrptr) == EMPTY)
		return 0;
	return 1;
}

char DETACHTHREAD(pthread_t tid)
{
	if (pthread_detach(tid) == EMPTY)
	{
		PRINT("FAILED TO DETACH THREAD, PROGRAM HAS A LOST THREAD");
		return 0;
	}
	return 1;
}

// Touches 'tidptr'
char CREATETHREAD(Mission* package, int attachedstate, unsigned int mark, pthread_t* tidaddr)	// Creates a thread, handles thread creation fail, places a tid value in '*tidaddr'
{												// (modifies 'joinarray' if attachedstate == PTHREAD_CREATE_JOINABLE)
	const pthread_attr_t attributes;
	register unsigned char errorstatus = 0;
	INIT_THREADATTR((pthread_attr_t*)(&attributes), attachedstate);	 					// Make attribute set (initializes 'attributes')
	if (errorstatus = pthread_create(tidaddr,(pthread_attr_t*)(&attributes), &blackbox, (void*)(package)))	// Execute new thread (initializes 'tid')
	{
		PRINTN((int)(errorstatus));
		PRINT("FAILED TO CREATE THREAD");
	}
	//else
	//	printf("Started thread %ld\n", *tidaddr);
	DESTROY_THREADATTR((pthread_attr_t*)(&attributes));	      						// Destroy (forget about) attribute set
	return (!errorstatus);	// Return if success, else return 0
}

char JOINTHREAD(pthread_t tid)
{
	char hold = pthread_join(tid, NULL);
	if (hold)
	{
		PRINTN((int)(hold));
		PRINT("FAILED TO JOIN THREAD, DETACHING");
		DETACHTHREAD(tid);
		return 0;
	}
	return 1;
}

// Touches 'tidptr'
void clearjoinarray()	// Clear all data in 'joinarray' and set 'tidptr' back to beginning of the 'joinarray'
{
	zeroarray((char*)(joinarray), sizeof(Tid) * MAXTHREADS_S + 1);	// Zero out this portion of the array
	tidptr = joinarray;
}

// Touches 'tidptr'
void addtid(pthread_t tid, unsigned int mark) // Will add a thread id to a 32-byte array (MAXTHREADS_S-byte array), will detach thread if no space is found
{
	if (!tidptr)						  // If first time use
		clearjoinarray();				  // Initialize 'joinarray' to all zeros and set 'tidptr' to beginning of 'joinarray'
	if (!mark)						  // No 'mark' can be zero, therefore all zero inputs default to a group 'mark' of 1
		++mark;
	register Tid* boundary       = joinarray + MAXTHREADS_S;  // Can be in register as it is never dereferenced
	register Tid* originaltidptr = tidptr;			  // Can be in register as it is never dereferenced
	while(tidptr->mark)					  // Skip all thread spots that are taken, stop at available slot in array
		++tidptr;
	if (tidptr == boundary)					  // If no space found from middle to end, reset, search from beginning to middle
	{
		tidptr = joinarray;
		while(tidptr->mark && tidptr < originaltidptr)	  // Skip all thread spots that are taken, stop at available slot in array (before original tidptr)
			++tidptr;
		if (tidptr >= originaltidptr)			  // If no space found detach thread
		{
			PRINT("NO ROOM DETACHING THREAD");
			DETACHTHREAD(tid);
			#ifdef WINCODE
				Sleep(SLEEPSAVE);
			#endif
			#ifdef UNIXCODE
				sleep(SLEEPSAVE);
			#endif
			return;				 	 // Skip adding thread id and return
		}
	}
	tidptr->tid      = tid;		// Set thread id (usually 0 as 'CREATETHREAD()' sets this value)
	tidptr->mark     = mark;	// Set thread mark (NEVER ZERO)
	++tidptr;			// Move to next slot
}

void unaddtid()	// Must be done soon after a thread is added
{
	--tidptr;				 // Point back to the new initialized 'Tid' element within 'joinarray'
	zeroarray((char*)(tidptr), sizeof(Tid)); // Zero out slot that was initialized with a 'Tid' element
}

void jointidgroup(unsigned int mark) // Will join all threads or a specified group and will free all their mission objects regardless of 'mission_object.cleanaction'
{
	register Tid* boundary = joinarray + MAXTHREADS_S;	// Can be held in register as it is never dereferenced
	Tid* ptr;
	for (ptr = joinarray; ptr < boundary; ++ptr)		// For each mark that matches, join corresponding thread
		if (ptr->mark == mark)
		{
			JOINTHREAD(ptr->tid);			// Join thread id (no need to accept a return value as functions.h has that capability)
			zeroarray((char*)(ptr), sizeof(Tid));	// Zero out this portion of the array
		}
}

void joinall()	// Will join all threads and will free all mission objects regardless of 'mission_object.cleanaction'
{
	register Tid* boundary = joinarray + MAXTHREADS_S; // Can be held in register as it is never dereferenced
	Tid* ptr;
	for (ptr = joinarray; ptr < boundary; ++ptr)	   // For each mark that matches, join corresponding thread
	{
		if (ptr->mark)
			JOINTHREAD(ptr->tid);		   // Join thread id (no need to accept a return value as functions.h has that capability)
	}
	clearjoinarray();
}

void printtidarray()
{
	Tid* boundary = joinarray + MAXTHREADS_S; // Can be held in register as it is never dereferenced
	Tid* ptr;
	for (ptr = joinarray; ptr < boundary; ++ptr)	   // Print each thread object
	{ printf("_____________________\nTID   |%ld|  ", ptr->tid); printf("GROUP |%d|\n", ptr->mark); }	  
}

void conquermission(Mission* package, int policy, unsigned int mark)	// Creates a thread and sends in a 'Mission' as a package to be executed 
{									// 'attr' only used to indicate attached or detached state
     if (!mark)
	THROW("THREAD MARK IS ZERO...NOT ALLOWED, WILL CAUSE MULTIPLE JOINS OF THREAD ID 0");

     if (policy == PTHREAD_CREATE_JOINABLE) // If still attached, add thread id for later joining
		addtid(0, mark);   	    // Increments 'tidptr' until free slot is found, fills it, and increments 'tidptr' to another slot (must decrement by 1 to directly access again)
					     
     if (!CREATETHREAD((void*)(package), policy, mark, &((tidptr - 1)->tid))) // ('CREATETHREAD()' sets 'tid_object.tid' value)
     { 									    			
	PRINT("THREAD NOT EXECUTED...EXECUTING MANUALLY");					
	if (policy == PTHREAD_CREATE_JOINABLE)
		unaddtid();
        missionstart(&package);	// Execute task manually if nbytestothread creation failed
     }
}

// Access granted to global variable 'cores'
void conquer_nbytesto(char* dest, char* src, unsigned long long int len)	// Same as 'nbytesto' but uses multithreading
{
	register unsigned long long int blocks = len / cores;
	if (blocks < (LARGEBUFFERSZ / cores))
	{
		nbytesto(dest, src, len);
		return;
	}
	register unsigned long long int remainder = len % cores; // Holds remainder of bytes to add in
	register unsigned long long int holdcalc;		 // Holds offset calculation for what segment of memory to assign "nbytesto"
	Mission* holder;					 // Placeholder for mission pointer returned by 'missionplan()'
	register unsigned char holdcorescalc = cores - 1;	 // Calculation before loop to optimize speed
	register unsigned char i;
	for (i = 0; i < holdcorescalc; ++i)
	{
		holdcalc = (i * blocks);
		holder = missionplan(&nbytesto,
				     assign3tools((MISSIONTOOL)(dest + holdcalc), (MISSIONTOOL)(src + holdcalc), (MISSIONTOOL)(blocks)),
				     3,
				     FREEMISSION);
		conquermission(holder, PTHREAD_CREATE_JOINABLE, GROUP2);
	}
  holdcalc = (i * blocks);
  holder = missionplan(&nbytesto, assign3tools((MISSIONTOOL)(dest + holdcalc), (MISSIONTOOL)(src + holdcalc), (MISSIONTOOL)(blocks + remainder)), 3, FREEMISSION);
  conquermission(holder, PTHREAD_CREATE_JOINABLE, GROUP2);
}

#endif
