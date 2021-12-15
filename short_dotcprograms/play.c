#include "../bytes.h"
#include <string.h>
#define i7i7 EXIT(HALT);

     #include <time.h>

#define ARGWANTED 1	// Set for what you need
#define NUMARGS	  2

void check_params(int num) { if (num < NUMARGS) THROW("NOT ENOUGH ARGS"); }	// Checks if correct number of args given

char* check_params_retstr(int num, char** vect)
{
	check_params(num);
	return vect[ARGWANTED];
}

int check_params_retnum(int num, char** vect)
{
	check_params(num);
	return atoi(vect[ARGWANTED]);
}

void programenvironment()
{
	arch();
	stackorient();
}


int main(int argc, char** argv)
{
    programenvironment();
    // Calculate the time taken by fun()
    clock_t t;
    t = clock();

	char mm[1094];
	memset(mm, '9', 1094);
	char hh[1094];
	printf("%c\n", hh[0]);
	nbytesto(hh, mm, 1094);
	nbytesto(hh, mm, 1094);
	nbytesto(hh, mm, 1094);
	nbytesto(hh, mm, 1094);
	nbytesto(hh, mm, 1094);
	nbytesto(hh, mm, 1094);
	printf("%c\n", hh[0]);

    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    printf("Took %f seconds to execute \n", time_taken);
}
