#include "mobile_unit.h"
#include <string>

using namespace std;

MobileUnit::MobileUnit(const int& uid, Point pos, const int& hp, const int& atkdmg, const int& atkrng,
                       const int& atkspd, const int& percep, const int& atkcnt, const int& spd, Direction direct):
                       Unit(uid, pos, hp, atkdmg, atkrng, atkspd, percep, atkcnt), moveSpeed(spd), direction(direct)
{
    //validation
}

/*
* Move the current point towards the target point based on Speed. 
* this is what the creep move should be, not the mobile units
*
void MobileUnit::Move( Point pt ) {
    //position.x += getDirection( position.x, pt.x ) * moveSpeed;
    //position.y += getDirection( position.y, pt.y )  * moveSpeed;
}*/

string MobileUnit::serializeMobileUnit()
{
    string s = Unit::serializeUnit();
    
    mobileunit_t m;
    m.speed = moveSpeed;
    m.direction = direction;
    s += string((char*)&m, sizeof(mobileunit_t));
    cout  << "MobileUnit Serialized: |"  << s << "| size: " << s.size() << endl;
    return s;
}