#include "Creep.h"

Creep::Creep(const int& teamID, const int& hp, const int& xPos, const int& yPos, const int& lane, const int& type):
 MobileUnit(teamID, hp, xPos, yPos){
    //based on creep type, init attack/move related things
}

int getLane(){
    return lane_;
}

int getType(){
    return type_;
}

void setLane(const int& lane){
    lane_ = lane;
}


