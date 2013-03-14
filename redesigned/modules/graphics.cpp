#include "graphics.h"
#include <fontconfig/fontconfig.h>
#include <iostream>
#include <SFGUI/SFGUI.hpp>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

#define ID_JOIN 100
#define ID_QUIT 101
#define ID_TEST 999

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

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
	
	g->loadImages();

	// Create window for client and assign it as the window for the graphics object.
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Client");
	g->window = &window;
	
	// We have to do this because we don't use SFML to draw.
	window.resetGLStates();

	// Create an sfgui object. Needs to be done before other SFGUI calls.
	sfg::SFGUI sfgui;

	// Go to the main menu first upon entering the game.
	g->initMainMenuControls();

	// Initialize the SFGUI join server widget and hide it on startup.
	g->initJoinWindow();
	g->hideJoinWindow();

	// Main loop for the graphics thread.
	while (window.isOpen()) {
		sf::Event event;

		// Check to see if there is an event on the stack. If so, enter the while loop (pollEvent call doesn't block).
		while (window.pollEvent(event)) {
			
			// Handle SFGUI events.
			g->sfgJoinWindow->HandleEvent(event);

			// If a mouse button was pressed, find out where we clicked.
			if (event.type == sf::Event::MouseButtonPressed){
				sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
				// Iterate through the buttons and check each button to see if we clicked within in.
				for (std::set<Button>::iterator button = g->clientGameLogic_.UIElements.begin(); button != g->clientGameLogic_.UIElements.end(); ++button) {
					// If we clicked within the button, check to see which button it was by ID.
					if (button->rect.getGlobalBounds().contains(mouse)) {
						// Join server button.
						if (button->id == ID_JOIN){
							g->showJoinWindow();
						}
						else if (button->id == ID_TEST)
						{
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
			// Close the application if requested.
			else if (event.type == sf::Event::Closed){
				window.close();
				exit(0);
			}
		}
 		
 		// Update the sfgui test window
 		g->sfgJoinWindow->Update( 0.f );
		
		window.clear();

		// Check to see which state the game is in and act accordingly.
		if (g->clientGameLogic_.getCurrentState() == LOBBY) {
			g->drawMainMenu(window);
		}
		else if (g->clientGameLogic_.getCurrentState() == IN_GAME) {
			g->drawMap(window);
			g->drawUnits(window);
			g->drawHud(window);
			sf::Text state("In Game", g->font, 20);
			window.draw(state);
		}

		// Iterate through the buttons and draw them one by one.
		for (std::set<Button>::iterator button = g->clientGameLogic_.UIElements.begin(); button != g->clientGameLogic_.UIElements.end(); ++button)
		{
			Button b = *button;
			b.draw(window);
		}

		// Display test windows.
		sfgui.Display(window);

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

Point Lerp(Point start, Point end, float percent)
{
	float sx = start.x, sy= start.y;
	float ex = end.x, ey= end.y;
	Point result;
	result.x = sx + percent * (ex - sx);
	result.y = sy + percent * (ey - sy);
	return result;
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

void Graphics::initMainMenuControls()
{
	// Clear all the UI buttons previous
	clientGameLogic_.UIElements.clear();

	// Create buttons for the menu screen and add them to the list of UI elements.
	Button a(ID_TEST, sf::Vector2f(250,300), sf::Vector2f(300,50), font, "                Test Game");
	Button b(ID_JOIN, 	   sf::Vector2f(250,400), sf::Vector2f(300,50), font, "               Join Game");
	Button c(ID_QUIT,  sf::Vector2f(250,500), sf::Vector2f(300,50), font, "                     Quit");

	clientGameLogic_.UIElements.insert(a);
	clientGameLogic_.UIElements.insert(b);
	clientGameLogic_.UIElements.insert(c);
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

void Graphics::initJoinWindow(){
	// Create join window using SFGUI
	sfgJoinWindow = sfg::Window::Create( sfg::Window::TITLEBAR | sfg::Window::BACKGROUND | sfg::Window::RESIZE); // Make the window.
	sfgJoinWindow->SetTitle(L"Join Game"); // Add a title to the window.
	sfgJoinWindow->SetPosition(sf::Vector2f(400,400)); // Change the window position.
	
	// Create a box to hold all the controls.
	sfgJoinBox = sfg::Box::Create(sfg::Box::VERTICAL);

	// Create all the labels.
	sfgNameLabel = sfg::Label::Create("Name:");
	sfgServerLabel = sfg::Label::Create("Server:");
	sfgPortLabel = sfg::Label::Create("Port:");

	// Create the entry boxes.
	sfgNameEntryBox = sfg::Entry::Create();
	sfgNameEntryBox->SetRequisition(sf::Vector2f(120, 0)); // Set entry box size to 80.
	sfgServerEntryBox = sfg::Entry::Create();
	sfgServerEntryBox->SetRequisition(sf::Vector2f(120, 0)); // Set entry box size to 80.
	sfgPortEntryBox = sfg::Entry::Create();
	sfgPortEntryBox->SetRequisition(sf::Vector2f(120, 0)); // Set entry box size to 80.

	// Create a button to join a server and handle it's signal
	sfgJoinButton = sfg::Button::Create("Join");
	sfgJoinButton->GetSignal( sfg::Widget::OnLeftClick ).Connect(&Graphics::joinButtonHandler, this);

	// Create a button to close the join window and handle it's signal
	sfgCloseJoinButton = sfg::Button::Create("Close");
	sfgCloseJoinButton->GetSignal( sfg::Widget::OnLeftClick ).Connect(&Graphics::hideJoinWindow, this);

	// Add all the controls to the container.
	sfgJoinBox->Pack(sfgNameLabel);
	sfgJoinBox->Pack(sfgNameEntryBox);
	sfgJoinBox->Pack(sfgServerLabel);
	sfgJoinBox->Pack(sfgServerEntryBox);
	sfgJoinBox->Pack(sfgPortLabel);
	sfgJoinBox->Pack(sfgPortEntryBox);
	sfgJoinBox->Pack(sfgJoinButton);
	sfgJoinBox->Pack(sfgCloseJoinButton);

	sfgJoinWindow->Add(sfgJoinBox);	
}

void Graphics::joinButtonHandler()
{
	cout << "Name:" << endl;//<< sfgNameEntryBox->GetText() << endl;
	//cout << "Server:" << sfgServerEntryBox->GetText() << endl;
	//cout << "Port:" << sfgPortEntryBox->GetText() << endl;
}

void Graphics::showJoinWindow()
{
	sfgJoinWindow->Show(true);
}

void Graphics::hideJoinWindow()
{
	sfgJoinWindow->Show(false);
}

/* Draws the HUD.
 *
 * PRE:     
 * POST:    Current HUD is displayed
 * RETURNS: 
 * NOTES:    */
void Graphics::drawHud(sf::RenderWindow& window)
{
	window.draw(hud);
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

/* Draws the lobby.
 *
 * PRE:     
 * POST:    Current lobby is displayed
 * RETURNS: 
 * NOTES:    */
void Graphics::drawMainMenu(sf::RenderWindow& window)
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
	health_bg.setSize(sf::Vector2f( 25, 5));

	for (std::vector<CLIENT_UNIT>::iterator unit = clientGameLogic_.units.begin(); unit != clientGameLogic_.units.end(); ++unit)
	{
		// Increment interpolation value, if there is a different between past and current positions.
		if (unit->past_position.x != unit->position.x || unit->past_position.y != unit->position.y)
			//  This increment should be as close as possible to the 1 over amount of time required until the next change in unit->position.
			unit->inter_value += 1/50.0; // TODO: factor in elapsed time since last draw.
		
		// Interpolation complete: set the past position to the current position and stop interpolation.
		if (unit->inter_value >= 1.0) {
			unit->past_position = unit->position; 
			unit->inter_value = 0;
		}
		
		if (unit->type == CASTLE) {
			castle_sprite.setPosition(unit->position.x, unit->position.y);
			health_bg.setPosition(unit->position.x, unit->position.y + castle_sprite.getTextureRect().height);
			healthbar.setPosition(unit->position.x, unit->position.y + castle_sprite.getTextureRect().height);
			healthbar.setSize(sf::Vector2f( min(max(unit->health/4, 0), 100), 5));
			window.draw(castle_sprite);
		} else if (unit->type == CREEP) {
			// Linear interpolation between a unit's past position and new position.
			Point interpolated = Lerp(unit->past_position, unit->position, unit->inter_value);
			// All drawable unit elements use the same interpolated position.
			creep_sprite.setPosition(interpolated.x, interpolated.y);
			health_bg.setPosition(interpolated.x, interpolated.y+25);
			healthbar.setPosition(interpolated.x, interpolated.y+25);
			healthbar.setSize(sf::Vector2f( min(max(unit->health/4, 0), 100), 5));
			window.draw(creep_sprite);
		}

		window.draw(health_bg);
		window.draw(healthbar);
	}
}

void Graphics::loadImages(){
	// Load the HUD background.
	hud_bg.loadFromFile("images/hud.png");
	hud.setTexture(hud_bg);
	hud.setPosition(0, 600);

	// Load the map texture.
	map_bg.loadFromFile("images/map.png");
	map.setTexture(map_bg);

	// Load the creep texture.
	creep_tex.loadFromFile("images/creep.png");
	creep_sprite.setTexture(creep_tex);
    
    // Load the castle texture.
    castle_tex.loadFromFile("images/castle.png");
	castle_sprite.setTexture(castle_tex);

	// Load the player texture.
    player_tex.loadFromFile("images/player.png");
	player_sprite.setTexture(player_tex);
}