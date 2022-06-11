#ifndef NETREACH_UNIX_H
#define NETREACH_UNIX_H

// WHEN EVER A 'NO' OR 'NO_' IS PREFIXED TO A DEFINITION ---> IT MEANS 'DONT DO SAID-ACTION'

#ifdef _WIN32
	#include <winsock2.h>
	#include <ws2tcpip.h>
	#pragma comment(lib, "Ws2_32.lib")
#else
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <unistd.h>
	#include <netinet/in.h>
	#include <arpa/inet.h> 
	#include <linux/if.h>
	#include <ifaddrs.h>
	#include <sys/ioctl.h>
#endif

#include "write.h"
#include "dir.h"

#include <errno.h>

#define TCP        	 0		
#define UDP        	 1		
#define SCTP      	 2

#define IP4ADDRLEN 	4
#define IP4STRLEN 	15
#define IP6ADDRLEN 	16
#define IP6STRLEN 	39
#define MACADDRLEN  	6

#define STRING		1
#define RAW		0

#define IPV4		4
#define IPV6		6

#define PORT      	 7777
#define LOCALHOST      	"127.0.0.1"

#define TRIES	  	 100000

#define BAD_REQUEST     "BAD REQUEST"
#define BAD_REQUEST_LEN  11

#define PORTAL  	 1
#define HOME    	 0		

#define CLEARBUFFER      1	// For 'READ'
#define NOCLEARBUFFER    0

#define ENCRYPT   	 1	// For 'portalize'
#define NOENCRYPT 	 0

#define EXPECTED_CLIENTS 1

#define NETWORK_NUMSZ    8

#define ALLDONE		 21
#define MORETOCOME	 22

#define INCEIVER	 1
#define PERCEIVER	 0

#define NO_OFFSET	 0

#define BADSOCKOPT   	-7

#define NULLIPSTR	(void*)(0)

// ********************************************************** Socket Operations

// ****  Macros  **** //
#define PORTALTUNNEL(x)	 	(x->mnum)
#define PORTALNUM(x)	 	(x->snum)
#define PORTALTYPE(x)	 	(x->type)
#define PORTALENCRYPTED(x)	(x->hold)
#define PORTALBUFFER(x)  	(x->line)
#define PORTALBOX(x) 	 	((struct sockaddr*)x->branch)
#define PORTALBOXFULL(x) 	((struct sockaddr_in*)x->branch)
#define PORTAL_LIST_HEAD 	portalhdr
#define PORTAL_ALLOCATION(x)	(x->lnum)
#define ADDRLEN		 	sizeof(struct sockaddr)


// **** GLOBAL **** //

// Type 'Elem' is typdef'ed to 'Portal' in "dir.h"

Portal* portalhdr   = NULLPTR; // Used to hold current file being worked on
u16 PORTALSOPEN     = 0;
// One Portal stores 
//	lnum   = allocated space for buffer
//	mnum   = tunnel
//	snum   = portal number opened
//	type   = TCP, UDP, SCTP
//	hold   = whether or not connection is ENCRYPTED with 'encrypt7' algorithm
//	line   = buffer
//	branch = struct sockaddr_in* ptr (connection settings)
//	nxt    = nxt portal element thats open

// ******************************** Prototypes ****************************************** //
Portal* portalize(char* ipstr, char* iface_ipstr, u32 port, u8 role, u8 encryptflag);     // 
											  //
i64  perceptnum(Portal* portal);		 				  	  //
Bytes* perceptbytes(Portal* portal, u64  limit);			 	          //
u8 perceptfile(Portal* portal); 							  //
//u8 perceptdir(Portal* portal);					 		  //
											  //
u8 inceptnum(Portal* portal, i64  object);			 		  	  //
u8 inceptcstr(Portal* portal, char* object);			 			  //
u8 inceptbytes(Portal* portal, Bytes** object);					  //
u8 inceptfile(Portal* portal, char* object, char* as);				  //
//u8 inceptdir(Portal* portal, char* object);						  //
// ******************************** Prototypes ****************************************** //

Bytes* extractforeignip(Portal* portal)	// Returns dynamically allocated ip address string of connected party
{
	Bytes* ipstr = dynamic_bytes(NULLPTR, INET_ADDRSTRLEN);
	inet_ntop(AF_INET, &(PORTALBOXFULL(portal)->sin_addr), ipstr->array, INET_ADDRSTRLEN);
	return ipstr;
}

Bytes* getmac(char* interface)	// Returns dynamic object of MAC address values (not string)
{
    struct ifreq s;
    int fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);

    nbytesto(s.ifr_name, interface, countuntilnul(interface));
    if (!(ioctl(fd, SIOCGIFHWADDR, &s)))
        return dynamic_bytes(s.ifr_addr.sa_data, 6);
    close(fd);
}

// STRING 1	format to return
// RAW	  0
// IPV4	  4	IP address family type to search for
// IPV6   6
Bytes* getip(char* interface, u8 strform, u8 iptype)	// Returns dynamic object of an IP address (either raw or string format)
{
    	struct ifaddrs *ifa, *ifa_tmp;
	Bytes* found = NULLPTR;
	u8 addr[IP6STRLEN];
	zeroarray(addr, IP6STRLEN);

	if (getifaddrs(&ifa) == -1) 
	{
	    perror("getifaddrs failed");
	    EXIT(HALT);
	}

	ifa_tmp = ifa;
	while (ifa_tmp)
	{
	    if ((ifa_tmp->ifa_addr) && ((ifa_tmp->ifa_addr->sa_family == AF_INET) || (ifa_tmp->ifa_addr->sa_family == AF_INET6))) 	// If relevant
	    {   // AF_INET
		if (ifa_tmp->ifa_addr->sa_family == AF_INET) // If a part of ipv4 family
		{   
			if (iptype == IPV4)	// If user wanted ipv4, if user did NOT want ipv4 go to next network family structure
				if (eqstr(interface, ifa_tmp->ifa_name)) // If passed in interface name is found
				{
					struct sockaddr_in *in = (struct sockaddr_in*) ifa_tmp->ifa_addr;
					if (strform)	// If user wanted ipv4 in string form
					{
						inet_ntop(AF_INET, &in->sin_addr, addr, sizeof(addr));
			    			found = dynamic_bytes(addr, countuntilnul(addr));
						goto address_searching_done;	// Go to free ifaddrs before returning
					}
					else			// If user wanted ipv4 in raw form
					{
						found = dynamic_bytes((u8*)(&in->sin_addr), IP4ADDRLEN);
						goto address_searching_done;	// Go to free ifaddrs before returning
					}
				}
		    goto nextfamily;
		}
	    	else
		{
			if (iptype == IPV6)	// If a part of ipv6 family
				if (eqstr(interface, ifa_tmp->ifa_name)) // If passed in interface name is found
				{
					struct sockaddr_in6 *in6 = (struct sockaddr_in6*) ifa_tmp->ifa_addr;
					if (strform)	// If user wanted ipv6 in string form
					{
						inet_ntop(AF_INET6, &in6->sin6_addr, addr, sizeof(addr));
			    			found = dynamic_bytes(addr, countuntilnul(addr));
						goto address_searching_done;	// Go to free ifaddrs before returning
					}
					else			// If user wanted ipv6 in raw form
					{
						found = dynamic_bytes((u8*)(&in6->sin6_addr), IP6ADDRLEN);
						goto address_searching_done;	// Go to free ifaddrs before returning
					}
				}
			goto nextfamily;
		}
	    }
	    nextfamily:
	    	ifa_tmp = ifa_tmp->ifa_next;
	}
	address_searching_done:
		freeifaddrs(ifa);
		return found;
}

void printbox(struct sockaddr_in* netbox_ptr)
{
	u8 str[INET_ADDRSTRLEN];
	zeroarray(str, INET_ADDRSTRLEN);
	inet_ntop(AF_INET, &(netbox_ptr->sin_addr), str, INET_ADDRSTRLEN);
	PRINT("------------ BOX --------------");
	printf("FAMILY  : "); PRINTN(netbox_ptr->sin_family);
        printf("ADDR    : "); PRINTN(netbox_ptr->sin_addr.s_addr);
	printf("IP ADDR : "); PRINT(str);
	printf("PORT    : "); PRINTX(netbox_ptr->sin_port);
	printf("ADDRLEN : "); PRINTN(ADDRLEN);
	PRINT("-------------------------------");
	PLN(0);
}
void setfamily(int family, struct sockaddr_in* netbox_ptr) 	 // Set to IPv4 mode (usually the case)
{ 
	goodptr(netbox_ptr, "NULLPTR BOX GIVEN TO SETFAMILY", NOFUNC_RETURN);		// Pointer checking
	netbox_ptr->sin_family = family; 
}

void setip(unsigned char* ipstr, struct sockaddr_in* netbox_ptr) // Set ip address to connect on or bind to
{ 
	goodptr(netbox_ptr, "NULLPTR BOX GIVEN TO SETIP", NOFUNC_RETURN);		// Pointer checking
	if (!ipstr)									// If NULLPTR set to automatic address assignment
	{ 
		netbox_ptr->sin_addr.s_addr = INADDR_ANY; 
		return; 
	}
	inet_pton(AF_INET, ipstr, &(netbox_ptr->sin_addr.s_addr)); // (deprecated) netbox_ptr->sin_addr.s_addr = inet_addr(ipstr); 
}

void setport(u32 port, struct sockaddr_in* netbox_ptr) // Set port number to connect on or bind to
{ 
	goodptr(netbox_ptr, "NULLPTR BOX GIVEN TO SETPORT", NOFUNC_RETURN);		// Pointer checking
	netbox_ptr->sin_port = htons(port); 
}

// *** INIT BOX FUNCTIONS *** //
struct sockaddr_in* init_tcpbox(char* ipstr, u32 port)	// Returns a netbox
{
	struct sockaddr_in* newbox = CALLOC(sizeof(struct sockaddr_in));	// Make space
	setfamily(AF_INET, newbox);						// Set family (NEED TO UPDATE FOR IPV6)
	setip(ipstr, newbox);							// Set ip
	setport(port, newbox);							// Set port
	return newbox;								// Get socket tunnel (usually tcp)
}

// *** SET UP FUNCTIONS *** //
#ifdef _WIN32
int WINSOCKET(int proto)
#else
int SOCKET(int proto)
#endif
{
	register int tunnel = socket(AF_INET, SOCK_STREAM, proto);
	if (tunnel == EMPTY)
	{
		perror("socket");
		THROW("SOCKET ERROR");
	}
	if (setsockopt(tunnel, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
	{
		perror("setsockopt");
		PRINT("SO_REUSEADDR not set.");
		return BADSOCKOPT;
	}
	if (setsockopt(tunnel, SOL_SOCKET, SO_REUSEPORT, &(int){1}, sizeof(int)) < 0)
	{
		perror("setsockopt");
		PRINT("SO_REUSEPORT not set.");
		return BADSOCKOPT;
	}
	return tunnel;
}

int CONNECT(int tunnel, struct sockaddr_in* netbox_ptr)	// Lower level
{
	goodptr(netbox_ptr, "NULLPTR BOX GIVEN TO CONNECT", NOFUNC_RETURN);	// Pointer checking
	register int c = connect(tunnel, (struct sockaddr*)netbox_ptr, ADDRLEN);
	if (c)
	{
		register int i = TRIES;
		while(i-- > 0)	// Post decrement purposeful
			if (!connect(tunnel, (struct sockaddr*)netbox_ptr, ADDRLEN))
				return c;
		perror("connect");
		THROW("CONNECT ERROR");
	}
	return c;
}

int CONNECT_TO(int tunnel, unsigned char* ipstr, u32 port, struct sockaddr_in* netbox_ptr)	// Connects to specified IP and PORT
{
	goodptr(netbox_ptr, "NULLPTR BOX GIVEN TO CONNECT_TO", NOFUNC_RETURN);	// Pointer checking
	setip(ipstr, netbox_ptr); setport(port, netbox_ptr);
	register int c = connect(tunnel, (struct sockaddr*)netbox_ptr, addrlen);
	if(c)
	{
		register u32 i = TRIES;
		while(i-- > 0)	// Post decrement purposeful
			if (!connect(tunnel, (struct sockaddr*)netbox_ptr, ADDRLEN))
				return c;
		perror("connect");
		THROW("CONNECT_TO ERROR");
	}	
	return c;
} 

int BIND(int tunnel, struct sockaddr_in* netbox_ptr)
{
	goodptr(netbox_ptr, "NULLPTR BOX GIVEN TO BIND", NOFUNC_RETURN);	// Pointer checking
	register int b = bind(tunnel, (struct sockaddr*)netbox_ptr, ADDRLEN);
	if (b)
	{
		perror("bind");
		THROW("BIND ERROR");
	}
	return b;
}

// EXPECTED_CLIENTS == 1
int LISTEN(int tunnel)
{
	register int l = listen(tunnel, EXPECTED_CLIENTS);
	if (l)
	{
		perror("listen");
		THROW("LISTEN ERROR");
	}
	return l;
}

int ACCEPT(int tunnel, struct sockaddr_in* netbox_ptr)
{
	goodptr(netbox_ptr, "NULLPTR BOX GIVEN TO ACCEPT", NOFUNC_RETURN);	// Pointer checking
	int addrlen = ADDRLEN;
	register int a = accept(tunnel, (struct sockaddr*)netbox_ptr, &addrlen);
	if(a == EMPTY)
	{
		perror("accept");
		THROW("ACCEPT ERROR");
	}
	return a;
}

// CLEARBUFFER   1
// NOCLEARBUFFER 0
u32 READ(Portal* portal, i64  offset, u32 amount, u8 clearbufferflag)
{
	goodptr(portal, "NULLPTR PORTAL GIVEN TO READ", NOFUNC_RETURN);		// Pointer checking
	if (offset + amount > PORTAL_ALLOCATION(portal))
	{
		PORTALBUFFER(portal)->array = REALLOC(PORTALBUFFER(portal)->array, offset + amount + 1);	// If more than preset limit, enlarge portal buffer (can crash embedded devices)
		zeroarray(PORTALBUFFER(portal)->array + offset, amount + 1);			// Includes Nul-terminator for all 'Bytes' objects
		PORTAL_ALLOCATION(portal) = offset + amount + 1;
		goto startreading;
	}
	if (clearbufferflag)	// If intending to clear only space needed for new read-in [ Customized actions as opposed to using 'CLEARPORTALBUFFER()' ]
	{
		zeroarray(PORTALBUFFER(portal)->array, amount);
		PORTALBUFFER(portal)->len = 0;
	}
	
	startreading: ;
		register int r = read(PORTALTUNNEL(portal), PORTALBUFFER(portal)->array + offset, amount);
		if (r == EMPTY) 
		{
			perror("read");
			THROW("READ ERROR");
			r = 0; // Unreachable for now
		}
		else
		{
			PORTALBUFFER(portal)->len += r;		// Update byte string length
			if (PORTALENCRYPTED(portal))		// If encrypted then decrypt
				decrypt7(PORTALBUFFER(portal));
		}
	return r;
}

// FREEOLD   1
// NOFREEOLD 0
u8 SENDSTR(Portal* portal, char* str, u8 freeold)	// Will free sent in string if specified
{
	goodptr(portal, "NULLPTR PORTAL GIVEN TO SENDSTR", NOFUNC_RETURN);	// Pointer checking
	if (!goodptr(str, "NULLPTR STR GIVEN TO SEND", FUNC_RETURN))		// Pointer checking
		return 0;
	if (PORTALENCRYPTED(portal))			// If encrypted connection then encrypt
		encrypt7(PORTALBUFFER(portal));		// FIX...
	if (write(PORTALTUNNEL(portal), str, countuntilnul(str)) == EMPTY)
	{
		perror("write");
		PRINT("SENDSTR ERROR");
		return 0;
	}
	if (freeold) 
	{
		if (PORTALBUFFER(portal))				// Pointer checking
			if (str != PORTALBUFFER(portal)->array) 	// DO NOT FREE THE PORTALBUFFER 'array' BY ACCIDENT
				FREE(&str);
		else 
			FREE(&str);
	}
	return 1;
}

u8 SEND(Portal* portal, Bytes** str, u8 freeold)	// Will free sent in string if specified
{
	goodptr(portal, "NULLPTR PORTAL GIVEN TO SEND", NOFUNC_RETURN);				// Pointer checking
	if (!goodptr(*str, "NULLPTR *STR GIVEN TO SEND", FUNC_RETURN))				// Pointer checking		
	{
		SENDSTR(portal, "SEND had null string and failed.\n", NOFREEOLD);
		return 1;
	}
	if (!goodptr((*str)->array, "NULLPTR STR->ARRAY GIVEN TO SEND", FUNC_RETURN))		// Pointer checking
		return 0;
	if (PORTALENCRYPTED(portal))								// If encrypted connection then encrypt
		encrypt7(*str);
	if (write(PORTALTUNNEL(portal), (*str)->array, (*str)->len) == EMPTY)
	{
		perror("write");
		PRINT("SEND ERROR");
		return 0;
	}
	if (freeold && *str != PORTALBUFFER(portal)) 	// DO NOT FREE THE PORTALBUFFER BY ACCIDENT
		free_bytes(str);
	return 1;
}

u8 SENDWITHOFFSET(Portal* portal, Bytes** str, i64  offset, u8 freeold)	// Will free sent in string if specified
{
	goodptr(portal, "NULLPTR PORTAL GIVEN TO SEND", NOFUNC_RETURN);				// Pointer checking
	if (!goodptr(*str, "NULLPTR *STR GIVEN TO SEND", FUNC_RETURN))				// Pointer checking		
	{
		SENDSTR(portal, "SEND had null string and failed.\n", NOFREEOLD);
		return 1;
	}
	if (!goodptr((*str)->array, "NULLPTR STR->ARRAY GIVEN TO SEND", FUNC_RETURN))		// Pointer checking
		return 0;
	if (PORTALENCRYPTED(portal))			// If encrypted connection then encrypt
		encrypt7(*str);
	if (write(PORTALTUNNEL(portal), (*str)->array + offset, (*str)->len - offset) == EMPTY)
	{
		perror("write");
		PRINT("SEND ERROR");
		return 0;
	}
	if (freeold && *str != PORTALBUFFER(portal)) 	// DO NOT FREE THE PORTALBUFFER BY ACCIDENT
		free_bytes(str);
	return 1;
}

void CLOSE(Portal** portal)
{ 
	if (!portal)
		return;
	goodptr(*portal, "NULLPTR PORTAL GIVEN TO CLOSE", NOFUNC_RETURN);	// Pointer checking
	close(PORTALTUNNEL((*portal)));						// Close connection
	FREE(&((*portal)->branch));						// Free netbox
	rm_elem(&portalhdr, portal); 						// Remove portal from portal list (All dynamic memory will be freed)
}

void CLEARPORTALBUFFER(Portal* portal)
{
	zeroarray(PORTALBUFFER(portal)->array, PORTALBUFFER(portal)->len);
	PORTALBUFFER(portal)->len = 0;
}

// *** COMM TOOLS *** //

u32 blindrecv(Portal* portal, u32 numbytes)	// Reads blind amount of bytes into portal buffer and returns that amount
{
	register u32 num = 0;
	register u32 amt = 0;
	do
	{
	  num += (amt = READ(portal, num, numbytes, CLEARBUFFER));
	} while (amt);
	return num;
}

void devotedrecv(Portal* portal, u32 numbytes)
{
	while (numbytes)	// Zero for no portal buffer offset
		numbytes -= READ(portal, 0, numbytes, CLEARBUFFER);
}

u64  recvmodule(Portal* portal)	// Does NOT clear portal buffer AFTERWARDS and returns current portal buffer length
{
	if (!portal)						 // Check if portal open
		return 0;
	register i32 readlimit  = NETMEMLIMIT + FILEMEMLIMIT;	 // Stores max amount that can be read
	register u32 actualread = 0; 				 // Stores amount actually read
	while (readlimit > 0)					 // While reading limit is not reached (actual value is subtracted by actual read number until zero)
	{
		if (readlimit < STREAM_LIMIT)
			goto reading_done;		
		readlimit -=  (actualread = READ(portal, PORTALBUFFER(portal)->len, STREAM_LIMIT, NOCLEARBUFFER)); // Read bytes at 1500MTU until limit or done (READ does not look at portalbuffer len)
//		printf("RECVMODULE -> actualread : %d\n", actualread);
		*(PORTALBUFFER(portal)->array + PORTALBUFFER(portal)->len) = 0; // Nul-terminate the string in the portal buffer (gibberish from past READs may exist after this Nul-terminator)
		if (actualread < STREAM_LIMIT)			 	 // If READ did not read to its own specified limit, stream is done.
			goto done;
	}
	reading_done:
		actualread = READ(portal, PORTALBUFFER(portal)->len, readlimit, NOCLEARBUFFER);	// Read last bytes
		*(PORTALBUFFER(portal)->array + PORTALBUFFER(portal)->len) = 0;  		// Nul-terminate (redundancy for robustness)
	done: // All done					    
	return PORTALBUFFER(portal)->len;
}

u8 sigmodule(Portal* portal, u64 numbytes_handled)	// Checks for signal bytes to know if sender will end or continue the network stream
{
	register u64  amtread = PORTALBUFFER(portal)->len;
	register u32 numbytes_fromprevsignal = numbytes_handled % (NETMEMLIMIT + FILEMEMLIMIT);
	if (!numbytes_fromprevsignal)	// If last read was NETMEMLIMIT + FILEMEMLIMIT bytes long the return first byte
		return *(PORTALBUFFER(portal)->array);
	else				// If last read was less, check for signal in case signal character exists in the middle
	{
		if ((numbytes_fromprevsignal + amtread) > (NETMEMLIMIT + FILEMEMLIMIT))	// If character signal in the middle, find and return it
			return *(PORTALBUFFER(portal)->array + ((NETMEMLIMIT + FILEMEMLIMIT) - numbytes_fromprevsignal));
		else									// Else carry on without a signal character
		{
//			PRINT("No signal found in portal buffer.");
			return 0;
		}
	} 
}

Portal* setup_tcp_sender(char* ipstr, char* iface_ipstr, u32 port, u8 encryptflag)
{
	struct sockaddr_in* box = init_tcpbox(ipstr, port);
	register int tunnel = SOCKET(IPPROTO_TCP);
	if (tunnel == BADSOCKOPT)
		THROW("BADSOCKOPT ERROR");
	printf("Aqcuired socket descriptor -> %d\n", tunnel);
	if (iface_ipstr)	// If interface ip is specified, make the connection using that interface's ip
	{
		inet_pton(AF_INET, iface_ipstr, &box->sin_addr.s_addr);	// Fill & bind
		BIND(tunnel, box);
	}	
	printf("Initiating reliable connection to %s\n", ipstr);
	CONNECT(tunnel, box);

	// Once connection is successful, record connection in list							      			// Around 6 MB of space (below)
	Portal* newportal = make_elem(&portalhdr, NETMEMLIMIT + FILEMEMLIMIT + 1, tunnel, ++PORTALSOPEN, IPPROTO_TCP, encryptflag, 
															dynamic_bytes(NULLPTR, NETMEMLIMIT + FILEMEMLIMIT), 
																		(void*)(box), ADDNODE);
	PORTALBUFFER(newportal)->len = 0; // Nothing read in yet so its zero although it has NETMEMLIMIT + FILEMEMLIMIT available bytes
	return newportal;
}

Portal* setup_tcp_receiver(char* ipstr, u32 port, u8 encryptflag) 
{
	struct sockaddr_in* box = init_tcpbox(ipstr, port);
	register int tunnel = SOCKET(IPPROTO_TCP);
	printf("Aqcuired socket descriptor -> %d\n", tunnel);
	if (tunnel == BADSOCKOPT)
		THROW("BADSOCKOPT ERROR");	
	printf("Binding to %d\n", port);
	BIND(tunnel, box);				// Bind to port through tunnel
	printf("Listening on %d\n", port);
	LISTEN(tunnel);					// Put fingers together 
	tunnel = ACCEPT(tunnel, box);			// Open and enter portal through tunnel
	printf("Incoming connection\n");

	// Once connection is successful, record connection in list							      // 6 MB of space
	Portal* newportal = make_elem(&portalhdr, NETMEMLIMIT + FILEMEMLIMIT + 1, tunnel, ++PORTALSOPEN, IPPROTO_TCP, encryptflag, 
															dynamic_bytes(NULLPTR, NETMEMLIMIT + FILEMEMLIMIT), 
																		(void*)(box), ADDNODE);
	PORTALBUFFER(newportal)->len = 0; // Nothing read in yet so its zero although it has NETMEMLIMIT + FILEMEMLIMIT available bytes
	return newportal;
}

// INCEIVER  1
// PERCEIVER 0
Portal* portalize(char* ipstr, char* iface_ipstr, u32 port, u8 role, u8 encryptflag)
{
	switch (role)
	{
		case INCEIVER  : return setup_tcp_sender(ipstr, iface_ipstr, port, encryptflag); // Sender
		case PERCEIVER : return setup_tcp_receiver(iface_ipstr, port, encryptflag);	 // Receiver
		default	       : return NULLPTR;
	}
}

i64  perceptnum(Portal* portal)	// Receives 8 (a.k.a. NETWORK_NUMSZ) bytes from sender and get integer of type 'i64 '
{
	goodptr(portal, "NULLPTR PORTAL GIVEN TO PERCEPTNUM", NOFUNC_RETURN);
	devotedrecv(portal, NETWORK_NUMSZ);					// Will not return until number is received
	          i64 *  numptr = (i64 *)(PORTALBUFFER(portal)->array);		// Get correct pointer type
	register  i64    number = (i64 )(*numptr);				// Get integer received in portal buffer (NETWORK_NUMSZ == 8 bytes)			
	zeroarray(PORTALBUFFER(portal)->array, NETWORK_NUMSZ);	 	 	// Clean buffer after 'devotedrecv' use
	return number;
}

Bytes* perceptbytes(Portal* portal, u64 limit)
{
	goodptr(portal, "NULLPTR PORTAL GIVEN TO PERCEPTBYTES", NOFUNC_RETURN);
	devotedrecv(portal, limit);						  // Will not return until byte limit to read has been reached
	Bytes* bytes = copy_bytes(PORTALBUFFER(portal));			  // Copy bytes from portal buffer to a pointer that will be returned for usage
	zeroarray(PORTALBUFFER(portal)->array, PORTALBUFFER(portal)->len);	  // Clean buffer after 'devotedrecv' use
	return bytes;
}

// START HERE (TRY READ THAT BLOCKS AFTER NOT READING ENOUGH BYTES)
u8 perceptfile(Portal* portal)
{
	goodptr(portal, "NULLPTR PORTAL GIVEN TO PERCEPTFILE", NOFUNC_RETURN);
	
	Bytes* filename = perceptbytes(portal, MAXPATHLEN);			// File path of up to 4096 characters allowed
	FILE* stream = fopen(filename->array, "w+");				// Open new file to write received contents to
	if (!stream)				  				// Check stream
	{
		PRINT("COULD NOT OPEN FILE PATH FOR INCOMING FILE");
		return 0;
	}
	
	register u64 numbytes_handled = 0; 
	register u8 firstloopdone = 0;
	u8 sighold = 0;
	do 
	{
		if (!recvmodule(portal))					// Receive upto 6MB and handle
			goto cleanup;
		if (!firstloopdone)						// Check for "404" once
		{
			if (eqstr(PORTALBUFFER(portal)->array, "404"))
			{
				PRINT("File is inaccessible due to permissions or lack of existence.");
				++numbytes_handled; // Set as zero bytes read [Addition is for "numbytes_handled - 1" in below printf statement]
				goto cleanup;
			}
			++firstloopdone;
		}
//		printf("PERCEPTFILE -> data read-in : %d\n", PORTALBUFFER(portal)->len);
		
		if ((sighold = sigmodule(portal, numbytes_handled)) == ALLDONE)
			PRINT("ALLDONE detected");
		if (!sighold)
			writefast(PORTALBUFFER(portal)->array, PORTALBUFFER(portal)->len, stream, NOCLOSEFILE); // Write bytes to file (no skip)
		else
			writefromnetwork(PORTALBUFFER(portal)->array, PORTALBUFFER(portal)->len, numbytes_handled, stream, NOCLOSEFILE);
		numbytes_handled += PORTALBUFFER(portal)->len; 			// Write bytes to file (skipping marker/signal byte) [above line]
		PORTALBUFFER(portal)->len = 0;					// Reset portal buffer length to 0 for next read
	} while (sigmodule(portal, numbytes_handled) != ALLDONE);		// While not done
	
	cleanup:
		zeroarray(PORTALBUFFER(portal)->array, NETMEMLIMIT + FILEMEMLIMIT);
		free_bytes(&filename);
		fclose(stream);
	printf("Received file data: %lld bytes.\n", numbytes_handled - 1);
	return 1;
}

// ****************** UNDER CONSTRUCTION ******************
/*u8 perceptdir(Portal* portal)
{
	goodptr(portal, "NULLPTR PORTAL GIVEN TO PERCEPTDIR", NOFUNC_RETURN);
	Bytes* holdcurrentpath = NULLPTR;
	do 
	{
		recvmodule(portal);							// Receive upto 6MB and handle
		holdcurrentpath = constructdir(&(PORTALBUFFER(portal)), recv_as_name, holdcurrentpath, NOFREEOLD); 	// Create directory structures from current PORTALBUFFER	
		PORTALBUFFER(portal)->len = 0;						// Reset portal buffer length to 0 for next read
	} while (*(PORTALBUFFER(portal)->array) != ALLDONE);
	zeroarray(PORTALBUFFER(portal)->array, NETMEMLIMIT + FILEMEMLIMIT);		// Clean portal buffer
	Bytes* holdname = NULLPTR;							// Initialize file-path-name holder
	Bytes* holdtop  = dynamic_bytes(recv_as_name, countuntilnul(recv_as_name));	// Initialize parent-path-name holder with a string
	register u64 initialtopsz = holdtop->len;					// Initialize parent-path-name string length
	appendctostr(holdtop, SLASH);							// Append a '/'
	do										// Read and write all large files coming in from the network
	{
		holdname = perceptbytes(portal, NULLIPSTR);
		if (!holdname)
			continue;
		holdtop = appendstr(holdtop, holdname->array + 1, countuntilnul(holdname->array + 1));
		perceptfile(portal, holdtop->array, NULLIPSTR);
		holdtop = chop(holdtop, holdtop->array + initialtopsz);
	} while (*(holdname->array) != ALLDONE);	
	PRINT("Received directory data.");
	return 1;
}*/

u8 inceptnum(Portal* portal, i64  number)		// DOES NOT FREE ANY MEMORY
{
	u8 numstr[NETWORK_NUMSZ];				// Use stack memory to store number value
	i64 * numptr = (i64 *)(numstr);				// Make a large integer pointer point to beginning of 8 byte array
	Bytes imitate_bytes;					// Make space for Bytes object on stack
	Bytes* bytes_ptr      = &imitate_bytes;
	imitate_bytes.array   = numstr;			 	// Assign string to array position in Bytes struct
	imitate_bytes.len     = NETWORK_NUMSZ;	 		// Assign string length to len position in Bytes struct
	zeroarray(numstr, NETWORK_NUMSZ);			// Zero-out the memory before injecting value
	*numptr = number;					// Inject the value of 'number' into the 8 byte section of memory
	return SEND(portal, &bytes_ptr, NOFREEOLD);		// Send number over network
}

u8 inceptcstr(Portal* portal, char* object)		// FREES 'OBJECT'
{
	Bytes imitate_bytes;				 // Make space for Bytes object on stack
	Bytes* bytes_ptr    = &imitate_bytes;
	imitate_bytes.array = object;			 // Assign string to array position in Bytes struct
	imitate_bytes.len   = countuntilnul(object);	 // Assign string length to len position in Bytes struct
	u8 hold = SEND(portal, &bytes_ptr, NOFREEOLD); // Does not attempt to free Bytes object ('FREE()' would figure it out but this is healthier))
	FREE(&object);				 	 // Frees c-string if 'object' is NOT a literal or stack value 
	return hold;					 // Successful send over network
}

u8 inceptbytes(Portal* portal, Bytes** object)	// FREES 'OBJECT'
{
	return SEND(portal, object, FREEOLD);		// Send bytes
}

u8 inceptfile(Portal* portal, Bytes** object, Bytes** as, u8 freeobject)	// (Like inception the movie) inject an "idea" into another computers mind (in this case send a file)	|	FREES 'AS'
{										// Sends file in blocks, each block is prefixed by a signal/marker byte (either MORETOCOME or ALLDONE)	|
	FILE* stream = fopen((*object)->array, "r");				// Opens object as file
	if (!stream)								// Checks stream
	{
		Bytes* errormsg = dynamic_bytes("404", 3);
		SEND(portal, &errormsg, FREEOLD);
		return 0;
	}
	
	SEND(portal, as, FREEOLD);				    // Send specified filepath name to be installed on other computer
	register u64  amtread = 0; 			    // The rest of the code opens and sends all of the file content over the network
	char* ptr_plusabyte = PORTALBUFFER(portal)->array + 1;
	while (amtread = FREAD(&ptr_plusabyte, NETMEMLIMIT + FILEMEMLIMIT - 1, stream))	// -1 --> one for signal char at beginning
	{
		ptr_plusabyte = PORTALBUFFER(portal)->array + 1;    // Reset pointer that read in data to portal buffer
		PORTALBUFFER(portal)->len = amtread + 1;	    // Update buffer length
		*(PORTALBUFFER(portal)->array + amtread + 1) = 0;   // Nul-terminate string just to be safe
		if (amtread != (NETMEMLIMIT + FILEMEMLIMIT - 1))    // Signals end of stream
			goto reading_done;
		*(PORTALBUFFER(portal)->array) = MORETOCOME;	    // Set MORETOCOME marker in communication stream to signal receiver that more data is following this data
//		printf("Data sent == %lld\n", portal->line->len);
		SEND(portal, &PORTALBUFFER(portal), NOFREEOLD);     // Send all NETMEMLIMIT+FILEMEMLIMIT+MARKER characters (DOES NOT FREE PORTALBUFFER)
	}
	
	if (!amtread)
		goto cleanup;
		
	reading_done:
		*(PORTALBUFFER(portal)->array) = ALLDONE;	  // Set ALLDONE marker in communication stream to signal receiver that stream is over
//		printf("Data sent == %lld\n", portal->line->len); 
		SEND(portal, &PORTALBUFFER(portal), NOFREEOLD);   // Send MARKER character + all bytes (DOES NOT FREE PORTALBUFFER)
	
	cleanup:
		if (freeobject)
			FREE(object);
		fclose(stream);	    	     		  	  // Closes file stream
		
	return 1; // Successful send
}	// Sending in blocks helps prevent the usage of too much RAM memory when dealing with small embedded systems and large MB/GB/TB scale files

/*
// ************************ UNDER CONSTRUCTION ************************
u8 inceptdir(Portal* portal, char* object)
{
	// *** ** * SETUP * ** *** //
	if (!CHDIR(object))
		return EMPTY;
	Bytes* cwd         = GETCWD();
	Bytes* cwdcpy      = copy_bytes(cwd); 							// Convert path to bytes object
	if (!goodptr(cwd, "DYNAMIC_BYTES FOR CWD RETURNED NULL -- MAKEREADY", FUNC_RETURN))	// Check pointer
		return 0;
	Portal*  startdir    = OPENDIR(cwd);					// Open directory
	if (!goodptr(startdir, "CANNOT OPEN CWD IN MAKEREADY", FUNC_RETURN))	// Check pointer
		return 0;
	return 1;
}*/

// ******************************************************************************************************************************** Main functions

#endif	// For NETREACH_UNIX_H
