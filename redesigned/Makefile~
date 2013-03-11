all: server client

LIBS = -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-system

server: server.cpp modules/*.cpp
	g++ -g server.cpp modules/*.cpp -o server $(LIBS)

client: client.cpp modules/*.cpp
	g++ -g client.cpp modules/*.cpp -o client $(LIBS)
