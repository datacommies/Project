#ifndef GAME_H
#define GAME_H

#include "Attackable.h"
#include <vector>

class Game {
	public:
		/* Castle for Team One and Two. */
		static Attackable& cOne, cTwo;

		/* Other Attackable Units for Team One and Two. */
		static std::vector<Attackable*> vTeamOne, vTeamTwo;
		static std::vector<Attacker*> vAOne, vATwo;

		static std::vector<Attackable*>::iterator getEnemiesBegin( int TeamNumber ) { 
			if( TeamNumber == 2 )
				return vTeamOne.begin();
			else
				return vTeamTwo.begin();
		}

		static std::vector<Attackable*>::iterator getEnemiesEnd( int TeamNumber ) {
			if( TeamNumber == 2 )
				return vTeamOne.end();
			else
				return vTeamTwo.end();
		}

		
		static std::vector<Attacker*>::iterator getAttackersBegin( int TeamNumber ) { 
			if( TeamNumber == 2 )
				return vAOne.begin();
			else
				return vATwo.begin();
		}

		static std::vector<Attacker*>::iterator getAttackersEnd( int TeamNumber ) {
			if( TeamNumber == 2 )
				return vAOne.end();
			else
				return vATwo.end();
		}

		static Attackable getEnemyCastle( int TeamNumber ) { 
			if( TeamNumber == 1 )
				return cOne;
			else 
				return cTwo;
		}

		static void addCastle( Attackable *unit, int TeamNumber ) {
			if(	TeamNumber == 1 )
				cOne = *unit;
			else
				cTwo = *unit;
		}

		static void addUnit ( Attackable *unit, int TeamNumber ) { 
			if( TeamNumber == 1 )
				vTeamOne.push_back( unit );
			else
				vTeamTwo.push_back( unit );
		}

		static void addAttacker ( Attacker *unit, int TeamNumber ) { 
			if( TeamNumber == 1 )
				vAOne.push_back( unit );
			else
				vATwo.push_back( unit );
		}
};

#endif