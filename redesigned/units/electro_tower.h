/*------------------------------------------------------------------------------
-- FILE: electro_tower.h
--
-- DATE: 2013/03/11
--
-- MAINTAINERS: Nick Raposo
--              Aiko Rose
-- FUNCTIONS: Attack
-- Update
--
-- DESCRIPTION: This inherits from Tower class. Attack() and Update() are overridden.
------------------------------------------------------------------------------*/


#ifndef ELECTRO_TOWER_H
#define ELECTRO_TOWER_H

#include "tower.h"

class ElectroTower : public Tower
{
public:

    ElectroTower(int uid, Point pos, int hp, int atkdmg, int atkrng,
int atkspd, int percep, int atkcnt, int wall);

    ElectroTower(int uid, int side, Point pos, int hp=200, int atkdmg=15, int atkrng=20,
        int atkspd=30, int percep=30, int atkcnt=0, int wall=0);

    void    Attack(Team*);
    virtual void    Update(Team& team){
	    /* If we have a Target, check their status. */
	    if( pTarget != NULL )
	        CheckTarget();

	    /* Search for Target. */
	    if( pTarget == NULL )
	        FindTarget(&team);

	    /* If we found a new Target, and they are in range.. */
	    if( pTarget != NULL ) {
	        Attack(&team);
	        //cout << "Elec att" << endl;
	    }
	}
    virtual UnitType getType() const { return TOWER_TWO; }
private:
};

#endif
