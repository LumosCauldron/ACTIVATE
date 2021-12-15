#ifndef CONVERSIONS_H
#define CONVERSIONS_H

#include "tools.h"

#define FREEOLD		1
#define NOFREEOLD	0

char  itoc(int i)        { return (char)i;  }
int   ctoi(char i)       { return (int)i;   }
void* llitovp(long long int i) { return (void*)i; }
char* llitocp(long long int i) { return (char*)i; }
int*  llitoip(long long int i) { return (int*)i;  }
char* vptocp(void* i)	 { return (char*)i; }
int*  vptoip(void* i)	 { return (int*)i;  }
int*  cptoip(char* i)	 { return (int*)i;  }
void* cptovp(char* i)	 { return (void*)i; }

int* ctoi_array(char* array, char freeold)	// Will map each character value to an integer value
{
	register int len = strlen(array);
	int* newarray = MALLOC(len * sizeof(int));
	register int i;
	for (i = 0; i < len; ++i)
		newarray[i] = (int)(array[i]);
	if (freeold)
		FREE(array);
	return newarray;
}

long long int* ctolli_array(char* array, char freeold)	// Will map each character value to an long long int value
{
	register int len = strlen(array);
	long long int* newarray = MALLOC(len * sizeof(long long int));
	register int i;
	for (i = 0; i < len; ++i)
		newarray[i] = (long long int)(array[i]);
	if (freeold)
		FREE(array);
	return newarray;
}

char* itoc_array(int* array, int sz, char freeold)	// Will map each integer value to a character
{
	char* newarray = MALLOC(sz + 1);
	register int i;
	for (i = 0; i < sz; ++i)
		newarray[i] = (char)(array[i]);
	newarray[sz] = '\0';
	if (freeold)
		FREE(array);
	return newarray;
}

long long int* itolli_array(int* array, int sz, char freeold)	// Will map each integer value to a long long int
{
	long long int* newarray = MALLOC(sz * sizeof(long long int));
	register int i;
	for (i = 0; i < sz; ++i)
		newarray[i] = (long long int)(array[i]);
	if (freeold)
		FREE(array);
	return newarray;
}

int* llitoi_array(long long int* array, int sz, char freeold)	// Will map each long long int value to an integer value
{
	int* newarray = MALLOC(sz * sizeof(int));
	register int i;
	for (i = 0; i < sz; ++i)
		newarray[i] = (int)(array[i]);
	if (freeold)
		FREE(array);
	return newarray;
}

char* llitoc_array(long long int* array, int sz, char freeold)	// Will map each long long int value to a character value
{
	char* newarray = MALLOC(sz + 1);
	register int i;
	for (i = 0; i < sz; ++i)
		newarray[i] = (char)(array[i]);
	newarray[sz] = '\0';
	if (freeold)
		FREE(array);
	return newarray;
}

#ifndef MAP_STRNUM_H
#define MAP_STRNUM_H
char* map_decnum_tostr(long long int num, int numdigits) // Function that makes an ascii string representing value in decimal, with a padded amount of digits --> "numdigits"
{ // 18 digits only for the first parameter
	char* neword = NULLPTR;			// Holds new string
	register long long int digits = 1;	// Tracks number of digits
	register int i = 0;			// Counts digits and tracks indexing from 'neword'
	while (num / digits != 0)		// Check to the highest 10th power before going over as a divisor
	{ digits *= 10; ++i; }
	digits /= 10;	// Set back down by 1 power of 10
	register int zeros = (numdigits * (numdigits > 0)) - i;	// Get specified number of padded zeros
	neword = (char*)MALLOC(i + 1 + zeros);	// Get space, +1 for Nul-terminator
	neword[i + zeros] = '\0';			// Nul-terminate
	for(i = 0; i < zeros; ++i)			// Insert zeros			
		neword[i] = 0x30;
	while (digits != 0)				// While not all digits placed into 'neword'
	{
		neword[i++] = num / digits + 0x30;	// Offset to ASCII value
		num -= ((num / digits) * digits);
		digits /= 10;				// Go down by a power of 10
	}
	return neword;
}

long long int map_decstr_tolongint(char* str) // Dark Magic --> String must only contain numbers (up to 8 digits only)
{
	register int num = strlen(str);
	register long long int chosen = 0;
	register long long int shift = 0x100;
	register long long int i;
	register long long int j;
	register long long int holder;
	for (i = num - 1; i >= 0; --i)
	{
		holder = (int)str[i];
		for (j =  num - 1; j > i; --j)
			holder *= shift; 
		chosen |= holder;
	}
	return chosen;
}
#endif

#endif
