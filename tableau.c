
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "tableau.h"
#include "usager.h"


#define MAX_ELEMS 1000
static int nbrElements = 0;
static void * tableau[MAX_ELEMS];



void tableauAjouter( void * elem ) {

	assert (elem != NULL && "usager doit être valide (pointeur non NULL)");

	tableau[nbrElements] = elem;
	nbrElements++;
}



int tableauTaille() {

	return nbrElements;
}



int tableauContient( const char * nom ) {

	int i;
	for ( i=0; i < nbrElements; i++ ) {
		if ( !strcmp(donnerNom(tableau[i]), nom) )
			return 1;
	}

	return 0;
}



int tableauPosition( const char * nom ) {

	int i;
	for ( i=0; i < nbrElements; i++ ) {
		if ( !strcmp(donnerNom(tableau[i]), nom) )
			return i;
	}

	return -1;
}



void * tableauElement( int position ) {
	
	return tableau[position];
}
