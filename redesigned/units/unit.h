#ifndef UNIT_H
#define UNIT_H

#include "../resource.h"

class Unit
{
public:
   int id;
   Point position;
   int health;
   int attackDamage;//damage that the unit deals per hit
   int attackRange; //distance that the unit can successfully attack
   int attackSpeed; //the speed which the attack counter has to hit in order to initiate an attack
   int perception;  //distance that the unit can aquire a target
   int attackCount; //counter between unit attacks

   bool isAlive() { return health == 0; }
   void serializeUnit(const Unit& unit);
private:   
};

#endif
