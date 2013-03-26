#include "castle.h"
#include "tower.h"
#include <string>

using namespace std;

Castle::Castle(int uid, Point pos, int hp, int atkdmg, int atkrng,
    int atkspd, int percep, int atkcnt, int wall, int cid):
    Tower(uid, pos, hp, atkdmg, atkrng, atkspd, percep, atkcnt, wall), 
    clientID_(cid)
{
    // validation
}

Castle::Castle(int cid, int uid, int side, Point pos, int hp, int atkdmg, int atkrng,
    int atkspd, int percep, int atkcnt, int wall):
    Tower(uid, side, pos, hp, atkdmg, atkrng, atkspd, percep, atkcnt, wall), 
    clientID_(cid)
{
    // validation
}
