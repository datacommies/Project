#ifndef UNIT_H
#define UNIT_H

#include "../resource.h"
#include "../types.h"

class Team;

class Unit
{
public:
    int id; //unit id
    int team; //the team the unit is on 
    Point position; //the units team
    int health; //the current health amount
    int maxHealth; // the maximum health
    int iElement; //units element, fire/water etc.
    int attackDamage;//damage that the unit deals per hit
    int attackRange; //distance that the unit can successfully attack
    int attackSpeed; //the speed which the attack counter has to hit in order to initiate an attack
    int perception;  //distance that the unit can aquire a target
    int attackCount; //counter between unit attacks
    Unit *pTarget;
    float fRotate;
    bool pendingDelete;

    
    bool            isAlive() { return health > 0; } //incase creep get hits more than its remaining health
    virtual void    Attack(void);
    virtual void    Update(Team&);
    void            setTarget(Unit &newTarget) { pTarget = &newTarget; }
    void           Rotate(Point); 
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

    Unit(int uid, int side, Point pos, int hp=200, int atkdmg=10, int atkrng=0,
         int atkspd=0, int percep=0, int atkcnt=0);
    
    virtual ~Unit(){};

    virtual UnitType getType() const = 0;
    virtual size_t getSize() const { return sizeof(unit_t); };
private:   
};
#endif
