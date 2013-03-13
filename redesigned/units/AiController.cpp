#include "AiController.h"
#include "../team.h"
/*

AI Controller

*/

void AiUpdate(Team& team1, Team& team2)
{

	for (int creep_idx = 0; creep_idx < team1.creeps.size(); ++creep_idx)
	{
		team1.creeps[creep_idx].Update(team2);
	}
	for (int tower_idx = 0; tower_idx < team1.towers.size(); ++tower_idx)
	{
		team1.towers[tower_idx].Update(team2);
	}

	for (int creep_idx = 0; creep_idx < team2.creeps.size(); ++creep_idx)
	{
		team2.creeps[creep_idx].Update(team1);
	}
	for (int tower_idx = 0; tower_idx < team2.towers.size(); ++tower_idx)
	{
		team2.towers[tower_idx].Update(team1);
	}
}