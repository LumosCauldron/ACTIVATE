#ifndef READ_H
#define READ_H

#include "fcntl.h"
#include "structlist.h"

#define JUMPWHITE	1	  // For 'readuntil' and 'readword'
#define NOJUMPWHITE	0

#define INCLUDEC	1	  // For 'readuntil'
#define NOINCLUDEC	0

#define GONXTLINE	1	  // For 'readwords'
#define NOGONXTLINE	0

#define HORIZONTAL	1	  // For 'readcolumns'
#define VERTICAL	0

#define CLOSEFILE	1	  // For 'print_tofile'
#define NOCLOSEFILE	0

#define STREAM_LIMIT 	1460		// For network streams (netstreams can only receive and handle NETMEMLIMIT + FILEMEMLIMIT bytes at a time
#define NETMEMLIMIT  	100000		// 100kb per network stream
#define FILEMEMLIMIT 	50000		// 50KB per per network stream for left over file

#define MAGICNUMBER	100000000 // For 'readfile_tobuffer'

// ****   Macros   **** //
#define ENDFILE(x)	(x->hold)
#define FILENAME(x)	(x->line->array)
#define FILEOPTIONS(x)	((char*)x->branch)
#define FILENAMELEN(x)	(x->line->len)
#define FILENUM(x)	(x->snum)
#define FILESTREAM(x)	((FILE*)x->lnum)
#define FILE_LIST_HEAD  filehdr

// **** Prototypes **** //
// Nothing yet


// GLOBAL
Elem* filehdr   = NULLPTR;		// Used to hold current file being worked on
int FILESOPEN = 0;
// One element stores 
//	lnum = stream pointer
//	mnum = 0
//	snum = file number opened
//	type = scrub or not to scrub
//	hold = EOF READ -- (CHECKED BY ENDFILE() macros)
//	line = filename and name length
//	branch = (char*) r/w option passed in
//	nxt = nxt file element thats open

FILE* FOPEN(char* file, char* opt)
{
	goodptr(file, "NULLPTR FILE GIVEN TO FOPEN", NOFUNC_RETURN);
	goodptr(opt , "NULLPTR OPT GIVEN TO FOPEN" , NOFUNC_RETURN);
	FILE* nwstrm = NULLPTR;
	nwstrm = fopen(file, opt);
	if (!nwstrm)
		return NULLPTR; //THROW("FOPEN ERROR"); 	// PRINT FILE NOT OPEN	
	else									           // e.g  "myfile.txt" "w+"
		make_elem(at(filehdr), (long long int)(nwstrm), 0, ++FILESOPEN, NOSCRUB, 0, dynamic_bytes(file, countuntilnul(file)), (void*)(opt), ADDNODE); // ELSE ADD TO LIST OF FILES IN USE
	return nwstrm;
}

void FCLOSE(FILE* stream)
{
	if (!stream)	// Check pointer
		return;
	Elem* fileobj = find_elem(filehdr, stream, LNUM, NXTSEARCH);		// Find file object
	fclose(stream);								// Close stream
	if (fileobj) 
		rm_elem(&filehdr, &fileobj);					// Delete from list of open files
	--FILESOPEN;								// Decrement number of files open
}

char FGETC(FILE* stream)
{
	register char hold = fgetc(stream);
	if (feof(stream))							// If end of file, set ENDFILE boolean value in
	{
		Elem* ptr = find_elem(filehdr, stream, LNUM, NXTSEARCH);	// Find file object
		if (!ptr)
			return hold;
		++ENDFILE(ptr);	// macro used					// Set ENDFILE flag in file object
	}
	return hold;
}

long long int FREAD(char** position, long long int numbytes, FILE* stream)	   // Does not place a Nul-terminator anywhere
{
	if (feof(stream))							   // If end of file, set ENDFILE boolean value in
		return 0;
	register long long int bytesread = fread(*position, 1, numbytes, stream);  // Read bytes from FILE stream into array and record amount read
	*position += bytesread;		  					   // Position is updated to just past the last character read into the array
	return bytesread;
}

// **************************************************************** READING STREAMS

char skipwhite(FILE* stream)				// Returns 0 if stream is now at EOF
{
	goodptr(stream, "NULLPTR STREAM GIVEN TO SKIPWHITE", NOFUNC_RETURN);
	Elem* current = find_elem(filehdr, stream, LNUM, NXTSEARCH); // Find file object being worked on
	if (!current)
		THROW("FILE NOT FOUND IN ELEMENT LIST -- SKIPWHITE");
	char hold = FGETC(stream);
	while(iswhitespace(hold) && !ENDFILE(current))	  // Skip all whitespace until non-whitespace character is encountered
		hold = FGETC(stream);
	if (!feof(stream))				  // If EOF return 1, else go back a character to prevent snipping-
		ungetc((int)(hold), stream);		  // -the first character off the newly encountered string in the file
	return (!feof(stream));
}

int ispure(Bytes* word)			// Checks if string is all whitespace and gives back size of string
{
	if (!word)
		return 0;
	if (!word->array)
		return 0;
	register int cnt = word->len;			// Get word length
	register int i = 0;				// Make index
	while (*(word->array + i) && i < cnt)		// While not NUL and less than word length
	{
		if (!iswhitespace(*(word->array + (i++))))	// If not whitespace character word is not pure
			return 0;
	}
	return cnt;					// If pure
}

void pushback(Bytes* str, FILE* stream)		// pushes back an entire word to a file stream.
{
	if (!str)
		return;
	register int num = str->len;				// Get string length
	while (num-- && num > 0)				// While not at beginning of word
		ungetc((int)(*(str->array + num)), stream);	// Push back a character from word to stream
}

Bytes* readuntil(char c, char includc, char skipw, FILE* stream)	      // Returns word upto letter c in stream, "includc" flag will ensure c is included in the returned word
{ 								              // Will skip whitespace if any are found after "c"
	goodptr(stream, "NULLPTR STREAM GIVEN TO READUNTIL", NOFUNC_RETURN);
	Elem* current = find_elem(filehdr, stream, LNUM, NXTSEARCH); // Find file object being worked on
	if (!current)
		THROW("FILE NOT FOUND IN ELEMENT LIST -- READUNTIL");
	register short i = 0;				 	      // Holds size and iteration
	char* newarray = NULLPTR;			  	      // Holds the new word
	register char hold = FGETC(stream);		  	      // Gets a new character
	while(hold != c && !ENDFILE(current))			      // While no-character-that-variable-c-holds or EOF is encountered
	{
		newarray = REALLOC(newarray, ++i);	// Allocates space for the character
		newarray[i - 1] = hold;			// Adds the character
		hold = FGETC(stream);			// Gets a new character
	}
	if (hold == c && includc)			// If stopped at character-that-c-holds and "includc" flag set, add it to newarray
	{
		newarray = REALLOC(newarray, ++i);	// Allocates space for the character
		newarray[i - 1] = hold;			// Adds the character
	}
	Bytes* neword = dynamic_bytes(newarray, i);	// Create byte array class
	FREE(&newarray);				// newarray was copied into byte array class so free it (CAN BE OPTIMIZED)
	if (skipw)
		skipwhite(stream);			// Skip white characters
	return neword;					// Return the new word
}

int checkahead_for(char c, FILE* stream)					    // Checks if a certain whitespace character 'c' comes before any other word or symbols  .
{ 										    // Returns the number of bytes that need to be read to before reading that character. If no 'c', returns 0.
	goodptr(stream, "NULLPTR STREAM GIVEN TO CHECKAHEAD_FOR", NOFUNC_RETURN);
	Elem* current = find_elem(filehdr, stream, LNUM, NXTSEARCH); // Find file object being worked on
	if (!current)
		THROW("FILE NOT FOUND IN ELEMENT LIST -- CHECKAHEAD_FOR");
	register int i = 0;				              // Holds size and iteration
	char* newarray = NULLPTR;			              // Holds the new word
	char hold = FGETC(stream);
	while(hold != c && !ENDFILE(current))			      // While 'c' not found yet and !ENDFILE(current)
	{
		newarray = REALLOC(newarray, ++i);	// Allocates space for the character
		newarray[i - 1] = hold;			// Adds the character
		hold = FGETC(stream);			// Gets a new character
	}
	Bytes* neword = dynamic_bytes(newarray, i);
	pushback(neword, stream);			// Push back already 'read' string to stream
	FREE(&newarray);					// Free memory
	free_bytes(&neword);
	return i;					// Return distance
}

Bytes* readword(FILE* stream, char skipw)		// Returns NULLPTR or Nul-terminated string (will skip white after word)
{
	goodptr(stream, "NULLPTR STREAM GIVEN TO READWORD", NOFUNC_RETURN);
	Elem* current = find_elem(filehdr, stream, LNUM, NXTSEARCH); // Find file object being worked on
	if (!current)
		THROW("FILE NOT FOUND IN ELEMENT LIST -- READWORD");
	register short i = 0;				// Holds size and iteration
	char* newarray = NULLPTR;			// Holds the new word
	skipwhite(stream);				// Skips white spaces before reading a word
	register char hold = FGETC(stream);		// Gets a new character
	while(!iswhitespace(hold) && !ENDFILE(current))	// While no whitespace or EOF is encountered
	{
		newarray = REALLOC(newarray, ++i);	// Allocates space for the character
		newarray[i - 1] = hold;			// Adds the character
		hold = FGETC(stream);			// Gets a new character
	}
	Bytes* neword = dynamic_bytes(newarray, i);	// Create byte array class
	FREE(&newarray);				// newarray was copied into byte array class so free it (CAN BE OPTIMIZED)
	if (skipw)
		skipwhite(stream);			// Skip white characters
	return neword;					// Return the new word
}

long long int readnum(FILE* stream, char skipw)		  // RETURNS LONG LONG INT OR 0
{
	goodptr(stream, "NULLPTR STREAM GIVEN TO READNUM", NOFUNC_RETURN);
	Bytes* holder = readword(stream, skipw);	    // Gets word from file
	register long long int num = atol(holder->array);   // Stores number from word --- 0 if holder is nullptr
	free_bytes(&holder);				    // Frees word from heap to prevent memory leak
	return num;					    // Return number
}

double readflt(FILE* stream, char skipw)		// RETURNS LONG LONG INT OR 0
{
	goodptr(stream, "NULLPTR GIVEN TO READFLT", NOFUNC_RETURN);
	Bytes* holder = readword(stream, skipw);	// Gets word from file
	register double num = atof(holder->array);	// Stores number from word --- 0 if holder is nullptr
	free_bytes(&holder);				// Frees word from heap to prevent memory leak
	return num;					// Return number
}

Bytes* readfile(char* file)	// CLOSES FILE
{ 
	goodptr(file, "NULLPTR FILE GIVEN TO READFILE", NOFUNC_RETURN);
	FILE* stream = FOPEN(file, "r");		   		// Open file
	if (!stream)
		return NULLPTR;
	Elem* current = find_elem(filehdr, stream, LNUM, NXTSEARCH); 	// Find file object being worked on
	register int i = 0;				   		// Holds size and iteration
	if (!current)
		THROW("FILE NOT FOUND IN ELEMENT LIST -- READFILE");
	char* newarray = NULLPTR;			   		// Holds the new word
	register char hold = FGETC(stream);		   		// Gets a new character
	while(!ENDFILE(current))					// While EOF not encountered
	{
		newarray = REALLOC(newarray, ++i);	// Allocates space for the character
		newarray[i - 1] = hold;			// Adds the character
		hold = FGETC(stream);			// Gets a new character
	}
	Bytes* neword = dynamic_bytes(newarray, i);	// Create byte array class
	FREE(&newarray);				// newarray was copied into byte array class so free it (CAN BE OPTIMIZED)
	FCLOSE(stream);
	return neword;
}

long long int read_tobuffer(Bytes* origin, long long int increment_sz, FILE* stream)	// Read whole stream into buffer
{
	if (!stream || !origin || !increment_sz)					// Return if even 1 parameter is NULLPTR or 0
		return 0;
	if (!origin->len)
		origin->array = MALLOC(increment_sz);					// Make space from no allocation
	else
		origin->array = REALLOC(origin->array, origin->len + increment_sz);	// Make more space for incoming files
	char* array = origin->array + origin->len;
	register long long int count         = origin->len;		// Holds origin length
	register long long int originalcount = count;			// Hold original count
	register long long int detect 	     = 0;
	do								// While bytes can be read from stream, read bytes
	{
		detect = FREAD(&array, increment_sz, stream);		// Read file sections into buffer until out of
		count += detect;
		if (detect == increment_sz)				// If out of memory, get more and UPDATE ARRAY (sheesh)
		{
			origin->array = REALLOC(origin->array, count + increment_sz);
			array = origin->array + count;
		}
	}
	while (detect);
	origin->array = REALLOC(origin->array, count);		// Reshape to memory needed
	origin->len   = count;					// Update count
	
	return count - originalcount;				// Return bytes read from stream
}

long long int filecount(char* file)	// CLOSES FILE
{ 
	goodptr(file, "NULLPTR FILE GIVEN TO FILECOUNT", NOFUNC_RETURN);
	FILE* stream = FOPEN(file, "r");		// Open file
	if (!stream)
		return 0;		 	      
	Elem* current = find_elem(filehdr, stream, LNUM, NXTSEARCH); // Find file object being worked on
	if (!current)
		THROW("FILE NOT FOUND IN ELEMENT LIST -- FILECOUNT");
	register long long int cnt = 0;			 	      // Holds size and iteration
	register char hold = FGETC(stream);		  	      // Gets a new character
	while(!ENDFILE(current))				      // While EOF not encountered
	{
		++cnt;
		hold = FGETC(stream);			 	      // Gets a new character
	}
	FCLOSE(stream);
	return cnt;
}


Bytes* readfile_withoutc(char* file, char c)	// CLOSES FILE
{ 
	goodptr(file, "NULLPTR FILE GIVEN TO READFILE_WITHOUTC", NOFUNC_RETURN);
	FILE* stream = FOPEN(file, "r");				// Open file
	if (!stream)
		return NULLPTR;
	Elem* current = find_elem(filehdr, stream, LNUM, NXTSEARCH); 	// Find file object being worked on
	if (!current)
		THROW("FILE NOT FOUND IN ELEMENT LIST -- READFILE_WITHOUTC");
	register int i = 0;						// Holds size and iteration
	char* newarray = NULLPTR;					// Holds the new word
	register char hold = FGETC(stream);				// Gets a new character
	while(!ENDFILE(current))					// While no-character-that-variable-c-holds or EOF is encountered
	{
		if (hold != c)					// If not char specified to be left out
		{
			newarray = REALLOC(newarray, ++i);	// Allocates space for the character
			newarray[i - 1] = hold;			// Adds the character
		}
		hold = FGETC(stream);				// Gets a new character
	}
	Bytes* neword = dynamic_bytes(newarray, i);		// Create byte array class
	FREE(&newarray);					// newarray was copied into byte array class so free it (CAN BE OPTIMIZED)
	FCLOSE(stream);
	return neword;
}

Bytes* readline(FILE* stream) { return readuntil('\n', INCLUDEC, NOJUMPWHITE, stream);  }	// Reads an entire line. File ptr now points to beginning of the next line.

Bytes* readnxt(long long int amt, FILE* stream)	// Reads next "amt" of characters from file --> will close stream if it reaches the end of the file. 	CLOSES FILE IFF END REACHED
{
	goodptr(stream, "NULLPTR STREAM GIVEN TO READNXT", NOFUNC_RETURN);
	Elem* current = find_elem(filehdr, stream, LNUM, NXTSEARCH); // Find file object being worked on
	if (!current)
		THROW("FILE NOT FOUND IN ELEMENT LIST -- READNXT");
	register long long int i = 0;			  	      // Holds size and iteration
	char* newarray = NULLPTR;			  	      // Holds the new word
	register char hold = FGETC(stream);		  	      // Gets a new character
	while(amt-- && !ENDFILE(current))			      // While no whitespace or EOF is encountered
	{
		newarray = REALLOC(newarray, ++i);	// Allocates space for the character
		newarray[i - 1] = hold;			// Adds the character
		hold = FGETC(stream);			// Gets a new character
	}
	ungetc((int)(hold), stream);			// Push last character back onto stream
	Bytes* neword = dynamic_bytes(newarray, i);	// Create byte array class
	FREE(&newarray);					// newarray was copied into byte array class so free it (CAN BE OPTIMIZED)
	if (ENDFILE(current))
		FCLOSE(stream);				// Close stream if done
	return neword;					// Return the new word
}

Bytes* skipreadword(int n, FILE* stream)		// Will skip (n - 1) words and returns the nth word (position dependent). File ptr now at next word
{
	goodptr(stream, "NULLPTR STREAM GIVEN TO SKIPREADWORD", NOFUNC_RETURN);
	register int i;
	for (i = 0; i < n; ++i)
		readword(stream, JUMPWHITE);
	return readword(stream, JUMPWHITE);
}

Bytes* skipreadline(int n, FILE* stream)		// Will skip (n - 1) lines and returns the nth line (position dependent). File ptr now at next line
{
	register int i;
	for (i = 0; i < n; ++i)
		readline(stream);
	return readline(stream);
}

void set_to_nextline(FILE* stream)
{
	Bytes* ptr = readuntil('\n', INCLUDEC, NOJUMPWHITE, stream);
	free_bytes(&ptr);
}

Bytes* readwords(int n, char set_to_next_line, FILE* stream)	// Will return n words as a string and choose whether to move to next string
{
	goodptr(stream, "NULLPTR STREAM GIVEN TO READWORDS", NOFUNC_RETURN);
	Bytes* neword = NULLPTR;
	if (n)
		neword = readword(stream, JUMPWHITE);
	register int i;
	for (i = 1; i < n; ++i)
		neword = concatbytes(neword, readword(stream, JUMPWHITE), ' ', FREEOLD);
	if (set_to_next_line)
		set_to_nextline(stream);
	return neword;
}
		  // LOL 1st time using 3 asterisks
int linelist(char* file, Bytes*** ptr)	// Returns number of strings attached to 'ptr' (each string holding one '\n' terminated line) 	CLOSES FILE
{
	FILE* stream = FOPEN(file, "r");				// Open file
	if (!stream)
		return 0;
	Elem* current = find_elem(filehdr, stream, LNUM, NXTSEARCH); 	// Find file object being worked on
	if (!current)
		THROW("FILE NOT FOUND IN ELEMENT LIST -- LINELIST");
	register int i = 0;						// Index
	Bytes** lines = NULLPTR;					// Unrelated : NUMLINES_EST is my intuition on how many lines will be in a random file (15 for now)
	while(!ENDFILE(current))				
	{
		Bytes** holder = lines;
		holder = REALLOC(lines, (i + 1) * sizeof(Bytes*));
		lines = holder;
		lines[i++] = readline(stream);
	}
	FCLOSE(stream);
	*ptr = lines;						// Set ptr to list of lines
	return i;
}

// HORIZONTAL 1
// VERTICAL   0
Bytes* readcolumn(short col, char dir, char* file) // Returns string of words in the specified column location from each line in file     CLOSES FILE
{
	if (!col)
		THROW("BAD ARG: WOULD HAVE DIVIDED BY ZERO");
	goodptr(file, "NULLPTR FILE GIVEN TO READCOLUMN", NOFUNC_RETURN);
	register int numlines;				// Set column index
	register int i = 0;
	Bytes** lines = NULLPTR;			// Holds line list
	Bytes*  neword = NULLPTR;			// Holds string of columns
	numlines = linelist(file, &lines);		// Holds number of lines in file (READS ENTIRE FILE IN THIS LINE)
	if (!lines)
		printf("FILE : %s --> EMPTY\n", file);
	else
	{
		while (i < numlines)	// For each line, find the word in the correct column and add it to neword string
		{
			Bytes* holder = getword(col, lines[i++], WORD); // i + 1 happens after access
			if (holder)
				neword = concatbytes(neword, holder, ((dir == HORIZONTAL) * ' ' + (dir == VERTICAL) * '\n'), FREEBACK); // Holder is freed in here
		}
	}
	return neword;
}

// **************************************************************** STRING OPERATIONS for file reading

char substr_loc_STREAM(Bytes* str, FILE* stream)	// Points stream to correct location in file, returns '1' if string is found in file, '0' if not 	CLOSES FILE
{
	if (!goodptr(str, "NULL STR TO FIND IN STREAM -- SUBSTR_LOC_STREAM", FUNC_RETURN))
		return 0;
	goodptr(stream, "NULLPTR STREAM GIVEN TO -- SUBSTR_LOC_STREAM", NOFUNC_RETURN);
	Elem* current = find_elem(filehdr, stream, LNUM, NXTSEARCH); // Find file object being worked on
	if (!current)
		THROW("FILE NOT FOUND IN ELEMENT LIST -- SUBSTR_LOC_STREAM");
	register unsigned long long int num = str->len;
	do
	{
		Bytes* holder = readnxt(num, stream);	  // Get set of characters equal in length to string-to-be-found
		if (!eqbytes(str, holder))		  // If not equal, push the word back, free the holder, and move forward one
		{
			pushback(holder, stream);
			FREE(&holder);
			FGETC(stream);
		}
		else
		{
			pushback(holder, stream);	  // Else, push back word and return. 'stream' will be pointed to beginning of word in file
			return 1;
		}
	} while (!ENDFILE(current));			  // While not at end of file
	FCLOSE(stream);					  // Close file if "str" not found
	return 0;
}

// CLOSEFILE
// NOCLOSEFILE
void print_tofile(Bytes* str, FILE* stream, char close)
{
	register unsigned long long int len = str->len;
	unsigned char* ptr = str->array;
	register unsigned long long int i;
	for (i = 0; i < len; ++i)
		fputc(ptr[i], stream);
	if (close)
		FCLOSE(stream);
}

#endif
