CC = gcc
CFLAGS = -W -Wall

all:		client server test

client:		client.o
server:		server.o
test:		test.o usager.o tableau.o

client.o:	client.c
server.o:	server.c
usager.o:	usager.c usager.h
test.o:		test.c usager.h tableau.h
tableau.o:  	tableau.c tableau.h


clean:
	rm *.o *~ client server test a.out
