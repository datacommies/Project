#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "../resource.h"
#include "client_game_logic.h"
#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>

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
private:
   // Module references
   ClientGameLogic& clientGameLogic_;

   // Graphics internals
   sf::Font font;
   sf::Texture map_bg;
   sf::Sprite  map;

   // Functions
   void setupMainMenu();
   void drawHud(sf::RenderWindow& window, Graphics* g);
   void drawLobby(sf::RenderWindow& window);
   void drawUnits(sf::RenderWindow& window);
   void drawMap(sf::RenderWindow& window);
   void initGameControls ();
   friend void * init (void *);
};

#endif
