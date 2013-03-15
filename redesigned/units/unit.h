#ifndef UNIT_H
#define UNIT_H

#include "../resource.h"
#include "../types.h"
//#include "../team.h"

class Team;

class Unit
{
public:
    
    int id; //unit id
    Point position;
    int health;
    int iElement;
    int attackDamage;//damage that the unit deals per hit
    int attackRange; //distance that the unit can successfully attack
    int attackSpeed; //the speed which the attack counter has to hit in order to initiate an attack
    int perception;  //distance that the unit can aquire a target
    int attackCount; //counter between unit attacks
    Unit *pTarget;
    
    bool            isAlive() { return health > 0; } //incase creep get hits more than its remaining health
    virtual void    Attack(void);
    virtual void    Update(Team&);
    void            setTarget(Unit &newTarget) { pTarget = &newTarget; }
    float           Rotate(Point); 
    void            setDamage(int newDamage) { attackDamage = newDamage;  }
    void            setRange(int newRange) { attackRange = newRange; }
    bool            inRange(Point, Point, int);
    virtual void    CheckTarget(void);
    virtual void    FindTarget(Team* team); // MAKE IMPL
    bool            hasWeakness(int, int);
    bool            hasStrength(int, int);
    Point           getPos() { return position; }

    std::string serializeUnit();
    
    Unit(int uid, Point pos, int hp, int atkdmg, int atkrng,
         int atkspd, int percep, int atkcnt);
    
    virtual UnitType getType() const = 0;
    virtual size_t getSize() const { return sizeof(unit_t); };
private:   
};
#endif
