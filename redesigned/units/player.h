#ifndef PLAYER_H
#define PLAYER_H

#include "../resource.h"
#include "../types.h"
#include "mobile_unit.h"

class Player : public MobileUnit
{
public:
   int clientId;
   
   std::string serializePlayer(const Player& player);

	virtual UnitTypes getType() const { return TYPE_PLAYER; }
	virtual size_t getSize() const { return sizeof(Player); }

private:   
};

#endif
