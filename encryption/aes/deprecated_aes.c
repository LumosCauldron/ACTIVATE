#ifndef TOOLS_H
#define TOOLS_H

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NULLPTR (void*)(0)
#define at(x) (&x)
#define EMPTY -1

#define CHAR	  0
#define SHORT     1
#define INT       2
#define LONG      3
#define LONG_LONG 4

// **************************************************************** WRAPPER FUNCTIONS

#define HALT		1
#define PASSTHROUGH	0

int ROUNDS = 10;
int Nklen = 4;

int MOD(int x, int y)	         { x = x % y; return (x * (x >= 0) + (x + y) * (x < 0)); }
void THROW(char* str); /* PROTO */
void PRINT(char* str)            { if (!str) THROW("NO STRING"); printf("%s\n", str); }	   // String
void PRINTC(char chr)            { printf("%c\n", chr);   }	   // CHAR
void PRINTN(int num) 	         { printf("%d\n", num);   }	   // INT
void PRINTUN(unsigned int num) 	 { printf("%d\n", num);   }	   // INT
void PRINTLLN(long long int num) { printf("%lld\n", num); }	   // INT
void PRINTX(int num) 	         { printf("%x\n", num);   }	   // INT
void PRINTLLX(long long int num) { printf("%llx\n", num); }	   // INT
void PRINTD(double num)          { printf("%lf\n", num);  }        // DOUBLE

void PRINTCARRAY(unsigned long long int* arr, int sz) 
{
	register int i; 
	for (i = 0; i < sz; ++i)
		printf("%c ", (char)arr[i]); 
	printf("\n"); 
}

void PRINTNUMARRAY(unsigned long long int* arr, int sz) 
{
	register int i; 
	for (i = 0; i < sz; ++i)
		printf("%lld ", arr[i]); 
	printf("\n"); 
}

void PRINTHEXARRAY(unsigned long long int* arr, int sz) 
{
	register int i; 
	for (i = 0; i < sz; ++i)
		printf("%llx ", 0x000000ff & arr[i]); 
	printf("\n"); 
}

void EXIT(char stop)  { if (stop) exit(7); }

void THROW(char* str) { PRINT(str); exit(9); }

void* MALLOC(long long int space)
{
	void* ptr = NULLPTR; ptr = malloc(space);
	if (!ptr) { PRINT("MALLOC ERROR"); EXIT(HALT); }
	return ptr;
}

void* REALLOC(void* ptr, long long int space)
{
	ptr = realloc(ptr, space);
	if (!ptr) { PRINT("REALLOC ERROR"); EXIT(HALT); }
	return ptr;
}

void* CALLOC(long long int space)
{
	void* ptr = NULLPTR; ptr = calloc(1, space);
	if (!ptr) { PRINT("CALLOC ERROR"); EXIT(HALT); }
	return ptr;
}


void FREE(void* ptr)
{ if (ptr) free(ptr); }

void* dynamic_obj(void* obj, unsigned int type, unsigned int sz)
{
	if (!type || !sz || !obj)		// Error checking
		return NULLPTR;
	register unsigned int i;
	switch(type)				// This makes 2 pointer of the correct "type", then fills dynamic array with object elements, then returns new obj
	{
		case sizeof(char)          : ; char* ptr1           = CALLOC(type * sz);
					       char* optr1          = (char*)obj;
					       for (i = 0; i < sz; ++i) { ptr1[i] = optr1[i]; }
			 		       return ptr1;
		case sizeof(short)         : ; short* ptr2          = CALLOC(type * sz);
					       short* optr2         = (short*)obj;
					       for (i = 0; i < sz; ++i) { ptr2[i] = optr2[i]; }
			                       return ptr2;
		case sizeof(int)           : ; int* ptr4            = CALLOC(type * sz);
					       int* optr4           = (int*)obj;
					       for (i = 0; i < sz; ++i) { ptr4[i] = optr4[i]; }
			                       return ptr4;
		case sizeof(long long int) : ; long long int* ptr8  = CALLOC(type * sz);
					       long long int* optr8 = (long long int*)obj;
					       for (i = 0; i < sz; ++i) { ptr8[i] = optr8[i]; }
			                       return ptr8;
	}
	return NULLPTR;
}

#endif





#ifndef CONVERSIONS_H
#define CONVERSIONS_H

#define FREEOLD		1
#define NOFREEOLD	0

long long int* ctolli_array(uint8_t* array, char freeold, int sz)	// Will map each character value to an long long int value
{
	register int len = sz;
	if (!sz)
		len = strlen(array);
	long long int* newarray = MALLOC(len * sizeof(long long int));
	register int i;
	for (i = 0; i < len; ++i)
		newarray[i] = 0x00000000000000ff & (long long int)(array[i]);
	if (freeold)
		FREE(array);
	return newarray;
}

char* llitoc_array(long long int* array, int sz, char freeold, char nul)	// Will map each long long int value to a character value
{
	char* newarray = MALLOC(sz + nul);
	register int i;
	for (i = 0; i < sz; ++i)
		newarray[i] = 0x00000000000000ff & (uint8_t)(array[i]);
	if (nul)
		newarray[sz] = '\0';
	if (freeold)
		FREE(array);
	return newarray;
}


#endif



#ifndef MATRIX_H
#define MATRIX_H

#define FREEMATRIX    1
#define NOFREEMATRIX  0

typedef struct matrix
	{
	  long long int* matrix;	// Holds full matrix in the form of an array
	  unsigned int numrow;
	  unsigned int numcol;
	} Matrix;

Matrix* create_matrix(long long int* array, unsigned int rsz, unsigned int csz)
{
	if (!rsz || !csz)
		THROW("ROW OR COLUMN SIZE IS ZERO");
	Matrix* newsquare = CALLOC(sizeof(Matrix)); // Zeros are padded to end of matrix
	newsquare->numrow = rsz;
	newsquare->numcol = csz;
	newsquare->matrix = (long long int*)dynamic_obj(array, sizeof(long long int), rsz * csz);
	return newsquare;
}

Matrix* copy_matrix(Matrix* ptr)	// Does not destroy original
{
	Matrix* newsquare = CALLOC(sizeof(Matrix)); // Zeros are padded to end of matrix
	newsquare->numrow = ptr->numrow;
	newsquare->numcol = ptr->numcol;
	newsquare->matrix = (long long int*)dynamic_obj(ptr->matrix, sizeof(long long int), ptr->numrow * ptr->numcol);
	return newsquare;
}

void destroy_matrix(Matrix* ptr, char freematrix)	// Zeros out everything and frees the memory
{
	if (!ptr)
		return;
	register int i;
	register int sz = ptr->numcol * ptr->numrow;

	ptr->numcol = 0;
	ptr->numrow = 0;
	if (freematrix)
		FREE(ptr->matrix);
	else
	{
		for (i = 0; i < sz; ++i)
			ptr->matrix[i] = 0;
	}
	FREE(ptr);
}

long long int* column(unsigned int col, Matrix* ptr)
{
	if (--col >= ptr->numcol)		// Checks for out of range (The --col is to calibrate "col" for the for loop while checking for out of range at the same time)
		return NULLPTR;
	long long int* COLUMN = MALLOC(sizeof(long long int) * ptr->numrow);	// Get space
	register unsigned int i;
	for (i = 0; i < ptr->numrow; ++i)
		COLUMN[i] = ptr->matrix[col + (ptr->numcol * i)];		// Get column from matrix
	return COLUMN;								// Return column
}

void replacecolumn(unsigned int col, long long int* replacer, Matrix* ptr, char freereplacer)
{
	if (--col >= ptr->numcol)		// Checks for out of range (The --col is to calibrate "col" for the for loop while checking for out of range at the same time)
		THROW("COLUMN SPECIFIED NONEXISTANT");
	register unsigned int i;
	for (i = 0; i < ptr->numrow; ++i)
		ptr->matrix[col + (ptr->numcol * i)] = replacer[i];		// Get column from matrix
	if (freereplacer)		// Free original holder of the injected values (prevents memory leak)
		FREE(replacer);
}

long long int* row(unsigned int rw, Matrix* ptr)
{
	if (--rw >= ptr->numrow)	// Checks if out of range (The --rw is to calibrate "rw" for the for loop while checking for out of range at the same time)
		return NULLPTR;
	long long int* ROW = MALLOC(sizeof(long long int) * ptr->numcol); // Get space
	register unsigned int i;
	for (i = 0; i < ptr->numcol; ++i)
		ROW[i] = ptr->matrix[i + (ptr->numcol * rw)];		  // Get row from matrix
	return ROW;							  // Return column
}

void replacerow(unsigned int rw, long long int* replacer, Matrix* ptr, char freereplacer)
{
	if (--rw >= ptr->numrow)	// Checks if out of range (The --rw is to calibrate "rw" for the for loop while checking for out of range at the same time)
		THROW("ROW SPECIFIED NONEXISTANT");
	register unsigned int i;
	for (i = 0; i < ptr->numcol; ++i)
		ptr->matrix[i + (ptr->numcol * rw)] = replacer[i]; // Get row from matrix
	if (freereplacer)		// Free original holder of the injected values (prevents memory leak)
		FREE(replacer);
}

void invertmatrix(Matrix* ptr)		// Inverts a square matrix
{
	if (ptr->numcol != ptr->numrow)
		THROW("MUST BE A SQUARE MATRIX IN ORDER TO INVERT");
	
	Matrix* copy = copy_matrix(ptr);
	register int i;
	for (i = 0; i < ptr->numrow; ++i)
		replacerow(i + 1, column(i + 1, copy), ptr, FREEOLD);
	destroy_matrix(copy, FREEMATRIX);
}

// ********************* OPERATIONS ********************* //

char bytemult(uint8_t first, uint8_t arrval)	// Executes Galois Field Multiplication [Only applicable to AES]
{
	first &= 0x00000000000000ff;
	arrval &= 0x00000000000000ff;
	char f = 0;
	if (arrval == 0x01)	  // If 1
		return first;
	else if (arrval == 0x02)  // If x
	{
		f = 0b10000000 & first;
		first <<= 1;
		if (f) return first ^ 0b00011011;
		else   return first ^ 0b00000000;
	}	
	else if (arrval == 0x03)  // If x+1
		return first ^ bytemult(first, 2);	
	else if (arrval == 0x09)  // Inverse
		return first ^ bytemult(bytemult(bytemult(first, 2), 2), 2);
	else if (arrval == 0x0b)  // Inverse
		return first ^ bytemult(first ^ bytemult(bytemult(first, 2), 2), 2);
	else if (arrval == 0x0d)  // Inverse
		return first ^ bytemult(bytemult(first ^ bytemult(first, 2), 2), 2);
	else if (arrval == 0x0e)  // Inverse
		return bytemult(first ^ bytemult(first ^ bytemult(first, 2), 2), 2);
	else
		THROW("ARRAY VALUE ERROR: only 0x01, 0x02, 0x03, 0x09, 0x0b, 0x0d, and 0x0e allowed");
	return 0; // Unreachable
}

char bytesubadd(uint8_t first, uint8_t second) { return (0x00000000000000ff & first) ^ (0x00000000000000ff & second); }

// Note: using byte multiplication here...so column must come from msg matrix and row from aes const. matrix (so only 1,2,3 values are on right side of 'bytemult' calculations)
long long int rowbycol(long long int* row, long long int* col, int rowelementsz)	// Multiplies row by column and returns a value, BOTH MUST HOLD THE SAME ARRAY LENGTH
{
	long long int val = 0;		// Value to hold operation result
	register unsigned int i;	
	for (i = 0; i < rowelementsz; ++i)	// For every row/column element value add result to final value
		val ^= bytemult(col[i], row[i]);	// col[i] is from msg, row[i] is from aes const matrix
	return 0x00000000000000ff & val;
}

long long int* matrixbycol(Matrix* ptr, long long int* COLUMN, char freecolumn)		// Returns a column
{
	long long int* NEWCOLUMN = MALLOC(sizeof(long long int) * ptr->numrow);	// Get space for new column
	register unsigned int i;	
	for (i = 1; i <= ptr->numrow; ++i)	// For every row get ith 'row' and multiply by column, each are of size 'numrow'
		NEWCOLUMN[i - 1] =  rowbycol(row(i, ptr), COLUMN, ptr->numcol);
	if (freecolumn)		// Free original holder of the injected values (prevents memory leak)
		FREE(COLUMN);
	return NEWCOLUMN;	// Return new column values in the form of a column
}

// RIGHT 1
// LEFT	 0
long long int* rotaterow(long long int* arr, int arrsz, char dir, int num)	// Rotates array by "num" shifts in direction "dir"
{
	if (!arr) return arr;					// If no array return NULLPTR
	if (!MOD(num, arrsz)) return arr;			// Checks if no work is needed
	num = abs(MOD((-(!dir) * num + num * dir), arrsz));	// Calibrates char array offset
	long long int* holder = MALLOC(arrsz * sizeof(long long int));	// Makes a bucket
	register int i;
	for (i = 0; i < arrsz; ++i)
		holder[MOD((i + num), arrsz)] = arr[i]; 	// Fills array with calculated rotation
	for (i = 0; i < arrsz; ++i)
		arr[i] = holder[i];				// Overwrite array with bucket values
	FREE(holder);					 	// Deletes bucket
	return arr;
}

#endif



#define ROWSIZE 4
#define COLSIZE 4
#define BLKSIZE 16
#define MIXERSZ 16
#define SBOXDIM	16
#define SBOXSZ	256

#define ENCRYPT 1
#define DECRYPT 0
char MODE = 1;

// SBOX FROM AES
uint8_t sbox[SBOXSZ] = 
// 	00 	01 	02 	03 	04 	05 	06 	07 	08 	09 	0a 	0b 	0c 	0d 	0e 	0f
/*00*/{	0x63, 	0x7c, 	0x77, 	0x7b, 	0xf2, 	0x6b, 	0x6f, 	0xc5, 	0x30, 	0x01, 	0x67, 	0x2b, 	0xfe, 	0xd7, 	0xab, 	0x76,
/*10*/ 	0xca, 	0x82, 	0xc9, 	0x7d, 	0xfa, 	0x59, 	0x47, 	0xf0, 	0xad, 	0xd4, 	0xa2, 	0xaf, 	0x9c, 	0xa4, 	0x72, 	0xc0,
/*20*/  0xb7, 	0xfd, 	0x93, 	0x26, 	0x36, 	0x3f, 	0xf7, 	0xcc, 	0x34, 	0xa5, 	0xe5, 	0xf1, 	0x71, 	0xd8, 	0x31, 	0x15,
/*30*/ 	0x04, 	0xc7, 	0x23, 	0xc3, 	0x18, 	0x96, 	0x05, 	0x9a, 	0x07, 	0x12, 	0x80, 	0xe2, 	0xeb, 	0x27, 	0xb2, 	0x75,
/*40*/ 	0x09,	0x83, 	0x2c, 	0x1a, 	0x1b, 	0x6e, 	0x5a, 	0xa0, 	0x52, 	0x3b, 	0xd6, 	0xb3, 	0x29, 	0xe3, 	0x2f, 	0x84,
/*50*/ 	0x53, 	0xd1, 	0x00, 	0xed, 	0x20, 	0xfc, 	0xb1, 	0x5b, 	0x6a, 	0xcb, 	0xbe, 	0x39, 	0x4a, 	0x4c, 	0x58, 	0xcf,
/*60*/ 	0xd0, 	0xef, 	0xaa, 	0xfb, 	0x43, 	0x4d, 	0x33, 	0x85, 	0x45, 	0xf9, 	0x02, 	0x7f, 	0x50, 	0x3c, 	0x9f, 	0xa8,
/*70*/ 	0x51, 	0xa3, 	0x40, 	0x8f, 	0x92, 	0x9d, 	0x38, 	0xf5, 	0xbc, 	0xb6, 	0xda, 	0x21, 	0x10, 	0xff, 	0xf3, 	0xd2,
/*80*/ 	0xcd, 	0x0c, 	0x13, 	0xec, 	0x5f, 	0x97, 	0x44, 	0x17, 	0xc4, 	0xa7, 	0x7e, 	0x3d, 	0x64, 	0x5d, 	0x19, 	0x73,
/*90*/ 	0x60, 	0x81, 	0x4f, 	0xdc, 	0x22, 	0x2a, 	0x90, 	0x88, 	0x46, 	0xee, 	0xb8, 	0x14, 	0xde, 	0x5e, 	0x0b, 	0xdb,
/*a0*/ 	0xe0, 	0x32, 	0x3a, 	0x0a, 	0x49, 	0x06, 	0x24, 	0x5c, 	0xc2, 	0xd3, 	0xac, 	0x62, 	0x91, 	0x95, 	0xe4, 	0x79,
/*b0*/ 	0xe7, 	0xc8, 	0x37, 	0x6d, 	0x8d, 	0xd5, 	0x4e, 	0xa9, 	0x6c, 	0x56, 	0xf4, 	0xea, 	0x65, 	0x7a, 	0xae, 	0x08,
/*c0*/ 	0xba, 	0x78, 	0x25, 	0x2e, 	0x1c, 	0xa6, 	0xb4, 	0xc6, 	0xe8, 	0xdd, 	0x74, 	0x1f, 	0x4b, 	0xbd, 	0x8b, 	0x8a,
/*d0*/ 	0x70, 	0x3e, 	0xb5, 	0x66, 	0x48, 	0x03, 	0xf6, 	0x0e, 	0x61, 	0x35, 	0x57, 	0xb9, 	0x86, 	0xc1, 	0x1d, 	0x9e,
/*e0*/ 	0xe1, 	0xf8, 	0x98, 	0x11, 	0x69, 	0xd9, 	0x8e, 	0x94, 	0x9b, 	0x1e, 	0x87, 	0xe9, 	0xce, 	0x55, 	0x28, 	0xdf,
/*f0*/ 	0x8c, 	0xa1, 	0x89, 	0x0d, 	0xbf, 	0xe6, 	0x42, 	0x68, 	0x41, 	0x99, 	0x2d, 	0x0f, 	0xb0, 	0x54, 	0xbb, 	0x16 }; 

// INVERSE SBOX FROM AES
uint8_t sbox_inverse[SBOXSZ] =
// 	00 	01 	02 	03 	04 	05 	06 	07 	08 	09 	0a 	0b 	0c 	0d 	0e 	0f
/*00*/{ 0x52, 	0x09, 	0x6a, 	0xd5, 	0x30, 	0x36, 	0xa5, 	0x38, 	0xbf, 	0x40, 	0xa3, 	0x9e, 	0x81, 	0xf3, 	0xd7, 	0xfb,
/*10*/ 	0x7c, 	0xe3, 	0x39, 	0x82, 	0x9b, 	0x2f, 	0xff, 	0x87, 	0x34, 	0x8e, 	0x43, 	0x44, 	0xc4, 	0xde, 	0xe9,	0xcb,
/*20*/ 	0x54, 	0x7b, 	0x94, 	0x32, 	0xa6, 	0xc2, 	0x23, 	0x3d, 	0xee, 	0x4c, 	0x95, 	0x0b, 	0x42, 	0xfa, 	0xc3,	0x4e,
/*30*/  0x08, 	0x2e, 	0xa1, 	0x66, 	0x28, 	0xd9, 	0x24, 	0xb2, 	0x76, 	0x5b, 	0xa2, 	0x49, 	0x6d, 	0x8b, 	0xd1,	0x25,
/*40*/ 	0x72, 	0xf8, 	0xf6, 	0x64, 	0x86, 	0x68, 	0x98, 	0x16, 	0xd4, 	0xa4, 	0x5c, 	0xcc, 	0x5d, 	0x65, 	0xb6,	0x92,
/*50*/ 	0x6c, 	0x70, 	0x48, 	0x50, 	0xfd, 	0xed, 	0xb9, 	0xda, 	0x5e, 	0x15, 	0x46, 	0x57, 	0xa7, 	0x8d, 	0x9d,	0x84,
/*60*/ 	0x90, 	0xd8, 	0xab, 	0x00, 	0x8c, 	0xbc, 	0xd3, 	0x0a, 	0xf7, 	0xe4, 	0x58, 	0x05, 	0xb8, 	0xb3, 	0x45,	0x06,
/*70*/ 	0xd0, 	0x2c, 	0x1e, 	0x8f, 	0xca, 	0x3f, 	0x0f, 	0x02, 	0xc1, 	0xaf, 	0xbd, 	0x03, 	0x01, 	0x13, 	0x8a,	0x6b,
/*80*/ 	0x3a, 	0x91, 	0x11, 	0x41, 	0x4f, 	0x67, 	0xdc, 	0xea, 	0x97, 	0xf2, 	0xcf, 	0xce, 	0xf0, 	0xb4, 	0xe6,	0x73,
/*90*/ 	0x96, 	0xac, 	0x74, 	0x22, 	0xe7, 	0xad, 	0x35, 	0x85, 	0xe2, 	0xf9, 	0x37, 	0xe8, 	0x1c, 	0x75, 	0xdf,	0x6e,
/*a0*/ 	0x47, 	0xf1, 	0x1a, 	0x71, 	0x1d, 	0x29, 	0xc5, 	0x89, 	0x6f, 	0xb7, 	0x62, 	0x0e, 	0xaa, 	0x18, 	0xbe,	0x1b,
/*b0*/ 	0xfc, 	0x56, 	0x3e, 	0x4b, 	0xc6, 	0xd2, 	0x79, 	0x20, 	0x9a, 	0xdb, 	0xc0, 	0xfe, 	0x78, 	0xcd, 	0x5a,	0xf4,
/*c0*/ 	0x1f, 	0xdd, 	0xa8, 	0x33, 	0x88, 	0x07, 	0xc7, 	0x31, 	0xb1, 	0x12, 	0x10, 	0x59, 	0x27, 	0x80, 	0xec,	0x5f,
/*d0*/ 	0x60, 	0x51, 	0x7f, 	0xa9, 	0x19, 	0xb5, 	0x4a, 	0x0d, 	0x2d, 	0xe5, 	0x7a, 	0x9f, 	0x93, 	0xc9, 	0x9c,	0xef,
/*e0*/ 	0xa0, 	0xe0, 	0x3b, 	0x4d, 	0xae, 	0x2a, 	0xf5, 	0xb0, 	0xc8, 	0xeb, 	0xbb, 	0x3c, 	0x83, 	0x53, 	0x99,	0x61,
/*f0*/ 	0x17, 	0x2b, 	0x04, 	0x7e, 	0xba, 	0x77, 	0xd6, 	0x26, 	0xe1, 	0x69, 	0x14, 	0x63, 	0x55, 	0x21, 	0x0c,	0x7d };


// MATRIX FROM AES
unsigned long long int mix[MIXERSZ] = { 0x0000000000000002, 0x0000000000000003, 0x0000000000000001, 0x0000000000000001, 
			      		0x0000000000000001, 0x0000000000000002, 0x0000000000000003, 0x0000000000000001, 
			       		0x0000000000000001, 0x0000000000000001, 0x0000000000000002, 0x0000000000000003, 
			       		0x0000000000000003, 0x0000000000000001, 0x0000000000000001, 0x0000000000000002, };
// INVERSE MATRIX FROM AES
unsigned long long int demix[MIXERSZ] = { 0x000000000000000e, 0x000000000000000b, 0x000000000000000d, 0x0000000000000009, 
			         	  0x0000000000000009, 0x000000000000000e, 0x000000000000000b, 0x000000000000000d, 
			         	  0x000000000000000d, 0x0000000000000009, 0x000000000000000e, 0x000000000000000b, 
			         	  0x000000000000000b, 0x000000000000000d, 0x0000000000000009, 0x000000000000000e, };
// References 'mix' values
Matrix* mixptr = NULLPTR;

// ***************** Project Specific Code Here ***************** //
void initmode(char mode) 
{
	if (mode) MODE = ENCRYPT; 
	else 	  MODE = DECRYPT;
}

void initmixer()
{
	if (MODE == ENCRYPT) mixptr =  create_matrix(mix,   ROWSIZE, COLSIZE);
	else		     mixptr =  create_matrix(demix, ROWSIZE, COLSIZE);
}
void freemixer() { FREE(mixptr); }


char sbox_mapval(long long int msgbyte)
{
	register long long int hmsk = 0x00000000000000f0;	// High value mask
	register long long int lmsk = 0x000000000000000f;	// Low  value mask
	register char rval = (char)((msgbyte & hmsk) >> 4);	// Gets row to pull substitution from (e.g. Input = 0x3a, 'rval' = 0x3) 
	register char cval = (char)(msgbyte & lmsk);		// Gets col to pull substitution from (e.g. Input = 0x3a, 'rval' = 0xa) 
	
	if (MODE == ENCRYPT) return sbox[rval * SBOXDIM + cval];
	else 		     return sbox_inverse[rval * SBOXDIM + cval];
}

Matrix* substitutebytes(Matrix* ptr)
{
	register int matrixsz = ptr->numrow * ptr->numcol;
	register int i;
	for (i = 0; i < matrixsz; ++i)
		ptr->matrix[i] = 0x00000000000000ff & sbox_mapval(ptr->matrix[i]);
	return ptr;
}

Matrix* shiftbytes(Matrix* ptr) // If 'MODE' is ENCRYPT, will shift right, else will shift left
{
	register int i;
	for (i = 1; i <= ptr->numrow; ++i)
		replacerow(    i,    rotaterow(row(i, ptr), ROWSIZE, !MODE, i - 1),      ptr,            FREEOLD  );
		    	//   -row-   -------------------replacer-------------------  -msg matrix-   -prevent memleak-
	return ptr;
}


Matrix* mixcolumns(Matrix* ptr)
{
	register unsigned int i;
	for (i = 1; i <= COLSIZE; ++i)		// Starts at 1 and goes to and including 4 because thats how the functions work
		replacecolumn(    i,    matrixbycol( mixptr, column(i, ptr), FREEOLD),      ptr,           FREEOLD  );
		    	   //   -col-   ------------------replacer------------------    -msg matrix- -prevent memleak-
	return ptr;
} // 'replacer' --> column that will replace original column in msg matrix 'm'

#define Nb 4  // Block Size ()
#define MAX_KEY_EXP 256
uint8_t dummy[MAX_KEY_EXP];

// Global AES Cipher Context
struct aes_ctx {
  unsigned int Nk;  // Key Length (32b words)
  unsigned int Nr;  // Number of rounds
  uint8_t schedule[MAX_KEY_EXP];
} ctx;


uint8_t* output = NULLPTR;

int Rcon[256] = {
0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 
0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 
0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 
0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 
0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 
0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 
0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 
0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 
0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 
0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 
0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 
0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 
0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 
0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 
0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 
0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d};
unsigned char * KEY;

unsigned char RKey16bytes[176];

void printout(uint8_t* out, int t)
{
	register int i;
	for (i = 0; i < t; ++i)
		printf("%x\t", out[i]);
	PRINT("");
}
//void printout(uint8_t* out, int t);
void keyexpansion (unsigned char rk[Nb * (ROUNDS+1)], unsigned char *key); // Prototype
int init(const uint8_t *key, const size_t len)
{
	ctx.Nk = len;
	 if (len > 16 && len <= 24)
	{
		ROUNDS = 12;
		Nklen = 6;

	}
  	else if(len > 24 && len <=32)
	{
		ROUNDS = 14;
		Nklen  = 8;
	}
	else
	{
		ROUNDS = 10;
		Nklen = 4;
	}
  // Initialize the global `aes_ctx` struct (ctx)
  //   - Set the Nk, Nr
  //   - Initialize the schedule via key expansion

  KEY = (unsigned char*)(key);
  ctx.Nk = len;
  ctx.Nr = (ctx.Nk == 4) * 10 + (ctx.Nk == 6) * 12 + (ctx.Nk == 8) * 14;
  memset(ctx.schedule, 0, MAX_KEY_EXP);
  keyexpansion(RKey16bytes, KEY);  
  strncpy(ctx.schedule, RKey16bytes, 176);
  return 1;  // Indicates a successful initialization
}
typedef unsigned char state_t[4][4]; //finite field

unsigned int Nround = 10;

void initall(char mode)
{
	initmode(mode);
	initmixer();
}

void cleanall()
{
	freemixer();
}

void rotateleft( unsigned char temp[4]) // rotates the key left
{
  unsigned char temps = temp[0]; // holds value
  temp[0] = temp[1];
  temp[1] = temp[2];
  temp[2] = temp[3];
  temp[3] = temps;
}
void subword (unsigned char temp[4]) //substitute values in the given sbox
{
  temp[0] = sbox[temp[0]];
  temp[1] = sbox[temp[1]];
  temp[2] = sbox[temp[2]];
  temp[3] = sbox[temp[3]];
 
}

void keyexpansion (unsigned char rk[Nb * (ROUNDS+1)], unsigned char *key) //only expanded once
{
  unsigned char temp[4];
  int i = 0;
  for (i = 0; i < Nklen; i++)
  {
    rk[i*4] = key[4*i];
	rk[i*4+1] = key[4*i+1];
	rk[i*4+2] = key[4*i+2];
	rk[i*4+3] = key[4*i+3];
  }

  i = Nklen;
  while (i< (Nb*(ROUNDS+1)))
  {
    
    temp[0] = rk[(i-1)*4];
	temp[1] = rk[(i-1)*4 +1];
	temp[2] = rk[(i-1)*4 +2];
	temp[3] = rk[(i-1)*4 +3];
    if (i % Nklen == 0)
    {
      rotateleft(temp);
      subword(temp);
      temp[0] = temp[0] ^ Rcon[i/Nklen];
    }
    else if (Nklen > 6 && i % Nklen == 4)
    {
      subword(temp);
    }
    rk[i*4] = rk[(i-Nklen) *4] ^ temp[0];
	rk[i*4+1] = rk[(i-Nklen) *4 +1] ^ temp[1];
	rk[i*4+2] = rk[(i-Nklen) *4 +2] ^ temp[2];
	rk[i*4+3] = rk[(i-Nklen) *4 +3] ^ temp[3];
    ++i;
  }
}

 //10 rounds (128b), XOR state and key, no inverse
void addroundkey (int round, char * state, unsigned char* rk) 
{
  char i;
  for (i = 0; i < 16; ++i)
      state[i] ^= rk[round * 16 + i];
}

char* updatestate(Matrix* ptr, char * state)
{
	FREE(state);
	return ( char*)(llitoc_array(ptr->matrix, BLKSIZE, NOFREEOLD, 0));
}

long long int* updatematrix(char * state, Matrix* ptr)
{
	FREE(ptr->matrix);
	return (long long int*)(ctolli_array(state, NOFREEOLD, BLKSIZE));
}

void encrypt (const uint8_t *in, uint8_t *out)
{

	initall(ENCRYPT);
	char* state = NULLPTR;
	Matrix* ptr = create_matrix(ctolli_array((uint8_t*)in, NOFREEOLD, BLKSIZE), ROWSIZE, COLSIZE);
	state = updatestate(ptr, state);

	addroundkey(0, state, RKey16bytes);

	register int i;
	for(i = 1;  i <= ROUNDS-1; ++i)
	{
		ptr->matrix = updatematrix(state, ptr); //////
		substitutebytes(ptr);
	
		invertmatrix(ptr);
		shiftbytes(ptr);
		mixcolumns(ptr);
		invertmatrix(ptr);

		state = updatestate(ptr, state); //////
		addroundkey(i, state, RKey16bytes);
	}
	
	ptr->matrix = updatematrix(state, ptr); //////
	substitutebytes(ptr);

	invertmatrix(ptr);
	shiftbytes(ptr);
	invertmatrix(ptr);

	state = updatestate(ptr, state); //////
	addroundkey(ROUNDS, state, RKey16bytes);

	output = (uint8_t*)state;

	cleanall();
}

void decrypt (const uint8_t *in, uint8_t* out)
{
	initall(DECRYPT);
	char * state = NULLPTR;
	Matrix* ptr = create_matrix(ctolli_array((char*)in, NOFREEOLD, BLKSIZE), ROWSIZE, COLSIZE);
	state = updatestate(ptr, state);
    	
	state = updatestate(ptr, state);		//////
	addroundkey(ROUNDS, state, RKey16bytes);
    	ptr->matrix = updatematrix(state, ptr);		//////

	invertmatrix(ptr);
	shiftbytes(ptr);
	invertmatrix(ptr);

	substitutebytes(ptr);	
	
	register int i;
	for(i = 1;  i <= ROUNDS-1; ++i)
	{
		state = updatestate(ptr, state);
		addroundkey(ROUNDS - i, state, RKey16bytes);
		ptr->matrix = updatematrix(state, ptr);

		invertmatrix(ptr);
		mixcolumns(ptr);
    		shiftbytes(ptr);
		invertmatrix(ptr);

		substitutebytes(ptr);
	}

  	state = updatestate(ptr, state); //////
	addroundkey(0, state, RKey16bytes);

	ptr->matrix = updatematrix(state, ptr); //////
	state = updatestate(ptr, state); //////
	
	output = (uint8_t*)state;

	cleanall();
}

// ***************** Project Specific Code End ***************** //

void printmatrix(Matrix* ptr)
{
	PRINTHEXARRAY(row(1, ptr), 4);
	PRINTHEXARRAY(row(2, ptr), 4);
	PRINTHEXARRAY(row(3, ptr), 4);
	PRINTHEXARRAY(row(4, ptr), 4);
}


int main(int argc, char** argv)
{
	if (argc == 3 && argv[1] && argv[2])
	{
  		char* ttt = argv[1];
		char* xxx = argv[2];
		printf("Key: \t\t");
		printout(ttt, 16);
		printf("Input:\t\t");
		printout(xxx, 16);

		init((const uint8_t*)ttt, 16);
		encrypt((const uint8_t*)xxx, output);
		printf("Encrypted:\t");
		printout(output, 16);

		decrypt((const uint8_t*)output, output);
		printf("Decrypted:\t");
		printout(output, 16);
	}
}

