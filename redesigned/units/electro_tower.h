#ifndef ELECTRO_TOWER_H
#define ELECTRO_TOWER_H

#include "tower.h"

class ElectroTower : public Tower
{
public:

    ElectroTower(int uid, Point pos, int hp, int atkdmg, int atkrng,
int atkspd, int percep, int atkcnt, int wall);
    void    Attack(Team*);
    void    Update(Team&);

private:
};

#endif
