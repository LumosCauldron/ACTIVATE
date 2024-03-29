#ifndef DIR_H
#define DIR_H

#ifdef WINCODE
	#include <Fileapi.h>
#endif

#ifdef UNIXCODE
	#include <dirent.h>
	#include <unistd.h>
	#include <sys/stat.h>
#endif
#include "stringvector.h" // Includes basic.h and bytes.h
#include "read.h"	  // Includes basic.h, bytes.h, tools.h, structlist.h
#include "functions.h"	  // Includes basic.h, bytes.h, tools.h

#define FILEOBJECT       4	// EOT - END OF TRANSMISSION character		// Random assigned character values
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
#define NUMFILES(x) 	  ((u64)(x->branch))
#define DIRPATH(x)	  ((char*)(x->line->array + x->line->len + 1))

#define BACKTRACE   1		// For 'trackobject'
#define NOBACKTRACE 0

#define CLOSEDIRECTORY   1	// Specifies whether or not a function closes a file when it is done.
#define NOCLOSEDIRECTORY 0

#define DEFENSEPERMISSIONS   448  // 0o700
#define COMFYPERMISSIONS     502  // 0o766
#define CHAOSPERMISSIONS    4095  // 0o777

#define ALLDONE    21	// For sending files [CAREFUL MANIPULATING THESE]
#define MORETOCOME 22	

#define FREEPATH      1 // For 'pathmaker'
#define NOFREEPATH    0
#define PATHAPPEAR    1
#define PATHDISAPPEAR 0

typedef Elem Portal;

// Globals
u8 objmark[NUM_MARKS] = { RESTRICTEDOBJECT, DIRECTORYOBJECT, FILEOBJECT, SYMBOLICOBJECT, SOCKETOBJECT, 0 };
u8 dirfilemark[3]     = { DIRECTORYOBJECT, FILEOBJECT, 0 };
Elem* dirhdr = NULLPTR;
u32 DIRECTORIESOPEN = 0;

u8 objectis(const char* target)
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

u64 objectsize(const char* target)
{
   struct stat statbuf;
   if (lstat(target, &statbuf) == EMPTY)
	return 0;
  return ((u64)(statbuf.st_size));
}

Bytes* recondir(Bytes* path, DIR* stream, u32 * numfiles, u32 * numdirs, u32 * numrestricted) // Makes chain of marked file/directory names, counts files and directories in opened directory
{
	register u64 dnamelen   = 0;				// Hold directory/filename length
	register u64 totallen   = 0;				// Hold chain length
	register u8 object 	= DIRECTORYOBJECT;		// Hold object type
	Bytes* newchain 	= dynamic_bytes(NULLPTR, 1);	// Initialize bytes
	struct dirent* entry 	= NULLPTR;			// Holds file/directory name

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
	u32  numfiles      = 0;
	u32  numdirs       = 0;
	u32  numrestricted = 0;
	Elem* newdir = NULLPTR;
	DIR*  stream = opendir(pathname->array);
	if (!stream)
		return NULLPTR; 	// THROW("OPENDIR ERROR"); (pathname NOT FREED)
	else				// Else add to list of open directories
	{		
		Bytes* chain = recondir(pathname, stream, &numfiles, &numdirs, &numrestricted);
		register u64 chainsz = chain->len;
		chain = concatbytes(chain, pathname, NULTERMINATOR, FREEFRONT);	// Concatenate object path to end of chain (changes chain->len, corrected in the next statement)
		chain->len = chainsz;	// Reset chain length back to only children files and directories
		newdir = make_elem(&dirhdr, (u64)(stream), ++DIRECTORIESOPEN, numdirs, NOSCRUB, numrestricted, chain, (void*)((u64)numfiles), ADDNODE); 
	}
	return newdir;
}

u32 CLOSEDIR(Elem** dirobj)
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

u32 MKDIR(char* path)	// Makes 3 attempts to create a directory based on the given path
{
	if (mkdir(path, COMFYPERMISSIONS)   != EMPTY)
		return COMFYPERMISSIONS;
	if (mkdir(path, DEFENSEPERMISSIONS) != EMPTY)
		return DEFENSEPERMISSIONS;
	if (mkdir(path, CHAOSPERMISSIONS)   != EMPTY)
		return CHAOSPERMISSIONS;
	return 0;
}

u8 CHDIR(char* path)
{
	goodptr(path, "NULLPTR STREAM GIVEN TO CHDIR", NOFUNC_RETURN);
	if (chdir(path) == EMPTY)
		return 0;
	return 1;
}

u8 RMDIR(char* path)
{
	// 
}

// ** UNDER MAINTENANCE ** //
u8 FAST_CHDIR(char* path)	// Path must be good, better to use always
{
	i32 fd = open(path, O_RDONLY | __O_NOATIME, S_IRUSR | S_IWUSR | S_IXUSR);	 // Try with rwx permissions
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

Bytes* getdir(char** position, u64 bytesleft)		// Changes position that was passed in directly 
{
	goodptr( position, "NULLPTR POSITION GIVEN TO GETDIR", NOFUNC_RETURN);	// Check pointer
	goodptr(*position, "NULLPTR POSITION GIVEN TO GETDIR", NOFUNC_RETURN);	// Check pointer
	if (!bytesleft)	return NULLPTR;
	char* startmark = findchar(DIRECTORYOBJECT, *position, bytesleft);	// Get start of directory name
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

Bytes* getfile(char** position, u64 bytesleft)		// Changes position that was passed in directly 
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

Bytes* getdirorfile(char** position, u64 bytesleft, u8* type)	// Changes position that was passed in directly and sets type found, type must be checked and declared as a variable
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

Bytes* huntobject(Elem** directory, Bytes* file, u8 objecttype, u8 closedirectory)	// Returns file string if found
{
	if (!directory)
		return NULLPTR;
	goodptr(*directory, "NULLPTR DIRECTORY ELEMENT GIVEN TO HUNTOBJECT", NOFUNC_RETURN);
	goodptr(file, "NULLPTR FILE STRING GIVEN TO HUNTOBJECT", NOFUNC_RETURN);
	file = prependctostr(objecttype, file);
	u8 object = 0;
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
Bytes* openhuntclose(Bytes* path, Bytes* filename, u8 objecttype)
{
	Elem* dir = OPENDIR(path);
	Bytes* filefound = huntobject(&dir, filename, objecttype, CLOSEDIRECTORY);
	return filefound;
}

u32 collectalldirs(Elem* dir, Bytes* cwd, Svect* vector, Svect* prunelist)	// Frees 'cwd'
{
	goodptr(dir, "NULLPTR DIRECTORY ELEMENT GIVEN TO COLLECTALLDIRS", NOFUNC_RETURN);	// Check pointer
	if (!goodptr(cwd, "NO ACCESS TO CWD IN COLLECTALLDIRS", FUNC_RETURN))			// Check pointer
		return 0;
	char* position  = DIRCHAIN(dir)->array;							// Holds position in chain of files/directories
	register u64 bytesleft = DIRCHAIN(dir)->len;				// Holds number of bytes left before the end of the chain
	Bytes* dirfound = NULLPTR;								// Holds any directory object found
	register u32  numcollected = 0;
	while(position)										// While not at end of chain
	{	
		if (!(*position))
			break;
		// Get another directory, bytes left continuously updated by moving position (position is changed by getdir)
		dirfound = concatbytes(cwd, getdir(&position, bytesleft - abs((char*)position - DIRCHAIN(dir)->array)), SLASH * (!eqstr(cwd->array, "/")), FREEBACK);
		if (dirfound)
		{
			// If wanting to avoid infinite searching of previous directories and pruned directory paths
			if ((eqstr(dirfound->array + ((dirfound->len - 2) * (dirfound->len > 2)), "..")) || vectcontains(prunelist, dirfound) || eqstr(dirfound->array, "/run"))// || eqstr(dirfound->array, "/proc")) 
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

u32 collectallfiles_toread(Elem* dir, Bytes* cwd, Svect* vector, Svect* largevector)	// Must check large-file vector after (This function frees 'cwd')
{
	goodptr(dir, "NULLPTR DIRECTORY ELEMENT GIVEN TO COLLECTALLFILESTOREAD", NOFUNC_RETURN);  	// Check pointer
	if (!goodptr(cwd, "NO ACCESS TO CWD IN COLLECTALLDIRS", FUNC_RETURN))			 	// Check pointer
		return 0;
	char* position  		   = DIRCHAIN(dir)->array;				 	// Holds position in chain of files/directories
	register u64 bytesleft   = DIRCHAIN(dir)->len;			 	// Holds number of bytes left before the end of the chain
	Bytes* filefound 	   	   = NULLPTR;						 	// Holds any directory object found
	register u32  numcollected = 0;
	while(position)										 	// While not at end of chain
	{	
		if (!(*position))
			break;
		// Get another directory, bytes left continuously updated by moving position (position is changed by getdir)
		filefound = concatbytes(cwd, getfile(&position, bytesleft - abs((char*)position - DIRCHAIN(dir)->array)), SLASH * (!eqstr(cwd->array, "/")), FREEBACK);
		if (filefound)
		{
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

u32 collectallfiles_tochange(Elem* dir, Bytes* cwd, Svect* vector, Svect* prunelist)	// Frees 'cwd'
{
	goodptr(dir, "NULLPTR DIRECTORY ELEMENT GIVEN TO COLLECTALLFILESTOCHANGE", NOFUNC_RETURN);	// Check pointer
	if (!goodptr(cwd, "NO ACCESS TO CWD IN COLLECTALLFILESTOCHANGE", FUNC_RETURN))			// Check pointer
		return 0;
	char* position  	 = DIRCHAIN(dir)->array;	// Holds position in chain of files/directories
	register u64 bytesleft   = DIRCHAIN(dir)->len;		// Holds number of bytes left before the end of the chain
	Bytes* filefound 	 = NULLPTR;			// Holds any directory object found
	register u32  numcollected = 0;
	while(position)						// While not at end of chain
	{	
		if (!(*position))
			break;
		// Get another directory, bytes left continuously updated by moving position (position is changed by getdir)
		filefound = concatbytes(cwd, getfile(&position, bytesleft - abs((char*)position - DIRCHAIN(dir)->array)), SLASH * (!eqstr(cwd->array, "/")), FREEBACK);
		if (filefound)
		{
			vectpush(vector, filefound);	// Collect file path
			++numcollected;
		}
	}
	free_bytes(&cwd);
	return numcollected;
}

void filescanmodule(char* start, u32  depth, u8 objecttype, Svect* prunelist, u8 (*fileop)(Portal*, Bytes**, Bytes**, u8), Portal* portal, Bytes* asprefix) // Returns path
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
	Svect* vector      = vectgrab(NULLPTR, NO_OPTAMT);
	Svect* filevector  = vectgrab(NULLPTR, NO_OPTAMT);
	register u64 xxt = 0;
	Bytes* finalpath;
	// *** ** * SETUP * ** *** //					

	if (!depth)	
		depth = 0xfffffffe;
	++depth; // Calibrate

	register Bytes** vheadinitial  = vector->head;
	register u32  tracker  = 0;
	register u32  numnodes = 0;
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
			collectallfiles_tochange(ptr, dynamic_bytes(DIRPATH(ptr), countuntilnul(DIRPATH(ptr))), filevector, prunelist);
			while(VECTITEMS(filevector))
			{
				printf("%s\n", VECTTOPELEM(filevector)->array);	// file op goes here...
				vectpop(filevector);
			}
				
		}	
							// Gets freed			// Record number of directories opened
		tracker += collectalldirs(ptr, dynamic_bytes(DIRPATH(ptr), countuntilnul(DIRPATH(ptr))), vector, prunelist);
		CLOSEDIR(&ptr);
		if (!numnodes)								// If no more jobs get newset
		{
			numnodes = tracker;						// Assign new set of directories to open
			tracker  = 0;							// Reset tracker
			--depth;							// Go down by one layer
		}
		else
			--numnodes;
		//volatile u64 g = 0;		// DEBUGGING (SETS RATE OF COMPUTATION ARTIFICIALLY)
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

Svect* trackobject(char* start, char* name, u32  depth, u8 objecttype, Svect* prunelist) // Returns path
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
	Svect* vector      = vectgrab(NULLPTR, NO_OPTAMT);
	Svect* pathsfound  = vectgrab(NULLPTR, NO_OPTAMT);
	volatile register u64 xxt = 0;
	// *** ** * SETUP * ** *** //					

	if (!depth)	
		depth = 0xfffffffe;
	++depth; // Calibrate

	register Bytes** vheadinitial = vector->head;
	register u32  tracker  = 0;
	register u32  numnodes = 0;
	Elem* ptr = startdir;
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
		tracker += collectalldirs(ptr, dynamic_bytes(DIRPATH(ptr), countuntilnul(DIRPATH(ptr))), vector, prunelist);
		CLOSEDIR(&ptr);
		if (!numnodes)								// If no more jobs get newset
		{
			numnodes = tracker;						// Assign new set of directories to open
			tracker  = 0;							// Reset tracker
			--depth;							// Go down by one layer
		}
		else
			--numnodes;
		//volatile u64 g = 0;	// DEBUGGING (SETS RATE OF COMPUTATION ARTIFICIALLY)
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

// FREEPATH   	 1
// NOFREEPATH 	 0
// PATHAPPEAR    1 --> Create path
// PATHDISAPPEAR 0 --> Delete path
void pathmaker(Bytes** filepath, u8 pathaction, u8 freepath)
{							   // 'MAKEFROM' option here is imperative 
	Svect* dirvect = strtovect((*filepath), SLASH, SKIPFIRST, MAKEFROM);	// Make vector of strings all pointing to different parts of the large filepath string (one huge string with no nul-terminators incorporated)
	if (!dirvect)
		return;
	Bytes** doneptr;
	Bytes** vptr;
	if (pathaction)	// If 'pathaction' == PATHAPPEAR
	{
		doneptr = VECTBOTTOM(dirvect);
		vptr    = VECTTOP(dirvect);
	}
	else
	{
		doneptr = VECTPREV(VECTTOP(dirvect));	// Goes one element backwards OUTSIDE of 'dirvect' boundary [NEVER DEREFERENCED AND ONLY USED FOR WHILE-LOOP TERMINATION CONDITION EVALUATION]
		vptr    = VECTBOTTOM(dirvect);
	}
		// Initialize vector pointer with first directory name pushed into 'dirvect'
	register char* ptr;  				// On initialization: will point equal-to or 1 byte forward of (*filepath)->array pointer (e.g. either '(*filepath)->array' and 'ptr' --> "firstdirinpath" OR 'filepath->array' --> "/firstdirinpath")
	register char* front = (*filepath)->array;	// Is the equivalent of '(*filepath)->array'
	register u32  vlen;				// Holds length of vector element
	register char  hold;				// Saves character in byte slot that will be nullfied so that it can be put back later
	while (vptr != doneptr)				// Make all directory names and paths except don't make and name a directory from the actual filename at the end of the filepath 
	{						// (e.g. "/home/user/Documents/file.txt" --> Don't make 'file.txt' a directory) [Vector contains all directory names + a filename as the last 'Bytes' object (aka string object)]
		ptr           = VECTELEM(vptr)->array;	// Get bytes array
		vlen  	      = VECTELEM(vptr)->len;	// Get bytes array length
		hold          = *(ptr + vlen);		// Save character in array that will be replaced with a nul-terminator
		*(ptr + vlen) = 0;			// Nul-terminate path to-be-made
		if (pathaction)				// Make/Remove directories in filesystem from current path
		{
			MKDIR(front);
			vptr  = VECTNEXT(vptr);
		}
		else
		{
			RMDIR(front);
			vptr  = VECTPREV(vptr);
		}
		*(ptr + vlen) = hold;			// Restore character that was saved in array
	}
	vectrelease(&dirvect);				// Memory management 101 (frees Svect structure, but elements are not freed)
	if (freepath)
		free_bytes(filepath);			// If desired, filepath is freed
}

#endif // For DIR_H
