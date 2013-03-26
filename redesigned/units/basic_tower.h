/*------------------------------------------------------------------------------
-- FILE:        basic_tower.h
--
-- DATE:        2013/03/12
--
-- MAINTAINERS: Cody Rossiter
--		Kevin Tangeman - 26/Mar/2013 - added team variable "side"
-- 			and default values in constructor
--
-- FUNCTIONS:   Attack
--
-- DESCRIPTION: File contains declaration for the basic_tower class.
--              BasicTower inherits from Tower.
--              BasicTower is the default tower. It targets a single unit.
------------------------------------------------------------------------------*/
#ifndef BASIC_TOWER_H
#define BASIC_TOWER_H

#include "tower.h"

class BasicTower : public Tower
{
public:

    BasicTower(int uid, Point pos, int hp, int atkdmg, int atkrng,
          int atkspd, int percep, int atkcnt, int wall);

    BasicTower(int uid, int side, Point pos, int hp=100, int atkdmg=0, int atkrng=0,
          int atkspd=0, int percep=0, int atkcnt=0, int wall=0);
          
    virtual void Attack(void);

	
private:  
};

#endif
