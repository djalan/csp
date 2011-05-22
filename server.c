#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <fullduplex.h> /* For name of the named-pipe */

static const char * rep_travail = "/tmp/SIRA15068305";
static const char * rep_client  = "/tmp/SIRA15068305/client";
static const char * rep_server  = "/tmp/SIRA15068305/server";

int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		fprintf(stderr, "%s: usage incorrect!\n", argv[0]);
		fprintf(stderr, "Aucun argument permis.\n");
		return 1;
	}
	
	printf("server\n");
	
	int rdfd, wrfd, ret_val, count, numread;
	char buf[MAX_BUF_SIZE];

	//Create the first named - pipe
	ret_val = mkfifo(NP1, 0666);

	if ((ret_val == -1) && (errno != EEXIST))
	{
		perror("Error creating the named pipe");
		exit (1);
	}
	
	ret_val = mkfifo(NP2, 0666);

	if ((ret_val == -1) && (errno != EEXIST))
	{
		perror("Error creating the named pipe");
		exit (1);
	}

	//Open the first named pipe for reading
	rdfd = open(NP1, O_RDONLY);

	//Open the second named pipe for writing
	wrfd = open(NP2, O_WRONLY);

	//Read from the first pipe
	numread = read(rdfd, buf, MAX_BUF_SIZE);

	buf[numread] = '0';

	printf("Full Duplex Server : Read From the pipe : %sn", buf);
	
	//Convert to the string to upper case 
	count = 0;
	while (count < numread)
	{
		buf[count] = toupper(buf[count]);
		count++;
	}

	//Write the converted string back to the second pipe    
	write(wrfd, buf, strlen(buf));
	
	return 0;
}