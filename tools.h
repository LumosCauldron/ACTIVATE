#ifndef TOOLS_H
#define TOOLS_H

#include <stdint.h>
#include "bytes.h"

#define CHAR	  1
#define SHORT     2
#define INT       4
#define LONGLONG  8

// **************************************************************** WRAPPER FUNCTIONS

static inline void PRINTC(char chr)             { printf("%c\n", chr);   	 }	 // CHAR
static inline void PRINT8(int8_t num)           { printf("%u\n", (int8_t)num);  }	 // SIGNED 8-bit
static inline void PRINTU8(uint8_t num)         { printf("%u\n", (uint8_t)num); }       // UNSIGNED 8-bit
static inline void PRINTN(int num) 	         { printf("%d\n", num);   	 }	 // INT
static inline void PRINTUN(int num) 	         { printf("%u\n", num);   	 }	 // UNSIGNED INT
static inline void PRINTLLN(long long int num)  { printf("%lld\n", num); 	 }	 // LONG LONG INT
static inline void PRINTULLN(long long int num) { printf("%llu\n", num); 	 }	 // UNSIGNED LONG LONG INT
static inline void PRINTX(int num) 	         { printf("0x%x\n", num);   	 }	 // HEX
static inline void PRINTLLX(long long int num)  { printf("0x%llx\n", num); 	 }	 // LONG LONG HEX
static inline void PRINTF(float num)            { printf("%llf\n", num);  	 }       // FLOAT
static inline void PRINTD(double num)           { printf("%llf\n", num);  	 }       // DOUBLE


// UNDER DEVELOPMENT
/* void PRINTN_LEFT_ALIGNED(long long int num, char sign)
{
	register long long int holder = num;
	while(holder /= 10)
		putc(' ');
	if (sign)
		printf("%lln", (long long int)(num));
	else
		printf("%lln", (unsigned long long int)(num));
} */

void PRINTNUMARRAY(long long int* arr, int sz) 
{
	goodptr(arr, "NULLPTR GIVEN TO PRINTNUMARRAY", NOFUNC_RETURN);
	register int i; 
	for (i = 0; i < sz; ++i)
		printf("%lld ", arr[i]); 
	printf("\n"); 
}

char* dynamic_string(char* str)		// Make string in heap [ACCESSIBLE]
{
	if (!goodptr(str, NOMSG, FUNC_RETURN))
		return NULLPTR;
	register int len = countuntilnul(str);		// Get length		
	char* neword = MALLOC(countuntilnul(str) + 1); // Make space
	neword = nbytesto(neword, str, len);	// Copy string into place
	neword[len] = '\0';			// Nul-terminate
	return neword;				// Return new string
}

void* dynamic_obj(void* obj, unsigned int type, unsigned int sz)
{
	if (!goodptr(obj, NOMSG, FUNC_RETURN) || !type || !sz)		// Error checking
		return NULLPTR;
	register unsigned int i;
	switch(type)				// This makes 2 pointer of the correct "type", then fills dynamic array with object elements, then returns new obj
	{
		case sizeof(char)          : ; char* ptr1           = MALLOC(type * sz);
					       char* optr1          = (char*)obj;
					       for (i = 0; i < sz; ++i) { ptr1[i] = optr1[i]; }
			 		       return ptr1;
		case sizeof(short)         : ; short* ptr2          = MALLOC(type * sz);
					       short* optr2         = (short*)obj;
					       for (i = 0; i < sz; ++i) { ptr2[i] = optr2[i]; }
			                       return ptr2;
		case sizeof(int)           : ; int* ptr4            = MALLOC(type * sz);
					       int* optr4           = (int*)obj;
					       for (i = 0; i < sz; ++i) { ptr4[i] = optr4[i]; }
			                       return ptr4;
		case sizeof(long long int) : ; long long int* ptr8  = MALLOC(type * sz);
					       long long int* optr8 = (long long int*)obj;
					       for (i = 0; i < sz; ++i) { ptr8[i] = optr8[i]; }
			                       return ptr8;
	}
	return NULLPTR;
}

#endif
