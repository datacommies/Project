all : server client
server : server.cpp net.o
	g++ server.cpp net.o -lpthread -o server

client : client.cpp net.o
	g++ client.cpp net.o -o client

clean :
	rm -f client server *.o

net.o : net.cpp
	g++ -c net.cpp
