#include "unit.h"
#include "creep.h"
#include <iostream>
#include <string>

using namespace std;

Creep::Creep(const int& uid, Point pos, const int& hp, const int& atkdmg, const int& atkrng,
             const int& atkspd, const int& percep, const int& atkcnt, const int& spd, Direction direct,
             Point* path, const int& movespeed): MobileUnit(uid, pos, hp, atkdmg, atkrng, atkspd,
             percep, atkcnt,spd, direct), pPath(path), moveSpeed(movespeed)
{
	//validation
}

string Creep::serializeCreep(const Creep& creep)
{

}

#endif
