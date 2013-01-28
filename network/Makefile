CC=g++ -Wall
CLIB=

all: server client

server: server.cpp network.o
	$(CC) server.cpp network.o -lpthread -o server

client: client.cpp network.o
	$(CC) client.cpp network.o -o client

clean:
	rm -f client server *.o

network.o: network.cpp
	$(CC) -c network.cpp
