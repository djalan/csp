/*
Classe:         usager.h

Description:    Structure objet pour definir un usager et ses attributs

Auteurs:        Alain Sirois      SIRA15068305
                Philippe Mercure  MERC
                
Date:           1er juin 2011
         
Cours:          INF5270
Groupe:         30
Travail:        TP1
Professeur:     Ammar Hamad
*/



typedef struct usager * Usager;



/*
Creer un usager et initialiser son nombre de fichier resultat a 1
*/
Usager creerUsager( const char * nom );


/*
Retourner le nom d'un Usager
*/
char * donnerNom( Usager usager );


/*
Retourner le nombre de fichiers resultats d'un usager
*/
int donnerNbrFichiers( Usager usager );


/*
Incremente de 1 le nombre de fichier de l'usager
*/
void ajouterFichier( Usager usager );
