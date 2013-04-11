#include "control.h"
#include "graphics.h"
#include <fontconfig/fontconfig.h>
#include <iostream>
#include <SFGUI/SFGUI.hpp>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include <string>
#include "../resource.h"
#include <fstream>
#include <vector>
#include <time.h>

using namespace std;

#define INIT_CREEP_HP 150
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 700
#define BUTTON_SIZE  40
#define PATH_WIDTH 163
#define QUIT_BSIZE 15
#define PATH_HEIGHT 10
#define ROW1 627
#define ROW2 619
#define ROW3 646
#define ROW4 673
#define INFOBUTTONX 770
#define INFOBUTTONY 670

Graphics* globalGraphics = NULL; // Used for the SFGUI button handlers in the lobby.

/*------------------------------------------------------------------------------
-- FUNCTION:   to_string
--
-- DATE:        2013/03/22
--
-- DESIGNER:   David Czech
-- PROGRAMMER: David Czech
--
-- INTERFACE:   inline string to_string(int num) - the integer to be converted
--
-- RETURNS:     string - the string version of the integer
--
-- DESCRIPTION: This function returns a string version of the given integer
------------------------------------------------------------------------------*/
inline string to_string(int num)
{
    stringstream ss; 
    ss << num; 	
    return ss.str();
}

/*------------------------------------------------------------------------------
-- FUNCTION:   init
--
-- DATE:        2013/03/22
--
-- DESIGNER:   David Czech, Albert Liao
-- PROGRAMMER: David Czech, Albert Liao, Jake Miner, Jesse Wright, Dennis Ho
--
-- INTERFACE:   void * init (void * in) - in is a pointer to the graphics object
--                                        being used.
--
-- RETURNS:     void * - not used
--
-- DESCRIPTION: This function is the main graphics thread that runs and constantly 
--              redraws the client screen with the graphics that should be drawn
--              depending on the game state and the units present.
------------------------------------------------------------------------------*/
void * init (void * in) 
{
    // Controls should not be initiated until the game has started.
    bool controls_init = false;

    // Pointer to the Graphics instance is passed through the thread create argument.
    Graphics* g = (Graphics *)in;
    
    // Load all the images into the SF sprites that we're going to draw.
    g->loadImages();

    // Create window for client and assign it as the window for the graphics object.
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Client");
    g->window = &window;
    
    // We have to do this because so SFGUI works.
    window.resetGLStates();

    // Create an sfgui object. Needs to be done before other SFGUI calls.
    sfg::SFGUI sfgui;

    // Go to the main menu first upon entering the game.
    g->initMainMenuControls();

    // Initialize the SFGUI window and make it display the join window by default
    g->initDesktop();

    // Main loop for the graphics thread.
    while (window.isOpen()) {
        sf::Event event;

        // Check to see if there is an event on the stack. If so, enter the while loop (pollEvent call doesn't block).
        while (window.pollEvent(event)) {
            
            // Handle SFGUI events.
            g->sfgDesktop.HandleEvent(event);
            
            // If we're in lobby, send a message otherwise if we have the join window open, attempt a join or open the join window.
            if ((event.type == sf::Event::KeyPressed) && sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            {
                // If we're in the connecting state, the enter button should trigger a connectino request to a server.
                if(g->clientGameLogic_.gameState_ == CONNECTING)
                {
                    g->joinButtonHandler();
                }
                // If we're in the lobby, the enter button should trigger a chat message send.
                else if (g->clientGameLogic_.gameState_ == LOBBY)
                {
                    g->sendMessage();
                }
                // If we're in the starting screen, the enter button should trigger opening the join window.
                else if (g->clientGameLogic_.gameState_ == MAIN_MENU)
                {
                    g->clientGameLogic_.UIElements.clear();
                    g->initJoinWindow();
                    g->showJoinWindow();
                    g->clientGameLogic_.connecting();
                }
            }
                
            // If a mouse button was pressed, find out where we clicked.
            if (event.type == sf::Event::MouseButtonPressed){
                sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                
                bool consumed = false;
                // Iterate through the buttons and check each button to see if we clicked within in.
                for (std::set<Button>::iterator button = g->clientGameLogic_.UIElements.begin(); button != g->clientGameLogic_.UIElements.end(); ++button) {
                    // If we clicked within the button, check to see which button it was by ID.
                    if (button->rect.getGlobalBounds().contains(mouse)) {
                        consumed = true;
                        Control::get()->AddNewCalledButton(button->id);
                        // Join server button.
                        if (button->id == ID_JOIN){
                            g->clientGameLogic_.UIElements.clear();
                            g->initJoinWindow();
                            g->showJoinWindow();
                            g->clientGameLogic_.connecting();
                            break;
                        }
                        // Quit button.
                        else if (button->id == ID_QUIT){
                            window.close();
                            exit(0);
                        }
                        
                        Control::get()->RunAllButtons();
                    }
                }
                // No one consumed the mouse click, pass it on to control.
                if (!consumed) {
                    consumed = true;
                    Point p;
                    p.x = mouse.x;
                    p.y = mouse.y;
                    Control::get()->MouseCallback(p);
                }
            }
            // Close the application if requested.
            else if (event.type == sf::Event::Closed){
                window.close();
                exit(0);
            }
            // Handle key presses when the game is running.
            else if ((event.type == sf::Event::KeyPressed) && (g->clientGameLogic_.gameState_ != LOBBY))
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                    Control::get()->AddNewCalledKey(sf::Keyboard::W);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                    Control::get()->AddNewCalledKey(sf::Keyboard::A);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                    Control::get()->AddNewCalledKey(sf::Keyboard::S);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                    Control::get()->AddNewCalledKey(sf::Keyboard::D);
                Control::get()->RunAllKeys();
            } else if ((event.type == sf::Event::KeyReleased) && (g->clientGameLogic_.gameState_ != LOBBY))
            {
                Control::get()->RunAllKeys();
            }
        }
        
        // Update the sfgui test window
        g->sfgDesktop.Update( 0.f );
        
        // Clear the window so that we can redraw everything based on the gamestate.
        window.clear();

        // Get the current game state.
        GameState c_state = g->clientGameLogic_.getCurrentState();

        // Check to see which state the game is in and act accordingly.        
        if (c_state == MAIN_MENU) {
            g->drawMainMenu(window);
        } else if (c_state == LOBBY) {
            // Check if connected and display lobby, or else show "connecting..." message.
            if (g->clientGameLogic_.clientNetwork_.connecting_status != "connected") {
                g->unassignedPlayersList->SetText(g->clientGameLogic_.clientNetwork_.connecting_status);
            } else {
                string unassigned; // Used to print out all the players unassigned to roles

                // Build the string.
                for (size_t i = 0; i < g->clientGameLogic_.clientNetwork_.waiting.size(); ++i)
                {
                    unassigned += g->clientGameLogic_.clientNetwork_.waiting[i].name;
                    unassigned += "\n";
                }

                // Display the string in the unassignedPlayerList text.
                g->unassignedPlayersList->SetText(unassigned);

                // If we're waiting for the game to start, draw the loading screen.
                if(g->clientGameLogic_.waitingForStart)
                {
                    g->drawLoadingScreen();
                }
                // Otherwise, update all the new names in the roles on the buttons in the lobby.
                else
                {
                    g->updateLobbyRoles();
                }

                // Update chat with the latest messages. If there are messages in the chatbuffer_, print them.
                for (std::vector<string>::iterator it = g->clientGameLogic_.clientNetwork_.chatbuffer_.begin(); it != g->clientGameLogic_.clientNetwork_.chatbuffer_.end(); ++it)
                {
                    // Append the new message to what's currently displayed.
                    g->sfgChatDisplayLabel->SetText(g->sfgChatDisplayLabel->GetText().toAnsiString() + *it);

                    // Scroll the scrollbar down to the bottom so the new message is displayed.
                    sfg::Adjustment::Ptr tempAdj = g->sfgChatDisplayWindow->GetVerticalAdjustment();
                    tempAdj->SetValue(tempAdj->GetUpper());
                    g->sfgChatDisplayWindow->SetVerticalAdjustment(tempAdj);
                }

                // After we've added all the messages, clear the buffer.
                g->clientGameLogic_.clientNetwork_.chatbuffer_.clear();
            }
        } else if (c_state == IN_GAME || c_state == WON_GAME || c_state == LOST_GAME) {
            // Only initialize the in game controls once.
            if (!controls_init) {
                controls_init = true;
                g->initGameControls();
            }

            // Redraw all the game elements
            g->drawMap(window);
            g->drawUnits(window);
            g->drawHud(window);
            g->drawCurrency(window);

            // Only draw the info screen if the button was pressed.
            if(g->_infoButtonVisible)
            {
                g->drawInfo(window);
            }

            // If the game is finished, draw the appropriate end screen.
            if (c_state == WON_GAME || c_state == LOST_GAME)
                g->drawEndGameScreen(window);
        }

        // Iterate through the buttons and draw them one by one.
        for (std::set<Button>::iterator button = g->clientGameLogic_.UIElements.begin(); button != g->clientGameLogic_.UIElements.end(); ++button)
        {
            Button b = *button;
            b.draw(window);
        }

        // If we're in the lobby, draw all of the sprites besides their rolebuttons.
        if (c_state == LOBBY) {
            sf::RectangleShape ready_box;
            ready_box.setSize(sf::Vector2f( 25, 25));

            // Draw the ready boxes depending on who's ready on the left team.
            for (size_t i = 0; i < 5; i++) {
                ready_box.setFillColor(g->clientGameLogic_.clientNetwork_.team_l[i].ready ? sf::Color(  0, 255,  0) : sf::Color(  255, 0,  0));
                ready_box.setPosition(65, i * 55 + 180);
                window.draw(ready_box);
            }

            // Draw the ready boxes depending on who's ready on the left team.
            for (size_t i = 0; i < 5; i++) {
                ready_box.setFillColor(g->clientGameLogic_.clientNetwork_.team_r[i].ready ? sf::Color(  0, 255,  0) : sf::Color(  255, 0,  0));
                ready_box.setPosition(710, i * 55 + 180);
                window.draw(ready_box);
            }

            // Draw the left side sprites.
            for (size_t i = 0; i < 5; i++) {
                g->player_sprites[i].setPosition(65, i * 55 + 180);
                g->window->draw(g->player_sprites[i]);
            }

            // Draw the right side sprites.
            for (size_t i = 0; i < 5; i++) {
                g->player_sprites[i].setPosition(710, i * 55 + 180);
                g->window->draw(g->player_sprites[i]);
            }
        }

        // Reset the states before drawing everything on SFGUI and then SFML after.
        window.resetGLStates();
        sfgui.Display(window);
        window.display();
    }

    return NULL;
}

/*------------------------------------------------------------------------------
-- FUNCTION:   find_font()
--
-- DATE:        2013/03/22
--
-- DESIGNER:   David Czech
-- PROGRAMMER: David Czech
--
-- INTERFACE:   bool find_font (char ** path) 
--
-- RETURNS:     whether or not a font path name was found
--
-- DESCRIPTION: Finds a font file path name and returns a pointer to it in path via value-result.
------------------------------------------------------------------------------*/
bool find_font (char ** path) 
{
    FcResult result;
    FcPattern* pat = FcPatternCreate();
    //pat = FcNameParse ((FcChar8 *) ""); //specify font family?
    FcConfigSubstitute (0, pat, FcMatchPattern);
    FcDefaultSubstitute (pat);
    FcPattern * match =  FcFontMatch(NULL, pat, &result);
    match = FcFontMatch (0, pat, &result);
    return (FcPatternGetString(match, FC_FILE, 0, (FcChar8**)path) == FcResultMatch);
}

/*------------------------------------------------------------------------------
-- FUNCTION:   Lerp
--
-- DATE:        2013/03/22
--
-- DESIGNER:   David Czech
-- PROGRAMMER: David Czech
--
-- INTERFACE:   Point Lerp(Point start, Point end, float percent)
--
-- RETURNS:     Linear Interpolated Point
--
-- DESCRIPTION: Returns a new Point of the Linear Interpolates between Point start and end by percent amount.
------------------------------------------------------------------------------*/
Point Lerp(Point start, Point end, float percent)
{
    float sx = start.x, sy= start.y;
    float ex = end.x, ey= end.y;
    Point result;
    result.x = sx + percent * (ex - sx);
    result.y = sy + percent * (ey - sy);
    return result;
}

/*------------------------------------------------------------------------------
-- FUNCTION:   Graphics Constructor
--
-- DATE:        2013/03/22
--
-- DESIGNER:   David Czech
-- PROGRAMMER: David Czech
--
-- INTERFACE:   Graphics(ClientGameLogic CGL)
--
--
-- DESCRIPTION: Finds a font path and initializes an sf::Font for the Graphics class. 
--          Create main graphics thread.
------------------------------------------------------------------------------*/
Graphics::Graphics(ClientGameLogic& clientGameLogic)
   : window(NULL), clientGameLogic_(clientGameLogic)
{
    // Set global graphics to point to this.
    globalGraphics = this;

    chatShowing = false;
    _infoButtonVisible = false;

    // Load font for game.
    char * font_path;
    find_font(&font_path);

    if (!this->font.loadFromFile(font_path)) {
        cerr << ("error loading font") << endl;
        exit(0);
    }

    // Run main graphics thread.
    pthread_create(&t, NULL, init, (void*)this);
}

/*------------------------------------------------------------------------------
-- FUNCTION:   Graphics::initMainMenuControls()
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Albert Liao
-- PROGRAMMER:  Albert Liao, Jacob Miner
--
-- INTERFACE:   void Graphics::initMainMenuControls()
--
-- RETURNS:     void
--
-- DESCRIPTION: Initializes main menu controls (Adds the join and quit buttons)
------------------------------------------------------------------------------*/
void Graphics::initMainMenuControls()
{
    // Clear all the UI buttons previous
    clientGameLogic_.UIElements.clear();

    // Create buttons for the menu screen and add them to the list of UI elements.
    Button b(ID_JOIN, 	   sf::Vector2f(250,300), sf::Vector2f(300,50), font, "               Join Game");
    Button c(ID_QUIT,  sf::Vector2f(250,400), sf::Vector2f(300,50), font, "                     Quit");

    // Add the buttons to the screen.
    clientGameLogic_.UIElements.insert(b);
    clientGameLogic_.UIElements.insert(c);
}

/*------------------------------------------------------------------------------
-- FUNCTION:   initGameControls 
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Jacob Miner, Albert Liao
-- PROGRAMMER: Jacob Miner, Albert Liao
--
-- INTERFACE:   Graphics::initGameControls()
--
-- RETURNS:     void
--
-- DESCRIPTION: Creates the buttons that are visible when we're in the game.
--              Build tower, build creep, lane choose, info etc.
------------------------------------------------------------------------------*/
void Graphics::initGameControls () 
{
    clientGameLogic_.UIElements.clear();

    int button[] = { 49 , 118, 188, 313, 569, 638, 708 };
    
    //Tower Buttons
    Button towerButton1(BUILDTOWER_1,sf::Vector2f(button[0],ROW1), sf::Vector2f(BUTTON_SIZE, BUTTON_SIZE), font, NULL);
    Button towerButton2(BUILDTOWER_2,sf::Vector2f(button[1],ROW1), sf::Vector2f(BUTTON_SIZE, BUTTON_SIZE), font, NULL);
    Button towerButton3(BUILDTOWER_3,sf::Vector2f(button[2],ROW1), sf::Vector2f(BUTTON_SIZE, BUTTON_SIZE), font, NULL);

    // Path Buttons
    Button highPath(SELECTHIPATH,sf::Vector2f(button[3],ROW2), sf::Vector2f(PATH_WIDTH, PATH_HEIGHT), font, NULL);
    Button midPath(SELECTMIDPATH,sf::Vector2f(button[3],ROW3), sf::Vector2f(PATH_WIDTH, PATH_HEIGHT), font, NULL);
    Button lowPath(SELECTLOPATH,sf::Vector2f(button[3],ROW4), sf::Vector2f(PATH_WIDTH, PATH_HEIGHT), font, NULL);
    
    // Creep Buttons
    Button creepButton1(BUILDCREEP_1,sf::Vector2f(button[4],ROW1), sf::Vector2f(BUTTON_SIZE, BUTTON_SIZE), font, NULL);
    Button creepButton2(BUILDCREEP_2,sf::Vector2f(button[5],ROW1), sf::Vector2f(BUTTON_SIZE, BUTTON_SIZE), font, NULL);
    Button creepButton3(BUILDCREEP_3,sf::Vector2f(button[6],ROW1), sf::Vector2f(BUTTON_SIZE, BUTTON_SIZE), font, NULL);
    
    // Info Buttons
    Button infoButton(INFOBUTTON,sf::Vector2f(INFOBUTTONX,INFOBUTTONY), sf::Vector2f(25, 25), font, NULL);
    infoButton.rect.setFillColor(sf::Color::Transparent);

    // Make all the buttons transparent.
    towerButton1.rect.setFillColor(sf::Color::Transparent);
    towerButton2.rect.setFillColor(sf::Color::Transparent);
    towerButton3.rect.setFillColor(sf::Color::Transparent);
    creepButton1.rect.setFillColor(sf::Color::Transparent);
    creepButton2.rect.setFillColor(sf::Color::Transparent);
    creepButton3.rect.setFillColor(sf::Color::Transparent);
    highPath.rect.setFillColor(sf::Color::Transparent);
    lowPath.rect.setFillColor(sf::Color::Transparent);
    midPath.rect.setFillColor(sf::Color::Transparent);
  
    // Add all the buttons to the screen.
    clientGameLogic_.UIElements.insert(towerButton1);
    clientGameLogic_.UIElements.insert(towerButton2);
    clientGameLogic_.UIElements.insert(towerButton3);
    clientGameLogic_.UIElements.insert(highPath);
    clientGameLogic_.UIElements.insert(midPath);
    clientGameLogic_.UIElements.insert(lowPath); 
    clientGameLogic_.UIElements.insert(creepButton1);
    clientGameLogic_.UIElements.insert(creepButton2);
    clientGameLogic_.UIElements.insert(creepButton3);
    clientGameLogic_.UIElements.insert(infoButton);
}

/*------------------------------------------------------------------------------
-- FUNCTION:   initDesktop
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Albert Liao
-- PROGRAMMER: Albert Liao
--
-- INTERFACE:   void Graphics::initDesktop()
--
-- RETURNS:     none.
--
-- DESCRIPTION: This function is the basis of all of our SFGUI objects that we
--              draw. In order for controls in SFGUI to be able to have their
--              settings like font size set, it needs to be in a Desktop container.
------------------------------------------------------------------------------*/
void Graphics::initDesktop()
{
    sfgDesktop = sfg::Desktop();
    sfgDesktop.SetProperty("Label", "FontSize", 22);
    sfgDesktop.SetProperty("Label", "FontSize", 22);
    sfgDesktop.SetProperty("Entry", "FontSize", 22);
}

/*------------------------------------------------------------------------------
-- FUNCTION:   getName
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Chris Porter
-- PROGRAMMER: Chris Porter
--
-- INTERFACE:   std::string getName( void ) 
--
-- RETURNS:     a string containing a single randomly generated name.
--
-- DESCRIPTION: Opens and read a random line from names.txt to find a random name
------------------------------------------------------------------------------*/
std::string getName( void ) {

    std::vector<string> lines;
    std::string line, result;

    srand (time(NULL));
    ifstream myfile;
    myfile.open("name.txt", ifstream::in);

    if ( !myfile.is_open() ) {
        cout << "Cannot find file." << endl;
        return std::string("Error:getName");
    }

    while ( myfile.good() ){
        getline( myfile, line );
        lines.push_back(line);
    }
    myfile.close();
    for(int i = 0; i < 1; i++ ) {
        int rnd = rand() % lines.size();
        result += lines.at(rnd);
    }
    return result;
}

/*------------------------------------------------------------------------------
-- FUNCTION:   initJoinWindow
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Albert Liao
-- PROGRAMMER: Albert Liao
--
-- INTERFACE:   void Graphics::initJoinWindow()
--
-- RETURNS:     nothing.
--
-- DESCRIPTION: This function creates the window that holds all the SFGUI Join
--              controls. This window is created when the user clicks join on the
--              main menu and assists in helping the user connect to a server.
------------------------------------------------------------------------------*/
void Graphics::initJoinWindow()
{
    // Create join window using SFGUI
    sfgJoinWindow = sfg::Window::Create(sfg::Window::BACKGROUND); // Make the window.
    sfgJoinWindow->SetPosition(sf::Vector2f(200,200)); // Change the window position.
    sfgJoinWindow->SetRequisition(sf::Vector2f(400, 400));
    
    // Create a box to hold all the controls.
    sfgJoinBox = sfg::Box::Create(sfg::Box::VERTICAL);

    // Create all the labels.
    sfgNameLabel = sfg::Label::Create("User Name:");
    sfgServerLabel = sfg::Label::Create("Server:");
    sfgPortLabel = sfg::Label::Create("Port:");

    // Create the entry boxes.
    sfgNameEntryBox = sfg::Entry::Create(getName());
    sfgNameEntryBox->SetRequisition(sf::Vector2f(120, 0)); // Set entry box size to 120.
    sfgNameEntryBox->SetMaximumLength(16);
    sfgServerEntryBox = sfg::Entry::Create("192.168.0.");
    sfgServerEntryBox->SetRequisition(sf::Vector2f(120, 0)); // Set entry box size to 120.
    sfgPortEntryBox = sfg::Entry::Create("4545");
    sfgPortEntryBox->SetRequisition(sf::Vector2f(120, 0)); // Set entry box size to 120.

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

    // Add the window to the desktop for displaying.
    sfgDesktop.Add(sfgJoinWindow);
}

/*------------------------------------------------------------------------------
-- FUNCTION:   initLobbyWindow
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Albert Liao
-- PROGRAMMER: Albert Liao
--
-- INTERFACE:  void Graphics::initLobbyWindow()
--
-- RETURNS:     none.
--
-- DESCRIPTION: This function creates the lobby window. The lobby window consists
--              entirely of SFGUI buttons and labels and it provides an interface
--              for users to see which players are in the game and select the team
--              and role that they want to take.
------------------------------------------------------------------------------*/
void Graphics::initLobbyWindow()
{
    // Create lobby window using SFGUI.
    sfgLobbyWindow = sfg::Window::Create(sfg::Window::BACKGROUND); // Make the window.
    sfgLobbyWindow->SetPosition(sf::Vector2f(100, 100)); // Change the window position.
    sfgLobbyWindow->SetRequisition(sf::Vector2f(600, 350));

    // Create a parent box to hold all the subboxes.
    sfgLobbyBox = sfg::Box::Create(sfg::Box::HORIZONTAL);

    // Create the subboxes to divide the screen.
    sfgLeftLobbyBox = sfg::Box::Create(sfg::Box::VERTICAL);
    sfgMiddleLobbyBox = sfg::Box::Create(sfg::Box::VERTICAL);
    sfgRightLobbyBox = sfg::Box::Create(sfg::Box::VERTICAL);

    // Create all the labels.
    teamOneLabel = sfg::Label::Create("Team Red");
    teamTwoLabel = sfg::Label::Create("Team Blue");
    unassignedPlayersLabel = sfg::Label::Create("Players Waiting:");
    unassignedPlayersList = sfg::Label::Create("NeedsVector\nGordon\nG-Man\nD0g\nAlyx");
    
    // Set the fontsize for upl labels.
    unassignedPlayersList->SetId("upl");
    sfgDesktop.SetProperty("#upl", "FontSize", "12");
    
    // Create the team selection buttons.
    for (int i = 0; i < 5; ++i)
    {
        leftPlayers[i] = sfg::Button::Create("Open Slot");
        leftPlayers[i]->GetSignal  (sfg::Widget::OnLeftClick).Connect(&Graphics::takeRole, (Graphics *) (long) (11+i));
        
        rightPlayers[i] = sfg::Button::Create("Open Slot");
        rightPlayers[i]->GetSignal  (sfg::Widget::OnLeftClick).Connect(&Graphics::takeRole, (Graphics *) (long) (21+i));
    }

    // Create the start game / exit buttons.
    startGameButton = sfg::Button::Create("Ready");
    startGameButton->GetSignal( sfg::Widget::OnLeftClick ).Connect(&Graphics::startGame, this);
    exitLobbyButton = sfg::Button::Create("Exit Game");
    exitLobbyButton->GetSignal( sfg::Widget::OnLeftClick ).Connect(&Graphics::exitLobby, this);

    // Add all the controls to the container.
    sfgMiddleLobbyBox->Pack(unassignedPlayersLabel);
    sfgMiddleLobbyBox->Pack(unassignedPlayersList);
    sfgMiddleLobbyBox->Pack(startGameButton);
    sfgMiddleLobbyBox->Pack(exitLobbyButton);
    sfgLeftLobbyBox->Pack(teamOneLabel);
    sfgRightLobbyBox->Pack(teamTwoLabel);
    for (int i = 0; i < 5; ++i) {
        sfgLeftLobbyBox->Pack(leftPlayers[i]);
        sfgRightLobbyBox->Pack(rightPlayers[i]);
    }
    sfgLobbyBox->Pack(sfgLeftLobbyBox);
    sfgLobbyBox->Pack(sfgMiddleLobbyBox);
    sfgLobbyBox->Pack(sfgRightLobbyBox);

    sfgLobbyWindow->Add(sfgLobbyBox);

    // Add it to the desktop to be drawn.
    sfgDesktop.Add(sfgLobbyWindow);
}

/*------------------------------------------------------------------------------
-- FUNCTION:   void Graphics::initMessageDisplayWindow()
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Albert Liao
-- PROGRAMMER: Albert Liao
--
-- INTERFACE:  void Graphics::initMessageDisplayWindow()
--
-- RETURNS:     none.
--
-- DESCRIPTION: This SFGUI initializer creates the window which the chat display
--              sits on. The window needs to be of type ScrolledWindow to support
--              scrolling. There is simply a label that gets appended to inside
--              this window and that's how we show our chat messages!
------------------------------------------------------------------------------*/
void Graphics::initMessageDisplayWindow()
{
    // Set up the size and other settings of the message window.
    sfgChatDisplayWindow = sfg::ScrolledWindow::Create(); // Make the scroll window
    sfgChatDisplayWindow->SetPosition(sf::Vector2f(100, 450)); // Change the window position.
    sfgChatDisplayWindow->SetRequisition( sf::Vector2f(600, 150) ); // Set the size
    sfgChatDisplayWindow->SetScrollbarPolicy(sfg::ScrolledWindow::VERTICAL_AUTOMATIC); // Allow vertical scrollbars.
    sfgChatDisplayWindow->SetPlacement( sfg::ScrolledWindow::TOP_LEFT ); // Set where content is placed. Puts scrollbars at right and bottom.
    
    // Test text.
    sfgChatDisplayLabel = sfg::Label::Create();
    sfgChatDisplayLabel->SetId("chat");
    sfgDesktop.SetProperty("#chat", "FontSize", "12");

    // Add the label containing the messages to the scrolling window.
    sfgChatDisplayWindow->AddWithViewport(sfgChatDisplayLabel);

    // Add the window to the displayed desktop.
    sfgDesktop.Add(sfgChatDisplayWindow);
}

/*------------------------------------------------------------------------------
-- FUNCTION:   initMessageSendWindow
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Albert Liao
-- PROGRAMMER: Albert Liao
--
-- INTERFACE:   void Graphics::initMessageSendWindow()
--
-- RETURNS:     none.
--
-- DESCRIPTION: This function creates the send message portion of the game's chat
-- system. The send message window consists of a simple entry field for the user
-- to enter in a message they want to send out and a send button to do so.
------------------------------------------------------------------------------*/
void Graphics::initMessageSendWindow()
{
    // Create the window that will hold the entrybox and button.
    sfgChatSendWindow = sfg::Window::Create(sfg::Window::BACKGROUND); // Make the window.
    sfgChatSendWindow->SetPosition(sf::Vector2f(100, 600)); // Change the window position.
    sfgChatSendWindow->SetRequisition(sf::Vector2f(600, 50));

    // Create the box that will sit inside the window and set things horizontally
    sfgChatSendBox = sfg::Box::Create(sfg::Box::HORIZONTAL);

    // Create the entry box which will store the user entered message.
    sfgChatSendEntry = sfg::Entry::Create();
    sfgChatSendEntry->SetRequisition(sf::Vector2f(300, 0)); // Set entry box size.
    sfgChatSendEntry->SetId("chat");
    sfgDesktop.SetProperty("#chat", "FontSize", "12");

    // Create a button to send the message.
    sfgChatSendButton = sfg::Button::Create("Send");
    sfgChatSendButton->GetSignal( sfg::Widget::OnLeftClick ).Connect(&Graphics::sendMessage, this);

    // Pack the box with the controls in order.
    sfgChatSendBox->Pack(sfgChatSendEntry);
    sfgChatSendBox->Pack(sfgChatSendButton);

    // Put the box in the window.
    sfgChatSendWindow->Add(sfgChatSendBox);

    // Add the window to the displayed desktop.
    sfgDesktop.Add(sfgChatSendWindow);

    // Start with no text in the send message entry box.
    sfgChatDisplayLabel->SetText("");
}

/*------------------------------------------------------------------------------
-- FUNCTION:   sendMessage
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Albert Liao
-- PROGRAMMER: Albert Liao
--
-- INTERFACE:   void Graphics::sendMessage()
--
-- RETURNS:     none.
--
-- DESCRIPTION: This is the button handler for the send button in the sfgChatSendWindow.
--              This button calls the send_chatmsg() function with the string that it
--              captures from the entry box. The message will then be sent to the server
--              and relayed back to all of the clients.
------------------------------------------------------------------------------*/  
void Graphics::sendMessage()
{
    // The message that we'll be sending over to the server.
    string message;

    // Fill the message with the name of the client appended with the user's input.
    message = clientGameLogic_.clientNetwork_._name + ": " + sfgChatSendEntry->GetText().toAnsiString() + "\n";

    // Only send to the server if the user actually typed text in the input box.
    if(sfgChatSendEntry->GetText().toAnsiString() != "")
    {
        // Send the message to the server.
        clientGameLogic_.clientNetwork_.send_chatmsg(message);
    }

    // Clear the entry box for new entries from the user.
    sfgChatSendEntry->SetText("");
}

/*------------------------------------------------------------------------------
-- FUNCTION:   takeRole
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Albert Liao, Jake Miner
-- PROGRAMMER: Albert Liao, Jake Miner
--
-- INTERFACE:   void Graphics::takeRole()
--
-- RETURNS:     none.
--
-- DESCRIPTION: This is the button handler for when a user clicks on a role button in
--              the lobby. This function needs to assign both the role and team
--              locally, as well as send it over the network to the server using
--              updatePlayerLobby so that all the clients are aware of what roles
--              everyone is currently in. Roles are able to be changed after selection.
------------------------------------------------------------------------------*/  
void Graphics::takeRole()
{
    int role = ((long) this % 10) - 1;
    int team = ((long) this >= 20);
    
    if (globalGraphics->clientGameLogic_.clientNetwork_.updatePlayerLobby(team, role, globalGraphics->clientGameLogic_.clientNetwork_._name.c_str(), false)){
        // Set it for when start button sends player_update.
        globalGraphics->clientGameLogic_.clientNetwork_.p.role = role;
        globalGraphics->clientGameLogic_.clientNetwork_.p.team = team;
    }
    
}

/*------------------------------------------------------------------------------
-- FUNCTION:   updateLobbyRole
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Albert Liao 
-- PROGRAMMER: Albert Liao
--
-- INTERFACE:  void Graphics::updateLobbyRoles()
--
-- RETURNS:     none.
--
-- DESCRIPTION: This function goes through each of the names in the left and right
--              teams and applies the name label to the lobby button corresponding 
--              to that role. This way, when a user selects a role, all clients will
--              be notified of it by the change in name of the role button.
------------------------------------------------------------------------------*/
void Graphics::updateLobbyRoles()
{
    // Loop through the teams and update the buttons.
    for(int i = 0; i < 5; i++)
    {
        // Go through left team. If the name isn't empty, there's a player in this role.
        if(strcmp(clientGameLogic_.clientNetwork_.team_l[i].name, ""))
        {
            leftPlayers[i]->SetLabel(clientGameLogic_.clientNetwork_.team_l[i].name);
        }
        else
        {
            leftPlayers[i]->SetLabel("Open Slot");
        }
        // Go through right team. If the name isn't empty, there's a player in this role.
        if(strcmp(clientGameLogic_.clientNetwork_.team_r[i].name, ""))
        {
            rightPlayers[i]->SetLabel(clientGameLogic_.clientNetwork_.team_r[i].name);
        }
        else
        {
            rightPlayers[i]->SetLabel("Open Slot");
        }
    }
}

/*------------------------------------------------------------------------------
-- FUNCTION:   startGame()
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Albert liao
-- PROGRAMMER: Albert Liao
--
-- INTERFACE:   Graphics::startGame()
--
-- RETURNS:     void
--
-- DESCRIPTION: Eventually sends a message to the server notifying it of this
--              client's team and role and also telling it that it is ready to
--              start the game.
------------------------------------------------------------------------------*/
void Graphics::startGame()
{
    // Set the ready state in client game logic.
    clientGameLogic_.ready();
    // Hide the lobby window, we should go to the waiting screen next.
    sfgLobbyWindow->Show(false);
}

/*------------------------------------------------------------------------------
-- FUNCTION:   exitLobby
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Albert Liao
-- PROGRAMMER: Albert Liao
--
-- INTERFACE:   void Graphics::exitLobby()
--
-- RETURNS:     none.
--
-- DESCRIPTION: This is the handler to the exit button in the lobby screen. This
--              function simply closes all o the SFGUI windows and exits the game.
------------------------------------------------------------------------------*/
void Graphics::exitLobby()
{
    sfgLobbyWindow->Show(false);
    sfgChatDisplayWindow->Show(false);
    sfgChatSendWindow->Show(false);

    this->initMainMenuControls();

    // Quit the client.
    clientGameLogic_.exitGame();
}

/*------------------------------------------------------------------------------
-- FUNCTION:   joinButtonHandler
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Albert Liao
-- PROGRAMMER: Albert Liao
--
-- INTERFACE:   void Graphics::joinButtonHandler()
--
-- RETURNS:     none.
--
-- DESCRIPTION: This is the button handler for the join button from the join window.
--              When the user hits this button, his/her username, server and port are
--              bound to the client and used throughout the rest of the game. Joining
--              also moves you to the lobby screen next.
------------------------------------------------------------------------------*/
void Graphics::joinButtonHandler()
{
    // The strings we'll be using to store user input.
    string name, server, port;
    
    // Get all of the user input.
    name = sfgNameEntryBox->GetText().toAnsiString();
    server = sfgServerEntryBox->GetText().toAnsiString();
    port = sfgPortEntryBox->GetText().toAnsiString();

    // Set the username, server and port in the network settings.
    clientGameLogic_.clientNetwork_.setConnectionInfo(name, server, atoi(port.c_str()));
    
    // Change the gamestate to the lobby state.
    clientGameLogic_.join();

    // Initialize the lobby window, chat display and also the chat input window.
    initLobbyWindow();
    initMessageDisplayWindow();
    initMessageSendWindow();

    // Hide the join window.
    sfgJoinWindow->Show(false);
}

/*------------------------------------------------------------------------------
-- FUNCTION:   showJoinWindow
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Albert Liao
-- PROGRAMMER: Albert Liao
--
-- INTERFACE:   void Graphics::showJoinWindow()
--
-- RETURNS:     none.
--
-- DESCRIPTION: This is a function wrapper that displays the join window.
------------------------------------------------------------------------------*/
void Graphics::showJoinWindow()
{
    sfgJoinWindow->Show(true);
}

/*------------------------------------------------------------------------------
-- FUNCTION:   hideJoinWindow
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Albert Liao
-- PROGRAMMER: Albert Liao
--
-- INTERFACE:   void Graphics::hideJoinWindow()
--
-- RETURNS:     none.
--
-- DESCRIPTION: This is a function wrapper that hides the join window.
------------------------------------------------------------------------------*/
void Graphics::hideJoinWindow()
{
    sfgJoinWindow->Show(false);
    this->initMainMenuControls();
    clientGameLogic_.menu();
}

/*------------------------------------------------------------------------------
-- FUNCTION:   drawHud
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Jacob Miner, Albert Liao
-- PROGRAMMER: Jacob Miner, Albert Liao
--
-- INTERFACE:   void Graphics::drawHud(sf::RenderWindow& window)
--
-- RETURNS:     none.
--
-- DESCRIPTION: This function adds the hud image to SFML so that it can be drawn on
--              the next refresh.
------------------------------------------------------------------------------*/
void Graphics::drawHud(sf::RenderWindow& window)
{
    window.draw(hud);
}

/*------------------------------------------------------------------------------
-- FUNCTION:   drawMap
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Jacob Miner, Albert Liao
-- PROGRAMMER: Jacob Miner, Albert Liao
--
-- INTERFACE:   void Graphics::drawMap(sf::RenderWindow& window)
--
-- RETURNS:     none.
--
-- DESCRIPTION: This function adds the map image to SFML so that it can be drawn on
--              the next refresh.
------------------------------------------------------------------------------*/
void Graphics::drawMap(sf::RenderWindow& window)
{
    window.draw(map);
}

/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Jacob Miner
-- PROGRAMMER: Jacob Miner
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
void Graphics::drawMainMenu(sf::RenderWindow& window)
{
    window.draw(titlesc);
    window.draw(title);
}

/*------------------------------------------------------------------------------
-- FUNCTION:   drawInfo
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Albert Liao
-- PROGRAMMER: Albert Liao
--
-- INTERFACE:   void Graphics::drawInfo(sf::RenderWindow& window)
--
-- RETURNS:     none.
--
-- DESCRIPTION: This function adds the creep/tower info to SFML so that it can 
--              be drawn on the next refresh.
------------------------------------------------------------------------------*/
void Graphics::drawInfo(sf::RenderWindow& window)
{
    window.draw(infoSprite);
}

/*------------------------------------------------------------------------------
-- FUNCTION:   drawHealthBar
--
-- DATE:        2013/03/22
--
-- DESIGNER:   David Czech
-- PROGRAMMER: David Czech
--
-- INTERFACE:   drawHealthBar(sf::RenderWindow& window, float x, float y, int health, int maxhealth)
--
-- RETURNS:     void
--
-- DESCRIPTION: draw a 25px by 3px health bar with a red background and green foreground.
--              green bar size is calculated with health over max_health.
------------------------------------------------------------------------------*/
void Graphics::drawHealthBar(sf::RenderWindow& window, float x, float y, int health, int maxhealth)

{
    sf::RectangleShape healthbar, health_bg;
    healthbar.setFillColor(sf::Color(  0, 255,  0));
    health_bg.setFillColor(sf::Color(255,   0,  0));
    health_bg.setSize(sf::Vector2f( 25, 3));

    health_bg.setPosition(x, y);
    healthbar.setPosition(x, y);

    float percent = ( ((float) health) / maxhealth);

    healthbar.setSize(sf::Vector2f( percent * 25, 3));
    window.draw(health_bg);
    window.draw(healthbar);	
}

/*------------------------------------------------------------------------------
-- FUNCTION:   drawTeamCircle
--
-- DATE:        2013/03/22
--
-- DESIGNER:   David Czech
-- PROGRAMMER: David Czech
--
-- INTERFACE:   drawTeamCircle (sf::RenderWindow& window, int team, float x, float y)
--
-- RETURNS:     void
--
-- DESCRIPTION: Draws a 25px cicrle indicating a unit's team (0 for red, 1 for blue).
------------------------------------------------------------------------------*/
void Graphics::drawTeamCircle (sf::RenderWindow& window, int team, float x, float y) {
    sf::CircleShape cs(25/2);
    cs.setPosition(x, y);
    cs.setFillColor(sf::Color::Transparent);
    cs.setOutlineColor(sf::Color(team == 0 ? 255 : 0, 0, team == 0 ? 0 : 255));
    cs.setOutlineThickness(2.0f);
    window.draw(cs);
}

/*------------------------------------------------------------------------------
-- FUNCTION:   drawUnits
--
-- DATE:        2013/03/22
--
-- DESIGNER:   David Czech, Jacob Miner 
-- PROGRAMMER: David Czech, Jacob Miner
--
-- INTERFACE:   void Graphics::drawUnits(sf::RenderWindow& window)
--
-- RETURNS:     none.
--
-- DESCRIPTION: This function loops through all of the units currently in the game
--              and draws them one by one based on their type. This happends every
--              time that the screen is refreshed in the graphics thread.
------------------------------------------------------------------------------*/
void Graphics::drawUnits(sf::RenderWindow& window)
{
    pthread_mutex_lock( &clientGameLogic_.unit_mutex );
    for (std::vector<CLIENT_UNIT>::iterator unit = clientGameLogic_.units.begin(); unit != clientGameLogic_.units.end(); ++unit)
    {
        // Increment interpolation value, if there is a different between past and current positions.
        if (unit->past_position.x != unit->position.x || unit->past_position.y != unit->position.y)
            //  This increment should be as close as possible to the 1 over amount of time required until the next change in unit->position.
            unit->inter_value += 1/4.0; // TODO: factor in elapsed time since last draw.
        
        // Interpolation complete: set the past position to the current position and stop interpolation.
        if (unit->inter_value >= 1.0) {
            unit->past_position = unit->position; 
            unit->inter_value = 0;
        }
        
        if (unit->type == CASTLE) 
        {
            castle_sprite.setPosition(unit->position.x, unit->position.y);			
            window.draw(castle_sprite);
            drawHealthBar(window, unit->position.x, unit->position.y + castle_sprite.getTextureRect().height, unit->health, unit->maxHealth);
        } 
        else if (unit->type == CREEP)
        {
            // Linear interpolation between a unit's past position and new position.
            Point interpolated = unit->inter_position = Lerp(unit->past_position, unit->position, unit->inter_value);
            // All drawable unit elements use the same interpolated position.
            drawTeamCircle(window, unit->team, interpolated.x, interpolated.y);
            
            if (unit->maxHealth == INIT_CREEP_HP)
            {
                creep_sprite1.setPosition(interpolated.x, interpolated.y);
                window.draw(creep_sprite1);
            } else if (unit->maxHealth == INIT_CREEP_HP * 3) {
                creep_sprite2.setPosition(interpolated.x, interpolated.y);
                window.draw(creep_sprite2);
            } else if (unit->maxHealth == (int)(INIT_CREEP_HP * .75)) {
                creep_sprite3.setPosition(interpolated.x, interpolated.y);
                window.draw(creep_sprite3);
            } else {
                creep_sprite1.setPosition(interpolated.x, interpolated.y);
                window.draw(creep_sprite1);
            }
            
            drawHealthBar(window, interpolated.x, interpolated.y+25, unit->health, unit->maxHealth);
        }
        else if (unit->type == TOWER)
        {
            tower_sprite1.setPosition(unit->position.x, unit->position.y);
            window.draw(tower_sprite1);
            drawHealthBar(window, unit->position.x, unit->position.y + tower_sprite1.getTextureRect().height, unit->health, unit->maxHealth);
        }
        else if (unit->type == TOWER_TWO)
        {
            tower_sprite2.setPosition(unit->position.x, unit->position.y);
            window.draw(tower_sprite2);
            drawHealthBar(window, unit->position.x, unit->position.y + tower_sprite2.getTextureRect().height, unit->health, unit->maxHealth);
        }
        else if (unit->type == TOWER_THREE)
        {
            tower_sprite3.setPosition(unit->position.x, unit->position.y);
            window.draw(tower_sprite3);
            drawHealthBar(window, unit->position.x, unit->position.y + tower_sprite3.getTextureRect().height, unit->health, unit->maxHealth);
        }
        else if (unit->type == PLAYER)
        {
            // Linear interpolation between a unit's past position and new position.
            Point interpolated = unit->inter_position = Lerp(unit->past_position, unit->position, unit->inter_value);
            // All drawable unit elements use the same interpolated position.
            drawTeamCircle(window, unit->team, interpolated.x, interpolated.y);
            player_sprites[unit->role].setPosition(interpolated.x, interpolated.y);			
            window.draw(player_sprites[unit->role]);
            drawHealthBar(window, interpolated.x, interpolated.y + player_sprites[unit->role].getTextureRect().height, unit->health, unit->maxHealth);
        }
    }
    pthread_mutex_unlock( &clientGameLogic_.unit_mutex );
}

/*------------------------------------------------------------------------------
-- FUNCTION:   drawCurrency
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Jacob Miner, Dennis Ho
-- PROGRAMMER: Jacob Miner, Dennis Ho
--
-- INTERFACE:   void Graphics::drawCurrency(sf::RenderWindow& window)
--
-- RETURNS:     
--
-- DESCRIPTION: Draws the team's current currency balance on the window
------------------------------------------------------------------------------*/
void Graphics::drawCurrency(sf::RenderWindow& window)
{
    sf::Text currencyText(to_string(clientGameLogic_.currency), font, 20);
    currencyText.setPosition(5, 675);
    window.draw(currencyText);
}

/*------------------------------------------------------------------------------
-- FUNCTION:   drawEndGameScreen
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Jacob Miner, Dennis Ho
-- PROGRAMMER: Jacob Miner, Dennis Ho
--
-- INTERFACE:   void Graphics::drawEndGameScreen(sf::RenderWindow& window)
--
-- RETURNS:     
--
-- DESCRIPTION: Draws the win/lose screen when the game ends
------------------------------------------------------------------------------*/
void Graphics::drawEndGameScreen(sf::RenderWindow& window)
{
    sf::Texture endGameScreen_bg;
    sf::Sprite  endGameScreen; 
    
    if (clientGameLogic_.getCurrentState() == WON_GAME)
        endGameScreen_bg.loadFromFile("images/win.png");
    else 
        endGameScreen_bg.loadFromFile("images/loss.png");

    endGameScreen.setTexture(endGameScreen_bg);
    endGameScreen.setScale(.625,.5);
    endGameScreen.setPosition(150,125);
    window.draw(endGameScreen);
}

/*------------------------------------------------------------------------------
-- FUNCTION:   drawLoadingScreen
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Jacob Miner
-- PROGRAMMER: Jacob Miner, Albert Liao
--
-- INTERFACE:   void Graphics::drawLoadingScreen()
--
-- RETURNS:     none.
--
-- DESCRIPTION: Draws a "waiting for other players" image on the screen when we're
--              in a ready state and waiting for all other players to be ready.
------------------------------------------------------------------------------*/
void Graphics::drawLoadingScreen()
{
    sf::Texture loadingScreen_bg;
    sf::Sprite  loadingScreen;

    loadingScreen_bg.loadFromFile("images/loading.png");
    loadingScreen.setTexture(loadingScreen_bg);

    window->draw(loadingScreen);
}

/*------------------------------------------------------------------------------
-- FUNCTION:   loadImages
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Albert Liao
-- PROGRAMMER: Albert Liao, Jacob Miner
--
-- INTERFACE:   void Graphics::loadImages()
--
-- RETURNS:     none.
--
-- DESCRIPTION: Loads all of the images that we use in the game into SFML sprites
--              so that they can be drawn on the screen. This includes things from
--              the creeps and towers that we draw to the HUD and map.
------------------------------------------------------------------------------*/
void Graphics::loadImages()
{
    // Load the HUD background.
    hud_bg.loadFromFile("images/hud.png");
    hud.setTexture(hud_bg);
    hud.setPosition(0, 600);
    
    // Load the map texture.
    map_bg.loadFromFile("images/map.png");
    map.setTexture(map_bg);

    // Load the creep texture.
    creep_tex1.loadFromFile("images/c1.png");
    creep_sprite1.setTexture(creep_tex1);

    creep_tex2.loadFromFile("images/c2.png");
    creep_sprite2.setTexture(creep_tex2);

    creep_tex3.loadFromFile("images/c3.png");
    creep_sprite3.setTexture(creep_tex3);
    
    // Load the castle texture.
    castle_tex.loadFromFile("images/castle.png");
    castle_sprite.setTexture(castle_tex);

    // Load the tower texture.
    tower_tex1.loadFromFile("images/t1.png");
    tower_sprite1.setTexture(tower_tex1);

    tower_tex2.loadFromFile("images/t2.png");
    tower_sprite2.setTexture(tower_tex2);

    tower_tex3.loadFromFile("images/t3.png");
    tower_sprite3.setTexture(tower_tex3);

    // Load the info screen image.
    infoImage.loadFromFile("images/infos.png");
    infoSprite.setTexture(infoImage);
    infoSprite.setPosition(150, 50);

    // Load the title background.
    titlesc_bg.loadFromFile("images/title.png");
    titlesc.setTexture(titlesc_bg);

    // Load the title text.
    title = sf::Text("Jurassic Mistake", font, 71);
    title.setPosition(sf::Vector2f(50, 0));
    title.setColor(sf::Color(255, 0, 0));

    for (int i = 0; i < 5; i++) {
        // Load the tower texture.
        stringstream ss;
        ss << "images/m" << i+1 << ".png";
        player_textures[i].loadFromFile(ss.str().c_str());
        player_sprites[i].setTexture(player_textures[i]);
    }
}

/*------------------------------------------------------------------------------
-- FUNCTION:   showChat
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Albert Liao
-- PROGRAMMER: Albert Liao, Jacob Miner
--
-- INTERFACE:   void Graphics::showChat(bool show)
--
-- RETURNS:     none.
--
-- DESCRIPTION: Loads all of the images that we use in the game into SFML sprites
--              so that they can be drawn on the screen. This includes things from
--              the creeps and towers that we draw to the HUD and map.
------------------------------------------------------------------------------*/
void Graphics::showChat(bool show)
{
    if(show)
    {
        sfgChatDisplayWindow->Show(true);
        sfgChatSendWindow->Show(true);
        chatShowing = true;
    }
    else
    {
        sfgChatDisplayWindow->Show(false);
        sfgChatSendWindow->Show(false);
        chatShowing = false;
    }
}

void Graphics::toggleInfoButton()
{
    _infoButtonVisible ? _infoButtonVisible = false : _infoButtonVisible = true;
}
