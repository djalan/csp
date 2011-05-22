#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <sys/stat.h>

#include <string.h>

#include "fullduplex.h"


static const char * rep_travail = "/tmp/SIRA15068305";
static const char * rep_client  = "/tmp/SIRA15068305/client";
static const char * rep_client_fichiers  = "/tmp/SIRA15068305/client/fichiers";
static const char * rep_client_resultats  = "/tmp/SIRA15068305/client/resultats";
static const char * rep_server  = "/tmp/SIRA15068305/server";



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

	return option;
}



void ListerFichier() {}
void ChercherFichierStocke() {}
void AfficherFichierResultat() {}
void LivrerFichierCommande() {}



void Quitter() {
	rmdir( rep_client_resultats );
	rmdir( rep_server );
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
				ListerFichier();
				break;
			case 2:
				ChercherFichierStocke();
				break;
			case 3:
				AfficherFichierResultat();
				break;
			case 4:
				LivrerFichierCommande();
				break;
			case 5:
				Quitter();
				break;
		}
	} while( option != 5 );
	
	return 0;
}
