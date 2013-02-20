#ifndef ATTACKER_H
#define ATTACKER_H
#include "Point.h"
#include "Attackable.h"
#include <vector>

class Attacker: public Attackable {
	public:
		bool			Attack();
		virtual void	Update();
		void			setTarget( Attackable &newTarget ) { pTarget = &newTarget; }
		float			Rotate( Point ); 
		void			setDamage( int newDamage ) { iDamage = newDamage;  }
		void			setRange( int newRange ) { iRange = newRange; }
		bool			inRange( Point, Point, int );

		int			iDamage;
		int			iRange;
		int			iPerception;

		Attackable	*pTarget; /* Needs to be INIT() to NULL. */
		float		fRotatation;
};

#endif