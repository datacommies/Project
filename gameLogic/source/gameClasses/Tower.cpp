#include "Tower.h"
#include <iostream>
using namespace std;


//written by Kevin T.
Tower::Tower(const int& teamID, const int& hp, const int& xPos, const int& yPos, const int& typeTower, const int& attackRadius, const int& attackSpeed, const int& attackDamage): StaticUnit(teamID, hp, xPos, yPos), typeTower_(typeTower){
		cout << "Tower built at position " << xPos << ", " << xPos << endl;
	}

void Tower::Run()
{
	int hp = getHP();
	// 1) check for attacks from enemy units, adjust healthPoints if needed
	
	// 2) check tower's healthPoints, if zero then tower is destroyed
	//if(healthPoints_ == 0){
	if(hp == 0){
		//call some kind of terminate() function for tower
		cout << "Tower ID destroyed!" << endl;
	}
	
	// 3) call AI functions to check for enemies in attack range, attack if needed 
	//if(enemy in attackRadius_){
	//	attackEnemy(x, y);
	//}
	
	// 4) call updateStats()
	//updateStats(struct towerStruct);
}

void Tower::attackEnemy(int x, int y)		
{
	cout << "Attacking enemy" << endl;
	// attack enemy at position x,y on map
	// use attack functions provided by AI team
}

void Tower::setAttackRadius(int radius)
{
	attackRadius_ = radius;	 	// set attackRadius_ to "radius"
}

int Tower::getAttackRadius()
{
	return attackRadius_;		// return unit's current attackRadius_
}

void Tower::setAttackSpeed(int speed)
{
	attackSpeed_ = speed;	 	// set attackSpeed_ to "speed"
}

int Tower::getAttackSpeed()
{
	return attackSpeed_;		// return unit's current attackSpeed_
}

void Tower::setAttackDamage(int damage)
{
	attackDamage_ = damage;	 	// set attackDamage_ to "damage"
}

int Tower::getAttackDamage()
{
	return attackDamage_;		// return unit's current attackDamage_
}

/* To test to see if this class compiles type:
 * g++ -Wall -DTESTCOMPILE Tower.cpp */
#ifdef TESTCOMPILE

int main() {
    return 0;
}

#endif
