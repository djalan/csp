typedef struct usager * Usager;



Usager creerUsager( const char * nom );
char * donnerNom( Usager usager );
int donnerNbrFichiers( Usager usager );
void ajouterFichier( Usager usager );
