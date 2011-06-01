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
#include "fichier.h"
#include "config.h"



void afficherFichier(const char * nomFic)
{

	//Valider si fichier a deja ete telecharge
	if (fichierExiste(nomFic) == 1)
	{	
		//Afficher le contenu du fichier
	   	char line[MAX_BUF_SIZE];
   		FILE * file = fopen (nomFic, "rt");

   		while(fgets(line, MAX_BUF_SIZE, file) != NULL)
   		{
		 	printf("%s", line);
   		}
   	    fclose(file);
    }
    else
    {
        printf("Ce fichier n'existe pas\n");
    }
}



void afficherFichierResultat(const int retourServeur)
{
	if (retourServeur == 0)
	{
    	char usager[256];
    	char fichier[256];
    	
		printf("Entrer un nom d'usager: ");
		scanf("%s", usager);
		printf("Entrer un nom de fichier: ");
		scanf("%s", fichier);

    	char fichierResultat[ (int) strlen(rep_client) + (int) strlen(fichier)];
    	strcpy(fichierResultat, rep_client);
    	strcat(fichierResultat, fichier);
    	
    	afficherFichier(fichierResultat);
	}
	else
	{
	    afficherFichier(fichier_client_res);
	}
}



void envoyerCommande(const char * commande)
{
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

	if (!strcmp(rdbuf, "Okay, afficher resultat"))
	{
		afficherFichierResultat(1);
	}
	else
	{
		printf("%s\n", rdbuf);
	}
}



int afficherMenu()
{
	printf("==========\n");
	printf("=  MENU  =\n");
	printf("==========\n");
	printf("1) ListerFichier(Usager)\n");
	printf("     lister les fichiers d'un usager sur le serveur\n");
	printf("\n");
	printf("2) ChercherFichierStocke(Usager, Numero)\n");
	printf("     pour chercher un fichier resultat qui a ete sauve sur le Serveur\n");
	printf("\n");
	printf("3) AfficherFichierResultat(Usager, Fichier)\n");
	printf("     pour lire le contenu d'un fichier de l'usager\n");
	printf("\n");
	printf("4) LivrerFichierCommande(Usager, Fichier, Desire(oui/non))\n");
	printf("     Envoi d'un fichier de commandes Unix\n");
	printf("     oui = resultat retourne dans un fichier et afficher au niveau client\n");
	printf("     non = resultat sauve au niveau du serveur\n");
	printf("\n");
	printf("5) Quitter le programme\n");
	printf("=======================\n");

	int option;
	do
	{
		printf("Saisir votre # option: ");
		scanf("%d", &option);
	} while(option < 1 || option > 5);

	printf("\n");
	return option;
}



void listerFichier()
{
	char usager[50] = {0};

	printf("Entrer un nom d'usager: ");
	scanf("%s", usager);

	char commande[ 2 + (int) strlen(usager) ];
	strcpy(commande, "1,");
	strcat(commande, usager);

	envoyerCommande(commande);
}



int validerNumero( const char * chaine ) {

        int taille = (int) strlen(chaine);

        int i;
        for ( i=0; i<taille; i++ ) {
                if ( isalpha(chaine[i]) )
                        return 0; // numero non valide
        }
        
        return 1; // numero valide
}



void chercherFichierStocke()
{
        char usager[50];
        char numero[50];

        printf("Entrer un nom d'usager: ");
        scanf("%s", usager);
        do
        {
                printf("Entrer un numero de fichier: ");
                scanf("%s", numero);
        } while( !validerNumero(numero) || atoi(numero) < 1 );

        char commande[ 2 + (int) strlen(usager) + 1 + (int) strlen(numero) ];
        strcpy(commande, "2,");
        strcat(commande, usager);
        strcat(commande, ",");
        strcat(commande, numero);

	envoyerCommande(commande);
}



void livrerFichierCommande()
{
	char desire[3] = {0};
	char usager[256];
	char fichier[256];

	printf("Entrer un nom d'usager: ");
	scanf("%s", usager);
	printf("Entrer un nom de fichier: ");
	scanf("%s", fichier);
	do
	{
		printf("Afficher le resultat? (oui/non): ");
		scanf("%s", desire);
	} while(strcmp(desire, "oui") && strcmp(desire, "non"));

	char commande[ 2 + (int) strlen(usager) + 1 + (int) strlen(fichier) + 1 + (int) strlen(desire) ];
	strcpy(commande, "4,");
	strcat(commande, usager);
	strcat(commande, ",");
	strcat(commande, fichier);
	strcat(commande, ",");
	strcat(commande, desire);
	strcat(commande, "\0");

	envoyerCommande(commande);
}



void quitter()
{
	envoyerCommande("quitter");

	char effacer_rep_client[ 7 + (int) strlen(rep_client) ];
	sprintf(effacer_rep_client, "rm -rf %s", rep_client);
	system(effacer_rep_client);

	rmdir(rep_travail);
}



int main(int argc, char * argv[])
{
	if (argc > 1)
	{
		fprintf(stderr, "%s: usage incorrect!\n", argv[0]);
		fprintf(stderr, "Aucun argument permis.\n");
		return 1;
	}

	mkdir( rep_travail, 0777 );
	mkdir( rep_client, 0777 );

	int option;
	do
	{
		option = afficherMenu();

		switch(option)
		{
			case 1:
				listerFichier();
				break;
			case 2:
				chercherFichierStocke();
				break;
			case 3:
				afficherFichierResultat(0);
				break;
			case 4:
				livrerFichierCommande();
				break;
			case 5:
				quitter();
				break;
		}
		sleep(3); // pause
	} while(option != 5);
	
	return 0;
}
