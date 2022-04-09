#include <time.h>
// #include <string.h>
#include "../stringvector.h"
#include "../functions.h"
#include "../dir.h"


#define ARGWANTED 1	// Set for what you need
#define NUMARGS	  2

void missionwrapper(long long int filepathaddr, long long int pathaction, long long int freepath)	// Varies from test case to test case [strtovect(Bytes* str, char dlim, char skipfirst, char opt)]
{
	//PRINTBYTES(*((Bytes**)filepathaddr));
	//printf("\n|||||||||||||||||||||||||||||||||||||||||||||||\n\n");
	pathmaker((Bytes**)filepathaddr, (char)pathaction, (char)freepath);
}

void timer(Mission** mission)
{
    clock_t t;
    double time_taken;
    t = clock();
    
    missionstart(mission);
    
    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds

    printf("\n[+] timer took %f seconds to execute [+]\n", time_taken);
}

// Global

int main(int argc, char** argv)
{
    CALIBRATE();
	char* hardcoded = "hello";
	char* cptr = (char*)((long long int)hardcoded * (argc != 2) + (argc == 2) * (long long int)argv[1]);
	Bytes* bptr = dynamic_bytes(cptr, countuntilnul(cptr));
	Mission* mptr = missionplan(missionwrapper, assign3tools((long long int)(&bptr), PATHDISAPPEAR, FREEPATH), 3, FREEMISSION);
	timer(&mptr);	// Frees 'mptr'
	//free_bytes(&bptr);	// Frees 'bptr'
     DECALIBRATE();
}

// filescanmodule("/", 0, 0, NULLPTR, NULLPTR, NULLPTR, NULLPTR); //(char* start, unsigned int depth, char objecttype, Svect* prunelist, char (*fileop)(Portal*, Bytes**, Bytes**, char), Portal* portal, Bytes* asprefix)


/*  
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
