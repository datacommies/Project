/*------------------------------------------------------------------------------
-- FILE:        AiConroller.cpp
--
-- DATE:        2013/03/11
--
-- MAINTAINERS: Nick Raposo
--
-- FUNCTIONS:   AiUpdate(Team&, Team&)
--
-- DESCRIPTION: Runs 1 "Turn" of AI. Every creep, tower, and projectile gets
--		an Update() called on it.
------------------------------------------------------------------------------*/
#include "AiController.h"
#include "../team.h"

void AiUpdate(Team& team1, Team& team2)
{

	//loop through team 1 creeps
	for (size_t creep_idx = 0; creep_idx < team1.creeps.size(); ++creep_idx)
	{
		team1.creeps[creep_idx].Update(team2);
	}

	//loop through team 1 towers
	for (size_t tower_idx = 0; tower_idx < team1.towers.size(); ++tower_idx)
	{
		team1.towers[tower_idx].Update(team2);
	}

	//loop through team 1 projectiles
	for (size_t projectile_idx = 0; projectile_idx < team1.projectiles.size(); ++projectile_idx)
	{
		team1.projectiles[projectile_idx].Update();
	}

	//loop through team 2 creeps
	for (size_t creep_idx = 0; creep_idx < team2.creeps.size(); ++creep_idx)
	{
		team2.creeps[creep_idx].Update(team1);
	}

	//loop through team 2 towers
	for (size_t tower_idx = 0; tower_idx < team2.towers.size(); ++tower_idx)
	{
		team2.towers[tower_idx].Update(team1);
	}

        //loop through team 2 projectiles
        for (size_t projectile_idx = 0; projectile_idx < team2.projectiles.size(); ++projectile_idx)
       	{
                team2.projectiles[projectile_idx].Update();
       	}
}
