#ifndef PLAYER_H
#define PLAYER_H

#include "../resource.h"
#include "../types.h"
#include "mobile_unit.h"

class Player : public MobileUnit
{
public:
    int clientID;
   
    Player(int uid, Point pos, int hp, int atkdmg, int atkrng,
          int atkspd, int percep, int atkcnt, int spd, Direction direct,
          int cid);

    std::string serializePlayer();

    virtual void Attack(void);
    virtual void Update(void);
    virtual void Move(void);

    virtual UnitTypes getType() const { return TYPE_PLAYER; }
	virtual size_t getSize() const { return MobileUnit::getSize(); }

private:   
};

#endif
