#include "electro_tower.h"
#include "unit.h"
#include <string>

using namespace std;

ElectroTower::ElectroTower(const int& uid, Point pos, const int& hp, const int& atkdmg, const int& atkrng,
            const int& atkspd, const int& percep, const int& atkcnt, const int& wall):
            Tower(uid, pos, hp, atkdmg, atkrng, atkspd, percep, atkcnt, wall)
{
    //validation
}
