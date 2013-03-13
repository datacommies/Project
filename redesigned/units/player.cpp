#include "player.h"
#include <string>

using namespace std;

Player::Player(const int& uid, Point pos, const int& hp, const int& atkdmg, const int& atkrng,
               const int& atkspd, const int& percep, const int& atkcnt, const int& spd, Direction direct,
               const int& cid): MobileUnit(uid, pos, hp, atkdmg, atkrng, atkspd, percep, atkcnt, spd, direct), clientID(clientID)
{
    //validation
}

void Player::Attack(){
    //1) based on the units direction, check for enemy units
    //2) based on the players attack type, determine which enemies would be hit
    //3) send attack messages to the server for all those units
}

void Player::Move(){
    //1) player presses button to move
    //2) set direction?
    //I don't know
}

void Player::Update(){
    //what should this even do?   

    //check moveCounter? 
    //move counter should be = to movement speed
    //that way if your movement speed is 30, you move every 1 second
}


string Player::serializePlayer(const Player& player)
{
	
}
