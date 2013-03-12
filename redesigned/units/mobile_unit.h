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
   
    MobileUnit(const int& uid, Point pos, const int& hp, const int& atkdmg, const int& atkrng,
        	   const int& atkspd, const int& percep, const int& atkcnt, const int& spd, Direction direct);

    void	Move( Point );

    void    setDirection(Direction newDirect) { direction = newDirect; }
	void	setSpeed(int newSpeed) { moveSpeed = newSpeed; }
    int     getSpeed(){ return moveSpeed; }
    Direction getDirection(){ return direction; }
    virtual UnitTypes getType() const = 0;
    virtual size_t getSize() const = 0;

    std::string serializeMobileUnit(const MobileUnit& mobileUnit);

private:   
};

#endif
