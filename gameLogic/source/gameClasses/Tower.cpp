#include "Tower.h"
using namespace std;

//written by Kevin T.
//this .cpp needs the constructor implementation
void Tower::run()
{
	// 1) check for attacks from enemy units, adjust healthPoints if needed
	
	// 2) check tower's healthPoints, if zero then tower is destroyed
	if(healthPoints == 0){
		//call some kind of terminate() function for tower
	}
	
	// 3) call AI functions to check for enemies in attack range, attack if needed 
	if(enemy in attackRadius_){
		attackEnemy(x, y);
	}
	
	// 4) call updateStats()
	updateStats(struct towerStruct);
}

void Tower::attackEnemy(int x, int y)		
{
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

