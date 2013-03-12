#include "unit.h"
#include <string>

using namespace std;

Unit::Unit(const int& uid, Point pos, const int& hp, const int& atkdmg,
           const int& atkrng, const int& atkspd, const int& percep, const int& atkcnt):
           id(uid), position(pos), health(hp), attackDamage(atkdmg), attackRange(atkrng),
           attackSpeed(atkspd), perception(percep), attackCount(atkcnt)
{
    //any required validation

}

string Unit::serializeUnit(const Unit& unit){
    return 0;
}
