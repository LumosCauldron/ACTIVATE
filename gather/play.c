#include <time.h>
// #include <string.h>
//#include "../stringvector.h"
#include "../functions.h"
//#include "../dir.h"
#include "../crypt.h"
#include "../bytes.h"
#include "../write.h"

#define ARGWANTED 1	// Set for whats needed
#define NUMARGS	  2

void missionwrapper(u8* box)	// Varies from test case to test case [strtovect(Bytes* str, char dlim, char skipfirst, char opt)]
{
	register double input = 0.0;
	register double adder = 1.0;
	register double e     = 2.71828182845905;
	register double pi    = 3.14159265358979;
	register double phi   = 1.61803398874989;
	u8 hit[256];
	register i16 i = 0;
	
	zeroarray(hit, BOXSZ);	// Zero out array
	
	// Create sbox from equation
	while(i < BOXSZ)
	{
		register double first  = tan(pow(sqrt(input), input));
		register double second = pow(e, cos(input));
		register double third  = pow(pi, sin(input));
	
		register double chaos = (first * second) / third;
		register double answer = 128 * sin(chaos) + 128;
		
		u16 candidate = (u16)(ceil(answer));
		if (candidate > BOXSZ - 1)
			goto keepgoing;
		if (!(*(hit + candidate)))
		{
			*(hit + candidate) = 1;
			*(box + i)         = candidate;
			++i;
		}
		
		keepgoing:
		input += adder;
		if (input >= BOXSZ)
		{
			adder /= 10.0;
			input = 0.0;
			input += adder;
		}
	}
	
	// Create inverse of generated sbox
	//for (i = 0; i < BOXSZ; ++i)
	//	BOXINVERSE(*(box + i)) = i;
}

void timer(Mission** mission)
{
    double time_taken;
    clock_t t = clock();
    int argc;
    for (argc = 0; argc < 256; ++argc)
    	missionstart(mission);
    
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds

    printf("\n[+] timer took %f seconds to execute [+]\n", time_taken);
}

// Global

int main(int argc, char** argv)
{
    CALIBRATE();
    Mission* mptr = missionplan(missionwrapper, EMPTYTOOLSET, ZEROTOOLS, NOFREEMISSION);
    //timer(&mptr);
    //missionscruball(&mptr);
    generator();

    DECALIBRATE();
}

// filescanmodule("/", 0, 0, NULLPTR, NULLPTR, NULLPTR, NULLPTR); //(char* start, unsigned int depth, char objecttype, Svect* prunelist, char (*fileop)(Portal*, Bytes**, Bytes**, char), Portal* portal, Bytes* asprefix)


/*  
	FILE* fptr = FOPEN("lol", "r");
	int i;
	int x = 0;
	uint8_t arr[256];
	zeroarray(arr, 256);
	for (i = 0; i < 256; ++i)
	{
		bptr = readword(fptr, 1);
		arr[atoi(bptr->array)] = i;
		free_bytes(&bptr);
	}
	for (i = 0; i < 256; ++i)
	{
			if (arr[i] / 100 > 0)
				printf("%d , ", arr[i]);
			else if (arr[i] / 10 > 0)
				printf("%d  , ", arr[i]);
			else
				printf("%d   , ", arr[i]);
		++x;
		if (x == 16)
		{
			x = 0;
			PLN(1);
		}
	}



    #define NUMBR 2
    volatile unsigned long long int hun = 1000000000;
    register unsigned long long int i = NUMBR;
    register unsigned int long long j = NUMBR;

    Bytes* ptr1 = dynamic_bytes(NULLPTR, hun);

    memset(ptr1->array, 'c', hun);

    Bytes* ptr2 = dynamic_bytes(NULLPTR, hun);

    memset(ptr2->array, 'c', hun);

    clock_t t;
    double time_taken;
    t = clock();
    while (--i)
    	memmove(ptr1->array, ptr2->array, hun);

    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds

    printf("memmove took %f seconds to execute \n", time_taken);

    t = clock();
    while (--j)
    {
    	conquer_nbytesto(ptr2->array, ptr1->array, hun);
	joinall();
    }

    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds

    printf("conquer took %f seconds to execute \n", time_taken);
*/
