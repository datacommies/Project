#include "castle.h"
#include "tower.h"
#include <string>

using namespace std;

Castle::Castle(const int& uid, Point pos, const int& hp, const int& atkdmg, const int& atkrng,
               const int& atkspd, const int& percep, const int& atkcnt, const int& wall, const int& cid):
               Tower(uid, pos, hp, atkdmg, atkrng, atkspd, percep, atkcnt, wall), clientID_(cid)
{
    //validation
}

string Castle::serializeCastle()
{
    return 0;
}
