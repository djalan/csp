#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "fichier.h"



//http://www.java2s.com/Code/C/File/Copyafile.htm
int copierFichier( const char * source, const char * destination )
{
	FILE *from, *to;
	char ch;

	//ouvrir la source
	if((from = fopen(source, "rb"))==NULL)
	{
		printf("Impossible d'ouvrir le fichier source!\n");
		return 1;
	}

	//ouvrir la destination
	if((to = fopen(destination, "wb"))==NULL)
	{
		printf("Impossible d'ouvrir le fichier destination!\n");
		return 2;
	}

	//copier le fichier
	while(!feof(from))
	{
		ch = fgetc(from);
		if(ferror(from))
		{
			printf("Erreur lors de la lecture du fichier source!\n");
			return 3;
		}
		if(!feof(from)) fputc(ch, to);
		if(ferror(to))
		{
			printf("Erreur lors de l'ecriture du fichier destination!\n");
			return 4;
		}
	}

	if(fclose(from)==EOF)
	{
		printf("Erreur lors de la fermeture du fichier source!\n");
		return 5;
	}

	if(fclose(to)==EOF)
	{
		printf("Erreur lors de la fermeture du fichier destination!\n");
		return 6;
	}

	return 0;
}



int fichierExiste(const char * fichier)
{

	struct stat st;
	stat( fichier, &st );

	FILE * file = fopen (fichier,"rb");
	if ( file != NULL && S_ISREG(st.st_mode) )
	{
		fclose (file);
		return 1;
	}
	else
	{
		return 0;
	}
}
