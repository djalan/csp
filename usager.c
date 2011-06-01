/*
Classe:         usager.c

Description:    Structure objet pour definir un usager et ses attributs

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
#include <assert.h>

#include "usager.h"



struct usager {
	char * nom;
	int nbrFichiers;
};

typedef struct usager s_usager;



/*
Creer un usager et initialiser son nombre de fichier resultat a 1
*/
Usager creerUsager( const char * nom ) {

	Usager monUsager = (Usager) malloc (sizeof(s_usager));
	if ( monUsager == NULL )
     		return NULL;
	
    monUsager->nom = malloc ( (int) strlen(nom) * sizeof(char) );
	strcpy( monUsager->nom, nom );
	
	monUsager->nbrFichiers = 1;

	return monUsager;
}



/*
Retourner le nom d'un Usager
*/
char * donnerNom( Usager usager ) {

	assert (usager != NULL && "usager doit être valide (pointeur non NULL)");

	return usager->nom;
}



/*
Retourner le nombre de fichiers resultats d'un usager
*/
int donnerNbrFichiers( Usager usager ) {

	assert (usager != NULL && "usager doit être valide (pointeur non NULL)");

	return usager->nbrFichiers;
}



/*
Incremente de 1 le nombre de fichier de l'usager
*/
void ajouterFichier( Usager usager ) {

	assert (usager != NULL && "usager doit être valide (pointeur non NULL)");

	usager->nbrFichiers = usager->nbrFichiers + 1;
}
