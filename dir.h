#ifndef DIR_H
#define DIR_H

#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include "stringvector.h" // Includes basic.h and bytes.h
#include "read.h"	  // Includes basic.h, bytes.h, tools.h, structlist.h
#include "functions.h"	  // Includes basic.h, bytes.h, tools.h

#define FILEOBJECT       4	// EOT - END OF TRANSMISSION character
#define DIRECTORYOBJECT  5	// ENQUIRY character
#define RESTRICTEDOBJECT 6	// ACK
#define SYMBOLICOBJECT   21	// NAK
#define SOCKETOBJECT 	 22	// SYN

#define NUM_MARKS 6

#define MAXPATHLEN	 4096
#define ALLOCCONST	 25

#define DIRSTREAM(x)	  ((DIR*)x->lnum)
#define NUMDIRS(x) 	  (x->snum)
#define DIRNUM(x) 	  (x->mnum)
#define FORENSICOPTION(x) (x->type)
#define DIRCHAIN(x) 	  (x->line) // Bytes* pointer
#define NUMFILES(x) 	  ((unsigned long long int)(x->branch))
#define DIRPATH(x)	  ((char*)(x->line->array + x->line->len + 1))

#define SLASH '/'		// For tacking on file names to file paths and concatenating paths

#define BACKTRACE   1		// For 'trackobject'
#define NOBACKTRACE 0

#define CLOSEDIRECTORY   1	// Specifies whether or not a function closes a file when it is done.
#define NOCLOSEDIRECTORY 0

#define DEFENSEPERMISSIONS   448  // 0o700
#define COMFYPERMISSIONS     502  // 0o766
#define CHAOSPERMISSIONS    4095  // 0o777

#define ALLDONE		 21	// For 'constructdir'
#define MORETOCOME	 22	

typedef Elem Portal;

// Globals
char objmark[NUM_MARKS] = { RESTRICTEDOBJECT, DIRECTORYOBJECT, FILEOBJECT, SYMBOLICOBJECT, SOCKETOBJECT, 0 };
char dirfilemark[3]     = { DIRECTORYOBJECT, FILEOBJECT, 0 };
Elem* dirhdr = NULLPTR;
int DIRECTORIESOPEN = 0;

char objectis(const char* target)
{
   struct stat statbuf;
   if (lstat(target, &statbuf) == EMPTY)
	return RESTRICTEDOBJECT;

   /*switch (statbuf.st_mode & S_IFMT)
    {
    case S_IFBLK:  printf("block device\n", target);            break;
    case S_IFCHR:  printf("character device\n", target);        break;
    case S_IFDIR:  printf("directory\n", target);               break;
    case S_IFIFO:  printf("FIFO/pipe\n", target);               break;
    case S_IFLNK:  printf("%s symlink\n", target);              break;
    case S_IFREG:  printf("%s regular file\n", target);         break;
    case S_IFSOCK: printf("socket\n", target);                  break;
    default:       printf("unknown?\n", target);                break;
    }*/

  switch ((statbuf.st_mode & S_IFMT))
  {
   case S_IFLNK	 : return SYMBOLICOBJECT;
   case S_IFSOCK : return SOCKETOBJECT;
   case S_IFREG  : return FILEOBJECT;
   case S_IFDIR  : return DIRECTORYOBJECT;
   default	 : return RESTRICTEDOBJECT;
  }
}

unsigned long long int objectsize(const char* target)
{
   struct stat statbuf;
   if (lstat(target, &statbuf) == EMPTY)
	return 0;
  return ((unsigned long long int)(statbuf.st_size));
}

Bytes* recondir(Bytes* path, DIR* stream, int* numfiles, int* numdirs, int* numrestricted) // Makes chain of marked file/directory names, counts files and directories in opened directory
{
	register unsigned long long int dnamelen = 0;				// Hold directory/filename length
	register unsigned long long int totallen = 0;				// Hold chain length
	register char object 			 = DIRECTORYOBJECT;		// Hold object type
	Bytes* newchain 			 = dynamic_bytes(NULLPTR, 1);	// Initialize bytes
	struct dirent* entry 			 = NULLPTR;			// Holds file/directory name

	while (entry = readdir(stream))						// Do until all files/directory names read
	{	
		if (entry->d_name)
		{
			if (!eqstr(entry->d_name, "."))
			{
				Bytes* entryname = concatbytes(path, dynamic_bytes(entry->d_name, countuntilnul(entry->d_name)), SLASH, FREEBACK);
				object           = objectis(entryname->array);
				*numfiles       += (object == FILEOBJECT);					// Update type counts 
				*numdirs        += (object == DIRECTORYOBJECT);
				*numrestricted  += (object == RESTRICTEDOBJECT);
				
				dnamelen = countuntilnul(entry->d_name);					// Get file/directory name length
				newchain->array = REALLOC(newchain->array, totallen += (dnamelen + 1));		// Get more space for chain to hold new name (updates totallen)
				*(newchain->array + (totallen - (dnamelen + 1))) = object;			// Mark first character of name to be a file or a directory
				nbytesto(newchain->array + (totallen - dnamelen), entry->d_name, dnamelen);	// Append bytes to chain
				free_bytes(&entryname);
			}
		}
	}
	newchain->len = totallen;	// Update length and return bytes
	return newchain;		// Return chain
}

Elem* OPENDIR(Bytes* pathname)		// Will FREE the given pathname
{
	if (!pathname)
		return NULLPTR;
	int numfiles   	  = 0;
	int numdirs       = 0;
	int numrestricted = 0;
	Elem* newdir = NULLPTR;
	DIR*  stream = opendir(pathname->array);
	if (!stream)
		return NULLPTR; 	// THROW("OPENDIR ERROR"); (pathname NOT FREED)
	else				// Else add to list of open directories
	{		
		Bytes* chain = recondir(pathname, stream, &numfiles, &numdirs, &numrestricted);
		register long long int chainsz = chain->len;
		chain = concatbytes(chain, pathname, NULTERMINATOR, FREEFRONT);	// Concatenate object path to end of chain (changes chain->len, corrected in the next statement)
		chain->len = chainsz;	// Reset chain length back to only children files and directories
		newdir = make_elem(&dirhdr, (long long int)(stream), ++DIRECTORIESOPEN, numdirs, NOSCRUB, numrestricted, chain, (void*)((unsigned long long int)numfiles), ADDNODE); 
	}
	return newdir;
}

int CLOSEDIR(Elem** dirobj)
{
	if (!goodptr(*dirobj, "NULLPTR DIROBJ ADDRESS GIVEN TO CLOSEDIR", FUNC_RETURN))	// Check pointers
		return 0; 
	if (!goodptr(*dirobj, "NULLPTR DIROBJ GIVEN TO CLOSEDIR", FUNC_RETURN))	// Check pointers
		return 0; 
	closedir(DIRSTREAM((*dirobj)));						// Close stream
	rm_elem(&dirhdr, dirobj);						// Delete from list of open directories
	--DIRECTORIESOPEN; 							// Decrement number of open directories
	return 1;								// Keeps this function compatible with the 'foreach_elem' function
}

int MKDIR(char* path)	// Makes 3 attempts to create a directory based on the given path
{
	if (mkdir(path, COMFYPERMISSIONS)   != EMPTY)
		return COMFYPERMISSIONS;
	if (mkdir(path, DEFENSEPERMISSIONS) != EMPTY)
		return DEFENSEPERMISSIONS;
	if (mkdir(path, CHAOSPERMISSIONS)   != EMPTY)
		return CHAOSPERMISSIONS;
	return 0;
}

char CHDIR(char* path)
{
	goodptr(path, "NULLPTR STREAM GIVEN TO CHDIR", NOFUNC_RETURN);
	if (chdir(path) == EMPTY)
		return 0;
	return 1;
}

// ** UNDER MAINTENANCE ** //
char FAST_CHDIR(char* path)	// Path must be good, better to use always
{
	int fd = open(path, O_RDONLY | __O_NOATIME, S_IRUSR | S_IWUSR | S_IXUSR);	 // Try with rwx permissions
	if (!fd)
		if (!(fd = open(path, O_RDONLY | __O_NOATIME, S_IRUSR | S_IXUSR))) // Try with rx  permissions
			return 0;
	if (fchdir(fd) == EMPTY)	// Change to directory based on file descriptor
	{
		close(fd);
		return 0;
	}
	close(fd);
	return 1;
}

Bytes* GETCWD()
{
	char* holder = getcwd(NULLPTR, 0);
	if (!holder)
		THROW("NOT ABLE TO GET CURRENT WORKING DIRECTORY PATH");
	Bytes* cwd = MALLOC(sizeof(Bytes));
	cwd->array = holder;
	cwd->len   = countuntilnul(holder);		
	return cwd;
}

void closealldirs()
{
	foreach_elem(&dirhdr, CLOSEDIR, NXTDIRECTION);
}

Bytes* getdir(char** position, long long int bytesleft)				// Changes position that was passed in directly 
{
	goodptr( position, "NULLPTR POSITION GIVEN TO GETDIR", NOFUNC_RETURN);	// Check pointer
	goodptr(*position, "NULLPTR POSITION GIVEN TO GETDIR", NOFUNC_RETURN);	// Check pointer
	if (!bytesleft)	return NULLPTR;
	char* startmark = findchar(DIRECTORYOBJECT, *position, bytesleft);	// Get start of directory name
	if (!startmark)								// If not found return NULLPTR
		return (Bytes*)(*position = NULLPTR);
	char* endmark   = findchars(objmark, startmark + 1, bytesleft - abs(startmark - *position));	// Get end of directory name (points to one byte after name ends)
	if (!endmark)												// If not found return start to end string
	{		
		++startmark;
		Bytes* holder = dynamic_bytes(startmark, countuntilnul(startmark));
		*position = NULLPTR;
		return holder;
	}
	return extractstr(++startmark, (*position = endmark));			// Else return extracted directory name
}

Bytes* getfile(char** position, long long int bytesleft)			// Changes position that was passed in directly 
{
	goodptr( position, "NULLPTR POSITION GIVEN TO GETFILE", NOFUNC_RETURN);	// Check pointer
	goodptr(*position, "NULLPTR POSITION GIVEN TO GETFILE", NOFUNC_RETURN);	// Check pointer
	if (!bytesleft)	return NULLPTR;
	char* startmark = findchar(FILEOBJECT, *position, bytesleft);		// Get start of directory name
	if (!startmark)								// If not found return NULLPTR
		return (Bytes*)(*position = NULLPTR);
	char* endmark   = findchars(objmark, startmark + 1, bytesleft - abs(startmark - *position));	// Get end of directory name (points to one byte after name ends)
	if (!endmark)											// If not found return start to end string
	{		
		++startmark;
		Bytes* holder = dynamic_bytes(startmark, countuntilnul(startmark));
		*position = NULLPTR;
		return holder;
	}
	return extractstr(++startmark, (*position = endmark));			// Else return extracted directory name
}

Bytes* getdirorfile(char** position, long long int bytesleft, char* type)			// Changes position that was passed in directly and sets type found, type must be checked and declared as a variable
{
	goodptr( position, "NULLPTR POSITION GIVEN TO GETDIRORFILE", NOFUNC_RETURN);	// Check pointer
	goodptr(*position, "NULLPTR POSITION GIVEN TO GETDIRORFILE", NOFUNC_RETURN);	// Check pointer
	if (!bytesleft)	return NULLPTR;
	char* startmark = findchars(dirfilemark, *position, bytesleft);		// Get start of directory name
	if (!startmark)								// If not found return NULLPTR
		return (Bytes*)(*position = NULLPTR);
	else
		*type = *startmark;
	char* endmark   = findchars(objmark, startmark + 1, bytesleft - abs(startmark - *position));	// Get end of file/directory name (points to one byte after name ends)
	if (!endmark)											// If not found return start to end string
	{		
		++startmark;
		Bytes* holder = dynamic_bytes(startmark, countuntilnul(startmark));
		*position = NULLPTR;
		return holder;
	}
	return extractstr(++startmark, (*position = endmark));			// Else return extracted directory name
}

Bytes* huntobject(Elem** directory, Bytes* file, char objecttype, char closedirectory)	// Returns file string if found
{
	if (!directory)
		return NULLPTR;
	goodptr(*directory, "NULLPTR DIRECTORY ELEMENT GIVEN TO HUNTOBJECT", NOFUNC_RETURN);
	goodptr(file, "NULLPTR FILE STRING GIVEN TO HUNTOBJECT", NOFUNC_RETURN);
	file = prependctostr(objecttype, file);
	char object = 0;
	char* found = substr_loc(file, DIRCHAIN((*directory)));
	file = unpendleft(file);
	if (closedirectory)
		CLOSEDIR(directory);
	if (found)
		return concatbytes(dynamic_bytes(DIRPATH((*directory)), countuntilnul(DIRPATH((*directory)))), file, SLASH * (!eqstr(DIRPATH((*directory)), "/")), FREEFRONT);
	return NULLPTR;
}

// CLOSEDIRECTORY   1
// NOCLOSEDIRECTORY 0
Bytes* openhuntclose(Bytes* path, Bytes* filename, char objecttype)
{
	Elem* dir = OPENDIR(path);
	Bytes* filefound = huntobject(&dir, filename, objecttype, CLOSEDIRECTORY);
	return filefound;
}

int collectalldirs(Elem* dir, Bytes* cwd, Svect* vector, Svect* prunelist, char backtrace)	// Frees 'cwd'
{
	goodptr(dir, "NULLPTR DIRECTORY ELEMENT GIVEN TO COLLECTALLDIRS", NOFUNC_RETURN);	// Check pointer
	if (!goodptr(cwd, "NO ACCESS TO CWD IN COLLECTALLDIRS", FUNC_RETURN))			// Check pointer
		return 0;
	char* position  = DIRCHAIN(dir)->array;							// Holds position in chain of files/directories
	register long long int bytesleft = DIRCHAIN(dir)->len;					// Holds number of bytes left before the end of the chain
	Bytes* dirfound = NULLPTR;								// Holds any directory object found
	register int numcollected = 0;
	while(position)										// While not at end of chain
	{	
		if (!(*position))
			break;
		// Get another directory, bytes left continuously updated by moving position (position is changed by getdir)
		dirfound = concatbytes(cwd, getdir(&position, bytesleft - abs((char*)position - DIRCHAIN(dir)->array)), SLASH * (!eqstr(cwd->array, "/")), FREEBACK);
		if (dirfound)
		{
			// If wanting to avoid infinite searching of previous directories and pruned directory paths
			if ((!backtrace && eqstr(dirfound->array + ((dirfound->len - 2) * (dirfound->len > 2)), "..")) || vectcontains(prunelist, dirfound) || eqstr(dirfound->array, "/run"))// || eqstr(dirfound->array, "/proc")) 
			{
				free_bytes(&dirfound);
				continue;
			}
			vectpush(vector, dirfound);	// Collect directory path
			++numcollected;
		}
	}
	free_bytes(&cwd);
	return numcollected;
}

int collectallfiles_toread(Elem* dir, Bytes* cwd, Svect* vector, Svect* largevector, char backtrace)	// Must check large-file vector after (This function frees 'cwd')
{
	goodptr(dir, "NULLPTR DIRECTORY ELEMENT GIVEN TO COLLECTALLFILESTOREAD", NOFUNC_RETURN);	// Check pointer
	if (!goodptr(cwd, "NO ACCESS TO CWD IN COLLECTALLDIRS", FUNC_RETURN))			// Check pointer
		return 0;
	char* position  		 = DIRCHAIN(dir)->array;				// Holds position in chain of files/directories
	register long long int bytesleft = DIRCHAIN(dir)->len;					// Holds number of bytes left before the end of the chain
	Bytes* filefound 	   	 = NULLPTR;						// Holds any directory object found
	register int numcollected 	 = 0;
	while(position)										// While not at end of chain
	{	
		if (!(*position))
			break;
		// Get another directory, bytes left continuously updated by moving position (position is changed by getdir)
		filefound = concatbytes(cwd, getfile(&position, bytesleft - abs((char*)position - DIRCHAIN(dir)->array)), SLASH * (!eqstr(cwd->array, "/")), FREEBACK);
		if (filefound)
		{
			// If wanting to avoid infinite searching of previous directories and pruned directory paths
			if ((!backtrace && eqstr(filefound->array + ((filefound->len - 2) * (filefound->len > 2)), "..")))
			{
				free_bytes(&filefound);
				continue;
			}
			if (objectsize(filefound->array) > FILEMEMLIMIT)
			{
				vectpush(largevector, filefound);
				continue;
			}
			vectpush(vector, filefound);	// Collect file path
			++numcollected;
		}
	}
	free_bytes(&cwd);
	return numcollected;
}

int collectallfiles_tochange(Elem* dir, Bytes* cwd, Svect* vector, Svect* prunelist, char backtrace)	// Frees 'cwd'
{
	goodptr(dir, "NULLPTR DIRECTORY ELEMENT GIVEN TO COLLECTALLFILESTOCHANGE", NOFUNC_RETURN);	// Check pointer
	if (!goodptr(cwd, "NO ACCESS TO CWD IN COLLECTALLFILESTOCHANGE", FUNC_RETURN))			// Check pointer
		return 0;
	char* position  		 = DIRCHAIN(dir)->array;				// Holds position in chain of files/directories
	register long long int bytesleft = DIRCHAIN(dir)->len;					// Holds number of bytes left before the end of the chain
	Bytes* filefound 	   	 = NULLPTR;						// Holds any directory object found
	register int numcollected 	 = 0;
	while(position)										// While not at end of chain
	{	
		if (!(*position))
			break;
		// Get another directory, bytes left continuously updated by moving position (position is changed by getdir)
		filefound = concatbytes(cwd, getfile(&position, bytesleft - abs((char*)position - DIRCHAIN(dir)->array)), SLASH * (!eqstr(cwd->array, "/")), FREEBACK);
		if (filefound)
		{
			// If wanting to avoid infinite searching of previous directories and pruned directory paths
			if ((!backtrace && eqstr(filefound->array + ((filefound->len - 2) * (filefound->len > 2)), "..")) || vectcontains(prunelist, filefound))
			{
				free_bytes(&filefound);
				continue;
			}
			vectpush(vector, filefound);	// Collect file path
			++numcollected;
		}
	}
	free_bytes(&cwd);
	return numcollected;
}

void filescanmodule(char* start, unsigned int depth, char objecttype, Svect* prunelist, char (*fileop)(Portal*, Bytes**, Bytes**, char), Portal* portal, Bytes* asprefix) // Returns path
{
	// *** ** * SETUP * ** *** //
	if (!CHDIR(start))
	{
		PRINT("CANT CHANGE TO START PATH -- FILESCANMODULE");
		return;
	}
	Bytes* cwd         = GETCWD();
	if (!goodptr(cwd, "DYNAMIC_BYTES FOR CWD RETURNED NULL -- FILESCANMODULE", FUNC_RETURN))	// Check pointer
		return;
	Elem*  startdir    = OPENDIR(cwd);						// Open directory
	if (!goodptr(startdir, "CANNOT OPEN CWD IN FILESCANMODULE", FUNC_RETURN))	// Check pointer
		return;
	Svect* vector      = vectgrab(NULLPTR);
	Svect* filevector  = vectgrab(NULLPTR);
	register long long int xxt = 0;
	Bytes* finalpath;
	// *** ** * SETUP * ** *** //					

	if (!depth)	
		depth = 0xfffffffe;
	++depth; // Calibrate

	register Bytes** vheadinitial = vector->head;
	register int tracker  = 0;
	register int numnodes = 0;
	register int vecti = 0;
	Elem* ptr = startdir;
	do
	{
		++xxt;				// Counter that holds count for future debugging and ideas, negligible speed difference
		//printvectormeta(vector);	// DEBUGGING ONLY TO SEE ALL VECTOR CONTENTS BEING PROCESSED (IN THIS CASE ALL DIRECTORIES BEING OPENED)
		if (*(vector->vptr))
		{	
/*
			if (asprefix)
				finalpath = concatbytes(asprefix, (*vector->vptr), 0, NOFREEOLD);	// Prefix path + actual path
			else 
				finalpath = *vector->vptr;						// Actual path
			fileop(portal, vector->vptr, &finalpath, NOFREEOLD);				// File operation function
*/
			collectallfiles_tochange(ptr, dynamic_bytes(DIRPATH(ptr), countuntilnul(DIRPATH(ptr))), filevector, prunelist, NOBACKTRACE);
			while(VECTITEMS(filevector))
			{
				printf("%s\n", VECTTOP(filevector)->array);	// file op goes here...
				vectpop(filevector);
			}
				
		}	
							// Gets freed			// Record number of directories opened
		tracker += collectalldirs(ptr, dynamic_bytes(DIRPATH(ptr), countuntilnul(DIRPATH(ptr))), vector, prunelist, NOBACKTRACE);
		CLOSEDIR(&ptr);
		if (!numnodes)								// If no more jobs get newset
		{
			numnodes = tracker;						// Assign new set of directories to open
			tracker  = 0;							// Reset tracker
			--depth;							// Go down by one layer
		}
		else
			--numnodes;
		//volatile int g = 0;		// DEBUGGING (SETS RATE OF COMPUTATION ARTIFICIALLY)
		//while (++g < 1000000);
		while (!(ptr = OPENDIR(*(vector->vptr))))				// Move vptr along until next directory path opens
		{
			if (*(vector->vptr))
				printf("-----> CANT OPEN : %s\n", ((*(vector->vptr))->array));
			if (vector->vptr++ > vector->end)
				goto scandone;
		}
		++vector->vptr;
	} while (((vector->vptr <= vector->end) && depth) || abs(vector->vptr - vheadinitial) == 1);	// Open directories down file system tree from start point until no more open directories exist
								// the object is found, or the specified depth for the search was exhausted
	scandone:
		vectdestruct(&vector);				// Delete every directory path that was added
	printf("Searched through %lld directories.\n", xxt);
	PRINT("----------------------- DONE -----------------------");
}

Svect* trackobject(char* start, char* name, unsigned int depth, char objecttype, Svect* prunelist) // Returns path
{
	// *** ** * SETUP * ** *** //
	if (!CHDIR(start))
		return (Svect*)(EMPTY);
	Bytes* cwd         = GETCWD();
	if (!goodptr(cwd, "DYNAMIC_BYTES FOR CWD RETURNED NULL -- TRACKOBJECT", FUNC_RETURN))	// Check pointer
		return NULLPTR;
	Elem*  startdir    = OPENDIR(cwd);					// Open directory
	if (!goodptr(startdir, "CANNOT OPEN CWD IN TRACKOBJECT", FUNC_RETURN))	// Check pointer
		return NULLPTR;
	Bytes* objectname  = dynamic_bytes(name, countuntilnul(name));		// Make file name into bytes object
	Bytes* find        = NULLPTR;
	Svect* vector      = vectgrab(NULLPTR);
	Svect* pathsfound  = vectgrab(NULLPTR);
	volatile register long long int xxt = 0;
	// *** ** * SETUP * ** *** //					

	if (!depth)	
		depth = 0xfffffffe;
	++depth; // Calibrate

	register Bytes** vheadinitial = vector->head;
	register int tracker  = 0;
	register int numnodes = 0;
	Elem* 	     ptr      = startdir;
	do
	{
		++xxt;				// Counter that holds count for future debugging and ideas, negligible speed difference
		//printvectormeta(vector);	// DEBUGGING ONLY TO SEE ALL VECTOR CONTENTS BEING PROCESSED (IN THIS CASE ALL DIRECTORIES BEING OPENED)
		if (*(vector->vptr))
			PRINT((*(vector->vptr))->array);

		if (objecttype != FILEOBJECT && objecttype != DIRECTORYOBJECT)		// Look for file/directory in current directory and return its full path
		{
			find = huntobject(&ptr, objectname, FILEOBJECT, NOCLOSEDIRECTORY);
			if (!find)
				find = huntobject(&ptr, objectname, DIRECTORYOBJECT, NOCLOSEDIRECTORY);
		}
		else
			find = huntobject(&ptr, objectname, objecttype, NOCLOSEDIRECTORY); 
		
		if (find)
			vectpush(pathsfound, find);	
							// Gets freed			// Record number of directories opened
		tracker += collectalldirs(ptr, dynamic_bytes(DIRPATH(ptr), countuntilnul(DIRPATH(ptr))), vector, prunelist, NOBACKTRACE);
		CLOSEDIR(&ptr);
		if (!numnodes)								// If no more jobs get newset
		{
			numnodes = tracker;						// Assign new set of directories to open
			tracker  = 0;							// Reset tracker
			--depth;							// Go down by one layer
		}
		else
			--numnodes;
		//volatile int g = 0;		// DEBUGGING (SETS RATE OF COMPUTATION ARTIFICIALLY)
		//while (++g < 1000000);
		while (!(ptr = OPENDIR(*(vector->vptr))))				// Move vptr along until next directory path opens
		{
			if (*(vector->vptr))
				printf("-----> CANT OPEN : %s\n", ((*(vector->vptr))->array));
			if (vector->vptr++ > vector->end)
				goto searchdone;
		}
		++vector->vptr;
	} while (((vector->vptr <= vector->end) && depth) || abs(vector->vptr - vheadinitial) == 1);	// Open directories down file system tree from start point until no more open directories exist, 	
								// the object is found, or the specified depth for the search was exhausted
	searchdone:
		vectdestruct(&vector);				// Delete every directory path that was added
		free_bytes(&objectname);
	printf("Searched through %lld directories.\n", xxt);
	PRINT("----------------------- DONE -----------------------");
	
	return pathsfound;
}


/*void makefileready(Bytes** finalstr, Bytes* file)		// Reads in fileobject mark, file name, and file data to finalstr
{
			if (!file)				// Check if good pointer
				return;				// Return otherwise
			FILE* stream = fopen(file->array, "r");	// Open file stream and don't add to the list of open files that program is using ['FOPEN()' does that]
			if (!stream)				// Check if open, else skip
				return;
	// step 1 //	(*finalstr) = appendctostr((*finalstr), FILEOBJECT);  		// Set character marker as FILEOBJECT
	// step 2 //	(*finalstr) = appendstr((*finalstr), file->array, file->len);  	// Set read in file name

	// step 3 //	register unsigned long long int amtsofar = (unsigned long long int)((*finalstr)->len) + 1;   		// Cast as large integer pointer
			(*finalstr)->len                        += sizeof(unsigned long long int) + 1;				// Update finalstr length to go past Nul-terminator and 8-bytes that store file size
	// step 4 //	register unsigned long long int amt_read = read_tobuffer((*finalstr), objectsize(file->array), stream); // Read file stream and update finalstr len
			unsigned long long int* szptr 		 = (unsigned long long int*)((*finalstr)->array + amtsofar);	// Record file size
			*szptr = amt_read;
			// Records number of bytes in 8 bytes before file data (pointed to by sz_embedder)
			
	// step 5 //	(*finalstr) = appendctostr((*finalstr), 0);	 // Append Nul-terminator to string
			fclose(stream);					 // Close file stream
}

void makedirready(Bytes** finalstr, Bytes* dir)		// FREES GIVEN DIRECTORY NAME
{
			if (!dir)							// Check if good pointer
				return;							// Return otherwise
	// step 1 //	(*finalstr) = appendctostr((*finalstr), DIRECTORYOBJECT); 	// Set character marker as DIRECTORYOBJECT
	// step 2 //	(*finalstr) = appendstr((*finalstr), dir->array, dir->len);   	// Read in directory pathname to finalstr
	// step 3 //	(*finalstr) = appendctostr((*finalstr), 0);		    	// Append Nul-terminator to string
}

Bytes* constructdir(Bytes** dirline, char* name, Bytes* topdir, char freeold)	// Takes line of data and constructs directory and file structures, updates topdir
{
	register int  ncount = 0;
	register char skip   = 0;
	Bytes*        caster = NULLPTR;		// Casted to Bytes object to input length and array
	if (!dirline)
		return topdir;	// If no pointer to data, return
	if (!(*dirline))
		return topdir;  // If no more data, return
	char* ptr = (*dirline)->array + (FIRSTCHAR(*dirline) == MORETOCOME || FIRSTCHAR(*dirline) == ALLDONE);	// +1 if a CONNECTION MARKER is present
	if (topdir)
		goto state_directory;
	else if (!name)
		THROW("NO NAME GIVEN -- CONSTRUCTDIR");

	initialize: ;				// Creates initial directory
		Bytes* cwd    = GETCWD();
		       topdir = concatbytes(cwd, dynamic_bytes(name, countuntilnul(name)), SLASH, FREEOLD);
		if (!MKDIR(topdir->array))
		{
			PRINT("DIRECTORY CONSTRUCTION FAILED -- CONSTRUCTDIR STATE: INITIALIZE");
			return topdir;
		}

	state_directory: ;			// Gets name, creates directory, moves pointer to file name, if no directory name, moves to file state
		if (*(ptr++) != DIRECTORYOBJECT)
		{
			--ptr;
			goto state_file;
		}
		ncount = countuntilnul(ptr);
		appendctostr(topdir, SLASH);
		if (!MKDIR((appendstr(topdir, ptr, ncount))->array))	// printf("-----> CANT MKDIR : %s\n", ptr);
		{
			PRINT("DIRECTORY CONSTRUCTION FAILED -- CONSTRUCTDIR STATE: STATE_DIRECTORY");
			return topdir;
		}
		ptr += ncount + 1;
		movewhilenul(ptr); // Should definitely hit a \x04 or \x05 byte, otherwise something is wrong with line structure
		if (abs(ptr - (*dirline)->array) >= (*dirline)->len)
			goto done;
		
	state_file: ;				// Constructs received file based on prefixed size
		if (*ptr == DIRECTORYOBJECT)
			goto state_directory;
		if (*(ptr++) != FILEOBJECT)
		{
			PRINT("BAD LINE STRUCTURE -- FILE MARKER NOT FOUND");
			return topdir;
		}
		ncount = countuntilnul(ptr);
		printf("Writing file: %s in directory %s\n", ptr, topdir->array); // For debugging purposes (make sure topdir array is nul-terminated)
		FILE* stream = fopen(ptr, "w+");
		ptr += ncount + 1;
		caster = (Bytes*)(ptr);		// Caster now points to length and content of the file
		if (!stream)
		{
			printf("Could not create file %s during construction...skipping this file.\n", ptr - (ncount + 1));
			goto fstreamdone;
		}
		FWRITE(caster->array, caster->len, stream);
		fclose(stream);
	fstreamdone:
		ptr += caster->len + sizeof(unsigned long long int);
		movewhilenul(ptr); // Should definitely hit a \x04 or \x05 hex-value byte, otherwise something is wrong with line structure
		goto state_directory;
		
	checkdone:				// Checks if done
		if (abs((unsigned long long int)ptr - (*dirline)->len) < (unsigned long long int)(*dirline)->array)
			goto state_directory;
	
	done:					// Cleans up
		if (freeold)
			free_bytes(dirline);
	return topdir;
}*/

#endif // For DIR_H
