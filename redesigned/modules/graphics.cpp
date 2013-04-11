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

inline string to_string(int num)
{
    stringstream ss; 
    ss << num; 	
    return ss.str();
}

Graphics* globalGraphics = NULL; // Used for the SFGUI button handlers in the lobby.

/* Graphics Thread entry point
 *
 * PRE:     
 * POST:    Window closed: no more graphics thread necessary.
 * RETURNS: nothing
 * NOTES:   Graphics init and main loop  
*/
void * init (void * in) 
{
    bool controls_init = false;
    // Pointer to the Graphics instance is passed through the thread create argument.
    Graphics* g = (Graphics *)in;
    
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
                            break;
                        } else if (button->id == ID_TEST){
                            g->initGameControls();
                            g->clientGameLogic_.start();
                            break; // Must break out now, initGameControls invalidates the iterators.
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
            } else if (event.type == sf::Event::KeyPressed)
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
            } else if (event.type == sf::Event::KeyReleased)
            {
                Control::get()->RunAllKeys();
            }
        }
        
        // Update the sfgui test window
        g->sfgDesktop.Update( 0.f );
        
        window.clear();

        // Check to see which state the game is in and act accordingly.        
        if (g->clientGameLogic_.getCurrentState() == MAIN_MENU) {
            g->drawMainMenu(window);
        } else if (g->clientGameLogic_.getCurrentState() == LOBBY) {
            // Check if connected and display lobby, or else show "connecting..." message.
            if (g->clientGameLogic_.clientNetwork_.connecting_status != "connected") {
                g->unassignedPlayersList->SetText(g->clientGameLogic_.clientNetwork_.connecting_status);
            } else {
                for (int i=0; i < 5; i++){
                    //cout << g->clientGameLogic_.clientNetwork_.team_l[i].name << endl;
                    //cout << g->clientGameLogic_.clientNetwork_.team_r[i].name << endl;
                }
                string unassigned;
                for (size_t i = 0; i < g->clientGameLogic_.clientNetwork_.waiting.size(); ++i)
                {
                    unassigned += g->clientGameLogic_.clientNetwork_.waiting[i].name;
                    unassigned += "\n";
                }
                g->unassignedPlayersList->SetText(unassigned);

                if(g->clientGameLogic_.waitingForStart)
                {
                    g->sfgLobbyWindow->Show(false);
                    g->sfgChatDisplayWindow->Show(false);
                    g->drawLoadingScreen();
                }
                else
                {
                    // Update the names on the buttons.
                    g->updateLobbyRoles();
                }
            }

            // Update the names on the buttons.
            g->updateLobbyRoles();
        } else if (g->clientGameLogic_.getCurrentState() == IN_GAME || g->clientGameLogic_.getCurrentState() == WON_GAME || g->clientGameLogic_.getCurrentState() == LOST_GAME) {
            if (!controls_init) {
                controls_init = true;
                g->initGameControls();
            }

            g->drawMap(window);
            g->drawUnits(window);
            g->drawHud(window);
            g->drawCurrency(window);

            if (g->clientGameLogic_.getCurrentState() == WON_GAME || g->clientGameLogic_.getCurrentState() == LOST_GAME)
                g->drawEndGameScreen(window);
        }

        // Iterate through the buttons and draw them one by one.
        for (std::set<Button>::iterator button = g->clientGameLogic_.UIElements.begin(); button != g->clientGameLogic_.UIElements.end(); ++button)
        {
                Button b = *button;
                b.draw(window);
        }

        // Display test windows.
        sfgui.Display(window);

        if (g->clientGameLogic_.getCurrentState() == LOBBY) {
            for (size_t i = 0; i < 5; i++) {
                g->player_sprites[i].setPosition(65, i * 55 + 180);          
                g->window->draw(g->player_sprites[i]);
            }

            for (size_t i = 0; i < 5; i++) {
                g->player_sprites[i].setPosition(710, i * 55 + 180);          
                g->window->draw(g->player_sprites[i]);
            }
        }

        window.display();
    }

    return NULL;
}

// Pick default system font with font config.
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
    // Set global graphics to point to this.
    globalGraphics = this;

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

/* Constructor
 *
 * PRE:     
 * POST:    Clears the SFML screen of all UI components and then adds the Main Menu Buttons.
 * RETURNS:	
 * NOTES:   This can be called at any time to draw the new buttons.
 */
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
    
    //towerButton1.rect.setFillColor(sf::Color(255, 0, 0));
    towerButton1.rect.setFillColor(sf::Color::Transparent);
    towerButton2.rect.setFillColor(sf::Color::Transparent);
    towerButton3.rect.setFillColor(sf::Color::Transparent);

    creepButton1.rect.setFillColor(sf::Color::Transparent);
    creepButton2.rect.setFillColor(sf::Color::Transparent);
    creepButton3.rect.setFillColor(sf::Color::Transparent);

    highPath.rect.setFillColor(sf::Color::Transparent);
    lowPath.rect.setFillColor(sf::Color::Transparent);
    midPath.rect.setFillColor(sf::Color::Transparent);
  
    clientGameLogic_.UIElements.insert(towerButton1);
    clientGameLogic_.UIElements.insert(towerButton2);
    clientGameLogic_.UIElements.insert(towerButton3);
    clientGameLogic_.UIElements.insert(highPath);
    clientGameLogic_.UIElements.insert(midPath);
    clientGameLogic_.UIElements.insert(lowPath); 
    clientGameLogic_.UIElements.insert(creepButton1);
    clientGameLogic_.UIElements.insert(creepButton2);
    clientGameLogic_.UIElements.insert(creepButton3);
}

/* Initializes sfgDesktop. ALL SFGUI objects will sit ontop of this. We need this because it's the only way to do
 * text styling in SFGUI
 *
 * PRE:     
 * POST:    SFGUI desktop is initialized
 * RETURNS: 
 * NOTES:    
 */
void Graphics::initDesktop()
{
    sfgDesktop = sfg::Desktop();
    sfgDesktop.SetProperty("Label", "FontSize", 22);
    sfgDesktop.SetProperty("Label", "FontSize", 22);
    sfgDesktop.SetProperty("Entry", "FontSize", 22);
}

/* Randomly generates a name based on the name.txt list. 
*
* PRE:
* POST: SFGUI desktop is initialized
* RETURNS:
* NOTES:
*/
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

/* Initializes the join window that the join UI sits ontop of.
 *
 * PRE:     
 * POST:    sfgJoinWindow will have initialized with all entry objects for user/server/port
 * RETURNS: 
 * NOTES:    
 */
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
    sfgServerEntryBox = sfg::Entry::Create("localhost");
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

    sfgDesktop.Add(sfgJoinWindow);
}

/* Initializes the lobby window that the lobby sits ontop of.
 *
 * PRE:     
 * POST:    sfgLobbyWindow will be initialized with all the lobby components on it
 * RETURNS: 
 * NOTES:    
 */
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
    unassignedPlayersLabel = sfg::Label::Create("Players Waiting:");
    unassignedPlayersList = sfg::Label::Create("NeedsVector\nGordon\nG-Man\nD0g\nAlyx");
    unassignedPlayersList->SetId("upl");
    sfgDesktop.SetProperty("#upl", "FontSize", "12");

    teamOneLabel = sfg::Label::Create("Team One");
    teamTwoLabel = sfg::Label::Create("Team Two");

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
    exitLobbyButton = sfg::Button::Create("Exit Lobby");
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

    sfgDesktop.Add(sfgLobbyWindow);
}

/* Initializes the chat window with the chat display.
 *
 * PRE:     
 * POST:    sfgChatDisplayWindow will be initialized with the scrollbars and label containing chat text.
 * RETURNS: 
 * NOTES:    
 */
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

/* Initializes the chat window with the sending mechanism
 *
 * PRE:     
 * POST:    sfgChatSendWindow will be initialized with the entry box and send button
 * RETURNS: 
 * NOTES:    
 */
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

    sfgChatDisplayLabel->SetText("");
}

/* Sends the message over the network.
 *
 * PRE:     
 * POST:    message is sent over to the server
 * RETURNS: 
 * NOTES:    
 */
void Graphics::sendMessage()
{
    // Add the message to what's currently there if it isn't empty.
    if(sfgChatSendEntry->GetText().toAnsiString() != "")
    {
        sfgChatDisplayLabel->SetText(sfgChatDisplayLabel->GetText().toAnsiString() + sfgChatSendEntry->GetText().toAnsiString() + "\n");
    }

    // Clear the entry box for new entries.
    sfgChatSendEntry->SetText("");
}

/* Button handler for the lobby player select buttons
 *
 * PRE:     Lobby window is initialized
 * POST:    player will have selected his/her role
 * RETURNS: 
 * NOTES:    
 */
void Graphics::takeRole()
{
    int role = ((long) this % 10) - 1;
    int team = ((long) this >= 20) + 1;
    
    // Set it for when start button sends player_update.
    globalGraphics->clientGameLogic_.clientNetwork_.p.role = role;
    globalGraphics->clientGameLogic_.clientNetwork_.p.team = team - 1;
    
    globalGraphics->clientGameLogic_.clientNetwork_.updatePlayerLobby(team, role, globalGraphics->clientGameLogic_.clientNetwork_._name.c_str(), false);
}

/* This method updates all the button texts in the lobby with those in the client network team_l and team_r.
 *
 * PRE:     Lobby window is initialized
 * POST:    All buttons are updated with text
 * RETURNS: 
 * NOTES:    
 */
void Graphics::updateLobbyRoles()
{
    // Loop through the teams and update the buttons.
    for(int i = 0; i < 5; i++)
    {
        if(strcmp(clientGameLogic_.clientNetwork_.team_l[i].name, ""))
        {
            leftPlayers[i]->SetLabel(clientGameLogic_.clientNetwork_.team_l[i].name);
        }
        else
        {
            leftPlayers[i]->SetLabel("Open Slot");
        }

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

/* Button handler for starting the game: set our ready state and inform the server
 *
 * PRE:     Lobby window is initialized
 * POST:    game will have started
 * RETURNS: 
 * NOTES:    
 */
void Graphics::startGame()
{
    cout << "start the game!" << endl;
    clientGameLogic_.ready();
    sfgLobbyWindow->Show(false);
    sfgChatDisplayWindow->Show(false);
}

/* Closes the lobby SFGUI window and redraws the main menu.
 *
 * PRE:     SFGUI Lobby window is open
 * POST:    Closes the lobby SFGUI window and redraws the main menu.
 * RETURNS: 
 * NOTES:    
 */
void Graphics::exitLobby()
{
    sfgLobbyWindow->Show(false);
    sfgChatDisplayWindow->Show(false);

    // todo: actually exit the session and go back to main screen.
    clientGameLogic_.exit();

    this->initMainMenuControls();
}

/* Button handler for the join button on the join window.
 *
 * PRE:     Join window is initialized
 * POST:    Joins the specified server and creates lobby window
 * RETURNS: 
 * NOTES:    
 */
void Graphics::joinButtonHandler()
{
    string name, server, port; 
    
    name = sfgNameEntryBox->GetText().toAnsiString();
    server = sfgServerEntryBox->GetText().toAnsiString();
    port = sfgPortEntryBox->GetText().toAnsiString();
    
    cout << "Name:"   << name << endl;
    cout << "Server:" << server << endl;
    cout << "Port:"   << port << endl;

    clientGameLogic_.clientNetwork_.setConnectionInfo(name, server, atoi(port.c_str()));
    clientGameLogic_.join();
    initLobbyWindow();
    initMessageDisplayWindow();
    initMessageSendWindow();

    sfgJoinWindow->Show(false);
}

/* Makes the JoinWindow visible.
 *
 * PRE:     JoinWindow is initialized
 * POST:    JoinWindow is shown
 * RETURNS: 
 * NOTES:    
 */
void Graphics::showJoinWindow()
{
sfgJoinWindow->Show(true);
}

/* Makes the JoinWindow invisible.
 *
 * PRE:     JoinWindow is initialized
 * POST:    JoinWindow is not drawn anymore
 * RETURNS: 
 * NOTES:    
 */
void Graphics::hideJoinWindow()
{
    sfgJoinWindow->Show(false);
    this->initMainMenuControls();
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

/* Draws the main menu background
 *
 * PRE:     
 * POST:    The main menu text is displayed (no buttons)
 * RETURNS: 
 * NOTES:    */
void Graphics::drawMainMenu(sf::RenderWindow& window)
{

    creep_tex.loadFromFile("images/dino.png");
    creep_sprite.setTexture(creep_tex);

    sf::Texture titlesc_bg; 
    titlesc_bg.loadFromFile("images/title.png");
    
    sf::Sprite titlesc; 
    titlesc.setTexture(titlesc_bg);

    sf::Text title("Child's Play", font, 71);
    title.setPosition(sf::Vector2f(200, 0));
    
    window.draw(titlesc);
    window.draw(title);
}

/* Healthbar is drawn
 *
 * PRE:     
 * POST:    Health bar is drawn at location
 * RETURNS: 
 * NOTES:    
 */
void Graphics::drawHealthBar(sf::RenderWindow& window, float x, float y, int health)
{
    sf::RectangleShape healthbar, health_bg;
    healthbar.setFillColor(sf::Color(  0, 255,  0));
    health_bg.setFillColor(sf::Color(255,   0,  0));
    health_bg.setSize(sf::Vector2f( 25, 3));

    health_bg.setPosition(x, y);
    healthbar.setPosition(x, y);

    float percent = (float) health / 100;

    healthbar.setSize(sf::Vector2f( percent * 25, 3));
    window.draw(health_bg);
    window.draw(healthbar);	
}

/* Draws a circle around the unit to identify which team the unit is on
 *
 * PRE:     
 * POST:    All current unit circles are displayed
 * RETURNS: 
 * NOTES:    */
void Graphics::drawTeamCircle (sf::RenderWindow& window, int team, float x, float y) {
    sf::CircleShape cs(25/2);
    cs.setPosition(x, y);
    cs.setFillColor(sf::Color::Transparent);
    cs.setOutlineColor(sf::Color(team == 0 ? 255 : 0, 0, team == 0 ? 0 : 255));
    cs.setOutlineThickness(2.0f);
    window.draw(cs);
}

/* Draws all current units.
 *
 * PRE:     
 * POST:    All current units are displayed
 * RETURNS: 
 * NOTES:    */
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
            drawHealthBar(window, unit->position.x, unit->position.y + castle_sprite.getTextureRect().height, unit->health);
        } 
        else if (unit->type == CREEP)
        {
            // Linear interpolation between a unit's past position and new position.
            Point interpolated = unit->inter_position = Lerp(unit->past_position, unit->position, unit->inter_value);
            // All drawable unit elements use the same interpolated position.
            drawTeamCircle(window, unit->team, interpolated.x, interpolated.y);
            creep_sprite.setPosition(interpolated.x, interpolated.y);
            window.draw(creep_sprite);
            drawHealthBar(window, interpolated.x, interpolated.y+25, unit->health);
        }
        else if (unit->type == TOWER)
        {
            tower_sprite.setPosition(unit->position.x, unit->position.y);			
            window.draw(tower_sprite);
            drawHealthBar(window, unit->position.x, unit->position.y + tower_sprite.getTextureRect().height, unit->health);
        }
        else if (unit->type == PLAYER)
        {
            // Linear interpolation between a unit's past position and new position.
            Point interpolated = unit->inter_position = Lerp(unit->past_position, unit->position, unit->inter_value);
            // All drawable unit elements use the same interpolated position.
            drawTeamCircle(window, unit->team, interpolated.x, interpolated.y);
            player_sprites[unit->role].setPosition(interpolated.x, interpolated.y);			
            window.draw(player_sprites[unit->role]);
            drawHealthBar(window, interpolated.x, interpolated.y + player_sprites[unit->role].getTextureRect().height, unit->health);
        }
    }
    pthread_mutex_unlock( &clientGameLogic_.unit_mutex );
}

/* Draws currency at the top of the screen
 *
 * PRE:     
 * POST:    Currency bar is at the top of the screen
 * RETURNS: 
 * NOTES:    
 */
void Graphics::drawCurrency(sf::RenderWindow& window)
{
    sf::Text currencyText(to_string(clientGameLogic_.currency), font, 20);
    currencyText.setPosition(5, 675);
    window.draw(currencyText);
}

/* Draws the end of game screen
 *
 * PRE:     
 * POST:    End of game message is drawn
 * RETURNS: 
 * NOTES:    
 */
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


void Graphics::drawLoadingScreen()
{
    sf::Texture loadingScreen_bg;
    sf::Sprite  loadingScreen;

    loadingScreen_bg.loadFromFile("images/loading.png");
    loadingScreen.setTexture(loadingScreen_bg);

    window->draw(loadingScreen);
}

/* Loads all the images that are used by the game
 *
 * PRE:     
 * POST:    Images for HUD, background units etc are initialized
 * RETURNS: 
 * NOTES:    
 */
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
    creep_tex.loadFromFile("images/dino.png");
    creep_sprite.setTexture(creep_tex);
     
    // Load the castle texture.
    castle_tex.loadFromFile("images/castle.png");
    castle_sprite.setTexture(castle_tex);

    // Load the player texture.
    player_tex.loadFromFile("images/player.png");
    player_sprite.setTexture(player_tex);

    // Load the tower texture.
    tower_tex.loadFromFile("images/tower.png");
    tower_sprite.setTexture(tower_tex);

    for (int i = 0; i < 5; i++) {
        // Load the tower texture.
        stringstream ss;
        ss << "images/m" << i+1 << ".png";
        player_textures[i].loadFromFile(ss.str().c_str());
        player_sprites[i].setTexture(player_textures[i]);
    }
}
