CFLAGS = -Wall -W -ansi -pedantic -g

all : server client

server : server.cpp net.o
	g++ $(CFLAGS) server.cpp net.o -lpthread -o server

client : client.cpp net.o client-graphics.cpp
	g++ $(CFLAGS) client.cpp client-graphics.cpp net.o -o client -lsfml-system -lsfml-graphics -lfontconfig

net.o : net.cpp
	g++ $(CFLAGS) -c net.cpp

clean :
	rm -f client server *.o
