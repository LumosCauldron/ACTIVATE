#ifndef STRUCTLIST_H
#define STRUCTLIST_H

#include "tools.h"

// DESIGNATED #DEF RANGE 70 - 80
#define OFFSET 70	// Used if we want to iterate through defines
#define LNUM   71
#define MNUM   72
#define SNUM   73
#define TYPE   74
#define HOLD   75
#define LINE   76
#define BRANCH 77
#define NXT    78
#define PREV   79
#define LINEA  80	// Searches 'node->line->array' instead of 'node->line'

#define NULLPTR (void*)(0)

#define PREVSEARCH 1
#define NXTSEARCH  0

#define PREVDIRECTION 1
#define NXTDIRECTION  0

#define ADDNODE   1	// For 'make_elem'
#define NOADDNODE 0

struct element
{
	long long int 	lnum;
	int           	mnum;
	short         	snum;
	char          	type;
	char          	hold;
	Bytes* 	      	line;
	void*	      	branch;
	struct element* nxt;
	struct element* prev;
};
typedef struct element Elem;
int elemcnt(Elem* hd)
{
	short i = 0;					// Make counter
	while(hd) {  ++i; hd = (Elem*)(hd->nxt);  }	// Count elem's
	return i;					// Return count
}

Elem* push_elem(Elem** hd, Elem* node)
{
	goodptr(node, "NULLPTR 'node' GIVEN TO PUSH Node", NOFUNC_RETURN);
	
	if (*hd)
	{
		(*hd)->prev = node;	// If head not pointing to NULLPTR set earlier block to point back to new block (node)
		node->nxt = *hd;	// Set node nxt to next block if existant
	}
	else
		node->nxt = NULLPTR;	// If no other existing blocks, point to NULLPTR
	node->prev = NULLPTR;		// Set node prev to NULLPTR
	(*hd) = node;			// Set head to new block

	return node;		// Return pointer to new Node
}
Elem* make_elem(Elem** hd, long long int l, int m, short s, char t, char h, Bytes* b, void* o, char add_option)
{
	Elem* nw = MALLOC(sizeof(Elem));	// Make space for new elem
	nw->lnum      = l;			// Fill lnum
	nw->mnum      = m;			// Fill mnum   
	nw->snum      = s;			// Fill snum 
	nw->type      = t;			// Fill type
	nw->hold      = h;			// Fill hold 
	nw->line      = b;			// Fill line
	nw->branch    = o;			// Fill branch
	if (add_option)
		return push_elem(hd, nw);		// Push new elem to stack
	return nw;
}
void free_elem(Elem** node)
{
	(*node)->lnum = 0;			// Zero out lnum
	(*node)->mnum = 0;			// Zero out mnum
	(*node)->snum = 0;			// Zero out snum   
	(*node)->type = 0;			// Zero out type 
	(*node)->hold = 0;			// Zero out hold 
	free_bytes(&((*node)->line));		// Free line and set to NULLPTR
	(*node)->branch = NULLPTR;		// (MUST CLEAN UP 'BRANCH' YOUSELF BEFORE CALLING "free_elem", IF YOU USE BRANCH TO POINT TO SOME OTHER DYNAMIC OBJECT)
	FREE(node);				// Free the node and set to NULLPTR
}

void rm_elem(Elem** hd, Elem** node)		// For removing specific nodes from list
{
		if ((*node)->prev == NULLPTR)
		{
			if ((*node)->nxt)
				(*node)->nxt->prev = NULLPTR;	// Set next block to point to NULLPTR
			(*hd) = (*node)->nxt;			// Update head to point to next block as being the first block
		}
		else if ((*node)->nxt == NULLPTR)
			(*node)->prev->nxt = NULLPTR;		// Set previous block to point to NULLPTR as it is now the tail block
		else
		{
			(*node)->prev->nxt = (*node)->nxt;		// Set previous block to point to next block after 'node'
			(*node)->nxt->prev = (*node)->prev;		// Set next block to point to previous block before 'node'
		}
		free_elem(node);			// Free 'node' memory
}

void pop_elem(Elem** hd)
{
	goodptr(hd,  "NULLPTR ADDRESS OF 'hd' GIVEN TO POP_ELEM", NOFUNC_RETURN);
	if (*hd)
		rm_elem(hd, hd);
}
void free_all(Elem** hd)
{
	Elem* hold_hd = *hd;				// Get first node
	Elem* holder;					// Make holder
	while(hold_hd)
	{ 
		holder = hold_hd;			// Store node
		hold_hd = (Elem*)(hold_hd->nxt);	// Go to next node
		free_elem(&holder); 			// Free the stored node
	}
	*hd = NULLPTR;					// Assign the original head to NULLPTR;
}

void make_into_list(Elem** hd)				// Reverses stack data structure
{
	Elem* list = NULLPTR;
	Elem* hold_hd = *hd;				// Get first node
	while (hold_hd)
	{ 
		Elem* holder = hold_hd;			// Store node
		hold_hd = (Elem*)(hold_hd->nxt);	// Go to next node
		push_elem(at(list), holder);		// Push stored node to list head
	}
	*hd = list;
}

void change_elem(Elem* node, void* q, short v)
{
	switch(v)
	{
		case LNUM   : 	node->lnum        = *((long long int*)(q));   // Set lnum
				break;
		case MNUM   : 	node->mnum        = *((int*)(q));   	     // Set mnum
				break;	
		case SNUM   : 	node->snum        = *((short*)(q)); 	     // Set snum
				break;
		case TYPE   : 	node->type        = *((char*)(q));  	     // Set type
				break;
		case HOLD   : 	node->hold        = *((char*)(q));  	     // Set hold
				break;
		case LINE   : 	node->line        = (Bytes*)(q); 	     // Set line
				break;
		case LINEA  : 	node->line->array = (char*)(q); 	     // Set line
				break;
		case BRANCH : 	node->branch      = q;   	   	     // Set branch
				break;
		case NXT    : 	node->nxt         = q;   	   	     // Set nxt
				break;	
		case PREV   : 	node->nxt         = q;   	   	     // Set nxt
				break;	
	}
}

// PREVDIRECTION 1
// NXTDIRECTION  0
void foreach_elem(Elem** start, int (*ptr)(Elem**), char dir) // Takes function pointer and executes it on every Node of Node list pointed to by given Node header
{
	if (!goodptr( start,  "NULLPTR ADDRESS OF 'start' GIVEN TO FOREACH_ELEM", FUNC_RETURN))
		return;
	if (!goodptr(*start, "NULLPTR 'start' GIVEN TO FOREACH_ELEM"            , FUNC_RETURN))
		return;
	Elem* indexor = *start;
	Elem* passoff = *start;
	int check = 0;
	while(indexor)
	{
		passoff = (Elem*)((((unsigned long long int)passoff->nxt) * (dir == NXTDIRECTION)) + (((unsigned long long int)passoff->prev) * (dir == PREVDIRECTION)));
		check = ptr(&indexor);
		if (check == FUNC_RETURN)
			return;
		indexor = passoff;	// Go to next/previous node saved by 'passoff'
	}
}

// PREVSEARCH 1 
// NXTSEARCH  0 
Elem* find_elem(Elem* hd, void* q, short v, char dir)	// Give list head, object to search for pointed by any pointer, and Elem type to search for (e.g. LNUM, MNUM, BRANCH ...etc)
{
	if (!goodptr(hd, NOMSG, FUNC_RETURN)) 				return NULLPTR;
	if (!goodptr(q, "NULLPTR Q GIVEN TO FIND_ELEM", FUNC_RETURN)) 	return NULLPTR;
	switch(v)
	{			// hd = (Elem*)(hd->nxt * (dir == NXTSEARCH) + hd->prev * (dir == PREVSEARCH)); ==> search along prevs or nxts depending on 'dir'
		case LNUM    :  while(hd)
				{ 
					if (hd->lnum == ((long long int)q))	 return hd;
					hd = (Elem*)((long long int)hd->nxt * (dir == NXTSEARCH) + (long long int)hd->prev * (dir == PREVSEARCH));
				}
				  break;

		case MNUM    :  while(hd)
				{ 
					if (hd->mnum == ((int)q))		 return hd;
					hd = (Elem*)((long long int)hd->nxt * (dir == NXTSEARCH) + (long long int)hd->prev * (dir == PREVSEARCH));
				}
				  break;

		case SNUM    :  while(hd)
				{ 
					if (hd->snum == ((short)q))		 return hd;
					hd = (Elem*)((long long int)hd->nxt * (dir == NXTSEARCH) + (long long int)hd->prev * (dir == PREVSEARCH));
				}
				  break;

		case TYPE    :  while(hd)
				{ 
					if (hd->type == ((char)q))		 return hd;
					hd = (Elem*)((long long int)hd->nxt * (dir == NXTSEARCH) + (long long int)hd->prev * (dir == PREVSEARCH));
				}
				  break;

		case HOLD    :  while(hd)
				{ 
					if (hd->hold == ((char)q))		 return hd;
					hd = (Elem*)((long long int)hd->nxt * (dir == NXTSEARCH) + (long long int)hd->prev * (dir == PREVSEARCH));
				}
				  break;

		case LINE    : 	while(hd)
				{ 
					if (!hd->line) 				 goto thisonesnull;
					if (eqbytes(hd->line, (Bytes*)(q)))	 return hd;
					hd = (Elem*)((long long int)hd->nxt * (dir == NXTSEARCH) + (long long int)hd->prev * (dir == PREVSEARCH));
				}
				  break;
		case LINEA   : 	while(hd)
				{ 
					if (!hd->line) 				 goto thisonesnull;
					if (!hd->line->array) 			 goto thisonesnull;
					if (eqstr(hd->line->array, (char*)(q)))	 return hd;
				    thisonesnull:
					hd = (Elem*)((long long int)hd->nxt * (dir == NXTSEARCH) + (long long int)hd->prev * (dir == PREVSEARCH));
				}
				  break;
		case BRANCH  : 	while(hd)
				{ 
					if (hd->branch == q)			 return hd;
					hd = (Elem*)((long long int)hd->nxt * (dir == NXTSEARCH) + (long long int)hd->prev * (dir == PREVSEARCH));
				}
				  break;
		case NXT    : 	while(hd)
				{ 
					if (hd->nxt == q)			 return hd;
					hd = (Elem*)((long long int)hd->nxt * (dir == NXTSEARCH) + (long long int)hd->prev * (dir == PREVSEARCH));
				}
				  break;
		case PREV    : 	while(hd)
				{ 
					if (hd->prev == q)			 return hd;
					hd = (Elem*)((long long int)hd->nxt * (dir == NXTSEARCH) + (long long int)hd->prev * (dir == PREVSEARCH));
				}
				  break;
	}
	return NULLPTR;
}
void print_elems(Elem* hd) // Debugging feature (can handle NULLPTR values)
{
	short i = 1;
	while(hd)
	{ 
		printf("################### Element %d ################## \n", i); 
		printf("lnum : "); PRINTLLN(hd->lnum);
		printf("mnum : "); PRINTN(hd->mnum);
		printf("snum : "); PRINTN(hd->snum);
		printf("type : "); PRINTN(hd->type);
		printf("hold : "); PRINTC(hd->hold);
		if (!hd->line)
			PRINT("line points to null");
		printf("line : ");
		PRINT(hd->line->array);	// Could be long so commented out until needed for debugging
		printf("path : ");
		PRINT(hd->line->array + hd->line->len + 1);
		printf("branch : "); PRINTX((long long int)hd->branch);
		hd = (Elem*)(hd->nxt);
		++i;
	}
}



#endif // For "STRUCTLIST_H"

