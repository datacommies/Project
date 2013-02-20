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

/*
* Used to check if the target has a weakness to the attacker's element.
*/
bool Attacker::hasWeakness( int iAttack, int iTarget ) {
	if( iAttack == iTarget + 1 % ELEMENT_COUNT )
		return true;
	return false;
}

/*
* Attacks the current target. If it has a weakness, it will apply a 75% damage bonus.
* QUESTION - If we attack a element we have a weakness against, do we do LESS damage? 
*/
void Attacker::Attack() {
	Point target = pTarget->getPos();

	std::cout << name << iTeam <<   " Attacking " << pTarget->name << pTarget->iTeam;
	if( hasWeakness( iElement, pTarget->iElement ) )
		pTarget->iHp -= iDamage * 1.75;
	else
		pTarget->iHp -= iDamage;

	if( pTarget->iHp <= 0 ) {
			/* KILL TARGET. */
	}
	std::cout << " HP of Target ( " << pTarget->iHp << " )\n"; 
}

/*
* Finds the next target, will loop through all enemies until one target is found.
* TODO - Add priority. ( Attack players over creeps )
*/
void Attacker::FindTarget( void ) {
	std::vector<Attackable*>::iterator it = Game::getEnemiesBegin( iTeam );
	std::vector<Attackable*>::iterator end = Game::getEnemiesEnd( iTeam );

	for( ; it != end; ++it ) {
		/* If in range and alive, set as target. */
		if( inRange( pCurrPoint, (*it)->getPos(), iPerception ) && (*it)->iHp > 0 ) {
			std::cout << "Found new Target." << std::endl;
			pTarget = *it;
			break;
		}
	}
}

/*
* Check if the target is alive and in range. Set the pTarget to NULL if either are true.
*/
void Attacker::CheckTarget( void ) {
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

/*
* If we have an attackable target, attack.
*/
void Attacker::Update() {

	/* If we have a Target, check their status. */
	if( pTarget != NULL )
		CheckTarget();

	/* Search for Target. */
	if( pTarget == NULL )
		FindTarget();

	/* If we found a new Target, and they are in range.. */
	if( pTarget != NULL ) {
		Attack(); /* Only move if unable to attack. */	
		Rotate( pTarget->getPos() );
	}
}

/*
* Rotate towards the target. Used for either a path, or a target. 
*/
float Attacker::Rotate( Point pt ) {
	return atan2( (float)pCurrPoint.y - pt.y, (float)pCurrPoint.x - pt.x );
}
	