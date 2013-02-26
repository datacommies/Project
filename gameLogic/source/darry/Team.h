#ifndef _TEAM_H_
#define _TEAM_H_

#include "Player.h"

#define NUM_PLAYERS_PER_TEAM 5

// This differs slightly from the documentation..
class Team {
  long _team_id;
  Player _players[NUM_PLAYERS_PER_TEAM];
};

#endif
