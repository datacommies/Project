#ifndef CREEP_H
#define CREEP_H

#include "../resource.h"
#include "../types.h"
#include "unit.h"
#include "mobile_unit.h"

class Creep : public MobileUnit
{
public: 
  	void spawn(int num);  //also creep type? when we have a type
	std::string serializeCreep();

	virtual UnitType getType() const { return CREEP; }
	virtual size_t getSize() const { return MobileUnit::getSize(); }

	Creep(int uid = 0, Point pos = Point(), int hp = 0, int atkdmg = 0, int atkrng = 0,
          int atkspd = 0, int percep = 0, int atkcnt = 0, int spd = 0, Direction direct = Direction(),
          Point* path=NULL, int movespeed = 0); 
          
          //assuming psaved does not need to be initialized when creep is created

	//bad
	//Creep(): pPath( 0 ), pSaved( 0 ), moveSpeed( 0 ){}

	//Creep(const Creep&);
	void	setPath(Point *pt)	{ pPath = pt; }
	void	nextPoint(void)	{ pPath++; }
	void	savePoint(Point &pt)	{ pSaved = &pt; }
	void    Move(Point);
	int		getTargetDirection(int, int);
	void	setTarget(Unit &newTarget) { pTarget = &newTarget; }
	void    Update( Team& team );


	//virtual void	CheckTarget(void) {}
	//virtual void	FindTarget(void) {}
	bool			hasWeakness(int, int);

	Point	*	pPath;
	Point	*	pSaved;


private:
};

#endif
