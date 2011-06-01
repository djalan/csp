/*
Classe:         tableau.h

Description:    Tableau implante sous forme de ArrayList avec quelques fonctions

Auteurs:        Alain Sirois      SIRA15068305
                Philippe Mercure  MERC
                
Date:           1er juin 2011
         
Cours:          INF5270
Groupe:         30
Travail:        TP1
Professeur:     Ammar Hamad
*/



/*
Ajouter un element dans le tableau
*/
void tableauAjouter( void * );


/*
Retourner la taille du tableau
*/
int tableauTaille();


/*
Retourner si le tableau contient un certain nom d'usager
*/
int tableauContient( const char * nom );


/*
Retourner la position d'un usager dans le tableau selon son nom
*/
int tableauPosition( const char * nom );


/*
Retourner l'element contenu a une certaine position dans le tableau
*/
void * tableauElement( int position );
