#include "unit.h"
#include "creep.h"
#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

Creep::Creep(int uid, Point pos, int hp, int atkdmg, int atkrng,
         int atkspd, int percep, int atkcnt, int spd, Direction direct,
         Point* path, int movespeed): MobileUnit(uid, pos, hp, atkdmg, atkrng, atkspd,
         percep, atkcnt,spd, direct), pPath(path)
{
    //validation
}

ifdef 1
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
void Creep::Update( Team& team ) {
    /* Check if we are at the next path point.  */
    if( pPath->x == position.x && pPath->y == position.y ) {
        nextPoint();
    }
    
    /*If we have a Target check their stats. */
    if( pTarget != NULL ) 
        CheckTarget();
    
    /* Search for Target. */
    if( pTarget == NULL ) {
        FindTarget(team);
    if( pTarget != NULL && pSaved == NULL )
        pSaved = &position;
    
    }
    
    /* If we found a new Target. */
    if( pTarget != NULL ) {
        if( inRange( position, pTarget->position, attackRange ) )
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

void Creep::Move( Point pt ) {
         pCurrPoint.x += getDirection( pCurrPoint.x, pt.x ) * moveSpeed;
         pCurrPoint.y += getDirection( pCurrPoint.y, pt.y )  * moveSpeed;
}

#endif
string Creep::serializeCreep()
{
    string s = MobileUnit::serializeMobileUnit();
    
    return s;
}

