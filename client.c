#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "fullduplex.h"



void envoyerCommande( const char * commande ) {

	printf( "La commande envoyée: %s\n", commande );


	int wrfd, rdfd, numread;
        char rdbuf[MAX_BUF_SIZE];

        //Open the first named pipe for writing
        wrfd = open(np_client_server, O_WRONLY);
        //Write to the pipe
        write(wrfd, commande, strlen(commande));

        //Open the second named pipe for reading
        rdfd = open(np_server_client, O_RDONLY);
        //Read from the pipe
        numread = read(rdfd, rdbuf, MAX_BUF_SIZE);
        rdbuf[numread] = '\0';

        printf( "%s\n", rdbuf );
}



int afficherMenu() {

	printf( "==========\n" );
	printf( "=  MENU  =\n" );
	printf( "==========\n" );
	printf( "1) ListerFichier(Usager)\n" );
	printf( "     lister les fichiers d'un usager sur le serveur\n" );
	printf( "\n" );
	printf( "2) ChercherFichierStocké(Usager, Numéro)\n" );
	printf( "     pour chercher un fichier résultat qui a été sauvé sur le Serveur\n" );
	printf( "\n" );
	printf( "3) AfficherFichierRésultat(Usager, Fichier)\n" );
	printf( "     pour lire le contenu d'un fichier de l'usager\n" );
	printf( "\n" );
	printf( "4) LivrerFichierCommande(Usager, Fichier, Désire(oui/non))\n" );
	printf( "     Envoi d'un fichier de commandes Unix\n" );
	printf( "     oui = résultat retourné dans un fichier et afficher au niveau client\n" );
	printf( "     non = résultat sauvé au niveau du serveur\n" );
	printf( "     La fin de la saisie du message est indiquée par un point au début de la dernière ligne\n" );
	printf( "\n" );
	printf( "5) Quitter le programme\n" );
	printf( "=======================\n" );

	int option;
	do {
		printf( "Saisir votre # option: " );
		scanf( "%d", &option );
	} while( option < 1 || option > 5 );

	printf( "\n" );
	return option;
}



void listerFichier() {

	char usager[50] = {0};

	printf( "Entrer un nom d'usager: " );
	scanf( "%s", usager );

	char commande[ 2 + (int) strlen(usager) ];
	strcpy( commande, "1," );
	strcat( commande, usager );

	envoyerCommande( commande );
}



void chercherFichierStocke() {

	char usager[50] = {0};
	int numero;

	printf( "Entrer un nom d'usager: " );
	scanf( "%s", usager );
	do {
		printf( "Entrer un numéro de fichier: " );
		scanf( "%d", &numero );
	} while( numero < 0 );


	char numero_str[10]; 
	sprintf( numero_str, "%d", numero );
	char commande[ 2 + (int) strlen(usager) + 1 + (int) strlen(numero_str) ];
	strcpy( commande, "2," );
	strcat( commande, usager );
	strcat( commande, "," );
	strcat( commande, numero_str );

	envoyerCommande( commande );
}



void afficherFichierResultat() {

	char usager[50] = {0};
	char fichier[50] = {0};

	printf( "Entrer un nom d'usager: " );
	scanf( "%s", usager );
	printf( "Entrer un nom de fichier: " );
	scanf( "%s", fichier );

	char fichierResultat[ (int) strlen(usager) + (int) strlen(fichier) + 8 ];
	strcpy( fichierResultat, usager );
	strcat( fichierResultat, fichier );
	strcat( fichierResultat, "_res.txt" );

	/* Valider si fichier a déjà été téléchargé */

	/* Afficher le contenu du fichier */
}



void livrerFichierCommande() {

	char usager[50] = {0};
	char fichier[50] = {0};
	char desire[3] = {0};

	printf( "Entrer un nom d'usager: " );
	scanf( "%s", usager );
	printf( "Entrer un nom de fichier: " );
	scanf( "%s", fichier );
	do {
		printf( "Afficher le resultat? (oui/non): " );
		scanf( "%s", desire );
	} while( strcmp(desire, "oui") && strcmp(desire, "non") );

	char commande[ 2 + (int) strlen(usager) + 1 + (int) strlen(fichier) + 1 + (int) strlen(desire) ];
	strcpy( commande, "4," );
	strcat( commande, usager );
	strcat( commande, "," );
	strcat( commande, fichier );
	strcat( commande, "," );
	strcat( commande, desire );

	envoyerCommande( commande );
}



void quitter() {
	envoyerCommande( "quitter" );

	char effacer_rep_client[ 7 + (int) strlen(rep_client) ];
	sprintf( effacer_rep_client, "rm -rf %s", rep_client );
	system( effacer_rep_client );

	rmdir( rep_travail );
}



int main( int argc, char * argv[] ) {

	if ( argc > 1 ) {
		fprintf( stderr, "%s: usage incorrect!\n", argv[0] );
		fprintf( stderr, "Aucun argument permis.\n" );
		return 1;
	}


	mkdir( rep_travail, 0777 );
	mkdir( rep_client, 0777 );
	mkdir( rep_client_fichiers, 0777 );
	mkdir( rep_client_resultats, 0777 );


	int option;
	do {
		option = afficherMenu();

		switch( option ) {
			case 1:
				listerFichier();
				break;
			case 2:
				chercherFichierStocke();
				break;
			case 3:
				afficherFichierResultat();
				break;
			case 4:
				livrerFichierCommande();
				break;
			case 5:
				quitter();
				break;
		}
	} while( option != 5 );
	
	return 0;
}
