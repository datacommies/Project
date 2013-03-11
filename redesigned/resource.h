#ifndef RESOURCE_H
#define RESOURCE_H

#include <vector>
#include <SFML/Graphics.hpp>

// Defines --------------------------------------------------------------------

#define MAPWIDTH  500 //TODO: change placeholder value
#define MAPHEIGHT 500 //TODO: change placeholder value

// Structs --------------------------------------------------------------------

struct Point
{
   int x;
   int y;
};

struct CLIENT_UNIT // This struct applies only to the client side - server side units are stored differently
{
   int id;
   int position;
   int health;
   int team;
   int type;
};

struct Button {
   sf::RectangleShape rect;
   int id;
   bool operator== (Button & right) {
      return (id == right.id);
   }

   bool operator< (const Button & right) const {
      return (id - right.id);
   }
};

// Enums ----------------------------------------------------------------------

enum Direction
{
   UP,
   LEFT,
   RIGHT,
   DOWN
};

enum UnitType
{
   PLAYER,
   CREEP,
   TOWER,
   CASTLE
};


enum GameState
{
   LOBBY,
   IN_GAME
};

// Typedefs -------------------------------------------------------------------

typedef std::vector<Point> PATH;

#endif