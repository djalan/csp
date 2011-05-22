#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>



static const char * rep_travail = "/tmp/SIRA15068305";
static const char * rep_client  = "/tmp/SIRA15068305/client";
static const char * rep_server  = "/tmp/SIRA15068305/server";




int main( int argc, char * argv[] ) {


	if ( argc > 1 ) {
		fprintf( stderr, "%s: usage incorrect!\n", argv[0] );
		fprintf( stderr, "Aucun argument permis.\n" );
		return 1;
	}

	


	printf( "server\n" );
	return 0;
} 
