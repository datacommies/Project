#ifndef _TEAM_H_
#define _TEAM_H_

#include "Player.h"

#define NUM_PLAYERS_PER_TEAM 5

// This differs slightly from the documentation..
// This will use polymorphism...
//Darry, what do you mean by this ^above^?  - Callum

class Team {
public:
  long _team_id;
  Player *_players[NUM_PLAYERS_PER_TEAM];
  //init these from the lobby
  int castlePlayerID_;
  int playerOneID_;
  int playerTwoID_;
  int playerThreeID_;
  int playerFourID_;
};

#endif
