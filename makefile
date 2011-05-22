CC = gcc
CFLAGS = -W -Wall

all:		client server

client:		client.o
server:		server.o	

client.o:	client.c
server.o:	server.c

clean:
	rm *.o *~ client server
