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


void missionwrapper(long long int revoff)	// Varies from test case to test case [strtovect(Bytes* str, char dlim, char skipfirst, char opt)]
{
	//PRINTBYTES(*((Bytes**)filepathaddr));
	//printf("\n|||||||||||||||||||||||||||||||||||||||||||||||\n\n");
	//pathmaker((Bytes**)filepathaddr, (char)pathaction, (char)freepath);
    double time_taken; clock_t t = clock();
    uint64_t decree = 0xab;
    uint64_t key  = rand64();
    key  = rand64();
    key  = rand64();
    key  = CLEARBYTE7(rand64());
    unsigned long long int x = 0;
    unsigned long long int y = 0;
    unsigned long long int max = 0;
    unsigned long long int maxrds = 0;
    unsigned long long int maxrev = revoff;
    uint64_t data = 0x7632abe5f2a3f1;
    uint64_t cpy = data;
    uint32_t* ptr32 = (uint32_t*)(&data);
    uint16_t* ptr16 = (uint16_t*)(&data);
    uint8_t*  ptr8  = (uint8_t*)(&data);
    PRINTLLX(cpy);
    while (--revoff > 0)
    {
    while(y < 64)
    {
    while (++x)
    {

	//if (x % check != 0)
	//ROTATELEFT_32BIT(data, y);
	//else
	data = ROTATERIGHT_56BIT(data, revoff);
	*ptr8 = REVERSE8(ptr8);
	*(ptr8 + 1) = REVERSE8(ptr8 + 1);
	*(ptr8 + 3) = REVERSE8(ptr8 + 3);
	if (cpy == data || !data)
	{
		if (maxrds <= x)
		{
			printf("MAX -------------------------------------------> %llu | %llu\n", y, x);
			max    = y;
			if (x != maxrds)
				maxrds = x;
			maxrev = revoff;
		}
		PRINTLLX(data);
		break;
	}
	//printbits_debug(data);
	//REVERSE16(ptr16 + 2);
	//REVERSE32(ptr32);
	//REVERSE64(&data);
	
	//printbits_debug(data);
    }
    x = 0;
    ++y;
    }
    y = x = 0;
    }
    PLN(1);
    PRINTLLX(cpy);
    printf("%llu revoff, %llu bits with %llu rounds\n", maxrev, max, maxrds);
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
	//Mission* mptr = missionplan(missionwrapper, assign1tool(atoi(argv[1])), 1, FREEMISSION);
	//timer(&mptr);	        // Frees 'mptr'
	free_bytes(&bptr);	// Frees 'bptr'
	u64 data = 0x00ffaabbddeecc17;
	register u64 cpy = data;
	u8* ptr8 = (u8*)(&data);
	PRINTLLX(data);
	register u8 i;
	register u64 x = 0;
	register u64 y = 0;
	while (1)
	{
		for (i = 0; i < 1; ++i)
		{
			//*(ptr8 + i) = TRANSPOSE(*(ptr8 + i));
			//*(ptr8 + i) = SEAL(*(ptr8 + i));
			*(ptr8 + i) = DARKNESS(*(ptr8 + i));
		}
		++x;
		
		if (*(ptr8 + 0) == 0x17)
			break;
		if (x % 1000 == y)
			PRINTLLX(data);
	}
	/*for (i = 0; i < 7; ++i)
	{
		*(ptr8 + i) = LIGHT(*(ptr8 + i));
		*(ptr8 + i) = UNSEAL(*(ptr8 + i));
		*(ptr8 + i) = TRANSLATE(*(ptr8 + i));
	}*/			
	PRINTLLX(data);
	PRINTLLN(x);

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
