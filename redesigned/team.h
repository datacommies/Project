#ifndef TEAM_H
#define TEAM_H

#include <vector>
#include "resource.h"
#include "units/player.h"
#include "units/creep.h"
#include "units/tower.h"
#include "units/projectile.h"

class Team
{
public:
   std::vector<Creep> creeps;
   std::vector<Tower> towers;
   std::vector<Player> players;
   std::vector<PATH> paths;
   std::vector<Projectile> projectiles;
   int currency;
   int teamId;

   bool isAlive() { return towers.size() > 0 && towers[0].isAlive(); }
private:
};

#endif
