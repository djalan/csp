#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "fullduplex.h"

int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		fprintf(stderr, "%s: usage incorrect!\n", argv[0]);
		fprintf(stderr, "Aucun argument permis.\n");
		return 1;
	}
	
	int rdfd, wrfd, ret_val, numread;
	char buf[MAX_BUF_SIZE];

	//Create the first named - pipe
	ret_val = mkfifo(np_client_server, 0666);

	if ((ret_val == -1) && (errno != EEXIST))
	{
		perror("Error creating the named pipe");
		return -1;
	}
	
	ret_val = mkfifo(np_server_client, 0666);

	if ((ret_val == -1) && (errno != EEXIST))
	{
		perror("Error creating the named pipe");
		return -1;
	}

	do
	{
		//Open the first named pipe for reading
		rdfd = open(np_client_server, O_RDONLY);

		//Open the second named pipe for writing
		wrfd = open(np_server_client, O_WRONLY);
	
		//Read from the first pipe
		numread = read(rdfd, buf, MAX_BUF_SIZE);
	
		buf[numread] = '\0';

		printf("Full Duplex Server : Read From the pipe : %s\n", buf);

		//Write the answer to the second pipe    
		write(wrfd, buf, strlen(buf));
	} while ( strcmp(buf, "quitter"));
	
	rmdir( rep_server );	

	return 0;
}
