CC = gcc
CFLAGS = -W -Wall

all:		client server test

client:		client.o fichier.o
server:		server.o fichier.o usager.o tableau.o
test:		test.o usager.o tableau.o

client.o:	client.c fichier.h
server.o:	server.c fichier.h usager.h tableau.h
usager.o:	usager.c usager.h
test.o:		test.c usager.h tableau.h
tableau.o:  	tableau.c tableau.h
fichier.o:	fichier.c fichier.h

clean:
	rm *.o *~ client server test a.out
