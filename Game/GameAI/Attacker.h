#ifndef ATTACKER_H
#define ATTACKER_H
#include "Point.h"
#include "Attackable.h"
#include <vector>

class Attacker: public Attackable {
	public:

		Attacker()
			:pTarget( 0 ), iAttackCount( 0 )
		{}
		Attacker( const Attacker& a )
			:Attackable( a), pTarget( a.pTarget ), iAttackCount( a.iAttackCount ), 
			iDamage( a.iDamage ), iRange( a.iRange ), iPerception( a.iPerception ), 
			iAttackSpeed( a.iAttackSpeed ), fRotatation( a.fRotatation )
		{}
		void			Attack( void );
		virtual void	Update( void );
		void			setTarget( Attackable &newTarget ) { pTarget = &newTarget; }
		float			Rotate( Point ); 
		void			setDamage( int newDamage ) { iDamage = newDamage;  }
		void			setRange( int newRange ) { iRange = newRange; }
		bool			inRange( Point, Point, int );
		virtual void	CheckTarget( void );
		virtual void	FindTarget( void );
		bool			hasWeakness( int, int );

		int				iDamage;
		int				iRange;
		int				iPerception;

		int				iAttackCount;
		int				iAttackSpeed;

		Attackable	*pTarget; /* Needs to be INIT() to NULL. */
		float		fRotatation;
};

#endif