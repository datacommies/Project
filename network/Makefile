CC=g++ -Wall
CLIB=

network: network.o server.o client.o
	$(CC) -o network network.o server.o client.o

clean:
	rm -f *.o network

network.o:
	$(CC) -c network.c

server.o:
	$(CC) -c server.cpp

client.o:
	$(CC) -c client.cpp
