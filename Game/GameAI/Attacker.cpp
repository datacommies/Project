#include "Attacker.h"
#include <iostream>
#include <math.h>
#include "Game.h"

/*
* Using the a^2 + b^2 = c^2 formula to calculate if the target is within a circle.
*/
bool Attacker::inRange( Point p1, Point p2, int distance ) {
	 if( sqrt( (double)	/* Square Rooting the entire thing. */
				pow( (double)abs( p1.x - p2.x ), 2 )	/* a^2; the adj si\de. */
				+ pow( (double)abs( p1.y - p2.y ), 2 ) /* add b^2; the opp side.*/
			) > distance ) /* And checking if it's larger than the distance.*/
			return false;
	 return true;
}

bool Attacker::Attack() {
	Point target = pTarget->getPos();
	
	if( inRange( pCurrPoint, target, iRange) ) {
		std::cout << name << iTeam <<   " Attacking " << pTarget->name << pTarget->iTeam;
		if( pTarget->iElement == iElement + 1 % 3 ) {
			std::cout << " Very effective ";
			pTarget->iHp -= iDamage * 1.75;
		}
		else
			pTarget->iHp -= iDamage;

		if( pTarget->iHp <= 0 ) {
			
		}
		std::cout << " HP of Target ( " << pTarget->iHp << " )\n"; 
		return true;
	}
	return false;
}

void Attacker::Update() {
	if( pTarget != NULL ) { 
		/* Target is DEAD. */

		if( pTarget->iHp <= 0 ) {
			std::cout << "Target is dead.\n";
			pTarget = NULL;
		}
		/* Or Target is out of range.  */
		else if ( inRange( pCurrPoint, pTarget->getPos(), iPerception) == false ) {	
			std::cout << "Target out of range." << std::endl;
			pTarget = NULL;
		}
	}

	/* Search for Target. */
	if( pTarget == NULL ) {

		std::vector<Attackable*>::iterator it = Game::getEnemiesBegin( iTeam );
		std::vector<Attackable*>::iterator end = Game::getEnemiesEnd( iTeam );
		
		for( ; it != end; ++it ) {

			if( inRange( pCurrPoint, (*it)->getPos(), iPerception ) && (*it)->iHp > 0 ) {
				std::cout << "Found new Target." << std::endl;
				pTarget = *it;
				break;
			}
			
		}

	}

		/* If we found a new Target. */

	if( pTarget != NULL ) {
		//std::cout << "Target Move." << std::endl;
		if( Attack() == false ) /* Only move if unable to attack. */
			std::cout << "Unable to Reach." << std::endl;
	
		Rotate( pTarget->getPos() );
	}
}

float Attacker::Rotate( Point pt ) {
	return atan2( (float)pCurrPoint.y - pt.y, (float)pCurrPoint.x - pt.x );
}
	