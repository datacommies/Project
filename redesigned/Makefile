all: server client

server: server.cpp modules/*.cpp
	g++ server.cpp modules/*.cpp -o server

client: client.cpp modules/*.cpp
	g++ client.cpp modules/*.cpp -o client