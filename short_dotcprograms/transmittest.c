#include <string.h>
#include "../netreach_unix.h"
#include <linux/if.h>
#include <ifaddrs.h>
#include <sys/ioctl.h>

#define CURRENT_INTERFACE "wls34u2" // "wlx00e04c0bf87d"

Bytes* getmac(char* interface)	// Returns dynamic bytes object
{
    struct ifreq s;
    int fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);

    nbytesto(s.ifr_name, interface, countuntilnul(interface));
    if (0 == ioctl(fd, SIOCGIFHWADDR, &s)) 
        return dynamic_bytes(s.ifr_addr.sa_data, 6);
    close(fd);
}

Bytes* getip4(char* interface)
{
    struct ifreq s;
    int fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);

    nbytesto(s.ifr_name, interface, countuntilnul(interface));
    if (0 == ioctl(fd, SIOCGIFADDR, &s))
	return dynamic_bytes((char*)(&(((struct sockaddr_in*)(&(s.ifr_addr)))->sin_addr).s_addr), IP4ADDRLEN);
    close(fd);
}

Bytes* getip6(char* interface)
{
    	struct ifaddrs *ifa, *ifa_tmp;
	char addr[IP6STRLEN];
	Bytes* holder = NULLPTR;

	if (getifaddrs(&ifa) == -1) 
	{
	    perror("getifaddrs failed");
	    EXIT(HALT);
	}

	ifa_tmp = ifa;
	while (ifa_tmp)
	{
	    if ((ifa_tmp->ifa_addr) && ((ifa_tmp->ifa_addr->sa_family == AF_INET) || (ifa_tmp->ifa_addr->sa_family == AF_INET6))) 
	    {
		if (ifa_tmp->ifa_addr->sa_family == AF_INET) 
		{   // AF_INET
		    // create IPv4 string
		    // struct sockaddr_in *in = (struct sockaddr_in*) ifa_tmp->ifa_addr;
		    // inet_ntop(AF_INET, &in->sin_addr, addr, sizeof(addr));
		    goto nextipv6;
		}
		// AF_INET6
		// create IPv6 string
		struct sockaddr_in6 *in6 = (struct sockaddr_in6*) ifa_tmp->ifa_addr;
		if ((in6->sin6_addr).s6_addr[0] == 0xfe && (in6->sin6_addr).s6_addr[1] == 0x80)
		{
			//inet_ntop(AF_INET6, &in6->sin6_addr, addr, sizeof(addr));
			holder = dynamic_bytes((char*)((in6->sin6_addr).s6_addr), IP6ADDRLEN);	// Capture this IPv6 address and return it
			goto address_searching_done;
		}
	    }
	    nextipv6:
	    	ifa_tmp = ifa_tmp->ifa_next;
	}
	address_searching_done:
		freeifaddrs(ifa);
		return holder;
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
	memset(&mcast_group, 0, sizeof(mcast_group));
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

	// ******************************************** Modified Begin
	Bytes* ip6 = getip6(CURRENT_INTERFACE);
	Bytes* ip4 = getip4(CURRENT_INTERFACE);
	
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
	// ******************************************** Modified End

	int sockfd;
	struct sockaddr_in     servaddr;

	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));

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
	while (loop++ < 10000000);
	
	if (sendto(sockfd, bytemsg->array, bytemsg->len, 0, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) 
	{
		perror("sendto()");
		exit(4);
	}
	
	cleanup:
		close(sockfd);
		close(recv_s);
		free_bytes(&bytemsg);
	
	executeorder66:
		// system(scriptcommand);	// Run script that changes iptable rules
		
	return dynamic_bytes(inet_ntoa(from.sin_addr), IP4STRLEN);
}

int main(int c, char** v) // "192.168.0.166"
{
	/*Bytes* scriptcommand = NULLPTR;	// Script path should not have spaces and should be encased with double quotes (e.g. "/dir1/dir2/script name arg1 arg2 ...etc")
	if (c < 2)			// If not entered, enter it manually during run time
	{
		PRINT("NOT ENOUGH ARGS");
		scriptcommand = userstring("Enter full path of script to run with its arguments all between \" and \": ");
	}
	else
		scriptcommand = { *(v + 1), countuntilnul(*(v + 1)) };*/
	
	// Run script to set up iptables first

	Bytes* msgfrom = listen_for_outreach();
	free_bytes(&msgfrom);
	
	Portal* ptr = setup_tcp_receiver(NULLPTR, 80, NOENCRYPT);
	char goodconnection = 1;
	Bytes* holdmsg = NULLPTR;
	while (goodconnection)
	{
		holdmsg = perceptbytes(ptr, &msgfrom);
		printf("Received http msg from %s\n", msgfrom->array);
		inceptbytes(ptr, holdmsg);
		free_bytes(&msgfrom);
	}
	
	return 0;
}
