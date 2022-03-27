#include <time.h>
#include "../bytes.h"
//#include <string.h>
#include "../conquer.h"
//#include "../dir.h"


#define ARGWANTED 1	// Set for what you need
#define NUMARGS	  2

void programenvironment()
{
	arch();
	setcores();
}

void timer()
{
    clock_t t;
    double time_taken;
    t = clock();
    
    // Function here
    
    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds

    printf("timer took %f seconds to execute \n", time_taken);
}

// Global
char* a1;
char* a2;
char* a3;
char* a4;


#define NUMBR 2
int main(int argc, char** argv)
{
    programenvironment();
    //int var = 0;
    //printf("%d\n", var);

    volatile unsigned long long int hun = 5000000000;
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
    	conquer_nbytesto(ptr1->array, ptr2->array, hun);

    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds

    printf("memmove took %f seconds to execute \n", time_taken);

    t = clock();
    while (--j)

    {
    	memmove(ptr2->array, ptr1->array, hun);
	joinall();
    }

    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds

    printf("conquer took %f seconds to execute \n", time_taken);

    // filescanmodule("/", 0, 0, NULLPTR, NULLPTR, NULLPTR, NULLPTR); //(char* start, unsigned int depth, char objecttype, Svect* prunelist, char (*fileop)(Portal*, Bytes**, Bytes**, char), Portal* portal, Bytes* asprefix)
}

/*  volatile unsigned long long int hun = 1000000000;
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
