CC=g++ -Wall
CLIB=

network: network.o
	$(CC) -o network network.o

clean:
	rm -f *.o network

network.o:
	$(CC) -c network.c

