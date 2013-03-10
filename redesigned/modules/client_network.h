#ifndef CLIENTNETWORK_H
#define CLIENTNETWORK_H

#include "../resource.h"

class ClientNetwork
{
public:
   // Functions
   bool createUnit(int playerId, UnitType type, Point location);
   bool movePlayer(int playerId, Direction direction);
   bool attack(int playerId, Direction direction);   
private:
};

#endif