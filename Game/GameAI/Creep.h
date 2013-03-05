#ifndef CREEP_H
#define CREEP_H
#include "Point.h"
#include "Attackable.h"
#include "Attacker.h"


class Creep: public Attacker {
public:
	Creep(): pPath( 0 ), pSaved( 0 ), iSpeed( 0 ) {}
	Creep( const Creep& );
	void	Update( void );
	void	setSpeed( int newSpeed) { iSpeed = newSpeed; }
	void	setPath( Point *pt )	{ pPath = pt; }
	void	nextPoint( void )	{ pPath++; }
	void	savePoint( Point &pt )	{ pSaved = &pt; }
	void	Move( Point );
	int	getDirection( int, int );

	Point	*pPath;
	Point	*pSaved;
	int	iSpeed;
};

class Tank: public Creep {
public:
	Tank() {
		iHp		= 2000;
		iDamage		= 3;
		iSpeed		= 5;
		iRange		= 20;
		iPerception	= 50;
		iAttackSpeed	= 5;
		iElement	= ELEMENT_WATER;
		name		= "Tank";
	}
};

class DPS: public Creep {
public:
	DPS() {
		iHp		= 250;
		iDamage		= 12;
		iSpeed		= 4;
		iRange		= 20;
		iPerception	= 100;
		iAttackSpeed	= 5;
		iElement	= ELEMENT_FIRE;
		name		= "DPS";
	}
};
#endif
