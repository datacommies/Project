#include "mobile_unit.h"
#include <string>

using namespace std;

MobileUnit::MobileUnit(int uid, Point pos, int hp, int atkdmg, int atkrng,
                       int atkspd, int percep, int atkcnt, int spd, Direction direct):
                       Unit(uid, pos, hp, atkdmg, atkrng, atkspd, percep, atkcnt), moveSpeed(spd), direction(direct)
{
    //validation
}

string MobileUnit::serializeMobileUnit()
{
    string s = Unit::serializeUnit();
    
    mobileunit_t m;
    m.speed = moveSpeed;
    m.direction = direction;
    s += string((char*)&m, sizeof(mobileunit_t));
    return s;
}
