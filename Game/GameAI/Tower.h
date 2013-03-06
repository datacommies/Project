#ifndef TOWER_H
#define TOWER_H
#include "Point.h"
#include "Attackable.h"
#include "Attacker.h"

class Tower: public Attacker {
	public:
};

class SingleShot: public Tower {
	public:
		SingleShot() {
			iHp			= 2000;
			iDamage			= 12;
			iRange			= 25;
			iPerception		= 25;
			iAttackSpeed		= 5;
			iElement		= ELEMENT_GRASS;
			name			= "Single";
		}
};

class MultiShot: public Tower {
	public:
		Attackable	*pTarget2;
		Attackable	*pTarget3;

		 virtual void	Update( void );
		 virtual void	FindTarget( void );
		 virtual void CheckTarget( void );

		MultiShot() {
			iHp			= 500;
			iDamage			= 5;
			iRange			= 15;
			iPerception		= 25;
			iAttackSpeed		= 5;
			iElement		= ELEMENT_GRASS;
			name			= "Multi";
			pTarget2		= 0;
			pTarget3		= 0;
		}
};

class AreaShot: public Tower {
		public:
			int iSplash;

		AreaShot() {
			iHp			= 1750;
			iDamage			= 10;
			iRange			= 15;
			iPerception		= 25;
			iAttackSpeed		= 5;
			iElement		= ELEMENT_GRASS;
			name			= "AOE";
			iSplash			= 15;
		}
};

#endif
