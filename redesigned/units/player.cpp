#include "player.h"
#include "mobile_unit.h"
#include <string>

using namespace std;

Player::Player(const int& uid, const int& pos, const int& hp, const int& atkdmg, const int& atkrng,
               const int& atkspd, const int& percep, const int& atkcnt, const int& spd, Direction direct,
               const int& cid): MobileUnit(uid, pos, hp, atkdmg, atkrng, atkspd, percep, atkcnt, spd, )

string Player::serializePlayer(const Player& player)
{
	
}
