#include "Tower.h"
using namespace std;

class Tower inherits from StaticUnit{
public:
	run()
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

	void attackEnemy(int x, int y)		
	{
		// attack enemy at position x,y on map
		// use attack functions provided by AI team
	}

	void setAttackRadius(int radius)
	{
		attackRadius_ = radius;	 	// set attackRadius_ to "radius"
	}
	
	int getAttackRadius()
	{
		return attackRadius_;		// return unit's current attackRadius_
	}
	
	void setAttackSpeed(int speed)
	{
		attackSpeed_ = speed;	 	// set attackSpeed_ to "speed"
	}
	
	int getAttackSpeed()
	{
		return attackSpeed_;		// return unit's current attackSpeed_
	}
	
	void setAttackDamage(int damage)
	{
		attackDamage_ = damage;	 	// set attackDamage_ to "damage"
	}
	
	int getAttackDamage()
	{
		return attackDamage_;		// return unit's current attackDamage_
	}


private:
	string typeTower_;		// type of tower (i.e. basic or some upgrade type)
	int attackRadius_;		// radius of attack for tower
	int attackSpeed_;		// frequency of attack for tower
	int attackDamage_;		// strength of attack for tower
}
