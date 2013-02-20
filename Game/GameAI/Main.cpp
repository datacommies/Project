#include <stdio.h>
#include <iostream>
#include <vector>

#include "Attackable.h"
#include "Attacker.h"
#include "Point.h"
#include "Creep.h"
#include "Tower.h"
#include "Game.h"

using namespace std;

vector<Attackable*> Game::vTeamOne, Game::vTeamTwo;
Castle cEnemy;
vector<Attacker*> Game::vAOne, Game::vATwo;
Attackable& Game::cOne = cEnemy, Game::cTwo = cEnemy;
int main( int argc, const char* argv[] ) {

	Point a = Point();
	a.x = 0, a.y = 0;
	Point b = Point();
	b.x = 100, b.y = 0;
	Point c = Point();
	c.x = 100, c.y = 100;
	Point path[] = { a, b, c };

	Point *start = path;

	cEnemy = Castle();
	cEnemy.pCurrPoint.x = 100,  cEnemy.pCurrPoint.y = 100;
	cEnemy.setTeam( 2 );


	//Team One - Single DPS.
	DPS d = DPS();
	d.pCurrPoint.x = 50;
	d.pCurrPoint.y = 0;
	d.setPath( start );
	d.setTarget( cEnemy );
	d.setTeam( 1 );


	//Team Two -- Castle / Tower.
	SingleShot ss = SingleShot();
	ss.pCurrPoint.x = 90;
	ss.pCurrPoint.y = 80;
	ss.setTarget( d );
	ss.setTeam( 2 );

	Game::addCastle( &cEnemy, 2 );
	Game::addUnit( &cEnemy, 2 );
	Game::addUnit( &d, 1 );
	Game::addUnit( &ss, 2 );
	Game::addAttacker( &d, 1 );
	Game::addAttacker( &ss, 2 );


	int index = 0;
	std::vector<Attacker*>::iterator it;
	std::vector<Attacker*>::iterator end;
	//for(int i = 0; i < 12; i++ ){
	while( Game::getEnemyCastle( 1 ).iHp > 0 ) {
		for( index = 1; index < 3; index++ ) {
			
			it = Game::getAttackersBegin( index );
			end = Game::getAttackersEnd( index );
			for( ; it != end; ++it ) {
				(*it)->Update();
			}
		}
	}
	// Enemy of Team One.
	cout << "Game over. 1 " << Game::getEnemyCastle( 1 ).name << " " << Game::getEnemyCastle( 1 ).iTeam << " HP=" << Game::getEnemyCastle( 1 ).iHp <<  endl;
	cout << "Game over. 2 " << Game::getEnemyCastle( 2 ).name << " " << Game::getEnemyCastle( 2 ).iTeam << " HP=" << Game::getEnemyCastle( 2 ).iHp <<  endl;




	getchar();
	return 0;
}