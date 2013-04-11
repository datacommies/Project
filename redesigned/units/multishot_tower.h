/*------------------------------------------------------------------------------
-- FILE: multishot_tower.h
--
-- DATE: 2013/03/20
--
-- PROGRAMMER: Aiko Rose
--
-- FUNCTIONS: Attack(Team*)
-- 
--
-- DESCRIPTION: MultiShotTower inherits from Tower.
-- The function Attack() is declared.
------------------------------------------------------------------------------*/


#ifndef MULTISHOT_TOWER_H
#define MULTISHOT_TOWER_H

#include "tower.h"


class MultiShotTower : public Tower
{
public:
    Team * team; // other team for multishot damage calculations
    
    MultiShotTower(int uid, Point pos, int hp, int atkdmg, int atkrng,
		int atkspd, int percep, int atkcnt, int wall, Team * t,
		int mulsdmg, int mulsrng);
    
    void Attack(Team*);
private:
};

#endif
