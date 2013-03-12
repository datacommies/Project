LIBS = -lsfml-window-d -lsfml-graphics-d -lsfml-audio-d -lsfml-system-d
MODULES = build/ai.o build/client_game_logic.o build/control.o build/server.o build/server_network.o build/client.o build/client_network.o build/graphics.o build/server_game_logic.o

all: server client

build/%.o: modules/%.cpp
	mkdir -p $(dir $@)
	$(CXX) -c $< -o $@

#server: server.cpp modules/*.cpp
#	g++ -g -lpthread server.cpp modules/*.cpp -o server $(LIBS)

client: client.cpp $(MODULES)
	g++ client.cpp -g -lpthread build/*.o -o client $(LIBS)

server: server.cpp $(MODULES)
	g++ server.cpp -g -lpthread build/*.o -o server $(LIBS)

clean:
	rm -rf server client
