#ifndef GAME_H
#define GAME_H

class Game {
	public:
		/* Castle for Team One and Two. */
		static Attackable *cOne, *cTwo;

		/* Attackable for Team One and Two. */
		static std::vector<Attackable*> vTeamOne, vTeamTwo;

		/* Attackers for Team One and Two. */
		static std::vector<Attacker*> vAOne, vATwo;

		/* User's Tower Selected. */
		static int towerSelected;
		/* User's Path Selected. */
		static int pathSelected;
		/* Paths. */
		static Point path[3][3];
	

		/*
		*Returns an iterator to the enemy's vector, so you can check if they are attackable. 
		*/
		static std::vector<Attackable*>::iterator getEnemiesBegin( int TeamNumber );

		/*
		*Returns an iterator to the end of enemy's vector. 
		*/
		static std::vector<Attackable*>::iterator getEnemiesEnd( int TeamNumber );
		/*
		*Returns an iterator to the attacker's vector, so you can update all Attackers.
		*/
		static std::vector<Attacker*>::iterator getAttackersBegin( int TeamNumber );
		/*
		* Returns an iterator to the end of the attacker's vector. 
		*/
		static std::vector<Attacker*>::iterator getAttackersEnd( int TeamNumber );
		/*
		* Returns the enemy's castle. For ease of access /  priority. 
		*/
		static Attackable* getCastle( int TeamNumber );

		/*
		* Adds a castle to a team. 
		*/
		static void addCastle( Attackable *unit, int TeamNumber );
		/*
		* Adds a unit to a team. 
		*/
		static void addUnit ( Attackable *unit, int TeamNumber );

		/*
		* Adds an attacker to a team. 
		*/
		static void addAttacker ( Attacker *unit, int TeamNumber );

		/*
		* Removes a unit after they are killed / sold. 
		*/
		static void removeUnit( Attackable *unit, int TeamNumber );

		static void Game::SelectTower( int tower );

		static void Game::SpawnCreep( void );

		static void Game::placeTower( int iTeam, int iTower, int x, int y );

		static void Game::BuildTower( int iTeam, int iTower, int x, int y );

		static bool Game::CheckSquare( int x, int y );
};

#endif