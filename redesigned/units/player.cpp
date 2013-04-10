/*------------------------------------------------------------------------------
-- FILE:        player.cpp
--
-- DATE:        2013/03/11
--
-- MAINTAINERS: Callum Styan, Behnam Bastami
--
-- FUNCTIONS:   Player constructor
--
-- DESCRIPTION: File contains implementation for the Player class.
------------------------------------------------------------------------------*/
#include "player.h"
#include <string>

using namespace std;

Player::Player(int uid, int cid, Point pos, int role, int hp, int atkdmg, int atkrng,
               int atkspd, int percep, int atkcnt, int spd, Direction direct)
               : MobileUnit(uid, pos, hp, atkdmg, atkrng, atkspd, percep, atkcnt, spd, direct), clientID(cid), role(role)
{
    //validation
}
