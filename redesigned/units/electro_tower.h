#ifndef ELECTRO_TOWER_H
#define ELECTRO_TOWER_H

#include "tower.h"

class ElectroTower : public Tower
{
public:

    ElectroTower(int uid, Point pos, int hp, int atkdmg, int atkrng,
int atkspd, int percep, int atkcnt, int wall);

    ElectroTower(int uid, int side, Point pos, int hp=100, int atkdmg=0, int atkrng=0,
        int atkspd=0, int percep=0, int atkcnt=0, int wall=0);

    void    Attack(Team*);
    void    Update(Team&);

private:
};

#endif
