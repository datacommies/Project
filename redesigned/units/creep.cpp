#include "unit.h"
#include "creep.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <string>

using namespace std;

/*Copy constructor. */
/*
  Creep::Creep( const Creep &c ) 
		:Attacker( c ), pPath( c.pPath), iSpeed(c.iSpeed), pSaved(c.pSaved)
	{}
*/
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
	pCurrPoint.x += getDirection( pCurrPoint.x, pt.x ) * moveSpeed;
	pCurrPoint.y += getDirection( pCurrPoint.y, pt.y )  * moveSpeed;
}

/*
* Check if we're at the next path point, if we are, update the path target.
* If we can find an attackable target, attack or move towards them.
* If not, move along the path. 
*/
void Creep::Update( void ) {
	/* Check if we are at the next path point.  */
	if( pPath->x == pCurrPoint.x && pPath->y == pCurrPoint.y ) {
		nextPoint();
	}

	/*If we have a Target check their stats. */
	if( pTarget != NULL ) 
		CheckTarget();

	/* Search for Target. */
	if( pTarget == NULL ) {
		FindTarget();
		if( pTarget != NULL && pSaved == NULL )
			pSaved = &pCurrPoint;

	}

	/* If we found a new Target. */
	if( pTarget != NULL ) {
		if( inRange( pCurrPoint, pTarget->pCurrPoint, attackRange ) )
			Attack();
		else 
			Move( pTarget->getPos() );

		Rotate( pTarget->getPos() );
	} else { /*No target. Move along path. */
		if( pSaved == 0 )
			Move( *pPath );
		else
			Move( *pSaved );
		Rotate( *pPath );
	}
}

string Creep::serializeCreep(const Creep& creep)
{

}
