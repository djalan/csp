CC = gcc
CFLAGS = -W -Wall

all:		client server client2

client:		client.o
server:		server.o	
client2:		client2.o

client.o:	client.c
server.o:	server.c
client2.o:	client2.c

clean:
	rm *.o *~ client server client2