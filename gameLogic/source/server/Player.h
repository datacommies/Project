#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Point.h"
#include <string>

class Player {
private:
	long _id;
	int _hp;
	std::string _class;
	Point _currentCoordinates;
	int _attackPoint;
	int _defendPoint;
	//perhaps some other status to the character
	int _movementSpeed;

	int _status;	//ready or not, which stage is he/she on...
	//etc...
  
public:
	Player(long id, int hp, std::string playClass, Point coord, int atkPtr, int defPtr, int mSpeed, int status);
	long getID();
	void setID(long);
	int getHP();
	void setHP(int);
	std::string getClass();
	void setClass(std::string);
	Point getCoord();
	void setCoord(Point);
	int getAtkPoint();
	void setAtkPoint(int);
	int getDefPoint();
	void setDefPoint(int);
	int getMoveSpeed();
	void setMoveSpeed(int);
	int getStatus();
	void setStatus(int);
	std::string getPlayerClass();
	void setPlayerClass(std::string playClass);
};
#endif
