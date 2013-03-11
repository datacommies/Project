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

/*#include "graphics.h"
void update (sf::RenderWindow& window, sf::Clock& sclock) {
    sf::Time elapsed = sclock.restart();
    ((void) elapsed); // silence warning for now.
    
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        else if (event.type == sf::Event::MouseButtonPressed){
            sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(window));
            for (size_t i = 0; i < shapes.size(); ++i) {
                if (shapes[i].getGlobalBounds().contains(mouse)) {
                    win_proc(1, i);
                }
            }
        }
    }

    sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(window));
    for (size_t i = 0; i < shapes.size(); ++i) {
        if (shapes[i].getGlobalBounds().contains(mouse)) {
            shapes[i].setOutlineColor(sf::Color(255, 0,0));
        } else {
            shapes[i].setOutlineColor(sf::Color::White);
        }
    }

    window.clear();

    size_t i;

    // There can only be at most 5 players in a team, and we draw all of them even if the slot is empty.
    for (i = 0; i < 5; ++i) {
        draw_slot(window, COLUMN_RIGHT, i, team_r[i]);
        draw_slot(window, COLUMN_LEFT, i, team_l[i]);
    }
    
    // There is an unknown amount of players can that can be waiting, draw all of them.
    for (i = 0; i < waiting.size(); ++i) {
        draw_slot(window, COLUMN_MIDDLE, i, waiting[i]);
    }

    for (i = 0; i < shapes.size(); ++i) {
        window.draw(shapes[i]);
    }

    for (i = 0; i < lables.size(); ++i) {
        window.draw(lables[i]);
    }

    draw_chat(window);

    window.display();
}*/


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