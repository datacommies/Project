#ifndef UNIT_H
#define UNIT_H

#include "../resource.h"
#include "../types.h"

class Unit
{
public:
	int id;
	Point position;
	int health;
	int attackDamage;//damage that the unit deals per hit
	int attackRange; //distance that the unit can successfully attack
	int attackSpeed; //the speed which the attack counter has to hit in order to initiate an attack
	//int perception;  //distance that the unit can aquire a target
	//int attackCount; //counter between unit attacks

<<<<<<< HEAD
	bool isAlive() { return health == 0; }
	std::string serializeUnit(const Unit& unit);
	
	virtual UnitTypes getType() const = 0;
	virtual size_t getSize() const = 0;
	
=======
   bool isAlive() { return health > 0; } //Check incase a unit is hit for more than its remaining hp.
   void serializeUnit(const Unit& unit);
>>>>>>> 932982e50d58aea124570f9f5ed67c2de6f9db03
private:   
};

#endif
