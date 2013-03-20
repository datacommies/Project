#include "projectile.h"
#include "unit.h"
#include "creep.h"

using namespace std;

Projectile::Projectile(int uid, Point pos, int hp, int atkdmg, int atkrng,
         int atkspd, int percep, int atkcnt, int spd, Direction direct,
         Point* path, int movespeed): Creep(uid, pos, hp, atkdmg, atkrng, atkspd,
         percep, atkcnt,spd, direct)
{
    //validation
    //psaved is initialized to NULL so that the game doesn't crash!
}

