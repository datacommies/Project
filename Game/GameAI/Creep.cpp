#include "Creep.h"
#include "Game.h"
#include <iostream>
#include <vector>
#include <math.h>

void Creep::Move( Point pt ) {
	int xDir, yDir;

	std::cout << "Moving "<< name << " " << pCurrPoint.x << ", " << pCurrPoint.y << " -> " << pt.x << ", " << pt.y << ".\n";

	if( pCurrPoint.x < pt.x ) { /* Target to the RIGHT.*/
		xDir = 1;
	} else if ( pCurrPoint.x > pt.x ) { /* Target to the LEFT.*/
		xDir = -1;
	} else { /* Target at same X. */
		xDir = 0;
	}

	if( pCurrPoint.y < pt.y ) { /* Target BELOW.*/
		yDir = 1;
	} else if ( pCurrPoint.y > pt.y ) { /* Target ABOVE.*/
		yDir = -1;
	} else { /* Target at same Y. */
		yDir = 0;
	}

	pCurrPoint.x += xDir * iSpeed;
	pCurrPoint.y += yDir * iSpeed;
}


void Creep::Update( void ) {

	if( pPath->x == pCurrPoint.x && pPath->y == pCurrPoint.y ) {
		std::cout << "At Path Point (" << pPath->x << " ," << pPath->y << " )\n";
		nextPoint();
	}

	/*If we have a Target check their stats. */
	if( pTarget != NULL ) { 

		/* Target is DEAD. */

		if( pTarget->iHp <= 0 ) {
			std::cout << pTarget->name << " is dead.\n";
			pTarget = NULL;
		}
		/* Or Target is out of range.  */
		else if ( inRange( pCurrPoint, pTarget->getPos(), iPerception) == false ) {	
			std::cout << pTarget->name << " out of range." << std::endl;
			pTarget = NULL;
		}
	}

	/* Search for Target. */
	if( pTarget == NULL ) {

		std::vector<Attackable*>::iterator it = Game::getEnemiesBegin( iTeam );
		std::vector<Attackable*>::iterator end = Game::getEnemiesEnd( iTeam );
		
		for( ; it != end; ++it ) {

			if( inRange( pCurrPoint, (*it)->getPos(), iPerception ) && (*it)->iHp > 0 ) {
				std::cout << "is my new Target." << std::endl;
				pTarget = *it;
				break;
			}
			
		}

	}

	/* If we found a new Target. */

	if( pTarget != NULL ) {
		//std::cout << "Target Move." << std::endl;
		if( Attack() == false ) {/* Only move if unable to attack. */
			std::cout << "Unable to Reach." << std::endl;
			Move( pTarget->getPos() );
		}

		Rotate( pTarget->getPos() );

	} else { /*No target. Move along path. */
		//std::cout << "Normal Move." << std::endl;
		Move( *pPath );
		Rotate( *pPath );
	}

}