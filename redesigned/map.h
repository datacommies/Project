#ifndef SERVERGAMELOGIC_H
#define SERVERGAMELOGIC_H

#include <vector>
#include "resource.h"
#include "units/player.h"
#include "units/creep.h"
#include "units/tower.h"
#include "units/projectile.h"

public class Map
{
public:
	Map(int width, int height) : width_(width), height_(height) { }
private:
	Unit* map_[width_][height_];
	int width_;
	int height_;
};

#endif