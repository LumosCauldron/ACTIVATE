#include <time.h>
// #include <string.h>
//#include "../stringvector.h"
#include "../functions.h"
//#include "../dir.h"
#include "../bits.h"
#include "../bytes.h"


#define ARGWANTED 1	// Set for whats needed
#define NUMARGS	  2

#define IMAX_BITS(m) ((m) / ((m) % 255 + 1) / 255 % 255 * 8 + 7 - 86 / ((m) % 255 + 12))
#define RAND_MAX_WIDTH IMAX_BITS(RAND_MAX)
_Static_assert((RAND_MAX & (RAND_MAX + 1u)) == 0, "RAND_MAX not a Mersenne number");

uint64_t rand64(void) 
{
  register uint64_t r = 0;
  register uint8_t i;
  for (i = 0; i < 64; i += RAND_MAX_WIDTH) 
  {
    r <<= RAND_MAX_WIDTH;
    r ^= (unsigned)(rand());
  }
  return r;
}


void missionwrapper()	// Varies from test case to test case [strtovect(Bytes* str, char dlim, char skipfirst, char opt)]
{
	//PRINTBYTES(*((Bytes**)filepathaddr));
	//printf("\n|||||||||||||||||||||||||||||||||||||||||||||||\n\n");
	//pathmaker((Bytes**)filepathaddr, (char)pathaction, (char)freepath);
    uint64_t decree = 0xab;
    uint64_t key  = rand64();
    CLEARBYTE7(key);
    uint64_t data = 0xaabbccddeeff11;
    uint64_t cpy = data;
    uint32_t* ptr32 = (uint32_t*)(&data);
    uint16_t* ptr16 = (uint16_t*)(&data);
    uint8_t*  ptr8  = (uint8_t*)(&data);
    double time_taken;
    clock_t t = clock();
    	printf("%llx\n", data);
    	printbits_debug(data);
	REVERSE64(&data);
	data >>= 8;
	REVERSE32(ptr32);
	REVERSE16(ptr16 + 2);
	printf("%llx\n", data);
	printbits_debug(data);
	REVERSE16(ptr16 + 2);
	REVERSE32(ptr32);
	data <<= 8;
	REVERSE64(&data);
	printf("%llx\n", data);
	printbits_debug(data);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
}

void timer(Mission** mission)
{
    double time_taken;
    clock_t t = clock();
    
    missionstart(mission);
    
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds

    //printf("\n[+] timer took %f seconds to execute [+]\n", time_taken);
}

// Global

int main(int argc, char** argv)
{
    CALIBRATE();
	char* hardcoded = "hello";
	char* cptr = (char*)((long long int)hardcoded * (argc != 2) + (argc == 2) * (long long int)argv[1]);
	Bytes* bptr = dynamic_bytes(cptr, countuntilnul(cptr));
	Mission* mptr = missionplan(missionwrapper, EMPTYTOOLSET, ZEROTOOLS, FREEMISSION);
	timer(&mptr);	        // Frees 'mptr'
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
