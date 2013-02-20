#ifndef TOWER_H
#define TOWER_H

class Tower: public Attacker {
	public:
		Point pPath;
		Point pSaved;
};

class SingleShot: public Tower {
	public:
		SingleShot() {
			iHp			= 2000;
			iDamage		= 30;
			iRange		= 25;
			iPerception = 25;
			iElement	= ELEMENT_GRASS;
			name = "Single";
		}
};

class MultiShot: public Tower {
	public:
		MultiShot() {
			iHp			= 250;
			iDamage		= 15;
			iRange		= 15;
			iPerception = 25;
			name = "Multi";
		}
};
#endif