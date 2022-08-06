#ifndef TOOLS_H
#define TOOLS_H

#include <stdint.h>
#include "bytes.h"

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
static inline void PRINTF(float num)            { printf("%lf\n", num);  	 }       // FLOAT
static inline void PRINTD(double num)           { printf("%lf\n", num);  	 }       // DOUBLE

void print_space_format256(u8 x, u8 sign)
{
	switch(sign)
	{
		case 2:
			if (x > 0x0f)
				printf(" 0x%x,",   x);
			else
				printf(" 0x0%x,",  x);
			break;
		case 1:	
			if (x > 100)
				printf(" %d,",   (i8)x);
			else if (x > 10)
				printf("  %d,",  (i8)x);
			else
				printf("   %d,", (i8)x);
			break;
		case 0:
			if (x > 100)
				printf(" %u,",   x);
			else if (x > 10)
				printf("  %u,",  x);
			else
				printf("   %u,", x);
	}
}

// UNDER DEVELOPMENT
 void printsboxes(u8* box)
 {
 	register u16 x = 0;
 	register u16 y;
 	u8 inverse[256];
 	zeroarray(inverse, 256);
 	printf("u8 sbox[BOXSZ] = {");
	for (y = 0; y < 256; ++y)
	{
		print_space_format256(box[y], 2);
		++x;
		if (x == 16 && x != 256)
		{
			PLN(1);
			printf("                  ");
			x = 0;
		}
		
		inverse[box[y]] = y;
	}
	PLN(2);
	printf("u8 sboxinverse[BOXSZ] = {");
	x = 0;
	for (y = 0; y < 256; ++y)
	{
		print_space_format256(inverse[y], 2);
		++x;
		if (x == 16)
		{
			PLN(1);
			printf("                         ");
			x = 0;
		}
	}
 }

void PRINTNUMARRAY(i64* arr, u32 sz) 
{
	goodptr(arr, "NULLPTR GIVEN TO PRINTNUMARRAY", NOFUNC_RETURN);
	register u32 i; 
	for (i = 0; i < sz; ++i)
		printf("%ld ", *(arr + i)); 
	printf("\n"); 
}

void* dynamic_obj(void* obj, u8 type, u32 sz)
{
	if (!goodptr(obj, NOMSG, FUNC_RETURN) || !type || !sz)		// Error checking
		return NULLPTR;
	register u32 i;
	switch(type)				// This makes 2 pointer of the correct "type", then fills dynamic array with object elements, then returns new obj
	{
		case sizeof(i8)          : ;   i8* ptr1     = MALLOC(type * sz);
					       i8* optr1    = (i8*)obj;
					       for (i = 0; i < sz; ++i) { *(ptr1 + i) = *(optr1 + i); }
			 		       return ptr1;
		case sizeof(i16)         : ;   i16* ptr2    = MALLOC(type * sz);
					       i16* optr2   = (i16*)obj;
					       for (i = 0; i < sz; ++i) { *(ptr2 + i) = *(optr2 + i); }
			                       return ptr2;
		case sizeof(i32)         : ;   i32* ptr4    = MALLOC(type * sz);
					       i32* optr4   = (i32*)obj;
					       for (i = 0; i < sz; ++i) { *(ptr4 + i) = *(optr4 + i); }
			                       return ptr4;
		case sizeof(i64) 	 : ;   i64* ptr8    = MALLOC(type * sz);
					       i64* optr8   = (i64*)obj;
					       for (i = 0; i < sz; ++i) { *(ptr8 + i) = *(optr8 + i); }
			                       return ptr8;
	}
	return NULLPTR;
}

#endif
