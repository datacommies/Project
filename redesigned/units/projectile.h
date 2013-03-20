#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "../resource.h"
#include "../types.h"
#include "creep.h"
#include "unit.h"
#include "mobile_unit.h"

class Projectile : public Creep
{
public:

	virtual UnitType getType() const {return PROJECTILE;}

	Projectile(int uid = 0, Point pos = Point(), int hp = 1, int atkdmg = 0, int atkrng = 0,
          int atkspd = 0, int percep = 0, int atkcnt = 0, int spd = 0, Direction direct = Direction(),
          Point* path=NULL, int movespeed = 0); 

    Point * pPath;
    Point * pSaved;
    void Attack(void);
    void Update(void);
    void CheckTarget(void);
	
private:
};

#endif
