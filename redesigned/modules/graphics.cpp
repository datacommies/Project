#include "graphics.h"
#include <fontconfig/fontconfig.h>
#include <iostream>

#include <unistd.h>
#include <SFML/Graphics.hpp>

using namespace std;


#define ID_START 123
#define ID_QUIT 124

// Pick default system font with font config.
bool find_font (char ** path) {
    FcResult result;
    FcPattern* pat = FcPatternCreate();
    //pat = FcNameParse ((FcChar8 *) ""); //specify font family?
    FcConfigSubstitute (0, pat, FcMatchPattern);
    FcDefaultSubstitute (pat);
    FcPattern * match =  FcFontMatch(NULL, pat, &result);
    match = FcFontMatch (0, pat, &result);
    return (FcPatternGetString(match, FC_FILE, 0, (FcChar8**)path) == FcResultMatch);
}


/* Graphics Thread entry point
 *
 * PRE:     
 * POST:    Window closed: no more graphics thread necessary.
 * RETURNS: nothing
 * NOTES:   Graphics init and main loop  
*/
void * init (void * in) {
	// Set g to current instance of Graphics object.
	Graphics* g = (Graphics *)in;

	// Create window for client.
	sf::RenderWindow window(sf::VideoMode(800, 600), "Client");
	g->window = &window;
	
	// Load font for game.
	char * font_path;
	find_font(&font_path);

    if (!g->font.loadFromFile(font_path)) {
		cerr << ("error loading font") << endl;
		exit(0);
	}
	
	// Create buttons for the menu screen and add them to the list of UI elements.
	Button a(ID_START, sf::Vector2f(250,300), sf::Vector2f(300,50), g->font, "                Start Game");
	Button b(321, 	   sf::Vector2f(250,400), sf::Vector2f(300,50), g->font, "     Press this button for fun");
	Button c(ID_QUIT,  sf::Vector2f(250,500), sf::Vector2f(300,50), g->font, "                     Quit");

	g->clientGameLogic_.UIElements.insert(a);
	g->clientGameLogic_.UIElements.insert(b);
	g->clientGameLogic_.UIElements.insert(c);

	// Load the map texture.
	g->map_bg.loadFromFile("images/map.png");
	g->map.setTexture(g->map_bg);

	// Main loop for the graphics thread.
	while (window.isOpen()) {
		sf::Event event;

		// Check to see if there is an event on the stack. If so, enter the while loop (pollEvent call doesn't block).
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			// If a mouse button was pressed, find out where we clicked.
			else if (event.type == sf::Event::MouseButtonPressed){
				sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(window));
				// Iterate through the buttons and check each button to see if we clicked within in.
				for (std::set<Button>::iterator button = g->clientGameLogic_.UIElements.begin(); button != g->clientGameLogic_.UIElements.end(); ++button) {
					// If we clicked within the button, check to see which button it was by ID.
					if (button->rect.getGlobalBounds().contains(mouse)) {
						// Start button.
						if (button->id == ID_START){
							g->initGameControls();
							g->clientGameLogic_.start();
							break; // Must break out now, initGameControls invalidates the iterators.
						}
						// Quit button.
						else if (button->id == ID_QUIT) {
							exit(0);
						}
						//AddNewCalledButton(button->id);
					}
				}
			}
		}

		window.clear();

		// Check to see which state the game is in and act accordingly.
		if (g->clientGameLogic_.getCurrentState() == LOBBY) {
			g->drawLobby(window);
		}
		else if (g->clientGameLogic_.getCurrentState() == IN_GAME) {
			g->drawUnits(window);
			g->drawMap(window);
			g->drawHud(window, g);
			sf::Text state("In Game", g->font, 20);
			window.draw(state);

		}

		// Iterate through the buttons and draw them one by one.
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
   : window(NULL), clientGameLogic_(clientGameLogic)
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
void Graphics::drawHud(sf::RenderWindow& window, Graphics* g)
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

/* Init Game controls
 *
 * PRE:     
 * POST:    
 * RETURNS: 
 * NOTES:   Clears and Initializes the set of UIElements for In-game controls */
void Graphics::initGameControls () {
	clientGameLogic_.UIElements.clear();
	Button a(999,sf::Vector2f(020,570), sf::Vector2f(100,25), font, "Tower1");
	Button b(998,sf::Vector2f(130,570), sf::Vector2f(100,25), font, "Tower2");
	Button c(997,sf::Vector2f(240,570), sf::Vector2f(100,25), font, "Tower3");
	Button d(996,sf::Vector2f(350,570), sf::Vector2f(100,25), font, "Creep1");
	Button e(995,sf::Vector2f(460,570), sf::Vector2f(100,25), font, "Creep2");
	Button f(994,sf::Vector2f(570,570), sf::Vector2f(100,25), font, "Creep3");
	Button h(ID_QUIT,sf::Vector2f(680,570), sf::Vector2f(100,25),  font, "Quit");
	
	a.rect.setFillColor(sf::Color(255, 0, 0));
	
	clientGameLogic_.UIElements.insert(a);
	clientGameLogic_.UIElements.insert(b);
	clientGameLogic_.UIElements.insert(c);
	clientGameLogic_.UIElements.insert(d);
	clientGameLogic_.UIElements.insert(e);
	clientGameLogic_.UIElements.insert(f);
	clientGameLogic_.UIElements.insert(h);
}