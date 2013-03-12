LIBS = -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-system
MODULES = build/ai.o build/client_game_logic.o build/control.o build/server.o build/server_network.o build/client.o build/client_network.o build/graphics.o build/server_game_logic.o

all: build server client

build:
	mkdir -p build

build/%.o: modules/%.cpp button.h resource.h team.h types.h units/*.h modules/*.h
	$(CXX) -c $< -o $@

#server: server.cpp modules/*.cpp
#	g++ -g -lpthread server.cpp modules/*.cpp -o server $(LIBS)

client: client.cpp $(MODULES)
	g++ client.cpp -g -lpthread build/*.o -o client $(LIBS)

server: server.cpp $(MODULES)
	g++ server.cpp -g -lpthread build/*.o -o server $(LIBS)

clean:
	rm -rf server client
