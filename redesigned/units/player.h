#ifndef PLAYER_H
#define PLAYER_H

#include "../resource.h"
#include "../types.h"
#include "mobile_unit.h"

class Player : public MobileUnit
{
public:
    int clientID;
   
    Player(const int& uid, Point pos, const int& hp, const int& atkdmg, const int& atkrng,
          const int& atkspd, const int& percep, const int& atkcnt, const int& spd, Direction direct,
          const int& cid);

    std::string serializePlayer();

    virtual void Attack( void );
    virtual void Update( void );

    virtual UnitTypes getType() const { return TYPE_PLAYER; }
	virtual size_t getSize() const { return MobileUnit::getSize(); }

private:   
};

#endif
