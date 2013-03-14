#include "electro_tower.h"
#include "unit.h"
#include <string>

using namespace std;

ElectroTower::ElectroTower(int uid, Point pos, int hp, int atkdmg, int atkrng,
            int atkspd, int percep, int atkcnt, int wall):
            Tower(uid, pos, hp, atkdmg, atkrng, atkspd, percep, atkcnt, wall)
{
    //validation
}
