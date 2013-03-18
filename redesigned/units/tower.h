#ifndef TOWER_H
#define TOWER_H

#include "../resource.h"
#include "../types.h"
#include "unit.h"


/*
    please fix this class so that it is using members
    inherited from it's base classes
    for example: unit has an ID, but you're creating another
    id in here

    there are so many of these :/
*/
class Tower : public Unit
{
private:
	int uid_;
	Point pos;
	int hp;
	int atkdmg;
	int atkspd;
	int percep;
	int atkcnt;
	int wall;
    int wallArmour_;

public:
    Tower(int uid, Point pos, int hp, int atkdmg, int atkrng,
          int atkspd, int percep, int atkcnt, int wall);
	
	void setUId(const int id){ uid_ = id; }
	int getUId(){ return uid_; }
	void setPos(const Point pt){ pos.x = pt.x; pos.y = pt.y; }
	Point getPos(){ return pos; }
	void setHP(const int HP){ hp = HP; }
	int getHP(){ return hp; }
	void setAtkdmg(const int dmg){ atkdmg = dmg; }
	int getAtkdmg(){ return atkdmg; }
	void setAtkspd(const int speed){ atkspd = speed; }
	int getAtkspd(){ return atkspd; }
	void setPercep(const int p){ percep = p; }
	int getPercep(){ return percep; }
	void setAtkcnt(const int cnt){ atkcnt = cnt; }
	int getAtkcnt(){ return atkcnt; }
	void setWall(const int w){ wall = w; }
	int getWall(){ return wall; }
    void setWallArmour(const int& amount) { wallArmour_ = amount; }
    int getWallArmour() { return wallArmour_; }
    std::string serializeTower();

    virtual UnitType getType() const { return CASTLE; }
	virtual size_t getSize() const { return Unit::getSize() + sizeof(tower_t); }
};
#endif

