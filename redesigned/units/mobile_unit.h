#ifndef MOBILE_UNIT_H
#define MOBILE_UNIT_H

#include "../resource.h"
#include "../types.h"
#include "unit.h"

class MobileUnit : public Unit
{
public:
    int moveSpeed;   //the speed which a unit can move. ex. (it can move 1 square per 30 frames)
    Direction direction;
    int moveCounter;
   
    MobileUnit(int uid, Point pos, int hp, int atkdmg, int atkrng,
        	   int atkspd, int percep, int atkcnt, int spd, Direction direct);

    void    setDirection(Direction newDirect) { direction = newDirect; }
	void	setSpeed(int newSpeed) { moveSpeed = newSpeed; }
    int     getSpeed(){ return moveSpeed; }
    Direction getDirection(){ return direction; }
    virtual UnitType getType() const = 0;
    virtual size_t getSize() const { return sizeof(unit_t)+sizeof(mobileunit_t); }

    std::string serializeMobileUnit();

private:   
};

#endif
