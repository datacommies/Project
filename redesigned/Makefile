CFLAGS = -Wall -g
LIBS = -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-system -lfontconfig
MODULES = build/ai.o build/client_game_logic.o build/control.o build/server.o build/server_network.o build/client.o build/client_network.o build/graphics.o build/server_game_logic.o

all: build server client

build:
	mkdir -p build

build/%.o: modules/%.cpp button.h resource.h team.h types.h units/*.h modules/*.h
	$(CXX) $(CFLAGS) -c $< -o $@

client: client.cpp $(MODULES)
	g++ $(CFLAGS) client.cpp -g -lpthread build/*.o -o client $(LIBS)

server: server.cpp $(MODULES)
	g++ $(CFLAGS) server.cpp -g -lpthread build/*.o -o server $(LIBS)

clean:
	rm -rf build
	rm -rf server client
