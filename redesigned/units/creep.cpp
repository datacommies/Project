#include "unit.h"
#include "creep.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <string>

using namespace std;

Creep::Creep(const int& uid, const int& pos, const int& hp, const int& atkdmg, const int& atkrng,
             const int& atkspd, const int& percep, const int& atkcnt, const int& spd, Direction direct,
             Point* path, const int& movespeed)
{
	//validation
}

/*Copy constructor. */
/*
  Creep::Creep( const Creep &c ) 
		:Attacker( c ), pPath( c.pPath), moveSpeed(c.iSpeed), pSaved(c.pSaved)
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

/*
* Using the a^2 + b^2 = c^2 formula to calculate if the target is within a circle.
*/
bool Creep::inRange( Point p1, Point p2, int distance ) {
	 if( sqrt( (double)				/* Square Rooting the entire thing. */
	     pow( (double)abs( p1.x - p2.x ), 2 )	/* a^2; the adj side. */
	     + pow( (double)abs( p1.y - p2.y ), 2 ) 	/* add b^2; the opp side.*/
	     ) > distance ) 				/* And checking if it's larger than the distance.*/
	     return false;
	 return true;
}

/*
* Used to check if the target has a weakness to the attacker's element.
*/
/*bool Creep::hasWeakness( int iAttack, int iTarget ) {
	if( iAttack == iTarget + 1 % ELEMENT_COUNT )
		return true;
	return false;
}*/

/*
* Attacks the current target. If it has a weakness, it will apply a 75% damage bonus.
* QUESTION - If we attack a element we have a weakness against, do we do LESS damage? 
*/
void Creep::Attack( void ) {
	if( attackCount++ < attackSpeed )
		return;

	attackSpeed = 0;
	/*if( hasWeakness( iElement, pTarget->iElement ) )
		pTarget->iHp -= iDamage * 1.75;
	else*/
		pTarget->health -= attackDamage;

	if( pTarget->health <= 0 ) {
		//Game::removeUnit( pTarget, pTarget->iTeam );
	}
}

/*
* Finds the next target, will loop through all enemies until one target is found.
* TODO - Add priority. ( Attack players over creeps )
*/
void Creep::FindTarget( void ) {
	//std::vector<Attackable*>::iterator it = Game::getEnemiesBegin( iTeam );
	//std::vector<Attackable*>::iterator end = Game::getEnemiesEnd( iTeam );

	//for( ; it != end; ++it ) {
		/* If in range and alive, set as target. */
	//	if( inRange( pCurrPoint, (*it)->getPos(), perception ) && (*it)->health > 0 ) {
	//		pTarget = *it;
	//		break;
	//	}
	//}
}

/*
* Check if the target is alive and in range. Set the pTarget to NULL if either are true.
*/
void Creep::CheckTarget( void ) {
	/* Target is DEAD. */
	if( pTarget->health <= 0 )
		pTarget = NULL;
	/* Or Target is out of range.  */
	else if ( inRange( pCurrPoint, pTarget->getPos(), perception) == false )
		pTarget = NULL;
	
}

/*
* If we have an attackable target, attack.
*/
//void Creep::Update() {
//
//	/* If we have a Target, check their status. */
//	if( pTarget != NULL )
//		CheckTarget();
//
//	/* Search for Target. */
//	if( pTarget == NULL )
//		FindTarget();
//
//	/* If we found a new Target, and they are in range.. */
//	if( pTarget != NULL ) {
//		Attack();
//		Rotate( pTarget->getPos() );
//	}
//}

/*
* Rotate towards the target. Used for either a path, or a target. 
*/
float Creep::Rotate( Point pt ) {
	return atan2( (float)pCurrPoint.y - pt.y, (float)pCurrPoint.x - pt.x );
}

string Creep::serializeCreep(const Creep& creep)
{

}
