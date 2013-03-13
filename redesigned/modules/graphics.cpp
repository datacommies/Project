#include "graphics.h"
#include <fontconfig/fontconfig.h>
#include <iostream>

#include <unistd.h>
#include <SFML/Graphics.hpp>

using namespace std;

#define ID_JOIN 100
#define ID_QUIT 101

sf::Texture creep_tex;
sf::Sprite  creep_sprite;

/* Graphics Thread entry point
 *
 * PRE:     
 * POST:    Window closed: no more graphics thread necessary.
 * RETURNS: nothing
 * NOTES:   Graphics init and main loop  
*/
void * init (void * in) {
	// Pointer to the Graphics instance is passed through the thread create argument.
	Graphics* g = (Graphics *)in;
	
	creep_tex.loadFromFile("images/creep.png");
	creep_sprite.setTexture(creep_tex);
    
	// Create window for client and assign it as the window for the graphics object.
	sf::RenderWindow window(sf::VideoMode(800, 600), "Client");
	g->window = &window;
	
	// Go to the main menu first upon entering the game.
	g->setupMainMenu();

	// Main loop for the graphics thread.
	while (window.isOpen()) {
		sf::Event event;

		// Check to see if there is an event on the stack. If so, enter the while loop (pollEvent call doesn't block).
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed){
				window.close();
				exit(0);
			}
			// If a mouse button was pressed, find out where we clicked.
			else if (event.type == sf::Event::MouseButtonPressed){
				sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(window));
				// Iterate through the buttons and check each button to see if we clicked within in.
				for (std::set<Button>::iterator button = g->clientGameLogic_.UIElements.begin(); button != g->clientGameLogic_.UIElements.end(); ++button) {
					// If we clicked within the button, check to see which button it was by ID.
					if (button->rect.getGlobalBounds().contains(mouse)) {
						// Start button.
						if (button->id == ID_JOIN){
							g->initGameControls();
							g->clientGameLogic_.start();
							break; // Must break out now, initGameControls invalidates the iterators.
						}
						// Quit button.
						else if (button->id == ID_QUIT) {
							window.close();
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
			g->drawMap(window);
			g->drawUnits(window);
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

/* Constructor
 *
 * PRE:     
 * POST:    
 * RETURNS: 
 * NOTES:   Creates a thread and starts running the module */
Graphics::Graphics(ClientGameLogic& clientGameLogic)
   : window(NULL), clientGameLogic_(clientGameLogic)
{
	// Load font for game.
	char * font_path;
	find_font(&font_path);

    if (!this->font.loadFromFile(font_path)) {
		cerr << ("error loading font") << endl;
		exit(0);
	}

	// Run main graphics thread.
   	pthread_t t;
   	pthread_create(&t, NULL, init, (void*)this);
}

void Graphics::setupMainMenu()
{
	// Create buttons for the menu screen and add them to the list of UI elements.
	Button a(ID_JOIN, sf::Vector2f(250,300), sf::Vector2f(300,50), font, "                Join Game");
	Button b(321, 	   sf::Vector2f(250,400), sf::Vector2f(300,50), font, "     Press this button for fun");
	Button c(ID_QUIT,  sf::Vector2f(250,500), sf::Vector2f(300,50), font, "                     Quit");

	clientGameLogic_.UIElements.insert(a);
	clientGameLogic_.UIElements.insert(b);
	clientGameLogic_.UIElements.insert(c);
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
	sf::RectangleShape healthbar, health_bg;
	healthbar.setFillColor(sf::Color(  0, 255,  0));
	health_bg.setFillColor(sf::Color(255,   0,  0));

	for (std::vector<CLIENT_UNIT>::iterator unit = clientGameLogic_.units.begin(); unit != clientGameLogic_.units.end(); ++unit)
	{
		creep_sprite.setPosition(unit->position.x, unit->position.y);
		
		health_bg.setPosition(unit->position.x, unit->position.y+25);
		health_bg.setSize(sf::Vector2f( 25, 5));

		healthbar.setPosition(unit->position.x, unit->position.y+25);
		healthbar.setSize(sf::Vector2f( min(max(unit->health/4, 0), 100), 5));
		window.draw(creep_sprite);
		window.draw(health_bg);
		window.draw(healthbar);
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
	// Load the map texture.
	map_bg.loadFromFile("images/map.png");
	map.setTexture(map_bg);

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
