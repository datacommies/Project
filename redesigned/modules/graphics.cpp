#include "graphics.h"
#include <iostream>

#include <unistd.h>
#include <SFML/Graphics.hpp>

using namespace std;

/* Graphics Thread entry point
 *
 * PRE:     
 * POST:    
 * RETURNS: 
 * NOTES:   Graphics init and main loop  */
void * init (void * in) {
   Graphics* g = (Graphics *)in;
   sf::RenderWindow window(sf::VideoMode(800, 600), "Client");
	
	sf::Font MyFont;
	if (!MyFont.loadFromFile("/usr/share/fonts/dejavu/DejaVuSans.ttf")) {
		cerr << ("error loading font") << endl ;
	}

	while (true) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			/*else if (event.type == sf::Event::MouseButtonPressed){
				sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(window));
				for (size_t i = 0; i < shapes.size(); ++i) {
					if (shapes[i].getGlobalBounds().contains(mouse)) {
					win_proc(1, i);
					}
				}
			}*/
		}
		window.clear();

		if (g->clientGameLogic_.getCurrentState() == LOBBY) {
			sf::Text state("Lobby", MyFont, 20);
			window.draw(state);
		} else if (g->clientGameLogic_.getCurrentState() == IN_GAME) {
			sf::Text state("In Game", MyFont, 20);
			window.draw(state);
		}
		window.display();
	}

}

/* Constructor
 *
 * PRE:     
 * POST:    
 * RETURNS: 
 * NOTES:   Creates a thread and starts running the module */
Graphics::Graphics(ClientGameLogic& clientGameLogic)
   : clientGameLogic_(clientGameLogic) 
{
   pthread_t t;
   pthread_create(&t, NULL, init, (void*)this);
}

/* Draws the HUD.
 *
 * PRE:     
 * POST:    Current HUD is displayed
 * RETURNS: 
 * NOTES:    */
void Graphics::drawHud()
{
}

/* Draws the lobby.
 *
 * PRE:     
 * POST:    Current lobby is displayed
 * RETURNS: 
 * NOTES:    */
void Graphics::drawLobby()
{
}

/* Draws all current units.
 *
 * PRE:     
 * POST:    All current units are displayed
 * RETURNS: 
 * NOTES:    */
void Graphics::drawUnits()
{
}

/* Draws the map
 *
 * PRE:     
 * POST:    The map is displayed
 * RETURNS: 
 * NOTES:    */
void Graphics::drawMap()
{
}