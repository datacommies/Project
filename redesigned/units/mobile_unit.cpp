#include "mobile_unit.h"
#include <string>

using namespace std;

MobileUnit::MobileUnit(const int& uid, Point pos, const int& hp, const int& atkdmg, const int& atkrng,
                       const int& atkspd, const int& percep, const int& atkcnt, const int& spd, Direction direct):
                       Unit(uid, pos, hp, atkdmg, atkrng, atkspd, percep, atkcnt), speed(spd), direction(direct)
{
    //validation
}

/*
* Move the current point towards the target point based on Speed. 
*/
void MobileUnit::Move( Point pt ) {
    pCurrPoint.x += getDirection( pCurrPoint.x, pt.x ) * moveSpeed;
    pCurrPoint.y += getDirection( pCurrPoint.y, pt.y )  * moveSpeed;
}

string MobileUnit::serializeMobileUnit(const MobileUnit& mobileUnit)
{
    return 0;
}
