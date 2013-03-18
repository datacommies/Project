CFLAGS = -Wall -g
LIBS = -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-system -lfontconfig -lsfgui
MODULES = build/modules/ai.o build/modules/client_game_logic.o build/modules/control.o build/modules/server.o build/modules/server_network.o build/modules/client.o build/modules/client_network.o build/modules/graphics.o build/modules/server_game_logic.o build/units/creep.o build/units/mobile_unit.o build/units/unit.o build/units/castle.o build/units/tower.o build/units/splash_tower.o build/units/electro_tower.o build/units/AiController.o build/control/Control.o build/control/ControlState.o build/control/ControlManager.o build/control/Controller.o build/control/BuildController.o build/control/ControlEvents.o


all: build server client

build:
	mkdir -p build/modules
	mkdir -p build/units
	mkdir -p build/control

build/modules/%.o: modules/%.cpp button.h resource.h team.h types.h units/*.h modules/*.h control/*.h
	$(CXX) $(CFLAGS) -c $< -o $@

build/units/%.o: units/%.cpp button.h resource.h team.h types.h units/*.h modules/*.h control/*.h
	$(CXX) $(CFLAGS) -c $< -o $@

build/control/%.o: control/%.cpp button.h resource.h team.h types.h units/*.h modules/*.h control/*.h
	$(CXX) $(CFLAGS) -c $< -o $@
	
client: client.cpp $(MODULES)
	g++ $(CFLAGS) client.cpp -g -lpthread $(MODULES) -o client $(LIBS)

server: server.cpp $(MODULES)
	g++ $(CFLAGS) server.cpp -g -lpthread $(MODULES) -o server $(LIBS)

clean:
	rm -rf build
	rm -rf server client
