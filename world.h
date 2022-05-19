#include "bytes.h"
	      // esc|opt|color		// OPTIONS 0 -> norm | 1 -> bold | 4 -> underline | 9 -> strike through
#define RED     "\033[0;31m"
#define CYAN    "\033[0;36m"
#define GREEN   "\033[0;32m"
#define BLUE    "\033[0;34m"

#define BLACK   "\033[0;30m"
#define BROWN   "\033[0;33m"
#define MAGENTA "\033[0;35m"
#define GRAY    "\033[0;37m"

#define NOCOLOR "\033[0m"

#define R_UNIT 32

Bytes* userstring(char* prompt)	// Gets user input until '\n' and returns a string
{
	PLN(1);
	if (prompt)
	{
		printf("%s", prompt);
		fflush(stdout);
	}
	char*  input = MALLOC(R_UNIT);		// Will hold input until (not including) '\n'
	register char c = getchar();		// First character input
	register u64 i;		// Will hold number of characters input by user
	for (i = 1; c != '\n'; ++i)		// Until input is ended, collect characters into a string.
	{
		if (!MOD(i, R_UNIT))
			input = REALLOC(input, i + R_UNIT);	// Make space in increments for faster code execution (every 32 bytes)
		*(input + (i - 1)) = c;				// Don't make them lower or upper case manually.
		c = getchar();
	}
	if (i == 1)	// If only the 'NL' character was input, count that as no user input and return NULLPTR
	{
		FREE(&prompt);
		goto done;
	}
	input = REALLOC(input, i + 1);	// Reshape array to correct size + 1 or nul-terminator
	*(input + i) = 0;		// String is nul-terminated
	if (input)			// If any characters were collected return string in Bytes form, Else return NULLPTR
	{
		Bytes* newobject = MALLOC(sizeof(Bytes));
		newobject->array = input;
		newobject->len   = i - 1;
		return newobject;
	}

	done:
		return NULLPTR;
}

void blink(char* msg)	// Assumes Nul-terminated string
{
	while (1)
	{
		u64 j = 0;
		while (++j != 100000000);
		puts(msg);
		fflush(stdout);
		u64 i = 0;
		while (++i != 150000000);
		system("clear");
	}
}
