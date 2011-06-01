/*
Classe:         server.c

Description:    Programme serveur qui attend des commandes du client

Auteurs:        Alain Sirois      SIRA15068305
                Philippe Mercure  MERC
                
Date:           1er juin 2011
         
Cours:          INF5270
Groupe:         30
Travail:        TP1
Professeur:     Ammar Hamad
*/



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
#include "config.h"



/*
Option qui permet de lister les fichiers resultats d'un usager.
On construit une chaine de caracteres contenant la reponse et
elle est retournee au client et afficher du cote client
*/
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

	    char ext[] = "_res.txt";
	    //int taille_rep;
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



/*
Option pour downloader un fichier resultat du serveur vers le client.
On retourne un statut au client dans une chaine de caracteres.
*/
char * chercherFichierStocke( char * commande )
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

	if ( copierFichier( source, destination) == 0 ) {
	   return "Le fichier a ete telecharge!\n";
    } else {
        return "Le fichier n'existe pas. Le telechargement a echoue!\n";
    }
}



/*
Fonction qui permet d'enlever un caractere d'une chaine.
On decale le reste de la chaine
*/
void removeCharFromString(char c, char *str)
{
    int i=0;
    int len = strlen(str)+1;

    for(i=0; i<len; i++)
    {
        if(str[i] == c)
        {
            // On deplace vers la gauche le caractere qui suit le char 'c'
            strncpy(&str[i],&str[i+1],len-i);
        }
    }
}



/*
Option qui permet d'uploader le fichier commande du client vers le serveur.
On decide si on envoit la reponse tout de suite au client pour l'afficher ou
si alors on sauve la reponse dans un fichier resultat du cote serveur
*/
char * livrerFichierCommande( char * commande )
{
	char * cmd	= strtok(commande, ",");
	char * usager   = strtok(NULL, ",");
	char * fichier	= strtok(NULL, ",");
	char * desire	= strtok(NULL, ",");
	
	//printf("%s - %s - %s - %s\n", cmd, usager, fichier, desire);
	

	if (fichierExiste(fichier) == 1)
	{
	    int nbrFic;
	    char * destinationServer;
		if (!strcmp(desire, "non"))
		{
		    
			if ( !tableauContient(usager) ) {
    			tableauAjouter( creerUsager(usager) );
    		} else {
    			ajouterFichier( tableauElement(tableauPosition(usager)) ); 
    		}
    		
    	
  		 	char temp_str[5];
  		 	nbrFic = donnerNbrFichiers( tableauElement(tableauPosition(usager)) );
		    sprintf( temp_str, "%d", nbrFic );
       		destinationServer = malloc ( sizeof(char) * ((int)strlen(rep_server) + (int)strlen(usager) + (int)strlen(temp_str) + 8) );
        	sprintf( destinationServer, "%s%s%d_res.txt", rep_server, usager, nbrFic );
		}
		
	  	FILE * file = fopen (fichier, "rt");
	  	char ligne[MAX_BUF_SIZE];
	  	
   		while(fgets(ligne, MAX_BUF_SIZE, file) != NULL)
  		{
  			removeCharFromString('\r', ligne);
  			removeCharFromString('\n', ligne);
  			strcat(ligne, " >> ");
  			if (!strcmp(desire, "non"))
			{
				strcat(ligne, destinationServer);
			}
			else
			{
				strcat(ligne, fichier_client_res);
			}
		 	system(ligne);
  		}
  		fclose(file);
  		
    	if (!strcmp(desire, "non"))
    	{
    		char temp_str[5];
    		sprintf( temp_str, "%d", nbrFic );
    		char message[] = "Votre numero de fichier est: ";
    		char * reponse = malloc ( sizeof(char) * ((int)strlen(message) + (int)strlen(temp_str) + 1) );
    		sprintf( reponse, "%s%d\n", message, nbrFic );
       		return reponse;
        } else {
            return "Okay, afficher resultat";
        }
  	}
  	else
  	{
  	     return "Ce fichier n'existe pas\n";
  	}
}



/*
Fonction pour faire le menage du cote serveur une fois que celui-ci se ferme.
La commande de fermeture est envoyee par le client.
*/
void quitter()
{
	if ( remove(np_client_server) != 0 )
	{
		fprintf( stderr, "Erreur lors de la suppression du named pipe np_client_server!\n" );
	}
	else
	{
		printf( "Le named pipe np_client_server a ete supprime!\n" );
	}
			
	if ( remove(np_server_client) != 0 )
	{
		fprintf( stderr, "Erreur lors de la suppression du named pipe np_server_client!\n" );
	}
	else
	{
		printf( "Le named pipe np_server_client a ete supprime!\n" );
	}

	char effacer_rep_server[ 7 + (int) strlen(rep_server) ];
	sprintf( effacer_rep_server, "rm -rf %s", rep_server );
	system( effacer_rep_server );

	rmdir( rep_travail );
}



/*
Le "main".
Reception et envoie des commandes/reponses avec des named pipes
Traitement des options disponibles.
*/
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
				sprintf( buf, "%s", listerFichier( buf ) );
				break;
			case '2':
				sprintf( buf, "%s", chercherFichierStocke( buf ) );
				break;
			case '4':
				sprintf( buf, "%s", livrerFichierCommande( buf ) );
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
