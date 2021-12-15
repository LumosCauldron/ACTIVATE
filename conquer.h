#ifndef CONQUER_H
#define CONQUER_H

#include "tools.h"
#include <pthread.h>

typedef struct thread_parameters // Created in 'commence_attack' for an individual thread and remains
{  				 // in existence until freed by that thread's execution
	void* tresources;
	short tnum;
} TParameters;

typedef struct thread_returns	 // Created in 'commence_attack' and remains in existence until freed
{
	long int* trets;
	short retsize;
} TReturns;

pthread_t* tptr;		 // Array of thread ids (parallel to retstruct in index)
TReturns retstruct;		 // Return Structure (parallel to tptr in index)

void* set_thread_resources(short i, void* parameters)
{
	TParameters* newthread_tools = MALLOC(sizeof(TParameters));
	newthread_tools->tresources = parameters;
	newthread_tools->tnum = i;
	return (void*)newthread_tools;
}

void init_retstruct()
{ 	
	retstruct.trets = NULLPTR;			// Set pointer-to-returns to NULLPTR
	retstruct.retsize = 0;				// Set return structure size to zero
}

void add_thread_return(long int ret) // Adds a return value to return structure and increases return size
{	// "ret" can be any address or an integer
	retstruct.trets = REALLOC(retstruct.trets, (++retstruct.retsize * sizeof(long int))); // Get space
	retstruct.trets[retstruct.retsize - 1] = ret;					   // Increase size
}

TReturns* commence_attack(short operations, void* (*fcptr)(void*), void* parameters)
{
	if (!operations) return NULLPTR;		// Check for 0 operations (prevents segfault)
	register short i;
	init_retstruct();				// Initialize return structure
	tptr = MALLOC(operations * sizeof(pthread_t));	// Make space for thread ids
	for (i = 0; i < operations; ++i)		// Create operations and execute
		pthread_create(&tptr[i], NULL, fcptr, set_thread_resources(i, parameters));	
	for (i = 0; i < operations; ++i)		// Join all threads
		pthread_join(tptr[i], NULL);
	FREE(&tptr);	// Free thread id array
	return &retstruct;
}

/*/ ****** EXAMPLE THREAD FUNCTION FORMAT ****** //
char array[100];
void* thread_format(void* iptr)
{
	TParameters* paramptr = (TParameters*)iptr;	// Set pointer to threadparameters
	printf("Thread %d\n", paramptr->tnum);
	// Do stuff...
	// Maybe --> add_thread_return(somevalue);	// Always before the 'free' function
	FREE(iptr);
}
// ****** EXAMPLE THREAD FUNCTION FORMAT ****** /*/
#endif
