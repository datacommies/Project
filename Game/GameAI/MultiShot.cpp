#include "Tower.h"
#include "Game.h"

/*
* Override: 
* FindTarget -- Find 3 Targets.
* Update -- Call everything on 3 Targets.
* CheckTarget -- Check all 3 Targets. 
*/

/*
* FindTarget -- This will attempt to find 3 targets for the MultiShot tower.
*/
void MultiShot::FindTarget( void ) {
	std::vector<Attackable*>::iterator it = Game::getEnemiesBegin( iTeam );
	std::vector<Attackable*>::iterator end = Game::getEnemiesEnd( iTeam );

	for( ; it != end; ++it ) {
		/* If in range and alive, set as target. */
		if( inRange( pCurrPoint, (*it)->getPos(), iPerception ) && (*it)->iHp > 0 ) {
			if( pTarget2 != *it && pTarget3 != *it && pTarget == NULL )
				pTarget = *it;
			else if ( pTarget != *it && pTarget3 != *it && pTarget2 == NULL )
				pTarget2 = *it;
			else if (pTarget != *it && pTarget2 != *it && pTarget3 == NULL ) {
				pTarget3 = *it;
			}
			/* If we have 3 targets, break. */
			if( pTarget != NULL && pTarget2 != NULL && pTarget3 != NULL ) {
				return;
			}
		}
	}

	
	/* 
	* If we haven't returned, then we didn't acquire 3 targets.
	* Check if we have a first target, and put him in the empty spots.
	*
	if( pTarget != NULL ) {
		if( pTarget2 == NULL ) {
			pTarget2 = pTarget;
		}
		if( pTarget3 == NULL ) {
			pTarget3 = pTarget;
		}
	} else if( pTarget2 != NULL ) {
		if( pTarget == NULL ) {
			pTarget = pTarget2;
		}
		if( pTarget3 == NULL ) {
			pTarget3 = pTarget2;
		}
	} else if( pTarget3 != NULL ) {
		if( pTarget == NULL ) {
			pTarget = pTarget3;
		}
		if( pTarget2 == NULL ) {
			pTarget2 = pTarget3;
		}
	}
	*/
}

/*
* MultiShot::CheckTarget, this will rotate the targets around to check if any of them are invalid.
* Using Attacker::CheckTarget() to check pTarget. 
*/
void MultiShot::CheckTarget( void ) {
	Attackable *temp;

	/* Since we have 3 targets, check the first then rotate them. */
	Attacker::CheckTarget();

	/*Check the 2nd target. */
	if( pTarget2 != NULL ) {
		temp = pTarget;
		pTarget = pTarget2;
		Attacker::CheckTarget();
		pTarget2 = pTarget;
		pTarget = temp;
	}
	/*Check the 3nd target. */
	if( pTarget3 != NULL ) {
		temp = pTarget;
		pTarget = pTarget3;
		Attacker::CheckTarget();
		pTarget3 = pTarget;
		pTarget = temp;
	}

}

void MultiShot::Update( void ) {
	Attackable *temp;

	/* If we have Targets, check their status. */
	if( pTarget != NULL  || pTarget2 != NULL || pTarget3 != NULL )
		CheckTarget();

	/* Search for Targets. */
	if( pTarget == NULL || pTarget2 == NULL || pTarget3 == NULL )
		FindTarget();

	/* If we found a new Target, and they are in range.. */
	if( pTarget != NULL )
		Attack();

	/*Using a temp target to hold the pTarget. This way we don't have to override Attack().*/
	if( pTarget2 != NULL ) {
		temp = pTarget;
		pTarget = pTarget2;
		Attack();
		pTarget = temp;
	}

	if( pTarget3 != NULL ) {
		temp = pTarget;
		pTarget = pTarget3;
		Attack();
		pTarget = temp;
	}
}
