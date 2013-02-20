#include "Creep.h"
#include "Game.h"
#include <iostream>
#include <vector>
#include <math.h>

/*
* Function to return the difference in two points. Used for movement. 
*/
int Creep::getDirection( int p1, int p2 ) {
	if( p1 < p2 ) /*Target is below or right. */
		return 1;
	else if ( p1 > p2 )  /* Target is above or left. */
		return -1;
	else /* Target on the same level. */
		return 0;
}

/*
* Move the current point towards the target point based on Speed. 
*/
void Creep::Move( Point pt ) {
	std::cout << "Moving "<< name << " " << pCurrPoint.x << ", " << pCurrPoint.y << " -> " << pt.x << ", " << pt.y << ".\n";
	pCurrPoint.x += getDirection( pCurrPoint.x, pTarget->pCurrPoint.x ) * iSpeed;
	pCurrPoint.y += getDirection( pCurrPoint.y, pTarget->pCurrPoint.y )  * iSpeed;
}

/*
* Check if we're at the next path point, if we are, update the path target.
* If we can find an attackable target, attack or move towards them.
* If not, move along the path. 
*/
void Creep::Update( void ) {
	/* Check if we are at the next path point.  */
	if( pPath->x == pCurrPoint.x && pPath->y == pCurrPoint.y ) {
		std::cout << "At Path Point (" << pPath->x << " ," << pPath->y << " )\n";
		nextPoint();
	}

	/*If we have a Target check their stats. */
	if( pTarget != NULL ) 
		CheckTarget();

	/* Search for Target. */
	if( pTarget == NULL )
		FindTarget();

	/* If we found a new Target. */
	if( pTarget != NULL ) {
		if( inRange( pCurrPoint, pTarget->pCurrPoint, iRange ) )
			Attack();
		else 
			Move( pTarget->getPos() );

		Rotate( pTarget->getPos() );
	} else { /*No target. Move along path. */
		Move( *pPath );
		Rotate( *pPath );
	}
}