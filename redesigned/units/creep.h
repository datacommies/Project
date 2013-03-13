#ifndef CREEP_H
#define CREEP_H

#include "../resource.h"
#include "../types.h"
#include "unit.h"
#include "mobile_unit.h"

class Creep : public MobileUnit
{
public: 
  	void spawn(const int& num);  //also creep type? when we have a type
	std::string serializeCreep();

	virtual UnitTypes getType() const { return TYPE_CREEP; }
	virtual size_t getSize() const { return MobileUnit::getSize(); }

	Creep(const int& uid = 0, Point pos = Point(), const int& hp = 0, const int& atkdmg = 0, const int& atkrng = 0,
          const int& atkspd = 0, const int& percep = 0, const int& atkcnt = 0, const int& spd = 0, Direction direct = Direction(),
          Point* path=NULL, const int& movespeed = 0); 
          //assuming psaved does not need to be initialized when creep is created

	//bad
	//Creep(): pPath( 0 ), pSaved( 0 ), moveSpeed( 0 ){}

	//Creep(const Creep&);
	void	Update(void);
	void	setPath(Point *pt)	{ pPath = pt; }
	void	nextPoint(void)	{ pPath++; }
	void	savePoint(Point &pt)	{ pSaved = &pt; }
	void    Move(Point) {}
	int		getTargetDirection(int, int);
	void	setTarget(Unit &newTarget) { pTarget = &newTarget; }


	virtual void	CheckTarget(void) {}
	virtual void	FindTarget(void) {}
	bool			hasWeakness(int, int);

	Point	*	pPath;
	Point	*	pSaved;


private:
};

#endif
