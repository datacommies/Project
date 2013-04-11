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
   
private:
   // Module references
   ClientGameLogic& clientGameLogic_;

   // Graphics internals
   sf::Font font;
   sf::Texture map_bg;
   sf::Texture hud_bg;
   sf::Sprite  map;
   sf::Sprite hud;
   sf::Texture creep_tex;
   sf::Sprite creep_sprite;
   sf::Texture castle_tex;
   sf::Sprite castle_sprite;
   sf::Texture player_tex;
   sf::Sprite player_sprite;
   sf::Texture tower_tex;
   sf::Sprite tower_sprite;

   sf::Texture player_textures[5];   
   sf::Sprite player_sprites[5];
   
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
   
   sfg::ScrolledWindow::Ptr sfgChatDisplayWindow;
   sfg::Label::Ptr sfgChatDisplayLabel;
   
   sfg::Window::Ptr sfgChatSendWindow;
   sfg::Box::Ptr sfgChatSendBox;
   sfg::Entry::Ptr sfgChatSendEntry;
   sfg::Button::Ptr sfgChatSendButton;


   sfg::Box::Ptr teamOneBox;
   sfg::Label::Ptr teamOneLabel;
   sfg::Button::Ptr leftPlayers[5];
   
   sfg::Box::Ptr teamTwoBox;
   sfg::Label::Ptr teamTwoLabel;
   sfg::Button::Ptr rightPlayers[5];

   // Functions
   void initMainMenuControls();
   void drawHud(sf::RenderWindow& window);
   void drawMainMenu(sf::RenderWindow& window);
   void drawLobby(sf::RenderWindow& window);
   void drawUnits(sf::RenderWindow& window);
   void drawMap(sf::RenderWindow& window);
   void initGameControls ();
   void loadImages();
   void drawTeamCircle(sf::RenderWindow& window, int team, float x, float y);
   void drawHealthBar(sf::RenderWindow& window, float x, float y, int health);
   void drawCurrency(sf::RenderWindow& window);
   void drawEndGameScreen(sf::RenderWindow& window);
   void drawLoadingScreen();

   // SFGUI Functions
   void initDesktop();
   void initJoinWindow();
   void showJoinWindow();
   void hideJoinWindow();
   void joinButtonHandler();
   void initLobbyWindow();
   void initChatWindow();
   void startGame();
   void exitLobby();
   void takeRole();
   void updateLobbyRoles();

   friend void * init (void *);
};

#endif
