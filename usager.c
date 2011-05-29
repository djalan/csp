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



Usager creerUsager( const char * nom ) {

	Usager monUsager = (Usager) malloc (sizeof(s_usager));
	if ( monUsager == NULL )
     		return NULL;
	
    monUsager->nom = malloc ( (int) strlen(nom) * sizeof(char) );
	strcpy( monUsager->nom, nom );
	
	monUsager->nbrFichiers = 1;

	return monUsager;
}



char * donnerNom( Usager usager ) {

	assert (usager != NULL && "usager doit être valide (pointeur non NULL)");

	return usager->nom;
}



int donnerNbrFichiers( Usager usager ) {

	assert (usager != NULL && "usager doit être valide (pointeur non NULL)");

	return usager->nbrFichiers;
}



void ajouterFichier( Usager usager ) {

	assert (usager != NULL && "usager doit être valide (pointeur non NULL)");

	usager->nbrFichiers = usager->nbrFichiers + 1;
}
