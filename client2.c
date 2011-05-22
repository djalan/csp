#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "fullduplex.h" /* For name of the named-pipe */

char * ClientServeurTest(char * commande[])
{
	int wrfd, rdfd, numread;
	char rdbuf[MAX_BUF_SIZE];
	
	//Open the first named pipe for writing
	wrfd = open(np_client_server, O_WRONLY);

	//Open the second named pipe for reading
	rdfd = open(np_server_client, O_RDONLY);

	//Write to the pipe
	write(wrfd, commande, strlen(commande));

	//Read from the pipe
	numread = read(rdfd, rdbuf, MAX_BUF_SIZE);

	rdbuf[numread] = '\0';
	
	return rdbuf;
}