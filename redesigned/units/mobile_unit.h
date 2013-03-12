#ifndef MOBILE_UNIT_H
#define MOBILE_UNIT_H

#include "../resource.h"
#include "../types.h"
#include "unit.h"

class MobileUnit : public Unit
{
public:
    int speed;
    Direction direction;
   
    MobileUnit(const int& uid, Point pos, const int& hp, const int& atkdmg, const int& atkrng,
        const int& atkspd, const int& percep, const int& atkcnt, const int& spd, Direction direct);
    
    std::string serializeMobileUnit(const MobileUnit& mobileUnit);

	virtual UnitTypes getType() const = 0;
	virtual size_t getSize() const = 0;

private:   
};

#endif
