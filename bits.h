#ifndef BITS_H
#define BITS_H

#include "tools.h"

#define B8    0
#define B16   1
#define B24   2
#define B32   3
#define B40   4
#define B48   5
#define B56   6
#define B64   7
#define B72   8
#define B80   9
#define B88   10
#define B96   11
#define B104  12
#define B112  13
#define B120  14
#define B128  15

#define B7    0b10000000
#define B6    0b01000000
#define B5    0b00100000
#define B4    0b00010000
#define B3    0b00001000
#define B2    0b00000100
#define B1    0b00000010
#define B0    0b00000001

#define RIGHT 1	 // For 'rotatebytes'
#define LEFT  0

struct bitblock
{
	char* field;
	short sz;
};

typedef struct bitblock Bitfield;

char bitselect[8] = {B0, B1, B2, B3, B4, B5, B6, B7};	// Outlines of a byte

Bitfield* create_bitfield(short size_bytes, void* item)
{
	Bitfield* newfield = MALLOC(sizeof(Bitfield));
	newfield->field = (char*)(item);
	newfield->sz = size_bytes;
}

char seebit(short bit, Bitfield* bitfield)	// Get value of bit in bitfield
{
	if (bit / 8 >= B128 || bit < 0) return 0;
	if       (bit < 8)	return bitfield->field[B8]   && bitselect[bit % 8];
	else if  (bit < 16)	return bitfield->field[B16]  && bitselect[bit % 8];
	else if  (bit < 32)	return bitfield->field[B32]  && bitselect[bit % 8];
	else if  (bit < 40)	return bitfield->field[B40]  && bitselect[bit % 8];
	else if  (bit < 48)	return bitfield->field[B48]  && bitselect[bit % 8];
	else if  (bit < 56)	return bitfield->field[B56]  && bitselect[bit % 8];
	else if  (bit < 64)	return bitfield->field[B64]  && bitselect[bit % 8];
	else if  (bit < 72)	return bitfield->field[B72]  && bitselect[bit % 8];
	else if  (bit < 80)	return bitfield->field[B80]  && bitselect[bit % 8];
	else if  (bit < 88)	return bitfield->field[B88]  && bitselect[bit % 8];
	else if  (bit < 96)	return bitfield->field[B96]  && bitselect[bit % 8];
	else if  (bit < 104)	return bitfield->field[B104] && bitselect[bit % 8];
	else if  (bit < 112)	return bitfield->field[B112] && bitselect[bit % 8];
	else if  (bit < 120)	return bitfield->field[B120] && bitselect[bit % 8];
	else if  (bit < 128)	return bitfield->field[B128] && bitselect[bit % 8];
	else return -1;
}

char setbit(short bit, Bitfield* bitfield) // Can be used to turn on and off flags (Sign number with B7)
{
	if (bit / 8 >= B128 || bit < 0) return 0;
	if       (bit < 8)	bitfield->field[B8]   ^= bitselect[bit % 8];
	else if  (bit < 16)	bitfield->field[B16]  ^= bitselect[bit % 8];
	else if  (bit < 32)	bitfield->field[B32]  ^= bitselect[bit % 8];
	else if  (bit < 40)	bitfield->field[B40]  ^= bitselect[bit % 8];
	else if  (bit < 48)	bitfield->field[B48]  ^= bitselect[bit % 8];
	else if  (bit < 56)	bitfield->field[B56]  ^= bitselect[bit % 8];
	else if  (bit < 64)	bitfield->field[B64]  ^= bitselect[bit % 8];
	else if  (bit < 72)	bitfield->field[B72]  ^= bitselect[bit % 8];
	else if  (bit < 80)	bitfield->field[B80]  ^= bitselect[bit % 8];
	else if  (bit < 88)	bitfield->field[B88]  ^= bitselect[bit % 8];
	else if  (bit < 96)	bitfield->field[B96]  ^= bitselect[bit % 8];
	else if  (bit < 104)	bitfield->field[B104] ^= bitselect[bit % 8];
	else if  (bit < 112)	bitfield->field[B112] ^= bitselect[bit % 8];
	else if  (bit < 120)	bitfield->field[B120] ^= bitselect[bit % 8];
	else 			bitfield->field[B128] ^= bitselect[bit % 8];
	return 1;
}

char xorbitfields(Bitfield* key, Bitfield* value) // XORS elements of 2 char arrays (returns 0 on failure)
{
	if (key->sz > value->sz) 		// If key too long return
	{
		printf("KEY TOO BIG\n");
		return 0;
	}
	register int i;				// Index		
	for (i = 0; i < key->sz; ++i)
		value->field[i] ^= key->field[i]; // XOR elements together
	return 1;				  // Value has been changed
}

// RIGHT 1
// LEFT	 0
Bitfield* rotatebytes(Bitfield* bytestr, char dir, int num)	// Rotates bytes by "num" shifts in direction "dir"
{
	if (!MOD(num, bytestr->sz)) return bytestr;			// Checks if no work is needed
	num = abs(MOD((-(!dir) * num + num * dir), bytestr->sz));	// Calibrates char array offset
	char* holder = MALLOC(bytestr->sz + 1);				// Makes a bucket
	holder[bytestr->sz] = '\0';					// Nul-terminates
	int i;
	for (i = 0; i < bytestr->sz; ++i)
		holder[MOD((i + num), bytestr->sz)] = bytestr->field[i]; // Fills string with calculated rotation
	bytestr->field = strncpy(bytestr->field, holder, bytestr->sz);	// Copies result to original string
	FREE(&holder);				 			// Deletes bucket
	return bytestr;
}

#endif
