#include "../read.h"
#include <sys/ptrace.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
	goto testing;
	if (argc < 2)
		return 1;
	
	int pid = atoi(argv[1]);
	if (!pid)
		return 1;
testing:
	;
	char* holder = MALLOC(10);
	
	char* core = holder - 1;
	int x;
	for (x = 0; x < 64; ++x)
	{
		//*(holder - x)      = 2;
		*(holder + x + 10) = 0;
		//PRINTN(x);
	}
	free(holder);
	char* news = MALLOC(40);
	
	for (x = 0; x < 64; ++x)
	{
		PRINTN((int)(*(news + x)));
	}

	EXIT(HALT);
	long long int res = ptrace(PTRACE_ATTACH, pid, (void*)(0), (void*)(0));
	wait((void*)(0));
	PRINTLLN(res);
}

