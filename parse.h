#include "bytes.h"

u64 parse_ipv4(char* ptr, u64 limit) // Parses out an IPv4 address and returns size of found pattern ('ptr' points directly at beginning of pattern)
{
	if(!goodptr(ptr, "NULLPTR PATTERN START GIVEN TO IPV4 PARSER", FUNC_RETURN))
		return 0;
	char* holdinitialptr = ptr;
	register u64 sizeofpattern  = 0;		// Holds size of pattern found and is what is returned	
	register u8 number = 0;				// Holds the number value of potential IPv4 address part (e.g. "192.168.0.25" ---> number could hold 192, 168, 0, or 25)
	register u8 iteration = 0;			// Holds portion number of IPv4 address being processed (4 portions total [1] 192 [2] 168 [3] 0 [4] 25 )
	
		state_number:
			number = atoi(ptr);							// Get value of part of IPv4 address
			ptr   += ((number / 100 != 0) * 1)  +  ((number / 10 != 0) * 1)  +  1;	// Move pointer over for each digit (up to 3 maximum for IPv4)
			++iteration;								// Set iteration to next portion
			
			if (limit < abs(ptr - holdinitialptr))	// Check that we have not surpassed the given end of string limit
				goto done_fail;
			if (iteration > 3)		   	// If done, return pattern size
				goto done_success;
			
		state_period:
			if (*ptr != 0x2e)	// ASCII character for '.'
				goto done_fail;
			++ptr;			// Move 'ptr' past '.'
			goto state_number;	// Process next portion
	
	done_success:
		sizeofpattern = abs(ptr - holdinitialptr);
	done_fail:
		return sizeofpattern;	// Returns zero if pattern is corrupted or not found
}
