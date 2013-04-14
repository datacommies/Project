/*------------------------------------------------------------------------------
-- FILE:        player.cpp
--
-- DATE:        2013/03/11
--
-- MAINTAINERS:  Behnam Bestami, Aaron Lee, Jesse Wright
--
-- FUNCTIONS:   Player constructor
--
-- DESCRIPTION: File contains implementation for the Player class.
------------------------------------------------------------------------------*/
#include "player.h"
#include <string>

using namespace std;
/*------------------------------------------------------------------------------
-- CONSTRUCTOR:    Player
--
-- DATE:        2013/04/07
--
-- PROGRAMMER:  Jesse Wright
--
-- INTERFACE:   Player constructor
--
-- DESCRIPTION: Initializes values of the Player, and calls Mobile unit's ctor.
------------------------------------------------------------------------------*/
Player::Player(int uid, int cid, Point pos, int role, int hp, int atkdmg, int atkrng,
               int atkspd, int percep, int atkcnt, int spd, Direction direct, time_t tod)
               : MobileUnit(uid, pos, hp, atkdmg, atkrng, atkspd, percep, atkcnt, spd, direct), clientID(cid), role(role), tod(tod)
{
	// validation is done before this constructor is called.
}
/*------------------------------------------------------------------------------
-- FUNCTION:    Player
--
-- DATE:        2013/04/07
--
-- DESIGNER: Behnam Bestami, Aaron Lee
-- PROGRAMMER: Behnam Bestami, Aaron Lee
--
-- INTERFACE:   string serializeMobileUnit()
--
-- DESCRIPTION: Serializes the mobile unit for sending across the network.
------------------------------------------------------------------------------*/
string Player::serializeMobileUnit()
{
	    std::string s = Unit::serializeUnit();
	    
	    mobileunit_t m;
	    m.speed = moveSpeed;
	    m.direction = direction;
	    m.role = role;
	    s += std::string((char*)&m, sizeof(mobileunit_t));
	    return s;
}