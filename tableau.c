/*
Classe:         tableau.c

Description:    Tableau implante sous forme de ArrayList avec quelques fonctions

Auteurs:        Alain Sirois      SIRA15068305
                Philippe Mercure  MERP27078708
                
Date:           1er juin 2011
         
Cours:          INF5270
Groupe:         30
Travail:        TP1
Professeur:     Ammar Hamad
*/



#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "tableau.h"
#include "usager.h"


#define MAX_ELEMS 1000
static int nbrElements = 0;
static void * tableau[MAX_ELEMS];



/*
Ajouter un element dans le tableau
*/
void tableauAjouter( void * elem ) {

	assert (elem != NULL && "usager doit être valide (pointeur non NULL)");

	tableau[nbrElements] = elem;
	nbrElements++;
}



/*
Retourner la taille du tableau
*/
int tableauTaille() {

	return nbrElements;
}



/*
Retourner si le tableau contient un certain nom d'usager
*/
int tableauContient( const char * nom ) {

	int i;
	for ( i=0; i < nbrElements; i++ ) {
		if ( !strcmp(donnerNom(tableau[i]), nom) )
			return 1;
	}

	return 0;
}



/*
Retourner la position d'un usager dans le tableau selon son nom
*/
int tableauPosition( const char * nom ) {

	int i;
	for ( i=0; i < nbrElements; i++ ) {
		if ( !strcmp(donnerNom(tableau[i]), nom) )
			return i;
	}

	return -1;
}



/*
Retourner l'element contenu a une certaine position dans le tableau
*/
void * tableauElement( int position ) {
	
	return tableau[position];
}
