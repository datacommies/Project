#include "Attackable.h"
#include "Attacker.h"
#include "Game.h"
#include <vector>
#include <algorithm>
#include <Windows.h>
#include "header.h"

	using namespace std;

	/*
	*Returns an iterator to the enemy's vector, so you can check if they are attackable. 
	*/
	vector<Attackable*>::iterator Game::getEnemiesBegin( int TeamNumber ) { 
			return TeamNumber == 2 ?  vTeamOne.begin() : vTeamTwo.begin() ;
	}

	/*
	*Returns an iterator to the end of enemy's vector. 
	*/
	vector<Attackable*>::iterator Game::getEnemiesEnd( int TeamNumber ) {
		return TeamNumber == 2 ?  vTeamOne.end() : vTeamTwo.end() ;
	}

	/*
	*Returns an iterator to the attacker's vector, so you can update all Attackers.
	*/
	vector<Attacker*>::iterator Game::getAttackersBegin( int TeamNumber ) { 
			return TeamNumber == 1 ?  vAOne.begin() : vATwo.begin() ;
	}
		
	/*
	* Returns an iterator to the end of the attacker's vector. 
	*/
	vector<Attacker*>::iterator Game::getAttackersEnd( int TeamNumber ) {
		return TeamNumber == 1 ?  vAOne.end() : vATwo.end() ;
	}

	/*
	* Returns the enemy's castle. For ease of access /  priority. 
	*/
	Attackable* Game::getCastle( int TeamNumber ) { 
		return TeamNumber == 1 ?  cOne : cTwo ;
	}

	/*
	* Adds a castle to a team. 
	*/
	void Game::addCastle( Attackable *unit, int TeamNumber ) {
		TeamNumber == 1 ?  cOne = unit : cTwo = unit;
		addUnit( unit, TeamNumber );
	}

	/*
	* Adds a unit to a team. 
	*/
	void Game::addUnit ( Attackable *unit, int TeamNumber ) {
		TeamNumber == 1 ? vTeamOne.push_back( unit ) : vTeamTwo.push_back( unit  );
	}

	/*
	* Adds an attacker to a team. 
	*/
	void Game::addAttacker ( Attacker *unit, int TeamNumber ) { 
		TeamNumber == 1 ? vAOne.push_back( unit ) : vATwo.push_back( unit  );
		addUnit( unit, TeamNumber );
	}

	/*
	* Removes a unit after they are killed / sold. 
	*/
	void Game::removeUnit( Attackable *unit, int TeamNumber ) {
		if( TeamNumber == 1 ) {
			vTeamOne.erase( remove( vTeamOne.begin(), vTeamOne.end(), unit ), vTeamOne.end() );
			vAOne.erase( remove( vAOne.begin(), vAOne.end(), unit ), vAOne.end() );
		} else {
 			vTeamTwo.erase( remove( vTeamTwo.begin(), vTeamTwo.end(), unit ), vTeamTwo.end() );
			vATwo.erase( remove( vATwo.begin(), vATwo.end(), unit ), vATwo.end() );
		}
	}

	/*
	* Spawn Creep will create a creep at 0, 0, on team 1. 
	* Path is evently picked between the three.
	* Should just be using pathSelected, and changing it on user input.
	* HARDCODED for testing purposes. 
	*/
	void Game::SpawnCreep( void ) {
		DPS d = DPS();
		d.pCurrPoint.x = 0;
		d.pCurrPoint.y = 0;

		d.setPath( path[pathSelected++ % 3] );
		d.setTeam( 1 );

		Game::addAttacker( new DPS( d ) , 1 );
	}

	/*
	* Set the towereSelected to the new tower. 
	*/
	void Game::SelectTower( int tower ) {
		Game::towerSelected = tower; 
	}

	/*
	* placeTower will create a new tower, set the team, x, and y correctly 
	* and then add them to the Attacker list for their team.
	*/
	void Game::placeTower( int iTeam, int iTower, int x, int y ) {
		MultiShot temp = MultiShot();
	
		/*
		Tower *temp;
		switch( iTower ) {
			case 1: temp = new SingleShot(); break;
			case 2: temp = new MultiShot(); break;
			case 3: temp = new AreaShot(); break;
		}
		*/
		temp.pCurrPoint.x = x * SQUARE_SIZE;
		temp.pCurrPoint.y = y * SQUARE_SIZE;

		temp.setTeam( iTeam );

		/*Add to game.*/

		Game::addAttacker( new MultiShot( temp ) , iTeam ); 
	}

	/*
	* CheckSquare will check the game's field if that spot is availaible.
	* Could use for checking if a user clicks on a turret. 
	* Then iterate over Attackers.
	*/
	bool Game::CheckSquare( int x, int y )  {
		/* Check against some sort of game-field. */
		//if( field[ x ][ y ].id  == -1 )
			return true;
		return false;
	}

	/*
	* BuildTower will check the clicked on square, 
	* and if they can place it, then place it.
	*/
	void Game::BuildTower( int iTeam, int iTower, int x, int y ) {
		/* Offset for mouse.*/
		x -= SQUARE_SIZE;
		y -= SQUARE_SIZE;

		int row, col;
		col = ceil( (double) y / SQUARE_SIZE );
		row = ceil( (double) x / SQUARE_SIZE );

		if( Game::CheckSquare( row, col ) == false )
			return;

		/*Check if they can afford it.*/

		Game::placeTower( iTeam, iTower, row, col );	
	}
