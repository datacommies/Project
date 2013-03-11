#ifndef CREEP_H
#define CREEP_H

#include "../resource.h"
//#include "unit.h"
#include "mobile_unit.h"

class Creep : public MobileUnit
{
public: 
   void spawn(const int& num);  //also creep type? when we have a type
   void serializeCreep(const Creep& creep);
private:
};

#endif
