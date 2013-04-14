#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "../resource.h"
#include "client_game_logic.h"
#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>

/*
  ** 3D Sprite rotation (cause why not) **
  **

  class MyTransform : public sf::Transform {
  public:
     Transform& rotate_x(float angle)
     {
        std::cout << "rotated!" << std::endl;
         float rad = angle * 3.141592654f / 180.f;
         float cos = std::cos(rad);
         float sin = std::sin(rad);

         Transform rotation(1,   0,    0,
                            0, cos, -sin,
                            0, sin,  cos);

         return combine(rotation);
     }
  };

  class MySprite : public sf::Sprite {
  private:
     MyTransform t;
  public:
     sf::Sprite inner;
     MySprite () { std::cout << "asadfasndfjkaslinit" << std::endl;}
     virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
     {
        static int i = 0;
        std::cout << "mysprite draw" << std::endl;
        MyTransform mt;
        mt.rotate_x(i++);
        const sf::Transform &t = mt;

        states.transform *= t;
        target.draw(inner, states);
     }

     const sf::Transform& getTransform() const
     {
         std::cout << "hello" << std::endl;
         return t;
         //MyTransform mt;
         //mt.rotate_x(10);
         //t.combine(mt);
         
     }
};*/

class Graphics
{
public:
   // Constructors
   Graphics(ClientGameLogic& clientGameLogic);
   sf::RenderWindow * window;
   pthread_t t;
   

   sfg::ScrolledWindow::Ptr sfgChatDisplayWindow;
   sfg::Window::Ptr sfgChatSendWindow;
   void toggleInfoButton();

private:
   // Module references
   ClientGameLogic& clientGameLogic_;

   // All of the image sprites that we pre-load.
   sf::Font font;
   sf::Texture map_bg; // Map
   sf::Sprite  map;
   sf::Texture hud_bg; // HUD
   sf::Sprite hud; 
   sf::Texture creep_tex1; // Creeps 
   sf::Sprite creep_sprite1;
   sf::Texture creep_tex2;
   sf::Sprite creep_sprite2;
   sf::Texture creep_tex3;
   sf::Sprite creep_sprite3;
   sf::Texture castle_tex; // Castle
   sf::Sprite castle_sprite;
   sf::Texture tower_tex1; // Towers
   sf::Sprite tower_sprite1;
   sf::Texture tower_tex3;
   sf::Sprite tower_sprite3;
   sf::Texture tower_tex2;
   sf::Sprite tower_sprite2;
   sf::Texture infoImage; // Info Screen
   sf::Sprite infoSprite;
   sf::Texture player_textures[5]; // Players 
   sf::Sprite player_sprites[5];
   sf::Sprite titlesc; // Title
   sf::Texture titlesc_bg; 
   sf::Text title;
   
   // SFGUI stuff
   sfg::Desktop sfgDesktop; // The desktop is the top level object that all other SFGUI elements display on.
   
   sfg::Window::Ptr sfgJoinWindow; // The "form" used for the join window.
   sfg::Entry::Ptr  sfgNameEntryBox;
   sfg::Entry::Ptr  sfgServerEntryBox;
   sfg::Entry::Ptr  sfgPortEntryBox;
   sfg::Button::Ptr sfgCloseJoinButton;
   sfg::Button::Ptr sfgJoinButton;
   sfg::Box::Ptr sfgJoinBox;
   sfg::Label::Ptr sfgNameLabel;
   sfg::Label::Ptr sfgServerLabel;
   sfg::Label::Ptr sfgPortLabel;

   sfg::Window::Ptr sfgLobbyWindow; // The form used for the lobby.
   sfg::Box::Ptr sfgLobbyBox;
   sfg::Box::Ptr sfgLeftLobbyBox;
   sfg::Box::Ptr sfgMiddleLobbyBox;
   sfg::Box::Ptr sfgRightLobbyBox;
   sfg::Button::Ptr startGameButton;
   sfg::Button::Ptr exitLobbyButton;
   sfg::Label::Ptr unassignedPlayersLabel;
   sfg::Label::Ptr unassignedPlayersList;
   sfg::Box::Ptr teamOneBox;
   sfg::Label::Ptr teamOneLabel;
   sfg::Button::Ptr leftPlayers[5];
   sfg::Box::Ptr teamTwoBox;
   sfg::Label::Ptr teamTwoLabel;
   sfg::Button::Ptr rightPlayers[5];
   
   sfg::Label::Ptr sfgChatDisplayLabel; // Used to create the chat controls.
   sfg::Box::Ptr sfgChatSendBox;
   sfg::Entry::Ptr sfgChatSendEntry;
   sfg::Button::Ptr sfgChatSendButton;

   bool chatShowing; // Whether the chat is currently showing or not.
   bool _infoButtonVisible; // Whether we should show the info screen or not.

   // Functions
   void initMainMenuControls(); // Add the buttons for the main menu
   void drawHud(sf::RenderWindow& window); // Draw the HUD image.
   void drawMainMenu(sf::RenderWindow& window); // Draw the MainMenu title and bg
   void drawUnits(sf::RenderWindow& window); // Draw all of the units that are in the game.
   void drawMap(sf::RenderWindow& window); // Draw the map image.
   void initGameControls (); // Draw the in game control buttons
   void loadImages(); // Pre-load all the images into the SFML sprites.
   void drawTeamCircle(sf::RenderWindow& window, int team, float x, float y); // Draw the Red or Blue circles around the units.
   void drawHealthBar(sf::RenderWindow& window, float x, float y, int health, int max); // Draw the healthbars of every unit.
   void drawCurrency(sf::RenderWindow& window); // Draw the currency for your team.
   void drawEndGameScreen(sf::RenderWindow& window); // Draw the end game screen depending on whether you won or lost.
   void drawLoadingScreen(); // Draw the loading screen when you're waiting for others to be ready as well.
   void drawInfo(sf::RenderWindow& window); // Draw the info screen when the info button is pressed in game.

   // SFGUI Functions
   void initDesktop(); // Create the desktop object that all other sfgui objects sit ontop of.
   void initJoinWindow(); // Create the join window that the user can use to input server details.
   void showJoinWindow(); // Wrapper to show the join window.
   void hideJoinWindow(); // Wrapper to hide the join window.
   void joinButtonHandler(); // Handler for the "Join" button on the join window.
   void initLobbyWindow(); // Create the lobby window that the users can pick and see roles in.
   void initMessageDisplayWindow(); // Create the message display window in which the chat is displayed.
   void initMessageSendWindow(); // Create the send window in which the users can send messages to other clients.
   void sendMessage(); // The handler for the "Send" button in the sendwindow for chat.
   void startGame(); // The handler for the start game button in the lobby.
   void exitLobby(); // The handler for the exit game button in the lobby.
   void takeRole(); // The handler for all of the role buttons in the lobby.
   void updateLobbyRoles(); // This function updates all the role buttons in the lobby with the user name that has taken that role.
   void showChat(bool show); // This function either hides or shows the chat windows based on the input parameter.

   friend void * init (void *); // This is the main graphics thread function which constantly loops and draws the latest images on the screen.
};

#endif
