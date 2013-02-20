#ifndef CREEP_H
#define CREEP_H
#include "Point.h"
#include "Attackable.h"
#include "Attacker.h"


class Creep: public Attacker {
	public:
		void	Update( void );
		void	setSpeed( int newSpeed) { iSpeed = newSpeed; }
		void	setPath( Point *pt )	{ pPath = pt; }
		void	nextPoint( void )		{ pPath++; }
		void	savePoint( Point &pt )	{ pSaved = &pt; }
		void	Move( Point );

		Point	*pPath;
		Point	*pSaved;
		int		iSpeed;
};

class Tank: public Creep {
	public:
		Tank() {
			iHp			= 2000;
			iDamage		= 3;
			iSpeed		= 5;
			iRange		= 20;
			iPerception = 50;
			iElement	= ELEMENT_WATER;
			name = "Tank";
		}
};

class DPS: public Creep {
	public:
		DPS() {
			iHp			= 250;
			iDamage		= 800;
			iSpeed		= 10;
			iRange		= 20;
			iPerception = 100;
			iElement	= ELEMENT_FIRE;
			name = "DPS";
		}
};
#endif