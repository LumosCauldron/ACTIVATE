#ifndef MATRIX_H
#define MATRIX_H

#include "bits.h"

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

void destroy_matrix(Matrix* ptr)	// Zeros out everything and frees the memory
{
	if (!ptr)
		return;
	register int i;
	register int sz = ptr->numcol * ptr->numrow;
	for (i = 0; i < sz; ++i)
		ptr->matrix[i] = 0;
	ptr->numcol = 0;
	ptr->numrow = 0;
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

void replacecolumn(unsigned int col, long long int* replacer, Matrix* ptr)
{
	if (--col >= ptr->numcol)		// Checks for out of range (The --col is to calibrate "col" for the for loop while checking for out of range at the same time)
		THROW("COLUMN SPECIFIED NONEXISTANT");
	register unsigned int i;
	for (i = 0; i < ptr->numrow; ++i)
		ptr->matrix[col + (ptr->numcol * i)] = replacer[i];		// Get column from matrix
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

void replacerow(unsigned int rw, long long int* replacer, Matrix* ptr)
{
	if (--rw >= ptr->numrow)	// Checks if out of range (The --rw is to calibrate "rw" for the for loop while checking for out of range at the same time)
		THROW("ROW SPECIFIED NONEXISTANT");
	register unsigned int i;
	for (i = 0; i < ptr->numcol; ++i)
		ptr->matrix[i + (ptr->numcol * rw)] = replacer[i];		  // Get row from matrix
}


// ********************* OPERATIONS ********************* //

char bytemult(char first, char arrval)	// Executes Galois Field Multiplication [Only applicable to AES]
{
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
	{
		return (first ^ bytemult(first, 2));
	}	
	else
		THROW("ARRAY VALUE ERROR: only 0x01, 0x02, and 0x03 allowed");
	return 0; // Unreachable
}

char bytesubadd(char first, char second) { return first ^ second; }


long long int rowbycol(long long int* row, long long int* col, int sz)	// Multiplies row by column and returns a value, BOTH MUST HOLD THE SAME ARRAY LENGTH
{
	long long int val = 0;		// Value to hold operation result
	register unsigned int i;	
	for (i = 0; i < sz; ++i)	// For every row/column element value add result to final value
		val += row[i] * col[i];
	return val;
}

long long int* matrixbycol(Matrix* ptr, long long int* COLUMN)		// Returns a column
{
	long long int* NEWCOLUMN = MALLOC(sizeof(long long int) * ptr->numrow);	// Get space for new column
	register unsigned int i;	
	for (i = 0; i < ptr->numrow; ++i)	// For every row get ith 'row' and multiply by column, each are of size 'numrow'
		NEWCOLUMN[i] = rowbycol(row(i, ptr), COLUMN, ptr->numcol);
	return NEWCOLUMN;	// Return new column values in the form of a column
}

#endif

