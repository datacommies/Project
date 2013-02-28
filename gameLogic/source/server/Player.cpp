#include "Player.h"

Player::Player(long id, int hp, string playClass, Point coord, int atkPtr, int defPtr, int mSpeed, int status) :
		_id(id), _hp(hp), _class(playClass), _currentCoordinates(coord), _attackPoint(atkPtr),
		_defendPoint(defPtr), _movementSpeed(mSpeed), _status(status);

long Player::getID(){
	return _id;
}

void Player::setID(long id){
	_id = id;
}

int Player::getHP(){
	return _hp;
}

void Player::setHP(int hp){
	_hp = hp;
}

string Player::getPlayerClass(){
	return _class;
}

void Player::setPlayerClass(string playClass){
	_class = playClass;
}

Point Player::getCoord(){
	return _currentCoordinates;
}

void Player::setCoord(Point coord){
	_currentCoordinates = coord;
}

int Player::getAtkPoint(){
	return _attackPoint;
}

void Player::setAtkPoint(int atkPtr){
	_attackPoint = atkPtr;
}

int Player::getDefPoint(){
	return _defendPoint;
}

void Player::setDefPoint(int defPtr){
	_defendPoint = defPtr;
}

int Player::getMoveSpeed(){
	return _movementSpeed;
}

void Player::setMoveSpeed(int mSpeed){
	_movementSpeed = mSpeed;
}

int Player::getStatus(){
	return _status;
}

void Player::setStatus(int status){
	_status = status;
}
