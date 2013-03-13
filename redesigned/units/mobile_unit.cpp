#include "mobile_unit.h"
#include <string>

using namespace std;

MobileUnit::MobileUnit(int uid, Point pos, int hp, int atkdmg, int atkrng,
                       int atkspd, int percep, int atkcnt, int spd, Direction direct):
                       Unit(uid, pos, hp, atkdmg, atkrng, atkspd, percep, atkcnt), moveSpeed(spd), direction(direct)
{
    //validation
}

/*
* Move the current point towards the target point based on Speed. 
* this is what the creep move should be, not the mobile units
*/
void MobileUnit::Move( Point pt ) {
    //position.x += getDirection( position.x, pt.x ) * moveSpeed;
    //position.y += getDirection( position.y, pt.y )  * moveSpeed;
}

string MobileUnit::serializeMobileUnit()
{
    string s = Unit::serializeUnit();
    
    mobileunit_t m;
    m.speed = speed;
    m.direction = direction;
    s += string(&m, sizeof(mobileunit_t));
    
    return s;
}
