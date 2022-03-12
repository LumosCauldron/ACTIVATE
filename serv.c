#include "transfer.h"
#define i7i7 EXIT(HALT);

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

int main()
{
	programenvironment();
	fileserver(7777, 0);
}
