#ifndef ATTACKER_H
#define ATTACKER_H
#include "Point.h"
#include "Attackable.h"
#include <vector>

class Attacker: public Attackable {
	public:
		void			Attack( void );
		virtual void	Update( void );
		void			setTarget( Attackable &newTarget ) { pTarget = &newTarget; }
		float			Rotate( Point ); 
		void			setDamage( int newDamage ) { iDamage = newDamage;  }
		void			setRange( int newRange ) { iRange = newRange; }
		bool			inRange( Point, Point, int );
		void			CheckTarget( void );
		void			FindTarget( void );
		bool			hasWeakness( int, int );

		int			iDamage;
		int			iRange;
		int			iPerception;

		Attackable	*pTarget; /* Needs to be INIT() to NULL. */
		float		fRotatation;
};

#endif