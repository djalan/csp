/*
Classe:         fichier.h

Description:    Bibliotheque de fonctions pour traiter des fichiers

Auteurs:        Alain Sirois      SIRA15068305
                Philippe Mercure  MERC
                
Date:           1er juin 2011
         
Cours:          INF5270
Groupe:         30
Travail:        TP1
Professeur:     Ammar Hamad
*/



/*
Fonction pour copier un fichier d'une source vers une destination
source: http://www.java2s.com/Code/C/File/Copyafile.htm
*/
int copierFichier( const char * source, const char * destination );



/*
Valide si un fichier existe et qu'il n'est pas un repertoire
*/
int fichierExiste(const char * fichier);
