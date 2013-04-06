#include "player.h"
#include <string>

using namespace std;

Player::Player(int uid, Point pos, int hp, int atkdmg, int atkrng,
               int atkspd, int percep, int atkcnt, int spd, Direction direct,
               int cid) : MobileUnit(uid, pos, hp, atkdmg, atkrng, atkspd, percep, atkcnt, spd, direct), clientID(cid)
{
    //validation
}

Player::Player(int uid, int cid, Point pos, int hp, int atkdmg, int atkrng,
               int atkspd, int percep, int atkcnt, int spd, Direction direct)
               : MobileUnit(uid, pos, hp, atkdmg, atkrng, atkspd, percep, atkcnt, spd, direct), clientID(cid)
{
    //validation
}
