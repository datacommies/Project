#ifndef CREEP_H
#define CREEP_H

#include "../resource.h"
#include "../types.h"
#include "unit.h"
#include "mobile_unit.h"

class Creep : public MobileUnit
{
public: 
    //what is spawn? call ctor mutliple times?
  	void spawn(int num);  //also creep type? when we have a type
	std::string serializeCreep();

	virtual UnitType getType() const { return CREEP; }
	virtual size_t getSize() const { return MobileUnit::getSize(); }

	Creep(int uid, Point pos, int hp = 0, int atkdmg = 0, int atkrng = 0,
          int atkspd = 0, int percep = 0, int atkcnt = 0, int spd = 0, Direction direct = Direction(),
          Point* path=NULL, int movespeed = 0); 
             

	Creep(int uid, int side, Point pos, Point* path, int hp = 100, int atkdmg = 10, int atkrng = 10,
             int atkspd = 10, int percep = 10, int atkcnt = 30, int movespeed = 10,
             Direction direct = Direction());

	
	void	setPath(Point *pt)	{ pPath = pt; }
	void	nextPoint(void)	{ pPath++; }
	void	savePoint(Point &pt)	{ pSaved = &pt; }
	void    Move(Point);
	int		getTargetDirection(int, int);
	void	setTarget(Unit &newTarget) { pTarget = &newTarget; }
	void    Update( Team& team );
	bool    hasWeakness(int, int);

	Point	*	pPath; //contains all points for the creeps path
	Point	*	pSaved; //user to save the point the creep is at when it's AI diverges it from the set path


private:
};

#endif
