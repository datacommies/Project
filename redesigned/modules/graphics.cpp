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
   g->window = &window;

	if (!g->font.loadFromFile("/usr/share/fonts/truetype/ttf-dejavu/DejaVuSans.ttf")) {
		cerr << ("error loading font") << endl ;
	}
	
	Button a;
	a.id = 1373;
	a.rect.setPosition (sf::Vector2f(0,300));
	a.rect.setSize (sf::Vector2f(100,100));
	g->clientGameLogic_.UIElements.insert(a);
	
	a.id = 100;
	a.rect.setPosition (sf::Vector2f(200,300));
	a.rect.setSize (sf::Vector2f(100,100));
	g->clientGameLogic_.UIElements.insert(a);



	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonPressed){
				sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(window));
				for (std::set<Button>::iterator button = g->clientGameLogic_.UIElements.begin(); button != g->clientGameLogic_.UIElements.end(); ++button) {
					if (button->rect.getGlobalBounds().contains(mouse)) {
						cout << "Button ID:" << button->id << endl;
						//AddNewCalledButton(button->id);
					}
				}
			}
		}
		window.clear();

		if (g->clientGameLogic_.getCurrentState() == LOBBY) {
			g->drawLobby(window);
		} else if (g->clientGameLogic_.getCurrentState() == IN_GAME) {
			sf::Text state("In Game", g->font, 20);
			window.draw(state);
		}

		for (std::set<Button>::iterator button = g->clientGameLogic_.UIElements.begin(); button != g->clientGameLogic_.UIElements.end(); ++button)
		{
			sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(window));
			
			sf::RectangleShape rs = button->rect;
			rs.setOutlineThickness(2.0f);

			if (rs.getGlobalBounds().contains(mouse))
				rs.setOutlineColor(sf::Color(100, 100, 100));
			window.draw(rs);
		}

		/*for (std::vector<CLIENT_UNIT>::iterator unit = g->clientGameLogic_.units.begin(); unit != g->clientGameLogic_.units.end(); ++unit)
		{
			//window.draw(button->rect);
		}*/
		window.display();
	}

	return NULL;
}

/* Constructor
 *
 * PRE:     
 * POST:    
 * RETURNS: 
 * NOTES:   Creates a thread and starts running the module */
Graphics::Graphics(ClientGameLogic& clientGameLogic)
   : clientGameLogic_(clientGameLogic), window(NULL)
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
void Graphics::drawHud(sf::RenderWindow& window)
{
}

/* Draws the lobby.
 *
 * PRE:     
 * POST:    Current lobby is displayed
 * RETURNS: 
 * NOTES:    */
void Graphics::drawLobby(sf::RenderWindow& window)
{
	sf::Text state("Lobby", font, 20);
	window.draw(state);
}

/* Draws all current units.
 *
 * PRE:     
 * POST:    All current units are displayed
 * RETURNS: 
 * NOTES:    */
void Graphics::drawUnits(sf::RenderWindow& window)
{
}

/* Draws the map
 *
 * PRE:     
 * POST:    The map is displayed
 * RETURNS: 
 * NOTES:    */
void Graphics::drawMap(sf::RenderWindow& window)
{
}