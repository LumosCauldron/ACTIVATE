#ifndef TRANSFER_H
#define TRANSFER_H

#include "netreach_unix.h"
#include "dir.h"
#include "world.h"

#define DIE      0
#define DOWNLOAD 1
#define UPLOAD   2
#define FIND	 3
#define NUM_MODS 4

void die(Bytes* objective, Bytes* client_ip, int* port, char encr);
void download(Bytes* objective, Bytes* client_ip, int* port, char encr);
void upload(Bytes* objective, Bytes* client_ip, int* port, char encr);
void findobj(Bytes* objective, Bytes* client_ip, int* port, char encr);

void (*module[NUM_MODS])(Bytes* mission, Bytes* ip, int* port, char encr) = {die, download, upload, findobj};

void die(Bytes* objective, Bytes* client_ip, int* port, char encr)
{
	inceptcstr(portalize(client_ip->array, (*port)++, INCEIVER, encr), "Server exiting");
	EXIT(HALT);
}
void download(Bytes* objective, Bytes* client_ip, int* port, char encr)
{
	PRINT(objective->array);
	Bytes* target = getword(2, objective, WORD);
	if (target)
	{
		PRINT(target->array);
		inceptfile(portalize(client_ip->array, (*port)++, INCEIVER, encr), target->array);
	}
	free_bytes(&target);
}
void upload(Bytes* objective, Bytes* client_ip, int* port, char encr)
{
	Bytes* target = getword(2, objective, WORD);
	if (target)
		perceptfile(portalize(NULLIPSTR, (*port)++, PERCEIVER, encr), target->array, NULLIPSTR);
	free_bytes(&target);
}
void findobj(Bytes* objective, Bytes* client_ip, int* port, char encr)
{
	Bytes* target   	= getword(2, objective, WORD);	// Hold start point
	Bytes* findname 	= getword(3, objective, WORD);	// Hold name to search for
	Bytes* options1  	= getword(4, objective, WORD);	// Hold depth or options
	Bytes* options2		= NULLPTR;			// Hold options if depth was specified
	Bytes* prune		= NULLPTR;			// Hold prune option "-p"
	Bytes* prunebranch      = NULLPTR;			// Hold filesytem path to prune
	Svect* prunelist	= NULLPTR;			// Hold list of all paths to prune
	register int depth	= 0;				// Holds depth at which to stop searching
	register int objtype	= 0;				// Holds file type
	register int argi       = 4;				// Holds argument incrementer
	if (!target || !findname)				// If bad command
	{
		free_bytes(&target);
		free_bytes(&findname);
		return;
	}
	if (options1)						// Record depth if possible
		depth    = atoi(options1->array);
	if (depth)						// If depth get other options that indicate what file system objects to look for
	{
		options2 = getword(++argi, objective, WORD);	
		if (options2)
		{
			if (eqstr(options2->array, "-f"))
				objtype = FILEOBJECT;
			else if (eqstr(options2->array, "-d"))
				objtype = DIRECTORYOBJECT;
			else
				--argi;
		}
	}
	else
	{
		if (options1)
		{
			if (eqstr(options1->array, "-f"))
				objtype = FILEOBJECT;
			else if (eqstr(options1->array, "-d"))
				objtype = DIRECTORYOBJECT;
			else 
				--argi;
		}
	}
	
	prune = getword(++argi, objective, WORD);
	if (prune)						// If potential prune option detected
	{
		if (eqstr(prune->array, "-p"))
		{
			prunelist = vectgrab(NULLPTR); // Initializes vector
			while (prunebranch = getword(++argi, objective, WORD))	// Store all paths to not search through into a vector of strings
				vectpush(prunelist, prunebranch);
		}
	}

	Svect* solutions = trackobject(target->array, findname->array, depth, objtype, prunelist);	// Search for object and pass vector of pruned paths to find function
	if (solutions != (Svect*)(EMPTY) && solutions)
	{
		if (solutions->numitems)
		{
			Bytes* holder = vecttostr(&solutions, solutions->head, '\n', NXTDIRECTION);
			inceptbytes(portalize(client_ip->array, (*port)++, INCEIVER, encr), &holder); // Holder is freed
		}
		else
			inceptcstr(portalize(client_ip->array, (*port)++, INCEIVER, encr), "No files found.\n");
		
	}
	else if (solutions == (Svect*)(EMPTY))
		inceptcstr(portalize(client_ip->array, (*port)++, INCEIVER, encr), "BAD PATH: Could not set the environment to the specified start path.\n");
	else
		inceptcstr(portalize(client_ip->array, (*port)++, INCEIVER, encr), "No files found. An error probably occurred on the server side. Not sure though.\n");

	free_bytes(&target);		// MEMORY MANAGEMENT 101
	free_bytes(&findname);
	free_bytes(&options1);
	free_bytes(&options2);
	free_bytes(&prune);
	free_bytes(&prunebranch);                                          
}


void directive_die(Bytes* objective, char* ipstr, int* port, char encr)	// Handles "die" command client side
{
	inceptcstr(portalize(ipstr, (*port)++, INCEIVER, encr), objective->array);
	Bytes* holder = perceptbytes(portalize(NULLIPSTR, (*port)++, PERCEIVER, encr), NULLIPSTR);
	if (holder)
		PRINT(holder->array);
	EXIT(HALT);
}
void directive_download(Bytes* objective, char* ipstr, int* port, char encr)	// Handles "download" command client side
{
	Bytes* target = getword(2, objective, WORD);
	if (!target)
	{
		PRINT("Second, Third, and Fourth arguments must be present.");
		free_bytes(&target);
		return;
	}
	Bytes* as     = getword(3, objective, WORD);
	if (as)
	{
		if (!eqstr(as->array, "as"))
		{
			PRINT("Third argument needs to be \"as\".");
			free_bytes(&as);
			free_bytes(&target);
			return;
		}
	}
	else
	{
		PRINT("Third and Fourth arguments need to be present.");
		free_bytes(&target);
		return;
	}
	Bytes* name   = getword(4, objective, WORD);
	if (!name)
	{
		PRINT("Fourth argument needs to be the name of the file to create after downloading the data from the server.");
		free_bytes(&as);
		free_bytes(&target);
		return;
	}

	inceptcstr(portalize(ipstr, (*port)++, INCEIVER, encr), objective->array);
	perceptfile(portalize(NULLIPSTR, (*port)++, PERCEIVER, encr), name->array, NULLIPSTR);
	// Receive file bytes and create file from them, then free bytes in memory

	free_bytes(&name);
	free_bytes(&as);
	free_bytes(&target);
}
void directive_upload(Bytes* objective, char* ipstr, int* port, char encr) 	// Handles "upload" command client side
{
	Bytes* target = getword(2, objective, WORD);
	if (target)
	{
		inceptcstr(portalize(ipstr, (*port)++, INCEIVER, encr), objective->array);
		if (inceptfile(portalize(ipstr, (*port)++, INCEIVER, encr), target->array)) // Send custom filename (path included as name)
			PRINT("File written to path on server.");
		else
			PRINT("File was not written to path on server due to set permissions or a bad file name.");
	}
	free_bytes(&target);
}
void directive_findobj(Bytes* objective, char* ipstr, int* port, char encr)	// Handles "find" command client side
{
	Bytes* start    = getword(2, objective, POINTER);	// Just a pointer, no dynamic memory involved here due to the 'POINTER' parameter
	Bytes* filename = getword(3, objective, POINTER);	// Just a pointer, no dynamic memory involved here due to the 'POINTER' parameter
	if (start && filename)
	{
		inceptcstr(portalize(ipstr, (*port)++, INCEIVER, encr), objective->array);
		Bytes* pathways = perceptbytes(portalize(NULLIPSTR, (*port)++, PERCEIVER, encr), NULLIPSTR);
		if (pathways)
		{
			PRINT("\t\tThe server sent the following data:\n");
			PRINT(pathways->array);
			free_bytes(&pathways);
		}
		return;
	}
	else
		PRINT("Both a start location for the search algorithm and a file name are required in order to find a file.");
}

char determinechoice(char* choicestr)	// Determines user input choice and handles NULLPTRs like a boss [ returns EMPTY (-1) on nothing found ]
{
	if      (eqstr(choicestr, "die"))
		return DIE;
	else if (eqstr(choicestr, "download"))
		return DOWNLOAD;
	else if (eqstr(choicestr, "upload"))
		return UPLOAD;
	else if (eqstr(choicestr, "find"))
		return FIND;
	return EMPTY;
}

void fileclient(char* ipstr, int port, char encr)	// Primitive shell like command handler
{
	void (*directive[NUM_MODS])(Bytes* mission, char* ip, int* port, char encr) = { directive_die, directive_download, directive_upload, directive_findobj };	// Array of functions to handle commands

	while(1)	// Loop forever
	{
		inputlabel: ;
			Bytes* mission     = userstring("\nOptions\n"
								"\n\tdie      --> \"die\""
								"\n\tdownload --> \"download\" [filename]"
								"\n\tupload   --> \"upload\"   [filename]"
								"\n\tfind     --> \"find\" [start directory] [filename/dirname] [depth (optional)] [ -f (for files) | -d (for directories) ]"
								"\n\t                                                                            [ -p [ paths to prune ... ] e.g. '/sys' ]"
								"\n\n--> ");	
								// Output prompt and get user input.

		if (!mission)					// If no string, get input again
		{
			PRINT("Bad null command reinput.");
			goto inputlabel;
		}

		Bytes* action = getword(1, mission, WORD);	// Get first word of command
		char   hold   = EMPTY;

		if (action)
			hold = determinechoice(action->array);	// Determine the action carry out (die, download, upload, find)

		if (hold == EMPTY)				// If bad command, get input again
		{
			PRINT("Bad command reinput.");
			free_bytes(&action);
			free_bytes(&mission);
			goto inputlabel;
		}

		directive[hold](mission, ipstr, &port, encr);	// "Ay Randall...Do the thing." -- Monsters University
		free_bytes(&action);
		free_bytes(&mission);	// Frees user input
	}
}

void fileserver(int port, char encr)		// File server that hands out files like no tomorrow.
{
	Bytes* clientip = NULLPTR;		// To collect sender ip

	while(1)				// Loop forever
	{	
		Bytes* mission = perceptbytes(portalize(NULLIPSTR, port++, PERCEIVER, encr), &clientip); // Get full command
		Bytes* action  = getword(1, mission, WORD);					 	 // Get first word in command
		if (action)
			module[determinechoice(action->array)](mission, clientip, &port, encr);  	 // "Ay Randall...Do the thing." -- Monsters University
		
		free_bytes(&action);		// MEMORY MANAGEMENT 101
		free_bytes(&mission);
		free_bytes(&clientip);
	}
}

#endif

