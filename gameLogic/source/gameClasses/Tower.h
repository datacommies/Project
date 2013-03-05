#ifndef TOWER_H
#define TOWER_H


//written by Kevin T.
#include "StaticUnit.h"

class Tower: public StaticUnit{
public:
    virtual void run();

    void attackEnemy(int x, int y);

    void setAttackRadius(int radius);
    
    int getAttackRadius();
    
    void setAttackSpeed(int speed);
    
    int getAttackSpeed();
    
    void setAttackDamage(int damage);
    
    int getAttackDamage();

private:
    //tower type should be an int, strings are annoying + we can define a name for each type
    int typeTower_;      // type of tower (i.e. basic or some upgrade type)
    int attackRadius_;      // radius of attack for tower
    int attackSpeed_;       // frequency of attack for tower
    int attackDamage_;      // strength of attack for tower
};

#endif