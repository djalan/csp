#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "fullduplex.h"



/*
http://www.java2s.com/Code/C/File/Copyafile.htm
*/
int copierFichier( const char * source, const char * destination ) {
/*
	printf( "%s\n", source );
	printf( "%s\n", destination );
*/

  FILE *from, *to;
  char ch;

  /* open source file */
  if((from = fopen(source, "rb"))==NULL) {
    printf("Cannot open source file.\n");
    return 1;
  }

  /* open destination file */
  if((to = fopen(destination, "wb"))==NULL) {
    printf("Cannot open destination file.\n");
    return 2;
  }

  /* copy the file */
  while(!feof(from)) {
    ch = fgetc(from);
    if(ferror(from)) {
      printf("Error reading source file.\n");
      return 3;
    }
    if(!feof(from)) fputc(ch, to);
    if(ferror(to)) {
      printf("Error writing destination file.\n");
      return 4;
    }
  }

  if(fclose(from)==EOF) {
    printf("Error closing source file.\n");
    return 5;
  }

  if(fclose(to)==EOF) {
    printf("Error closing destination file.\n");
    return 6;
  }

  return 0;
}



void listerFichier( char * commande ) {

	char * cmd	= strtok( commande, "," );
	char * usager	= strtok( NULL, "," );

	printf( "%s - %s\n", cmd, usager );

}



void chercherFichierStocke( char * commande ) {

	char * cmd	= strtok( commande, "," );
	char * usager	= strtok( NULL, "," );
	char * numero	= strtok( NULL, "," );

	printf( "%s - %s - %s\n", cmd, usager, numero );

	char fichierResultat[ (int) strlen(usager) + (int) strlen(numero) + 8 ];
	strcpy( fichierResultat, usager );
	strcat( fichierResultat, numero );
	strcat( fichierResultat, "_res.txt" );

	char source[ (int)strlen(rep_server) + (int)strlen(fichierResultat) ];
	strcpy( source, rep_server );
	strcat( source, fichierResultat);

	char destination[ (int)strlen(rep_client) + (int)strlen(fichierResultat) ];
	strcpy( destination, rep_client );
	strcat( destination, fichierResultat);

	copierFichier( source, destination);
}



void afficherFichierResultat( char * commande ) {
	
	char * cmd	= strtok( commande, "," );
	char * usager	= strtok( NULL, "," );
	char * fichier	= strtok( NULL, "," );

	printf( "%s - %s - %s\n", cmd, usager, fichier );	

}



void livrerFichierCommande( char * commande ) {

	char * cmd	= strtok( commande, "," );
	char * usager	= strtok( NULL, "," );
	char * fichier	= strtok( NULL, "," );
	char * desire	= strtok( NULL, "," );

	printf( "%s - %s - %s - %s\n", cmd, usager, fichier, desire );	
}




void quitter() {

	if ( remove(np_client_server) != 0 )
		fprintf( stderr, "Erreur lors de la suppression du named pipe np_client_server!\n" );
	else
		printf( "Le named pipe np_client_server a été supprimé!\n" );
	
		
	if ( remove(np_server_client) != 0 )
		fprintf( stderr, "Erreur lors de la suppression du named pipe np_server_client!\n" );
	else
		printf( "Le named pipe np_server_client a été supprimé!\n" );

	char effacer_rep_server[ 7 + (int) strlen(rep_server) ];
	sprintf( effacer_rep_server, "rm -rf %s", rep_server );
	system( effacer_rep_server );

	rmdir( rep_travail );
}



int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		fprintf(stderr, "%s: usage incorrect!\n", argv[0]);
		fprintf(stderr, "Aucun argument permis.\n");
		return 1;
	}

	mkdir( rep_travail, 0777 );
	mkdir( rep_server, 0777) ;
	
	
	int rdfd, wrfd, ret_val, numread;
	char buf[MAX_BUF_SIZE];

	//Create the first named - pipe
	ret_val = mkfifo(np_client_server, 0777);

	if ((ret_val == -1) && (errno != EEXIST))
	{
		perror("Error creating the named pipe");
		return -1;
	}
	
	ret_val = mkfifo(np_server_client, 0777);

	if ((ret_val == -1) && (errno != EEXIST))
	{
		perror("Error creating the named pipe");
		return -1;
	}

	do
	{
		//Open the first named pipe for reading
		rdfd = open(np_client_server, O_RDONLY);
		//Read from the first pipe
		numread = read(rdfd, buf, MAX_BUF_SIZE);
		buf[numread] = '\0';

		printf("Full Duplex Server : Read From the pipe : %s\n", buf);

		switch( buf[0] ) {
			case '1':
				listerFichier( buf );
				break;
			case '2':
				chercherFichierStocke( buf );
				break;
			case '3':
				afficherFichierResultat( buf );
				break;
			case '4':
				livrerFichierCommande( buf );
				break;
			case 'q':
				break;
		}

		//Open the second named pipe for writing
		wrfd = open(np_server_client, O_WRONLY);
		//Write the answer to the second pipe    
		write(wrfd, buf, strlen(buf));

	} while ( strcmp(buf, "quitter"));

	quitter();	

	return 0;
}
