#ifndef UNIT_H
#define UNIT_H

#include "../resource.h"

class Unit
{
public:
   int id;
   Point position;
   int health;
   int attackDamage;
   int attackRange;
   int attackSpeed;

   bool isAlive() { return health == 0; }
   void serializeUnit(const Unit& unit);
private:   
};

#endif
