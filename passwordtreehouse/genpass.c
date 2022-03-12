#define NULLPTR (void*)(0)

#include <stdio.h>
#include <stdlib.h>

#define BASE  'a'
#define TOP   'z'
#define CCBASE 'A'
#define CCTOP  'Z'
#define LOWER  32
#define UPPER -32

void brutegen(short len) // Magic
{
	char* ptr = calloc(len, 1);
	register short i = 0;
	register short x = 0;
	ptr[i] = BASE;			// Initialize first digit
	while (i < len)
	{
		printf("%s\n", ptr);
		if (*ptr == TOP)	// If reached end of alphabet
		{
			while (ptr[x] == TOP)	// Set all except last digit to first letter in bathroom
				ptr[x++] = BASE;
			if (ptr[x])		// Increment last digit if not at last alphabet character
				ptr[x] += 1;
			else			// If last digit is last character of alphabet, reset
			{
				ptr[x] = BASE;
				++i;
			}
			x = 0;			// Reset count
			continue;
		}
		*ptr += 1;			// Increment first digit
	}
}

void Brutegen(short len) // Magic
{
	char* ptr = calloc(len, 1);
	register short i = 0;
	register short x = 0;
	ptr[i] = CCBASE;			// Initialize first digit
	while (i < len)
	{
		printf("%s\n", ptr);
		if (*ptr == TOP || *ptr == CCTOP)	// If reached end of alphabet
		{
			while (ptr[x] == TOP || ptr[x] == CCTOP) // Set all except last digit to first letter in bathroom
			{
				if (!x) ptr[x++] = CCBASE;
				else	ptr[x++] = BASE;
			}
			if (ptr[x])		// Increment last digit if not at last alphabet character
				ptr[x] += 1;
			else			// If last digit is last character of alphabet, reset
			{
				ptr[x] = BASE;
				++i;
			}
			x = 0;			// Reset count
			continue;
		}
		*ptr += 1;			// Increment first digit
	}
}

void BRUTEGEN(short len) // Magic
{
	char* ptr = calloc(len, 1);
	register short i = 0;
	register short x = 0;
	ptr[i] = CCBASE;			// Initialize first digit
	while (i < len)
	{
		printf("%s\n", ptr);
		if (*ptr == CCTOP)	// If reached end of alphabet
		{
			while (ptr[x] == CCTOP)	// Set all except last digit to first letter in bathroom
				ptr[x++] = CCBASE;
			if (ptr[x])		// Increment last digit if not at last alphabet character
				ptr[x] += 1;
			else			// If last digit is last character of alphabet, reset
			{
				ptr[x] = CCBASE;
				++i;
			}
			x = 0;			// Reset count
			continue;
		}
		*ptr += 1;			// Increment first digit
	}
}

void brutealpha(short len, char* alpha) // Magic
{
	char* ptr = calloc(len, 1);
	register short i = 0;
	while (*(alpha + i))
		++i;
	register short alphaboundary = i - 1;
	i = 0;
	register short a = 0;
	register short b = 0;
	register short x = 0;
	ptr[i] = alpha[0];				// Initialize first digit
	while (i < len)
	{
		printf("%s\n", ptr);
		if (*ptr == alpha[alphaboundary])	// If reached end of alphabet
		{
			while (ptr[x] == alpha[alphaboundary])	// Set all except last digit to first letter in bathroom
				ptr[x++] = alpha[0];
			if (ptr[x])			// Increment last digit if not at last alphabet character
			{
				if (b + 1 == alphaboundary + 1)		// Set b to one value above ptr[x] in last digit
				{
					register short q;
					for (q = 0; q <= alphaboundary; ++q)	 // Guaranteed to find correct index
						if (ptr[x] == alpha[q])
							break;
					b = q;
				}
				ptr[x] = alpha[++b];	// B INCREMENTS TOO FAR BEFORE ALL DIGITS GET A CHANCE
			}
			else				// If last digit is last character of alphabet, reset
			{
				b = 0;
				ptr[x] = alpha[0];
				++i;
			}
			x = 0;				// Reset count
			a = 0;
			continue;
		}
		*ptr = alpha[++a];			// Increment first digit
	}
}

int main(int argc, char** argv)
{
	if (argc == 3)
	{
		if (argv[1][0] == 'c')
			Brutegen(atoi(argv[2]));
		else if (argv[1][0] == 'C')
			BRUTEGEN(atoi(argv[2]));
		else if (argv[1][0] == 'a')
		{
			brutegen(atoi(argv[2]));
			Brutegen(atoi(argv[2]));
			BRUTEGEN(atoi(argv[2]));
		}
		else if (atoi(argv[1]))
			brutegen(atoi(argv[1]));
		else
			printf("USE: ./genpass [cCaA] [alphabet]\n\nc --> First digit is capitalized (Letters only)\nC --> All digits capitalized (Letters only)\na --> Generate lowercase, c, & C\nA --> Generate permutations from supplied alphabet\n");
	}	
	else if (argc == 4 && argv[1][0] == 'A')
			brutealpha(atoi(argv[3]), argv[2]);
	else
		printf("USE: ./genpass [cCaA] [alphabet]\n\nc --> First digit is capitalized (Letters only)\nC --> All digits capitalized (Letters only)\na --> Generate lowercase, c, & C\nA --> Generate permutations from supplied alphabet\n");
}

