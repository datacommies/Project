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

inline string to_string(int num)
{
    stringstream ss; 
    ss << num; 	
    return ss.str();
}

Graphics* globalGraphics = NULL; // Used for the SFGUI button handlers in the lobby.

/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
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
            
            // If we're in lobby, send a message otherwise if we have the join window open, attempt a join or open the join window.
            if ((event.type == sf::Event::KeyPressed) && sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            {
                if(g->clientGameLogic_.gameState_ == CONNECTING)
                {
                    g->joinButtonHandler();
                }
                else if (g->clientGameLogic_.gameState_ == LOBBY)
                {
                    g->sendMessage();
                }
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
            } else if ((event.type == sf::Event::KeyPressed) && (g->clientGameLogic_.gameState_ != LOBBY))
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
        
        window.clear();
        GameState c_state = g->clientGameLogic_.getCurrentState();
        // Check to see which state the game is in and act accordingly.        
        if (c_state == MAIN_MENU) {
            g->drawMainMenu(window);
        } else if (c_state == LOBBY) {
            // Check if connected and display lobby, or else show "connecting..." message.
            if (g->clientGameLogic_.clientNetwork_.connecting_status != "connected") {
                g->unassignedPlayersList->SetText(g->clientGameLogic_.clientNetwork_.connecting_status);
            } else {
                string unassigned;
                for (size_t i = 0; i < g->clientGameLogic_.clientNetwork_.waiting.size(); ++i)
                {
                    unassigned += g->clientGameLogic_.clientNetwork_.waiting[i].name;
                    unassigned += "\n";
                }
                g->unassignedPlayersList->SetText(unassigned);

                if(g->clientGameLogic_.waitingForStart)
                {
                    g->drawLoadingScreen();
                }
                else
                {
                    // Update the names on the buttons.
                    g->updateLobbyRoles();
                }

                // Update chat with the latest messages.
                for (std::vector<string>::iterator it = g->clientGameLogic_.clientNetwork_.chatbuffer_.begin(); it != g->clientGameLogic_.clientNetwork_.chatbuffer_.end(); ++it)
                {
                    g->sfgChatDisplayLabel->SetText(g->sfgChatDisplayLabel->GetText().toAnsiString() + *it);

                    // Set scrollbar to lower bound.
                    sfg::Adjustment::Ptr tempAdj = g->sfgChatDisplayWindow->GetVerticalAdjustment();
                    tempAdj->SetValue(tempAdj->GetUpper());
                    g->sfgChatDisplayWindow->SetVerticalAdjustment(tempAdj);
                }

                g->clientGameLogic_.clientNetwork_.chatbuffer_.clear();
            }

            // Update the names on the buttons.
            g->updateLobbyRoles();
        } else if (c_state == IN_GAME || c_state == WON_GAME || c_state == LOST_GAME) {
            g->sfgLobbyWindow->Show(false);
            g->sfgChatDisplayWindow->Show(false);
            g->sfgChatSendWindow->Show(false);

            if (!controls_init) {
                controls_init = true;
                g->initGameControls();
            }

            g->drawMap(window);
            g->drawUnits(window);
            g->drawHud(window);
            g->drawCurrency(window);

            if (c_state == WON_GAME || c_state == LOST_GAME)
                g->drawEndGameScreen(window);
        }

        // Iterate through the buttons and draw them one by one.
        for (std::set<Button>::iterator button = g->clientGameLogic_.UIElements.begin(); button != g->clientGameLogic_.UIElements.end(); ++button)
        {
                Button b = *button;
                b.draw(window);
        }


        if (c_state == LOBBY) {
            sf::RectangleShape ready_box;
            ready_box.setSize(sf::Vector2f( 25, 25));

            for (size_t i = 0; i < 5; i++) {
                ready_box.setFillColor(g->clientGameLogic_.clientNetwork_.team_l[i].ready ? sf::Color(  0, 255,  0) : sf::Color(  255, 0,  0));
                ready_box.setPosition(65, i * 55 + 180);
                window.draw(ready_box);
            }

            for (size_t i = 0; i < 5; i++) {
                ready_box.setFillColor(g->clientGameLogic_.clientNetwork_.team_r[i].ready ? sf::Color(  0, 255,  0) : sf::Color(  255, 0,  0));
                ready_box.setPosition(710, i * 55 + 180);
                window.draw(ready_box);
            }


            for (size_t i = 0; i < 5; i++) {
                g->player_sprites[i].setPosition(65, i * 55 + 180);
                g->window->draw(g->player_sprites[i]);
            }

            for (size_t i = 0; i < 5; i++) {
                g->player_sprites[i].setPosition(710, i * 55 + 180);
                g->window->draw(g->player_sprites[i]);
            }
        }

        window.resetGLStates();
        sfgui.Display(window);
        window.display();
    }

    return NULL;
}

/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
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
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
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
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
Graphics::Graphics(ClientGameLogic& clientGameLogic)
   : window(NULL), clientGameLogic_(clientGameLogic)
{
    // Set global graphics to point to this.
    globalGraphics = this;

    chatShowing = false;

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
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
void Graphics::initMainMenuControls()
{
    // Clear all the UI buttons previous
    clientGameLogic_.UIElements.clear();

    // Create buttons for the menu screen and add them to the list of UI elements.
    Button b(ID_JOIN, 	   sf::Vector2f(250,300), sf::Vector2f(300,50), font, "               Join Game");
    Button c(ID_QUIT,  sf::Vector2f(250,400), sf::Vector2f(300,50), font, "                     Quit");

    clientGameLogic_.UIElements.insert(b);
    clientGameLogic_.UIElements.insert(c);
}

/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
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

/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
void Graphics::initDesktop()
{
    sfgDesktop = sfg::Desktop();
    sfgDesktop.SetProperty("Label", "FontSize", 22);
    sfgDesktop.SetProperty("Label", "FontSize", 22);
    sfgDesktop.SetProperty("Entry", "FontSize", 22);
}

/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
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
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
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

    sfgDesktop.Add(sfgJoinWindow);
}
/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
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
/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
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
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
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

    sfgChatDisplayLabel->SetText("");
}
/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/  
void Graphics::sendMessage()
{
    string message;

    message = clientGameLogic_.clientNetwork_._name + ": " + sfgChatSendEntry->GetText().toAnsiString() + "\n";

    // Add the message to what's currently there if it isn't empty.
    if(sfgChatSendEntry->GetText().toAnsiString() != "")
    {
        //sfgChatDisplayLabel->SetText(sfgChatDisplayLabel->GetText().toAnsiString());
        cout << "in graphics, string is: " << message << endl;
        clientGameLogic_.clientNetwork_.send_chatmsg(message);
    }

    // Clear the entry box for new entries.
    sfgChatSendEntry->SetText("");
}
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
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
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
/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
void Graphics::startGame()
{
    cout << "start the game!" << endl;
    clientGameLogic_.ready();
    sfgLobbyWindow->Show(false);
}

/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
void Graphics::exitLobby()
{
    sfgLobbyWindow->Show(false);
    sfgChatDisplayWindow->Show(false);
    sfgChatSendWindow->Show(false);

    // todo: actually exit the session and go back to main screen.
    clientGameLogic_.exit();

    this->initMainMenuControls();
}
/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
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
/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
void Graphics::showJoinWindow()
{
sfgJoinWindow->Show(true);
}
/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
void Graphics::hideJoinWindow()
{
    sfgJoinWindow->Show(false);
    this->initMainMenuControls();
}
/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
void Graphics::drawHud(sf::RenderWindow& window)
{
    window.draw(hud);
}
/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
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
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
void Graphics::drawMainMenu(sf::RenderWindow& window)
{

    creep_tex1.loadFromFile("images/c1.png");
    creep_sprite1.setTexture(creep_tex1);

    sf::Texture titlesc_bg; 
    titlesc_bg.loadFromFile("images/title.png");
    
    sf::Sprite titlesc; 
    titlesc.setTexture(titlesc_bg);

    sf::Text title("Child's Play", font, 71);
    title.setPosition(sf::Vector2f(200, 0));
    
    window.draw(titlesc);
    window.draw(title);
}


/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
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
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
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
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
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
            
           /* if (unit->maxHealth == INIT_CREEP_HP)
            {
                tower_sprite1.setPosition(unit->position.x, unit->position.y);
                window.draw(tower_sprite1);
            } else if (unit->maxHealth == INIT_CREEP_HP * 3) {
                tower_sprite2.setPosition(unit->position.x, unit->position.y);
                window.draw(tower_sprite2);
            } else if (unit->maxHealth == INIT_CREEP_HP * .75) {
                tower_sprite3.setPosition(unit->position.x, unit->position.y);
                window.draw(tower_sprite3);
            }*/

            tower_sprite1.setPosition(unit->position.x, unit->position.y);
            window.draw(tower_sprite1);
            
            drawHealthBar(window, unit->position.x, unit->position.y + tower_sprite1.getTextureRect().height, unit->health, unit->maxHealth);
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
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
void Graphics::drawCurrency(sf::RenderWindow& window)
{
    sf::Text currencyText(to_string(clientGameLogic_.currency), font, 20);
    currencyText.setPosition(5, 675);
    window.draw(currencyText);
}
/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
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
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
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
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
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

    for (int i = 0; i < 5; i++) {
        // Load the tower texture.
        stringstream ss;
        ss << "images/m" << i+1 << ".png";
        player_textures[i].loadFromFile(ss.str().c_str());
        player_sprites[i].setTexture(player_textures[i]);
    }
}

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
