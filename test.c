#include <stdio.h>
#include <stdlib.h>
#include "tableau.h"
#include "usager.h"


int main () {


	Usager alain = creerUsager( "Alain" );
	printf( "%s\n", donnerNom(alain) );
	printf( "%d\n", donnerNbrFichiers(alain) );
	ajouterFichier(alain);
	printf( "%d\n", donnerNbrFichiers(alain) );
	
	
	Usager denis = creerUsager( "Denis" );
	printf( "%s\n", donnerNom(denis) );
	printf( "%d\n", donnerNbrFichiers(denis) );
	ajouterFichier(denis);
	ajouterFichier(denis);


	printf( "Taille: %d\n", tableauTaille() );
	tableauAjouter( alain );
	printf( "tableau: %s\n", donnerNom(tableauElement(0)) );
	printf( "tableau: %d\n", donnerNbrFichiers(tableauElement(0)) );

	printf( "Taille: %d\n", tableauTaille() );

	tableauAjouter( denis );

	printf( "Taille: %d\n", tableauTaille() );

	Usager user;
	if ( tableauContient("Denis") ) {
		user = tableauElement( tableauPosition("Denis") );
	}

	printf( "tableau: %s\n", donnerNom(user) );
	printf( "tableau: %d\n", donnerNbrFichiers(user) );
	
	
	return 0;
}
