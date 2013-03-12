#include "mobile_unit.h"
#include "unit.h"
#include <string>

using namespace std;

MobileUnit::MobileUnit(const int& uid, Point pos, const int& hp, const int& atkdmg, const int& atkrng,
        const int& atkspd, const int& percep, const int& atkcnt, const int& spd, Direction direct):
        Unit(uid, pos, hp, atkdmg, atkrng, atkspd, percep, atkcnt), speed(spd), direction(direct)
{
    //validation?
}

string MobileUnit::serializeMobileUnit(const MobileUnit& mobileUnit)
{
    return 0;
}
