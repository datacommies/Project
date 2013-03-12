#include "tower.h"
#include "unit.h"
#include <string>

using namespace std;

Tower::Tower(const int& uid, Point pos, const int& hp, const int& atkdmg, const int& atkrng,
            const int& atkspd, const int& percep, const int& atkcnt, const int& wall):
            Unit(uid, pos, hp, atkdmg, atkrng, atkspd, percep, atkcnt), wallArmour_(wall)
{
    //validation
}

string Tower::serializeTower(){
    string s;
    s = Unit::serializeUnit();

    tower_t t;
    t.wallArmour = wallArmour_;
    
    s += string(&t, sizeof(t));
    
    return s;
}
