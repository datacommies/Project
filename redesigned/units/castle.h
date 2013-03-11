#ifndef CASTLE_H
#define CASTLE_H

#include "../resource.h"
#include "tower.h"

class Castle : public Tower
{
public:
	void serializeCastle(const Castle& castle);
private:   
};

#endif
