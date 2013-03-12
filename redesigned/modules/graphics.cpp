#include "graphics.h"
#include <iostream>

#include <unistd.h>
#include <SFML/Graphics.hpp>

using namespace std;


#define ID_START 123
#define ID_QUIT 124


/* Graphics Thread entry point
 *
 * PRE:     
 * POST:    Window closed: no more graphics thread necessary.
 * RETURNS: nothing
 * NOTES:   Graphics init and main loop  */
void * init (void * in) {
   Graphics* g = (Graphics *)in;
   sf::RenderWindow window(sf::VideoMode(800, 600), "Client");
   g->window = &window;

	if (!g->font.loadFromFile("/usr/share/fonts/truetype/ttf-dejavu/DejaVuSans.ttf")) {
		cerr << ("error loading font") << endl ;
	}
	
	Button a(ID_START, sf::Vector2f(200,300), sf::Vector2f(300,50), g->font, "Start Game");
	Button b(321, 	   sf::Vector2f(200,400), sf::Vector2f(300,50), g->font, "Press This button for fun");
	Button c(ID_QUIT,  sf::Vector2f(200,500), sf::Vector2f(300,50), g->font, "Quit");

	g->clientGameLogic_.UIElements.insert(a);
	g->clientGameLogic_.UIElements.insert(b);
	g->clientGameLogic_.UIElements.insert(c);

	g->map_bg.loadFromFile("images/map.png");
	g->map.setTexture(g->map_bg);

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
						if (button->id == ID_START){
							g->clientGameLogic_.start();
							g->clientGameLogic_.UIElements.clear();
							break;
						} else if (button->id == ID_QUIT) {
							exit(0);
						}
						//AddNewCalledButton(button->id);
					}
				}
			}
		}
		window.clear();

		if (g->clientGameLogic_.getCurrentState() == LOBBY) {
			g->drawLobby(window);
		} else if (g->clientGameLogic_.getCurrentState() == IN_GAME) {
			g->drawUnits(window);
			g->drawMap(window);
			
			sf::Text state("In Game", g->font, 20);
			window.draw(state);
		}

		for (std::set<Button>::iterator button = g->clientGameLogic_.UIElements.begin(); button != g->clientGameLogic_.UIElements.end(); ++button)
		{
			Button b = *button;
			b.draw(window);
		}

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
	sf::Text title("Child's Play", font, 71);
	title.setPosition(sf::Vector2f(200, 0));
	window.draw(title);
}

/* Draws all current units.
 *
 * PRE:     
 * POST:    All current units are displayed
 * RETURNS: 
 * NOTES:    */
void Graphics::drawUnits(sf::RenderWindow& window)
{

	for (std::vector<CLIENT_UNIT>::iterator unit = clientGameLogic_.units.begin(); unit != clientGameLogic_.units.end(); ++unit)
	{
		//window.draw(button->rect);
	}
}

/* Draws the map
 *
 * PRE:     
 * POST:    The map is displayed
 * RETURNS: 
 * NOTES:    */
void Graphics::drawMap(sf::RenderWindow& window)
{
	window.draw(map);
}