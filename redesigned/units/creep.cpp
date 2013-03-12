#include "unit.h"
#include "creep.h"
#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

Creep::Creep(const int& uid, Point pos, const int& hp, const int& atkdmg, const int& atkrng,
         const int& atkspd, const int& percep, const int& atkcnt, const int& spd, Direction direct,
         Point* path, const int& movespeed): MobileUnit(uid, pos, hp, atkdmg, atkrng, atkspd,
         percep, atkcnt,spd, direct), pPath(path), moveSpeed(movespeed)
{
    //validation
}

/*
* Function to return the difference in two points. Used for movement. 
*/
int Creep::getTargetDirection( int p1, int p2 ) {
    if( p1 < p2 ) /*Target is below or right. */
        return 1;
    else if ( p1 > p2 )  /* Target is above or left. */
        return -1;
    else /* Target on the same level. */
        return 0;
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

