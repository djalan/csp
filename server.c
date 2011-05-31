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
#include "fichier.h"
#include "usager.h"
#include "tableau.h"



char * listerFichier( char * commande )
{
	char * cmd	= strtok( commande, "," );
	char * usager	= strtok( NULL, "," );

	printf( "%s - %s\n", cmd, usager );


	if ( !tableauContient(usager) ) {
		return "Cet usager n'a aucun fichier!\n";	
	} else {
		Usager u = tableauElement( tableauPosition(usager) ); 
		int nbrFichiers = donnerNbrFichiers( u );

	        char ext[] = ".txt";
	        int taille_rep;
	        int taille_usager = (int) strlen(usager);
	        int taille_ext = (int) strlen(ext);
	        char * rep = (char *) malloc ( sizeof(char) * (taille_usager + 1 + taille_ext + 1) );
		sprintf( rep, "%s1%s\n", usager, ext );
	       
		int i;
	        char temp_str[5];
	        for ( i=2; i<=nbrFichiers; i++ ) { 
	                sprintf( temp_str, "%d", i );
			char fichier[ taille_usager + (int) strlen(temp_str) + taille_ext + 1 ];
			sprintf( fichier, "%s%d%s\n", usager, i, ext );
	
	                rep = (char *) realloc ( rep, sizeof(char) * ((int) strlen(rep) + (int) strlen(fichier)) );
			strcat( rep, fichier );
	        }   
	
		return rep;
	}
}



void chercherFichierStocke( char * commande )
{
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




void afficherFichierResultat( char * commande )
{	
	char * cmd	= strtok( commande, "," );
	char * usager	= strtok( NULL, "," );
	char * fichier	= strtok( NULL, "," );

	printf( "%s - %s - %s\n", cmd, usager, fichier );	
}



void removeCharFromString(char c, char *str)
{
    int i=0;
    int len = strlen(str)+1;

    for(i=0; i<len; i++)
    {
        if(str[i] == c)
        {
            // Move all the char following the char "c" by one to the left.
            strncpy(&str[i],&str[i+1],len-i);
        }
    }
}



void livrerFichierCommande( char * commande )
{
	char * cmd	= strtok(commande, ",");
	char * usager = strtok(NULL, ",");
	char * fichier	= strtok(NULL, ",");
	char * desire	= strtok(NULL, ",");
	
	printf("%s - %s - %s - %s\n", cmd, usager, fichier, desire);
	
	char source[ (int)strlen(rep_client) + (int)strlen(usager) + (int)strlen(fichier) + 4 ];
	strcpy(source, rep_client);
	strcat(source, usager);
	strcat(source, fichier);
	strcat(source, ".txt");
	
	char destinationClient[ (int)strlen(rep_client) + (int)strlen(usager) + (int)strlen(fichier) + 8 ];
	strcpy(destinationClient, rep_server);
	strcat(destinationClient, usager);
	strcat(destinationClient, fichier);
	strcat(destinationClient, "_res.txt");
	
	char destinationServer[ (int)strlen(rep_server) + (int)strlen(usager) + (int)strlen(fichier) + 8 ];
	strcpy(destinationServer, rep_server);
	strcat(destinationServer, usager);
	strcat(destinationServer, fichier);
	strcat(destinationServer, "_res.txt");
	
	if (fichierExiste(source) == 1)
	{
		if (strcmp(desire, "oui") == 0)
		{
			printf("Commande Is OK");
			strcpy(commande, "OK");
	  		if (fichierExiste(destinationClient) == 1)
			{
				remove(destinationClient);
			}
		}
		else
		{
			if (fichierExiste(destinationServer) == 1)
			{
				remove(destinationServer);
			}
		}
		
	  	FILE * file = fopen (source, "rt");
	  	char ligne[MAX_BUF_SIZE];
	  	
   		while(fgets(ligne, MAX_BUF_SIZE, file) != NULL)
  		{
  			removeCharFromString('\r', ligne);
  			removeCharFromString('\n', ligne);
  			strcat(ligne, " >> ");
  			printf("1");
  			if (strcmp(desire, "oui") == 0)
			{
				printf("2");
				strcat(ligne, destinationClient);
				printf("3");
			}
			else
			{
				printf("4");
				strcat(ligne, destinationServer);
				printf("5");
			}
			printf("6");
		 	system(ligne);
		 	printf("7");
  		}
  		fclose(file);

		if ( !tableauContient(usager) ) {
			tableauAjouter( creerUsager(usager) );
		} else {
			Usager u = tableauElement( tableauPosition(usager) ); 
			ajouterFichier( u ); 
		}
		
  	}
  	else
  	{
  		printf("Ce fichier n'existe pas\n");
  	}
}



void quitter()
{
	if ( remove(np_client_server) != 0 )
	{
		fprintf( stderr, "Erreur lors de la suppression du named pipe np_client_server!\n" );
	}
	else
	{
		printf( "Le named pipe np_client_server a été supprimé!\n" );
	}
			
	if ( remove(np_server_client) != 0 )
	{
		fprintf( stderr, "Erreur lors de la suppression du named pipe np_server_client!\n" );
	}
	else
	{
		printf( "Le named pipe np_server_client a été supprimé!\n" );
	}

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

		switch( buf[0] )
		{
			case '1':
				printf( "%s\n", listerFichier( buf ) );
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

	} while (strcmp(buf, "quitter"));

	quitter();	

	return 0;
}
