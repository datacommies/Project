#ifndef UNIT_H
#define UNIT_H

#include "../resource.h"
#include "../types.h"

class Unit
{
public:
    int id; //unit id
    Point position;
    int health;
    int attackDamage;//damage that the unit deals per hit
    int attackRange; //distance that the unit can successfully attack
    int attackSpeed; //the speed which the attack counter has to hit in order to initiate an attack
    int perception;  //distance that the unit can aquire a target
    int attackCount; //counter between unit attacks
    bool            isAlive() { return health > 0; } //incase creep get hits more than its remaining health
    void            Attack( void );
    virtual void    Update( void );
    void            setTarget( Unit &newTarget ) { pTarget = &newTarget; }
    float           Rotate( Point ); 
    void            setDamage( int newDamage ) { attackDamage = newDamage;  }
    void            setRange( int newRange ) { attackRange = newRange; }
    bool            inRange( Point, Point, int );
    virtual void    CheckTarget( void );
    virtual void    FindTarget( void );
    bool            hasWeakness( int, int );

    std::string serializeUnit(const Unit& unit);
    
    Unit(const int& uid, Point pos, const int& hp, const int& atkdmg, const int& atkrng,
        const int& atkspd, const int& percep, const int& atkcnt);
    
    virtual UnitTypes getType() const = 0;
    virtual size_t getSize() const = 0;
private:   
};



#endif
