#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "tools.h"
#include "conditions.h"

extern int global;

// *********************************** For - loops *********************************** //

void floop_onglobals(int (*func)(int i, int n), int num)		// Loops function and globals are changed by 'func', nothing is returned
{
	register int i;		// Index
	for (i = 0; i < num; ++i)
		func(i,  global);	// Do function "num" times
}

int floop_combine(int (*func)(int i, int n), int num)		// Loops function and adds each result towards the final value
{
	register int val = 0;		// Stores final value
	register int i;		// Index
	for (i = 0; i < num; ++i)
		val += func(i,  global);	// Do function "num" times
	return val;		//  Return final value
}

int* floop_layout_int(int (*func)(int i, int n), int num)	// Loops function and stores each result in an array of integers
{
	int* array = MALLOC(num * sizeof(int));	// Get space
	register int i;			// Index
	for (i = 0; i < num; ++i)
		array[i] = func(i,  global);		// Fill array
	return array;			// Return array address
}

char* floop_layout_str(int (*func)(int i, int n), int num)	// Loops function and stores each result in an array of characters
{
	char* neword = MALLOC(num + 1);	// Get space
	neword[num] = '\0';			// Nul-terminate
	register int i;			// Index
	for (i = 0; i < num; ++i)
		neword[i] = func(i,  global);	// Fill array
	return neword;			// Return array in form of a string
}

// *********************************** While - loops *********************************** //

void wloop_onglobals(int (*func)(int, int), int* condition)		// Loops function, nothing is returned ("condition" must be changed by 'func')
{
	register int i = 0;
	while (*condition)
		func(i++, global);	// Do function until condition reached
}

int wloop_combine(int (*func)(int i, int n), int* condition)		// Loops function and adds each result towards the final value
{
	register int val = 0;
	register int i = 0;
	while (*condition)
		val += func(i++, global);	// Do function until condition reached
	return val;
}

int* wloop_layout_int(int (*func)(int i, int n), int* condition)	// Loops function and stores each result in an array of integers
{
	int* array = NULLPTR;		// Get space
	register int i = 0;		// Index
	while (*condition)
	{
		array = REALLOC(array, (i + 1) * sizeof(int));	// Get space for each loop
		array[i++] = func(i,  global);			// Do function until condition reached
	}
	return array;
}

char* wloop_layout_str(int (*func)(int i, int n), int* condition)	// Loops function and stores each result in an array of characters
{
	char* neword = NULLPTR;		// Get space
	register int i = 0;		// Index
	while (*condition)
	{
		neword = REALLOC(neword, (i + 2)); // Get space for each loop (+1 for offset, +1 for Nul-termination)
		neword[i++] = func(i,  global);	   // Do function until condition reached
	}
	neword[i] = '\0';		// Nul-terminate string
	return neword;
}

#endif
