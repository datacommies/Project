#ifndef CREEP_H
#define CREEP_H

#include "../resource.h"
#include "unit.h"

class Creep : public MobileUnit
{
public: 
   void spawn(const int& num);  //also creep type? when we have a type
private:
};

#endif
