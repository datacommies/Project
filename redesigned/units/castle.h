#ifndef CASTLE_H
#define CASTLE_H

#include "../resource.h"
#include "../types.h"
#include "tower.h"

class Castle : public Tower
{
public:
	std::string serializeCastle(const Castle& castle);

	virtual UnitTypes getType() const { return TYPE_CASTLE; }
	virtual size_t getSize() const { return sizeof(Castle); }

private:   
};

#endif
