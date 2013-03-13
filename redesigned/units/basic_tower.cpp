/*
 * Basic tower attacks a single unit; default tower
 * - Basic implementation
*/
#include "basic_tower.h"
#include "unit.h"
#include <string>

using namespace std;

BasicTower::BasicTower(const int& uid, Point pos, const int& hp, const int& atkdmg, const int& atkrng,
            const int& atkspd, const int& percep, const int& atkcnt, const int& wall):
            Tower(uid, pos, hp, atkdmg, atkrng, atkspd, percep, atkcnt, wall)
{
    //validation
}

